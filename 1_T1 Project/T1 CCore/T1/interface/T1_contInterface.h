/************************************************************************************/
/*! \file           T1_contInterface.h
 *
 *  \brief          T1.cont interface declarations and macros
 *
 *  \par Visibility
 *                  External
 *
 *  \author nick
 *
 *  \version 3.5.0.0 r67652
 *
 *  \copyright GLIWA embedded systems GmbH & Co. KG, Weilheim i.OB. All rights reserved
 ************************************************************************************/

#ifndef T1_CONT_INTERFACE_H_
#define T1_CONT_INTERFACE_H_ ( 1 )

/*!
 * \defgroup T1_cont T1.cont
 * \brief    Provides continuous timing supervision on the target.
 *
 * see \ref T1_cont_page
 *
 * @{
 */

/*!
 * \defgroup T1_cont_interfaces Interface Functions
 * \ingroup  T1_cont
 * \brief    Functions and function like macros to interface with T1.cont during
 *           runtime.
 */

/*!
 * \defgroup T1_cont_cert_interfaces T1-TARGET-SW-CERT Only Interface Functions
 * \ingroup  T1_cont
 * \brief    Functions and function like macros to interface with T1.cont during
 *           runtime.
 * \details  These are only functional in T1-TARGET-SW-CERT releases, it is
 *           however safe to call them in normal T1-TARGET-SW releases.
 *           \note Results are valid for versions of the T1-TARGET-SW-CERT only.
 */

/*!
 * \defgroup T1_cont_callbacks User Callbacks
 * \ingroup  T1_cont
 * \brief    User callbacks provide notifications, which might be used by other SW
 *           components or the T1 integration itself.
 */

/*!
 * \defgroup T1_cont_callouts Callouts
 * \ingroup  T1_cont
 * \brief    Callouts are used to implement functionality, that can not be implemented
 *           as part of the T1-TARGET-SW library code.
 *
 * \note     The default implementations in T1_config.c should only be changed under
 *           advice from a GLIWA engineer, please contact \ref SUPPORT if needed.
 */

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_baseInterface.h"
#include "T1_scopeInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_CONT_PLUGIN_ID      ( 5u )

#define T1_ENABLE_CPULOAD_CALC ( 1 )

#define T1_TASK_STACK_OVERRUNS ( 4 )

#if defined T1_ENABLE && !defined T1_DISABLE_T1_CONT
/*! \brief T1.cont entry in plugin table. */
#    define T1_contPlugin ( &T1_contPluginStruct )
#else
#    define T1_contPlugin ( T1_DISABLED_PLUGIN )
#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_CONT */

#define T1_PERCENT_TO_256THS( percent_ ) ( (percent_)*2.56f + 0.5f )

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
#define T1_CONT_CPU_OVERLOAD( to_, te_, cpuLoadThreshold_ )                          \
    ( ( ( cpuLoadThreshold_ ) != 255u )                                              \
      && ( ( ( ( cpuLoadThreshold_ ) * (T1_uint32_t)( to_ ) ) >> 8 ) < ( te_ ) ) )

#define T1_NOF_CS_VS    ( 8u ) /* context-sensitive event chains */

#define T1_VAL_CHANGED  ( T1_resultTime_t )( 1uL )
#define T1_MIN_INIT_VAL ( T1_resultTime_t )( ~T1_VAL_CHANGED )
#define T1_MAX_INIT_VAL ( T1_resultTime_t )( 0uL )

/* Return non-zero if and only if num1_/den1_ < num2_/den2_, for 16-bit values. */
#define FRACTIONS_LESS_THAN_16BIT( num1_, den1_, num2_, den2_ )                      \
    ( (T1_uint32_t)( num1_ ) * ( den2_ ) < (T1_uint32_t)( num2_ ) * ( den1_ ) )

#define T1_BACKGROUND_TASK_IDX_CORE0  ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE0 )
#define T1_BACKGROUND_TASK_IDX_CORE1  ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE1 )
#define T1_BACKGROUND_TASK_IDX_CORE2  ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE2 )
#define T1_BACKGROUND_TASK_IDX_CORE3  ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE3 )
#define T1_BACKGROUND_TASK_IDX_CORE4  ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE4 )
#define T1_BACKGROUND_TASK_IDX_CORE5  ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE5 )
#define T1_BACKGROUND_TASK_IDX_CORE6  ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE6 )
#define T1_BACKGROUND_TASK_IDX_CORE7  ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE7 )
#define T1_BACKGROUND_TASK_IDX_CORE8  ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE8 )
#define T1_BACKGROUND_TASK_IDX_CORE9  ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE9 )
#define T1_BACKGROUND_TASK_IDX_CORE10 ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE10 )
#define T1_BACKGROUND_TASK_IDX_CORE11 ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE11 )
#define T1_BACKGROUND_TASK_IDX_CORE12 ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE12 )
#define T1_BACKGROUND_TASK_IDX_CORE13 ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE13 )
#define T1_BACKGROUND_TASK_IDX_CORE14 ( (T1_taskIdx_t)T1_BACKGROUND_TASK_ID_CORE14 )

/*---------------------- bits of variable T1_contBgStatus --------------------------*/
/* the lowest bit indicates information ("INF") */
/*! \brief T1.cont overheads have been updated after calibration, see
 * T1_CONT_CALIBRATE_OVERHEADS_PC(). */
#define T1_INF_OVERHEADS_UPDATED      ( (T1_contStatus_t)1 << 0 )
/* the lower bits indicate warnings ("WRN") */
/*! \brief Not every traced event has been read by T1.cont. */
#define T1_WRN_INCOMPLETE_ANALYSIS    ( (T1_contStatus_t)1 << 1 )
/*! \brief At least one T1.cont constraint has been violated. */
#define T1_WRN_CONSTRAINT_VIOLATED    ( (T1_contStatus_t)1 << 2 )
/*! \brief A CET stopwatch stopped in a different task or task instance. */
#define T1_WRN_INVALID_CET_STPW       ( (T1_contStatus_t)1 << 3 )
/*! \brief T1.cont result out-of-range, sometimes an underflow after subtracting
 * incorrect overheads. */
#define T1_WRN_RESULT_OUT_OF_RANGE    ( (T1_contStatus_t)1 << 4 )
/* the higher bits indicate errors ("ERR") */
/*! \brief The traced events read by T1.cont are not valid. */
#define T1_ERR_FAULTY_TRACE_DATA      ( (T1_contStatus_t)1 << 5 )
/*! \brief Too much preemption, or unbalanced task start/stop events. */
#define T1_ERR_STACK_OVERFLOW         ( (T1_contStatus_t)1 << 6 )
/*! \brief T1.cont is unable to keep up with T1.scope. */
#define T1_ERR_OVERRUN                ( (T1_contStatus_t)1 << 7 )

/*---------------------- bits of variable T1_contHandlerStatus ---------------------*/
/* the lower bits indicate warnings ("WRN") */
/*! \brief The T1.cont analysis has been stopped. */
#define T1_WRN_ANALYSIS_STOPPED       ( (T1_contStatus_t)1 << 0 )
/* the upper bits give status information */
/*! \brief The T1.cont 4th focus measurement is running. */
#define T1_MODE_FOCUS_RUNNING_3       ( (T1_contStatus_t)1 << 1 )
/*! \brief The T1.cont 3rd focus measurement is running. */
#define T1_MODE_FOCUS_RUNNING_2       ( (T1_contStatus_t)1 << 2 )
/*! \brief The T1.cont 2nd focus measurement is running. */
#define T1_MODE_FOCUS_RUNNING_1       ( (T1_contStatus_t)1 << 3 )
/*! \brief The T1.cont 1st focus measurement is running. */
#define T1_MODE_FOCUS_RUNNING_0       ( (T1_contStatus_t)1 << 4 )
/*! \brief T1.cont constraints are enabled. */
#define T1_MODE_CONSTRAINTS_ENABLED   ( (T1_contStatus_t)1 << 5 )
/*! \brief New T1.cont results are transmitted as soon as they are calculated. */
#define T1_MODE_TRANSMISSION_ENABLED  ( (T1_contStatus_t)1 << 6 )
/*! \brief T1.cont analysis is enabled. */
#define T1_MODE_ANALYSIS_ENABLED      ( (T1_contStatus_t)1 << 7 )
/*
 * T1_MODE_FOCUS_RUNNING is excluded from T1_MODES_BITMASK because it is set and
 * cleared indirectly through the focus protocol.
 */
#define T1_MODES_BITMASK                                                             \
    ( (T1_contStatus_t)( T1_MODE_CONSTRAINTS_ENABLED | T1_MODE_TRANSMISSION_ENABLED  \
                         | T1_MODE_ANALYSIS_ENABLED ) )
/*----------------------------------------------------------------------------------*/

/* bits for constraint configuration */
/*! \brief constraint configuration on maximum threshold. */
#define T1_CSRN_MAX                         ( 1u )
/*! \brief constraint configuration on minimum threshold. */
#define T1_CSRN_MIN                         ( 2u )
#define T1_STOPTRIGGER                      ( T1_STOPTRIGGER_DEPRECATED )
#define T1_CALLBACK                         ( T1_CALLBACK_DEPRECATED )
#define T1_MESSAGE                          ( T1_MESSAGE_DEPRECATED )
#define T1_CSRN_UNDEF                       ( T1_CSRN_UNDEF_DEPRECATED )

#define T1_INVALID_TASK_IDX                 ( (T1_taskIdx_t)-1 )
#define T1_INVALID_RESULT_IDX               ( (T1_resultsIdx_t)-1 )

#define T1_INVALID_STPW_IDX                 ( (T1_stpwIdx_t)-1 )

#define T1_CONT_STPW_GET                    ( 0u ) //!< Last start to first stop
#define T1_CONT_STPW_DATA_AGE               ( 1u ) //!< Last start to last stop
#define T1_CONT_STPW_CET                    ( 2u ) //!< Last start to first stop in same task instance
#define T1_CONT_STPW_NPC                    ( 3u ) //!< Last start to first stop with no preemptions
#define T1_CONT_STPW_CET_FN                 ( 4u )  //!< Overlap with deprecated IDs
#define T1_CONT_STPW_CET_NF                 ( 5u )  //!< Overlap with deprecated IDs
#define T1_CONT_STPW_REENTRANT0             ( 4u )  //!< Used for nesting
#define T1_CONT_STPW_REENTRANT1             ( 5u )  //!< Used for nesting
#define T1_CONT_STPW_REENTRANT2             ( 6u )  //!< Used for nesting
#define T1_CONT_STPW_REENTRANT3             ( 7u )  //!< Used for nesting
#define T1_CONT_STPW_REENTRANT4             ( 8u )  //!< Used for nesting
#define T1_CONT_STPW_REENTRANT5             ( 9u )  //!< Used for nesting
#define T1_CONT_STPW_REENTRANT6             ( 10u ) //!< Used for nesting
#define T1_CONT_STPW_REENTRANT7             ( 11u ) //!< Used for nesting
#define T1_CONT_STPW_INVALID_CFG            ( 255u )

