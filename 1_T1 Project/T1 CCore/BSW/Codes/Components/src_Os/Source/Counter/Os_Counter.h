/*
********************************************************************************
*
*  File name: Os_Counter.h
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCL/2021.11.16
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: LiG/2022.11.21
* Change: Change OS_VAR_NOINIT to OS_VAR_NO_INIT.
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: JiangGL/2022.11.23
* Change: Added Os_ Counter_ SetNextPoint interface.
* Cause: Bugfix
********************************************************************************
* Version: 3.3
* Author/Date: WangJP/2022.12.10
* Change: Modification of coding standard.
* Cause: Optimize
********************************************************************************
* Version: 3.4
* Author/Date: HanCL/2023.1.12
* Change: Add Os_Counter_TargetGetCounterValue interfaces to add multi-core
          call functionality.
* Cause: Update
********************************************************************************
* Version: 3.5
* Author/Date: LiG/2023.2.14
* Change: Notes optimization and parameter type change.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: LiG/2023.2.15
* Change: Modified for QAC.
* Cause: Optimization
********************************************************************************
* Version: 3.7
* Author/Date: JiangGL/2023.6.9
* Change: Solve the issue of setting expiration points for error reporting.
* Cause: Bugfix
********************************************************************************
*/
#ifndef OS_COUNTER_H_
#define OS_COUNTER_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "Os_Counter_Types.h"
#include "Os_Platform_Lcfg.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/* Get the counter static configuration by counter id. */
#define OS_COUNTER_GETCFG(cntId) (Os_CounterCfgData[cntId])
/* Get the counter dynamic configuration. */
#define OS_COUNTER_GETDYN(cntCfg, type) (((type)(cntCfg))->counterDyn)
/* Get half of the maximum allowed value of counter. */
#define OS_COUNTER_GET_HALF_MAXVALUE(cntCfg) ((cntCfg)->maxAllowValue / OS_COUNTER_HALF_VALUE)
/* Determine the validity of the counter in the process of setting the alarm or scheduling table. */
#define OS_COUNTER_CHECKINVALIDVALUE(cntCfg, offset, cycle) (((cycle) > OS_COUNTER_GET_HALF_MAXVALUE(cntCfg))  \
                                                             || (((cntCfg)->minCycle > (cycle)) && ((cycle) > OS_ZERO_VALUE)) \
                                                             || ((offset) > OS_COUNTER_GET_HALF_MAXVALUE(cntCfg)))
/* Counter tick addition operation. */
#define OS_COUNTER_TICKADD(cntCfg, value, addValue) \
        (((addValue) > ((cntCfg)->maxAllowValue - (value))) ? \
        (TickType)((addValue) - ((cntCfg)->maxAllowValue - (value) + OS_ONE_VALUE)) : \
        (TickType)((value) + (addValue)))
/* Counter tick subtraction operation. */
#define OS_COUNTER_TICKSUB(cntCfg, value, subValue) \
        (((value) < (subValue)) ? \
        (TickType)((value) + ((cntCfg)->maxAllowValue - (subValue) + OS_ONE_VALUE)) : \
        (TickType)((value) - (subValue)))

/*
********************************************************************************
*    Global Types
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
/*
********************************************************************************
*    Global Functions
********************************************************************************
*/

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
#if( OS_HRT_ENABLE == STD_ON )
/*
********************************************************************************
* Function Name: Os_Counter_HrtGetCntValue
*
* Explanation: Get HRT counter value.
*
* param: cntBaseCfg: Counter base configuration.
*
* retval: Tick value.
********************************************************************************
*/
LOCAL_INLINE FUNC(Os_TickType, OS_CODE) Os_Counter_HrtGetCntValue
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) cntBaseCfg
)
{
    Os_TickType value = OS_COUNTER_INIT;

     /* If the counter is HRT. */
    if( OS_COUNTER_HRT == cntBaseCfg->counterType )
    {
        value = Os_Arch_Mach_HrtTimerGetValue(((Os_CounterHrtCfgType*)cntBaseCfg)->HwConfig);
    }

    return value;
}

