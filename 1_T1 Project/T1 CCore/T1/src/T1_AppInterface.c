/************************************************************************************/
/*! \file           T1_AppInterface.c
 *
 *  \brief          Application-specific interface functions for T1
 *
 *  $Author: jialinli $
 *
 *  $Revision: 370 $
 *
 *  \copyright GLIWA embedded systems GmbH & Co. KG, Weilheim i.OB. All rights reserved
 ************************************************************************************/

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined __TASKING__
/*
 * Avoid harmless but unnecessary clearing of T1_bss sections by the Tasking start-up
 * code.
 * This pragma is disallowed by some compiler options, so you may have to remove it.
 */
#    pragma noclear
#endif /* defined __TASKING__ */

#include "T1_AppInterface.h"
#include "T1_Can.h"/* WangM */

/*----------------------------------------------------------------------------------*/
/*--- Local macros -----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_NOF_CORES
#    error T1_NOF_CORES is undefined, please set -usingMulticoreLibs=true in T1_Cfg.inv
#endif /* defined T1_ENABLE && ! defined T1_NOF_CORES */

/*----------------------------------------------------------------------------------*/
/*--- Optimization pragmas for uniform code generation with widely-used compilers --*/
/*----------------------------------------------------------------------------------*/

#if defined __ghs__
#    pragma ghs OS
#elif defined __TASKING__
#    pragma optimize 2
#elif defined __GNUC__ && !defined __TMS470__ && !defined __clang__                  \
    && !defined __ARMCC_VERSION
#    pragma GCC optimize "Os"
#endif /* compiler */

/*----------------------------------------------------------------------------------*/
/*--- definitions of global variables ----------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE

#    define T1_START_SEC_VAR_POWER_ON_CLEARED_8
#    include "T1_MemMap.h"
/*!
 * Record the number of errors observed in the application interface with T1.
 * It is incremented using #INC_T1_ERROR_COUNT and #INC_T1_ERROR_COUNT_REMOTE.
 */
T1_uint8_t T1_SEC_VAR_POWER_ON_CLEARED_8 T1_errorCount[T1_NOF_CORES];
#    define T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#    include "T1_MemMap.h"

#    if 1 < T1_NOF_CORES
#        define T1_START_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"
/*!
 * T1_coreTriggerCounter[coreId] is incremented when coreId requests a trigger from
 * all other cores. T1_coreTriggerCounter[coreId] is written only from core coreId
 * and is, therefore, parallel-safe.
 */
T1_uint8_t T1_SEC_VAR_POWER_ON_CLEARED_8 T1_coreTriggerCounter[T1_NOF_CORES];
/*!
 * Each core keeps a (shadow) copy of T1_coreTriggerCounter for every core.
 * When they differ, a trigger has occurred. T1_shadowTriggerCounter[coreId] is
 * written (and, indeed read) only from core coreId and is, therefore, parallel-safe.
 */
T1_uint8_t T1_SEC_VAR_POWER_ON_CLEARED_8
    T1_shadowTriggerCounter[T1_NOF_CORES][T1_NOF_CORES];
#        define T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"

#        define T1_START_SEC_VAR_POWER_ON_CLEARED_16
#        include "T1_MemMap.h"
T1_uint16_t T1_SEC_VAR_POWER_ON_CLEARED_16 T1_afterXevents;
#        define T1_STOP_SEC_VAR_POWER_ON_CLEARED_16
#        include "T1_MemMap.h"
#    endif /* 1 < T1_NOF_CORES */

#    define T1_START_SEC_CONST_16
#    include "T1_MemMap.h"
const T1_frameSize_t T1_maxRxFrameBytes T1_SEC_CONST_16 = T1_GCP_MAX_RX_FRAME_SIZE;
const T1_frameSize_t T1_maxTxFrameBytes T1_SEC_CONST_16 = T1_GCP_MAX_TX_FRAME_SIZE;
#    define T1_STOP_SEC_CONST_16
#    include "T1_MemMap.h"

#    define T1_START_SEC_VAR_POWER_ON_CLEARED_8
#    include "T1_MemMap.h"
/*! A buffer for received data between calls to T1_ReceiveFrame() and T1_Handler() */
static union {
    T1_uint8_t u8[T1_GCP_MAX_RX_FRAME_SIZE];
    T1_uint32_t _align32; /* 32-bit alignment may improve performance */
} T1_rxFrameBuffer T1_SEC_VAR_POWER_ON_CLEARED_8;
#    if !defined T1_COMMS_SHARED_MEM_TX
/*!
 * A buffer for data to transmit between calls to T1_TxBufferRequest() and
 * T1_TransmitFrame() and, in the case of the polling model
 * (e.g. diagnostic interface), the data actually being polled out.
 */
