/*
********************************************************************************
*
* File name: NeuLib_Timer.c
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
* Change: 1.Modify memory-map label error.
*         2.Modify copyright.
* Cause: Bugfix
********************************************************************************
*/
#include "NeuLib_Timer.h"
#include "NeuLib_Service.h"
#include "NeuLib_Def.h"
#include "NeuLib.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/

/*
********************************************************************************
*    Local Types
********************************************************************************
*/
/*
********************************************************************************
*    Local Variables
********************************************************************************
*/
#define NEULIB_START_SEC_VAR_INIT
#include "NeuLib_MemMap.h"

#define NEULIB_STOP_SEC_VAR_INIT
#include "NeuLib_MemMap.h"

/*
********************************************************************************
*    Local Constants
********************************************************************************
*/
#define NEULIB_START_SEC_CONST
#include "NeuLib_MemMap.h"
static CONST(NeuLibTick_Type, NEULIB_CONST) NeuLibTickMax = NEULIB_TICK_MAX / NEULIB_SHIFT_2;

#define NEULIB_STOP_SEC_CONST
#include "NeuLib_MemMap.h"

/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
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
#define NEULIB_START_SEC_CODE
#include "NeuLib_MemMap.h"
/*
********************************************************************************
* Function Name: NeuLibTimer_Init
*
* Explanation:   Initialize the software timer.
* (Synchronous)
*
* param:         desc      Memory pool descriptor.
*                timerList Soft timer list .
*
* retval:        None
********************************************************************************
*/
FUNC(void, NEULIB_CODE) NeuLibTimer_Init(
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc,
    P2VAR(NeuLibList_Type, AUTOMATIC, NEULIB_APPL_DATA) timerList
)
{
    NeuLibMemPool_Init(desc);
    NeuLibList_Init(timerList);
}

/*
********************************************************************************
* Function Name: NeuLibTimer_Create
*
* Explanation:   This function will create a timer
* (Synchronous)
*
* param:         name      The timer name.
*                desc      Memory pool descriptor.
*                timeout   Is the timeout function.
*                parameter Is the parameter of timeout function.
*                time      Is timeout ticks of the timer.
*                flag      The flag of timer. eg: NEULIB_TIMER_FLAG_PERIODIC.
*
* retval:        The created timer object.
********************************************************************************
*/
FUNC_P2VAR(NeuLibTimer_Type, NEULIB_APPL_DATA, NEULIB_CODE) NeuLibTimer_Create(
    P2CONST(char, AUTOMATIC, NEULIB_APPL_CONST) name,
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc,
    NeuTimeOutFunc_Type timeout,
    P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) parameter,
    NeuLibTick_Type time,
    uint8 flag
)
{
    NeuLibTimer_Type *timer;

    /* Allocate the timer object. */
    timer = (NeuLibTimer_Type *)NeuLibMemPool_Malloc(desc);
    if (NULL_PTR == timer)
    {
        return NULL_PTR;
    }

    NeuLib_memset(timer, 0u, sizeof(NeuLibTimer_Type));
    timer->timeoutFunc  = timeout;
    timer->parameter    = parameter;

    timer->flag         = flag;
    timer->initTick     = time;
    timer->timeoutTick  = 0u;

    /* initialize timer list */
    NeuLibList_Init(&timer->row);

#if NEU_DEBUG
    NeuLib_memcpy(timer->name, name, NeuLib_strlen(name));
#else
    NEU_UNUSED_ARG(name);
#endif  /* NEU_DEBUG */

    return timer;
}

/*
********************************************************************************
* Function Name: NeuLibTimer_Delete
*
* Explanation:   This function will delete a timer and release timer memory.
* (Synchronous)
*
* param:         desc  Memory pool descriptor.
*                timer The timer to be deleted.
*
* retval:        Always E_OK.
********************************************************************************
*/
FUNC(Std_ReturnType, NEULIB_CODE) NeuLibTimer_Delete(
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc,
    P2VAR(NeuLibTimer_Type, AUTOMATIC, NEULIB_APPL_DATA) timer
)
{
    NEULIB_SYS_ARCH_DECL_PROTECT(level);

    /* parameter check */
    NEULIB_ASSERT_MSG("NeuLibTimer", "", timer != NULL_PTR);

    /* disable interrupt */
    NEULIB_SYS_ARCH_PROTECT(level);

    NeuLibList_Remove(&timer->row);

    /* enable interrupt */
    NEULIB_SYS_ARCH_UNPROTECT(level);

    /* Free the timer object. */
    NeuLibMemPool_Free(desc, timer);

    return E_OK;
}

