/************************************************************************************/
/*! \file           T1_config.c
 *
 *  \brief          Application-specific configuration of T1
 *
 *  $Author: jialinli $
 *
 *  $Revision: 370 $
 *
 *  \copyright GLIWA embedded systems GmbH & Co. KG, Weilheim i.OB. All rights reserved
 ************************************************************************************/

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*
 * The following define is REQUIRED for MPC5xxx and SPC5xx. Only if T1.flex and
 * debugger coexistence is supported by the hardware this may be omitted.
 */
/* #define T1_FLEX_DISABLE_WITH_DEBUGGER (1) */

#define T1_OVERRIDE_SYNCTOTRACETIMERPC ( 1 ) /* Backwards compatibility */

#include "T1_AppInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- Local macros  ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if !defined T1_GET_TRACE_TIME_UMPC
/*!
 * If we can invoke #T1_GET_TRACE_TIME_PC in user mode then we can map
 * #T1_GET_TRACE_TIME_UMPC directly to #T1_GET_TRACE_TIME_PC. Otherwise the integrator
 * must define #T1_GET_TRACE_TIME_UMPC to safely read the trace timer in user mode.
 * \returns the trace timer count register scaled to trace timer ticks
 */
#    define T1_GET_TRACE_TIME_UMPC( coreId_ ) T1_GET_TRACE_TIME_PC( coreId_ )
#endif /* ! defined T1_GET_TRACE_TIME_UMPC */

#if !defined T1_CONT_CPU_LOAD_EXTRAS
#    define T1_CONT_CPU_LOAD_EXTRAS( coreId_, cpuLoadFrac_, cpuLoadThreshold_ )      \
        (void)0
#endif /* ! defined T1_CONT_CPU_LOAD_EXTRAS */

#define HFSR_DEBUGEVT_MASK ( 0x80000000uL )

/*----------------------------------------------------------------------------------*/
/*--- Optimization pragmas for uniform code generation with widely-used compilers --*/
/*----------------------------------------------------------------------------------*/

#if defined __ghs__
#    pragma ghs O
#elif defined __TASKING__
#    pragma optimize 2
#elif defined __GNUC__ && !defined __TMS470__ && !defined __clang__                  \
    && !defined __ARMCC_VERSION
#    pragma GCC optimize "O2"
#endif /* compiler */

#if defined T1_ENABLE

/*----------------------------------------------------------------------------------*/
/*--- T1.base configuration --------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_ALLOCATE_PLUGIN_TABLE( T1_pluginTable )
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    if !defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE
#        define T1_START_SEC_VAR_CLEARED_32
#        include "T1_MemMap.h"
/*! \brief Shared data for remote core T1.cont pairs of cores. */
T1_bakery_t T1_SEC_VAR_CLEARED_32
    T1_contRemoteSemPC[T1_NOF_CORES][T1_CONT_REMOTE_NOF_SEMAPHORE_USERS];
#        define T1_STOP_SEC_VAR_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* ! defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE */

#    define T1_START_SEC_CODE
#    include "T1_MemMap.h"
void T1_CODE T1_SuspendAllInterruptsPC( T1_uint8Least_t coreId )
{
    /* May be replaced by a call to AUTOSAR OS SuspendAllInterrupts( ) */
	SuspendAllInterrupts();//petter
//    T1_SuspendAllInterruptsPC_( coreId );
}

void T1_CODE T1_ResumeAllInterruptsPC( T1_uint8Least_t coreId )
{
    /* May be replaced by a call to AUTOSAR OS ResumeAllInterrupts( ) */
	ResumeAllInterrupts(); //petter
//    T1_ResumeAllInterruptsPC_( coreId );
}

void T1_CODE T1_DisableT1HandlerPC( T1_uint8Least_t coreId )
{
#    if !defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE
    (void)T1_GetSpinlockPC( T1_CONT_RC_UNMAP( coreId ),
                            T1_contRemoteSemPC[coreId],
                            1u,
                            2u,
                            T1_FALSE );
#    else
    /* May be replaced by a call to AUTOSAR OS GetResource( ) */
    T1_SuspendAllInterruptsPC( coreId );
#    endif /* ! defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE */
}

void T1_CODE T1_EnableT1HandlerPC( T1_uint8Least_t coreId )
{
#    if !defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE
    T1_ReleaseSpinlockPC( T1_CONT_RC_UNMAP( coreId ),
                          T1_contRemoteSemPC[coreId],
                          1u,
                          T1_FALSE );
#    else
    /* May be replaced by a call to AUTOSAR OS ReleaseResource( ) */
    T1_ResumeAllInterruptsPC( coreId );
#    endif /* ! defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE */
}

