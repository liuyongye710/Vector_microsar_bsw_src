/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**     \file     Mirror_Queue.c
 *      \brief    Mirror queue source file
 *
 *      \details  Implementation of Mirror queue.
 *
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
#define MIRROR_QUEUE_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_Queue.h"
#include "Mirror.h"
#include "Mirror_Int.h"

#include "vstdlib.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define MIRROR_QUEUE_INIT_ZERO               (0u)
#define MIRROR_QUEUE_FIRST_BYTE_POS          (0u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/**********************************************************************************************************************
 *  Mirror_QueueGetWriteIdx()
 *********************************************************************************************************************/
/*! \brief       Function returns the write index for the new data
 *  \details     -
 *  \param[in]   queue         The current queue.
 *  \param[in]   useNewElement Flag that indicates if a new queue element shall be used.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(uint16, MIRROR_CODE) Mirror_QueueGetWriteIdx(Mirror_Queue* queue, boolean useNewElement);

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/**********************************************************************************************************************
 *  Mirror_QueueGetWriteIdx()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(uint16, MIRROR_CODE) Mirror_QueueGetWriteIdx(Mirror_Queue* queue, boolean useNewElement)
{
  /* #10 If a new element shall be used: */
  if(useNewElement == TRUE)
  {
    /*#20 Update queue read and write index. */
    queue->FreeElements--;
    queue->WriteIdx++;

    if(queue->WriteIdx >= queue->QueueSize)
    {
      queue->WriteIdx = MIRROR_QUEUE_INIT_ZERO;
    }

    Mirror_GetDestinationQueueMgmtBuffer(queue->WriteIdx).Length = MIRROR_QUEUE_INIT_ZERO;
  }

  /* #30 Return the write index. */
  return queue->WriteIdx;
} /* Mirror_QueueGetWriteIdx() */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/**********************************************************************************************************************
 *  Mirror_QueueInit()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_QueueInit(Mirror_Queue* queue, uint8* queueBuffer, uint16 queueElementCount, 
                                         uint16 queueElementLength)
{
  uint16 i;

  /* #10 Set the queue configuration of the current destination channel. */
  queue->FreeElements = queueElementCount;
  queue->QueueSize = queueElementCount;
  queue->QueueElementLength = queueElementLength;
  queue->ReadIdx = MIRROR_QUEUE_INIT_ZERO;
  queue->WriteIdx = queueElementCount;

  /* #20 Initialize the queue elements. */
  for(i = 0u; i < queue->QueueSize; i++)
  {
    Mirror_GetDestinationQueueMgmtBuffer(i).Length = MIRROR_QUEUE_INIT_ZERO;
    Mirror_GetDestinationQueueMgmtBuffer(i).Data = &queueBuffer[(queueElementLength * i)];
  }
} /* Mirror_QueueInit() */

/**********************************************************************************************************************
 *  Mirror_QueueRead()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_QueueRead(Mirror_Queue* queue, uint8* queueElement, uint16* length)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 If there is at least one element in the queue: */
  if(Mirror_QueueIsEmpty(queue) == FALSE)
  {
    uint16 queueElementLength = Mirror_GetDestinationQueueMgmtBuffer(queue->ReadIdx).Length;

    /* #20 Copy the content of the next element of the queue to the given buffer, if the given buffer is big enough. */
    if((*length) >= queueElementLength)
    {
      VStdLib_MemCpy(queueElement, Mirror_GetDestinationQueueMgmtBuffer(queue->ReadIdx).Data, queueElementLength); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

      (*length) = queueElementLength;

      retVal = E_OK;
    }

    /* #30 Update queue read and write index. */
    queue->FreeElements++;
    queue->ReadIdx++;

    if(queue->ReadIdx >= queue->QueueSize)
    {
      queue->ReadIdx = MIRROR_QUEUE_INIT_ZERO;
    }
  }

  return retVal;
} /* Mirror_QueueRead() */

/**********************************************************************************************************************
 *  Mirror_QueueWrite()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_QueueWrite(Mirror_Queue* queue, const uint8* data, uint16 length, 
                                                    boolean useNewElement, uint16 writeOffset)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 If there is a free element in the queue: */
  if(queue->FreeElements > 0u)
  {
    /* #20 Get the write index of the current used queue element */
    uint16 writeIdx = Mirror_QueueGetWriteIdx(queue, useNewElement);

    /* #30 Copy the given data to the queue element and update the write index. */
    VStdLib_MemCpy(&(Mirror_GetDestinationQueueMgmtBuffer(writeIdx).Data[writeOffset]), data, length); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    Mirror_GetDestinationQueueMgmtBuffer(writeIdx).Length += length;

    retVal = E_OK;
  }

  return retVal;
} /* Mirror_QueueWrite() */

/**********************************************************************************************************************
 *  Mirror_QueueIsEmpty()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, MIRROR_CODE) Mirror_QueueIsEmpty(const Mirror_Queue* queue)
{
  boolean retVal = FALSE;

  /* #10 If the queue is empty, return TRUE. */
  if(queue->FreeElements == queue->QueueSize)
  {
    retVal = TRUE;
  }

  return retVal;
} /* Mirror_QueueIsEmpty() */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  END OF FILE: Mirror_Queue.c
 *********************************************************************************************************************/
