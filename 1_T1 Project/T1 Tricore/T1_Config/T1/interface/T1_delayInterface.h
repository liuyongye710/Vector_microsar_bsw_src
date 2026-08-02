/*********************************************************************************//*!
*   \file           T1_delayInterface.h
*
*   \brief          T1.delay interface declarations and macros
*
*   \par Visibility
*                   External
*
*   \author alexandrebau
*
*   \version 2.5.5.0 r40022
*
*   \copyright GLIWA GmbH embedded systems, Weilheim i.OB. All rights reserved
*************************************************************************************/

#ifndef T1_DELAY_INTERFACE_H_
#define T1_DELAY_INTERFACE_H_ (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_baseInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*! \brief Identifier of a given delay on its core. */
typedef T1_uint8_t              T1_delayId_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Number of trace timer ticks for which to delay. */
typedef T1_uint32_t             T1_delay_t;
/*----------------------------------------------------------------------------------*/
/*! \brief T1.base global data for one core. */
typedef struct {
    T1_uint8_t                  delayTxState;
} T1_delayGlobals_t;

/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN T1_delay_t    * const T1_SEC_CONST_32 T1_delaysPC[];
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_DeclarePlugin( T1_delayPluginStruct );
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32
#   include "T1_MemMap.h"
T1_EXTERN T1_delay_t            T1_SEC_NO_INIT_32 T1_delays[];
#   define T1_STOP_SEC_NO_INIT_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_8
#   include "T1_MemMap.h"
/*! \brief For each core, the number of configured delays. */
T1_EXTERN T1_uint8_t const      T1_SEC_CONST_8 T1_nofDelaysPC[];
/*! \brief The number of configured delays. */
T1_EXTERN T1_uint8_t const      T1_SEC_CONST_8 T1_nofDelays;
#   define T1_STOP_SEC_CONST_8
#   include "T1_MemMap.h"

#if defined T1_NOF_CORES && !defined T1_MULTICORE_CLONE
#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN T1_delayGlobals_t * const T1_SEC_CONST_32 T1_delayGlobalsPC[];
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"
#elif defined T1_MULTICORE_CLONE
#   define T1_START_SEC_NO_INIT_32_CLONE
#   include "T1_MemMap.h"
T1_EXTERN T1_delayGlobals_t T1_SEC_NO_INIT_32_CLONE T1_delayGlobals;
#   define T1_STOP_SEC_NO_INIT_32_CLONE
#   include "T1_MemMap.h"
#else
#   define T1_START_SEC_NO_INIT_32
#   include "T1_MemMap.h"
T1_EXTERN T1_delayGlobals_t T1_SEC_NO_INIT_32 T1_delayGlobals;
#   define T1_STOP_SEC_NO_INIT_32
#   include "T1_MemMap.h"
#endif /* T1_NOF_CORES */

#endif /* #if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY */

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_DELAY_PLUGIN_ID                      (3u)

#if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY
/*! \brief T1.delay entry in plugin table. */
#   define T1_delayPlugin                       (&T1_delayPluginStruct)
#else
#   define T1_delayPlugin                       (T1_DISABLED_PLUGIN)
#endif

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for global functions ------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY

#   define T1_START_SEC_CODE
#   include "T1_MemMap.h"
#   if defined T1_NOF_CORES
/*! \brief Perform the delay corresponding to the given identifier. See \ref PC and \ref DELAYSDECLARATION. */
#       define T1_DelayRoutine( id_ )    T1_DelayRoutinePC( T1_GetCoreIdOffset( ), (id_) )
/*! \brief Reset all delays for this core to zero. See \ref PC and \ref DELAYSRESET. */
#       define T1_ResetDelays( )         T1_ResetDelaysPC( T1_GetCoreIdOffset( ) )
/*! \brief Reset all delays for this core to zero. See \ref PC and \ref DELAYSRESET. */
T1_EXTERN void        T1_CODE T1_ResetDelaysPC( T1_uint8Least_t coreId );
/*! \brief Perform the delay corresponding to the given identifier. See \ref PC and \ref DELAYSDECLARATION. */
T1_EXTERN T1_status_t T1_CODE T1_DelayRoutinePC( T1_uint8Least_t coreId, T1_delayId_t id );
/*! \brief Internal: Consume a number trace timer ticks, see T1_GetTraceTime(). See \ref PC. */
T1_EXTERN void        T1_CODE T1_DelayForTimerTicksPC( T1_uint8Least_t coreId, T1_delay_t timerTicks );
#   else /* defined T1_NOF_CORES */
/*! \brief Perform the delay corresponding to the given identifier. See \ref PC and \ref DELAYSDECLARATION. */
#       define T1_DelayRoutinePC( coreId_, id_ ) T1_DelayRoutine( id_ )
/*! \brief Reset all delays for this core to zero. See \ref PC and \ref DELAYSRESET. */
#       define T1_ResetDelaysPC( coreId_ ) T1_ResetDelays( )
/*! \brief Reset all delays for this core to zero. See \ref PC and \ref DELAYSRESET. */
T1_EXTERN void        T1_CODE T1_ResetDelays( void );
/*! \brief Perform the delay corresponding to the given identifier. See \ref PC and \ref DELAYSDECLARATION. */
T1_EXTERN T1_status_t T1_CODE T1_DelayRoutine( T1_delayId_t id );
/*! \brief Internal: Consume a number trace timer ticks, see T1_GetTraceTime(). See \ref PC. */
T1_EXTERN void        T1_CODE T1_DelayForTimerTicks( T1_delay_t timerTicks );
#   endif /* defined T1_NOF_CORES */

#   define T1_STOP_SEC_CODE
#   include "T1_MemMap.h"

#else  /* #if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY */

#   define T1_DelayRoutine( id_ )               (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_ResetDelays( )                    ((void)0)
#   define T1_DelayRoutinePC( coreId_, id_ )    (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_ResetDelaysPC( coreId_ )          ((void)0)

#endif /* #if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY */

/*----------------------------------------------------------------------------------*/
/*--- documentation ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_DOXYGEN_ONLY

/*!
 * \page DELAYS Delays

T1 delays can be inserted anywhere in the application to increase or vary the CET
of a function.

Declare delays {#DELAYSDECLARATION}
==============

All delays must be declared as a enum in T1_AppInterface.h in order
for the T1-HOST-SW to offer run-time control:

~~~~~~~~~~~~~~~{.c}
...*/

enum
{
    /* @T1@ <Delay Name="Bg task delay"> */
    T1_D_BG_DELAY_ID        =  0,
    /* @T1@ </Delay> */

    /* @T1@ <Delay Name="2ms runnable 0 delay"> */
    T1_D_2MS_R0_DELAY_ID    =  1,
    /* @T1@ </Delay> */

    /* Sum of delays */
    T1_NOF_DELAYS_CORE0     =  2
}

/*...
~~~~~~~~~~~~~~~

The comment of the declaration must be like the example above, because it need to
be read also by T1-HOST-SW. Only the name in comment can be changed by user.

The sum of delays must also be declared at the end of enum.

The value, or we could call it DelayID, has to begin with 0.

Position the delays {#DELAYSPOSITION}
===================

The delayID previously declared can be used with T1_DelayRoutine() or
T1_DelayRoutinePC(), the following code example shows how is a delay inserted in a
function.

~~~~~~~~~~~~~~~{.c}
void 2msRunnable0( void )
{
    ...
    (void)T1_DelayRoutine( T1_D_2MS_R0_DELAY_ID );
    ...
}
~~~~~~~~~~~~~~~

After the delays are declared and inserted, they can be found and set up in the
T1-HOST-SW target control under T1.delay. Please see the T1.help for more
information.

Reset the delays {#DELAYSRESET}
================

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
        /* Reset delays to 0 in case of failed activation */
        T1_ResetDelays();
        /* Trace failed activation supposing additionalInfo is the task id*/
        T1_TraceEvent( T1_ACTIVATION_FAILED, additionalInfo );
        /* Halt tracing */
        (void)T1_SetStopTrigger( T1_bufferSize >> 1 );
    }
}

/*...
~~~~~~~~~~~~~~~

 */

#endif /* T1_DOXYGEN_ONLY */

#endif /* T1_DELAY_INTERFACE_H_ */
