/*
********************************************************************************
*
*  File name: Os_Arch_Context_Types.h
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCL/2021.11.23
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: JiangGL/2023.09.05
* Change: Fit for CCFC3008.
* Cause: Update
********************************************************************************
*/
#ifndef OS_ARCH_CONTEXT_TYPES_H_
#define OS_ARCH_CONTEXT_TYPES_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "Os_Arch_Types.h"

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/* CPR register default vlaue. */
#define OS_INITIAL_CPR                          (0x00000000U)
/* PSW register user mode bit. */
#define OS_INITIAL_MSR_UM                       (0x00004000U)
/* PSW register interrupt disable bit. */
#define OS_INITIAL_MSR_EE                       (0xFFFF7FFFU)
#ifdef T1_ENABLE
/* MSR register default vlaue. */
#define OS_INITIAL_MSR                          (0x02069200U) /* WangM */
#else /* !defined T1_ENABLE */
#define OS_INITIAL_MSR                          (0x02069000U) /* WangM */
#endif

/* Init vlaue. */
#define OS_CONTEXT_INIT                         (0U)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
struct Os_Arch_ContextDyn
{
    /* Current sp. */
    uint32* currentSp;
};

struct Os_Arch_ContextCfg
{
    struct Os_Arch_ContextDyn* contextDyn;
    /* Machine state register. */
    uint32 msr;
    /* The interrupt level of this thread. */
    uint32 cpr;
    /* Entry point of the thread. */
    uint32 entryAddr;
    /* The return address of this thread. */
    uint32 exitAddr;
    /* Associated stack start address. */
    Os_Stack_Address* stackStartAddr;
    /* Associated stack end address. */
    Os_Stack_Address* stackEndAddr;
};

typedef struct Os_Arch_ContextDyn Os_Arch_ContextDynType;
typedef struct Os_Arch_ContextCfg Os_Arch_ContextCfgType;

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

#endif /* OS_ARCH_CONTEXT_TYPES_H_ */
