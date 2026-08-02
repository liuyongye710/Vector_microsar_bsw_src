/*********************************************************************************//*!
*   \file           T1_AppInterface.c
*
*   \brief          Application-specific interface functions for T1
*
*   $Author: jialinli $
*
*   $Revision: 120 $
*
*   \copyright GLIWA GmbH embedded systems, Weilheim i.OB. All rights reserved
*************************************************************************************/

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#ifdef __TASKING__
/*
 * Avoid harmless but unnecessary clearing of T1_bss sections by the Tasking start-up
 * code.
 * This pragma is disallowed by some compiler options, so you may have to remove it.
 */
#   pragma noclear
#endif /* defined __TASKING__ */
#include "CanIf.h"//mzy
#include "T1_AppInterface.h"
#if defined T1_VAR_FRAME_SIZE
#   include "GCP_driverInterface.h"
#endif

/*----------------------------------------------------------------------------------*/
/*--- Local macros -----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if ! defined T1_NOF_CORES
#   define T1_commsCoreOffset (0)
#endif /* ! defined T1_NOF_CORES */

/*----------------------------------------------------------------------------------*/
/*--- Optimization pragmas for uniform code generation -----------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined __GNUC__
#   pragma GCC optimize "Os"
#elif defined __ghs__
#   pragma ghs OS
#elif defined __TASKING__
#   pragma optimize acefgIklMnoprsUvwy,+predict
#endif

/*----------------------------------------------------------------------------------*/
/*--- definitions of global variables ----------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE
#   define T1_START_SEC_NO_INIT_8
#   include "T1_MemMap.h"
#   if defined T1_NOF_CORES
#       if 2 <= T1_NOF_CORES
/*
 * T1_coreTriggerCounter[coreId] is incremented when coreId requests a trigger fom
 * all other cores. T1_coreTriggerCounter[coreId] is written only from core coreId
 * and is, therefore, parallel-safe.
 */
T1_uint8_t T1_SEC_NO_INIT_8 T1_coreTriggerCounter[T1_NOF_CORES];
/*
 * Each core keeps a (shadow) copy of T1_coreTriggerCounter for every other core.
 * When they differ, a trigger has occurred. T1_shadowTriggerCounter[coreId] is
 * written (and, indeed read) only from core coreId and is, therefore, parallel-safe.
 */
T1_uint8_t T1_SEC_NO_INIT_8 T1_shadowTriggerCounter[T1_NOF_CORES][T1_NOF_CORES-1];
#       endif /* 2 <= T1_NOF_CORES */
#   endif /* defined T1_NOF_CORES */
T1_uint8_t T1_errorCount
#   if defined T1_NOF_CORES
                        [T1_NOF_CORES]
#   endif /* defined T1_NOF_CORES */
                                        ;
#   define T1_STOP_SEC_NO_INIT_8
#   include "T1_MemMap.h"

#   if defined T1_VAR_FRAME_SIZE

#       define T1_START_SEC_CONST_16
#       include "T1_MemMap.h"
const T1_frameSize_t T1_maxRxFrameBytes T1_SEC_CONST_16 = T1_GCP_MAX_RX_FRAME_SIZE;
const T1_frameSize_t T1_maxTxFrameBytes T1_SEC_CONST_16 = T1_GCP_MAX_TX_FRAME_SIZE;
#       define T1_STOP_SEC_CONST_16
#       include "T1_MemMap.h"

/*
 * To avoid an unnecessary reliance on dynamic memory allocation,
 * our template allocates one global transmit buffer, large enough for
 * the maximum transmit frame bytes. Also, a variable contains the length in bytes of the
 * actual data content. When this length variable is set to 0, it denotes an empty buffer
 * available for (re-)allocation.
 */
#       define T1_START_SEC_NO_INIT_8
#       include "T1_MemMap.h"
GCP_txFrame_t txFrameBuffer;
#       define T1_STOP_SEC_NO_INIT_8
#       include "T1_MemMap.h"

