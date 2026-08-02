/************************************************************************************/
/*! \file           T1_flexInterface.h
 *
 *  \brief          T1.flex interface declarations and macros
 *
 *  \par Visibility
 *                  External
 *
 *  \author nick
 *
 *  \version 3.5.0.0 r67267
 *
 *  \copyright GLIWA embedded systems GmbH & Co. KG, Weilheim i.OB. All rights reserved
 ************************************************************************************/

#ifndef T1_FLEX_INTERFACE_H_
#define T1_FLEX_INTERFACE_H_ ( 1 )

/*!
 * \defgroup T1_flex T1.flex
 * \brief
 *
 * see \ref T1_flex_page
 *
 * @{
 */

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_scopeInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- macros required for type definitions -----------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_TRICORE
#    define T1_NOF_TRICORE_BPS ( 5u )
/* clang-format off */
#    define T1_EXCEPTION_HANDLER_PARAMS             \
        T1_flexAddr_t pInterruptedAddress,          \
        T1_flexAddr_t addrToSet,                    \
        T1_uint32_t pcxi,                           \
        T1_flexAddr_t pReturnAddress,               \
        struct T1_flexGlobalsStruct_t *pFlexGlobals
#elif defined T1_ARM7M
#    define T1_EXCEPTION_HANDLER_PARAMS             \
        T1_flexAddr_t *pIntrptStackFrame,           \
        struct T1_flexGlobalsStruct_t *pFlexGlobals
#elif defined T1_MPC5XXX
#    define T1_EXCEPTION_HANDLER_PARAMS             \
        T1_flexAddr_t pReturnAddress,               \
        T1_flexAddr_t pInterruptedAddress,          \
        T1_flexAddr_t pNextCodeAddress,             \
        struct T1_flexGlobalsStruct_t *pFlexGlobals
#else
#    define T1_EXCEPTION_HANDLER_PARAMS             \
        T1_flexAddr_t pReturnAddress,               \
        T1_flexAddr_t pInterruptedAddress,          \
        struct T1_flexGlobalsStruct_t *pFlexGlobals
/* clang-format on */
#endif

#define T1_NOF_DBGBCR_VALS       ( 4 )
#define T1_NOF_UED_FILTER_RANGES ( 2 )
#define T1_UED_FILTER_VALS       ( 2 ) /* min/max */
#define T1_NOF_CODE_BP_HANDLERS  ( 10 )
#define T1_NOF_DATA_BP_HANDLERS  ( 11 )
#define T1_NOF_DATA_BP_KINDS     ( 2 ) /* read/write */
#define T1_NOF_SW_HANDLERS       ( 20 )
#define T1_NOF_RESTR_TYPE        ( 2 )

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if !defined T1_TARGET_ADDRESS_TYPE
typedef T1_uint32_t T1_flexAddr_t;
#endif /* defined T1_TARGET_ADDRESS_TYPE */

/*! \brief Used to store address ranges */
typedef struct
{
    T1_flexAddr_t begin;
    T1_flexAddr_t end;
} const T1_flexRange_t;

struct T1_flexGlobalsStruct_t;

