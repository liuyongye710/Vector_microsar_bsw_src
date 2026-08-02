/*
********************************************************************************
*
* File name: NeuLib_Timer.h
*
* Copyright 2023-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: ZhangDX/2023.08.01
* Change: New
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: TianG/2024.10.12
* Change: 1.Add a memory-map label to function.
*         2.Modify copyright.
* Cause: Bugfix
********************************************************************************
*/
#ifndef NEULIB_TIMER_H_
#define NEULIB_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "NeuLib_Def.h"
#include "NeuLib_MemPool.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define NEULIB_TICK_MAX                 0xFFFFFFFFUL

/* Clock & timer macros. */
#define NEULIB_TIMER_FLAG_DEACTIVATED   0x0 /*!< timer is deactive */
#define NEULIB_TIMER_FLAG_ACTIVATED     0x1 /*!< timer is active */
#define NEULIB_TIMER_FLAG_ONE_SHOT      0x0 /*!< One shot timer. */
#define NEULIB_TIMER_FLAG_PERIODIC      0x2 /*!< Periodic timer. */

/* MD_MSR_Rule20.10_0342 */
#define NEULIB_TIMER_MEMP_VAR(_moduleName, _name, _num)                                     \
        NEULIB_MEM_POOL_DEF_VAR(_moduleName, _name##Timer, _num, sizeof(NeuLibTimer_Type))  \
        /* soft timer list */                                                               \
        static VAR(NeuLibList_Type, _moduleName##_VAR_NO_INIT) _name##_SoftTimerList;

/* MD_MSR_Rule20.10_0342 */
#define NEULIB_TIMER_MEMP_CONST(_moduleName, _name, _num)                           \
        NEULIB_MEM_POOL_DEF_CONST(_moduleName, _name##Timer, _num, sizeof(NeuLibTimer_Type));

/* MD_MSR_Rule20.10_0342 */
#define NEULIB_TIMER_INIT(_name)                                                    \
        NeuLibTimer_Init(&(NeuMemp_##_name##Timer), &(_name##_SoftTimerList))

/* MD_MSR_Rule20.10_0342 */
#define NEULIB_TIMER_CREATE(_name, _desc, _timeoutFunc, _parameter, _time, _flag)   \
        NeuLibTimer_Create(_name, &(NeuMemp_##_desc##Timer), _timeoutFunc, _parameter, _time, _flag)

/* MD_MSR_Rule20.10_0342 */
#define NEULIB_TIMER_START(_getTick, _timer, _name)                                 \
        NeuLibTimer_Start(_getTick, _timer, &_name##_SoftTimerList)

/* MD_MSR_Rule20.10_0342 */
#define NEULIB_TIMER_ENTRY(_getTick, _name)                                         \
        NeuLibTimer_Entry(_getTick, &_name##_SoftTimerList)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
typedef P2FUNC(NeuLibTick_Type, TYPEDEF, NeuLibTimeGetTick_Type)(void);
typedef P2FUNC(void, TYPEDEF, NeuTimeOutFunc_Type)(void *parameter);
/**
 * timer structure
 */
struct NeuLibTimer
{
#if NEU_DEBUG
    char                 name[128];
#endif  /* NEU_DEBUG */
    NeuLibList_Type        row;
    NeuTimeOutFunc_Type timeoutFunc;    /*!< timeout function.             */
    void                 *parameter;    /*!< timeout function's parameter. */
    NeuLibTick_Type        initTick;    /*!< timer timeout tick.           */
    NeuLibTick_Type        timeoutTick; /*!< timeout tick.                 */
    uint8                flag;          /*!< timeout flag.                 */
};
typedef struct NeuLibTimer NeuLibTimer_Type;

/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
/*
********************************************************************************
*    Global Functions
********************************************************************************
*/
#define NEULIB_START_SEC_CODE
#include "NeuLib_MemMap.h"
FUNC(void, NEULIB_CODE) NeuLibTimer_Init(
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc,
    P2VAR(NeuLibList_Type, AUTOMATIC, NEULIB_APPL_DATA) timerList
);
FUNC_P2VAR(NeuLibTimer_Type, NEULIB_APPL_DATA, NEULIB_CODE) NeuLibTimer_Create(
    P2CONST(char, AUTOMATIC, NEULIB_APPL_CONST) name,
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc,
    NeuTimeOutFunc_Type timeoutFunc,
    P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) parameter,
    NeuLibTick_Type time,
    uint8 flag
);
FUNC(Std_ReturnType, NEULIB_CODE) NeuLibTimer_Delete(
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc,
    P2VAR(NeuLibTimer_Type, AUTOMATIC, NEULIB_APPL_DATA) timer
);
FUNC(Std_ReturnType, NEULIB_CODE) NeuLibTimer_Start(
    NeuLibTimeGetTick_Type getTick,
    P2VAR(NeuLibTimer_Type, AUTOMATIC, NEULIB_APPL_DATA) timer,
    P2VAR(NeuLibList_Type, AUTOMATIC, NEULIB_APPL_DATA)  timerList
);
FUNC(Std_ReturnType, NEULIB_CODE) NeuLibTimer_Stop(
    P2VAR(NeuLibTimer_Type, AUTOMATIC, NEULIB_APPL_DATA) timer
);
FUNC(void, NEULIB_CODE) NeuLibTimer_Entry(
    NeuLibTimeGetTick_Type getTick,
    P2VAR(NeuLibList_Type, AUTOMATIC, NEULIB_APPL_DATA)  timerList
);
#define NEULIB_STOP_SEC_CODE
#include "NeuLib_MemMap.h"

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* NEULIB_TIMER_H_ */
