/*********************************************************************************//*!
*   \file           T1_contInterface.h
*
*   \brief          T1.cont interface declarations and macros
*
*   \par Visibility
*                   External
*
*   \author alexandrebau
*
*   \version 2.5.5.0 r40234
*
*   \copyright GLIWA GmbH embedded systems, Weilheim i.OB. All rights reserved
*************************************************************************************/

#ifndef T1_CONT_INTERFACE_H_
#define T1_CONT_INTERFACE_H_ (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_baseInterface.h"
#include "T1_scopeInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_CONT_PLUGIN_ID       (5u)

#define T1_ENABLE_CPULOAD_CALC  (1)

#define T1_TASK_STACK_OVERRUNS  (4)

#if defined T1_ENABLE && !defined T1_DISABLE_T1_CONT
/*! \brief T1.cont entry in plugin table. */
#   define T1_contPlugin                    (&T1_contPluginStruct)
#else
#   if defined T1_CONT_REMOTE
#       error T1_CONT_REMOTE while T1.cont is disabled via T1_DISABLE_T1_CONT
#   endif
#   define T1_contPlugin                    (T1_DISABLED_PLUGIN)
#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_CONT */

#define T1_PERCENT_TO_256THS( percent_ )    ((percent_) * 2.56f + 0.5f)

/*!
 * Compare CPU load of latest CPU load frame expressed as the fraction te_ / to_ with
 * the threshold CPU load expressed as the fraction cpuLoadThreshold_ / 256.
 * If cpuLoadThreshold_ is 255, this sentinel value represents no threshold, so that
 * zero is always returned.
 * Return zero if and only if the load is below the threshold without using division,
 * which might be computationally expensive for smaller processors.
 * \param[in] to_               overall time for the CPU load frame
 * \param[in] te_               execution time of tasks/ISRs within the CPU load frame
 * \param[in] cpuLoadThreshold_ configured CPU load threshold
 * \returns   zero if and only if te_ / to_ < cpuLoadThreshold_ / 256
 */
#define T1_CONT_CPU_OVERLOAD( to_, te_, cpuLoadThreshold_ )                 \
(                                                                           \
    ( (cpuLoadThreshold_) != 255u )                                         \
    && ( (((cpuLoadThreshold_) * (T1_uint32_t)(to_)) >> 8) < (te_) )        \
)

/* Return non-zero if and only if num1_/den1_ < num2_/den2_, for 16-bit values. */
#define FRACTIONS_LESS_THAN_16BIT( num1_, den1_, num2_, den2_ )             \
    ( (T1_uint32_t)(num1_) * (den2_) < (T1_uint32_t)(num2_) * (den1_) )

#if defined T1_CONT_DIRECT_ID_MAPPINGS
#   define T1_BACKGROUND_TASK_IDX_CORE0     (T1_BACKGROUND_TASK_ID_CORE0)
#   define T1_BACKGROUND_TASK_IDX_CORE1     (T1_BACKGROUND_TASK_ID_CORE1)
#   define T1_BACKGROUND_TASK_IDX_CORE2     (T1_BACKGROUND_TASK_ID_CORE2)
#   define T1_BACKGROUND_TASK_IDX_CORE3     (T1_BACKGROUND_TASK_ID_CORE3)
#   define T1_BACKGROUND_TASK_IDX_CORE4     (T1_BACKGROUND_TASK_ID_CORE4)
#   define T1_BACKGROUND_TASK_IDX_CORE5     (T1_BACKGROUND_TASK_ID_CORE5)
#   define T1_BACKGROUND_TASK_IDX_CORE6     (T1_BACKGROUND_TASK_ID_CORE6)
#   define T1_BACKGROUND_TASK_IDX_CORE7     (T1_BACKGROUND_TASK_ID_CORE7)
#   define T1_BACKGROUND_TASK_IDX_CORE8     (T1_BACKGROUND_TASK_ID_CORE8)
#   define T1_BACKGROUND_TASK_IDX_CORE9     (T1_BACKGROUND_TASK_ID_CORE9)
#   define T1_BACKGROUND_TASK_IDX_CORE10    (T1_BACKGROUND_TASK_ID_CORE10)
#   define T1_BACKGROUND_TASK_IDX_CORE11    (T1_BACKGROUND_TASK_ID_CORE11)
#   define T1_BACKGROUND_TASK_IDX_CORE12    (T1_BACKGROUND_TASK_ID_CORE12)
#   define T1_BACKGROUND_TASK_IDX_CORE13    (T1_BACKGROUND_TASK_ID_CORE13)
#   define T1_BACKGROUND_TASK_IDX_CORE14    (T1_BACKGROUND_TASK_ID_CORE14)
#endif /* defined T1_CONT_DIRECT_ID_MAPPINGS */

/*---------------------- bits of variable T1_contBgStatus --------------------------*/
/* the lowest bit indicates information ("INF") */
/*! \brief T1.cont overheads have been updated after calibration, see T1_CONT_CALIBRATE_OVERHEADS_PC(). */
#define T1_INF_OVERHEADS_UPDATED            ((T1_contStatus_t)1<<0)
/* the lower bits indicate warnings ("WRN") */
/*! \brief Not every traced event has been read by T1.cont. */
#define T1_WRN_INCOMPLETE_ANALYSIS          ((T1_contStatus_t)1<<1)
/*! \brief At least one T1.cont constraint has been violated. */
#define T1_WRN_CONSTRAINT_VIOLATED          ((T1_contStatus_t)1<<2)
/*! \brief A CET stopwatch stopped in a different task or task instance. */
#define T1_WRN_INVALID_CET_STPW             ((T1_contStatus_t)1<<3)
/*! \brief T1.cont result out-of-range, sometimes an underflow after subtracting incorrect overheads. */
#define T1_WRN_RESULT_OUT_OF_RANGE          ((T1_contStatus_t)1<<4)
/* the higher bits indicate errors ("ERR") */
/*! \brief The traced events read by T1.cont are not valid. */
#define T1_ERR_FAULTY_TRACE_DATA            ((T1_contStatus_t)1<<5)
/*! \brief Too much pre-emption, or unbalanced task start/stop events. */
#define T1_ERR_STACK_OVERFLOW               ((T1_contStatus_t)1<<6)
/*! \brief T1.cont is unable to keep up with T1.scope. */
#define T1_ERR_OVERRUN                      ((T1_contStatus_t)1<<7)

/*---------------------- bits of variable T1_contHandlerStatus ---------------------*/
/* the lower bits indicate warnings ("WRN") */
/*! \brief The T1.cont analysis has been stopped. */
#define T1_WRN_ANALYSIS_STOPPED             ((T1_contStatus_t)1<<0)
/* the upper bits give status information */
/*! \brief The T1.cont 4th focus measurement is running. */
#define T1_MODE_FOCUS_RUNNING_3             ((T1_contStatus_t)1<<1)
/*! \brief The T1.cont 3rd focus measurement is running. */
#define T1_MODE_FOCUS_RUNNING_2             ((T1_contStatus_t)1<<2)
/*! \brief The T1.cont 2nd focus measurement is running. */
#define T1_MODE_FOCUS_RUNNING_1             ((T1_contStatus_t)1<<3)
/*! \brief The T1.cont 1st focus measurement is running. */
#define T1_MODE_FOCUS_RUNNING_0             ((T1_contStatus_t)1<<4)
/*! \brief T1.cont constraints are enabled. */
#define T1_MODE_CONSTRAINTS_ENABLED         ((T1_contStatus_t)1<<5)
/*! \brief New T1.cont results are transmitted as soon as they are calcuated. */
#define T1_MODE_TRANSMISSION_ENABLED        ((T1_contStatus_t)1<<6)
/*! \brief T1.cont analysis is enabled. */
#define T1_MODE_ANALYSIS_ENABLED            ((T1_contStatus_t)1<<7)
/*
 * T1_MODE_FOCUS_RUNNING is excluded from T1_MODES_BITMASK because it is set and
 * cleared indirectly through the focus protocol.
 */
#define T1_MODES_BITMASK ((T1_contStatus_t)(T1_MODE_CONSTRAINTS_ENABLED  |  \
                                            T1_MODE_TRANSMISSION_ENABLED |  \
                                            T1_MODE_ANALYSIS_ENABLED))
/*----------------------------------------------------------------------------------*/

/* bits for constraint configuration */
#define T1_CSRN_MAX                 (1u)
#define T1_CSRN_MIN                 (2u)
#define T1_STOPTRIGGER              (T1_STOPTRIGGER_DEPRECATED)
#define T1_CALLBACK                 (T1_CALLBACK_DEPRECATED)
#define T1_MESSAGE                  (T1_MESSAGE_DEPRECATED)
#define T1_CSRN_UNDEF               (T1_CSRN_UNDEF_DEPRECATED)

#define T1_INVALID_TASK_IDX         ((T1_taskIdx_t)-1)
#define T1_INVALID_TASK_ID          T1_INVALID_TASK_IDX
#define T1_INVALID_RESULT_IDX       ((T1_resultsIdx_t)-1)

#define T1_INVALID_STPW_IDX         ((T1_stpwIdx_t)-1)

#define T1_STOPWATCH_ID_FOR_T1_FLEX (&T1_undefined)

#define T1_CONT_STPW_GET            (0u)    //!< Last start to first stop
#define T1_CONT_STPW_DATA_AGE       (1u)    //!< Last start to last stop
#define T1_CONT_STPW_CET            (2u)    //!< Last start to first stop in same task instance
#define T1_CONT_STPW_NPC            (3u)    //!< Last start to first stop with no preemptions
#define T1_CONT_STPW_REENTRANT0     (4u)    //!< Used for nesting
#define T1_CONT_STPW_REENTRANT1     (5u)    //!< Used for nesting
#define T1_CONT_STPW_REENTRANT2     (6u)    //!< Used for nesting
#define T1_CONT_STPW_REENTRANT3     (7u)    //!< Used for nesting
#define T1_CONT_STPW_REENTRANT4     (8u)    //!< Used for nesting
#define T1_CONT_STPW_REENTRANT5     (9u)    //!< Used for nesting
#define T1_CONT_STPW_REENTRANT6     (10u)   //!< Used for nesting
#define T1_CONT_STPW_REENTRANT7     (11u)   //!< Used for nesting
#define T1_CONT_STPW_INVALID_CFG    (255u)

