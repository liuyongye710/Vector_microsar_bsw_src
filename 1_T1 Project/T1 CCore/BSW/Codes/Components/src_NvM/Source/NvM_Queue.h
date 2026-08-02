/*
********************************************************************************
*
* File name: NvM_Queue.h
*
* Copyright 2018-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: WangJipeng/2018.07.03
* Change: New
* Cause: New
********************************************************************************
* Version: 2.0
* Author/Date: Baowanglong/2019.11.12
* Change: Modify the code format
* Cause: Coding Standards
********************************************************************************
* Version: 3.0
* Author/Date: Baowanglong/2020.02.17
* Change: Nothing
* Cause: Update to V3.0
********************************************************************************
* Version: 3.1
* Author/Date: Hanbaiyu/2020.03.27
* Change: Change parameter name from CurBlockId to curBlockId.
* Cause: QAC
********************************************************************************
* Version: 3.2
* Author/Date: Hanbaiyu/2020.09.29
* Change: 1. Change the code style to AUTOSAR format.
*         2. Add definition of paragraph.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: HanBY/2020.11.04
* Change: Deleting memrory maps for variable or function declarations.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: HanBY/2020.12.07
* Change: Modify the code format.
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: WangLX/2024.04.01
* Change: Modify the label of the input parameter Ptrclass for NvM_QueueProcess
*         and NvM_ReQueueProcess.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: WangLX/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.7
* Author/Date: WangLX/2024.08.08
* Change: Change copyright information.
* Cause: Update
********************************************************************************
*/
#ifndef NVM_QUEUE_H_
#define NVM_QUEUE_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"

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
#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

extern FUNC(uint8, NVM_CODE) NvM_QueueAddSort_ImmediateJob
(
    uint16 BlockId,
    uint8 NvM_Ctrl
);
extern FUNC(void, NVM_CODE) NvM_QueueAddSort_StandardJob(uint16 BlockId);
extern FUNC(Std_ReturnType, NVM_CODE) NvM_QueueProcess
(
    uint16 BlockId,
    P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_Point,
    uint8 NvM_Ctrl
);
extern FUNC(Std_ReturnType, NVM_CODE) NvM_ReQueueProcess
(
    uint16 BlockId,
    P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_Point,
    uint8 NvM_Ctrl
);
extern FUNC(Std_ReturnType, NVM_CODE) NvM_CancelQueueProcess(uint16 BlockId);
extern FUNC(uint16, NVM_CODE) NvM_QueuePop(void);

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#endif /* NVM_QUEUE_H_ */
