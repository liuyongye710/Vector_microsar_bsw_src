/************************************************************************************/
/*! \file           T1_scopeInterface.h
 *
 *  \brief          T1.scope interface declarations and macros
 *
 *  \par Visibility
 *                  External
 *
 *  \author nick
 *
 *  \version 3.3.255.1 r60389
 *
 *  \copyright GLIWA embedded systems GmbH & Co. KG, Weilheim i.OB. All rights reserved
 ************************************************************************************/

#ifndef T1_SCOPE_INTERFACE_H_
#define T1_SCOPE_INTERFACE_H_ ( 1 )

/*!
 * \defgroup T1_scope T1.scope
 * \brief
 *
 * see \ref T1_scope_page
 *
 * @{
 */

/*!
 * \defgroup T1_scope_interfaces Interface Functions
 * \ingroup  T1_scope
 * \brief    Functions and function like macros to interface with T1.scope during
 *           runtime.
 */

/*!
 * \defgroup T1_scope_trace_interfaces Trace Event Interface Functions
 * \ingroup  T1_scope
 * \brief    Macro layer for T1_TraceEvent
 */

/*!
 * \defgroup T1_scope_cert_interfaces T1-TARGET-SW-CERT Only Interface Functions
 * \ingroup  T1_scope
 * \brief    Functions and function like macros to interface with T1.scope during
 *           runtime.
 * \details  These are only functional in T1-TARGET-SW-CERT releases, it is
 *           however safe to call them in normal T1-TARGET-SW releases.
 */

/*!
 * \defgroup T1_scope_callbacks User Callbacks
 * \ingroup  T1_scope
 * \brief    User callbacks provide notifications, which might be used by other SW
 *           components or the T1 integration itself.
 */

/*!
 * \defgroup T1_scope_callouts Callouts
 * \ingroup  T1_scope
 * \brief    Callouts are used to implement functionality, that can not be implemented
 *           as part of the T1-TARGET-SW library code.
 *
 * \note     The default implementations in *T1_config.c* should only be changed under
 *           advice from a GLIWA engineer, please contact \ref SUPPORT if needed.
 */

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_baseInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- macros used by type definitions ----------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_NOF_HANDLERS        ( 19u )

/* Additional values support event chains, calibration and error handling. */
#define T1_NOF_HANDLER_ENTRIES ( 43u )

#define T1_VS_ACT_IDX          ( 0 )
#define T1_VS_START_IDX        ( 1 )
#define T1_VS_STOP_IDX         ( 2 )
#define T1_VS_START_STPW_IDX   ( 3 )
#define T1_VS_STOP_STPW_IDX    ( 4 )
#define T1_VS_OTHER_IDX        ( 5 )
#define T1_VS_EVENT_KINDS      ( 6u )

#define T1_CC_QUEUE_MAX        ( 8u )

#define T1_OH_KINDS            ( 2u ) /* With and without T1.flex */
#define T1_FG_HANDLER_KINDS    ( 2u ) /* With and without event chain */

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/* The following type defines the structure of a single trace-entry  */
/* The array T1_traceBuffer of entries of this type define the trace buffer */
typedef T1_uint16_t T1_eventInfo_t;
typedef T1_uint32_t T1_traceEntry_t;
#define T1_DATA_BYTES_PER_ENTRY     ( 3u )
#define T1_DATA_BYTES_USERDATA_STOP ( 1u )
#define T1_INFO_BIT_WIDTH           ( 10 )
/*----------------------------------------------------------------------------------*/
/* When using a logic analyzer instead of the trace buffer, the event and the       */
/* info is written to a single cell which is traced. Instead of the target's        */
/* internal time, the logic analyzer's time stamp is used.                          */
typedef T1_uint16_t T1_traceCell_t;
/*----------------------------------------------------------------------------------*/
typedef T1_uint16Least_t T1_nOfEntries_t; //!< number of trace buffer entries
/*----------------------------------------------------------------------------------*/
/*! \brief Storage for Lamport's Bakery algorithm. */
typedef volatile struct
{
    T1_bool_t entering;
    T1_uint8_t align8;
    T1_uint16_t number;
} T1_bakery_t;
/*----------------------------------------------------------------------------------*/
/*! \brief T1.scope task identifier. */
typedef T1_sint16_t T1_taskId_t;
/*! \brief T1.scope stopwatch identifier. */
typedef T1_uint16_t T1_stpwId_t;
/*! \brief 32-bit type for time calculations. */
typedef T1_uint32_t T1_longTime_t;
/*! \brief Type for 31-bit T1.cont result (Bits 0..30) */
typedef T1_uint32_t T1_resultTime_t;
/*! \brief T1.cont constraint index. */
typedef T1_uint8_t T1_csrnIdx_t;
/*! \brief T1.cont stopwatch index. */
typedef T1_uint8_t T1_stpwIdx_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Used for one task being analyzed in the foreground. */
typedef struct
{
    T1_taskId_t prevTaskId;          //!< Preempted task ID
    T1_uint8_t instanceKey;          //!< Instance key of preempted task
    T1_uint8_t taskType;             //!< Flags e.g. multi-activation
    T1_stpwIdx_t vStpwStartIdx;      //!< Event chain to start at task start event
    T1_uint8_t align8;               //!< Only for alignment
    T1_uint16_t align16;             //!< Only for alignment
    T1_resultTime_t netAccumulation; //!< CET of preempted (or this in WAIT)
    T1_resultTime_t max;             //!< Maximum core execution time
    T1_resultTime_t min;             //!< Minimum core execution time
    T1_resultTime_t maxIPT;          //!< Maximum initial pending time
    T1_resultTime_t maxRT;           //!< Maximum response time
    union {
        T1_uint32_t data; //!< Activation data
        struct
        {
            T1_uint16_t dataOffset; //!< Index into multiple activation array
            T1_uint8_t activationHead;
            T1_uint8_t activationTail;
        } _;
    } act;
    T1_resultTime_t total; //!< Aggregated core execution time
} T1_taskFgData_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Used for one task being analyzed in the foreground. */
typedef const struct
{
    T1_uint8_t taskType; //!< Flags e.g. multi-activation
    T1_uint8_t align8;
    T1_uint16_t dataOffset; //!< Index into multiple activation array
} T1_taskFgInitData_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Used for task instance data. */
typedef union {
    struct
    {
        T1_uint8_t stpwType;          //!< CET/GET/DA
        T1_uint8_t instanceKeyOrTail; //!< Distinguish task instances
        T1_taskId_t taskIdOrHead;     //!< Started task ID for CET stopwatch
    } _;
    T1_uint32_t all; //!< Used for equality testing
} T1_taskInstance_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Used for one stopwatch being analyzed in the foreground. */
typedef struct
{
    T1_taskInstance_t _;
    T1_uint32_t start;                   //!< Start time
    /* Bits 31..30: focusIdx, bits 29..24 csrnIdx, bits 24..0 shortThreshold */
    T1_uint32_t focusCsrnShortThreshold; //!< Combined value
} T1_stpwFgData_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Used for one foreground virtual stopwatch (event chain). */
typedef struct
{
    T1_uint16_t eventInfo;
    T1_uint8_t startStopIdx;
    T1_stpwIdx_t stpwIdx;
} T1_vStpwData_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Used for BSF CPU load. */
typedef struct
{
    T1_longTime_t te_;
    T1_longTime_t lastFrameEventTime_;
    T1_longTime_t teTotal_;
    T1_longTime_t toTotal_;
    T1_uint16_t discardCount_;
    T1_uint16_t avgCPULoadCount_;
} T1_cpuLoad_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Part of one focus measurement. */
struct T1_focusStruct_t
{
    T1_uint32_t focusEventCount_;
    T1_resultTime_t focusTotalLow_;
    T1_resultTime_t focusIntervalLow_;
    union {
        T1_uint32_t both;
        struct
        {
            T1_uint16_t total;
            T1_uint16_t interval;
        } parts;
    } focusHighs_;
    T1_stpwIdx_t focusStpwIdx_;
    T1_sint8_t focusIdx_;
    union {
        T1_bool_t focusRunning_;
        T1_uint8_t focusState_;
    } _;
    T1_uint8_t coreId_;
    T1_uint32_t focusEventMax_;
};
/*! \brief Used for one focus measurement. */
typedef struct
{
    struct T1_focusStruct_t _;
    T1_resultTime_t focusLastTime_;
} T1_focusData_t;
/*----------------------------------------------------------------------------------*/
/*! \brief T1.scope data relating sync to trace time. */
typedef struct
{
    T1_tickUint_t traceTime;
    T1_uint32_t syncTime;
} T1_syncTimerBase_t;
/*----------------------------------------------------------------------------------*/
/*! \brief T1.cont data related to virtual stopwatches */
typedef struct
{
    T1_uint16_t eventInfoIn;
    T1_uint8_t eventOut;
    T1_stpwIdx_t stpwIdx;
} T1_vStpwMapping_t;
/*----------------------------------------------------------------------------------*/
/*! Used to cache virtual stopwatch data for fast access */
typedef union {
    struct
    {
        union {
            struct
            {
                T1_uint8_t taskInstKey;
                T1_uint8_t controllingStpwIdx;
            } d;
            T1_uint16_t copy;
        } u;
        T1_uint8_t controlledVStpwIdx;
        T1_bool_t isStarted;
    } d;
    T1_uint32_t clear;
} T1_csVStpwCache_t;
/*----------------------------------------------------------------------------------*/
/* polyspace<MISRA-C3:1.3,5.7:Not a defect:Justified> A structure forward declaration is intentional for information hiding */
struct T1_stpwDataStruct_t;
struct T1_scopeConstsStruct_t;
/*! \brief Jump table for foreground T1.cont helper functions. */
typedef struct
{
    void ( *pFgContRefreshTaskRTNoSuspPC )( T1_uint8Least_t coreId,
                                            T1_uint16Least_t nOfTasks );
    void ( *pFgContResetCPULoadNoSuspPC )( T1_uint8Least_t coreId,
                                           T1_uint16_t cpuLoadTxPeriod,
                                           T1_uint16_t avgCPULoadSamples );
    T1_uint8Least_t ( *pFgContGetTaskResultPC )( T1_uint8Least_t coreId,
                                                 T1_uint16Least_t taskIdx,
                                                 T1_resultTime_t *pResult );
    void ( *pFgContResetTaskPC )( T1_uint8Least_t coreId,
                                  T1_uint16Least_t taskMinIdx,
                                  T1_uint16Least_t taskMaxIdx );
    void ( *pFgContResetStpwPC )( T1_uint8Least_t coreId,
                                  T1_uint16Least_t stpwMinIdx,
                                  T1_uint16Least_t stpwMaxIdx,
                                  struct T1_stpwDataStruct_t *pStpwConfig );
    T1_uint32_t ( *pFgContCalibrationPC )( T1_uint8Least_t coreId,
                                           T1_uint8Least_t phaseId,
                                           T1_uint32_t fgData );
    T1_uint8_t ( *pFgContChangedStatusPC )( T1_uint8Least_t coreId );
    void ( *pFgContStartFocusPC )( T1_uint8Least_t coreId, T1_sint8_t _focusIdx );
    void ( *pFgContHaltFocusPC )( T1_uint8Least_t coreId, T1_sint8_t _focusIdx );
    void ( *pFgContSetVSNoSuspPC )( T1_uint8Least_t coreId,
                                    T1_uint32_t vStpwStartStopEventInfo,
                                    T1_stpwIdx_t stpwIdx,
                                    T1_uint8_t stpwCfg );
    void ( *pFgContUnsetVSPC )( T1_uint8Least_t coreId, T1_stpwIdx_t stpwIdx );
    void ( *pFgContSetConstraintPC )( T1_uint8Least_t coreId,
                                      T1_stpwIdx_t stpwIdx,
                                      T1_csrnIdx_t csrnIdx,
                                      T1_longTime_t threshold );
    T1_uint8_t *( *pFgContAllocCCVS )( void );
    void ( *pFgContConfigCCVS )( void );
    void ( *pFgContSetCCVSPC )( T1_uint8Least_t coreId,
                                T1_uint8Least_t analysisCoreId );
    void ( *pFgContCCVSPC )( T1_uint8Least_t coreId,
                             T1_uint8Least_t analysisCoreId,
                             T1_uint32_t syncTime );
    T1_resultTime_t ( *pFgContGetCCVSMinNoSusp )( void );
    T1_resultTime_t ( *pFgContGetCCVSMaxNoSusp )( void );
    void ( *pFgContResetCCVSMinMax )( void );
    void ( *pFgContInitNoSuspPC )( T1_uint8Least_t coreId );
    void ( *pFgContUpdateBsfPC )( T1_uint8Least_t coreId, T1_eventInfo_t bsfDelim );
    void ( *pFgContScopeOHHelper )(
        const struct T1_scopeConstsStruct_t *pScopeConsts );
    void ( *pFgContFlexOHHelper )( const struct T1_scopeConstsStruct_t *pScopeConsts,
                                   T1_eventInfo_t startEventInfo,
                                   T1_eventInfo_t stopEventInfo );
    void ( *pFgContRefreshCCVSPC )( T1_uint8Least_t coreId,
                                    T1_uint8Least_t analysisCoreId );
} T1_fgContHelpers_t;
/*----------------------------------------------------------------------------------*/
/*! \brief T1.scope global data for one core. */
typedef struct
{
    /* 0 */
    union {
        T1_uint32_t combined;
        struct
        {
            T1_uint16_t wrIdx;
            T1_uint16_t wrWrapCounter;
        } _;
    } volatile tB;
    T1_uint16_t compareIdx;
    T1_uint8_t compareState;
    T1_uint8_t syncPeriodCounter;
    T1_uint16_t triggerIdx;
    T1_uint16_t streamBlockIdx;
    T1_uint16_t streamBlockEvents;
    T1_uint8_t triggerWrapMark;
    T1_uint8_t streamSeqIdx;
    /* 16 */
    T1_syncTimerBase_t _;
    T1_uint32_t syncTimeHigh;
    T1_uint8_t volatile scopeState;    /* See state machine */
    T1_uint8_t partCount;              /* For buffer > 64KB */
    T1_uint16_t bufferEntriesMinusOne; /* Duplicate in RAM */
    /* 32 */
    T1_uint32_t transmitControlMask;        /* Messages to transmit */
    T1_traceEntry_t T1_FARPTR pTraceBuffer; /* Duplicate in RAM */
} T1_scopeGlobals_t;
/*----------------------------------------------------------------------------------*/
struct T1_scopeFgConstsStruct_t;
typedef T1_tickUint_t ( *T1_pFgContEventHandler_t )(
    struct T1_scopeFgConstsStruct_t const *pScopeFgConsts,
    T1_eventInfo_t eventInfo,
    T1_uint32_t syncTime,
    T1_uint32_t traceTime );
/* polyspace<MISRA-C3:1.3,5.7:Not a defect:Justified> Checker artefact: Tool seems to be confused by struct forward declaration. */
struct T1_contGlobalsStruct_t;
/*! \brief T1.scope global data for one core. */
typedef struct
{
    T1_scopeGlobals_t _;
    T1_longTime_t now_;
    T1_resultTime_t netTaskAccumulation_; /* No init required because background task
                                             has no CET */
    T1_taskInstance_t currentTask_;
    T1_uint16_t overhead_[T1_OH_KINDS];
    T1_uint8_t cpuLoadMultiplier_; /* Zero in background task */
    T1_uint8_t taskInstanceSeed_;
    T1_uint16_t maxNofTasks_;
    T1_uint8_t nOfUserStpws_;
    T1_uint8_t nOfNonVrtlStpws_;
    T1_uint8_t volatile cCStpwHead;
    T1_uint8_t volatile cCStpwTail;
    T1_longTime_t bsfTe;
    T1_longTime_t bsfStopTime;
    T1_uint8_t pHandlerIdx[T1_NOF_HANDLERS];
    T1_uint8_t status;
    T1_uint16_t tmp_;
    T1_eventInfo_t bsfDelimiter;
    T1_cpuLoad_t cpuLoadData;
    void ( *pFgVStpwAll )( struct T1_scopeFgConstsStruct_t const *pScopeConsts,
                           T1_uint16_t eventInfo,
                           T1_uint32_t traceTime,
                           T1_vStpwMapping_t const *vStpws );
    T1_vStpwData_t ccvsData[T1_VS_EVENT_KINDS];
    T1_uint32_t cCStpwData[T1_CC_QUEUE_MAX];
    T1_uint32_t cCNow;
    T1_uint32_t handlerConfigMask;
} T1_scopeFgGlobals_t;
/*----------------------------------------------------------------------------------*/
/*
 * Elements 'bufferEntriesMinusOne' and 'syncTimerWidthBits' are not strictly
 * necessary but they are useful and, without them, we would have required alignment
 * padding.
 */
/*! \brief T1.scope constant data for one core. */
typedef const struct T1_scopeConstsStruct_t
{
    union {
        T1_scopeGlobals_t *pScopeGlobals;     //!< Non-consts
        T1_scopeFgGlobals_t *pScopeFgGlobals; //!< Non-consts with foreground T1.cont
    } _;
    T1_traceEntry_t T1_FARPTR pTraceBuffer; //!< Trace buffer
    T1_uint16_t bufferEntriesMinusOne;
    T1_bool_t syncTimerIsTraceTimer;
    T1_uint8_t syncTimerWidthBits;
    T1_uint8_t traceTimerWidthBits;
    T1_uint8_t coreId;
    T1_uint16_t bufferEntries; //!< Trace buffer entries
    /* 16 */
    T1_tickUint_t volatile const *pTraceTimer; //!< Null unless timer is memory-mapped
    T1_bool_t traceWideSyncTimer;
    T1_uint8_t nOfVrtlStpws;
    T1_uint16_t fgContTaskActEntries;
    T1_tickUint_t ( *pNoSuspTime )( struct T1_scopeConstsStruct_t const *pScopeConsts,
                                    T1_eventInfo_t eventInfo,
                                    T1_tickUint_t time );
    T1_tickUint_t ( *pUint32RestNoSusp )(
        struct T1_scopeConstsStruct_t const *pScopeConsts, T1_uint32_t data );
    T1_tickUint_t ( *pUint56RestNoSusp )(
        struct T1_scopeConstsStruct_t const *pScopeConsts,
        T1_uint32_t dataLow,
        T1_uint32_t dataHigh );
} T1_scopeConsts_t;
/*----------------------------------------------------------------------------------*/
/*! \brief T1.scope constant data for one core extended for foreground T1.cont. */
typedef const struct T1_scopeFgConstsStruct_t
{
    T1_scopeConsts_t _;
    T1_tickUint_t ( *pDispatcher )(
        struct T1_scopeFgConstsStruct_t const *pScopeConsts,
        T1_eventInfo_t eventInfo,
        T1_uint8Least_t handlerIdx );
    T1_uint16_t maxNofTasks_;
    T1_uint8_t nOfUserStpws_;
    T1_uint8_t nOfNonVrtlStpws_;
    T1_uint8_t nOfFocusMeasurements_;
    T1_uint8_t nOfConstraints_;
    T1_uint16_t align16;
    T1_uint32_t minusNOfFlexStpws;
    T1_taskFgData_t *pTaskData;
    T1_focusData_t *pFocus;
    T1_stpwFgData_t *pStpwData;
    void const *pContHandlerStatus; /* T1_contStatus_t is out-of-scope here. */
    void ( *pFgVStpwAll )( struct T1_scopeFgConstsStruct_t const *pScopeConsts,
                           T1_uint16_t eventInfo,
                           T1_uint32_t traceTime,
                           T1_vStpwMapping_t const *vStpws );
    T1_resultTime_t *pStpwResults;
    T1_vStpwMapping_t *pVStpws_;      /* cached T1_vStpw (address) */
    T1_vStpwMapping_t *pVStpwStarts_; /* upper half of T1_vStpw */
    T1_csVStpwCache_t *pCsVStpwCache_;
    T1_pFgContEventHandler_t pHandler[T1_NOF_HANDLER_ENTRIES];
} T1_scopeFgConsts_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Initial values for Foreground T1.cont */
typedef const struct
{
    T1_uint16_t overhead_;
    T1_uint16_t flexOverhead_;
    T1_uint16_t flexEpilogueOverhead_;
    T1_uint16_t align16_;
    /* 64-bit aligned */
    T1_uint32_t handlerConfigMask;
    T1_uint16_t align16;
    T1_eventInfo_t bsfDelimiter;
} T1_scopeFgGlobalsInit_t;
/*----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/*--- macros, inline functions and forward declarations ----------------------------*/
/*----------------------------------------------------------------------------------*/

/*! \brief Is tracing enabled? See \ref PC. \ingroup T1_scope_trace_interfaces */
#define T1_IS_TRACING_ENABLED_PC( coreId_ )                                          \
    ( 2u != T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ )->_.pScopeGlobals->compareState )
/*! \brief Is tracing enabled? \ingroup T1_scope_trace_interfaces */
#define T1_IS_TRACING_ENABLED( )                                                     \
    ( 2u                                                                             \
      != T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) )                         \
             ->_.pScopeGlobals->compareState )
/*! \brief Convert a time in nanoseconds to core 0 trace timer ticks. */
#define T1_NS_TO_TICKS_CORE0( ns_ )                                                  \
    ( (T1_tickUint_t)( 0 == ( ns_ ) ? 0.0f                                           \
                                    : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE0_NS ) )
/*! \brief Convert a time in microseconds to core 0 trace timer ticks. */
#define T1_US_TO_TICKS_CORE0( us_ )                                                  \
    ( (T1_tickUint_t)( 0 == ( us_ )                                                  \
                           ? 0.0f                                                    \
                           : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE0_NS ) )
/*! \brief Convert a time in milliseconds to core 0 trace timer ticks. */
#define T1_MS_TO_TICKS_CORE0( ms_ )                                                  \
    ( (T1_tickUint_t)( 0 == ( ms_ )                                                  \
                           ? 0.0f                                                    \
                           : ( (ms_)*1000000.0f ) / T1_TICK_DURATION_CORE0_NS ) )
#if 1 < T1_NOF_CORES
/*! \brief Convert a time in nanoseconds to core 1 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE1( ns_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE1_NS ) )
/*! \brief Convert a time in microseconds to core 1 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE1( us_ )                                              \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE1_NS ) )
/*! \brief Convert a time in milliseconds to core 1 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE1( ms_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE1_NS ) )
#endif /* 1 < T1_NOF_CORES */
#if 2 < T1_NOF_CORES
/*! brief Convert a time in nanoseconds to core 2 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE2( ns_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE2_NS ) )
/*! \brief Convert a time in microseconds to core 2 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE2( us_ )                                              \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE2_NS ) )
/*! \brief Convert a time in milliseconds to core 2 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE2( ms_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE2_NS ) )
#endif /* 2 < T1_NOF_CORES */
#if 3 < T1_NOF_CORES
/*! brief Convert a time in nanoseconds to core 3 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE3( ns_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE3_NS ) )
/*! \brief Convert a time in microseconds to core 3 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE3( us_ )                                              \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE3_NS ) )
/*! \brief Convert a time in milliseconds to core 3 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE3( ms_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE3_NS ) )
#endif /* 3 < T1_NOF_CORES */
#if 4 < T1_NOF_CORES
/*! brief Convert a time in nanoseconds to core 4 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE4( ns_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE4_NS ) )
/*! \brief Convert a time in microseconds to core 4 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE4( us_ )                                              \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE4_NS ) )
/*! \brief Convert a time in milliseconds to core 4 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE4( ms_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE4_NS ) )
#endif /* 4 < T1_NOF_CORES */
#if 5 < T1_NOF_CORES
/*! brief Convert a time in nanoseconds to core 5 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE5( ns_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE5_NS ) )
/*! \brief Convert a time in microseconds to core 5 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE5( us_ )                                              \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE5_NS ) )
/*! \brief Convert a time in milliseconds to core 5 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE5( ms_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE5_NS ) )
#endif /* 5 < T1_NOF_CORES */
#if 6 < T1_NOF_CORES
/*! brief Convert a time in nanoseconds to core 6 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE6( ns_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE6_NS ) )
/*! \brief Convert a time in microseconds to core 6 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE6( us_ )                                              \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE6_NS ) )
/*! \brief Convert a time in milliseconds to core 6 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE6( ms_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE6_NS ) )
#endif /* 6 < T1_NOF_CORES */
#if 7 < T1_NOF_CORES
/*! brief Convert a time in nanoseconds to core 7 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE7( ns_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE7_NS ) )
/*! \brief Convert a time in microseconds to core 7 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE7( us_ )                                              \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE7_NS ) )
/*! \brief Convert a time in milliseconds to core 7 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE7( ms_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE7_NS ) )
#endif /* 7 < T1_NOF_CORES */
#if 8 < T1_NOF_CORES
/*! brief Convert a time in nanoseconds to core 8 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE8( ns_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE8_NS ) )
/*! \brief Convert a time in microseconds to core 8 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE8( us_ )                                              \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE8_NS ) )
/*! \brief Convert a time in milliseconds to core 8 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE8( ms_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE8_NS ) )
#endif /* 8 < T1_NOF_CORES */
#if 9 < T1_NOF_CORES
/*! brief Convert a time in nanoseconds to core 9 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE9( ns_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE9_NS ) )
/*! \brief Convert a time in microseconds to core 9 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE9( us_ )                                              \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE9_NS ) )
/*! \brief Convert a time in milliseconds to core 9 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE9( ms_ )                                              \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE9_NS ) )
#endif /* 9 < T1_NOF_CORES */
#if 10 < T1_NOF_CORES
/*! brief Convert a time in nanoseconds to core 10 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE10( ns_ )                                             \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE10_NS ) )
/*! \brief Convert a time in microseconds to core 10 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE10( us_ )                                             \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE10_NS ) )
/*! \brief Convert a time in milliseconds to core 10 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE10( ms_ )                                             \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE10_NS ) )
#endif /* 10 < T1_NOF_CORES */
#if 11 < T1_NOF_CORES
/*! brief Convert a time in nanoseconds to core 11 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE11( ns_ )                                             \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE11_NS ) )
/*! \brief Convert a time in microseconds to core 11 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE11( us_ )                                             \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE11_NS ) )
/*! \brief Convert a time in milliseconds to core 11 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE11( ms_ )                                             \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE11_NS ) )
#endif /* 11 < T1_NOF_CORES */
#if 12 < T1_NOF_CORES
/*! brief Convert a time in nanoseconds to core 12 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE12( ns_ )                                             \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE12_NS ) )
/*! \brief Convert a time in microseconds to core 12 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE12( us_ )                                             \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE12_NS ) )
/*! \brief Convert a time in milliseconds to core 12 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE12( ms_ )                                             \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE12_NS ) )
#endif /* 12 < T1_NOF_CORES */
#if 13 < T1_NOF_CORES
/*! brief Convert a time in nanoseconds to core 13 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE13( ns_ )                                             \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE13_NS ) )
/*! \brief Convert a time in microseconds to core 13 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE13( us_ )                                             \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE13_NS ) )
/*! \brief Convert a time in milliseconds to core 13 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE13( ms_ )                                             \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE13_NS ) )
#endif /* 13 < T1_NOF_CORES */
#if 14 < T1_NOF_CORES
/*! brief Convert a time in nanoseconds to core 14 trace timer ticks. */
#    define T1_NS_TO_TICKS_CORE14( ns_ )                                             \
        ( (T1_tickUint_t)( 0 == ( ns_ )                                              \
                               ? 0.0f                                                \
                               : ( (ns_)*1.0f ) / T1_TICK_DURATION_CORE14_NS ) )
/*! \brief Convert a time in microseconds to core 14 trace timer ticks. */
#    define T1_US_TO_TICKS_CORE14( us_ )                                             \
        ( (T1_tickUint_t)( 0 == ( us_ )                                              \
                               ? 0.0f                                                \
                               : ( (us_)*1000.0f ) / T1_TICK_DURATION_CORE14_NS ) )
/*! \brief Convert a time in milliseconds to core 14 trace timer ticks. */
#    define T1_MS_TO_TICKS_CORE14( ms_ )                                             \
        ( (T1_tickUint_t)( 0 == ( ms_ ) ? 0.0f                                       \
                                        : ( (ms_)*1000000.0f )                       \
                                              / T1_TICK_DURATION_CORE14_NS ) )
#endif /* 14 < T1_NOF_CORES */

/*!
 * \brief Do not use this task ID to trace a valid task
 */
#define T1_INVALID_TASK_ID             ( (T1_taskId_t)-1 )

#define T1_FG_CONT_INVALID_FOCUS_IDX   ( -1 )
#define T1_FG_CONT_INVALID_CSRN_IDX    ( -1 )

/* taskType flags */
#define T1_TT_FG_TASK                  ( 0x1u )
#define T1_TT_GET_CPU_LOAD_MULT( tt_ ) ( (tt_)&0x1u )
#define T1_TT_ALL_CORE_ID              ( 0xFu )
#define T1_TT_GET_CORE_ID( tt_ )       ( (T1_uint8Least_t)( ( ( tt_ ) >> 1 ) & 0xFu ) )
#define T1_TT_MULTI_ACT_SHIFT          ( 5 )
#define T1_TT_GET_MULTI_ACT( tt_ )     ( ( tt_ ) >> T1_TT_MULTI_ACT_SHIFT )

#define T1_FOCUS_DISABLED              ( 3u )
/* foreground T1.cont calibration phases */
#define T1_CALIBRATION_SCOPE_START     ( 0u )
#define T1_CALIBRATION_SCOPE_STOP      ( 1u )
#define T1_CALIBRATION_FLEX_START      ( 2u )
#define T1_CALIBRATION_FLEX_STOP       ( 3u )

#if !defined T1_OH_UNDERFLOW
#    define T1_OH_UNDERFLOW( coreId_ )
#endif

#define T1_DISPATCH_CORE0 T1_Dispatch0
#if defined T1_GET_RAW_TIME && defined T1_RAW_TO_TRACE_TIME
#    define T1_DISPATCH_CORE1  T1_Dispatch0
#    define T1_DISPATCH_CORE2  T1_Dispatch0
#    define T1_DISPATCH_CORE3  T1_Dispatch0
#    define T1_DISPATCH_CORE4  T1_Dispatch0
#    define T1_DISPATCH_CORE5  T1_Dispatch0
#    define T1_DISPATCH_CORE6  T1_Dispatch0
#    define T1_DISPATCH_CORE7  T1_Dispatch0
#    define T1_DISPATCH_CORE8  T1_Dispatch0
#    define T1_DISPATCH_CORE9  T1_Dispatch0
#    define T1_DISPATCH_CORE10 T1_Dispatch0
#    define T1_DISPATCH_CORE11 T1_Dispatch0
#    define T1_DISPATCH_CORE12 T1_Dispatch0
#    define T1_DISPATCH_CORE13 T1_Dispatch0
#    define T1_DISPATCH_CORE14 T1_Dispatch0
#else /* !defined T1_GET_RAW_TIME || !defined T1_RAW_TO_TRACE_TIME */
#    define T1_DISPATCH_CORE1  T1_Dispatch1
#    define T1_DISPATCH_CORE2  T1_Dispatch2
#    define T1_DISPATCH_CORE3  T1_Dispatch3
#    define T1_DISPATCH_CORE4  T1_Dispatch4
#    define T1_DISPATCH_CORE5  T1_Dispatch5
#    define T1_DISPATCH_CORE6  T1_Dispatch6
#    define T1_DISPATCH_CORE7  T1_Dispatch7
#    define T1_DISPATCH_CORE8  T1_Dispatch8
#    define T1_DISPATCH_CORE9  T1_Dispatch9
#    define T1_DISPATCH_CORE10 T1_Dispatch10
#    define T1_DISPATCH_CORE11 T1_Dispatch11
#    define T1_DISPATCH_CORE12 T1_Dispatch12
#    define T1_DISPATCH_CORE13 T1_Dispatch13
#    define T1_DISPATCH_CORE14 T1_Dispatch14
#endif /* defined T1_GET_RAW_TIME && defined T1_RAW_TO_TRACE_TIME */

/* Remove T1.flex bit. Range check is performed by callers. Override for debugging. */
#if !defined T1_CHECK_HNDLR_IDX
#    define T1_CHECK_HNDLR_IDX( pScopeConsts_, handlerIdx_ )                         \
        do                                                                           \
        {                                                                            \
            ( handlerIdx_ ) >>= 1;                                                   \
        }                                                                            \
        while( 0 )
#endif

#define T1_HANDLER_DIFF_SHIFT ( 27 )
#define T1_DIFF_MASK          ( 0xFFFFFFFFuL >> ( 32 - T1_HANDLER_DIFF_SHIFT ) )

#if defined T1_SUPPORT_TIMER_OVERFLOW || defined T1_DETECT_TIMER_OVERFLOW
/*
 * Support intervals over 65535 ticks at the expense of variable overhead.
 * Very large intervals are logged with T1_DISCONTINUITY. Shorter intervals are
 * logged by inserting T1_EMPTY events to ensure intervals are up to 65535 ticks.
 */
#    define T1_CHECK_DIFF( pScopeConsts_,                                            \
                           eventInfo_,                                               \
                           diff_,                                                    \
                           syncTime_,                                                \
                           handlerIdx_,                                              \
                           near_ )                                                   \
        do                                                                           \
        {                                                                            \
            if( 0uL != ( diff_ ) >> 16 )                                             \
            {                                                                        \
                if( 0uL != ( diff_ ) >> T1_HANDLER_DIFF_SHIFT )                      \
                {                                                                    \
                    return T1_##near_##BrokenInterval(                               \
                        ( pScopeConsts_ ),                                           \
                        ( eventInfo_ ),                                              \
                        T1_INSERT32( ( diff_ ),                                      \
                                     ( handlerIdx_ ),                                \
                                     T1_HANDLER_DIFF_SHIFT,                          \
                                     ( 32 - T1_HANDLER_DIFF_SHIFT ) ),               \
                        ( syncTime_ ) );                                             \
                }                                                                    \
                return T1_##near_##LargeInterval(                                    \
                    ( pScopeConsts_ ),                                               \
                    ( eventInfo_ ),                                                  \
                    T1_INSERT32( ( diff_ ),                                          \
                                 ( handlerIdx_ ),                                    \
                                 T1_HANDLER_DIFF_SHIFT,                              \
                                 ( 32 - T1_HANDLER_DIFF_SHIFT ) ),                   \
                    ( syncTime_ ) );                                                 \
            }                                                                        \
        }                                                                            \
        while( 0 )
#else /* When interval is already guaranteed <= 65535 ticks, minimize latency. */
#    define T1_CHECK_DIFF( pScopeConsts_,                                            \
                           eventInfo_,                                               \
                           diff_,                                                    \
                           syncTime_,                                                \
                           handlerIdx_,                                              \
                           near_ )                                                   \
        ( (void)0 )
#endif