#    define T1_STOP_SEC_CODE
#    include "T1_MemMap.h"

/*----------------------------------------------------------------------------------*/
/*--- T1.cont configuration --------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#    if !defined T1_DISABLE_T1_CONT

#        if defined T1_CONT_REMOTE && defined T1_ENABLE_WRITE_TIME
#            error T1_CONT_REMOTE and T1_ENABLE_WRITE_TIME are not compatible
#        endif /* defined T1_CONT_REMOTE && defined T1_ENABLE_WRITE_TIME */

#        define T1_START_SEC_CODE
#        include "T1_MemMap.h"

void T1_NOINLINE T1_CODE
T1_ContCsrnCallbackNoSuspPC( T1_uint8Least_t coreId,
                             T1_UNUSED( T1_resultTime_t result ),
                             T1_UNUSED( T1_csrnIdx_t idx ),
                             T1_nOfEntries_t afterXevnts )
{
    (void)coreId; /* Suppress warnings if T1_CONT_RC_UNMAP does not use coreId */
    if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRIGGER ) )
    {
#        if 1 < T1_NOF_CORES
        T1_afterXevents = (T1_uint16_t)afterXevnts;
        ++T1_coreTriggerCounter[T1_CONT_RC_UNMAP( coreId )];
#        else  /* single core */
        (void)T1_SetStopTrigger( afterXevnts );
#        endif /* 1 < T1_NOF_CORES */
    }
}

void T1_CODE T1_ContCsrnCallbackPC( T1_uint8Least_t coreId,
                                    T1_resultTime_t result,
                                    T1_csrnIdx_t idx,
                                    T1_nOfEntries_t afterXevnts )
{
    /* No interrupt protection is required for default T1_ContCsrnCallbackNoSuspPC. */
    T1_ContCsrnCallbackNoSuspPC( coreId, result, idx, afterXevnts );
}

void T1_CODE T1_ContCPULoadCallbackPC( T1_uint8Least_t coreId,
                                       T1_uint32_t cpuLoadFrac,
                                       T1_uint8Least_t cpuLoadThreshold,
                                       T1_nOfEntries_t afterXevnts )
{
    /* CPU load denominator (Nenner) in the range [0x8000..0xFFFF] */
    T1_uint16Least_t const to = (T1_uint16Least_t)( cpuLoadFrac >> 16 );
    /* CPU load numerator (Zaehler)  in the range [0x0000..to] */
    T1_uint16Least_t const te = (T1_uint16Least_t)( cpuLoadFrac & 0xFFFFu );
    (void)coreId; /* Suppress warnings if T1_CONT_RC_UNMAP does not use coreId */

    T1_SuspendAllInterruptsPC( T1_CONT_RC_UNMAP( coreId ) );

    if( T1_CONT_CPU_OVERLOAD( to, te, cpuLoadThreshold ) )
    {
        T1_uint8Least_t const cpuLoadPercent =
            (T1_uint8Least_t)( ( te * 200uL + 1 ) / to ) / 2u;
        if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRIGGER ) )
        {
            T1_AppSetStopTriggerAllCores( T1_CONT_RC_UNMAP( coreId ), afterXevnts );
        }
#        if 1 == T1_NOF_CORES
        T1_TraceEventNoSuspUMPC(
            0u,
            T1_COMBINE_EVENT_INFO( T1_UE_CPU_LOAD_CALLBACK_CORE0, cpuLoadPercent ) );
#        else  /* 1 < T1_NOF_CORES */
        T1_TraceEventNoSuspUMPC(
            T1_CONT_RC_UNMAP( coreId ),
            T1_COMBINE_EVENT_INFO( T1_UE_CPU_LOAD_CALLBACK_CORE0 + coreId,
                                   cpuLoadPercent ) );
#        endif /* 1 == T1_NOF_CORES */
    }

    T1_ResumeAllInterruptsPC( T1_CONT_RC_UNMAP( coreId ) );

    T1_CONT_CPU_LOAD_EXTRAS( coreId, cpuLoadFrac, cpuLoadThreshold );
}

