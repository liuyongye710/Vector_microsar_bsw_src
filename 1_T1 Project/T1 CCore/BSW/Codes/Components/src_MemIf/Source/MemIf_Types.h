/*
********************************************************************************
*
* File name: MemIf_Types.h
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
* Change: New created.
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date: TongQian/2015.05.10
* Change: Format adjustment.
* Cause: Optimization
********************************************************************************
* Version: 3.0
* Author/Date:liuziyang/2020.03.27
* Change: Only version update to V3.0.
* Cause: Update
********************************************************************************
* Version: 3.1
* Author/Date: WangLX/2024.08.08
* Change: Change copyright information.
* Cause: Update
********************************************************************************
* Version: 3.2
* Author/Date: WangLX/2024.08.22
* Change: Change file name information.
* Cause: Bugfix
********************************************************************************
*/
#ifndef MEMIF_TYPES_H_
#define MEMIF_TYPES_H_

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
/* Development Errors. */
#define MEMIF_E_NO_ERROR        (0x00u) /* No error. */
#define MEMIF_E_PARAM_DEVICE    (0x01u) /* API service called with wrong device index parameter. */
#define MEMIF_E_PARAM_POINTER   (0x02u) /* API service called with NULL pointer argument. */

/* Deveice ID. */
#define MEMIF_DEVEICE_EA         (0u)   /* EEPROM Abstraction. */
#define MEMIF_DEVEICE_FEE        (1u)   /* Flash EEPROM Emulation. */

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/* Denotes the current status of the underlying abstraction module and device drive. */
typedef enum
{
  MEMIF_UNINIT = 0U,    /* The underlying abstraction module or device driver has not been initialized (yet). */
  MEMIF_IDLE,       /* The underlying abstraction module or device driver is currently idle. */
  MEMIF_BUSY,    /* The underlying abstraction module or device driver is currently busy. */
  MEMIF_BUSY_INTERNAL    /* The underlying abstraction module is busy with internal management operations. The underlying device driver can be busy or idle. */
} MemIf_StatusType;

/* Denotes the result of the last job. */
typedef enum
{
  MEMIF_JOB_OK = 0U,    /* The job has been finished successfully. */
  MEMIF_JOB_FAILED,     /* The job has not been finished successfully. */
  MEMIF_JOB_PENDING,    /* The job has not yet been finished. */
  MEMIF_JOB_CANCELED,   /* The job has been canceled. */
  MEMIF_BLOCK_INCONSISTENT,   /* 1. The requested block is inconsistent, it may contain corrupted data.2. Block is NOT found. */
  MEMIF_BLOCK_INVALID   /* The requested block has been marked as invalid, the requested operation can not be performed. */
} MemIf_JobResultType;

/* Denotes the operation mode of the underlying abstraction modules and device drivers. */
typedef enum
{
    MEMIF_MODE_SLOW = 0U,    /* The underlying memory abstraction modules and drivers are working in slow mode. */
    MEMIF_MODE_FAST    /* The underlying memory abstraction modules and drivers are working in fast mode. */
} MemIf_ModeType;

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

#endif /* MEMIF_TYPES_H_ */
