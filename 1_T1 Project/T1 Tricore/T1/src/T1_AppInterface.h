/*********************************************************************************//*!
*   \file           T1_AppInterface.h
*
*   \brief          Application-specific declarations and macros for T1
*
*   $Author: jialinli $
*
*   $Revision: 120 $
*
*   \copyright GLIWA GmbH embedded systems, Weilheim i.OB. All rights reserved
*************************************************************************************/

#ifndef T1_APPINTERFACE_H_
#define T1_APPINTERFACE_H_ (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*
 * If single core, or core ID register content is equal to the T1 logical core ID
 * offset, the T1 headers contain a suitable default and you should define nothing
 * here. Otherwise define T1_GetCoreIdOffset here to read the hardware core ID
 * register and return the appropriate T1 core ID offset.
 * #define T1_GetCoreIdOffset( ) ...
 */
#define T1_ENABLE (1)
#include "T1_config.h"
/* Uncomment to use T1_WAIT and T1_RESUME with T1.cont enabled */
/* #define T1_WAIT_RESUME (1) */
#include "T1_baseInterface.h"
#include "T1_scopeInterface.h"
#include "T1_delayInterface.h"
#define T1_CONT_DIRECT_ID_MAPPINGS (1)
#include "T1_contInterface.h"
#include "T1_flexInterface.h"
#include "T1_modInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#ifdef T1_ENABLE

#if ! defined T1_GET_TRACE_TIME
/* Read non-memory-mapped and/or core-specific trace timer */
#   define T1_GET_TRACE_TIME( ) \
        <replace with C code, probably based on one of the following examples>
/* AURIX 2G STM0_TIM0 divided by 4             ( *(T1_tickUint_t *)(0xF0001010uL) >> 2 ) */
/* TriCore performance counter divided by 2   ( (T1_tickUint_t)(__mfcr( 0xFC04 )) >> 1 ) */
/* MPC5xxx read via address cached in SPRG7       ( *(T1_tickUint_t *)(__mfspr( 263 )) ) */
/* MPC5xxx TimeBase low word (TBL) divided by 4 ( (T1_tickUint_t)(__mfspr( 268 )) >> 2 ) */
#endif /* defined T1_GET_TRACE_TIME */

#if defined T1_DEFN_CONT_UNMAP_CORE_ID
T1_DEFN_CONT_UNMAP_CORE_ID
#endif /* defined T1_DEFN_CONT_UNMAP_CORE_ID */

#if defined T1_CONT_DIRECT_ID_MAPPINGS
#   define T1_CONT_DEFAULT_CONFIG_STOPWATCH( idx_ ) T1_CONT_CET_STOPWATCH( idx_ )
#endif /* defined T1_CONT_DIRECT_ID_MAPPINGS */
#define T1_CONT_DEFAULT_CONFIG_CONSTRAINT           T1_CONT_INVALID_CONSTRAINT

#if defined T1_NOF_CORES
#   define INC_T1_ERROR_COUNT( coreId_ )    \
    ( T1_errorCount[(coreId_)] < 255u ? ++T1_errorCount[(coreId_)] : 255u )
#else /* single core */
#   define INC_T1_ERROR_COUNT( coreId_ )    \
    ( T1_errorCount < 255u ? ++T1_errorCount : 255u )
#endif /* defined T1_NOF_CORES */

/* @T1@ <AppFeature Name="T1_AF_TRACE_STARTUP"> */
#define T1_AF_TRACE_STARTUP                 0x00000001uL /* capture start-up of the ECU */
/* @T1@ </AppFeature> */
/* @T1@ <AppFeature Name="T1_AF_ALLOW_TRIGGER"> */
#define T1_AF_ALLOW_TRIGGER                 0x00000002uL /* permit triggering (trace capture) */
/* @T1@ </AppFeature> */
/* @T1@ <AppFeature Name="T1_AF_ALLOW_TRACEDATA"> */
#define T1_AF_ALLOW_TRACEDATA               0x00000004uL /* permit T1_TraceData */
/* @T1@ </AppFeature> */
/* @T1@ <AppFeature Name="T1_AF_MEASURE_T1_HANDLER"> */
#define T1_AF_MEASURE_T1_HANDLER            0x00000008uL /* capture T1_AppHandler calls */
/* @T1@ </AppFeature> */
/*----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/

/* @T1@ <SystemElement Name="T1.cont error callback for core 0" Type="UserEvent"> */
#define T1_UE_T1_CONT_ERR_CORE0             0x20
/* @T1@ </SystemElement > */
/* @T1@ <SystemElement Name="T1.cont error callback for core 1" Type="UserEvent"> */
#define T1_UE_T1_CONT_ERR_CORE1             0x21
/* @T1@ </SystemElement > */
/* @T1@ <SystemElement Name="T1.cont error callback for core 2" Type="UserEvent"> */
#define T1_UE_T1_CONT_ERR_CORE2             0x22
/* @T1@ </SystemElement > */
/* @T1@ <SystemElement Name="T1.cont error callback for core 3" Type="UserEvent"> */
#define T1_UE_T1_CONT_ERR_CORE3             0x23
/* @T1@ </SystemElement > */
/* @T1@ <SystemElement Name="T1.cont error callback for core 4" Type="UserEvent"> */
#define T1_UE_T1_CONT_ERR_CORE4             0x24
/* @T1@ </SystemElement > */
/* @T1@ <SystemElement Name="T1.cont error callback for core 5" Type="UserEvent"> */
#define T1_UE_T1_CONT_ERR_CORE5             0x25
/* @T1@ </SystemElement > */
/* @T1@ <SystemElement Name="T1.cont CPU load callback for core 0" Type="UserEvent"> */
#define T1_UE_CPU_LOAD_CALLBACK_CORE0       0x26
/* @T1@ </SystemElement> */
/* @T1@ <SystemElement Name="T1.cont CPU load callback for core 1" Type="UserEvent"> */
#define T1_UE_CPU_LOAD_CALLBACK_CORE1       0x27
/* @T1@ </SystemElement> */
/* @T1@ <SystemElement Name="T1.cont CPU load callback for core 2" Type="UserEvent"> */
#define T1_UE_CPU_LOAD_CALLBACK_CORE2       0x28
/* @T1@ </SystemElement> */
/* @T1@ <SystemElement Name="T1.cont CPU load callback for core 3" Type="UserEvent"> */
#define T1_UE_CPU_LOAD_CALLBACK_CORE3       0x29
/* @T1@ </SystemElement> */
/* @T1@ <SystemElement Name="T1.cont CPU load callback for core 4" Type="UserEvent"> */
#define T1_UE_CPU_LOAD_CALLBACK_CORE4       0x2A
/* @T1@ </SystemElement> */
/* @T1@ <SystemElement Name="T1.cont CPU load callback for core 5" Type="UserEvent"> */
#define T1_UE_CPU_LOAD_CALLBACK_CORE5       0x2B
/* @T1@ </SystemElement> */