void T1_CODE T1_ContErrCallbackPC( T1_uint8Least_t coreId,
                                   T1_uint8Least_t errMask,
                                   T1_uint8Least_t triggerMask,
                                   T1_nOfEntries_t afterXevnts )
{
    (void)coreId; /* Suppress warnings if T1_CONT_RC_UNMAP does not use coreId */
#        if 1 == T1_NOF_CORES
    T1_TraceEventUMPC( 0u,
                       T1_COMBINE_EVENT_INFO( T1_UE_T1_CONT_ERR_CORE0, errMask ) );
#        else  /* 1 < T1_NOF_CORES */
    T1_TraceEventUMPC(
        T1_CONT_RC_UNMAP( coreId ),
        T1_COMBINE_EVENT_INFO( T1_UE_T1_CONT_ERR_CORE0 + coreId, errMask ) );
#        endif /* 1 == T1_NOF_CORES */
    if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRIGGER )
        && ( 0 != ( errMask & triggerMask ) ) )
    {
        T1_AppSetStopTriggerAllCores( T1_CONT_RC_UNMAP( coreId ), afterXevnts );
    }
}

void T1_CODE T1_ContOHCallbackPC( T1_uint8Least_t coreId, T1_uint8Least_t errMask )
{
    (void)coreId; /* Suppress warnings if T1_CONT_RC_UNMAP does not use coreId */
    if( 0u == ( T1_INF_OVERHEADS_UPDATED & errMask ) )
    {
        /* Overheads were not updated */
        INC_T1_ERROR_COUNT_REMOTE( T1_CONT_RC_UNMAP( coreId ), coreId );
    }
#        if !defined T1_REMOTE_CONT /* Only possible without remote core T1.cont */
    /* Free T1.cont event chains used for calibration */
    T1_CONT_STOP_CALIBRATION_PC( coreId );
#            if !defined T1_FG_CONT
    /*
     * Resetting results can discard valuable data but with background T1.cont it
     * MAY be required to clear underflows from overheads that were too large.
     */
    T1_ContResetResultsPC( coreId );
#            endif /* defined T1_FG_CONT */
#        endif /* defined T1_REMOTE_CONT */
}

T1_resultTime_t T1_CODE T1_ContStartStopCETPC( T1_UNUSED( T1_uint8Least_t coreId ),
                                               T1_UNUSED( T1_taskIdx_t taskIdx ) )
{
    /* T1_START_STOP is not used */
    return 0uL;
}

#        if !defined T1_70618
void T1_CODE T1_49672( T1_UNUSED( T1_uint8Least_t coreId ),
                       T1_UNUSED( T1_taskIdx_t taskIdx ),
                       T1_UNUSED( T1_resultTime_t taskCET ) )
{
}
void T1_CODE T1_84399( T1_UNUSED( T1_uint8Least_t coreId ),
                       T1_UNUSED( T1_longTime_t now ) )
{
}
#        endif /* ! defined T1_70618 */

#        define T1_STOP_SEC_CODE
#        include "T1_MemMap.h"

#    endif /* ! defined T1_DISABLE_T1_CONT */

/*----------------------------------------------------------------------------------*/
/*--- T1.scope configuration -------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#    if !defined T1_DISABLE_T1_SCOPE

#        define T1_START_SEC_VAR_CLEARED_32
#        include "T1_MemMap.h"
/*! \brief Shared data for serializing calibration with Lamport's Bakery algorithm. */
T1_bakery_t T1_SEC_VAR_CLEARED_32 T1_calibrationSemPC[T1_NOF_CORES];
#        define T1_STOP_SEC_VAR_CLEARED_32
#        include "T1_MemMap.h"

#        define T1_START_SEC_CODE_FAST
#        include "T1_MemMap.h"

#        if defined __ghs__
/* Green Hills __noinline keyword can be disabled, so use the pragma instead. */
#            pragma ghs startnoinline
#        endif /* defined __ghs__ */

#        if defined T1_GCC_ADAPT
#            undef T1_TraceEventNoSusp__
T1_CODE_FAST( T1_tickUint_t )
T1_NOINLINE T1_CODE_OPT T1_TraceEventNoSusp__( T1_scopeConsts_t *pScopeConsts,
                                               T1_eventInfo_t eventInfo )
{
    return T1_NearTraceEventNoSusp__( pScopeConsts, eventInfo );
}
T1_CODE_FAST( T1_tickUint_t )
T1_NOINLINE T1_CODE_OPT T1_NearTraceEventNoSusp__
#        else
T1_CODE_FAST( T1_tickUint_t )
T1_NOINLINE T1_CODE_OPT T1_TraceEventNoSusp__
#        endif /* defined T1_GCC_ADAPT */
    ( T1_scopeConsts_t *pScopeConsts, T1_eventInfo_t eventInfo )
{
#        if defined T1_FG_CONT && !defined T1_DISABLE_T1_CONT
    T1_uint8Least_t handlerIdx;
    T1_FG_CONT_GET_HANDLER_IDX( eventInfo, handlerIdx );
    return T1_Dispatch2_( pScopeConsts, eventInfo, handlerIdx << 1 );
#        else /* !defined T1_FG_CONT || defined T1_DISABLE_T1_CONT */
    T1_tickUint_t const now =
#            if defined T1_ALL_TIMERS_ARE_MEMORY_MAPPED                              \
                && defined T1_RAW_TO_TRACE_TIME && !defined T1_GET_RAW_TIME
        T1_RAW_TO_TRACE_TIME( *pScopeConsts->pTraceTimer );
#            else  /* !defined T1_ALL_TIMERS_ARE_MEMORY_MAPPED */
        T1_GET_TRACE_TIME_PC( pScopeConsts->coreId );
#            endif /* defined T1_ALL_TIMERS_ARE_MEMORY_MAPPED */
    return T1_TRACE_EVENT_NOSUSP_TIME( pScopeConsts, eventInfo, now );
#        endif     /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */
}

