/*********************************************************************************//*!
*   \file           T1_config.c
*
*   \brief          Application-specific configuration of T1
*
*   $Author: jialinli $
*
*   $Revision: 122 $
*
*   \copyright GLIWA GmbH embedded systems, Weilheim i.OB. All rights reserved
*************************************************************************************/

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#ifdef __TASKING__
/*
 * Avoid harmless but unnecessary clearing of T1_bss sections by the Tasking start-up
 * code.
 * This pragma is disallowed by some compiler options, so you may have to remove it.
 */
#   pragma noclear
#endif /* defined __TASKING__ */

/*
 * The following define is REQUIRED for MPC5xxx and SPC5xx. Only if T1.flex and
 * debugger coexistence is supported by the hardware this may be omitted.
 */
/* #define T1_FLEX_DISABLE_WITH_DEBUGGER (1) */

#define T1_OVERRIDE_SYNCTOTRACETIMERPC  (1) /* Backwards compatibility */

#include "T1_AppInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- Optimization pragmas for uniform code generation -----------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined __ghs__
#   pragma ghs OS
#elif defined __TASKING__
#   pragma optimize acefgIklMnoprsUvwy,+predict
#elif defined __GNUC__ && ! defined __TI_COMPILER_VERSION__
#   pragma GCC optimize "Os"
#endif

#if defined T1_ENABLE

/*----------------------------------------------------------------------------------*/
/*--- T1.base configuration --------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_START_SEC_CONST_32
#include "T1_MemMap.h"
T1_ALLOCATE_PLUGIN_TABLE( T1_pluginTable )
#define T1_STOP_SEC_CONST_32
#include "T1_MemMap.h"

#define T1_START_SEC_CODE
#include "T1_MemMap.h"

#if defined T1_NOF_CORES
void T1_CODE T1_SuspendAllInterruptsPC( T1_uint8Least_t coreId )
{
    /* Normally replaced by a call to AUTOSAR OS SuspendAllInterrupts( ) */
    T1_SuspendAllInterruptsPC_( coreId );
}
void T1_CODE T1_ResumeAllInterruptsPC( T1_uint8Least_t coreId )
{
    /* Normally replaced by a call to AUTOSAR OS ResumeAllInterrupts( ) */
    T1_ResumeAllInterruptsPC_( coreId );
}
void T1_CODE T1_DisableT1HandlerPC( T1_uint8Least_t coreId )
{
#   if ! defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE
    /* TODO: Obtain mutual exclusion with relevant core, see Integration Guide. */
#   else
    /* May be replaced by a call to AUTOSAR OS GetResource( ) */
    T1_SuspendAllInterruptsPC( coreId );
#   endif
}
void T1_CODE T1_EnableT1HandlerPC( T1_uint8Least_t coreId )
{
#   if ! defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE
    /* TODO: Obtain mutual exclusion with relevant core, see Integration Guide. */
#   else
    /* May be replaced by a call to AUTOSAR OS ReleaseResource( ) */
    T1_ResumeAllInterruptsPC( coreId );
#   endif
}
#else /* single core */
void T1_CODE T1_SuspendAllInterrupts( void )
{
    /* Normally replaced by AUTOSAR OS SuspendAllInterrupts( ); */
    T1_SuspendAllInterrupts_( );
}
void T1_CODE T1_ResumeAllInterrupts( void )
{
    /* Normally replaced by AUTOSAR OS ResumeAllInterrupts( ); */
    T1_ResumeAllInterrupts_( );
}
void T1_CODE T1_DisableT1Handler( void )
{
    /* May be replaced by AUTOSAR OS GetResource( ); */
    T1_SuspendAllInterrupts( );
}
void T1_CODE T1_EnableT1Handler( void )
{
    /* May be replaced by AUTOSAR OS ReleaseResource( ); */
    T1_ResumeAllInterrupts( );
}
#endif /* defined T1_NOF_CORES */

#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

/*----------------------------------------------------------------------------------*/
/*--- T1.cont configuration --------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if ! defined T1_DISABLE_T1_CONT

#   if defined T1_CONT_REMOTE && defined T1_ENABLE_WRITE_TIME
#       error T1_CONT_REMOTE and T1_ENABLE_WRITE_TIME are not compatible
#   endif /* defined T1_CONT_REMOTE && defined T1_ENABLE_WRITE_TIME */


/*!
 * Call-out function to act on a T1.cont constraint violation. The default
 * implementation halts tracing on every core using T1_AppSetStopTriggerAllCores().
 * See \ref PC.
 * \param[in] coreId       the T1 logical core ID of the trace analyzed by T1.cont
 * \param[in] result       the violating result in trace timer ticks
 * \param[in] idx          the index of the violated constraint
 * \param[in] afterXevents the number of additional events to trace on this core
 *                         before tracing actually stops, see T1_SetStopTriggerPC()
 */
