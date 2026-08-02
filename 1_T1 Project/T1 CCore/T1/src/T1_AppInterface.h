/************************************************************************************/
/*! \file           T1_AppInterface.h
 *
 *  \brief          Application-specific declarations and macros for T1
 *
 *  $Author: jialinli $
 *
 *  $Revision: 370 $
 *
 *  \copyright GLIWA embedded systems GmbH & Co. KG, Weilheim i.OB. All rights reserved
 ************************************************************************************/

#ifndef T1_APPINTERFACE_H_
#define T1_APPINTERFACE_H_ ( 1 )
#define T1_ENABLE
//#define T1_DISABLE_T1_FLEX  (1)/* WangM */
/*----------------------------------------------------------------------------------*/
/*--- macros required before header includes ---------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && 0
/*
 * Replace the dummy #define T1_GET_RAW_TIME, unless using the same memory-mapped
 * timer for every core, in which case T1_GET_RAW_TIME is generated in T1_config.h
 * and this code must be removed or disabled.
 */
/* Read non-memory-mapped and/or core-specific trace timer, see examples below. */
#    define T1_GET_RAW_TIME( ) ( (T1_tickUint_t)( 0 /* dummy */ ) )
/* TriCore performance counter                ( (T1_tickUint_t)(__mfcr( 0xFC04 )) ) */
/* MPC5xxx read via address cached in SPRG7  ( *(T1_tickUint_t *)(__mfspr( 263 )) ) */
/* MPC5xxx TimeBase low word (TBL)              ( (T1_tickUint_t)(__mfspr( 268 )) ) */
#endif /* defined T1_ENABLE && 0 */

/*!
 * \def T1_GetCoreIdOffset
 * The T1-TARGET-SW provides a default implementation, using the appropriate hardware
 * register, if there is no user macro of this name and if the core ID register
 * content is equal to the T1 logical core ID offset.
 * Otherwise it is possible to define it at the beginning of T1_AppInterface.h, before
 * all headers inclusion to read the hardware core ID register and return the
 * appropriate T1 core ID offset.
 * \returns the zero-based T1 logical core index
 */
/*
 * For multi-core T1 integrations with Arm cores this must be always defined here.
 * For example, with the ST Stellar MCU we read the MPIDR register and return 0..5:
 *  #define T1_GetCoreIdOffset( ) ({                                        \
 *      T1_uint32_t mpidr, temp;                                            \
 *      __asm( "MRC p15, 0, %0, c0, c0, 5" : "=r" (mpidr) :: "memory" );    \
 *      temp = mpidr & ~(mpidr >> 1);                                       \
 *      temp = temp + (temp >> 7);                                          \
 *      temp & 0xFFu;                                                       \
 *  })
 */

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_config.h"
#include "T1_baseInterface.h"
#include "T1_scopeInterface.h"
#include "T1_delayInterface.h"
#include "T1_contInterface.h"
#include "T1_flexInterface.h"
#include "T1_modInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/* Backwards compatibility. */
#define T1_AppRxCallback( _pData ) T1_AppReceiveFrame( ( _pData ), 8u )

#if defined T1_ENABLE

#    if !defined T1_GET_RAW_TIME
#       error T1_GET_RAW_TIME is not generated in T1_config.h and must be defined in T1_AppInterface.h, see +++
#    endif /* ! defined T1_GET_RAW_TIME */

#    if defined T1_DEFN_CONT_UNMAP_CORE_ID
T1_DEFN_CONT_UNMAP_CORE_ID
#    endif /* defined T1_DEFN_CONT_UNMAP_CORE_ID */

/*!
 * Default configuration for all stopwatches. Possible values are
 * #T1_CONT_CET_STOPWATCH, #T1_CONT_GET_STOPWATCH and #T1_CONT_DATA_AGE_STOPWATCH.
 * See \ref USER_STOPWATCHES.
 */
#    define T1_CONT_DEFAULT_CONFIG_STOPWATCH( idx_ ) T1_CONT_CET_STOPWATCH( idx_ )
/*!
 * Default configuration allocating constraints to be used by the T1-HOST-SW.
 * This macro needs to be commented to manually configure constraints, see
 * \ref CONSTRAINTS.
 */
#    define T1_CONT_DEFAULT_CONFIG_CONSTRAINT        T1_CONT_INVALID_CONSTRAINT

/*!
 * Each remote core T1.cont semaphore is used by two cores: the tracing core and the
 * core that runs the T1.cont analysis.
 */
#    define T1_CONT_REMOTE_NOF_SEMAPHORE_USERS       ( 2u )

/*!
 * \def INC_T1_ERROR_COUNT_
 * \brief Increase the error counter and trace a user event indicating the core
 * concerned. Halts the tracing if T1_AF_ALLOW_TRIGGER is set.
 * \param[in] coreId_         the T1 logical ID of the calling core
 * \param[in] analyzedCoreId_ the T1 logical ID to record in the user event payload
 */
