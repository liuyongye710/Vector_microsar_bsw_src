/************************************************************************************/
/*! \file           T1_delayInterface.h
 *
 *  \brief          T1.delay interface declarations and macros
 *
 *  \par Visibility
 *                  External
 *
 *  \author nick
 *
 *  \version 3.5.0.0 r67781
 *
 *  \copyright GLIWA embedded systems GmbH & Co. KG, Weilheim i.OB. All rights reserved
 ************************************************************************************/

#ifndef T1_DELAY_INTERFACE_H_
#define T1_DELAY_INTERFACE_H_ ( 1 )

/*!
 * \defgroup T1_delay T1.delay
 * \brief    T1.delay is a plugin of T1 that provides scalable delay routines
 *           which consume a specified amount of net-run-time (CET).
 *
 * see \ref T1_delay_page
 *
 * @{
 */

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_baseInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*!
 * \internal
 * \brief Identifier of a given delay on its core.
 */
typedef T1_uint8_t T1_delayId_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Number of trace timer ticks for which to delay. */
typedef T1_uint32_t T1_delay_t;
/*----------------------------------------------------------------------------------*/
/*! \brief T1.base global data for one core. */
typedef struct
{
    T1_uint8_t delayTxState;
} T1_delayGlobals_t;

/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
/*!
 * \brief For each system, a pointer to the T1.delay configuration
 * (array with initial values).
 *
 * \sa    \ref DELAYS_INIT
 *
 */
T1_EXTERN T1_delay_t const * const T1_SEC_CONST_32 T1_delayConfigPC[];
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
/*!
 * \brief For each system, a pointer to the current T1.delay values
 * (array with currently set values).
 */
T1_EXTERN T1_delay_t * const T1_SEC_CONST_32 T1_delaysPC[];
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_DeclarePlugin( T1_delayPluginStruct );
T1_EXTERN T1_uint32_t const T1_SEC_CONST_32 T1_delayRevision;
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_8
#    include "T1_MemMap.h"
/*! \brief For each core, the number of configured delays. */
T1_EXTERN T1_uint8_t const T1_SEC_CONST_8 T1_nOfDelaysPC[];
#    define T1_STOP_SEC_CONST_8
#    include "T1_MemMap.h"

#    if !defined T1_MULTICORE_CLONE
#        define T1_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_delayGlobals_t * const T1_SEC_CONST_32 T1_delayGlobalsPC[];
#        define T1_STOP_SEC_CONST_32
#        include "T1_MemMap.h"
#    else /* clone */
#        define T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_delayGlobals_t T1_CLONE_SEC_VAR_POWER_ON_CLEARED_32 T1_delayGlobals;
#        define T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* ! defined T1_MULTICORE_CLONE */

#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_DELAY */

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_DELAY_PLUGIN_ID ( 3u )

#if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY
/*! \brief T1.delay entry in plugin table. */
#    define T1_delayPlugin ( &T1_delayPluginStruct )
#else /* ! defined T1_ENABLE || defined T1_DISABLE_T1_DELAY */
#    define T1_delayPlugin ( T1_DISABLED_PLUGIN )
#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_DELAY */

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for global functions ------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY

#    define T1_START_SEC_CODE
#    include "T1_MemMap.h"

/*!
 * \brief   Initialize all delays for this core.
 * \returns #T1_PLUGIN_NOT_AVAILABLE if T1.delay is disabled,
 *          #T1_OK otherwise
 *
 * The delays will be initialized to the values stored in
 * [T1_delayConfigXX](\ref T1_delayConfig0).
 *
 * \note The T1-HOST-SW will only update the list of delays once on startup. Thus
 *       changes to the delays on the target side during runtime will not get
 *       reflected on the host side until a new connection is established.
 *
 * \sa    \ref DELAYS_INIT
 *
 */
#    define T1_InitDelays( )  T1_InitDelaysPC( T1_GetCoreIdOffset( ) )

/*!
 * \brief   Reset all delays for the calling core to zero.
 * \returns #T1_PLUGIN_NOT_AVAILABLE if T1.delay is disabled,
 *          #T1_OK otherwise
 *
 * The delays will be reset to *0s*.
 *
 * \note The T1-HOST-SW will only update the list of delays once on startup. Thus
 *       changes to the delays on the target side during runtime will not get
 *       reflected on the host side until a new connection is established.
 *
 * \sa    \ref DELAYS_RESET.
 *
 */
#    define T1_ResetDelays( ) T1_ResetDelaysPC( T1_GetCoreIdOffset( ) )

