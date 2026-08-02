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
/*!        \file  vSwUpdM_Queue.c
 *        \brief  vSwUpdM queue implementation source file
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define VSWUPDM_QUEUE_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "vSwUpdM_Priv.h"
#include "vSwUpdM_Queue.h"
#include "vSwUpdM_DevError_Impl.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  vSwUpdM_QueueMove
 **********************************************************************************************************************/
/*! \brief         Move queue entry in the same or other queue.
 *  \details       Cut queue entry from current position and place it at a different location (either in same or other queue).
 *  \param[in,out] Queue            Pointer to queue object.
 *  \param[in]     Handle           Handle of queue entry to be moved.
 *  \param[in]     NewPrev          Handle of new predecessor.
 *  \return        Handle of affected entry.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           vSwUpdM_QueueInit executed before, source queue not empty.
 *                 Passed handles have to represent actual predecessor and successor relationship.
 **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vSwUpdM_QueueHandleType, VSWUPDM_CODE) vSwUpdM_QueueMove(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue,
  vSwUpdM_QueueHandleType Handle,
  vSwUpdM_QueueHandleType NewPrev);

/***********************************************************************************************************************
 *  vSwUpdM_QueueMoveFirstFreeEntry
 **********************************************************************************************************************/
/*! \brief         Cut first free entry and insert it into defined location in used queue.
 *  \details       Take first free entry, remove it from free queue and insert it into defined location in used queue.
 *  \param[in,out] Queue            Pointer to queue object.
 *  \param[in]     NewPrev          Handle of new predecessor.
 *  \return        Handle of moved entry.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           vSwUpdM_QueueInit executed before, queue not full.
 **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vSwUpdM_QueueHandleType, VSWUPDM_CODE) vSwUpdM_QueueMoveFirstFreeEntry(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue,
  vSwUpdM_QueueHandleType NewPrev);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_QueueMove
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(vSwUpdM_QueueHandleType, VSWUPDM_CODE) vSwUpdM_QueueMove(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue, /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
  vSwUpdM_QueueHandleType Handle,
  vSwUpdM_QueueHandleType NewPrev )
{
  vSwUpdM_QueueHandleType oldPrev;
  vSwUpdM_QueueHandleType oldNext;
  vSwUpdM_QueueHandleType newNext;
  P2VAR(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) entries;

  entries = Queue->Entries;

  /* Check for matching handles. */
  if (Handle == NewPrev)
  {
    /* Entry requested to be placed behind itself.
     * Can e.g. occur when priority of existing entry is updated.
     * This effectively results in it placed at exact same location.
     * No need to change anything. */
  }
  else
  {
    /* Get current predecessor and successor. */
    oldPrev = entries[Handle].prev;
    oldNext = entries[Handle].next;

    /* Remove entry from old queue. */
    entries[oldPrev].next = oldNext;
    entries[oldNext].prev = oldPrev;

    /* Get new predecessor. */
    newNext = entries[NewPrev].next;

    /* Insert entry into new queue. */
    entries[Handle].prev  = NewPrev;
    entries[NewPrev].next = Handle;
    entries[Handle].next  = newNext;
    entries[newNext].prev = Handle;

    /* Update state of entry to match current queue. */
    entries[Handle].state = entries[NewPrev].state;
  }

  return Handle;
}

/**********************************************************************************************************************
 * vSwUpdM_QueueMoveFirstFreeEntry
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(vSwUpdM_QueueHandleType, VSWUPDM_CODE) vSwUpdM_QueueMoveFirstFreeEntry(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue,
  vSwUpdM_QueueHandleType NewPrev )
{
  vSwUpdM_DevError_Assert(!vSwUpdM_QueueIsFull(Queue), VSWUPDM_DEVERROR_ASSERT_41); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  Queue->UsedCount++;

  /* Move first free entry to new position. */
  return vSwUpdM_QueueMove(Queue, Queue->Entries[VSWUPDM_QUEUE_HANDLE_HEAD_FREE].next, NewPrev);
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**************************************************************
 *  Queue handling
 **************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_QueueInit
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_QueueInit(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue,
  P2VAR(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) Entries,
  vSwUpdM_QueueHandleType Length,
  vSwUpdM_QueuePrioOrderType PrioOrder,
  vSwUpdM_EntityHandleType EntityStart,
  vSwUpdM_EntityHandleType EntityIncrement)
{
  vSwUpdM_QueueHandleType handle;
  vSwUpdM_QueueHandleType prevHandle;
  vSwUpdM_QueueHandleType nextHandle;
  vSwUpdM_EntityHandleType entityHandle;
  P2VAR(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) entry;
  vSwUpdM_QueuePrioType entryPrio;

  /* Start with empty queue by self-reference. */
  entry = &Entries[VSWUPDM_QUEUE_HANDLE_HEAD_USED];
  entry->state  = VSWUPDM_QUEUE_ENTRY_STATE_USED;
  entry->next   = VSWUPDM_QUEUE_HANDLE_HEAD_USED;
  entry->prev   = VSWUPDM_QUEUE_HANDLE_HEAD_USED;
  /* Set default values. */
  if (PrioOrder == VSWUPDM_QUEUE_PRIO_ORDER_DESC)
  {
    entry->prio = VSWUPDM_QUEUE_PRIO_HIGHEST;
  }
  else
  {
    entry->prio = VSWUPDM_QUEUE_PRIO_LOWEST;
  }
  entry->entity = VSWUPDM_QUEUE_ENTITY_HANDLE_NONE;

  /* Setup double linked list of empty queue entries.
   * Head references last entry as predecessor. */
  prevHandle = Length - 1u;
  nextHandle = VSWUPDM_QUEUE_HANDLE_HEAD_FREE;

  entityHandle = EntityStart;

  if (PrioOrder == VSWUPDM_QUEUE_PRIO_ORDER_DESC)
  {
    entryPrio = VSWUPDM_QUEUE_PRIO_LOWEST;
  }
  else
  {
    entryPrio = VSWUPDM_QUEUE_PRIO_HIGHEST;
  }

  /* Append available entries to free queue. */
  for (handle = VSWUPDM_QUEUE_HANDLE_HEAD_FREE; handle < Length; handle++)
  {
    nextHandle++;
    entry = &Entries[handle];

    /* Set predecessor and successor. */
    entry->prev   = prevHandle;
    entry->next   = nextHandle;
    /* Set default values. */
    entry->prio   = entryPrio;
    entry->state  = VSWUPDM_QUEUE_ENTRY_STATE_FREE;

    if (handle == VSWUPDM_QUEUE_HANDLE_HEAD_FREE)
    {
      entry->entity = VSWUPDM_QUEUE_ENTITY_HANDLE_NONE;
    }
    else
    {
      entry->entity = entityHandle;
      entityHandle += EntityIncrement;
    }

    prevHandle = handle;
  }

  /* Last entry references head as successor. */
  Entries[Length - 1u].next = VSWUPDM_QUEUE_HANDLE_HEAD_FREE;

  Queue->Entries    = Entries;
  Queue->Length     = Length;
  Queue->PrioOrder  = PrioOrder;
  Queue->UsedCount  = 0u;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
}

