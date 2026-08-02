/*
********************************************************************************
*
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
#include "Rte_IoHwAbSelf.h"
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
    Timer handling
********************************************************************************
*/

/*
********************************************************************************
*    Local Types
********************************************************************************
*/

/*
********************************************************************************
*    Definition of Buffers for unqueued S/R 
********************************************************************************
*/


/*
********************************************************************************
*    Buffers for implicit communication
********************************************************************************
*/

/*
********************************************************************************
*    TxAck/ModeSwitchAck Flags
********************************************************************************
*/

/*
********************************************************************************
*    Update Flags for each Receiver variables
********************************************************************************
*/

/*
********************************************************************************
*    Timeout Flags for each Receiver variables
********************************************************************************
*/

/*
********************************************************************************
*    Invalid Flags for each Receiver variables
********************************************************************************
*/

/*
********************************************************************************
*    Never Received Flags for each external Rx Signal with handleNeverReceived != 0
********************************************************************************
*/

/*
********************************************************************************
*    Definition of Per-Instance Memory variables
********************************************************************************
*/

/*
********************************************************************************
*    Definition of Buffers for inter-runnable variables
********************************************************************************
*/

/*
********************************************************************************
*    Data structures for mode management
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
#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h"

/*
********************************************************************************
*    Client Server API (Rte_Call)
********************************************************************************
*/


/*
********************************************************************************
*    COM-Callbacks for COM Invalid Notification
********************************************************************************
*/

/*
********************************************************************************
*    COM-Callbacks for DataSendCompletedEvent triggered runnables for transmission acknowledgement and error handling
********************************************************************************
*/

/*
********************************************************************************
*    COM Callbacks Function definition for Rx Update Notification
********************************************************************************
*/



/*
********************************************************************************
*    LdCom Callbacks Function definition for TX Trigger Transmit
********************************************************************************
*/

/*
********************************************************************************
*    Definition of Internal/External Tx connections
********************************************************************************
*/

/*
********************************************************************************
*    Definition of Internal/External Rx connections
********************************************************************************
*/
  
/*
********************************************************************************
*    Inter-runnable variable access
********************************************************************************
*/

/*
********************************************************************************
*    Definition of Rte_Invalidate_<p>_<d> (explicit S/R communication with isQueued = false)
********************************************************************************
*/

/*
********************************************************************************
*    Transmission/Mode Switch Acknowledgement handling (Rte_Feedback/Rte_SwitchAck)
********************************************************************************
*/

/*
********************************************************************************
*    Runnable Entities for Nv Block Components
********************************************************************************
*/

/*
********************************************************************************
*    Task bodies for RTE controlled tasks
********************************************************************************
*/
#define RTE_START_SEC_CODE
#include "Rte_MemMap.h"
TASK(Task_Init_Core2_QM)
{
    RunnableInit_Core2();
    Test_Runnable_Core2_Init();

    (void)TerminateTask();
}

TASK(Task_1ms_Core2_QM)
{
    NvM_MainFunction();
    Fee_MainFunction();
    Fls_MainFunction();
    Runnable1ms_Core2();
    Test_Runnable_Core2_1ms();

    (void)TerminateTask();
}

TASK(Task_4ms_Core2_QM)
{
    Runnable4ms_Core2();

    (void)TerminateTask();
}

TASK(Task_5ms_Core2_QM)
{
    EcuM_MainFunction();
    BswM_MainFunction();
    Com_MainFunctionTx();
    Com_MainFunctionRx();
    J1939Tp_MainFunction();
    ComM_MainFunction_0();
    ComM_MainFunction_1();
    ComM_MainFunction_2();
    ComM_MainFunction_3();
    CanSM_MainFunction();
    CanTp_MainFunction();
    Runnable5ms_Core2();
    Test_Runnable_Core2_5ms();

    (void)TerminateTask();
}

TASK(Task_10ms_Core2_QM)
{
    Dcm_MainFunction();
    Dem_MainFunction();
    Dsm_MainFunction();
    CDS_Mainfunction();
    Xcp_MainFunction();
    BswM_CheckShutDown_MainFunction();
    Runnable10ms_Core2();
    Test_Runnable_Core2_10ms();

    (void)TerminateTask();
}

TASK(Task_20ms_Core2_QM)
{
    Runnable20ms_Core2();
    Test_Runnable_Core2_20ms();

    (void)TerminateTask();
}

TASK(Task_50ms_Core2_QM)
{
    Runnable50ms_Core2();
    Test_Runnable_Core2_50ms();

    (void)TerminateTask();
}

TASK(Task_100ms_Core2_QM)
{
    Runnable100ms_Core2();
    Test_Runnable_Core2_100ms();

    (void)TerminateTask();
}

TASK(Task_200ms_Core2_QM)
{
    Runnable200ms_Core2();
    Test_Runnable_Core2_200ms();

    (void)TerminateTask();
}

TASK(Task_500ms_Core2_QM)
{
    Runnable500ms_Core2();
    Test_Runnable_Core2_500ms();

    (void)TerminateTask();
}

TASK(Task_1000ms_Core2_QM)
{
    Runnable1000ms_Core2();
    Test_Runnable_Core2_1000ms();

    (void)TerminateTask();
}

#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h"

/*
********************************************************************************
*    Mode Switch API (Rte_Switch)
********************************************************************************
*/
/*
********************************************************************************
*    Mode Mode API (Rte_Mode)
********************************************************************************
*/
/*
********************************************************************************
*    IsUpdate Func
********************************************************************************
*/