/* No do ... while( 0 ) to avoid Tasking warnings */
#define T1_DISPATCH_PC( coreId_,                                                     \
                        pScopeConsts_,                                               \
                        eventInfo_,                                                  \
                        traceTime_,                                                  \
                        handlerIdx_,                                                 \
                        clm_,                                                        \
                        checkInterval_,                                              \
                        near_ )                                                      \
    {                                                                                \
        T1_scopeFgGlobals_t * const pScopeGlobals =                                  \
            pScopeConsts->_._.pScopeFgGlobals;                                       \
        T1_uint32_t syncTime;                                                        \
        T1_uint32_t withoutOverhead;                                                 \
        T1_uint32_t const diff =                                                     \
            ( ( traceTime_ ) - ( pScopeGlobals->now_ ) )                             \
            & ( 0xFFFFFFFFuL >> ( 32 - T1_TRACE_TIMER_BIT_LENGTH_CORE##coreId_ ) );  \
        pScopeGlobals->now_ += diff;                                                 \
        withoutOverhead =                                                            \
            diff - pScopeGlobals->overhead_[T1_IS_FLEX_HANDLER( handlerIdx_ )];      \
        T1_CHECK_HNDLR_IDX( pScopeGlobals, ( handlerIdx_ ) );                        \
        pScopeGlobals->netTaskAccumulation_ += withoutOverhead;                      \
        pScopeGlobals->bsfTe += withoutOverhead * ( clm_ );                          \
        if( T1_TRACE_TIMER_IS_SYNC_TIMER_CORE##coreId_ )                             \
        {                                                                            \
            syncTime = pScopeGlobals->now_;                                          \
        }                                                                            \
        else                                                                         \
        {                                                                            \
            T1_tickUint_t const traceTimerDelta =                                    \
                (traceTime_)-pScopeGlobals->_._.traceTime;                           \
            syncTime = pScopeGlobals->_._.syncTime                                   \
                       + T1_TRACE_TO_SYNC_TIME_CORE##coreId_( traceTimerDelta );     \
        }                                                                            \
        if( checkInterval_ )                                                         \
        {                                                                            \
            T1_CHECK_DIFF( pScopeConsts,                                             \
                           ( eventInfo_ ),                                           \
                           diff,                                                     \
                           syncTime,                                                 \
                           ( handlerIdx_ ),                                          \
                           near_ );                                                  \
        }                                                                            \
        {                                                                            \
            T1_uint8Least_t translatedHandlerIdx =                                   \
                pScopeGlobals->pHandlerIdx[( handlerIdx_ )];                         \
            if( T1_LAST_HNDLR_IDX < translatedHandlerIdx )                           \
            {                                                                        \
                translatedHandlerIdx = T1_LAST_HNDLR_IDX;                            \
            }                                                                        \
            return pScopeConsts->pHandler[translatedHandlerIdx](                     \
                pScopeConsts,                                                        \
                ( eventInfo_ ),                                                      \
                pScopeGlobals->now_,                                                 \
                syncTime );                                                          \
        }                                                                            \
    }

#define T1_SCOPE_PLUGIN_ID ( 1u )

/* Note check that eventId is not too large to be a valid shift. */
#define T1_FG_CONT_GET_HANDLER_IDX( eventInfo_, handlerIdx_ )                        \
    do                                                                               \
    {                                                                                \
        T1_uint16Least_t const eventId = ( eventInfo >> T1_INFO_BIT_WIDTH ) & 0x3Fu; \
        ( handlerIdx_ )                = T1_EMPTY_HNDLR_IDX;                         \
        if( ( eventId <= 15u )                                                       \
            && ( 0u                                                                  \
                 != ( ( ( ( 1u << T1_ACTIVATION_HNDLR_IDX )                          \
                          | ( 1u << T1_START_HNDLR_IDX )                             \
                          | ( 1u << T1_START_STOP_HNDLR_IDX )                        \
                          | ( 1u << T1_STOP_HNDLR_IDX )                              \
                          | ( 1u << T1_RESUME_HNDLR_IDX )                            \
                          | ( 1u << T1_WAIT_HNDLR_IDX )                              \
                          | ( 1u << T1_STOP_START_HNDLR_IDX )                        \
                          | ( 1u << T1_STPW_START_HNDLR_IDX )                        \
                          | ( 1u << T1_STPW_STOP_HNDLR_IDX )                         \
                          | ( 1u << T1_STPW_STOP_START_INC_HNDLR_IDX )               \
                          | ( 1u << T1_STPW_STOP_START_HNDLR_IDX ) )                 \
                        >> eventId )                                                 \
                      & 1u ) ) )                                                     \
        {                                                                            \
            ( handlerIdx_ ) = eventId;                                               \
            ( eventInfo_ ) &= T1_COMBINE_EVENT_INFO( 0u, 0xFFFFFFFFuL );             \
        }                                                                            \
    }                                                                                \
    while( 0 )

#define T1_EMPTY_HNDLR_IDX                    ( 0u )
#define T1_START_HNDLR_IDX                    ( 1u )
#define T1_STOP_HNDLR_IDX                     ( 2u )
#define T1_START_STOP_HNDLR_IDX               ( 3u )
#define T1_STOP_START_HNDLR_IDX               ( 4u )
#define T1_STPW_START_HNDLR_IDX               ( 5u )
#define T1_STPW_STOP_HNDLR_IDX                ( 6u )
#define T1_STPW_STOP_START_HNDLR_IDX          ( 7u )
#define T1_STPW_STOP_START_INC_HNDLR_IDX      ( 8u )
#define T1_FLEX_STPW_START_HNDLR_IDX          ( 9u )
#define T1_FLEX_STPW_STOP_HNDLR_IDX           ( 10u )
#define T1_START_NOACT_HNDLR_IDX              ( 11u )
#define T1_ACTIVATION_HNDLR_IDX               ( 12u )
#define T1_WAIT_HNDLR_IDX                     ( 13u )
#define T1_RESUME_HNDLR_IDX                   ( 14u )
#define T1_STOP_START_NOACT_HNDLR_IDX         ( 15u )
#define T1_FLEX_STPW_STOP_START_INC_HNDLR_IDX ( 16u )
#define T1_FLEX_STPW_STOP_GET_START_HNDLR_IDX ( 17u ) /* STOP SWD */
#define T1_FLEX_STPW_START_SWD_HNDLR_IDX      ( 18u )

#define T1_USER_DATA_STOP_HNDLER_IDX          ( T1_NOF_HANDLERS * T1_FG_HANDLER_KINDS + 0u )
#define T1_CALIB_START_STPW_HNDLER_IDX        ( T1_NOF_HANDLERS * T1_FG_HANDLER_KINDS + 1u )
#define T1_CALIB_STOP_STPW_HNDLER_IDX         ( T1_NOF_HANDLERS * T1_FG_HANDLER_KINDS + 2u )
#define T1_CALIB_STOP_START_STPW_HNDLER_IDX                                          \
    ( T1_NOF_HANDLERS * T1_FG_HANDLER_KINDS + 3u )
#define T1_LAST_HNDLR_IDX ( T1_NOF_HANDLERS * T1_FG_HANDLER_KINDS + 4u )
#if T1_LAST_HNDLR_IDX + 1 != T1_NOF_HANDLER_ENTRIES
#    error T1_LAST_HNDLR_IDX + 1 != T1_NOF_HANDLER_ENTRIES
#endif

/* clang-format off */
#define T1_ALL_START_MASK                               \
(     (1uL << T1_START_HNDLR_IDX)                       \
    | (1uL << T1_START_NOACT_HNDLR_IDX)                 \
    | (1uL << T1_STOP_START_HNDLR_IDX)                  \
    | (1uL << T1_STOP_START_NOACT_HNDLR_IDX)            \
)

#define T1_ALL_STOP_MASK                                \
(     (1uL << T1_STOP_HNDLR_IDX)                        \
    | (1uL << T1_STOP_START_HNDLR_IDX)                  \
    | (1uL << T1_STOP_START_NOACT_HNDLR_IDX)            \
)

#define T1_ALL_STOPWATCH_START_MASK                     \
(     (1uL << T1_STPW_START_HNDLR_IDX)                  \
    | (1uL << T1_STPW_STOP_START_HNDLR_IDX)             \
    | (1uL << T1_STPW_STOP_START_INC_HNDLR_IDX)         \
)

#define T1_ALL_STOPWATCH_STOP_MASK                      \
(     (1uL << T1_STPW_STOP_HNDLR_IDX)                   \
    | (1uL << T1_STPW_STOP_START_HNDLR_IDX)             \
    | (1uL << T1_STPW_STOP_START_INC_HNDLR_IDX)         \
)

#define T1_ALL_FLEX_STOPWATCH_START_MASK                \
(     (1uL << T1_FLEX_STPW_START_HNDLR_IDX)             \
    | (1uL << T1_FLEX_STPW_START_SWD_HNDLR_IDX)         \
    | (1uL << T1_FLEX_STPW_STOP_START_INC_HNDLR_IDX)    \
)

#define T1_ALL_FLEX_STOPWATCH_STOP_MASK                 \
(     (1uL << T1_FLEX_STPW_STOP_HNDLR_IDX)              \
    | (1uL << T1_FLEX_STPW_STOP_GET_START_HNDLR_IDX)    \
    | (1uL << T1_FLEX_STPW_STOP_START_INC_HNDLR_IDX)    \
)

#define T1_ALL_OTHER_MASK                           \
(                                                   \
    (1uL << T1_EMPTY_HNDLR_IDX)                     \
  | (1uL << T1_WAIT_HNDLR_IDX)                      \
  | (1uL << T1_RESUME_HNDLR_IDX)                    \
)
/* clang-format on */

#if defined T1_DISABLE_T1_FLEX && !defined T1_TEST_ONLY
#    define T1_IS_FLEX_HANDLER( handlerIdx_ ) ( 0u )
#else
#    define T1_IS_FLEX_HANDLER( handlerIdx_ ) ( ( handlerIdx_ ) % T1_OH_KINDS )
#endif /* defined T1_ALTERNATIVE_IS_FLEX_HANDLER */

#define T1_BSF_EVENT_TO_MASK( eventId_ )                                             \
    ( ( T1_START == ( eventId_ ) )        ? T1_ALL_START_MASK                        \
      : ( T1_ACTIVATION == ( eventId_ ) ) ? 1uL << T1_ACTIVATION_HNDLR_IDX           \
                                          : 1uL << T1_EMPTY_HNDLR_IDX )

/* clang-format off */
#define T1_EMPTY                    0x00u   /*!< Empty event (no entry, initialized) */
#define T1_START                    0x01u   /*!< Start of a task or ISR */
#define T1_STOP                     0x02u   /*!< End of a task or ISR */
#define T1_START_STOP               0x03u   /*!< Start and end of a short task or ISR. \sa T1_ContStartStopCETPC() */
#define T1_STOP_START               0x04u   /*!< End of one task and start of a 2nd */
#define T1_STOPWATCH_START          0x05u   /*!< Start stopwatch */
#define T1_STOPWATCH_STOP           0x06u   /*!< Stop stopwatch */
#define T1_STOPWATCH_STOP_START     0x07u   /*!< Stop stopwatch n, start n */
#define T1_STOPWATCH_STOP_START_INC 0x08u   /*!< Stop stopwatch n-1, start n */
#define T1_FLEX_UEC                 0x09u   /*!< \internal \brief T1.flex code event */
#define T1_FLEX_UED                 0x0Au   /*!< \internal \brief T1.flex data event */
#define T1_FLEX_USERDATA_START      0x0Bu   /*!< \internal \brief T1.flex data event with data */
#define T1_ACTIVATION               0x0Cu   /*!< Successful task activation */
#if defined T1_DISABLE_T1_CONT || defined T1_WAIT_RESUME
#   define T1_WAIT                  0x0Du   /*!< ECC task called WaitEvent. This describes the transition from RUNNING to WAITING state for ECC tasks in an AUTOSAR OS. */
#   define T1_RESUME                0x0Eu   /*!< ECC task returned from WaitEvent. This describes the transition from READY to RUNNING coming from WAITING state for ECC tasks in an AUTOSAR OS. */
#endif /* defined T1_DISABLE_T1_CONT || defined T1_WAIT_RESUME */
#define T1_DISCONTINUITY            0x0Fu   /*!< Resume after stop trace */
#define T1_ACTIVATION_FAILED        0x10u   /*!< Failed task activation (E_OS_LIMIT) */
#define T1_RELEASE                  0x11u   /*!< Task had a waiting event set. This describes the transition from WAITING to READY state for ECC tasks in an AUTOSAR OS. */
#define T1_SYNCDATA                 0x12u   /*!< \internal \brief Synchronisation timestamp data transferred with a single entry */
#define T1_SYNCDATA_START           0x12u   /*!< \internal \brief Synchronisation timestamp data transferred in a sequence */
#define T1_USERDATA_START           0x13u   /*!< \internal \brief User data */
#define T1_USERDATA_MID             0x14u   /*!< \internal \brief User data with no timestamp */
#define T1_USERDATA_STOP            0x15u   /*!< \internal \brief User data */
#define T1_RUNNABLE_START           0x16u   /*!< Start of a runnable */
#define T1_RUNNABLE_STOP            0x17u   /*!< End of a runnable */
#define T1_TRIGGER                  0x18u   /*!< \brief Trigger event. \sa T1_SetStopTrigger() */
#define T1_STOPWATCH_STOP_GET_START 0x19u   /*!< \internal \brief Stop stopwatch plus GET user data */
#define T1_START_IPT_START          0x1Au   /*!< \internal \brief Start task plus IPT user data */
#define T1_FLEX_MSR_ID              0x1Bu   /*!< \internal \brief Start/stop measurement ID */
#define T1_STOP_START_IPT_START     0x1Du   /*!< \internal \brief Start task plus IPT and stop task user data */
#if T1_STOP_START_IPT_START - T1_START_IPT_START != T1_STOP_START - T1_START
#   error Invalid T1_STOP_START_IPT_START identifier
#endif /* T1_STOP_START_IPT_START - T1_START_IPT_START != T1_STOP_START - T1_START */
#define T1_TASK_NAME_START          0x1Eu   /*!< \internal \brief Dynamic task name */
#define T1_TASK_OS_IDS_START        0x1Fu   /*!< \internal \brief Dynamic OS-specific IDs */
/* clang-format on */

/*
 * Do not change the value of T1_NAMEBUFFER_ENTRIES,
 * It will break the traceBuffer interpretation on T1-HOST-SW side
 * Special care is required to ensure that a traceBuffer transfer is not
 * mis-interpreted as a prefix transfer.
 */
#define T1_NAMEBUFFER_ENTRIES          ( 28 )
#define T1_NAME_BYTES                  ( 32 )
/* GCP handles 0xFFFF bytes but limit to 0xFFF8 to keep 64-bit events intact. */
#define T1_MAX_TRACE_BUFFER_MSG_BYTES_ ( 0xFFF8 )
#define T1_MAX_TRACE_BUFFER_MSG_BYTES                                                \
    ( (T1_uint32Least_t)T1_MAX_TRACE_BUFFER_MSG_BYTES_ )
#define T1_TRACE_ENTRY_BYTES ( 4 )

#if defined T1_ENABLE && !defined T1_DISABLE_T1_SCOPE

/*!
 * Combine event ID and info field into a single 16-bit value.
 * \param[in] event_ the event ID
 * \param[in] info_  additional info field, for example task/stopwatch ID
 * \returns          the combined result
 */
#    define T1_COMBINE_EVENT_INFO( event_, info_ )                                   \
        ( (T1_eventInfo_t)( ( (T1_eventInfo_t)( event_ ) << T1_INFO_BIT_WIDTH )      \
                            | ( (T1_eventInfo_t)( info_ )                            \
                                & ( 0xFFFFFFFFuL                                     \
                                    >> ( 32 - T1_INFO_BIT_WIDTH ) ) ) ) )

#    define T1_TRACEDATA_UINT8     0x0u
#    define T1_TRACEDATA_SINT8     0x1u
#    define T1_TRACEDATA_UINT16    0x2u
#    define T1_TRACEDATA_SINT16    0x3u
#    define T1_TRACEDATA_UINT32    0x4u
#    define T1_TRACEDATA_SINT32    0x5u
#    define T1_TRACEDATA_UINT64    0x6u
#    define T1_TRACEDATA_SINT64    0x7u
#    define T1_TRACEDATA_FLOAT     0x8u
#    define T1_TRACEDATA_ADDRESS   0x9u
#    define T1_TRACEDATA_STR_REST0 0xAu
#    define T1_TRACEDATA_STR_REST1 0xBu
#    define T1_TRACEDATA_STR_REST2 0xCu
#    define T1_TRACEDATA_BIN_REST0 0xDu
#    define T1_TRACEDATA_BIN_REST1 0xEu
#    define T1_TRACEDATA_BIN_REST2 0xFu

#    define T1_TRACE_ATOMIC_( vrnt_, te_, pScopeConsts_, eventInfo_ )                \
        T1_CAT( T1_TRACE_ATOMIC3, vrnt_ )( te_, pScopeConsts_, eventInfo_ )
#    define T1_TRACE_ATOMIC__( vrnt_, te_, pScopeConsts_, data1_, data2_ )           \
        T1_CAT( T1_TRACE_ATOMIC4, vrnt_ )( te_, pScopeConsts_, data1_, data2_ )
#    define T1_TRACE_ATOMIC___( vrnt_, te_, pScopeConsts_, data1_, data2_, data3_ )  \
        T1_CAT( T1_TRACE_ATOMIC5, vrnt_ )                                            \
        ( te_, pScopeConsts_, data1_, data2_, data3_ )

#    if defined T1_INTERRUPTS_ARE_ENABLED
#        define T1_TRACE_ATOMIC3( te_, pScopeConsts_, eventInfo_ )                   \
            do                                                                       \
            {                                                                        \
                if( T1_INTERRUPTS_ARE_ENABLED( ) )                                   \
                {                                                                    \
                    T1_TRACE_ATOMIC3_FAST( te_, pScopeConsts_, eventInfo_ );         \
                }                                                                    \
                else                                                                 \
                {                                                                    \
                    T1_TRACE_ATOMIC3_NOSUSP( te_, pScopeConsts_, eventInfo_ );       \
                }                                                                    \
            }                                                                        \
            while( 0 )
#        define T1_TRACE_ATOMIC4( te_, pScopeConsts_, data1_, data2_ )               \
            do                                                                       \
            {                                                                        \
                if( T1_INTERRUPTS_ARE_ENABLED( ) )                                   \
                {                                                                    \
                    T1_TRACE_ATOMIC4_FAST( te_, pScopeConsts_, data1_, data2_ );     \
                }                                                                    \
                else                                                                 \
                {                                                                    \
                    T1_TRACE_ATOMIC4_NOSUSP( te_, pScopeConsts_, data1_, data2_ );   \
                }                                                                    \
            }                                                                        \
            while( 0 )
#    else /* ! defined T1_INTERRUPTS_ARE_ENABLED */
#        define T1_TRACE_ATOMIC3( te_, pScopeConsts_, eventInfo_ )                   \
            T1_TRACE_ATOMIC3_FAST( te_, pScopeConsts_, eventInfo_ )
#        define T1_TRACE_ATOMIC4( te_, pScopeConsts_, data1_, data2_ )               \
            T1_TRACE_ATOMIC4_FAST( te_, pScopeConsts_, data1_, data2_ )
#    endif /* defined T1_INTERRUPTS_ARE_ENABLED */
#    define T1_TRACE_ATOMIC3_FAST( te_, pScopeConsts_, eventInfo_ )                  \
        do                                                                           \
        {                                                                            \
            T1_DISABLE_INTERRUPTS( );                                                \
            T1_INSTRUCTION_REORDER_BARRIER( );                                       \
            T1_TRACE_ATOMIC3_NOSUSP( te_, pScopeConsts_, eventInfo_ );               \
            T1_INSTRUCTION_REORDER_BARRIER( );                                       \
            T1_ENABLE_INTERRUPTS( );                                                 \
        }                                                                            \
        while( 0 )
#    define T1_TRACE_ATOMIC4_FAST( te_, pScopeConsts_, data1_, data2_ )              \
        do                                                                           \
        {                                                                            \
            T1_DISABLE_INTERRUPTS( );                                                \
            T1_INSTRUCTION_REORDER_BARRIER( );                                       \
            T1_TRACE_ATOMIC4_NOSUSP( te_, pScopeConsts_, data1_, data2_ );           \
            T1_INSTRUCTION_REORDER_BARRIER( );                                       \
            T1_ENABLE_INTERRUPTS( );                                                 \
        }                                                                            \
        while( 0 )
#    if defined T1_CONT_REMOTE
#        define T1_RC RC__
#    else /* ! defined T1_CONT_REMOTE */
#        define T1_RC __
#    endif /* defined T1_CONT_REMOTE */
#    define T1_TRACE_EVENT_NOSUSP_TIME     T1_CAT( T1_NearTraceEventNoSuspTime, T1_RC )
#    define T1_FAR_TRACE_EVENT_NOSUSP_TIME T1_CAT( T1_TraceEventNoSuspTime, T1_RC )
#    define T1_TRACE_ATOMIC3_NOSUSP( te_, pScopeConsts_, eventInfo_ )                \
        ( T1_CAT( te_##NoSusp, T1_RC )( pScopeConsts_, eventInfo_ ) )
#    define T1_TRACE_ATOMIC4_NOSUSP( te_, pScopeConsts_, eventInfo_, data_ )         \
        ( T1_CAT( te_##NoSusp, T1_RC )( pScopeConsts_, eventInfo_, data_ ) )
#    define T1_TRACE_ATOMIC4_NOSUSPTIME( te_, pScopeConsts_, data1_, data2_ )        \
        ( T1_CAT( te_##NoSuspTime, T1_RC )( pScopeConsts_, data1_, data2_ ) )
#    define T1_TRACE_ATOMIC5_NOSUSPTIME( te_,                                        \
                                         pScopeConsts_,                              \
                                         data1_,                                     \
                                         data2_,                                     \
                                         data3_ )                                    \
        ( T1_CAT( te_##NoSuspTime, T1_RC )( pScopeConsts_, data1_, data2_, data3_ ) )
#    define T1_TraceEventNoSuspRC__( pScopeConsts_, eventInfo_ )                     \
        T1_TraceEventNoSusp__( pScopeConsts_, eventInfo_ )

#    define T1_TRACE_UINT32( vrnt_, pScopeConsts_, info_, ui32_ )                    \
        T1_TRACE_ATOMIC__( vrnt_,                                                    \
                           T1_TRACE_UINT32_,                                         \
                           pScopeConsts_,                                            \
                           T1_COMBINE_EVENT_INFO( T1_USERDATA_START, info_ ),        \
                           ui32_ )
#    if defined T1_FG_CONT
#        define T1_TRACE_UINT32_NoSusp__( pScopeConsts_, eventInfo_, ui32_ )         \
            ( (void)T1_Dispatch2_( pScopeConsts_,                                    \
                                   eventInfo_,                                       \
                                   T1_EMPTY_HNDLR_IDX << 1 ),                        \
              (void)T1_TraceUint32RestNoSuspFg( ( pScopeConsts_ ), ( ui32_ ) ) )
#        define T1_FAR_TRACE_UINT32_REST_NOSUSP  T1_TraceUint32RestNoSuspFg
#        define T1_FAR_TRACE_UINT56_REST_NOSUSP  T1_TraceUint56RestNoSuspFg
#        define T1_NEAR_TRACE_UINT56_REST_NOSUSP T1_NearTraceUint56RestNoSuspFg
#    else /* ! defined T1_FG_CONT */
#        define T1_TRACE_UINT32_NoSusp__( pScopeConsts_, eventInfo_, ui32_ )         \
            ( (void)T1_TraceEventNoSusp__( ( pScopeConsts_ ), ( eventInfo_ ) ),      \
              (void)T1_TraceUint32RestNoSusp( ( pScopeConsts_ ), ( ui32_ ) ) )
#        if defined T1_CONT_REMOTE
#            define T1_FAR_TRACE_UINT32_REST_NOSUSP  T1_TraceUint32RestNoSuspRC
#            define T1_FAR_TRACE_UINT56_REST_NOSUSP  T1_TraceUint56RestNoSuspRC
#            define T1_NEAR_TRACE_UINT56_REST_NOSUSP T1_NearTraceUint56RestNoSuspRC
#        else /* ! defined T1_CONT_REMOTE */
#            define T1_FAR_TRACE_UINT32_REST_NOSUSP  T1_TraceUint32RestNoSusp
#            define T1_FAR_TRACE_UINT56_REST_NOSUSP  T1_TraceUint56RestNoSusp
#            define T1_NEAR_TRACE_UINT56_REST_NOSUSP T1_NearTraceUint56RestNoSusp
#        endif /* defined T1_CONT_REMOTE */
#    endif     /* defined T1_FG_CONT */
#    define T1_TRACE_UINT32_NoSuspRC__( pScopeConsts_, eventInfo_, ui32_ )           \
        ( (void)T1_TraceEventNoSusp__( ( pScopeConsts_ ), ( eventInfo_ ) ),          \
          (void)T1_TraceUint32RestNoSuspRC( ( pScopeConsts_ ), ( ui32_ ) ) )

#    if defined T1_SYNC_TIMER_WIDTH_BITS /* Inhibit for library build */
#        if T1_SYNC_TIMER_WIDTH_BITS < 28
/* Truncate to correct any subtraction underflow for timer with less than 28 bits. */
#            define T1_TRUNC_SYNC_GET( data_ )                                       \
                ( ( data_ ) & ( 0xFFFFFFFFuL >> ( 32 - T1_SYNC_TIMER_WIDTH_BITS ) ) )
/* Truncate similarly but for values shifted left by 4. */
#            define T1_TRUNC_SYNC_DATA( data_ )                                      \
                ( ( data_ ) & ( 0xFFFFFFFFuL >> ( 28 - T1_SYNC_TIMER_WIDTH_BITS ) ) )
#        else /* 28 <= T1_SYNC_TIMER_WIDTH_BITS */
#            define T1_TRUNC_SYNC_GET( data_ )  ( data_ )
#            define T1_TRUNC_SYNC_DATA( data_ ) ( data_ )
#        endif /* T1_SYNC_TIMER_WIDTH_BITS < 28 */
#    endif     /* defined T1_SYNC_TIMER_WIDTH_BITS */

#    define T1_TRACE_SYNC( vrnt_, pScopeConsts_, eventInfo_ )                        \
        T1_TRACE_ATOMIC_( vrnt_, T1_TRACE_SYNC_, pScopeConsts_, eventInfo_ )

#    if defined T1_SYNC_TIMER_WIDTH_BITS /* Inhibit for library build */
#        if T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER && 28 <= T1_SYNC_TIMER_WIDTH_BITS
#            define T1_TRACE_TIMER_TO_SYNC_TIMER__( pScopeConsts_, traceTime_ )      \
                ( traceTime_ )
#        else /* ! T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER || T1_SYNC_TIMER_WIDTH_BITS <  \
                 28 */
#            define T1_TRACE_TIMER_TO_SYNC_TIMER__( pScopeConsts_, traceTime_ )      \
                T1_TraceToSyncNoSusp__( ( pScopeConsts_ ), ( traceTime_ ) )
#        endif /* T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER && 28 <=                        \
                  T1_SYNC_TIMER_WIDTH_BITS */
#        if T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER && 32 == T1_SYNC_TIMER_WIDTH_BITS
#            define T1_TRACE_TIMER_TO_SYNC_TIMER___( pScopeConsts_, traceTime_ )     \
                ( traceTime_ )
#        else /* ! T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER || T1_SYNC_TIMER_WIDTH_BITS <  \
                 32 */
#            define T1_TRACE_TIMER_TO_SYNC_TIMER___( pScopeConsts_, traceTime_ )     \
                T1_TraceToSyncNoSusp__( ( pScopeConsts_ ), ( traceTime_ ) )
#        endif /* T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER && 32 ==                        \
                  T1_SYNC_TIMER_WIDTH_BITS */
#    endif     /* defined T1_SYNC_TIMER_WIDTH_BITS */

#    if defined T1_TRACE_56BIT_SYNC_TIMER /* Inhibit for library build */
#        if T1_TRACE_56BIT_SYNC_TIMER
#            if defined T1_CONT_REMOTE
#                define T1_TRACE_SYNC_NoSuspRC__( pScopeConsts_, eventInfo_ )        \
                    ( T1_TraceSync56RestNoSusp(                                      \
                        ( pScopeConsts_ ),                                           \
                        T1_TraceEventNoSusp__( ( pScopeConsts_ ),                    \
                                               ( eventInfo_ )                        \
                                                   + T1_TRACEDATA_BIN_REST1          \
                                                   - T1_TRACEDATA_UINT32 ) ) )
#            else
#                define T1_TRACE_SYNC_NoSusp__( pScopeConsts_, eventInfo_ )          \
                    ( T1_TraceSync56RestNoSusp(                                      \
                        ( pScopeConsts_ ),                                           \
                        T1_TraceEventNoSusp__( ( pScopeConsts_ ),                    \
                                               ( eventInfo_ )                        \
                                                   + T1_TRACEDATA_BIN_REST1          \
                                                   - T1_TRACEDATA_UINT32 ) ) )
#            endif
#        else /* Trace 32 bits of sync timer. */
#            if defined T1_CONT_REMOTE
#                define T1_TRACE_SYNC_NoSuspRC__( pScopeConsts_, eventInfo_ )        \
                    ( (void)T1_TraceUint32RestNoSuspRC(                              \
                        ( pScopeConsts_ ),                                           \
                        T1_TRACE_TIMER_TO_SYNC_TIMER___(                             \
                            ( pScopeConsts_ ),                                       \
                            T1_TraceEventNoSusp__( ( pScopeConsts_ ),                \
                                                   ( eventInfo_ ) ) ) ) )
#            elif defined T1_FG_CONT
#                define T1_TRACE_SYNC_NoSusp__( pScopeConsts_, eventInfo_ )          \
                    ( (void)T1_TraceUint32RestNoSuspFg(                              \
                        ( pScopeConsts_ ),                                           \
                        T1_TRACE_TIMER_TO_SYNC_TIMER___(                             \
                            ( pScopeConsts_ ),                                       \
                            T1_Dispatch2_( ( pScopeConsts_ ),                        \
                                           ( eventInfo_ ),                           \
                                           T1_EMPTY << 1 ) ) ) )
#            else
#                define T1_TRACE_SYNC_NoSusp__( pScopeConsts_, eventInfo_ )          \
                    ( (void)T1_TraceUint32RestNoSusp(                                \
                        ( pScopeConsts_ ),                                           \
                        T1_TRACE_TIMER_TO_SYNC_TIMER___(                             \
                            ( pScopeConsts_ ),                                       \
                            T1_TraceEventNoSusp__( ( pScopeConsts_ ),                \
                                                   ( eventInfo_ ) ) ) ) )
#            endif
#        endif /* T1_TRACE_56BIT_SYNC_TIMER */
#    endif     /* defined T1_TRACE_56BIT_SYNC_TIMER */

#    define T1_TRACE_SYNC_SW( vrnt_, pScopeConsts_, eventInfo_, startData_ )         \
        T1_TRACE_ATOMIC__( vrnt_, T1_SWStop, pScopeConsts_, eventInfo_, startData_ )
#    define T1_TRACE_SYNC_SW_( vrnt_, pScopeConsts_, eventInfo_, startData_, now_ )  \
        T1_TRACE_ATOMIC__( vrnt_,                                                    \
                           T1_SWStop,                                                \
                           pScopeConsts_,                                            \
                           startData_,                                               \
                           T1_FAR_TRACE_EVENT_NOSUSP_TIME( ( pScopeConsts_ ),        \
                                                           ( eventInfo_ ),           \
                                                           ( now_ ) ) )

#    define T1_TRACEDATA( vrnt_, info_, pData_, len_ )                               \
        ( T1_TraceData##vrnt_( T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),  \
                               T1_COMBINE_EVENT_INFO( T1_USERDATA_START, info_ ),    \
                               ( pData_ ),                                           \
                               ( len_ ) ) )
#    define T1_TRACEDATA_PC( vrnt_, coreId_, info_, pData_, len_ )                   \
        ( T1_TraceData##vrnt_( T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                \
                               T1_COMBINE_EVENT_INFO( T1_USERDATA_START, info_ ),    \
                               ( pData_ ),                                           \
                               ( len_ ) ) )
#    define T1_TRACEDATA_NOSUSPTIME( info_, pData_, len_, time_ )                    \
        ( (void)T1_TraceDataNoSuspTime_(                                             \
            T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),                     \
            T1_COMBINE_EVENT_INFO( T1_USERDATA_START, info_ ),                       \
            ( pData_ ),                                                              \
            ( len_ ),                                                                \
            ( time_ ) ) )
#    define T1_TRACEDATA_NOSUSPTIME_PC( coreId_, info_, pData_, len_, time_ )        \
        ( (void)T1_TraceDataNoSuspTime_(                                             \
            T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                                   \
            T1_COMBINE_EVENT_INFO( T1_USERDATA_START, info_ ),                       \
            ( pData_ ),                                                              \
            ( len_ ),                                                                \
            ( time_ ) ) )

#    define T1_OH_SW          ( 0x2FFu )
#    define T1_CONT_UPDATE_OH ( 0x3FCu )

#    if defined T1_SYNC_TIMER_WIDTH_BITS /* Inhibit for library build */
#        if defined T1_TRACE_ACT_EVENT_AND_CROSS_CORE_ACT
#            define T1_TRACE_ACT_PC_NoSusp__( pScopeConsts_, ei_, offset_ )          \
                ( ( T1_TRACE_TIMER_TO_SYNC_TIMER__(                                  \
                        ( pScopeConsts_ ),                                           \
                        T1_NearTraceEventNoSusp__( ( pScopeConsts_ ), ( ei_ ) ) )    \
                    << 4 )                                                           \
                  - ( offset_ ) )
#        elif 28 <= T1_SYNC_TIMER_WIDTH_BITS /* Just read sync timer */
#            define T1_TRACE_ACT_PC_NoSusp__( pScopeConsts_, ei_, offset_ )          \
                ( ( T1_GET_SYNC_TIME( ) << 4 ) - ( offset_ ) )
#        else /* Add high bits from synthesized sync timer */
#            define T1_TRACE_ACT_PC_NoSusp__( pScopeConsts_, ei_, offset_ )          \
                ( ( ( ( pScopeConsts_ )->syncTime                                    \
                      + T1_TRUNC_SYNC_GET( T1_GET_SYNC_TIME( )                       \
                                           - ( pScopeConsts_ )->syncTime ) )         \
                    << 4 )                                                           \
                  - ( offset_ ) )
#        endif /* T1_TRACE_ACT_EVENT_AND_CROSS_CORE_ACT */
#        define T1_TRACE_ACT_PC_NoSuspRC__( pScopeConsts_, ei_, offset_ )            \
            ( T1_TRACE_ACT_PC_NoSusp__( ( pScopeConsts_ ), ( ei_ ), ( offset_ ) ) )
#    endif /* defined T1_SYNC_TIMER_WIDTH_BITS */

#    if !defined T1_DISABLE_T1_CONT && defined T1_FG_CONT
#        define T1_TRACE_START_PC( vrnt_, coreId_, taskId_ )                         \
            T1_TRACE_ATOMIC_( vrnt_,                                                 \
                              T1_TaskStart,                                          \
                              T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                 \
                              ( taskId_ ) )
#        define T1_TRACE_START_PC_( vrnt_, coreId_, taskId_, now_ )                  \
            T1_TRACE_ATOMIC__( vrnt_, T1_TaskStart, coreId_, ( taskId_ ), ( now_ ) )
#        define T1_TRACE_STOP_START_PC( vrnt_, coreId_, startTaskId_ )               \
            T1_TRACE_ATOMIC_( vrnt_,                                                 \
                              T1_TaskStopStart,                                      \
                              T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                 \
                              ( startTaskId_ ) )
#        define T1_TRACE_STOP_START_PC_( vrnt_, coreId_, taskId_, now_ )             \
            T1_TRACE_ATOMIC__( vrnt_,                                                \
                               T1_TaskStopStart,                                     \
                               coreId_,                                              \
                               ( taskId_ ),                                          \
                               ( now_ ) )
#        define T1_TRACE_START_NOACT_PC( vrnt_, coreId_, taskId_ )                   \
            T1_TRACE_ATOMIC_( vrnt_,                                                 \
                              T1_TaskStartNoAct,                                     \
                              T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                 \
                              ( taskId_ ) )
#        define T1_TRACE_START_NOACT_PC_( vrnt_, coreId_, taskId_, now_ )            \
            T1_TRACE_ATOMIC__( vrnt_,                                                \
                               T1_TaskStartNoAct,                                    \
                               coreId_,                                              \
                               ( taskId_ ),                                          \
                               ( now_ ) )
#        define T1_TRACE_STOP_START_NOACT_PC( vrnt_, coreId_, startTaskId_ )         \
            T1_TRACE_ATOMIC_( vrnt_,                                                 \
                              T1_TaskStopStartNoAct,                                 \
                              T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                 \
                              ( startTaskId_ ) )
#        define T1_TRACE_STOP_START_NOACT_PC_( vrnt_, coreId_, taskId_, now_ )       \
            T1_TRACE_ATOMIC__( vrnt_,                                                \
                               T1_TaskStopStartNoAct,                                \
                               coreId_,                                              \
                               ( taskId_ ),                                          \
                               ( now_ ) )
#        define T1_TRACE_STOP_PC( vrnt_, coreId_, taskId_ )                          \
            T1_TRACE_ATOMIC_( vrnt_,                                                 \
                              T1_TaskStop,                                           \
                              T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                 \
                              ( taskId_ ) )
#        define T1_TRACE_STOP_PC_( vrnt_, coreId_, taskId_, now_ )                   \
            T1_TRACE_ATOMIC__( vrnt_, T1_TaskStop, coreId_, ( taskId_ ), ( now_ ) )
#        define T1_TRACE_ACT_PC( vrnt_, coreId_, taskId_ )                           \
            T1_TRACE_ATOMIC_( vrnt_,                                                 \
                              T1_TaskAct,                                            \
                              T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                 \
                              ( taskId_ ) )
#        define T1_TRACE_START_ACT_PC( vrnt_,                                        \
                                       coreId_,                                      \
                                       taskId_,                                      \
                                       actCoreId_,                                   \
                                       actTime_ )                                    \
            T1_TRACE_ATOMIC__( vrnt_,                                                \
                               T1_TaskStartAct,                                      \
                               T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                \
                               ( taskId_ ),                                          \
                               ( ( actTime_ ) << 4 ) - (actCoreId_)-1 )
#        define T1_TRACE_START_ACT_PC_( vrnt_,                                       \
                                        coreId_,                                     \
                                        taskId_,                                     \
                                        actCoreId_,                                  \
                                        actTime_,                                    \
                                        now_ )                                       \
            T1_TRACE_ATOMIC___( vrnt_,                                               \
                                T1_TaskStartAct,                                     \
                                coreId_,                                             \
                                ( taskId_ ),                                         \
                                ( ( actTime_ ) << 4 ) - (actCoreId_)-1,              \
                                ( now_ ) )
#        define T1_TRACE_STOP_START_ACT_PC( vrnt_,                                   \
                                            coreId_,                                 \
                                            startTaskId_,                            \
                                            actCoreId_,                              \
                                            actTime_ )                               \
            T1_TRACE_ATOMIC__( vrnt_,                                                \
                               T1_TaskStopStartAct,                                  \
                               T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                \
                               ( startTaskId_ ),                                     \
                               ( ( actTime_ ) << 4 ) - (actCoreId_)-1 )
#        define T1_TRACE_STOP_START_ACT_PC_( vrnt_,                                  \
                                             coreId_,                                \
                                             startTaskId_,                           \
                                             actCoreId_,                             \
                                             actTime_,                               \
                                             now_ )                                  \
            T1_TRACE_ATOMIC___( vrnt_,                                               \
                                T1_TaskStopStartAct,                                 \
                                coreId_,                                             \
                                ( startTaskId_ ),                                    \
                                ( ( actTime_ ) << 4 ) - (actCoreId_)-1,              \
                                ( now_ ) )
#        define T1_TRACE_START_STOP_PC( vrnt_, coreId_, taskId_ )                    \
            T1_TRACE_ATOMIC_( vrnt_,                                                 \
                              T1_TaskStartStop,                                      \
                              T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                 \
                              ( taskId_ ) )
#        define T1_TRACE_START_STOP_PC_( vrnt_, coreId_, taskId_, now_ )             \
            T1_TRACE_ATOMIC_( vrnt_,                                                 \
                              T1_TaskStartStop,                                      \
                              coreId_,                                               \
                              ( taskId_ ),                                           \
                              ( now_ ) )

#        define T1_TaskStartNoSusp__( pScopeConsts_, taskId_ )                       \
            T1_Dispatch2_( ( pScopeConsts_ ), ( taskId_ ), T1_START_HNDLR_IDX << 1 )
#        define T1_TaskStartNoSuspTime__( coreId_, taskId_, now_ )                   \
            T1_DISPATCH_##coreId_( T1_CORE_ID_TO_SCOPE_FG_CONSTS( coreId_ ),         \
                                   ( taskId_ ),                                      \
                                   ( now_ ),                                         \
                                   T1_START_HNDLR_IDX << 1 )
#        define T1_TaskStartNoActNoSusp__( pScopeConsts_, taskId_ )                  \
            T1_Dispatch2_( ( pScopeConsts_ ),                                        \
                           ( taskId_ ),                                              \
                           T1_START_NOACT_HNDLR_IDX << 1 )
#        define T1_TaskStartNoActNoSuspTime__( coreId_, taskId_, now_ )              \
            T1_DISPATCH_##coreId_( T1_CORE_ID_TO_SCOPE_FG_CONSTS( coreId_ ),         \
                                   ( taskId_ ),                                      \
                                   ( now_ ),                                         \
                                   T1_START_NOACT_HNDLR_IDX << 1 )
#        define T1_TaskStopNoSusp__( pScopeConsts_, taskId_ )                        \
            T1_Dispatch2_( ( pScopeConsts_ ), ( taskId_ ), T1_STOP_HNDLR_IDX << 1 )
#        define T1_TaskStopNoSuspTime__( coreId_, taskId_, now_ )                    \
            T1_DISPATCH_STOP_##coreId_( T1_CORE_ID_TO_SCOPE_FG_CONSTS( coreId_ ),    \
                                        ( taskId_ ),                                 \
                                        ( now_ ),                                    \
                                        T1_STOP_HNDLR_IDX << 1 )
#        define T1_TaskStopStartNoSusp__( pScopeConsts_, taskId_ )                   \
            T1_Dispatch2_( ( pScopeConsts_ ),                                        \
                           ( taskId_ ),                                              \
                           T1_STOP_START_HNDLR_IDX << 1 )
#        define T1_TaskStopStartNoSuspTime__( coreId_, taskId_, now_ )               \
            T1_DISPATCH_STOP_##coreId_( T1_CORE_ID_TO_SCOPE_FG_CONSTS( coreId_ ),    \
                                        ( taskId_ ),                                 \
                                        ( now_ ),                                    \
                                        T1_STOP_START_HNDLR_IDX << 1 )
#        define T1_TaskStopStartNoActNoSusp__( pScopeConsts_, taskId_ )              \
            T1_Dispatch2_( ( pScopeConsts_ ),                                        \
                           ( taskId_ ),                                              \
                           T1_STOP_START_NOACT_HNDLR_IDX << 1 )
#        define T1_TaskStopStartNoActNoSuspTime__( coreId_, taskId_, now_ )          \
            T1_DISPATCH_STOP_##coreId_( T1_CORE_ID_TO_SCOPE_FG_CONSTS( coreId_ ),    \
                                        ( taskId_ ),                                 \
                                        ( now_ ),                                    \
                                        T1_STOP_START_NOACT_HNDLR_IDX << 1 )
#        define T1_TaskActNoSusp__( pScopeConsts_, taskId_ )                         \
            T1_Dispatch2_( ( pScopeConsts_ ),                                        \
                           ( taskId_ ),                                              \
                           T1_ACTIVATION_HNDLR_IDX << 1 )