static union {
    T1_uint8_t u8[T1_GCP_MAX_TX_FRAME_SIZE];
    T1_uint32_t _align32; /* 32-bit alignment may improve performance */
} T1_txFrameBuffer T1_SEC_VAR_POWER_ON_CLEARED_8;
/*!
 * Indicate that #T1_txFrameBuffer is occupied between T1_TxBufferRequest() and
 * T1_TransmitFrame()
 */
static T1_bool_t volatile T1_SEC_VAR_POWER_ON_CLEARED_8 T1_txFrameBufferAllocated;
#    endif /* ! defined T1_COMMS_SHARED_MEM_TX */

#    define T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#    include "T1_MemMap.h"

#    if defined T1_POLLING_TRANSMIT
#        define T1_START_SEC_VAR_POWER_ON_CLEARED_16
#        include "T1_MemMap.h"
/*!
 * Record the number of bytes of actual data in #T1_txFrameBuffer between
 * T1_TransmitFrame() and the data being polled out.
 */
static T1_uint16_t volatile T1_SEC_VAR_POWER_ON_CLEARED_16 T1_txFrameNOfBytes;
#        define T1_STOP_SEC_VAR_POWER_ON_CLEARED_16
#        include "T1_MemMap.h"
#    endif /* defined T1_POLLING_TRANSMIT */

#    if defined T1_COMMS_SHARED_MEM_TX || defined T1_COMMS_SHARED_MEM_RX
#        define T1_CORE_COMMS_START_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"

#        if defined T1_COMMS_SHARED_MEM_TX
/* Read and written by T1-TARGET-SW */
T1_uint8_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8
    T1_targetToHostArray[T1_GCP_MAX_TX_FRAME_SIZE];
T1_uint8_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8 T1_targetToHostHandshakeAnnounce;
/* Only read by T1-TARGET-SW (except for in T1_AppInit) */
T1_uint8_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8
    T1_targetToHostHandshakeAcknowledge;
#        endif /* defined T1_COMMS_SHARED_MEM_TX */

#        if defined T1_COMMS_SHARED_MEM_RX
/* Only read by T1-TARGET-SW (except for in T1_AppInit) */
T1_uint8_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8
    T1_hostToTargetArray[T1_GCP_MAX_RX_FRAME_SIZE];
T1_uint8_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8 T1_hostToTargetHandshakeAnnounce;
/* Read and written by T1-TARGET-SW */
T1_uint8_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8
    T1_hostToTargetHandshakeAcknowledge;
#        endif /* defined T1_COMMS_SHARED_MEM_RX */

#        define T1_CORE_COMMS_STOP_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"

#        define T1_CORE_COMMS_START_SEC_VAR_POWER_ON_CLEARED_16
#        include "T1_MemMap.h"

#        if defined T1_COMMS_SHARED_MEM_TX
/* Read and written by T1-TARGET-SW */
T1_uint16_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_16 T1_targetToHostFrameLength;
#        endif /* defined T1_COMMS_SHARED_MEM_TX */

#        if defined T1_COMMS_SHARED_MEM_RX
/* Only read by T1-TARGET-SW (except for in T1_AppInit) */
T1_uint16_t T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_16 T1_hostToTargetFrameLength;
#        endif /* defined T1_COMMS_SHARED_MEM_RX */

#        define T1_CORE_COMMS_STOP_SEC_VAR_POWER_ON_CLEARED_16
#        include "T1_MemMap.h"
#    endif /* defined T1_COMMS_SHARED_MEM_TX || defined T1_COMMS_SHARED_MEM_RX */

#    if defined T1_CHECK_INTEGRATION

#        define T1_START_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"
T1_uint8_t T1_SEC_VAR_POWER_ON_CLEARED_8 T1_checkIntegrationGlobal;
#        define T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"

#    endif /* defined T1_CHECK_INTEGRATION */

#endif /* defined T1_ENABLE */