#   define T1_START_SEC_CODE
#   include "T1_MemMap.h"
void T1_CODE
#   if defined T1_NOF_CORES
T1_ContCsrnCallbackPC( T1_uint8Least_t coreId, T1_resultTime_t result, T1_csrnIdx_t idx, T1_nofEntries_t afterXevnts )
#   else /* single core */
T1_ContCsrnCallback( T1_resultTime_t result, T1_csrnIdx_t idx, T1_nofEntries_t afterXevnts )
#   endif /* defined T1_NOF_CORES */
{
    if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRIGGER ) )
    {
        T1_AppSetStopTriggerAllCores( T1_CONT_RC_UNMAP( coreId ), afterXevnts );
    }
}

#   if defined T1_NOF_CORES
/*!
 * Call-out function on each T1.cont CPU load frame. The default
 * implementation traces the CPU load percentage as a user event and halts tracing on
 * every core using T1_AppSetStopTriggerAllCores().
 * See \ref PC.
 * \param[in] coreId           the T1 logical core ID of the trace analyzed by T1.cont
 * \param[in] to               overall time for the CPU load frame
 * \param[in] te               execution time of tasks/ISRs within the CPU load frame
 * \param[in] cpuLoadThreshold configured CPU load threshold
 * \param[in] afterXevnts      the number of additional events to trace on this core
 *                             before tracing stops, see T1_SetStopTriggerPC()
 */
void T1_CODE T1_ContCPULoadCallbackPC( T1_uint8Least_t coreId, T1_uint16Least_t to, T1_uint16Least_t te, T1_uint8Least_t cpuLoadThreshold, T1_nofEntries_t afterXevnts )
{
    if( T1_CONT_CPU_OVERLOAD( to, te, cpuLoadThreshold ) )
    {
        T1_TraceEventPC( T1_CONT_RC_UNMAP( coreId ), T1_UE_CPU_LOAD_CALLBACK_CORE0 + coreId, (T1_uint8Least_t)((te * 200uL + 1) / to) / 2u );
        if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRIGGER ) )
        {
            T1_AppSetStopTriggerAllCores( T1_CONT_RC_UNMAP( coreId ), afterXevnts );
        }
    }
}
#   else /* single core */
/*!
 * Call-out function to act on a T1.cont CPU load violation. The default
 * implementation traces the CPU load percentage as a user event and halts tracing on
 * every core using T1_AppSetStopTriggerAllCores().
 * See \ref PC.
 * \param[in] to               overall time for the CPU load frame
 * \param[in] te               execution time of tasks/ISRs within the CPU load frame
 * \param[in] cpuLoadThreshold configured CPU load threshold
 * \param[in] afterXevnts      the number of additional events to trace on this core
 *                             before tracing stops, see T1_SetStopTriggerPC()
 */
void T1_CODE T1_ContCPULoadCallback( T1_uint16Least_t to, T1_uint16Least_t te, T1_uint8Least_t cpuLoadThreshold, T1_nofEntries_t afterXevnts )
{
    if( T1_CONT_CPU_OVERLOAD( to, te, cpuLoadThreshold ) )
    {
        T1_TraceEvent( T1_UE_CPU_LOAD_CALLBACK_CORE0, (T1_uint8Least_t)((te * 200uL + 1u) / to) / 2u );
        if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRIGGER ) )
        {
            (void)T1_SetStopTrigger( afterXevnts );
        }
    }
}
#   endif /* defined T1_NOF_CORES */

/*!
 * Call-out function to act on a T1.cont error. The default
 * implementation traces the error mask as a user event and halts tracing on
 * every core using T1_AppSetStopTriggerAllCores().
 * See \ref PC.
 * \param[in] coreId       the T1 logical core ID of the trace analyzed by T1.cont
 * \param[in] errMask      the current error mask
 * \param[in] triggerMask  the mask of errors on which to trigger
 * \param[in] afterXevents the number of additional events to trace on this core
 *                         before tracing stops, see T1_SetStopTriggerPC()
 */
void T1_CODE
#   if defined T1_NOF_CORES
T1_ContErrCallbackPC( T1_uint8Least_t coreId, T1_uint8Least_t errMask, T1_uint8Least_t triggerMask, T1_nofEntries_t afterXevnts )
#   else /* single core */
T1_ContErrCallback( T1_uint8Least_t errMask, T1_uint8Least_t triggerMask, T1_nofEntries_t afterXevnts )
#   endif /* defined T1_NOF_CORES */
{
/* polyspace<MISRA-C3:2.2:Not a defect:Other> Checker artefact? This code is not dead. */
    INC_T1_ERROR_COUNT( coreId );
#   if defined T1_NOF_CORES
    T1_TraceEventPC(    T1_CONT_RC_UNMAP( coreId ),
                        T1_UE_T1_CONT_ERR_CORE0 + coreId,
                        errMask );
#   else /* single core */
    T1_TraceEvent( T1_UE_T1_CONT_ERR_CORE0, errMask );
#   endif /* defined T1_NOF_CORES */
    if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRIGGER ) && (0 != (errMask & triggerMask)) )
    {
        T1_AppSetStopTriggerAllCores( T1_CONT_RC_UNMAP( coreId ), afterXevnts );
    }
}

