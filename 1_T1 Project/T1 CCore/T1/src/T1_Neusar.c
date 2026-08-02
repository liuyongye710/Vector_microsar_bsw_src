/***************************************************************************//*!
*   \file      T1_Neusar.c
*
*   \brief     This file glues the OS Timing Hooks of the
*              Neusar OS to T1 trace event calls
*
*   $Author: jialinli $
*
*   $Revision: 370 $
*
*   \copyright GLIWA GmbH & Co. KG, Weilheim i.OB. All rights reserved
*******************************************************************************/

#include "T1_Neusar.h"

#define T1_TRACE_DBG  1

#        define T1_START_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"
/*record task states 0: terminated, 1: activated, 2: running*/
T1_uint8_t T1_SEC_VAR_POWER_ON_CLEARED_8 T1_NEUSAR_TASK_STATE[T1_MAX_NOF_TASKS] = {0};
#        define T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"

#        define T1_START_SEC_CODE_FAST
#        include "T1_MemMap.h"

void T1_TASK_RESET_ACTIVATION( T1_uint8_t coreID, T1_uint16Least_t id)
{
    T1_TraceActivationPC(coreID, id);
    T1_NEUSAR_TASK_STATE[id] = 1;
    # if T1_TRACE_DBG
    T1_TraceEvent(T1_UE_TRACE_DEBUG, 0);
    #endif
}

void T1_TASK_RESET_TERMINATION( T1_uint8_t coreID, T1_uint16Least_t id)
{
    T1_TraceStopPC(coreID, id);
    T1_NEUSAR_TASK_STATE[id] = 0;
    # if T1_TRACE_DBG
    T1_TraceEvent(T1_UE_TRACE_DEBUG, 1);
    #endif
}
void T1_TASK_INIT_ACTIVATION( T1_uint8_t coreID, T1_uint16Least_t id)
{
    T1_TraceActivationPC(coreID, id);
    T1_NEUSAR_TASK_STATE[id] = 1;
    # if T1_TRACE_DBG
    T1_TraceEvent(T1_UE_TRACE_DEBUG, 2);
    #endif
}
void T1_TASK_SETNEXTTASKDATA_START( T1_uint8_t coreID, T1_uint16Least_t id)
{
    if ( 2 > T1_NEUSAR_TASK_STATE[id] ) /*if not pre-empted*/
    {
        T1_TraceStartPC(coreID, id);
        T1_NEUSAR_TASK_STATE[id] = 2;
    }
    
    # if T1_TRACE_DBG
    T1_TraceEvent(T1_UE_TRACE_DEBUG, 3);
    #endif
}
void T1_TASK_SWITCH_WAIT( T1_uint8_t coreID, T1_uint16Least_t id)
{
#if defined T1_WAIT_RESUME
    T1_TraceWaitPC(coreID, id);
#else
    T1_TraceStopPC(coreID, id);
#endif
    T1_NEUSAR_TASK_STATE[id] = 0;
    # if T1_TRACE_DBG
    T1_TraceEvent(T1_UE_TRACE_DEBUG, 4);
    #endif
}
void T1_TASK_SWITCH_RELEASE( T1_uint8_t coreID, T1_uint16Least_t id)
{
#if defined T1_WAIT_RESUME
    T1_TraceReleasePC(coreID, id);
#else
    T1_TraceActivationPC(coreID, id);
#endif
    T1_NEUSAR_TASK_STATE[id] = 1;
    # if T1_TRACE_DBG
    T1_TraceEvent(T1_UE_TRACE_DEBUG, 5);
    #endif
}
void T1_TASK_SETEVENT_RELEASE( T1_uint8_t coreID, T1_uint16Least_t id)
{
    #if defined T1_WAIT_RESUME
    T1_TraceReleasePC(coreID, id);
#else
    T1_TraceActivationPC(coreID, id);
#endif
    T1_NEUSAR_TASK_STATE[id] = 1;
    # if T1_TRACE_DBG
    T1_TraceEvent(T1_UE_TRACE_DEBUG, 6);
    #endif
}
void T1_TASK_APPTERMINATETASK_TERMINATE( T1_uint8_t coreID, T1_uint16Least_t id)
{
     T1_TraceStopPC(coreID, id);
     T1_NEUSAR_TASK_STATE[id] = 0;
    # if T1_TRACE_DBG
    T1_TraceEvent(T1_UE_TRACE_DEBUG, 7);
    #endif
}
void T1_TASK_STARTFIRST_START( T1_uint8_t coreID, T1_uint16Least_t id)
{
    T1_TraceStartPC(coreID, id);
    T1_NEUSAR_TASK_STATE[id] = 2;
    # if T1_TRACE_DBG
    T1_TraceEvent(T1_UE_TRACE_DEBUG, 8);
    #endif
}
void T1_TASK_ACTIVATETASKSIMP_ACTIVATION( T1_uint8_t coreID, T1_uint16Least_t id)
{
    T1_TraceActivationPC(coreID, id);
    T1_NEUSAR_TASK_STATE[id] = 1;
    # if T1_TRACE_DBG
    T1_TraceEvent(T1_UE_TRACE_DEBUG, 9);
    #endif
}
void T1_ISR_ENTRY_START( T1_uint8_t coreID, T1_uint16Least_t id)
{
    T1_TraceStartNoActPC(coreID, id + T1_MIN_CAT2_ISR_ID_OFFSET );
    T1_NEUSAR_TASK_STATE[id + T1_MIN_CAT2_ISR_ID_OFFSET] = 2;
    # if T1_TRACE_DBG
    T1_TraceEvent(T1_UE_TRACE_DEBUG, 10);
    #endif
}
void T1_ISR_EXIT_STOP( T1_uint8_t coreID, T1_uint16Least_t id)
{
    T1_TraceStopPC(coreID, id + T1_MIN_CAT2_ISR_ID_OFFSET );
    T1_NEUSAR_TASK_STATE[id + T1_MIN_CAT2_ISR_ID_OFFSET] = 0;
    # if T1_TRACE_DBG
    T1_TraceEvent(T1_UE_TRACE_DEBUG, 11);
    #endif
}
void T1_ISR_CALLCBDRT_STOP( T1_uint8_t coreID, T1_uint16Least_t id)
{
    T1_TraceStopPC(coreID, id + T1_MIN_CAT2_ISR_ID_OFFSET );
    T1_NEUSAR_TASK_STATE[id + T1_MIN_CAT2_ISR_ID_OFFSET] = 0;
    # if T1_TRACE_DBG
    //T1_TraceEvent(T1_UE_TRACE_DEBUG, 12);
    #endif
}

#        define T1_STOP_SEC_CODE_FAST
#        include "T1_MemMap.h"