/*----------------------------------------------------------------------------------*/
/*--- definitions of global functions ----------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_START_SEC_CODE
#include "T1_MemMap.h"
/*!
 * Wrapper function for T1_Init(). It also initializes T1_taskAct
 * if tracing cross-core task activations and T1_shadowTriggerCounter
 * on behalf of T1_AppSetStopTriggerAllCores().
 * Call T1_AppInit() on every core in privileged mode
 * - before other T1 services on any core and
 * - after starting the trace timer.
 */
void T1_CODE T1_AppInit( void )
{
#if defined T1_ENABLE
volatile	uint8 tt=1;
    T1_uint8Least_t const coreId = T1_GetCoreIdOffset( );
    T1_errorCount[coreId]        = 0; /* Clear error count */
//if(coreId!=2)
//{
//	while(tt);
//}
#    if defined T1_CROSS_CORE_ACT && 1 < T1_NOF_CORES
    if( 0u == coreId )
    {
        T1_uint8Least_t taskId = T1_MAX_NOF_TASKS;
        do
        {
            T1_taskAct[--taskId] = 0uL;
        }
        while( 0u != taskId );
    }
#    endif /* defined T1_CROSS_CORE_ACT && 1 < T1_NOF_CORES */

    if( T1_OK != T1_InitPC( coreId, T1_pluginTable ) )
    {
        for( ;; )
        {
            /* Infinite loop to trap init failure */
        }
    }

    /*
     * All delays are reset to zero by T1_InitPC. If there are configured, non-zero,
     * initial values, they can be set by calling T1_InitDelaysPC here.
     */
    T1_InitDelaysPC( coreId );

#    if defined T1_POLLING_TRANSMIT
    T1_txFrameNOfBytes = 0u;
#    endif /* defined T1_POLLING_TRANSMIT */

#    if 1 < T1_NOF_CORES
    /* Functionally redundant initialization avoids spurious warnings. */
    T1_afterXevents               = 0u;
    T1_coreTriggerCounter[coreId] = 0u;
    /*
     * Variables used for triggering all cores at the same time,
     * see T1_AppBackgroundHandler() and T1_AppSetStopTriggerAllCores().
     * Initialize T1_shadowTriggerCounter equal to T1_coreTriggerCounter
     * to avoid (spurious) trigger.
     */
    {
        T1_uint8Least_t shadowTriggerIndex = T1_NOF_CORES;
        do
        {
            --shadowTriggerIndex;
            T1_shadowTriggerCounter[coreId][shadowTriggerIndex] =
                T1_coreTriggerCounter[shadowTriggerIndex];
        }
        while( 0u != shadowTriggerIndex );
    }
#    endif /* 1 < T1_NOF_CORES */

    /*
     * NoSusp/NOSUSP variants are used because preemption from traced tasks and ISRs
     * is prohibited in T1_AppInit.
     */

    /*
     * Communications core may not have completed T1_Init at this point on
     * the running core.
     * So we test the T1_initFeatureMask rather than the T1_featureMask to
     * determine whether or not to trigger and capture the start-up trace.
     */
    if( ( T1_initFeatureMask & (T1_featureMask_t)T1_AF_TRACE_STARTUP ) != 0uL )
    {
        /* Capture the start-up trace */
        (void)T1_SetStopTriggerNoSuspPC( coreId,
                                         T1_TRACE_BUFFER_ENTRIES_PC( coreId ) );
    }

    T1_CheckIntegrationInitPC( coreId );

//    T1_CONT_CALIBRATE_OVERHEADS_NOSUSP_PC( coreId );
#endif /* defined T1_ENABLE */
}
/*----------------------------------------------------------------------------------*/
/*!
 * Wrapper function for T1_ContBgHandler().
 * If using more than one core, it can call T1_SetStopTriggerPC() on behalf of
 * an execution of T1_AppSetStopTriggerAllCores() on a different core.
 * T1_ContBgHandler() is not permitted to preempt T1_Handler(), therefore
 * T1_AppBackgroundHandler() is not permitted to preempt T1_AppHandler().
 */
