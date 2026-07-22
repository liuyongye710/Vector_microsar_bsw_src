/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vSwUpdM_Queue.h
 *        \brief  vSwUpdM queue implementation header file
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#ifndef VSWUPDM_QUEUE_H
#define VSWUPDM_QUEUE_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**************************************************************
 *  Queue handling
 **************************************************************/

/*! Reserve two entries in data structure for explicit free and used head. */
#define VSWUPDM_RESERVED_QUEUE_ENTRIES                2u

/* Handles for free and used head. */
#define VSWUPDM_QUEUE_HANDLE_HEAD_USED                0u
#define VSWUPDM_QUEUE_HANDLE_HEAD_FREE                1u
/* Start handle for actual entries. */
#define VSWUPDM_QUEUE_HANDLE_ENTRY_OFFSET             2u

#define VSWUPDM_QUEUE_HANDLE_NONE                     0xFFFFFFFFu

/* Default priorities for queue entries. */
#define VSWUPDM_QUEUE_PRIO_LOWEST                     0x00u
#define VSWUPDM_QUEUE_PRIO_HIGHEST                    0xFFFFFFFFu

#define VSWUPDM_QUEUE_ENTITY_HANDLE_NONE              0xFFFFFFFFu

#define VSWUPDM_QUEUE_SIZE(count)                     ((uint32)(count) + VSWUPDM_RESERVED_QUEUE_ENTRIES)

/**************************************************************
 *  Queue handling
 **************************************************************/

/* Access macros to check for empty queues.
 * A queue is empty if the head references itself (cyclic double linked list). */
#define vSwUpdM_QueueIsEmpty(queue)                   (VSWUPDM_QUEUE_HANDLE_HEAD_USED == (queue)->Entries[VSWUPDM_QUEUE_HANDLE_HEAD_USED].next)
#define vSwUpdM_QueueIsFull(queue)                    (VSWUPDM_QUEUE_HANDLE_HEAD_FREE == (queue)->Entries[VSWUPDM_QUEUE_HANDLE_HEAD_FREE].next)

/* Access macros to get handle of first entry. */
#define vSwUpdM_QueueGetFirstUsedHandle(queue)        ((queue)->Entries[VSWUPDM_QUEUE_HANDLE_HEAD_USED].next)
#define vSwUpdM_QueueGetLastUsedHandle(queue)         ((queue)->Entries[VSWUPDM_QUEUE_HANDLE_HEAD_USED].prev)
#define vSwUpdM_QueueGetFirstFreeHandle(queue)        ((queue)->Entries[VSWUPDM_QUEUE_HANDLE_HEAD_FREE].next)
#define vSwUpdM_QueueGetLastFreeHandle(queue)         ((queue)->Entries[VSWUPDM_QUEUE_HANDLE_HEAD_FREE].prev)

/*! Access macro to entry using handle. */
#define vSwUpdM_QueueGetEntry(queue, handle)          ((queue)->Entries[handle])

#define vSwUpdM_QueueGetEntityHandle(queue, handle)                 (vSwUpdM_QueueGetEntry((queue), (handle)).entity)
#define vSwUpdM_QueueSetEntityHandle(queue, handle, entityHandle)   { vSwUpdM_QueueGetEntry((queue), (handle)).entity = (entityHandle); }

/* Access macros to get first or last entry. */
#define vSwUpdM_QueueGetFirstUsedEntry(queue)         (vSwUpdM_QueueGetEntry((queue), vSwUpdM_QueueGetFirstUsedHandle(queue)))
#define vSwUpdM_QueueGetLastUsedEntry(queue)          (vSwUpdM_QueueGetEntry((queue), vSwUpdM_QueueGetLastUsedHandle(queue)))
#define vSwUpdM_QueueGetFirstFreeEntry(queue)         (vSwUpdM_QueueGetEntry((queue), vSwUpdM_QueueGetFirstFreeHandle(queue)))
#define vSwUpdM_QueueGetLastFreeEntry(queue)          (vSwUpdM_QueueGetEntry((queue), vSwUpdM_QueueGetLastFreeHandle(queue)))

/* Access macros to get fill level of queue. */
#define vSwUpdM_QueueGetNumberOfUsedEntries(queue)    ((queue)->UsedCount)

