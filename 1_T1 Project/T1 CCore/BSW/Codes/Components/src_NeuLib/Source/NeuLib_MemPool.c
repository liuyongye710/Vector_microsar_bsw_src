/*
********************************************************************************
*
* File name: NeuLib_MemPool.c
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
* Change: 1.Add a memory-map label to function.
*         2.Modify memory-map label error.
*         3.Modify copyright.
*         4.Modify FUNC_P2VAR error.
* Cause: Bugfix
********************************************************************************
*/
#include "NeuLib_MemPool.h"
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

#define NEULIB_STOP_SEC_CONST
#include "NeuLib_MemMap.h"

/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
#define NEULIB_START_SEC_CODE
#include "NeuLib_MemMap.h"
#if (NEULIB_MEMP_OVERFLOW_CHECK == STD_ON)
static FUNC(void, NEULIB_CODE) NeuMemP_OverflowCheckElement(
    P2VAR(NeuLibMemPool_Type, AUTOMATIC, NEULIB_APPL_DATA) p,
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc
);
static FUNC(void, NEULIB_CODE) NeuMemP_OverflowInitElement(
    P2VAR(NeuLibMemPool_Type, AUTOMATIC, NEULIB_APPL_DATA) p,
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc
);
static FUNC(void, NEULIB_CODE) NeuMemP_OverflowCheckAll(
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc
);
#endif  /* NEULIB_MEMP_OVERFLOW_CHECK == STD_ON */
#define NEULIB_STOP_SEC_CODE
#include "NeuLib_MemMap.h"

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

#if (NEULIB_MEMP_OVERFLOW_CHECK == STD_ON)
/*
********************************************************************************
* Function Name: NeuMemP_OverflowCheckElement
*
* Explanation:   Check if a memp element was victim of an overflow or underflow
*                (e.g. the restricted area after/before it has been altered).
* (Synchronous)
*
* param:         p    The memp element to check.
*                desc The pool p comes from.
*
* retval:        None
********************************************************************************
*/
static FUNC(void, NEULIB_CODE) NeuMemP_OverflowCheckElement(
    P2VAR(NeuLibMemPool_Type, AUTOMATIC, NEULIB_APPL_DATA) p,
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc
)
{
#if (NEU_MEM_SANITY_REGION_AFTER_ALIGNED || NEU_MEM_SANITY_REGION_BEFORE_ALIGNED)
    uint16 k;
    uint8 *m;

#if (NEU_MEM_SANITY_REGION_AFTER_ALIGNED > 0)
    m = (uint8*)p + desc->size;
    for (k = 0; k < NEU_MEM_SANITY_REGION_AFTER_ALIGNED; k++)
    {
        NEULIB_ASSERT_MSG("NeuLibMemPool_Assert", "pool", m[k] == NEULIB_MEM_SANITY_VALUE);
    }
#endif  /* (NEU_MEM_SANITY_REGION_AFTER_ALIGNED > 0) */

#if (NEU_MEM_SANITY_REGION_BEFORE_ALIGNED > 0)
    m = (uint8*)p - NEU_MEM_SANITY_REGION_BEFORE_ALIGNED;
    for (k = 0; k < NEU_MEM_SANITY_REGION_BEFORE_ALIGNED; k++)
    {
        NEULIB_ASSERT_MSG("NeuLibMemPool_Assert", "pool", m[k] == NEULIB_MEM_SANITY_VALUE);
    }
#endif  /* (NEU_MEM_SANITY_REGION_BEFORE_ALIGNED > 0) */

#else   /* (NEU_MEM_SANITY_REGION_AFTER_ALIGNED || NEU_MEM_SANITY_REGION_BEFORE_ALIGNED) */
    NEU_UNUSED_ARG(p);
    NEU_UNUSED_ARG(desc);
    NEU_UNUSED_ARG(descr);
#endif  /* (NEU_MEM_SANITY_REGION_AFTER_ALIGNED || NEU_MEM_SANITY_REGION_BEFORE_ALIGNED) */
}

