/***************************************************************************//*!
*   \file      T1_Neusar.h
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

#ifndef T1_NEUSAR_H_
#define T1_NEUSAR_H_ (1)
#include "T1_AppInterface.h"


#if defined T1_ENABLE

void T1_TASK_RESET_ACTIVATION( T1_uint8_t coreID, T1_uint32_t id);
void T1_TASK_RESET_TERMINATION( T1_uint8_t coreID, T1_uint32_t id);
void T1_TASK_INIT_ACTIVATION( T1_uint8_t coreID, T1_uint32_t id);
void T1_TASK_SETNEXTTASKDATA_START( T1_uint8_t coreID, T1_uint32_t id);
void T1_TASK_SWITCH_WAIT( T1_uint8_t coreID, T1_uint32_t id);
void T1_TASK_SWITCH_RELEASE( T1_uint8_t coreID, T1_uint32_t id);
void T1_TASK_SETEVENT_RELEASE( T1_uint8_t coreID, T1_uint32_t id);
void T1_TASK_APPTERMINATETASK_TERMINATE( T1_uint8_t coreID, T1_uint32_t id);
void T1_TASK_STARTFIRST_START( T1_uint8_t coreID, T1_uint32_t id);
void T1_TASK_ACTIVATETASKSIMP_ACTIVATION( T1_uint8_t coreID, T1_uint32_t id);
void T1_ISR_ENTRY_START( T1_uint8_t coreID, T1_uint32_t id);
void T1_ISR_EXIT_STOP( T1_uint8_t coreID, T1_uint32_t id);
void T1_ISR_CALLCBDRT_STOP( T1_uint8_t coreID, T1_uint32_t id);

#define OSTH_TASK_RESET_ACTIVATION(coreID, taskId)              T1_TASK_RESET_ACTIVATION(coreID, taskId)
#define OSTH_TASK_RESET_TERMINATION(coreID, taskId)             T1_TASK_RESET_TERMINATION(coreID, taskId)
#define OSTH_TASK_INIT_ACTIVATION(coreID, taskId)               T1_TASK_INIT_ACTIVATION(coreID, taskId)
#define OSTH_TASK_SETNEXTTASKDATA_START(coreID, taskId)         T1_TASK_SETNEXTTASKDATA_START(coreID, taskId)
#define OSTH_TASK_SWITCH_WAIT(coreID, taskId)                   T1_TASK_SWITCH_WAIT(coreID, taskId)
#define OSTH_TASK_SWITCH_RELEASE(coreID, taskId)                T1_TASK_SWITCH_RELEASE(coreID, taskId)
#define OSTH_TASK_SETEVENT_RELEASE(coreID, taskId)              T1_TASK_SETEVENT_RELEASE(coreID, taskId)
#define OSTH_TASK_APPTERMINATETASK_TERMINATE(coreID, taskId)    T1_TASK_APPTERMINATETASK_TERMINATE(coreID, taskId)
#define OSTH_TASK_STARTFIRST_START(coreID, taskId)              T1_TASK_STARTFIRST_START(coreID, taskId)
#define OSTH_TASK_ACTIVATETASKSIMP_ACTIVATION(coreID, taskId)   T1_TASK_ACTIVATETASKSIMP_ACTIVATION(coreID, taskId)

#define OSTH_ISR_ENTRY_START(coreID, taskId)                    T1_ISR_ENTRY_START(coreID, taskId)
#define OSTH_ISR_EXIT_STOP(coreID, taskId)                      T1_ISR_EXIT_STOP(coreID, taskId)
#define OSTH_ISR_CALLCBDRT_STOP(coreID, taskId)                 T1_ISR_CALLCBDRT_STOP(coreID, taskId)

#else
#define OSTH_TASK_RESET_ACTIVATION(coreID, taskId)              ((void)0)
#define OSTH_TASK_RESET_TERMINATION(coreID, taskId)             ((void)0)
#define OSTH_TASK_INIT_ACTIVATION(coreID, taskId)               ((void)0)
#define OSTH_TASK_SETNEXTTASKDATA_START(coreID, taskId)         ((void)0)
#define OSTH_TASK_SWITCH_WAIT(coreID, taskId)                   ((void)0)
#define OSTH_TASK_SWITCH_RELEASE(coreID, taskId)                ((void)0)
#define OSTH_TASK_SETEVENT_RELEASE(coreID, taskId)              ((void)0)
#define OSTH_TASK_APPTERMINATETASK_TERMINATE(coreID, taskId)    ((void)0)
#define OSTH_TASK_STARTFIRST_START(coreID, taskId)              ((void)0)
#define OSTH_TASK_ACTIVATETASKSIMP_ACTIVATION(coreID, taskId)   ((void)0)

#define OSTH_ISR_ENTRY_START(coreID, taskId)                    ((void)0)
#define OSTH_ISR_EXIT_STOP(coreID, taskId)                      ((void)0)
#define OSTH_ISR_CALLCBDRT_STOP(coreID, taskId)                 ((void)0)

#endif
#endif