/*----------------------------------------------------------------------------------*/

/* @T1@ <SystemElement Name="T1_Handler" Type="Stopwatch" SID="2" > */
#define T1_SW_T1_HANDLER_CORE0              0u
/* @T1@ </SystemElement> */
#define T1_NOF_USER_STPWS_CORE0             1u
/*----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/* Event Chain IDs: */
#define T1_EVTCHN_0_ID                      0u

/*----------------------------------------------------------------------------------*/

/* T1.delay: Core0 */
enum
{
    /* @T1@ <Delay Name="Task0 Delay" SID="2"> */
    T1_DL_TASK0_CORE0_ID        =  0,
    /* @T1@ </Delay> */
    T1_NOF_DELAYS_CORE0         =  1
};

/* T1.delay: Core1 */
enum
{
    /* @T1@ <Delay Name="Task0 Delay" SID="3"> */
    T1_DL_TASK0_CORE1_ID        =  0,
    /* @T1@ </Delay> */
    T1_NOF_DELAYS_CORE1         =  1
};

/* T1.delay: Core2 */
enum
{
    /* @T1@ <Delay Name="Task0 Delay" SID="4"> */
    T1_DL_TASK0_CORE2_ID        =  0,
    /* @T1@ </Delay> */
    T1_NOF_DELAYS_CORE2         =  1
};

/* T1.delay: Core3 */
enum
{
    /* @T1@ <Delay Name="Task0 Delay" SID="5"> */
    T1_DL_TASK0_CORE3_ID        =  0,
    /* @T1@ </Delay> */
    T1_NOF_DELAYS_CORE3         =  1
};

/* T1.delay: Core4 */
enum
{
    /* @T1@ <Delay Name="Task0 Delay" SID="6"> */
    T1_DL_TASK0_CORE4_ID        =  0,
    /* @T1@ </Delay> */
    T1_NOF_DELAYS_CORE4         =  1
};

/* T1.delay: Core5 */
enum
{
    /* @T1@ <Delay Name="Task0 Delay" SID="7"> */
    T1_DL_TASK0_CORE5_ID        =  0,
    /* @T1@ </Delay> */
    T1_NOF_DELAYS_CORE5         =  1
};


/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_DeclarePluginTable(T1_pluginTable);
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_8
#   include "T1_MemMap.h"
T1_EXTERN T1_uint8_t T1_errorCount
#   if defined T1_NOF_CORES
                                    [T1_NOF_CORES]
#   endif /* defined T1_NOF_CORES */
                                                    ;
#   define T1_STOP_SEC_NO_INIT_8
#   include "T1_MemMap.h"

#endif /* T1_ENABLE */

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for global functions ------------------------------------*/
/*----------------------------------------------------------------------------------*/

/* wrapper functions defined in T1_AppInterface.c */
#   define T1_START_SEC_CODE
#   include "T1_MemMap.h"
#   if defined T1_NOF_CORES
T1_EXTERN void T1_CODE T1_AppSetStopTriggerAllCores( T1_uint8Least_t coreId, T1_nofEntries_t afterXevents );
#   else /* single core */
#       define T1_AppSetStopTriggerAllCores( coreId_, afterXevents_ ) ( (void)T1_SetStopTrigger( afterXevents_ ) )
#   endif /* defined T1_NOF_CORES */
T1_EXTERN void T1_CODE T1_AppInit( void );
T1_EXTERN void T1_CODE T1_AppBackgroundHandler( void );
T1_EXTERN void T1_CODE T1_AppHandler( void );
T1_EXTERN void T1_CODE T1_AppRxCallback( T1_uint8_t const * pRxData );
T1_EXTERN void T1_CODE T1_AppEnableUnsafePlugins( void );
#   define T1_STOP_SEC_CODE
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_8
#   include "T1_MemMap.h"
/* Undefined symbol to catch an invalid event chain index. */
T1_EXTERN T1_uint8_t T1_invalidCETeventChainIdx;
#   define T1_STOP_SEC_NO_INIT_8
#   include "T1_MemMap.h"


/*----------------------------------------------------------------------------------*/

#endif /* T1_APPINTERFACE_H_ */