#        if defined T1_NEAR_CODE_FAST
T1_tickUint_t T1_NOINLINE T1_NEAR_CODE_FAST
    __attribute__( ( alias( "T1_TraceEventNoSusp__" ) ) )
    T1_NearTraceEventNoSusp__( T1_scopeConsts_t *pScopeConsts,
                               T1_eventInfo_t eventInfo );
#        endif /* defined T1_NEAR_CODE_FAST */

#        if defined __ghs__
#            pragma ghs endnoinline
#        endif /* defined __ghs__ */

#        define T1_STOP_SEC_CODE_FAST
#        include "T1_MemMap.h"

#        define T1_START_SEC_CODE
#        include "T1_MemMap.h"

T1_tickUint_t T1_CODE T1_TraceEventNoSuspUMPC( T1_uint8Least_t coreId,
                                               T1_eventInfo_t eventInfo )
{
    (void)coreId; /* Suppress warnings if coreId is not used */
#        if defined T1_FLEX_UM_TRACE
    if( T1_IsT1FlexEnabledPC( coreId ) )
    {
        return T1_FlexTraceEventPC_( coreId, eventInfo );
    }
#        endif /* defined T1_FLEX_UM_TRACE */
#        if defined T1_FG_CONT && !defined T1_DISABLE_T1_CONT
    {
        T1_uint8Least_t handlerIdx;
        T1_FG_CONT_GET_HANDLER_IDX( eventInfo, handlerIdx );
        return T1_DispatchTimePC( coreId,
                                  eventInfo,
                                  handlerIdx << 1,
                                  T1_GET_TRACE_TIME_UMPC( coreId ) );
    }
#        else  /* ! defined T1_FG_CONT || defined T1_DISABLE_T1_CONT */
    return T1_FAR_TRACE_EVENT_NOSUSP_TIME( T1_CORE_ID_TO_SCOPE_CONSTS( coreId ),
                                           eventInfo,
                                           T1_GET_TRACE_TIME_UMPC( coreId ) );
#        endif /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */
}

void T1_CODE T1_TraceEventUMPC( T1_uint8Least_t coreId, T1_eventInfo_t eventInfo )
{
#        if defined T1_FLEX_UM_TRACE
    if( T1_IsT1FlexEnabledPC( coreId ) )
    {
        (void)T1_FlexTraceEventPC_( coreId, eventInfo );
        return;
    }
#        endif /* defined T1_FLEX_UM_TRACE */
    T1_SuspendAllInterruptsPC( coreId );
#        if defined T1_FG_CONT && !defined T1_DISABLE_T1_CONT
    {
        T1_uint8Least_t handlerIdx;
        T1_FG_CONT_GET_HANDLER_IDX( eventInfo, handlerIdx );
        (void)T1_DispatchTimePC( coreId,
                                 eventInfo,
                                 handlerIdx << 1,
                                 T1_GET_TRACE_TIME_UMPC( coreId ) );
    }
#        else  /* ! defined T1_FG_CONT || defined T1_DISABLE_T1_CONT */
    (void)T1_FAR_TRACE_EVENT_NOSUSP_TIME( T1_CORE_ID_TO_SCOPE_CONSTS( coreId ),
                                          eventInfo,
                                          T1_GET_TRACE_TIME_UMPC( coreId ) );
#        endif /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */
    T1_ResumeAllInterruptsPC( coreId );
}

T1_tickUint_t T1_CODE T1_GetTraceTime( void )
{
#        if !defined T1_GET_RAW_TIME || !defined T1_RAW_TO_TRACE_TIME
    T1_uint8Least_t const coreId = T1_GetCoreIdOffset( );
#        endif /* ! defined T1_GET_RAW_TIME || ! defined T1_RAW_TO_TRACE_TIME */
    return T1_GET_TRACE_TIME_PC( coreId );
}