#        define T1_TaskStartActNoSusp__( pScopeConsts_, taskId_, actData_ )          \
            ( 0u == T1_TT_GET_MULTI_ACT( T1_taskFgData[taskId_].taskType )           \
                  ? ( T1_taskFgData[taskId_].act.data = ( actData_ ),                \
                      T1_Dispatch2_( ( pScopeConsts_ ),                              \
                                     ( taskId_ ),                                    \
                                     T1_START_HNDLR_IDX << 1 ) )                     \
                  : (T1_tickUint_t)0u )
#        define T1_TaskStartActNoSuspTime__( coreId_, taskId_, actData_, now_ )      \
            ( 0u == T1_TT_GET_MULTI_ACT( T1_taskFgData[taskId_].taskType )           \
                  ? ( T1_taskFgData[taskId_].act.data = ( actData_ ),                \
                      T1_DISPATCH_##coreId_(                                         \
                          T1_CORE_ID_TO_SCOPE_FG_CONSTS( coreId_ ),                  \
                          ( taskId_ ),                                               \
                          ( now_ ),                                                  \
                          T1_START_HNDLR_IDX << 1 ) )                                \
                  : (T1_tickUint_t)0u )
#        define T1_TaskStopStartActNoSusp__( pScopeConsts_, taskId_, actData_ )      \
            ( 0u == T1_TT_GET_MULTI_ACT( T1_taskFgData[taskId_].taskType )           \
                  ? ( T1_taskFgData[taskId_].act.data = ( actData_ ),                \
                      T1_Dispatch2_( ( pScopeConsts_ ),                              \
                                     ( taskId_ ),                                    \
                                     T1_STOP_START_HNDLR_IDX << 1 ) )                \
                  : (T1_tickUint_t)0u )
#        define T1_TaskStopStartActNoSuspTime__( coreId_, taskId_, actData_, now_ )  \
            ( 0u == T1_TT_GET_MULTI_ACT( T1_taskFgData[taskId_].taskType )           \
                  ? ( T1_taskFgData[taskId_].act.data = ( actData_ ),                \
                      T1_DISPATCH_STOP_##coreId_(                                    \
                          T1_CORE_ID_TO_SCOPE_FG_CONSTS( coreId_ ),                  \
                          ( taskId_ ),                                               \
                          ( now_ ),                                                  \
                          T1_STOP_START_HNDLR_IDX << 1 ) )                           \
                  : (T1_tickUint_t)0u )
#        define T1_TaskStartStopNoSusp__( pScopeConsts_, taskId_ )                   \
            T1_Dispatch2_( ( pScopeConsts_ ),                                        \
                           ( taskId_ ),                                              \
                           T1_START_STOP_HNDLR_IDX << 1 )
#        define T1_TaskStartStopNoSuspTime__( pScopeConsts_, taskId_, now_ )         \
            T1_DISPATCH_##coreId_( T1_CORE_ID_TO_SCOPE_FG_CONSTS( coreId_ ),         \
                                   ( taskId_ ),                                      \
                                   ( now_ ),                                         \
                                   T1_START_STOP_HNDLR_IDX << 1 )

#        if defined __GNUC__ /* Avoid double expansion of pScopeConsts_ */
/* polyspace<MISRA-C3:11.3:Justified:Low> The cast is intentional  */
#            define T1_Dispatch2_( pScopeConsts_, eventInfo_, handlerIdx_ )          \
                ( {                                                                  \
                    T1_scopeFgConsts_t * const pScopeFgConsts__ =                    \
                        (T1_scopeFgConsts_t *)( pScopeConsts_ );                     \
                    pScopeFgConsts__->pDispatcher( pScopeFgConsts__,                 \
                                                   ( eventInfo_ ),                   \
                                                   ( handlerIdx_ ) );                \
                } )
#        else /* ! defined __GNUC__ unavoidable double expansion of pScopeConsts_ */
/* polyspace<MISRA-C3:11.3:Justified:Low> The cast is intentional  */
#            define T1_Dispatch2_( pScopeConsts_, eventInfo_, handlerIdx_ )          \
                ( ( (T1_scopeFgConsts_t *)( pScopeConsts_ ) )                        \
                      ->pDispatcher( (T1_scopeFgConsts_t *)( pScopeConsts_ ),        \
                                     ( eventInfo_ ),                                 \
                                     ( handlerIdx_ ) ) )
#        endif /* defined __GNUC__ */

#        if defined T1_SYNC_TIMER_WIDTH_BITS /* Inhibit for library build */
#            if defined T1_CROSS_CORE_ACT && 1 < T1_NOF_CORES
#                if defined T1_TRACE_ACT_EVENT_AND_CROSS_CORE_ACT
#                    define ACT_TASK_HANDLER    T1_ActivateAndTraceTask
#                    define ACT_TASK_VS_HANDLER T1_ActivateAndTraceTaskVS
#                else /* ! defined T1_TRACE_ACT_EVENT_AND_CROSS_CORE_ACT */
#                    define ACT_TASK_HANDLER    T1_ActivateTask
#                    define ACT_TASK_VS_HANDLER T1_ActivateTaskVS
#                endif /* defined T1_TRACE_ACT_EVENT_AND_CROSS_CORE_ACT */
#                define START_TASK_HANDLER         T1_StartTask
#                define START_TASK_VS_HANDLER      T1_StartTaskVS
#                define STOP_START_TASK_HANDLER    T1_StopStartTask
#                define STOP_START_TASK_VS_HANDLER T1_StopStartTaskVS
#            else /* ! defined T1_CROSS_CORE_ACT || 1 == T1_NOF_CORES */
#                define ACT_TASK_HANDLER           T1_ActivateAndTraceTask
#                define ACT_TASK_VS_HANDLER        T1_ActivateAndTraceTaskVS
#                define START_TASK_HANDLER         T1_StartNoIptTask
#                define START_TASK_VS_HANDLER      T1_StartNoIptTaskVS
#                define STOP_START_TASK_HANDLER    T1_StopStartNoIptTask
#                define STOP_START_TASK_VS_HANDLER T1_StopStartNoIptTaskVS
#            endif /* defined T1_CROSS_CORE_ACT && 1 < T1_NOF_CORES */
#            if defined T1_DISABLE_T1_FLEX && !defined T1_TEST_ONLY
#                define START_FLEX_CET_STPW_HANLDER T1_Empty
#                define START_FLEX_STPW_VS_HANLDER  T1_EmptyVS
#                define START_FLEX_SWD_HANLDER      T1_Empty
#                define START_FLEX_SWD_VS_HANLDER   T1_EmptyVS
#                define STOP_FLEX_STPW_HANLDER      T1_Empty
#                define STOP_FLEX_STPW_VS_HANLDER   T1_EmptyVS
#                define STOP_FLEX_SWD_HANLDER       T1_Empty
#                define STOP_FLEX_SWD_VS_HANLDER    T1_EmptyVS
#            else /* ! defined T1_DISABLE_T1_FLEX || defined T1_TEST_ONLY */
#                define START_FLEX_CET_STPW_HANLDER T1_StartFlexStopwatch
#                define START_FLEX_STPW_VS_HANLDER  T1_StartFlexStopwatchVS
#                define START_FLEX_SWD_HANLDER      T1_StartFlexSwd
#                define START_FLEX_SWD_VS_HANLDER   T1_StartFlexSwdVS
#                define STOP_FLEX_STPW_HANLDER      T1_StopFlexStopwatch
#                define STOP_FLEX_STPW_VS_HANLDER   T1_StopFlexStopwatchVS
#                if T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER
#                    define STOP_FLEX_SWD_HANLDER T1_StopFlexSwdSyncIsTraceTimer
#                else /* ! T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER */
#                    define STOP_FLEX_SWD_HANLDER T1_StopFlexSwd
#                endif /* T1_ALL_TRACE_TIMERS_ARE_SYNC_TIMER */
#                define STOP_FLEX_SWD_VS_HANLDER T1_StopFlexSwdVS
#            endif /* defined T1_DISABLE_T1_FLEX && ! defined T1_TEST_ONLY */
#        endif     /* defined T1_SYNC_TIMER_WIDTH_BITS */

/* clang-format off */
#        define T1_HANDLERS                                                          \
{                                                                                    \
    /*  0 */    T1_Empty,                     T1_EmptyVS,                            \
    /*  1 */    START_TASK_HANDLER,           START_TASK_VS_HANDLER,                 \
    /*  2 */    T1_StopTask,                  T1_StopTaskVS,                         \
    /*  3 */    T1_StartStopNoIptTask,        T1_StartStopNoIptTaskVS,               \
    /*  4 */    STOP_START_TASK_HANDLER,      STOP_START_TASK_VS_HANDLER,            \
    /*  5 */    T1_StartStopwatch,            T1_StartStopwatchVS,                   \
    /*  6 */    T1_StopStopwatch,             T1_StopStopwatchVS,                    \
    /*  7 */    T1_StopStartStopwatch,        T1_StopStartStopwatchVS,               \
    /*  8 */    T1_StopStartIncStopwatch,     T1_StopStartIncStopwatchVS,            \
    /*  9 */    START_FLEX_CET_STPW_HANLDER,  START_FLEX_STPW_VS_HANLDER,            \
    /* 10 */    STOP_FLEX_STPW_HANLDER,       STOP_FLEX_STPW_VS_HANLDER,             \
    /* 11 */    T1_StartNoActTask,            T1_StartNoActTaskVS,                   \
    /* 12 */    ACT_TASK_HANDLER,             ACT_TASK_VS_HANDLER,                   \
    /* 13 */    T1_WaitTask,                  T1_WaitTaskVS,                         \
    /* 14 */    T1_ResumeTask,                T1_ResumeTaskVS,                       \
    /* 15 */    T1_StopStartNoActTask,        T1_StopStartNoActTaskVS,               \
    /* 16 */    T1_StopStartIncFlexStopwatch, T1_StopStartIncFlexStopwatchVS,        \
    /* 17 */    STOP_FLEX_SWD_HANLDER,        STOP_FLEX_SWD_VS_HANLDER,              \
    /* 18 */    START_FLEX_SWD_HANLDER,       START_FLEX_SWD_VS_HANLDER,             \
                T1_UserDataStopHandler,       T1_CalibStartStopwatch,                \
                T1_CalibStopStopwatch,        T1_CalibStopStartStopwatch,            \
                T1_Error                                                             \
}
/* clang-format on */

#    else /* defined T1_DISABLE_T1_CONT || ! defined T1_FG_CONT */
#        if defined T1_CROSS_CORE_ACT && 1 < T1_NOF_CORES
#            define T1_TRACE_START_PC( vrnt_, coreId_, taskId_ )                     \
                do                                                                   \
                {                                                                    \
                    T1_uint8Least_t const coreId__ = ( coreId_ );                    \
                    (void)coreId__; /* Avoid compiler warnings if coreId is not      \
                                       used. */                                      \
                    if( ( ( taskId_ ) < T1_MAX_NOF_TASKS )                           \
                        && T1_NEEDS_IPT( coreId__, ( taskId_ ) ) )                   \
                    {                                                                \
                        T1_scopeConsts_t * const pScopeConsts__ =                    \
                            T1_CORE_ID_TO_SCOPE_CONSTS( coreId__ );                  \
                        T1_INCR_PREEMPTIONS_PC(                                      \
                            coreId__,                                                \
                            T1_TRACE_SYNC_SW(                                        \
                                vrnt_,                                               \
                                pScopeConsts__,                                      \
                                T1_COMBINE_EVENT_INFO( T1_START_IPT_START,           \
                                                       ( taskId_ ) ),                \
                                T1_taskAct[taskId_] + 1uL ) );                       \
                        T1_taskAct[taskId_] = 0uL;                                   \
                    }                                                                \
                    else                                                             \
                    {                                                                \
                        T1_TRACE_START_NOACT_PC( vrnt_, coreId__, ( taskId_ ) );     \
                    }                                                                \
                }                                                                    \
                while( 0 )
#            define T1_TRACE_START_PC_( vrnt_, coreId_, taskId_, now_ )              \
                do                                                                   \
                {                                                                    \
                    T1_uint8Least_t const coreId__ = ( coreId_ );                    \
                    (void)coreId__; /* Avoid compiler warnings if coreId is not      \
                                       used. */                                      \
                    if( ( ( taskId_ ) < T1_MAX_NOF_TASKS )                           \
                        && T1_NEEDS_IPT( coreId__, ( taskId_ ) ) )                   \
                    {                                                                \
                        T1_scopeConsts_t * const pScopeConsts__ =                    \
                            T1_CORE_ID_TO_SCOPE_CONSTS( coreId__ );                  \
                        T1_INCR_PREEMPTIONS_PC(                                      \
                            coreId__,                                                \
                            T1_TRACE_SYNC_SW_(                                       \
                                vrnt_,                                               \
                                pScopeConsts__,                                      \
                                T1_COMBINE_EVENT_INFO( T1_START_IPT_START,           \
                                                       ( taskId_ ) ),                \
                                T1_taskAct[taskId_] + 1uL,                           \
                                ( now_ ) ) );                                        \
                        T1_taskAct[taskId_] = 0uL;                                   \
                    }                                                                \
                    else                                                             \
                    {                                                                \
                        T1_TRACE_START_NOACT_PC_( vrnt_,                             \
                                                  coreId__,                          \
                                                  ( taskId_ ),                       \
                                                  ( now_ ) );                        \
                    }                                                                \
                }                                                                    \
                while( 0 )
#            define T1_TRACE_STOP_START_PC( vrnt_, coreId_, startTaskId_ )           \
                do                                                                   \
                {                                                                    \
                    T1_uint8Least_t const coreId__ = ( coreId_ );                    \
                    (void)coreId__; /* Avoid compiler warnings if coreId is not      \
                                       used. */                                      \
                    if( ( ( startTaskId_ ) < T1_MAX_NOF_TASKS )                      \
                        && T1_NEEDS_IPT( coreId__, ( startTaskId_ ) ) )              \
                    {                                                                \
                        T1_scopeConsts_t * const pScopeConsts__ =                    \
                            T1_CORE_ID_TO_SCOPE_CONSTS( coreId__ );                  \
                        T1_TRACE_SYNC_SW(                                            \
                            vrnt_,                                                   \
                            pScopeConsts__,                                          \
                            T1_COMBINE_EVENT_INFO( T1_STOP_START_IPT_START,          \
                                                   ( startTaskId_ ) ),               \
                            T1_taskAct[startTaskId_] + 1uL );                        \
                        T1_taskAct[startTaskId_] = 0uL;                              \
                    }                                                                \
                    else                                                             \
                    {                                                                \
                        T1_TRACE_STOP_START_NOACT_PC( vrnt_,                         \
                                                      coreId__,                      \
                                                      ( startTaskId_ ) );            \
                    }                                                                \
                }                                                                    \
                while( 0 )
#            define T1_TRACE_STOP_START_PC_( vrnt_, coreId_, startTaskId_, now_ )    \
                do                                                                   \
                {                                                                    \
                    T1_uint8Least_t const coreId__ = ( coreId_ );                    \
                    (void)coreId__; /* Avoid compiler warnings if coreId is not      \
                                       used. */                                      \
                    if( ( ( startTaskId_ ) < T1_MAX_NOF_TASKS )                      \
                        && T1_NEEDS_IPT( coreId__, ( startTaskId_ ) ) )              \
                    {                                                                \
                        T1_scopeConsts_t * const pScopeConsts__ =                    \
                            T1_CORE_ID_TO_SCOPE_CONSTS( coreId__ );                  \
                        T1_TRACE_SYNC_SW(                                            \
                            vrnt_,                                                   \
                            pScopeConsts__,                                          \
                            T1_COMBINE_EVENT_INFO( T1_STOP_START_IPT_START,          \
                                                   ( startTaskId_ ) ),               \
                            T1_taskAct[startTaskId_] + 1uL,                          \
                            ( now_ ) );                                              \
                        T1_taskAct[startTaskId_] = 0uL;                              \
                    }                                                                \
                    else                                                             \
                    {                                                                \
                        T1_TRACE_STOP_START_NOACT_PC( vrnt_,                         \
                                                      coreId__,                      \
                                                      ( startTaskId_ ) );            \
                    }                                                                \
                }                                                                    \
                while( 0 )
#            define T1_TRACE_ACT_PC( vrnt_, coreId_, taskId_ )                       \
                T1_TRACE_ATOMIC__(                                                   \
                    vrnt_,                                                           \
                    T1_taskAct[( taskId_ ) < T1_MAX_NOF_TASKS ? ( taskId_ )          \
                                                              : T1_MAX_NOF_TASKS] =  \
                        T1_TRACE_ACT_PC_,                                            \
                    T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                           \
                    T1_COMBINE_EVENT_INFO( T1_ACTIVATION, ( taskId_ ) ),             \
                    ( coreId_ ) + 1 )
#        else /* not logging cross-core activations */
#            define T1_TRACE_START_PC( vrnt_, coreId_, taskId_ )                     \
                T1_INCR_PREEMPTIONS_PC(                                              \
                    ( coreId_ ),                                                     \
                    T1_TRACE_ATOMIC_(                                                \
                        vrnt_,                                                       \
                        T1_TraceEvent,                                               \
                        T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                       \
                        T1_COMBINE_EVENT_INFO( T1_START, ( taskId_ ) ) ) )
#            define T1_TRACE_START_PC_( vrnt_, coreId_, taskId_, now_ )              \
                T1_INCR_PREEMPTIONS_PC(                                              \
                    ( coreId_ ),                                                     \
                    T1_TRACE_ATOMIC__(                                               \
                        vrnt_,                                                       \
                        T1_TraceEvent,                                               \
                        T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                       \
                        T1_COMBINE_EVENT_INFO( T1_START, ( taskId_ ) ),              \
                        ( now_ ) ) )
#            define T1_TRACE_STOP_START_PC( vrnt_, coreId_, startTaskId_ )           \
                T1_TRACE_ATOMIC_(                                                    \
                    vrnt_,                                                           \
                    T1_TraceEvent,                                                   \
                    T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                           \
                    T1_COMBINE_EVENT_INFO( T1_STOP_START, ( startTaskId_ ) ) )
#            define T1_TRACE_STOP_START_PC_( vrnt_, coreId_, startTaskId_, now_ )    \
                T1_TRACE_ATOMIC__(                                                   \
                    vrnt_,                                                           \
                    T1_TraceEvent,                                                   \
                    T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                           \
                    T1_COMBINE_EVENT_INFO( T1_STOP_START, ( startTaskId_ ) ),        \
                    ( now_ ) )
#            define T1_TRACE_ACT_PC( vrnt_, coreId_, taskId_ )                       \
                T1_TRACE_ATOMIC_(                                                    \
                    vrnt_,                                                           \
                    T1_TraceEvent,                                                   \
                    T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                           \
                    T1_COMBINE_EVENT_INFO( T1_ACTIVATION, ( taskId_ ) ) )
#        endif /* defined T1_CROSS_CORE_ACT && 1 < T1_NOF_CORES */
#        define T1_TRACE_START_NOACT_PC( vrnt_, coreId_, taskId_ )                   \
            T1_INCR_PREEMPTIONS_PC(                                                  \
                ( coreId_ ),                                                         \
                T1_TRACE_ATOMIC_( vrnt_,                                             \
                                  T1_TraceEvent,                                     \
                                  T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),             \
                                  T1_COMBINE_EVENT_INFO( T1_START, ( taskId_ ) ) ) )
#        define T1_TRACE_START_NOACT_PC_( vrnt_, coreId_, taskId_, now_ )            \
            T1_INCR_PREEMPTIONS_PC(                                                  \
                ( coreId_ ),                                                         \
                T1_TRACE_ATOMIC__( vrnt_,                                            \
                                   T1_TraceEvent,                                    \
                                   T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),            \
                                   T1_COMBINE_EVENT_INFO( T1_START, ( taskId_ ) ),   \
                                   ( now_ ) ) )
#        define T1_TRACE_STOP_PC( vrnt_, coreId_, taskId_ )                          \
            T1_TRACE_ATOMIC_( vrnt_,                                                 \
                              T1_TraceEvent,                                         \
                              T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                 \
                              T1_COMBINE_EVENT_INFO( T1_STOP, ( taskId_ ) ) )
#        define T1_TRACE_STOP_PC_( vrnt_, coreId_, taskId_, now_ )                   \
            T1_TRACE_ATOMIC__( vrnt_,                                                \
                               T1_TraceEvent,                                        \
                               T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                \
                               T1_COMBINE_EVENT_INFO( T1_STOP, ( taskId_ ) ),        \
                               ( now_ ) )
#        define T1_TRACE_STOP_START_NOACT_PC( vrnt_, coreId_, startTaskId_ )         \
            T1_TRACE_ATOMIC_(                                                        \
                vrnt_,                                                               \
                T1_TraceEvent,                                                       \
                T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                               \
                T1_COMBINE_EVENT_INFO( T1_STOP_START, ( startTaskId_ ) ) )
#        define T1_TRACE_STOP_START_NOACT_PC_( vrnt_, coreId_, startTaskId_, now_ )  \
            T1_TRACE_ATOMIC__(                                                       \
                vrnt_,                                                               \
                T1_TraceEvent,                                                       \
                T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                               \
                T1_COMBINE_EVENT_INFO( T1_STOP_START, ( startTaskId_ ) ),            \
                ( now_ ) )
#        define T1_TRACE_START_ACT_PC( vrnt_,                                        \
                                       coreId_,                                      \
                                       taskId_,                                      \
                                       actCoreId_,                                   \
                                       actTime_ )                                    \
            T1_INCR_PREEMPTIONS_PC(                                                  \
                ( coreId_ ),                                                         \
                T1_TRACE_SYNC_SW(                                                    \
                    vrnt_,                                                           \
                    T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                           \
                    T1_COMBINE_EVENT_INFO( T1_START_IPT_START, ( taskId_ ) ),        \
                    ( ( actTime_ ) << 4 ) - ( actCoreId_ ) ) )
#        define T1_TRACE_START_ACT_PC_( vrnt_,                                       \
                                        coreId_,                                     \
                                        taskId_,                                     \
                                        actCoreId_,                                  \
                                        actTime_,                                    \
                                        now_ )                                       \
            T1_INCR_PREEMPTIONS_PC(                                                  \
                ( coreId_ ),                                                         \
                T1_TRACE_SYNC_SW_(                                                   \
                    vrnt_,                                                           \
                    T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                           \
                    T1_COMBINE_EVENT_INFO( T1_START_IPT_START, ( taskId_ ) ),        \
                    ( ( actTime_ ) << 4 ) - ( actCoreId_ ),                          \
                    ( now_ ) ) )
#        define T1_TRACE_STOP_START_ACT_PC( vrnt_,                                   \
                                            coreId_,                                 \
                                            startTaskId_,                            \
                                            actCoreId_,                              \
                                            actTime_ )                               \
            T1_TRACE_SYNC_SW(                                                        \
                vrnt_,                                                               \
                T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                               \
                T1_COMBINE_EVENT_INFO( T1_STOP_START_IPT_START, ( startTaskId_ ) ),  \
                ( ( actTime_ ) << 4 ) - ( actCoreId_ ) )
#        define T1_TRACE_STOP_START_ACT_PC_( vrnt_,                                  \
                                             coreId_,                                \
                                             startTaskId_,                           \
                                             actCoreId_,                             \
                                             actTime_,                               \
                                             now_ )                                  \
            T1_TRACE_SYNC_SW_(                                                       \
                vrnt_,                                                               \
                T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                               \
                T1_COMBINE_EVENT_INFO( T1_STOP_START_IPT_START, ( startTaskId_ ) ),  \
                ( ( actTime_ ) << 4 ) - ( actCoreId_ ),                              \
                ( now_ ) )
#        define T1_TRACE_START_STOP_PC( vrnt_, coreId_, taskId_ )                    \
            T1_TRACE_ATOMIC_( vrnt_,                                                 \
                              T1_TraceEvent,                                         \
                              T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                 \
                              T1_COMBINE_EVENT_INFO( T1_START_STOP, ( taskId_ ) ) )
#        define T1_TRACE_START_STOP_PC_( vrnt_, coreId_, taskId_, now_ )             \
            T1_TRACE_ATOMIC__( vrnt_,                                                \
                               T1_TraceEvent,                                        \
                               T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                \
                               T1_COMBINE_EVENT_INFO( T1_START_STOP, ( taskId_ ) ),  \
                               ( now_ ) )

#        if defined T1_TRACE_ACT_EVENT_AND_CROSS_CORE_ACT
#            define T1_NEEDS_IPT( coreId_, taskId_ )                                 \
                ( ( 0uL != T1_taskAct[taskId_] )                                     \
                  && ( 0uL                                                           \
                       != ( ( (T1_uint32_t)( coreId_ ) + T1_taskAct[taskId_] + 1uL ) \
                            & 0xFuL ) ) )
#        else
#            define T1_NEEDS_IPT( coreId_, taskId_ ) ( 0uL != T1_taskAct[taskId_] )
#        endif /* T1_TRACE_ACT_EVENT_AND_CROSS_CORE_ACT */

#    endif /* ! defined T1_DISABLE_T1_CONT && defined T1_FG_CONT */

#    define T1_P_SCOPE_FG_CONSTS0  ( &T1_scopeFgConsts0 )
#    define T1_P_SCOPE_FG_CONSTS1  ( &T1_scopeFgConsts1 )
#    define T1_P_SCOPE_FG_CONSTS2  ( &T1_scopeFgConsts2 )
#    define T1_P_SCOPE_FG_CONSTS3  ( &T1_scopeFgConsts3 )
#    define T1_P_SCOPE_FG_CONSTS4  ( &T1_scopeFgConsts4 )
#    define T1_P_SCOPE_FG_CONSTS5  ( &T1_scopeFgConsts5 )
#    define T1_P_SCOPE_FG_CONSTS6  ( &T1_scopeFgConsts6 )
#    define T1_P_SCOPE_FG_CONSTS7  ( &T1_scopeFgConsts7 )
#    define T1_P_SCOPE_FG_CONSTS8  ( &T1_scopeFgConsts8 )
#    define T1_P_SCOPE_FG_CONSTS9  ( &T1_scopeFgConsts9 )
#    define T1_P_SCOPE_FG_CONSTS10 ( &T1_scopeFgConsts10 )
#    define T1_P_SCOPE_FG_CONSTS11 ( &T1_scopeFgConsts11 )
#    define T1_P_SCOPE_FG_CONSTS12 ( &T1_scopeFgConsts12 )
#    define T1_P_SCOPE_FG_CONSTS13 ( &T1_scopeFgConsts13 )
#    define T1_P_SCOPE_FG_CONSTS14 ( &T1_scopeFgConsts14 )
#    if !defined T1_FG_CONT || defined T1_DISABLE_T1_CONT
#        define T1_P_SCOPE_CONSTS0  ( &T1_scopeConsts0 )
#        define T1_P_SCOPE_CONSTS1  ( &T1_scopeConsts1 )
#        define T1_P_SCOPE_CONSTS2  ( &T1_scopeConsts2 )
#        define T1_P_SCOPE_CONSTS3  ( &T1_scopeConsts3 )
#        define T1_P_SCOPE_CONSTS4  ( &T1_scopeConsts4 )
#        define T1_P_SCOPE_CONSTS5  ( &T1_scopeConsts5 )
#        define T1_P_SCOPE_CONSTS6  ( &T1_scopeConsts6 )
#        define T1_P_SCOPE_CONSTS7  ( &T1_scopeConsts7 )
#        define T1_P_SCOPE_CONSTS8  ( &T1_scopeConsts8 )
#        define T1_P_SCOPE_CONSTS9  ( &T1_scopeConsts9 )
#        define T1_P_SCOPE_CONSTS10 ( &T1_scopeConsts10 )
#        define T1_P_SCOPE_CONSTS11 ( &T1_scopeConsts11 )
#        define T1_P_SCOPE_CONSTS12 ( &T1_scopeConsts12 )
#        define T1_P_SCOPE_CONSTS13 ( &T1_scopeConsts13 )
#        define T1_P_SCOPE_CONSTS14 ( &T1_scopeConsts14 )
#    else /* defined T1_FG_CONT && ! defined T1_DISABLE_T1_CONT */
#        define T1_P_SCOPE_CONSTS0  ( &T1_scopeFgConsts0._ )
#        define T1_P_SCOPE_CONSTS1  ( &T1_scopeFgConsts1._ )
#        define T1_P_SCOPE_CONSTS2  ( &T1_scopeFgConsts2._ )
#        define T1_P_SCOPE_CONSTS3  ( &T1_scopeFgConsts3._ )
#        define T1_P_SCOPE_CONSTS4  ( &T1_scopeFgConsts4._ )
#        define T1_P_SCOPE_CONSTS5  ( &T1_scopeFgConsts5._ )
#        define T1_P_SCOPE_CONSTS6  ( &T1_scopeFgConsts6._ )
#        define T1_P_SCOPE_CONSTS7  ( &T1_scopeFgConsts7._ )
#        define T1_P_SCOPE_CONSTS8  ( &T1_scopeFgConsts8._ )
#        define T1_P_SCOPE_CONSTS9  ( &T1_scopeFgConsts9._ )
#        define T1_P_SCOPE_CONSTS10 ( &T1_scopeFgConsts10._ )
#        define T1_P_SCOPE_CONSTS11 ( &T1_scopeFgConsts11._ )
#        define T1_P_SCOPE_CONSTS12 ( &T1_scopeFgConsts12._ )
#        define T1_P_SCOPE_CONSTS13 ( &T1_scopeFgConsts13._ )
#        define T1_P_SCOPE_CONSTS14 ( &T1_scopeFgConsts14._ )
#    endif /* ! defined T1_FG_CONT || defined T1_DISABLE_T1_CONT */

/*! \brief T1.scope entry in plugin table. */
#    define T1_scopePlugin ( &T1_scopePluginStruct )

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_DeclarePlugin( T1_scopePluginStruct );
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    define T1_START_SEC_VAR_CLEARED_32
#    include "T1_MemMap.h"
/*!
 * \brief Used to achieve mutual exclusion for calibrating T1 between different cores.
 */
T1_EXTERN T1_bakery_t T1_SEC_VAR_CLEARED_32 T1_calibrationSemPC[];
#    define T1_STOP_SEC_VAR_CLEARED_32
#    include "T1_MemMap.h"

#    if defined T1_CROSS_CORE_ACT && 1 < T1_NOF_CORES
#        define T1_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
/*!
 * \brief Used to record task activation times
 */
T1_EXTERN T1_uint32_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_taskAct[];
#        define T1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* defined T1_CROSS_CORE_ACT */

#    define T1_START_SEC_CODE
#    include "T1_MemMap.h"
/*!
 * \brief Re-initialize T1.scope for CERT version of the T1-TARGET-SW.
 * \ifnot CERT_SECTION
 *   \copydetails T1_scope_cert_interfaces
 * \endif
 * \ingroup T1_scope_cert_interfaces
 * \param[in] coreId the T1 logical ID of the calling core
 *
 * This can be used to re-start tracing after a trigger. Use only when the
 * T1-HOST-SW is not connected.
 * See \ref PC.
 */
T1_EXTERN void T1_CODE T1_InitTraceBufferPC( T1_uint8Least_t coreId );

/*!
 * \brief Re-initialize T1.scope for CERT version of the T1-TARGET-SW.
 * \ifnot CERT_SECTION
 *   \copydetails T1_scope_cert_interfaces
 * \endif
 * \ingroup T1_scope_cert_interfaces
 *
 * This can be used to re-start tracing after a trigger. Use only when the
 * T1-HOST-SW is not connected.
 */
#    define T1_InitTraceBuffer( ) T1_InitTraceBufferPC( T1_GetCoreIdOffset( ) )

/*!
 * \brief Insert #T1_TRIGGER event to mark interesting trace data.
 * \ingroup T1_scope_interfaces
 * \param[in] coreId the T1 logical ID of the calling core
 * \param[in] afterXevents halt tracing only after this number of further events
 * \returns
 *  - #T1_OK     on success
 *  - #T1_NOFUNC if the trigger has already been set
 *  - #T1_VALUE  if `afterXevents` exceeds trace buffer size
 *  - #T1_FAILED if trace buffer corruptions prevents triggering
 *
 * Unless already streaming, halt tracing for download and analysis by the T1-HOST-SW.
 * See \ref PC, \ref INTRPT and \ref USER_TRIGGERS.
 */
T1_EXTERN T1_status_t T1_CODE T1_SetStopTriggerPC( T1_uint8Least_t coreId,
                                                   T1_nOfEntries_t afterXevents );

/*!
 * \brief Insert #T1_TRIGGER event to mark interesting trace data.
 * \ingroup T1_scope_interfaces
 *
 * \copydetails T1_SetStopTriggerPC
 */
T1_EXTERN T1_status_t T1_CODE
T1_SetStopTriggerNoSuspPC( T1_uint8Least_t coreId, T1_nOfEntries_t afterXevents );

/*!
 * \brief Insert #T1_TRIGGER event to mark interesting trace data.
 * \ingroup T1_scope_interfaces
 * \param[in] afterXevents_ halt tracing only after this number of further events
 * \returns
 *  - #T1_OK     on success
 *  - #T1_NOFUNC if the trigger has already been set
 *  - #T1_VALUE  if `afterXevents_` exceeds trace buffer size
 *  - #T1_FAILED if trace buffer corruptions prevents triggering
 *
 * Unless already streaming, halt tracing for download and analysis by the T1-HOST-SW.
 * See \ref PC, \ref INTRPT and \ref USER_TRIGGERS.
 */
#    define T1_SetStopTrigger( afterXevents_ )                                       \
        T1_SetStopTriggerPC( T1_GetCoreIdOffset( ), afterXevents_ )

/*!
 * \brief Insert #T1_TRIGGER event to mark interesting trace data.
 * \ingroup T1_scope_interfaces
 *
 * \copydetails T1_SetStopTrigger
 */
#    define T1_SetStopTriggerNoSusp( afterXevents_ )                                 \
        T1_SetStopTriggerNoSuspPC( T1_GetCoreIdOffset( ), afterXevents_ )

/*!
 * \brief Insert #T1_TRIGGER event to mark interesting trace data.
 * \ingroup T1_scope_interfaces
 *
 * \copydetails T1_SetStopTrigger
 */
#    define T1_SetStopTriggerFast( afterXevents_ ) T1_SetStopTrigger( afterXevents_ )

/*!
 * \brief Insert #T1_TRIGGER event to mark interesting trace data.
 * \ingroup T1_scope_interfaces
 * \param[in] coreId_ the T1 logical ID of the calling core
 *
 * \copydetails T1_SetStopTrigger
 */
#    define T1_SetStopTriggerFastPC( coreId_, afterXevents_ )                        \
        T1_SetStopTriggerPC( coreId_, afterXevents_ )

T1_EXTERN void T1_CODE T1_TraceData_( T1_scopeConsts_t *pScopeConsts,
                                      T1_eventInfo_t eventInfo,
                                      T1_uint8_t const *pData,
                                      T1_uint8Least_t length );
T1_EXTERN void T1_CODE T1_TraceDataNoSusp_( T1_scopeConsts_t *pScopeConsts,
                                            T1_eventInfo_t eventInfo,
                                            T1_uint8_t const *pData,
                                            T1_uint8Least_t length );
T1_EXTERN T1_uint8Least_t T1_CODE
T1_TraceDataNoSuspTime_( T1_scopeConsts_t *pScopeConsts,
                         T1_eventInfo_t eventInfo,
                         T1_uint8_t const *pData,
                         T1_uint8Least_t length,
                         T1_tickUint_t now );
#    define T1_TraceDataRC_       T1_TraceData_
#    define T1_TraceDataNoSuspRC_ T1_TraceDataNoSusp_

T1_EXTERN T1_uint32_t T1_CODE T1_16toU32( T1_uint16_t data16 );

/*!
 * \brief   Start the T1 overhead calibration sequence.
 * \ingroup T1_scope_interfaces
 * \param[in] coreId the T1 logical ID of the calling core
 *
 * This should normally be called via T1_CONT_CALIBRATE_OVERHEADS_PC() or
 * T1_CONT_CALIBRATE_OVERHEADS_NOSUSP_PC() in order to calibrate the overheads with
 * T1.cont.
 */
T1_EXTERN void T1_CODE T1_ScopeOverheadSequenceNoSuspPC( T1_uint8Least_t coreId );

/*!
 * \brief   Trace the dynamic re-naming of a task.
 * \ingroup T1_scope_trace_interfaces
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] now_    the trace time
 * \param[in] taskId_ the T1.scope task ID
 *
 * See \ref PC and \ref INTRPT.
 */
#    define T1_TraceNameNoSuspTimePC( coreId_, now_, taskId_ )                       \
        ( T1_TraceNameNoSuspTime_( T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),            \
                                   ( taskId_ ),                                      \
                                   ( now_ ) ) )

/*!
 * \brief   Trace the dynamic re-naming of a task.
 * \ingroup T1_scope_trace_interfaces
 * \param[in] now_    the trace time
 * \param[in] taskId_ the T1.scope task ID
 *
 * See \ref INTRPT.
 */
#    define T1_TraceNameNoSuspTime( now_, taskId_ )                                  \
        ( T1_TraceNameNoSuspTime_(                                                   \
            T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),                     \
            ( taskId_ ),                                                             \
            ( now_ ) ) )

/*!
 * \internal
 * \brief   Trace the dynamic re-naming of a task.
 * \ingroup T1_scope_trace_interfaces
 */
T1_EXTERN T1_uint8Least_t T1_CODE T1_TraceNameNoSuspTime_(
    T1_scopeConsts_t *pScopeConsts, T1_taskId_t taskId, T1_tickUint_t now );

/*!
 * \brief Trace the dynamic re-initializing of OS-specific IDs.
 * \ingroup T1_scope_trace_interfaces
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] now_    the trace time
 * \param[in] taskId_ the T1.scope task ID
 *
 * See \ref PC and \ref INTRPT.
 */
#    define T1_TraceOsIdsNoSuspTimePC( coreId_, now_, taskId_ )                      \
        ( T1_TraceOsIdsNoSuspTime_( T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),           \
                                    ( taskId_ ),                                     \
                                    ( now_ ) ) )

/*!
 * \brief Trace the dynamic re-initializing of OS-specific IDs.
 * \ingroup T1_scope_trace_interfaces
 * \param[in] now_    the trace time
 * \param[in] taskId_ the T1.scope task ID
 *
 * See \ref INTRPT.
 */
#    define T1_TraceOsIdsNoSuspTime( now_, taskId_ )                                 \
        ( T1_TraceOsIdsNoSuspTime_(                                                  \
            T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),                     \
            ( taskId_ ),                                                             \
            ( now_ ) ) )

/*!
 * \internal
 * \brief Trace the dynamic re-initializing of OS-specific IDs.
 * \ingroup T1_scope_trace_interfaces
 */
T1_EXTERN T1_uint8Least_t T1_CODE T1_TraceOsIdsNoSuspTime_(
    T1_scopeConsts_t *pScopeConsts, T1_taskId_t taskId, T1_tickUint_t now );