/*! \brief T1.flex global data for one core. */
typedef struct T1_flexGlobalsStruct_t
{
    T1_uint16Least_t flexBpBudget_; /* 32-bit type is too expensive on C166 */
#if defined T1_TRICORE
    void ( *pTrxHandler[T1_NOF_TRICORE_BPS] )( T1_EXCEPTION_HANDLER_PARAMS );
#else  /* not TriCore */
    void ( *pCodeBpBHandler_ )( T1_EXCEPTION_HANDLER_PARAMS );
    /* pCodeBpAHandler and pDataBpAHandler are adjacent for targets with 1 code BP. */
    void ( *pCodeBpAHandler_ )( T1_EXCEPTION_HANDLER_PARAMS );
#endif /* defined T1_TRICORE */
    void ( *pDataBpAHandler_ )( T1_EXCEPTION_HANDLER_PARAMS );
    void ( *pDataBpAWriteHandler_ )( T1_EXCEPTION_HANDLER_PARAMS );
    void ( *pDataBpBHandler_ )( T1_EXCEPTION_HANDLER_PARAMS );
    void ( *pDataBpBWriteHandler_ )( T1_EXCEPTION_HANDLER_PARAMS );
    void ( *pAfterSwStopAHandler_ )( T1_EXCEPTION_HANDLER_PARAMS );
    T1_flexAddr_t pAfterSwStopAAddr_;
    void ( *pAfterSwStopBHandler_ )( T1_EXCEPTION_HANDLER_PARAMS );
    T1_flexAddr_t pAfterSwStopBAddr_;
#if defined T1_FLEX_SINGLESTEP || defined T1_TRICORE
    void ( *pSavedBpHandler_ )( T1_EXCEPTION_HANDLER_PARAMS );
#endif /* defined T1_FLEX_SINGLESTEP || defined T1_TRICORE */
    T1_uint8Least_t savedIcuReg_;
    T1_uint8Least_t savedIcuRegB_;

    T1_uint16_t savedPreemptionCounter_[T1_NOF_RESTR_TYPE];
    volatile T1_uint16_t preemptionCounter_;
    T1_uint8_t cftStateOrRestrType_;
    T1_uint8_t flexBufferLastIdx_;

#if defined T1_FLEX_SINGLESTEP
#    if defined T1_ARM7R
    T1_uint16_t dbgbcrVals[T1_NOF_DBGBCR_VALS];
    T1_uint32_t savedCRVal_;
    T1_uint32_t volatile *pDBGplus0x100_;
    T1_flexAddr_t savedCodeAddrA_;
    T1_flexAddr_t savedStepAddr_;
    T1_flexAddr_t flexCallTrustedFunctionAddr;
    T1_flexAddr_t pInterruptedAddress_;
#    elif defined T1_ARM8R
    T1_uint32_t savedCRVal_;
    T1_flexAddr_t savedCodeAddrA_;
    T1_flexAddr_t savedStepAddr_;
    T1_flexAddr_t flexCallTrustedFunctionAddr;
    T1_flexAddr_t pInterruptedAddress_;
#    elif defined T1_ARM7M
    T1_flexAddr_t savedCodeAddrA_;
    T1_flexAddr_t savedCodeAddrB_;
    T1_uint16_t savedCodeA_;
    T1_uint16_t savedCodeB_;
    T1_flexAddr_t flexCallTrustedFunctionAddr;
    volatile T1_uint32_t *pFpComp0;
#    endif /* defined T1_ARM7R/T1_ARM8R/T1_ARM7M */
    T1_uint32_t savedStepVal_;
    T1_flexAddr_t interruptedUEDMAddr_;
#endif /* defined T1_FLEX_SINGLESTEP */

#if defined T1_TRICORE
    T1_flexAddr_t savedCodeAddrB_;
    T1_uint32_t savedD15_;
#endif /* defined T1_TRICORE */

    union {
        T1_scopeConsts_t *pFlexScopeConsts_;
        T1_scopeFgConsts_t *pFlexScopeFgConsts_;
    } _;
    T1_scopeGlobals_t *pFlexScopeGlobals_;

    T1_uint32_t hitCounterData_;
    T1_uint32_t hitCounterCode_;
    T1_uint32_t minRestrHitCounter_;
    T1_uint32_t maxRestrHitCounter_;
    T1_uint8_t stopwatchIdx_;
    T1_uint8_t lastStopwatchIdxA_;
    T1_uint8_t lastStopwatchIdxB_;
    T1_uint8_t coreId_;
    T1_uint32_t currentRestrHitCounter_[T1_NOF_RESTR_TYPE];
    T1_uint16Least_t flexAnalysisCapacity_;

    T1_flexAddr_t *pAddrs_;
    T1_uint16Least_t rwMask_; /* target-specific read-write mask for data */

    T1_uint32_t cftTracedPath_;
    T1_uint32_t *pFlexBuffer_;

    T1_uint16_t afterXevents_;

    T1_stpwIdx_t nOfStpws_; //!< number of (T1.cont) stopwatches
    T1_uint8_t fpCtrlRev;   /* Used by Armv7M, otherwise just alignment */

    /* duration counters for code breakpoints A and B */
    T1_uint32_t durationCounterCodeA_;
    T1_uint32_t durationCounterCodeB_;

    /* duration counter for data breakpoint A */
    T1_uint32_t durationCounterDataA_;

    T1_uint32_t flexTxState_;
    T1_uint32_t runningMeasMask_;

    T1_uint32_t uedFilterRange_[T1_NOF_UED_FILTER_RANGES][T1_UED_FILTER_VALS];

    T1_flexAddr_t dataAddrA_;
    T1_flexAddr_t dataAddrB_;
    T1_uint16_t dataLengthA_;
    T1_uint16_t dataLengthB_;

    T1_bool_t restrictNextMeasurement_;
    T1_bool_t budgetExpired_;
    T1_uint8_t nOfNCAs_;
    T1_uint8_t flexOverrunState_;

    union {
        struct
        {
            T1_uint8_t state_;
            T1_uint8_t flexBufferWrIdx_;
        } _;
        T1_uint16_t init_;
    } cft_;

    T1_uint16_t align16;
    T1_uint32_t token;
#if defined T1_TRICORE
    T1_uint32_t savedLcx_;
#endif /* defined T1_TRICORE */
    void ( *pMaybeStoreCodeAddress_ )( struct T1_flexGlobalsStruct_t *pFlexGlobals,
                                       T1_flexAddr_t addr );
} T1_flexGlobals_t;