T1_tickUint_t T1_CODE T1_GetTraceTimeUM( void )
{
#        if !defined T1_GET_RAW_TIME || !defined T1_RAW_TO_TRACE_TIME
    T1_uint8Least_t coreId = T1_GetCoreIdOffset( );
#        endif /* ! defined T1_GET_RAW_TIME || ! defined T1_RAW_TO_TRACE_TIME */
    return T1_GET_TRACE_TIME_UMPC( coreId );
}

#        if defined __ghs__
/* Green Hills __noinline keyword can be disabled, so use the pragma instead. */
#            pragma ghs startnoinline
#        endif /* defined __ghs__ */

void T1_NOINLINE T1_CODE T1_GetTraceAndSyncTimeNoSuspPC(
    T1_uint8Least_t coreId, T1_syncTimerBase_t *pSyncTimerBase )
{
    T1_uint32_t syncTime;
    T1_tickUint_t traceTime;
#        if /* always defined to 0 or 1 */ T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER
    (void)coreId; /* Suppress warnings since coreId is not actually used */
    syncTime  = T1_GET_SYNC_TIME( );
    traceTime = syncTime;
#        else /* at least one trace timer is not the sync timer */
#            if defined T1_GET_RAW_TIME && defined T1_RAW_TO_TRACE_TIME
    syncTime = T1_GET_SYNC_TIME( );
    traceTime = T1_RAW_TO_TRACE_TIME( T1_GET_RAW_TIME( ) );
#            else /* different timer/speeds for different cores */
    switch( coreId )
    {
#                if !T1_TRACE_TIMER_IS_SYNC_TIMER_CORE0
    case 0u:
        syncTime  = T1_GET_SYNC_TIME( );
        traceTime = T1_RAW_TO_TRACE_TIME_CORE0( T1_GET_RAW_TIME_CORE0( ) );
        break;
#                endif /* ! T1_TRACE_TIMER_IS_SYNC_TIMER_CORE0 */
#                if 2 <= T1_NOF_CORES && !T1_TRACE_TIMER_IS_SYNC_TIMER_CORE1
    case 1u:
        syncTime  = T1_GET_SYNC_TIME( );
        traceTime = T1_RAW_TO_TRACE_TIME_CORE1( T1_GET_RAW_TIME_CORE1( ) );
        break;
#                endif
#                if 3 <= T1_NOF_CORES && !T1_TRACE_TIMER_IS_SYNC_TIMER_CORE2
    case 2u:
        syncTime  = T1_GET_SYNC_TIME( );
        traceTime = T1_RAW_TO_TRACE_TIME_CORE2( T1_GET_RAW_TIME_CORE2( ) );
        break;
#                endif
#                if 4 <= T1_NOF_CORES && !T1_TRACE_TIMER_IS_SYNC_TIMER_CORE3
    case 3u:
        syncTime  = T1_GET_SYNC_TIME( );
        traceTime = T1_RAW_TO_TRACE_TIME_CORE3( T1_GET_RAW_TIME_CORE3( ) );
        break;
#                endif
#                if 5 <= T1_NOF_CORES && !T1_TRACE_TIMER_IS_SYNC_TIMER_CORE4
    case 4u:
        syncTime  = T1_GET_SYNC_TIME( );
        traceTime = T1_RAW_TO_TRACE_TIME_CORE4( T1_GET_RAW_TIME_CORE4( ) );
        break;
#                endif
#                if 6 <= T1_NOF_CORES && !T1_TRACE_TIMER_IS_SYNC_TIMER_CORE5
    case 5u:
        syncTime  = T1_GET_SYNC_TIME( );
        traceTime = T1_RAW_TO_TRACE_TIME_CORE5( T1_GET_RAW_TIME_CORE5( ) );
        break;
#                endif
    default:
        syncTime  = T1_GET_SYNC_TIME( );
        traceTime = syncTime;
        break;
    }
#            endif /* defined T1_GET_RAW_TIME && defined T1_RAW_TO_TRACE_TIME */
#        endif     /* T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER */
#        if T1_SYNC_TIMER_WIDTH_BITS < 32 /* Extend sync timer to 32-bit value */
    syncTime = pSyncTimerBase->syncTime
               + T1_TRUNC_SYNC_GET( syncTime - pSyncTimerBase->syncTime );
#        endif /* T1_SYNC_TIMER_WIDTH_BITS < 32 */
    pSyncTimerBase->syncTime  = syncTime;
    pSyncTimerBase->traceTime = traceTime;
}

