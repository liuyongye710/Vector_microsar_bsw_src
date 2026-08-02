/*
********************************************************************************
*
* File name: Rte.c
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: Gaol/2022.6.14
* Change: New created.
* Cause: New
********************************************************************************
*/

#define RTE_CORE

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os.h" 
#include "Rte_Type.h"
#include "Rte_Main.h"
#include "Rte_Cbk.h"
#include "Rte_Hook.h"
#include "SchM_BswM.h"
#include "SchM_CanIf.h"
#include "SchM_CanSM.h"
#include "SchM_CanTp.h"
#include "SchM_CanTrcv.h"
#include "Com.h"
#include "SchM_Com.h"
#include "SchM_ComM.h"
#include "SchM_Dcm.h"
#include "SchM_Dem.h"
#include "SchM_EcuM.h"
#include "SchM_Fee.h"
#include "SchM_J1939Tp.h"
#include "SchM_NvM.h"
#include "SchM_Xcp.h"

/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)

#define RTE_START_SEC_VAR_INIT
#include "Rte_MemMap.h"
VAR(uint8, RTE_VAR_INIT) Rte_CoreState[RTE_CORE_COUNT] = {0U};
#define RTE_STOP_SEC_VAR_INIT
#include "Rte_MemMap.h"

#define RTE_START_SEC_CONST
#include "Rte_MemMap.h"
CONST(uint8, RTE_CONST) Rte_CoreInUseState[RTE_CORE_COUNT] = {RTE_CORE_IN_USE, RTE_CORE_IN_USE, RTE_CORE_IN_USE};
#define RTE_STOP_SEC_CONST
#include "Rte_MemMap.h"

#endif

/*
********************************************************************************
*   API for enable / disable interrupts up to the systemLevel.
********************************************************************************
*/
#define Rte_DisableOSInterrupts() SuspendOSInterrupts()
#define Rte_EnableOSInterrupts() ResumeOSInterrupts()


/*
********************************************************************************
*    Definition of Calibration Parameters
********************************************************************************
*/


/*
********************************************************************************
*    Timer handling. 
********************************************************************************
*/

# define RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 (1U)
# define RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 (1U)
# define RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 (1U)

/*
********************************************************************************
*    NvM-Callback for Rte_SetMirror
********************************************************************************
*/

/*
********************************************************************************
*    NvM-Callback for Rte_GetMirror
********************************************************************************
*/

/*
********************************************************************************
*    NvM-Callback for Rte_NvMNotifyInitBlock
********************************************************************************
*/

/*
********************************************************************************
*    NvM-Callback for Rte_NvMNotifyJobFinished
********************************************************************************
*/

/*
********************************************************************************
*    Definition of Rte functions
********************************************************************************
*/
#define RTE_START_SEC_CODE
#include "Rte_MemMap.h"

FUNC(void, RTE_CODE) Rte_MemClr(P2VAR(void, AUTOMATIC, RTE_VAR_NOINIT) ptr, uint16_least num); 
FUNC(void, RTE_CODE) Rte_MemCpy(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) destination, P2CONST(void, AUTOMATIC, RTE_APPL_DATA) source, uint32_least num);
FUNC(void, RTE_CODE) Rte_MemCpy32(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) destination, P2CONST(void, AUTOMATIC, RTE_APPL_DATA) source, uint32_least num);
FUNC(void, RTE_CODE) RteBuff_PushRelease(P2VAR(RteQueueBufferType, AUTOMATIC, RTE_APPL_DATA) cPtr);
FUNC(void, RTE_CODE) RteBuff_PopRelease(P2VAR(RteQueueBufferType, AUTOMATIC, RTE_APPL_DATA) cPtr);
FUNC_P2VAR(void, RTE_APPL_DATA, RTE_CODE) RteBuff_PopLock(P2VAR(RteQueueBufferType, AUTOMATIC, RTE_APPL_DATA) cPtr);
FUNC_P2VAR(void, RTE_APPL_DATA, RTE_CODE) RteBuff_PushLock(P2VAR(RteQueueBufferType, AUTOMATIC, RTE_APPL_DATA) cPtr);
FUNC_P2VAR(void, RTE_APPL_DATA, RTE_CODE) RteStack_Push(P2VAR(RteStackBufferType, AUTOMATIC, RTE_APPL_DATA) cPtr);
FUNC_P2VAR(void, RTE_APPL_DATA, RTE_CODE) RteStack_Pop(P2VAR(RteStackBufferType, AUTOMATIC, RTE_APPL_DATA) cPtr);
FUNC_P2VAR(void, RTE_APPL_DATA, RTE_CODE) Rte_MemSet(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) destination, uint8 c, uint32 num);
FUNC(void, RTE_CODE) Rte_MoveFront(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) cPtr, uint32 bufferLength, uint32 moveLength);
FUNC(void, RTE_CODE) Rte_MoveBehind(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) cPtr, uint32 bufferLength, uint32 moveLength);