void T1_CODE T1_AppBackgroundHandler( void )
{
#if defined T1_ENABLE
#    if 1 < T1_NOF_CORES || ( !defined T1_DISABLE_T1_CONT && !defined T1_FG_CONT )
    T1_uint8Least_t const coreId = T1_GetCoreIdOffset( );
#    endif /* 1 < T1_NOF_CORES || ! defined T1_DISABLE_T1_CONT */

#    if !defined T1_FG_CONT /* Foreground T1.cont calls no T1_ContBgHandlerPC */
#        if defined T1_CONT_REMOTE
#            if T1_NOF_CORES < 2
#                error T1.cont remote core configured with only one core
#            endif /* T1_NOF_CORES < 2 */
    if( T1_CONT_RC_UNMAP( 0 ) == coreId )
    {
        /* This core runs the T1.cont background handler for T1 logical core ID 0 */
        if( T1_BUSY == T1_ContBgHandlerPC( 0 ) )
        {
            /* T1_ContBgHandlerPC re-entered? */
            INC_T1_ERROR_COUNT_REMOTE( coreId, 0 );
        }
    }
    if( T1_CONT_RC_UNMAP( 1 ) == coreId )
    {
        /* This core runs the T1.cont background handler for T1 logical core ID 1 */
        if( T1_BUSY == T1_ContBgHandlerPC( 1 ) )
        {
            /* T1_ContBgHandlerPC re-entered? */
            INC_T1_ERROR_COUNT_REMOTE( coreId, 1 );
        }
    }
#            if 3 <= T1_NOF_CORES
    if( T1_CONT_RC_UNMAP( 2 ) == coreId )
    {
        /* This core runs the T1.cont background handler for T1 logical core ID 2 */
        if( T1_BUSY == T1_ContBgHandlerPC( 2 ) )
        {
            /* T1_ContBgHandlerPC re-entered? */
            INC_T1_ERROR_COUNT_REMOTE( coreId, 2 );
        }
    }
#            endif /* 3 <= T1_NOF_CORES */
#            if 4 <= T1_NOF_CORES
    if( T1_CONT_RC_UNMAP( 3 ) == coreId )
    {
        /* This core runs the T1.cont background handler for T1 logical core ID 3 */
        if( T1_BUSY == T1_ContBgHandlerPC( 3 ) )
        {
            /* T1_ContBgHandlerPC re-entered? */
            INC_T1_ERROR_COUNT_REMOTE( coreId, 3 );
        }
    }
#            endif /* 4 <= T1_NOF_CORES */
#            if 5 <= T1_NOF_CORES
    if( T1_CONT_RC_UNMAP( 4 ) == coreId )
    {
        /* This core runs the T1.cont background handler for T1 logical core ID 4 */
        if( T1_BUSY == T1_ContBgHandlerPC( 4 ) )
        {
            /* T1_ContBgHandlerPC re-entered? */
            INC_T1_ERROR_COUNT_REMOTE( coreId, 4 );
        }
    }
#            endif /* 5 <= T1_NOF_CORES */
#            if 6 <= T1_NOF_CORES
    if( T1_CONT_RC_UNMAP( 5 ) == coreId )
    {
        /* This core runs the T1.cont background handler for T1 logical core ID 5 */
        if( T1_BUSY == T1_ContBgHandlerPC( 5 ) )
        {
            /* T1_ContBgHandlerPC re-entered? */
            INC_T1_ERROR_COUNT_REMOTE( coreId, 5 );
        }
    }
#            endif /* 6 <= T1_NOF_CORES */
#        else      /* ! defined T1_CONT_REMOTE */
    if( T1_BUSY == T1_ContBgHandlerPC( coreId ) )
    {
        INC_T1_ERROR_COUNT( coreId ); /* T1_ContBgHandlerPC re-entered? */
    }
#        endif     /* defined T1_CONT_REMOTE */
#    endif         /* defined T1_FG_CONT */
    /* At this point it is safe to copy from T1_resultBuffer, for example to NVRAM. */

#    if 1 < T1_NOF_CORES
    /*
     * Check to see if another core has requested a trigger, indicated by a mismatch
     * between counter and shadow counter, see T1_AppSetStopTriggerAllCores().
     */
    {
        T1_uint8Least_t shadowTriggerIndex = T1_NOF_CORES;
        do
        {
            --shadowTriggerIndex;
            if( T1_shadowTriggerCounter[coreId][shadowTriggerIndex]
                != T1_coreTriggerCounter[shadowTriggerIndex] )
            {
                /* Found a difference: reset indices and trigger */
                T1_nOfEntries_t const maxBufferEntries =
                    T1_TRACE_BUFFER_ENTRIES_PC( coreId );
                shadowTriggerIndex = T1_NOF_CORES;
                do
                {
                    --shadowTriggerIndex;
                    T1_shadowTriggerCounter[coreId][shadowTriggerIndex] =
                        T1_coreTriggerCounter[shadowTriggerIndex];
                }
                while( 0u != shadowTriggerIndex );
                /* Stop tracing on this core */
                (void)T1_SetStopTriggerPC( coreId,
                                           T1_afterXevents <= maxBufferEntries
                                               ? T1_afterXevents
                                               : maxBufferEntries );
                /* Stop looking for a counter mismatch. */
                break;
            }
        }
        while( 0u != shadowTriggerIndex );
    }
#    endif /* 1 < T1_NOF_CORES */
#endif     /* defined T1_ENABLE */
}

