/*
********************************************************************************
*
* File name: MemIf_Cfg.h
*
* Copyright 2018-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: WangJipeng/2018.11.13
* Change: New created
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date: WangJipeng/2019.01.05
* Change: Add configuration items.
* Cause: Optimization
********************************************************************************
* Version: 1.2
* Author/Date: TongQian/2019.05.07
* Change: Format adjustment.
* Cause: Optimization
********************************************************************************
* Version: 1.3
* Author/Date: TongQian/2019.05.08
* Change: Add comments.
* Cause: Optimization
********************************************************************************
* Version: 3.0
* Author/Date: WangLX/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.1
* Author/Date: WangLX/2024.08.08
* Change: Change copyright information.
* Cause: Update
********************************************************************************
*/
#ifndef MEMIF_CFG_H_
#define MEMIF_CFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "MemIf_Types.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define MEMIF_DEV_ERROR_DETECT           (STD_ON)
#define MEMIF_NUMBER_OF_DEVICES          (2U)
#define MEMIF_VERSION_INFO_API           (STD_ON)
#define MEMIF_EA_ENABLE                  (STD_OFF)
#define MEMIF_FEE_ENABLE                 (STD_ON)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
typedef struct
{
	void(* SetMode)(MemIf_ModeType Mode);    /* Set the mode. */
	uint8(* Read)(uint16 BlockNumber, uint16 BlockOffset, uint8* DataBufferPtr, uint16 Length);    /* Read Length bytes. */
	uint8(* Write)(uint16 BlockNumber, const uint8* DataBufferPtr);     /* Writes contents. */
	void(* Cancel)(void);    /* Cancel the ongoing asynchronous operation. */
	MemIf_StatusType(* GetStatus)(void);    /* Return the status. */
	MemIf_JobResultType(* GetJobResult)(void);    /* Query the result of the last accepted job issued by the upper layer software. */
	uint8(* InvalidateBlock)(uint16 BlockNumber);    /* Invalidate the block BlockNumber. */
	uint8(* EraseImmediateBlock)(uint16 BlockNumber);    /* Erase the block BlockNumber. */
} MemIf_API_Type_st;

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
#define MEMIF_START_SEC_CONFIG_DATA
#include "MemIf_MemMap.h"

extern CONST(MemIf_API_Type_st, MEMIF_CONFIG_DATA) MemIf_API_Table[MEMIF_NUMBER_OF_DEVICES];

#define MEMIF_STOP_SEC_CONFIG_DATA
#include "MemIf_MemMap.h"

/*
********************************************************************************
*    Global Functions
********************************************************************************
*/

#endif /* MEMIF_CFG_H_ */