FUNC(void, RTE_CODE) Rte_MemCpy(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) destination, P2CONST(void, AUTOMATIC, RTE_APPL_DATA) source, uint32_least num)
{
  P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) src = source;
  P2VAR(uint8, AUTOMATIC, RTE_APPL_VAR) dst = destination;
  uint32_least i;
  for (i = 0; i < num; i++)
  {
    dst[i] = src[i];
  }
}

#define RTE_MEMCPY32ALIGN (sizeof(uint32) - 1)

FUNC(void, RTE_CODE) Rte_MemCpy32(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) destination, P2CONST(void, AUTOMATIC, RTE_APPL_DATA) source, uint32_least num)
{
    #define UNALIGNED(X, Y)     (((uint32)X & (sizeof (uint32) - 1)) | ((uint32)Y & (sizeof (uint32) - 1)))
    #define BIGBLOCKSIZE        (sizeof(uint32) << 2)
    #define LITTLEBLOCKSIZE     (sizeof(uint32))
    #define TOO_SMALL(LEN)      ((LEN) < BIGBLOCKSIZE)
    #define RTE_P2P(_dstPtrType, _ptr)        ((_dstPtrType* )(_ptr))
    uint32 *alignedDst;
    uint32 *alignedSrc;
    uint8* uint8Dst = RTE_P2P(uint8, destination);
    uint8* uint8Src = RTE_P2P(uint8, source);
    if (!TOO_SMALL(num) && !UNALIGNED(source, destination))
    {
        alignedDst = (uint32 *)destination;
        alignedSrc = (uint32 *)source;
        while (num >= BIGBLOCKSIZE)
        {
            *alignedDst++ = *alignedSrc++;
            *alignedDst++ = *alignedSrc++;
            *alignedDst++ = *alignedSrc++;
            *alignedDst++ = *alignedSrc++;
            num -= BIGBLOCKSIZE;
        }
        while (num >= LITTLEBLOCKSIZE)
        {
            *alignedDst++ = *alignedSrc++;
            num -= LITTLEBLOCKSIZE;
        }

        uint8Dst = RTE_P2P(uint8, alignedDst);
        uint8Src = RTE_P2P(uint8, alignedSrc);
    }

    while (num--)
    {
        *uint8Dst++ = *uint8Src++;
    }
}

FUNC(void, RTE_CODE) Rte_MemClr(P2VAR(void, AUTOMATIC, RTE_VAR_NOINIT) ptr, uint16_least num)
{
  P2VAR(uint8, AUTOMATIC, RTE_VAR_NOINIT) dst = ptr;
  uint16_least i;
  for (i = 0; i < num; i++)
  {
    dst[i] = 0;
  }
}

#define RTE_BYTE_ZERO (0U)