#define T1_CONT_STPW_IS_CET( cfg_ )         ( T1_CONT_STPW_CET <= ( cfg_ ) )

/* See T1_stpwConfig_t */
#define T1_CONT_STPW( type_, id_ )          T1_CONT_STPW_##type_

/*! \brief Configure CET for the given stopwatch ID */
#define T1_CONT_CET_STOPWATCH( id_ )        T1_CONT_STPW( CET, ( id_ ) )
#define T1_CONT_NPC_STOPWATCH( id_ )        T1_CONT_STPW( NPC, ( id_ ) )
/*! \brief Configure GET for the given stopwatch ID */
#define T1_CONT_GET_STOPWATCH( id_ )        T1_CONT_STPW( GET, ( id_ ) )
/*! \brief Configure data age (DA) for the given stopwatch ID */
#define T1_CONT_DATA_AGE_STOPWATCH( id_ )   T1_CONT_STPW( DATA_AGE, ( id_ ) )
#define T1_CONT_REENTRANT0_STOPWATCH( id_ ) T1_CONT_STPW( REENTRANT0, ( id_ ) )
#define T1_CONT_REENTRANT1_STOPWATCH( id_ ) T1_CONT_STPW( REENTRANT1, ( id_ ) )
#define T1_CONT_REENTRANT2_STOPWATCH( id_ ) T1_CONT_STPW( REENTRANT2, ( id_ ) )
#define T1_CONT_REENTRANT3_STOPWATCH( id_ ) T1_CONT_STPW( REENTRANT3, ( id_ ) )
#define T1_CONT_REENTRANT4_STOPWATCH( id_ ) T1_CONT_STPW( REENTRANT4, ( id_ ) )
#define T1_CONT_REENTRANT5_STOPWATCH( id_ ) T1_CONT_STPW( REENTRANT5, ( id_ ) )
#define T1_CONT_REENTRANT6_STOPWATCH( id_ ) T1_CONT_STPW( REENTRANT6, ( id_ ) )
#define T1_CONT_REENTRANT7_STOPWATCH( id_ ) T1_CONT_STPW( REENTRANT7, ( id_ ) )

/*! \brief Convert a time in nanoseconds to core 0 trace timer ticks. */
#define T1_NS_TO_TICKS( ns_ )               T1_NS_TO_TICKS_CORE0( ns_ )
/*! \brief Convert a time in microseconds to core 0 trace timer ticks. */
#define T1_US_TO_TICKS( us_ )               T1_US_TO_TICKS_CORE0( us_ )
/*! \brief Convert a time in milliseconds to core 0 trace timer ticks. */
#define T1_MS_TO_TICKS( ms_ )               T1_MS_TO_TICKS_CORE0( ms_ )

/* Note that min=0 maps to max=0x7FFFFFFF, since they are equivalent (and useless). */
#define T1_CONT_CONSTRAINT_TIME( ticks_, config_ )                                   \
    ( ( T1_CSRN_MIN == ( config_ ) )                                                 \
          ? ( ( (ticks_)&0x7FFFFFFFuL ) + 0x7FFFFFFFuL )                             \
          : ( ( T1_CSRN_MAX == ( config_ ) ) ? (ticks_)&0x7FFFFFFFuL : 0uL ) )

/*!
 * Allow to configure a constraint in the array initializer, effective after the
 * call of T1_InitPC().
 * See \ref CONSTRAINTS.
 * \param[in] contStpwIdx_ user stopwatch or event chain ID
 * \param[in] ticks_ duration in timer ticks, see core specific and unit specific:
                     - T1_NS_TO_TICKS_CORE<coreID>( ns )
                     - T1_US_TO_TICKS_CORE<coreID>( us )
                     - T1_MS_TO_TICKS_CORE<coreID>( ms )
 * \param[in] config_ possible values are #T1_CSRN_MIN or #T1_CSRN_MAX.
 */
#define T1_STPW_IDX_CONSTRAINT( contStpwIdx_, ticks_, config_ )                      \
    {                                                                                \
        ( T1_stpwIdx_t )( contStpwIdx_ ), 0u, 0u,                                    \
            T1_CONT_CONSTRAINT_TIME( (T1_longTime_t)( ticks_ ), ( config_ ) )        \
    }
/*!
 * Configuration for constraint unused by the T1-TARGET-SW. This is the default
 * configuration to allow the T1-HOST-SW to use constraints on the target.
 */
#define T1_CONT_INVALID_CONSTRAINT                                                   \
    {                                                                                \
        T1_INVALID_STPW_IDX, 0u, 0u, 0uL                                             \
    }

#ifndef T1_CONT_NOF_VRTL_STPWS
/*!
 * Defines the number of event chains which can be configured, 8 or 64. See
 * [-numberOfVirtualStopwatches](@ref numberOfVirtualStopwatches).
 */
#    define T1_CONT_NOF_VRTL_STPWS ( 8 )
#endif

#define T1_CONT_NOF_INIT_CET_VRTLS_STPWS ( 4u )

#if !defined T1_CET_EVT_CHAIN_TO_IDX_PC
/*!
 * \brief Returns the index mapped to the provided CET event chain ID,
 *        see \ref EVENT_CHAINS.
 *
 * \param[in] coreId_ the T1 logical core ID of the calling core
 * \param[in] id_     the ID of the CET event chain, allowed values are 0 .. 3
 */
#    define T1_CET_EVT_CHAIN_TO_IDX_PC( coreId_, id_ )                               \
        ( ( ( id_ ) < T1_CONT_NOF_INIT_CET_VRTLS_STPWS )                             \
              ? T1_NOF_STPWS_CORE##coreId_ + ( 2u * ( id_ ) )                        \
              : T1_INVALID_STPW_IDX )
#endif /* defined T1_CET_EVT_CHAIN_TO_IDX_PC */

#if !defined T1_GET_EVT_CHAIN_TO_IDX_PC
/*!
 * \brief Returns the index mapped to the provided GET event chain ID,
 *        see \ref EVENT_CHAINS.
 *
 * \param[in] coreId_ the T1 logical core ID of the calling core
 * \param[in] id_     the ID of the GET event chain, allowed values are
 *                    0 .. \ref T1_CONT_NOF_VRTL_STPWS - 5
 */
#    define T1_GET_EVT_CHAIN_TO_IDX_PC( coreId_, id_ )                               \
        ( ( ( id_ ) + T1_CONT_NOF_INIT_CET_VRTLS_STPWS < T1_CONT_NOF_VRTL_STPWS )    \
              ? T1_NOF_STPWS_CORE##coreId_                                           \
                    + ( ( T1_CONT_NOF_INIT_CET_VRTLS_STPWS <= ( id_ ) )              \
                            ? ( ( id_ ) + T1_CONT_NOF_INIT_CET_VRTLS_STPWS )         \
                            : ( 2u * ( id_ ) + 1u ) )                                \
              : T1_INVALID_STPW_IDX )
#endif /* defined T1_GET_EVT_CHAIN_TO_IDX_PC */

/* Legacy macros for backwards compatibility. */
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE0
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE0( id_ )                                     \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 0, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE1
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE1( id_ )                                     \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 1, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE2
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE2( id_ )                                     \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 2, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE3
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE3( id_ )                                     \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 3, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE4
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE4( id_ )                                     \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 4, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE5
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE5( id_ )                                     \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 5, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE6
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE6( id_ )                                     \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 6, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE7
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE7( id_ )                                     \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 7, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE8
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE8( id_ )                                     \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 8, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE9
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE9( id_ )                                     \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 9, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE10
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE10( id_ )                                    \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 10, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE11
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE11( id_ )                                    \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 11, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE12
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE12( id_ )                                    \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 12, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE13
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE13( id_ )                                    \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 13, ( id_ ) )
#endif
#if !defined T1_CET_EVT_CHAIN_TO_IDX_CORE14
#    define T1_CET_EVT_CHAIN_TO_IDX_CORE14( id_ )                                    \
        T1_CET_EVT_CHAIN_TO_IDX_PC( 14, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE0
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE0( id_ )                                     \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 0, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE1
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE1( id_ )                                     \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 1, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE2
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE2( id_ )                                     \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 2, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE3
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE3( id_ )                                     \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 3, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE4
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE4( id_ )                                     \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 4, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE5
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE5( id_ )                                     \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 5, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE6
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE6( id_ )                                     \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 6, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE7
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE7( id_ )                                     \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 7, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE8
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE8( id_ )                                     \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 8, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE9
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE9( id_ )                                     \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 9, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE10
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE10( id_ )                                    \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 10, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE11
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE11( id_ )                                    \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 11, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE12
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE12( id_ )                                    \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 12, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE13
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE13( id_ )                                    \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 13, ( id_ ) )
#endif
#if !defined T1_GET_EVT_CHAIN_TO_IDX_CORE14
#    define T1_GET_EVT_CHAIN_TO_IDX_CORE14( id_ )                                    \
        T1_GET_EVT_CHAIN_TO_IDX_PC( 14, ( id_ ) )
#endif

#if defined T1_ENABLE && !defined T1_DISABLE_T1_CONT

#    define T1_VSTPWS_IDX_BASE ( T1_nOfStpwsPC[coreId__] - T1_CONT_NOF_VRTL_STPWS )

#    if defined T1_FG_CONT
#        define T1_CONT_CALIBRATE_OVERHEADS_PC( coreId_ )                            \
            do                                                                       \
            {                                                                        \
                T1_uint8Least_t const coreId__ = ( coreId_ );                        \
                T1_SuspendAllInterruptsPC( coreId__ );                               \
                T1_ScopeOverheadSequenceNoSuspPC( coreId__ );                        \
                (void)T1_TraceEventNoSuspPC( coreId__,                               \
                                             T1_EMPTY,                               \
                                             T1_CONT_UPDATE_OH );                    \
                T1_ResumeAllInterruptsPC( coreId__ );                                \
            }                                                                        \
            while( 0 )
#        define T1_CONT_CALIBRATE_OVERHEADS_NOSUSP_PC( coreId_ )                     \
            do                                                                       \
            {                                                                        \
                T1_uint8Least_t const coreId__ = ( coreId_ );                        \
                T1_ScopeOverheadSequenceNoSuspPC( coreId__ );                        \
                (void)T1_TraceEventNoSuspPC( coreId__,                               \
                                             T1_EMPTY,                               \
                                             T1_CONT_UPDATE_OH );                    \
            }                                                                        \
            while( 0 )
#        define T1_CONT_STOP_CALIBRATION_PC( coreId_ ) ( (void)0 )
#    else /* !defined T1_FG_CONT */
/*!
 * Calibrate T1.scope and T1.flex overheads as used by T1.cont.
 * Note that this could take around 100us, which might be undesirable during
 * initialization. Calibration can be postponed from initialization to a less
 * time-critical area, such as the background task. Any T1.cont results computed
 * before calibration are calculated using the overheads configured in the .inv
 * file(s). Requires to run in supervisor mode.
 * See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical core ID of the calling core
 */