/*!
 * Call-out function to act on T1.cont overhead calibration. The default
 * implementation frees the used event chains using T1_CONT_STOP_CALIBRATION_PC().
 * See \ref PC.
 * \param[in] coreId       the T1 logical core ID of the trace analyzed by T1.cont
 * \param[in] errMask      the current error mask
 * \param[in] afterXevents the number of additional events to trace on this core
 *                         before tracing stops, see T1_SetStopTriggerPC()
 */
void T1_CODE
#   if defined T1_NOF_CORES
T1_ContOHCallbackPC( T1_uint8Least_t coreId, T1_uint8Least_t errMask )
#   else /* single core */
T1_ContOHCallback( T1_uint8Least_t errMask )
#   endif /* defined T1_NOF_CORES */
{
    if( 0u == (T1_INF_OVERHEADS_UPDATED & errMask) )
    {
        /* Overheads were not updated */
/* polyspace<MISRA-C3:2.2:Not a defect:Other> Suspecting checker artefact, this code is not dead. */
        INC_T1_ERROR_COUNT( T1_CONT_RC_UNMAP( coreId ) );
    }
    /* Free T1.cont event chains used for calibration */
    T1_CONT_STOP_CALIBRATION_PC( coreId );
}

/*!
 * Call-out function to supply CET for ISRs instrumented only with T1_START_STOP.
 * See \ref PC.
 * \param[in] coreId       the T1 logical core ID of the trace analyzed by T1.cont
 * \param[in] taskIdx      the T1.cont task index of the ISR
 */
T1_resultTime_t T1_CODE
#   if defined T1_NOF_CORES
T1_ContStartStopCETPC( T1_UNUSED( T1_uint8Least_t coreId ), T1_UNUSED( T1_taskIdx_t taskIdx ) )
#   else /* single core */
T1_ContStartStopCET( T1_UNUSED( T1_taskIdx_t taskIdx ) )
#   endif /* defined T1_NOF_CORES */
{
    /* T1_START_STOP is not used */
    return 0uL;
}

/*!
 * Translate a duration in synchronization timer ticks to trace timer ticks. This is
 * used as a call-out from library code and should not normally be called directly
 * from user code.
 * \param[in] coreId    use the trace timer tick duration for this core
 * \param[in] getSwTime the GET stopwatch duration to convert
 * \returns             converted result
 */