#    define INC_T1_ERROR_COUNT_( coreId_, analyzedCoreId_ )                          \
        do                                                                           \
        {                                                                            \
            T1_errorCount[coreId_] < 255u ? ++T1_errorCount[coreId_] : 255u;         \
            T1_TraceEventUMPC( ( coreId_ ),                                          \
                               T1_COMBINE_EVENT_INFO( T1_UE_T1_ERR_CORE_ALL,         \
                                                      ( analyzedCoreId_ ) ) );       \
            if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRIGGER ) )                         \
            {                                                                        \
                T1_SetStopTriggerPC( ( coreId_ ),                                    \
                                     T1_BUFFER_SIZE_PC( coreId_ ) >> 1u );           \
            }                                                                        \
        }                                                                            \
        while( 0 )
/*!
 * \def INC_T1_ERROR_COUNT
 * \brief Increase the error counter and trace a user event indicating the core
 * concerned. Halts the tracing if T1_AF_ALLOW_TRIGGER is set.
 * \param[in] coreId_         the T1 logical ID of the calling core
 */
#    if 1 == T1_NOF_CORES
#        define INC_T1_ERROR_COUNT( coreId_ ) INC_T1_ERROR_COUNT_( 0u, 0u )
#    else /* 1 < T1_NOF_CORES */
#        define INC_T1_ERROR_COUNT( coreId_ )                                        \
            INC_T1_ERROR_COUNT_( ( coreId_ ), ( coreId_ ) )
#    endif /* 1 == T1_NOF_CORES */

/*!
 * \def INC_T1_ERROR_COUNT_REMOTE
 * \brief Increase the error counter and trace a user event indicating the core
 * concerned. Can be used in context where T1.cont remote core is used or when a
 * non-communicating core calls T1_AppReceiveFrame(). Halts the tracing
 * if T1_AF_ALLOW_TRIGGER is set.
 * \param[in] coreId_         the T1 logical ID of the calling core
 * \param[in] analyzedCoreId_ the T1 logical ID of the core concerned by the issue
 */
#    if 1 == T1_NOF_CORES
#        define INC_T1_ERROR_COUNT_REMOTE( coreId_, analyzedCoreId_ )                \
            INC_T1_ERROR_COUNT_( 0u, 0u )
#    else /* 1 < T1_NOF_CORES */
#        define INC_T1_ERROR_COUNT_REMOTE( coreId_, analyzedCoreId_ )                \
            INC_T1_ERROR_COUNT_( ( coreId_ ), ( analyzedCoreId_ ) )
#    endif /* 1 == T1_NOF_CORES */

/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_DeclarePluginTable( T1_pluginTable );
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    define T1_START_SEC_VAR_POWER_ON_CLEARED_8
#    include "T1_MemMap.h"
T1_EXTERN T1_uint8_t T1_SEC_VAR_POWER_ON_CLEARED_8 T1_errorCount[T1_NOF_CORES];
#    define T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#    include "T1_MemMap.h"

#    if !defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE
#        define T1_START_SEC_VAR_CLEARED_32
#        include "T1_MemMap.h"
/*! \brief Shared data for remote core T1.cont pairs of cores. */
T1_EXTERN T1_bakery_t T1_SEC_VAR_CLEARED_32
    T1_contRemoteSemPC[T1_NOF_CORES][T1_CONT_REMOTE_NOF_SEMAPHORE_USERS];
#        define T1_STOP_SEC_VAR_CLEARED_32
#        include "T1_MemMap.h"
#    endif /* ! defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE */

#    if 1 < T1_NOF_CORES
#        define T1_START_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"
T1_EXTERN T1_uint8_t T1_SEC_VAR_POWER_ON_CLEARED_8
    T1_coreTriggerCounter[T1_NOF_CORES];
#        define T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"

#        define T1_START_SEC_VAR_POWER_ON_CLEARED_16
#        include "T1_MemMap.h"
T1_EXTERN T1_uint16_t T1_SEC_VAR_POWER_ON_CLEARED_16 T1_afterXevents;
#        define T1_STOP_SEC_VAR_POWER_ON_CLEARED_16
#        include "T1_MemMap.h"
#    endif /* 1 < T1_NOF_CORES */

#    if defined T1_COMMS_SHARED_MEM
#        define T1_CORE_COMMS_START_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"
/* Read and written by T1-TARGET-SW */
T1_EXTERN T1_uint8_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8
    T1_targetToHostArray[T1_GCP_MAX_TX_FRAME_SIZE];
T1_EXTERN T1_uint8_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8
    T1_targetToHostHandshakeAnnounce;
T1_EXTERN T1_uint8_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8
    T1_hostToTargetHandshakeAcknowledge;
/* Only read by T1-TARGET-SW (except for in T1_AppInit) */
T1_EXTERN T1_uint8_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8
    T1_hostToTargetArray[T1_GCP_MAX_RX_FRAME_SIZE];
T1_EXTERN T1_uint8_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8
    T1_hostToTargetHandshakeAnnounce;
T1_EXTERN T1_uint8_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8
    T1_targetToHostHandshakeAcknowledge;