/*
********************************************************************************
* Function Name: NeuLibTimer_Start
*
* Explanation:   This function will start the timer.
* (Synchronous)
*
* param:         getTick   Retrieves the specified timer heartbeat value.
*                timer     The timer to be started
*                timerList Soft timer list.
*
* retval:        The operation status, E_OK on OK.
********************************************************************************
*/
FUNC(Std_ReturnType, NEULIB_CODE) NeuLibTimer_Start(
    NeuLibTimeGetTick_Type getTick,
    P2VAR(NeuLibTimer_Type, AUTOMATIC, NEULIB_APPL_DATA) timer,
    P2VAR(NeuLibList_Type, AUTOMATIC, NEULIB_APPL_DATA)  timerList
)
{
    NeuLibList_Type *rowHead;

    NEULIB_SYS_ARCH_DECL_PROTECT(level);

    /* parameter check */
    NEULIB_ASSERT_MSG("NeuLibTimer", "", timer != NULL_PTR);
    NEULIB_ASSERT_MSG("NeuLibTimer", "", getTick != NULL_PTR);
    NEULIB_ASSERT_MSG("NeuLibTimer", "", timerList != NULL_PTR);

    /* stop timer firstly */
    NEULIB_SYS_ARCH_PROTECT(level);

    /* Remove timer from list. */
    NeuLibList_Remove(&timer->row);
    /* change status of timer */
    timer->flag &= ~NEULIB_TIMER_FLAG_ACTIVATED;

    timer->timeoutTick = getTick() + timer->initTick;

    for (rowHead = timerList; rowHead != timerList->prev; rowHead = rowHead->next)
    {
        NeuLibTimer_Type *t;
        NeuLibList_Type *p = rowHead->next;

        /* fix up the entry pointer */
        t = NeuLibList_Entry(p, NeuLibTimer_Type, row);

        /**
         * If we have two timers that timeout at the same time, it's
         * preferred that the timer inserted early get called early.
         * So insert the new timer to the end the the some-timeout timer
         * list.
         */
        if ((t->timeoutTick - timer->timeoutTick) == 0)
        {
            continue;
        }
        else if ((t->timeoutTick - timer->timeoutTick) < NeuLibTickMax)
        {
            break;
        }
        else
        {
            /* Do nothing. */
        }
    }

    NeuLibList_InsertAfter(rowHead, &timer->row);

    timer->flag |= NEULIB_TIMER_FLAG_ACTIVATED;
    /* enable interrupt */
    NEULIB_SYS_ARCH_UNPROTECT(level);

    return E_OK;
}

/*
********************************************************************************
* Function Name: NeuLibTimer_Stop
*
* Explanation:   This function will stop the timer.
* (Synchronous)
*
* param:         timer The timer to be stopped.
*
* retval:        None
********************************************************************************
*/
FUNC(Std_ReturnType, NEULIB_CODE) NeuLibTimer_Stop(
    P2VAR(NeuLibTimer_Type, AUTOMATIC, NEULIB_APPL_DATA) timer
)
{
    NEULIB_SYS_ARCH_DECL_PROTECT(level);

    /* parameter check */
    NEULIB_ASSERT_MSG("NeuLibTimer", "", timer != NULL_PTR);

    /* disable interrupt */
    NEULIB_SYS_ARCH_PROTECT(level);

    NeuLibList_Remove(&timer->row);

    /* enable interrupt */
    NEULIB_SYS_ARCH_UNPROTECT(level);

    return E_OK;
}

/*
********************************************************************************
* Function Name: NeuLibTimer_Entry
*
* Explanation:   Software timer thread entry.
* (Synchronous)
*
* param:         getTick   Retrieves the specified timer heartbeat value.
*                timerList Is the array of time list.
*
* retval:        None
********************************************************************************
*/
FUNC(void, NEULIB_CODE) NeuLibTimer_Entry(
    NeuLibTimeGetTick_Type getTick,
    P2VAR(NeuLibList_Type, AUTOMATIC, NEULIB_APPL_DATA)  timerList
)
{
    NeuLibTick_Type currentTick;
    NeuLibTimer_Type *t;
    NeuLibList_Type list;
    NEULIB_SYS_ARCH_DECL_PROTECT(level);

    /* get the next timeout tick */
    if (NeuLibList_IsEmpty(timerList))
    {
        /* no software timer exist, suspend self. */
        return ;
    }

    NeuLibList_Init(&list);

    NEULIB_DEBUG_LOG("NeuLibTimer", ("software timer check enter\n"));

    /* Disable interrupt. */
    NEULIB_SYS_ARCH_PROTECT(level);

    while (!NeuLibList_IsEmpty(timerList))
    {
        t = NeuLibList_Entry(timerList->next, NeuLibTimer_Type, row);

        currentTick = getTick();

        /* It supposes that the new tick shall less than the half duration of tick max. */
        if ((currentTick - t->timeoutTick) < NeuLibTickMax)
        {

            /* Remove timer from timer list firstly. */
            NeuLibList_Remove(&t->row);

            /* Add timer to temporary list.  */
            NeuLibList_InsertAfter(&list, &t->row);

            /* Enable interrupt */
            NEULIB_SYS_ARCH_UNPROTECT(level);

            /* Call timeout function. */
            t->timeoutFunc(t->parameter);

            NEULIB_DEBUG_LOG("NeuLibTimer", ("current tick: %d\n", currentTick));

            /* Disable interrupt. */
            NEULIB_SYS_ARCH_PROTECT(level);

            /* Check whether the timer object is detached or started again. */
            if (NeuLibList_IsEmpty(&list))
            {
                continue;
            }
            NeuLibList_Remove(&t->row);

            if ((t->flag & NEULIB_TIMER_FLAG_PERIODIC) &&
                (t->flag & NEULIB_TIMER_FLAG_ACTIVATED)
            )
            {
                /* Start it. */
                t->flag &= ~NEULIB_TIMER_FLAG_ACTIVATED;
                NeuLibTimer_Start(getTick, t, timerList);
            }
        }
        else
        {
            break; /* not check anymore */
        }
    }
    /* enable interrupt */
    NEULIB_SYS_ARCH_UNPROTECT(level);

    NEULIB_DEBUG_LOG("NeuLibTimer", ("software timer check leave\n"));
}

#define NEULIB_STOP_SEC_CODE
#include "NeuLib_MemMap.h"