#        define T1_CONT_CALIBRATE_OVERHEADS_PC( coreId_ )                            \
            do                                                                       \
            {                                                                        \
                T1_uint8Least_t const coreId__ = ( coreId_ );                        \
                T1_SuspendAllInterruptsPC( coreId__ );                               \
                T1_ConfigEventChainPC(                                               \
                    coreId__,                                                        \
                    T1_COMBINE_EVENT_INFO( T1_STOPWATCH_STOP_START, T1_OH_SW ),      \
                    T1_COMBINE_EVENT_INFO( T1_STOPWATCH_STOP_START, T1_OH_SW ),      \
                    T1_VSTPWS_IDX_BASE + 3 );                                        \
                T1_ConfigEventChainPC(                                               \
                    coreId__,                                                        \
                    T1_COMBINE_EVENT_INFO( T1_STOPWATCH_START, T1_OH_SW - 1 ),       \
                    T1_COMBINE_EVENT_INFO( T1_STOPWATCH_STOP, T1_OH_SW - 1 ),        \
                    T1_VSTPWS_IDX_BASE + 5 );                                        \
                T1_ConfigEventChainPC(                                               \
                    coreId__,                                                        \
                    T1_COMBINE_EVENT_INFO( T1_STOPWATCH_START, T1_OH_SW - 2 ),       \
                    T1_COMBINE_EVENT_INFO( T1_STOPWATCH_STOP, T1_OH_SW - 2 ),        \
                    T1_VSTPWS_IDX_BASE + 7 );                                        \
                T1_ScopeOverheadSequenceNoSuspPC( coreId__ );                        \
                (void)T1_TraceEventNoSuspPC( coreId__,                               \
                                             T1_EMPTY,                               \
                                             T1_CONT_UPDATE_OH );                    \
                T1_ResumeAllInterruptsPC( coreId__ );                                \
            }                                                                        \
            while( 0 )
/*!
 * Calibrate T1.scope and T1.flex overheads as used by T1.cont.
 * Note that this could take around 100us, which might be undesirable during
 * initialization. Calibration can be postponed from initialization to a less
 * time-critical area, such as the background task. Any T1.cont results computed
 * before calibration are calculated using the overheads configured in the .inv
 * file(s). Requires to run in supervisor mode.
 * \param[in] coreId_ the T1 logical core ID of the calling core
 * See \ref PC and \ref INTRPT.
 */
#        define T1_CONT_CALIBRATE_OVERHEADS_NOSUSP_PC( coreId_ )                     \
            do                                                                       \
            {                                                                        \
                T1_uint8Least_t const coreId__ = ( coreId_ );                        \
                T1_ConfigEventChainPC(                                               \
                    coreId__,                                                        \
                    T1_COMBINE_EVENT_INFO( T1_STOPWATCH_STOP_START, T1_OH_SW ),      \
                    T1_COMBINE_EVENT_INFO( T1_STOPWATCH_STOP_START, T1_OH_SW ),      \
                    T1_VSTPWS_IDX_BASE + 3 );                                        \
                T1_ConfigEventChainPC(                                               \
                    coreId__,                                                        \
                    T1_COMBINE_EVENT_INFO( T1_STOPWATCH_START, T1_OH_SW - 1 ),       \
                    T1_COMBINE_EVENT_INFO( T1_STOPWATCH_STOP, T1_OH_SW - 1 ),        \
                    T1_VSTPWS_IDX_BASE + 5 );                                        \
                T1_ConfigEventChainPC(                                               \
                    coreId__,                                                        \
                    T1_COMBINE_EVENT_INFO( T1_STOPWATCH_START, T1_OH_SW - 2 ),       \
                    T1_COMBINE_EVENT_INFO( T1_STOPWATCH_STOP, T1_OH_SW - 2 ),        \
                    T1_VSTPWS_IDX_BASE + 7 );                                        \
                T1_ScopeOverheadSequenceNoSuspPC( coreId__ );                        \
                (void)T1_TraceEventNoSuspPC( coreId__,                               \
                                             T1_EMPTY,                               \
                                             T1_CONT_UPDATE_OH );                    \
            }                                                                        \
            while( 0 )
/*!
 * Free T1.cont event chains used for calibration. See \ref PC.
 * \param[in] coreId_ the T1 logical core ID of the calling core
 */
#        define T1_CONT_STOP_CALIBRATION_PC( coreId_ )                               \
            do                                                                       \
            {                                                                        \
                T1_uint8Least_t const coreId__ = ( coreId_ );                        \
                T1_DeleteCalibrationEventChainPC( coreId__,                          \
                                                  T1_VSTPWS_IDX_BASE + 3 );          \
                T1_DeleteCalibrationEventChainPC( coreId__,                          \
                                                  T1_VSTPWS_IDX_BASE + 5 );          \
                T1_DeleteCalibrationEventChainPC( coreId__,                          \
                                                  T1_VSTPWS_IDX_BASE + 7 );          \
            }                                                                        \
            while( 0 )
#    endif /* defined T1_FG_CONT */
#    define T1_CONT_CALIBRATE_OVERHEADS( )                                           \
        T1_CONT_CALIBRATE_OVERHEADS_PC( T1_GetCoreIdOffset( ) )
#    define T1_CONT_CALIBRATE_OVERHEADS_NOSUSP( )                                    \
        T1_CONT_CALIBRATE_OVERHEADS_NOSUSP_PC( T1_GetCoreIdOffset( ) )
#    define T1_CONT_STOP_CALIBRATION( )                                              \
        T1_CONT_STOP_CALIBRATION_PC( T1_GetCoreIdOffset( ) )

#else /* T1.cont is disabled */

#    define T1_CONT_CALIBRATE_OVERHEADS_PC( coreId_ )        ( (void)0 )
#    define T1_CONT_CALIBRATE_OVERHEADS_NOSUSP_PC( coreId_ ) ( (void)0 )
#    define T1_CONT_STOP_CALIBRATION_PC( coreId_ )           ( (void)0 )
#    define T1_CONT_CALIBRATE_OVERHEADS( )                   ( (void)0 )
#    define T1_CONT_CALIBRATE_OVERHEADS_NOSUSP( )            ( (void)0 )
#    define T1_CONT_STOP_CALIBRATION( )                      ( (void)0 )

#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_CONT */

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

typedef T1_uint32_t T1_resultMask_t;
/*!
 * \brief T1.cont task index.
 * This is equal to the T1.scope task identifier.
 */
typedef T1_uint16_t T1_taskIdx_t;
/*! \brief T1.cont result index. */
typedef T1_uint16_t T1_resultsIdx_t;
/*! \brief Type for T1_contGlobals_t#analysisCapacity_. */
typedef T1_uint16_t T1_anaCapa_t;
/*!
 * \brief Type for T1.cont status.
 * Used for both #T1_contBgStatusPC and #T1_contHandlerStatusPC.
 */
typedef T1_uint8_t T1_contStatus_t; /* Two different single-byte values */
typedef T1_uint8_t T1_resultKind_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Used to store initial values for a stopwatch */
typedef const T1_uint8_t T1_stpwConfig_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Used only for tasks that enter the WAITING state. */
typedef struct
{
    T1_uint8_t taskInstance; //!< Waiting instance
#if defined T1_CPU16BIT || defined T1_CPU32BIT || defined T1_CPU64BIT
    T1_uint8_t unused8; /* Force alignment */
#    if defined T1_CPU32BIT || defined T1_CPU64BIT
    T1_uint16_t unused16; /* Force alignment */
#    endif                /* definedT1_CPU32BIT || defined T1_CPU64BIT */
#endif /* defined T1_CPU16BIT || defined T1_CPU32BIT || defined T1_CPU64BIT */
    T1_resultTime_t netAccumulation; //!< Net time before waiting
} T1_taskData_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Used to store stopwatch data */
typedef struct T1_stpwDataStruct_t
{
    /* Convert task net to stopwatch net or absolute to stopwatch gross. */
    T1_resultTime_t netConversionOrStartTime;
    T1_uint8_t config; /* See T1_stpwConfig_t */
    /* If the startTaskInstKey is zero, the stopwatch is not running. */
    T1_uint8_t startTaskInstKey; /* The instance of the starting task */
    /*
     * High two bits of constraintFocusIdx are focus, low 6 bits are constraint index
     * Focus: 3 => focus disabled, 0..2 => focus enabled for focus index 0..2
     */
    T1_csrnIdx_t constraintFocusIdx; /* Constraint or focus index for result */
    T1_uint8_t reentrantCount;       /* Count times reentered */
} T1_stpwData_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Used to store data for constraints */
typedef struct
{
    /* REVIEWNOTE: T1_stpwIdx_t is used as a T1_taskIdx_t if a task constraint */
    T1_stpwIdx_t stpwIdx; /* T1_INVALID_STPW_IDX for unused constraint */
    T1_uint8_t unused8;   /* Force alignment */
#if defined T1_CPU32BIT || defined T1_CPU64BIT
    T1_uint16_t unused16; /* Force alignment */
#endif                    /* definedT1_CPU32BIT || defined T1_CPU64BIT */
    T1_longTime_t threshold;
    /*
     * Threshold is a 32-bit value.
     * If the MSB is set, the value must be GREATER THAN this threshold.
     * If the MSB is clear, the value must be LESS THAN this threshold.
     */
} T1_csrnData_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Running and preempted tasks are recorded on the T1.cont task stack. */
typedef struct
{
    T1_taskIdx_t idx;       //!< T1.cont task index
    T1_uint8_t instanceKey; //!< Distinguish task instances
#if defined T1_CPU32BIT || defined T1_CPU64BIT
    T1_uint8_t unused8;              /* Force alignment */
#endif                               /* defined T1_CPU32BIT || defined T1_CPU64BIT */
    T1_resultTime_t netAccumulation; //!< Accumulated net time for this task
} T1_taskStackElem_t;
/*----------------------------------------------------------------------------------*/
typedef T1_uint32_t T1_txState_t;
/*----------------------------------------------------------------------------------*/
/*! \brief T1.cont global data for one core. */
typedef struct T1_contGlobalsStruct_t
{
    T1_uint32_t contRdIdx_; //!< T1.cont trace buffer read index
    T1_longTime_t now_;
    T1_resultTime_t netTaskAccumulation_; /* No init required because background task
                                             has no CET */
    T1_tick_t lastEventTime_;
    T1_tick_t overhead_; //!< Currently active T1.scope overhead
    /* Offset 16 */
    /*
     * taskStack is a stack that reflects the preemption hierarchy. The topmost (last)
     * task on the stack is the one currently running, as far as the T1.cont
     * interpretation is concerned.
     */
    T1_taskStackElem_t *pTopOfTaskStack_;

    T1_uint8_t taskInstanceKey_;
    T1_stpwIdx_t nOfUserStpws_; /* Cached in RAM for fast access. */
    T1_uint16_t startOfFrameEvent_;

    T1_taskIdx_t bgTaskIdx_; //!< T1.cont task index of task to exclude from CPU load.
    T1_anaCapa_t analysisCapacity_; //!< One call to T1_ContBgHandler() reads at most
                                    //!< this number of events.

    T1_uint16_t flexOverhead_;     //!< Currently active additional T1.flex overhead
    T1_stpwIdx_t nOfNonVrtlStpws_; /* Cached in RAM for fast access */
    T1_stpwIdx_t nOfStpws_;        /* Cached in RAM for fast access */

    /* Offset 32 */
    T1_cpuLoad_t cpuLoadData;

    /* Offset 52 */
    T1_longTime_t teFgMask_;
    T1_taskStackElem_t *pTaskStackOverrun_;
    union {
        T1_uint32_t test;
        struct
        {
            volatile T1_uint8_t mask;
            T1_bool_t T1ContResults;
            T1_bool_t T1ContAnalysis;
            T1_uint8_t unused8;
        } parts;
    } reset_;

    /* Offset 64 */
    struct T1_focusStruct_t tx_;

    T1_vStpwMapping_t *pVStpws_;      /* cached T1_vStpw (address) */
    T1_vStpwMapping_t *pVStpwStarts_; /* upper half of T1_vStpw */
    void ( *pDoVStpwAll_ )( struct T1_contGlobalsStruct_t *pContGlobals,
                            T1_uint16Least_t nOfTasks,
                            T1_uint16_t eventInfo,
                            T1_vStpwMapping_t const *vStpws );

    T1_txState_t contTxState_;
    T1_uint16_t msgFocusIdx_; /* min 2 bytes for GCP */
    T1_resultsIdx_t resetStpwAfterResultIdx_;

    T1_uint16_t vStpwNewStartEventInfo_;
    T1_uint16_t vStpwNewStopEventInfo_;
    T1_uint16_t vStpwNewStartStopIds_;

    T1_uint16_t txPos_;

    T1_resultsIdx_t searchIdx_; /* No init required */

    T1_bool_t scopeStoppedOrContDisabled_;
    T1_bool_t statusChanged_;

    T1_uint8_t ackForResetStpw_;
    T1_stpwIdx_t resetResultsForStpwIdx_;
    T1_taskIdx_t resetResultsForTaskIdx_;

    T1_focusData_t *pFocusData_; //!< Array of focus states
    T1_stpwIdx_t delayedResetStpwIdx_;
    T1_csrnIdx_t nOfActiveCsrns_;
    T1_uint8_t newCfgForResetStpw_;

    T1_uint8_t triggerMask_; //!< Mask on which the background handler errors should
                             //!< cause a trigger, see #T1_ContSetTriggerMaskPC

    T1_csVStpwCache_t *pCsVStpwCache_;

#if defined T1_CPU32BIT || defined T1_CPU64BIT
    T1_longTime_t refTime_;
    T1_longTime_t bgCallbackPeriod_;
#endif /* defined T1_CPU32BIT || defined T1_CPU64BIT */

    T1_uint16_t cpuLoadTxPeriod_;
    T1_uint8_t avgCPULoadSamples_;
    T1_uint8_t cpuLoadThreshold_;
    T1_bool_t
#if !defined T1_CHECKER_ARTEFACT
        volatile
#endif /* defined T1_CHECKER_ARTEFACT */
        inBgHandler_;
    /* How much more of the buffer to fill after a callback trigger (0..128 128ths) */
    T1_uint8_t constraintTrigger128ths_;
    T1_uint8_t overloadTrigger128ths_;
    T1_uint8_t errorTrigger128ths_;

    T1_traceEntry_t lastUserDataMid_;
    T1_uint16_t crossCoreEventInfo_;
    T1_uint8_t txControlByte_;
    T1_uint8_t unused8; /* Force alignment */
#if defined T1_CPU64BIT
    T1_uint32_t unused32; /* Force alignment */
#endif                    /* defined T1_CPU64BIT */
} T1_contGlobals_t;