#   if defined T1_NOF_CORES
#       if (1 == T1_NOF_CORES && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE0) || (2 == T1_NOF_CORES && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE0 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE1) || (3 == T1_NOF_CORES && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE0 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE1 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE2) || (4 == T1_NOF_CORES && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE0 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE1 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE2 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE3) || (5 == T1_NOF_CORES && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE0 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE1 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE2 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE3 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE4) || (6 == T1_NOF_CORES && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE0 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE1 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE2 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE3 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE4 && T1_TRACE_TIMER_IS_SYNC_TIMER_CORE5)
/* polyspace<MISRA-C3:20.7:Low:Improve> This deal with unused parameters is not MISRA compliant. */
T1_longTime_t T1_CODE T1_SyncToTraceTimerPC( T1_UNUSED( T1_uint8Least_t coreId ), T1_longTime_t getSwTime )
{
    return getSwTime;
}
#       else
T1_longTime_t T1_CODE T1_SyncToTraceTimerPC( T1_uint8Least_t coreId, T1_longTime_t getSwTime )
{
/*
 * TODO: Use the following code ONLY AFTER careful checking for loss of precision at
 *       integer casts and overflow at multiplication. Alternatives include using a
 *       single integer divide or a shift or using floating-point arithmetic.
 */
    switch( coreId )
    {
    default:
        if( T1_SYNC_TIMER_DURATION_NS <= T1_TICK_DURATION_CORE0_NS )
        {
/* polyspace<MISRA-C3:16.3:Low:Justified> A return followed by a break statement may give rise to a warning with certain compilers */
            return getSwTime / (T1_longTime_t)(T1_TICK_DURATION_CORE0_NS / T1_SYNC_TIMER_DURATION_NS);
        }
/* polyspace<MISRA-C3:16.3:Low:Justified> A return followed by a break statement may give rise to a warning with certain compilers */
        return getSwTime * (T1_longTime_t)(T1_SYNC_TIMER_DURATION_NS / T1_TICK_DURATION_CORE0_NS);
#           if 1 < T1_NOF_CORES
    case 1:
        if( T1_SYNC_TIMER_DURATION_NS <= T1_TICK_DURATION_CORE1_NS )
        {
/* polyspace<MISRA-C3:16.3:Low:Justified> A return followed by a break statement may give rise to a warning with certain compilers */
            return getSwTime / (T1_longTime_t)(T1_TICK_DURATION_CORE1_NS / T1_SYNC_TIMER_DURATION_NS);
        }
/* polyspace<MISRA-C3:16.3:Low:Justified> A return followed by a break statement may give rise to a warning with certain compilers */
        return getSwTime * (T1_longTime_t)(T1_SYNC_TIMER_DURATION_NS / T1_TICK_DURATION_CORE1_NS);
#           endif /* 1 < T1_NOF_CORES */
#           if 2 < T1_NOF_CORES
    case 2:
        if( T1_SYNC_TIMER_DURATION_NS <= T1_TICK_DURATION_CORE2_NS )
        {
/* polyspace<MISRA-C3:16.3:Low:Justified> A return followed by a break statement may give rise to a warning with certain compilers */
            return getSwTime / (T1_longTime_t)(T1_TICK_DURATION_CORE2_NS / T1_SYNC_TIMER_DURATION_NS);
        }
/* polyspace<MISRA-C3:16.3:Low:Justified> A return followed by a break statement may give rise to a warning with certain compilers */
        return getSwTime * (T1_longTime_t)(T1_SYNC_TIMER_DURATION_NS / T1_TICK_DURATION_CORE2_NS);
#           endif /* 2 < T1_NOF_CORES */
#           if 3 < T1_NOF_CORES
    case 3:
        if( T1_SYNC_TIMER_DURATION_NS <= T1_TICK_DURATION_CORE3_NS )
        {
/* polyspace<MISRA-C3:16.3:Low:Justified> A return followed by a break statement may give rise to a warning with certain compilers */
            return getSwTime / (T1_longTime_t)(T1_TICK_DURATION_CORE3_NS / T1_SYNC_TIMER_DURATION_NS);
        }
/* polyspace<MISRA-C3:16.3:Low:Justified> A return followed by a break statement may give rise to a warning with certain compilers */
        return getSwTime * (T1_longTime_t)(T1_SYNC_TIMER_DURATION_NS / T1_TICK_DURATION_CORE3_NS);
#           endif /* 3 < T1_NOF_CORES */
#           if 4 < T1_NOF_CORES
    case 4:
        if( T1_SYNC_TIMER_DURATION_NS <= T1_TICK_DURATION_CORE4_NS )
        {
/* polyspace<MISRA-C3:16.3:Low:Justified> A return followed by a break statement may give rise to a warning with certain compilers */
            return getSwTime / (T1_longTime_t)(T1_TICK_DURATION_CORE4_NS / T1_SYNC_TIMER_DURATION_NS);
        }
/* polyspace<MISRA-C3:16.3:Low:Justified> A return followed by a break statement may give rise to a warning with certain compilers */
        return getSwTime * (T1_longTime_t)(T1_SYNC_TIMER_DURATION_NS / T1_TICK_DURATION_CORE4_NS);
#           endif /* 4 < T1_NOF_CORES */
#           if 5 < T1_NOF_CORES
    case 5:
        if( T1_SYNC_TIMER_DURATION_NS <= T1_TICK_DURATION_CORE5_NS )
        {
/* polyspace<MISRA-C3:16.3:Low:Justified> A return followed by a break statement may give rise to a warning with certain compilers */
            return getSwTime / (T1_longTime_t)(T1_TICK_DURATION_CORE5_NS / T1_SYNC_TIMER_DURATION_NS);
        }
/* polyspace<MISRA-C3:16.3:Low:Justified> A return followed by a break statement may give rise to a warning with certain compilers */
        return getSwTime * (T1_longTime_t)(T1_SYNC_TIMER_DURATION_NS / T1_TICK_DURATION_CORE5_NS);
#           endif /* 5 < T1_NOF_CORES */
    }
}
#       endif
#   endif /* T1_NOF_CORES */

#   if defined T1_CONT_DIRECT_ID_MAPPINGS

/*! \brief T1 helper function. Do not edit. */
T1_stpwIdx_t T1_CODE
#       if defined T1_NOF_CORES
/* polyspace<MISRA-C3:20.7:Low:Improve> This deal with unused parameters is not MISRA compliant. */
T1_ContUserStpwIdxToIdPC( T1_UNUSED( T1_uint8Least_t coreId ), T1_uint16Least_t stpwId )
#       else /* single core */
T1_ContUserStpwIdxToId( T1_uint16Least_t stpwId )
#       endif /* defined T1_NOF_CORES */
{
    return (T1_stpwIdx_t)stpwId;
}

