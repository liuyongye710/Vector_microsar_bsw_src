/*********************************************************************************//*!
*   \file           T1_scopeInterface.h
*
*   \brief          T1.scope interface declarations and macros
*
*   \par Visibility
*                   External
*
*   \author alexandrebau
*
*   \version 2.5.5.0 r39992
*
*   \copyright GLIWA GmbH embedded systems, Weilheim i.OB. All rights reserved
*************************************************************************************/

#ifndef T1_SCOPE_INTERFACE_H_
#define T1_SCOPE_INTERFACE_H_ (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_baseInterface.h"

#if defined T1_NOF_CORES && ! defined T1_MULTICORE_CLONE && ! defined T1_USE_SCOPE_GLOBALS_PARAM
#   define T1_USE_SCOPE_GLOBALS_PARAM   (1)
#endif /* defined T1_NOF_CORES && ! defined T1_USE_SCOPE_GLOBALS_PARAM */

#if defined T1_USE_SCOPE_GLOBALS_PARAM
#   define T1_SCOPE_GLOBALS_PARAM       T1_scopeGlobals_t *pScopeGlobals,
#   define T1_SCOPE_GLOBALS_ARG         pScopeGlobals,
#   define T1_SCOPE_GLOBALS( coreId_ )  T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ),
#else /* address of T1.scope globals structure is not passed as parameter */
#   define T1_SCOPE_GLOBALS_PARAM
#   define T1_SCOPE_GLOBALS_ARG
#   define T1_SCOPE_GLOBALS( coreId_ )
#endif /* defined T1_USE_SCOPE_GLOBALS_PARAM */

/*----------------------------------------------------------------------------------*/
/*--- macros needed for type definitions -------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/* The following type defines the structure of a single trace-entry  */
/* The array T1_traceBuffer of entries of this type define the trace buffer */
#if defined T1_32BIT_TRACE_TIME
typedef struct
{
    T1_uint16_t         timeLow;    /* 32 bit time field split for alignment */
    T1_uint16_t         timeHigh;
    T1_uint16_t         eventInfo;
}
T1_traceEntry_t;
#else /* !defined T1_32BIT_TRACE_TIME */
typedef T1_uint32_t T1_traceEntry_t;
#endif /* defined T1_32BIT_TRACE_ENTRY */
/*----------------------------------------------------------------------------------*/
/* When using a logic analyzer instead of the trace buffer, the event and the       */
/* info is written to a single cell which is traced. Instead of the target's        */
/* internal time, the logic analyzer's time stamp is used.                          */
typedef T1_uint16_t         T1_traceCell_t;
/*----------------------------------------------------------------------------------*/
typedef T1_uint16Least_t    T1_nofEntries_t;    //!< number of trace buffer entries
/*----------------------------------------------------------------------------------*/
typedef struct
{
    T1_traceEntry_t T1_FARPTR volatile pTraceBufferWr;
    T1_uint8_t         volatile wrapCntr;
    T1_uint8_t                  avgCPULoadSamples_;
    T1_uint8_t                  cpuLoadThreshold_;
    T1_bool_t                   inBgHandler_;
}
T1_traceBufferPos_t; //!< Combined write pointer and wrap counter for "remote" T1.cont
/*----------------------------------------------------------------------------------*/
/*! \brief T1.scope global data for one core. */
typedef struct
{
    /* 0 */
    T1_traceEntry_t T1_FARPTR
#if defined T1_CPU32BIT
                        volatile
#endif /* defined T1_CPU32BIT */
                                    pTraceBufferWr_;
    T1_traceEntry_t const T1_FARPTR pCompare_;              /* Wrap or trigger */
    T1_uint8_t                      compareState_;
    volatile T1_uint8_t             wrapCntr_;
    T1_uint8_t                      scopeState_;            /* See state machine */
    T1_uint8_t                      triggerWrapCntr_;
    /* 16 */
    T1_traceEntry_t const T1_FARPTR pTraceBufferLast_;
    T1_traceEntry_t const T1_FARPTR pTrigger_;              /* Trigger */
    T1_uint16_t                     transmitControlMask_;   /* Messages to transmit */
#if defined T1_CPU32BIT
    T1_bool_t                       syncTimerIsTraceTimer_;
    T1_uint8_t                      unused8_;               /* Force alignment */
    /* 32-bit targets cache trace buffer address in RAM */
    T1_traceEntry_t       T1_FARPTR pTraceBuffer_;          /* Start of buffer */
    /* 32 */
#   if defined T1_NOF_CORES
    volatile T1_traceBufferPos_t   *pContTraceBufferPos_;
#   endif /* T1_NOF_CORES */
#endif /* defined T1_CPU32BIT */
}
T1_scopeGlobals_t;
/*----------------------------------------------------------------------------------*/
typedef struct
{
    T1_tickUint_t             (*pNoSuspTime)( T1_SCOPE_GLOBALS_PARAM T1_uint16Least_t eventInfo, T1_tickUint_t time );
    T1_tickUint_t             (*pSyncNoSusp)( T1_SCOPE_GLOBALS_PARAM T1_uint16Least_t eventInfo, T1_uint32_t baseTime );
}
T1_traceIndirect_t;
/*----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/*--- macros, inline functions and forward declarations ----------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_SCOPE_PLUGIN_ID          (1u)

#define T1_EMPTY                    0x00u   /* empty (no entry, initialized) */
#define T1_START                    0x01u   /* start of a task or ISR */
#define T1_STOP                     0x02u   /* end of a task or ISR */
#define T1_START_STOP               0x03u   /* start and end of a short task or ISR */
#define T1_STOP_START               0x04u   /* end of one task and start of a 2nd */
#define T1_STOPWATCH_START          0x05u   //!< start stopwatch
#define T1_STOPWATCH_STOP           0x06u   //!< stop stopwatch
#define T1_STOPWATCH_STOP_START     0x07u   //!< stop stopwatch n, start n
#define T1_STOPWATCH_STOP_START_INC 0x08u   //!< stop stopwatch n-1, start n
#define T1_FLEX_UEC                 0x09u   /* T1.flex code event */
#define T1_FLEX_UED                 0x0Au   /* T1.flex data event */
#define T1_FLEX_USERDATA_START      0x0Bu   /* T1.flex data event with data */
#define T1_ACTIVATION               0x0Cu   /* successful task activation */
#if defined T1_DISABLE_T1_CONT || defined T1_WAIT_RESUME
#   define T1_WAIT                  0x0Du   /* task called WaitEvent */
#   define T1_RESUME                0x0Eu   /* task returned from WaitEvent */
#endif /* defined T1_DISABLE_T1_CONT || defined T1_WAIT_RESUME */
#define T1_DISCONTINUITY            0x0Fu   /* resume after stop trace */
#define T1_ACTIVATION_FAILED        0x10u   //!< failed task activation (E_OS_LIMIT)
#define T1_RELEASE                  0x11u   /* task had a waiting event set */
#define T1_SYNCDATA_START           0x12u   /* synchronisation timestamp data */
#define T1_USERDATA_START           0x13u   /* user data */
#define T1_USERDATA_MID             0x14u   /* user data with no timestamp */
#define T1_USERDATA_STOP            0x15u   /* user data */
#define T1_RUNNABLE_START           0x16u   /* start of a runnable */
#define T1_RUNNABLE_STOP            0x17u   /* end of a runnable */
#define T1_TRIGGER_SYNC             0x18u   /* trigger */
#define T1_STOPWATCH_STOP_GET_START 0x19u   /* stop stopwatch plus GET user data */
#define T1_START_IPT_START          0x1Au   /* start task plus IPT user data */
#define T1_STOP_START_IPT_START     0x1Du   /* start task plus IPT and stop task user data */
#if T1_STOP_START_IPT_START - T1_START_IPT_START != T1_STOP_START - T1_START
#   error Invalid T1_STOP_START_IPT_START identifier
#endif /* T1_STOP_START_IPT_START - T1_START_IPT_START != T1_STOP_START - T1_START */

#if defined T1_ENABLE && !defined T1_DISABLE_T1_SCOPE

/*!
 * Combine event ID and info field into a single 16-bit value.
 * \param[in] event_ the event ID
 * \param[in] info_  additional info field, for example task/stopwatch ID
 * \returns          the combined result
 */
/* polyspace<MISRA-C3:10.8:Not a defect:Justified> Performance tuning, T1_uintxxLeast_t is not wider on all architectures. */
#   define T1_COMBINE_EVENT_INFO( event_, info_ )                                   \
    ( (((T1_uint16Least_t)(event_) << 10) & 0xFC00u) | ((T1_uint16Least_t)(info_) & 0x03FFu) )

#   define T1_TRACEDATA_UINT8           0x0u
#   define T1_TRACEDATA_SINT8           0x1u
#   define T1_TRACEDATA_UINT16          0x2u
#   define T1_TRACEDATA_SINT16          0x3u
#   define T1_TRACEDATA_UINT32          0x4u
#   define T1_TRACEDATA_SINT32          0x5u
#   define T1_TRACEDATA_UINT64          0x6u
#   define T1_TRACEDATA_SINT64          0x7u
#   define T1_TRACEDATA_FLOAT           0x8u
#   define T1_TRACEDATA_ADDRESS         0x9u
#   if defined T1_32BIT_TRACE_TIME
#       define T1_TRACEDATA_STR_REST0   0x200u
#       define T1_TRACEDATA_STR_REST1   0x201u
#       define T1_TRACEDATA_STR_REST2   0x202u
#       define T1_TRACEDATA_STR_REST3   0x203u
#       define T1_TRACEDATA_STR_REST4   0x204u
#       define T1_TRACEDATA_BIN_REST0   0x205u
#       define T1_TRACEDATA_BIN_REST1   0x206u
#       define T1_TRACEDATA_BIN_REST2   0x207u
#       define T1_TRACEDATA_BIN_REST3   0x208u
#       define T1_TRACEDATA_BIN_REST4   0x209u
#   else /* 16 bit trace time */
#       define T1_TRACEDATA_STR_REST0   0xAu
#       define T1_TRACEDATA_STR_REST1   0xBu
#       define T1_TRACEDATA_STR_REST2   0xCu
#       define T1_TRACEDATA_BIN_REST0   0xDu
#       define T1_TRACEDATA_BIN_REST1   0xEu
#       define T1_TRACEDATA_BIN_REST2   0xFu
#   endif /* defined T1_32BIT_TRACE_TIME */

#    if defined T1_INTERRUPTS_ARE_ENABLED
#       define T1_TraceEvent_( pScopeGlobals_, eventInfo_ )                         \
    do                                                                              \
    {                                                                               \
        if( T1_INTERRUPTS_ARE_ENABLED( ) )                                          \
        {                                                                           \
            T1_TraceEventFast_( pScopeGlobals_, eventInfo_ );                       \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            T1_TraceEventNoSusp_( pScopeGlobals_, eventInfo_ );                     \
        }                                                                           \
    }                                                                               \
    while( 0 )
#       define T1_TraceSync_( pScopeGlobals_, eventInfo_, baseTime_ )               \
    do                                                                              \
    {                                                                               \
        if( T1_INTERRUPTS_ARE_ENABLED( ) )                                          \
        {                                                                           \
            T1_TraceSyncFast_( pScopeGlobals_, eventInfo_, baseTime_ );             \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            T1_TraceSyncNoSusp_( pScopeGlobals_, eventInfo_, baseTime_ );           \
        }                                                                           \
    }                                                                               \
    while( 0 )
#   else /* ! defined T1_INTERRUPTS_ARE_ENABLED */
#       define T1_TraceEvent_( pScopeGlobals_, eventInfo_ )                         \
    T1_TraceEventFast_( pScopeGlobals_, eventInfo_ )
#       define T1_TraceSync_( pScopeGlobals_, eventInfo_, baseTime_ )               \
    T1_TraceSyncFast_( pScopeGlobals_, eventInfo_, baseTime_ )
#   endif /* defined T1_INTERRUPTS_ARE_ENABLED */
#   define T1_TraceEventFast_( pScopeGlobals_, eventInfo_ )                         \
    do                                                                              \
    {                                                                               \
        T1_DISABLE_INTERRUPTS( );                                                   \
        T1_TraceEventNoSusp_( pScopeGlobals_, eventInfo_ );                         \
        T1_ENABLE_INTERRUPTS( );                                                    \
    }                                                                               \
    while( 0 )
#   define T1_TraceSyncFast_( pScopeGlobals_, eventInfo_, baseTime_ )               \
    do                                                                              \
    {                                                                               \
        T1_DISABLE_INTERRUPTS( );                                                   \
        T1_TraceSyncNoSusp_( pScopeGlobals_, eventInfo_, baseTime_ );               \
        T1_ENABLE_INTERRUPTS( );                                                    \
    }                                                                               \
    while( 0 )
#   if defined T1_USE_SCOPE_GLOBALS_PARAM
#       define T1_TraceEventNoSusp_( pScopeGlobals_, eventInfo_ )                   \
    T1_TraceEventNoSusp__( pScopeGlobals_, eventInfo_ )
#       define T1_TraceEventNoSuspTime_( pScopeGlobals_, time_, eventInfo_ )        \
    T1_TraceEventNoSuspTime__( pScopeGlobals_, eventInfo_, time_ )
#       define T1_TraceSyncNoSusp_( pScopeGlobals_, eventInfo_, baseTime_ )         \
    T1_TraceSyncNoSusp__( pScopeGlobals_, eventInfo_, baseTime_ )
#   else /* ! defined T1_USE_SCOPE_GLOBALS_PARAM */
#       define T1_TraceEventNoSusp_( pScopeGlobals_, eventInfo_ )                   \
    T1_TraceEventNoSusp__( eventInfo_ )
#       define T1_TraceEventNoSuspTime_( pScopeGlobals_, time_, eventInfo_ )        \
    T1_TraceEventNoSuspTime__( eventInfo_, time_ )
#       define T1_TraceSyncNoSusp_( pScopeGlobals_, eventInfo_, baseTime_ )         \
    T1_TraceSyncNoSusp__( eventInfo_, baseTime_ )
#   endif /* defined T1_USE_SCOPE_GLOBALS_PARAM */

#   if defined T1_INTERRUPTS_ARE_ENABLED
#       define T1_TraceSyncRC_( pScopeGlobals_, eventInfo_, baseTime_ )             \
    do                                                                              \
    {                                                                               \
        if( T1_INTERRUPTS_ARE_ENABLED( ) )                                          \
        {                                                                           \
            T1_TraceSyncFastRC_( pScopeGlobals_, eventInfo_, baseTime_ );           \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            T1_TraceSyncNoSuspRC_( pScopeGlobals_, eventInfo_, baseTime_ );         \
        }                                                                           \
    }                                                                               \
    while( 0 )
#   else /* ! defined T1_INTERRUPTS_ARE_ENABLED */
#       define T1_TraceSyncRC_( pScopeGlobals_, eventInfo_, baseTime_ )             \
    T1_TraceSyncFastRC_( pScopeGlobals_, eventInfo_, baseTime_ )