/*!
 * \brief   Initialize all delays for this core. See \ref PC.
 * \returns #T1_PLUGIN_NOT_AVAILABLE if T1.delay is disabled,
 *          #T1_VALUE if an invalid identifier was provided,
 *          #T1_OK otherwise
 *
 * The delays will be initialized to the values stored in
 * [T1_delayConfigXX](\ref T1_delayConfig0).
 *
 * \note The T1-HOST-SW will only update the list of delays once on startup. Thus
 *       changes to the delays on the target side during runtime will not get
 *       reflected on the host side until a new connection is established.
 *
 * \sa    \ref PC
 * \sa    \ref DELAYS_INIT
 *
 */
T1_EXTERN T1_status_t T1_CODE T1_InitDelaysPC( T1_uint8Least_t coreId );

/*!
 * \brief     Reset all delays for this core to zero.
 * \param[in] coreId the T1 logical core ID of the calling core
 * \returns   #T1_PLUGIN_NOT_AVAILABLE if T1.delay is disabled,
 *            #T1_VALUE if an invalid identifier was provided,
 *            #T1_OK otherwise
 *
 * The delays will be reset to *0s*.
 *
 * \note The T1-HOST-SW will only update the list of delays once on startup. Thus
 *       changes to the delays on the target side during runtime will not get
 *       reflected on the host side until a new connection is established.
 *
 * \sa        \ref PC
 * \sa        \ref DELAYS_RESET
 *
 */
T1_EXTERN T1_status_t T1_CODE T1_ResetDelaysPC( T1_uint8Least_t coreId );

/*!
 * \brief     Perform the delay corresponding to the given identifier.
 * \param[in] id_ the identifier of the delay
 * \returns   #T1_PLUGIN_NOT_AVAILABLE if T1.delay is disabled,
 *            #T1_VALUE if an invalid identifier was provided,
 *            #T1_OK otherwise
 *
 * \sa        \ref DELAYS_USAGE
 *
 */
#    define T1_DelayRoutine( id_ ) T1_DelayRoutinePC( T1_GetCoreIdOffset( ), ( id_ ) )

/*!
 * \brief     Perform the delay corresponding to the given identifier.
 * \param[in] coreId the T1 logical core ID of the calling core
 * \param[in] id     the identifier of the delay
 * \returns   #T1_PLUGIN_NOT_AVAILABLE if T1.delay is disabled,
 *            #T1_VALUE if an invalid identifier was provided,
 *            #T1_OK otherwise
 *
 * \sa        \ref PC
 * \sa        \ref DELAYS_USAGE
 */
T1_EXTERN T1_status_t T1_CODE T1_DelayRoutinePC( T1_uint8Least_t coreId,
                                                 T1_delayId_t id );

/*!
 * \internal
 * \brief Consume a number trace timer ticks and return T1_OK.
 * \param[in] coreId     the T1 logical core ID of the calling core
 * \param[in] timerTicks delay in number of timer ticks
 * \returns   #T1_OK
 *
 * \sa \ref PC
 * \sa T1_GetTraceTime()
 *
 */
T1_EXTERN T1_status_t T1_CODE T1_DelayForTimerTicksPC( T1_uint8Least_t coreId,
                                                       T1_delay_t timerTicks );

#    define T1_STOP_SEC_CODE
#    include "T1_MemMap.h"

#else /* ! defined T1_ENABLE || defined T1_DISABLE_T1_DELAY */

#    define T1_DelayRoutine( id_ )            ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_InitDelays( )                  ( (void)0 )
#    define T1_ResetDelays( )                 ( (void)0 )
#    define T1_DelayRoutinePC( coreId_, id_ ) ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_InitDelaysPC( coreId_ )        ( (void)0 )
#    define T1_ResetDelaysPC( coreId_ )       ( (void)0 )
#    define T1_delayRevision                  ( 0uL )

#endif /* defined T1_ENABLE && ! defined T1_DISABLE_T1_DELAY */

/**@}*/

/*----------------------------------------------------------------------------------*/
/*--- documentation ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_DOXYGEN_ONLY
/* clang-format off */

/*! \page T1_delay_page T1.delay

T1.delay is a plugin of T1 that provides scalable delay routines which consume
a specified amount of net-run-time. The T1-HOST-SW is typically be used to
configure these delays. Use-cases for T1.delay include simulating the run-time
that not yet integrated software component may consume and the determination
of the run-time *head-room* that an application has. T1 delays can be inserted
anywhere in the application to increase or vary the CET of a function.

- \subpage T1_delay_how_to

*/

