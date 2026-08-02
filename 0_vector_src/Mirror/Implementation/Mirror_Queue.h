/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!     \file     Mirror_Queue.h
 *      \brief    Mirror queue header file
 *
 *      \details  Header of implementation of mirror queue.
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
#if !defined (MIRROR_QUEUE_H)
# define MIRROR_QUEUE_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ComStack_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Struct for the queue management. */
typedef struct
{
  uint16 ReadIdx;
  uint16 WriteIdx;
  uint16 FreeElements;
  uint16 QueueSize;
  uint16 QueueElementLength;
} Mirror_Queue;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define MIRROR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/**********************************************************************************************************************
 *  Mirror_QueueInit()
 *********************************************************************************************************************/
/*! \brief       Function to initialize the queue.
 *  \details     Queue is initialized depending of the current destination channel.
 *  \param[in]   queue              Queue management information.
 *  \param[in]   queueBuffer        Buffer for the queue.
 *  \param[in]   queueElementCount  Number of elements in the queue.
 *  \param[in]   queueElementLength Size of one element of the queue.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_QueueInit(Mirror_Queue* queue, uint8* queueBuffer, uint16 queueElementCount, 
                                         uint16 queueElementLength);

/**********************************************************************************************************************
 *  Mirror_QueueRead()
 *********************************************************************************************************************/
/*! \brief         Function to read one element from the queue
 *  \details       -
 *  \param[in]     queue        The queue.
 *  \param[out]    queueElement Buffer for the data to read of the queue.
 *  \param[in,out] length       Length of the buffer/Length of the element.
 *  \return        E_OK: A element from the queue is returned
 *  \return        E_NOT_OK: Queue read failed.
 *  \pre           Module is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_QueueRead(Mirror_Queue* queue, uint8* queueElement, uint16* length);

/**********************************************************************************************************************
 *  Mirror_QueueWrite()
 *********************************************************************************************************************/
/*! \brief       Function to store data in the queue
 *  \details     - 
 *  \param[in]   queue         The queue.
 *  \param[in]   data          The data to store in the queue.
 *  \param[in]   length        Length of the data
 *  \param[in]   useNewElement Flag that indicates if a new queue element shall be used
 *  \param[in]   writeOffset   Write offset if no new queue element shall be used
 *  \return      E_OK: Data are written to the queue.
 *  \return      E_NOT_OK: Write operation failed.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_QueueWrite(Mirror_Queue* queue, const uint8* data, uint16 length, 
                                                    boolean useNewElement, uint16 writeOffset);

/**********************************************************************************************************************
 *  Mirror_QueueIsEmpty()
 *********************************************************************************************************************/
/*! \brief       Function that indicates if the queue is empty.
 *  \details     - 
 *  \param[in]   queue  The queue.
 *  \return      TRUE: The queue is empty.
 *  \return      FALSE: The queue is not empty.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(boolean, MIRROR_CODE) Mirror_QueueIsEmpty(const Mirror_Queue* queue);

# define MIRROR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#endif /* MIRROR_QUEUE_H */

/**********************************************************************************************************************
 *  END OF FILE: Mirror_Queue.h
 *********************************************************************************************************************/