FUNC(void, RTE_CODE) RteBuff_PushRelease
(
    P2VAR(RteQueueBufferType, AUTOMATIC, RTE_APPL_DATA) cPtr
)
{
    ++cPtr->currCnt;
}
FUNC(void, RTE_CODE) RteBuff_PopRelease
(
    P2VAR(RteQueueBufferType, AUTOMATIC, RTE_APPL_DATA) cPtr
)
{
    --cPtr->currCnt;
}

FUNC_P2VAR(void, RTE_APPL_DATA, RTE_CODE) RteBuff_PushLock
(
    P2VAR(RteQueueBufferType, AUTOMATIC, RTE_APPL_DATA) cPtr
)
{
    void* dataPtr;
    void* retVal;

    if( (cPtr == NULL_PTR) || (cPtr->currCnt == cPtr->maxCnt) )
    {
        /* No space */
        retVal = NULL_PTR;	
    }
    else
    {
        dataPtr = cPtr->head;
        cPtr->head = (char *)cPtr->head + cPtr->dataSize;
        if( cPtr->head == cPtr->bufEnd )
        {
            cPtr->head = cPtr->bufStart;
        }
        retVal = dataPtr;
    }
    return retVal;
}

FUNC_P2VAR(void, RTE_APPL_DATA, RTE_CODE) RteBuff_PopLock
(
    P2VAR(RteQueueBufferType, AUTOMATIC, RTE_APPL_DATA) cPtr
)
{
    void *dataPtr = NULL_PTR;
    void* retVal;

    if( ((cPtr==NULL_PTR) || (cPtr->currCnt == RTE_BYTE_ZERO)) == TRUE )
    {
        retVal = NULL_PTR;
    }
    else
    {
        dataPtr = cPtr->tail;
        cPtr->tail = (char *)cPtr->tail + cPtr->dataSize;
        if( cPtr->tail == cPtr->bufEnd )
        {
            cPtr->tail = cPtr->bufStart;
        }
        retVal = dataPtr;
    }
    return retVal;
}

FUNC_P2VAR(void, RTE_APPL_DATA, RTE_CODE) RteStack_Push
(
    P2VAR(RteStackBufferType, AUTOMATIC, RTE_APPL_DATA) cPtr
)
{
    void* retVal = NULL_PTR;

    if( (NULL_PTR == cPtr) || (cPtr->currCnt == cPtr->maxCnt) )
    {
        /* No space */
        retVal = NULL_PTR;	
    }
    else
    {
        /* Get pointer and add top */
        retVal = cPtr->top;
        cPtr->top = (char *)cPtr->top + cPtr->dataSize;
        ++cPtr->currCnt;
        
        /* Pointer is error */
        if( cPtr->top > cPtr->bufEnd )
        {
            /* Error: roll-back */
            cPtr->top = (char *)cPtr->top - cPtr->dataSize;
            --cPtr->currCnt;
            retVal = NULL_PTR;
        }
    }
    return retVal;
}

FUNC_P2VAR(void, RTE_APPL_DATA, RTE_CODE) RteStack_Pop
(
    P2VAR(RteStackBufferType, AUTOMATIC, RTE_APPL_DATA) cPtr
)
{
    void* retVal = NULL_PTR;

    if( (NULL_PTR == cPtr) || (RTE_BYTE_ZERO == cPtr->currCnt) )
    {
        /* No data */
        retVal = NULL_PTR;
    }
    else
    {
        /* Subtract top and get pointer */
        cPtr->top = (char *)cPtr->top - cPtr->dataSize;
        --cPtr->currCnt;
        retVal = cPtr->top;
        
        /* Pointer is error */
        if( cPtr->top < cPtr->bufStart )
        {
            /* Error: roll-back */
            cPtr->top = (char *)cPtr->top + cPtr->dataSize;
            ++cPtr->currCnt;
            retVal = NULL_PTR;
        }
    }
    return retVal;
}

#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)

FUNC(void, RTE_CODE) Rte_WaitMasterCoreStart(void)
{
    while(RTE_CORE_STATE_INIT != (uint8)Rte_CoreState[RTE_CORE_MASTER_ID]) {};
}