/*! \page T1_delay_how_to How to Use Delays

Declaration {#DELAYS_DECLARATION}
==================

There are two possible ways to declare T1 delays.

-# The legacy method described in \ref DELAYS_DECLARATION_ENUM
-# The new method using the invocation file, described in \ref DELAYS_DECLARATION_INV

\note It is not possible to mix the [enum](\ref DELAYS_DECLARATION_ENUM) and
[invocation file](\ref DELAYS_DECLARATION_INV) methods.

Invocation File Method {#DELAYS_DECLARATION_INV}
----------------------

Delays can be configured using the parameter [-allocateDL](\ref allocateDL) in order
for the T1-HOST-SW to offer run-time control of that delay.

Example configuration:

~~~~~~~~~~~~~~~
#system all:
; Allocate delays for all cores
-allocateDL=CHECK_INTEGRATION, "Check Integration Delay", 100us

#system 0:
; Allocate delays for core 0 only
-allocateDL=2MS_R0_DELAY, "2ms runnable 0 delay"
~~~~~~~~~~~~~~~

This will create the following macros into *T1_config.h*:

~~~~~~~~~~~~~~~{.h}
...*/
/*----------------------------------------------------------------------------------*/
/*--- T1.delay IDs -----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/* Delays for all cores */
#define T1_DL_CHECK_INTEGRATION_CORE_ALL              (0u) /*!< Check Integration Delay */

/* Delays for core 0 */
#define T1_DL_CHECK_INTEGRATION_CORE0                 (T1_DL_CHECK_INTEGRATION_CORE_ALL) /*!< Check Integration Delay */
#define T1_DL_2MS_R0_DELAY_CORE0                      (1u) /*!< 2ms runnable 0 delay */

/* Delays for core 1 */
#define T1_DL_CHECK_INTEGRATION_CORE1                 (T1_DL_CHECK_INTEGRATION_CORE_ALL) /*!< Check Integration Delay */
/*...*/
/*!
 * \brief Specifies the number of delays for system 0.
 */
#define T1_NOF_DELAYS_CORE0                           (2u)
/*...*/
/*!
 * \brief Specifies the number of delays for system 1.
 */
#define T1_NOF_DELAYS_CORE1                           (1u)
/*...
~~~~~~~~~~~~~~~

And arrays were the initial values are copied from into *T1_configGen.c*
(see T1_InitDelaysPC()):

~~~~~~~~~~~~~~~{.c}
...*/
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
/*!
 * \brief Array with T1.delay configuration values use by T1_InitDelays() and
 *        T1_InitDelaysPC(), for system 0.
 */
#   if 1 != T1_NOF_DELAYS_CORE0
#       error T1_NOF_DELAYS_CORE0 does not match generated configuration
#   endif /* 1 != T1_NOF_DELAYS_CORE0 */
static T1_delay_t const T1_SEC_CONST_32 T1_delayConfig0[2] =
{
    /*   0 */ (T1_delay_t)T1_US_TO_TICKS_CORE0( 100u ) /* 100us */, /* Check Integration Delay */
    /*   1 */ (T1_delay_t)0u /* 0us */, /* 2ms runnable 0 delay */
};
/*!
 * \brief Array with T1.delay configuration values use by T1_InitDelays() and
 *        T1_InitDelaysPC(), for system 1.
 */
#   if 1 != T1_NOF_DELAYS_CORE1
#       error T1_NOF_DELAYS_CORE1 does not match generated configuration
#   endif /* 1 != T1_NOF_DELAYS_CORE1 */
static T1_delay_t const T1_SEC_CONST_32 T1_delayConfig1[1] =
{
    /*   0 */ (T1_delay_t)T1_US_TO_TICKS_CORE1( 100u ) /* 100us */, /* Check Integration Delay */
};
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
/*...
~~~~~~~~~~~~~~~

And XML elements in the T1 project files, which are used by the T1-HOST-SW for
displaying purposes:

~~~~~~~~~~~~~~~{.xml}
<System Name="Core0" ... >
  <!-- ... -->
  <Delay Name="Check Integration Delay" Id="0" />
  <!-- ... -->
</System>
<System Name="Core1" ... >
  <!-- ... -->
  <Delay Name="Check Integration Delay" Id="0" />
  <!-- ... -->
</System>
~~~~~~~~~~~~~~~

See [-allocateDL](\ref allocateDL).

Inline XML Method (legacy) {#DELAYS_DECLARATION_ENUM}
--------------------------

All delays must be declared as an enum in T1_AppInterface.h in order
for the T1-HOST-SW to offer run-time control:

~~~~~~~~~~~~~~~{.c}
...*/

#define T1_DL_CHECK_INTEGRATION_CORE_ALL (T1_DL_CHECK_INTEGRATION_CORE0)

enum
{
    /* @T1@ <Delay Name="Check Integration Delay"> */
    T1_DL_CHECK_INTEGRATION_CORE0   =  0,
    /* @T1@ </Delay> */

