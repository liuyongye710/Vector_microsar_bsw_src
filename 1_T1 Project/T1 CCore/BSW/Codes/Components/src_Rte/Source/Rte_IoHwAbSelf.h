/*
********************************************************************************
*
* File name: Rte_IoHwAbSelf.h
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
#ifndef RTE_IOHWABSELF_H_
#define RTE_IOHWABSELF_H_
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Rte_Type.h"
#include "Os.h"

/*
********************************************************************************
*    extern declaration of RTE buffers
********************************************************************************
*/

/*
********************************************************************************
*    RTE Helper-Functions prototypes
********************************************************************************
*/
#define RTE_START_SEC_CODE
#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) Rte_MemCpy(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) destination, P2CONST(void, AUTOMATIC, RTE_APPL_DATA) source, uint32_least num);
FUNC(void, RTE_CODE) Rte_MemCpy32(P2VAR(void, AUTOMATIC, RTE_APPL_VAR) destination, P2CONST(void, AUTOMATIC, RTE_APPL_DATA) source, uint32_least num);
#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h"

/*
********************************************************************************
*    API prototypes
********************************************************************************
*/

/*
********************************************************************************
*    Rte_IRead_<r>_<p>_<d>
*    Rte_IStatus_<r>_<p>_<d>
*    Rte_IWrite_<r>_<p>_<d>
*    Rte_IWriteRef_<r>_<p>_<d>
*    Rte_IInvalidate_<r>_<p>_<d>
********************************************************************************
*/

/*
********************************************************************************
*    Rte_Receive_<p>_<d> (explicit S/R communication with isQueued = true)
********************************************************************************
*/

/*
********************************************************************************
*    Rte_Send_<p>_<d> (explicit S/R communication with isQueued = true)
********************************************************************************
*/

/*
********************************************************************************
*    Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
********************************************************************************
*/

/*
********************************************************************************
*    Rte_IsUpdated_<p>_<d> (explicit S/R communication with isQueued = false)
********************************************************************************
*/

/*
********************************************************************************
*    Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
********************************************************************************
*/

/*
********************************************************************************
*    Periodic Runnable entities 
********************************************************************************
*/
#define RTE_START_SEC_CODE
#include "Rte_MemMap.h"
FUNC(void, RTE_CODE) BswM_CheckShutDown_MainFunction(void);
FUNC(void, RTE_CODE) CDS_Mainfunction(void);
FUNC(void, RTE_CODE) Com_MainFunctionRx(void);
FUNC(void, RTE_CODE) Com_MainFunctionTx(void);
FUNC(void, RTE_CODE) Dsm_MainFunction(void);
FUNC(void, RTE_CODE) EcuM_StartupTwo(void);
FUNC(void, RTE_CODE) Fls_MainFunction(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void);
FUNC(void, RTE_CODE) Runnable1000ms_Core0(void);
FUNC(void, RTE_CODE) Runnable1000ms_Core1(void);
FUNC(void, RTE_CODE) Runnable1000ms_Core2(void);
FUNC(void, RTE_CODE) Runnable100ms_Core0(void);
FUNC(void, RTE_CODE) Runnable100ms_Core1(void);
FUNC(void, RTE_CODE) Runnable100ms_Core2(void);
FUNC(void, RTE_CODE) Runnable10ms_Core0(void);
FUNC(void, RTE_CODE) Runnable10ms_Core1(void);
FUNC(void, RTE_CODE) Runnable10ms_Core2(void);
FUNC(void, RTE_CODE) Runnable1ms_Core2(void);
FUNC(void, RTE_CODE) Runnable200ms_Core0(void);
FUNC(void, RTE_CODE) Runnable200ms_Core1(void);
FUNC(void, RTE_CODE) Runnable200ms_Core2(void);
FUNC(void, RTE_CODE) Runnable20ms_Core0(void);
FUNC(void, RTE_CODE) Runnable20ms_Core1(void);
FUNC(void, RTE_CODE) Runnable20ms_Core2(void);
FUNC(void, RTE_CODE) Runnable2ms_Core0(void);
FUNC(void, RTE_CODE) Runnable4ms_Core2(void);
FUNC(void, RTE_CODE) Runnable500ms_Core0(void);
FUNC(void, RTE_CODE) Runnable500ms_Core1(void);
FUNC(void, RTE_CODE) Runnable500ms_Core2(void);
FUNC(void, RTE_CODE) Runnable50ms_Core0(void);
FUNC(void, RTE_CODE) Runnable50ms_Core1(void);
FUNC(void, RTE_CODE) Runnable50ms_Core2(void);
FUNC(void, RTE_CODE) Runnable5ms_Core1(void);
FUNC(void, RTE_CODE) Runnable5ms_Core2(void);
FUNC(void, RTE_CODE) RunnableInit_Core0(void);
FUNC(void, RTE_CODE) RunnableInit_Core1(void);
FUNC(void, RTE_CODE) RunnableInit_Core2(void);
FUNC(void, RTE_CODE) SchM_Init(void);
FUNC(void, RTE_CODE) Test_Runnable_Core0_1000ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core0_100ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core0_10ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core0_200ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core0_20ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core0_2ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core0_500ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core0_50ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core0_DefaultInit(void);
FUNC(void, RTE_CODE) Test_Runnable_Core0_Init(void);
FUNC(void, RTE_CODE) Test_Runnable_Core1_1000ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core1_100ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core1_10ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core1_200ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core1_20ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core1_500ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core1_50ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core1_5ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core1_DefaultInit(void);
FUNC(void, RTE_CODE) Test_Runnable_Core1_Init(void);
FUNC(void, RTE_CODE) Test_Runnable_Core2_1000ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core2_100ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core2_10ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core2_1ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core2_200ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core2_20ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core2_500ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core2_50ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core2_5ms(void);
FUNC(void, RTE_CODE) Test_Runnable_Core2_DefaultInit(void);
FUNC(void, RTE_CODE) Test_Runnable_Core2_Init(void);
#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h"

#endif /* RTE_IOHWABSELF_H_ */