/*
 * ++++++
 * Ideally, do not define an additional copy of the transmit buffer here but rather
 * directly use the transmit buffer already allocated by the diagnostic layer.
 * However, to make this example more self-contained, and because some projects have
 * required this approach, we define an additional copy of the transmit buffer.
 */
#       define T1_START_SEC_NO_INIT_16
#       include "T1_MemMap.h"
GCP_uint16_t txFrameLength;
#       define T1_STOP_SEC_NO_INIT_16
#       include "T1_MemMap.h"

#   endif /* defined T1_VAR_FRAME_SIZE */

#endif /* defined T1_ENABLE */

/*----------------------------------------------------------------------------------*/
/*--- definitions of global functions ----------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_START_SEC_CODE
#include "T1_MemMap.h"
/*!
 * Wrapper function for T1_Init(), T1_InitExtra1(), T1_InitExtra2() and
 * T1_InitExtra3(). It also initializes T1_taskAct if tracing cross-core task
 * activations and T1_shadowTriggerCounter on behalf of
 * T1_AppSetStopTriggerAllCores().
 * Call T1_AppInit() on every core in privileged mode
 * - before other T1 services on any core and
 * - after starting the trace timer.
 */
void T1_CODE T1_AppInit( void )
{
#if defined T1_ENABLE
#   if defined T1_NOF_CORES
/* polyspace<MISRA-C3:9.1:Not a defect:Other> Suspected checker artefact; misinterpreting return value of a complex expression.
   polyspace<MISRA-C3:10.3:Not a defect:Other> Intrinsics. */
    const T1_uint8Least_t coreId = T1_GetCoreIdOffset( );
#   endif /* defined T1_NOF_CORES */
    T1_errorCount
#   if defined T1_NOF_CORES
                [coreId]
#   endif /* defined T1_NOF_CORES */
                        = 0; /* Clear error count */

#   if defined T1_CROSS_CORE_ACT
    if( 0u == coreId )
    {
        T1_uint8Least_t taskId = T1_MAX_NOF_TASKS;
        do
        {
            T1_taskAct[--taskId] = 0uL;
        }
        while( 0u != taskId );
    }
#   endif /* defined T1_CROSS_CORE_ACT */

    if( T1_OK != T1_InitPC( coreId, T1_pluginTable ) )
    {
        for( ;; )
        {
            /* Infinite loop to trap init failure */
        }
    }
#   if defined T1_VAR_FRAME_SIZE
    txFrameLength = 0; /* empty */
#   endif /* defined T1_VAR_FRAME_SIZE */

#   if ! defined T1_ENABLE_ONLY_SAFE_PLUGINS_AT_INIT
/* polyspace<MISRA-C3:9.1:Not a defect:Other> Suspected checker artefact; misinterpreting return value of a complex expression.
   polyspace<MISRA-C3:10.3:Not a defect:Other> Intrinsics. */
    T1_InitExtra1( );
/* polyspace<MISRA-C3:9.1:Not a defect:Other> Suspected checker artefact; misinterpreting return value of a complex expression.
   polyspace<MISRA-C3:10.3:Not a defect:Other> Intrinsics. */
    T1_InitExtra2( );
/* polyspace<MISRA-C3:9.1:Not a defect:Other> Suspected checker artefact; misinterpreting return value of a complex expression.
   polyspace<MISRA-C3:10.3:Not a defect:Other> Intrinsics. */
    T1_InitExtra3( );
#   endif /* ! defined T1_ENABLE_ONLY_SAFE_PLUGINS_AT_INIT */

#   if 0
    if( 0u == coreId )
    {
        /* Configure CET event chain on core 0 without the GUI */
        T1_ConfigEventChainPC(  0u,
                                T1_COMBINE_EVENT_INFO( T1_START, 3 /* task with ID 3 */ ),
                                T1_COMBINE_EVENT_INFO( T1_STOP,  3 /* task with ID 3 */ ),
                                T1_CET_EVT_CHAIN_TO_IDX_CORE0(T1_EVTCHN_0_ID) );
    }
#   endif

#   if defined T1_NOF_CORES
    /*
     * Variables used for triggering all cores at the same time,
     * see T1_AppBackgroundHandler and T1_AppSetStopTriggerAllCores.
     * Initialize T1_shadowTriggerCounter equal to T1_coreTriggerCounter
     * to avoid (spurious) trigger.
     */
#       if 2 == T1_NOF_CORES
    T1_shadowTriggerCounter[coreId][0] = T1_coreTriggerCounter[coreId ^ 1u];
#       elif 3 <= T1_NOF_CORES
    {
        T1_uint8Least_t shadowTriggerIndex = T1_NOF_CORES - 2;
        do
        {
            T1_uint8Least_t coreTriggerIndex = shadowTriggerIndex;
            if( coreId <= coreTriggerIndex )
            {
                ++coreTriggerIndex;
            }
            T1_shadowTriggerCounter[coreId][shadowTriggerIndex]
                = T1_coreTriggerCounter[coreTriggerIndex];
        }
        while( 0u != shadowTriggerIndex-- );
    }
#       endif /* T1_NOF_CORES */
#   endif /* defined T1_NOF_CORES */

    /*
     * NoSusp/NOSUSP variants are used because pre-emption from traced tasks and ISRs
     * is prohibited in T1_AppInit.
     */

    /*
     * Communications core may not have completed T1_Init at this point on
     * the running core.
     * So we test the T1_initFeatureMask rather than the T1_featureMask to
     * determine whether or not to trigger and capture the start-up trace.
     */
    if( (T1_initFeatureMask & (T1_featureMask_t)T1_AF_TRACE_STARTUP) != 0uL )
    {
        /* Capture the start-up trace */
        (void)T1_SetStopTriggerNoSuspPC( coreId, T1_BUFFER_SIZE_PC( coreId ) );
    }

/* polyspace<MISRA-C3:17.7:Not a defect:Justified> The return value is used in some conditional compilation variants of this function but not others.
   polyspace<MISRA-C3:10.3:Not a defect:Justified> Wider type coreId used for performance reasons on some platforms. */
    T1_CONT_CALIBRATE_OVERHEADS_NOSUSP_PC( coreId );
#endif /* defined T1_ENABLE */
}
/*----------------------------------------------------------------------------------*/
/*!
 * Wrapper function for T1_InitExtra1(), T1_InitExtra2() and T1_InitExtra3() when
 * they are not called from T1_AppInit(). Call in privileged mode.
 */