/*----------------------------------------------------------------------------------*/
/*!
 * Wrapper function for T1_Handler(). Call periodically, for example every 5ms.
 * Different periods can be safely used on different cores, if required.
 * T1_ContBgHandler() is not permitted to preempt T1_Handler(), therefore
 * T1_AppBackgroundHandler() is not permitted to preempt T1_AppHandler().
 */
void T1_CODE T1_AppHandler( void )
{
#if defined T1_ENABLE
    T1_uint8Least_t const coreId = T1_GetCoreIdOffset( );

    /*
     * If the invocation file parameter [-checkIntegration](\ref checkIntegration)
       is true, T1_CheckIntegrationHandlerPC is defined.
     * If the invocation file parameter is false, this should be void.
     */
    T1_CheckIntegrationHandlerPC( coreId );

#    if defined T1_COMMS_SHARED_MEM_RX
    if( T1_COMMS_CORE_OFFSET == coreId )
    {
        /*
         * Poll for new data ready from host to target
         * This could also be moved to a different function if necessary
         */
        if( T1_hostToTargetHandshakeAcknowledge != T1_hostToTargetHandshakeAnnounce )
        {
            /*
             * Executing this before T1_HandlerPC ensures that the new data will be
             * processed as soon as possible, if this is the receiving core.
             */
            T1_AppReceiveFrame( T1_hostToTargetArray, T1_hostToTargetFrameLength );
            /*
             * Ensure that the payload data is read before the "acknowledge" variable
             * is written
             */
            T1_TARGET_DSYNC( );
            /* Acknowledge equals announce indicates that the buffer is free again */
            T1_hostToTargetHandshakeAcknowledge = T1_hostToTargetHandshakeAnnounce;
        }
    }
#    endif /* defined T1_COMMS_SHARED_MEM_RX */

#    if !defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE
    (void)T1_GetSpinlockPC( coreId, T1_contRemoteSemPC[coreId], 0u, 2u, T1_FALSE );
#    endif /* ! defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE */
    if( T1_OK != T1_HandlerPC( coreId ) )
    {
        INC_T1_ERROR_COUNT( coreId );
        /* T1 failure */
    }
#    if !defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE
    T1_ReleaseSpinlockPC( coreId, T1_contRemoteSemPC[coreId], 0u, T1_FALSE );
#    endif /* ! defined T1_DISABLE_T1_CONT && defined T1_CONT_REMOTE*/

#endif /* defined T1_ENABLE */
}

#if defined T1_ENABLE
/*----------------------------------------------------------------------------------*/

void T1_CODE T1_InitCommunications( void )
{
#    if defined T1_COMMS_SHARED_MEM_TX
    /*
     * Announce equals acknowledge indicates that the buffers are free and that the
     * T1-TARGET-SW is free to send a new message.
     */
    T1_targetToHostHandshakeAnnounce = T1_targetToHostHandshakeAcknowledge;
#    else
    T1_txFrameBufferAllocated = T1_FALSE;
#    endif /* defined T1_COMMS_SHARED_MEM_TX */

#    if defined T1_COMMS_SHARED_MEM_RX
    /*
     * Acknowledge equals announce indicates that the buffers are free and that the
     * T1-HOST-SW is free to send a new message.
     */
    T1_hostToTargetHandshakeAcknowledge = T1_hostToTargetHandshakeAnnounce;
#    endif /* T1_COMMS_SHARED_MEM_RX */
}

/*----------------------------------------------------------------------------------*/