/*!
 * \brief ARMv7-R and ARMv8-R only, used to forward Prefetch and Data aborts to the
 *        application specific handlers.
 */
typedef struct
{
    void ( *pPrefetchAbortHandler )( void );
    void ( *pDataAbortHandler )( void );
} const T1_flexHandlers_t;

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_FLEX_PLUGIN_ID ( 2u )

#if defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX
/*! \brief T1.flex entry in plugin table. */
#    define T1_flexPlugin ( &T1_flexPluginStruct )
#else
#    define T1_flexPlugin   ( T1_DISABLED_PLUGIN )
#    define T1_flexRevision ( 0uL )
#endif

#if !defined T1_CORE_ID_TO_FLEX_GLOBALS
#    if !defined T1_MULTICORE_CLONE
#        if 1 == T1_NOF_CORES
#            define T1_CORE_ID_TO_FLEX_GLOBALS( coreId_ ) ( &T1_flexGlobals0 )
#        elif 2 == T1_NOF_CORES
#            define T1_CORE_ID_TO_FLEX_GLOBALS( coreId_ )                            \
                ( ( 0 == ( coreId_ ) ) ? ( &T1_flexGlobals0 ) : ( &T1_flexGlobals1 ) )
#        else
#            define T1_CORE_ID_TO_FLEX_GLOBALS( coreId_ )                            \
                ( T1_flexGlobalsPC[coreId_] )
#        endif /* T1_NOF_CORES */
#    else      /* clone */
#        define T1_CORE_ID_TO_FLEX_GLOBALS( coreId_ ) ( &T1_flexGlobals )
#    endif /* ! defined T1_MULTICORE_CLONE */
#endif     /* ! defined T1_CORE_ID_TO_FLEX_GLOBALS */

#if defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX && defined T1_COUNT_PREEMPTION  \
    && !defined T1_FG_CONT
/*
 * Increment and decrement are not atomic but it does not matter because interrupts
 * leave T1_preemptionCounter unchanged.
 */
#    define T1_INCR_PREEMPTIONS( te_ )                                               \
        T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), te_ )
#    define T1_DECR_PREEMPTIONS( te_ )                                               \
        T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), te_ )
#    define T1_INCR_PREEMPTIONS_PC( coreId_, te_ )                                   \
        do                                                                           \
        {                                                                            \
            ++( T1_CORE_ID_TO_FLEX_GLOBALS( coreId_ )->preemptionCounter_ );         \
            {                                                                        \
                te_;                                                                 \
            }                                                                        \
        }                                                                            \
        while( 0 )