    /* @T1@ <Delay Name="2ms runnable 0 delay"> */
    T1_DL_2MS_R0_DELAY_CORE0        =  1,
    /* @T1@ </Delay> */

    /* Number of delays */
    T1_NOF_DELAYS_CORE0             =  2
}

enum
{
    /* @T1@ <Delay Name="Check Integration Delay"> */
    T1_DL_CHECK_INTEGRATION_CORE1   =  0,
    /* @T1@ </Delay> */

    /* Number of delays */
    T1_NOF_DELAYS_CORE1             =  1
}

/*...
~~~~~~~~~~~~~~~

- The comment of the declaration must be like the example above, because it need to
  be read also by T1-HOST-SW. Only the name in comment can be changed by user.
- The number of delays per core must also be declared. It can be done either by adding
  the parameter [-numberOfDelays](\ref numberOfDelays) per system in *T1_UserCfg.inv*
  or by adding the enumerator [T1_NOF_DELAYS_CORE<coreID>](\ref T1_NOF_DELAYS_CORE0).
  A maximum of 255 delays are allowed per core.
- The value, or we could call it *DelayID*, has to begin with 0.

Delays Usage {#DELAYS_USAGE}
============

The *DelayID* previously declared can be used with T1_DelayRoutine() or
T1_DelayRoutinePC(), the following code example shows how is a delay inserted in a
function.

~~~~~~~~~~~~~~~{.c}
...*/

void T1_CODE T1_CheckIntegrationHandlerPC( T1_uint8Least_t coreId )
{
    T1_uint8Least_t const destCoreId = coreId + 1u < T1_NOF_CORES ? coreId + 1u : 0u;
    T1_uint32_t const temp = *(T1_checkIntegrationPC[coreId]);
    (void)T1_DelayRoutinePC( coreId, T1_DL_CHECK_INTEGRATION_CORE_ALL );
    *(T1_checkIntegrationPC[destCoreId]) = temp + coreId + 1u;
}

/*...*/

void 2msRunnable0_Core0( void )
{
    /*...*/
    (void)T1_DelayRoutinePC( 0u, T1_DL_2MS_R0_DELAY_CORE0 );
    /*...*/
}

/*...
~~~~~~~~~~~~~~~

After the delays are declared and inserted, they can be found and set up in the
T1-HOST-SW target control under T1.delay. Please see the T1.help for more
information.

Reset Delays {#DELAYS_RESET}
============

All delays can be reset using T1_ResetDelays() and T1_ResetDelaysPC(). The following
code example shows how to reset all delays in an error hook called in case of failed
activation, additionally halting the tracing to capture the state of the application.

~~~~~~~~~~~~~~~{.c}
...*/

void ErrorHook( OS_status_t errorType, OS_errInfo_t additionalInfo )
{
    /* AUTOSAR E_OS_ACTIVATION */
    if( OS_ERR_OVERLOAD == errorType )
    {
        T1_uint8Least_t const coreId = T1_GetCoreIdOffset( );
        /* Reset delays to 0 in case of failed activation */
        (void)T1_ResetDelaysPC( coreId );
        /* Trace failed activation supposing additionalInfo is the task id */
        T1_TraceEventPC( coreId, T1_ACTIVATION_FAILED, additionalInfo );
        /* Halt tracing on this core */
        (void)T1_SetStopTriggerPC( coreId, T1_TRACE_BUFFER_ENTRIES_PC( coreId ) >> 1 );
    }
}

/*...
~~~~~~~~~~~~~~~

\note The T1-HOST-SW will only update the list of delays once on startup. Thus
      changes to the delays on the target side during runtime will not get
      reflected on the host side until a new connection is established.

Initialize Delays {#DELAYS_INIT}
=================

All delays will be reset to *0s* during T1_Init(). It is possible to initialize them
to other values using the T1_InitDelays() and T1_InitDelaysPC() services. The initial
values can be set via the invocation file parameter
[-allocateDL](\ref allocateDL).

~~~~~~~~~~~~~~~{.c}
...*/

if( T1_OK != T1_InitPC( coreId, T1_pluginTable ) )
{
    for( ;; )
    {
        /* Infinite loop to trap init failure */
    }
}

(void)T1_InitDelaysPC( coreId );

/*...
~~~~~~~~~~~~~~~

\note The T1-HOST-SW will only update the list of delays once on startup. Thus
      changes to the delays on the target side during runtime will not get
      reflected on the host side until a new connection is established.

*/

/* clang-format on */
#endif /* T1_DOXYGEN_ONLY */

#endif /* T1_DELAY_INTERFACE_H_ */