/*
********************************************************************************
* Function Name: NeuMemP_OverflowInitElement
*
* Explanation:   Initialize the restricted area of on memp element.
* (Synchronous)
*
* param:         p    The memp element to check.
*                desc The pool p comes from.
*
* retval:        None
********************************************************************************
*/
static FUNC(void, NEULIB_CODE) NeuMemP_OverflowInitElement(
    P2VAR(NeuLibMemPool_Type, AUTOMATIC, NEULIB_APPL_DATA) p,
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc
)
{
#if (NEU_MEM_SANITY_REGION_BEFORE_ALIGNED > 0 || NEU_MEM_SANITY_REGION_AFTER_ALIGNED > 0)
    uint8 *m;
#if (NEU_MEM_SANITY_REGION_BEFORE_ALIGNED > 0)
    m = (uint8*)p - NEU_MEM_SANITY_REGION_BEFORE_ALIGNED;
    NeuLib_memset(m, NEULIB_MEM_SANITY_VALUE, NEU_MEM_SANITY_REGION_BEFORE_ALIGNED);
#endif  /* (NEU_MEM_SANITY_REGION_BEFORE_ALIGNED > 0) */

#if (NEU_MEM_SANITY_REGION_AFTER_ALIGNED > 0)
    m = (uint8*)p + desc->size;
    NeuLib_memset(m, NEULIB_MEM_SANITY_VALUE, NEU_MEM_SANITY_REGION_AFTER_ALIGNED);
#endif  /* (NEU_MEM_SANITY_REGION_AFTER_ALIGNED > 0) */

#else   /* (NEU_MEM_SANITY_REGION_BEFORE_ALIGNED > 0 || NEU_MEM_SANITY_REGION_AFTER_ALIGNED > 0) */
    NEU_UNUSED_ARG(p);
    NEU_UNUSED_ARG(desc);
#endif  /* (NEU_MEM_SANITY_REGION_BEFORE_ALIGNED > 0 || NEU_MEM_SANITY_REGION_AFTER_ALIGNED > 0) */
}

/*
********************************************************************************
* Function Name: NeuMemP_OverflowCheckAll
*
* Explanation:   Do an overflow check for all elements in every pool.
* (Synchronous)
*
* param:         desc The pool p comes from.
*
* retval:        None
********************************************************************************
*/
static FUNC(void, NEULIB_CODE) NeuMemP_OverflowCheckAll(
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc
)
{
    uint16 idx;
    NeuLibMemPool_Type *p;

    NEULIB_SYS_ARCH_DECL_PROTECT(old_level);
    NEULIB_SYS_ARCH_PROTECT(old_level);

    p = (NeuLibMemPool_Type *)NEULIB_MEM_ALIGN(desc->base);
    for (idx = 0; idx < desc->num; ++idx)
    {
        NeuMemP_OverflowCheckElement(p, desc);
        p = NEULIB_ALIGNMENT_CAST(NeuLibMemPool_Type *, ((uint8 *)p + desc->size + NEU_MEM_SANITY_REGION_AFTER_ALIGNED));
    }
    NEULIB_SYS_ARCH_UNPROTECT(old_level);
}
#endif  /* NEULIB_MEMP_OVERFLOW_CHECK == STD_ON */

/*
********************************************************************************
* Function Name: NeuLibMemPool_Init
*
* Explanation:   Carves out memp_memory into linked lists for each pool-type.
* (Synchronous)
*
* param:         desc Memory pool descriptor.
*
* retval:        None
********************************************************************************
*/
FUNC(void, NEULIB_CODE) NeuLibMemPool_Init(
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc
)
{
    uint16 idx;
    NeuLibMemPool_Type *memp;

    NEULIB_ASSERT_MSG("NeuLibMemPool_Assert", "NeuLibMemPoolPool_Malloc: The type range is incorrect.", desc != NULL_PTR);
    *desc->tab = NULL_PTR;
    memp = (NeuLibMemPool_Type*)NEULIB_MEM_ALIGN(desc->base);

    /* Create a linked list of memp elements. */
    for (idx = 0u; idx < desc->num; ++idx)
    {
        memp->next = *desc->tab;
        *desc->tab = memp;
#if (NEULIB_MEMP_OVERFLOW_CHECK == STD_ON)
        NeuMemP_OverflowInitElement(memp, desc);
#endif  /* NEULIB_MEMP_OVERFLOW_CHECK == STD_ON */

        /* Cast through void* to get rid of alignment warnings. */
        memp = (NeuLibMemPool_Type *)(void *)(uint8*)(memp + desc->size

#if (NEULIB_MEMP_OVERFLOW_CHECK == STD_ON)
        + NEU_MEM_SANITY_REGION_BEFORE_ALIGNED
#endif  /* NEULIB_MEMP_OVERFLOW_CHECK == STD_ON */
        );
    }
#if (NEULIB_MEMP_STATS_ENABLED == STD_ON)
    desc->stats.avail = desc->num;
#endif  /* (NEULIB_MEMP_STATS_ENABLED == STD_ON) */

#if (NEULIB_MEMP_OVERFLOW_CHECK == STD_ON)
    /* Check everything a first time to see if it worked. */
    NeuMemP_OverflowCheckAll(desc);
#endif  /* NEULIB_MEMP_OVERFLOW_CHECK == STD_ON */
}