#    define T1_DECR_PREEMPTIONS_PC( coreId_, te_ )                                   \
        do                                                                           \
        {                                                                            \
            {                                                                        \
                te_;                                                                 \
            }                                                                        \
            --( T1_CORE_ID_TO_FLEX_GLOBALS( coreId_ )->preemptionCounter_ );         \
        }                                                                            \
        while( 0 )
#else
#    define T1_INCR_PREEMPTIONS( te_ )                                               \
        do                                                                           \
        {                                                                            \
            te_;                                                                     \
        }                                                                            \
        while( 0 )
#    define T1_DECR_PREEMPTIONS( te_ )                                               \
        do                                                                           \
        {                                                                            \
            te_;                                                                     \
        }                                                                            \
        while( 0 )
#    define T1_INCR_PREEMPTIONS_PC( coreId_, te_ )                                   \
        do                                                                           \
        {                                                                            \
            te_;                                                                     \
        }                                                                            \
        while( 0 )
#    define T1_DECR_PREEMPTIONS_PC( coreId_, te_ )                                   \
        do                                                                           \
        {                                                                            \
            te_;                                                                     \
        }                                                                            \
        while( 0 )
#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_FLEX && defined               \
          T1_COUNT_PREEMPTION && ! defined T1_FG_CONT */

#define T1_FLEX_SW_MIN_ID     ( 0x300u )
#define T1_FLEX_SW_MAX_ID     ( 0x3FFu )
#define T1_FLEX_NOF_PRE_ADDRS ( 4u )

/*----------------------------------------------------------------------------------*/
/*--- forward declaration of callback and its MPC helper ---------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_START_SEC_CODE
#include "T1_MemMap.h"
T1_EXTERN T1_bool_t T1_CODE T1_FlexAllowExternalDebug( void );
T1_EXTERN T1_bool_t T1_CODE T1_FlexAllowMPCExternalDebug( void );
#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_DeclarePlugin( T1_flexPluginStruct );
T1_EXTERN const T1_uint32_t T1_SEC_CONST_32 T1_flexRevision;
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_EXTERN T1_flexAddr_t * const T1_SEC_CONST_32 T1_addrsPC[];
T1_EXTERN T1_uint32_t * const T1_SEC_CONST_32 T1_flexBufferPC[];
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    if defined T1_MULTICORE_CLONE

#        define T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CLONE_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals;
T1_EXTERN T1_uint32_t T1_CLONE_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP;
#        define T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"

#    else /* ! defined T1_MULTICORE_CLONE */

#        define T1_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals;
T1_EXTERN T1_uint32_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP;
#        define T1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"

#    endif /* defined T1_MULTICORE_CLONE */

#    define T1_START_SEC_CONST_8
#    include "T1_MemMap.h"
T1_EXTERN T1_uint8_t const T1_SEC_CONST_8 T1_nOfAddrsPC[];
T1_EXTERN T1_stpwIdx_t const T1_SEC_CONST_8 T1_nOfFlexStpwsPC[];
T1_EXTERN T1_uint8_t const T1_SEC_CONST_8 T1_nOfFlexBufferEntriesPC[];
#    define T1_STOP_SEC_CONST_8
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_8
#    include "T1_MemMap.h"
T1_EXTERN T1_uint8_t const T1_SEC_CONST_8 T1_32852;
#    define T1_STOP_SEC_CONST_8
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_EXTERN T1_flexRange_t T1_SEC_CONST_32 T1_33108[];
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    define T1_START_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"
T1_EXTERN T1_uint32_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_swdStart;
#    define T1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"

#    define T1_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE0_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals0;
/*!
 * \brief ARMv7-R and ARMv8-R only, used as pointer to a custom stack for the data and
 *        prefetch abort handlers.
 *
 * Size must be a multiple of 8 and must be 8 byte aligned.
 * Should hold the address after the last element of the allocated stack.
 * Used by T1_DataAbortHandlerSPCore0() and T1_PrefetchAbortHandlerSPCore0().
 *
 */