#define T1_CONT_STPW_IS_CET( cfg_ )         ( T1_CONT_STPW_CET <= (cfg_) )

/* See T1_stpwConfig_t */
#ifdef T1_CONT_DIRECT_ID_MAPPINGS
#   define T1_CONT_CET_STOPWATCH( id_ )         { T1_CONT_STPW_CET, 0u }            //!< Configure CET for the given stopwatch ID
#   define T1_CONT_NPC_STOPWATCH( id_ )         { T1_CONT_STPW_NPC, 0u }            //!< Deprecated
#   define T1_CONT_GET_STOPWATCH( id_ )         { T1_CONT_STPW_GET, 0u }            //!< Configure CET for the given stopwatch ID
#   define T1_CONT_DATA_AGE_STOPWATCH( id_ )    { T1_CONT_STPW_DATA_AGE, 0u }       //!< Configure data age for the given stopwatch ID
#   define T1_CONT_REENTRANT0_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT0, 0u }     //!< Not supported
#   define T1_CONT_REENTRANT1_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT1, 0u }     //!< Not supported
#   define T1_CONT_REENTRANT2_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT2, 0u }     //!< Not supported
#   define T1_CONT_REENTRANT3_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT3, 0u }     //!< Not supported
#   define T1_CONT_REENTRANT4_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT4, 0u }     //!< Not supported
#   define T1_CONT_REENTRANT5_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT5, 0u }     //!< Not supported
#   define T1_CONT_REENTRANT6_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT6, 0u }     //!< Not supported
#   define T1_CONT_REENTRANT7_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT7, 0u }     //!< Not supported
#else /* !T1_CONT_DIRECT_ID_MAPPINGS */
#   define T1_CONT_CET_STOPWATCH( id_ )         { T1_CONT_STPW_CET, (id_) }         //!< Configure CET for the given stopwatch ID
#   define T1_CONT_NPC_STOPWATCH( id_ )         { T1_CONT_STPW_NPC, (id_) }         //!< Deprecated
#   define T1_CONT_GET_STOPWATCH( id_ )         { T1_CONT_STPW_GET, (id_) }         //!< Configure CET for the given stopwatch ID
#   define T1_CONT_DATA_AGE_STOPWATCH( id_ )    { T1_CONT_STPW_DATA_AGE, (id_) }    //!< Configure data age for the given stopwatch ID
#   define T1_CONT_REENTRANT0_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT0, (id_) }  //!< Not supported
#   define T1_CONT_REENTRANT1_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT1, (id_) }  //!< Not supported
#   define T1_CONT_REENTRANT2_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT2, (id_) }  //!< Not supported
#   define T1_CONT_REENTRANT3_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT3, (id_) }  //!< Not supported
#   define T1_CONT_REENTRANT4_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT4, (id_) }  //!< Not supported
#   define T1_CONT_REENTRANT5_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT5, (id_) }  //!< Not supported
#   define T1_CONT_REENTRANT6_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT6, (id_) }  //!< Not supported
#   define T1_CONT_REENTRANT7_STOPWATCH( id_ )  { T1_CONT_STPW_REENTRANT7, (id_) }  //!< Not supported
#endif /* T1_CONT_DIRECT_ID_MAPPINGS */

/*! \brief Convert a time in nanoseconds to core 0 trace timer ticks. */
#define T1_NS_TO_TICKS( ns_ )       T1_NS_TO_TICKS_CORE0( ns_ )
/*! \brief Convert a time in microseconds to core 0 trace timer ticks. */
#define T1_US_TO_TICKS( us_ )       T1_US_TO_TICKS_CORE0( us_ )
/*! \brief Convert a time in milliseconds to core 0 trace timer ticks. */
#define T1_MS_TO_TICKS( ms_ )       T1_MS_TO_TICKS_CORE0( ms_ )

#define T1_CONT_CONSTRAINT_TIME( ticks_, config_ )                              \
( ((config_) == T1_CSRN_MAX)                                                    \
  ? ((ticks_) & 0x7FFFFFFFuL)                                                   \
  : ( ((config_) == T1_CSRN_MIN) ? (((ticks_) + 1uL) | 0x80000000uL) : 0uL ) )

#define T1_STPW_IDX_CONSTRAINT( contStpwIdx_, ticks_, config_ )             \
{                                                                           \
    (T1_stpwIdx_t)(contStpwIdx_),                                           \
    0u, 0u,                                                                 \
    T1_CONT_CONSTRAINT_TIME( (T1_longTime_t)(ticks_), (config_) )           \
}
#define T1_TASK_IDX_CONSTRAINT( contTaskIdx_, ticks_, config_ )             \
{                                                                           \
    (T1_stpwIdx_t)(contStpwIdx_),                                           \
    1u, 0u,                                                                 \
    T1_CONT_CONSTRAINT_TIME( (T1_longTime_t)(ticks_), (config_) )           \
}
#define T1_CONT_INVALID_CONSTRAINT  { T1_INVALID_STPW_IDX, 0u, 0u, 0uL }

#ifndef T1_CONT_NOF_VRTL_STPWS
/*!
 * Either 8 or 64 event chains can be configured. The default is 8. To select 64 event
 * chains, define #T1_CONT_NOF_VRTL_STPWS to be 64 in T1_AppInterface.h before
 * including T1_contInterface.h.
 */
#   define T1_CONT_NOF_VRTL_STPWS   (8)
#endif

#if defined T1_ENABLE && !defined T1_DISABLE_T1_CONT

#   if defined T1_NOF_CORES
#       define T1_VSTPWS_IDX_BASE ( T1_nofStpwsPC[coreId__] - T1_CONT_NOF_VRTL_STPWS )
/*!
 * Calibrate T1.scope and T1.flex overheads as used by T1.cont.
 * Note that this could take around 100us, which might be undesirable during
 * intialization. Calibration can be postponed from initialization to a less
 * time-critical area, such as the background task. Any T1.cont results computed
 * before calibration are calculated using the overheads configured in the .inv
 * file(s).
 * See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical core ID of the calling core
 */
#       define T1_CONT_CALIBRATE_OVERHEADS_PC( coreId_ )                            \
do                                                                                  \
{                                                                                   \
    const T1_uint8Least_t coreId__ = (coreId_);                                     \
    T1_ConfigEventChainPC(  coreId__,                                               \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_STOP_START,        \
                                                    T1_OH_SW ),                     \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_STOP_START,        \
                                                    T1_OH_SW ),                     \
                            T1_VSTPWS_IDX_BASE + 3 );                               \
    T1_ConfigEventChainPC(  coreId__,                                               \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_START,             \
                                                    T1_OH_SW - 1 ),                 \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_STOP,              \
                                                    T1_OH_SW - 1 ),                 \
                            T1_VSTPWS_IDX_BASE + 5 );                               \
    T1_ConfigEventChainPC(  coreId__,                                               \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_START,             \
                                                    T1_OH_SW - 2 ),                 \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_STOP,              \
                                                    T1_OH_SW - 2 ),                 \
                            T1_VSTPWS_IDX_BASE + 7 );                               \
    T1_ScopeOverheadSequencePC( coreId__, T1_FALSE );                               \
    T1_SuspendAllInterruptsPC( coreId__ );                                          \
    (void)T1_TraceEventNoSuspPC( coreId__, T1_EMPTY, T1_CONT_UPDATE_OH );           \
    T1_ResumeAllInterruptsPC( coreId__ );                                           \
}                                                                                   \
while( 0 )
/*!
 * Calibrate T1.scope and T1.flex overheads as used by T1.cont.
 * Note that this could take around 100us, which might be undesirable during
 * intialization. Calibration can be postponed from initialization to a less
 * time-critical area, such as the background task. Any T1.cont results computed
 * before calibration are calculated using the overheads configured in the .inv
 * file(s).
 * \param[in] coreId_ the T1 logical core ID of the calling core
 * See \ref PC and \ref INTRPT.
 */
#       define T1_CONT_CALIBRATE_OVERHEADS_NOSUSP_PC( coreId_ )                     \
do                                                                                  \
{                                                                                   \
    const T1_uint8Least_t coreId__ = (coreId_);                                     \
    T1_ConfigEventChainPC(  coreId__,                                               \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_STOP_START,        \
                                                    T1_OH_SW ),                     \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_STOP_START,        \
                                                    T1_OH_SW ),                     \
                            T1_VSTPWS_IDX_BASE + 3 );                               \
    T1_ConfigEventChainPC(  coreId__,                                               \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_START,             \
                                                    T1_OH_SW - 1 ),                 \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_STOP,              \
                                                    T1_OH_SW - 1 ),                 \
                            T1_VSTPWS_IDX_BASE + 5 );                               \
    T1_ConfigEventChainPC(  coreId__,                                               \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_START,             \
                                                    T1_OH_SW - 2 ),                 \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_STOP,              \
                                                    T1_OH_SW - 2 ),                 \
                            T1_VSTPWS_IDX_BASE + 7 );                               \
    T1_ScopeOverheadSequencePC( coreId__, T1_TRUE );                                \
    (void)T1_TraceEventNoSuspPC( coreId__, T1_EMPTY, T1_CONT_UPDATE_OH );           \
}                                                                                   \
while( 0 )
/*!
 * Free T1.cont event chains used for calibration. See \ref PC.
 * \param[in] coreId_ the T1 logical core ID of the calling core
 */