/*!
 * \brief Read some or all of the trace buffer.
 * \ifnot CERT_SECTION
 *   \copydetails T1_scope_cert_interfaces
 * \endif
 * \ingroup T1_scope_cert_interfaces
 * \param[in]  coreId      the T1 logical ID of the calling core
 * \param[in]  pDest       the address at which to write the data, as uint32 values
 * \param[in]  offsetWords the number of uint32 values to skip in the trace buffer.
 *                         It needs to be incremented by the return value of the
 *                         previous call, so that successive calls read the entire
 *                         trace buffer.
 * \param[in]  maxWords    the maximum number of uint32 values to write
 * \returns Number of bytes copied, or
 *          minus one to denote that tracing was restarted during the copy,
 *          corrupting the results, or
 *          minus two to denote invalid coreId.
 *          Zero (no bytes copied) occurs either when offsetWords skips the entire
 *          buffer, which is normal after reading all the trace data, or
 *          when offsetWords is zero but tracing is enabled.
 *
 * See \ref PC.
 */
T1_EXTERN T1_sint32_t T1_CODE T1_ReadTraceBufferPC( T1_uint8Least_t coreId,
                                                    T1_uint32_t *pDest,
                                                    T1_uint32_t offsetWords,
                                                    T1_uint32_t maxWords );

/*!
 * \brief Read some or all of the trace buffer.
 * \ifnot CERT_SECTION
 *   \copydetails T1_scope_cert_interfaces
 * \endif
 * \ingroup T1_scope_cert_interfaces
 * \param[in]  pDest_       the address at which to write the read data
 * \param[in]  offsetWords_ the number of uint32 values to skip in the trace buffer.
 *                          It needs to be incremented by the return value of the
 *                          previous call, so that successive calls read the entire
 *                          trace buffer.
 * \param[in]  maxWords_    the maximum number of uint32 values to write
 * \returns Number of bytes copied, or
 *          minus one to denote that tracing was restarted during the copy,
 *          corrupting the results.
 *          Zero (no bytes copied) occurs either when offsetWords_ skips the entire
 *          buffer, which is normal after reading all the trace data, or
 *          when offsetWords_ is zero but tracing is enabled.
 *
 * See \ref PC.
 */
#    define T1_ReadTraceBuffer( pDest_, offsetWords_, maxWords_ )                    \
    ( T1_ReadTraceBufferPC( T1_GetCoreIdOffset( ), (pDest_), (offsetWords_), (maxWords_) )

/*!
 * \brief Start streaming out trace data without T1-HOST-SW communication.
 * \ifnot CERT_SECTION
 *   \copydetails T1_scope_cert_interfaces
 * \endif
 * \ingroup T1_scope_cert_interfaces
 * \param[in]  coreId      the T1 logical ID of the calling core
 * \returns
 *  - #T1_OK     on success
 *  - #T1_NOFUNC unable to stream, for example because the T1-HOST-SW has established
 *               a communications link to the T1-TARGET-SW
 *
 * See \ref PC.
 */
T1_status_t T1_CODE T1_StartStreamingPC( T1_uint8Least_t coreId );

/*!
 * \brief Start streaming out trace data without T1-HOST-SW communication.
 * \ifnot CERT_SECTION
 *   \copydetails T1_scope_cert_interfaces
 * \endif
 * \ingroup T1_scope_cert_interfaces
 * \returns
 *  - #T1_OK     on success
 *  - #T1_NOFUNC unable to stream, for example because the T1-HOST-SW has established
 *               a communications link to the T1-TARGET-SW
 *
 * See \ref PC.
 */
#    define T1_StartStreaming( ) ( T1_StartStreamingPC( T1_GetCoreIdOffset( ) ) )

/*!
 * \addtogroup T1_scope_callouts
 *
 * @{
 */
/*
 * The following functions, by default, map to their equivalent without 'UM'. They
 * are called from T1_Handler and T1_ContBgHandler, which (can) run in user mode and
 * they can be overridden in the event that calling T1_TraceEvent in user mode is not
 * permitted. We know of one case where the trace timer cannot be accessed in user
 * mode, for example. In this case, these functions can be re-implemented using
 * CallTrustedFunction, or some equivalent, to call T1_TraceEvent in supervisor mode.
 * This should only be done with support from GLIWA.
 */

/*!
 * \brief Callout to execute T1_ScopeOverheadSequenceNoSuspPC() from T1_HandlerPC().
 * \param[in] coreId the T1 logical core ID of the calling core
 *
 * Call T1_ScopeOverheadSequenceNoSuspPC() in supervisor mode.
 *
 * \par Default Implementation
 * The default implementation assumes that T1_HandlerPC() runs in supervisor mode
 * already.
 *
 * \note T1_ScopeOverheadSequenceNoSuspPC() reads the trace timer which might not be
 *       safe from user-mode.
 *
 */
T1_EXTERN void T1_CODE T1_ScopeOverheadSequenceUMPC( T1_uint8Least_t coreId );

/*!
 * \brief Callout to insert one event in the trace buffer without assuming supervisor
 *        privileges.
 * \param[in] coreId    the T1 logical core ID of the calling core
 * \param[in] eventInfo combined event ID and info field created by
 *                      T1_COMBINE_EVENT_INFO()
 * \returns             all counting bits of the time-stamp
 *
 * This is used as a callout from library code and should not normally be called
 * directly from user code.
 *
 * \par Default Implementation
 * The default implementation uses T1.flex to insert the event into the trace buffer,
 * if T1.flex is available. It will call T1_TraceEventNoSuspUMPC() with interrupts
 * disabled if T1.flex is not available.
 *
 */
T1_EXTERN void T1_CODE T1_TraceEventUMPC( T1_uint8Least_t coreId,
                                          T1_eventInfo_t eventInfo );

/*!
 * \brief Callout to insert one event in the trace buffer without assuming that
 *        interrupts are disabled without assuming supervisor privileges.
 * \param[in] coreId    the T1 logical core ID of the calling core
 * \param[in] eventInfo combined event ID and info field created by
 *                      T1_COMBINE_EVENT_INFO()
 * \returns             all counting bits of the time-stamp
 *
 * This is used as a callout from library code and should not normally be called
 * directly from user code.
 *
 */
T1_EXTERN T1_tickUint_t T1_CODE T1_TraceEventNoSuspUMPC( T1_uint8Least_t coreId,
                                                         T1_eventInfo_t eventInfo );

/*! @} */

/*!
 * \internal
 * \brief For testing only.
 */
T1_EXTERN void T1_CODE T1_TraceScopeUploadNoSuspTime__(
    T1_scopeConsts_t *pScopeConsts, T1_eventInfo_t eventInfo, T1_tickUint_t now );
#    define T1_STOP_SEC_CODE
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_8
#    include "T1_MemMap.h"
/*!
 * \brief Width of the T1 sync timer in bits. \sa \ref syncTimeBitLength
 */
T1_EXTERN const T1_uint8_t T1_SEC_CONST_8 T1_syncTimerWidthBits;
#    define T1_STOP_SEC_CONST_8
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_EXTERN const T1_uint32_t T1_SEC_CONST_32 T1_scopeRevision;
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

/*!
 * \brief Number of events stored in the core specific trace buffer, see \ref PC.
 * \param[in] coreId_ the T1 logical ID of the calling core
 */
#    define T1_TRACE_BUFFER_ENTRIES_PC( coreId_ ) ( T1_traceEntriesPC[( coreId_ )] )

/*!
 * \brief Number of events stored in the core specific trace buffer, see \ref PC.
 * \param[in] coreId_ the T1 logical ID of the calling core
 */
#    define T1_BUFFER_SIZE_PC( coreId_ )          ( T1_TRACE_BUFFER_ENTRIES_PC( coreId_ ) )

/*!
 * \brief Number of events stored in the core specific trace buffer.
 */
#    define T1_BUFFER_SIZE( )                     ( T1_BUFFER_SIZE_PC( T1_GetCoreIdOffset( ) ) )

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
/*!
 * \brief Array of pointers to the trace buffers per system
 */
T1_EXTERN T1_traceEntry_t T1_FARPTR const T1_SEC_CONST_32 T1_traceBufferPC[];
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_16
#    include "T1_MemMap.h"
/*!
 * \brief Array of pointers to the trace sizes per system
 */
T1_EXTERN T1_nOfEntries_t const T1_SEC_CONST_16 T1_traceEntriesPC[];
#    define T1_STOP_SEC_CONST_16
#    include "T1_MemMap.h"

#    define T1_START_SEC_CODE_FAST
#    include "T1_MemMap.h"

/*!
 * \brief   Callout to insert one event in the trace buffer without suspending
 *          interrupts.
 * \ingroup T1_scope_callouts
 *
 * This is not part of the T1-TARGET-SW API. Do **NOT** call it directly from user
 * code. It is called from the T1.scope API macro layer, see T1_TraceEventNoSuspPC(),
 * for example.
 * This is one of the most time-critical routines in the T1-TARGET-SW. In addition to
 * requiring efficient code, the following additional restrictions apply:
 * - Processors with floating point and/or MAC registers are not permitted to use them
 * - RH850 projects using `-no_check_rh850_abi_flags` with the *22* libraries
 *   are not permitted to use *R2* and *R15-R24*.
 *
 * \note This code should only be changed under advice from a GLIWA engineer.
 *
 */
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_NOINLINE T1_CODE_OPT T1_TraceEventNoSusp__( T1_scopeConsts_t *pScopeConsts,
                                               T1_eventInfo_t eventInfo );

/*!
 * \brief Insert one event into the trace buffer.
 *
 * This is not part of the T1-TARGET-SW API. Do **NOT** call it directly from user
 * code. It is called from the T1.scope API macro layer.
 */
#    if defined T1_CONT_REMOTE
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_NOINLINE T1_CODE_OPT T1_TraceEventNoSuspTimeRC__( T1_scopeConsts_t *pScopeConsts,
                                                     T1_eventInfo_t eventInfo,
                                                     T1_tickUint_t now );
#    else  /* ! defined T1_CONT_REMOTE */
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_NOINLINE T1_CODE_OPT T1_TraceEventNoSuspTime__( T1_scopeConsts_t *pScopeConsts,
                                                   T1_eventInfo_t eventInfo,
                                                   T1_tickUint_t now );
#    endif /* defined T1_CONT_REMOTE */

#    if defined T1_NEAR_CODE_FAST
T1_EXTERN T1_tickUint_t T1_NOINLINE T1_NEAR_CODE_FAST
T1_NearTraceEventNoSusp__( T1_scopeConsts_t *pScopeConsts, T1_eventInfo_t eventInfo );
T1_EXTERN T1_tickUint_t T1_NOINLINE T1_NEAR_CODE_FAST T1_NearTraceEventNoSuspTime__(
    T1_scopeConsts_t *pScopeConsts, T1_eventInfo_t eventInfo, T1_tickUint_t now );
T1_EXTERN T1_tickUint_t T1_NOINLINE T1_NEAR_CODE_FAST T1_NearTraceEventNoSuspTimeRC__(
    T1_scopeConsts_t *pScopeConsts, T1_eventInfo_t eventInfo, T1_tickUint_t now );
T1_EXTERN void T1_NOINLINE T1_NEAR_CODE_FAST T1_CODE_OPT T1_NearSWStopNoSusp__(
    T1_scopeConsts_t *pScopeConsts, T1_eventInfo_t eventInfo, T1_uint32_t syncData );
T1_EXTERN T1_tickUint_t T1_NEAR_CODE_FAST T1_CODE_OPT
T1_NearTraceUint32RestNoSusp( T1_scopeConsts_t *pScopeConsts, T1_uint32_t data );
T1_EXTERN T1_tickUint_t T1_NEAR_CODE_FAST T1_CODE_OPT
T1_NearTraceUint32RestNoSuspRC( T1_scopeConsts_t *pScopeConsts, T1_uint32_t data );
T1_EXTERN T1_tickUint_t T1_NEAR_CODE_FAST T1_CODE_OPT
T1_NearTraceUint32RestNoSuspFg( T1_scopeConsts_t *pScopeConsts, T1_uint32_t data );
T1_EXTERN T1_tickUint_t T1_NEAR_CODE_FAST T1_CODE_OPT T1_NearTraceUint56RestNoSusp(
    T1_scopeConsts_t *pScopeConsts, T1_uint32_t dataLow, T1_uint32_t dataHigh );
T1_EXTERN T1_tickUint_t T1_NEAR_CODE_FAST T1_CODE_OPT T1_NearTraceUint56RestNoSuspRC(
    T1_scopeConsts_t *pScopeConsts, T1_uint32_t dataLow, T1_uint32_t dataHigh );
T1_EXTERN T1_tickUint_t T1_NEAR_CODE_FAST T1_CODE_OPT T1_NearTraceUint56RestNoSuspFg(
    T1_scopeConsts_t *pScopeConsts, T1_uint32_t dataLow, T1_uint32_t dataHigh );
#    elif defined T1_GCC_ADAPT
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_NOINLINE T1_NearTraceEventNoSusp__( T1_scopeConsts_t *pScopeConsts,
                                       T1_eventInfo_t eventInfo );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_NOINLINE T1_NearTraceEventNoSuspTime__( T1_scopeConsts_t *pScopeConsts,
                                           T1_eventInfo_t eventInfo,
                                           T1_tickUint_t now );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_NOINLINE T1_NearTraceEventNoSuspTimeRC__( T1_scopeConsts_t *pScopeConsts,
                                             T1_eventInfo_t eventInfo,
                                             T1_tickUint_t now );
T1_EXTERN T1_CODE_FAST( void ) T1_NOINLINE T1_CODE_OPT
    T1_NearSWStopNoSusp__( T1_scopeConsts_t *pScopeConsts,
                           T1_eventInfo_t eventInfo,
                           T1_uint32_t syncData );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_CODE_OPT T1_NearTraceUint32RestNoSusp( T1_scopeConsts_t *pScopeConsts,
                                          T1_uint32_t data );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_CODE_OPT T1_NearTraceUint32RestNoSuspRC( T1_scopeConsts_t *pScopeConsts,
                                            T1_uint32_t data );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_CODE_OPT T1_NearTraceUint32RestNoSuspFg( T1_scopeConsts_t *pScopeConsts,
                                            T1_uint32_t data );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_CODE_OPT T1_NearTraceUint56RestNoSusp( T1_scopeConsts_t *pScopeConsts,
                                          T1_uint32_t dataLow,
                                          T1_uint32_t dataHigh );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_CODE_OPT T1_NearTraceUint56RestNoSuspRC( T1_scopeConsts_t *pScopeConsts,
                                            T1_uint32_t dataLow,
                                            T1_uint32_t dataHigh );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_CODE_OPT T1_NearTraceUint56RestNoSuspFg( T1_scopeConsts_t *pScopeConsts,
                                            T1_uint32_t dataLow,
                                            T1_uint32_t dataHigh );
#        define T1_TraceEventNoSusp__ T1_NearTraceEventNoSusp__
#        define T1_SWStopNoSusp__     T1_NearSWStopNoSusp__
#    else
#        define T1_NearTraceEventNoSusp__       T1_TraceEventNoSusp__
#        define T1_NearTraceEventNoSuspTime__   T1_TraceEventNoSuspTime__
#        define T1_NearTraceEventNoSuspTimeRC__ T1_TraceEventNoSuspTimeRC__
#        define T1_NearSWStopNoSusp__           T1_SWStopNoSusp__
#        define T1_NearTraceUint32RestNoSusp    T1_TraceUint32RestNoSusp
#        define T1_NearTraceUint32RestNoSuspRC  T1_TraceUint32RestNoSuspRC
#        define T1_NearTraceUint32RestNoSuspFg  T1_TraceUint32RestNoSuspFg
#        define T1_NearTraceUint56RestNoSusp    T1_TraceUint56RestNoSusp
#        define T1_NearTraceUint56RestNoSuspRC  T1_TraceUint56RestNoSuspRC
#        define T1_NearTraceUint56RestNoSuspFg  T1_TraceUint56RestNoSuspFg
#    endif /* defined T1_NEAR_CODE_FAST */

#    define T1_SWStopNoSuspRC__     T1_SWStopNoSusp__
#    define T1_SWStopNoSuspTimeRC__ T1_SWStopNoSuspTime__
T1_EXTERN T1_CODE_FAST( void ) T1_NOINLINE T1_CODE_OPT
    T1_SWStopNoSusp__( T1_scopeConsts_t *pScopeConsts,
                       T1_eventInfo_t eventInfo,
                       T1_uint32_t syncData );
T1_EXTERN T1_CODE_FAST( void ) T1_NOINLINE T1_CODE_OPT
    T1_SWStopNoSuspTime__( T1_scopeConsts_t *pScopeConsts,
                           T1_uint32_t syncData,
                           T1_tickUint_t traceTime );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_CODE_OPT T1_TraceUint32RestNoSusp( T1_scopeConsts_t *pScopeConsts,
                                      T1_uint32_t data );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_CODE_OPT T1_TraceUint32RestNoSuspRC( T1_scopeConsts_t *pScopeConsts,
                                        T1_uint32_t data );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_CODE_OPT T1_TraceUint32RestNoSuspFg( T1_scopeConsts_t *pScopeConsts,
                                        T1_uint32_t data );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_CODE_OPT T1_TraceUint56RestNoSusp( T1_scopeConsts_t *pScopeConsts,
                                      T1_uint32_t dataLow,
                                      T1_uint32_t dataHigh );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_CODE_OPT T1_TraceUint56RestNoSuspRC( T1_scopeConsts_t *pScopeConsts,
                                        T1_uint32_t dataLow,
                                        T1_uint32_t dataHigh );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_CODE_OPT T1_TraceUint56RestNoSuspFg( T1_scopeConsts_t *pScopeConsts,
                                        T1_uint32_t dataLow,
                                        T1_uint32_t dataHigh );
T1_EXTERN T1_CODE_FAST( T1_uint32_t )
T1_CODE_OPT T1_TraceToSyncNoSusp__( T1_scopeConsts_t *pScopeConsts,
                                    T1_tickUint_t traceTime );
T1_EXTERN T1_CODE_FAST( void ) T1_CODE_OPT
    T1_TraceSync56RestNoSusp( T1_scopeConsts_t *pScopeConsts,
                              T1_tickUint_t traceTime );

#    define T1_STOP_SEC_CODE_FAST
#    include "T1_MemMap.h"

/* Foreground T1.cont core-specific dispatchers. */

#    if 1 == T1_NOF_CORES                                                            \
        || ( defined T1_GET_RAW_TIME && defined T1_RAW_TO_TRACE_TIME )
#        define T1_START_SEC_CODE_FAST
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch0( T1_scopeFgConsts_t *pScopeConsts,
                  T1_eventInfo_t eventInfo,
                  T1_uint8Least_t handlerIdx );
#        define T1_STOP_SEC_CODE_FAST
#        include "T1_MemMap.h"
#    else /* 1 != T1_NOF_CORES && (! defined T1_GET_RAW_TIME || ! defined            \
             T1_RAW_TO_TRACE_TIME) */
#        define T1_CORE0_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch0( T1_scopeFgConsts_t *pScopeConsts,
                  T1_eventInfo_t eventInfo,
                  T1_uint8Least_t handlerIdx );
#        define T1_CORE0_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 1 == T1_NOF_CORES || (defined T1_GET_RAW_TIME && defined               \
              T1_RAW_TO_TRACE_TIME) */
#    if 1 < T1_NOF_CORES
#        define T1_CORE1_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch1( T1_scopeFgConsts_t *pScopeConsts,
                  T1_eventInfo_t eventInfo,
                  T1_uint8Least_t handlerIdx );
#        define T1_CORE1_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 1 < T1_NOF_CORES */
#    if 2 < T1_NOF_CORES
#        define T1_CORE2_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch2( T1_scopeFgConsts_t *pScopeConsts,
                  T1_eventInfo_t eventInfo,
                  T1_uint8Least_t handlerIdx );
#        define T1_CORE2_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 2 < T1_NOF_CORES */
#    if 3 < T1_NOF_CORES
#        define T1_CORE3_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch3( T1_scopeFgConsts_t *pScopeConsts,
                  T1_eventInfo_t eventInfo,
                  T1_uint8Least_t handlerIdx );
#        define T1_CORE3_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 3 < T1_NOF_CORES */
#    if 4 < T1_NOF_CORES
#        define T1_CORE4_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch4( T1_scopeFgConsts_t *pScopeConsts,
                  T1_eventInfo_t eventInfo,
                  T1_uint8Least_t handlerIdx );
#        define T1_CORE4_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 4 < T1_NOF_CORES */
#    if 5 < T1_NOF_CORES
#        define T1_CORE5_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch5( T1_scopeFgConsts_t *pScopeConsts,
                  T1_eventInfo_t eventInfo,
                  T1_uint8Least_t handlerIdx );
#        define T1_CORE5_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 5 < T1_NOF_CORES */
#    if 6 < T1_NOF_CORES
#        define T1_CORE6_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch6( T1_scopeFgConsts_t *pScopeConsts,
                  T1_eventInfo_t eventInfo,
                  T1_uint8Least_t handlerIdx );
#        define T1_CORE6_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 6 < T1_NOF_CORES */
#    if 7 < T1_NOF_CORES
#        define T1_CORE7_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch7( T1_scopeFgConsts_t *pScopeConsts,
                  T1_eventInfo_t eventInfo,
                  T1_uint8Least_t handlerIdx );
#        define T1_CORE7_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 7 < T1_NOF_CORES */
#    if 8 < T1_NOF_CORES
#        define T1_CORE8_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch8( T1_scopeFgConsts_t *pScopeConsts,
                  T1_eventInfo_t eventInfo,
                  T1_uint8Least_t handlerIdx );
#        define T1_CORE8_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 8 < T1_NOF_CORES */
#    if 9 < T1_NOF_CORES
#        define T1_CORE9_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch9( T1_scopeFgConsts_t *pScopeConsts,
                  T1_eventInfo_t eventInfo,
                  T1_uint8Least_t handlerIdx );
#        define T1_CORE9_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 9 < T1_NOF_CORES */
#    if 10 < T1_NOF_CORES
#        define T1_CORE10_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch10( T1_scopeFgConsts_t *pScopeConsts,
                   T1_eventInfo_t eventInfo,
                   T1_uint8Least_t handlerIdx );
#        define T1_CORE10_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 10 < T1_NOF_CORES */
#    if 11 < T1_NOF_CORES
#        define T1_CORE11_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch11( T1_scopeFgConsts_t *pScopeConsts,
                   T1_eventInfo_t eventInfo,
                   T1_uint8Least_t handlerIdx );
#        define T1_CORE11_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 11 < T1_NOF_CORES */
#    if 12 < T1_NOF_CORES
#        define T1_CORE12_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch12( T1_scopeFgConsts_t *pScopeConsts,
                   T1_eventInfo_t eventInfo,
                   T1_uint8Least_t handlerIdx );
#        define T1_CORE12_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 12 < T1_NOF_CORES */
#    if 13 < T1_NOF_CORES
#        define T1_CORE13_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch13( T1_scopeFgConsts_t *pScopeConsts,
                   T1_eventInfo_t eventInfo,
                   T1_uint8Least_t handlerIdx );
#        define T1_CORE13_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 13 < T1_NOF_CORES */
#    if 14 < T1_NOF_CORES
#        define T1_CORE14_START_SEC_CODE
#        include "T1_MemMap.h"
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_Dispatch14( T1_scopeFgConsts_t *pScopeConsts,
                   T1_eventInfo_t eventInfo,
                   T1_uint8Least_t handlerIdx );
#        define T1_CORE14_STOP_SEC_CODE
#        include "T1_MemMap.h"
#    endif /* 14 < T1_NOF_CORES */

#    define T1_START_SEC_CODE
#    include "T1_MemMap.h"
T1_EXTERN T1_tickUint_t T1_CODE T1_DispatchTimePC( T1_uint8Least_t coreId,
                                                   T1_eventInfo_t eventInfo,
                                                   T1_uint8Least_t handlerIdx,
                                                   T1_tickUint_t now );
#    define T1_STOP_SEC_CODE
#    include "T1_MemMap.h"

/*!
 * \name T1_TraceActivation
 * @{
 * \def T1_TraceActivation
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task activation. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of activated task
 *
 * \def T1_TraceActivationPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task activation. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of activated task
 *
 * \def T1_TraceActivationFast
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task activation. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of activated task
 *
 * \def T1_TraceActivationFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task activation. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of activated task
 *
 * \def T1_TraceActivationNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task activation. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of activated task
 *
 * \def T1_TraceActivationNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task activation. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of activated task
 * @}
 *
 * \name T1_TraceStart
 * @{
 * \def T1_TraceStart
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR start. See also T1_TraceStartNoAct(), especially for ISRs.
 *        See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task/ISR start. See also T1_TraceStartNoAct(), especially for ISRs.
 *        See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartFast
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task/ISR start. See also T1_TraceStartNoAct(), especially for ISRs.
 *        See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task/ISR start. See also T1_TraceStartNoAct(), especially for ISRs.
 * See \ref PC and \ref INTRPT. \param[in] coreId_ the T1 logical ID of the calling
 * core \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task/ISR start. See also T1_TraceStartNoAct(), especially for ISRs.
 * See \ref PC and \ref INTRPT. \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task/ISR start. See also T1_TraceStartNoAct(), especially for ISRs.
 * See \ref PC and \ref INTRPT. \param[in] coreId_ the T1 logical ID of the calling
 * core \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartNoSuspTime
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] time_   nominal time of task/ISR start
 * \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartNoSuspTimePC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] time_   nominal time of task/ISR start
 * \param[in] taskId_ T1.scope task ID of starting task
 * @}
 *
 * \name T1_TraceStartNoAct
 * @{
 * \def T1_TraceStartNoAct
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR start for which there is no activation event. This is not
 * compatible with multiple activation. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartNoActPC
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR start for which there is no activation event. This is not
 * compatible with multiple activation. See \ref PC and \ref
 * INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartNoActFast
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR start for which there is no activation event. This is not
 * compatible with multiple activation. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartNoActFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR start for which there is no activation event. This is not
 * compatible with multiple activation. See \ref PC and \ref
 * INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartNoActNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR start for which there is no activation event. This is not
 * compatible with multiple activation. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartNoActNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR start for which there is no activation event. This is not
 * compatible with multiple activation. See \ref PC and \ref
 * INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartNoActNoSuspTime
 * \ingroup T1_scope_trace_interfaces
 * \brief Only provided for GLIWA T1 integration optimization.
 * \param[in] time_   nominal time of task/ISR start
 * \param[in] taskId_ T1.scope task ID of starting task
 *
 * \def T1_TraceStartNoActNoSuspTimePC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] time_   nominal time of task/ISR start
 * \param[in] taskId_ T1.scope task ID of starting task
 * @}
 *
 * \name T1_TraceStartAct
 * @{
 *
 * \def T1_TraceStartAct
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR start for which there is no activation event but the
 * activation time is somehow discoverable. This is not compatible with multiple
 * activation. The most common example is a timer ISR where the activation time can be
 * derived from the old compare value.
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_    T1.scope task ID of starting task
 * \param[in] actCoreId_ the T1 logical ID of the activating core
 * \param[in] actTime_   activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStartActPC
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR start for which there is no activation event but the
 * activation time is somehow discoverable. This is not compatible with multiple
 * activation. The most common example is a timer ISR where the activation time can be
 * derived from the old compare value.
 * See \ref PC and \ref INTRPT.
 * \param[in] coreId_    the T1 logical ID of the calling core
 * \param[in] taskId_    T1.scope task ID of starting task
 * \param[in] actCoreId_ the T1 logical ID of the activating core
 * \param[in] actTime_   activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStartActFast
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR start for which there is no activation event but the
 * activation time is somehow discoverable. This is not compatible with multiple
 * activation. The most common example is a timer ISR where the activation time can be
 * derived from the old compare value.
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_    T1.scope task ID of starting task
 * \param[in] actCoreId_ the T1 logical ID of the activating core
 * \param[in] actTime_   activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStartActFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR start for which there is no activation event but the
 * activation time is somehow discoverable. This is not compatible with multiple
 * activation. The most common example is a timer ISR where the activation time can be
 * derived from the old compare value.
 * See \ref PC and \ref INTRPT.
 * \param[in] coreId_    the T1 logical ID of the calling core
 * \param[in] taskId_    T1.scope task ID of starting task
 * \param[in] actCoreId_ the T1 logical ID of the activating core
 * \param[in] actTime_   activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStartActNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR start for which there is no activation event but the
 * activation time is somehow discoverable. This is not compatible with multiple
 * activation. The most common example is a timer ISR where the activation time can be
 * derived from the old compare value.
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_    T1.scope task ID of starting task
 * \param[in] actCoreId_ the T1 logical ID of the activating core
 * \param[in] actTime_   activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStartActNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR start for which there is no activation event but the
 * activation time is somehow discoverable. This is not compatible with multiple
 * activation. The most common example is a timer ISR where the activation time can be
 * derived from the old compare value.
 * See \ref PC and \ref INTRPT.
 * \param[in] coreId_    the T1 logical ID of the calling core
 * \param[in] taskId_    T1.scope task ID of starting task
 * \param[in] actCoreId_ the T1 logical ID of the activating core
 * \param[in] actTime_   activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStartActNoSuspTime
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] time_      nominal time of task/ISR start
 * \param[in] taskId_    T1.scope task ID of starting task
 * \param[in] actCoreId_ the T1 logical ID of the activating core
 * \param[in] actTime_   activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStartActNoSuspTimePC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] coreId_    the T1 logical ID of the calling core
 * \param[in] time_      nominal time of task/ISR start
 * \param[in] taskId_    T1.scope task ID of starting task
 * \param[in] actCoreId_ the T1 logical ID of the activating core
 * \param[in] actTime_   activation time of starting task in sync timer ticks
 *
 * @}
 *
 * \name T1_TraceStop
 * @{
 *
 * \def T1_TraceStop
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at task/ISR stop. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of stopping task
 *
 * \def T1_TraceStopPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task/ISR stop. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of stopping task
 *
 * \def T1_TraceStopFast
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task/ISR stop. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of stopping task
 *
 * \def T1_TraceStopFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task/ISR stop. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of stopping task
 *
 * \def T1_TraceStopNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task/ISR stop. See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of stopping task
 *
 * \def T1_TraceStopNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at task/ISR stop. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of stopping task
 *
 * \def T1_TraceStopNoSuspTime
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] time_   nominal time of task/ISR start
 * \param[in] taskId_ T1.scope task ID of stopping task
 *
 * \def T1_TraceStopNoSuspTimePC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] time_   nominal time of task/ISR start
 * \param[in] taskId_ T1.scope task ID of stopping task
 *
 * @}
 *
 * \name T1_TraceStopStart
 * @{
 *
 * \def T1_TraceStopStart
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at the context switch from a stopping task to a newly activated
 * starting task. It is important to use this in preference to having two separate
 * events, where possible.
 * See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 *
 * \def T1_TraceStopStartPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at the context switch from a stopping task to a newly activated
 * starting task. It is important to use this in preference to having two separate
 * events, where possible.
 * See \ref PC and \ref INTRPT.
 * \param[in] coreId_     the T1 logical ID of the calling core
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 *
 * \def T1_TraceStopStartFast
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at the context switch from a stopping task to a newly activated
 * starting task. It is important to use this in preference to having two separate
 * events, where possible.
 * See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 *
 * \def T1_TraceStopStartFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at the context switch from a stopping task to a newly activated
 * starting task. It is important to use this in preference to having two separate
 * events, where possible.
 * See \ref PC and \ref INTRPT.
 * \param[in] coreId_     the T1 logical ID of the calling core
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 *
 * \def T1_TraceStopStartNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at the context switch from a stopping task to a newly activated
 * starting task. It is important to use this in preference to having two separate
 * events, where possible.
 * See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 *
 * \def T1_TraceStopStartNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at the context switch from a stopping task to a newly activated
 * starting task. It is important to use this in preference to having two separate
 * events, where possible.
 * See \ref PC and \ref INTRPT.
 * \param[in] coreId_     the T1 logical ID of the calling core
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 *
 * \def T1_TraceStopStartNoSuspTime
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] time_       nominal time of task/ISR start
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 *
 * \def T1_TraceStopStartNoSuspTimePC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] coreId_     the T1 logical ID of the calling core
 * \param[in] time_       nominal time of task/ISR start
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task
 *
 * @}
 *
 * \name T1_TraceStopStartNoAct
 * @{
 *
 * \def T1_TraceStopStartNoAct
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at the context switch from a stopping task to a newly starting task for
 * which there is no activation event. This is not compatible with multiple
 * activation. It is important to use this in preference to having two separate
 * events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 *
 * \def T1_TraceStopStartNoActPC
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at the context switch from a stopping task to a newly starting task for
 * which there is no activation event. This is not compatible with multiple
 * activation. It is important to use this in preference to having two separate
 * events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 *
 * \def T1_TraceStopStartNoActFast
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at the context switch from a stopping task to a newly starting task for
 * which there is no activation event. This is not compatible with multiple
 * activation. It is important to use this in preference to having two separate
 * events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 *
 * \def T1_TraceStopStartNoActFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at the context switch from a stopping task to a newly starting task for
 * which there is no activation event. This is not compatible with multiple
 * activation. It is important to use this in preference to having two separate
 * events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 *
 * \def T1_TraceStopStartNoActNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at the context switch from a stopping task to a newly starting task for
 * which there is no activation event. This is not compatible with multiple
 * activation. It is important to use this in preference to having two separate
 * events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 *
 * \def T1_TraceStopStartNoActNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at the context switch from a stopping task to a newly starting task for
 * which there is no activation event. This is not compatible with multiple
 * activation. It is important to use this in preference to having two separate
 * events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 *
 * \def T1_TraceStopStartNoActNoSuspTime
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] time_       nominal time of task/ISR start
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 *
 * \def T1_TraceStopStartNoActNoSuspTimePC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] time_       nominal time of task/ISR start
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 *
 * @}
 *
 * \name T1_TraceStopStartAct
 * @{
 *
 * \def T1_TraceStopStartAct
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at the context switch from a stopping task to a newly starting task/ISR
 * for which there is no activation event but the activation time is somehow
 * discoverable. This is not compatible with multiple activation.
 * The most common example is a timer ISR that is already pending on exit and will
 * re-start immediately and where the activation time can be derived from the old
 * compare value. It is important to use this in preference to having two separate
 * events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \param[in] actCoreId_  the T1 logical ID of the activating core
 * \param[in] actTime_    activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStopStartActPC
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at the context switch from a stopping task to a newly starting task/ISR
 * for which there is no activation event but the activation time is somehow
 * discoverable. This is not compatible with multiple activation.
 * The most common example is a timer ISR that is already pending on exit and will
 * re-start immediately and where the activation time can be derived from the old
 * compare value. It is important to use this in preference to having two separate
 * events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \param[in] actCoreId_  the T1 logical ID of the activating core
 * \param[in] actTime_    activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStopStartActFast
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at the context switch from a stopping task to a newly starting task/ISR
 * for which there is no activation event but the activation time is somehow
 * discoverable. This is not compatible with multiple activation.
 * The most common example is a timer ISR that is already pending on exit and will
 * re-start immediately and where the activation time can be derived from the old
 * compare value. It is important to use this in preference to having two separate
 * events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \param[in] actCoreId_  the T1 logical ID of the activating core
 * \param[in] actTime_    activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStopStartActFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at the context switch from a stopping task to a newly starting task/ISR
 * for which there is no activation event but the activation time is somehow
 * discoverable. This is not compatible with multiple activation.
 * The most common example is a timer ISR that is already pending on exit and will
 * re-start immediately and where the activation time can be derived from the old
 * compare value. It is important to use this in preference to having two separate
 * events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] coreId_     the T1 logical ID of the calling core
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \param[in] actCoreId_  the T1 logical ID of the activating core
 * \param[in] actTime_    activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStopStartActNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at the context switch from a stopping task to a newly starting task/ISR
 * for which there is no activation event but the activation time is somehow
 * discoverable. This is not compatible with multiple activation.
 * The most common example is a timer ISR that is already pending on exit and will
 * re-start immediately and where the activation time can be derived from the old
 * compare value. It is important to use this in preference to having two separate
 * events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \param[in] actCoreId_  the T1 logical ID of the activating core
 * \param[in] actTime_    activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStopStartActNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at the context switch from a stopping task to a newly starting task/ISR
 * for which there is no activation event but the activation time is somehow
 * discoverable. This is not compatible with multiple activation.
 * The most common example is a timer ISR that is already pending on exit and will
 * re-start immediately and where the activation time can be derived from the old
 * compare value. It is important to use this in preference to having two separate
 * events, where possible. See \ref PC and \ref INTRPT.
 * \param[in] coreId_     the T1 logical ID of the calling core
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \param[in] actCoreId_  the T1 logical ID of the activating core
 * \param[in] actTime_    activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStopStartActNoSuspTime
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] time_       nominal time of task/ISR start
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \param[in] actCoreId_  the T1 logical ID of the activating core
 * \param[in] actTime_    activation time of starting task in sync timer ticks
 *
 * \def T1_TraceStopStartActNoSuspTimePC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] coreId_     the T1 logical ID of the calling core
 * \param[in] time_       nominal time of task/ISR start
 * \param[in] stopTaskId_ T1.scope task ID of stopping task
 *                        (this parameter is only for backwards compatibility, the
 *                         value is ignored)
 * \param[in] taskId_     T1.scope task ID of starting task/ISR
 * \param[in] actCoreId_  the T1 logical ID of the activating core
 * \param[in] actTime_    activation time of starting task in sync timer ticks
 *
 * @}
 *
 * \name T1_TraceStartNoActStop
 * @{
 *
 * \def T1_TraceStartNoActStop
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at ISR too short for T1_TraceStart() then T1_TraceStop(). See also
 * T1_ContStartStopCETPC(). See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of short ISR
 *
 * \def T1_TraceStartNoActStopPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at ISR too short for T1_TraceStart() then T1_TraceStop(). See also
 * T1_ContStartStopCETPC(). See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of short ISR
 *
 * \def T1_TraceStartNoActStopFast
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at ISR too short for T1_TraceStart() then T1_TraceStop(). See also
 * T1_ContStartStopCETPC(). See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of short ISR
 *
 * \def T1_TraceStartNoActStopFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at ISR too short for T1_TraceStart() then T1_TraceStop(). See also
 * T1_ContStartStopCETPC(). See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of short ISR
 *
 * \def T1_TraceStartNoActStopNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at ISR too short for T1_TraceStart() then T1_TraceStop(). See also
 * T1_ContStartStopCETPC(). See \ref PC and \ref INTRPT.
 * \param[in] taskId_ T1.scope task ID of short ISR
 *
 * \def T1_TraceStartNoActStopNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at ISR too short for T1_TraceStart() then T1_TraceStop(). See also
 * T1_ContStartStopCETPC(). See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_ T1.scope task ID of short ISR
 *
 * \def T1_TraceStartNoActStopNoSuspTime
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] time_   nominal time of task/ISR start
 * \param[in] taskId_ T1.scope task ID of short ISR
 *
 * \def T1_TraceStartNoActStopNoSuspTimePC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Only provided for GLIWA T1 integration optimization.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] time_   nominal time of task/ISR start
 * \param[in] taskId_ T1.scope task ID of short ISR
 *
 * @}
 *
 * \name T1_TraceRelease
 * @{
 *
 * \def T1_TraceRelease
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call when a WAITING task becomes READY, in SetEvent.
 *          See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of released task
 *
 * \def T1_TraceReleasePC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call when a WAITING task becomes READY, in SetEvent.
 *          See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_     T1.scope task ID of released task
 *
 * \def T1_TraceReleaseFast
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call when a WAITING task becomes READY, in SetEvent.
 *          See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of released task
 *
 * \def T1_TraceReleaseFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call when a WAITING task becomes READY, in SetEvent.
 *          See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_     T1.scope task ID of released task
 *
 * \def T1_TraceReleaseNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call when a WAITING task becomes READY, in SetEvent.
 *          See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of released task
 *
 * \def T1_TraceReleaseNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call when a WAITING task becomes READY, in SetEvent.
 *          See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_     T1.scope task ID of released task
 *
 * @}
 *
 * \name T1_TraceWait
 * @{
 *
 * \def T1_TraceWait
 * \ingroup T1_scope_trace_interfaces
 * \brief Call when a RUNNING task becomes WAITING, on entry to WaitEvent.
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 *
 * \def T1_TraceWaitPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call when a RUNNING task becomes WAITING, on entry to WaitEvent.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 *
 * \def T1_TraceWaitFast
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call when a RUNNING task becomes WAITING, on entry to WaitEvent.
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 *
 * \def T1_TraceWaitFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call when a RUNNING task becomes WAITING, on entry to WaitEvent.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 *
 * \def T1_TraceWaitNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call when a RUNNING task becomes WAITING, on entry to WaitEvent.
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 *
 * \def T1_TraceWaitNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call when a RUNNING task becomes WAITING, on entry to WaitEvent.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 *
 * @}
 *
 * \name T1_TraceResume
 * @{
 *
 * \def T1_TraceResume
 * \ingroup T1_scope_trace_interfaces
 * \brief Call on exit from WaitEvent. See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 *
 * \def T1_TraceResumePC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call on exit from WaitEvent. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_     T1.scope task ID of waiting task
 *
 * \def T1_TraceResumeFast
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call on exit from WaitEvent. See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 *
 * \def T1_TraceResumeFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call on exit from WaitEvent. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_     T1.scope task ID of waiting task
 *
 * \def T1_TraceResumeNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call on exit from WaitEvent. See \ref PC and \ref INTRPT.
 * \param[in] taskId_     T1.scope task ID of waiting task
 *
 * \def T1_TraceResumeNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call on exit from WaitEvent. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] taskId_     T1.scope task ID of waiting task
 *
 * @}
 *
 * \name T1_TraceEvent
 * @{
 *
 * \def T1_TraceEvent
 * \ingroup T1_scope_trace_interfaces
 * \brief Call at a user event or user stopwatch event. See \ref PC and \ref INTRPT.
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 *
 * \def T1_TraceEventPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at a user event or user stopwatch event. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 *
 * \def T1_TraceEventFast
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at a user event or user stopwatch event. See \ref PC and \ref INTRPT.
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 *
 * \def T1_TraceEventFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at a user event or user stopwatch event. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 *
 * \def T1_TraceEventNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at a user event or user stopwatch event. See \ref PC and \ref INTRPT.
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 *
 * \def T1_TraceEventNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call at a user event or user stopwatch event. See \ref PC and \ref INTRPT.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] event_ #T1_STOPWATCH_START/#T1_STOPWATCH_STOP or configured
 *                   user event ID
 * \param[in] info_  T1.scope stopwatch ID or user event 10-bit info field
 *
 * @}
 *
 * \name T1_TraceUint32
 * @{
 *
 * \def T1_TraceUint32
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] ui32_ 32-bit unsigned integer
 *
 * \def T1_TraceUint32PC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] ui32_ 32-bit unsigned integer
 *
 * \def T1_TraceUint32Fast
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] ui32_ 32-bit unsigned integer
 *
 * \def T1_TraceUint32FastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] ui32_ 32-bit unsigned integer
 *
 * \def T1_TraceUint32NoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] ui32_ 32-bit unsigned integer
 *
 * \def T1_TraceUint32NoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] ui32_ 32-bit unsigned integer
 *
 * @}
 *
 * \name T1_TraceUint16
 * @{
 *
 * \def T1_TraceUint16
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 16-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] ui16_ 16-bit unsigned integer
 *
 * \def T1_TraceUint16PC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 16-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] ui16_ 16-bit unsigned integer
 *
 * \def T1_TraceUint16Fast
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 16-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] ui16_ 16-bit unsigned integer
 *
 * \def T1_TraceUint16FastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 16-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] ui16_ 16-bit unsigned integer
 *
 * \def T1_TraceUint16NoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 16-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] ui16_ 16-bit unsigned integer
 *
 * \def T1_TraceUint16NoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 16-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] ui16_ 16-bit unsigned integer
 *
 * @}
 *
 * \name T1_TraceSint32
 * @{
 *
 * \def T1_TraceSint32
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] si32_ 32-bit signed integer
 *
 * \def T1_TraceSint32PC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] si32_ 32-bit signed integer
 *
 * \def T1_TraceSint32Fast
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] si32_ 32-bit signed integer
 *
 * \def T1_TraceSint32FastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] si32_ 32-bit signed integer
 *
 * \def T1_TraceSint32NoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] si32_ 32-bit signed integer
 *
 * \def T1_TraceSint32NoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] si32_ 32-bit signed integer
 *
 * @}
 *
 * \name T1_TraceSint16
 * @{
 *
 * \def T1_TraceSint16
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 16-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] si16_ 16-bit signed integer
 *
 * \def T1_TraceSint16PC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 16-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] si16_ 16-bit signed integer
 *
 * \def T1_TraceSint16Fast
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 16-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] si16_ 16-bit signed integer
 *
 * \def T1_TraceSint16FastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 16-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] si16_ 16-bit signed integer
 *
 * \def T1_TraceSint16NoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 16-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] si16_ 16-bit signed integer
 *
 * \def T1_TraceSint16NoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 16-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] si16_ 16-bit signed integer
 *
 * @}
 *
 * \name T1_TraceUint64
 * @{
 *
 * \def T1_TraceUint64
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 64-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] ui64_ 64-bit unsigned integer
 *
 * \def T1_TraceUint64PC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 64-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] ui64_ 64-bit unsigned integer
 *
 * \def T1_TraceUint64Fast
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 64-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] ui64_ 64-bit unsigned integer
 *
 * \def T1_TraceUint64FastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 64-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] ui64_ 64-bit unsigned integer
 *
 * \def T1_TraceUint64NoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 64-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] ui64_ 64-bit unsigned integer
 *
 * \def T1_TraceUint64NoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 64-bit unsigned integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] ui64_ 64-bit unsigned integer
 *
 * @}
 *
 * \name T1_TraceSint64
 * @{
 *
 * \def T1_TraceSint64
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 64-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] si64_ 64-bit signed integer
 *
 * \def T1_TraceSint64PC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 64-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] si64_ 64-bit signed integer
 *
 * \def T1_TraceSint64Fast
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 64-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] si64_ 64-bit signed integer
 *
 * \def T1_TraceSint64FastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 64-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] si64_ 64-bit signed integer
 *
 * \def T1_TraceSint64NoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 64-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] si64_ 64-bit signed integer
 *
 * \def T1_TraceSint64NoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 64-bit signed integer.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] si64_ 64-bit signed integer
 *
 * @}
 *
 * \name T1_TraceAddr
 * @{
 *
 * \def T1_TraceAddr
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit address.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] addr_ 32-bit address
 *
 * \def T1_TraceAddrPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit address.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] addr_ 32-bit address
 *
 * \def T1_TraceAddrFast
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit address.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] addr_ 32-bit address
 *
 * \def T1_TraceAddrFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit address.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] addr_ 32-bit address
 *
 * \def T1_TraceAddrNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit address.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] addr_ 32-bit address
 *
 * \def T1_TraceAddrNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with 32-bit address.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] addr_ 32-bit address
 *
 * @}
 *
 * \name T1_TraceFloat
 * @{
 *
 * \def T1_TraceFloat
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with IEEE 754 32-bit float.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] float_ IEEE 754 32-bit float
 *
 * \def T1_TraceFloatPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with IEEE 754 32-bit float.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] float_ IEEE 754 32-bit float
 *
 * \def T1_TraceFloatFast
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with IEEE 754 32-bit float.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] float_ IEEE 754 32-bit float
 *
 * \def T1_TraceFloatFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with IEEE 754 32-bit float.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] float_ IEEE 754 32-bit float
 *
 * \def T1_TraceFloatNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with IEEE 754 32-bit float.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] float_ IEEE 754 32-bit float
 *
 * \def T1_TraceFloatNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with IEEE 754 32-bit float.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] float_ IEEE 754 32-bit float
 *
 * @}
 *
 * \name T1_TraceString
 * @{
 *
 * \def T1_TraceString
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with address and length of string data.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] pData_ address of string
 * \param[in] len_ length of string (max 255 bytes)
 *
 * \def T1_TraceStringPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with address and length of string data.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] pData_ address of string
 * \param[in] len_ length of string (max 255 bytes)
 *
 * \def T1_TraceStringFast
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with address and length of string data.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] pData_ address of string
 * \param[in] len_ length of string (max 255 bytes)
 *
 * \def T1_TraceStringFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with address and length of string data.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] pData_ address of string
 * \param[in] len_ length of string (max 255 bytes)
 *
 * \def T1_TraceStringNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with address and length of string data.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] id_ configured user data event ID
 * \param[in] pData_ address of string
 * \param[in] len_ length of string (max 255 bytes)
 *
 * \def T1_TraceStringNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with address and length of string data.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS.
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] pData_ address of string
 * \param[in] len_ length of string (max 255 bytes)
 *
 * @}
 *
 * \name T1_TraceBinary
 * @{
 *
 * \def     T1_TraceBinary( id_, pData_, len_ )
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with a struct or array.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS
 * \param[in] id_ configured user data event ID
 * \param[in] pData_ address of struct or array
 * \param[in] len_ length of struct/array
 *
 * \def     T1_TraceBinaryFast( id_, pData_, len_ )
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with a struct or array.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS
 * \param[in] id_ configured user data event ID
 * \param[in] pData_ address of struct or array
 * \param[in] len_ length of struct/array
 *
 * \def     T1_TraceBinaryNoSusp( id_, pData_, len_ )
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with a struct or array.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS
 * \param[in] id_ configured user data event ID
 * \param[in] pData_ address of struct or array
 * \param[in] len_ length of struct/array
 *
 * \def     T1_TraceBinaryPC( coreId_, id_, pData_, len_ )
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with a struct or array.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] pData_ address of struct or array
 * \param[in] len_ length of struct/array
 *
 * \def     T1_TraceBinaryFastPC( coreId_, id_, pData_, len_ )
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with a struct or array.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] pData_ address of struct or array
 * \param[in] len_ length of struct/array
 *
 * \def     T1_TraceBinaryNoSuspPC( coreId_, id_, pData_, len_ )
 * \ingroup T1_scope_trace_interfaces
 * \brief   Call at user data event with a struct or array.
 *          See \ref PC, \ref INTRPT and \ref USER_DATA_EVENTS
 * \param[in] coreId_ the T1 logical ID of the calling core
 * \param[in] id_ configured user data event ID
 * \param[in] pData_ address of struct or array
 * \param[in] len_ length of struct/array
 *
 * @}
 *
 * \name T1_TraceSyncTimer
 * @{
 *
 * \def T1_TraceSyncTimer
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call to create an additional sync event. See \ref PC, \ref INTRPT.
 *         This is usually unnecessary but facilitates synchronization of multi-core
 *         traces from "post mortem" debugger trace download, for example.
 *
 * \def T1_TraceSyncTimerPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call to create an additional sync event. See \ref PC, \ref INTRPT.
 *         This is usually unnecessary but facilitates synchronization of multi-core
 *         traces from "post mortem" debugger trace download, for example.
 * \param[in] coreId_ the T1 logical ID of the calling core
 *
 * \def T1_TraceSyncTimerFast
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call to create an additional sync event. See \ref PC, \ref INTRPT.
 *         This is usually unnecessary but facilitates synchronization of multi-core
 *         traces from "post mortem" debugger trace download, for example.
 *
 * \def T1_TraceSyncTimerFastPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call to create an additional sync event. See \ref PC, \ref INTRPT.
 *         This is usually unnecessary but facilitates synchronization of multi-core
 *         traces from "post mortem" debugger trace download, for example.
 * \param[in] coreId_ the T1 logical ID of the calling core
 *
 * \def T1_TraceSyncTimerNoSusp
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call to create an additional sync event. See \ref PC, \ref INTRPT.
 *         This is usually unnecessary but facilitates synchronization of multi-core
 *         traces from "post mortem" debugger trace download, for example.
 *
 * \def T1_TraceSyncTimerNoSuspPC
 * \ingroup T1_scope_trace_interfaces
 * \brief  Call to create an additional sync event. See \ref PC, \ref INTRPT.
 *         This is usually unnecessary but facilitates synchronization of multi-core
 *         traces from "post mortem" debugger trace download, for example.
 * \param[in] coreId_ the T1 logical ID of the calling core
 *
 * @}
 */

/* clang-format off */
/* BEGIN generated variant macros */
#   if 1 == T1_NOF_CORES
#       define T1_TraceActivation( taskId_ )                                \
        T1_TRACE_ACT_PC( , 0, (taskId_) )
#       define T1_TraceActivationPC( coreId_, taskId_ )                     \
        T1_TRACE_ACT_PC( , 0, (taskId_) )
#       define T1_TraceActivationFast( taskId_ )                            \
        T1_TRACE_ACT_PC( _FAST, 0, (taskId_) )
#       define T1_TraceActivationFastPC( coreId_, taskId_ )                 \
        T1_TRACE_ACT_PC( _FAST, 0, (taskId_) )
#       define T1_TraceActivationNoSusp( taskId_ )                          \
        T1_TRACE_ACT_PC( _NOSUSP, 0, (taskId_) )
#       define T1_TraceActivationNoSuspPC( coreId_, taskId_ )               \
        T1_TRACE_ACT_PC( _NOSUSP, 0, (taskId_) )
#       define T1_TraceEvent( event_, info_ )                               \
        T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#       define T1_TraceEventPC( coreId_, event_, info_ )                    \
        T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#       define T1_TraceEventFast( event_, info_ )                           \
        T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#       define T1_TraceEventFastPC( coreId_, event_, info_ )                \
        T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#       define T1_TraceEventNoSusp( event_, info_ )                         \
        T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#       define T1_TraceEventNoSuspPC( coreId_, event_, info_ )              \
        T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#       define T1_TraceEventNoSuspTime( time_, event_, info_ )              \
        T1_TRACE_ATOMIC__( _NOSUSPTIME, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ), (time_) )
#       define T1_TraceEventNoSuspTimePC( coreId_, time_, event_, info_ )   \
        T1_TRACE_ATOMIC__( _NOSUSPTIME, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( (event_), (info_) ), (time_) )
#       define T1_TraceRelease( taskId_ )                                   \
        T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#       define T1_TraceReleasePC( coreId_, taskId_ )                        \
        T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#       define T1_TraceReleaseFast( taskId_ )                               \
        T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#       define T1_TraceReleaseFastPC( coreId_, taskId_ )                    \
        T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#       define T1_TraceReleaseNoSusp( taskId_ )                             \
        T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#       define T1_TraceReleaseNoSuspPC( coreId_, taskId_ )                  \
        T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#       define T1_TraceResume( taskId_ )                                    \
        T1_INCR_PREEMPTIONS_PC( 0, T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#       define T1_TraceResumePC( coreId_, taskId_ )                         \
        T1_INCR_PREEMPTIONS_PC( 0, T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#       define T1_TraceResumeFast( taskId_ )                                \
        T1_INCR_PREEMPTIONS_PC( 0, T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#       define T1_TraceResumeFastPC( coreId_, taskId_ )                     \
        T1_INCR_PREEMPTIONS_PC( 0, T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#       define T1_TraceResumeNoSusp( taskId_ )                              \
        T1_INCR_PREEMPTIONS_PC( 0, T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#       define T1_TraceResumeNoSuspPC( coreId_, taskId_ )                   \
        T1_INCR_PREEMPTIONS_PC( 0, T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#       define T1_TraceStart( taskId_ )                                     \
        T1_TRACE_START_PC( , 0, (taskId_) )
#       define T1_TraceStartPC( coreId_, taskId_ )                          \
        T1_TRACE_START_PC( , 0, (taskId_) )
#       define T1_TraceStartFast( taskId_ )                                 \
        T1_TRACE_START_PC( _FAST, 0, (taskId_) )
#       define T1_TraceStartFastPC( coreId_, taskId_ )                      \
        T1_TRACE_START_PC( _FAST, 0, (taskId_) )
#       define T1_TraceStartNoSusp( taskId_ )                               \
        T1_TRACE_START_PC( _NOSUSP, 0, (taskId_) )
#       define T1_TraceStartNoSuspPC( coreId_, taskId_ )                    \
        T1_TRACE_START_PC( _NOSUSP, 0, (taskId_) )
#       define T1_TraceStartNoSuspTime( time_, taskId_ )                    \
        T1_TRACE_START_PC_( _NOSUSPTIME, 0, (taskId_), (time_) )
#       define T1_TraceStartNoSuspTimePC( coreId_, time_, taskId_ )         \
        T1_TRACE_START_PC_( _NOSUSPTIME, 0, (taskId_), (time_) )
#       define T1_TraceStartAct( taskId_, actCoreId_, actTime_ )            \
        T1_TRACE_START_ACT_PC( , 0, (taskId_), 0, (actTime_) )
#       define T1_TraceStartActPC( coreId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_START_ACT_PC( , 0, (taskId_), 0, (actTime_) )
#       define T1_TraceStartActFast( taskId_, actCoreId_, actTime_ )        \
        T1_TRACE_START_ACT_PC( _FAST, 0, (taskId_), 0, (actTime_) )
#       define T1_TraceStartActFastPC( coreId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_START_ACT_PC( _FAST, 0, (taskId_), 0, (actTime_) )
#       define T1_TraceStartActNoSusp( taskId_, actCoreId_, actTime_ )      \
        T1_TRACE_START_ACT_PC( _NOSUSP, 0, (taskId_), 0, (actTime_) )
#       define T1_TraceStartActNoSuspPC( coreId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_START_ACT_PC( _NOSUSP, 0, (taskId_), 0, (actTime_) )
#       define T1_TraceStartActNoSuspTime( time_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_START_ACT_PC_( _NOSUSPTIME, 0, (taskId_), 0, (actTime_), (time_) )
#       define T1_TraceStartActNoSuspTimePC( coreId_, time_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_START_ACT_PC_( _NOSUSPTIME, 0, (taskId_), 0, (actTime_), (time_) )
#       define T1_TraceStartNoAct( taskId_ )                                \
        T1_TRACE_START_NOACT_PC( , 0, (taskId_) )
#       define T1_TraceStartNoActPC( coreId_, taskId_ )                     \
        T1_TRACE_START_NOACT_PC( , 0, (taskId_) )
#       define T1_TraceStartNoActFast( taskId_ )                            \
        T1_TRACE_START_NOACT_PC( _FAST, 0, (taskId_) )
#       define T1_TraceStartNoActFastPC( coreId_, taskId_ )                 \
        T1_TRACE_START_NOACT_PC( _FAST, 0, (taskId_) )
#       define T1_TraceStartNoActNoSusp( taskId_ )                          \
        T1_TRACE_START_NOACT_PC( _NOSUSP, 0, (taskId_) )
#       define T1_TraceStartNoActNoSuspPC( coreId_, taskId_ )               \
        T1_TRACE_START_NOACT_PC( _NOSUSP, 0, (taskId_) )
#       define T1_TraceStartNoActNoSuspTime( time_, taskId_ )               \
        T1_TRACE_START_NOACT_PC_( _NOSUSPTIME, 0, (taskId_), (time_) )
#       define T1_TraceStartNoActNoSuspTimePC( coreId_, time_, taskId_ )    \
        T1_TRACE_START_NOACT_PC_( _NOSUSPTIME, 0, (taskId_), (time_) )
#       define T1_TraceStartNoActStop( taskId_ )                            \
        T1_TRACE_START_STOP_PC( , 0, (taskId_) )
#       define T1_TraceStartNoActStopPC( coreId_, taskId_ )                 \
        T1_TRACE_START_STOP_PC( , 0, (taskId_) )
#       define T1_TraceStartNoActStopFast( taskId_ )                        \
        T1_TRACE_START_STOP_PC( _FAST, 0, (taskId_) )
#       define T1_TraceStartNoActStopFastPC( coreId_, taskId_ )             \
        T1_TRACE_START_STOP_PC( _FAST, 0, (taskId_) )
#       define T1_TraceStartNoActStopNoSusp( taskId_ )                      \
        T1_TRACE_START_STOP_PC( _NOSUSP, 0, (taskId_) )
#       define T1_TraceStartNoActStopNoSuspPC( coreId_, taskId_ )           \
        T1_TRACE_START_STOP_PC( _NOSUSP, 0, (taskId_) )
#       define T1_TraceStartNoActStopNoSuspTime( time_, taskId_ )           \
        T1_TRACE_START_STOP_PC_( _NOSUSPTIME, 0, (taskId_), (time_) )
#       define T1_TraceStartNoActStopNoSuspTimePC( coreId_, time_, taskId_ ) \
        T1_TRACE_START_STOP_PC_( _NOSUSPTIME, 0, (taskId_), (time_) )
#       define T1_TraceStop( taskId_ )                                      \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_STOP_PC( , 0, (taskId_) ) )
#       define T1_TraceStopPC( coreId_, taskId_ )                           \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_STOP_PC( , 0, (taskId_) ) )
#       define T1_TraceStopFast( taskId_ )                                  \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_STOP_PC( _FAST, 0, (taskId_) ) )
#       define T1_TraceStopFastPC( coreId_, taskId_ )                       \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_STOP_PC( _FAST, 0, (taskId_) ) )
#       define T1_TraceStopNoSusp( taskId_ )                                \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_STOP_PC( _NOSUSP, 0, (taskId_) ) )
#       define T1_TraceStopNoSuspPC( coreId_, taskId_ )                     \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_STOP_PC( _NOSUSP, 0, (taskId_) ) )
#       define T1_TraceStopNoSuspTime( time_, taskId_ )                     \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_STOP_PC_( _NOSUSPTIME, 0, (taskId_), (time_) ) )
#       define T1_TraceStopNoSuspTimePC( coreId_, time_, taskId_ )          \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_STOP_PC_( _NOSUSPTIME, 0, (taskId_), (time_) ) )
#       define T1_TraceStopStart( stopTaskId_, taskId_ )                    \
        T1_TRACE_STOP_START_PC( , 0, (taskId_) )
#       define T1_TraceStopStartPC( coreId_, stopTaskId_, taskId_ )         \
        T1_TRACE_STOP_START_PC( , 0, (taskId_) )
#       define T1_TraceStopStartFast( stopTaskId_, taskId_ )                \
        T1_TRACE_STOP_START_PC( _FAST, 0, (taskId_) )
#       define T1_TraceStopStartFastPC( coreId_, stopTaskId_, taskId_ )     \
        T1_TRACE_STOP_START_PC( _FAST, 0, (taskId_) )
#       define T1_TraceStopStartNoSusp( stopTaskId_, taskId_ )              \
        T1_TRACE_STOP_START_PC( _NOSUSP, 0, (taskId_) )
#       define T1_TraceStopStartNoSuspPC( coreId_, stopTaskId_, taskId_ )   \
        T1_TRACE_STOP_START_PC( _NOSUSP, 0, (taskId_) )
#       define T1_TraceStopStartNoSuspTime( time_, stopTaskId_, taskId_ )   \
        T1_TRACE_STOP_START_PC_( _NOSUSPTIME, 0, (taskId_), (time_) )
#       define T1_TraceStopStartNoSuspTimePC( coreId_, time_, stopTaskId_, taskId_ ) \
        T1_TRACE_STOP_START_PC_( _NOSUSPTIME, 0, (taskId_), (time_) )
#       define T1_TraceStopStartAct( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC( , 0, (taskId_), 0, (actTime_) )
#       define T1_TraceStopStartActPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC( , 0, (taskId_), 0, (actTime_) )
#       define T1_TraceStopStartActFast( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC( _FAST, 0, (taskId_), 0, (actTime_) )
#       define T1_TraceStopStartActFastPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC( _FAST, 0, (taskId_), 0, (actTime_) )
#       define T1_TraceStopStartActNoSusp( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC( _NOSUSP, 0, (taskId_), 0, (actTime_) )
#       define T1_TraceStopStartActNoSuspPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC( _NOSUSP, 0, (taskId_), 0, (actTime_) )
#       define T1_TraceStopStartActNoSuspTime( time_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC_( _NOSUSPTIME, 0, (taskId_), 0, (actTime_), (time_) )
#       define T1_TraceStopStartActNoSuspTimePC( coreId_, time_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC_( _NOSUSPTIME, 0, (taskId_), 0, (actTime_), (time_) )
#       define T1_TraceStopStartNoAct( stopTaskId_, taskId_ )               \
        T1_TRACE_STOP_START_NOACT_PC( , 0, (taskId_) )
#       define T1_TraceStopStartNoActPC( coreId_, stopTaskId_, taskId_ )    \
        T1_TRACE_STOP_START_NOACT_PC( , 0, (taskId_) )
#       define T1_TraceStopStartNoActFast( stopTaskId_, taskId_ )           \
        T1_TRACE_STOP_START_NOACT_PC( _FAST, 0, (taskId_) )
#       define T1_TraceStopStartNoActFastPC( coreId_, stopTaskId_, taskId_ ) \
        T1_TRACE_STOP_START_NOACT_PC( _FAST, 0, (taskId_) )
#       define T1_TraceStopStartNoActNoSusp( stopTaskId_, taskId_ )         \
        T1_TRACE_STOP_START_NOACT_PC( _NOSUSP, 0, (taskId_) )
#       define T1_TraceStopStartNoActNoSuspPC( coreId_, stopTaskId_, taskId_ ) \
        T1_TRACE_STOP_START_NOACT_PC( _NOSUSP, 0, (taskId_) )
#       define T1_TraceStopStartNoActNoSuspTime( time_, stopTaskId_, taskId_ ) \
        T1_TRACE_STOP_START_NOACT_PC_( _NOSUSPTIME, 0, (taskId_), (time_) )
#       define T1_TraceStopStartNoActNoSuspTimePC( coreId_, time_, stopTaskId_, taskId_ ) \
        T1_TRACE_STOP_START_NOACT_PC_( _NOSUSPTIME, 0, (taskId_), (time_) )
#       define T1_TraceSyncTimer( coreId_ )                                 \
        T1_TRACE_SYNC( , T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ) )
#       define T1_TraceSyncTimerPC( coreId_ )                               \
        T1_TRACE_SYNC( , T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ) )
#       define T1_TraceSyncTimerFast( coreId_ )                             \
        T1_TRACE_SYNC( _FAST, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ) )
#       define T1_TraceSyncTimerFastPC( coreId_ )                           \
        T1_TRACE_SYNC( _FAST, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ) )
#       define T1_TraceSyncTimerNoSusp( coreId_ )                           \
        T1_TRACE_SYNC( _NOSUSP, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ) )
#       define T1_TraceSyncTimerNoSuspPC( coreId_ )                         \
        T1_TRACE_SYNC( _NOSUSP, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ) )
#       define T1_TraceWait( taskId_ )                                      \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       define T1_TraceWaitPC( coreId_, taskId_ )                           \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       define T1_TraceWaitFast( taskId_ )                                  \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       define T1_TraceWaitFastPC( coreId_, taskId_ )                       \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       define T1_TraceWaitNoSusp( taskId_ )                                \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       define T1_TraceWaitNoSuspPC( coreId_, taskId_ )                     \
        T1_DECR_PREEMPTIONS_PC( 0, T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( 0 ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#   else /* more than one core */
#       define T1_TraceActivation( taskId_ )                                \
        T1_TRACE_ACT_PC( , T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceActivationPC( coreId_, taskId_ )                     \
        T1_TRACE_ACT_PC( , (coreId_), (taskId_) )
#       define T1_TraceActivationFast( taskId_ )                            \
        T1_TRACE_ACT_PC( _FAST, T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceActivationFastPC( coreId_, taskId_ )                 \
        T1_TRACE_ACT_PC( _FAST, (coreId_), (taskId_) )
#       define T1_TraceActivationNoSusp( taskId_ )                          \
        T1_TRACE_ACT_PC( _NOSUSP, T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceActivationNoSuspPC( coreId_, taskId_ )               \
        T1_TRACE_ACT_PC( _NOSUSP, (coreId_), (taskId_) )
#       define T1_TraceEvent( event_, info_ )                               \
        T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#       define T1_TraceEventPC( coreId_, event_, info_ )                    \
        T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#       define T1_TraceEventFast( event_, info_ )                           \
        T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#       define T1_TraceEventFastPC( coreId_, event_, info_ )                \
        T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#       define T1_TraceEventNoSusp( event_, info_ )                         \
        T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#       define T1_TraceEventNoSuspPC( coreId_, event_, info_ )              \
        T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ) )
#       define T1_TraceEventNoSuspTime( time_, event_, info_ )              \
        T1_TRACE_ATOMIC__( _NOSUSPTIME, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( (event_), (info_) ), (time_) )
#       define T1_TraceEventNoSuspTimePC( coreId_, time_, event_, info_ )   \
        T1_TRACE_ATOMIC__( _NOSUSPTIME, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ), T1_COMBINE_EVENT_INFO( (event_), (info_) ), (time_) )
#       define T1_TraceRelease( taskId_ )                                   \
        T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#       define T1_TraceReleasePC( coreId_, taskId_ )                        \
        T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#       define T1_TraceReleaseFast( taskId_ )                               \
        T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#       define T1_TraceReleaseFastPC( coreId_, taskId_ )                    \
        T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#       define T1_TraceReleaseNoSusp( taskId_ )                             \
        T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#       define T1_TraceReleaseNoSuspPC( coreId_, taskId_ )                  \
        T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RELEASE, (taskId_) ) )
#       define T1_TraceResume( taskId_ )                                    \
        T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#       define T1_TraceResumePC( coreId_, taskId_ )                         \
        T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#       define T1_TraceResumeFast( taskId_ )                                \
        T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#       define T1_TraceResumeFastPC( coreId_, taskId_ )                     \
        T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#       define T1_TraceResumeNoSusp( taskId_ )                              \
        T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#       define T1_TraceResumeNoSuspPC( coreId_, taskId_ )                   \
        T1_INCR_PREEMPTIONS_PC( (coreId_), T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_RESUME, (taskId_) ) ) )
#       define T1_TraceStart( taskId_ )                                     \
        T1_TRACE_START_PC( , T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStartPC( coreId_, taskId_ )                          \
        T1_TRACE_START_PC( , (coreId_), (taskId_) )
#       define T1_TraceStartFast( taskId_ )                                 \
        T1_TRACE_START_PC( _FAST, T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStartFastPC( coreId_, taskId_ )                      \
        T1_TRACE_START_PC( _FAST, (coreId_), (taskId_) )
#       define T1_TraceStartNoSusp( taskId_ )                               \
        T1_TRACE_START_PC( _NOSUSP, T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStartNoSuspPC( coreId_, taskId_ )                    \
        T1_TRACE_START_PC( _NOSUSP, (coreId_), (taskId_) )
#       define T1_TraceStartNoSuspTime( time_, taskId_ )                    \
        T1_TRACE_START_PC_( _NOSUSPTIME, T1_GetCoreIdOffset( ), (taskId_), (time_) )
#       define T1_TraceStartNoSuspTimePC( coreId_, time_, taskId_ )         \
        T1_TRACE_START_PC_( _NOSUSPTIME, coreId_, (taskId_), (time_) )
#       define T1_TraceStartAct( taskId_, actCoreId_, actTime_ )            \
        T1_TRACE_START_ACT_PC( , T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#       define T1_TraceStartActPC( coreId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_START_ACT_PC( , (coreId_), (taskId_), (actCoreId_), (actTime_) )
#       define T1_TraceStartActFast( taskId_, actCoreId_, actTime_ )        \
        T1_TRACE_START_ACT_PC( _FAST, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#       define T1_TraceStartActFastPC( coreId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_START_ACT_PC( _FAST, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#       define T1_TraceStartActNoSusp( taskId_, actCoreId_, actTime_ )      \
        T1_TRACE_START_ACT_PC( _NOSUSP, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#       define T1_TraceStartActNoSuspPC( coreId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_START_ACT_PC( _NOSUSP, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#       define T1_TraceStartActNoSuspTime( time_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_START_ACT_PC_( _NOSUSPTIME, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_), (time_) )
#       define T1_TraceStartActNoSuspTimePC( coreId_, time_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_START_ACT_PC_( _NOSUSPTIME, coreId_, (taskId_), (actCoreId_), (actTime_), (time_) )
#       define T1_TraceStartNoAct( taskId_ )                                \
        T1_TRACE_START_NOACT_PC( , T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStartNoActPC( coreId_, taskId_ )                     \
        T1_TRACE_START_NOACT_PC( , (coreId_), (taskId_) )
#       define T1_TraceStartNoActFast( taskId_ )                            \
        T1_TRACE_START_NOACT_PC( _FAST, T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStartNoActFastPC( coreId_, taskId_ )                 \
        T1_TRACE_START_NOACT_PC( _FAST, (coreId_), (taskId_) )
#       define T1_TraceStartNoActNoSusp( taskId_ )                          \
        T1_TRACE_START_NOACT_PC( _NOSUSP, T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStartNoActNoSuspPC( coreId_, taskId_ )               \
        T1_TRACE_START_NOACT_PC( _NOSUSP, (coreId_), (taskId_) )
#       define T1_TraceStartNoActNoSuspTime( time_, taskId_ )               \
        T1_TRACE_START_NOACT_PC_( _NOSUSPTIME, T1_GetCoreIdOffset( ), (taskId_), (time_) )
#       define T1_TraceStartNoActNoSuspTimePC( coreId_, time_, taskId_ )    \
        T1_TRACE_START_NOACT_PC_( _NOSUSPTIME, coreId_, (taskId_), (time_) )
#       define T1_TraceStartNoActStop( taskId_ )                            \
        T1_TRACE_START_STOP_PC( , T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStartNoActStopPC( coreId_, taskId_ )                 \
        T1_TRACE_START_STOP_PC( , (coreId_), (taskId_) )
#       define T1_TraceStartNoActStopFast( taskId_ )                        \
        T1_TRACE_START_STOP_PC( _FAST, T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStartNoActStopFastPC( coreId_, taskId_ )             \
        T1_TRACE_START_STOP_PC( _FAST, (coreId_), (taskId_) )
#       define T1_TraceStartNoActStopNoSusp( taskId_ )                      \
        T1_TRACE_START_STOP_PC( _NOSUSP, T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStartNoActStopNoSuspPC( coreId_, taskId_ )           \
        T1_TRACE_START_STOP_PC( _NOSUSP, (coreId_), (taskId_) )
#       define T1_TraceStartNoActStopNoSuspTime( time_, taskId_ )           \
        T1_TRACE_START_STOP_PC_( _NOSUSPTIME, T1_GetCoreIdOffset( ), (taskId_), (time_) )
#       define T1_TraceStartNoActStopNoSuspTimePC( coreId_, time_, taskId_ ) \
        T1_TRACE_START_STOP_PC_( _NOSUSPTIME, coreId_, (taskId_), (time_) )
#       define T1_TraceStop( taskId_ )                                      \
        T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_STOP_PC( , T1_GetCoreIdOffset( ), (taskId_) ) )
#       define T1_TraceStopPC( coreId_, taskId_ )                           \
        T1_DECR_PREEMPTIONS_PC( (coreId_), T1_TRACE_STOP_PC( , (coreId_), (taskId_) ) )
#       define T1_TraceStopFast( taskId_ )                                  \
        T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_STOP_PC( _FAST, T1_GetCoreIdOffset( ), (taskId_) ) )
#       define T1_TraceStopFastPC( coreId_, taskId_ )                       \
        T1_DECR_PREEMPTIONS_PC( (coreId_), T1_TRACE_STOP_PC( _FAST, (coreId_), (taskId_) ) )
#       define T1_TraceStopNoSusp( taskId_ )                                \
        T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_STOP_PC( _NOSUSP, T1_GetCoreIdOffset( ), (taskId_) ) )
#       define T1_TraceStopNoSuspPC( coreId_, taskId_ )                     \
        T1_DECR_PREEMPTIONS_PC( (coreId_), T1_TRACE_STOP_PC( _NOSUSP, (coreId_), (taskId_) ) )
#       define T1_TraceStopNoSuspTime( time_, taskId_ )                     \
        T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_STOP_PC_( _NOSUSPTIME, T1_GetCoreIdOffset( ), (taskId_), (time_) ) )
#       define T1_TraceStopNoSuspTimePC( coreId_, time_, taskId_ )          \
        T1_DECR_PREEMPTIONS_PC( coreId_, T1_TRACE_STOP_PC_( _NOSUSPTIME, coreId_, (taskId_), (time_) ) )
#       define T1_TraceStopStart( stopTaskId_, taskId_ )                    \
        T1_TRACE_STOP_START_PC( , T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStopStartPC( coreId_, stopTaskId_, taskId_ )         \
        T1_TRACE_STOP_START_PC( , (coreId_), (taskId_) )
#       define T1_TraceStopStartFast( stopTaskId_, taskId_ )                \
        T1_TRACE_STOP_START_PC( _FAST, T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStopStartFastPC( coreId_, stopTaskId_, taskId_ )     \
        T1_TRACE_STOP_START_PC( _FAST, (coreId_), (taskId_) )
#       define T1_TraceStopStartNoSusp( stopTaskId_, taskId_ )              \
        T1_TRACE_STOP_START_PC( _NOSUSP, T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStopStartNoSuspPC( coreId_, stopTaskId_, taskId_ )   \
        T1_TRACE_STOP_START_PC( _NOSUSP, (coreId_), (taskId_) )
#       define T1_TraceStopStartNoSuspTime( time_, stopTaskId_, taskId_ )   \
        T1_TRACE_STOP_START_PC_( _NOSUSPTIME, T1_GetCoreIdOffset( ), (taskId_), (time_) )
#       define T1_TraceStopStartNoSuspTimePC( coreId_, time_, stopTaskId_, taskId_ ) \
        T1_TRACE_STOP_START_PC_( _NOSUSPTIME, coreId_, (taskId_), (time_) )
#       define T1_TraceStopStartAct( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC( , T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#       define T1_TraceStopStartActPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC( , (coreId_), (taskId_), (actCoreId_), (actTime_) )
#       define T1_TraceStopStartActFast( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC( _FAST, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#       define T1_TraceStopStartActFastPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC( _FAST, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#       define T1_TraceStopStartActNoSusp( stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC( _NOSUSP, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_) )
#       define T1_TraceStopStartActNoSuspPC( coreId_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC( _NOSUSP, (coreId_), (taskId_), (actCoreId_), (actTime_) )
#       define T1_TraceStopStartActNoSuspTime( time_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC_( _NOSUSPTIME, T1_GetCoreIdOffset( ), (taskId_), (actCoreId_), (actTime_), (time_) )
#       define T1_TraceStopStartActNoSuspTimePC( coreId_, time_, stopTaskId_, taskId_, actCoreId_, actTime_ ) \
        T1_TRACE_STOP_START_ACT_PC_( _NOSUSPTIME, coreId_, (taskId_), (actCoreId_), (actTime_), (time_) )
#       define T1_TraceStopStartNoAct( stopTaskId_, taskId_ )               \
        T1_TRACE_STOP_START_NOACT_PC( , T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStopStartNoActPC( coreId_, stopTaskId_, taskId_ )    \
        T1_TRACE_STOP_START_NOACT_PC( , (coreId_), (taskId_) )
#       define T1_TraceStopStartNoActFast( stopTaskId_, taskId_ )           \
        T1_TRACE_STOP_START_NOACT_PC( _FAST, T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStopStartNoActFastPC( coreId_, stopTaskId_, taskId_ ) \
        T1_TRACE_STOP_START_NOACT_PC( _FAST, (coreId_), (taskId_) )
#       define T1_TraceStopStartNoActNoSusp( stopTaskId_, taskId_ )         \
        T1_TRACE_STOP_START_NOACT_PC( _NOSUSP, T1_GetCoreIdOffset( ), (taskId_) )
#       define T1_TraceStopStartNoActNoSuspPC( coreId_, stopTaskId_, taskId_ ) \
        T1_TRACE_STOP_START_NOACT_PC( _NOSUSP, (coreId_), (taskId_) )
#       define T1_TraceStopStartNoActNoSuspTime( time_, stopTaskId_, taskId_ ) \
        T1_TRACE_STOP_START_NOACT_PC_( _NOSUSPTIME, T1_GetCoreIdOffset( ), (taskId_), (time_) )
#       define T1_TraceStopStartNoActNoSuspTimePC( coreId_, time_, stopTaskId_, taskId_ ) \
        T1_TRACE_STOP_START_NOACT_PC_( _NOSUSPTIME, coreId_, (taskId_), (time_) )
#       define T1_TraceSyncTimer( coreId_ )                                 \
        T1_TRACE_SYNC( , T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ) )
#       define T1_TraceSyncTimerPC( coreId_ )                               \
        T1_TRACE_SYNC( , T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ) )
#       define T1_TraceSyncTimerFast( coreId_ )                             \
        T1_TRACE_SYNC( _FAST, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ) )
#       define T1_TraceSyncTimerFastPC( coreId_ )                           \
        T1_TRACE_SYNC( _FAST, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ) )
#       define T1_TraceSyncTimerNoSusp( coreId_ )                           \
        T1_TRACE_SYNC( _NOSUSP, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ) )
#       define T1_TraceSyncTimerNoSuspPC( coreId_ )                         \
        T1_TRACE_SYNC( _NOSUSP, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_SYNCDATA_START, T1_TRACEDATA_UINT32 ) )
#       define T1_TraceWait( taskId_ )                                      \
        T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       define T1_TraceWaitPC( coreId_, taskId_ )                           \
        T1_DECR_PREEMPTIONS_PC( (coreId_), T1_TRACE_ATOMIC_( , T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       define T1_TraceWaitFast( taskId_ )                                  \
        T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       define T1_TraceWaitFastPC( coreId_, taskId_ )                       \
        T1_DECR_PREEMPTIONS_PC( (coreId_), T1_TRACE_ATOMIC_( _FAST, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       define T1_TraceWaitNoSusp( taskId_ )                                \
        T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#       define T1_TraceWaitNoSuspPC( coreId_, taskId_ )                     \
        T1_DECR_PREEMPTIONS_PC( (coreId_), T1_TRACE_ATOMIC_( _NOSUSP, T1_TraceEvent, T1_CORE_ID_TO_SCOPE_CONSTS( (coreId_) ), T1_COMBINE_EVENT_INFO( T1_WAIT, (taskId_) ) ) )
#   endif /* 1 == T1_NOF_CORES */
/* END   generated variant macros */
/* clang-format on */

/* Used by T1_TraceUint16/Sint16... Only support little-endian T1_ARM7M */
#    if defined T1_TRICORE || defined T1_RH850 || defined T1_HOST || defined T1_ARM7M
#        define T1_16_TO_U32( _16_ ) ( (T1_uint32_t)(T1_uint16_t)( _16_ ) )
#    elif defined T1_MPC5XXXX
#        define T1_16_TO_U32( _16_ ) ( (T1_uint32_t)( _16_ ) << 16 )
#    else /* endian-ness depends on specific variant */
#        define T1_16_TO_U32( _16_ ) ( T1_16toU32( _16_ ) )
#    endif /* endian-ness */

#    define T1_TraceData( id_, vrnt_, pData_, len_ )                                 \
        T1_TRACEDATA( _,                                                             \
                      ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | ( vrnt_ ),                  \
                      (T1_uint8_t const *)( pData_ ),                                \
                      ( len_ ) )
#    define T1_TraceDataFast( id_, vrnt_, pData_, len_ )                             \
        T1_TRACEDATA( _,                                                             \
                      ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | ( vrnt_ ),                  \
                      (T1_uint8_t const *)( pData_ ),                                \
                      ( len_ ) )
#    define T1_TraceDataNoSusp( id_, vrnt_, pData_, len_ )                           \
        T1_TRACEDATA( NoSusp_,                                                       \
                      ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | ( vrnt_ ),                  \
                      (T1_uint8_t const *)( pData_ ),                                \
                      ( len_ ) )
#    define T1_TraceDataNoSuspTime( id_, vrnt_, pData_, len_, time_ )                \
        T1_TRACEDATA_NOSUSPTIME( ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | ( vrnt_ ),       \
                                 (T1_uint8_t const *)( pData_ ),                     \
                                 ( len_ ),                                           \
                                 ( time_ ) )
#    define T1_TraceUint16( id_, ui16_ )                                             \
        T1_TRACE_UINT32(,                                                            \
                        T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),         \
                        ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT16,      \
                        T1_16_TO_U32( ui16_ ) )
#    define T1_TraceUint16Fast( id_, ui16_ )                                         \
        T1_TRACE_UINT32( _FAST,                                                      \
                         T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),        \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT16,     \
                         T1_16_TO_U32( ui16_ ) )
#    define T1_TraceUint16NoSusp( id_, ui16_ )                                       \
        T1_TRACE_UINT32( _NOSUSP,                                                    \
                         T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),        \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT16,     \
                         T1_16_TO_U32( ui16_ ) )
#    define T1_TraceUint32( id_, ui32_ )                                             \
        T1_TRACE_UINT32(,                                                            \
                        T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),         \
                        ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT32,      \
                        ( ui32_ ) )
#    define T1_TraceUint32Fast( id_, ui32_ )                                         \
        T1_TRACE_UINT32( _FAST,                                                      \
                         T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),        \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT32,     \
                         ( ui32_ ) )
#    define T1_TraceUint32NoSusp( id_, ui32_ )                                       \
        T1_TRACE_UINT32( _NOSUSP,                                                    \
                         T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),        \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT32,     \
                         ( ui32_ ) )
#    define T1_TraceSint16( id_, si16_ )                                             \
        T1_TRACE_UINT32(,                                                            \
                        T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),         \
                        ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT16,      \
                        T1_16_TO_U32( si16_ ) )
#    define T1_TraceSint16Fast( id_, si16_ )                                         \
        T1_TRACE_UINT32( _FAST,                                                      \
                         T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),        \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT16,     \
                         T1_16_TO_U32( si16_ ) )
#    define T1_TraceSint16NoSusp( id_, si16_ )                                       \
        T1_TRACE_UINT32( _NOSUSP,                                                    \
                         T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),        \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT16,     \
                         T1_16_TO_U32( si16_ ) )
#    define T1_TraceSint32( id_, si32_ )                                             \
        T1_TRACE_UINT32(,                                                            \
                        T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),         \
                        ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT32,      \
                        (T1_uint32_t)( si32_ ) )
#    define T1_TraceSint32Fast( id_, si32_ )                                         \
        T1_TRACE_UINT32( _FAST,                                                      \
                         T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),        \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT32,     \
                         (T1_uint32_t)( si32_ ) )