T1_EXTERN T1_uint32_t T1_CORE0_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP0;
#    define T1_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"

#    if 1 < T1_NOF_CORES
#        define T1_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE1_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals1;
T1_EXTERN T1_uint32_t T1_CORE1_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP1;
#        define T1_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 1 < T1_NOF_CORES */
#    if 2 < T1_NOF_CORES
#        define T1_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE2_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals2;
T1_EXTERN T1_uint32_t T1_CORE2_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP2;
#        define T1_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 2 < T1_NOF_CORES */
#    if 3 < T1_NOF_CORES
#        define T1_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE3_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals3;
T1_EXTERN T1_uint32_t T1_CORE3_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP3;
#        define T1_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 3 < T1_NOF_CORES */
#    if 4 < T1_NOF_CORES
#        define T1_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE4_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals4;
T1_EXTERN T1_uint32_t T1_CORE4_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP4;
#        define T1_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 4 < T1_NOF_CORES */
#    if 5 < T1_NOF_CORES
#        define T1_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE5_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals5;
T1_EXTERN T1_uint32_t T1_CORE5_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP5;
#        define T1_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 5 < T1_NOF_CORES */
#    if 6 < T1_NOF_CORES
#        define T1_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE6_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals6;
T1_EXTERN T1_uint32_t T1_CORE6_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP6;
#        define T1_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 6 < T1_NOF_CORES */
#    if 7 < T1_NOF_CORES
#        define T1_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE7_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals7;
T1_EXTERN T1_uint32_t T1_CORE7_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP7;
#        define T1_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 7 < T1_NOF_CORES */
#    if 8 < T1_NOF_CORES
#        define T1_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE8_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals8;
T1_EXTERN T1_uint32_t T1_CORE8_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP8;
#        define T1_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 8 < T1_NOF_CORES */
#    if 9 < T1_NOF_CORES
#        define T1_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE9_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals9;
T1_EXTERN T1_uint32_t T1_CORE9_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP9;
#        define T1_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 9 < T1_NOF_CORES */
#    if 10 < T1_NOF_CORES
#        define T1_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE10_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals10;
T1_EXTERN T1_uint32_t T1_CORE10_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP10;
#        define T1_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 10 < T1_NOF_CORES */
#    if 11 < T1_NOF_CORES
#        define T1_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE11_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals11;
T1_EXTERN T1_uint32_t T1_CORE11_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP11;
#        define T1_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 11 < T1_NOF_CORES */
#    if 12 < T1_NOF_CORES
#        define T1_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE12_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals12;
T1_EXTERN T1_uint32_t T1_CORE12_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP12;
#        define T1_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 12 < T1_NOF_CORES */
#    if 13 < T1_NOF_CORES
#        define T1_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE13_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals13;
T1_EXTERN T1_uint32_t T1_CORE13_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP13;
#        define T1_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 13 < T1_NOF_CORES */
#    if 14 < T1_NOF_CORES
#        define T1_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CORE14_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals14;
T1_EXTERN T1_uint32_t T1_CORE14_SEC_VAR_POWER_ON_CLEARED_32 T1_abortSP14;
#        define T1_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 14 < T1_NOF_CORES */

#    if defined T1_MULTICORE_CLONE

#        define T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t T1_CLONE_SEC_VAR_POWER_ON_CLEARED_32 T1_flexGlobals;
#        define T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"

#    else /* ! defined T1_MULTICORE_CLONE */

#        define T1_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t * const T1_SEC_CONST_32 T1_flexGlobalsPC[];
#        define T1_STOP_SEC_CONST_32
#        include "T1_MemMap.h"

#    endif /* T1_MULTICORE_CLONE */

#    if defined T1_ARM7R

#        define T1_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_uint32_t volatile * const T1_SEC_CONST_32 T1_pDBGplus0x100PC[];
#        define T1_STOP_SEC_CONST_32
#        include "T1_MemMap.h"

#    endif /* defined T1_ARM7R */

#    if defined T1_ARM7M