void T1_CODE T1_AppEnableUnsafePlugins( void )
{
#   if defined T1_ENABLE && defined T1_ENABLE_ONLY_SAFE_PLUGINS_AT_INIT
    T1_InitExtra1( );
    T1_InitExtra2( );
    T1_InitExtra3( );
#   endif /* defined T1_ENABLE && defined T1_ENABLE_ONLY_SAFE_PLUGINS_AT_INIT */
}
/*----------------------------------------------------------------------------------*/
/*!
 * Wrapper function for T1_ContBgHandler().
 * If using more than one core, it can call T1_SetStopTriggerPC() on behalf of
 * an execution of T1_AppSetStopTriggerAllCores() on a different core.
 * T1_ContBgHandler() is not permitted to pre-empt T1_Handler(), therefore
 * T1_AppBackgroundHandler() is not permitted to pre-empt T1_AppHandler().
 */
void T1_CODE T1_AppBackgroundHandler( void )
{
#if defined T1_ENABLE
#   if defined T1_NOF_CORES
/* polyspace<MISRA-C3:9.1:Not a defect:Other> Suspected checker artefact; misinterpreting return value of a complex expression.
   polyspace<MISRA-C3:10.3:Not a defect:Other> Intrinsics. */
    const T1_uint8Least_t coreId = T1_GetCoreIdOffset( );
#   endif /* defined T1_NOF_CORES */

#   if defined T1_CONT_REMOTE
#       if T1_NOF_CORES < 2
#           error T1.cont remote core configured with only one core
#       endif /* T1_NOF_CORES < 2 */
    if( T1_CONT_RC_UNMAP( 0 ) == coreId )
    {
        /* This core runs the T1.cont background handler for T1 logical core ID 0 */
        if( T1_BUSY == T1_ContBgHandlerPC( 0 ) )
        {
            INC_T1_ERROR_COUNT( coreId );   /* T1_ContBgHandlerPC re-entered? */
        }
    }
    if( T1_CONT_RC_UNMAP( 1 ) == coreId )
    {
        /* This core runs the T1.cont background handler for T1 logical core ID 1 */
        if( T1_BUSY == T1_ContBgHandlerPC( 1 ) )
        {
            INC_T1_ERROR_COUNT( coreId );   /* T1_ContBgHandlerPC re-entered? */
        }
    }
#       if 3 <= T1_NOF_CORES
    if( T1_CONT_RC_UNMAP( 2 ) == coreId )
    {
        /* This core runs the T1.cont background handler for T1 logical core ID 2 */
        if( T1_BUSY == T1_ContBgHandlerPC( 2 ) )
        {
            INC_T1_ERROR_COUNT( coreId );   /* T1_ContBgHandlerPC re-entered? */
        }
    }
#       endif /* 3 <= T1_NOF_CORES */
#       if 4 <= T1_NOF_CORES
    if( T1_CONT_RC_UNMAP( 3 ) == coreId )
    {
        /* This core runs the T1.cont background handler for T1 logical core ID 3 */
        if( T1_BUSY == T1_ContBgHandlerPC( 3 ) )
        {
            INC_T1_ERROR_COUNT( coreId );   /* T1_ContBgHandlerPC re-entered? */
        }
    }
#       endif /* 4 <= T1_NOF_CORES */
#       if 5 <= T1_NOF_CORES
    if( T1_CONT_RC_UNMAP( 4 ) == coreId )
    {
        /* This core runs the T1.cont background handler for T1 logical core ID 4 */
        if( T1_BUSY == T1_ContBgHandlerPC( 4 ) )
        {
            INC_T1_ERROR_COUNT( coreId );   /* T1_ContBgHandlerPC re-entered? */
        }
    }
#       endif /* 5 <= T1_NOF_CORES */
#       if 6 <= T1_NOF_CORES
    if( T1_CONT_RC_UNMAP( 5 ) == coreId )
    {
        /* This core runs the T1.cont background handler for T1 logical core ID 5 */
        if( T1_BUSY == T1_ContBgHandlerPC( 5 ) )
        {
            INC_T1_ERROR_COUNT( coreId );   /* T1_ContBgHandlerPC re-entered? */
        }
    }
#       endif /* 6 <= T1_NOF_CORES */
#   else /* ! defined T1_CONT_REMOTE */
    if( T1_BUSY == T1_ContBgHandlerPC( coreId ) )
    {
        INC_T1_ERROR_COUNT( coreId );       /* T1_ContBgHandlerPC re-entered? */
    }
#   endif /* defined T1_CONT_REMOTE */
    /* At this point it is safe to copy from T1_resultBuffer, for example to NVRAM. */

#   if defined T1_NOF_CORES
#       if 2 <= T1_NOF_CORES
    /*
     * Check to see if another core has requested a trigger,
     * see T1_AppSetStopTriggerAllCores.
     */
    {
        T1_uint8Least_t doTrigger = 0u;
        T1_uint8Least_t shadowTriggerIndex = T1_NOF_CORES - 2;
        do
        {
            T1_uint8Least_t coreTriggerIndex = shadowTriggerIndex;
            if( coreId <= coreTriggerIndex )
            {
                ++coreTriggerIndex;
            }
            if( T1_shadowTriggerCounter[coreId][shadowTriggerIndex]
                != T1_coreTriggerCounter[coreTriggerIndex] )
            {
                doTrigger = 1u;
                break;
            }
        }
        while( 0u != shadowTriggerIndex-- );
        if( 0u != doTrigger )
        {
            shadowTriggerIndex = T1_NOF_CORES - 2;
            do
            {
                T1_uint8Least_t coreTriggerIndex = shadowTriggerIndex;
                if( coreId <= coreTriggerIndex )
                {
                    ++coreTriggerIndex;
                }
                T1_shadowTriggerCounter[coreId][shadowTriggerIndex]
                    = T1_coreTriggerCounter[coreTriggerIndex];
            }
            while( 0u != shadowTriggerIndex-- );
            /* Stop tracing on this core */
            (void)T1_SetStopTriggerPC( coreId, T1_BUFFER_SIZE_PC( coreId ) >> 2 );
        }
    }
#       endif /* 2 <= T1_NOF_CORES */
#   endif /* defined T1_NOF_CORES */
#endif /* defined T1_ENABLE */
}