/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_CONT

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_DeclarePlugin( T1_contPluginStruct );
T1_EXTERN const T1_uint32_t T1_SEC_CONST_32 T1_contRevision;
T1_EXTERN T1_csVStpwCache_t * const T1_SEC_CONST_32 T1_contCsVStpwCachePC[];
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    if defined T1_MULTICORE_CLONE
#        define T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CLONE_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals;
#        define T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    else /* ! defined T1_MULTICORE_CLONE */
#        define T1_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE0_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals0;
#        define T1_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE1_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals1;
#        define T1_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE2_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals2;
#        define T1_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE3_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals3;
#        define T1_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE4_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals4;
#        define T1_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE5_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals5;
#        define T1_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE6_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals6;
#        define T1_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE7_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals7;
#        define T1_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE8_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals8;
#        define T1_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE9_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals9;
#        define T1_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE10_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals10;
#        define T1_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE11_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals11;
#        define T1_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE12_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals12;
#        define T1_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE13_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals13;
#        define T1_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t T1_CORE14_SEC_VAR_POWER_ON_CLEARED_32 T1_contGlobals14;
#        define T1_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        define T1_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_contGlobals_t * const T1_SEC_CONST_32 T1_contGlobalsPC[];
#        define T1_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#        define T1_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE0_SEC_VAR_POWER_ON_CLEARED_32 T1_focus0[];
#        define T1_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if 1 < T1_NOF_CORES
#            define T1_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE1_SEC_VAR_POWER_ON_CLEARED_32 T1_focus1[];
#            define T1_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 1 < T1_NOF_CORES */
#        if 2 < T1_NOF_CORES
#            define T1_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE2_SEC_VAR_POWER_ON_CLEARED_32 T1_focus2[];
#            define T1_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 2 < T1_NOF_CORES */
#        if 3 < T1_NOF_CORES
#            define T1_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE3_SEC_VAR_POWER_ON_CLEARED_32 T1_focus3[];
#            define T1_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 3 < T1_NOF_CORES */
#        if 4 < T1_NOF_CORES
#            define T1_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE4_SEC_VAR_POWER_ON_CLEARED_32 T1_focus4[];
#            define T1_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 4 < T1_NOF_CORES */
#        if 5 < T1_NOF_CORES
#            define T1_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE5_SEC_VAR_POWER_ON_CLEARED_32 T1_focus5[];
#            define T1_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 5 < T1_NOF_CORES */
#        if 6 < T1_NOF_CORES
#            define T1_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE6_SEC_VAR_POWER_ON_CLEARED_32 T1_focus6[];
#            define T1_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 6 < T1_NOF_CORES */
#        if 7 < T1_NOF_CORES
#            define T1_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE7_SEC_VAR_POWER_ON_CLEARED_32 T1_focus7[];
#            define T1_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 7 < T1_NOF_CORES */
#        if 8 < T1_NOF_CORES
#            define T1_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE8_SEC_VAR_POWER_ON_CLEARED_32 T1_focus8[];
#            define T1_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 8 < T1_NOF_CORES */
#        if 9 < T1_NOF_CORES
#            define T1_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE9_SEC_VAR_POWER_ON_CLEARED_32 T1_focus9[];
#            define T1_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 9 < T1_NOF_CORES */
#        if 10 < T1_NOF_CORES
#            define T1_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE10_SEC_VAR_POWER_ON_CLEARED_32 T1_focus10[];
#            define T1_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 10 < T1_NOF_CORES */
#        if 11 < T1_NOF_CORES
#            define T1_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE11_SEC_VAR_POWER_ON_CLEARED_32 T1_focus11[];
#            define T1_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 11 < T1_NOF_CORES */
#        if 12 < T1_NOF_CORES
#            define T1_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE12_SEC_VAR_POWER_ON_CLEARED_32 T1_focus12[];
#            define T1_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 12 < T1_NOF_CORES */
#        if 13 < T1_NOF_CORES
#            define T1_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE13_SEC_VAR_POWER_ON_CLEARED_32 T1_focus13[];
#            define T1_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 13 < T1_NOF_CORES */
#        if 14 < T1_NOF_CORES
#            define T1_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_focusData_t T1_CORE14_SEC_VAR_POWER_ON_CLEARED_32 T1_focus14[];
#            define T1_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* 14 < T1_NOF_CORES */
#    endif     /* defined T1_MULTICORE_CLONE */

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_EXTERN const T1_longTime_t T1_SEC_CONST_32 T1_06960;
T1_EXTERN const T1_longTime_t T1_SEC_CONST_32 T1_38948[];
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

/* const data */
#    define T1_START_SEC_CONST_8
#    include "T1_MemMap.h"
T1_EXTERN const T1_uint8_t T1_SEC_CONST_8 T1_cpuLoadThresholdPC[];
T1_EXTERN const T1_uint8_t T1_SEC_CONST_8 T1_avgCPULoadSamplesPC[];
T1_EXTERN const T1_uint8_t T1_SEC_CONST_8 T1_nOfPreemptionsPC[];
T1_EXTERN const T1_stpwIdx_t T1_SEC_CONST_8 T1_nOfStpwsPC[];
T1_EXTERN const T1_stpwIdx_t T1_SEC_CONST_8 T1_nOfUserStpwsPC[];
T1_EXTERN const T1_csrnIdx_t T1_SEC_CONST_8 T1_nOfCsrnsPC[];
T1_EXTERN const T1_uint8_t T1_SEC_CONST_8 T1_nOfVrtlStpws;
T1_EXTERN const T1_uint8_t T1_SEC_CONST_8 T1_nOfFocusMeasurements;
T1_EXTERN const T1_bool_t T1_SEC_CONST_8 T1_fgContEnabled;
#    define T1_STOP_SEC_CONST_8
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_16
#    include "T1_MemMap.h"
T1_EXTERN const T1_tick_t T1_SEC_CONST_16 T1_overheadPC[];
T1_EXTERN const T1_tick_t T1_SEC_CONST_16 T1_flexOverheadPC[];
T1_EXTERN const T1_taskIdx_t T1_SEC_CONST_16 T1_nOfTasksPC[];
T1_EXTERN const T1_uint16_t T1_SEC_CONST_16 T1_startOfFrameEventPC[];
T1_EXTERN const T1_uint16_t T1_SEC_CONST_16 T1_cpuLoadTxPeriodPC[];
/*! For each core, the initializer for T1_contGlobals_t#analysisCapacity_, see \ref
 * analysisCapacity. */
T1_EXTERN const T1_anaCapa_t T1_SEC_CONST_16 T1_defaultAnalysisCapacityPC[];
T1_EXTERN const T1_resultsIdx_t T1_SEC_CONST_16 T1_nOfResultsPC[];
T1_EXTERN const T1_taskIdx_t T1_SEC_CONST_16 T1_bgTaskIdxPC[];
#    define T1_STOP_SEC_CONST_16
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_EXTERN T1_stpwConfig_t * const T1_SEC_CONST_32 T1_stpwConfigPC[];
T1_EXTERN const T1_csrnData_t * const T1_SEC_CONST_32 T1_csrnConfigPC[];
T1_EXTERN T1_taskData_t * const T1_SEC_CONST_32 T1_taskDataPC[];
T1_EXTERN T1_stpwData_t * const T1_SEC_CONST_32 T1_stpwDataPC[];
T1_EXTERN T1_csrnData_t * const T1_SEC_CONST_32 T1_csrnDataPC[];
/*!
 * \brief For each core, a pointer to the T1.cont result buffer.
 */