/*! \brief T1 helper function. Do not edit. */
T1_uint16Least_t T1_CODE
#       if defined T1_NOF_CORES
/* polyspace<MISRA-C3:20.7:Low:Improve> This deal with unused parameters is not MISRA compliant. */
T1_GetTaskIdByIdxPC( T1_UNUSED( T1_uint8Least_t coreId ), T1_taskIdx_t taskIdx )
#       else /* single core */
T1_GetTaskIdByIdx( T1_taskIdx_t taskIdx )
#       endif /* defined T1_NOF_CORES */
{
    return (T1_uint16Least_t)taskIdx;
}

#   else /* T1.cont idx != T1.scope ID */

/*! \brief T1 helper function. Do not edit. */
T1_stpwIdx_t T1_CODE
#       if defined T1_NOF_CORES
T1_ContUserStpwIdxToIdPC( T1_uint8Least_t coreId, T1_uint16Least_t stpwId )
{
    return T1_stpwConfigPC[coreId][stpwIdx].id;
}
#       else /* single core */
T1_ContUserStpwIdxToId( T1_uint16Least_t stpwId )
{
    return T1_stpwConfig[stpwIdx].id;
}
#       endif /* defined T1_NOF_CORES */

/*!
 * Call-out function to translate from T1.cont task index to T1.scope task identifier.
 * \param[in] taskIdx T1.cont task index to be translated.
 */
T1_uint16Least_t T1_CODE
#       if defined T1_NOF_CORES
T1_GetTaskIdByIdxPC( T1_uint8Least_t coreId, T1_taskIdx_t taskIdx )
#       else /* single core */
T1_GetTaskIdByIdx( T1_taskIdx_t taskIdx )
#       endif /* defined T1_NOF_CORES */
{
    return <insert code to translate from T1.cont task idx to T1.scope task ID>;
}

/*!
 * Call-out function to translate from T1.scope task identifier to T1.cont task index.
 * \param[in] taskId T1.scope task identifier to be translated.
 */
T1_taskIdx_t T1_CODE
#       if defined T1_NOF_CORES
T1_GetTaskIdxByIdPC( T1_uint8Least_t coreId, T1_uint16Least_t taskId )
#       else /* single core */
T1_GetTaskIdxByIdP( T1_uint16Least_t taskId )
#       endif /* defined T1_NOF_CORES */
{
    return <insert code to translate from T1.scope task ID to T1.cont task idx>;
}

#   endif /* defined T1_CONT_DIRECT_ID_MAPPINGS */

#   if defined T1_NOF_CORES
#       if !defined T1_70618
/* polyspace<MISRA-C3:20.7:Low:Improve> This deal with unused parameters is not MISRA compliant. */
void T1_CODE T1_49672( T1_UNUSED( T1_uint8Least_t coreId ), T1_UNUSED( T1_taskIdx_t taskIdx ), T1_UNUSED( T1_resultTime_t taskCET ) ) { }
/* polyspace<MISRA-C3:20.7:Low:Improve> This deal with unused parameters is not MISRA compliant. */
void T1_CODE T1_84399( T1_UNUSED( T1_uint8Least_t coreId ), T1_UNUSED( T1_longTime_t now ) ) { }
#       endif /* defined T1_70618 */
#   else /* single core */
#       if !defined T1_70618
/* polyspace<MISRA-C3:20.7:Low:Improve> This deal with unused parameters is not MISRA compliant. */
void T1_CODE T1_63193( T1_UNUSED( T1_taskIdx_t taskIdx ), T1_UNUSED( T1_resultTime_t taskCET ) ) { }
/* polyspace<MISRA-C3:20.7:Low:Improve> This deal with unused parameters is not MISRA compliant. */
void T1_CODE T1_00767( T1_UNUSED( T1_longTime_t now ) ) { }
#       endif /* defined T1_70618 */
#   endif /* defined T1_NOF_CORES */

#   define T1_STOP_SEC_CODE
#   include "T1_MemMap.h"

#endif /* ! defined T1_DISABLE_T1_CONT  */

/*----------------------------------------------------------------------------------*/
/*--- T1.scope configuration -------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if ! defined T1_DISABLE_T1_SCOPE

#   if defined T1_NOF_CORES
/*!
 * Not in a T1-TARGET-SW section because it is initialized RAM, for which T1 has no section.
 * Locate in shared, un-cached RAM. See T1_GetCalibrationSpinlockPC().
 */
T1_uint32_t T1_ALIGN_32 T1_spinlockVar = 0uL;
#   endif /* defined T1_NOF_CORES */

#   define T1_START_SEC_CODE_FAST
#   include "T1_MemMap.h"

#   if defined __ghs__
/* Green Hills __noinline keyword can be disabled, so use the pragma in stead. */
#       pragma ghs startnoinline
#   endif

#   if defined T1_ENABLE_WRITE_TIME