/* HINT: The cast to vSwUpdM_QueueHandleType is required to avoid an undesired integer promotion to signed (!) integer (see C99 6.3.1.1). */
#define vSwUpdM_QueueGetNumberOfFreeEntries(queue)    ((vSwUpdM_QueueHandleType)((queue)->Length - (queue)->UsedCount))
/* PRQA L:FUNCTIONLIKEMACRO */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef struct
{
  P2VAR(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR)  Entries;
  vSwUpdM_QueueHandleType                                     Length;
  vSwUpdM_QueueHandleType                                     UsedCount;
  vSwUpdM_QueuePrioOrderType                                  PrioOrder;
} vSwUpdM_QueueType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**************************************************************
 *  Queue handling
 **************************************************************/

/***********************************************************************************************************************
 *  vSwUpdM_QueueInit
 **********************************************************************************************************************/
/*! \brief         Initialize queue structure.
 *  \details       Implements two double linked lists, representing a used and a free queue.
 *  \param[in,out] Queue            Pointer to queue object.
 *  \param[in,out] Entries          Pointer to array of queue entries.
 *  \param[in]     Length           Total length of queue, including entries for used and free head.
 *  \param[in]     PrioOrder        VSWUPDM_QUEUE_PRIO_ORDER_DESC   Sort in descending order: Higher values result in higher priority.
 *                                  VSWUPDM_QUEUE_PRIO_ORDER_ASC    Sort in ascending order: Lower values result in higher priority.
 *  \param[in]     EntityStart      Entity handle to be assigned to first entry (excluding head entries).
 *  \param[in]     EntityIncrement  Increment applied to entity handle when assigned to next entry.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 **********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_QueueInit(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue,
  P2VAR(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) Entries,
  vSwUpdM_QueueHandleType Length,
  vSwUpdM_QueuePrioOrderType PrioOrder,
  vSwUpdM_EntityHandleType EntityStart,
  vSwUpdM_EntityHandleType EntityIncrement);

/***********************************************************************************************************************
 *  vSwUpdM_QueueAppend
 **********************************************************************************************************************/
/*! \brief         Append entry to end of queue.
 *  \details       Take first free entry, remove it from free queue and insert it as last entry into used queue.
 *  \param[in,out] Queue            Pointer to queue object.
 *  \return        Handle of appended entry.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           vSwUpdM_QueueInit executed before, queue not full.
 ********************************************************************************************************************/
FUNC(vSwUpdM_QueueHandleType, VSWUPDM_CODE) vSwUpdM_QueueAppend(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue);

/***********************************************************************************************************************
 *  vSwUpdM_QueueRemove
 **********************************************************************************************************************/
/*! \brief         Remove specific entry from queue.
 *  \details       Take specific entry, remove it from queue and insert it as last entry into free queue.
 *  \param[in,out] Queue            Pointer to queue object.
 *  \param[in]     Handle           Queue entry handle.
 *  \return        Handle of removed entry.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           vSwUpdM_QueueInit executed before, queue not empty.
 **********************************************************************************************************************/
FUNC(vSwUpdM_QueueHandleType, VSWUPDM_CODE) vSwUpdM_QueueRemove(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue,
  vSwUpdM_QueueHandleType Handle);

/***********************************************************************************************************************
 *  vSwUpdM_QueuePrioUpdate
 **********************************************************************************************************************/
/*! \brief         Update priority of a queue entry.
 *  \details       Take specific entry, remove it from queue and re-insert it according to the updated priority.
 *  \param[in,out] Queue            Pointer to queue object.
 *  \param[in]     Handle           Queue entry handle.
 *  \param[in]     Prio             New priority value.
 *  \return        Handle of updated entry.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           vSwUpdM_QueueInit executed before, queue not empty.
 **********************************************************************************************************************/
FUNC(vSwUpdM_QueueHandleType, VSWUPDM_CODE) vSwUpdM_QueuePrioUpdate(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue,
  vSwUpdM_QueueHandleType Handle,
  vSwUpdM_QueuePrioType Prio);

/***********************************************************************************************************************
 *  vSwUpdM_QueuePrioInsert
 **********************************************************************************************************************/
/*! \brief         Insert entry into queue using given priority.
 *  \details       Take first free entry, remove it from free queue and insert it according to the given priority.
 *                 Additionally set job associated with queue entry.
 *  \param[in,out] Queue            Pointer to queue object.
 *  \param[in]     Prio             Priority value.
 *  \return        Handle of inserted entry.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           vSwUpdM_QueueInit executed before, queue not full.
 **********************************************************************************************************************/
FUNC(vSwUpdM_QueueHandleType, VSWUPDM_CODE) vSwUpdM_QueuePrioInsert(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue,
  vSwUpdM_QueuePrioType Prio);

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_QUEUE_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Queue.h
 *********************************************************************************************************************/