FUNC(void, RTE_CODE) Rte_WaitMultiCoreSyncStart(void)
{
    uint8 synCoreIdx;
    uint8 allCoreInitOk;
    do
    {
        allCoreInitOk = RTE_CORE_ALL_INIT_OK;
        for(synCoreIdx = 0; synCoreIdx < (uint8)RTE_CORE_COUNT; synCoreIdx++)
        {
            if(RTE_CORE_IN_USE == Rte_CoreInUseState[synCoreIdx] && RTE_CORE_STATE_INIT != Rte_CoreState[synCoreIdx])
            {
                allCoreInitOk = RTE_CORE_NOT_INIT_OK;
            }
        }
    } while(RTE_CORE_ALL_INIT_OK != allCoreInitOk);
}

#endif

FUNC_P2VAR(void, RTE_APPL_DATA, RTE_CODE) Rte_MemSet(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) destination, uint8 c, uint32 num)
{
    P2VAR(uint8, AUTOMATIC, RTE_APPL_VAR) dst = destination;
    uint32 i = 0;
    for(i = 0; i < num; ++i)
    {
        dst[i] = c;
    }
    return destination;
}

FUNC(void, RTE_CODE) Rte_MoveFront(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) cPtr, uint32 bufferLength, uint32 moveLength)
{
    P2VAR(uint8, AUTOMATIC, RTE_APPL_VAR) dst = cPtr;
    uint32 i = 0;
    uint32 iMoveLength = 0;
    uint8 temp = 0;
    for(; iMoveLength < moveLength; ++iMoveLength)
    {
        temp = dst[0];
        for(i = 0; i < bufferLength - 1; ++i)
        {
            dst[i] = dst[i + 1];
        }
        dst[bufferLength - 1] = temp;
    }
}

FUNC(void, RTE_CODE) Rte_MoveBehind(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) cPtr, uint32 bufferLength, uint32 moveLength)
{
    P2VAR(uint8, AUTOMATIC, RTE_APPL_VAR) dst = cPtr;
    uint32 i = 0;
    uint32 iMoveLength = 0;
    uint8 temp = 0;
    for(; iMoveLength < moveLength; ++iMoveLength)
    {
        temp = dst[bufferLength - 1];
        for(i = bufferLength - 1; i > 0 ; --i)
        {
            dst[i] = dst[i - 1];
        }
        dst[0] = temp;
    }
}

/*
********************************************************************************
*    RTE life cycle API. 
********************************************************************************
*/