/*!
 * Call-out function used only if #T1_ENABLE_WRITE_TIME is defined.
 * It is time-critical and to be optimized as required.
 * \param[out] pTimeStamp Write the low 16 bits of the time-stamp at this address
 * \returns               all counting bits of the time-stamp.
 */
T1_tickUint_t T1_NOINLINE T1_CODE_FAST T1_WriteTraceTime(
#       if defined T1_32BIT_TRACE_TIME
                                                            T1_traceEntry_t
#       else
                                                            T1_uint16_t
#       endif /* defined T1_32BIT_TRACE_TIME */
                                                                *pTimeStamp )
{
    T1_tickUint_t const now = T1_GET_TRACE_TIME( );
#       if defined T1_32BIT_TRACE_TIME
    pTimeStamp->timeLow  = (T1_uint16_t)now;
    pTimeStamp->timeHigh = (T1_uint16_t)(now >> 16);
#       else
    *pTimeStamp = (T1_uint16_t)now;
#       endif /* defined T1_32BIT_TRACE_TIME */
    return now;
}

#   else /* ! defined T1_ENABLE_WRITE_TIME */

/*!
 * Insert one event in the trace buffer assuming that interrupts are disabled.
 * This is not part of the T1-TARGET-SW API. Do NOT call it directly from user
 * code. It is called from the API macro layer, see T1_TraceEventNoSuspPC(), for
 * example.
 */
T1_tickUint_t T1_NOINLINE T1_CODE_FAST
T1_TraceEventNoSusp__( T1_SCOPE_GLOBALS_PARAM T1_uint16Least_t eventInfo )
{
    return
#       if defined T1_CONT_REMOTE
        T1_TraceEventNoSuspTimeRC__
#       else /* ! defined T1_CONT_REMOTE */
        T1_TraceEventNoSuspTime__
#       endif /* defined T1_CONT_REMOTE */
            ( T1_SCOPE_GLOBALS_ARG eventInfo, T1_GET_TRACE_TIME( ) );
}

#   endif /* defined T1_ENABLE_WRITE_TIME */

#   if defined __ghs__
#       pragma ghs endnoinline
#   endif

#   if defined T1_NOF_CORES
/*!
 * Obtain the synchronisation trace timer value.
 * It is time-critical and to be optimized as required.
 * There is no need to mask off any non-counting bits.
 * \returns the synchronization timer count register
 */
T1_uint32_t T1_CODE_FAST T1_GetSyncTime( void )
{
    return T1_GET_SYNC_TIME( );
}
#   endif /* defined T1_NOF_CORES */

#   define T1_STOP_SEC_CODE_FAST
#   include "T1_MemMap.h"

#   define T1_START_SEC_CODE
#   include "T1_MemMap.h"

#   if defined T1_NOF_CORES

#       if 1 < T1_NOF_CORES
/*!
 * Short delay used only to inhibit "thrashing" of T1_spinlockVar, see
 * T1_GetCalibrationSpinlockPC().
 */
static void T1_CODE T1_delay( void )
{
    T1_NOP( ); T1_NOP( ); T1_NOP( );
    T1_NOP( ); T1_NOP( ); T1_NOP( );
    T1_NOP( ); T1_NOP( ); T1_NOP( );
    T1_NOP( ); T1_NOP( ); T1_NOP( );
    T1_NOP( ); T1_NOP( ); T1_NOP( );
}
#       endif /* 1 < T1_NOF_CORES */

/*!
 * Obtain mutual exclusion with other cores for T1 overhead calibration sequence
 * and, if isNoSusp is zero, suspend interrupts.
 * This is used as a call-out from library code and should not be called directly from
 * user code. Normally the integrator should replace the body of this function with a
 * call to existing application code.
 * See \ref PC.
 * \param[in] coreId   the T1 logical core ID of the calling core
 * \param[in] isNoSusp zero unless called in ...NoSusp context, see \ref INTRPT.
 */
void T1_CODE T1_GetCalibrationSpinlockPC( T1_uint8Least_t coreId, T1_bool_t isNoSusp )
{
    if( isNoSusp )
    {
#       if 1 < T1_NOF_CORES
        while( ! T1_ObtainedMutexPC( coreId, &T1_spinlockVar ) )
        {
            /* Spin with interrupt lock is unavoidable */
/* polyspace<MISRA-C3:2.2:Not a defect:Justifed> Nonfunctional effect needed. */
            T1_delay( );
        }
#       endif /* 1 < T1_NOF_CORES */
    }
    else
    {
        T1_SuspendAllInterruptsPC( coreId );
#       if 1 < T1_NOF_CORES
        while( ! T1_ObtainedMutexPC( coreId, &T1_spinlockVar ) )
        {
            /* Avoid spinning with interrupts disabled */
            T1_ResumeAllInterruptsPC( coreId );
/* polyspace<MISRA-C3:2.2:Not a defect:Justifed> Nonfunctional effect needed. */
            T1_delay( );
            T1_SuspendAllInterruptsPC( coreId );
        }
#       endif /* 1 < T1_NOF_CORES */
    }
}