/*
********************************************************************************
* Function Name: Os_Counter_HrtGetCompareValue
*
* Explanation: Get HRT counter compare value.
*
* param: cntBaseCfg: Counter base configuration.
*
* retval: Tick value.
********************************************************************************
*/
LOCAL_INLINE FUNC(Os_TickType, OS_CODE) Os_Counter_HrtGetCompareValue
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) cntBaseCfg
)
{
    Os_TickType value = OS_COUNTER_INIT;

     /* If the counter is HRT. */
    if( OS_COUNTER_HRT == cntBaseCfg->counterType )
    {
        value = Os_Arch_Mach_HrtTimerGetCompareValue(((Os_CounterHrtCfgType*)cntBaseCfg)->HwConfig);
    }

    return value;
}

/*
********************************************************************************
* Function Name: Os_Counter_HrtSetCompareValue
*
* Explanation: Set HRT counter compare value.
*
* param: cntBaseCfg: Counter base configuration.
*        value: The value being set.
*
* retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Counter_HrtSetCompareValue
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) cntBaseCfg,
    Os_TickType value
)
{
    Os_TickType nowValue;

     /* If the counter is HRT. */
    if( OS_COUNTER_HRT == cntBaseCfg->counterType )
    {
        Os_Arch_Mach_HrtTimerSetCompareValue(((Os_CounterHrtCfgType*)cntBaseCfg)->HwConfig, value);

        nowValue = Os_Arch_Mach_HrtTimerGetValue(((Os_CounterHrtCfgType*)cntBaseCfg)->HwConfig);
        if( OS_COUNTER_TICKSUB(cntBaseCfg, value, nowValue) > OS_COUNTER_GET_HALF_MAXVALUE(cntBaseCfg) )
        {
#ifdef OS_SUPPORT_HARDWARE_TRIGGER_INTERRUPT
            Os_Arch_Hrt_TrigerIrq(((Os_CounterHrtCfgType*)cntBaseCfg)->HwConfig);
#else
            Os_TickType lastValue;
            Os_TickType compareValue;
            Os_TickType offsetValue = OS_ONE_VALUE;
            Os_TickType diffValue = OS_ZERO_VALUE;

            /* Make sure that the value set by counter is greater than the value currently fetched. */
            do
            {
                nowValue = Os_Arch_Mach_HrtTimerGetValue(((Os_CounterHrtCfgType*)cntBaseCfg)->HwConfig);
                compareValue = nowValue + offsetValue + diffValue;
                Os_Arch_Mach_HrtTimerSetCompareValue(((Os_CounterHrtCfgType*)cntBaseCfg)->HwConfig, compareValue);
                compareValue = Os_Arch_Mach_HrtTimerGetCompareValue(((Os_CounterHrtCfgType*)cntBaseCfg)->HwConfig);
                lastValue = Os_Arch_Mach_HrtTimerGetValue(((Os_CounterHrtCfgType*)cntBaseCfg)->HwConfig);
                diffValue = OS_COUNTER_TICKSUB(cntBaseCfg, lastValue, nowValue);
                offsetValue++;
            } while( OS_COUNTER_TICKSUB(cntBaseCfg, lastValue, compareValue) < OS_COUNTER_GET_HALF_MAXVALUE(cntBaseCfg) );
#endif
        }
    }
}

/*
********************************************************************************
* Function Name: Os_Counter_HrtClearInterrupt
*
* Explanation: Clear HRT Interrupt flag.
*
* param: cntBaseCfg: Counter base configuration.
*
* retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Counter_HrtClearInterrupt
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) cntBaseCfg
)
{
     /* If the counter is HRT. */
    if( OS_COUNTER_HRT == cntBaseCfg->counterType )
    {
        Os_Arch_Mach_HrtClearInterrupt(((Os_CounterHrtCfgType*)cntBaseCfg)->HwConfig);
    }
}