/*----------------------------------------------------------------------------------*/
/*!
 * Wrapper function for T1_Handler(). Call periodically, for example every 5ms.
 * Different periods can be safely used on different cores, if required.
 * T1_ContBgHandler() is not permitted to pre-empt T1_Handler(), therefore
 * T1_AppBackgroundHandler() is not permitted to pre-empt T1_AppHandler().
 */
void T1_CODE T1_AppHandler( void )
{
#if defined T1_ENABLE
#   if defined T1_NOF_CORES
/* polyspace<MISRA-C3:9.1:Not a defect:Other> Suspected checker artefact; misinterpreting return value of a complex expression.
   polyspace<MISRA-C3:10.3:Not a defect:Other> Intrinsics. */
    const T1_uint8Least_t coreId = T1_GetCoreIdOffset( );
#   endif /* defined T1_NOF_CORES */
    const int traceStopwatch = T1_IsFeatureEnabled( T1_AF_MEASURE_T1_HANDLER )
#if defined T1_NOF_CORES
                                && ( 0u == coreId )
#endif /* defined T1_NOF_CORES */
                                                                                ;

    if( traceStopwatch )
    {
        T1_TraceEventPC( 0u, T1_STOPWATCH_START, T1_SW_T1_HANDLER_CORE0 );
    }

    if( T1_OK != T1_HandlerPC( coreId ) )
    {
/* polyspace<MISRA-C3:2.2:Not a defect:Other> Suspecting checker artefact, this code is not dead. */
        INC_T1_ERROR_COUNT( coreId );
        /* T1 failure */
    }

    if( traceStopwatch )
    {
        T1_TraceEventPC( 0u, T1_STOPWATCH_STOP, T1_SW_T1_HANDLER_CORE0 );
    }

#endif /* defined T1_ENABLE */
}