#       define T1_CONT_STOP_CALIBRATION_PC( coreId_ )                               \
do                                                                                  \
{                                                                                   \
    const T1_uint8Least_t coreId__ = (coreId_);                                     \
    T1_DeleteCalibrationEventChainPC( coreId__, T1_VSTPWS_IDX_BASE + 3 );           \
    T1_DeleteCalibrationEventChainPC( coreId__, T1_VSTPWS_IDX_BASE + 5 );           \
    T1_DeleteCalibrationEventChainPC( coreId__, T1_VSTPWS_IDX_BASE + 7 );           \
}                                                                                   \
while( 0 )
#   else /* single core */
#       define T1_VSTPWS_IDX_BASE ( T1_nofStpws - T1_CONT_NOF_VRTL_STPWS )
/*!
 * Calibrate T1.scope and T1.flex overheads as used by T1.cont.
 * Note that this could take around 100us, which might be undesirable during
 * intialization. Calibration can be postponed from initialization to a less
 * time-critical area, such as the background task. Any T1.cont results computed
 * before calibration are calculated using the overheads configured in the *.inv
 * file(s).
 * See \ref PC and \ref INTRPT.
 */
#       define T1_CONT_CALIBRATE_OVERHEADS( )                                       \
do                                                                                  \
{                                                                                   \
    T1_ConfigEventChain(    T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_STOP_START,        \
                                                    T1_OH_SW ),                     \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_STOP_START,        \
                                                    T1_OH_SW ),                     \
                            T1_VSTPWS_IDX_BASE + 3 );                               \
    T1_ConfigEventChain(    T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_START,             \
                                                    T1_OH_SW - 1 ),                 \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_STOP,              \
                                                    T1_OH_SW - 1 ),                 \
                            T1_VSTPWS_IDX_BASE + 5 );                               \
    T1_ConfigEventChain(    T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_START,             \
                                                    T1_OH_SW - 2 ),                 \
                            T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_STOP,              \
                                                    T1_OH_SW - 2 ),                 \
                            T1_VSTPWS_IDX_BASE + 7 );                               \
    T1_ScopeOverheadSequence( T1_FALSE );                                           \
    T1_SuspendAllInterrupts( );                                                     \
    T1_TraceEventNoSusp( T1_EMPTY, T1_CONT_UPDATE_OH );                             \
    T1_ResumeAllInterrupts( );                                                      \
}                                                                                   \
while( 0 )
/*!
 * Calibrate T1.scope and T1.flex overheads as used by T1.cont.
 * Note that this could take around 100us, which might be undesirable during
 * intialization. Calibration can be postponed from initialization to a less
 * time-critical area, such as the background task. Any T1.cont results computed
 * before calibration are calculated using the overheads configured in the .inv
 * file(s).
 * See \ref PC and \ref INTRPT.
 */
#       define T1_CONT_CALIBRATE_OVERHEADS_NOSUSP( )                                \
do                                                                                  \
{                                                                                   \
    T1_ConfigEventChain(    T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_STOP_START,        \
                                                    T1_OH_SW ),                     \
                            T1_COMBINE_EVENT_INFO( T1_STOPWATCH_STOP_START,         \
                                                   T1_OH_SW ),                      \
                            T1_VSTPWS_IDX_BASE + 3 );                               \
    T1_ConfigEventChain(    T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_START,             \
                                                    T1_OH_SW - 1 ),                 \
                            T1_COMBINE_EVENT_INFO( T1_STOPWATCH_STOP,               \
                                                   T1_OH_SW - 1 ),                  \
                            T1_VSTPWS_IDX_BASE + 5 );                               \
    T1_ConfigEventChain(    T1_COMBINE_EVENT_INFO(  T1_STOPWATCH_START,             \
                                                    T1_OH_SW - 2 ),                 \
                            T1_COMBINE_EVENT_INFO( T1_STOPWATCH_STOP,               \
                                                   T1_OH_SW - 2 ),                  \
                            T1_VSTPWS_IDX_BASE + 7 );                               \
    T1_ScopeOverheadSequence( T1_TRUE );                                            \
    T1_TraceEventNoSusp( T1_EMPTY, T1_CONT_UPDATE_OH );                             \
}                                                                                   \
while( 0 )
/*! Free T1.cont event chains used for calibration. See \ref PC. */
#       define T1_CONT_STOP_CALIBRATION( )                                          \
do                                                                                  \
{                                                                                   \
    T1_DeleteCalibrationEventChain( T1_VSTPWS_IDX_BASE + 3 );                       \
    T1_DeleteCalibrationEventChain( T1_VSTPWS_IDX_BASE + 5 );                       \
    T1_DeleteCalibrationEventChain( T1_VSTPWS_IDX_BASE + 7 );                       \
}                                                                                   \
while( 0 )
#       define T1_CONT_CALIBRATE_OVERHEADS_PC( coreId_ )                            \
            T1_CONT_CALIBRATE_OVERHEADS( )
#       define T1_CONT_CALIBRATE_OVERHEADS_NOSUSP_PC( coreId_ )                     \
            T1_CONT_CALIBRATE_OVERHEADS_NOSUSP( )
#       define T1_CONT_STOP_CALIBRATION_PC( coreId_ )                               \
            T1_CONT_STOP_CALIBRATION( )
#   endif /* T1_NOF_CORES */

#else /* T1.cont is disabled */

#   define T1_CONT_CALIBRATE_OVERHEADS_PC( coreId_ )        ( (void)0 )
#   define T1_CONT_CALIBRATE_OVERHEADS_NOSUSP_PC( coreId_ ) ( (void)0 )
#   define T1_CONT_STOP_CALIBRATION_PC( coreId_ )           ( (void)0 )
#   define T1_CONT_CALIBRATE_OVERHEADS( )                   ( (void)0 )
#   define T1_CONT_CALIBRATE_OVERHEADS_NOSUSP( )            ( (void)0 )
#   define T1_CONT_STOP_CALIBRATION( )                      ( (void)0 )

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_CONT */


/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

typedef unsigned long   T1_resultMask_t;
/*!
 * \brief T1.scope task identifier. When #T1_CONT_DIRECT_ID_MAPPINGS is defined, this
 * is equal to the T1.cont task index, T1_taskIdx_t.
 */
typedef unsigned short  T1_taskId_t;
/*!
 * \brief T1.cont task index. When #T1_CONT_DIRECT_ID_MAPPINGS is defined, this is
 * equal to the T1.scope task identifier, T1_taskId_t.
 */
typedef unsigned char   T1_taskIdx_t;
/*!
 * \brief T1.scope stopwatch identifier. When #T1_CONT_DIRECT_ID_MAPPINGS is defined,
 * this is equal to the T1.cont stopwatch index, T1_stpwIdx_t.
 */
typedef unsigned short  T1_stpwId_t;
/*!
 * \brief T1.cont stopwatch index. When #T1_CONT_DIRECT_ID_MAPPINGS is defined, this
 * is equal to the T1.scope stopwatch identifier, T1_stpwId_t.
 */