#        define T1_START_SEC_CONST_8
#        include "T1_MemMap.h"
T1_EXTERN T1_uint8_t const T1_SEC_CONST_8 T1_fpCtrlRev;
#        define T1_STOP_SEC_CONST_8
#        include "T1_MemMap.h"

#    endif /* defined T1_ARM7M */

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_EXTERN void ( * const T1_00483[T1_NOF_CODE_BP_HANDLERS] )(
    T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_02986[T1_NOF_CODE_BP_HANDLERS] )(
    T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_36799[T1_NOF_DATA_BP_HANDLERS][T1_NOF_DATA_BP_KINDS] )(
    T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_20315[T1_NOF_DATA_BP_HANDLERS][T1_NOF_DATA_BP_KINDS] )(
    T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_96945[T1_NOF_DATA_BP_HANDLERS][T1_NOF_DATA_BP_KINDS] )(
    T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_61319[T1_NOF_SW_HANDLERS] )( T1_EXCEPTION_HANDLER_PARAMS )
    T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_51501[T1_NOF_SW_HANDLERS] )( T1_EXCEPTION_HANDLER_PARAMS )
    T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_23656[T1_NOF_CODE_BP_HANDLERS] )(
    T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_00885[T1_NOF_CODE_BP_HANDLERS] )(
    T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_42046[T1_NOF_DATA_BP_HANDLERS][T1_NOF_DATA_BP_KINDS] )(
    T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_71075[T1_NOF_DATA_BP_HANDLERS][T1_NOF_DATA_BP_KINDS] )(
    T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_95477[T1_NOF_DATA_BP_HANDLERS][T1_NOF_DATA_BP_KINDS] )(
    T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_73409[T1_NOF_SW_HANDLERS] )( T1_EXCEPTION_HANDLER_PARAMS )
    T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_55015[T1_NOF_SW_HANDLERS] )( T1_EXCEPTION_HANDLER_PARAMS )
    T1_SEC_CONST_32;
T1_EXTERN void ( * const ( * const T1_pCodeBpHandlers )[T1_NOF_CODE_BP_HANDLERS] )(
    T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32;
T1_EXTERN void ( * const ( * const T1_pDataBpHandlers )[T1_NOF_DATA_BP_HANDLERS]
                                                       [T1_NOF_DATA_BP_KINDS] )(
    T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32;
T1_EXTERN void ( * const ( * const T1_pSwHandlers )[T1_NOF_SW_HANDLERS] )(
    T1_EXCEPTION_HANDLER_PARAMS ) T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_pHandlerTraceEvent )( T1_uint8Least_t coreId,
                                                  T1_uint32_t val ) T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_pNcaMaybeStoreCodeAddress )(
    T1_flexGlobals_t *pFlexGlobals, T1_flexAddr_t addr ) T1_SEC_CONST_32;
T1_EXTERN void ( * const T1_pCftMaybeStoreCodeAddress )(
    T1_flexGlobals_t *pFlexGlobals, T1_flexAddr_t addr ) T1_SEC_CONST_32;
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

/*----------------------------------------------------------------------------------*/
/*--- external function declarations -----------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#    define T1_START_SEC_CODE
#    include "T1_MemMap.h"

#    if defined T1_ARM7M
/*
 * This declarations is required to allow T1_DebugMonitorHandler to call library
 * function T1_DebugMonitorHandler_.
 */
#        if defined T1_NEAR_CODE_FAST
void T1_NEAR_CODE_FAST
#        else
T1_CODE_FAST( void )
#        endif /* defined T1_NEAR_CODE_FAST */
T1_DebugMonitorHandler_( T1_flexGlobals_t *pFlexGlobals );
#    endif /* defined T1_ARM7M */

/*!
 * Call T1_TraceEvent() via T1.flex. This has a much higher overhead than a direct
 * call to T1_TraceEvent() but it can be called from user mode, so that the total
 * overhead might be lower.
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 */
#    define T1_FlexTraceEvent( event_, info_ )                                       \
        T1_FlexTraceEventPC( T1_GetCoreIdOffset( ), ( event_ ), ( info_ ) )