T1_EXTERN T1_resultTime_t * const T1_SEC_CONST_32 T1_resultBufferPC[];
T1_EXTERN T1_taskStackElem_t * const T1_SEC_CONST_32 T1_taskStackPC[];
T1_EXTERN T1_vStpwMapping_t * const T1_SEC_CONST_32 T1_vStpwPC[];
T1_EXTERN T1_focusData_t * const T1_SEC_CONST_32 T1_focusPC[];
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

/* Public for debugger interface */
#    define T1_START_SEC_VAR_POWER_ON_CLEARED_8
#    include "T1_MemMap.h"
/*!
 * \brief For each core, the T1_ContBgHandler T1.cont status.
 */
T1_EXTERN T1_contStatus_t T1_SEC_VAR_POWER_ON_CLEARED_8 T1_contBgStatusPC[];
/*!
 * For each core, the T1_Handler T1.cont status.
 */
T1_EXTERN T1_contStatus_t T1_SEC_VAR_POWER_ON_CLEARED_8 T1_contHandlerStatusPC[];
#    define T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#    include "T1_MemMap.h"

#    if defined T1_MULTICORE_CLONE
#        define T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"
/*!
 * \brief For each core, the T1_ContBgHandler T1.cont status.
 */
T1_EXTERN T1_contStatus_t T1_CLONE_SEC_VAR_POWER_ON_CLEARED_8 T1_contBgStatus;
/*!
 * For each core, the T1_Handler T1.cont status.
 */
T1_EXTERN T1_contStatus_t T1_CLONE_SEC_VAR_POWER_ON_CLEARED_8 T1_contHandlerStatus;
#        define T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"
#    else /* ! defined T1_MULTICORE_CLONE */
#        define T1_START_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"
T1_EXTERN T1_contStatus_t T1_SEC_VAR_POWER_ON_CLEARED_8 T1_contBgStatus;
T1_EXTERN T1_contStatus_t T1_SEC_VAR_POWER_ON_CLEARED_8 T1_contHandlerStatus;
#        define T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"
#    endif /* T1_MULTICORE_CLONE */

#    define T1_START_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"
T1_EXTERN T1_taskData_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_taskData[];
T1_EXTERN T1_stpwData_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_stpwData[];
T1_EXTERN T1_csrnData_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_csrnData[];
T1_EXTERN T1_resultTime_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_resultBuffer[];
T1_EXTERN T1_taskStackElem_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_taskStack[];
T1_EXTERN T1_vStpwMapping_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw[];
T1_EXTERN T1_focusData_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_focus[];
#    define T1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"

#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_CONT */

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for global functions ------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*!
 * \def T1_ContBgHandler
 * \ingroup T1_cont_interfaces
 * T1.cont background handler. Runs either in background or at a priority no
 * greater than T1_Handler(). See \ref PC and \ref INTRPT and #T1_contBgStatusPC and
 * T1_contGlobals_t#analysisCapacity_ and \ref RESBUF.
 * \returns   #T1_BUSY if T1_Handler() or T1_ContBgHandler() is already running due
 *            to unsupported re-entrancy,
 *            #T1_NOFUNC if no new trace events were available for processing (which
 *            is always then case when foreground T1.cont is enabled and
 *            T1_ContBgHandler is uselessly called),
 *            #T1_OK otherwise

 * \def T1_ContBgHandlerPC
 * \ingroup T1_cont_interfaces
 * T1.cont background handler. Runs either in background or at a priority no
 * greater than T1_Handler(). See \ref PC and \ref INTRPT and #T1_contBgStatusPC and
 * T1_contGlobals_t#analysisCapacity_ and \ref RESBUF.
 * \param[in] coreId_      the T1 logical ID of the calling core
 * \returns   #T1_BUSY if T1_HandlerPC() or T1_ContBgHandlerPC() is already running
 *            due to unsupported re-entrancy,
 *            #T1_NOFUNC if no new trace events were available for processing
 *            of if foreground T1.cont is enabled,
 *            #T1_OK otherwise

 * \def T1_ContReset
 * \ingroup T1_cont_interfaces
 * Reset the T1.cont internal analysis, for example after a task stack overflow
 * error. See \ref PC and \ref INTRPT.

 * \def T1_ContResetPC
 * \ingroup T1_cont_interfaces
 * Reset the T1.cont internal analysis, for example after a task stack overflow
 * error. See \ref PC and \ref INTRPT.
 * \param[in] coreId_      the T1 logical ID of the calling core

 * \def T1_ContResetBgTaskId
 * \ingroup T1_cont_interfaces
 * Reset the T1.cont internal analysis and update the T1 ID of the background task,
 * for example after a task stack overflow error. See \ref PC and \ref INTRPT.
 * \param[in] bgTaskId_    the T1 ID of the background task

 * \def T1_ContResetBgTaskIdPC
 * \ingroup T1_cont_interfaces
 * Reset the T1.cont internal analysis and update the T1 ID of the background task,
 * for example after a task stack overflow error. See \ref PC and \ref INTRPT.
 * \param[in] bgTaskId_    the T1 ID of the background task
 * \param[in] coreId_      the T1 logical ID of the calling core

 * \def T1_ContResetResults
 * \ingroup T1_cont_interfaces
 * Reset the T1.cont results, for example at a mode change.
 * See \ref PC and \ref INTRPT.

 * \def T1_ContResetResultsPC
 * \ingroup T1_cont_interfaces
 * Reset the T1.cont results, for example at a mode change.
 * See \ref PC and \ref INTRPT.
 * \param[in] coreId_      the T1 logical ID of the calling core
 */

#if defined T1_ENABLE && !defined T1_DISABLE_T1_CONT

#    define T1_START_SEC_CODE
#    include "T1_MemMap.h"

#    if defined T1_CONT_REMOTE
T1_EXTERN T1_status_t T1_CODE T1_ContBgHandlerDirectRCPC( T1_uint8Least_t coreId );
T1_EXTERN void T1_CODE T1_ContResetDirectRCPC( T1_uint8Least_t coreId,
                                               T1_taskId_t bgTaskId );
T1_EXTERN void T1_CODE T1_ContResetResultsDirectRCPC( T1_uint8Least_t coreId );
#        define T1_ContBgHandlerPC( coreId_ ) T1_ContBgHandlerDirectRCPC( coreId_ )
#        define T1_ContResetPC( coreId_ )                                            \
            T1_ContResetDirectRCPC( coreId_, T1_INVALID_TASK_ID )
#        define T1_ContResetBgTaskIdPC( coreId_, bgTaskId_ )                         \
            T1_ContResetDirectRCPC( coreId_, bgTaskId_ )
#        define T1_ContResetResultsPC( coreId_ )                                     \
            T1_ContResetResultsDirectRCPC( coreId_ )
#    else /* ! defined T1_CONT_REMOTE */
T1_EXTERN T1_status_t T1_CODE T1_ContBgHandlerDirectPC( T1_uint8Least_t coreId );
T1_EXTERN void T1_CODE T1_ContResetDirectPC( T1_uint8Least_t coreId,
                                             T1_taskId_t bgTaskId );
T1_EXTERN void T1_CODE T1_ContResetResultsDirectPC( T1_uint8Least_t coreId );
#        define T1_ContBgHandlerPC( coreId_ ) T1_ContBgHandlerDirectPC( coreId_ )
#        define T1_ContResetPC( coreId_ )                                            \
            T1_ContResetDirectPC( coreId_, T1_INVALID_TASK_ID )
#        define T1_ContResetBgTaskIdPC( coreId_, bgTaskId_ )                         \
            T1_ContResetDirectPC( coreId_, bgTaskId_ )
#        define T1_ContResetResultsPC( coreId_ )                                     \
            T1_ContResetResultsDirectPC( coreId_ )
#    endif /* defined T1_CONT_REMOTE */

#    define T1_ContBgHandler( ) T1_ContBgHandlerPC( T1_GetCoreIdOffset( ) )
#    define T1_ContReset( )     T1_ContResetPC( T1_GetCoreIdOffset( ) )
#    define T1_ContResetBgTaskId( bgTaskId_ )                                        \
        T1_ContResetBgTaskIdPC( T1_GetCoreIdOffset( ), bgTaskId_ )
#    define T1_ContResetResults( coreId_ )                                           \
        T1_ContResetResultsPC( T1_GetCoreIdOffset( ) )
/*!
 * \brief Configure an event chain at start-up.
 * \param[in] e1_    event chain start event, formed using T1_COMBINE_EVENT_INFO()
 * \param[in] e2_    event chain stop event, formed using T1_COMBINE_EVENT_INFO()
 * \param[in] swIdx_ see @ref EVENT_CHAINS for usage
 * \returns          #T1_FAILED if there is no available event chain
 *                   #T1_VALUE if stpwIdx is invalid
 *                   #T1_OK otherwise
 *
 * \note Once communications with the T1-HOST-SW have been established,
 *       event chains must be configured using the T1-HOST-SW only.
 *
 */
#    define T1_ConfigEventChain( e1_, e2_, swIdx_ )                                  \
        T1_ConfigEventChainPC( T1_GetCoreIdOffset( ), e1_, e2_, swIdx_ )

/*!
 * \brief   Callback function to act on a T1.cont error.
 * \ingroup T1_cont_callbacks
 * \param[in] coreId       the T1 logical core ID of the trace analyzed by T1.cont
 * \param[in] errMask      the current error mask, one or more of the following bits
 *                         might be set:
 *                         - #T1_INF_OVERHEADS_UPDATED
 *                         - #T1_WRN_INCOMPLETE_ANALYSIS
 *                         - #T1_WRN_CONSTRAINT_VIOLATED
 *                         - #T1_WRN_INVALID_CET_STPW
 *                         - #T1_WRN_RESULT_OUT_OF_RANGE
 *                         - #T1_ERR_FAULTY_TRACE_DATA
 *                         - #T1_ERR_STACK_OVERFLOW
 *                         - #T1_ERR_OVERRUN
 * \param[in] triggerMask  the mask of errors on which to trigger
 * \param[in] afterXevnts  the number of additional events to trace on this core
 *                         before tracing stops, see T1_SetStopTriggerPC()
 *
 * Called with interrupts enabled.
 *
 * \par Default Implementation
 * The default implementation traces the error mask as a user event and halts tracing
 * on every core using T1_AppSetStopTriggerAllCores().
 *
 */
T1_EXTERN void T1_CODE T1_ContErrCallbackPC( T1_uint8Least_t coreId,
                                             T1_uint8Least_t errMask,
                                             T1_uint8Least_t triggerMask,
                                             T1_nOfEntries_t afterXevnts );

/*!
 * \brief   Callback function to act on a T1.cont constraint violation.
 * \ingroup T1_cont_callbacks
 * \param[in] coreId       the T1 logical core ID of the trace analyzed by T1.cont
 * \param[in] result       the violating result in trace timer ticks
 * \param[in] idx          the index of the violated constraint
 * \param[in] afterXevnts  the number of additional events to trace on this core
 *                         before tracing actually stops, see T1_SetStopTriggerPC()
 *
 * Only used when background T1.cont is configured.
 * Called in the context of T1_ContBgHandlerPC().
 * Called with interrupts enabled.
 *
 * \par Default Implementation
 * The default implementation calls T1_ContCsrnCallbackNoSuspPC().
 *
 * \note This code should only be changed under advice from a GLIWA engineer.
 *
 */