/*!
 * Release mutual exclusion with other cores for T1 overhead calibration sequence
 * and, if isNoSusp is zero, suspend interrupts.
 * This is used as a call-out from library code and should not be called directly from
 * user code. Normally the integrator should replace the body of this function with a
 * call to existing application code.
 * See \ref PC.
 * \param[in] coreId   the T1 logical core ID of the calling core
 * \param[in] isNoSusp zero unless called in ...NoSusp context, see \ref INTRPT.
 */
void T1_CODE T1_ReleaseCalibrationSpinlockPC( T1_uint8Least_t coreId, T1_bool_t isNoSusp )
{
#       if 1 < T1_NOF_CORES
    T1_spinlockVar = 0uL;   /* Clear to release mutex. */
#       endif /* 1 < T1_NOF_CORES */

    if( ! isNoSusp )
    {
        T1_ResumeAllInterruptsPC( coreId );
    }
}

#   endif /* defined T1_NOF_CORES */

/*!
 * Insert one event in the trace buffer assuming that interrupts are disabled
 * without assuming supervisor privileges. This is used as a call-out from library
 * code and should not normally be called directly from user code.
 * See \ref PC and \ref INTRPT.
 * \param[in] eventInfo combined event ID and info field created by
 *                      T1_COMBINE_EVENT_INFO()
 * \returns             all counting bits of the time-stamp
 */
T1_tickUint_t T1_CODE T1_TraceEventNoSuspUM( T1_uint16Least_t eventInfo )
{
    return T1_TraceEventNoSusp__(
#   if defined T1_USE_SCOPE_GLOBALS_PARAM
                                    T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ),
#   endif /* defined T1_USE_SCOPE_GLOBALS_PARAM */
                                    eventInfo );
}

/*!
 * Insert one event in the trace buffer without assuming supervisor privileges. This
 * is used as a call-out from library code and should not normally be called directly
 * from user code.
 * See \ref PC and \ref INTRPT.
 * \param[in] eventInfo combined event ID and info field created by
 *                      T1_COMBINE_EVENT_INFO()
 * \returns             all counting bits of the time-stamp
 */
void T1_CODE T1_TraceEventUM( T1_uint16Least_t eventInfo )
{
#   if defined T1_NOF_CORES
    const T1_uint8Least_t coreId = T1_GetCoreIdOffset( );
#   endif /* defined T1_NOF_CORES */
    T1_SuspendAllInterruptsPC( coreId );
    (void)T1_TraceEventNoSusp__(
#   if defined T1_USE_SCOPE_GLOBALS_PARAM
                                    T1_CORE_ID_TO_SCOPE_GLOBALS( coreId ),
#   endif /* defined T1_USE_SCOPE_GLOBALS_PARAM */
                                    eventInfo );
    T1_ResumeAllInterruptsPC( coreId );
}

/*!
 * Insert one event in the trace buffer assuming that interrupts are disabled
 * without assuming supervisor privileges. This is used as a call-out from library
 * code and should not normally be called directly from user code.
 * See \ref PC and \ref INTRPT.
 * \param[in] coreId    the T1 logical core ID of the calling core
 * \param[in] eventInfo combined event ID and info field created by
 *                      T1_COMBINE_EVENT_INFO()
 * \returns             all counting bits of the time-stamp
 */
T1_tickUint_t T1_CODE T1_TraceEventNoSuspUMPC(  T1_uint8Least_t coreId,
                                                T1_uint16Least_t eventInfo )
{
    return T1_TraceEventNoSusp__(
#   if defined T1_USE_SCOPE_GLOBALS_PARAM
                                    T1_CORE_ID_TO_SCOPE_GLOBALS( coreId ),
#   endif /* defined T1_USE_SCOPE_GLOBALS_PARAM */
                                    eventInfo );
}

/*!
 * Insert one event in the trace buffer without assuming supervisor privileges. This
 * is used as a call-out from library code and should not normally be called directly
 * from user code.
 * See \ref PC and \ref INTRPT.
 * \param[in] coreId   the T1 logical core ID of the calling core
 * \param[in] eventInfo combined event ID and info field created by
 *                      T1_COMBINE_EVENT_INFO()
 * \returns             all counting bits of the time-stamp
 */
void T1_CODE T1_TraceEventUMPC( T1_uint8Least_t coreId,
                                T1_uint16Least_t eventInfo )
{
    T1_SuspendAllInterruptsPC( coreId );
    (void)T1_TraceEventNoSusp__(
#   if defined T1_USE_SCOPE_GLOBALS_PARAM
                                    T1_CORE_ID_TO_SCOPE_GLOBALS( coreId ),
#   endif /* defined T1_USE_SCOPE_GLOBALS_PARAM */
                                    eventInfo );
    T1_ResumeAllInterruptsPC( coreId );
}