FUNC(void, RTE_CODE) SchM_Init(void)
{
    uint32 id = GetCoreID();

    if (id == OS_CORE_ID_0)
    {

#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
        Rte_CoreState[0] = RTE_CORE_STATE_SCHM_INIT;
#endif
    }
    if (id == OS_CORE_ID_1)
    {

#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
        Rte_CoreState[1] = RTE_CORE_STATE_SCHM_INIT;
#endif
    }
    if (id == OS_CORE_ID_2)
    {

        (void)SetRelAlarm(RTE_AL_TE_TASK_10MS_CORE2_QM_10MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 10, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 10);
        (void)SetRelAlarm(RTE_AL_TE_TASK_1MS_CORE2_QM_1MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 1, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 1);
        (void)SetRelAlarm(RTE_AL_TE_TASK_5MS_CORE2_QM_5MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 5, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 5);
#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
        Rte_CoreState[2] = RTE_CORE_STATE_SCHM_INIT;
#endif
    }
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void)
{
    uint32 id = GetCoreID();

    if (id == OS_CORE_ID_0)
    {
        (void)ActivateTask(TASK_INIT_CORE0_QM);

        (void)SetRelAlarm(RTE_AL_TE_TASK_1000MS_CORE0_QM_1000MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 1000, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 1000);
        (void)SetRelAlarm(RTE_AL_TE_TASK_100MS_CORE0_QM_100MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 100, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 100);
        (void)SetRelAlarm(RTE_AL_TE_TASK_10MS_CORE0_QM_10MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 10, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 10);
        (void)SetRelAlarm(RTE_AL_TE_TASK_200MS_CORE0_QM_200MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 200, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 200);
        (void)SetRelAlarm(RTE_AL_TE_TASK_20MS_CORE0_QM_20MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 20, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 20);
        (void)SetRelAlarm(RTE_AL_TE_TASK_2MS_CORE0_QM_2MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 2, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 2);
        (void)SetRelAlarm(RTE_AL_TE_TASK_500MS_CORE0_QM_500MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 500, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 500);
        (void)SetRelAlarm(RTE_AL_TE_TASK_50MS_CORE0_QM_50MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 50, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE0 * 50);
#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
        Rte_CoreState[0] = RTE_CORE_STATE_INIT;
#endif
    }
    if (id == OS_CORE_ID_1)
    {
        (void)ActivateTask(TASK_INIT_CORE1_QM);

        (void)SetRelAlarm(RTE_AL_TE_TASK_1000MS_CORE1_QM_1000MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 1000, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 1000);
        (void)SetRelAlarm(RTE_AL_TE_TASK_100MS_CORE1_QM_100MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 100, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 100);
        (void)SetRelAlarm(RTE_AL_TE_TASK_10MS_CORE1_QM_10MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 10, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 10);
        (void)SetRelAlarm(RTE_AL_TE_TASK_200MS_CORE1_QM_200MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 200, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 200);
        (void)SetRelAlarm(RTE_AL_TE_TASK_20MS_CORE1_QM_20MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 20, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 20);
        (void)SetRelAlarm(RTE_AL_TE_TASK_500MS_CORE1_QM_500MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 500, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 500);
        (void)SetRelAlarm(RTE_AL_TE_TASK_50MS_CORE1_QM_50MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 50, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 50);
        (void)SetRelAlarm(RTE_AL_TE_TASK_5MS_CORE1_QM_5MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 5, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE1 * 5);
#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
        Rte_CoreState[1] = RTE_CORE_STATE_INIT;
#endif
    }
    if (id == OS_CORE_ID_2)
    {
        (void)ActivateTask(TASK_INIT_CORE2_QM);

        (void)SetRelAlarm(RTE_AL_TE_TASK_1000MS_CORE2_QM_1000MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 1000, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 1000);
        (void)SetRelAlarm(RTE_AL_TE_TASK_100MS_CORE2_QM_100MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 100, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 100);
        (void)SetRelAlarm(RTE_AL_TE_TASK_200MS_CORE2_QM_200MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 200, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 200);
        (void)SetRelAlarm(RTE_AL_TE_TASK_20MS_CORE2_QM_20MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 20, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 20);
        (void)SetRelAlarm(RTE_AL_TE_TASK_4MS_CORE2_QM_4MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 4, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 4);
        (void)SetRelAlarm(RTE_AL_TE_TASK_500MS_CORE2_QM_500MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 500, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 500);
        (void)SetRelAlarm(RTE_AL_TE_TASK_50MS_CORE2_QM_50MS, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 50, RTE_CONST_MSEC_SYSTEMTIMER_BASE_SYSTEMTIMER_CORE2 * 50);
#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
        Rte_CoreState[2] = RTE_CORE_STATE_INIT;
#endif
    }
    return RTE_E_OK;
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Stop(void)
{
    uint32 id = GetCoreID();

    if (id == OS_CORE_ID_0)
    {
        (void)CancelAlarm(RTE_AL_TE_TASK_1000MS_CORE0_QM_1000MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_100MS_CORE0_QM_100MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_10MS_CORE0_QM_10MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_200MS_CORE0_QM_200MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_20MS_CORE0_QM_20MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_2MS_CORE0_QM_2MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_500MS_CORE0_QM_500MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_50MS_CORE0_QM_50MS);
#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
        Rte_CoreState[0] = RTE_CORE_STATE_SCHM_INIT;
#endif
    }
    if (id == OS_CORE_ID_1)
    {
        (void)CancelAlarm(RTE_AL_TE_TASK_1000MS_CORE1_QM_1000MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_100MS_CORE1_QM_100MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_10MS_CORE1_QM_10MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_200MS_CORE1_QM_200MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_20MS_CORE1_QM_20MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_500MS_CORE1_QM_500MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_50MS_CORE1_QM_50MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_5MS_CORE1_QM_5MS);
#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
        Rte_CoreState[1] = RTE_CORE_STATE_SCHM_INIT;
#endif
    }
    if (id == OS_CORE_ID_2)
    {
        (void)CancelAlarm(RTE_AL_TE_TASK_1000MS_CORE2_QM_1000MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_100MS_CORE2_QM_100MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_200MS_CORE2_QM_200MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_20MS_CORE2_QM_20MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_4MS_CORE2_QM_4MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_500MS_CORE2_QM_500MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_50MS_CORE2_QM_50MS);
#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
        Rte_CoreState[2] = RTE_CORE_STATE_SCHM_INIT;
#endif
    }
    return RTE_E_OK;
}

FUNC(void, RTE_CODE) SchM_Deinit(void)
{
    uint32 id = GetCoreID();

    if (id == OS_CORE_ID_0)
    {
#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
        Rte_CoreState[0] = RTE_CORE_STATE_UNINIT;
#endif
    }
    if (id == OS_CORE_ID_1)
    {
#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
        Rte_CoreState[1] = RTE_CORE_STATE_UNINIT;
#endif
    }
    if (id == OS_CORE_ID_2)
    {
        (void)CancelAlarm(RTE_AL_TE_TASK_10MS_CORE2_QM_10MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_1MS_CORE2_QM_1MS);
        (void)CancelAlarm(RTE_AL_TE_TASK_5MS_CORE2_QM_5MS);
#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
        Rte_CoreState[2] = RTE_CORE_STATE_UNINIT;
#endif
    }
}

/*
********************************************************************************
*    BSW Modules Exclusive Areas 
********************************************************************************
*/

FUNC(void, RTE_CODE) SchM_Enter_BswM_BSWM_EXCLUSIVE_AREA_0(void)
{
    SuspendAllInterrupts();
}

FUNC(void, RTE_CODE) SchM_Exit_BswM_BSWM_EXCLUSIVE_AREA_0(void)
{
    ResumeAllInterrupts();
}

FUNC(void, RTE_CODE) SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_0(void)
{
    SuspendAllInterrupts();
}

FUNC(void, RTE_CODE) SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_0(void)
{
    ResumeAllInterrupts();
}

FUNC(void, RTE_CODE) SchM_Enter_Dcm_DCM_EXCLUSIVE_AREA_0(void)
{
    SuspendAllInterrupts();
}

FUNC(void, RTE_CODE) SchM_Exit_Dcm_DCM_EXCLUSIVE_AREA_0(void)
{
    ResumeAllInterrupts();
}

FUNC(void, RTE_CODE) SchM_Enter_Dem_DEM_EXCLUSIVE_AREA_0(void)
{
    SuspendAllInterrupts();
}

FUNC(void, RTE_CODE) SchM_Exit_Dem_DEM_EXCLUSIVE_AREA_0(void)
{
    ResumeAllInterrupts();
}

FUNC(void, RTE_CODE) SchM_Enter_Xcp_XCP_EXCLUSIVE_AREA_0(void)
{
    SuspendAllInterrupts();
}

FUNC(void, RTE_CODE) SchM_Exit_Xcp_XCP_EXCLUSIVE_AREA_0(void)
{
    ResumeAllInterrupts();
}



#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h"
/*
********************************************************************************
*    COM Callbacks Function definition for Rx Update Notification
********************************************************************************
*/

/*
********************************************************************************
*    COM Callbacks Function definition for Rx Timeout Notification
********************************************************************************
*/

/*
********************************************************************************
*    COM Callbacks Function definition for Map Service
********************************************************************************
*/