typedef unsigned char   T1_stpwIdx_t;
/*! \brief T1.cont constraint index. */
typedef unsigned char   T1_csrnIdx_t;
/*! \brief T1.cont result index. */
typedef unsigned short  T1_resultsIdx_t;
/*! \brief Type for T1_contGlobals_t#analysisCapacity_. */
typedef unsigned short  T1_anaCapa_t;
/*! \brief Type for both #T1_contBgStatus and #T1_contHandlerStatus. */
typedef T1_uint8_t      T1_contStatus_t;    /* Two different single-byte values */
/*! \brief 32-bit type for time calculations. */
typedef T1_uint32_t     T1_longTime_t;
typedef T1_uint8_t      T1_resultKind_t;
/*! \brief Type for 31-bit T1.cont result and 1-bit flag. */
typedef T1_uint32_t     T1_resultTime_t;
/*----------------------------------------------------------------------------------*/
typedef const struct
{
    T1_uint8_t          configInit;         //!< for example T1_CONT_STPW_GET
    T1_stpwId_t         id;                 //!< T1.scope stopwatch identifier
} T1_stpwConfig_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Used only for tasks that enter the WAITING state. */
typedef struct
{
    T1_uint8_t          taskInstance;       //!< Waiting instance
#if defined T1_CPU16BIT
    T1_uint8_t          unused8;            /* Force alignment */
#   if defined T1_CPU32BIT
    T1_uint16_t         unused16;           /* Force alignment */
#   endif /* definedT1_CPU32BIT */
#endif /* defined T1_CPU16BIT */
    T1_resultTime_t     netAccumulation;    //!< Net time before waiting
}
T1_taskData_t;
/*----------------------------------------------------------------------------------*/
typedef struct
{
    /* Convert task net to stopwatch net or absolute to stopwatch gross. */
    T1_resultTime_t     netConversionOrStartTime;
    T1_uint8_t          config;             /* See T1_stpwConfig_t */
    /* If the startTaskInstKey is zero, the stopwatch is not running. */
    T1_uint8_t          startTaskInstKey;   /* The instance of the starting task */
    /*
     * High two bits of constraintFocusIdx are focus, low 6 bits are constraint index
     * Focus: 3 => focus disabled, 0..2 => focus enabled for focus index 0..2
     */
    T1_csrnIdx_t        constraintFocusIdx;/* Constraint or focus index for result */
    T1_uint8_t          reentrantCount;     /* Count times reentered */
} T1_stpwData_t;
/*----------------------------------------------------------------------------------*/
typedef struct
{
    /* REVIEWNOTE: T1_stpwIdx_t is used as a T1_taskIdx_t if a task constraint */
    T1_stpwIdx_t        stpwOrTaskIdx;    /* T1_INVALID_STPW_IDX for unused constraint */
    T1_bool_t           isTaskConstraint;   /* False for an unused constraint */
#if defined T1_CPU32BIT
    T1_uint16_t         unused16;           /* Force alignment */
#endif /* definedT1_CPU32BIT */
    T1_longTime_t       threshold;
    /*
     * Threshold is a 32-bit value.
     * If the MSB is set, the value must be GREATER THAN this threshold.
     * If the MSB is clear, the value must be LESS THAN this threshold.
     */
} T1_csrnData_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Running and pre-empted tasks are recorded on the T1.cont task stack. */
typedef struct {
    T1_taskIdx_t        idx;                //!< T1.cont task index
    T1_uint8_t          instanceKey;        //!< Distinguish task instances
#if defined T1_CPU32BIT
    T1_uint16_t         unused16;           /* Force alignment */
#endif /* defined T1_CPU32BIT */
    T1_resultTime_t     netAccumulation;    //!< Accumulated net time for this task
} T1_taskStackElem_t;
/*----------------------------------------------------------------------------------*/
typedef struct {
    T1_uint16_t         eventInfoIn;
    T1_uint8_t          eventOut;
    T1_stpwIdx_t        stpwIdx;
} T1_vStpwMapping_t;
/*----------------------------------------------------------------------------------*/
typedef T1_uint32_t T1_txState_t;
/*----------------------------------------------------------------------------------*/
typedef union {
    struct {
        union {
            struct {
                T1_uint8_t      taskInstKey;
                T1_uint8_t      controllingStpwIdx;
            } d;
            T1_uint16_t         copy;
        } u;
        T1_uint8_t              controlledVStpwIdx;
        T1_bool_t               isStarted;
    } d;
    T1_uint32_t                 clear;
} T1_csVStpwCache_t;
/*----------------------------------------------------------------------------------*/
/*! \brief T1.cont global data for one focus measurement. */
typedef struct {
    T1_uint32_t                 focusEventCount_;
    T1_uint32_t                 focusEventMax_;
    T1_resultTime_t             focusLastTime_;
    T1_resultTime_t             focusTotalLow_;
    T1_resultTime_t             focusIntervalLow_;
    union {
        T1_uint32_t             both;
        struct {
            T1_uint16_t         total;
            T1_uint16_t         interval;
        }                       parts;
    }                           focusHighs_;
    T1_stpwIdx_t                focusStpwIdx_;
    T1_bool_t                   focusRunning_;  /* Non-zero between start and stop */
#if defined T1_CPU32BIT
    T1_uint16_t                 unused16;       /* Force alignment */
#endif /* definedT1_CPU32BIT */
} T1_focusData_t;
/*----------------------------------------------------------------------------------*/
/*! \brief T1.cont global data for one core. */
typedef struct
{
    T1_traceEntry_t const T1_FARPTR pContRd_;       //!< T1.cont trace buffer read pointer
    T1_longTime_t               now_;
    T1_resultTime_t             netTaskAccumulation_; /* No init required because background task has no CET */
    T1_tick_t                   lastEventTime_;
    T1_uint8_t                  contWrapCntr_;      //!< Used for overrun detection
    T1_uint8_t                  taskInstanceKey_;
    /* Offset 16 */
    /*
     * taskStack is a stack that reflects the preemption hirachy. The topmost (last)
     * task on the stack is the one currently running, as far as the T1.cont
     * interpretation is concerned.
     */
    T1_taskStackElem_t         *pTopOfTaskStack_;
    T1_uint16_t                 startOfFrameEvent_;
    T1_taskIdx_t                bgTaskIdx_;         //!< T1.cont task index of task to exclude from CPU load.
    T1_stpwIdx_t                nOfUserStpws_;      /* Cached in RAM for fast access. */
    T1_anaCapa_t                analysisCapacity_;  //!< One call to T1_ContBgHandler() reads at most this number of events.
    T1_tick_t                   flexOverhead_;      //!< Currently active additional T1.flex overhead

    T1_tick_t                   overhead_;          //!< Currently active T1.scope overhead

    T1_stpwIdx_t                nOfNonVrtlStpws_;   /* Cached in RAM for fast access */
    T1_stpwIdx_t                nOfStpws_;          /* Cached in RAM for fast access */

    /* Offset 32 */
    T1_longTime_t               te_;
    T1_longTime_t               teFgMask_;
    T1_longTime_t               toTotal_;
    T1_longTime_t               teTotal_;
    /* Offset 48 */
    T1_taskStackElem_t         *pTaskStackOverrun_;
    T1_longTime_t               lastFrameEventTime_;
    union {
        T1_uint32_t             test;
        struct {
            volatile T1_uint8_t mask;
            T1_bool_t           T1ContResults;
            T1_bool_t           T1ContAnalysis;
        }                       parts;
    }                           reset_;
    T1_focusData_t             *pFocusData_;        //!< Array of focus states

    /* Offset 64 */
    T1_uint32_t                 focusTxEventCount_;
    T1_resultTime_t             focusTxTotalLow_;
    T1_resultTime_t             focusTxIntervalLow_;
    union {
        T1_uint32_t             both;
        struct {
            T1_uint16_t         total;
            T1_uint16_t         interval;
        }                       parts;
    }                           focusTxHighs_;

    /* Offset 80 */
    T1_stpwIdx_t                focusTxStpwIdx_;
    T1_uint8_t                  focusTxFocusIdx_;
    T1_uint8_t                  focusTxState_;
    T1_uint8_t                  coreId;         /* Unused for single core */

    T1_vStpwMapping_t          *pVStpws_;       /* cached T1_vStpw (address) */
    T1_vStpwMapping_t          *pVStpwStarts_;  /* upper half of T1_vStpw */
    void                      (*pDoVStpwAll_)( void );

    /* Offset 96 */

    T1_txState_t                contTxState_;
    T1_uint16_t                 msgFocusIdx_;   /* min 2 bytes for GCP */
    T1_resultsIdx_t             resetStpwAfterResultIdx_;

    T1_uint16_t                 vStpwNewStartEventInfo_;
    T1_uint16_t                 vStpwNewStopEventInfo_;
    T1_uint16_t                 vStpwNewStartStopIds_;

    T1_uint16_t                 txPos_;

    /* Offset 112 */
    T1_uint16_t                 discardCount_;
    T1_resultsIdx_t             searchIdx_;     /* No init required */

    T1_bool_t                   isFirstFrame_;  /* for CPU load */
    T1_bool_t                   scopeStoppedOrContDisabled_;
    T1_bool_t                   statusChanged_;
    T1_uint8_t                  newCfgForResetStpw_;

    T1_uint8_t                  ackForResetStpw_;
    T1_uint8_t                  txControlByte_;
    T1_taskIdx_t                resetResultsForTaskIdx_;
    T1_stpwIdx_t                resetResultsForStpwIdx_;

    /* Offset 128 */
    T1_stpwIdx_t                delayedResetStpwIdx_;
    T1_csrnIdx_t                nofActiveCsrns_;
    T1_uint8_t                  avgCPULoadCount_;
    /* Which background handler errors should cause a trigger. */
    T1_uint8_t                  triggerMask_;

    T1_csVStpwCache_t           pCsVStpwCache_[8];

#if defined T1_CPU32BIT
    T1_longTime_t               refTime_;
    T1_longTime_t               bgCallbackPeriod_;
#endif /* defined T1_CPU32BIT */
#if defined T1_NOF_CORES
    /* Required for multi-core adaptations of T1 */
    T1_traceBufferPos_t         bufferWrPos_;

    T1_traceEntry_t             lastUserDataMid_;
    T1_uint16_t                 crossCoreEventInfo_;
#else /* single core */
    /* Required also for single core adaptations of T1 */
    T1_uint8_t                  avgCPULoadSamples_;
    T1_uint8_t                  cpuLoadThreshold_;
    T1_bool_t                   inBgHandler_;
#endif /* defined T1_NOF_CORES */
    /* How much more of the buffer to fill after a callback trigger (0..128 128ths) */
    T1_uint8_t                  overloadTrigger128ths_;
    T1_uint8_t                  errorTrigger128ths_;
    T1_uint8_t                  constraintTrigger128ths_;
    T1_uint8_t                  unused8;    /* Force alignment */

} T1_contGlobals_t;
/*----------------------------------------------------------------------------------*/
/*! \brief T1.cont and T1.scope global data for one core. */
typedef struct
{
    T1_contGlobals_t            contGlobals;
#if defined T1_USE_SCOPE_GLOBALS_PARAM
    T1_scopeGlobals_t           scopeGlobals;
#endif /* defined T1_USE_SCOPE_GLOBALS_PARAM */
} T1_contScopeGlobals_t;

/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_CONT

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_DeclarePlugin( T1_contPluginStruct );
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   if defined T1_NOF_CORES && !defined T1_MULTICORE_CLONE
#       define T1_START_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE0 T1_contGlobals0;
#       define T1_STOP_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE1
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE1 T1_contGlobals1;
#       define T1_STOP_SEC_NO_INIT_32_CORE1
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE2
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE2 T1_contGlobals2;
#       define T1_STOP_SEC_NO_INIT_32_CORE2
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE3
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE3 T1_contGlobals3;
#       define T1_STOP_SEC_NO_INIT_32_CORE3
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE4
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE4 T1_contGlobals4;
#       define T1_STOP_SEC_NO_INIT_32_CORE4
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE5
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE5 T1_contGlobals5;
#       define T1_STOP_SEC_NO_INIT_32_CORE5
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE6
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE6 T1_contGlobals6;
#       define T1_STOP_SEC_NO_INIT_32_CORE6
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE7
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE7 T1_contGlobals7;
#       define T1_STOP_SEC_NO_INIT_32_CORE7
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE8
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE8 T1_contGlobals8;
#       define T1_STOP_SEC_NO_INIT_32_CORE8
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE9
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE9 T1_contGlobals9;
#       define T1_STOP_SEC_NO_INIT_32_CORE9
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE10
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE10 T1_contGlobals10;
#       define T1_STOP_SEC_NO_INIT_32_CORE10
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE11
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE11 T1_contGlobals11;
#       define T1_STOP_SEC_NO_INIT_32_CORE11
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE12
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE12 T1_contGlobals12;
#       define T1_STOP_SEC_NO_INIT_32_CORE12
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE13
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE13 T1_contGlobals13;
#       define T1_STOP_SEC_NO_INIT_32_CORE13
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE14
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t         T1_SEC_NO_INIT_32_CORE14 T1_contGlobals14;
#       define T1_STOP_SEC_NO_INIT_32_CORE14
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t * const T1_SEC_CONST_32 T1_contGlobalsPC[];
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#   elif defined T1_MULTICORE_CLONE
#       define T1_START_SEC_NO_INIT_32_CLONE
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t T1_SEC_NO_INIT_32_CLONE T1_contGlobals;
#       define T1_STOP_SEC_NO_INIT_32_CLONE
#       include "T1_MemMap.h"
#   else /* single core */
#       define T1_START_SEC_NO_INIT_32
#       include "T1_MemMap.h"
T1_EXTERN T1_contScopeGlobals_t T1_SEC_NO_INIT_32 T1_contGlobals;
#       define T1_STOP_SEC_NO_INIT_32
#       include "T1_MemMap.h"
#   endif /* T1_NOF_CORES */

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN const T1_longTime_t T1_SEC_CONST_32 T1_06960;
T1_EXTERN const T1_longTime_t T1_SEC_CONST_32 T1_38948[];
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