/*!
 * Obtain the current trace timer value.
 * It is time-critical and to be optimized as required.
 * There is no need to mask off any non-counting bits.
 * \returns the trace timer count register
 */
T1_tickUint_t T1_CODE T1_GetTraceTime( void )
{
    return T1_GET_TRACE_TIME( );
}

#   define T1_STOP_SEC_CODE
#   include "T1_MemMap.h"

#   if defined T1_DISABLE_T1_FLEX
#       define T1_START_SEC_CODE
#       include "T1_MemMap.h"
void T1_CODE
#       if defined T1_NOF_CORES
                T1_FlexOHAddrPC(    T1_uint8Least_t coreId,
#       else /* single core */
                T1_FlexOHAddr(
#       endif /* defined T1_MULTICORE */
                                    T1_uint32_t pAddrStart )
{
    /* Empty function to allow linkage when T1.flex is disabled. */
}
#       define T1_STOP_SEC_CODE
#       include "T1_MemMap.h"
#   endif /* defined T1_DISABLE_T1_FLEX */

#endif /* defined T1_DISABLE_T1_SCOPE */

#endif /* defined T1_ENABLE */

/*----------------------------------------------------------------------------------*/
/*--- T1.flex configuration --------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX
T1_uint32_t T1_flexInitSem __attribute__(( __align( 4 ) )) = 0uL;
#   if defined T1_FLEX_DISABLE_WITH_DEBUGGER
#       define T1_START_SEC_CODE
#       include "T1_MemMap.h"
T1_uint8Least_t T1_CODE T1_FlexDisallowExternalDebug( void )
{
    return (T1_uint8Least_t)T1_TRUE;
}
#       define T1_STOP_SEC_CODE
#       include "T1_MemMap.h"
#   endif /* defined T1_FLEX_DISABLE_WITH_DEBUGGER */

#   if defined T1_MPC5XXX
#       define T1_START_SEC_CODE_FAST
#       include "T1_MemMap.h"
/* polyspace<MISRA-C3:8.2,8.3:Not a defect:Other> Artefact of monolithic checker project.
   polyspace<DEFECT:DECL_MISMATCH:Not a defect:Other> Artefact of monolithic checker project. */
T1_EXTERN void T1_CODE_FAST T1_CODE_OPT T1_ExceptionHandler( T1_uint32_t param1, T1_uint32_t param2, T1_uint32_t param3, T1_uint32_t param4, T1_flexGlobals_t * const pFlexGlobals );
T1_EXTERN void T1_CODE_FAST T1_CODE_OPT T1_PreExceptionHandler( T1_uint32_t param1, T1_uint32_t param2, T1_uint32_t param3, T1_uint32_t param4 );

/*! \brief T1 helper function. Do not edit. */
void T1_CODE_FAST T1_CODE_OPT T1_PreExceptionHandler( T1_uint32_t param1, T1_uint32_t param2, T1_uint32_t param3, T1_uint32_t param4 )
{
    T1_ExceptionHandler( param1, param2, param3, param4,
#       if defined T1_NOF_CORES
#           if 1 == T1_NOF_CORES
                         &T1_flexGlobals0 );
#           elif 2 == T1_NOF_CORES
                         /* For exactly two cores it is faster to use the ?: operator */
                         ( 0u == T1_GetCoreIdOffset( ) ) ? &T1_flexGlobals0 : &T1_flexGlobals1 );
#           else /* More than 2 cores */
                         T1_flexGlobalsPC[T1_GetCoreIdOffset( )] );
#           endif /* T1_NOF_CORES */
#       else /* ! defined T1_NOF_CORES */
                         &T1_flexGlobals );
#       endif /* defined T1_NOF_CORES */
}
#       define T1_STOP_SEC_CODE_FAST
#       include "T1_MemMap.h"
#   endif /* defined T1_MPC5XXX */


#else /* T1.flex is disabled */

#   define T1_START_SEC_CODE_FAST
#   include "T1_MemMap.h"
/*
 * TODO
 * If T1.flex is integrated in the vector table, define the T1.flex exception handler
 * entry point(s), to allow linking when T1.flex is disabled to forward the exception
 * to an existing handler, as a jump to either
 * (a) the unexpected exception handler, or
 * (b) the handler to which T1.flex would have forwarded a non-T1 exception, cf.
 *     ARM-7R T1_pAppPrefetchAbortHandler and T1_pAppDataAbortHandler
 * If there is really no suitable, existing handler, use an infinite loop to
 * demonstrate that this code is never reached.
 */
#   define T1_STOP_SEC_CODE_FAST
#   include "T1_MemMap.h"

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX */
