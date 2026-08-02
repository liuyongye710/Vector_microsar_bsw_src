/*********************************************************************************//*!
*   \file           T1_baseInterface.h
*
*   \brief          T1.base interface declarations and macros
*
*   \par Visibility
*                   External
*
*   \author alexandrebau
*
*   \version 2.5.5.0 r40137
*
*   \copyright GLIWA GmbH embedded systems, Weilheim i.OB. All rights reserved
*************************************************************************************/

#ifndef T1_BASE_INTERFACE_H_
#define T1_BASE_INTERFACE_H_ (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/* Set default single-core T1_GetCoreIdOffset before including T1_targetSpecifics.h */
#if ! defined T1_GetCoreIdOffset
#   if defined T1_NOF_CORES
#       if 1 == T1_NOF_CORES
#           define T1_GetCoreIdOffset( )    (0u)
#       endif
#   else /* single core */
#       define T1_GetCoreIdOffset( )        (0u)
#   endif /* defined T1_NOF_CORES */
#endif /* ! defined T1_GetCoreIdOffset */

#include "T1_targetSpecifics.h"

/*----------------------------------------------------------------------------------*/
/*--- macros -----------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#ifndef T1_EXTERN
#   if defined __cplusplus
#       define T1_EXTERN        extern "C"
#   else
#       define T1_EXTERN        extern
#   endif
#endif

#ifndef T1_FAR
#   define T1_FAR
#endif

#ifndef T1_FARPTR
#   define T1_FARPTR            *
#endif

#ifdef T1_NEAR
#   define T1_USE_NEAR          (1)
#else
#   define T1_USE_NEAR          (0)
#   define T1_NEAR
#endif

#ifndef T1_NEARPTR
#   define T1_NEARPTR           *
#endif

#ifndef T1_NULL
#   define T1_NULL              ((void *)0)
#endif

#ifndef T1_INLINE
#   define T1_INLINE
#endif

#ifndef T1_NOINLINE
#   define T1_NOINLINE
#endif

#ifndef T1_SEC_CONST_32
#   define T1_SEC_CONST_32
#endif

#ifndef T1_SEC_CONST_16
#   define T1_SEC_CONST_16
#endif

#ifndef T1_SEC_CONST_8
#   define T1_SEC_CONST_8
#endif

#ifndef T1_SEC_CONST_32_CLONE
#   define T1_SEC_CONST_32_CLONE
#endif

#ifndef T1_SEC_CONST_16_CLONE
#   define T1_SEC_CONST_16_CLONE
#endif

#ifndef T1_SEC_CONST_8_CLONE
#   define T1_SEC_CONST_8_CLONE
#endif

#ifndef T1_CODE
#   define T1_CODE
#endif

#ifndef T1_CODE_CORE0
#   define T1_CODE_CORE0
#endif

#ifndef T1_CODE_CORE1
#   define T1_CODE_CORE1
#endif

#ifndef T1_CODE_CORE2
#   define T1_CODE_CORE2
#endif

#ifndef T1_CODE_CORE3
#   define T1_CODE_CORE3
#endif

#ifndef T1_CODE_CORE4
#   define T1_CODE_CORE4
#endif

#ifndef T1_CODE_CORE5
#   define T1_CODE_CORE5
#endif

#ifndef T1_CODE_CORE6
#   define T1_CODE_CORE6
#endif

#ifndef T1_CODE_CORE7
#   define T1_CODE_CORE7
#endif

#ifndef T1_CODE_CORE8
#   define T1_CODE_CORE8
#endif

#ifndef T1_CODE_CORE9
#   define T1_CODE_CORE9
#endif

#ifndef T1_CODE_CORE10
#   define T1_CODE_CORE10
#endif

#ifndef T1_CODE_CORE11
#   define T1_CODE_CORE11
#endif

#ifndef T1_CODE_CORE12
#   define T1_CODE_CORE12
#endif

#ifndef T1_CODE_CORE13
#   define T1_CODE_CORE13
#endif

#ifndef T1_CODE_CORE14
#   define T1_CODE_CORE14
#endif

#ifndef T1_FAR_CODE
#   define T1_FAR_CODE T1_CODE
#endif

#ifndef T1_CODE_FAST
#   define T1_CODE_FAST T1_CODE
#endif

#ifndef T1_CODE_OPT
#   define T1_CODE_OPT
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER
#   define T1_SEC_NO_INIT_32_TRACEBUFFER
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE1
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE1
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE2
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE2
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE3
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE3
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE4
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE4
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE5
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE5
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE6
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE6
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE7
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE7
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE8
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE8
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE9
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE9
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE10
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE10
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE11
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE11
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE12
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE12
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE13
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE13
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE14
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE14
#endif

#ifndef T1_SEC_NEAR_NO_INIT_32
#   define T1_SEC_NEAR_NO_INIT_32
#endif

#ifndef T1_SEC_NO_INIT_32
#   define T1_SEC_NO_INIT_32
#endif

#ifndef T1_SEC_NO_INIT_32_CORE0
#   define T1_SEC_NO_INIT_32_CORE0
#endif

#ifndef T1_SEC_NO_INIT_32_CORE1
#   define T1_SEC_NO_INIT_32_CORE1
#endif

#ifndef T1_SEC_NO_INIT_32_CORE2
#   define T1_SEC_NO_INIT_32_CORE2
#endif

#ifndef T1_SEC_NO_INIT_32_CORE3
#   define T1_SEC_NO_INIT_32_CORE3
#endif

#ifndef T1_SEC_NO_INIT_32_CORE4
#   define T1_SEC_NO_INIT_32_CORE4
#endif

#ifndef T1_SEC_NO_INIT_32_CORE5
#   define T1_SEC_NO_INIT_32_CORE5
#endif

#ifndef T1_SEC_NO_INIT_32_CORE6
#   define T1_SEC_NO_INIT_32_CORE6
#endif

#ifndef T1_SEC_NO_INIT_32_CORE7
#   define T1_SEC_NO_INIT_32_CORE7
#endif

#ifndef T1_SEC_NO_INIT_32_CORE8
#   define T1_SEC_NO_INIT_32_CORE8
#endif

#ifndef T1_SEC_NO_INIT_32_CORE9
#   define T1_SEC_NO_INIT_32_CORE9
#endif

#ifndef T1_SEC_NO_INIT_32_CORE10
#   define T1_SEC_NO_INIT_32_CORE10
#endif

#ifndef T1_SEC_NO_INIT_32_CORE11
#   define T1_SEC_NO_INIT_32_CORE11
#endif

#ifndef T1_SEC_NO_INIT_32_CORE12
#   define T1_SEC_NO_INIT_32_CORE12
#endif

#ifndef T1_SEC_NO_INIT_32_CORE13
#   define T1_SEC_NO_INIT_32_CORE13
#endif

#ifndef T1_SEC_NO_INIT_32_CORE14
#   define T1_SEC_NO_INIT_32_CORE14
#endif

#ifndef T1_SEC_NEAR_NO_INIT_16
#   define T1_SEC_NEAR_NO_INIT_16
#endif

#ifndef T1_SEC_NO_INIT_16
#   define T1_SEC_NO_INIT_16
#endif

#ifndef T1_SEC_NEAR_NO_INIT_8
#   define T1_SEC_NEAR_NO_INIT_8
#endif

#ifndef T1_SEC_NO_INIT_8
#   define T1_SEC_NO_INIT_8
#endif

#ifndef T1_SEC_NO_INIT_8_CORE0
#   define T1_SEC_NO_INIT_8_CORE0
#endif

#ifndef T1_SEC_NO_INIT_8_CORE1
#   define T1_SEC_NO_INIT_8_CORE1
#endif

#ifndef T1_SEC_NO_INIT_8_CORE2
#   define T1_SEC_NO_INIT_8_CORE2
#endif

#ifndef T1_SEC_NO_INIT_8_CORE3
#   define T1_SEC_NO_INIT_8_CORE3
#endif

#ifndef T1_SEC_NO_INIT_8_CORE4
#   define T1_SEC_NO_INIT_8_CORE4
#endif

#ifndef T1_SEC_NO_INIT_8_CORE5
#   define T1_SEC_NO_INIT_8_CORE5
#endif

#ifndef T1_SEC_NO_INIT_8_CORE6
#   define T1_SEC_NO_INIT_8_CORE6
#endif

#ifndef T1_SEC_NO_INIT_8_CORE7
#   define T1_SEC_NO_INIT_8_CORE7
#endif

#ifndef T1_SEC_NO_INIT_8_CORE8
#   define T1_SEC_NO_INIT_8_CORE8
#endif

#ifndef T1_SEC_NO_INIT_8_CORE9
#   define T1_SEC_NO_INIT_8_CORE9
#endif

#ifndef T1_SEC_NO_INIT_8_CORE10
#   define T1_SEC_NO_INIT_8_CORE10
#endif

#ifndef T1_SEC_NO_INIT_8_CORE11
#   define T1_SEC_NO_INIT_8_CORE11
#endif

#ifndef T1_SEC_NO_INIT_8_CORE12
#   define T1_SEC_NO_INIT_8_CORE12
#endif

#ifndef T1_SEC_NO_INIT_8_CORE13
#   define T1_SEC_NO_INIT_8_CORE13
#endif

#ifndef T1_SEC_NO_INIT_8_CORE14
#   define T1_SEC_NO_INIT_8_CORE14
#endif

#ifndef T1_SEC_NO_INIT_32_CLONE
#   define T1_SEC_NO_INIT_32_CLONE
#endif

#ifndef T1_SEC_NO_INIT_16_CLONE
#   define T1_SEC_NO_INIT_16_CLONE
#endif

#ifndef T1_SEC_NO_INIT_8_CLONE
#   define T1_SEC_NO_INIT_8_CLONE
#endif

#ifndef T1_STRING
#   define T1_STRING
#endif

#ifndef T1_UNUSED
#   define T1_UNUSED( varDecl_ )    varDecl_
#endif

#ifndef T1_ALIGN_32
#   define T1_ALIGN_32              T1_ALIGN_VAR( 4 )
#endif

#if ! defined T1_NOP
#   define T1_NOP( )                __asm( "nop" )
#endif /* T1_NOP */

/*! \brief Declare a plugin for use in #T1_DeclarePluginTable. */
#define T1_DeclarePlugin(x_)        T1_EXTERN struct T1_pluginStruct const T1_SEC_CONST_32 (x_)
/*! \brief Declare a plugin table for use in T1_Init. */
#define T1_DeclarePluginTable(x_)   T1_EXTERN T1_pluginTable_t T1_SEC_CONST_32 (x_)
#define T1_DISABLED_PLUGIN          ((T1_pPlugin_t)-1)

#define T1_BASE_PLUGIN_ID           (0u)

#define T1_GCP_STD_MSG_BYTES        (8u)

/*----------------------------------------------------------------------------------*/
#ifdef T1_ENABLE
/*! \brief T1.base entry in plugin table. */
#   define T1_basePlugin            (&T1_basePluginStruct)
#else
#   define T1_basePlugin            (T1_DISABLED_PLUGIN)
#endif

/*! \brief return codes with this bit set indicate an error */
#define T1_ERR_MASK                 ((T1_status_t)0x80u)
/*! \brief return true if and only if the input code indicates an error */
#define T1_IS_ERROR( errCode_ )     (((errCode_) & T1_ERR_MASK) == T1_ERR_MASK)

/*! \brief the service completed correctly */
#define T1_OK                       ((T1_status_t)0x00u)
#define T1_YES                      ((T1_status_t)0x01u)
#define T1_NO                       ((T1_status_t)0x02u)

/*! \brief the service did not perform any action */
#define T1_NOFUNC                   ((T1_status_t)0x03u)

/* the following return codes indicate the execution of the service failed */
/*! \brief the service failed in a way not described by a more specific code */
#define T1_FAILED                   ((T1_status_t)0x80u)
/*! \brief T1_Handler() or T1_ContBgHandler() has been re-entered */
#define T1_BUSY                     ((T1_status_t)0x81u)
/*! \brief T1_Handler() has been called before T1_Init() */
#define T1_NOTINITIALIZED           ((T1_status_t)0x82u)
/*! \brief the service did not perform any action because its plugin is disabled */
#define T1_PLUGIN_NOT_AVAILABLE     ((T1_status_t)0x83u)
/*! \brief an invalid input was supplied to the service */
#define T1_VALUE                    ((T1_status_t)0x84u)
#define T1_INVALID_COMMAND          ((T1_status_t)0x85u)
#define T1_NOT_IN_PRIVILEGED_MODE   ((T1_status_t)0x86u)
#define T1_INVALID_ACCESS_MASK      ((T1_status_t)0x87u)
#define T1_NOT_SUPPORTED_BY_TARGET  ((T1_status_t)0x88u)
#define T1_EXTERNAL_DEBUG           ((T1_status_t)0x89u)

#ifdef T1_ENABLE

/*! \brief Return non-zero if the given feature (mask) is enabled. */
#   define T1_IsFeatureEnabled( mask_ )                             \
    ( (T1_featureMask & (T1_featureMask_t)(mask_)) != 0uL )

/*! \brief Define a T1-TARGET-SW plugin table with the given name. */
#   define T1_ALLOCATE_PLUGIN_TABLE( pluginTable_ )                 \
T1_pluginTable_t (pluginTable_) T1_SEC_CONST_32 =                   \
{                                                                   \
    T1_basePlugin,                                                  \
    T1_scopePlugin,                                                 \
    T1_flexPlugin,                                                  \
    T1_delayPlugin,                                                 \
    T1_modPlugin,                                                   \
    T1_contPlugin                                                   \
};

/*!
 * \brief Define a T1-TARGET-SW plugin table with the given name.
 * Regardless of #T1_DISABLE_T1_FLEX, T1.flex is never enabled.
 */
#   define T1_ALLOCATE_PLUGIN_TABLE_NO_T1_FLEX( pluginTable_ )      \
T1_pluginTable_t (pluginTable_) T1_SEC_CONST_32 =                   \
{                                                                   \
    T1_basePlugin,                                                  \
    T1_scopePlugin,                                                 \
    T1_DISABLED_PLUGIN,                                             \
    T1_delayPlugin,                                                 \
    T1_modPlugin,                                                   \
    T1_contPlugin                                                   \
};

/*!
 * \brief Define a T1-TARGET-SW plugin table with the given name.
 * Regardless of #T1_DISABLE_T1_CONT, T1.cont is never enabled.
 */
#   define T1_ALLOCATE_PLUGIN_TABLE_NO_T1_CONT( pluginTable_ )      \
T1_pluginTable_t (pluginTable_) T1_SEC_CONST_32 =                   \
{                                                                   \
    T1_basePlugin,                                                  \
    T1_scopePlugin,                                                 \
    T1_flexPlugin,                                                  \
    T1_delayPlugin,                                                 \
    T1_modPlugin,                                                   \
    T1_DISABLED_PLUGIN                                              \
};

/* polyspace<MISRA-C3:8.3:Not a defect:Other> Checker artifact. This macro is completely unrelated to the relevant violation. */
#   define T1_CAT_( x_, y_ ) x_ ## y_
#   define T1_CAT( x_, y_ )  T1_CAT_( x_, y_ )

#else

#   define T1_IsFeatureEnabled( mask_ ) (0)
#   define T1_ALLOCATE_PLUGIN_TABLE( pluginTable_ )

#endif /* #ifdef T1_ENABLE */

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*!
 * \typedef T1_uint8Least_t
 * \brief Unsigned integer with at least 8 bits. No modulo 256 arithmetic!
 */
/*!
 * \typedef T1_uint16Least_t
 * \brief Unsigned integer with at least 16 bits. No modulo 65536 arithmetic!
 */
/*!
 * \typedef T1_uint32Least_t
 * \brief Unsigned integer with at least 32 bits. No modulo 4294967296 arithmetic!
 */

#if defined T1_CPU8BIT /* CPU has 8-bit registers */
/*!
 * \def T1_CPU8BIT
 * \brief Internal: If defined, the CPU uses 8-bit registers.
 */
typedef unsigned char       T1_uint8Least_t;
typedef unsigned short      T1_uint16Least_t;
typedef unsigned long       T1_uint32Least_t;
#elif defined T1_CPU16BIT /* CPU has 16-bit registers and no 8-bit registers */
/*!
 * \def T1_CPU16BIT
 * \brief Internal: If defined, the CPU uses 16-bit registers.
 */
typedef unsigned short      T1_uint8Least_t;
typedef unsigned short      T1_uint16Least_t;
typedef unsigned long       T1_uint32Least_t;
#elif defined T1_CPU32BIT /* CPU has 32-bit registers and no 8- or 16-bit registers */
/*!
 * \def T1_CPU32BIT
 * \brief Internal: If defined, the CPU uses 32-bit registers.
 */
typedef unsigned long       T1_uint8Least_t;
typedef unsigned long       T1_uint16Least_t;
typedef unsigned long       T1_uint32Least_t;
#else
#   error T1_CPU<n>BIT not defined
#endif

/* Usually platform independent */
typedef unsigned char       T1_uint8_t;     //!< Unsigned 8-bit integer
typedef unsigned short      T1_uint16_t;    //!< Unsigned 16-bit integer
typedef unsigned long       T1_uint32_t;    //!< Unsigned 32-bit integer

/* Types for more than one plug-in */
#if defined T1_32BIT_TRACE_TIME
typedef T1_uint32_t             T1_tick_t;      //!< Used for storage
typedef T1_uint32Least_t        T1_tickUint_t;  //!< Never used for storage
#else /* 16 bit time is default */
typedef T1_uint16_t             T1_tick_t;      //!< Used for storage
typedef T1_uint16Least_t        T1_tickUint_t;  //!< Never used for storage
#endif /* T1_32BIT_TRACE_TIME */

/*! \brief T1-TARGET-SW boolean type. */
typedef T1_uint8_t              T1_bool_t;
/*! \brief T1-TARGET-SW boolean true value. */
/* polyspace<MISRA-C3:13.5:Not a defect:Other> No side effects. */
#define T1_TRUE                 ((T1_bool_t)1u)
/*! \brief T1-TARGET-SW boolean false value. */
#define T1_FALSE                ((T1_bool_t)0u)

/*! \brief Return value from some T1-TARGET-SW API cals and callbacks. */
typedef T1_uint8Least_t         T1_status_t;

/*! \brief Internal: void-void function pointer used in T1_configGen.c. */
typedef void                  (*T1_pVoidVoid_t)( void );

/*----------------------------------------------------------------------------------*/
/*! \brief Internal: Unique plugin idenifier. */
typedef T1_uint8_t              T1_pluginID_t;
/*----------------------------------------------------------------------------------*/
/* polyspace<MISRA-C3:1.3:Low:Justified> A structure forward declaration is intentional for information hiding */
struct T1_pluginStruct;
/*! \brief Internal: Pointer to const plugin data. */
typedef struct T1_pluginStruct const * T1_pPlugin_t;
/* polyspace<MISRA-C3:1.1:Not a defect:Other> *Polyspace Artefact* False positive admitted by supplier 2016-2-10 */
/*! \brief Internal: All plugins, whether enabled or not. */
typedef T1_pPlugin_t const      T1_pluginTable_t[];
/*----------------------------------------------------------------------------------*/
/*! \brief Internal: Type for T1_featureMask. */
typedef T1_uint32_t             T1_featureMask_t;
/*----------------------------------------------------------------------------------*/
/*! \brief 8-byte word-aligned container for communication layer (e.g. CAN) frames. */
typedef struct
{
    union
    {
        T1_uint8_t  u8 [8];
        T1_uint16_t u16[4];
        T1_uint32_t u32[2];
    } d;
} T1_rawData_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Type for T1_timeouts. */
typedef struct {
    T1_uint16_t     gcpRx;
    T1_uint16_t     gcpTx;
    T1_uint16_t     t1response;
} T1_timeouts_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Internal: Word-aligned container passed between T1-TARGET-SW and GCP. */
typedef union {
    T1_uint8_t      u8[T1_GCP_STD_MSG_BYTES];
    T1_uint16_t     u16[T1_GCP_STD_MSG_BYTES / 2];
    T1_uint32_t     alignmentDummy;
} T1_fakeGcpBuf_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Internal: Callback after successful packet transmission. */
typedef void (*T1_pTxComplete_t)(
#ifdef T1_NOF_CORES
                                    T1_uint8Least_t coreId
#else /* single core */
                                    void
#endif /* T1_NOF_CORES */
                                                            );
/*----------------------------------------------------------------------------------*/
/*! \brief T1.base global data for one core. */
typedef struct {
    T1_uint8_t              txBufferState;      //!< State machine for transmission
    volatile T1_uint8_t     interruptNestCount; //!< Used by T1_SuspendAllInterrupts()
    T1_uint16_t             txState;            //!< T1.base transmit queue
    T1_uint8_t              gcpTid;             //!< GCP Target-ID
    T1_bool_t               locked;             //!< Lock out T1_Handler()
    T1_uint8_t              pluginToTransmitId;
    T1_uint8_t              pluginsEnabledMask; //!< One bit set per plugin
    T1_fakeGcpBuf_t         txBuffer;           //! Transmit interface with GCP
    T1_fakeGcpBuf_t         rxBuffer;           //! Receive interface with GCP
    T1_uint16_t             txValue;            //!< Queued data from T1_TxValue()
    T1_uint16_t             responseTimeout;    //!< Timeout on reaching zero
    struct T1_pluginStruct const * const *activePluginTable;    //!< Plugin table
    T1_pTxComplete_t        pTxCompleteFn;
    T1_uint16_t             checkSum;
    T1_uint16_t             unused16;           //!< force alignment
#if defined T1_ALLOC_GLOBAL_VAR
    T1_icuRegister_t        savedIcuRegister;   //!< Used by T1_SuspendAllInterrupts()
#endif /* defined T1_ALLOC_GLOBAL_VAR */
    T1_uint16_t             initTime;
    T1_uint8_t              txValueState;       //!< State machine for txValue queue
} T1_baseGlobals_t;


/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#ifdef T1_ENABLE

#   if defined T1_NO_INIT_SID
#       define T1_START_SEC_NO_INIT_8
#       include "T1_MemMap.h"
T1_EXTERN T1_uint8_t                    T1_SEC_NO_INIT_8 T1_sid;
#       define T1_STOP_SEC_NO_INIT_8
#       include "T1_MemMap.h"
#   else /* ! defined T1_NO_INIT_SID */
#       define T1_START_SEC_CONST_8
#       include "T1_MemMap.h"
T1_EXTERN const T1_uint8_t              T1_SEC_CONST_8 T1_sid;
#       define T1_STOP_SEC_CONST_8
#       include "T1_MemMap.h"
#   endif /* defined T1_NO_INIT_SID */

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_DeclarePlugin( T1_basePluginStruct );
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN const T1_featureMask_t        T1_SEC_CONST_32 T1_initFeatureMask;
T1_EXTERN T1_uint8_t const * const      T1_SEC_CONST_32 T1_pBid;
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32
#   include "T1_MemMap.h"
/*! \brief Internal: Feature bit mask shared by all cores. See T1_IsFeatureEnabled( mask ). */
T1_EXTERN T1_featureMask_t              T1_SEC_NO_INIT_32 T1_featureMask;
#   define T1_STOP_SEC_NO_INIT_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_8
#   include "T1_MemMap.h"

#   ifdef T1_CPU32BIT
T1_EXTERN const T1_uint8_t              T1_SEC_CONST_8 T1_traceTimerBitLength;
T1_EXTERN const T1_uint8_t              T1_SEC_CONST_8 T1_traceTimerBitLengthPC[];
#   endif /* T1_CPU32BIT */

/* polyspace<MISRA-C3:8.6:Not a defect:Other> Suspected Polyspace atrifact, overseen definition in header file.
   polyspace<MISRA-C3:5.5:Not a defect:Improve> Make the code more understandable: avoid re-definition of macros. */
T1_EXTERN const T1_uint8_t              T1_SEC_CONST_8 T1_nofCores;
T1_EXTERN const T1_uint8_t              T1_SEC_CONST_8 T1_commsCoreOffset;

#   define T1_STOP_SEC_CONST_8
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_16
#   include "T1_MemMap.h"
/*! \brief GCP and T1-TARGET-SW timeout values as multiples of the T1_Handler period. */
T1_EXTERN const T1_timeouts_t           T1_SEC_CONST_16 T1_timeouts;
#   define T1_STOP_SEC_CONST_16
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
/*!
 * \brief Build ID uniquely identifies each linked ELF file.
 * \details The build ID guards against a mismatch between the executing code and the
 * ELF file used by the T1-HOST-SW for translation between symbol names and addresses.
 * Ideally this should be generated every time and ELF file is linked but typically
 * it is only generated when the T1 configuration scripts are executed.
 * it is only generated when the T1 configuration scripts are executed.
 */
T1_EXTERN const T1_uint32_t             T1_SEC_CONST_32 T1_bid;
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   if defined T1_NOF_CORES && !defined T1_MULTICORE_CLONE

#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_EXTERN T1_baseGlobals_t * const T1_SEC_CONST_32 T1_baseGlobalsPC[];
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"

#   elif defined T1_MULTICORE_CLONE

#       define T1_START_SEC_NO_INIT_32_CLONE
#       include "T1_MemMap.h"
T1_EXTERN T1_baseGlobals_t T1_SEC_NO_INIT_32_CLONE T1_baseGlobals;
#       define T1_STOP_SEC_NO_INIT_32_CLONE
#       include "T1_MemMap.h"

#else /* single core */

#       define T1_START_SEC_NO_INIT_32
#       include "T1_MemMap.h"
T1_EXTERN T1_baseGlobals_t T1_SEC_NO_INIT_32 T1_baseGlobals;
#       define T1_STOP_SEC_NO_INIT_32
#       include "T1_MemMap.h"

#   endif /* T1_NOF_CORES */

#endif /* #ifdef T1_ENABLE */

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for global functions ------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_START_SEC_CODE
#include "T1_MemMap.h"

/*
 * For safety reasons, the services T1_SuspendAllInterrupts() and
 * T1_ResumeAllInterrupts() are present even if T1_ENABLE is not defined, i.e.
 * T1-TARGET-SW is disabled. Thus, these services are not encapsulated by
 * #ifdef T1_ENABLE / #endif
 *
 * These functions must be able to be nested. For example,
 * T1_SuspendAllInterrupts shall not assume that interrupts
 * are enabled on entry and T1_ResumeAllInterrupts shall not
 * unconditionally enable interrupts.
 *
 * These functions are actually not implemented in the T1-TARGET-SW libraries but in
 * T1_config.c and the default map to T1-TARGET-SW library functions that are
 * simplistic and generally not safe from user-mode. During integration, these are
 * typically adapted to map to OS functions, firstly so that they are safe also from
 * user-mode and secondly to avoid useless code duplication.
 */
#if defined T1_NOF_CORES
/*! \brief Inhibit all interrupts. See \ref PC and \ref INTRPT. */
T1_EXTERN void T1_CODE T1_SuspendAllInterruptsPC( T1_uint8Least_t coreId );
/*! \brief Internal library helper function for default T1_SuspendAllInterruptsPC(). */
T1_EXTERN void T1_CODE T1_SuspendAllInterruptsPC_( T1_uint8Least_t coreId );
/*! \brief Permit interrupts as before T1_SuspendAllInterrupts. See \ref PC and \ref INTRPT. */
T1_EXTERN void T1_CODE T1_ResumeAllInterruptsPC( T1_uint8Least_t coreId );
/*! \brief Internal library helper function for default T1_ResumeAllInterruptsPC(). */
T1_EXTERN void T1_CODE T1_ResumeAllInterruptsPC_( T1_uint8Least_t coreId );
/*! \brief Inhibit all interrupts. See \ref PC and \ref INTRPT. */
#   define T1_SuspendAllInterrupts( )           T1_SuspendAllInterruptsPC( T1_GetCoreIdOffset( ) )
/*! \brief Permit interrupts as before T1_SuspendAllInterrupts. See \ref PC and \ref INTRPT. */
#   define T1_ResumeAllInterrupts( )            T1_ResumeAllInterruptsPC( T1_GetCoreIdOffset( ) )
#else /* single core */
/*! \brief Inhibit all interrupts. See \ref PC and \ref INTRPT. */
#   define T1_SuspendAllInterruptsPC( coreId_ ) T1_SuspendAllInterrupts( )
/*! \brief Permit interrupts as before T1_SuspendAllInterrupts. See \ref PC and \ref INTRPT. */
#   define T1_ResumeAllInterruptsPC( coreId_ )  T1_ResumeAllInterrupts( )
/*! \brief Inhibit all interrupts. See \ref PC and \ref INTRPT. */
T1_EXTERN void T1_CODE T1_SuspendAllInterrupts( void );
/*! \brief Internal library helper function for default T1_SuspendAllInterrupts(). */
T1_EXTERN void T1_CODE T1_SuspendAllInterrupts_( void );
/*! \brief Permit interrupts as before T1_SuspendAllInterrupts. See \ref PC and \ref INTRPT. */
T1_EXTERN void T1_CODE T1_ResumeAllInterrupts( void );
/*! \brief Internal library helper function for default T1_ResumeAllInterrupts(). */
T1_EXTERN void T1_CODE T1_ResumeAllInterrupts_( void );
#endif /* defined T1_NOF_CORES */

#ifdef T1_ENABLE

#if defined T1_NOF_CORES
/*!
 * Call periodically to service communication with T1-HOST-SW. See \ref PC.
 * \param[in] coreId the T1 logical ID of the calling core
 * \returns   #T1_VALUE if an invalid message was receivd at the last call to
 *            T1_RxCallback(),
 *            #T1_BUSY if T1_Handler() is already running due to unsupported
 *            re-entrancy,
 *            #T1_NOTINITIALIZED if T1_Init() has not yet completed,
 *            #T1_OK otherwise
 */
T1_EXTERN T1_status_t T1_CODE T1_HandlerPC( T1_uint8Least_t coreId );
/*!
 * Call periodically to service communication with T1-HOST-SW. See \ref PC.
 * \returns   #T1_VALUE if an invalid message was receivd at the last call to
 *            T1_RxCallback(),
 *            #T1_BUSY if T1_HandlerPC() is already running due to unsupported
 *            re-entrancy,
 *            #T1_NOTINITIALIZED if T1_InitPC() has not yet completed,
 *            #T1_OK otherwise
 */
#   define T1_Handler( )            T1_HandlerPC( T1_GetCoreIdOffset( ) )
/*!
 * Call, with supervisor privileges, after reset and before any other T1-TARGET-SW
 * service. See \ref PC and \ref RESBUF.
 * \param[in] coreId      the T1 logical ID of the calling core
 * \param[in] pluginTable the T1-TARGET-SW plugin table
 * \returns   #T1_OK if every enabled plugin was successfully initialized
 */
T1_EXTERN T1_status_t T1_CODE T1_InitPC( T1_uint8Least_t coreId, T1_pluginTable_t pluginTable );
/*!
 * Call, with supervisor privileges, after reset and before any other T1-TARGET-SW
 * service. See \ref PC and \ref RESBUF.
 * \param[in] pluginTable_ the T1-TARGET-SW plugin table
 * \returns   #T1_OK if every enabled plugin was successfully initialized
 */
#   define T1_Init( pluginTable_ )  T1_InitPC( T1_GetCoreIdOffset( ), (pluginTable_) )
#else /* single core */
/*!
 * Call periodically to service communication with T1-HOST-SW. See \ref PC.
 * \returns   #T1_VALUE if an invalid message was receivd at the last call to
 *            T1_RxCallback()
 */
T1_EXTERN T1_status_t T1_CODE T1_Handler( void );
/*!
 * Call periodically to service communication with T1-HOST-SW. See \ref PC.
 * \param[in] coreId_ the T1 logical ID of the calling core (zero)
 * \returns   #T1_VALUE if an invalid message was receivd at the last call to
 *            T1_RxCallback()
 */
#   define T1_HandlerPC( coreId_ )              T1_Handler( )
/*!
 * Call, with supervisor privileges, after reset and before any other T1-TARGET-SW
 * service. See \ref PC and \ref RESBUF.
 * \param[in] pluginTable the T1-TARGET-SW plugin table
 * \returns   #T1_OK if every enabled plugin was successfully initialized
 */
T1_EXTERN T1_status_t T1_CODE T1_Init( T1_pluginTable_t pluginTable );
/*!
 * Call, with supervisor privileges, after reset and before any other T1-TARGET-SW
 * service. See \ref PC and \ref RESBUF.
 * \param[in] coreId_      the T1 logical ID of the calling core (zero)
 * \param[in] pluginTable_ the T1-TARGET-SW plugin table
 * \returns   #T1_OK if every enabled plugin was successfully initialized
 */
#   define T1_InitPC( coreId_, pluginTable_ )   T1_Init( pluginTable_ )
#endif /* T1_NOF_CORES */

/*
 * T1_DisableT1Handler must inhibit scheduling of the task
 * that calls T1_Handler.
 * T1_EnableT1Handler must restore scheduling again.
 * The default implementations, in T1_config.c disable and
 * reenable interrupts using T1_SuspendAllInterrupts and
 * T1_ResumeAllInterrupts so they have to be modified
 * by the integrator if T1_ContBgHandler is called from
 * contexts without permission to directly disable
 * interrupts. For example, OS resource locks might be
 * used to achieve the required mutual exclusion.
 * For efficiency, they can also be empty functions, if
 * the task that calls T1_Handler cannot, in any case,
 * preempt the background task.
 */
#if defined T1_NOF_CORES
/*!
 * Obtain mutual exclusion with T1_Handler() on the specified core.
 * By default maps to T1_SuspendAllInterruptsPC() unless #T1_CONT_REMOTE is defined.
 * \param[in] coreId the core with which to obtain mutual exclusion
 */
T1_EXTERN void T1_CODE T1_DisableT1HandlerPC( T1_uint8Least_t coreId );
/*!
 * Release mutual exclusion with T1_Handler() on the specified core.
 * By default maps to T1_ResumeAllInterruptsPC() unless #T1_CONT_REMOTE is defined.
 * \param[in] coreId the core with which to release mutual exclusion
 */
T1_EXTERN void T1_CODE T1_EnableT1HandlerPC( T1_uint8Least_t coreId );
/*!
 * Transmit 16-bit data to the T1-HOST-SW as soon as possible, not via the T1.scope
 * trace buffer. You can construct a matching handler at the T1-HOST-SW to react to
 * the data. See \ref PC.
 * \param[in] val_ the value to be transmitted
 * \returns        #T1_FAILED if the transmit buffer is blocked because the previous
 *                 value has not yet been transmitted
 */
#   define T1_TxValue( val_ ) T1_TxValuePC( T1_GetCoreIdOffset( ), (val_) )
/*!
 * Transmit 16-bit data to the T1-HOST-SW as soon as possible, not via the T1.scope
 * trace buffer. You can construct a matching handler at the T1-HOST-SW to react to
 * the data. See \ref PC.
 * \param[in] coreId the T1 logical ID of the calling core
 * \param[in] val    the value to be transmitted
 * \returns          #T1_FAILED if the transmit buffer is blocked because the previous
 *                   value has not yet been transmitted
 */
T1_EXTERN T1_status_t T1_CODE T1_TxValuePC( T1_uint8Least_t coreId, T1_uint16_t val );
T1_EXTERN void T1_CODE T1_InitExtra1PC_( T1_uint8Least_t coreId );
T1_EXTERN void T1_CODE T1_InitExtra2PC_( T1_uint8Least_t coreId );
T1_EXTERN void T1_CODE T1_InitExtra3PC_( T1_uint8Least_t coreId );
/*! Prepare for T1_InitExtra2(). */
#   define T1_InitExtra1( )             T1_InitExtra1PC_( T1_GetCoreIdOffset( ) )
/*! Prepare for T1_InitExtra3(). */
#   define T1_InitExtra2( )             T1_InitExtra2PC_( T1_GetCoreIdOffset( ) )
/*! Enable 'unsafe' plugins. */
#   define T1_InitExtra3( )             T1_InitExtra3PC_( T1_GetCoreIdOffset( ) )
/*!
 * Prepare for T1_InitExtra2PC().
 * \param[in] coreId_ the T1 logical ID of the calling core
 */
#   define T1_InitExtra1PC( coreId_ )   T1_InitExtra1PC_( coreId_ )
/*!
 * Prepare for T1_InitExtra3PC().
 * \param[in] coreId_ the T1 logical ID of the calling core
 */
#   define T1_InitExtra2PC( coreId_ )   T1_InitExtra2PC_( coreId_ )
/*!
 * Enable 'unsafe' plugins.
 * \param[in] coreId_ the T1 logical ID of the calling core
 */
#   define T1_InitExtra3PC( coreId_ )   T1_InitExtra3PC_( coreId_ )
#else /* single core */
/*!
 * Obtain mutual exclusion with T1_Handler().
 * By default maps to T1_SuspendAllInterruptsPC().
 */
T1_EXTERN void T1_CODE T1_DisableT1Handler( void );
/*!
 * Release mutual exclusion with T1_Handler().
 * By default maps to T1_ResumeAllInterruptsPC().
 */
T1_EXTERN void T1_CODE T1_EnableT1Handler( void );
/*!
 * Transmit 16-bit data to the T1-HOST-SW as soon as possible, not via the T1.scope
 * trace buffer. You can construct a matching handler at the T1-HOST-SW to react to
 * the data. See \ref PC.
 * \param[in] coreId_ the T1 logical ID of the calling core (zero)
 * \param[in] val_    the value to be transmitted
 * \returns           #T1_FAILED if the transmit buffer is blocked because the
 *                    previous value has not yet been transmitted
 */
#define T1_TxValuePC( coreId_, val_ ) T1_TxValue( val_ )
/*!
 * Transmit 16-bit data to the T1-HOST-SW as soon as possible, not via the T1.scope
 * trace buffer. You can construct a matching handler at the T1-HOST-SW to react to
 * the data. See \ref PC.
 * \param[in] val the value to be transmitted
 * \returns       #T1_FAILED if the transmit buffer is blocked because the previous
 *                value has not yet been transmitted
 */
T1_EXTERN T1_status_t T1_CODE T1_TxValue( T1_uint16_t val );
T1_EXTERN void T1_CODE T1_InitExtra1_( void );
T1_EXTERN void T1_CODE T1_InitExtra2_( void );
T1_EXTERN void T1_CODE T1_InitExtra3_( void );
/*! \brief Prepare for T1_InitExtra2(). */
#   define T1_InitExtra1( )             T1_InitExtra1_( )
/*! \brief Prepare for T1_InitExtra3(). */
#   define T1_InitExtra2( )             T1_InitExtra2_( )
/*! \brief Enable 'unsafe' plugins. */
#   define T1_InitExtra3( )             T1_InitExtra3_( )
/*!
 * Prepare for T1_InitExtra2PC().
 * \param[in] coreId_ the T1 logical ID of the calling core (zero)
 * \returns           #T1_FAILED if the transmit buffer is blocked because the
 *                    previous value has not yet been transmitted
 */
#   define T1_InitExtra1PC( coreId_ )   T1_InitExtra1_( )
/*!
 * Prepare for T1_InitExtra3PC().
 * \param[in] the T1 logical ID of the calling core (zero)
 */
#   define T1_InitExtra2PC( coreId_ )   T1_InitExtra2_( )
/*!
 * Enable 'unsafe' plugins.
 * \param[in] the T1 logical ID of the calling core (zero)
 */
#   define T1_InitExtra3PC( coreId_ )   T1_InitExtra3_( )
#endif /* defined T1_NOF_CORES */


#else /* ! defined T1_ENABLE */

#   define T1_Handler( )                        (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_Init( pPluginTable_ )             (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_TxValue( val_ )                   (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_TxValuePC( coreId_, val_ )        (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_InitExtra1( )                     (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_InitExtra2( )                     (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_InitExtra3( )                     (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_InitExtra1PC( coreId_ )           (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_InitExtra2PC( coreId_ )           (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_InitExtra3PC( coreId_ )           (T1_PLUGIN_NOT_AVAILABLE)

#endif /* defined T1_ENABLE */

/*!
 * Call-out function to be provided (implemented) by the integrator to transmit an
 * 8-byte frame, unless using the GCP 'N' interface.
 * \param[in] pData the 8-byte frame data
 * \returns         #T1_OK only if the data was successfully queued for transmission,
 *                  #T1_FAILED otherwise
 */
T1_EXTERN T1_status_t T1_CODE T1_Transmit( T1_rawData_t const T1_FARPTR pData );
/*!
 * Call, on the communications core, when an 8-byte frame arrives, unless using the
 * GCP 'N' interface.
 * \param[in] pData the 8-byte frame data
 * \returns         #T1_OK
 */
T1_EXTERN T1_status_t T1_CODE T1_RxCallback( T1_rawData_t const *pData );

#if defined T1_NOF_CORES
T1_EXTERN T1_bool_t T1_CODE T1_ObtainedMutexPC( T1_uint8Least_t coreId, T1_uint32_t *spinLockVar );
#endif /* defined T1_NOF_CORES */

/*----------------------------------------------------------------------------------*/

#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

/*----------------------------------------------------------------------------------*/
/*--- documentation ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_DOXYGEN_ONLY

/*!
 * \def T1_GetCoreIdOffset
 * T1-TARGET-SW provides a default implementation, using the appropriate hardware
 * register, if there is no user macro of this name.
 * \returns the zero-based T1 logical core index
 */

/*!
 * \mainpage
 *
 * T1-TARGET-SW offers a rich API at the target side which can be used to configure
 * user events, user stopwatches and constraints statically (always active).
 *
 * Furthermore application features can be managed and delays (artificial CPU-Load)
 * injected in the code.
 *
 * The T1.scope trace can also be stopped by an application code trigger in order to
 * record events of interest, such as those preceding an error condition.
 */

/*!
 * \page PC API calls with and without explicit core ID
 *
 * All T1-TARGET-SW API calls are available in two versions. One version has a 'PC'
 * (per core) suffix and an additional, first parameter that explicity states the T1
 * logical identifier of the core to be processed. The other version has no 'PC'
 * suffix and obtains the T1 logical identifier of the calling core by invoking
 * T1_GetCoreIdOffset. For example, see T1_Init( T1_pluginTable_t pluginTable ) and
 * T1_InitPC( T1_uint8Least_t coreId, T1_pluginTable_t pluginTable ). The integrator
 * selects the most appropriate version for your integration.
 *
 * The 'PC' version is provided for two reasons.
 * -# Some implementations of T1_GetCoreIdOffset() are very slow, for example because
 *    a trap to supervisor mode is required in order to read the core ID register. By
 *    using the 'PC' version, the integrator controls exactly when
 *    T1_GetCoreIdOffset() is called and can cache the result to minimise the number
 *    of calls.
 * -# When using the 'remote core' configuration of T1.cont, T1_ContBgHandlerPC() is
 *    called with a core ID other than the running core.
 */

/*!
 * \page INTRPT API use of interrupt locks
 *
 * The T1-TARGET-SW scalable multi-core concept requires that, as much as possible,
 * services run exclusively on one core. Thus, for multi-core and for single core
 * implementations of T1-TARGET-SW, mutual exclusion requires only an interrupt
 * lock. However, disabling interrupts is typically not allowed in user mode. T1
 * provides two different concepts to handle most API calls, which are execute
 * relatively rarely and have little impact on the performance of the system, and
 * time-critical API calls such as T1_TraceEvent() that execute frequently and at
 * performance-sensitive points in the system.
 * -# Apart from T1_Init() and the family of API calls starting T1_Trace...,
 *    T1-TARGET-SW API calls can safely be called in user mode. Interrupts are
 *    disabled and enabled via T1_SuspendAllInterrupts() and T1_ResumeAllInterrupts()
 *    and the integrator can provide implementations that operate correctly in user
 *    mode.
 * -# The family of API calls starting T1_Trace... are too time-critical to use
 *    callouts to T1_SuspendAllInterrupts() and T1_ResumeAllInterrupts().
 *    - Generally, the integrator should manage the disabling of interrupts outside
 *      of T1-TARGET-SW and call these API calls after interrupts have been
 *      disabled. For each T1_Trace... API call there is a version with the suffix
 *      NoSusp that does not attempt to suspend interrupts, on the assumption that
 *      they are already disabled. See T1_TraceStartNoSusp(), for example.
 *    - If the integrator knows that the code is executing with sufficient privileges
 *      to disable interrupts and interrupts may or may not be disabled, they can
 *      call the version with no suffix and it will suspend and restore interrupts as
 *      required by reading and writing to the single bit in the relevant processor
 *      register. See T1_TraceStart(), for example.
 *    - If the integrator knows that the code is executing with sufficient privileges
 *      to disable interrupts and interrupts are certainly enabled, they can
 *      call the version with the ...Fast suffix and it will disable and enable
 *      interrupts as required by writing to the single bit in the relevant processor
 *      register. See T1_TraceStartFast(), for example.
 *    - To interface between the less time-critical functions that can run in user
 *      mode and the more time-critical functions that require supervisor privileges,
 *      there exists a set of 'UM' callouts, see T1_TraceEventUM(). These are
 *      implemented by the integrator to be safe to call in user mode.
 */

/*!
 * \page APPFEATURES Application features

T1 user events, user data events and stopwatches all consume entries in the trace
buffer and, if they are very frequent, they can significantly reduce the amount of
time captured and visualised in one trace buffer. In order to optimise the density
of relevant events in each trace, it is often necessary to enable and disable user
events and stopwatches at run-time.

To support this, T1 provides application features, which can be independently enabled
and disabled from the T1-HOST-SW and that can be tested in the application code.

There is always one, global application feature mask, even when multiple cores
are configured. This allows related events on different cores to be enabled
and disabled simultaneously.

Configure application feature {#APPFEATURESCONFIG}
=============================

The application feature must be declared in T1_AppInterface.h in order for the
T1-HOST-SW to offer run-time control of that feature:

~~~~~~~~~~~~~~~{.c}
...*/

/* @T1@ <AppFeature Name="OS error hook"> */
#define T1_AF_TRIGGER_ERRORHOOK     (0x00000001uL)  /* capture OS errors (ErrorHook) */
/* @T1@ </AppFeature> */

/*...
~~~~~~~~~~~~~~~

The comment of the declaration must be like the example above, because it need to be
read also by T1-HOST-SW. Only the names in comment can be changed by user.
The value, or we could call it appFeatureMask, has to be defined to 1uL << shift,
where shift is in the range 0..31.

Check application feature {#APPFEATURESCHECK}
=========================

~~~~~~~~~~~~~~~{.c}
int T1_IsFeatureEnabled( T1_featureMask_t appFeatureMask );
~~~~~~~~~~~~~~~

appFeatureMask is 1uL << shift, where shift is in the range 0..31.

A return value of zero indicates that the application feature is not enabled.

A return value other than zero indicates that the application feature is enabled.

For example:
~~~~~~~~~~~~~~~{.c}
void ErrorHook( OS_status_t errorType, OS_errInfo_t additionalInfo )
{
    if( T1_IsFeatureEnabled( T1_AF_TRIGGER_ERRORHOOK ) )
    {
        T1_TraceEvent( T1_OS_ERROR, (errorType << 8) | additionalInfo );
    }
}
~~~~~~~~~~~~~~~

Trace per feature {#TRACEPERFEATURE}
=================
There are additional variants of the T1_TraceEvent calls that only log an event
if a particular feature is enabled. They are formed by adding the suffix
PerFeature and adding a third argument to specify the feature mask.

So we could also write the above example as follows:
~~~~~~~~~~~~~~~{.c}
void ErrorHook( OS_status_t errorType, OS_errInfo_t additionalInfo )
{
    T1_TraceEventPerFeature( T1_OS_ERROR, (errorType << 8) | additionalInfo, T1_AF_TRIGGER_ERRORHOOK );
}
~~~~~~~~~~~~~~~

 */

#endif /* defined T1_DOXYGEN_ONLY */

#endif /* T1_BASE_INTERFACE_H_ */