/*
********************************************************************************
* Function Name: NeuLibMemPool_Malloc
*
* Explanation:   Get an element from a specific pool.
* (Synchronous)
*
* param:         desc Memory pool descriptor.
*
* retval:        A pointer to the allocated memory or a NULL_PTR pointer on funErr.
********************************************************************************
*/
FUNC_P2VAR(void, NEULIB_APPL_DATA, NEULIB_CODE) NeuLibMemPool_Malloc(
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc
)
{
    NeuLibMemPool_Type *memp;

    NEULIB_ASSERT_MSG("NeuLibMemPool_Assert", "NeuLibMemPoolPool_Malloc: The type range is incorrect.", desc != NULL_PTR);

#if (NEULIB_MEMP_OVERFLOW_CHECK == STD_ON)
    NeuMemP_OverflowCheckAll(desc);
#endif  /* NEULIB_MEMP_OVERFLOW_CHECK == STD_ON */

    NEULIB_SYS_ARCH_DECL_PROTECT(oldLevel);
    NEULIB_SYS_ARCH_PROTECT(oldLevel);

    memp = *desc->tab;
    if (memp != NULL_PTR)
    {
        *desc->tab = memp->next;
        /* memp properly aligned? */
        NEULIB_ASSERT_MSG("NeuLibMemPool_Assert", "NeuLibMemPoolPool_Malloc: memp properly aligned", ((NeuLibMemPtr_Type)memp % NEULIB_MEM_ALIGNMENT) == 0u);

#if (NEULIB_MEMP_STATS_ENABLED == STD_ON)
        desc->stats.used++;
        if (desc->stats.used > desc->stats.max)
        {
            desc->stats.max = desc->stats.used;
        }
#endif  /* (NEULIB_MEMP_STATS_ENABLED == STD_ON) */

        NEULIB_SYS_ARCH_UNPROTECT(oldLevel);
        /* cast through uint8* to get rid of alignment warnings */
        return (void*)memp;
    }
    else
    {
#if (NEULIB_MEMP_STATS_ENABLED == STD_ON)
        desc->stats.err++;
#endif  /* (NEULIB_MEMP_STATS_ENABLED == STD_ON) */
        NEULIB_SYS_ARCH_UNPROTECT(oldLevel);
    }

    return NULL_PTR;
}

/*
********************************************************************************
* Function Name: NeuLibMemPool_Free
*
* Explanation:   Put an element back into its pool.
* (Synchronous)
*
* param:         desc Memory pool descriptor.
*                mem  The memp element to free.
*
* retval:        None
********************************************************************************
*/
FUNC(void, NEULIB_CODE) NeuLibMemPool_Free(
    P2CONST(NeuLibMemPoolDesc_Type, AUTOMATIC, NEULIB_APPL_CONST) desc,
    P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) mem
)
{
    NeuLibMemPool_Type *memp;

    NEULIB_ASSERT_MSG("NeuLibMemPool_Assert", "NeuLibMemPoolPool_Malloc: The type range is incorrect.", desc != NULL_PTR);
    if (mem == NULL_PTR)
    {
        return;
    }

#if (NEULIB_MEMP_OVERFLOW_CHECK == STD_ON)
    NeuMemP_OverflowCheckAll(desc);
#endif  /* NEULIB_MEMP_OVERFLOW_CHECK == STD_ON */

    NEULIB_SYS_ARCH_DECL_PROTECT(oldLevel);

    NEULIB_ASSERT_MSG("NeuLibMemPool_Assert", "Buffer length is not aligned.", ((NeuLibMemPtr_Type)mem % NEULIB_MEM_ALIGNMENT) == 0);

    /* Cast through void* to get rid of alignment warnings. */
    memp = (NeuLibMemPool_Type*)mem;

    NEULIB_SYS_ARCH_PROTECT(oldLevel);

#if (NEULIB_MEMP_STATS_ENABLED == STD_ON)
    desc->stats.used--;
#endif  /* (NEULIB_MEMP_STATS_ENABLED == STD_ON) */

    memp->next = *desc->tab;
    *desc->tab = memp;

    NEULIB_SYS_ARCH_UNPROTECT(oldLevel);
}

#define NEULIB_STOP_SEC_CODE
#include "NeuLib_MemMap.h"