/* const data */
#   define T1_START_SEC_CONST_8
#   include "T1_MemMap.h"
T1_EXTERN const T1_taskIdx_t        T1_SEC_CONST_8 T1_bgTaskIdx;
T1_EXTERN const T1_taskIdx_t        T1_SEC_CONST_8 T1_bgTaskIdxPC[];
T1_EXTERN const T1_uint8_t          T1_SEC_CONST_8 T1_cpuLoadThreshold;
T1_EXTERN const T1_uint8_t          T1_SEC_CONST_8 T1_cpuLoadThresholdPC[];
T1_EXTERN const T1_uint8_t          T1_SEC_CONST_8 T1_avgCPULoadSamples;
T1_EXTERN const T1_uint8_t          T1_SEC_CONST_8 T1_avgCPULoadSamplesPC[];
T1_EXTERN const T1_uint8_t          T1_SEC_CONST_8 T1_nofPreemptionsPC[];
T1_EXTERN const T1_uint8_t          T1_SEC_CONST_8 T1_nofPreemptions;
T1_EXTERN const T1_taskIdx_t        T1_SEC_CONST_8 T1_nofTasksPC[];
T1_EXTERN const T1_taskIdx_t        T1_SEC_CONST_8 T1_nofTasks;
T1_EXTERN const T1_stpwIdx_t        T1_SEC_CONST_8 T1_nofStpwsPC[];
T1_EXTERN const T1_stpwIdx_t        T1_SEC_CONST_8 T1_nofStpws;
T1_EXTERN const T1_stpwIdx_t        T1_SEC_CONST_8 T1_nofUserStpwsPC[];
T1_EXTERN const T1_stpwIdx_t        T1_SEC_CONST_8 T1_nofUserStpws;
T1_EXTERN const T1_csrnIdx_t        T1_SEC_CONST_8 T1_nofCsrnsPC[];
T1_EXTERN const T1_csrnIdx_t        T1_SEC_CONST_8 T1_nofCsrns;
T1_EXTERN T1_stpwConfig_t           T1_SEC_CONST_8 T1_stpwConfig[];
T1_EXTERN const T1_uint8_t          T1_SEC_CONST_8 T1_nOfVrtlStpws;
T1_EXTERN const T1_uint8_t          T1_SEC_CONST_8 T1_nofFocusMeasurements;
#   define T1_STOP_SEC_CONST_8
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_16
#   include "T1_MemMap.h"
#   if ! defined T1_32BIT_TRACE_TIME
T1_EXTERN const T1_tick_t           T1_SEC_CONST_16 T1_overhead;
T1_EXTERN const T1_tick_t           T1_SEC_CONST_16 T1_flexOverhead;
#   endif /* defined T1_32BIT_TRACE_TIME */
#   define T1_STOP_SEC_CONST_16
#   include "T1_MemMap.h"
#   define T1_START_SEC_CONST_16
#   include "T1_MemMap.h"
#   if ! defined T1_32BIT_TRACE_TIME
T1_EXTERN const T1_tick_t           T1_SEC_CONST_16 T1_overheadPC[];
T1_EXTERN const T1_tick_t           T1_SEC_CONST_16 T1_flexOverheadPC[];
#   endif /* defined T1_32BIT_TRACE_TIME */
T1_EXTERN const T1_uint16_t         T1_SEC_CONST_16 T1_cpuLoadTxPeriod;
T1_EXTERN const T1_uint16_t         T1_SEC_CONST_16 T1_startOfFrameEvent;
T1_EXTERN const T1_uint16_t         T1_SEC_CONST_16 T1_startOfFrameEventPC[];
T1_EXTERN const T1_uint16_t         T1_SEC_CONST_16 T1_cpuLoadTxPeriodPC[];
/*! Initializer for T1_contGlobals_t#analysisCapacity_. */
T1_EXTERN const T1_anaCapa_t        T1_SEC_CONST_16 T1_defaultAnalysisCapacity;
/*! For each core, the initializer for T1_contGlobals_t#analysisCapacity_. */
T1_EXTERN const T1_anaCapa_t        T1_SEC_CONST_16 T1_defaultAnalysisCapacityPC[];
T1_EXTERN const T1_resultsIdx_t     T1_SEC_CONST_16 T1_nofResultsPC[];
T1_EXTERN const T1_resultsIdx_t     T1_SEC_CONST_16 T1_nofResults;
#   define T1_STOP_SEC_CONST_16
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN const T1_csrnData_t       T1_SEC_CONST_32 T1_csrnConfig[];
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"
#   if defined T1_NOF_CORES
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_EXTERN T1_stpwConfig_t   * const T1_SEC_CONST_32 T1_stpwConfigPC[];
T1_EXTERN const T1_csrnData_t * const T1_SEC_CONST_32 T1_csrnConfigPC[];
T1_EXTERN T1_taskData_t     * const T1_SEC_CONST_32 T1_taskDataPC[];
/* polyspace<MISRA-C3:5.4: Not a defect:Justified> AUTOSAR MemMap concept requires repeated definition of the same identifier */
T1_EXTERN T1_stpwData_t     * const T1_SEC_CONST_32 T1_stpwDataPC[];
/* polyspace<MISRA-C3:5.4: Not a defect:Justified> AUTOSAR MemMap concept requires repeated definition of the same identifier */
T1_EXTERN T1_csrnData_t     * const T1_SEC_CONST_32 T1_csrnDataPC[];
/*!
 * \var T1_resultBufferPC
 * For each core, a pointer to the T1.cont result buffer.
 */
T1_EXTERN T1_resultTime_t   * const T1_SEC_CONST_32 T1_resultBufferPC[];
T1_EXTERN T1_taskStackElem_t* const T1_SEC_CONST_32 T1_taskStackPC[];
T1_EXTERN T1_vStpwMapping_t * const T1_SEC_CONST_32 T1_vStpwPC[];
T1_EXTERN T1_focusData_t    * const T1_SEC_CONST_32 T1_focusPC[];
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#endif /* defined T1_NOF_CORES */
#   if defined T1_32BIT_TRACE_TIME
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_EXTERN const T1_tick_t           T1_SEC_CONST_32 T1_overhead;
T1_EXTERN const T1_tick_t           T1_SEC_CONST_32 T1_flexOverhead;
T1_EXTERN const T1_tick_t           T1_SEC_CONST_32 T1_overheadPC[];
T1_EXTERN const T1_tick_t           T1_SEC_CONST_32 T1_flexOverheadPC[];
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#   endif /* defined T1_32BIT_TRACE_TIME */

/* Public for debugger interface */
#   define T1_START_SEC_NO_INIT_8
#   include "T1_MemMap.h"
/*!
 * \var T1_contBgStatusPC
 * \brief For each core, the T1_ContBgHandler T1.cont status.
 */
T1_EXTERN T1_contStatus_t          T1_SEC_NO_INIT_8 T1_contBgStatusPC[];
/*!
 * \var T1_contHandlerStatusPC
 * For each core, the T1_Handler T1.cont status.
 */
T1_EXTERN T1_contStatus_t          T1_SEC_NO_INIT_8 T1_contHandlerStatusPC[];
#   define T1_STOP_SEC_NO_INIT_8
#   include "T1_MemMap.h"

#   ifdef T1_MULTICORE_CLONE
#       define T1_START_SEC_NO_INIT_8_CLONE
#       include "T1_MemMap.h"
/*!
 * \var T1_contBgStatusPC
 * \brief For each core, the T1_ContBgHandler T1.cont status.
 */
T1_EXTERN T1_contStatus_t          T1_SEC_NO_INIT_8_CLONE T1_contBgStatus;
/*!
 * \var T1_contHandlerStatusPC
 * For each core, the T1_Handler T1.cont status.
 */
T1_EXTERN T1_contStatus_t          T1_SEC_NO_INIT_8_CLONE T1_contHandlerStatus;
#       define T1_STOP_SEC_NO_INIT_8_CLONE
#       include "T1_MemMap.h"
#   else /* !T1_MULTICORE_CLONE */
#       define T1_START_SEC_NO_INIT_8
#       include "T1_MemMap.h"
/*!
 * \var T1_contBgStatus
 * \brief The T1_ContBgHandler T1.cont status.
 */
T1_EXTERN T1_contStatus_t          T1_SEC_NO_INIT_8 T1_contBgStatus;
/*!
 * \var T1_contHandlerStatus
 * The T1_Handler T1.cont status.
 */
T1_EXTERN T1_contStatus_t          T1_SEC_NO_INIT_8 T1_contHandlerStatus;
#       define T1_STOP_SEC_NO_INIT_8
#       include "T1_MemMap.h"
#   endif /* T1_MULTICORE_CLONE */

#   define T1_START_SEC_NO_INIT_32
#   include "T1_MemMap.h"
T1_EXTERN T1_taskData_t             T1_SEC_NO_INIT_32 T1_taskData[];
T1_EXTERN T1_stpwData_t             T1_SEC_NO_INIT_32 T1_stpwData[];
T1_EXTERN T1_csrnData_t             T1_SEC_NO_INIT_32 T1_csrnData[];
/*!
 * \var T1_resultBuffer
 * The T1.cont result buffer.
 */
