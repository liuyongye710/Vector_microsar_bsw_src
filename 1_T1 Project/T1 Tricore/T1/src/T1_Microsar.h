/***************************************************************************//*!
*   \file      T1_Microsar.h
*
*   \brief     This file glues the OS Timing Hooks of the
*              Microsar OS to T1 trace event calls
*
*   $Author: jialinli $
*
*   $Revision: 120 $
*
*   \copyright GLIWA GmbH embedded systems, Weilheim i.OB. All rights reserved
*******************************************************************************/

#ifndef T1_MICROSAR_H_
#define T1_MICROSAR_H_ (1)

#include "T1_AppInterface.h"

#if defined T1_ENABLE && !defined T1_DISABLE_T1_SCOPE

    /*
     * General Information:
     * The OS_VTH_ hooks are all called with category 2 interrupts
     * disabled. Therefore the NoSusp variants of the T1 trace
     * event calls can be used if only category 2 interrupts are
     * present.
     * If category 1 or category 0 interrupts are present and
     * instrumented then this file needs to be switched to the
     * standard variant of the T1 trace event calls.
     * This interface implementation can be used for the 'endless
     * ECC task model' for tasks which are using events for scheduling
     * if T1_WAIT_RESUME is not defined.
     * It can also be used when T1_WAIT_RESUME is defined for normal
     * usage of the events, for the terminating ECC task model
     * or the endless ECC task model where there is more than one event
     * used only for scheduling.
     * Note: only if OS_VTH_WAITEVENT_NOWAIT is implemented in the
     * OS version being used T1 can recognize the case that an event
     * for which an extended task shall wait is already set before
     * the WaitEvent call. If this hook is not implemented this case
     * leads to an accumulation of the CETs of multiple loops.
     */

/*-----------------------------------------------------------*/
/*--- macros ------------------------------------------------*/
/*-----------------------------------------------------------*/

    /*
     * Trace task activation. Check T1_TRACE_TASK to exclude
     * tasks from tracing.
     */
#   define OS_VTH_ACTIVATION( taskId_, destCoreId_, callerCoreId_ )                  \
        if( T1_TRACE_TASK( taskId_ ) )                                               \
        {                                                                            \
            T1_TraceActivationNoSuspPC( ( callerCoreId_ ), ( taskId_ ) );            \
        }

/*-----------------------------------------------------------*/

    /*
     * Trace a failed task activation and halt the tracing if
     * T1_AF_ALLOW_TRIGGER is set. Check T1_TRACE_TASK to
     * exclude tasks from tracing.
     */
#   define OS_VTH_ACTIVATION_LIMIT( taskId_, destCoreId_, callerCoreId_ )                               \
        if( T1_TRACE_TASK( taskId_ ) )                                                                  \
        {                                                                                               \
            T1_TraceEventNoSuspPC( ( callerCoreId_ ), T1_ACTIVATION_FAILED, ( taskId_ ) );              \
            if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRIGGER ) )                                            \
            {                                                                                           \
                T1_AppSetStopTriggerAllCores( callerCoreId_, T1_BUFFER_SIZE_PC( callerCoreId_ ) >> 2 ); \
            }                                                                                           \
        }

/*-----------------------------------------------------------*/

#   if defined T1_WAIT_RESUME
        /*
         * Trace task release after the setting of an event,
         * if the task state changes from WAITING to READY.
         * Check T1_TRACE_TASK to exclude tasks from tracing.
         */
#       define OS_VTH_SETEVENT( taskId_, eventMask_, stateChange_, destCoreId_, callerCoreId_ )  \
            if( ( stateChange_ ) && T1_TRACE_TASK( taskId_ ) )                                   \
            {                                                                                    \
                T1_TraceReleaseNoSuspPC( ( callerCoreId_ ), ( taskId_ ) );                       \
            }
#   else
        /*
         * Trace task activation after the setting of an event,
         * if the task state changes from WAITING to READY.
         * Check T1_TRACE_TASK to exclude tasks from tracing.
         */
#       define OS_VTH_SETEVENT( taskId_, eventMask_, stateChange_, destCoreId_, callerCoreId_ )  \
            if( ( stateChange_ ) && T1_TRACE_TASK( taskId_ ) )                                   \
            {                                                                                    \
                T1_TraceActivationNoSuspPC( ( callerCoreId_ ), ( taskId_ ) );                    \
            }
#   endif /* defined T1_WAIT_RESUME */

/*-----------------------------------------------------------*/

#   if defined T1_WAIT_RESUME
        /*
         * Trace T1_STOP for task termination and end of ISR
         *
         * Trace T1_WAIT for tasks calling WaitEvent().
         *
         * Trace T1_START for start of ISR (NoAct), task activation
         * (here: meaning first transition from READY to RUNNING),
         *
         * Trace T1_RESUME for resumption returning from WaitEvent().
         *
         * Check T1_TRACE_TASK to exclude tasks from tracing.
         *
         * Do not trace anything in all other cases.
         * Not considering semaphores so far.
         */