#        if defined __ghs__
#            pragma ghs endnoinline
#        endif /* defined __ghs__ */

void T1_CODE T1_GetTraceAndSyncTimeNoSuspUMPC( T1_uint8Least_t coreId,
                                               T1_syncTimerBase_t *pSyncTimerBase )
{
    T1_GetTraceAndSyncTimeNoSuspPC( coreId, pSyncTimerBase );
}

void T1_CODE T1_ScopeOverheadSequenceUMPC( T1_uint8Least_t coreId )
{
    T1_SuspendAllInterruptsPC( coreId );
    T1_ScopeOverheadSequenceNoSuspPC( coreId );
    T1_ResumeAllInterruptsPC( coreId );
}

#        define T1_STOP_SEC_CODE
#        include "T1_MemMap.h"

#        if defined T1_DISABLE_T1_FLEX
#            define T1_START_SEC_CODE
#            include "T1_MemMap.h"
void T1_CODE T1_FlexOHAddrPC( T1_UNUSED( T1_uint8Least_t coreId ),
                              T1_UNUSED( T1_uint32_t pAddrStart ) )
{
    /* Empty function to allow linkage when T1.flex is disabled. */
}
#            define T1_STOP_SEC_CODE
#            include "T1_MemMap.h"
#        endif /* defined T1_DISABLE_T1_FLEX */

#    endif /* ! defined T1_DISABLE_T1_SCOPE */

/*----------------------------------------------------------------------------------*/
/*--- T1.flex configuration --------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#    if !defined T1_DISABLE_T1_FLEX

#        define T1_START_SEC_CODE
#        include "T1_MemMap.h"
T1_bool_t T1_CODE T1_FlexAllowExternalDebug( void )
{
#        if defined T1_TRICORE && !defined T1_FLEX_DISABLE_WITH_DEBUGGER
    return T1_TRUE;
#        elif defined T1_MPC5XXX && !defined T1_FLEX_DISABLE_WITH_DEBUGGER
    return T1_FlexAllowMPCExternalDebug( );
#        else  /* defined T1_FLEX_DISABLE_WITH_DEBUGGER */
    return T1_FALSE;
#        endif /* defined T1_TRICORE && ! defined T1_FLEX_DISABLE_WITH_DEBUGGER */
}
#        define T1_STOP_SEC_CODE
#        include "T1_MemMap.h"
/*----------------------------------------------------------------------------------*/
#        if defined T1_MPC5XXX
#            define T1_START_SEC_CODE_FAST
#            include "T1_MemMap.h"
T1_EXTERN
#            if defined T1_NEAR_CODE_FAST
void T1_NEAR_CODE_FAST T1_CODE_OPT
#            else
T1_CODE_FAST( void )
T1_CODE_OPT
#            endif
T1_ExceptionHandler( T1_uint32_t param1,
                     T1_uint32_t param2,
                     T1_uint32_t param3,
                     T1_uint32_t param4,
                     T1_flexGlobals_t *pFlexGlobals );
T1_EXTERN T1_CODE_FAST( void ) T1_CODE_OPT T1_PreExceptionHandler(
    T1_uint32_t param1, T1_uint32_t param2, T1_uint32_t param3, T1_uint32_t param4 );

/*! \brief T1 helper function. Do not edit. */
T1_CODE_FAST( void )
T1_CODE_OPT T1_PreExceptionHandler( T1_uint32_t param1,
                                    T1_uint32_t param2,
                                    T1_uint32_t param3,
                                    T1_uint32_t param4 )
{
    T1_ExceptionHandler( param1,
                         param2,
                         param3,
                         param4,
                         T1_CORE_ID_TO_FLEX_GLOBALS( T1_GetCoreIdOffset( ) ) );
}
#            define T1_STOP_SEC_CODE_FAST
#            include "T1_MemMap.h"

#        elif /* ! defined T1_MPC5XXX && */ defined T1_ARM7R || defined T1_ARM8R
/*----------------------------------------------------------------------------------*/
#            define T1_START_SEC_CODE_FAST
#            include "T1_MemMap.h"
T1_EXTERN
#            if defined T1_NEAR_CODE_FAST
void T1_NEAR_CODE_FAST
#            else
T1_CODE_FAST( void )
#            endif /* defined T1_NEAR_CODE_FAST */
T1_ExceptionHandlerCode( T1_uint32_t param1,
                         T1_uint32_t param2,
                         T1_flexGlobals_t *pFlexGlobals,
                         T1_uint32_t param3 );
T1_EXTERN T1_CODE_FAST( void ) T1_CODE_OPT T1_PreExceptionHandlerCode(
    T1_uint32_t param1, T1_uint32_t param2, T1_uint32_t unused, T1_uint32_t param3 );

/*! \brief T1 helper function. Do not edit. */
T1_CODE_FAST( void )
T1_CODE_OPT T1_PreExceptionHandlerCode( T1_uint32_t param1,
                                        T1_uint32_t param2,
                                        T1_UNUSED( T1_uint32_t unused ),
                                        T1_uint32_t param3 )
{
    T1_ExceptionHandlerCode( param1,
                             param2,
                             T1_CORE_ID_TO_FLEX_GLOBALS( T1_GetCoreIdOffset( ) ),
                             param3 );
}
/*----------------------------------------------------------------------------------*/
T1_EXTERN
#            if defined T1_NEAR_CODE_FAST
void T1_NEAR_CODE_FAST
#            else
T1_CODE_FAST( void )
#            endif /* defined T1_NEAR_CODE_FAST */
T1_ExceptionHandlerData( T1_uint32_t param1,
                         T1_uint32_t param2,
                         T1_flexGlobals_t *pFlexGlobals );
T1_EXTERN T1_CODE_FAST( void ) T1_CODE_OPT
    T1_PreExceptionHandlerData( T1_uint32_t param1, T1_uint32_t param2 );

/*! \brief T1 helper function. Do not edit. */
T1_CODE_FAST( void )
T1_CODE_OPT T1_PreExceptionHandlerData( T1_uint32_t param1, T1_uint32_t param2 )
{
    T1_ExceptionHandlerData( param1,
                             param2,
                             T1_CORE_ID_TO_FLEX_GLOBALS( T1_GetCoreIdOffset( ) ) );
}
#            define T1_STOP_SEC_CODE_FAST
#            include "T1_MemMap.h"

#        elif /* ... && ! defined T1_ARM8R && */ defined T1_ARM7M
/*----------------------------------------------------------------------------------*/
#            define T1_START_SEC_CODE_FAST
#            include "T1_MemMap.h"
/*! \brief T1 helper function. Do not edit. */
T1_CODE_FAST( void ) T1_CODE_OPT T1_DebugMonitorHandler( void )
{
    /*
     * T1_DebugMonitorHandler and T1_HardFaultHandler should have approximately the
     * same CET, so we replicate the functionally useless code to read and write HFSR.
     */
    T1_uint32_t volatile * const pHfsr = T1_P_HFSR;
    T1_uint32_t const hfsrDebugEvt = *pHfsr & T1_HFSR_DEBUGEVT_MASK;
    *pHfsr = hfsrDebugEvt; /* Writing zero has no effect */

    /*
     * REVIEWNOTE: Check that T1_DebugMonitorHandler_ is tail-called
     * (i.e. with no stack frame from T1_DebugMonitorHandler on the stack).
     */
    T1_DebugMonitorHandler_( T1_CORE_ID_TO_FLEX_GLOBALS( T1_GetCoreIdOffset( ) ) );
}
/*----------------------------------------------------------------------------------*/
/*! \brief T1 helper function. Modify only to forward to correct HardFaultHandler. */
T1_CODE_FAST( void ) T1_CODE_OPT T1_HardFaultHandler( void )
{
    T1_uint32_t volatile * const pHfsr = T1_P_HFSR;
    T1_uint32_t const hfsrDebugEvt = *pHfsr & T1_HFSR_DEBUGEVT_MASK;
    *pHfsr = hfsrDebugEvt; /* Clear HFSR.DEBUGEVT if set */
    if( 0uL != hfsrDebugEvt )
    {
        /*
         * HFSR.DEBUGEVT == 1
         * This is an escalated DebugMonitor exception
         * REVIEWNOTE: Check that T1_DebugMonitorHandler_ is tail-called
         * (i.e. with no stack frame from T1_HardFaultHandler on the stack).
         */
        T1_DebugMonitorHandler_(
            T1_CORE_ID_TO_FLEX_GLOBALS( T1_GetCoreIdOffset( ) ) );
        return;
    }
    /*
     * There is no use in restoring changed registers before forwarding to
     * application HardFaultHandler. They could have been corrupted also
     * by a previous tail-chaining exception handler so if HardFaultHandler
     * requires them, it has to restore them from the stack itself anyway.
     * REVIEWNOTE: Check that HardFaultHandler is tail-called
     * (i.e. with no stack frame from T1_HardFaultHandler on the stack).
     */
    {
        /* Modify to forward to appropriate application HardFault handler. */
        void HardFaultHandler( void );
        HardFaultHandler( );
    }
}
#            define T1_STOP_SEC_CODE_FAST
#            include "T1_MemMap.h"