T1_uint8_t T1_FARPTR T1_CODE
T1_TxBufferRequest( T1_UNUSED( T1_frameSize_t nOfBytes ) )
{
#    if defined T1_COMMS_SHARED_MEM_TX
    if( T1_targetToHostHandshakeAnnounce == T1_targetToHostHandshakeAcknowledge )
    {
        /* Buffer is free */
        return T1_targetToHostArray;
    }
    else
    {
        /* Wait until buffer is free */
        return T1_NULL;
    }
#    else
    if( T1_txFrameBufferAllocated )
    {
        /* Wait until buffer is free */
        return T1_NULL;
    }

    T1_txFrameBufferAllocated = T1_TRUE;
#        if defined T1_POLLING_TRANSMIT
    T1_txFrameNOfBytes        = 0u;
#        endif /* defined T1_POLLING_TRANSMIT */
    return T1_txFrameBuffer.u8;
#    endif     /* defined T1_COMMS_SHARED_MEM_TX */
}

T1_status_t T1_CODE T1_TransmitFrame( T1_uint8_t const T1_FARPTR pData,
                                      T1_frameSize_t nOfBytes )
{
#    if defined T1_POLLING_TRANSMIT
    (void)pData; /* Suppress warning if pData is unused */

    if( 0u != T1_txFrameNOfBytes )
    {
        return T1_FAILED;
    }

    T1_txFrameNOfBytes = (T1_uint16_t)nOfBytes; /* Data ready to transmit */
    return T1_OK;
#    elif defined T1_COMMS_SHARED_MEM_TX
    (void)pData; /* Suppress warning if pData is unused */

    T1_targetToHostFrameLength = (T1_uint16_t)nOfBytes;
    /* Ensure that the previous write has been performed before continuing */
    T1_TARGET_DSYNC( );
    /*
     * Increment handshake announce variable to indicate that new data is ready to be
     * transferred from the target to the host
     */
    ++T1_targetToHostHandshakeAnnounce;
    /* Transmit always is deemed to have succeeded. */
    return T1_OK;
#    else  /* ! defined T1_POLLING_TRANSMIT */
    T1_status_t txStatus = T1_OK;

    /* TODO: transmit data in T1_txFrameBuffer */
    /*
     * IMPORTANT: Return T1_FAILED if transfer to comms layer failed, so that T1 can
     * retry. Return T1_OK only if message is successfully transferred to the comms
     * layer for immediate or queued transmission.
     */
    /* WangM  start*/
    Std_ReturnType Result = E_OK;
    Result = T1_CanTransmit(pData, nOfBytes);
    if(Result == E_OK)
    {
        txStatus = T1_OK;
    }
    else
    {
        txStatus = T1_FAILED;
    }
	/* WangM  stop*/

    if( T1_OK == txStatus )
    {
        /*
         * Free buffer after it has been read by the comms layer.
         * If the comms layer API call copied the data out of the transmit buffer
         * before indicating success then it can be freed now. Otherwise it might
         * have to be freed in a comms layer callback that indicates that the data has
         * been read (and probably transmitted, also).
         */
        T1_txFrameBufferAllocated = T1_FALSE;
    }
    return txStatus;
#    endif /* defined T1_POLLING_TRANSMIT */
}
#endif /* defined T1_ENABLE */

#if defined T1_POLLING_TRANSMIT

/*!
 * Poll data out of #T1_txFrameBuffer for transmission to the T1-HOST-SW.
 * \param[out] ppData    pointer to data payload to transmit
 * \param[out] pNOfBytes the number of bytes of data to transmit
 */
void T1_CODE T1_AppReadData( T1_uint8_t const **ppData, T1_frameSize_t *pNOfBytes )
{
#    if defined T1_ENABLE
    *ppData    = T1_NULL;
    *pNOfBytes = 0u;
    if( 0u != T1_txFrameNOfBytes )
    {
        *ppData                   = T1_txFrameBuffer.u8;
        *pNOfBytes                = T1_txFrameNOfBytes;
        /*
         * Ensure this thread of execution completes reading #T1_txFrameBuffer
         * before T1_Handler() calls T1_TxBufferRequest() and/or T1_TransmitFrame()
         * as they will write to #T1_txFrameBuffer after seeing #T1_txFrameNOfBytes
         * and #T1_txFrameBufferAllocated clear. Alternatively, clear
         * #T1_txFrameNOfBytes and #T1_txFrameBufferAllocated not here but in a
         * callback that indicates the data has been transmitted.
         */
        T1_txFrameNOfBytes        = 0u;
        T1_txFrameBufferAllocated = T1_FALSE;
    }
#    endif /* defined T1_ENABLE */
}

#endif /* defined T1_POLLING_TRANSMIT */