#       define OS_VTH_SCHEDULE( fromThreadId_, fromThreadReason_, toThreadId_, toThreadReason_, callerCoreId_ ) \
            {                                                                                                   \
                const T1_uint8Least_t fromId = ( fromThreadId_ );                                               \
                const T1_uint8Least_t toId = ( toThreadId_ );                                                   \
                /* Old Tasks */                                                                                 \
                if( (  ( OS_VTHP_TASK_TERMINATION == ( fromThreadReason_ ) )                                    \
                    || ( OS_VTHP_ISR_END          == ( fromThreadReason_ ) ) )                                  \
                    && T1_TRACE_TASK( fromId ) )                                                                \
                {                                                                                               \
                    T1_TraceStopNoSuspPC( ( callerCoreId_ ), fromId );                                          \
                }                                                                                               \
                else if( ( OS_VTHP_TASK_WAITEVENT == ( fromThreadReason_ ) ) && T1_TRACE_TASK( fromId ) )       \
                {                                                                                               \
                    T1_TraceWaitNoSuspPC( ( callerCoreId_ ), fromId );                                          \
                }                                                                                               \
                /* CAT2 ISR Start */                                                                            \
                if(      ( OS_VTHP_ISR_START       == ( toThreadReason_ ) ) && T1_TRACE_TASK( toId ) )          \
                {                                                                                               \
                    T1_TraceStartNoActNoSuspPC( ( callerCoreId_ ), toId );                                      \
                }                                                                                               \
                /* New Tasks */                                                                                 \
                else if( ( OS_VTHP_TASK_ACTIVATION == ( toThreadReason_ ) ) && T1_TRACE_TASK( toId ) )          \
                {                                                                                               \
                    T1_TraceStartNoSuspPC( ( callerCoreId_ ), toId );                                           \
                }                                                                                               \
                /* ECC Task resume after set event */                                                           \
                else if( ( OS_VTHP_TASK_SETEVENT   == ( toThreadReason_ ) ) && T1_TRACE_TASK( toId ) )          \
                {                                                                                               \
                    T1_TraceResumeNoSuspPC( ( callerCoreId_ ), toId );                                          \
                }                                                                                               \
            }
#   else
        /*
         * Trace T1_STOP for task termination, end of ISR,
         * and waiting on an event (assuming
         * endless ECC task model).
         *
         * Trace T1_START for start of ISR, task activation
         * (here: meaning first transition from READY to RUNNING),
         * and resumption returning from WaitEvent().
         * Check T1_TRACE_TASK to exclude tasks from tracing.
         *
         * Do not trace anything in all other cases.
         * Not considering semaphores so far.
         */
#       define OS_VTH_SCHEDULE( fromThreadId_, fromThreadReason_, toThreadId_, toThreadReason_, callerCoreId_ ) \
            {                                                                                                   \
                const T1_uint8Least_t fromId = ( fromThreadId_ );                                               \
                const T1_uint8Least_t toId = ( toThreadId_ );                                                   \
                /* Old Tasks */                                                                                 \
                if( (  ( OS_VTHP_TASK_TERMINATION == ( fromThreadReason_ ) )                                    \
                    || ( OS_VTHP_ISR_END          == ( fromThreadReason_ ) )                                    \
                    || ( OS_VTHP_TASK_WAITEVENT   == ( fromThreadReason_ ) ) )                                  \
                    && T1_TRACE_TASK( fromId ) )                                                                \
                {                                                                                               \
                    T1_TraceStopNoSuspPC( (callerCoreId_), fromId );                                            \
                }                                                                                               \
                /* New Tasks */                                                                                 \
                if( (  ( OS_VTHP_TASK_ACTIVATION == ( toThreadReason_ ) )                                       \
                    || ( OS_VTHP_TASK_SETEVENT   == ( toThreadReason_ ) ) )                                     \
                    && T1_TRACE_TASK( toId ) )                                                                  \
                {                                                                                               \
                    T1_TraceStartNoSuspPC( ( callerCoreId_ ), toId );                                           \
                }                                                                                               \
                /* CAT2 ISR Start */                                                                            \
                else if( ( OS_VTHP_ISR_START == ( toThreadReason_ ) ) && T1_TRACE_TASK( toId ) )                \
                {                                                                                               \
                    T1_TraceStartNoActNoSuspPC( ( callerCoreId_ ), toId );                                      \
                }                                                                                               \
            }
#   endif /* defined T1_WAIT_RESUME */
/*-----------------------------------------------------------*/

#   if defined T1_WAIT_RESUME
        /* Trace nothing if WaitEvent is called and one of the
         * events is already set (assuming T1_WAIT_RESUME is defined).
         */
#       define OS_VTH_WAITEVENT_NOWAIT( taskId_, eventMask_, destCoreId_, callerCoreId_ ) \
            ((void)0);
#   else
        /*
         * Trace T1_STOP_START if WaitEvent is called and one of the
         * events is already set, so that the task remains in the
         * RUNNING state (assuming endless ECC task model).
         * This resets the CET calculation by T1 for this task.
         * Note: Note that, with T1-TARGET-SW prior to V2.5.0.0,
         * for T1_STOP_START only 5 bits are allocated for each
         * of the two task IDs. Therefore the maximum task ID
         * of 31 must not be exceeded.
         */
#       define OS_VTH_WAITEVENT_NOWAIT( taskId_, eventMask_, destCoreId_, callerCoreId_ )      \
            if( T1_TRACE_TASK( taskId_ ) )                                                     \
            {                                                                                  \
                T1_TraceStopStartNoActNoSuspPC( ( callerCoreId_ ), ( taskId_ ), ( taskId_ ) ); \
            }
#   endif /* defined T1_WAIT_RESUME */

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_SCOPE */

#endif /* T1_MICROSAR_H_ */