#    define T1_TraceSint32NoSusp( id_, si32_ )                                       \
        T1_TRACE_UINT32( _NOSUSP,                                                    \
                         T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),        \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT32,     \
                         (T1_uint32_t)( si32_ ) )
#    define T1_TraceAddr( id_, addr_ )                                               \
        T1_TRACE_UINT32(,                                                            \
                        T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),         \
                        ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_ADDRESS,     \
                        (T1_uint32_t)( addr_ ) )
#    define T1_TraceAddrFast( id_, addr_ )                                           \
        T1_TRACE_UINT32( _FAST,                                                      \
                         T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),        \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_ADDRESS,    \
                         (T1_uint32_t)( addr_ ) )
#    define T1_TraceAddrNoSusp( id_, addr_ )                                         \
        T1_TRACE_UINT32( _NOSUSP,                                                    \
                         T1_CORE_ID_TO_SCOPE_CONSTS( T1_GetCoreIdOffset( ) ),        \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_ADDRESS,    \
                         (T1_uint32_t)( addr_ ) )
#    define T1_TraceFloat( id_, float_ )                                             \
        T1_TRACEDATA( _,                                                             \
                      ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_FLOAT,         \
                      (T1_uint8_t const *)&( float_ ),                               \
                      4u )
#    define T1_TraceFloatFast( id_, float_ )                                         \
        T1_TRACEDATA( _,                                                             \
                      ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_FLOAT,         \
                      (T1_uint8_t const *)&( float_ ),                               \
                      4u )
#    define T1_TraceFloatNoSusp( id_, float_ )                                       \
        T1_TRACEDATA( NoSusp_,                                                       \
                      ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_FLOAT,         \
                      (T1_uint8_t const *)&( float_ ),                               \
                      4u )
#    define T1_TraceUint64( id_, ui64_ )                                             \
        T1_TRACEDATA( _,                                                             \
                      ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT64,        \
                      (T1_uint8_t const *)&( ui64_ ),                                \
                      8u )
#    define T1_TraceUint64Fast( id_, ui64_ )                                         \
        T1_TRACEDATA( _,                                                             \
                      ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT64,        \
                      (T1_uint8_t const *)&( ui64_ ),                                \
                      8u )
#    define T1_TraceUint64NoSusp( id_, ui64_ )                                       \
        T1_TRACEDATA( NoSusp_,                                                       \
                      ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT64,        \
                      (T1_uint8_t const *)&( ui64_ ),                                \
                      8u )
#    define T1_TraceSint64( id_, si64_ )                                             \
        T1_TRACEDATA( _,                                                             \
                      ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT64,        \
                      (T1_uint8_t const *)&( si64_ ),                                \
                      8u )
#    define T1_TraceSint64Fast( id_, si64_ )                                         \
        T1_TRACEDATA( _,                                                             \
                      ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT64,        \
                      (T1_uint8_t const *)&( si64_ ),                                \
                      8u )
#    define T1_TraceSint64NoSusp( id_, si64_ )                                       \
        T1_TRACEDATA( NoSusp_,                                                       \
                      ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT64,        \
                      (T1_uint8_t const *)&( si64_ ),                                \
                      8u )
#    define T1_TraceString( id_, pData_, len_ )                                      \
        T1_TRACEDATA(                                                                \
            _,                                                                       \
            ( ( ( id_ ) & ( 0x1Fu ) ) << 4 )                                         \
                | ( T1_TRACEDATA_STR_REST0 + ( len_ ) % T1_DATA_BYTES_PER_ENTRY ),   \
            (T1_uint8_t const *)( pData_ ),                                          \
            ( len_ ) )
#    define T1_TraceStringFast( id_, pData_, len_ )                                  \
        T1_TRACEDATA(                                                                \
            _,                                                                       \
            ( ( ( id_ ) & ( 0x1Fu ) ) << 4 )                                         \
                | ( T1_TRACEDATA_STR_REST0 + ( len_ ) % T1_DATA_BYTES_PER_ENTRY ),   \
            (T1_uint8_t const *)( pData_ ),                                          \
            ( len_ ) )
#    define T1_TraceStringNoSusp( id_, pData_, len_ )                                \
        T1_TRACEDATA(                                                                \
            NoSusp_,                                                                 \
            ( ( ( id_ ) & ( 0x1Fu ) ) << 4 )                                         \
                | ( T1_TRACEDATA_STR_REST0 + ( len_ ) % T1_DATA_BYTES_PER_ENTRY ),   \
            (T1_uint8_t const *)( pData_ ),                                          \
            ( len_ ) )
#    define T1_TraceBinary( id_, pData_, len_ )                                      \
        T1_TRACEDATA(                                                                \
            _,                                                                       \
            ( ( ( id_ ) & ( 0x1Fu ) ) << 4 )                                         \
                | ( T1_TRACEDATA_BIN_REST0 + ( len_ ) % T1_DATA_BYTES_PER_ENTRY ),   \
            (T1_uint8_t const *)( pData_ ),                                          \
            ( len_ ) )
#    define T1_TraceBinaryFast( id_, pData_, len_ )                                  \
        T1_TRACEDATA(                                                                \
            _,                                                                       \
            ( ( ( id_ ) & ( 0x1Fu ) ) << 4 )                                         \
                | ( T1_TRACEDATA_BIN_REST0 + ( len_ ) % T1_DATA_BYTES_PER_ENTRY ),   \
            (T1_uint8_t const *)( pData_ ),                                          \
            ( len_ ) )
#    define T1_TraceBinaryNoSusp( id_, pData_, len_ )                                \
        T1_TRACEDATA(                                                                \
            NoSusp_,                                                                 \
            ( ( ( id_ ) & ( 0x1Fu ) ) << 4 )                                         \
                | ( T1_TRACEDATA_BIN_REST0 + ( len_ ) % T1_DATA_BYTES_PER_ENTRY ),   \
            (T1_uint8_t const *)( pData_ ),                                          \
            ( len_ ) )
#    define T1_TraceDataPC( coreId_, id_, vrnt_, pData_, len_ )                      \
        T1_TRACEDATA_PC( _,                                                          \
                         ( coreId_ ),                                                \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | ( vrnt_ ),               \
                         (T1_uint8_t const *)( pData_ ),                             \
                         ( len_ ) )
#    define T1_TraceDataFastPC( coreId_, id_, vrnt_, pData_, len_ )                  \
        T1_TRACEDATA_PC( _,                                                          \
                         ( coreId_ ),                                                \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | ( vrnt_ ),               \
                         (T1_uint8_t const *)( pData_ ),                             \
                         ( len_ ) )
#    define T1_TraceDataNoSuspPC( coreId_, id_, vrnt_, pData_, len_ )                \
        T1_TRACEDATA_PC( NoSusp_,                                                    \
                         ( coreId_ ),                                                \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | ( vrnt_ ),               \
                         (T1_uint8_t const *)( pData_ ),                             \
                         ( len_ ) )
#    define T1_TraceDataNoSuspTimePC( coreId_, id_, vrnt_, pData_, len_, time_ )     \
        T1_TRACEDATA_NOSUSPTIME_PC( ( coreId_ ),                                     \
                                    ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | ( vrnt_ ),    \
                                    (T1_uint8_t const *)( pData_ ),                  \
                                    ( len_ ),                                        \
                                    ( time_ ) )
#    define T1_TraceUint16PC( coreId_, id_, ui16_ )                                  \
        T1_TRACE_UINT32(,                                                            \
                        T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                       \
                        ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT16,      \
                        T1_16_TO_U32( ui16_ ) )
#    define T1_TraceUint16FastPC( coreId_, id_, ui16_ )                              \
        T1_TRACE_UINT32( _FAST,                                                      \
                         T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                      \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT16,     \
                         T1_16_TO_U32( ui16_ ) )
#    define T1_TraceUint16NoSuspPC( coreId_, id_, ui16_ )                            \
        T1_TRACE_UINT32( _NOSUSP,                                                    \
                         T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                      \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT16,     \
                         T1_16_TO_U32( ui16_ ) )
#    define T1_TraceUint32PC( coreId_, id_, ui32_ )                                  \
        T1_TRACE_UINT32(,                                                            \
                        T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                       \
                        ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT32,      \
                        ( ui32_ ) )
#    define T1_TraceUint32FastPC( coreId_, id_, ui32_ )                              \
        T1_TRACE_UINT32( _FAST,                                                      \
                         T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                      \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT32,     \
                         ( ui32_ ) )
#    define T1_TraceUint32NoSuspPC( coreId_, id_, ui32_ )                            \
        T1_TRACE_UINT32( _NOSUSP,                                                    \
                         T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                      \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT32,     \
                         ( ui32_ ) )
#    define T1_TraceSint16PC( coreId_, id_, si16_ )                                  \
        T1_TRACE_UINT32(,                                                            \
                        T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                       \
                        ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT16,      \
                        T1_16_TO_U32( si16_ ) )
#    define T1_TraceSint16FastPC( coreId_, id_, si16_ )                              \
        T1_TRACE_UINT32( _FAST,                                                      \
                         T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                      \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT16,     \
                         T1_16_TO_U32( si16_ ) )
#    define T1_TraceSint16NoSuspPC( coreId_, id_, si16_ )                            \
        T1_TRACE_UINT32( _NOSUSP,                                                    \
                         T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                      \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT16,     \
                         T1_16_TO_U32( si16_ ) )
#    define T1_TraceSint32PC( coreId_, id_, si32_ )                                  \
        T1_TRACE_UINT32(,                                                            \
                        T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                       \
                        ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT32,      \
                        (T1_uint32_t)( si32_ ) )
#    define T1_TraceSint32FastPC( coreId_, id_, si32_ )                              \
        T1_TRACE_UINT32( _FAST,                                                      \
                         T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                      \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT32,     \
                         (T1_uint32_t)( si32_ ) )
#    define T1_TraceSint32NoSuspPC( coreId_, id_, si32_ )                            \
        T1_TRACE_UINT32( _NOSUSP,                                                    \
                         T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                      \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT32,     \
                         (T1_uint32_t)( si32_ ) )
#    define T1_TraceAddrPC( coreId_, id_, addr_ )                                    \
        T1_TRACE_UINT32(,                                                            \
                        T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                       \
                        ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_ADDRESS,     \
                        (T1_uint32_t)( addr_ ) )
#    define T1_TraceAddrFastPC( coreId_, id_, addr_ )                                \
        T1_TRACE_UINT32( _FAST,                                                      \
                         T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                      \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_ADDRESS,    \
                         (T1_uint32_t)( addr_ ) )
#    define T1_TraceAddrNoSuspPC( coreId_, id_, addr_ )                              \
        T1_TRACE_UINT32( _NOSUSP,                                                    \
                         T1_CORE_ID_TO_SCOPE_CONSTS( coreId_ ),                      \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_ADDRESS,    \
                         (T1_uint32_t)( addr_ ) )
#    define T1_TraceFloatPC( coreId_, id_, float_ )                                  \
        T1_TRACEDATA_PC( _,                                                          \
                         ( coreId_ ),                                                \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_FLOAT,      \
                         (T1_uint8_t const *)&( float_ ),                            \
                         4u )
#    define T1_TraceFloatFastPC( coreId_, id_, float_ )                              \
        T1_TRACEDATA_PC( _,                                                          \
                         ( coreId_ ),                                                \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_FLOAT,      \
                         (T1_uint8_t const *)&( float_ ),                            \
                         4u )
#    define T1_TraceFloatNoSuspPC( coreId_, id_, float_ )                            \
        T1_TRACEDATA_PC( NoSusp_,                                                    \
                         ( coreId_ ),                                                \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_FLOAT,      \
                         (T1_uint8_t const *)&( float_ ),                            \
                         4u )
#    define T1_TraceUint64PC( coreId_, id_, ui64_ )                                  \
        T1_TRACEDATA_PC( _,                                                          \
                         ( coreId_ ),                                                \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT64,     \
                         (T1_uint8_t const *)&( ui64_ ),                             \
                         8u )
#    define T1_TraceUint64FastPC( coreId_, id_, ui64_ )                              \
        T1_TRACEDATA_PC( _,                                                          \
                         ( coreId_ ),                                                \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT64,     \
                         (T1_uint8_t const *)&( ui64_ ),                             \
                         8u )
#    define T1_TraceUint64NoSuspPC( coreId_, id_, ui64_ )                            \
        T1_TRACEDATA_PC( NoSusp_,                                                    \
                         ( coreId_ ),                                                \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_UINT64,     \
                         (T1_uint8_t const *)&( ui64_ ),                             \
                         8u )
#    define T1_TraceSint64PC( coreId_, id_, si64_ )                                  \
        T1_TRACEDATA_PC( _,                                                          \
                         ( coreId_ ),                                                \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT64,     \
                         (T1_uint8_t const *)&( si64_ ),                             \
                         8u )
#    define T1_TraceSint64FastPC( coreId_, id_, si64_ )                              \
        T1_TRACEDATA_PC( _,                                                          \
                         ( coreId_ ),                                                \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT64,     \
                         (T1_uint8_t const *)&( si64_ ),                             \
                         8u )
#    define T1_TraceSint64NoSuspPC( coreId_, id_, si64_ )                            \
        T1_TRACEDATA_PC( NoSusp_,                                                    \
                         ( coreId_ ),                                                \
                         ( ( ( id_ ) & ( 0x1Fu ) ) << 4 ) | T1_TRACEDATA_SINT64,     \
                         (T1_uint8_t const *)&( si64_ ),                             \
                         8u )
#    define T1_TraceStringPC( coreId_, id_, pData_, len_ )                           \
        T1_TRACEDATA_PC(                                                             \
            _,                                                                       \
            ( coreId_ ),                                                             \
            ( ( ( id_ ) & ( 0x1Fu ) ) << 4 )                                         \
                | ( T1_TRACEDATA_STR_REST0 + ( len_ ) % T1_DATA_BYTES_PER_ENTRY ),   \
            (T1_uint8_t const *)( pData_ ),                                          \
            ( len_ ) )
#    define T1_TraceStringFastPC( coreId_, id_, pData_, len_ )                       \
        T1_TRACEDATA_PC(                                                             \
            _,                                                                       \
            ( coreId_ ),                                                             \
            ( ( ( id_ ) & ( 0x1Fu ) ) << 4 )                                         \
                | ( T1_TRACEDATA_STR_REST0 + ( len_ ) % T1_DATA_BYTES_PER_ENTRY ),   \
            (T1_uint8_t const *)( pData_ ),                                          \
            ( len_ ) )
#    define T1_TraceStringNoSuspPC( coreId_, id_, pData_, len_ )                     \
        T1_TRACEDATA_PC(                                                             \
            NoSusp_,                                                                 \
            ( coreId_ ),                                                             \
            ( ( ( id_ ) & ( 0x1Fu ) ) << 4 )                                         \
                | ( T1_TRACEDATA_STR_REST0 + ( len_ ) % T1_DATA_BYTES_PER_ENTRY ),   \
            (T1_uint8_t const *)( pData_ ),                                          \
            ( len_ ) )
#    define T1_TraceBinaryPC( coreId_, id_, pData_, len_ )                           \
        T1_TRACEDATA_PC(                                                             \
            _,                                                                       \
            ( coreId_ ),                                                             \
            ( ( ( id_ ) & ( 0x1Fu ) ) << 4 )                                         \
                | ( T1_TRACEDATA_BIN_REST0 + ( len_ ) % T1_DATA_BYTES_PER_ENTRY ),   \
            (T1_uint8_t const *)( pData_ ),                                          \
            ( len_ ) )
#    define T1_TraceBinaryFastPC( coreId_, id_, pData_, len_ )                       \
        T1_TRACEDATA_PC(                                                             \
            _,                                                                       \
            ( coreId_ ),                                                             \
            ( ( ( id_ ) & ( 0x1Fu ) ) << 4 )                                         \
                | ( T1_TRACEDATA_BIN_REST0 + ( len_ ) % T1_DATA_BYTES_PER_ENTRY ),   \
            (T1_uint8_t const *)( pData_ ),                                          \
            ( len_ ) )
#    define T1_TraceBinaryNoSuspPC( coreId_, id_, pData_, len_ )                     \
        T1_TRACEDATA_PC(                                                             \
            NoSusp_,                                                                 \
            ( coreId_ ),                                                             \
            ( ( ( id_ ) & ( 0x1Fu ) ) << 4 )                                         \
                | ( T1_TRACEDATA_BIN_REST0 + ( len_ ) % T1_DATA_BYTES_PER_ENTRY ),   \
            (T1_uint8_t const *)( pData_ ),                                          \
            ( len_ ) )

/* Deprecated */
#    define T1_TraceSync( pTime_ )       ( (void)0 )
#    define T1_TraceSyncFast( pTime_ )   ( (void)0 )
#    define T1_TraceSyncNoSusp( pTime_ ) ( (void)0 )

/*!
 * \name T1_TraceEventPerFeature
 * @{
 */

/*!
 * \brief   Trace a user stopwatch event or user event only if application feature is
 *          enabled.
 * \ingroup T1_scope_trace_interfaces
 * \param[in] event_ the event ID
 * \param[in] info_  additional info field, for example task/stopwatch ID
 * \param[in] mask_  the application feature to test
 *
 * \sa \ref APP_FEATURES, \ref USER_EVENTS, \ref USER_STOPWATCHES and \ref INTRPT
 */
#    define T1_TraceEventPerFeature( event_, info_, mask_ )                          \
        do                                                                           \
        {                                                                            \
            if( T1_IsFeatureEnabled( mask_ ) )                                       \
            {                                                                        \
                T1_TraceEvent( event_, info_ );                                      \
            }                                                                        \
        }                                                                            \
        while( 0 )
/*!
 * \brief   Trace a user stopwatch event or user event only if application feature is
 *          enabled.
 * \ingroup T1_scope_trace_interfaces
 * \param[in] event_ the event ID
 * \param[in] info_  additional info field, for example task/stopwatch ID
 * \param[in] mask_  the application feature to test
 *
 * \sa \ref APP_FEATURES, \ref USER_EVENTS, \ref USER_STOPWATCHES and \ref INTRPT
 */
#    define T1_TraceEventFastPerFeature( event_, info_, mask_ )                      \
        do                                                                           \
        {                                                                            \
            if( T1_IsFeatureEnabled( mask_ ) )                                       \
            {                                                                        \
                T1_TraceEventFast( event_, info_ );                                  \
            }                                                                        \
        }                                                                            \
        while( 0 )
/*!
 * \brief   Trace a user stopwatch event or user event only if application feature is
 *          enabled.
 * \ingroup T1_scope_trace_interfaces
 * \param[in] event_ the event ID
 * \param[in] info_  additional info field, for example task/stopwatch ID
 * \param[in] mask_  the application feature to test
 *
 * \sa \ref APP_FEATURES, \ref USER_EVENTS, \ref USER_STOPWATCHES and \ref INTRPT
 */
#    define T1_TraceEventNoSuspPerFeature( event_, info_, mask_ )                    \
        do                                                                           \
        {                                                                            \
            if( T1_IsFeatureEnabled( mask_ ) )                                       \
            {                                                                        \
                T1_TraceEventNoSusp( event_, info_ );                                \
            }                                                                        \
        }                                                                            \
        while( 0 )

/*! @} */

#else /* ! defined T1_ENABLE || defined T1_DISABLE_T1_SCOPE */
#    define T1_scopePlugin                                                ( T1_DISABLED_PLUGIN )
/* empty macros */
#    define T1_InitTraceBufferPC( coreId_ )                               ( (void)0 )
#    define T1_TraceEvent( event_, info_ )                                ( (void)0 )
#    define T1_TraceEventFast( event_, info_ )                            ( (void)0 )
#    define T1_TraceEventNoSusp( event_, info_ )                          ( (void)0 )
#    define T1_TraceEventNoSuspTime( time_, event_, info_ )               ( (void)0 )
#    define T1_TraceEventPC( coreId_, event_, info_ )                     ( (void)0 )
#    define T1_TraceEventFastPC( coreId_, event_, info_ )                 ( (void)0 )
#    define T1_TraceEventNoSuspPC( coreId_, event_, info_ )               ( (void)0 )
#    define T1_TraceEventNoSuspTimePC( coreId_, time_, event_, info_ )    ( (void)0 )
#    define T1_TraceStart( taskId_ )                                      ( (void)0 )
#    define T1_TraceStartFast( taskId_ )                                  ( (void)0 )
#    define T1_TraceStartNoSusp( taskId_ )                                ( (void)0 )
#    define T1_TraceStartPC( coreId_, taskId_ )                           ( (void)0 )
#    define T1_TraceStartFastPC( coreId_, taskId_ )                       ( (void)0 )
#    define T1_TraceStartNoSuspPC( coreId_, taskId_ )                     ( (void)0 )
#    define T1_TraceStartAct( taskId_, actCoreId_, time_ )                ( (void)0 )
#    define T1_TraceStartActFast( taskId_, actCoreId_, time_ )            ( (void)0 )
#    define T1_TraceStartActNoSusp( taskId_, actCoreId_, time_ )          ( (void)0 )
#    define T1_TraceStartActPC( coreId_, taskId_, actCoreId_, time_ )     ( (void)0 )
#    define T1_TraceStartActFastPC( coreId_, taskId_, actCoreId_, time_ ) ( (void)0 )
#    define T1_TraceStartActNoSuspPC( coreId_, taskId_, actCoreId_, time_ )          \
        ( (void)0 )
#    define T1_TraceStartNoAct( taskId_ )                                 ( (void)0 )
#    define T1_TraceStartNoActFast( taskId_ )                             ( (void)0 )
#    define T1_TraceStartNoActNoSusp( taskId_ )                           ( (void)0 )
#    define T1_TraceStartNoActPC( coreId_, taskId_ )                      ( (void)0 )
#    define T1_TraceStartNoActFastPC( coreId_, taskId_ )                  ( (void)0 )
#    define T1_TraceStartNoActNoSuspPC( coreId_, taskId_ )                ( (void)0 )
#    define T1_TraceStop( taskId_ )                                       ( (void)0 )
#    define T1_TraceStopFast( taskId_ )                                   ( (void)0 )
#    define T1_TraceStopNoSusp( taskId_ )                                 ( (void)0 )
#    define T1_TraceStopPC( coreId_, taskId_ )                            ( (void)0 )
#    define T1_TraceStopFastPC( coreId_, taskId_ )                        ( (void)0 )
#    define T1_TraceStopNoSuspPC( coreId_, taskId_ )                      ( (void)0 )
#    define T1_TraceActivation( taskId_ )                                 ( (void)0 )
#    define T1_TraceActivationFast( taskId_ )                             ( (void)0 )
#    define T1_TraceActivationNoSusp( taskId_ )                           ( (void)0 )
#    define T1_TraceActivationPC( coreId_, taskId_ )                      ( (void)0 )
#    define T1_TraceActivationFastPC( coreId_, taskId_ )                  ( (void)0 )
#    define T1_TraceActivationNoSuspPC( coreId_, taskId_ )                ( (void)0 )
#    define T1_TraceStopStart( stopTaskId_, startTaskId_ )                ( (void)0 )
#    define T1_TraceStopStartFast( stopTaskId_, startTaskId_ )            ( (void)0 )
#    define T1_TraceStopStartNoSusp( stopTaskId_, startTaskId_ )          ( (void)0 )
#    define T1_TraceStopStartPC( coreId_, stopTaskId_, startTaskId_ )     ( (void)0 )
#    define T1_TraceStopStartFastPC( coreId_, stopTaskId_, startTaskId_ ) ( (void)0 )
#    define T1_TraceStopStartNoSuspPC( coreId_, stopTaskId_, startTaskId_ )          \
        ( (void)0 )
#    define T1_TraceStopStartAct( stopTaskId_, startTaskId_, actCoreId_, time_ )     \
        ( (void)0 )
#    define T1_TraceStopStartActFast( stopTaskId_, startTaskId_, actCoreId_, time_ ) \
        ( (void)0 )
#    define T1_TraceStopStartActNoSusp( stopTaskId_,                                 \
                                        startTaskId_,                                \
                                        actCoreId_,                                  \
                                        time_ )                                      \
        ( (void)0 )
#    define T1_TraceStopStartActPC( coreId_,                                         \
                                    stopTaskId_,                                     \
                                    startTaskId_,                                    \
                                    actCoreId_,                                      \
                                    time_ )                                          \
        ( (void)0 )
#    define T1_TraceStopStartActFastPC( coreId_,                                     \
                                        stopTaskId_,                                 \
                                        startTaskId_,                                \
                                        actCoreId_,                                  \
                                        time_ )                                      \
        ( (void)0 )
#    define T1_TraceStopStartActNoSuspPC( coreId_,                                   \
                                          stopTaskId_,                               \
                                          startTaskId_,                              \
                                          actCoreId_,                                \
                                          time_ )                                    \
        ( (void)0 )
#    define T1_TraceStopStartNoAct( stopTaskId_, startTaskId_ )            ( (void)0 )
#    define T1_TraceStopStartNoActFast( stopTaskId_, startTaskId_ )        ( (void)0 )
#    define T1_TraceStopStartNoActNoSusp( stopTaskId_, startTaskId_ )      ( (void)0 )
#    define T1_TraceStopStartNoActPC( coreId_, stopTaskId_, startTaskId_ ) ( (void)0 )
#    define T1_TraceStopStartNoActFastPC( coreId_, stopTaskId_, startTaskId_ )       \
        ( (void)0 )
#    define T1_TraceStopStartNoActNoSuspPC( coreId_, stopTaskId_, startTaskId_ )     \
        ( (void)0 )
#    define T1_TraceStartNoActStop( taskId_ )                         ( (void)0 )
#    define T1_TraceStartNoActStopFast( taskId_ )                     ( (void)0 )
#    define T1_TraceStartNoActStopNoSusp( taskId_ )                   ( (void)0 )
#    define T1_TraceStartNoActStopPC( coreId_, taskId_ )              ( (void)0 )
#    define T1_TraceStartNoActStopFastPC( coreId_, taskId_ )          ( (void)0 )
#    define T1_TraceStartNoActStopNoSuspPC( coreId_, taskId_ )        ( (void)0 )
#    define T1_TraceData( id_, kind_, pData_, len_ )                  ( (void)0 )
#    define T1_TraceDataFast( id_, kind_, pData_, len_ )              ( (void)0 )
#    define T1_TraceDataNoSusp( id_, kind_, pData_, len_ )            ( (void)0 )
#    define T1_TraceUint16( id_, ui16_ )                              ( (void)0 )
#    define T1_TraceUint16Fast( id_, ui16_ )                          ( (void)0 )
#    define T1_TraceUint16NoSusp( id_, ui16_ )                        ( (void)0 )
#    define T1_TraceUint32( id_, ui32_ )                              ( (void)0 )
#    define T1_TraceUint32Fast( id_, ui32_ )                          ( (void)0 )
#    define T1_TraceUint32NoSusp( id_, ui32_ )                        ( (void)0 )
#    define T1_TraceAddr( id_, addr_ )                                ( (void)0 )
#    define T1_TraceAddrFast( id_, addr_ )                            ( (void)0 )
#    define T1_TraceAddrNoSusp( id_, addr_ )                          ( (void)0 )
#    define T1_TraceString( id_, pData_, len_ )                       ( (void)0 )
#    define T1_TraceStringFast( id_, pData_, len_ )                   ( (void)0 )
#    define T1_TraceStringNoSusp( id_, pData_, len_ )                 ( (void)0 )
#    define T1_TraceBinary( id_, pData_, len_ )                       ( (void)0 )
#    define T1_TraceBinaryFast( id_, pData_, len_ )                   ( (void)0 )
#    define T1_TraceBinaryNoSusp( id_, pData_, len_ )                 ( (void)0 )
#    define T1_TraceDataPC( coreId_, id_, kind_, pData_, len_ )       ( (void)0 )
#    define T1_TraceDataFastPC( coreId_, id_, kind_, pData_, len_ )   ( (void)0 )
#    define T1_TraceDataNoSuspPC( coreId_, id_, kind_, pData_, len_ ) ( (void)0 )
#    define T1_TraceUint16PC( coreId_, id_, ui16_ )                   ( (void)0 )
#    define T1_TraceUint16FastPC( coreId_, id_, ui16_ )               ( (void)0 )
#    define T1_TraceUint16NoSuspPC( coreId_, id_, ui16_ )             ( (void)0 )
#    define T1_TraceUint32PC( coreId_, id_, ui32_ )                   ( (void)0 )
#    define T1_TraceUint32FastPC( coreId_, id_, ui32_ )               ( (void)0 )
#    define T1_TraceUint32NoSuspPC( coreId_, id_, ui32_ )             ( (void)0 )
#    define T1_TraceAddrPC( coreId_, id_, addr_ )                     ( (void)0 )
#    define T1_TraceAddrFastPC( coreId_, id_, addr_ )                 ( (void)0 )
#    define T1_TraceAddrNoSuspPC( coreId_, id_, addr_ )               ( (void)0 )
#    define T1_TraceStringPC( coreId_, id_, pData_, len_ )            ( (void)0 )
#    define T1_TraceStringFastPC( coreId_, id_, pData_, len_ )        ( (void)0 )
#    define T1_TraceStringNoSuspPC( coreId_, id_, pData_, len_ )      ( (void)0 )
#    define T1_TraceBinaryPC( coreId_, id_, pData_, len_ )            ( (void)0 )
#    define T1_TraceBinaryFastPC( coreId_, id_, pData_, len_ )        ( (void)0 )
#    define T1_TraceBinaryNoSuspPC( coreId_, id_, pData_, len_ )      ( (void)0 )
#    define T1_TraceSync( pTime_ )                                    ( (void)0 )
#    define T1_TraceSyncFast( pTime_ )                                ( (void)0 )
#    define T1_TraceSyncNoSusp( pTime_ )                              ( (void)0 )
#    define T1_TraceSyncTimer( core_ )                                ( (void)0 )
#    define T1_TraceSyncTimerFast( core_ )                            ( (void)0 )
#    define T1_TraceSyncTimerNoSusp( core_ )                          ( (void)0 )
#    define T1_TraceSyncTimerPC( core_ )                              ( (void)0 )
#    define T1_TraceSyncTimerFastPC( core_ )                          ( (void)0 )
#    define T1_TraceSyncTimerNoSuspPC( core_ )                        ( (void)0 )
#    define T1_SetStopTrigger( afterXevents_ )                        ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_SetStopTriggerFast( afterXevents_ )                    ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_SetStopTriggerNoSusp( afterXevents_ )                  ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_SetStopTriggerPC( coreId_, afterXevents_ )             ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_SetStopTriggerFastPC( coreId_, afterXevents_ )                        \
        ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_SetStopTriggerNoSuspPC( coreId_, afterXevents_ )                      \
        ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_TraceEventPerFeature( event_, info_, mask_ )       ( (void)0 )
#    define T1_TraceEventFastPerFeature( event_, info_, mask_ )   ( (void)0 )
#    define T1_TraceEventNoSuspPerFeature( event_, info_, mask_ ) ( (void)0 )
#    define T1_scopeRevision                                      ( 0uL )
#    define T1_TraceNamePC( coreId_, taskId_ )                    ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_TraceName( taskId_ )                               ( T1_PLUGIN_NOT_AVAILABLE )
#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_SCOPE */

