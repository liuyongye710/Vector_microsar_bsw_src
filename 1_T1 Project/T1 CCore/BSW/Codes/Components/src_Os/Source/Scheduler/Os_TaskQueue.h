/*
********************************************************************************
*
*  File name: Os_TaskQueue.h
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCl/2021.12.07
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: LiG/2022.11.21
* Change: Change OS_VAR_NOINIT to OS_VAR_NO_INIT.
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: WangJP/2022.12.10
* Change: Modification of coding standard.
* Cause: Optimize
********************************************************************************
* Version: 3.3
* Author/Date: JianGL/2023.01.08
* Change: Fix the problem that data may exceed the boundary when deleting the 
*         scheduling point of the scheduling queue.
* Cause: Bugfix
********************************************************************************
* Version: 3.4
* Author/Date: LiG/2023.2.15
* Change: Modified for QAC.
* Cause: Optimization
********************************************************************************
*/
#ifndef OS_TASKQUEUE_H_
#define OS_TASKQUEUE_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "Os_Task_Types.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/*
********************************************************************************
*    Global Types
********************************************************************************
*/
typedef uint16 Os_TaskQueIdType;

typedef struct
{
    Os_TaskQueIdType writeId;
    Os_TaskQueIdType readId;
    Os_TaskQueIdType usrSize;
    Os_TaskQueIdType size;
    Os_TaskDynRefType* data;
} Os_TaskQueType;

typedef Os_TaskQueType* Os_TaskQueRefType;

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
/*
********************************************************************************
* Function Name: Os_TaskQue_Init
*
* Explanation: Task queue initialization.
*
* param: taskQue: Task queue configuration.
*        dataArray: Queue data.
*        size: Array size
*
* retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_TaskQue_Init
(
    P2VAR(Os_TaskQueType, AUTOMATIC, OS_APPL_DATA) taskQue,
    P2VAR(Os_TaskDynRefType, AUTOMATIC, OS_APPL_DATA) dataArray,
    Os_TaskQueIdType size
)
{
    taskQue->writeId = OS_ZERO_VALUE;
    taskQue->readId  = OS_ZERO_VALUE;
    taskQue->usrSize = OS_ZERO_VALUE;
    taskQue->size    = size;
    taskQue->data    = dataArray;
}

/*
********************************************************************************
* Function Name: Os_TaskQue_Init
*
* Explanation: Task queue pop data.
*
* param: taskQue: Task queue configuration.
*
* retval: Queue data.
********************************************************************************
*/
LOCAL_INLINE FUNC_P2VAR(Os_TaskDynType, OS_APPL_DATA, OS_CODE) Os_TaskQue_Pop
(
    P2VAR(Os_TaskQueType, AUTOMATIC, OS_APPL_DATA) taskQue
)
{
    Os_TaskDynType* data;
    
    data = taskQue->data[taskQue->readId];
    if( taskQue->usrSize > OS_ZERO_VALUE )
    {
        taskQue->readId++;
        taskQue->usrSize--;
        if( taskQue->readId == taskQue->size )
        {
            taskQue->readId = OS_ZERO_VALUE;
        }
    }

    return data;
}

/*
********************************************************************************
* Function Name: Os_TaskQue_PushF
*
* Explanation: Task queue push data form head of queue.
*
* param: taskQue: Task queue configuration.
*        data: Data.
*
* retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_TaskQue_PushF
(
    P2VAR(Os_TaskQueType, AUTOMATIC, OS_APPL_DATA) taskQue,
    P2VAR(Os_TaskDynType, AUTOMATIC, OS_APPL_DATA) data
)
{
    if( taskQue->usrSize < taskQue->size )
    {
        if( OS_ZERO_VALUE == taskQue->readId )
        {
            taskQue->readId = taskQue->size;
        }

        taskQue->readId--;
        taskQue->data[taskQue->readId] = data;
        taskQue->usrSize++;
    }
}

/*
********************************************************************************
* Function Name: Os_TaskQue_Push
*
* Explanation: Task queue push data from the end of the queue.
*
* param: taskQue: Task queue configuration.
*        data: Data.
*
* retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_TaskQue_Push
(
    P2VAR(Os_TaskQueType, AUTOMATIC, OS_APPL_DATA) taskQue,
    P2VAR(Os_TaskDynType, AUTOMATIC, OS_APPL_DATA) data
)
{
    if( taskQue->usrSize < taskQue->size )
    {
        taskQue->data[taskQue->writeId] = data;
        taskQue->writeId++;
        taskQue->usrSize++;
        if( taskQue->writeId == taskQue->size )
        {
            taskQue->writeId = OS_ZERO_VALUE;
        }
    }
}

/*
********************************************************************************
* Function Name: Os_TaskQue_Get
*
* Explanation: Task queue get data .
*
* param: taskQue: Task queue configuration.
*
* retval: Queue data.
********************************************************************************
*/
LOCAL_INLINE FUNC_P2VAR(Os_TaskDynType, OS_APPL_DATA, OS_CODE) Os_TaskQue_Get
(
    P2VAR(Os_TaskQueType, AUTOMATIC, OS_APPL_DATA) taskQue
)
{
    return taskQue->data[taskQue->readId];
}

/*
********************************************************************************
* Function Name: Os_TaskQue_Del
*
* Explanation: Task queue Delete data .
*
* param: taskQue: Task queue configuration.
*        data: Queue data.
*
* retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_TaskQue_Del
(
    P2VAR(Os_TaskQueType, AUTOMATIC, OS_APPL_DATA) taskQue,
    P2CONST(Os_TaskDynType, AUTOMATIC, OS_APPL_CONST) data
)
{
    Os_TaskQueIdType readId = taskQue->readId;
    Os_TaskQueIdType newWriteId = readId;

    while( readId != taskQue->writeId )
    {
       if( data != taskQue->data[readId] )
       {
           taskQue->data[newWriteId] = taskQue->data[readId];
           newWriteId++;
           if( newWriteId >= taskQue->size )
           {
                newWriteId = OS_ZERO_VALUE;
           }
       }
       readId++;
       if( readId >= taskQue->size )
       {
           readId = OS_ZERO_VALUE;
       }
    }
    taskQue->writeId = newWriteId;
}

/*
********************************************************************************
* Function Name: Os_TaskQue_IsEmpty
*
* Explanation: Check if the queue is empty.
*
* param: taskQue: Task queue configuration.
*
* retval: Whether empty.
********************************************************************************
*/
LOCAL_INLINE FUNC(Os_StatusType, OS_CODE) Os_TaskQue_IsEmpty
(
    P2CONST(Os_TaskQueType, AUTOMATIC, OS_APPL_CONST) taskQue
)
{
    return ((Os_StatusType)((taskQue->readId == taskQue->writeId) ? TRUE : FALSE));
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* OS_TASKQUEUE_H_ */