#if defined T1_VAR_FRAME_SIZE
#   if defined T1_ENABLE
/*----------------------------------------------------------------------------------*/
/*
 * This function needs only be modified if a different buffering system is required.
*/
GCP_txFrame_t * GCP_CODE GCP_TxBufferRequest( void )
{
    if( 0u != txFrameLength )
    {
        /* Wait until buffer is free */
        return GCP_NULL;
    }
    else
    {
        return &txFrameBuffer;
    }
}

/*
 * This function needs only be modified if a different buffering system is required.
 * In this example, we ensure that the data is in our copy of the transmit buffer,
 * txFrameBuffer, see comment ++++++ above.
 */
GCP_error_t GCP_CODE GCP_TransmitFrame( GCP_txFrame_t const *pData, GCP_dataLength_t len )
{
    GCP_uint16Least_t i; /* loop index */
    if( 0u != txFrameLength )
    {
        return GCP_TX_IN_PROGRESS;
    }
    else
    {
        if( pData != &txFrameBuffer )
        {
            /* Data not yet copied to txFrameBuffer, do it now */
            for( i = 0u; i < len; ++i )
            {
                txFrameBuffer.u8[i] = pData->u8[i];
            }
        }
        __asm( "" ); /* Prevent instruction re-ordering by optimizer */
        txFrameLength = (GCP_uint16_t)len; /* Transmit buffer is full */
        return GCP_OK;
    }
}
#   endif /* defined T1_ENABLE */