T1_EXTERN T1_resultTime_t           T1_SEC_NO_INIT_32 T1_resultBuffer[];
T1_EXTERN T1_taskStackElem_t        T1_SEC_NO_INIT_32 T1_taskStack[];
T1_EXTERN T1_vStpwMapping_t         T1_SEC_NO_INIT_32 T1_vStpw[];
T1_EXTERN T1_focusData_t            T1_SEC_NO_INIT_32 T1_focus[];
#   define T1_STOP_SEC_NO_INIT_32
#   include "T1_MemMap.h"

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_CONT */

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for global functions ------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*!
 * \def T1_ContBgHandler
 * T1.cont background handler. Runs either in background or at a priority no
 * greater than T1_Handler(). See \ref PC and \ref INTRPT and #T1_contBgStatus and
 * T1_contGlobals_t#analysisCapacity_ and \ref RESBUF.
 * \returns   #T1_BUSY if T1_Handler() or T1_ContBgHandler() is already running due
 *            to unsupported re-entrancy,
 *            #T1_NOFUNC if no new trace events were available for processing,
 *            #T1_OK otherwise
 * \def T1_ContBgHandlerPC
 * T1.cont background handler. Runs either in background or at a priority no
 * greater than T1_Handler(). See \ref PC and \ref INTRPT and #T1_contBgStatusPC and
 * T1_contGlobals_t#analysisCapacity_ and \ref RESBUF.
 * \param[in] coreId      the T1 logical ID of the calling core
 * \returns   #T1_BUSY if T1_HandlerPC() or T1_ContBgHandlerPC() is already running
 *            due to unsupported re-entrancy,
 *            #T1_NOFUNC if no new trace events were available for processing,
 *            #T1_OK otherwise
 * \def T1_ContReset
 * Reset the T1.cont internal analysis, for example after a task stack overflow
 * error. See \ref PC and \ref INTRPT.
 * \def T1_ContResetPC
 * Reset the T1.cont internal analysis, for example after a task stack overflow
 * error. See \ref PC and \ref INTRPT.
 * \param[in] coreId      the T1 logical ID of the calling core
 * \def T1_ContResetResults
 * Reset the T1.cont results, for example at a mode change.
 * See \ref PC and \ref INTRPT.
 * \def T1_ContResetResultsPC
 * Reset the T1.cont results, for example at a mode change.
 * See \ref PC and \ref INTRPT.
 * \param[in] coreId      the T1 logical ID of the calling core
 */

#if defined T1_ENABLE && !defined T1_DISABLE_T1_CONT

#   define T1_START_SEC_CODE
#   include "T1_MemMap.h"

#   if defined T1_CONT_REMOTE
#       if defined T1_CONT_DIRECT_ID_MAPPINGS
T1_EXTERN T1_status_t T1_CODE T1_ContBgHandlerDirectRCPC( T1_uint8Least_t coreId );
T1_EXTERN void T1_CODE T1_ContResetDirectRCPC( T1_uint8Least_t coreId, T1_uint16Least_t bgTaskId );
T1_EXTERN void T1_CODE T1_ContResetResultsDirectRCPC( T1_uint8Least_t coreId );
#           define T1_ContBgHandlerPC( coreId_ ) T1_ContBgHandlerDirectRCPC( coreId_ )
#           define T1_ContResetPC( coreId_ ) T1_ContResetDirectRCPC( coreId_, T1_INVALID_TASK_IDX )
#           define T1_ContResetBgTaskIdPC( coreId_, bgTaskId_ ) T1_ContResetDirectRCPC( coreId_, bgTaskId_ )
#           define T1_ContResetResultsPC( coreId_ ) T1_ContResetResultsDirectRCPC( coreId_ )
#       else /* original */
T1_EXTERN T1_status_t T1_CODE T1_ContBgHandlerOrigRCPC( T1_uint8Least_t coreId );
T1_EXTERN void T1_CODE T1_ContResetOrigRCPC( T1_uint8Least_t coreId, T1_uint16Least_t bgTaskId );
T1_EXTERN void T1_CODE T1_ContResetResultsOrigRCPC( T1_uint8Least_t coreId );
#           define T1_ContBgHandlerPC( coreId_ ) T1_ContBgHandlerOrigRCPC( coreId_ )
#           define T1_ContResetPC( coreId_ ) T1_ContResetOrigRCPC( coreId_, T1_INVALID_TASK_IDX )
#           define T1_ContResetBgTaskIdPC( coreId_, bgTaskId_ ) T1_ContResetOrigRCPC( coreId_, bgTaskId_ )
#           define T1_ContResetResultsPC( coreId_ ) T1_ContResetResultsOrigRCPC( coreId_ )
T1_EXTERN T1_taskIdx_t T1_CODE T1_GetTaskIdxByIdPC( T1_uint8Least_t coreId, T1_uint16Least_t taskId );
#       endif /* build variants */
#   else /* ! defined T1_CONT_REMOTE */
#       if defined T1_CONT_DIRECT_ID_MAPPINGS
#           if defined T1_NOF_CORES
T1_EXTERN T1_status_t T1_CODE T1_ContBgHandlerDirectPC( T1_uint8Least_t coreId );
T1_EXTERN void T1_CODE T1_ContResetDirectPC( T1_uint8Least_t coreId, T1_uint16Least_t bgTaskId );
T1_EXTERN void T1_CODE T1_ContResetResultsDirectPC( T1_uint8Least_t coreId );
#               define T1_ContBgHandlerPC( coreId_ ) T1_ContBgHandlerDirectPC( coreId_ )
#               define T1_ContResetPC( coreId_ ) T1_ContResetDirectPC( coreId_, T1_INVALID_TASK_IDX )
#               define T1_ContResetBgTaskIdPC( coreId_, bgTaskId_ ) T1_ContResetDirectPC( coreId_, bgTaskId_ )
#               define T1_ContResetResultsPC( coreId_ ) T1_ContResetResultsDirectPC( coreId_ )
#           else /* single core */
T1_EXTERN T1_status_t T1_CODE T1_ContBgHandlerDirect( void );
T1_EXTERN void T1_CODE T1_ContResetDirect( T1_uint16Least_t bgTaskId );
T1_EXTERN void T1_CODE T1_ContResetResultsDirect( void );
#               define T1_ContBgHandler( ) T1_ContBgHandlerDirect( )
#               define T1_ContReset( ) T1_ContResetDirect( T1_INVALID_TASK_IDX )
#               define T1_ContResetBgTaskId( bgTaskId_ ) T1_ContResetDirect( bgTaskId_ )
#               define T1_ContResetResults( ) T1_ContResetResultsDirect( )
#           endif /* T1_NOF_CORES */
#       else /* original */
#           if defined T1_NOF_CORES
T1_EXTERN T1_status_t T1_CODE T1_ContBgHandlerOrigPC( T1_uint8Least_t coreId );
T1_EXTERN void T1_CODE T1_ContResetOrigPC( T1_uint8Least_t coreId, T1_uint16Least_t bgTaskId );
T1_EXTERN void T1_CODE T1_ContResetResultsOrigPC( T1_uint8Least_t coreId );
#               define T1_ContBgHandlerPC( coreId_ ) T1_ContBgHandlerOrigPC( coreId_ )
#               define T1_ContResetPC( coreId_ ) T1_ContResetOrigPC( coreId_, T1_INVALID_TASK_IDX )
#               define T1_ContResetBgTaskIdPC( coreId_, bgTaskId_ ) T1_ContResetOrigPC( coreId_, bgTaskId_ )
#               define T1_ContResetResultsPC( coreId_ ) T1_ContResetResultsOrigPC( coreId_ )
T1_EXTERN T1_taskIdx_t T1_CODE T1_GetTaskIdxByIdPC( T1_uint8Least_t coreId, T1_uint16Least_t taskId );
/*!
 * When not using #T1_CONT_DIRECT_ID_MAPPINGS, this is a callout function that
 * must be implemented by the integrator to translate from T1.cont task idx to
 * T1.scope task ID. See \ref PC.
 */
T1_EXTERN T1_uint16Least_t T1_CODE T1_GetTaskIdByIdxPC( T1_uint8Least_t coreId, T1_taskIdx_t taskIdx );
#           else /* single core */
T1_EXTERN T1_status_t T1_CODE T1_ContBgHandlerOrig( void );
T1_EXTERN void T1_CODE T1_ContResetOrig( T1_uint16Least_t bgTaskId );
T1_EXTERN void T1_CODE T1_ContResetResultsOrig( void );
#               define T1_ContBgHandler( ) T1_ContBgHandlerOrig( )
#               define T1_ContReset( ) T1_ContResetOrig( T1_INVALID_TASK_IDX )
#               define T1_ContResetBgTaskId( bgTaskId_ ) T1_ContResetOrig( bgTaskId_ )
#               define T1_ContResetResults( ) T1_ContResetResultsOrig( )
T1_EXTERN T1_taskIdx_t T1_CODE T1_GetTaskIdxById( T1_uint16Least_t taskId );
/*!
 * When not using #T1_CONT_DIRECT_ID_MAPPINGS, this is a callout function that
 * must be implemented by the integrator to translate from T1.cont task idx to
 * T1.scope task ID. See \ref PC.
 */
T1_EXTERN T1_uint16Least_t T1_CODE T1_GetTaskIdByIdx( T1_taskIdx_t taskIdx );
#           endif /* T1_NOF_CORES */
#       endif /* build variants */
#   endif /* defined T1_CONT_REMOTE */

#   if defined T1_NOF_CORES
#       define T1_ContBgHandler( ) T1_ContBgHandlerPC( T1_GetCoreIdOffset( ) )
#       define T1_ContReset( ) T1_ContResetPC( T1_GetCoreIdOffset( ) )
#       define T1_ContResetBgTaskId( bgTaskId_ ) T1_ContResetBgTaskIdPC( T1_GetCoreIdOffset( ), bgTaskId_ )
#       define T1_ContResetResults( coreId_ ) T1_ContResetResultsPC( T1_GetCoreIdOffset( ) )
/*!
 * Configure an event chain at start-up. Once communications with the T1-HOST-SW
 * have been established, event chains must be configured using the T1-HOST-SW only.
 * \param[in] e1_            event chain start event, formed using T1_COMBINE_EVENT_INFO()
 * \param[in] e2_            event chain stop event, formed using T1_COMBINE_EVENT_INFO()
 * \param[in] swIdx_         see @ref EVENTCHAINS for usage
 * \returns                  #T1_FAILED if there is no available event chain
 *                           #T1_VALUE if stpwIdx is invalid
 *                           #T1_OK otherwise
 */