#   endif /* defined T1_INTERRUPTS_ARE_ENABLED */
#   define T1_TraceSyncFastRC_( pScopeGlobals_, eventInfo_, baseTime_ )             \
    do                                                                              \
    {                                                                               \
        T1_DISABLE_INTERRUPTS( );                                                   \
        T1_TraceSyncNoSuspRC_( pScopeGlobals_, eventInfo_, baseTime_ );             \
        T1_ENABLE_INTERRUPTS( );                                                    \
    }                                                                               \
    while( 0 )
#   if defined T1_USE_SCOPE_GLOBALS_PARAM
#       define T1_TraceEventNoSuspTimeRC_( pScopeGlobals_, time_, eventInfo_ )      \
    T1_TraceEventNoSuspTimeRC__( pScopeGlobals_, eventInfo_, time_ )
#       define T1_TraceSyncNoSuspRC_( pScopeGlobals_, eventInfo_, baseTime_ )       \
    T1_TraceSyncNoSuspRC__( pScopeGlobals_, eventInfo_, baseTime_ )
#   else /* ! defined T1_USE_SCOPE_GLOBALS_PARAM */
#       define T1_TraceEventNoSuspTimeRC_( pScopeGlobals_, time_, eventInfo_ )      \
    T1_TraceEventNoSuspTimeRC__( eventInfo_, time_ )
#       define T1_TraceSyncNoSuspRC_( pScopeGlobals_, eventInfo_, baseTime_ )       \
    T1_TraceSyncNoSuspRC__( eventInfo_, baseTime_ )
#   endif /* defined T1_USE_SCOPE_GLOBALS_PARAM */

#   define T1_TraceEventRC_( pScopeGlobals_, eventInfo_ )                           \
    T1_TraceEvent_( pScopeGlobals_, eventInfo_ )
#   define T1_TraceEventFastRC_( pScopeGlobals_, eventInfo_ )                       \
    T1_TraceEventFast_( pScopeGlobals_, eventInfo_ )
#   define T1_TraceEventNoSuspRC_( pScopeGlobals_, eventInfo_ )                     \
    T1_TraceEventNoSusp_( pScopeGlobals_, eventInfo_ )

#   define T1_TRACEDATA( kind_, info_, pData_, len_ )                               \
    ( T1_TraceData##kind_( T1_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) )                \
                       T1_COMBINE_EVENT_INFO( T1_USERDATA_START, info_ ),           \
                       (pData_),                                                    \
                       (len_) ) )
#   define T1_TRACEDATA_PC( kind_, coreId_, info_, pData_, len_ )                   \
    ( T1_TraceData##kind_( T1_SCOPE_GLOBALS( coreId_ )                              \
                       T1_COMBINE_EVENT_INFO( T1_USERDATA_START, info_ ),           \
                       (pData_),                                                    \
                       (len_) ) )

#   define T1_OH_SW                     (0x2FFu)
#   define T1_CONT_UPDATE_OH            (0x3FFu)

#   if defined T1_TRACE_ACT_EVENT_AND_CROSS_CORE_ACT
#       define T1_NEEDS_IPT( coreId_, taskId_ )     \
        ( (0u != T1_taskAct[taskId_]) && (0u != ((~(coreId_) ^ T1_taskAct[taskId_]) & 0xFuL)) )
#       define T1_ACT_TIME( ta_, te_, offset_ )     do { te_; (ta_) = (T1_GET_SYNC_TIME( ) << 4) - (offset_); } while( 0 )
#       define T1_ACT_TIME_NOSUSP( coreId_, te_ )   \
    ( T1_syncTimerIsTraceTimerPC[coreId_] ? ( (te_) << 4 ) : ( (te_), T1_GET_SYNC_TIME( ) << 4 ) )
#   else /* Just read sync timer */
#       define T1_NEEDS_IPT( coreId_, taskId_ )     ( 0u != T1_taskAct[taskId_] )
#       define T1_ACT_TIME( ta_, te_, offset_ )     do { (ta_) = (T1_GET_SYNC_TIME( ) << 4) - (offset_); } while( 0 )
#       define T1_ACT_TIME_NOSUSP( coreId_, te_ )   (T1_GET_SYNC_TIME( ) << 4)
#   endif /* T1_TRACE_ACT_EVENT_AND_CROSS_CORE_ACT */

#   if defined T1_CROSS_CORE_ACT
#       define T1_TRACE_START_PC( vrnt_, coreId_, taskId_ )                         \
        do                                                                          \
        {                                                                           \
            if( T1_NEEDS_IPT( (coreId_), (taskId_) ) )                              \
            {                                                                       \
                T1_CAT( T1_TraceSync##vrnt_, _ )                                    \
                    ( T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ),                       \
                      T1_COMBINE_EVENT_INFO( T1_START_IPT_START,                    \
                      (taskId_) ), T1_taskAct[taskId_] );                           \
            }                                                                       \
            else                                                                    \
            {                                                                       \
                T1_TRACE_START_NOACT_PC( vrnt_, (coreId_), (taskId_) );             \
            }                                                                       \
        }                                                                           \
        while( 0 )
#       define T1_TRACE_START_NOACT_PC( vrnt_, coreId_, taskId_ )                   \
        T1_CAT( T1_TraceEvent##vrnt_, _ )( T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ), T1_COMBINE_EVENT_INFO( T1_START, (taskId_) ) )
#       define T1_TRACE_STOP_START_PC( vrnt_, coreId_, startTaskId_ )               \
        do                                                                          \
        {                                                                           \
            if( T1_NEEDS_IPT( (coreId_), (startTaskId_) ) )                         \
            {                                                                       \
                T1_CAT( T1_TraceSync##vrnt_, _ )                                    \
                    ( T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ),                       \
                      T1_COMBINE_EVENT_INFO( T1_STOP_START_IPT_START, (startTaskId_) ), \
                      T1_taskAct[startTaskId_] );                                   \
            }                                                                       \
            else                                                                    \
            {                                                                       \
                T1_TRACE_STOP_START_NOACT_PC( vrnt_, (coreId_), (startTaskId_) );   \
            }                                                                       \
        }                                                                           \
        while( 0 )
#       define T1_TRACE_STOP_START_NOACT_PC( vrnt_, coreId_, startTaskId_ )         \
        T1_CAT( T1_TraceEvent##vrnt_, _ )( T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ), T1_COMBINE_EVENT_INFO( T1_STOP_START, (startTaskId_) ) )
#       define T1_TRACE_ACT_NOSUSP_PC( coreId_, taskId_ )                           \
        ( T1_taskAct[taskId_] = T1_ACT_TIME_NOSUSP( (coreId_), T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ), T1_COMBINE_EVENT_INFO( T1_ACTIVATION, (taskId_) ) ) ) - (coreId_) - 1 )
#       define T1_TRACE_ACT_PC( coreId_, taskId_ )                                  \
        T1_ACT_TIME( T1_taskAct[taskId_], T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ), T1_COMBINE_EVENT_INFO( T1_ACTIVATION, (taskId_) ) ), (coreId_) + 1 )
#   else /* not logging cross-core activations */
#       define T1_TRACE_START_PC( vrnt_, coreId_, taskId_ )                         \
        T1_CAT( T1_TraceEvent##vrnt_, _ )( T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ), T1_COMBINE_EVENT_INFO( T1_START, (taskId_) ) )
#       define T1_TRACE_STOP_START_PC( vrnt_, coreId_, startTaskId_ )               \
        T1_CAT( T1_TraceEvent##vrnt_, _ )( T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ), T1_COMBINE_EVENT_INFO( T1_STOP_START, (startTaskId_) ) )
#       define T1_TRACE_START_NOACT_PC( vrnt_, coreId_, taskId_ )                   \
        T1_TRACE_START_PC( vrnt_, (coreId_), (taskId_) )
#       define T1_TRACE_STOP_START_NOACT_PC( vrnt_, coreId_, startTaskId_ )         \
        T1_TRACE_STOP_START_PC( vrnt_, (coreId_), (startTaskId_) )
#       define T1_TRACE_ACT_NOSUSP_PC( coreId_, taskId_ )                           \
        T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ), T1_COMBINE_EVENT_INFO( T1_ACTIVATION, (taskId_) ) )
#       define T1_TRACE_ACT_PC( coreId_, taskId_ )                                  \
        T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ), T1_COMBINE_EVENT_INFO( T1_ACTIVATION, (taskId_) ) )
#   endif /* defined T1_CROSS_CORE_ACT */