/* !!! NOTE: this is only pseudo code for a function that has to be called for the from the diagnostic layer !!!
 * The ReadByIdentifier function then tests txFrameLength. If it is zero, a negative acknowledgement
 * is returned to the T1-HOST-SW, indicating no ready data. Otherwise,
 * the txFrameBuffer is handed over to the diagnostic layer for transmission. When the
 * diagnostic layer has finished reading the data in the txFrameBuffer, it sets txFrame-Length
 * back to zero, indicating that the txFrameBuffer can be allocated again for the next frame.
 */
/* TODO: custom diagnosis interface return type */ void GCP_CODE T1_AppDgn_ReadDataByIdentifier( /* TODO: custom diagnosis interface parameters */ void )
{
#   if defined T1_ENABLE
    if( 0u != txFrameLength )
    {
        /*
         * TODO: Pass (pointer to) payload data to the diagnostic layer.
         * In this example pass a pointer to txFrameBuffer but the data could already
         * be in the diagnostic layer buffer, see comment ++++++ above.
         */
        __asm( "" );            /* Prevent instruction re-ordering by optimizer */
        txFrameLength = 0u;     /* Mark transmit buffer free for re-allocation */
    }
    else
    {
        /* TODO: Send negative response with ErrorCode 0x22 'Condition Not Correct' */
    }
#   endif /* defined T1_ENABLE */
    return /* TODO */;
}

/*----------------------------------------------------------------------------------*/
/* !!! NOTE: this is only pseudo code for a function that has to be called for the from the diagnostic layer !!!
 * The WriteByIndentifier function calls GCP_RxHandler. We
 * need to ensure that the data pointed to by the parameter passed to GCP_RxHandler
 * remains unchanged until it can be polled out by T1_Handler. For some configurations
 * of diagnostic interface, we do not require an additional receive buffer. However, if the
 * memory pointed to by the parameter to WriteByIndentifier is going to be re-used on
 * return from WriteByIndentifier then we have to create and maintain a receive buffer,
 * see T1_AppRxCallback below
 */
/* TODO: custom diagnosis interface return type */ void GCP_CODE T1_AppDgn_WriteDataByIdentifier( /* TODO: custom diagnosis interface parameters */ void )
{
#   if defined T1_ENABLE
    if( /* TODO: <payload data> in <custom diagnosis interface parameters> has valid length */ 1 )
    {
        /* Ignore return code, which is always GCP_OK. */
        (void)GCP_RxHandler( (GCP_rxFrame_t const *)(/* TODO: <(pointer to) payload data>) */ 0), /* TODO: length of received data */ 0 );
    }
    else
    {
        /* TODO: Send negative response 0x13 'Incorrect Message Length Or Invalid Format' */
    }
#   endif /* defined T1_ENABLE */
    return /* TODO */;
}

#else /* ! defined T1_VAR_FRAME_SIZE */

/*----------------------------------------------------------------------------------*/
#   if defined T1_ENABLE
#       define T1_START_SEC_NO_INIT_32
#       include "T1_MemMap.h"
static T1_rawData_t rxBuffer;
#       define T1_STOP_SEC_NO_INIT_32
#       include "T1_MemMap.h"
#   endif /* defined T1_ENABLE */

/*!
 * Wrapper for T1_RxCallback(). Call this on receipt of an 8-byte T1 data frame unless
 * T1 is configured for 'GCP N' communications with variable size data frames, for
 * example from a CAN receive interrupt handler.
 * Adapt parameters to fit the application. This example uses an array of 8 bytes
 * to pass the CAN data. 16- or 32-bit access can (and should) be used if the
 * necessary alignment of the source data can be guaranteed and the processor supports
 * 16- or 32-bit memory access.
 * The data passed to T1_RxCallback() is read at the next call to T1_Handler(), so the
 * incoming data must be cached, see rxBuffer, unless the source data persists until
 * then. With a typical AUTOSAR COM stack, the source data does not persist and the
 * rxBuffer is needed.
 * \param[in] pRxData pointer to 8-byte data payload of received frame
 */