/**********************************************************************************************************************
 * vSwUpdM_QueueAppend
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(vSwUpdM_QueueHandleType, VSWUPDM_CODE) vSwUpdM_QueueAppend(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue)
{
  /* Insert at end of used queue.
     Place between current last entry and tail (== head). */
  return vSwUpdM_QueueMoveFirstFreeEntry(Queue, Queue->Entries[VSWUPDM_QUEUE_HANDLE_HEAD_USED].prev);
}

/**********************************************************************************************************************
 * vSwUpdM_QueueRemove
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(vSwUpdM_QueueHandleType, VSWUPDM_CODE) vSwUpdM_QueueRemove(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue,
  vSwUpdM_QueueHandleType Handle )
{
  vSwUpdM_DevError_Assert(!vSwUpdM_QueueIsEmpty(Queue), VSWUPDM_DEVERROR_ASSERT_42); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  Queue->UsedCount--;

  /* Insert at end of free queue.
     Place between current last entry and tail (== head). */
  return vSwUpdM_QueueMove(Queue, Handle, Queue->Entries[VSWUPDM_QUEUE_HANDLE_HEAD_FREE].prev);
}

/**********************************************************************************************************************
 * vSwUpdM_QueuePrioUpdate
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(vSwUpdM_QueueHandleType, VSWUPDM_CODE) vSwUpdM_QueuePrioUpdate(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue,
  vSwUpdM_QueueHandleType Handle,
  vSwUpdM_QueuePrioType Prio)
{
  vSwUpdM_QueueHandleType prevHandle;
  P2VAR(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) entries;

  entries = Queue->Entries;

  /* Start search at last entry. */
  prevHandle = entries[VSWUPDM_QUEUE_HANDLE_HEAD_USED].prev;

  /* Skip all entries with lower priority.
      Remark: Search is assured to stop at head because it has the highest possible priority. */
  if (Queue->PrioOrder == VSWUPDM_QUEUE_PRIO_ORDER_DESC)
  {
    while (entries[prevHandle].prio < Prio)
    {
      prevHandle = entries[prevHandle].prev;
    }
  }
  else
  {
    while (entries[prevHandle].prio > Prio)
    {
      prevHandle = entries[prevHandle].prev;
    }
  }

  /* Append after first entry with higher or equal priority. */
  (void)vSwUpdM_QueueMove(Queue, Handle, prevHandle);
  /* Update priority of inserted entry. */
  entries[Handle].prio = Prio;

  return Handle;
}

/**********************************************************************************************************************
 * vSwUpdM_QueuePrioInsert
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(vSwUpdM_QueueHandleType, VSWUPDM_CODE) vSwUpdM_QueuePrioInsert(
  P2VAR(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_VAR) Queue,
  vSwUpdM_QueuePrioType Prio)
{
  vSwUpdM_QueueHandleType handle;

  vSwUpdM_DevError_Assert(!vSwUpdM_QueueIsFull(Queue), VSWUPDM_DEVERROR_ASSERT_43); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  Queue->UsedCount++;

   /* Relocate first free entry according to given priority. */
  handle = vSwUpdM_QueuePrioUpdate(Queue, Queue->Entries[VSWUPDM_QUEUE_HANDLE_HEAD_FREE].next, Prio);

  return handle;
}

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Queue.c
 *********************************************************************************************************************/