/*----------------------------------------------------------------------------------*/
/*--- Declarations for global data structures --------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if !defined T1_MULTICORE_CLONE
#    define T1_CORE0_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE0_SEC_CONST_32 T1_scopeConsts0;
T1_EXTERN T1_scopeFgConsts_t T1_CORE0_SEC_CONST_32 T1_scopeFgConsts0;
#    define T1_CORE0_STOP_SEC_CONST_32
#    include "T1_MemMap.h"
#    if 1 < T1_NOF_CORES
#        define T1_CORE1_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE1_SEC_CONST_32 T1_scopeConsts1;
T1_EXTERN T1_scopeFgConsts_t T1_CORE1_SEC_CONST_32 T1_scopeFgConsts1;
#        define T1_CORE1_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 1 < T1_NOF_CORES */
#    if 2 < T1_NOF_CORES
#        define T1_CORE2_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE2_SEC_CONST_32 T1_scopeConsts2;
T1_EXTERN T1_scopeFgConsts_t T1_CORE2_SEC_CONST_32 T1_scopeFgConsts2;
#        define T1_CORE2_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 2 < T1_NOF_CORES */
#    if 3 < T1_NOF_CORES
#        define T1_CORE3_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE3_SEC_CONST_32 T1_scopeConsts3;
T1_EXTERN T1_scopeFgConsts_t T1_CORE3_SEC_CONST_32 T1_scopeFgConsts3;
#        define T1_CORE3_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 3 < T1_NOF_CORES */
#    if 4 < T1_NOF_CORES
#        define T1_CORE4_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE4_SEC_CONST_32 T1_scopeConsts4;
T1_EXTERN T1_scopeFgConsts_t T1_CORE4_SEC_CONST_32 T1_scopeFgConsts4;
#        define T1_CORE4_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 4 < T1_NOF_CORES */
#    if 5 < T1_NOF_CORES
#        define T1_CORE5_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE5_SEC_CONST_32 T1_scopeConsts5;
T1_EXTERN T1_scopeFgConsts_t T1_CORE5_SEC_CONST_32 T1_scopeFgConsts5;
#        define T1_CORE5_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 5 < T1_NOF_CORES */
#    if 6 < T1_NOF_CORES
#        define T1_CORE6_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE6_SEC_CONST_32 T1_scopeConsts6;
T1_EXTERN T1_scopeFgConsts_t T1_CORE6_SEC_CONST_32 T1_scopeFgConsts6;
#        define T1_CORE6_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 6 < T1_NOF_CORES */
#    if 7 < T1_NOF_CORES
#        define T1_CORE7_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE7_SEC_CONST_32 T1_scopeConsts7;
T1_EXTERN T1_scopeFgConsts_t T1_CORE7_SEC_CONST_32 T1_scopeFgConsts7;
#        define T1_CORE7_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 7 < T1_NOF_CORES */
#    if 8 < T1_NOF_CORES
#        define T1_CORE8_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE8_SEC_CONST_32 T1_scopeConsts8;
T1_EXTERN T1_scopeFgConsts_t T1_CORE8_SEC_CONST_32 T1_scopeFgConsts8;
#        define T1_CORE8_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 8 < T1_NOF_CORES */
#    if 9 < T1_NOF_CORES
#        define T1_CORE9_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE9_SEC_CONST_32 T1_scopeConsts9;
T1_EXTERN T1_scopeFgConsts_t T1_CORE9_SEC_CONST_32 T1_scopeFgConsts9;
#        define T1_CORE9_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 9 < T1_NOF_CORES */
#    if 10 < T1_NOF_CORES
#        define T1_CORE10_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE10_SEC_CONST_32 T1_scopeConsts10;
T1_EXTERN T1_scopeFgConsts_t T1_CORE10_SEC_CONST_32 T1_scopeFgConsts10;
#        define T1_CORE10_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 10 < T1_NOF_CORES */
#    if 11 < T1_NOF_CORES
#        define T1_CORE11_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE11_SEC_CONST_32 T1_scopeConsts11;
T1_EXTERN T1_scopeFgConsts_t T1_CORE11_SEC_CONST_32 T1_scopeFgConsts11;
#        define T1_CORE11_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 11 < T1_NOF_CORES */
#    if 12 < T1_NOF_CORES
#        define T1_CORE12_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE12_SEC_CONST_32 T1_scopeConsts12;
T1_EXTERN T1_scopeFgConsts_t T1_CORE12_SEC_CONST_32 T1_scopeFgConsts12;
#        define T1_CORE12_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 12 < T1_NOF_CORES */
#    if 13 < T1_NOF_CORES
#        define T1_CORE13_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE13_SEC_CONST_32 T1_scopeConsts13;
T1_EXTERN T1_scopeFgConsts_t T1_CORE13_SEC_CONST_32 T1_scopeFgConsts13;
#        define T1_CORE13_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 13 < T1_NOF_CORES */
#    if 14 < T1_NOF_CORES
#        define T1_CORE14_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeConsts_t T1_CORE14_SEC_CONST_32 T1_scopeConsts14;
T1_EXTERN T1_scopeFgConsts_t T1_CORE14_SEC_CONST_32 T1_scopeFgConsts14;
#        define T1_CORE14_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    endif /* 14 < T1_NOF_CORES */
#    define T1_CHECKED_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE0_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals0;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE0_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals0;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE0_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData0[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE0_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer0[];
#    if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE0_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw0[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE0_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache0[];
#    endif /* defined T1_FG_CONT */
#    define T1_CHECKED_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"
#    if !defined T1_FG_CONT
#        define T1_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE0_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw0[];
T1_EXTERN T1_csVStpwCache_t T1_CORE0_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache0[];
#        define T1_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* defined T1_FG_CONT */
#    if 1 < T1_NOF_CORES
#        define T1_CHECKED_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE1_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals1;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE1_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals1;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE1_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData1[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE1_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer1[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE1_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw1[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE1_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache1[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE1_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw1[];
T1_EXTERN T1_csVStpwCache_t T1_CORE1_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache1[];
#            define T1_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 1 < T1_NOF_CORES */
#    if 2 < T1_NOF_CORES
#        define T1_CHECKED_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE2_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals2;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE2_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals2;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE2_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData2[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE2_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer2[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE2_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw2[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE2_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache2[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE2_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw2[];
T1_EXTERN T1_csVStpwCache_t T1_CORE2_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache2[];
#            define T1_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 2 < T1_NOF_CORES */
#    if 3 < T1_NOF_CORES
#        define T1_CHECKED_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE3_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals3;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE3_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals3;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE3_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData3[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE3_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer3[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE3_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw3[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE3_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache3[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE3_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw3[];
T1_EXTERN T1_csVStpwCache_t T1_CORE3_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache3[];
#            define T1_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 3 < T1_NOF_CORES */
#    if 4 < T1_NOF_CORES
#        define T1_CHECKED_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE4_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals4;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE4_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals4;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE4_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData4[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE4_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer4[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE4_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw4[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE4_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache4[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE4_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw4[];
T1_EXTERN T1_csVStpwCache_t T1_CORE4_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache4[];
#            define T1_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 4 < T1_NOF_CORES */
#    if 5 < T1_NOF_CORES
#        define T1_CHECKED_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE5_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals5;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE5_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals5;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE5_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData5[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE5_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer5[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE5_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw5[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE5_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache5[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE5_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw5[];
T1_EXTERN T1_csVStpwCache_t T1_CORE5_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache5[];
#            define T1_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 5 < T1_NOF_CORES */
#    if 6 < T1_NOF_CORES
#        define T1_CHECKED_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE6_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals6;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE6_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals6;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE6_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData6[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE6_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer6[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE6_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw6[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE6_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache6[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE6_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw6[];
T1_EXTERN T1_csVStpwCache_t T1_CORE6_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache6[];
#            define T1_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 6 < T1_NOF_CORES */
#    if 7 < T1_NOF_CORES
#        define T1_CHECKED_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE7_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals7;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE7_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals7;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE7_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData7[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE7_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer7[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE7_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw7[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE7_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache7[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE7_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw7[];
T1_EXTERN T1_csVStpwCache_t T1_CORE7_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache7[];
#            define T1_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 7 < T1_NOF_CORES */
#    if 8 < T1_NOF_CORES
#        define T1_CHECKED_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE8_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals8;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE8_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals8;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE8_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData8[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE8_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer8[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE8_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw8[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE8_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache8[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE8_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw8[];
T1_EXTERN T1_csVStpwCache_t T1_CORE8_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache8[];
#            define T1_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 8 < T1_NOF_CORES */
#    if 9 < T1_NOF_CORES
#        define T1_CHECKED_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE9_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals9;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE9_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals9;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE9_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData9[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE9_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer9[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE9_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw9[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE9_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache9[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE9_SEC_VAR_POWER_ON_CLEARED_32 T1_vStpw9[];
T1_EXTERN T1_csVStpwCache_t T1_CORE9_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache9[];
#            define T1_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 9 < T1_NOF_CORES */
#    if 10 < T1_NOF_CORES
#        define T1_CHECKED_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE10_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals10;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE10_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals10;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE10_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData10[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE10_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer10[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE10_SEC_VAR_POWER_ON_CLEARED_32
    T1_vStpw10[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE10_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache10[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE10_SEC_VAR_POWER_ON_CLEARED_32
    T1_vStpw10[];
T1_EXTERN T1_csVStpwCache_t T1_CORE10_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache10[];
#            define T1_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 10 < T1_NOF_CORES */
#    if 11 < T1_NOF_CORES
#        define T1_CHECKED_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE11_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals11;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE11_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals11;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE11_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData11[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE11_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer11[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE11_SEC_VAR_POWER_ON_CLEARED_32
    T1_vStpw11[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE11_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache11[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE11_SEC_VAR_POWER_ON_CLEARED_32
    T1_vStpw11[];
T1_EXTERN T1_csVStpwCache_t T1_CORE11_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache11[];
#            define T1_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 11 < T1_NOF_CORES */
#    if 12 < T1_NOF_CORES
#        define T1_CHECKED_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE12_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals12;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE12_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals12;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE12_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData12[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE12_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer12[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE12_SEC_VAR_POWER_ON_CLEARED_32
    T1_vStpw12[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE12_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache12[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE12_SEC_VAR_POWER_ON_CLEARED_32
    T1_vStpw12[];
T1_EXTERN T1_csVStpwCache_t T1_CORE12_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache12[];
#            define T1_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 12 < T1_NOF_CORES */
#    if 13 < T1_NOF_CORES
#        define T1_CHECKED_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE13_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals13;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE13_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals13;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE13_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData13[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE13_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer13[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE13_SEC_VAR_POWER_ON_CLEARED_32
    T1_vStpw13[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE13_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache13[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE13_SEC_VAR_POWER_ON_CLEARED_32
    T1_vStpw13[];
T1_EXTERN T1_csVStpwCache_t T1_CORE13_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache13[];
#            define T1_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 13 < T1_NOF_CORES */
#    if 14 < T1_NOF_CORES
#        define T1_CHECKED_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CHECKED_CORE14_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeGlobals14;
T1_EXTERN T1_scopeFgGlobals_t T1_CHECKED_CORE14_SEC_VAR_POWER_ON_CLEARED_32
    T1_scopeFgGlobals14;
T1_EXTERN T1_stpwFgData_t T1_CHECKED_CORE14_SEC_VAR_POWER_ON_CLEARED_32
    T1_stpwFgData14[];
T1_EXTERN T1_resultTime_t T1_CHECKED_CORE14_SEC_VAR_POWER_ON_CLEARED_32
    T1_resultBuffer14[];
#        if defined T1_FG_CONT
T1_EXTERN T1_vStpwMapping_t T1_CHECKED_CORE14_SEC_VAR_POWER_ON_CLEARED_32
    T1_vStpw14[];
T1_EXTERN T1_csVStpwCache_t T1_CHECKED_CORE14_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache14[];
#        endif /* defined T1_FG_CONT */
#        define T1_CHECKED_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#        if !defined T1_FG_CONT
#            define T1_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
T1_EXTERN T1_vStpwMapping_t T1_CORE14_SEC_VAR_POWER_ON_CLEARED_32
    T1_vStpw14[];
T1_EXTERN T1_csVStpwCache_t T1_CORE14_SEC_VAR_POWER_ON_CLEARED_32
    T1_contCsVStpwCache14[];
#            define T1_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_32
#            include "T1_MemMap.h"
#        endif /* defined T1_FG_CONT */
#    endif     /* 14 < T1_NOF_CORES */
#    define T1_TRACEBUFFER_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE0_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer0[];
#    define T1_TRACEBUFFER_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"
#    if 1 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE1_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer1[];
#        define T1_TRACEBUFFER_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 1 < T1_NOF_CORES */
#    if 2 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE2_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer2[];
#        define T1_TRACEBUFFER_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 2 < T1_NOF_CORES */
#    if 3 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE3_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer3[];
#        define T1_TRACEBUFFER_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 3 < T1_NOF_CORES */
#    if 4 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE4_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer4[];
#        define T1_TRACEBUFFER_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 4 < T1_NOF_CORES */
#    if 5 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE5_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer5[];
#        define T1_TRACEBUFFER_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 5 < T1_NOF_CORES */
#    if 6 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE6_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer6[];
#        define T1_TRACEBUFFER_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 6 < T1_NOF_CORES */
#    if 7 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE7_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer7[];
#        define T1_TRACEBUFFER_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 7 < T1_NOF_CORES */
#    if 8 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE8_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer8[];
#        define T1_TRACEBUFFER_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 8 < T1_NOF_CORES */
#    if 9 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE9_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer9[];
#        define T1_TRACEBUFFER_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 9 < T1_NOF_CORES */
#    if 10 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE10_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer10[];
#        define T1_TRACEBUFFER_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 10 < T1_NOF_CORES */
#    if 11 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE11_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer11[];
#        define T1_TRACEBUFFER_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 11 < T1_NOF_CORES */
#    if 12 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE12_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer12[];
#        define T1_TRACEBUFFER_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 12 < T1_NOF_CORES */
#    if 13 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE13_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer13[];
#        define T1_TRACEBUFFER_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 13 < T1_NOF_CORES */
#    if 14 < T1_NOF_CORES
#        define T1_TRACEBUFFER_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR T1_TRACEBUFFER_CORE14_SEC_VAR_POWER_ON_CLEARED_32
    T1_traceBuffer14[];
#        define T1_TRACEBUFFER_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* 14 < T1_NOF_CORES */
#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t * const T1_SEC_CONST_32 T1_scopeGlobalsPC[];
/*! \brief Array of core-specific T1.scope global data. */
T1_EXTERN T1_scopeConsts_t * const T1_SEC_CONST_32 T1_scopeConstsPC[];
T1_EXTERN T1_scopeFgGlobals_t * const T1_SEC_CONST_32 T1_scopeFgGlobalsPC[];
T1_EXTERN T1_scopeFgConsts_t * const T1_SEC_CONST_32 T1_scopeFgConstsPC[];
T1_EXTERN T1_stpwFgData_t * const T1_SEC_CONST_32 T1_stpwFgDataPC[];
T1_EXTERN T1_scopeFgGlobalsInit_t T1_SEC_CONST_32 T1_initFgContScopePC[];
T1_EXTERN T1_taskFgInitData_t T1_SEC_CONST_32 T1_initFgContTasks[];
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"
#else /* clone */
#    define T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"
T1_EXTERN T1_scopeGlobals_t T1_CLONE_SEC_VAR_POWER_ON_CLEARED_32 T1_scopeGlobals;
T1_EXTERN T1_stpwFgData_t T1_CLONE_SEC_VAR_POWER_ON_CLEARED_32 T1_stpwFgData;
#    define T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"
#endif /* ! defined T1_MULTICORE_CLONE */

#if !defined T1_DISABLE_T1_CONT && defined T1_FG_CONT
#    define T1_CHECKED_START_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"
T1_EXTERN T1_taskFgData_t T1_CHECKED_SEC_VAR_POWER_ON_CLEARED_32 T1_taskFgData[];
T1_EXTERN T1_uint32_t T1_CHECKED_SEC_VAR_POWER_ON_CLEARED_32 T1_actExtra[];
#    define T1_CHECKED_STOP_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"
#endif /* ! defined T1_DISABLE_T1_CONT && defined T1_FG_CONT */

#define T1_START_SEC_CONST_32
#include "T1_MemMap.h"
T1_EXTERN T1_fgContHelpers_t const * const T1_SEC_CONST_32 T1_pFgContHelpers;
T1_EXTERN T1_fgContHelpers_t const T1_SEC_CONST_32 T1_46828;
T1_EXTERN T1_fgContHelpers_t const T1_SEC_CONST_32 T1_91054;
#define T1_STOP_SEC_CONST_32
#include "T1_MemMap.h"

#define T1_START_SEC_CONST_8
#include "T1_MemMap.h"
T1_EXTERN T1_uint8_t const T1_SEC_CONST_8 T1_syncPeriodPC[];
#define T1_STOP_SEC_CONST_8
#include "T1_MemMap.h"

#define T1_START_SEC_CONST_16
#include "T1_MemMap.h"
T1_EXTERN T1_uint16_t const T1_SEC_CONST_16 T1_maxNofTasks;
#define T1_STOP_SEC_CONST_16
#include "T1_MemMap.h"

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for external functions ----------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_START_SEC_CODE_FAST
#include "T1_MemMap.h"

T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_LargeInterval( T1_scopeFgConsts_t *pScopeConsts,
                      T1_eventInfo_t eventInfo,
                      T1_uint32_t diff,
                      T1_uint32_t syncTime );
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_BrokenInterval( T1_scopeFgConsts_t *pScopeConsts,
                       T1_eventInfo_t eventInfo,
                       T1_uint32_t diff,
                       T1_uint32_t syncTime );
#if defined T1_NEAR_CODE_FAST
T1_EXTERN T1_tickUint_t T1_NEAR_CODE_FAST
T1_NearLargeInterval( T1_scopeFgConsts_t *pScopeConsts,
                      T1_eventInfo_t eventInfo,
                      T1_uint32_t diff,
                      T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_NEAR_CODE_FAST
T1_NearBrokenInterval( T1_scopeFgConsts_t *pScopeConsts,
                       T1_eventInfo_t eventInfo,
                       T1_uint32_t diff,
                       T1_uint32_t syncTime );
#else /* ! defined T1_NEAR_CODE_FAST */
#    define T1_NearLargeInterval  T1_LargeInterval
#    define T1_NearBrokenInterval T1_BrokenInterval
#endif /* defined T1_NEAR_CODE_FAST */
#define T1_STOP_SEC_CODE_FAST
#include "T1_MemMap.h"

#define T1_START_SEC_CODE
#include "T1_MemMap.h"
T1_EXTERN T1_tickUint_t T1_CODE
T1_UserDataStopHandler( T1_scopeFgConsts_t *pScopeConsts,
                        T1_eventInfo_t eventInfo,
                        T1_uint32_t traceTime,
                        T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_Error( T1_scopeFgConsts_t *pScopeConsts,
                                          T1_eventInfo_t eventInfo,
                                          T1_uint32_t traceTime,
                                          T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_Empty( T1_scopeFgConsts_t *pScopeConsts,
                                          T1_eventInfo_t eventInfo,
                                          T1_uint32_t traceTime,
                                          T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_EmptyVS( T1_scopeFgConsts_t *pScopeConsts,
                                            T1_eventInfo_t eventInfo,
                                            T1_uint32_t traceTime,
                                            T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_ActivateTask( T1_scopeFgConsts_t *pScopeConsts,
                                                 T1_eventInfo_t taskId,
                                                 T1_uint32_t traceTime,
                                                 T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_ActivateTaskVS( T1_scopeFgConsts_t *pScopeConsts,
                                                   T1_eventInfo_t taskId,
                                                   T1_uint32_t traceTime,
                                                   T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_ActivateAndTraceTask( T1_scopeFgConsts_t *pScopeConsts,
                         T1_eventInfo_t taskId,
                         T1_uint32_t traceTime,
                         T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_ActivateAndTraceTaskVS( T1_scopeFgConsts_t *pScopeConsts,
                           T1_eventInfo_t taskId,
                           T1_uint32_t traceTime,
                           T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_ResumeTask( T1_scopeFgConsts_t *pScopeConsts,
                                               T1_eventInfo_t taskId,
                                               T1_uint32_t traceTime,
                                               T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_ResumeTaskVS( T1_scopeFgConsts_t *pScopeConsts,
                                                 T1_eventInfo_t taskId,
                                                 T1_uint32_t traceTime,
                                                 T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StartFlexStopwatchVS( T1_scopeFgConsts_t *pScopeConsts,
                         T1_eventInfo_t eventInfo,
                         T1_uint32_t traceTime,
                         T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StartFlexSwd( T1_scopeFgConsts_t *pScopeConsts,
                                                 T1_eventInfo_t eventInfo,
                                                 T1_uint32_t traceTime,
                                                 T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StartFlexSwdVS( T1_scopeFgConsts_t *pScopeConsts,
                                                   T1_eventInfo_t eventInfo,
                                                   T1_uint32_t traceTime,
                                                   T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StartStopwatch( T1_scopeFgConsts_t *pScopeConsts,
                                                   T1_eventInfo_t stpwId,
                                                   T1_uint32_t traceTime,
                                                   T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StartStopwatchVS( T1_scopeFgConsts_t *pScopeConsts,
                                                     T1_eventInfo_t stpwId,
                                                     T1_uint32_t traceTime,
                                                     T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StartTask( T1_scopeFgConsts_t *pScopeConsts,
                                              T1_eventInfo_t taskId,
                                              T1_uint32_t traceTime,
                                              T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StartTaskVS( T1_scopeFgConsts_t *pScopeConsts,
                                                T1_eventInfo_t taskId,
                                                T1_uint32_t traceTime,
                                                T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StartNoActTask( T1_scopeFgConsts_t *pScopeConsts,
                                                   T1_eventInfo_t taskId,
                                                   T1_uint32_t traceTime,
                                                   T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StartNoActTaskVS( T1_scopeFgConsts_t *pScopeConsts,
                                                     T1_eventInfo_t taskId,
                                                     T1_uint32_t traceTime,
                                                     T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StartNoIptTask( T1_scopeFgConsts_t *pScopeConsts,
                                                   T1_eventInfo_t taskId,
                                                   T1_uint32_t traceTime,
                                                   T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StartNoIptTaskVS( T1_scopeFgConsts_t *pScopeConsts,
                                                     T1_eventInfo_t taskId,
                                                     T1_uint32_t traceTime,
                                                     T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StartStopNoIptTask( T1_scopeFgConsts_t *pScopeConsts,
                       T1_eventInfo_t taskId,
                       T1_uint32_t traceTime,
                       T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StartStopNoIptTaskVS( T1_scopeFgConsts_t *pScopeConsts,
                         T1_eventInfo_t taskId,
                         T1_uint32_t traceTime,
                         T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StopFlexStopwatch( T1_scopeFgConsts_t *pScopeConsts,
                      T1_eventInfo_t eventInfo,
                      T1_uint32_t traceTime,
                      T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StopFlexStopwatchVS( T1_scopeFgConsts_t *pScopeConsts,
                        T1_eventInfo_t eventInfo,
                        T1_uint32_t traceTime,
                        T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StopFlexSwd( T1_scopeFgConsts_t *pScopeConsts,
                                                T1_eventInfo_t eventInfo,
                                                T1_uint32_t traceTime,
                                                T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StopFlexSwdSyncIsTraceTimer( T1_scopeFgConsts_t *pScopeConsts,
                                T1_eventInfo_t eventInfo,
                                T1_uint32_t traceTime,
                                T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StopFlexSwdVS( T1_scopeFgConsts_t *pScopeConsts,
                                                  T1_eventInfo_t eventInfo,
                                                  T1_uint32_t traceTime,
                                                  T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StopStartIncFlexStopwatch( T1_scopeFgConsts_t *pScopeConsts,
                              T1_eventInfo_t eventInfo,
                              T1_uint32_t traceTime,
                              T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StopStartIncFlexStopwatchVS( T1_scopeFgConsts_t *pScopeConsts,
                                T1_eventInfo_t eventInfo,
                                T1_uint32_t traceTime,
                                T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StopStartIncStopwatch( T1_scopeFgConsts_t *pScopeConsts,
                          T1_eventInfo_t stpwId,
                          T1_uint32_t traceTime,
                          T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StopStartIncStopwatchVS( T1_scopeFgConsts_t *pScopeConsts,
                            T1_eventInfo_t stpwId,
                            T1_uint32_t traceTime,
                            T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StopStartStopwatch( T1_scopeFgConsts_t *pScopeConsts,
                       T1_eventInfo_t stpwId,
                       T1_uint32_t traceTime,
                       T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StopStartStopwatchVS( T1_scopeFgConsts_t *pScopeConsts,
                         T1_eventInfo_t stpwId,
                         T1_uint32_t traceTime,
                         T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StopStartTask( T1_scopeFgConsts_t *pScopeConsts,
                                                  T1_eventInfo_t startTaskId,
                                                  T1_uint32_t traceTime,
                                                  T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StopStartTaskVS( T1_scopeFgConsts_t *pScopeConsts,
                                                    T1_eventInfo_t startTaskId,
                                                    T1_uint32_t traceTime,
                                                    T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StopStartNoActTask( T1_scopeFgConsts_t *pScopeConsts,
                       T1_eventInfo_t startTaskId,
                       T1_uint32_t traceTime,
                       T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StopStartNoActTaskVS( T1_scopeFgConsts_t *pScopeConsts,
                         T1_eventInfo_t startTaskId,
                         T1_uint32_t traceTime,
                         T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StopStartNoIptTask( T1_scopeFgConsts_t *pScopeConsts,
                       T1_eventInfo_t startTaskId,
                       T1_uint32_t traceTime,
                       T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_StopStartNoIptTaskVS( T1_scopeFgConsts_t *pScopeConsts,
                         T1_eventInfo_t startTaskId,
                         T1_uint32_t traceTime,
                         T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StopStopwatch( T1_scopeFgConsts_t *pScopeConsts,
                                                  T1_eventInfo_t stpwId,
                                                  T1_uint32_t traceTime,
                                                  T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StopStopwatchVS( T1_scopeFgConsts_t *pScopeConsts,
                                                    T1_eventInfo_t stpwId,
                                                    T1_uint32_t traceTime,
                                                    T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StopTask( T1_scopeFgConsts_t *pScopeConsts,
                                             T1_eventInfo_t taskId,
                                             T1_uint32_t traceTime,
                                             T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_StopTaskVS( T1_scopeFgConsts_t *pScopeConsts,
                                               T1_eventInfo_t taskId,
                                               T1_uint32_t traceTime,
                                               T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_WaitTask( T1_scopeFgConsts_t *pScopeConsts,
                                             T1_eventInfo_t taskId,
                                             T1_uint32_t traceTime,
                                             T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE T1_WaitTaskVS( T1_scopeFgConsts_t *pScopeConsts,
                                               T1_eventInfo_t taskId,
                                               T1_uint32_t traceTime,
                                               T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_CalibStartStopwatch( T1_scopeFgConsts_t *pScopeConsts,
                        T1_eventInfo_t stpwId,
                        T1_uint32_t traceTime,
                        T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_CalibStopStartStopwatch( T1_scopeFgConsts_t *pScopeConsts,
                            T1_eventInfo_t stpwId,
                            T1_uint32_t traceTime,
                            T1_uint32_t syncTime );
T1_EXTERN T1_tickUint_t T1_CODE
T1_CalibStopStopwatch( T1_scopeFgConsts_t *pScopeConsts,
                       T1_eventInfo_t stpwId,
                       T1_uint32_t traceTime,
                       T1_uint32_t syncTime );
T1_EXTERN void T1_NOINLINE T1_CODE T1_FgDoVStpw8( T1_scopeFgConsts_t *pScopeConsts,
                                                  T1_uint16_t eventInfo,
                                                  T1_uint32_t traceTime,
                                                  T1_vStpwMapping_t const *vStpws );
T1_EXTERN void T1_CODE T1_FgDoVStpw64( T1_scopeFgConsts_t *pScopeConsts,
                                       T1_uint16_t eventInfo,
                                       T1_uint32_t traceTime,
                                       T1_vStpwMapping_t const *vStpws );
T1_EXTERN T1_char_t const T1_FARPTR T1_CODE T1_GetTaskName( T1_taskId_t taskId );
T1_EXTERN void T1_CODE T1_InitNameBufferNoSuspPC( T1_uint8Least_t coreId );
T1_EXTERN T1_uint8_t T1_FARPTR T1_CODE T1_GetNameBufferPC( T1_uint8Least_t coreId );
T1_EXTERN void *T1_CODE T1_InitTaskIdListPC( T1_uint8Least_t coreId );
T1_EXTERN T1_taskId_t T1_CODE T1_GetNextTaskId( void *pHandle );
T1_EXTERN T1_status_t T1_CODE T1_RewindTaskId( void *pHandle );
T1_EXTERN T1_uint8Least_t T1_CODE T1_GetTaskOsIds( T1_taskId_t taskId,
                                                   T1_uint32_t const **ppOsIds );
T1_EXTERN void T1_CODE T1_TraceScopeUploadNoSuspTimeIntern(
    T1_scopeFgConsts_t *pScopeConsts, T1_eventInfo_t eventInfo, T1_tickUint_t now );
T1_EXTERN T1_scopeConsts_t *T1_CODE T1_GetSpinlockPC( T1_uint8Least_t coreId,
                                                      T1_bakery_t *pSem,
                                                      T1_uint8Least_t semId,
                                                      T1_uint8Least_t nOfSemIds,
                                                      T1_bool_t isPrivNoSusp );
T1_EXTERN void T1_CODE T1_ReleaseSpinlockPC( T1_uint8Least_t coreId,
                                             T1_bakery_t *pSem,
                                             T1_uint8Least_t semId,
                                             T1_bool_t isPrivNoSusp );

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for user functions --------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*!
 * \brief   Callout to obtain the current trace timer value, with at least 16 counting
 *          bits.
 * \ingroup T1_scope_callouts
 * \returns the trace timer count register
 *
 * There is no need to mask off any non-counting bits.
 * It is not time-critical and does not need to be safe to call from user mode.
 *
 */
T1_EXTERN T1_tickUint_t T1_CODE T1_GetTraceTime( void );

/*!
 * \brief   Callout to obtain the current trace timer value, with at least 16 counting
 *          bits.
 * \ingroup T1_scope_callouts
 * \returns the trace timer count register
 *
 * It is not time-critical but does **need to be safe to call from user mode**.
 * There is no need to mask off any non-counting bits.
 *
 */
T1_EXTERN T1_tickUint_t T1_CODE T1_GetTraceTimeUM( void );

/*!
 * \brief   Callout to obtain the synchronization trace timer value and the trace
 *          timer value together.
 * \ingroup T1_scope_callouts
 * \param[in]  coreId         the T1 logical core ID of the calling core
 * \param[out] pSyncTimerBase both timer count registers
 *
 * Read them as close together as possible. Extend sync timer to 32 bits.
 *
 */
T1_EXTERN void T1_NOINLINE T1_CODE T1_GetTraceAndSyncTimeNoSuspPC(
    T1_uint8Least_t coreId, T1_syncTimerBase_t *pSyncTimerBase );

/*!
 * \brief   Callout to obtain the synchronization trace timer value and the trace
 *          timer value together.
 * \ingroup T1_scope_callouts
 * \param[in]  coreId         the T1 logical core ID of the calling core
 * \param[out] pSyncTimerBase both timer count registers
 *
 * Read them as close together as possible.
 * There is no need to mask off any non-counting bits.
 * It is not time-critical but does run with interrupts disabled. It does
 * **need to be safe to call from user mode**, if T1_Handler() runs in user mode.
 * The default implementation assumes that T1_Handler() runs in supervisor
 * mode, or that both timers can be read in user mode.
 *
 */
T1_EXTERN void T1_CODE T1_GetTraceAndSyncTimeNoSuspUMPC(
    T1_uint8Least_t coreId, T1_syncTimerBase_t *pSyncTimerBase );
#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

#define T1_START_SEC_CODE_FAST
#include "T1_MemMap.h"
/*!
 * \brief   Callout to translate a duration in trace timer ticks to synchronization
 *          timer ticks.
 * \ingroup T1_scope_callouts
 *
 * \note This callout function is generated into T1_configGen.c.
 *
 */
T1_EXTERN T1_CODE_FAST( T1_uint32_t )
    T1_TraceToSyncTimerPC( T1_uint8Least_t coreId, T1_tickUint_t traceTime );
#if defined T1_NEAR_CODE_FAST
T1_EXTERN T1_tickUint_t T1_NOINLINE T1_NEAR_CODE_FAST
T1_NearTraceToSyncTimerPC( T1_uint8Least_t coreId, T1_tickUint_t traceTime );
#elif defined T1_GCC_ADAPT
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
T1_NOINLINE T1_NearTraceToSyncTimerPC( T1_uint8Least_t coreId,
                                       T1_tickUint_t traceTime );
#    define T1_TraceToSyncTimerPC T1_NearTraceToSyncTimerPC
#else
#    define T1_NearTraceToSyncTimerPC T1_TraceToSyncTimerPC
#endif /* defined T1_NEAR_CODE_FAST */

/*!
 * \internal
 * \brief Handle flex stopwatch start
 */
T1_EXTERN T1_CODE_FAST( T1_tickUint_t )
    T1_StartFlexStopwatch( T1_scopeFgConsts_t *pScopeConsts,
                           T1_eventInfo_t eventInfo,
                           T1_uint32_t traceTime,
                           T1_uint32_t syncTime );

#define T1_STOP_SEC_CODE_FAST
#include "T1_MemMap.h"

/**@}*/

/*----------------------------------------------------------------------------------*/
/*--- documentation ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_DOXYGEN_ONLY
/* clang-format off */

/*!
 * \brief Internal macro switch enables required adaptation for certain compilers
 * without GCC alias and far code support.
 */
#define T1_GCC_ADAPT    (1)

/*! \brief Disable #T1_GCC_ADAPT for testing. */
#define T1_NO_GCC_ADAPT (1)

/*!
 * \page T1_scope_page T1.scope
 *
 * T1.scope is a plugin of T1 that is used for in depth analysis of the timing behavior
 * of an application. T1.scope as part of the T1-TARGET-SW is responsible for
 * instrumenting the application and recording traces. These can then be analyzed
 * on the target using [T1.cont](@ref T1_cont_page) or offline using the T1-HOST-SW.
 *
 * - \subpage RUNNABLES
 * - \subpage USER_DATA_EVENTS
 * - \subpage USER_EVENTS
 * - \subpage USER_STOPWATCHES
 * - \subpage USER_TRIGGERS
 * - \subpage DEBUGGER_DOWNLOAD
 *
 */

/*! \page USER_EVENTS User Events

\tableofcontents{HTML:2}

T1 user events can be inserted anywhere in the application to observe specific
events, log data in the T1.scope trace and/or be used to configure virtual
stopwatches with the T1-HOST-SW.

Declaration {#USER_EVENTS_DECLARATION}
===========

Invocation File Method {#USER_EVENTS_DECLARATION_INV}
----------------------

User events can be configured using the parameter [-allocateUE](\ref allocateUE)
in order for the T1-HOST-SW to display them correctly.

### Basic Example ### {#USER_EVENTS_DECLARATION_INV_BASIC_EXAMPLE}

Example configuration:

~~~~~~~~~~~~~~~{.unparsed}
#system all:
; Allocate user events for all cores
-allocateUE=T1_UE_T1_CONT_ERR_CORE0,        "T1.cont error callback for core 0"
-allocateUE=T1_UE_T1_CONT_ERR_CORE1,        "T1.cont error callback for core 1"
-allocateUE=T1_UE_T1_CONT_ERR_CORE2,        "T1.cont error callback for core 2"
-allocateUE=T1_UE_T1_CONT_ERR_CORE3,        "T1.cont error callback for core 3"
-allocateUE=T1_UE_T1_CONT_ERR_CORE4,        "T1.cont error callback for core 4"
-allocateUE=T1_UE_T1_CONT_ERR_CORE5,        "T1.cont error callback for core 5"

-allocateUE=T1_UE_CPU_LOAD_CALLBACK_CORE0,  "T1.cont CPU load callback for core 0"
-allocateUE=T1_UE_CPU_LOAD_CALLBACK_CORE1,  "T1.cont CPU load callback for core 1"
-allocateUE=T1_UE_CPU_LOAD_CALLBACK_CORE2,  "T1.cont CPU load callback for core 2"
-allocateUE=T1_UE_CPU_LOAD_CALLBACK_CORE3,  "T1.cont CPU load callback for core 3"
-allocateUE=T1_UE_CPU_LOAD_CALLBACK_CORE4,  "T1.cont CPU load callback for core 4"
-allocateUE=T1_UE_CPU_LOAD_CALLBACK_CORE5,  "T1.cont CPU load callback for core 5"
~~~~~~~~~~~~~~~

This will create the following macros into *T1_config.h*:

~~~~~~~~~~~~~~~{.h}
...*/

/*----------------------------------------------------------------------------------*/
/*--- User Data Event and User Event IDs -------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/* User Events for all cores */
#define T1_UE_T1_CONT_ERR_CORE0                       (32u) /*!< T1.cont error callback for core 0 */
#define T1_UE_T1_CONT_ERR_CORE1                       (33u) /*!< T1.cont error callback for core 1 */
#define T1_UE_T1_CONT_ERR_CORE2                       (34u) /*!< T1.cont error callback for core 2 */
#define T1_UE_T1_CONT_ERR_CORE3                       (35u) /*!< T1.cont error callback for core 3 */
#define T1_UE_T1_CONT_ERR_CORE4                       (36u) /*!< T1.cont error callback for core 4 */
#define T1_UE_T1_CONT_ERR_CORE5                       (37u) /*!< T1.cont error callback for core 5 */
#define T1_UE_CPU_LOAD_CALLBACK_CORE0                 (38u) /*!< T1.cont CPU load callback for core 0 */
#define T1_UE_CPU_LOAD_CALLBACK_CORE1                 (39u) /*!< T1.cont CPU load callback for core 1 */
#define T1_UE_CPU_LOAD_CALLBACK_CORE2                 (40u) /*!< T1.cont CPU load callback for core 2 */
#define T1_UE_CPU_LOAD_CALLBACK_CORE3                 (41u) /*!< T1.cont CPU load callback for core 3 */
#define T1_UE_CPU_LOAD_CALLBACK_CORE4                 (42u) /*!< T1.cont CPU load callback for core 4 */
#define T1_UE_CPU_LOAD_CALLBACK_CORE5                 (43u) /*!< T1.cont CPU load callback for core 5 */

/*...
~~~~~~~~~~~~~~~

And XML elements in the T1 project files, which are used by the T1-HOST-SW for
displaying purposes:

~~~~~~~~~~~~~~~{.xml}
<System Name="Core0" ... >
  <!-- ... -->
  <SystemElement Name="T1.cont error callback for core 0" ID="32" Type="UserEvent" />
  <SystemElement Name="T1.cont error callback for core 1" ID="33" Type="UserEvent" />
  <SystemElement Name="T1.cont error callback for core 2" ID="34" Type="UserEvent" />
  <SystemElement Name="T1.cont error callback for core 3" ID="35" Type="UserEvent" />
  <SystemElement Name="T1.cont error callback for core 4" ID="36" Type="UserEvent" />
  <SystemElement Name="T1.cont error callback for core 5" ID="37" Type="UserEvent" />
  <SystemElement Name="T1.cont CPU load callback for core 0" ID="38" Type="UserEvent" />
  <SystemElement Name="T1.cont CPU load callback for core 1" ID="39" Type="UserEvent" />
  <SystemElement Name="T1.cont CPU load callback for core 2" ID="40" Type="UserEvent" />
  <SystemElement Name="T1.cont CPU load callback for core 3" ID="41" Type="UserEvent" />
  <SystemElement Name="T1.cont CPU load callback for core 4" ID="42" Type="UserEvent" />
  <SystemElement Name="T1.cont CPU load callback for core 5" ID="43" Type="UserEvent" />
  <!-- ... -->
</System>
<System Name="Core1" ... >
  <!-- ... -->
  <SystemElement Name="T1.cont error callback for core 0" ID="32" Type="UserEvent" />
  <SystemElement Name="T1.cont error callback for core 1" ID="33" Type="UserEvent" />
  <SystemElement Name="T1.cont error callback for core 2" ID="34" Type="UserEvent" />
  <SystemElement Name="T1.cont error callback for core 3" ID="35" Type="UserEvent" />
  <SystemElement Name="T1.cont error callback for core 4" ID="36" Type="UserEvent" />
  <SystemElement Name="T1.cont error callback for core 5" ID="37" Type="UserEvent" />
  <SystemElement Name="T1.cont CPU load callback for core 0" ID="38" Type="UserEvent" />
  <SystemElement Name="T1.cont CPU load callback for core 1" ID="39" Type="UserEvent" />
  <SystemElement Name="T1.cont CPU load callback for core 2" ID="40" Type="UserEvent" />
  <SystemElement Name="T1.cont CPU load callback for core 3" ID="41" Type="UserEvent" />
  <SystemElement Name="T1.cont CPU load callback for core 4" ID="42" Type="UserEvent" />
  <SystemElement Name="T1.cont CPU load callback for core 5" ID="43" Type="UserEvent" />
  <!-- ... -->
</System>
~~~~~~~~~~~~~~~

### Advanced Example

It is possible to define the meaning of each value, which will be observed by user events.
The additional information must be defined with the paramater [-keyValueMapUE](@ref keyValueMapUE).
In this case the defined names will be shown instead of the values in the T1.scope view.

~~~~~~~~~~~~~~~
#system 0:
; Allocate user events for core 0 only
-allocateUE=CONT_ERR,    "T1.cont error callback for core 0"
-keyValueMapUE=CONT_ERR, 0x01, "INF: Overheads calibrated"
-keyValueMapUE=CONT_ERR, 0x02, "WRN: Analysis incomplete"
-keyValueMapUE=CONT_ERR, 0x03, "WRN: Analysis incomplete&#xD;&#xA;INF: Overheads calibrated"
; ...
-keyValueMapUE=CONT_ERR, 0xFE, "ERR: Overrun&#xD;&#xA;ERR: Stack overflow&#xD;&#xA;ERR: Faulty trace&#xD;&#xA;WRN: Out of range&#xD;&#xA;WRN: Invalid CET stpw&#xD;&#xA;WRN: Constraint violated&#xD;&#xA;WRN: Analysis incomplete"
-keyValueMapUE=CONT_ERR, 0xFF, "ERR: Overrun&#xD;&#xA;ERR: Stack overflow&#xD;&#xA;ERR: Faulty trace&#xD;&#xA;WRN: Out of range&#xD;&#xA;WRN: Invalid CET stpw&#xD;&#xA;WRN: Constraint violated&#xD;&#xA;WRN: Analysis incomplete&#xD;&#xA;INF: Overheads calibrated"
~~~~~~~~~~~~~~~

This will produce the same macro as shown in the \ref USER_EVENTS_DECLARATION_INV_BASIC_EXAMPLE,
but the T1 project file will change accordingly:

~~~~~~~~~~~~~~~{.xml}
<System Name="Core0" ... >
  <!-- ... -->
  <SystemElement Name="T1.cont error callback for core 0" ID="32" Type="UserEvent">
    <Info InfoStr="INF: Overheads calibrated" Index="0x01" />
    <Info InfoStr="WRN: Analysis incomplete" Index="0x02" />
    <Info InfoStr="WRN: Analysis incomplete&#xD;&#xA;INF: Overheads calibrated" Index="0x03" />
    <!-- ... -->
    <Info InfoStr="ERR: Overrun&#xD;&#xA;ERR: Stack overflow&#xD;&#xA;ERR: Faulty trace&#xD;&#xA;WRN: Out of range&#xD;&#xA;WRN: Invalid CET stpw&#xD;&#xA;WRN: Constraint violated&#xD;&#xA;WRN: Analysis incomplete" Index="0xFE" />
    <Info InfoStr="ERR: Overrun&#xD;&#xA;ERR: Stack overflow&#xD;&#xA;ERR: Faulty trace&#xD;&#xA;WRN: Out of range&#xD;&#xA;WRN: Invalid CET stpw&#xD;&#xA;WRN: Constraint violated&#xD;&#xA;WRN: Analysis incomplete&#xD;&#xA;INF: Overheads calibrated" Index="0xFF" />
  </SystemElement>
  <!-- ... -->
</System>
~~~~~~~~~~~~~~~

Inline XML Method (legacy) {#USER_EVENTS_DECLARATION_XML}
--------------------------

The user event must be declared in *T1_AppInterface.h* in order to get recognized
in the T1-HOST-SW when a trace is downloaded.

### Basic Example

~~~~~~~~~~~~~~~{.c}
...*/

/* @T1@ <SystemElement Name="OS Error" Type="UserEvent"> */
#define T1_OS_ERROR (0x21)
/* @T1@ </SystemElement> */

/*...
~~~~~~~~~~~~~~~
The inline XML syntax in the C comments must be exactly as in the example above,
because these are parsed also by the T1-HOST-SW:
- The body of the macro determines the user event identifier and has to be in the
  range 0x20 to 0x3F (32 to 63) and different from all other user event identifiers.
- The "Name" field is configurable and can be changed by the user.

### Advanced Example

It is possible to define the meaning of each value, which will be observed by
user events. The additional information must be defined such as the following code.
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

Trace User Events {#TRACE_USER_EVENTS}
=================

After the ID has been declared following \ref USER_EVENTS_DECLARATION, it can be
traced anywhere in the application in order to show the current value of a interesting
variable in the trace using T1_TraceEvent().

Only 10 bits of data are traced with a user event, so the result is transferred
modulo 1024. If a variable out of this range need to be observed, please see
\ref USER_DATA_EVENTS.

The following code shows an example of tracing a user event:

~~~~~~~~~~~~~~~{.c}
...*/

void T1_CODE
T1_ContErrCallbackPC(   T1_uint8Least_t coreId,
                        T1_uint8Least_t errMask,
                        T1_uint8Least_t triggerMask,
                        T1_nOfEntries_t afterXevnts )
{
    (void)coreId;    /* Suppress warnings if T1_CONT_RC_UNMAP does not use coreId */
    INC_T1_ERROR_COUNT( coreId );
#       if 1 == T1_NOF_CORES
    T1_TraceEventUMPC( 0u, T1_COMBINE_EVENT_INFO( T1_UE_T1_CONT_ERR_CORE0, errMask ) );
#       else /* 1 < T1_NOF_CORES */
    T1_TraceEventUMPC(  T1_CONT_RC_UNMAP( coreId ),
                        T1_COMBINE_EVENT_INFO( T1_UE_T1_CONT_ERR_CORE0 + coreId,
                                               errMask ) );
#       endif /* 1 == T1_NOF_CORES */
    if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRIGGER ) && (0 != (errMask & triggerMask)) )
    {
        T1_AppSetStopTriggerAllCores( T1_CONT_RC_UNMAP( coreId ), afterXevnts );
    }
}

/*...
~~~~~~~~~~~~~~~

*/

/*! \page USER_DATA_EVENTS User Data Events

\tableofcontents{HTML:2}

T1 user data events (UDE) can be inserted anywhere in the application. In comparison with
user event (UE), user data event can provide more ways to observe specific events or
to log data. For example, `printf` can be mapped on to a T1 user data event so that
string data is captured in the trace. Besides, not like user event, user data event
can log any 16 bit or 32 bit variable, even an array or struct.

Declaration {#USER_DATA_EVENTS_DECLARATION}
===========

Invocation File Method {#USER_DATA_EVENTS_DECLARATION_INV}
----------------------

User data events can be configured using the parameter [-allocateUDE](\ref allocateUDE)
in order for the T1-HOST-SW to display them correctly.

Example configuration:

~~~~~~~~~~~~~~~
; Allocate user data events for all cores
-allocateUDE=PRINTF,         "printf string"
-allocateUDE=16BitDataTrace, "16 bit Data tracing"
-allocateUDE=32BitDataTrace, "32 bit Data tracing"
-allocateUDE=BinaryTrace,    "Binary Data tracing"
~~~~~~~~~~~~~~~

This will create the following macros into *T1_config.h*:

~~~~~~~~~~~~~~~{.c}
... */

/*----------------------------------------------------------------------------------*/
/*--- User Data Event and User Event IDs -------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/* User Events for all cores */
#define T1_UDE_PRINTF_CORE_ALL                        (0u) /*!< printf string */
#define T1_UDE_16BitDataTrace_CORE_ALL                (1u) /*!< 16 bit Data tracing */
#define T1_UDE_32BitDataTrace_CORE_ALL                (2u) /*!< 32 bit Data tracing */
#define T1_UDE_BinaryTrace_CORE_ALL                   (3u) /*!< Binary Data tracing */

/* User Events for core 0 */
#define T1_UDE_PRINTF_CORE0                           (T1_UDE_PRINTF_CORE_ALL) /*!< printf string */
#define T1_UDE_16BitDataTrace_CORE0                   (T1_UDE_16BitDataTrace_CORE_ALL) /*!< 16 bit Data tracing */
#define T1_UDE_32BitDataTrace_CORE0                   (T1_UDE_32BitDataTrace_CORE_ALL) /*!< 32 bit Data tracing */
#define T1_UDE_BinaryTrace_CORE0                      (T1_UDE_BinaryTrace_CORE_ALL) /*!< Binary Data tracing */

/* User Events for core 1 */
#define T1_UDE_PRINTF_CORE1                           (T1_UDE_PRINTF_CORE_ALL) /*!< printf string */
#define T1_UDE_16BitDataTrace_CORE1                   (T1_UDE_16BitDataTrace_CORE_ALL) /*!< 16 bit Data tracing */
#define T1_UDE_32BitDataTrace_CORE1                   (T1_UDE_32BitDataTrace_CORE_ALL) /*!< 32 bit Data tracing */
#define T1_UDE_BinaryTrace_CORE1                      (T1_UDE_BinaryTrace_CORE_ALL) /*!< Binary Data tracing */

/* ...
~~~~~~~~~~~~~~~

And XML elements in the T1 project files, which are used by the T1-HOST-SW for
displaying purposes:

~~~~~~~~~~~~~~~{.xml}
<System Name="Core0" ... >
  <!-- ... -->
  <SystemElement Name="printf string" ID="0" Type="UserEvent" />
  <SystemElement Name="16 bit Data tracing" ID="1" Type="UserEvent" />
  <SystemElement Name="32 bit Data tracing" ID="2" Type="UserEvent" />
  <SystemElement Name="Binary Data tracing" ID="3" Type="UserEvent" />
  <!-- ... -->
</System>
<System Name="Core1" ... >
  <!-- ... -->
  <SystemElement Name="printf string" ID="0" Type="UserEvent" />
  <SystemElement Name="16 bit Data tracing" ID="1" Type="UserEvent" />
  <SystemElement Name="32 bit Data tracing" ID="2" Type="UserEvent" />
  <SystemElement Name="Binary Data tracing" ID="3" Type="UserEvent" />
  <!-- ... -->
</System>
~~~~~~~~~~~~~~~



Inline XML Method (legacy) {#USER_DATA_EVENTS_DECLARATION_XML}
--------------------------

Like user event, the user data event must also be declared in T1_AppInterface.h in
order for the T1-HOST-SW to interpret the event in a downloaded trace.

~~~~~~~~~~~~~~~{.c}
...*/

/* @T1@ <SystemElement Name="printf string" Type="UserEvent"> */
#define T1_UDE_PRINTF_CORE_ALL          0x00
/* @T1@ </SystemElement> */

/* @T1@ <SystemElement Name="16 bit Data tracing" Type="UserEvent"> */
#define T1_UDE_16BitDataTrace_CORE_ALL  0x01
/* @T1@ </SystemElement> */

/* @T1@ <SystemElement Name="32 bit Data tracing" Type="UserEvent"> */
#define T1_UDE_32BitDataTrace_CORE_ALL  0x02
/* @T1@ </SystemElement> */

/* @T1@ <SystemElement Name="Binary Data tracing" Type="UserEvent"> */
#define T1_UDE_BinaryTrace_CORE_ALL     0x03
/* @T1@ </SystemElement> */

/*...
~~~~~~~~~~~~~~~

The inline XML syntax in the C comments must be exactly as in the example above,
because these are parsed also by the T1-HOST-SW:
- The body of the macro determines the user data event identifier and has to be in
  the range 0x00 to 0x1F (0 to 31) and different from all other user data event
  identifiers.
- The "Name" field is configurable and can be changed by the user.

Trace User Data Events {#USER_DATA_EVENTS_TRACE}
======================

Trace String {#USER_DATA_EVENTS_TRACE_STRING}
------------

String can be traced using `T1_TraceString()` or its variants, see \ref PC and
\ref INTRPT.

The following example implementation of `fputc` redirects a typical embedded `printf`
function to generate T1 user data events.

~~~~~~~~~~~~~~~{.c}
...*/

int fputc( int c, FILE* ignored )
{
    static T1_uint8_t buff[20];
    static T1_uint8Least_t buffIdx = 0u;
    if( (c == '\n') || (c == EOF) || (buffIdx == 20u) )
    {
        if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRACEDATA ) )
        {
            T1_TraceString( T1_UDE_PRINTF_CORE_ALL, buff, buffIdx );
        }
        buffIdx = 0u;
    }
    else
    {
        buff[buffIdx++] = (T1_uint8_t)c;
    }
    return c;
}

/*...
~~~~~~~~~~~~~~~

Trace Integer {#USER_DATA_EVENTS_TRACE_INT}
-------------

Signed and unsigned integer can be traced using `T1_TraceUint16()`, `T1_TraceUint32()`,
`T1_TraceSint16()`, `T1_TraceSint32()` or their variants, see \ref PC and \ref INTRPT.

For example, the following implementation of `5msTask` observes the variable "counter":

~~~~~~~~~~~~~~~{.c}
... */

void 5msTask( void )
{
    static T1_uint16_t counter = 0;
    /* ... */
    ++counter;
    if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRACEDATA ) )
    {
        T1_TraceUint16( T1_UDE_16BitDataTrace_CORE_ALL, counter );
    }
    /* ... */
}

/* ...
~~~~~~~~~~~~~~~

Trace Binary {#USER_DATA_EVENTS_TRACE_BIN}
------------
Structure or array can be traced using `T1_TraceBinary()` or its variants, see \ref PC
and \ref INTRPT.

For example, the following implementation of `5msTask` observes the array `array1`:

~~~~~~~~~~~~~~~{.c}
... */

void 5msTask( void )
{
    static T1_uint16_t array1[20];
    /* ... */
    if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRACEDATA ) )
    {
        T1_TraceBinary( T1_UDE_BinaryTrace_CORE_ALL, array1, sizeof(array1) );
    }
    /* ... */
}

/* ...
~~~~~~~~~~~~~~~

Trace Address {#USER_DATA_EVENTS_TRACE_PTR}
-------------
The value of a 32-bit address can be traced using `T1_TraceAddr()` or its variants,
see \ref PC and \ref INTRPT.

Note on User Data Event {#USER_DATA_EVENTS_NOTE}
-----------------------

Tracing a variable using a user data event must not be done while measuring this
variable with a T1.flex data measurement. The T1.flex data measurement result would
include the additional read access performed to trace the variable in a user data
event, concealing the real result.
To support this, user data events tracing should be guarded by an application
feature. During a T1.flex data measurement, the application feature
(see \ref APP_FEATURES) must be disabled:

~~~~~~~~~~~~~~~{.c}
... */

if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRACEDATA ) )
{
    T1_TraceUint32( T1_UDE_32BitDataTrace_CORE_ALL, tmp );
}

/* ...
~~~~~~~~~~~~~~~

Additionally, the T1 API reads data one byte at a time, variables updated by
peripherals or other cores potentially could be traced incorrectly, with one byte
coming from an old value and another byte coming from a newer value.
In this case, the data should be atomically copied to an auto variable before being
traced. If the variable read is not inherently atomic then some other mechanism must
be used to protect against inconsistency
In the following example `u32value` is 32-bit aligned in the memory of a TriCore
processor, so the read is inherently atomic:
~~~~~~~~~~~~~~~{.c}
...*/

if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRACEDATA ) )
{
    const T1_uint32_t tmp = u32value;/* Atomic read */
    T1_TraceUint32( T1_UDE_32BitDataTrace_CORE_ALL, tmp );
}

/*...
~~~~~~~~~~~~~~~

Advanced Tracing {#USER_DATA_EVENTS_TRACE_ADVANCED}
----------------

For less commonly used data type, such as a 64 bits variable or float variable,
please contact \ref SUPPORT for assistance.

 */

/*! \page USER_STOPWATCHES User Stopwatches

\tableofcontents{HTML:2}

T1 stopwatches can be used in order to statically instrument any code
fragment to either determine its core execution time or gross execution time via
T1.scope and T1.cont and also allowing it to be supervised by T1.cont.
It can also be used to determine data-age, the minimum and maximum
time between a write access and the consecutive read accesses.

Declaration {#USER_STOPWATCHES_DECLARATION}
===========

Invocation File Method {#USER_STOPWATCHES_DECLARATION_INV}
----------------------

User stopwatches can be configured using the parameter [-allocateUserSW](\ref allocateUserSW)
in order for the T1-HOST-SW to display them correctly.

Example configuration:

~~~~~~~~~~~~~~~
#system all:
; Allocate user stopwatches for all cores
-allocateUserSW=CHECK_INTEGRATION, "T1 Check Integration", DEFAULT

#system 0:
; Allocate user stopwatches for core 0 only
-allocateUserSW=DATA_AGE_V_VEH, "V_Veh data age", DA
~~~~~~~~~~~~~~~

This will create the following macros into *T1_config.h*:

~~~~~~~~~~~~~~~{.h}
...*/

/*----------------------------------------------------------------------------------*/
/*--- User Stopwatch IDs -----------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/* User stopwatches for all cores */
/* The following user stopwatches are supervised by T1.cont */
#define T1_SW_CHECK_INTEGRATION_CORE_ALL              (   0u) /*!< T1 Check Integration */

/* User stopwatches for core 0 */
/* The following user stopwatches are supervised by T1.cont */
#define T1_SW_CHECK_INTEGRATION_CORE0                 (T1_SW_CHECK_INTEGRATION_CORE_ALL) /*!< T1 Check Integration */
#define T1_SW_DATA_AGE_V_VEH_CORE0                    (   1u) /*!< V_Veh data age */

/* User stopwatches for core 1 */
/* The following user stopwatches are supervised by T1.cont */
#define T1_SW_CHECK_INTEGRATION_CORE1                 (T1_SW_CHECK_INTEGRATION_CORE_ALL) /*!< T1 Check Integration */

/*...*/

/*!
 * \brief Defines the number of user stopwatches for system 0.
 */
#define T1_NOF_USER_STPWS_CORE0                       (2u)

/*...*/

/*!
 * \brief Defines the number of user stopwatches for system 1.
 */
#define T1_NOF_USER_STPWS_CORE1                       (1u)

/*...
~~~~~~~~~~~~~~~

And arrays were the configuration is copied from into *T1_configGen.c*:

~~~~~~~~~~~~~~~{.c}
...*/

#   if defined T1_CONT_DEFAULT_CONFIG_STOPWATCH
#       define T1_START_SEC_CONST_8
#       include "T1_MemMap.h"
#       if 2 != T1_NOF_USER_STPWS_CORE0
#           error T1_NOF_USER_STPWS_CORE0 does not match generated configuration
#       endif /* 2 != T1_NOF_USER_STPWS_CORE0 */
static T1_stpwConfig_t  T1_SEC_CONST_8 T1_stpwConfig0[2] =
{
    T1_CONT_DEFAULT_CONFIG_STOPWATCH( T1_SW_CHECK_INTEGRATION_CORE0 ), /* T1 Check Integration */
    T1_CONT_DATA_AGE_STOPWATCH(       T1_SW_DATA_AGE_V_VEH_CORE0 ), /* V_Veh data age */
};
#       if 1 != T1_NOF_USER_STPWS_CORE1
#           error T1_NOF_USER_STPWS_CORE1 does not match generated configuration
#       endif /* 1 != T1_NOF_USER_STPWS_CORE1 */
static T1_stpwConfig_t  T1_SEC_CONST_8 T1_stpwConfig1[1] =
{
    T1_CONT_DEFAULT_CONFIG_STOPWATCH( T1_SW_CHECK_INTEGRATION_CORE1 ), /* T1 Check Integration */
};
#       define T1_STOP_SEC_CONST_8
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_stpwConfig_t * const T1_SEC_CONST_32 T1_stpwConfigPC[2] =
{
    T1_stpwConfig0,
    T1_stpwConfig1
};
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#   endif /* defined T1_CONT_DEFAULT_CONFIG_STOPWATCH */

/*...
~~~~~~~~~~~~~~~

And XML elements in the T1 project files, which are used by the T1-HOST-SW for
displaying purposes:

~~~~~~~~~~~~~~~{.xml}
<System Name="Core0" ... >
  <!-- ... -->
  <SystemElement Name="T1 Check Integration" ID="0" Type="Stopwatch" />
  <SystemElement Name="V_Veh data age" ID="1" Type="Stopwatch" IsDataflow="true" />
  <!-- ... -->
</System>
<System Name="Core1" ... >
  <!-- ... -->
  <SystemElement Name="T1 Check Integration" ID="0" Type="Stopwatch" />
  <!-- ... -->
</System>
~~~~~~~~~~~~~~~

Inline XML Method (legacy) {#USER_STOPWATCHES_DECLARATION_XML}
--------------------------

In order to expose the ID of a stopwatch to the T1-HOST-SW as well as to the
T1-TARGET-SW the following definition including the inline XML syntax is to be used
in T1_AppInterface.h for any stopwatch assigned in the project:
~~~~~~~~~~~~~~~{.c}
...*/

/* @T1@ <SystemElement Name="T1 Check Integration" Type="Stopwatch"> */
#define T1_SW_CHECK_INTEGRATION_CORE_ALL    0u
/* @T1@ </SystemElement > */

/* @T1@ <SystemElement Name="V_Veh data age" Type="Stopwatch" IsDataflow="true" SID="2"> */
#define T1_SW_DATA_AGE_V_VEH_CORE0          1u
/* @T1@ </SystemElement > */

/*...
~~~~~~~~~~~~~~~

The inline XML syntax in the C comments must be exactly as in the example above,
because these are parsed also by the T1-HOST-SW:
- The body of the macro determines the stopwatch identifier and has to be in the range
  0x0 to 0x2FC (0 to 764) and different from all other stopwatch identifiers used on
  this core.
- The "Name" field is configurable and can be changed by the user.
- The "SID" field is the system identifier of the core, it is usually the core id
  incremented by 2, if all cores are used and no shifting occurs. The value is
  specified via the parameter -sid in T1_Cfg.inv per system. If no "SID" is given,
  the stopwatch is added to all cores, and it must be ensured that the number of
  stopwatches on each core is adjusted to accommodate the given stopwatch ID, in
  order that T1.cont can supervise its results.
- The field "IsDataflow" can be set, as shown in the second example, to select data
  flow visualization in downloaded traces.

Additionally, the number of user stopwatches per core must be defined. It can be done
either by adding the parameter -numberOfUserStpws per system in T1_UserCfg.inv or by
adding the macro T1_NOF_USER_STPWS_CORE<coreID> in T1_AppInterface.h, in the previous
example T1_NOF_USER_STPWS_CORE0 would be 2 and T1_NOF_USER_STPWS_CORE1 would be 1.
Please note that if the macro and the parameter are both present, but with different
values, an error will be generated during the generation.
Please note that this macro controls how many user stopwatches are analyzed by
T1.cont. The max number of stopwatches analyzed by T1.cont per core is 255.
User stopwatches with an identifier larger or equal to T1_NOF_USER_STPWS_CORE<coreID>
can still be used with T1.scope, but are not analyzed by T1.cont.

### Default Configuration {#USER_STOPWATCHES_DEFAULT_CONFIG}

According to its ID, each stopwatch is initialized to record a CET, GET or data
age time.

A default configuration is generated that is active if the macro
#T1_CONT_DEFAULT_CONFIG_STOPWATCH is defined. This is particularly useful
when using large numbers of user stopwatches, as the manual configuration:
- is time-consuming and potentially error-prone
- needs to be maintained consistent with the number of configured user stopwatches
  for T1.cont to observe.

This default configuration is generated in T1_configGen.c, here is an example with
two cores:
~~~~~~~~~~~~~~~{.c}
...*/

#   if defined T1_CONT_DEFAULT_CONFIG_STOPWATCH
#       define T1_START_SEC_CONST_8
#       include "T1_MemMap.h"
T1_stpwConfig_t         T1_SEC_CONST_8 T1_stpwConfig0[1] =
{
    T1_CONT_DEFAULT_CONFIG_STOPWATCH( 0u )
};
T1_stpwConfig_t         T1_SEC_CONST_8 T1_stpwConfig1[1] =
{
    T1_CONT_DEFAULT_CONFIG_STOPWATCH( 0u )
};
#       define T1_STOP_SEC_CONST_8
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_stpwConfig_t * const T1_SEC_CONST_32 T1_stpwConfigPC[2] =
{
    T1_stpwConfig0,
    T1_stpwConfig1
};
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#   endif /* defined T1_CONT_DEFAULT_CONFIG_STOPWATCH */

/*...
~~~~~~~~~~~~~~~

### Advanced Configuration {#USER_STOPWATCHES_ADVANCED_CONFIG}

Please see \ref USER_STOPWATCHES_DECLARATION_INV for an example how to achieve this
with invocation file parameters.

If the default configuration is not suitable, for example because we require some CET
stopwatches and some GET stopwatches, then #T1_CONT_DEFAULT_CONFIG_STOPWATCH must be
undefined and the array initializers must be adapted as needed and added into
T1_config.c. Please remember the difficulty in correctly maintaining such a manual
configuration and only use it when necessary.

The following example can be added in T1_config.c:

~~~~~~~~~~~~~~~{.c}
...*/

#       if ! defined T1_CONT_DEFAULT_CONFIG_STOPWATCH
/*
 * Advanced configuration example of user stopwatches
 * In this example, we take the default generated code from T1_configGen.c with
 * 2 cores as template and adapt it by configuring:
 * - on the first core: a CET stopwatch and a data-age stopwatch
 * - on the second core: a GET stopwatch.
 */
#           define T1_START_SEC_CONST_8
#           include "T1_MemMap.h"
T1_stpwConfig_t         T1_SEC_CONST_8 T1_stpwConfig0[2] =
{
    /* Core0 SW0: CET */
    T1_CONT_CET_STOPWATCH( T1_SW_T1_HANDLER_CORE0 ),
    /* Core0 SW1: Data age */
    T1_CONT_DATA_AGE_STOPWATCH( T1_SW_DATA_AGE_V_VEH )
};
T1_stpwConfig_t         T1_SEC_CONST_8 T1_stpwConfig1[1] =
{
    /* Core1 SW0: GET */
    T1_CONT_GET_STOPWATCH( T1_SW_INTRPT )
};
#           define T1_STOP_SEC_CONST_8
#           include "T1_MemMap.h"
#           define T1_START_SEC_CONST_32
#           include "T1_MemMap.h"
T1_stpwConfig_t * const T1_SEC_CONST_32 T1_stpwConfigPC[2] =
{
    T1_stpwConfig0,
    T1_stpwConfig1
};
#           define T1_STOP_SEC_CONST_32
#           include "T1_MemMap.h"
#       endif /* ! defined T1_CONT_DEFAULT_CONFIG_STOPWATCH */

/*...
~~~~~~~~~~~~~~~

Please note that the size of each core specific array initializer in T1_config.c must
match the number of stopwatches defined in T1_AppInterface.h.

CET And GET Stopwatches Usage {#USER_STOPWATCHES_CET_GET}
=============================

A stopwatch start event has to be traced at the beginning of the code fragment to be
measured and a stopwatch stop event has to be traced at the end:
~~~~~~~~~~~~~~~{.c}
...*/

void T1_AppHandler(void)
{
#if defined T1_ENABLE
    const T1_uint8Least_t coreId = T1_GetCoreIdOffset( );

#   if defined T1_CHECK_INTEGRATION
    /* If the application feature T1_AF_CHECK_INTEGRATION is enabled, trace the
     * static stopwatch T1_SW_CHECK_INTEGRATION_CORE_ALL which has the ID 0 by default.
     */
    if( T1_IsFeatureEnabled( T1_AF_CHECK_INTEGRATION ) )
    {
        T1_TraceEventPC( coreId, T1_STOPWATCH_START, T1_SW_CHECK_INTEGRATION_CORE_ALL );
        T1_CheckIntegrationHandlerPC( coreId );
        T1_TraceEventPC( coreId, T1_STOPWATCH_STOP, T1_SW_CHECK_INTEGRATION_CORE_ALL );
    }
#   endif /* defined T1_CHECK_INTEGRATION */
/*...*/
#endif /* defined T1_ENABLE */
/*...
~~~~~~~~~~~~~~~

Data Age Stopwatches Usage {#USER_STOPWATCHES_DATA_AGE}
==========================

Starting from a write access to a variable, data age stopwatches allow to determine
the minimum and maximum time of the consecutive read accesses in order to supervise
possible constraint violations arising from outdated data read accesses.

Please note that cross-core data-age are only possible using T1.flex with the
T1-HOST-SW.

A stopwatch start event has to be traced where any write access takes place:
~~~~~~~~~~~~~~~{.c}

void set_v_veh( uint32_t val )
{
    T1_SuspendAllInterruptsPC( 0u );
    v_veh = val;
    T1_TraceEventNoSuspPC( 0u, T1_STOPWATCH_START, T1_SW_DATA_AGE_V_VEH_CORE0 );
    T1_ResumeAllInterruptsPC( 0u );
}

~~~~~~~~~~~~~~~

A stopwatch stop has to be traced where any read access takes place:
~~~~~~~~~~~~~~~{.c}

uint32_t get_v_veh( void )
{
    uint32_t result;
    T1_SuspendAllInterruptsPC( 0u );
    result = v_veh;
    T1_TraceEventNoSuspPC( 0u, T1_STOPWATCH_STOP, T1_SW_DATA_AGE_V_VEH_CORE0 );
    T1_ResumeAllInterruptsPC( 0u );
    return result;
}

~~~~~~~~~~~~~~~

Special Note on Usage {#USER_STOPWATCHES_NOTES}
=====================

Note that interrupt locks are nearly always required for meaningful data age
stopwatches. Otherwise an interrupt, a task switch and an arbitrary amount of time can
elapse between the actual data read/write and the stopwatch event. Consider the above
example without interrupt locks, you see that you could even trace the stopwatch stop
before the stopwatch start, if an interrupt separates the write from the trace event
and that interrupt (calls code that) calls \c get_v_veh().

GET stopwatch instrumentation must be done with similar care, with regard to
preemption.

In contrast, CET stopwatches rarely need such interrupt locks because the
start and stop events occur in the same task or ISR instance and interrupting time
gets subtracted.

*/

/*!
 * \page USER_TRIGGERS User triggers

T1 user triggers can be inserted anywhere in the application to stop tracing and
ensure that specific events or sequences are captured for download and visualization.

It is possible to trigger a specific core with T1_SetStopTrigger() and
T1_SetStopTriggerPC().

T1_AppInterface.c provides a default implementation of T1_AppSetStopTriggerAllCores()
allowing to trigger all cores.

Additionally the default implementation of T1_AppInit() allows to capture the start-up
trace depending on the application feature T1_AF_TRACE_STARTUP, see \ref APP_FEATURES.

\note After the initial start-up or re-starting the tracing, an entirely new trace is
      captured regardless of the parameter "afterXevents"! Thus, more events
      than "afterXevents" may be traced after the trigger point if the trace buffer needs
      to be filled.
      In general, in a downloaded trace, the trigger might be earlier than expected.

Examples {#USER_TRIGGERS_EXAMPLES}
========

To capture a full buffer containing only events after this point in the code, we call:
~~~~~~~~~~~~~~~{.c}
(void)T1_SetStopTrigger( T1_TRACE_BUFFER_ENTRIES_PC( coreId ) );
~~~~~~~~~~~~~~~

To capture a buffer containing an equal number of events before and after this point
in the code with the T1 logical core ID, we call:
~~~~~~~~~~~~~~~{.c}
(void)T1_SetStopTriggerPC( coreId, T1_TRACE_BUFFER_ENTRIES_PC( coreId ) >> 1 );
~~~~~~~~~~~~~~~

 */

/*!
 * \page RUNNABLES Runnables
Runnables can be instrumented in the T1-TARGET-SW or by using T1.flex in the
T1-HOST-SW (see the GUI help for more information).

T1 assumes that runnables are functions with no arguments and no return value that are
called from tasks. There are two ways to do static instrumentation of runnables
depending on the way the runnables are deployed. These ways define the kind of ID
that T1 uses to trace those runnables:
- a static runnable ID can be used for runnables that are called directly,
  unconditionally and in a fixed order from a single task.
- dynamic runnable IDs must be used if the requirements for using a static runnable
  ID are not fulfilled. Typical cases are runnables called from two or more tasks
  and runnables which are called conditionally.

It is important to note that only one of those two methods can be used in a single
task.
The table \ref RUNNABLES_SUMMARY "Static instrumentation of runnables" summarizes the
differences between both methods.

<table>
  <caption id="RUNNABLES_SUMMARY">Static instrumentation of runnables</caption>
  <tr align="center">
    <th> Runnable ID Type
    <th> Number of IDs used
    <th> Supported by T1.cont
    <th> Number of Events Traced
  <tr align="center">
    <td> static
    <td> 1
    <td> no
    <td> With N Runnables, 2N or N+1
  <tr align="center">
    <td> dynamic
    <td> Number of runnables traced
    <td> yes with event chains
    <td> With N Runnables, 2N (T1.cont capable) or N+1
</table>

Configuration {#RUNNABLES_CONFIG}
=============
Static runnable ID {#RUNNABLES_CONFIG_STATIC}
------------------
This method requires each runnable to be assigned to its unique respective task in the
T1 project file which needs to be generated during the build process.

The following parameter used in T1_UserCfg.inv:
~~~~~~~~~~~~~~~{.c}
-staticRunnableID=<value> [0..1023].
~~~~~~~~~~~~~~~

will generate the following macro in T1_config.h:
~~~~~~~~~~~~~~~{.c}
#define T1_STATIC_RUNNABLE_ID           (<value>u)
~~~~~~~~~~~~~~~

Dynamic runnable ID {#RUNNABLES_CONFIG_DYNAMIC}
-------------------
This method requires each runnable traced to be assigned its own ID. The ID range is
0 to 1023 and the runnable IDs are specific to one T1 System ID. If the static
runnable ID is also used in the project, no dynamic runnables can use this
particular ID.

It is necessary to create the runnables IDs in T1_AppInterface.h as follow:
~~~~~~~~~~~~~~~{.c}
...*/

/* @T1@ <SystemElement Name="Core2_10msRunnable0" Type="RunnableDynamic" SID="4">*/
#define T1_Core2_10msRunnable0_ID 0u
/* @T1@ </SystemElement > */
/* @T1@ <SystemElement Name="Core2_10msRunnable1" Type="RunnableDynamic" SID="4">*/
#define T1_Core2_10msRunnable1_ID 1u
/* @T1@ </SystemElement > */
/* @T1@ <SystemElement Name="Core2_10msRunnable2" Type="RunnableDynamic" SID="4">*/
#define T1_Core2_10msRunnable2_ID 2u
/* @T1@ </SystemElement > */

/*...
~~~~~~~~~~~~~~~

Runnable tracing {#RUNNABLES_TRACING}
================
The runnables are traced with T1_TraceEvent() or its variants, see \ref PC and \ref
INTRPT.

N+1 events {#RUNNABLES_TRACING_SINGLE}
----------
If the runnable calls are back to back, i.e. there is no code being executed between
runnables, then it is possible to instrument the runnables using consecutive
#T1_RUNNABLE_START and one final #T1_RUNNABLE_STOP.
Furthermore, if resource conservation is prioritized over runnable measurement
precision, this is also the preferred method.

~~~~~~~~~~~~~~~{.c}
...*/

TASK(Core2_5msTask)
{
    T1_TraceEvent(T1_RUNNABLE_START , T1_STATIC_RUNNABLE_ID);
    Core2_5msRunnable0( );
    T1_TraceEvent(T1_RUNNABLE_START , T1_STATIC_RUNNABLE_ID);
    Core2_5msRunnable1( );
    T1_TraceEvent(T1_RUNNABLE_STOP , T1_STATIC_RUNNABLE_ID);
}

TASK(Core2_10msTask)
{
    T1_TraceEvent(T1_RUNNABLE_START , T1_Core2_10msRunnable0_ID);
    Core2_10msRunnable0( );
    T1_TraceEvent(T1_RUNNABLE_START , T1_Core2_10msRunnable1_ID);
    Core2_10msRunnable1( );
    T1_TraceEvent(T1_RUNNABLE_START , T1_Core2_10msRunnable2_ID);
    Core2_10msRunnable2( );
    T1_TraceEvent(T1_RUNNABLE_STOP , T1_Core2_10msRunnable2_ID);
}

/*...
~~~~~~~~~~~~~~~

2N events {#RUNNABLES_TRACING_DOUBLE}
---------
Explicit #T1_RUNNABLE_START/#T1_RUNNABLE_STOP pairs have to be used in order to
obtain reliable measurements for the runnables when they are separated by:
- explicit CPU yielding, e.g. a call to the OS scheduler.
- a call to WaitEvent, GetSpinlock or a similar function.
- any other significant code sequences not part of a runnable.

This method is also required in order to use \ref EVENT_CHAINS to obtain T1.cont
results with the dynamic runnable ID.

~~~~~~~~~~~~~~~{.c}
...*/

TASK(Core2_5msTask)
{
    T1_TraceEvent(T1_RUNNABLE_START , T1_STATIC_RUNNABLE_ID);
    Core2_5msRunnable0( );
    T1_TraceEvent(T1_RUNNABLE_STOP , T1_STATIC_RUNNABLE_ID);
    Os_Schedule( );
    T1_TraceEvent(T1_RUNNABLE_START , T1_STATIC_RUNNABLE_ID);
    Core2_5msRunnable1( );
    T1_TraceEvent(T1_RUNNABLE_STOP , T1_STATIC_RUNNABLE_ID);
}

TASK(Core2_10msTask)
{
    EventMaskType ev;

    T1_TraceEvent(T1_RUNNABLE_START , T1_Core2_10msRunnable0_ID);
    Core2_10msRunnable0( );
    T1_TraceEvent(T1_RUNNABLE_STOP , T1_Core2_10msRunnable0_ID);

    WaitEvent( event1, event2 );
    GetEvent( Core2_10msTask, ev);
    if( ev & event1 != 0 )
    {
        T1_TraceEvent(T1_RUNNABLE_START , T1_Core2_10msRunnable1_ID);
        Core2_10msRunnable1( );
        T1_TraceEvent(T1_RUNNABLE_STOP , T1_Core2_10msRunnable1_ID);
    }
    if( ev & event2 != 0 )
    {
        T1_TraceEvent(T1_RUNNABLE_START , T1_Core2_10msRunnable2_ID);
        Core2_10msRunnable2( );
        T1_TraceEvent(T1_RUNNABLE_STOP , T1_Core2_10msRunnable2_ID);
    }
}

/*...
~~~~~~~~~~~~~~~

 */

/* clang-format on */
#endif /* defined T1_DOXYGEN_ONLY */

#endif /* T1_SCOPE_INTERFACE_H_ */