#       define T1_ConfigEventChain( e1_, e2_, swIdx_ ) T1_ConfigEventChainPC( T1_GetCoreIdOffset( ), e1_, e2_, swIdx_ )
#       define T1_ContDisableAnalysis( ) T1_ContDisableAnalysisPC( T1_GetCoreIdOffset( ) )
T1_EXTERN void T1_CODE T1_ContDisableAnalysisPC( T1_uint8Least_t coreId );
T1_EXTERN void T1_CODE T1_ContErrCallbackPC( T1_uint8Least_t coreId, T1_uint8Least_t errMask, T1_uint8Least_t triggerMask, T1_nofEntries_t afterXevnts );
T1_EXTERN void T1_CODE T1_ContCsrnCallbackPC( T1_uint8Least_t coreId, T1_resultTime_t result, T1_csrnIdx_t idx, T1_nofEntries_t afterXevnts );
T1_EXTERN void T1_CODE T1_ContOHCallbackPC( T1_uint8Least_t coreId, T1_uint8Least_t errMask );
T1_EXTERN T1_resultTime_t T1_CODE T1_ContStartStopCETPC( T1_uint8Least_t coreId, T1_taskIdx_t taskIdx );
T1_EXTERN T1_longTime_t T1_CODE T1_SyncToTraceTimerPC( T1_uint8Least_t coreId, T1_longTime_t getSwTime );
T1_EXTERN void T1_CODE T1_ContCPULoadCallbackPC( T1_uint8Least_t coreId, T1_uint16Least_t to, T1_uint16Least_t te, T1_uint8Least_t cpuLoadThreshold, T1_nofEntries_t afterXevnts );
T1_EXTERN void T1_CODE T1_ContResetCPULoadPC( T1_uint8Least_t coreId );
#       define T1_ContResetCPULoad( ) T1_ContResetCPULoadPC( T1_GetCoreIdOffset( ) )
T1_EXTERN void T1_CODE T1_27981( T1_uint8Least_t coreId, T1_uint16_t *pAu16, T1_uint16_t *pBu16 );
/*!
 * Configure an event chain at start-up. Once communications with the T1-HOST-SW
 * have been established, event chains must be configured using the T1-HOST-SW only.
 * \param[in] coreId         the T1 logical core ID of the calling core
 * \param[in] startEventInfo event chain start event, formed using T1_COMBINE_EVENT_INFO()
 * \param[in] stopEventInfo  event chain stop event, formed using T1_COMBINE_EVENT_INFO()
 * \param[in] stpwIdx        see @ref EVENTCHAINS for usage
 * \returns                  #T1_FAILED if there is no available event chain
 *                           #T1_VALUE if stpwIdx is invalid
 *                           #T1_OK otherwise
 */
T1_EXTERN T1_status_t T1_CODE T1_ConfigEventChainPC
                                            (   T1_uint8Least_t coreId,
                                                T1_uint16_t startEventInfo,
                                                T1_uint16_t stopEventInfo,
                                                T1_stpwIdx_t stpwIdx        );
/*! \brief T1 helper function. */
T1_EXTERN void T1_CODE T1_DeleteCalibrationEventChainPC( T1_uint8Least_t coreId, T1_stpwIdx_t stpwIdx );
T1_EXTERN T1_stpwIdx_t T1_ContUserStpwIdxToIdPC(    T1_uint8Least_t coreId,
                                                    T1_uint16Least_t stpwId );
T1_EXTERN T1_uint16Least_t T1_CODE T1_GetTaskIdByIdxPC( T1_uint8Least_t coreId, T1_taskIdx_t taskIdx );
#   else /* single core */
#       define T1_ContBgHandlerPC( coreId_ ) T1_ContBgHandler( )
#       define T1_ContResetPC( coreId_ ) T1_ContReset( )
#       define T1_ContResetBgTaskIdPC( coreId_, bgTaskId_ ) T1_ContResetBgTaskId( bgTaskId_ )
#       define T1_ContResetResultsPC( coreId_ ) T1_ContResetResults( )
#       define T1_ConfigEventChainPC( coreId_, e1_, e2_, swIdx_ ) T1_ConfigEventChain( e1_, e2_, swIdx_ )
#       define T1_ContDisableAnalysisPC( coreId_ ) T1_ContDisableAnalysis( )
T1_EXTERN void T1_CODE T1_ContDisableAnalysis( void );
T1_EXTERN void T1_CODE T1_ContErrCallback( T1_uint8Least_t errMask, T1_uint8Least_t triggerMask, T1_nofEntries_t afterXevnts );
T1_EXTERN void T1_CODE T1_ContCsrnCallback( T1_resultTime_t result, T1_csrnIdx_t idx, T1_nofEntries_t afterXevnts );
T1_EXTERN void T1_CODE T1_ContOHCallback( T1_uint8Least_t errMask );
T1_EXTERN T1_resultTime_t T1_CODE T1_ContStartStopCET( T1_taskIdx_t taskIdx );
T1_EXTERN void T1_CODE T1_ContCPULoadCallback( T1_uint16Least_t to, T1_uint16Least_t te, T1_uint8Least_t cpuLoadThreshold, T1_nofEntries_t afterXevnts );
T1_EXTERN void T1_CODE T1_ContResetCPULoad( void );
#       define T1_ContResetCPULoadPC( coreId_ ) T1_ContResetCPULoad( )
T1_EXTERN void T1_CODE T1_32553( T1_uint16_t *pTo, T1_uint16_t *pTe );
/*!
 * Configure an event chain at start-up. Once communications with the T1-HOST-SW
 * have been established, event chains must be configured using the T1-HOST-SW only.
 * \param[in] startEventInfo event chain start event, formed using T1_COMBINE_EVENT_INFO()
 * \param[in] stopEventInfo  event chain stop event, formed using T1_COMBINE_EVENT_INFO()
 * \param[in] stpwIdx        see @ref EVENTCHAINS for usage
 * \returns                  #T1_FAILED if there is no available event chain
 *                           #T1_VALUE if stpwIdx is invalid
 *                           #T1_OK otherwise
 */
T1_EXTERN T1_status_t T1_CODE T1_ConfigEventChain
                                            (   T1_uint16_t startEventInfo,
                                                T1_uint16_t stopEventInfo,
                                                T1_stpwIdx_t stpwIdx        );
/*! \brief T1 helper function. */
T1_EXTERN void T1_CODE T1_DeleteCalibrationEventChain( T1_stpwIdx_t stpwIdx );
T1_EXTERN T1_stpwIdx_t T1_ContUserStpwIdxToId( T1_uint16Least_t stpwId );
T1_EXTERN T1_uint16Least_t T1_CODE T1_GetTaskIdByIdx( T1_taskIdx_t taskIdx );
#   endif /* defined T1_NOF_CORES */

#   if defined T1_NOF_CORES && ! defined T1_MULTICORE_CLONE
#       define T1_ContSetTriggerMaskPC( coreId_, mask_ )                \
            ( (void)( T1_contGlobalsPC[coreId]->triggerMask_ = (mask_) ) )
#       define T1_ContSetTriggerMask( mask_ )                           \
            ( (void)( T1_contGlobalsPC[T1_GetCoreIdOffset( )]->triggerMask_ = (mask_) ) )
#   else /* single core or clone */
#       define T1_ContSetTriggerMaskPC( coreId_, mask_ )                \
            ( (void)( T1_contGlobals.triggerMask_ = (mask_) ) )
#       define T1_ContSetTriggerMask( mask_ )                           \
            ( (void)( T1_contGlobals.triggerMask_ = (mask_) ) )
#   endif /* defined T1_NOF_CORES && ! defined T1_MULTICORE_CLONE */

T1_EXTERN void T1_CODE T1_49672( T1_uint8Least_t coreId, T1_taskIdx_t taskIdx, T1_resultTime_t taskCET );
T1_EXTERN void T1_CODE T1_84399( T1_uint8Least_t coreId, T1_longTime_t now );
T1_EXTERN void T1_CODE T1_63193( T1_taskIdx_t taskIdx, T1_resultTime_t taskCET );
T1_EXTERN void T1_CODE T1_00767( T1_longTime_t now );

#   define T1_STOP_SEC_CODE
#   include "T1_MemMap.h"

#else /* ! defined T1_ENABLE || defined T1_DISABLE_T1_CONT */

#   define T1_ContBgHandlerPC( coreId_ )                            (T1_NOFUNC)
#   define T1_ContResetPC( coreId_ )                                ((void)0)
#   define T1_ContResetBgTaskIdPC( coreId_, bgTaskId_ )             ((void)0)
#   define T1_ContResetResultsPC( coreId_ )                         ((void)0)
#   define T1_ContDisableAnalysisPC( coreId_ )                      ((void)0)
#   define T1_ConfigEventChainPC( coreId_, e1_, e2_, swIdx_ )       (T1_NOFUNC)
#   define T1_ContSetTriggerMaskPC( coreId_, mask_ )                ((void)0)
#   define T1_ContBgHandler( )                                      (T1_NOFUNC)
#   define T1_ContReset( )                                          ((void)0)
#   define T1_ContResetBgTaskId( bgTaskId_ )                        ((void)0)
#   define T1_ContResetResults( )                                   ((void)0)
#   define T1_ContDisableAnalysis( )                                ((void)0)
#   define T1_ConfigEventChain( e1_, e2_, swIdx_ )                  (T1_NOFUNC)
#   define T1_ContSetTriggerMask( mask_ )                           ((void)0)

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_CONT */

/*----------------------------------------------------------------------------------*/
/*--- documentation ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_DOXYGEN_ONLY

/*!
 * \brief Guarantee that T1.cont task and stopwatch indices are equal to their
 * T1.scope identifiers.
 */
#   define T1_CONT_DIRECT_ID_MAPPINGS