#        endif /* defined T1_MPC5XXX */

#    endif /* ! defined T1_DISABLE_T1_FLEX */

#endif /* defined T1_ENABLE */

#if !defined T1_ENABLE || defined T1_DISABLE_T1_FLEX

#    define T1_START_SEC_CODE_FAST
#    include "T1_MemMap.h"
/*
 * TODO
 * If T1.flex is integrated in the vector table, define the T1.flex exception handler
 * entry point(s), to allow linking when T1.flex is disabled to forward the exception
 * to an existing handler, as a jump to either
 * (a) the unexpected exception handler, or
 * (b) the handler to which T1.flex would have forwarded a non-T1 exception, cf.
 *     ARM-7R T1_pAppHandlers
 * If there is really no suitable, existing handler, use an infinite loop to
 * demonstrate that this code is never reached.
 */
#    define T1_STOP_SEC_CODE_FAST
#    include "T1_MemMap.h"

#endif /* ! defined T1_ENABLE || defined T1_DISABLE_T1_FLEX */

/*----------------------------------------------------------------------------------*/
/*--- documentation ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_DOXYGEN_ONLY

/*!
 * \brief Disable the plug-in T1.cont, see [-disableT1Cont](@ref disableT1Cont)
 * and \ref SWITCH_PLUGINS.
 */
#    define T1_DISABLE_T1_CONT        ( 1 )

/*!
 * \brief Disable the plug-in T1.flex, see [-disableT1Flex](@ref disableT1Flex)
 * and \ref SWITCH_PLUGINS.
 */
#    define T1_DISABLE_T1_FLEX        ( 1 )

/*!
 * \brief Disable the plug-in T1.delay, see [-disableT1Delay](@ref disableT1Delay)
 * and \ref SWITCH_PLUGINS.
 */
#    define T1_DISABLE_T1_DELAY       ( 1 )

/*!
 * \brief Disable the plug-in T1.mod, see [-disableT1Mod](@ref disableT1Mod)
 * and \ref SWITCH_PLUGINS.
 */
#    define T1_DISABLE_T1_MOD         ( 1 )

/*!
 * \brief Enable preemption counting to enhance T1.flex restricted measurements.
 * See [-countPreemption](@ref countPreemption).
 */
#    define T1_COUNT_PREEMPTION       ( 1 )

/*!
 * \brief Enable remote T1.cont.
 * See [-contRunsOnCore](@ref contRunsOnCore).
 */
#    define T1_CONT_REMOTE            ( 1 )

/*!
 * \brief Enable tracing of cross-core task activation.
 * See [-crossCoreAct](@ref crossCoreAct).
 */
#    define T1_CROSS_CORE_ACT         ( 1 )

/*!
 * \brief Enable foreground T1.cont.
 * See [-foregroundCont](@ref foregroundCont).
 */
#    define T1_FG_CONT                ( 1 )

/*!
 * \brief Enable the T1-TARGET-SW, see \ref SWITCH.
 */
#    define T1_ENABLE                 ( 1 )

/*!
 * \brief Support timer overflow with \ref FOREGROUND_CONT.
 * See [-supportTimerOverflow](@ref supportTimerOverflow).
 */
#    define T1_SUPPORT_TIMER_OVERFLOW ( 1 )

/*!
 * \brief Check for timer overflow with \ref FOREGROUND_CONT.
 * See [-detectTimerOverflow](@ref detectTimerOverflow).
 */
#    define T1_DETECT_TIMER_OVERFLOW  ( 1 )

/*!
 * \brief Allow usage of T1_WAIT and T1_RESUME with T1.cont enabled.
 * See [-waitResume](@ref waitResume).
 */
#    define T1_WAIT_RESUME            ( 1 )

/*!
 * \brief Enable default target to host transmission using shared
 * memory for TRACE32 communication. This macro is generated when
 * [-rxChannel](@ref rxChannel) is set to TRACE32.
 * See [-t32TargetToHostBufferSize](@ref t32TargetToHostBufferSize).
 */
#    define T1_COMMS_SHARED_MEM_TX    ( 1 )

/*!
 * \brief Enable default host to target transmission using shared
 * memory for TRACE32 communication. This macro is generated when
 * [-txChannel](@ref txChannel) is set to TRACE32.
 * See [-t32HostToTargetBufferSize](@ref t32HostToTargetBufferSize).
 */
#    define T1_COMMS_SHARED_MEM_RX    ( 1 )

#endif /* T1_DOXYGEN_ONLY */