#        define T1_CORE_COMMS_STOP_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"

#        define T1_CORE_COMMS_START_SEC_VAR_POWER_ON_CLEARED_16
#        include "T1_MemMap.h"
/* Read and written by T1-TARGET-SW */
T1_EXTERN T1_uint16_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_16
    T1_targetToHostFrameLength;
/* Only read by T1-TARGET-SW (except for in T1_AppInit) */
T1_EXTERN T1_uint16_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_16
    T1_hostToTargetFrameLength;
#        define T1_CORE_COMMS_STOP_SEC_VAR_POWER_ON_CLEARED_16
#        include "T1_MemMap.h"
#    endif /* defined T1_COMMS_SHARED_MEM */

#    if defined T1_CHECK_INTEGRATION
#        define T1_START_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"
T1_EXTERN T1_uint8_t T1_SEC_VAR_POWER_ON_CLEARED_8 T1_checkIntegrationGlobal;
#        define T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"
#        define T1_START_SEC_CONST_8
#        include "T1_MemMap.h"
T1_EXTERN T1_uint8_t * const T1_SEC_CONST_8 T1_checkIntegrationPC[];
#        define T1_STOP_SEC_CONST_8
#        include "T1_MemMap.h"
#    endif /* defined T1_CHECK_INTEGRATION */

#endif /* defined T1_ENABLE */

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for global functions ------------------------------------*/
/*----------------------------------------------------------------------------------*/

/* wrapper functions defined in T1_AppInterface.c */
#define T1_START_SEC_CODE
#include "T1_MemMap.h"
T1_EXTERN void T1_CODE T1_AppSetStopTriggerAllCores( T1_uint8Least_t coreId,
                                                     T1_nOfEntries_t afterXevents );
T1_EXTERN void T1_CODE T1_AppInit( void );
T1_EXTERN void T1_CODE T1_AppBackgroundHandler( void );
T1_EXTERN void T1_CODE T1_AppHandler( void );
T1_EXTERN void T1_CODE T1_AppReceiveFrame( T1_uint8_t const T1_FARPTR pData,
                                           T1_frameSize_t nOfBytes );
#if defined T1_POLLING_TRANSMIT
void T1_CODE T1_AppReadData( T1_uint8_t const **ppData, T1_frameSize_t *pNOfBytes );
#else /* !defined T1_POLLING_TRANSMIT */
#    define T1_AppReadData( ppData_, pNOfBytes_ ) ( (void)0 )
#endif /* defined T1_POLLING_TRANSMIT */

#if defined T1_ENABLE && defined T1_CHECK_INTEGRATION
#    if !defined T1_CHECK_INTEGRATION_INV_PARAM
#        error Please use the invocation file parameter -checkIntegration to enable the check integration feature!
#    endif /* ! defined T1_CHECK_INTEGRATION_INV_PARAM */
#    if !defined T1_SW_CHECK_INTEGRATION_CORE_ALL
#        error The stopwatch T1_SW_CHECK_INTEGRATION_CORE_ALL used by T1_CHECK_INTEGRATION must be defined!
#    endif /* ! defined T1_SW_CHECK_INTEGRATION_CORE_ALL */
#    if !defined T1_UDE_CHECK_INTEGRATION_SYNCTIMER_CORE_ALL
#        error The user data event T1_UDE_CHECK_INTEGRATION_SYNCTIMER_CORE_ALL used by T1_CHECK_INTEGRATION must be defined!
#    endif /* ! defined T1_UDE_CHECK_INTEGRATION_SYNCTIMER_CORE_ALL */
#    if !defined T1_DL_CHECK_INTEGRATION_CORE_ALL
#        error The delay T1_DL_CHECK_INTEGRATION_CORE_ALL used by T1_CHECK_INTEGRATION must be defined!
#    endif /* ! defined T1_DL_CHECK_INTEGRATION_CORE_ALL */
T1_EXTERN void T1_CODE T1_CheckIntegrationInitPC( T1_uint8Least_t coreId );
T1_EXTERN void T1_CODE T1_CheckIntegrationHandlerPC( T1_uint8Least_t coreId );
#    define T1_CheckIntegrationInit( )                                               \
        T1_CheckIntegrationInitPC( T1_GetCoreIdOffset( ) )
#    define T1_CheckIntegrationHandler( )                                            \
        T1_CheckIntegrationHandlerPC( T1_GetCoreIdOffset( ) )
#else /* ! defined T1_ENABLE || ! defined T1_CHECK_INTEGRATION */
#    define T1_CheckIntegrationInitPC( coreId_ )    ( (void)0 )
#    define T1_CheckIntegrationHandlerPC( coreId_ ) ( (void)0 )
#    define T1_CheckIntegrationInit( )              ( (void)0 )
#    define T1_CheckIntegrationHandler( )           ( (void)0 )
#endif /* defined T1_ENABLE && defined T1_CHECK_INTEGRATION */
#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

/*----------------------------------------------------------------------------------*/

#endif /* T1_APPINTERFACE_H_ */