T1_EXTERN void T1_CODE T1_ContCsrnCallbackPC( T1_uint8Least_t coreId,
                                              T1_resultTime_t result,
                                              T1_csrnIdx_t idx,
                                              T1_nOfEntries_t afterXevnts );

/*!
 * \brief   Callback function to act on a T1.cont constraint violation.
 * \ingroup T1_cont_callbacks
 * \param[in] coreId       the T1 logical core ID of the trace analyzed by T1.cont
 * \param[in] result       the violating result in trace timer ticks
 * \param[in] idx          the index of the violated constraint
 * \param[in] afterXevnts  the number of additional events to trace on this core
 *                         before tracing actually stops, see T1_SetStopTriggerPC()
 *
 * Only used when background T1.cont is configured.
 * Called in the context of T1_ContBgHandlerPC().
 * Called with interrupts enabled.
 *
 * \par Default Implementation
 * The default implementation traces the CPU load percentage as a user event
 * and halts tracing on every core using T1_coreTriggerCounter.
 *
 * \note This code should only be changed under advice from a GLIWA engineer.
 */
T1_EXTERN void T1_CODE T1_ContCsrnCallbackNoSuspPC( T1_uint8Least_t coreId,
                                                    T1_resultTime_t result,
                                                    T1_csrnIdx_t idx,
                                                    T1_nOfEntries_t afterXevnts );

/*!
 * \brief   Callback function to act on T1.cont overhead calibration.
 * \ingroup T1_cont_callbacks
 * \param[in] coreId    the T1 logical core ID of the trace analyzed by T1.cont
 * \param[in] errMask   the current error mask
 *
 * Called with interrupts enabled by background T1.cont. Called with interrupts
 * disabled by foreground T1.cont.
 *
 * \par Default Implementation
 * The default implementation frees the used event chains using
 * T1_CONT_STOP_CALIBRATION_PC() and resets T1.cont, which might have warnings
 * relating to previously uncalibrated overheads.
 */
T1_EXTERN void T1_CODE T1_ContOHCallbackPC( T1_uint8Least_t coreId,
                                            T1_uint8Least_t errMask );

/*!
 * \brief   Callout function returns CET of #T1_START_STOP ISRs.
 * \ingroup T1_cont_callouts
 * \param[in] coreId       the T1 logical core ID of the analyzed trace
 * \param[in] taskIdx      the T1.cont task index of the ISR
 * \returns   the T1.cont configured CET for an ISR too short to sensibly instrument
 *            with separate T1_TraceStart() and T1_TraceStop() events, see
 *            T1_TraceStartNoActStop().
 *
 */
T1_EXTERN T1_resultTime_t T1_CODE T1_ContStartStopCETPC( T1_uint8Least_t coreId,
                                                         T1_taskIdx_t taskIdx );

/*!
 * \brief   Callout function to translate a duration in synchronization timer ticks to
 *          trace timer ticks.
 * \ingroup T1_cont_callouts
 *
 * \note This callout function is generated into T1_configGen.c.
 *
 */
T1_EXTERN T1_longTime_t T1_CODE T1_SyncToTraceTimerPC( T1_uint8Least_t coreId,
                                                       T1_longTime_t getSwTime );

/*!
 * \brief   Callback function called when T1.cont has calculated a new CPU load value.
 * \ingroup T1_cont_callbacks
 * \param[in] coreId           the T1 logical core ID of the analyzed trace
 * \param[in] cpuLoadFrac      32-bit encoding of the CPU load fraction: te/to
 * \param[in] cpuLoadThreshold configured CPU load threshold
 * \param[in] afterXevnts      the number of additional events to trace on this core
 *                             before tracing stops, see T1_SetStopTriggerPC()
 *
 * - Called in the context of T1_ContBgHandlerPC(), or T1_HandlerPC() when
 *   [foreground T1.cont](@ref FOREGROUND_CONT) is enabled.
 * - Called for each basic scheduling frame (BSF),
 *   see [-osBasicSchedFrameName](@ref osBasicSchedFrameName)
 * - Called asynchronously with respect to the BSF
 *
 */
T1_EXTERN void T1_CODE T1_ContCPULoadCallbackPC( T1_uint8Least_t coreId,
                                                 T1_uint32_t cpuLoadFrac,
                                                 T1_uint8Least_t cpuLoadThreshold,
                                                 T1_nOfEntries_t afterXevnts );

T1_EXTERN void T1_CODE T1_ContResetCPULoadPC( T1_uint8Least_t coreId );
#    define T1_ContResetCPULoad( ) T1_ContResetCPULoadPC( T1_GetCoreIdOffset( ) )

/*!
 * \brief   Read the T1.cont maximum BSF CPU load (*pTe / *pTo).
 * \ifnot CERT_SECTION
 *   \copydetails T1_cont_cert_interfaces
 * \endif
 * \ingroup T1_cont_cert_interfaces
 * \param[in]  coreId the T1 logical core ID of the calling core
 * \param[out] pTo    over-all duration of the BSF frame
 * \param[out] pTe    total execution time of tasks and ISRs in the BSF frame
 *
 */
T1_EXTERN void T1_CODE T1_ContGetMaxCPULoadPC( T1_uint8Least_t coreId,
                                               T1_uint16_t *pTo,
                                               T1_uint16_t *pTe );

/*!
 * \brief   Read the T1.cont minimum BSF CPU load (*pTe / *pTo).
 * \ifnot CERT_SECTION
 *   \copydetails T1_cont_cert_interfaces
 * \endif
 * \ingroup T1_cont_cert_interfaces
 * \param[in]  coreId the T1 logical core ID of the calling core
 * \param[out] pTo    over-all duration of the BSF frame
 * \param[out] pTe    total execution time of tasks and ISRs in the BSF frame
 *
 */
T1_EXTERN void T1_CODE T1_ContGetMinCPULoadPC( T1_uint8Least_t coreId,
                                               T1_uint16_t *pTo,
                                               T1_uint16_t *pTe );

/*!
 * \brief   Read the task or ISR maximum CET.
 * \ifnot CERT_SECTION
 *   \copydetails T1_cont_cert_interfaces
 * \endif
 * \ingroup T1_cont_cert_interfaces
 * \param[in] coreId    the T1 logical core ID of the calling core
 * \param[in] taskIsrId T1 identifier for the task or ISR
 * \returns             the maximum CET observed by T1.cont for that task or ISR
 *                      in trace timer ticks of the designated T1 logical core
 *
 */
T1_EXTERN T1_resultTime_t T1_CODE
T1_ContGetTaskIsrMaxCETPC( T1_uint8Least_t coreId, T1_uint16Least_t taskIsrId );

/*!
 * \brief   Read the maximum stopwatch result.
 * \ifnot CERT_SECTION
 *   \copydetails T1_cont_cert_interfaces
 * \endif
 * \ingroup T1_cont_cert_interfaces
 * \param[in] coreId the T1 logical core ID of the calling core
 * \param[in] stpwId T1 identifier for the stopwatch
 * \returns          the maximum result observed by T1.cont for that stopwatch
 *                   in trace timer ticks of the designated T1 logical core
 *
 */
T1_EXTERN T1_resultTime_t T1_CODE T1_ContGetStopwatchMaxPC( T1_uint8Least_t coreId,
                                                            T1_uint16Least_t stpwId );

/*!
 * \brief   Read the minimum stopwatch result.
 * \ifnot CERT_SECTION
 *   \copydetails T1_cont_cert_interfaces
 * \endif
 * \ingroup T1_cont_cert_interfaces
 * \param[in] coreId the T1 logical core ID of the calling core
 * \param[in] stpwId T1 identifier for the stopwatch
 * \returns          the minimum result observed by T1.cont for that stopwatch
 *                   in trace timer ticks of the designated T1 logical core
 *
 */
T1_EXTERN T1_resultTime_t T1_CODE T1_ContGetStopwatchMinPC( T1_uint8Least_t coreId,
                                                            T1_uint16Least_t stpwId );

/*!
 * \brief   Read the T1.cont maximum BSF CPU load (*pTe / *pTo).
 * \ifnot CERT_SECTION
 *   \copydetails T1_cont_cert_interfaces
 * \endif
 * \ingroup T1_cont_cert_interfaces
 * \param[out] pTo_ over-all duration of the BSF frame
 * \param[out] pTe_ total execution time of tasks and ISRs in the BSF frame
 *
 */
#    define T1_ContGetMaxCPULoad( pTo_, pTe_ )                                       \
        T1_ContGetMaxCPULoadPC( T1_GetCoreIdOffset( ), ( pTo_ ), ( pTe_ ) )

/*!
 * \brief   Read the T1.cont minimum BSF CPU load (*pTe / *pTo).
 * \ifnot CERT_SECTION
 *   \copydetails T1_cont_cert_interfaces
 * \endif
 * \ingroup T1_cont_cert_interfaces
 * \param[out] pTo_ over-all duration of the BSF frame
 * \param[out] pTe_ total execution time of tasks and ISRs in the BSF frame
 *
 */
#    define T1_ContGetMinCPULoad( pTo_, pTe_ )                                       \
        T1_ContGetMinCPULoadPC( T1_GetCoreIdOffset( ), ( pTo_ ), ( pTe_ ) )

/*!
 * \brief   Read the task or ISR maximum CET.
 * \ifnot CERT_SECTION
 *   \copydetails T1_cont_cert_interfaces
 * \endif
 * \ingroup T1_cont_cert_interfaces
 * \param[in] taskIsrId_ T1 identifier for the task or ISR
 * \returns              the maximum CET observed by T1.cont for that task or ISR
 *                       in trace timer ticks of the designated T1 logical core
 *
 */
#    define T1_ContGetTaskIsrMaxCET( taskIsrId_ )                                    \
        T1_ContGetTaskIsrMaxCETPC( T1_GetCoreIdOffset( ), ( taskIsrId_ ) )

/*!
 * \brief   Read the maximum stopwatch result.
 * \ifnot CERT_SECTION
 *   \copydetails T1_cont_cert_interfaces
 * \endif
 * \ingroup T1_cont_cert_interfaces
 * \param[in] stpwId_ T1 identifier for the stopwatch
 * \returns           the maximum result observed by T1.cont for that stopwatch
 *                    in trace timer ticks of the designated T1 logical core
 *
 */
#    define T1_ContGetStopwatchMax( stpwId_ )                                        \
        T1_ContGetStopwatchMaxPC( T1_GetCoreIdOffset( ), ( stpwId_ ) )

/*!
 * \brief   Read the minimum stopwatch result.
 * \ifnot CERT_SECTION
 *   \copydetails T1_cont_cert_interfaces
 * \endif
 * \ingroup T1_cont_cert_interfaces
 * \param[in] stpwId_ T1 identifier for the stopwatch
 * \returns           the minimum result observed by T1.cont for that stopwatch
 *                    in trace timer ticks of the designated T1 logical core
 *
 */