/*!
 * \page RESBUF Preserving T1.cont results over reset
 *
 * It is possible to preserve the T1.cont result data over a processor reset. The
 * principle is to copy #T1_resultBuffer, at shutdown, to memory that remains intact
 * through reset and to restore #T1_resultBuffer from that memory after T1_Init().
 * Kinds of memory that persist through reset include flash, NVRAM and, for a soft
 * reset, static RAM.
 *
 * \section RESBUFSIZE Buffer size
 * T1.cont stores all results in the array #T1_resultBuffer.
 * Multi-core implementations of the T1-TARGET-SW replace
 * #T1_resultBuffer with #T1_resultBufferPC, which is an array of pointers to each
 * core-specific result buffer. For the remainder of this document, we ignore this and
 * refer to the buffer simply as #T1_resultBuffer. The size of the result buffer for a
 * single-core implementation can be defined with the following macro:
 * \code{.c}
#define T1_RESULT_BUFFER_BYTES (4 * ((((T1_NOF_TASKS_CORE0 + 2*(T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS) + 3u) + 0xFu) & ~0xFu) + 1u))
 * \endcode
 *
 * \section RESBUFACC T1-TARGET-SW accesses
 * For a 32-bit processor, T1.cont writes to each 32-bit element of the
 * #T1_resultBuffer only using atomic, 32-bit write instructions. This means that the
 * buffer state is always consistent and that it is safe to read a 'snapshot' image of
 * the buffer at any time without regard for any synchronization.
 *
 * \section RESBUFSAV Saving T1_resultBuffer
 * For 32-bit implementations of the T1-TARGET-SW, it is always safe to read
 * #T1_resultBuffer.  This means that, at shutdown, the current results can be saved
 * to non-volatile memory and be restored after reset.
 *
 * \section RESBUFREST Restoring T1_resultBuffer
 * The T1-TARGET-SW API call T1_Init() initializes #T1_resultBuffer, setting maximum
 * value to zero so that all new results are captured, for example. To use older,
 * saved results from before a reset, restore the #T1_resultBuffer from NVRAM
 * between T1_Init() and the first call to T1_ContBgHandler(). As it is
 * often important to minimize time in T1_AppInit(), it is usual to perform the
 * restore in T1_AppBackgroundHandler() just before the first call to
 * T1_ContBgHandler().
 *
 * \section RESBUFSOFT Preserving T1.cont results over soft reset
 * After a soft reset, the RAM containing the T1.cont result buffer will be intact, as
 * long as it has not been cleared by over-zealous start-up code. If we need to
 * preserve results only over a soft reset, it may well be sufficient simply to copy
 * the result buffer before T1_Init() and to restore it again between T1_Init() and
 * T1_ContBgHandler().
 */

/*!
 * \page EVENTCHAINS Event chains

The concept of event chains allows to set stopwatches at
run-time, based on existing instrumentation events. In that sense they can be
considered as virtual stopwatches. The advantages of this concept are:
- the existing instrumentation (tasks/ISRs/stopwatches) can be reused: The valuable
  trace buffer is not wasted due to redundant instrumentation
- being applicable on T1.flex UEC and UED events, a manifold number of event
  chains can be configured at run-time eliminating the need for a rebuild
- the default timing results for tasks and ISRs calculated by T1.cont can be
  efficiently reduced to only provide CET[max]/GET[max]. Additional task results
  can be obtained by applying an event chain to the existing task/ISR instrumentation

Event chains can be configured either by an initialization in the T1-TARGET-SW of by
using the T1-HOST-SW (see the GUI help for more information).

Restrictions {#EVENTCHAINSRESTRICTIONS}
============

Some restrictions do apply for event chains:
- by default, a maximum of 8 event chains per system is supported by T1.cont.
  This can be changed to 64 at application build time, see #T1_CONT_NOF_VRTL_STPWS
- each event chain in the T1-TARGET-SW is fixed to measure either GET or CET
- an event can only be used as a START event or as a STOP event for at most one event
  chain (e.g. an activation event of a task cannot be used twice as a START event,
  either the response-time or the initial pending time of a task can be provided by
  using event chains)
- an event chain cannot be applied across system boundaries


Configure event chains {#EVENTCHAINSCONFIG}
====================

Each of these event chains is fixed to either a CET or GET measurement, according to
the scheme shown in Table
@ref EVENT_CHAIN_ALLOCATION "Event Chain Allocation in the T1-TARGET-SW".
For the sake of convenience, the generated T1_config.h (or T1_ids.h respectively)
already defines two macros which map the CET or GET event chain IDs to their indices
for each core:

~~~~~~~~~~~~~~~{.c}
#define T1_CET_EVT_CHAIN_TO_IDX_CORE0( id_ ) ( T1_NOF_STPWS_CORE0 + ( ( 3u < (id_) ) ? T1_invalidCETeventChainIdx : ( 2u*(id_) ) ) )
#define T1_GET_EVT_CHAIN_TO_IDX_CORE0( id_ ) ( T1_NOF_STPWS_CORE0 + ( ( 3u < (id_) ) ? ( (id_) + 4u ) : ( 2u*(id_) + 1u ) ) )
~~~~~~~~~~~~~~~

<table>
  <caption id="EVENT_CHAIN_ALLOCATION">Event Chain Allocation in the T1-TARGET-SW</caption>
  <tr align="center">
    <th> Event Chain Type
    <th> ID
    <th> Index
    <th> Comment
  <tr align="center">
    <td> CET
    <td> 0
    <td> 0
    <td>
  <tr align="center">
    <td> CET
    <td> 1
    <td> 2
    <td>
  <tr align="center">
    <td> CET
    <td> 2
    <td> 4
    <td>
  <tr align="center">
    <td> CET
    <td> 3
    <td> 6
    <td>
  <tr align="center">
    <td> GET
    <td> 0
    <td> 1
    <td>
  <tr align="center">
    <td> GET
    <td> 1
    <td> 3
    <td rowspan="3"> Used for auto-calibration
  <tr align="center">
    <td> GET
    <td> 2
    <td> 5
  <tr align="center">
    <td> GET
    <td> 3
    <td> 7
  <tr align="center">
    <td> GET
    <td> 4
    <td> 8
    <td rowspan="5"> Only if 64 event chains are configured
  <tr align="center">
    <td> GET
    <td> 5
    <td> 9
  <tr align="center">
    <td> GET
    <td> ...
    <td> ...
  <tr align="center">
    <td> GET
    <td> 58
    <td> 62
  <tr align="center">
    <td> GET
    <td> 59
    <td> 63
</table>

In order to configure an event chain using ID 0 and providing the ResponseTime
(activation to stop) of a task, the macro #T1_ConfigEventChain can be used in
T1_AppInit() after the call to T1_Init():
~~~~~~~~~~~~~~~{.c}
T1_ConfigEventChain(
    T1_COMBINE_EVENT_INFO( T1_ACTIVATION, T1_Task_BSW_10ms_ID ),
    T1_COMBINE_EVENT_INFO( T1_STOP,       T1_Task_BSW_10ms_ID ),
    T1_GET_EVT_CHAIN_TO_IDX_CORE0( 0 ) );
~~~~~~~~~~~~~~~

For a multi-core configuration, the same example must take care that the event chain
configuration code runs only on the intended core using T1_ConfigEventChainPC().
~~~~~~~~~~~~~~~{.c}
...*/

if( 0 == coreId )
{
    T1_ConfigEventChainPC( 0, /* Core 0 */
        T1_COMBINE_EVENT_INFO( T1_ACTIVATION, T1_Task_BSW_10ms_ID ),
        T1_COMBINE_EVENT_INFO( T1_STOP,       T1_Task_BSW_10ms_ID ),
        T1_GET_EVT_CHAIN_TO_IDX_CORE0( 0 ) );
}

/*...
~~~~~~~~~~~~~~~

Care must be taken to avoid conflicts with other explicitly configured event chains
and with GET event chains with indices 3, 5 and 7 (GET event chain IDs 1, 2 and 3)
implicitly used by auto-calibration. A solution is described in the
@ref EVENTCHAINSREUSEOVERHEAD to use these 3 GET event chain IDs.

If the event chain initialized on the target provides an additional task result the
T1-HOST-SW will automatically detect this and add it in the project explorer and
also apply the according labels in the trace viewer and T1.cont table view.
In all other cases the T1-HOST-SW will make use of a generic name containing
the event chain ID.

Reuse of event chains used for overhead calibration {#EVENTCHAINSREUSEOVERHEAD}
===================================================


The T1-TARGET-SW performs an overhead calibration at start-up with the configuration
of the GET event chains IDs 1, 2 and 3, see
#T1_CONT_CALIBRATE_OVERHEADS_NOSUSP and #T1_CONT_CALIBRATE_OVERHEADS_NOSUSP_PC.

If these event chains need to be statically configured, it is possible in the
callback following overhead calibration, after the three event chains have been
de-allocated from calibration.
It is necessary to configure the event chains with GET IDs 1, 2 or 3
only after the calibration has been stopped in T1_ContOHCallbackPC() by calling
#T1_CONT_STOP_CALIBRATION.

The following example show how it can be configured on the core 0:
~~~~~~~~~~~~~~~{.c}
...*/

void T1_CODE T1_ContOHCallbackPC( T1_uint8Least_t coreId,
                                  T1_uint8Least_t errMask )
{
    if( 0u == (T1_INF_OVERHEADS_UPDATED & errMask) )
    {
        /* Overheads were not updated */
        INC_T1_ERROR_COUNT( T1_CONT_RC_UNMAP( coreId ) );
    }
    /* Free T1.cont event chains used for calibration */
    T1_CONT_STOP_CALIBRATION_PC( coreId );
    /* Re-use event chain with GET ID 1 on core 0 */
    if( 0u == coreId )
    {
        T1_ConfigEventChainPC( /* core */ 0u,
          T1_COMBINE_EVENT_INFO( T1_START,
                                 T1_Core0_25msTask_ID ),
          T1_COMBINE_EVENT_INFO( T1_STOP,
                                 T1_Core0_25msTask_ID ),
          T1_GET_EVT_CHAIN_TO_IDX_CORE0( 1u ) );
    }
}

/*...
~~~~~~~~~~~~~~~

 */

#endif /* defined T1_DOXYGEN_ONLY */
#endif /* T1_CONT_INTERFACE_H_ */