void T1_CODE T1_AppRxCallback( T1_uint8_t const *pRxData )
{
#   if defined T1_ENABLE

    rxBuffer.d.u8[0] = pRxData[0];
    rxBuffer.d.u8[1] = pRxData[1];
    rxBuffer.d.u8[2] = pRxData[2];
    rxBuffer.d.u8[3] = pRxData[3];
    rxBuffer.d.u8[4] = pRxData[4];
    rxBuffer.d.u8[5] = pRxData[5];
    rxBuffer.d.u8[6] = pRxData[6];
    rxBuffer.d.u8[7] = pRxData[7];

/* polyspace<MISRA-C3:2.1:Not a defect:Other> Checker artefact. This code is not unreachable. */
    if( T1_OK != T1_RxCallback( &rxBuffer ) )
    {
/* polyspace<MISRA-C3:2.2:Not a defect:Other> Suspecting checker artefact, this code is not dead. */
        INC_T1_ERROR_COUNT( T1_commsCoreOffset );
        /* T1 failure */
    }

#   endif /* defined T1_ENABLE */

}

#endif /* defined T1_VAR_FRAME_SIZE */

/*----------------------------------------------------------------------------------*/
#if defined T1_ENABLE && ! defined T1_VAR_FRAME_SIZE

/*!
 * T1_Transmit() is called from T1 library code to transmit a fixed 8-byte data frame
 * unless T1 is configured for 'GCP N' communications with variable size data frames.
 * If the lower layer is unable to accept a new frame at this point, T1_Transmit()
 * must return #T1_FAILED in order that T1 will re-try the frame until it succeeds or
 * times out.
 */
T1_status_t T1_CODE T1_Transmit( T1_rawData_t const T1_FARPTR pData )
{
    T1_status_t retVal = T1_OK;

    /* TODO: transmit 8 bytes of rawData with the T1 CAN-transmit identifier */
    /* IMPORTANT: return T1_FAILED if transmission failed so that T1 can retry. */
    uint8 Status_u8;

    PduIdType 	T1TxPduId = CanIfConf_CanIfTxPduCfg_T1_TxMsg_oCAN00_102eb41e_Tx;
    PduInfoType T1TxPduInfo;

    T1TxPduInfo.SduDataPtr = (uint8 *)pData;
    T1TxPduInfo.SduLength = 8;

    Status_u8 = CanIf_Transmit(T1TxPduId,&T1TxPduInfo);
    if(Status_u8 == E_NOT_OK)
    {
    	retVal = T1_FAILED;
    }

    return retVal;//MZY for T1_Transmit
}
#endif /* defined T1_ENABLE && ! defined T1_VAR_FRAME_SIZE */

/*----------------------------------------------------------------------------------*/
#if defined T1_NOF_CORES
/*!
 * Halt tracing on every core. On this core T1_SetStopTriggerPC() is called. For each
 * other core, T1_SetStopTriggerPC() is called from T1_AppBackgroundHandler()
 * executing on that core.
 * \param[in] coreId       the T1 logical ID of the calling core
 * \param[in] afterXevents the number of additional events to trace on this core
 *                         before tracing actually stops, see T1_SetStopTriggerPC()
 */
void T1_CODE T1_AppSetStopTriggerAllCores( T1_uint8Least_t coreId, T1_nofEntries_t afterXevents )
{
#   if defined T1_ENABLE
#       if 1 == T1_NOF_CORES
    (void)T1_SetStopTriggerPC( 0, afterXevents );
#       else /* 2 or more cores */
    /* Stop tracing on this core */
    if( T1_OK == T1_SetStopTriggerPC( coreId, afterXevents ) )
    {
        /* If successful, signal other cores to stop tracing */
        ++T1_coreTriggerCounter[coreId];
    }
#       endif /* T1_NOF_CORES */
#   endif /* defined T1_ENABLE */
}
#endif /* defined T1_NOF_CORES */

#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"
