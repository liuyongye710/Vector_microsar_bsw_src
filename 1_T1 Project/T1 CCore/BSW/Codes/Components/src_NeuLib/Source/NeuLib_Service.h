/*
********************************************************************************
*
* File name: NeuLib_Service.h
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
*         2.Modify copyright.
* Cause: Bugfix
********************************************************************************
*/
#ifndef NEU_LIST_H_
#define NEU_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
********************************************************************************
*    Includes
********************************************************************************
*/
/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/**
 * NEULIB_CONTAINER_OF - return the start address of struct type, while ptr is the member of struct type.
 */
#define NEULIB_CONTAINER_OF(_ptr, _type, _member)     ((_type *)((char *)(_ptr) - (unsigned long)(&((_type *)0)->_member)))

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
#define NEULIB_START_SEC_CODE
#include "NeuLib_MemMap.h"
/*
********************************************************************************
* Function Name: NeuLibList_Init
*
* Explanation:   Initialize a list.
* (Synchronous)
*
* param:         l list to be initialized
*
* retval:        None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLibList_Init(
    P2VAR(NeuLibList_Type, AUTOMATIC, NEULIB_APPL_DATA) l
)
{
    l->next = l->prev = l;
}

/*
********************************************************************************
* Function Name: NeuLibList_InsertAfter
*
* Explanation:   Insert a node after a list.
* (Synchronous)
*
* param:         l List to insert it.
*                n New node to be inserted.
*
* retval:        None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLibList_InsertAfter(
    P2VAR(NeuLibList_Type, AUTOMATIC, NEULIB_APPL_DATA) l,
    P2VAR(NeuLibList_Type, AUTOMATIC, NEULIB_APPL_DATA) n
)
{
    l->next->prev = n;
    n->next = l->next;

    l->next = n;
    n->prev = l;
}

/*
********************************************************************************
* Function Name: NeuLibList_Remove
*
* Explanation:   Remove node from list.
* (Synchronous)
*
* param:         n the node to remove from the list.
*
* retval:        None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLibList_Remove(
    P2VAR(NeuLibList_Type, AUTOMATIC, NEULIB_APPL_DATA) n
)
{
    n->next->prev = n->prev;
    n->prev->next = n->next;

    n->next = n->prev = n;
}

/*
********************************************************************************
* Function Name: NeuLibList_IsEmpty
*
* Explanation:   Tests whether a list is empty.
* (Synchronous)
*
* param:         l the list to test.
*
* retval:        None
********************************************************************************
*/
LOCAL_INLINE FUNC(Std_ReturnType, NEULIB_CODE) NeuLibList_IsEmpty(
    P2CONST(NeuLibList_Type, AUTOMATIC, NEULIB_APPL_CONST) l
)
{
    return l->next == l ? E_OK : E_NOT_OK;
}
#define NEULIB_STOP_SEC_CODE
#include "NeuLib_MemMap.h"

/*
********************************************************************************
* Function Name: NeuLibList_Entry
*
* Explanation:   Get the struct for this entry.
* (Synchronous)
*
* param:         node   The entry point.
*                type   The type of structure.
*                member The name of list in structure.
*
* retval:        None
********************************************************************************
*/
#define NeuLibList_Entry(node, type, member)  NEULIB_CONTAINER_OF(node, type, member)

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef NEU_LIST_H_ */