#    define T1_ContGetStopwatchMin( stpwId_ )                                        \
        T1_ContGetStopwatchMinPC( T1_GetCoreIdOffset( ), ( stpwId_ ) )

/*!
 * Configure an event chain at start-up. Once communications with the T1-HOST-SW
 * have been established, event chains must be configured using the T1-HOST-SW only.
 * \param[in] coreId         the T1 logical core ID of the calling core
 * \param[in] startEventInfo event chain start event, formed using
 * T1_COMBINE_EVENT_INFO() \param[in] stopEventInfo  event chain stop event, formed
 * using T1_COMBINE_EVENT_INFO() \param[in] stpwIdx        see @ref EVENT_CHAINS for
 * usage \returns                  #T1_FAILED if there is no available event chain
 *                           #T1_VALUE if stpwIdx is invalid
 *                           #T1_OK otherwise
 */
T1_EXTERN T1_status_t T1_CODE T1_ConfigEventChainPC( T1_uint8Least_t coreId,
                                                     T1_eventInfo_t startEventInfo,
                                                     T1_eventInfo_t stopEventInfo,
                                                     T1_stpwIdx_t stpwIdx );
/*! \brief T1 helper function. */
T1_EXTERN void T1_CODE T1_DeleteCalibrationEventChainPC( T1_uint8Least_t coreId,
                                                         T1_stpwIdx_t stpwIdx );

#    if !defined T1_MULTICORE_CLONE
/*!
 * Configure the mask of errors on which to trigger in T1_ContErrCallbackPC().
 * \param[in] coreId_       the T1 logical core ID of the calling core
 * \param[in] mask_         the mask of errors on which to trigger
 */
#        define T1_ContSetTriggerMaskPC( coreId_, mask_ )                            \
            ( (void)( T1_contGlobalsPC[( coreId_ )]->triggerMask_ = ( mask_ ) ) )
/*!
 * Configure the mask of errors on which to trigger in T1_ContErrCallbackPC() on the
 * T1 logical core ID of the calling core.
 * \param[in] mask_         the mask of errors on which to trigger
 */
#        define T1_ContSetTriggerMask( mask_ )                                       \
            ( (void)( T1_contGlobalsPC[T1_GetCoreIdOffset( )]->triggerMask_ =        \
                          ( mask_ ) ) )
#    else /* clone */
#        define T1_ContSetTriggerMaskPC( coreId_, mask_ )                            \
            ( (void)( T1_contGlobals.triggerMask_ = ( mask_ ) ) )
#        define T1_ContSetTriggerMask( mask_ )                                       \
            ( (void)( T1_contGlobals.triggerMask_ = ( mask_ ) ) )
#    endif /* ! defined T1_MULTICORE_CLONE */

T1_EXTERN void T1_CODE T1_49672( T1_uint8Least_t coreId,
                                 T1_taskIdx_t taskIdx,
                                 T1_resultTime_t taskCET );
T1_EXTERN void T1_CODE T1_84399( T1_uint8Least_t coreId, T1_longTime_t now );

#    define T1_STOP_SEC_CODE
#    include "T1_MemMap.h"

#else /* ! defined T1_ENABLE || defined T1_DISABLE_T1_CONT */

#    define T1_ContBgHandlerPC( coreId_ )                      ( T1_NOFUNC )
#    define T1_ContResetPC( coreId_ )                          ( (void)0 )
#    define T1_ContResetBgTaskIdPC( coreId_, bgTaskId_ )       ( (void)0 )
#    define T1_ContResetResultsPC( coreId_ )                   ( (void)0 )
#    define T1_ContDisableAnalysisPC( coreId_ )                ( (void)0 )
#    define T1_ConfigEventChainPC( coreId_, e1_, e2_, swIdx_ ) ( T1_NOFUNC )
#    define T1_ContSetTriggerMaskPC( coreId_, mask_ )          ( (void)0 )
#    define T1_ContBgHandler( )                                ( T1_NOFUNC )
#    define T1_ContReset( )                                    ( (void)0 )
#    define T1_ContResetBgTaskId( bgTaskId_ )                  ( (void)0 )
#    define T1_ContResetResults( )                             ( (void)0 )
#    define T1_ContDisableAnalysis( )                          ( (void)0 )
#    define T1_ConfigEventChain( e1_, e2_, swIdx_ )            ( T1_NOFUNC )
#    define T1_ContSetTriggerMask( mask_ )                     ( (void)0 )
#    define T1_ContGetMaxCPULoadPC( coreId_, pTo_, pTe_ )                            \
        ( (void)( *( pTo_ ) = 1u, *( pTe_ ) = 0u ) )
#    define T1_ContGetMinCPULoadPC( coreId_, pTo_, pTe_ )                            \
        ( (void)( *( pTo_ ) = 1u, *( pTe_ ) = 0u ) )
#    define T1_ContGetTaskIsrMaxCETPC( coreId_, taskIsrId_ ) ( (T1_resultTime_t)0u )
#    define T1_ContGetStopwatchMaxPC( coreId_, stpwId_ )     ( (T1_resultTime_t)0u )
#    define T1_ContGetStopwatchMinPC( coreId_, stpwId_ )     ( (T1_resultTime_t)0u )
#    define T1_ContGetMaxCPULoad( pTo_, pTe_ )                                       \
        ( (void)( *( pTo_ ) = 1u, *( pTe_ ) = 0u ) )
#    define T1_ContGetMinCPULoad( pTo_, pTe_ )                                       \
        ( (void)( *( pTo_ ) = 1u, *( pTe_ ) = 0u ) )
#    define T1_ContGetTaskIsrMaxCET( taskIsrId_ ) ( (T1_resultTime_t)0u )
#    define T1_ContGetStopwatchMax( stpwId_ )     ( (T1_resultTime_t)0u )
#    define T1_ContGetStopwatchMin( stpwId_ )     ( (T1_resultTime_t)0u )
#    define T1_contRevision                       ( 0uL )

#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_CONT */

#define T1_START_SEC_VAR_POWER_ON_CLEARED_8
#include "T1_MemMap.h"
/*!
 * \brief Undefined symbol to catch an invalid event chain index. Referencing it
 *  would indicate an illegal event chain ID, see \ref EVENT_CHAINS_CONFIG.
 */
T1_EXTERN T1_uint8_t T1_invalidCETeventChainIdx;
#define T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#include "T1_MemMap.h"

/**@}*/

/*----------------------------------------------------------------------------------*/
/*--- documentation ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_DOXYGEN_ONLY
/* clang-format off */

/*!
 * \page T1_cont_page T1.cont
 *
 * T1.cont is a plugin of T1 that allows for continues timing analysis and supervision
 * on the target. The timing analysis and supervision is performed in the
 * T1-TARGET-SW, the T1-HOST-SW is only used for displaying the measurement
 * results.
 *
 * - \subpage CONSTRAINTS
 * - \subpage EVENT_CHAINS
 * - \subpage FOREGROUND_CONT
 * - \subpage RESBUF
 *
 */

/*!
 * \page RESBUF Preserving T1.cont results over reset

It is possible to preserve the T1.cont result data over a processor reset. The
principle is to copy the T1.cont result buffer, at shutdown, to memory that remains
intact through reset and to restore it from that memory after T1_InitPC().
Kinds of memory that persist through reset include flash, NVRAM and, for a soft
reset, static RAM.

Buffer size {#RESBUFSIZE}
===========
T1.cont uses #T1_resultBufferPC to hold the core-specific result buffers. For example
#T1_resultBufferPC[0] holds the pointer to the core 0 specific result buffer
#T1_resultBuffer0.

The number of entries in the result buffer can be retrieved with the
following formula:
~~~~~~~~~~~~~~~{.c}
...*/
T1_uint8Least_t const coreId = T1_GetCoreIdOffset( );
T1_uint16Least_t const resultBufferEntries = 1u + ( ~0xFu & (0xFu + T1_nOfResultsPC[coreId] ) );
/*...
~~~~~~~~~~~~~~~

T1-TARGET-SW accesses {#RESBUFACC}
=====================
For a 32-bit processor, T1.cont writes to each 32-bit element of the core-specific
result buffer only using atomic, 32-bit write instructions. This means that the
buffer state is always consistent and that it is safe to read a 'snapshot' image of
the buffer at any time without regard for any synchronization.

Saving the T1.cont result buffer {#RESBUFSAV}
================================
For 32-bit implementations of the T1-TARGET-SW, it is always safe to read the array
pointed to by #T1_resultBufferPC. This means that, at shutdown, the current results
can be saved to non-volatile memory and be restored after reset.

Restoring the T1.cont result buffer {#RESBUFREST}
===================================
The T1-TARGET-SW API call T1_InitPC() initializes the array pointed to by
#T1_resultBufferPC, setting maximum value to zero so that all new results are
captured.
To use older, saved results from before a reset, it is possible to restore the
array pointed to by #T1_resultBufferPC from NVRAM between T1_InitPC() and the first
call to T1_ContBgHandlerPC(). As it is often important to minimize time in
T1_AppInit(), it is possible to perform the restore in T1_AppBackgroundHandler()
just before the first call to T1_ContBgHandlerPC().

Preserving T1.cont results over soft reset {#RESBUFSOFT}
==========================================
After a soft reset, if the RAM containing the T1.cont result buffer is intact and
not modified by the start-up code, it is sufficient to simply copy the array
pointed to by #T1_resultBufferPC and to restore it again between T1_InitPC() and
T1_ContBgHandlerPC().

For example, if the variable softResetDetected indicated a soft reset in T1_AppInit():
~~~~~~~~~~~~~~~{.c}
...*/

T1_uint8Least_t const coreId = T1_GetCoreIdOffset( );
T1_uint16Least_t const resultBufferEntries = 1u + ( ~0xFu & (0xFu + T1_nOfResultsPC[coreId] ) );

/* Array large enough to back up the T1.cont result buffer. */
T1_resultTime_t backupResultBuffer[resultBufferEntries];

if( softResetDetected )
{
    /* Save T1.cont result buffer */
    T1_uint16Least_t i;
    for( i = 0; i < resultBufferEntries; ++i )
    {
        backupResultBuffer[i] = T1_resultBufferPC[coreId][i];
    }
}

...

if( T1_OK != T1_InitPC( coreId, T1_pluginTable ) )
{
    for( ;; )
    {
        /* Infinite loop to trap init failure */
    }
}

...

if( softResetDetected )
{
    /* Restore T1.cont result buffer */
    T1_uint16Least_t i;
    for( i = 0; i < resultBufferEntries; ++i )
    {
        T1_resultBufferPC[coreId][i] = backupResultBuffer[i];
    }
}

/*...
~~~~~~~~~~~~~~~

 */