/*
********************************************************************************
* Function Name: Os_Counter_HrtInit
*
* Explanation: Hrt init.
*
* param: cntBaseCfg: Counter base configuration.
*
* retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Counter_HrtInit
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) cntBaseCfg
)
{
     /* If the counter is HRT. */
    if( OS_COUNTER_HRT == cntBaseCfg->counterType )
    {
        Os_Arch_Mach_HrtTimerInit(((Os_CounterHrtCfgType*)cntBaseCfg)->HwConfig);
    }
}
#endif

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

extern FUNC(Os_StatusType, OS_CODE) Os_Counter_IcrmCnt
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) counterBaseCfg,
    P2VAR(Os_CounterSwDynType, AUTOMATIC, OS_APPL_DATA) counterDyn
);
extern FUNC(void, OS_CODE) Os_Counter_Init
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) cntBaseCfg
);
extern FUNC(void, OS_CODE) Os_Counter_Start
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) cntBaseCfg
);
extern FUNC(void, OS_CODE) Os_Counter_SetNextPoint
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) counterBase
);
extern FUNC(void, OS_CODE) Os_Counter_SetExpPoint
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) counterBase,
    Os_TickType start,
    Os_TickType offset,
    P2VAR(Os_CntExpListNodeCfgType, AUTOMATIC, OS_APPL_DATA) expListNode
);
extern FUNC(Os_StatusType, OS_CODE) Os_Counter_ExpListPop
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) counterBase,
    P2VAR(Os_CntExpListNodeCfgType*, AUTOMATIC, OS_APPL_DATA) expListNode
);
extern FUNC(Os_StatusType, OS_CODE) Os_Counter_ExpPointDel
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) counterBase,
    P2CONST(Os_CntExpListNodeCfgType, AUTOMATIC, OS_APPL_CONST) expListNode
);
extern FUNC(Os_StatusType, OS_CODE) Os_Counter_InsertAbsExpPoint
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) counterBase,
    P2VAR(Os_CntExpListNodeCfgType, AUTOMATIC, OS_APPL_DATA) expListNode,
    Os_TickType start
);
extern FUNC(Os_StatusType, OS_CODE) Os_Counter_InsertExpPoint
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) counterBase,
    P2VAR(Os_CntExpListNodeCfgType, AUTOMATIC, OS_APPL_DATA) expListNode,
    Os_TickType increment
);
extern FUNC(Os_StatusType, OS_CODE) Os_Counter_GetBase
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) counterBase,
    AlarmBaseRefType info
);
extern FUNC(Os_StatusType, OS_CODE) Os_Counter_GetExpTick
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) counterBase,
    P2CONST(Os_CntExpListNodeCfgType, AUTOMATIC, OS_APPL_CONST) expListNode,
    TickRefType tick
);
extern FUNC(Os_TickType, OS_CODE) Os_Counter_GetCntValue
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_APPL_CONST) cntBaseCfg
);

#if( OS_PIT_ENABLE == STD_ON )
extern OS_ISR(OS_PIT);
#endif

#if( OS_HRT_ENABLE == STD_ON )
extern OS_ISR(OS_HRT);
#endif
extern FUNC(Os_StatusType, OS_CODE) Os_Counter_IncrementCounter
(
    CounterType counterId
);
extern FUNC(Os_StatusType, OS_CODE) Os_Counter_GetCounterValue
(
    CounterType counterId,
    TickRefType value
);
extern FUNC(Os_StatusType, OS_CODE) Os_Counter_GetElapsedValue
(
    CounterType counterId,
    TickRefType value,
    TickRefType elapsedValue
);

#if( OS_CFG_MULTI_CORE == STD_ON )
extern FUNC(Os_StatusType, OS_CODE) Os_Counter_TargetGetCounterValue
(
    CounterType counterId,
    TickRefType value
);
#endif /* OS_CFG_MULTI_CORE == STD_ON */

#endif /* OS_COUNTER_H_ */