/*----------------------------------------------------------------------------------*/

/*!
 * Wrapper for T1_ReceiveFrame(). Call this on receipt of a data frame.
 * Adapt parameters to fit the application. This example uses an array of bytes
 * to pass the data. 16- or 32-bit access can (and should) be used if the
 * necessary alignment of the source data can be guaranteed and the processor supports
 * 16- or 32-bit memory access.
 * The data passed to T1_ReceiveFrame() is read at the next call to T1_Handler(), so
 * the incoming data must be cached, see #T1_rxFrameBuffer, unless the source data
 * persists until then. With a typical AUTOSAR COM stack, the source data does not
 * persist and the #T1_rxFrameBuffer is needed.
 * \param[in] pData  pointer to data payload of received frame
 * \param[in] nOfBytes number of bytes of received data
 */
void T1_CODE T1_AppReceiveFrame( T1_uint8_t const T1_FARPTR pData,
                                 T1_frameSize_t nOfBytes )
{
#if defined T1_ENABLE
    T1_uint8Least_t const coreId = T1_GetCoreIdOffset( );
    if( T1_COMMS_CORE_OFFSET != coreId )
    {
        /* Prevent T1_ReceiveFrame from being called on the wrong core. */
        INC_T1_ERROR_COUNT_REMOTE( coreId, T1_COMMS_CORE_OFFSET );
        return;
    }

    {
        /*
         * For large (e.g. Ethernet) frames, try to avoid copying.
         * For small (e.g. classic CAN) frames, an inline, byte loop
         * is faster than a call to memcpy.
         */
        T1_uint16Least_t i;
        for( i = 0u; i < nOfBytes; ++i )
        {
            T1_rxFrameBuffer.u8[i] = pData[i];
        }
    }

    if( T1_OK != T1_ReceiveFrame( T1_rxFrameBuffer.u8, nOfBytes ) )
    {
        INC_T1_ERROR_COUNT( coreId );
        /* T1 failure */
    }
#endif /* defined T1_ENABLE */
}

/*----------------------------------------------------------------------------------*/
/*!
 * Halt tracing on every core. On this core T1_SetStopTriggerPC() is called. For each
 * other core, T1_SetStopTriggerPC() is called from T1_AppBackgroundHandler()
 * executing on that core.
 * \param[in] coreId       the T1 logical ID of the calling core
 * \param[in] afterXevents the number of additional events to trace on this core
 *                         before tracing actually stops, see T1_SetStopTriggerPC()
 */
void T1_CODE T1_AppSetStopTriggerAllCores( T1_uint8Least_t coreId,
                                           T1_nOfEntries_t afterXevents )
{
#if defined T1_ENABLE
    T1_nOfEntries_t const maxBufferEntries = T1_TRACE_BUFFER_ENTRIES_PC( coreId );
#    if 1 == T1_NOF_CORES
    (void)T1_SetStopTrigger( afterXevents <= maxBufferEntries ? afterXevents
                                                              : maxBufferEntries );
#    else  /* 2 or more cores */
    /* Stop tracing on this core */
    if( T1_OK
        == T1_SetStopTriggerPC(
            coreId,
            afterXevents <= maxBufferEntries ? afterXevents : maxBufferEntries ) )
    {
        T1_afterXevents = (T1_uint16_t)afterXevents;
        /* If successful, signal other cores to stop tracing, see
         * T1_AppBackgroundHandler */
        ++T1_coreTriggerCounter[coreId];
    }
#    endif /* T1_NOF_CORES */
#endif     /* defined T1_ENABLE */
}

/*----------------------------------------------------------------------------------*/
#if defined T1_ENABLE
void T1_CODE T1_FeatureMaskChangedPC( T1_uint8Least_t coreId,
                                      T1_featureMask_t featureMask )
{
    /* Insert code here to handle a changed application feature. */
    (void)coreId;      /* Suppress warning if coreId is unused */
    (void)featureMask; /* Suppress warning if featureMask is unused */
}
#endif /* defined T1_ENABLE */

#if defined T1_ENABLE && defined T1_CHECK_INTEGRATION

/*----------------------------------------------------------------------------------*/
/*!
 * Function called from T1_AppInit() to initialize variables used in
 * T1_CheckIntegrationHandlerPC() if the invocation file parameter
 * [-checkIntegration](\ref checkIntegration) is true.
 * If the parameter is not set to true, this function should not be defined/used.
 * Trace the value of the sync timer using T1_UDE_CHECK_INTEGRATION_SYNCTIMER_CORE_ALL
 * to check in the start-up trace the presence of trace timer overflow.
 */