/*!
 * Call T1_TraceEvent() via T1.flex. This has a much higher overhead than a direct
 * call to T1_TraceEvent() but it can be called from user mode, so that the total
 * overhead might be lower.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 */
#    define T1_FlexTraceEventPC( coreId_, event_, info_ )                            \
        T1_FlexTraceEventPC_( ( coreId_ ),                                           \
                              T1_COMBINE_EVENT_INFO( ( event_ ), ( info_ ) ) )
T1_EXTERN T1_tickUint_t T1_CODE T1_FlexTraceEventPC_( T1_uint8Least_t coreId,
                                                      T1_eventInfo_t eventInfo );
/*----------------------------------------------------------------------------------*/
T1_EXTERN void T1_CODE T1_11338( T1_uint8Least_t coreId, T1_uint32_t val );
T1_EXTERN void T1_CODE T1_11056( T1_uint8Least_t coreId, T1_uint32_t val );
T1_EXTERN void T1_CODE T1_30318( T1_uint8Least_t coreId, T1_uint32_t val );
T1_EXTERN void T1_CODE T1_15112( T1_uint8Least_t coreId, T1_uint32_t val );
/*----------------------------------------------------------------------------------*/
T1_EXTERN void T1_CODE T1_93425( T1_flexGlobals_t *pFlexGlobals, T1_flexAddr_t addr );
T1_EXTERN void T1_CODE T1_15052( T1_flexGlobals_t *pFlexGlobals, T1_flexAddr_t addr );
T1_EXTERN void T1_CODE T1_57687( T1_flexGlobals_t *pFlexGlobals, T1_flexAddr_t addr );
T1_EXTERN void T1_CODE T1_40585( T1_flexGlobals_t *pFlexGlobals, T1_flexAddr_t addr );
T1_EXTERN void T1_CODE T1_35804( T1_flexGlobals_t *pFlexGlobals, T1_flexAddr_t addr );
T1_EXTERN void T1_CODE T1_84306( T1_flexGlobals_t *pFlexGlobals, T1_flexAddr_t addr );
T1_EXTERN void T1_CODE T1_20590( T1_flexGlobals_t *pFlexGlobals, T1_flexAddr_t addr );
T1_EXTERN void T1_CODE T1_35035( T1_flexGlobals_t *pFlexGlobals, T1_flexAddr_t addr );
#    define T1_STOP_SEC_CODE
#    include "T1_MemMap.h"

#    if defined T1_TRICORE

#        if defined T1_MULTICORE_CLONE

#            define T1_DMS_CLONE_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandler( void );
#            define T1_DMS_CLONE_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_START_SEC_CODE_FAST
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandler_( void );
#            define T1_STOP_SEC_CODE_FAST
#            include "T1_MemMap.h"

/*
 * Inhibit section macro for T1_dcx because it (only) contains align attributes,
 * which contradict the alignment of T1_dcx.
 */
#            define T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_flexAddr_t T1_dcx[4] /* T1_CLONE_SEC_VAR_POWER_ON_CLEARED_32 */;
#            define T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"

#        else /* ! defined T1_MULTICORE_CLONE */

#            define T1_START_SEC_CONST_32
#            include "T1_MemMap.h"
T1_EXTERN T1_pVoidVoid_t const T1_SEC_CONST_32 T1_outerHandlerPC[];
T1_EXTERN T1_flexAddr_t * const T1_SEC_CONST_32 T1_dcxPC[];
#            define T1_STOP_SEC_CONST_32
#            include "T1_MemMap.h"