/*!
 * \page EVENT_CHAINS Event chains

The concept of event chains allows to set stopwatches at
run-time, based on existing instrumentation events. In that sense they can be
considered as virtual stopwatches. The advantages of this concept are:
- the existing instrumentation (tasks/ISRs/stopwatches) can be reused: the valuable
  trace buffer is not wasted due to redundant instrumentation
- being applicable on T1.flex UEC and UED events, a manifold number of event
  chains can be configured at run-time eliminating the need for a rebuild
- the default timing results for tasks and ISRs calculated by T1.cont can be
  efficiently reduced to only provide CET[max]/GET[max]. Additional task results
  can be obtained by applying an event chain to the existing task/ISR instrumentation

Event chains can be configured either by an initialization in the T1-TARGET-SW of by
using the T1-HOST-SW (see the GUI help for more information).

Restrictions {#EVENT_CHAINS_RESTRICTIONS}
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


Event chains configuration {#EVENT_CHAINS_CONFIG}
==========================

Each of these event chains is fixed to either a CET or GET measurement, according to
the scheme shown in Table
@ref EVENT_CHAIN_ALLOCATION "Event Chain Allocation in the T1-TARGET-SW".
For the sake of convenience, the generated T1_config.h (or T1_ids.h respectively)
already defines two macros which map the CET or GET event chain IDs to their indices
for each core, such as #T1_CET_EVT_CHAIN_TO_IDX_PC and
#T1_GET_EVT_CHAIN_TO_IDX_PC.

Depending on your compiler settings, you may be forced to declare
\ref T1_invalidCETeventChainIdx but be careful not to define it, since referencing it
would indicate an illegal event chain ID that is intended to cause a link error!

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
@ref EVENT_CHAINS_REUSE_OVERHEAD to use these 3 GET event chain IDs.

If the event chain initialized on the target provides an additional task result the
T1-HOST-SW will automatically detect this and add it in the project explorer and
also apply the according labels in the trace viewer and T1.cont table view.
In all other cases the T1-HOST-SW will make use of a generic name containing
the event chain ID.

Reuse of event chains used for overhead calibration {#EVENT_CHAINS_REUSE_OVERHEAD}
===================================================


The T1-TARGET-SW performs an overhead calibration at start-up with the configuration
of the GET event chains IDs 1, 2 and 3, see #T1_CONT_CALIBRATE_OVERHEADS_NOSUSP_PC.

If these event chains need to be statically configured, it is possible in the
callback following overhead calibration, after the three event chains have been
deallocated from calibration.
It is necessary to configure the event chains with GET IDs 1, 2 or 3
only after the calibration has been stopped in T1_ContOHCallbackPC() by calling
#T1_CONT_STOP_CALIBRATION_PC.

The following example show how it can be configured on the core 0:
~~~~~~~~~~~~~~~{.c}
...*/

void T1_CODE T1_ContOHCallbackPC( T1_uint8Least_t coreId,
                                  T1_uint8Least_t errMask )
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
    T1_ContResetResultsPC( coreId );
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
#        endif /* defined T1_REMOTE_CONT */
}

/*...
~~~~~~~~~~~~~~~

 */

/*!
 * \page CONSTRAINTS Constraints

Constraints can be set on event chains and stopwatches to monitor minimum and/or
maximum duration. In order to allow user-defined measures on detection of a violation,
T1.cont also calls a callback function.

Each stopwatch and event chain supports up to one constraint. To add a second
constraint to a stopwatch, create a matching event chain that implements the second
constraint.

Each constraint to be used on the target and by the T1-HOST-SW needs to be allocated
at compile-time. It is good practice to allocate at least two constraints that can
be used by the T1-HOST-SW.

Default configuration {#CONSTRAINTS_DEFAULT_CONFIG}
=====================
A default configuration is generated that is active if the macro
#T1_CONT_DEFAULT_CONFIG_CONSTRAINT is defined. This is particularly useful
when no constraint needs to be configured on the target but rather be made available
for the T1-HOST-SW at run-time.

The number of allocated constraints is at least 1, this can be increased per system
via T1_UserCfg.inv and the [-numberOfConstraints](@ref numberOfConstraints) parameter:

~~~~~~~~~~~~~~~
-numberOfConstraints=2 ; number of constraints [1..64] (optional)
~~~~~~~~~~~~~~~

With the previous parameter set for each system, here is an example with two cores of
the default configuration generated in T1_configGen.c:
~~~~~~~~~~~~~~~{.c}
...*/

#   if defined T1_CONT_DEFAULT_CONFIG_CONSTRAINT
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_csrnData_t const     T1_SEC_CONST_32 T1_csrnConfig0[2] =
{
    T1_CONT_DEFAULT_CONFIG_CONSTRAINT,
    T1_CONT_DEFAULT_CONFIG_CONSTRAINT
};
T1_csrnData_t const     T1_SEC_CONST_32 T1_csrnConfig1[2] =
{
    T1_CONT_DEFAULT_CONFIG_CONSTRAINT,
    T1_CONT_DEFAULT_CONFIG_CONSTRAINT
};
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_csrnData_t const * const T1_SEC_CONST_32 T1_csrnConfigPC[2] =
{
    T1_csrnConfig0,
    T1_csrnConfig1
};
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#   endif /* defined T1_CONT_DEFAULT_CONFIG_CONSTRAINT */

/*...
~~~~~~~~~~~~~~~

Advanced configuration
======================

Invocation File Method {#CONSTRAINTS_CONFIG_INV}
----------------------

If the default configuration is not suitable, for example because we require some
constraint made available during the start-up phase, then the invocation file
parameter [-addConstraintToUserSW](@ref addConstraintToUserSW) can be used in order
to add a constraint to an existing ***T1*** user stopwatch.

Currently it is only possible to add constraints to ***T1*** user stopwatches using
an invocation file parameter. Please refer to the
[next section](@ref CONSTRAINTS_CONFIG_C_CODE) for a more flexible solution that also
allows adding constraints to [event chains](@ref EVENT_CHAINS).

C Code Method (legacy) {#CONSTRAINTS_CONFIG_C_CODE}
----------------------

If the default configuration is not suitable, for example because we require some
constraint made available during the start-up phase, then
#T1_CONT_DEFAULT_CONFIG_CONSTRAINT must be commented out.
Please remember the difficulty in correctly maintaining such a manual
configuration and only use it when necessary.

Additionally, the number of constraints per core must be defined. It can be done
either by adding the parameter -numberOfConstraints per system in T1_UserCfg.inv or by
adding the macro T1_NOF_CSRNS_CORE<coreID> in T1_AppInterface.h.
Please note that if the macro and the parameter are both present, but with different
values, an error will be generated during the generation.

The following example shows the configuration on the core 0 of a constraint
supervising the duration of the CET event chain with ID 0 being 80 microseconds at
maximum.
~~~~~~~~~~~~~~~{.c}
...*/
T1_STPW_IDX_CONSTRAINT( T1_CET_EVT_CHAIN_TO_IDX_PC( 0, 0u ),
                        T1_US_TO_TICKS_CORE0( 80u ),
                        T1_CSRN_MAX )
/*...
~~~~~~~~~~~~~~~

Alternatively, this example shows the configuration on the core 1 for the user
stopwatch with ID 2 and a supervision of its minimum duration of 10 milliseconds.
~~~~~~~~~~~~~~~{.c}
...*/

T1_STPW_IDX_CONSTRAINT( 2u, /* Stopwatch ID 2 */
                        T1_MS_TO_TICKS_CORE1( 10u ),
                        T1_CSRN_MIN )

/*...
~~~~~~~~~~~~~~~

We take the default generated code as template and adapt it for each core with the
constraint configuration while optionally keeping the allocation of one further
constraint per system for the T1-HOST-SW.
The index of the constraint in the array will be reported in case of constraint
violation:
~~~~~~~~~~~~~~~{.c}
...*/

#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_csrnData_t const     T1_SEC_CONST_32 T1_csrnConfig0[2] =
{
    T1_STPW_IDX_CONSTRAINT( T1_CET_EVT_CHAIN_TO_IDX_PC( 0, 0u ),
                            T1_US_TO_TICKS_CORE0( 80u ),
                            T1_CSRN_MAX ),
    T1_CONT_DEFAULT_CONFIG_CONSTRAINT
};
T1_csrnData_t const     T1_SEC_CONST_32 T1_csrnConfig1[2] =
{
    T1_STPW_IDX_CONSTRAINT( 2u, /* Stopwatch ID 2 */
                            T1_MS_TO_TICKS_CORE1( 10u ),
                            T1_CSRN_MIN ),
    T1_CONT_DEFAULT_CONFIG_CONSTRAINT
};
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_csrnData_t const * const T1_SEC_CONST_32 T1_csrnConfigPC[2] =
{
    T1_csrnConfig0,
    T1_csrnConfig1
};
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"

/*...
~~~~~~~~~~~~~~~

Constraint callback {#CONSTRAINTS_CALLBACK}
===================
In case T1.cont observes the violation of a constraint, the callback function
T1_ContCsrnCallbackPC() is called. It is possible to adapt the callback to react
depending on the index of the constraint.

 */

/*!
 * \page FOREGROUND_CONT Foreground T1.cont

Foreground T1.cont performs T1.cont calculations in the context of T1_TraceEvent()
rather than in the context of T1_ContBgHandler(). This key difference means that
T1.cont results are available also during overload situations, i.e. when
background T1.cont would have been overrun.

At the expense of a far greater tracing overhead, foreground T1.cont is more
genuinely continuous than background T1.cont.
This is most obvious with a focus measurement, which is forced to stop when
background T1.cont is overrun, while it will continue with foreground T1.cont
when background activity and even low priority tasks are starved of execution
time on an overloaded CPU.

Event chain processing is relatively slow and raises even further the tracing
overhead. If this is required for task events (e.g. activation, start and stop)
then the overhead of task tracing may become too high for the application to function
correctly. To reduce the need for event chains on task events, foreground T1.cont
provides not only maximum CET but also minimum CET, maximum IPT and maximum Response
Time for each task. Background T1.cont, in contrast, would have used event chains to
obtain these results.

Configuration {#FOREGROUND_CONT_ENABLE}
=============

Foreground T1.cont is enabled when setting the invocation file parameter
[-foregroundCont](@ref foregroundCont).
It will define the macro #T1_FG_CONT in T1_config.h before including all the T1 header
files.

Timer Overflow {#FOREGROUND_CONT_TIMER}
==============

If any trace timer is not the sync timer, the sync timer is required to have at
least 28 counting bits, see #T1_SYNC_TIMER_WIDTH_BITS. Foreground T1.cont can
exploit a trace timer with more than 16 counting bits to detect and handle
intervals (between successive events) of more than 65535 trace timer ticks.

Two invocation file parameters are provided for this purpose, see
[-supportTimerOverflow](@ref supportTimerOverflow) and
[-detectTimerOverflow](@ref detectTimerOverflow).

Ideally, an analytical approach is used to avoid 16-bit overflows, in which case you
define neither of these macros and get no additional overhead. If there is a 16-bit
overflow when neither macro is defined then a downloaded trace will show incorrect
timing data but, as long as the interval is representable using the number of counting
trace timer bits, foreground T1.cont will continuously report correct timing results.
This is often the most practical option when using foreground T1.cont.

 */

/* clang-format on */
#endif /* defined T1_DOXYGEN_ONLY */

#endif /* T1_CONT_INTERFACE_H_ */