#   if defined T1_NOF_CORES
#       define T1_TRACE_START_ACT_PC( vrnt_, coreId_, taskId_, actCoreId_, actTime_ ) \
    T1_CAT( T1_TraceSync##vrnt_, _ )( T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ), T1_COMBINE_EVENT_INFO( T1_START_IPT_START, (taskId_) ), ((actTime_) << 4) - (actCoreId_) - 1 )
#       define T1_TRACE_STOP_START_ACT_PC( vrnt_, coreId_, startTaskId_, actCoreId_, actTime_ ) \
    T1_CAT( T1_TraceSync##vrnt_, _ )( T1_CORE_ID_TO_SCOPE_GLOBALS( coreId_ ), T1_COMBINE_EVENT_INFO( T1_STOP_START_IPT_START, (startTaskId_) ), ((actTime_) << 4) - (actCoreId_) - 1 )
#   else /* ! defined T1_NOF_CORES */
#       define T1_TRACE_START_ACT_PC( vrnt_, coreId_, taskId_, actCoreId_, actTime_ ) \
    T1_TRACE_START_PC( vrnt_, coreId_, taskId_ )
#       define T1_TRACE_STOP_START_ACT_PC( vrnt_, coreId_, startTaskId_, actCoreId_, actTime_ ) \
    T1_TRACE_STOP_START_PC( vrnt_, coreId_, startTaskId_ )
#   endif /* defined T1_NOF_CORES */

/*! \brief T1.scope entry in plugin table. */
#   define T1_scopePlugin       (&T1_scopePluginStruct)
#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_DeclarePlugin( T1_scopePluginStruct );
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   if defined T1_NOF_CORES && defined T1_CROSS_CORE_ACT
#       if 1 < T1_NOF_CORES
#           define T1_START_SEC_NO_INIT_32
#           include "T1_MemMap.h"
T1_EXTERN T1_uint32_t T1_SEC_NO_INIT_32 T1_taskAct[];
#           define T1_STOP_SEC_NO_INIT_32
#           include "T1_MemMap.h"
#       endif /* 1 < T1_NOF_CORES */
#   endif /* defined T1_NOF_CORES && defined T1_CROSS_CORE_ACT */

#   define T1_START_SEC_CODE
#   include "T1_MemMap.h"
#   if defined T1_NOF_CORES
#       if 1 < T1_NOF_CORES && defined T1_CROSS_CORE_ACT
T1_EXTERN void        T1_CODE T1_InitTaskAct( void );
#       else /* not logging cross-core activations */
#           define T1_InitTaskAct( )    (void)0
#       endif /* 1 < T1_NOF_CORES && defined T1_CROSS_CORE_ACT */
#   else /* single core */
#       define T1_InitTaskAct( )        (void)0
#   endif /* defined T1_NOF_CORES */
#   if defined T1_NOF_CORES
T1_EXTERN void        T1_CODE T1_InitTraceBufferPC( T1_uint8Least_t coreId );
/*!
 * Halt tracing for download and analysis by the T1-HOST-SW.
 * See \ref PC and \ref INTRPT.
 * \param[in] afterXevents halt tracing only after this number of further events
 * \returns                #T1_NOFUNC if the trigger has already been set
 */
T1_EXTERN T1_status_t T1_CODE T1_SetStopTriggerPC( T1_uint8Least_t coreId, T1_nofEntries_t afterXevents );
/*!
 * Halt tracing for download and analysis by the T1-HOST-SW.
 * See \ref PC and \ref INTRPT.
 * \param[in] afterXevents halt tracing only after this number of further events
 * \returns                #T1_NOFUNC if the trigger has already been set
 */
T1_EXTERN T1_status_t T1_CODE T1_SetStopTriggerNoSuspPC( T1_uint8Least_t coreId, T1_nofEntries_t afterXevents );
/*!
 * Halt tracing for download and analysis by the T1-HOST-SW.
 * See \ref PC and \ref INTRPT.
 * \param[in] afterXevents halt tracing only after this number of further events
 * \returns                #T1_NOFUNC if the trigger has already been set
 */
#       define T1_SetStopTrigger( afterXevents_ ) T1_SetStopTriggerPC( T1_GetCoreIdOffset( ), afterXevents_ )
/*!
 * Halt tracing for download and analysis by the T1-HOST-SW.
 * See \ref PC and \ref INTRPT.
 * \param[in] afterXevents halt tracing only after this number of further events
 * \returns                #T1_NOFUNC if the trigger has already been set
 */
#       define T1_SetStopTriggerNoSusp( afterXevents_ ) T1_SetStopTriggerNoSuspPC( T1_GetCoreIdOffset( ), afterXevents_ )
#       define T1_InitTraceBuffer( ) T1_InitTraceBufferPC( T1_GetCoreIdOffset( ) )
#   else /* single core */
T1_EXTERN void        T1_CODE T1_InitTraceBuffer( void );
/*!
 * Halt tracing for download and analysis by the T1-HOST-SW.
 * See \ref PC and \ref INTRPT.
 * \param[in] afterXevents halt tracing only after this number of further events
 * \returns                #T1_NOFUNC if the trigger has already been set
 */
T1_EXTERN T1_status_t T1_CODE T1_SetStopTrigger( T1_nofEntries_t afterXevents );
/*!
 * Halt tracing for download and analysis by the T1-HOST-SW.
 * See \ref PC and \ref INTRPT.
 * \param[in] afterXevents halt tracing only after this number of further events
 * \returns                #T1_NOFUNC if the trigger has already been set
 */
T1_EXTERN T1_status_t T1_CODE T1_SetStopTriggerNoSusp( T1_nofEntries_t afterXevents );
/*!
 * Halt tracing for download and analysis by the T1-HOST-SW.
 * See \ref PC and \ref INTRPT.
 * \param[in] afterXevents halt tracing only after this number of further events
 * \returns                #T1_NOFUNC if the trigger has already been set
 */
#       define T1_SetStopTriggerPC( coreId_, afterXevents_ ) T1_SetStopTrigger( afterXevents_ )
/*!
 * Halt tracing for download and analysis by the T1-HOST-SW.
 * See \ref PC and \ref INTRPT.
 * \param[in] afterXevents halt tracing only after this number of further events
 * \returns                #T1_NOFUNC if the trigger has already been set
 */
#       define T1_SetStopTriggerNoSuspPC( coreId_, afterXevents_ ) T1_SetStopTriggerNoSusp( afterXevents_ )
#       define T1_InitTraceBufferPC( coreId_ ) T1_InitTraceBuffer( )
#   endif /* T1_NOF_CORES */
/*!
 * Halt tracing for download and analysis by the T1-HOST-SW.
 * See \ref PC and \ref INTRPT.
 * \param afterXevents Halt tracing only after this number of further events.
 */
#   define T1_SetStopTriggerFast( afterXevents_ ) T1_SetStopTrigger( afterXevents_ )
/*!
 * Halt tracing for download and analysis by the T1-HOST-SW.
 * See \ref PC and \ref INTRPT.
 * \param afterXevents Halt tracing only after this number of further events.
 */
#   define T1_SetStopTriggerFastPC( coreId_, afterXevents_ ) T1_SetStopTriggerPC( coreId_, afterXevents_ )
T1_EXTERN void        T1_CODE T1_TraceData_(        T1_SCOPE_GLOBALS_PARAM
                                                    T1_uint16Least_t    eventInfo,
                                                    T1_uint8_t const   *pData,
                                                    T1_uint8Least_t     length  );
T1_EXTERN void        T1_CODE T1_TraceDataNoSusp_(  T1_SCOPE_GLOBALS_PARAM
                                                    T1_uint16Least_t    eventInfo,
                                                    T1_uint8_t const   *pData,
                                                    T1_uint8Least_t     length  );
#   define T1_TraceDataRC_          T1_TraceData_
#   define T1_TraceDataNoSuspRC_    T1_TraceDataNoSusp_
T1_EXTERN void        T1_CODE T1_ScopeOverheadSequence( T1_bool_t isNoSusp );
T1_EXTERN void        T1_CODE T1_ScopeOverheadSequencePC( T1_uint8Least_t coreId, T1_bool_t isNoSusp );
/*
 * The following functions, by default, map to their equivalent without 'UM'. They
 * are called from T1_Handler and T1_ContBgHandler, which (can) run in user mode and
 * they can be overridden in the event that calling T1_TraceEvent in user mode is not
 * permitted. We know of one case where the trace timer cannot be accessed in user
 * mode, for example. In this case, these functions can be re-implemented using
 * CallTrustedFunction, or some equivalent, to call T1_TraceEvent in supervisor mode.
 * This should only be done with support from GLIWA.
 */
T1_EXTERN void        T1_CODE T1_TraceEventUM( T1_uint16Least_t eventInfo );
T1_EXTERN T1_tickUint_t T1_CODE T1_TraceEventNoSuspUM( T1_uint16Least_t eventInfo );
T1_EXTERN void        T1_CODE T1_TraceEventUMPC( T1_uint8Least_t coreId, T1_uint16Least_t eventInfo );
T1_EXTERN T1_tickUint_t T1_CODE T1_TraceEventNoSuspUMPC( T1_uint8Least_t coreId, T1_uint16Least_t eventInfo );
#   define T1_STOP_SEC_CODE
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_8
#   include "T1_MemMap.h"
T1_EXTERN const T1_uint8_t                      T1_SEC_CONST_8 T1_syncTimerWidthBits;
T1_EXTERN const T1_bool_t                       T1_SEC_CONST_8 T1_syncTimerIsTraceTimerPC[];
#   define T1_STOP_SEC_CONST_8
#   include "T1_MemMap.h"
#   define T1_START_SEC_CONST_16
#   include "T1_MemMap.h"
T1_EXTERN const T1_uint16_t                     T1_SEC_CONST_16 T1_bufferSizePC[];
T1_EXTERN const T1_uint16_t                     T1_SEC_CONST_16 T1_bufferSize;
#   define T1_STOP_SEC_CONST_16
#   include "T1_MemMap.h"
#   if defined T1_NOF_CORES
#       define T1_BUFFER_SIZE_PC( coreId_ ) ( T1_bufferSizePC[(coreId_)] )
#       define T1_BUFFER_SIZE( )            ( T1_bufferSizePC[T1_GetCoreIdOffset( )] )
#   else /* single core */
#       define T1_BUFFER_SIZE_PC( coreId_ ) ( T1_bufferSize )
#       define T1_BUFFER_SIZE( )            ( T1_bufferSize )
#   endif /* defined T1_NOF_CORES */
#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FARPTR const       T1_SEC_CONST_32 T1_traceBufferPC[];
T1_EXTERN const T1_traceIndirect_t              T1_SEC_CONST_32 T1_traceIndirect;
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32_TRACEBUFFER
#   include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR                T1_SEC_NO_INIT_32_TRACEBUFFER T1_traceBuffer[];
#   define T1_STOP_SEC_NO_INIT_32_TRACEBUFFER
#   include "T1_MemMap.h"

#   define T1_START_SEC_CODE_FAST
#   include "T1_MemMap.h"
#   if defined T1_ENABLE_WRITE_TIME
T1_EXTERN T1_tickUint_t T1_NOINLINE T1_CODE_FAST T1_WriteTraceTime(
#       if defined T1_32BIT_TRACE_TIME
                                                                    T1_traceEntry_t
#       else
                                                                    T1_uint16_t
#       endif /* defined T1_32BIT_TRACE_TIME */
                                                                        *pTimeStamp );
#   endif /* defined T1_ENABLE_WRITE_TIME */
T1_EXTERN T1_tickUint_t T1_NOINLINE T1_CODE_FAST T1_TraceEventNoSusp__( T1_SCOPE_GLOBALS_PARAM T1_uint16Least_t eventInfo );
T1_EXTERN T1_tickUint_t T1_NOINLINE T1_CODE_FAST T1_TraceEventNoSuspTime__(  T1_SCOPE_GLOBALS_PARAM T1_uint16Least_t eventInfo, T1_tickUint_t now );
T1_EXTERN T1_tickUint_t T1_NOINLINE T1_CODE_FAST T1_TraceEventNoSuspTimeRC__( T1_SCOPE_GLOBALS_PARAM T1_uint16Least_t eventInfo, T1_tickUint_t now );
T1_EXTERN T1_tickUint_t T1_CODE_FAST T1_TraceSyncNoSusp__( T1_SCOPE_GLOBALS_PARAM
                                                    T1_uint16Least_t    eventInfo,
                                                    T1_uint32_t         baseTime    );
T1_EXTERN T1_tickUint_t T1_CODE_FAST T1_TraceSyncNoSuspRC__( T1_SCOPE_GLOBALS_PARAM
                                                    T1_uint16Least_t    eventInfo,
                                                    T1_uint32_t         baseTime    );
#   define T1_STOP_SEC_CODE_FAST
#   include "T1_MemMap.h"

/*!
 * \def T1_TraceActivation
 * Call at task activation. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of activated task
 * \def T1_TraceActivationPC
 * Call at task activation. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of activated task
 * \def T1_TraceActivationFast
 * Call at task activation. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of activated task
 * \def T1_TraceActivationFastPC
 * Call at task activation. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of activated task
 * \def T1_TraceActivationNoSusp
 * Call at task activation. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of activated task
 * \def T1_TraceActivationNoSuspPC
 * Call at task activation. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of activated task
 * \def T1_TraceStart
 * Call at task/ISR start. See also T1_TraceStartNoAct(), especially for ISRs. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of starting task
 * \def T1_TraceStartPC
 * Call at task/ISR start. See also T1_TraceStartNoAct(), especially for ISRs. See
 * \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of starting task
 * \def T1_TraceStartFast
 * Call at task/ISR start. See also T1_TraceStartNoAct(), especially for ISRs. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of starting task
 * \def T1_TraceStartFastPC
 * Call at task/ISR start. See also T1_TraceStartNoAct(), especially for ISRs. See
 * \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of starting task
 * \def T1_TraceStartNoSusp
 * Call at task/ISR start. See also T1_TraceStartNoAct(), especially for ISRs. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of starting task
 * \def T1_TraceStartNoSuspPC
 * Call at task/ISR start. See also T1_TraceStartNoAct(), especially for ISRs. See
 * \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of starting task
 * \def T1_TraceStartNoAct
 * Call at task/ISR start for which there is no activation event. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of starting task
 * \def T1_TraceStartNoActPC
 * Call at task/ISR start for which there is no activation event. See \ref PC and \ref
 * INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of starting task
 * \def T1_TraceStartNoActFast
 * Call at task/ISR start for which there is no activation event. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of starting task
 * \def T1_TraceStartNoActFastPC
 * Call at task/ISR start for which there is no activation event. See \ref PC and \ref
 * INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of starting task
 * \def T1_TraceStartNoActNoSusp
 * Call at task/ISR start for which there is no activation event. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of starting task
 * \def T1_TraceStartNoActNoSuspPC
 * Call at task/ISR start for which there is no activation event. See \ref PC and \ref
 * INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of starting task
 * \def T1_TraceStop
 * Call at task/ISR stop. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of stopping task
 * \def T1_TraceStopPC
 * Call at task/ISR stop. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of stopping task
 * \def T1_TraceStopFast
 * Call at task/ISR stop. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of stopping task
 * \def T1_TraceStopFastPC
 * Call at task/ISR stop. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of stopping task
 * \def T1_TraceStopNoSusp
 * Call at task/ISR stop. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of stopping task
 * \def T1_TraceStopNoSuspPC
 * Call at task/ISR stop. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of stopping task
 * \def T1_TraceStopStart
 * Call at the context switch from a stopping task to a newly activated starting task.
 * It is important to use this in preference to having two separate events, where possible.
 * See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 * \def T1_TraceStopStartPC
 * Call at the context switch from a stopping task to a newly activated starting task.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * It is important to use this in preference to having two separate events, where possible.
 * See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 * \def T1_TraceStopStartFast
 * Call at the context switch from a stopping task to a newly activated starting task.
 * It is important to use this in preference to having two separate events, where possible.
 * See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 * \def T1_TraceStopStartFastPC
 * Call at the context switch from a stopping task to a newly activated starting task.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * It is important to use this in preference to having two separate events, where possible.
 * See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 * \def T1_TraceStopStartNoSusp
 * Call at the context switch from a stopping task to a newly activated starting task.
 * It is important to use this in preference to having two separate events, where possible.
 * See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 * \def T1_TraceStopStartNoSuspPC
 * Call at the context switch from a stopping task to a newly activated starting task.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * It is important to use this in preference to having two separate events, where possible.
 * See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 * \def T1_TraceStopStartNoAct
 * Call at the context switch from a stopping task to a newly starting task for which
 * there is no activation event. It is important to use this in preference to having
 * two separate events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \def T1_TraceStopStartNoActPC
 * Call at the context switch from a stopping task to a newly starting task for which
 * \param[in] coreId_ the T1 logical ID of the calling core
 * there is no activation event. It is important to use this in preference to having
 * two separate events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \def T1_TraceStopStartNoActFast
 * Call at the context switch from a stopping task to a newly starting task for which
 * there is no activation event. It is important to use this in preference to having
 * two separate events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \def T1_TraceStopStartNoActFastPC
 * Call at the context switch from a stopping task to a newly starting task for which
 * \param[in] coreId_ the T1 logical ID of the calling core
 * there is no activation event. It is important to use this in preference to having
 * two separate events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \def T1_TraceStopStartNoActNoSusp
 * Call at the context switch from a stopping task to a newly starting task for which
 * there is no activation event. It is important to use this in preference to having
 * two separate events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \def T1_TraceStopStartNoActNoSuspPC
 * Call at the context switch from a stopping task to a newly starting task for which
 * \param[in] coreId_ the T1 logical ID of the calling core
 * there is no activation event. It is important to use this in preference to having
 * two separate events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \def T1_TraceRelease
 * Call when a WAITING task becomes READY, in SetEvent. See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of released task
 * \def T1_TraceReleasePC
 * Call when a WAITING task becomes READY, in SetEvent. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_     T1.scope task ID of released task
 * \def T1_TraceReleaseFast
 * Call when a WAITING task becomes READY, in SetEvent. See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of released task
 * \def T1_TraceReleaseFastPC
 * Call when a WAITING task becomes READY, in SetEvent. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_     T1.scope task ID of released task
 * \def T1_TraceReleaseNoSusp
 * Call when a WAITING task becomes READY, in SetEvent. See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of released task
 * \def T1_TraceReleaseNoSuspPC
 * Call when a WAITING task becomes READY, in SetEvent. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_     T1.scope task ID of released task
 * \def T1_TraceWait
 * Call when a RUNNING task becomes WAITING, on entry to WaitEvent.
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 * \def T1_TraceWaitPC
 * Call when a RUNNING task becomes WAITING, on entry to WaitEvent.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 * \def T1_TraceWaitFast
 * Call when a RUNNING task becomes WAITING, on entry to WaitEvent.
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 * \def T1_TraceWaitFastPC
 * Call when a RUNNING task becomes WAITING, on entry to WaitEvent.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 * \def T1_TraceWaitNoSusp
 * Call when a RUNNING task becomes WAITING, on entry to WaitEvent.
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 * \def T1_TraceWaitNoSuspPC
 * Call when a RUNNING task becomes WAITING, on entry to WaitEvent.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 * \def T1_TraceResume
 * Call on exit from WaitEvent. See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 * \def T1_TraceResumePC
 * Call on exit from WaitEvent. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_     T1.scope task ID of waiting task
 * \def T1_TraceResumeFast
 * Call on exit from WaitEvent. See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 * \def T1_TraceResumeFastPC
 * Call on exit from WaitEvent. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_     T1.scope task ID of waiting task
 * \def T1_TraceResumeNoSusp
 * Call on exit from WaitEvent. See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 * \def T1_TraceResumeNoSuspPC
 * Call on exit from WaitEvent. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_     T1.scope task ID of waiting task
 * \def T1_TraceEvent
 * Call at a user event or user stopwatch event. See \ref PC and \ref INTRPT.
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 * \def T1_TraceEventPC
 * Call at a user event or user stopwatch event. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 * \def T1_TraceEventFast
 * Call at a user event or user stopwatch event. See \ref PC and \ref INTRPT.
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 * \def T1_TraceEventFastPC
 * Call at a user event or user stopwatch event. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 * \def T1_TraceEventNoSusp
 * Call at a user event or user stopwatch event. See \ref PC and \ref INTRPT.
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 * \def T1_TraceEventNoSuspPC
 * Call at a user event or user stopwatch event. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 * \def T1_TraceUint32
 * \brief Call at user data event with 32-bit unsigned integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceUint32PC
 * \brief Call at user data event with 32-bit unsigned integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceUint32Fast
 * \brief Call at user data event with 32-bit unsigned integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceUint32FastPC
 * \brief Call at user data event with 32-bit unsigned integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceUint32NoSusp
 * \brief Call at user data event with 32-bit unsigned integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceUint32NoSuspPC
 * \brief Call at user data event with 32-bit unsigned integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceUint16
 * \brief Call at user data event with 16-bit unsigned integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceUint16PC
 * \brief Call at user data event with 16-bit unsigned integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceUint16Fast
 * \brief Call at user data event with 16-bit unsigned integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceUint16FastPC
 * \brief Call at user data event with 16-bit unsigned integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceUint16NoSusp
 * \brief Call at user data event with 16-bit unsigned integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceUint16NoSuspPC
 * \brief Call at user data event with 16-bit unsigned integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceSint32
 * \brief Call at user data event with 32-bit signed integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceSint32PC
 * \brief Call at user data event with 32-bit signed integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceSint32Fast
 * \brief Call at user data event with 32-bit signed integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceSint32FastPC
 * \brief Call at user data event with 32-bit signed integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceSint32NoSusp
 * \brief Call at user data event with 32-bit signed integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceSint32NoSuspPC
 * \brief Call at user data event with 32-bit signed integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceSint16
 * \brief Call at user data event with 16-bit signed integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceSint16PC
 * \brief Call at user data event with 16-bit signed integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceSint16Fast
 * \brief Call at user data event with 16-bit signed integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceSint16FastPC
 * \brief Call at user data event with 16-bit signed integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceSint16NoSusp
 * \brief Call at user data event with 16-bit signed integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceSint16NoSuspPC
 * \brief Call at user data event with 16-bit signed integer. See \ref PC and \ref INTRPT.
 * \def T1_TraceAddr
 * \brief Call at user data event with 32-bit address. See \ref PC and \ref INTRPT.
 * \def T1_TraceAddrPC
 * \brief Call at user data event with 32-bit address. See \ref PC and \ref INTRPT.
 * \def T1_TraceAddrFast
 * \brief Call at user data event with 32-bit address. See \ref PC and \ref INTRPT.
 * \def T1_TraceAddrFastPC
 * \brief Call at user data event with 32-bit address. See \ref PC and \ref INTRPT.
 * \def T1_TraceAddrNoSusp
 * \brief Call at user data event with 32-bit address. See \ref PC and \ref INTRPT.
 * \def T1_TraceAddrNoSuspPC
 * \brief Call at user data event with 32-bit address. See \ref PC and \ref INTRPT.
 * \def T1_TraceString
 * \brief Call at user data event with address and length of string data. See \ref PC and \ref INTRPT.
 * \def T1_TraceStringPC
 * \brief Call at user data event with address and length of string data. See \ref PC and \ref INTRPT.
 * \def T1_TraceStringFast
 * \brief Call at user data event with address and length of string data. See \ref PC and \ref INTRPT.
 * \def T1_TraceStringFastPC
 * \brief Call at user data event with address and length of string data. See \ref PC and \ref INTRPT.
 * \def T1_TraceStringNoSusp
 * \brief Call at user data event with address and length of string data. See \ref PC and \ref INTRPT.
 * \def T1_TraceStringNoSuspPC
 * \brief Call at user data event with address and length of string data. See \ref PC and \ref INTRPT.
 */


/* BEGIN generated variant macros */
#   if defined T1_NOF_CORES
#       if 1 == T1_NOF_CORES
#           define T1_TraceActivation( taskId_ )                            \
            T1_TRACE_ACT_PC( 0, (taskId_) )
#           define T1_TraceActivationPC( coreId_, taskId_ )                 \
            T1_TRACE_ACT_PC( 0, (taskId_) )
#           define T1_TraceActivationFast( taskId_ )                        \
            T1_TRACE_ACT_PC( 0, (taskId_) )
#           define T1_TraceActivationFastPC( coreId_, taskId_ )             \
            T1_TRACE_ACT_PC( 0, (taskId_) )
#           define T1_TraceActivationNoSusp( taskId_ )                      \
            T1_TRACE_ACT_NOSUSP_PC( 0, (taskId_) )
#           define T1_TraceActivationNoSuspPC( coreId_, taskId_ )           \
            T1_TRACE_ACT_NOSUSP_PC( 0, (taskId_) )
#           define T1_TraceEvent( event_, info_ )                           \
            T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventPC( coreId_, event_, info_ )                \
            T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventFast( event_, info_ )                       \
            T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventFastPC( coreId_, event_, info_ )            \
            T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSusp( event_, info_ )                     \
            T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSuspPC( coreId_, event_, info_ )          \
            T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSuspTime( time_, event_, info_ )          \
            T1_TraceEventNoSuspTime_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), (time_), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSuspTimePC( coreId_, time_, event_, info_ ) \
            T1_TraceEventNoSuspTime_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), (time_), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceRelease( taskId_ )                               \
            T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleasePC( coreId_, taskId_ )                    \
            T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseFast( taskId_ )                           \
            T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseFastPC( coreId_, taskId_ )                \
            T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseNoSusp( taskId_ )                         \
            T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseNoSuspPC( coreId_, taskId_ )              \
            T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceResume( taskId_ )                                \
            T1_INCR_PREEMPTIONS_PC( 0, T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumePC( coreId_, taskId_ )                     \
            T1_INCR_PREEMPTIONS_PC( 0, T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeFast( taskId_ )                            \
            T1_INCR_PREEMPTIONS_PC( 0, T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeFastPC( coreId_, taskId_ )                 \
            T1_INCR_PREEMPTIONS_PC( 0, T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeNoSusp( taskId_ )                          \
            T1_INCR_PREEMPTIONS_PC( 0, T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeNoSuspPC( coreId_, taskId_ )               \
            T1_INCR_PREEMPTIONS_PC( 0, T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceStart( taskId_ )                                 \
            T1_INCR_PREEMPTIONS_PC( 0, T1_TRACE_START_PC( , 0, (taskId_) ) )
#           define T1_TraceStartPC( coreId_, taskId_ )                      \
            T1_INCR_PREEMPTIONS_PC( 0, T1_TRACE_START_PC( , 0, (taskId_) ) )
#           define T1_TraceStartFast( taskId_ )                             \
            T1_INCR_PREEMPTIONS_PC( 0, T1_TRACE_START_PC( Fast, 0, (taskId_) ) )
#           define T1_TraceStartFastPC( coreId_, taskId_ )                  \
            T1_INCR_PREEMPTIONS_PC( 0, T1_TRACE_START_PC( Fast, 0, (taskId_) ) )
#           define T1_TraceStartNoSusp( taskId_ )                           \
            T1_INCR_PREEMPTIONS_PC( 0, T1_TRACE_START_PC( NoSusp, 0, (taskId_) ) )
#           define T1_TraceStartNoSuspPC( coreId_, taskId_ )                \
            T1_INCR_PREEMPTIONS_PC( 0, T1_TRACE_START_PC( NoSusp, 0, (taskId_) ) )
#           define T1_TraceStartAct( taskId_, actCoreId_, actTime_ )        \
            T1_TRACE_START_ACT_PC( , 0, (taskId_), 0, (actTime_) )
#           define T1_TraceStartActPC( coreId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_START_ACT_PC( , 0, (taskId_), 0, (actTime_) )
#           define T1_TraceStartActFast( taskId_, actCoreId_, actTime_ )    \
            T1_TRACE_START_ACT_PC( Fast, 0, (taskId_), 0, (actTime_) )
#           define T1_TraceStartActFastPC( coreId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_START_ACT_PC( Fast, 0, (taskId_), 0, (actTime_) )
#           define T1_TraceStartActNoSusp( taskId_, actCoreId_, actTime_ )  \
            T1_TRACE_START_ACT_PC( NoSusp, 0, (taskId_), 0, (actTime_) )
#           define T1_TraceStartActNoSuspPC( coreId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_START_ACT_PC( NoSusp, 0, (taskId_), 0, (actTime_) )
#           define T1_TraceStartNoAct( taskId_ )                            \
            T1_TRACE_START_NOACT_PC( , 0, (taskId_) )
#           define T1_TraceStartNoActPC( coreId_, taskId_ )                 \
            T1_TRACE_START_NOACT_PC( , 0, (taskId_) )
#           define T1_TraceStartNoActFast( taskId_ )                        \
            T1_TRACE_START_NOACT_PC( Fast, 0, (taskId_) )
#           define T1_TraceStartNoActFastPC( coreId_, taskId_ )             \
            T1_TRACE_START_NOACT_PC( Fast, 0, (taskId_) )
#           define T1_TraceStartNoActNoSusp( taskId_ )                      \
            T1_TRACE_START_NOACT_PC( NoSusp, 0, (taskId_) )
#           define T1_TraceStartNoActNoSuspPC( coreId_, taskId_ )           \
            T1_TRACE_START_NOACT_PC( NoSusp, 0, (taskId_) )
#           define T1_TraceStop( taskId_ )                                  \
            T1_DECR_PREEMPTIONS_PC( 0,T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopPC( coreId_, taskId_ )                       \
            T1_DECR_PREEMPTIONS_PC( 0,T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopFast( taskId_ )                              \
            T1_DECR_PREEMPTIONS_PC( 0,T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopFastPC( coreId_, taskId_ )                   \
            T1_DECR_PREEMPTIONS_PC( 0,T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopNoSusp( taskId_ )                            \
            T1_DECR_PREEMPTIONS_PC( 0,T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopNoSuspPC( coreId_, taskId_ )                 \
            T1_DECR_PREEMPTIONS_PC( 0,T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopStart( stopTaskId_, taskId_ )                \
            T1_TRACE_STOP_START_PC( , 0, (taskId_) )
#           define T1_TraceStopStartPC( coreId_, stopTaskId_, taskId_ )     \
            T1_TRACE_STOP_START_PC( , 0, (taskId_) )
#           define T1_TraceStopStartFast( stopTaskId_, taskId_ )            \
            T1_TRACE_STOP_START_PC( Fast, 0, (taskId_) )
#           define T1_TraceStopStartFastPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_PC( Fast, 0, (taskId_) )
#           define T1_TraceStopStartNoSusp( stopTaskId_, taskId_ )          \
            T1_TRACE_STOP_START_PC( NoSusp, 0, (taskId_) )
#           define T1_TraceStopStartNoSuspPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_PC( NoSusp, 0, (taskId_) )
#           define T1_TraceStopStartAct( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( , 0, (taskId_), 0, (actTime_) )
#           define T1_TraceStopStartActPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( , 0, (taskId_), 0, (actTime_) )
#           define T1_TraceStopStartActFast( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( Fast, 0, (taskId_), 0, (actTime_) )
#           define T1_TraceStopStartActFastPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( Fast, 0, (taskId_), 0, (actTime_) )
#           define T1_TraceStopStartActNoSusp( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( NoSusp, 0, (taskId_), 0, (actTime_) )
#           define T1_TraceStopStartActNoSuspPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( NoSusp, 0, (taskId_), 0, (actTime_) )
#           define T1_TraceStopStartNoAct( stopTaskId_, taskId_ )           \
            T1_TRACE_STOP_START_NOACT_PC( , 0, (taskId_) )
#           define T1_TraceStopStartNoActPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_NOACT_PC( , 0, (taskId_) )
#           define T1_TraceStopStartNoActFast( stopTaskId_, taskId_ )       \
            T1_TRACE_STOP_START_NOACT_PC( Fast, 0, (taskId_) )
#           define T1_TraceStopStartNoActFastPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_NOACT_PC( Fast, 0, (taskId_) )
#           define T1_TraceStopStartNoActNoSusp( stopTaskId_, taskId_ )     \
            T1_TRACE_STOP_START_NOACT_PC( NoSusp, 0, (taskId_) )
#           define T1_TraceStopStartNoActNoSuspPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_NOACT_PC( NoSusp, 0, (taskId_) )
#           define T1_TraceSyncTimer( coreId_ )                             \
            T1_TraceSync_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerPC( coreId_ )                           \
            T1_TraceSync_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerFast( coreId_ )                         \
            T1_TraceSyncFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerFastPC( coreId_ )                       \
            T1_TraceSyncFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerNoSusp( coreId_ )                       \
            T1_TraceSyncNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerNoSuspPC( coreId_ )                     \
            T1_TraceSyncNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceWait( taskId_ )                                  \
            T1_DECR_PREEMPTIONS_PC( 0,T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitPC( coreId_, taskId_ )                       \
            T1_DECR_PREEMPTIONS_PC( 0,T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitFast( taskId_ )                              \
            T1_DECR_PREEMPTIONS_PC( 0,T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitFastPC( coreId_, taskId_ )                   \
            T1_DECR_PREEMPTIONS_PC( 0,T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitNoSusp( taskId_ )                            \
            T1_DECR_PREEMPTIONS_PC( 0,T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitNoSuspPC( coreId_, taskId_ )                 \
            T1_DECR_PREEMPTIONS_PC( 0,T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( 0 ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       elif defined T1_CONT_REMOTE
#           define T1_TraceActivation( taskId_ )                            \
            T1_TRACE_ACT_PC( T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceActivationPC( coreId_, taskId_ )                 \
            T1_TRACE_ACT_PC( (coreId_), (taskId_) )
#           define T1_TraceActivationFast( taskId_ )                        \
            T1_TRACE_ACT_PC( T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceActivationFastPC( coreId_, taskId_ )             \
            T1_TRACE_ACT_PC( (coreId_), (taskId_) )
#           define T1_TraceActivationNoSusp( taskId_ )                      \
            T1_TRACE_ACT_NOSUSP_PC( T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceActivationNoSuspPC( coreId_, taskId_ )           \
            T1_TRACE_ACT_NOSUSP_PC( (coreId_), (taskId_) )
#           define T1_TraceEvent( event_, info_ )                           \
            T1_TraceEventRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventPC( coreId_, event_, info_ )                \
            T1_TraceEventRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventFast( event_, info_ )                       \
            T1_TraceEventFastRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventFastPC( coreId_, event_, info_ )            \
            T1_TraceEventFastRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSusp( event_, info_ )                     \
            T1_TraceEventNoSuspRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSuspPC( coreId_, event_, info_ )          \
            T1_TraceEventNoSuspRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSuspTime( time_, event_, info_ )          \
            T1_TraceEventNoSuspTimeRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), (time_), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSuspTimePC( coreId_, time_, event_, info_ ) \
            T1_TraceEventNoSuspTimeRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), (time_), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceRelease( taskId_ )                               \
            T1_TraceEventRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleasePC( coreId_, taskId_ )                    \
            T1_TraceEventRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseFast( taskId_ )                           \
            T1_TraceEventFastRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseFastPC( coreId_, taskId_ )                \
            T1_TraceEventFastRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseNoSusp( taskId_ )                         \
            T1_TraceEventNoSuspRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseNoSuspPC( coreId_, taskId_ )              \
            T1_TraceEventNoSuspRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceResume( taskId_ )                                \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TraceEventRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumePC( coreId_, taskId_ )                     \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TraceEventRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeFast( taskId_ )                            \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TraceEventFastRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeFastPC( coreId_, taskId_ )                 \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TraceEventFastRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeNoSusp( taskId_ )                          \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TraceEventNoSuspRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeNoSuspPC( coreId_, taskId_ )               \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TraceEventNoSuspRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceStart( taskId_ )                                 \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_START_PC( RC, T1_GetCoreIdOffset( ), (taskId_) ) )
#           define T1_TraceStartPC( coreId_, taskId_ )                      \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TRACE_START_PC( RC, (coreId_), (taskId_) ) )
#           define T1_TraceStartFast( taskId_ )                             \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_START_PC( FastRC, T1_GetCoreIdOffset( ), (taskId_) ) )
#           define T1_TraceStartFastPC( coreId_, taskId_ )                  \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TRACE_START_PC( FastRC, (coreId_), (taskId_) ) )
#           define T1_TraceStartNoSusp( taskId_ )                           \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_START_PC( NoSuspRC, T1_GetCoreIdOffset( ), (taskId_) ) )
#           define T1_TraceStartNoSuspPC( coreId_, taskId_ )                \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TRACE_START_PC( NoSuspRC, (coreId_), (taskId_) ) )
#           define T1_TraceStartAct( taskId_, actCoreId_, actTime_ )        \
            T1_TRACE_START_ACT_PC( RC, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActPC( coreId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_START_ACT_PC( RC, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActFast( taskId_, actCoreId_, actTime_ )    \
            T1_TRACE_START_ACT_PC( FastRC, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActFastPC( coreId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_START_ACT_PC( FastRC, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActNoSusp( taskId_, actCoreId_, actTime_ )  \
            T1_TRACE_START_ACT_PC( NoSuspRC, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActNoSuspPC( coreId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_START_ACT_PC( NoSuspRC, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartNoAct( taskId_ )                            \
            T1_TRACE_START_NOACT_PC( RC, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStartNoActPC( coreId_, taskId_ )                 \
            T1_TRACE_START_NOACT_PC( RC, (coreId_), (taskId_) )
#           define T1_TraceStartNoActFast( taskId_ )                        \
            T1_TRACE_START_NOACT_PC( FastRC, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStartNoActFastPC( coreId_, taskId_ )             \
            T1_TRACE_START_NOACT_PC( FastRC, (coreId_), (taskId_) )
#           define T1_TraceStartNoActNoSusp( taskId_ )                      \
            T1_TRACE_START_NOACT_PC( NoSuspRC, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStartNoActNoSuspPC( coreId_, taskId_ )           \
            T1_TRACE_START_NOACT_PC( NoSuspRC, (coreId_), (taskId_) )
#           define T1_TraceStop( taskId_ )                                  \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopPC( coreId_, taskId_ )                       \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopFast( taskId_ )                              \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventFastRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopFastPC( coreId_, taskId_ )                   \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventFastRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopNoSusp( taskId_ )                            \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventNoSuspRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopNoSuspPC( coreId_, taskId_ )                 \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventNoSuspRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopStart( stopTaskId_, taskId_ )                \
            T1_TRACE_STOP_START_PC( RC, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartPC( coreId_, stopTaskId_, taskId_ )     \
            T1_TRACE_STOP_START_PC( RC, (coreId_), (taskId_) )
#           define T1_TraceStopStartFast( stopTaskId_, taskId_ )            \
            T1_TRACE_STOP_START_PC( FastRC, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartFastPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_PC( FastRC, (coreId_), (taskId_) )
#           define T1_TraceStopStartNoSusp( stopTaskId_, taskId_ )          \
            T1_TRACE_STOP_START_PC( NoSuspRC, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartNoSuspPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_PC( NoSuspRC, (coreId_), (taskId_) )
#           define T1_TraceStopStartAct( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( RC, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( RC, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActFast( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( FastRC, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActFastPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( FastRC, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActNoSusp( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( NoSuspRC, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActNoSuspPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( NoSuspRC, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartNoAct( stopTaskId_, taskId_ )           \
            T1_TRACE_STOP_START_NOACT_PC( RC, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartNoActPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_NOACT_PC( RC, (coreId_), (taskId_) )
#           define T1_TraceStopStartNoActFast( stopTaskId_, taskId_ )       \
            T1_TRACE_STOP_START_NOACT_PC( FastRC, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartNoActFastPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_NOACT_PC( FastRC, (coreId_), (taskId_) )
#           define T1_TraceStopStartNoActNoSusp( stopTaskId_, taskId_ )     \
            T1_TRACE_STOP_START_NOACT_PC( NoSuspRC, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartNoActNoSuspPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_NOACT_PC( NoSuspRC, (coreId_), (taskId_) )
#           define T1_TraceSyncTimer( coreId_ )                             \
            T1_TraceSyncRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerPC( coreId_ )                           \
            T1_TraceSyncRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerFast( coreId_ )                         \
            T1_TraceSyncFastRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerFastPC( coreId_ )                       \
            T1_TraceSyncFastRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerNoSusp( coreId_ )                       \
            T1_TraceSyncNoSuspRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerNoSuspPC( coreId_ )                     \
            T1_TraceSyncNoSuspRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceWait( taskId_ )                                  \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitPC( coreId_, taskId_ )                       \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitFast( taskId_ )                              \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventFastRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitFastPC( coreId_, taskId_ )                   \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventFastRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitNoSusp( taskId_ )                            \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventNoSuspRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitNoSuspPC( coreId_, taskId_ )                 \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventNoSuspRC_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       else /* more than one core, no remote core T1.cont */
#           define T1_TraceActivation( taskId_ )                            \
            T1_TRACE_ACT_PC( T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceActivationPC( coreId_, taskId_ )                 \
            T1_TRACE_ACT_PC( (coreId_), (taskId_) )
#           define T1_TraceActivationFast( taskId_ )                        \
            T1_TRACE_ACT_PC( T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceActivationFastPC( coreId_, taskId_ )             \
            T1_TRACE_ACT_PC( (coreId_), (taskId_) )
#           define T1_TraceActivationNoSusp( taskId_ )                      \
            T1_TRACE_ACT_NOSUSP_PC( T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceActivationNoSuspPC( coreId_, taskId_ )           \
            T1_TRACE_ACT_NOSUSP_PC( (coreId_), (taskId_) )
#           define T1_TraceEvent( event_, info_ )                           \
            T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventPC( coreId_, event_, info_ )                \
            T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventFast( event_, info_ )                       \
            T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventFastPC( coreId_, event_, info_ )            \
            T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSusp( event_, info_ )                     \
            T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSuspPC( coreId_, event_, info_ )          \
            T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSuspTime( time_, event_, info_ )          \
            T1_TraceEventNoSuspTime_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), (time_), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSuspTimePC( coreId_, time_, event_, info_ ) \
            T1_TraceEventNoSuspTime_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), (time_), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceRelease( taskId_ )                               \
            T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleasePC( coreId_, taskId_ )                    \
            T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseFast( taskId_ )                           \
            T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseFastPC( coreId_, taskId_ )                \
            T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseNoSusp( taskId_ )                         \
            T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseNoSuspPC( coreId_, taskId_ )              \
            T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceResume( taskId_ )                                \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumePC( coreId_, taskId_ )                     \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeFast( taskId_ )                            \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeFastPC( coreId_, taskId_ )                 \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeNoSusp( taskId_ )                          \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeNoSuspPC( coreId_, taskId_ )               \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceStart( taskId_ )                                 \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_START_PC( , T1_GetCoreIdOffset( ), (taskId_) ) )
#           define T1_TraceStartPC( coreId_, taskId_ )                      \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TRACE_START_PC( , (coreId_), (taskId_) ) )
#           define T1_TraceStartFast( taskId_ )                             \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_START_PC( Fast, T1_GetCoreIdOffset( ), (taskId_) ) )
#           define T1_TraceStartFastPC( coreId_, taskId_ )                  \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TRACE_START_PC( Fast, (coreId_), (taskId_) ) )
#           define T1_TraceStartNoSusp( taskId_ )                           \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_START_PC( NoSusp, T1_GetCoreIdOffset( ), (taskId_) ) )
#           define T1_TraceStartNoSuspPC( coreId_, taskId_ )                \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TRACE_START_PC( NoSusp, (coreId_), (taskId_) ) )
#           define T1_TraceStartAct( taskId_, actCoreId_, actTime_ )        \
            T1_TRACE_START_ACT_PC( , T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActPC( coreId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_START_ACT_PC( , (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActFast( taskId_, actCoreId_, actTime_ )    \
            T1_TRACE_START_ACT_PC( Fast, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActFastPC( coreId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_START_ACT_PC( Fast, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActNoSusp( taskId_, actCoreId_, actTime_ )  \
            T1_TRACE_START_ACT_PC( NoSusp, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActNoSuspPC( coreId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_START_ACT_PC( NoSusp, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartNoAct( taskId_ )                            \
            T1_TRACE_START_NOACT_PC( , T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStartNoActPC( coreId_, taskId_ )                 \
            T1_TRACE_START_NOACT_PC( , (coreId_), (taskId_) )
#           define T1_TraceStartNoActFast( taskId_ )                        \
            T1_TRACE_START_NOACT_PC( Fast, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStartNoActFastPC( coreId_, taskId_ )             \
            T1_TRACE_START_NOACT_PC( Fast, (coreId_), (taskId_) )
#           define T1_TraceStartNoActNoSusp( taskId_ )                      \
            T1_TRACE_START_NOACT_PC( NoSusp, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStartNoActNoSuspPC( coreId_, taskId_ )           \
            T1_TRACE_START_NOACT_PC( NoSusp, (coreId_), (taskId_) )
#           define T1_TraceStop( taskId_ )                                  \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopPC( coreId_, taskId_ )                       \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopFast( taskId_ )                              \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopFastPC( coreId_, taskId_ )                   \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopNoSusp( taskId_ )                            \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopNoSuspPC( coreId_, taskId_ )                 \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopStart( stopTaskId_, taskId_ )                \
            T1_TRACE_STOP_START_PC( , T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartPC( coreId_, stopTaskId_, taskId_ )     \
            T1_TRACE_STOP_START_PC( , (coreId_), (taskId_) )
#           define T1_TraceStopStartFast( stopTaskId_, taskId_ )            \
            T1_TRACE_STOP_START_PC( Fast, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartFastPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_PC( Fast, (coreId_), (taskId_) )
#           define T1_TraceStopStartNoSusp( stopTaskId_, taskId_ )          \
            T1_TRACE_STOP_START_PC( NoSusp, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartNoSuspPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_PC( NoSusp, (coreId_), (taskId_) )
#           define T1_TraceStopStartAct( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( , T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( , (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActFast( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( Fast, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActFastPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( Fast, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActNoSusp( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( NoSusp, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActNoSuspPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( NoSusp, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartNoAct( stopTaskId_, taskId_ )           \
            T1_TRACE_STOP_START_NOACT_PC( , T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartNoActPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_NOACT_PC( , (coreId_), (taskId_) )
#           define T1_TraceStopStartNoActFast( stopTaskId_, taskId_ )       \
            T1_TRACE_STOP_START_NOACT_PC( Fast, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartNoActFastPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_NOACT_PC( Fast, (coreId_), (taskId_) )
#           define T1_TraceStopStartNoActNoSusp( stopTaskId_, taskId_ )     \
            T1_TRACE_STOP_START_NOACT_PC( NoSusp, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartNoActNoSuspPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_NOACT_PC( NoSusp, (coreId_), (taskId_) )
#           define T1_TraceSyncTimer( coreId_ )                             \
            T1_TraceSync_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerPC( coreId_ )                           \
            T1_TraceSync_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerFast( coreId_ )                         \
            T1_TraceSyncFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerFastPC( coreId_ )                       \
            T1_TraceSyncFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerNoSusp( coreId_ )                       \
            T1_TraceSyncNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerNoSuspPC( coreId_ )                     \
            T1_TraceSyncNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceWait( taskId_ )                                  \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitPC( coreId_, taskId_ )                       \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitFast( taskId_ )                              \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitFastPC( coreId_, taskId_ )                   \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitNoSusp( taskId_ )                            \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitNoSuspPC( coreId_, taskId_ )                 \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       endif /* 1 == T1_NOF_CORES */
#   else /* single core */
#       if 1
#           define T1_TraceActivation( taskId_ )                            \
            T1_TRACE_ACT_PC( T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceActivationPC( coreId_, taskId_ )                 \
            T1_TRACE_ACT_PC( (coreId_), (taskId_) )
#           define T1_TraceActivationFast( taskId_ )                        \
            T1_TRACE_ACT_PC( T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceActivationFastPC( coreId_, taskId_ )             \
            T1_TRACE_ACT_PC( (coreId_), (taskId_) )
#           define T1_TraceActivationNoSusp( taskId_ )                      \
            T1_TRACE_ACT_NOSUSP_PC( T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceActivationNoSuspPC( coreId_, taskId_ )           \
            T1_TRACE_ACT_NOSUSP_PC( (coreId_), (taskId_) )
#           define T1_TraceEvent( event_, info_ )                           \
            T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventPC( coreId_, event_, info_ )                \
            T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventFast( event_, info_ )                       \
            T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventFastPC( coreId_, event_, info_ )            \
            T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSusp( event_, info_ )                     \
            T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSuspPC( coreId_, event_, info_ )          \
            T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSuspTime( time_, event_, info_ )          \
            T1_TraceEventNoSuspTime_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), (time_), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceEventNoSuspTimePC( coreId_, time_, event_, info_ ) \
            T1_TraceEventNoSuspTime_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), (time_), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#           define T1_TraceRelease( taskId_ )                               \
            T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleasePC( coreId_, taskId_ )                    \
            T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseFast( taskId_ )                           \
            T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseFastPC( coreId_, taskId_ )                \
            T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseNoSusp( taskId_ )                         \
            T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceReleaseNoSuspPC( coreId_, taskId_ )              \
            T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#           define T1_TraceResume( taskId_ )                                \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumePC( coreId_, taskId_ )                     \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeFast( taskId_ )                            \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeFastPC( coreId_, taskId_ )                 \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeNoSusp( taskId_ )                          \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceResumeNoSuspPC( coreId_, taskId_ )               \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#           define T1_TraceStart( taskId_ )                                 \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_START_PC( , T1_GetCoreIdOffset( ), (taskId_) ) )
#           define T1_TraceStartPC( coreId_, taskId_ )                      \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TRACE_START_PC( , (coreId_), (taskId_) ) )
#           define T1_TraceStartFast( taskId_ )                             \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_START_PC( Fast, T1_GetCoreIdOffset( ), (taskId_) ) )
#           define T1_TraceStartFastPC( coreId_, taskId_ )                  \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TRACE_START_PC( Fast, (coreId_), (taskId_) ) )
#           define T1_TraceStartNoSusp( taskId_ )                           \
            T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_START_PC( NoSusp, T1_GetCoreIdOffset( ), (taskId_) ) )
#           define T1_TraceStartNoSuspPC( coreId_, taskId_ )                \
            T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TRACE_START_PC( NoSusp, (coreId_), (taskId_) ) )
#           define T1_TraceStartAct( taskId_, actCoreId_, actTime_ )        \
            T1_TRACE_START_ACT_PC( , T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActPC( coreId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_START_ACT_PC( , (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActFast( taskId_, actCoreId_, actTime_ )    \
            T1_TRACE_START_ACT_PC( Fast, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActFastPC( coreId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_START_ACT_PC( Fast, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActNoSusp( taskId_, actCoreId_, actTime_ )  \
            T1_TRACE_START_ACT_PC( NoSusp, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartActNoSuspPC( coreId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_START_ACT_PC( NoSusp, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStartNoAct( taskId_ )                            \
            T1_TRACE_START_NOACT_PC( , T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStartNoActPC( coreId_, taskId_ )                 \
            T1_TRACE_START_NOACT_PC( , (coreId_), (taskId_) )
#           define T1_TraceStartNoActFast( taskId_ )                        \
            T1_TRACE_START_NOACT_PC( Fast, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStartNoActFastPC( coreId_, taskId_ )             \
            T1_TRACE_START_NOACT_PC( Fast, (coreId_), (taskId_) )
#           define T1_TraceStartNoActNoSusp( taskId_ )                      \
            T1_TRACE_START_NOACT_PC( NoSusp, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStartNoActNoSuspPC( coreId_, taskId_ )           \
            T1_TRACE_START_NOACT_PC( NoSusp, (coreId_), (taskId_) )
#           define T1_TraceStop( taskId_ )                                  \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopPC( coreId_, taskId_ )                       \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopFast( taskId_ )                              \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopFastPC( coreId_, taskId_ )                   \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopNoSusp( taskId_ )                            \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopNoSuspPC( coreId_, taskId_ )                 \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_STOP, (taskId_) ) ) )
#           define T1_TraceStopStart( stopTaskId_, taskId_ )                \
            T1_TRACE_STOP_START_PC( , T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartPC( coreId_, stopTaskId_, taskId_ )     \
            T1_TRACE_STOP_START_PC( , (coreId_), (taskId_) )
#           define T1_TraceStopStartFast( stopTaskId_, taskId_ )            \
            T1_TRACE_STOP_START_PC( Fast, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartFastPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_PC( Fast, (coreId_), (taskId_) )
#           define T1_TraceStopStartNoSusp( stopTaskId_, taskId_ )          \
            T1_TRACE_STOP_START_PC( NoSusp, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartNoSuspPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_PC( NoSusp, (coreId_), (taskId_) )
#           define T1_TraceStopStartAct( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( , T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( , (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActFast( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( Fast, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActFastPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( Fast, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActNoSusp( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( NoSusp, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartActNoSuspPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
            T1_TRACE_STOP_START_ACT_PC( NoSusp, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#           define T1_TraceStopStartNoAct( stopTaskId_, taskId_ )           \
            T1_TRACE_STOP_START_NOACT_PC( , T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartNoActPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_NOACT_PC( , (coreId_), (taskId_) )
#           define T1_TraceStopStartNoActFast( stopTaskId_, taskId_ )       \
            T1_TRACE_STOP_START_NOACT_PC( Fast, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartNoActFastPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_NOACT_PC( Fast, (coreId_), (taskId_) )
#           define T1_TraceStopStartNoActNoSusp( stopTaskId_, taskId_ )     \
            T1_TRACE_STOP_START_NOACT_PC( NoSusp, T1_GetCoreIdOffset( ), (taskId_) )
#           define T1_TraceStopStartNoActNoSuspPC( coreId_, stopTaskId_, taskId_ ) \
            T1_TRACE_STOP_START_NOACT_PC( NoSusp, (coreId_), (taskId_) )
#           define T1_TraceSyncTimer( coreId_ )                             \
            T1_TraceSync_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerPC( coreId_ )                           \
            T1_TraceSync_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerFast( coreId_ )                         \
            T1_TraceSyncFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerFastPC( coreId_ )                       \
            T1_TraceSyncFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerNoSusp( coreId_ )                       \
            T1_TraceSyncNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceSyncTimerNoSuspPC( coreId_ )                     \
            T1_TraceSyncNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ), 0u )
#           define T1_TraceWait( taskId_ )                                  \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitPC( coreId_, taskId_ )                       \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEvent_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitFast( taskId_ )                              \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitFastPC( coreId_, taskId_ )                   \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventFast_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitNoSusp( taskId_ )                            \
            T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ),T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#           define T1_TraceWaitNoSuspPC( coreId_, taskId_ )                 \
            T1_DECR_PREEMPTIONS_PC( (coreId_),T1_TraceEventNoSusp_( T1_CORE_ID_TO_SCOPE_GLOBALS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       endif /* 1 == T1_NOF_CORES */
#   endif /* defined T1_NOF_CORES */
/* END   generated variant macros */

#   define T1_TraceData( id_, kind_, pData_, len_ )                         \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (kind_), (T1_uint8_t const *)(pData_), (len_) )
#   define T1_TraceDataFast( id_, kind_, pData_, len_ )                     \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (kind_), (T1_uint8_t const *)(pData_), (len_) )
#   define T1_TraceDataNoSusp( id_, kind_, pData_, len_ )                   \
    T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | (kind_), (T1_uint8_t const *)(pData_), (len_) )
#   define T1_TraceUint16( id_, ui16_ )                                     \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT16, (T1_uint8_t const *)&(ui16_), 2u )
#   define T1_TraceUint16Fast( id_, ui16_ )                                 \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT16, (T1_uint8_t const *)&(ui16_), 2u )
#   define T1_TraceUint16NoSusp( id_, ui16_ )                               \
    T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT16, (T1_uint8_t const *)&(ui16_), 2u )
#   define T1_TraceUint32( id_, ui32_ )                                     \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT32, (T1_uint8_t const *)&(ui32_), 4u )
#   define T1_TraceUint32Fast( id_, ui32_ )                                 \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT32, (T1_uint8_t const *)&(ui32_), 4u )
#   define T1_TraceUint32NoSusp( id_, ui32_ )                               \
    T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT32, (T1_uint8_t const *)&(ui32_), 4u )
#   define T1_TraceSint16( id_, si16_ )                                     \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT16, (T1_uint8_t const *)&(si16_), 2u )
#   define T1_TraceSint16Fast( id_, si16_ )                                 \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT16, (T1_uint8_t const *)&(si16_), 2u )
#   define T1_TraceSint16NoSusp( id_, si16_ )                               \
    T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT16, (T1_uint8_t const *)&(si16_), 2u )
#   define T1_TraceSint32( id_, si32_ )                                     \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT32, (T1_uint8_t const *)&(si32_), 4u )
#   define T1_TraceSint32Fast( id_, si32_ )                                 \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT32, (T1_uint8_t const *)&(si32_), 4u )
#   define T1_TraceSint32NoSusp( id_, si32_ )                               \
    T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT32, (T1_uint8_t const *)&(si32_), 4u )
#   define T1_TraceAddr( id_, addr_ )                                       \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_ADDRESS, (T1_uint8_t const *)&(addr_), 4u )
#   define T1_TraceAddrFast( id_, addr_ )                                   \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_ADDRESS, (T1_uint8_t const *)&(addr_), 4u )
#   define T1_TraceAddrNoSusp( id_, addr_ )                                 \
    T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_ADDRESS, (T1_uint8_t const *)&(addr_), 4u )
#   if defined T1_32BIT_TRACE_TIME
#       define T1_TraceString( id_, pData_, len_ )                              \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceStringFast( id_, pData_, len_ )                          \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceStringNoSusp( id_, pData_, len_ )                        \
    T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceBinary( id_, pData_, len_ )                              \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceBinaryFast( id_, pData_, len_ )                          \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceBinaryNoSusp( id_, pData_, len_ )                        \
    T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#   else /* 16 bit trace time */
#       define T1_TraceString( id_, pData_, len_ )                              \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceStringFast( id_, pData_, len_ )                          \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceStringNoSusp( id_, pData_, len_ )                        \
    T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceBinary( id_, pData_, len_ )                              \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceBinaryFast( id_, pData_, len_ )                          \
    T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceBinaryNoSusp( id_, pData_, len_ )                        \
    T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#   endif /* defined T1_32BIT_TRACE_TIME */
#   define T1_TraceDataPC( coreId_, id_, kind_, pData_, len_ )              \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | (kind_), (T1_uint8_t const *)(pData_), (len_) )
#   define T1_TraceDataFastPC( coreId_, id_, kind_, pData_, len_ )          \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | (kind_), (T1_uint8_t const *)(pData_), (len_) )
#   define T1_TraceDataNoSuspPC( coreId_, id_, kind_, pData_, len_ )        \
    T1_TRACEDATA_PC( NoSusp_, (coreId_), (((id_) & 0x1Fu) << 4) | (kind_), (T1_uint8_t const *)(pData_), (len_) )
#   define T1_TraceUint16PC( coreId_, id_, ui16_ )                          \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT16, (T1_uint8_t const *)&(ui16_), 2u )
#   define T1_TraceUint16FastPC( coreId_, id_, ui16_ )                      \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT16, (T1_uint8_t const *)&(ui16_), 2u )
#   define T1_TraceUint16NoSuspPC( coreId_, id_, ui16_ )                    \
    T1_TRACEDATA_PC( NoSusp_, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT16, (T1_uint8_t const *)&(ui16_), 2u )
#   define T1_TraceUint32PC( coreId_, id_, ui32_ )                          \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT32, (T1_uint8_t const *)&(ui32_), 4u )
#   define T1_TraceUint32FastPC( coreId_, id_, ui32_ )                      \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT32, (T1_uint8_t const *)&(ui32_), 4u )
#   define T1_TraceUint32NoSuspPC( coreId_, id_, ui32_ )                    \
    T1_TRACEDATA_PC( NoSusp_, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT32, (T1_uint8_t const *)&(ui32_), 4u )
#   define T1_TraceSint16PC( coreId_, id_, si16_ )                          \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT16, (T1_uint8_t const *)&(si16_), 2u )
#   define T1_TraceSint16FastPC( coreId_, id_, si16_ )                      \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT16, (T1_uint8_t const *)&(si16_), 2u )
#   define T1_TraceSint16NoSuspPC( coreId_, id_, si16_ )                    \
    T1_TRACEDATA_PC( NoSusp_, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT16, (T1_uint8_t const *)&(si16_), 2u )
#   define T1_TraceSint32PC( coreId_, id_, si32_ )                          \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT32, (T1_uint8_t const *)&(si32_), 4u )
#   define T1_TraceSint32FastPC( coreId_, id_, si32_ )                      \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT32, (T1_uint8_t const *)&(si32_), 4u )
#   define T1_TraceSint32NoSuspPC( coreId_, id_, si32_ )                    \
    T1_TRACEDATA_PC( NoSusp_, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT32, (T1_uint8_t const *)&(si32_), 4u )
#   define T1_TraceAddrPC( coreId_, id_, addr_ )                            \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_ADDRESS, (T1_uint8_t const *)&(addr_), 4u )
#   define T1_TraceAddrFastPC( coreId_, id_, addr_ )                        \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_ADDRESS, (T1_uint8_t const *)&(addr_), 4u )
#   define T1_TraceAddrNoSuspPC( coreId_, id_, addr_ )                      \
    T1_TRACEDATA_PC( NoSusp_, (coreId_), (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_ADDRESS, (T1_uint8_t const *)&(addr_), 4u )
#   if defined T1_32BIT_TRACE_TIME
#       define T1_TraceStringPC( coreId_, id_, pData_, len_ )               \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceStringFastPC( coreId_, id_, pData_, len_ )           \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceStringNoSuspPC( coreId_, id_, pData_, len_ )         \
    T1_TRACEDATA_PC( NoSusp_, (coreId_), (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceBinaryPC( coreId_, id_, pData_, len_ )               \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceBinaryFastPC( coreId_, id_, pData_, len_ )           \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceBinaryNoSuspPC( coreId_, id_, pData_, len_ )         \
    T1_TRACEDATA_PC( NoSusp_, (coreId_), (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#   else /* 16 bit trace time */
#       define T1_TraceStringPC( coreId_, id_, pData_, len_ )               \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceStringFastPC( coreId_, id_, pData_, len_ )           \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceStringNoSuspPC( coreId_, id_, pData_, len_ )         \
    T1_TRACEDATA_PC( NoSusp_, (coreId_), (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceBinaryPC( coreId_, id_, pData_, len_ )               \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceBinaryFastPC( coreId_, id_, pData_, len_ )           \
    T1_TRACEDATA_PC( _, (coreId_), (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceBinaryNoSuspPC( coreId_, id_, pData_, len_ )         \
    T1_TRACEDATA_PC( NoSusp_, (coreId_), (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#   endif /* defined T1_32BIT_TRACE_TIME */

    /* Deprecated */
#   define T1_TraceSync( pTime_ )                   ((void)0)
#   define T1_TraceSyncFast( pTime_ )               ((void)0)
#   define T1_TraceSyncNoSusp( pTime_ )             ((void)0)

/*!
 * Trace a user stopwatch event or user event only if application feature is enabled.
 * See \ref INTRPT.
 * \param[in] event_ the event ID
 * \param[in] info_  additional info field, for example task/stopwatch ID
 * \param[in] mask_  the application feature to test
 */
#   define T1_TraceEventPerFeature( event_, info_, mask_ )              \
    do                                                                  \
    {                                                                   \
        if( T1_IsFeatureEnabled( mask_ ) )                              \
        {                                                               \
            T1_TraceEvent( event_, info_ );                             \
        }                                                               \
    }                                                                   \
    while( 0 )
/*!
 * Trace a user stopwatch event or user event only if application feature is enabled.
 * See \ref INTRPT.
 * \param[in] event_ the event ID
 * \param[in] info_  additional info field, for example task/stopwatch ID
 * \param[in] mask_  the application feature to test
 */
#   define T1_TraceEventFastPerFeature( event_, info_, mask_ )          \
    do                                                                  \
    {                                                                   \
        if( T1_IsFeatureEnabled( mask_ ) )                              \
        {                                                               \
            T1_TraceEventFast( event_, info_ );                         \
        }                                                               \
    }                                                                   \
    while( 0 )
/*!
 * Trace a user stopwatch event or user event only if application feature is enabled.
 * See \ref INTRPT.
 * \param[in] event_ the event ID
 * \param[in] info_  additional info field, for example task/stopwatch ID
 * \param[in] mask_  the application feature to test
 */
#   define T1_TraceEventNoSuspPerFeature( event_, info_, mask_ )        \
    do                                                                  \
    {                                                                   \
        if( T1_IsFeatureEnabled( mask_ ) )                              \
        {                                                               \
            T1_TraceEventNoSusp( event_, info_ );                       \
        }                                                               \
    }                                                                   \
    while( 0 )

#else /* !defined T1_ENABLE || defined T1_DISABLE_T1_SCOPE */
#   define T1_scopePlugin (T1_DISABLED_PLUGIN)
/* empty macros */
#   if defined T1_NOF_CORES
#       define T1_InitTraceBufferPC( coreId_ )      ((void)0)
#   else /* single core */
#       define T1_InitTraceBuffer( )                ((void)0)
#   endif /* T1_NOF_CORES */
#   define T1_TraceEvent( event_, info_ )           ((void)0)
#   define T1_TraceEventFast( event_, info_ )       ((void)0)
#   define T1_TraceEventNoSusp( event_, info_ )     ((void)0)
#   define T1_TraceEventNoSuspTime( time_, event_, info_ ) ((void)0)
#   define T1_TraceEventPC( coreId_, event_, info_ ) ((void)0)
#   define T1_TraceEventFastPC( coreId_, event_, info_ ) ((void)0)
#   define T1_TraceEventNoSuspPC( coreId_, event_, info_ ) ((void)0)
#   define T1_TraceEventNoSuspTimePC( coreId_, time_, event_, info_ ) ((void)0)
#   define T1_TraceStart( taskId_ )                 ((void)0)
#   define T1_TraceStartFast( taskId_ )             ((void)0)
#   define T1_TraceStartNoSusp( taskId_ )           ((void)0)
#   define T1_TraceStartPC( coreId_, taskId_ )      ((void)0)
#   define T1_TraceStartFastPC( coreId_, taskId_ )  ((void)0)
#   define T1_TraceStartNoSuspPC( coreId_, taskId_ ) ((void)0)
#   define T1_TraceStartAct( taskId_, actCoreId_, time_ ) ((void)0)
#   define T1_TraceStartActFast( taskId_, actCoreId_, time_ ) ((void)0)
#   define T1_TraceStartActNoSusp( taskId_, actCoreId_, time_ ) ((void)0)
#   define T1_TraceStartActPC( coreId_, taskId_, actCoreId_, time_ ) ((void)0)
#   define T1_TraceStartActFastPC( coreId_, taskId_, actCoreId_, time_ ) ((void)0)
#   define T1_TraceStartActNoSuspPC( coreId_, taskId_, actCoreId_, time_ ) ((void)0)
#   define T1_TraceStartNoAct( taskId_ )            ((void)0)
#   define T1_TraceStartNoActFast( taskId_ )        ((void)0)
#   define T1_TraceStartNoActNoSusp( taskId_ )      ((void)0)
#   define T1_TraceStartNoActPC( coreId_, taskId_ ) ((void)0)
#   define T1_TraceStartNoActFastPC( coreId_, taskId_ ) ((void)0)
#   define T1_TraceStartNoActNoSuspPC( coreId_, taskId_ ) ((void)0)
#   define T1_TraceStop( taskId_ )                  ((void)0)
#   define T1_TraceStopFast( taskId_ )              ((void)0)
#   define T1_TraceStopNoSusp( taskId_ )            ((void)0)
#   define T1_TraceStopPC( coreId_, taskId_ )       ((void)0)
#   define T1_TraceStopFastPC( coreId_, taskId_ )   ((void)0)
#   define T1_TraceStopNoSuspPC( coreId_, taskId_ ) ((void)0)
#   define T1_TraceActivation( taskId_ )            ((void)0)
#   define T1_TraceActivationFast( taskId_ )        ((void)0)
#   define T1_TraceActivationNoSusp( taskId_ )      ((void)0)
#   define T1_TraceActivationPC( coreId_, taskId_ ) ((void)0)
#   define T1_TraceActivationFastPC( coreId_, taskId_ ) ((void)0)
#   define T1_TraceActivationNoSuspPC( coreId_, taskId_ ) ((void)0)
#   define T1_TraceStopStart( stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartFast( stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartNoSusp( stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartPC( coreId_, stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartFastPC( coreId_, stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartNoSuspPC( coreId_, stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartAct( stopTaskId_, startTaskId_, actCoreId_, time_ ) ((void)0)
#   define T1_TraceStopStartActFast( stopTaskId_, startTaskId_, actCoreId_, time_ ) ((void)0)
#   define T1_TraceStopStartActNoSusp( stopTaskId_, startTaskId_, actCoreId_, time_ ) ((void)0)
#   define T1_TraceStopStartActPC( coreId_, stopTaskId_, startTaskId_, actCoreId_, time_ ) ((void)0)
#   define T1_TraceStopStartActFastPC( coreId_, stopTaskId_, startTaskId_, actCoreId_, time_ ) ((void)0)
#   define T1_TraceStopStartActNoSuspPC( coreId_, stopTaskId_, startTaskId_, actCoreId_, time_ ) ((void)0)
#   define T1_TraceStopStartNoAct( stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartNoActFast( stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartNoActNoSusp( stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartNoActPC( coreId_, stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartNoActFastPC( coreId_, stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartNoActNoSuspPC( coreId_, stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceData( id_, kind_, pData_, len_ ) ((void)0)
#   define T1_TraceDataFast( id_, kind_, pData_, len_ ) ((void)0)
#   define T1_TraceDataNoSusp( id_, kind_, pData_, len_ ) ((void)0)
#   define T1_TraceUint16( id_, ui16_ )             ((void)0)
#   define T1_TraceUint16Fast( id_, ui16_ )         ((void)0)
#   define T1_TraceUint16NoSusp( id_, ui16_ )       ((void)0)
#   define T1_TraceUint32( id_, ui32_ )             ((void)0)
#   define T1_TraceUint32Fast( id_, ui32_ )         ((void)0)
#   define T1_TraceUint32NoSusp( id_, ui32_ )       ((void)0)
#   define T1_TraceAddr( id_, addr_ )               ((void)0)
#   define T1_TraceAddrFast( id_, addr_ )           ((void)0)
#   define T1_TraceAddrNoSusp( id_, addr_ )         ((void)0)
#   define T1_TraceString( id_, pData_, len_ )      ((void)0)
#   define T1_TraceStringFast( id_, pData_, len_ )  ((void)0)
#   define T1_TraceStringNoSusp( id_, pData_, len_ ) ((void)0)
#   define T1_TraceBinary( id_, pData_, len_ )      ((void)0)
#   define T1_TraceBinaryFast( id_, pData_, len_ )  ((void)0)
#   define T1_TraceBinaryNoSusp( id_, pData_, len_ ) ((void)0)
#   define T1_TraceDataPC( coreId_, id_, kind_, pData_, len_ )((void)0)
#   define T1_TraceDataFastPC( coreId_, id_, kind_, pData_, len_ ) ((void)0)
#   define T1_TraceDataNoSuspPC( coreId_, id_, kind_, pData_, len_ ) ((void)0)
#   define T1_TraceUint16PC( coreId_, id_, ui16_ )   ((void)0)
#   define T1_TraceUint16FastPC( coreId_, id_, ui16_ ) ((void)0)
#   define T1_TraceUint16NoSuspPC( coreId_, id_, ui16_ ) ((void)0)
#   define T1_TraceUint32PC( coreId_, id_, ui32_ )   ((void)0)
#   define T1_TraceUint32FastPC( coreId_, id_, ui32_ ) ((void)0)
#   define T1_TraceUint32NoSuspPC( coreId_, id_, ui32_ ) ((void)0)
#   define T1_TraceAddrPC( coreId_, id_, addr_ )     ((void)0)
#   define T1_TraceAddrFastPC( coreId_, id_, addr_ ) ((void)0)
#   define T1_TraceAddrNoSuspPC( coreId_, id_, addr_ ) ((void)0)
#   define T1_TraceStringPC( coreId_, id_, pData_, len_ ) ((void)0)
#   define T1_TraceStringFastPC( coreId_, id_, pData_, len_ ) ((void)0)
#   define T1_TraceStringNoSuspPC( coreId_, id_, pData_, len_ ) ((void)0)
#   define T1_TraceBinaryPC( coreId_, id_, pData_, len_ ) ((void)0)
#   define T1_TraceBinaryFastPC( coreId_, id_, pData_, len_ ) ((void)0)
#   define T1_TraceBinaryNoSuspPC( coreId_, id_, pData_, len_ ) ((void)0)
#   define T1_TraceSync( pTime_ )                   ((void)0)
#   define T1_TraceSyncFast( pTime_ )               ((void)0)
#   define T1_TraceSyncNoSusp( pTime_ )             ((void)0)
#   define T1_TraceSyncTimer( core_ )               ((void)0)
#   define T1_TraceSyncTimerFast( core_ )           ((void)0)
#   define T1_TraceSyncTimerNoSusp( core_ )         ((void)0)
#   define T1_TraceSyncTimerPC( core_ )             ((void)0)
#   define T1_TraceSyncTimerFastPC( core_ )         ((void)0)
#   define T1_TraceSyncTimerNoSuspPC( core_ )       ((void)0)
#   define T1_SetStopTrigger( afterXevents_ )               (T1_FAILED)
#   define T1_SetStopTriggerFast( afterXevents_ )           (T1_FAILED)
#   define T1_SetStopTriggerNoSusp( afterXevents_ )         (T1_FAILED)
#   define T1_SetStopTriggerPC( coreId_, afterXevents_ )    (T1_FAILED)
#   define T1_SetStopTriggerFastPC( coreId_, afterXevents_ ) (T1_FAILED)
#   define T1_SetStopTriggerNoSuspPC( coreId_, afterXevents_ ) (T1_FAILED)
#   define T1_TraceEventPerFeature( event_, info_, mask_ )          ((void)0)
#   define T1_TraceEventFastPerFeature( event_, info_, mask_ )      ((void)0)
#   define T1_TraceEventNoSuspPerFeature( event_, info_, mask_ )    ((void)0)
#endif

/*----------------------------------------------------------------------------------*/
/*--- Declarations for global data structures --------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_NOF_CORES && !defined T1_MULTICORE_CLONE
#   define T1_START_SEC_NO_INIT_32_CORE0
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE0 T1_scopeGlobals0;
#   define T1_STOP_SEC_NO_INIT_32_CORE0
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE1
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE1 T1_scopeGlobals1;
#   define T1_STOP_SEC_NO_INIT_32_CORE1
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE2
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE2 T1_scopeGlobals2;
#   define T1_STOP_SEC_NO_INIT_32_CORE2
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE3
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE3 T1_scopeGlobals3;
#   define T1_STOP_SEC_NO_INIT_32_CORE3
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE4
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE4 T1_scopeGlobals4;
#   define T1_STOP_SEC_NO_INIT_32_CORE4
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE5
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE5 T1_scopeGlobals5;
#   define T1_STOP_SEC_NO_INIT_32_CORE5
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE6
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE6 T1_scopeGlobals6;
#   define T1_STOP_SEC_NO_INIT_32_CORE6
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE7
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE7 T1_scopeGlobals7;
#   define T1_STOP_SEC_NO_INIT_32_CORE7
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE8
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE8 T1_scopeGlobals8;
#   define T1_STOP_SEC_NO_INIT_32_CORE8
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE9
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE9 T1_scopeGlobals9;
#   define T1_STOP_SEC_NO_INIT_32_CORE9
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE10
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE10 T1_scopeGlobals10;
#   define T1_STOP_SEC_NO_INIT_32_CORE10
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE11
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE11 T1_scopeGlobals11;
#   define T1_STOP_SEC_NO_INIT_32_CORE11
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE12
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE12 T1_scopeGlobals12;
#   define T1_STOP_SEC_NO_INIT_32_CORE12
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE13
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE13 T1_scopeGlobals13;
#   define T1_STOP_SEC_NO_INIT_32_CORE13
#   include "T1_MemMap.h"
#   define T1_START_SEC_NO_INIT_32_CORE14
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t         T1_SEC_NO_INIT_32_CORE14 T1_scopeGlobals14;
#   define T1_STOP_SEC_NO_INIT_32_CORE14
#   include "T1_MemMap.h"
#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t * const T1_SEC_CONST_32 T1_scopeGlobalsPC[];
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"
#elif defined T1_MULTICORE_CLONE
#   define T1_START_SEC_NO_INIT_32_CLONE
#   include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_SEC_NO_INIT_32_CLONE T1_scopeGlobals;
#   define T1_STOP_SEC_NO_INIT_32_CLONE
#   include "T1_MemMap.h"
#else
#   if T1_USE_NEAR
#       define T1_START_SEC_NEAR_NO_INIT_32
#       include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_NEAR T1_SEC_NEAR_NO_INIT_32 T1_scopeGlobals;
#       define T1_STOP_SEC_NEAR_NO_INIT_32
#       include "T1_MemMap.h"
#   else /* ! T1_USE_NEAR */
#       define T1_START_SEC_NO_INIT_32
#       include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_SEC_NO_INIT_32 T1_scopeGlobals;
#       define T1_STOP_SEC_NO_INIT_32
#       include "T1_MemMap.h"
#   endif /* T1_USE_NEAR */
#endif /* T1_NOF_CORES */

#if defined T1_NOF_CORES

/* Intentially not in a T1-TARGET-SW section to allow for compiler init. */
T1_EXTERN T1_uint32_t T1_ALIGN_32 T1_spinlockVar;

#endif /* defined T1_NOF_CORES */

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for user functions --------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_START_SEC_CODE
#include "T1_MemMap.h"
T1_EXTERN T1_tickUint_t T1_CODE T1_GetTraceTime( void );
#if defined T1_NOF_CORES
T1_EXTERN void T1_CODE T1_GetCalibrationSpinlockPC( T1_uint8Least_t coreId, T1_bool_t isNoSusp );
T1_EXTERN void T1_CODE T1_ReleaseCalibrationSpinlockPC( T1_uint8Least_t coreId, T1_bool_t isNoSusp );
#endif /* defined T1_NOF_CORES */
#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

#if defined T1_NOF_CORES
#define T1_START_SEC_CODE_FAST
#include "T1_MemMap.h"
T1_EXTERN T1_uint32_t T1_CODE_FAST T1_GetSyncTime( void );
#define T1_STOP_SEC_CODE_FAST
#include "T1_MemMap.h"
#endif /* defined T1_NOF_CORES */

/*----------------------------------------------------------------------------------*/
/*--- documentation ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_DOXYGEN_ONLY

/*! \page USEREVENTS User events

T1 user events can be inserted anywhere in the application to observe specific
events, log data in the T1.scope trace and/or be used to configure virtual
stopwatches with the T1-HOST-SW.

Configure user events {#USEREVENTSCONFIG}
=====================
The user event must be declared in T1_AppInterface.h in order to get recognized
in the T1-HOST-SW when a trace is downloaded.

~~~~~~~~~~~~~~~{.c}
...*/

/* @T1@ <SystemElement Name="OS Error" Type="UserEvent"> */
#define T1_OS_ERROR (0x21)
/* @T1@ </SystemElement> */

/*...
~~~~~~~~~~~~~~~
The comment of the declaration must be like the example above, because it will be
read also by the T1-HOST-SW. In the first line only the name
(in this case "OS Error") can be changed by user. The value, or we could call it
UserEventID (uevId), has to be defined from 32 to 63 (from 0x20 to 0x3F).

It it possible to define the meaning of each value, which will be observed by
user events. The additional information must be defined as following codes.
In this case the defined names will be shown instead of the values in
the T1.scope view.
~~~~~~~~~~~~~~~{.c}
...*/

/* @T1@ <SystemElement Name="OS Error" Type="UserEvent"> */
/*enum
{
Error message 1 = 1,
Error message 2 = 3,
Error message 3 = 5
};*/
#define T1_OS_ERROR (0x21)
/* @T1@ </SystemElement> */

/*...
~~~~~~~~~~~~~~~

Trace user events {#TRACEUSEREVENTS}
=================
After the UserEventID has been declared following @ref USEREVENTSCONFIG, it can be
inserted anywhere in the application in order to show the current value of a
interesting variable in the trace. Only 10 bits of data are traced with
a user event, so the result is transferred modulo 1024. If a variable out of this
range need to be observed, please see @ref USERDATAEVENTS.

~~~~~~~~~~~~~~~{.c}
T1_TraceEvent( uevId, data );
~~~~~~~~~~~~~~~

uevId: UserEventID, which must be declared in T1_AppInterface.h. Its range must be
from 32 to 63.

data: The variable whose content is logged. Its current value, modulo 1024, will be
shown in a downloaded trace in T1-HOST-SW.

Multi-core adaptions of T1-TARGET-SW additionally provide T1_TraceEventPC(),
see @ref PC.

If interrupts are always enabled at this point in the code, the slightly faster
variants T1_TraceEventFast() and T1_TraceEventFastPC() can be used.

If interrupts are always disabled at this point in the code, the significantly
faster variants T1_TraceEventNoSusp() and T1_TraceEventNoSuspPC() can be used.


The following code shows you an example of tracing a user event:

~~~~~~~~~~~~~~~{.c}
T1_uint16Least_t osErrCode;
...
osErrCode = fun1(...);
T1_TraceEvent( T1_OS_ERROR, osErrCode );
~~~~~~~~~~~~~~~

*/

/*!
 * \page USERDATAEVENTS User data events

T1 user data events can be inserted anywhere in the application. In comparison with
user event, user data event can provide you more ways to observe specific events or
to log data. For example, printf can be mapped on to a T1 user data event so that
string data is captured in the trace. Besides, not like user event, user data event
can log any 16 bit or 32 bit variable, even an array or struct.

Configure user data events {#USERDATAEVENTSCONFIG}
=====================
Like user event, the user data event must also be declared in T1_AppInterface.h in
order for the T1-HOST-SW to interpret the event in a downloaded trace.

~~~~~~~~~~~~~~~{.c}
...*/

/* @T1@ <SystemElement Name="printf string" Type="UserEvent"> */
#define T1_UDE_PRINTF (0x05)
/* @T1@ </SystemElement> */

/* @T1@ <SystemElement Name="16 bit Data tracing" Type="UserEvent"> */
#define T1_UDE_16BitDataTrace (0x06)
/* @T1@ </SystemElement> */

/* @T1@ <SystemElement Name="32 bit Data tracing" Type="UserEvent"> */
#define T1_UDE_32BitDataTrace (0x07)
/* @T1@ </SystemElement> */

/* @T1@ <SystemElement Name="Binary Data tracing" Type="UserEvent"> */
#define T1_UDE_BinaryTrace (0x08)
/* @T1@ </SystemElement> */

/*...
~~~~~~~~~~~~~~~

The comments must conform to the syntax of the above examples because they need to be
readable by the T1-HOST-SW. Only the names in the comment can be chosen by the user.
The ID of the user data event (udevId) has to be in the range 0 to 31 (from 0x00 to
0x1F).

Trace user data events {#TRACEUSERDATAEVENTS}
======================

The API call is T1_TraceData(), with optimized versions T1_TraceDataFast() and
T1_TraceDataNoSusp(), described below. For commonly traced types such as strings
and 16/32 bit integers, a more convenient API is provided via a macro layer,
consisting of T1_TraceString(), T1_TraceBinary(), T1_TraceAddr(), T1_TraceUint32(),
T1_TraceSint32(), T1_TraceUint16() and T1_TraceSint16(). Each is available in the
Fast and NoSusp variations. T1_TraceData should generally not be called directly
unless explicitly instructed by GLIWA GmbH. The convenience API maps to T1_TraceData
and should normally be used in all cases.

NOTE: T1_TraceData() must not be used on variables that are also measured with T1.flex
data measurements. The T1.flex data measurement result would include the additional
read access performed by T1_TraceData(), concealing the real result. This restriction
applies also to the convenience API, of course.

To support this, T1_TraceData() calls should be guarded by an application feature, as
shown in the following code fragment. During a T1.flex data measurement, the
application feature must be disabled.

~~~~~~~~~~~~~~~{.c}
if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRACEDATA ) )
{
    T1_TraceUint32( T1_UDE_32BitDataTrace, u32value );
}
~~~~~~~~~~~~~~~

Because T1_TraceData() reads data one byte at a time, variables updated by peripherals
or other cores potentially could be traced incorrectly, with one byte coming from an
old value and another byte coming from a newer value. In this case, the data should
additionally be atomically copied to an auto variable before being traced. If the
variable read is not inherently atomic then some other mechanism must be used to
protect against inconsistency. In the following example, u32value is 32-bit aligned
in the memory of a TriCore processor, so the read is inherently atomic.

~~~~~~~~~~~~~~~{.c}
...*/

if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRACEDATA ) )
{
    const T1_uint32_t tmp = u32value;/* Atomic read */
    T1_TraceUint32( T1_UDE_32BitDataTrace, tmp );
}

/*...
~~~~~~~~~~~~~~~


Specific API for user data events {#TRACEUSERDATAEVENTSEXAMPLES}
=================================

Trace string
------------
~~~~~~~~~~~~~~~{.c}
void T1_TraceString( T1_uint8_t udevId, T1_uint8_t const *pString, T1_uint8_t lenBytes );
~~~~~~~~~~~~~~~
udevId: UserDataEventID, which must be declared in T1_AppInterface.h. Its range must
be from 0 to 31.

*pString: Address of string, which shall be shown in the tracing result in T1-HOST-SW.

lenBytes: Size of the string, which shall be shown in the tracing result in
T1-HOST-SW. Its range must be from 0 to 255.

For example, the following implementation of fputc redirects a typical embedded
printf function to generate T1 user data events.

~~~~~~~~~~~~~~~{.c}
int fputc( int c, FILE* ignored )
{
    static T1_uint8_t buff[20];
    static T1_uint8Least_t buffIdx = 0u;
    if( (c == '\n') || (c == EOF) || (buffIdx == 20u) )
    {
        T1_TraceString( T1_PRINTF, buff, buffIdx );
        buffIdx = 0u;
    }
    else
    {
        buff[buffIdx++] = (T1_uint8_t)c;
    }
    return c;
}
~~~~~~~~~~~~~~~

Trace integer
------------------
~~~~~~~~~~~~~~~{.c}
void T1_TraceUint16( T1_uint8_t udevId, T1_uint16_t value );
void T1_TraceUint32( T1_uint8_t udevId, T1_uint32_t value );
void T1_TraceSint16( T1_uint8_t udevId, signed short value );
void T1_TraceSint32( T1_uint8_t udevId, signed long value );
~~~~~~~~~~~~~~~

These four functions can be used to observe a 16 bit or 32 bit variable and show their
current value in the tracing result in T1-HOST-SW.

udevId: UserDataEventID, which must be declared in T1_AppInterface.h. Its range must
be from 0 to 31.

value: 16 or 32 bit to be measured variable. Its current value shall be shown in the
tracing result in T1-HOST-SW.

For example, the following implementation of 5msTask observes the variable "counter":

~~~~~~~~~~~~~~~{.c}
void 5msTask( void )
{
    static T1_uint16_t counter = 0;
    ...
    ++counter;
    T1_TraceUint16( T1_UDE_16BitDataTrace, counter );
    ...
}
~~~~~~~~~~~~~~~

Trace binary
------------
~~~~~~~~~~~~~~~{.c}
void T1_TraceBinary( T1_uint8_t udevId, T1_uint8_t const *variable, T1_uint8_t lenVariable );
~~~~~~~~~~~~~~~

This function can be used to observe a struct or array and show their current value
in the tracing result in T1-HOST-SW.

udevId: UserDataEventID, which must be declared in T1_AppInterface.h. Its range must
be from 0 to 31.

*variable: Address of struct or array. Its current value shall be shown in the
tracing result in T1-HOST-SW.

lenVariable: Size or length of struct or array.

For example, the following implementation of 5msTask observes the array "array1":

~~~~~~~~~~~~~~~{.c}
void 5msTask( void )
{
    static T1_uint16_t array1[20];
    ...
    T1_TraceBinary( T1_UDE_BinaryTrace, array1, sizeof(array1) );
    ...
}
~~~~~~~~~~~~~~~

Trace address
-------------
~~~~~~~~~~~~~~~{.c}
void T1_TraceAddr( T1_uint8_t udevId, T1_uint32_t addr );
~~~~~~~~~~~~~~~

This function can be used to observe the value of the 32 bit address and show its
current value in the tracing result in T1-HOST-SW.

udevId: UserDataEventID, which must be declared in T1_AppInterface.h. Its range must
be from 0 to 31.

addr: 32 bit address. Its current value shall be shown in the tracing result in
T1-HOST-SW.

Standard tracing
----------------
~~~~~~~~~~~~~~~{.c}
void T1_TraceData( T1_uint8_t udevId, T1_uint8_t kind, T1_uint8_t const *addr, T1_uint8_t lenVariable);
~~~~~~~~~~~~~~~

This function can be used to observe the value of a less commonly used data type,
such as a 64 bit variable or a float variable. Its current value shall be shown in
the tracing result in T1-HOST-SW.

udevId: UserDataEventID, which must be declared in T1_AppInterface.h. Its range must
be from 0 to 31.

kind: one of:
- #T1_TRACEDATA_SINT8
- #T1_TRACEDATA_SINT16
- #T1_TRACEDATA_SINT32
- #T1_TRACEDATA_UINT64
- #T1_TRACEDATA_SINT64
- #T1_TRACEDATA_FLOAT
- #T1_TRACEDATA_ADDRESS

addr: 32 bit address. Its current value shall be shown in the tracing result in
T1-HOST-SW.

lenVariable: Length of variable.

 */

/*! \page USERSTOPWATCHES User stopwatches

T1 user stopwatches can be inserted anywhere in the application to observe specific
periods of time. They also can be used to configure virtual stopwatches with the
T1-HOST-SW.

Configure user stopwatches {#USERSTOPWATCHESCONFIG}
==========================
The stopwatch must be declared in T1_AppInterface.h in order for the T1-HOST-SW to
interpret the event in a downloaded trace.

~~~~~~~~~~~~~~~{.c}
...*/

/* @T1@ <SystemElement Name="Suspend Interrupts" Type="Stopwatch" SID="2"> */
#define T1_SW_INTRPT (1)
/* @T1@ </SystemElement> */

/* @T1@ <SystemElement Name="Example Data Flow" Type="Stopwatch" IsDataflow="true" SID="2"> */
#define T1_SW_ExmpDataflow (2)
/* @T1@ </SystemElement> */

/*...
~~~~~~~~~~~~~~~

The syntax of the C comments must be exactly as in the example above, because these
are parsed also by the T1-HOST-SW:
- The “Name” field is configurable and can be changed by the user.
- The body of the macro determines the stopwatch identifier and has to be in the range
  0 to 767 and different from all other stopwatch identifiers used on this core.
- The "SID" field is the system identifier of the core, it is usually the core id
  incremented by 2, if all cores are used and no shifting occurs.
- Additionally, the field “IsDataflow” can be set, as shown in the second example, to
  select data flow visualization in downloaded traces.

Trace user stopwatches {#TRACEUSERSTOPWATCHES}
======================

Once a user stopwatch has been configured, you can trace the start and stop events in
the code in order to measure any time interval.

~~~~~~~~~~~~~~~{.c}
T1_TraceEvent( event, swId );
~~~~~~~~~~~~~~~

event: one of:
- #T1_STOPWATCH_START
- #T1_STOPWATCH_STOP
- #T1_STOPWATCH_STOP_START
- #T1_STOPWATCH_STOP_START_INC

swId: a T1.scope stopwatch ID, expressed as a macro defined in T1_AppInterface.h, for
example T1_SW_INTRPT, see above.

Multi-core adaptions of T1-TARGET-SW additionally provide T1_TraceEventPC(),
see @ref PC.

#T1_STOPWATCH_START and #T1_STOPWATCH_STOP are self-expanatory. The additional
stopwatch events allow one event to both stop and start a stopwatch. This is required
for the correct measurement of periods, for example, where all time must be accounted
for. If we used two different events to stop and restart a stopwatch then there would
always be a little bit of time excluded from the period. Equally, if we wish to
divide a task execution time into component portions using stopwatches, we need to
instrument the stop of the old stopwatch and the start of the new stopwatch with a
single event. Otherwise, the sum of the CET portions would be slightly smaller than
the task CET. The following example shows how to use these events
#T1_STOPWATCH_STOP_START and #T1_STOPWATCH_STOP_START_INC.

~~~~~~~~~~~~~~~{.c}
...*/

T1_TraceEvent( T1_STOPWATCH_START, 1 );          /* Start stopwatch 1 */
T1_TraceEvent( T1_STOPWATCH_STOP_START, 1 );     /* Stop and immediately restart stopwatch 1 */
T1_TraceEvent( T1_STOPWATCH_STOP_START_INC, 2 ); /* Stop stopwatch 1 and immediately start stopwatch 2 */
T1_TraceEvent( T1_STOPWATCH_STOP, 2 );           /* Stop stopwatch 2 */

/*...
~~~~~~~~~~~~~~~

If interrupts are always enabled at this point in the code, the slightly faster
variants T1_TraceEventFast() and T1_TraceEventFastPC() can be used.

If interrupts are always disabled at this point in the code, the significantly
faster variants T1_TraceEventNoSusp() and T1_TraceEventNoSuspPC() can be used.

 */

/*!
 * \page USERTRIGGERS User triggers

T1 user triggers can be inserted anywhere in the application to stop tracing and
ensure that specific events or sequences are captured for download and visualisation.

It is possible to trigger with:
~~~~~~~~~~~~~~~{.c}
T1_status_t T1_SetStopTrigger( T1_nofEntries_t afterXevents );
~~~~~~~~~~~~~~~

afterXevents: Number of entries, which shall be captured after the point of trigger.
It must be in the range 0..\<buffer size\>.

Multi-core adaptions of T1-TARGET-SW additionally provide T1_SetStopTriggerPC(),
see @ref PC.

A return value of #T1_VALUE indicates that afterXevents was larger than the buffer
size.

A return value of #T1_NOFUNC indicates that the trigger has already been set.

NOTE: After the initial start-up or re-starting tracing, an entirely new trace is
captured regardless the parameter "afterXevents"! Thus, you may get more than
“afterXevents” after the trigger point if they are required to fill the trace buffer
with new entries. In general you should be aware that, in a downloaded trace,
the trigger might be earlier than you expect.

For example, to capture a full buffer containing only events after this point in the
code, we call:
~~~~~~~~~~~~~~~{.c}
(void)T1_SetStopTrigger( T1_bufferSize );
~~~~~~~~~~~~~~~

To capture a buffer containing an equal number of events before and after this point
in the code, we call:
~~~~~~~~~~~~~~~{.c}
(void)T1_SetStopTrigger( T1_bufferSize >> 1 );
~~~~~~~~~~~~~~~

To capture a buffer containing an equal number of events before and after this point
in the code in a multi-core integration, we call:
~~~~~~~~~~~~~~~{.c}
(void)T1_SetStopTriggerPC( coreId, T1_bufferSizePC[coreId] >> 1 );
~~~~~~~~~~~~~~~

TIP: T1_AppInterface.c contains a default implementation of T1_AppInit() allowing
to capture the start-up trace depending on the application feature
#T1_AF_TRACE_STARTUP, see @ref APPFEATURES. It also provides a default implementation
allowing to trigger all cores, see T1_AppSetStopTriggerAllCores().

 */

#endif /* defined T1_DOXYGEN_ONLY */

#endif /* T1_SCOPE_INTERFACE_H_ */