void T1_CODE T1_CheckIntegrationInitPC( T1_uint8Least_t coreId )
{
    T1_uint32_t const syncTime = T1_GET_SYNC_TIME( );
    T1_checkIntegrationGlobal  = 0;

    T1_TraceUint32PC( coreId, T1_UDE_CHECK_INTEGRATION_SYNCTIMER_CORE_ALL, syncTime );
    if( T1_IsFeatureEnabled( T1_AF_CHECK_INTEGRATION ) )
    {
        *( T1_checkIntegrationPC[coreId] ) = 1u;
        T1_TraceEventPC( coreId,
                         T1_STOPWATCH_START,
                         T1_SW_CHECK_INTEGRATION_CORE_ALL );
    }
    else
    {
        *( T1_checkIntegrationPC[coreId] ) = 0u;
    }
}

/*----------------------------------------------------------------------------------*/
/*
 * Function called from T1_AppHandler() if the invocation file parameter
 * [-checkIntegration](\ref checkIntegration) is true.
 * If the application feature T1_AF_CHECK_INTEGRATION is enabled, trace the
 * static stopwatch T1_SW_CHECK_INTEGRATION_CORE_ALL to obtain the Delta Time
 * of the function.
 * If the parameter is not set to true, this function should not be defined/used.
 * The default implementation allows the integrator to:
 * - use T1.flex SWD, UED, DAF, DCA on T1_checkIntegrationGlobal and
 *   T1_checkIntegrationX, with:
 *  - X being the T1 logical core ID of a writer/reader
 *  - ( ( X + 1 ) %  T1_nOfCores ) being the T1 logical core ID of a reader
 *   This variable holds the previous state of T1_AF_CHECK_INTEGRATION per core.
 * - use the delay T1_DL_CHECK_INTEGRATION_CORE_ALL which has the ID 0 by default,
 *   and is initialized at 0ns.
 * - verify the timers configuration as the sync timer value is traced using
 *   T1_UDE_CHECK_INTEGRATION_SYNCTIMER_CORE_ALL.
 */

void T1_CODE T1_CheckIntegrationHandlerPC( T1_uint8Least_t coreId )
{
    T1_uint8Least_t const readCoreId  = coreId + 1u < T1_nOfCores ? coreId + 1u : 0u;
    T1_uint8_t const prevFeatureState = *( T1_checkIntegrationPC[coreId] );
    T1_uint32_t const syncTime        = T1_GET_SYNC_TIME( );

    if( T1_IsFeatureEnabled( T1_AF_CHECK_INTEGRATION ) )
    {
        /*
         * if prevFeatureState is 0, the appFeature T1_AF_CHECK_INTEGRATION
         * was previously disabled. Only trace a T1_START event.
         */
        if( prevFeatureState == 0u )
        {
            T1_TraceEventPC( coreId,
                             T1_STOPWATCH_START,
                             T1_SW_CHECK_INTEGRATION_CORE_ALL );
        }
        else
        {
            T1_TraceEventPC( coreId,
                             T1_STOPWATCH_STOP_START,
                             T1_SW_CHECK_INTEGRATION_CORE_ALL );
        }
        *( T1_checkIntegrationPC[coreId] ) = 1u;
    }
    else
    {
        /*
         * if prevFeatureState is 1, the appFeature T1_AF_CHECK_INTEGRATION
         * was previously enabled. Trace a T1_STOP event.
         */
        if( prevFeatureState == 1u )
        {
            T1_TraceEventPC( coreId,
                             T1_STOPWATCH_STOP,
                             T1_SW_CHECK_INTEGRATION_CORE_ALL );
        }
        *( T1_checkIntegrationPC[coreId] ) = 0u;
    }

    T1_TraceUint32PC( coreId, T1_UDE_CHECK_INTEGRATION_SYNCTIMER_CORE_ALL, syncTime );
    (void)T1_DelayRoutinePC( coreId, T1_DL_CHECK_INTEGRATION_CORE_ALL );

    /* Cross-core read and write*/
    T1_checkIntegrationGlobal += *( T1_checkIntegrationPC[readCoreId] );
}
#endif /* defined T1_ENABLE && defined T1_CHECK_INTEGRATION */

#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"