#            define T1_DMS_CORE0_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore0( void );
#            define T1_DMS_CORE0_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE1_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore1( void );
#            define T1_DMS_CORE1_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE2_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore2( void );
#            define T1_DMS_CORE2_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE3_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore3( void );
#            define T1_DMS_CORE3_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE4_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore4( void );
#            define T1_DMS_CORE4_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE5_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore5( void );
#            define T1_DMS_CORE5_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE6_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore6( void );
#            define T1_DMS_CORE6_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE7_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore7( void );
#            define T1_DMS_CORE7_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE8_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore8( void );
#            define T1_DMS_CORE8_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE9_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore9( void );
#            define T1_DMS_CORE9_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE10_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore10( void );
#            define T1_DMS_CORE10_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE11_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore11( void );
#            define T1_DMS_CORE11_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE12_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore12( void );
#            define T1_DMS_CORE12_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE13_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore13( void );
#            define T1_DMS_CORE13_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_DMS_CORE14_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( void ) T1_OuterHandlerCore14( void );
#            define T1_DMS_CORE14_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE0_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE0_CODE T1_OuterHandlerCore0_( void );
#            define T1_CORE0_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE1_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE1_CODE T1_OuterHandlerCore1_( void );
#            define T1_CORE1_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE2_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE2_CODE T1_OuterHandlerCore2_( void );
#            define T1_CORE2_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE3_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE3_CODE T1_OuterHandlerCore3_( void );
#            define T1_CORE3_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE4_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE4_CODE T1_OuterHandlerCore4_( void );
#            define T1_CORE4_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE5_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE5_CODE T1_OuterHandlerCore5_( void );
#            define T1_CORE5_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE6_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE6_CODE T1_OuterHandlerCore6_( void );
#            define T1_CORE6_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE7_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE7_CODE T1_OuterHandlerCore7_( void );
#            define T1_CORE7_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE8_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE8_CODE T1_OuterHandlerCore8_( void );
#            define T1_CORE8_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE9_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE9_CODE T1_OuterHandlerCore9_( void );
#            define T1_CORE9_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE10_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE10_CODE T1_OuterHandlerCore10_( void );
#            define T1_CORE10_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE11_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE11_CODE T1_OuterHandlerCore11_( void );
#            define T1_CORE11_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE12_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE12_CODE T1_OuterHandlerCore12_( void );
#            define T1_CORE12_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE13_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE13_CODE T1_OuterHandlerCore13_( void );
#            define T1_CORE13_STOP_SEC_CODE
#            include "T1_MemMap.h"

#            define T1_CORE14_START_SEC_CODE
#            include "T1_MemMap.h"
T1_EXTERN void T1_CORE14_CODE T1_OuterHandlerCore14_( void );
#            define T1_CORE14_STOP_SEC_CODE
#            include "T1_MemMap.h"

#        endif /* defined T1_MULTICORE_CLONE */

#    elif /* ! defined T1_TRICORE && */ defined T1_ARM7R || defined T1_ARM8R

#        define T1_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_uint32_t * const T1_SEC_CONST_32 T1_abortSPPC[];
#        define T1_STOP_SEC_CONST_32
#        include "T1_MemMap.h"

#    endif /* defined T1_TRICORE ... */

#else /* ! defined T1_ENABLE || defined T1_DISABLE_T1_FLEX */
#    define T1_FlexTraceEvent( event_, info_ )            ( (T1_tickUint_t)0u )
#    define T1_FlexTraceEventPC( coreId_, event_, info_ ) ( (T1_tickUint_t)0u )
#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_FLEX */

#define T1_START_SEC_CODE
#include "T1_MemMap.h"
T1_EXTERN void T1_CODE T1_FlexOHAddrPC( T1_uint8Least_t coreId,
                                        T1_uint32_t pAddrStart );
#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

#if defined T1_TRICORE
#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_EXTERN void ( * const T1_pAppContextManagementHandlerPC[] )( void )
    T1_SEC_CONST_32;
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"
#endif /* defined T1_TRICORE */

/**@}*/

/*----------------------------------------------------------------------------------*/
/*--- documentation ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_DOXYGEN_ONLY

/*!
 * \page T1_flex_page T1.flex
 *
 * T1.flex is a plugin of T1 that allows for instrumentation of any function, line of
 * code or data-accesses on-the-fly. T1.flex works without static instrumentation
 * and therefore does not require re-compiling the application to add instrumentation
 * points.
 *
 */

#endif /* T1_DOXYGEN_ONLY */

#endif /* T1_FLEX_INTERFACE_H_ */
