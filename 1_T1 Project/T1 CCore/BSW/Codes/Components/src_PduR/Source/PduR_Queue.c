/*
********************************************************************************
*
*  File name: PduR_Queue.c
*
*  Copyright 2019-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: SunHQ/2022.09.20
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: SunHQ/2022.10.31
* Change: Fixed the PduR_Queue_Write_Pdu_Length function to check the info
*         parameter to prevent access to null pointers.
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: SunHQ/2023.02.10
* Change: Modify the macro that controls the code implementation.
* Cause: Clear compile warning
********************************************************************************
* Version: 3.3
* Author/Date: SunHQ/2023.02.28
* Change: 1.Optimize the processing speed of the queue.
*         2.Add an argument(bufferSizePtr) to the PduR_Queue_LoTpCopyRxData
*           function.
* Cause: Update
********************************************************************************
* Version: 3.4
* Author/Date: SunHQ/2023.03.18
* Change: 1.Modify the PduR_Queue_Write_Pdu function to return BUFREQ_E_OVFL
*           when the queue is insufficient.
*         2.Modify the PduR_Queue_Write_Pdu_Length function to return
*           BUFREQ_E_OVFL when the queue is insufficient.
* Cause: Update
********************************************************************************
* Version: 3.5
* Author/Date: YuHC/2023.05.26
* Change: 1.Add the return value judgment processing of function
*           PduR_LoTpRxIndication.
*         2.Add the return value judgment processing of function
*           PduR_LoTpCopyRxData.
*         3.Add the return value judgment processing of function
*           PduR_LoTpStartOfReception
* Cause: Bugfix
********************************************************************************
* Version: 3.6
* Author/Date: LuQ/2024.03.13
* Change: Memmap modify.
* Cause: Optimization
********************************************************************************
* Version: 3.7
* Author/Date: LuQ/2024.03.18
* Change: Modify P2CONST member labels.
* Cause: Optimization
********************************************************************************
* Version: 3.8
* Author/Date: LuQ/2024.04.02
* Change: 1. Modify the comments format.
*         2. Modify P2CONST member labels.
*         3. Memmap modify.
* Cause: Optimization
********************************************************************************
* Version: 3.9
* Author/Date: LuQ/2024.05.13
* Change: Add Memmap segment definition.
* Cause: Optimization
********************************************************************************
* Version: 3.10
* Author/Date: LuQ/2024.09.20
* Change: 1. Modify Memmap segment definition.
*         2. Add function PduR_Queue_LoTpStartOfReceptionCheck.
*         3. Modify header file.
*         4. Modify copyright information.
* Cause: Optimization
********************************************************************************
* Version: 3.11
* Author/Date: LuQ/2024.09.23
* Change: Modify the comments format.
* Cause: Optimization
********************************************************************************
* Version: 3.12
* Author/Date: LuQ/2024.10.09
* Change: 1. Modify the error message of undefined macro PDUR_MODULE_ID_DCM_UP.
*         2. Modify Memmap segment definition.
* Cause: Bugfix
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "PduR_Queue.h"
#include "PduR_Buffer.h"
#include "PduR.h"
#include "PduR_Router.h"

#if (STD_OFF == PDUR_ZERO_COST_OPERATION)

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
#define PDUR_SDU_NULL_MASK                  (0x10U)
#define PDUR_EVENT_MASK                     (0x0FU)

#define PDUR_EVENT_CANCEL_RECEIVE           (0x00U)
#define PDUR_EVENT_CANCEL_TRANSMIT          (0x01U)
#define PDUR_EVENT_TRANSMIT                 (0x02U)
#define PDUR_EVENT_TXCONFIRMATION           (0x03U)
#define PDUR_EVENT_RXINDICATION             (0x04U)
#define PDUR_EVENT_TP_RXINDICATION          (0x05U)
#define PDUR_EVENT_TP_TXCONFIRMATION        (0x06U)
#define PDUR_EVENT_TP_COPYRXDATA            (0x07U)
#define PDUR_EVENT_TP_STARTOFRECEPTION      (0x08U)

#define PDUR_EVENT_SIZE                     sizeof(uint8)
#define PDUR_ID_SIZE                        sizeof(PduIdType)
#define PDUR_LENGTH_SIZE                    sizeof(PduLengthType)

#define PDUR_PDU_SIZE(SduLength)            (PDUR_ID_SIZE + PDUR_LENGTH_SIZE + (SduLength))

#define PDUR_QUEUE_LEN_0                    (0x00U)

#define PDUR_ROUTING_FLAG_MASK(id)          (0x01U << ((id) % 0x08U))
#define PDUR_ROUTING_FLAG_INDEX(id)         ((id) / 0x08U)

/*
********************************************************************************
*    Local Types
********************************************************************************
*/
typedef struct
{
    P2VAR(uint8, TYPEDEF, PDUR_APPL_DATA) dataPtr;
    uint32 pos;
} PduR_CacheType;

/*
********************************************************************************
*    Local Variables
********************************************************************************
*/
/*
********************************************************************************
*    Local Constants
********************************************************************************
*/
/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"
static FUNC(void, PDUR_CODE) PduR_Cache_WriteData
(
    P2VAR(PduR_CacheType, AUTOMATIC, PDUR_APPL_DATA) cache,
    P2CONST(void, AUTOMATIC, PDUR_APPL_CONST) src,
    uint32 num
);
static FUNC(void, PDUR_CODE) PduR_Cache_ReadData
(
    P2VAR(PduR_CacheType, AUTOMATIC, PDUR_APPL_DATA) cache,
    P2VAR(void, AUTOMATIC, PDUR_APPL_DATA) dst,
    uint32 num
);
static FUNC(void, PDUR_CODE) PduR_Cache_ReadPdu
(
    P2VAR(PduR_CacheType, AUTOMATIC, PDUR_APPL_DATA) cache,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
    boolean read_sdu
);
static FUNC(Std_ReturnType, PDUR_CODE) PduR_Queue_Write_Id
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    uint8 eventCode,
    PduIdType id
);
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Queue_Write_Pdu
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    uint8 eventCode,
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
);
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Queue_Write_Pdu_Length
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    uint8 eventCode,
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
    PduLengthType sduLength
);
static FUNC(Std_ReturnType, PDUR_CODE) PduR_Queue_Write_Result
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    uint8 eventCode,
    PduIdType id,
    Std_ReturnType result
);
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
#define PDUR_START_SEC_GLOBAL_VAR_INIT
#include "PduR_MemMap.h"

extern P2VAR(uint8, PDUR_VAR_INIT, PDUR_APPL_DATA) PduR_RoutingPathFlagTable;

#define PDUR_STOP_SEC_GLOBAL_VAR_INIT
#include "PduR_MemMap.h"

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/*
********************************************************************************
* Function Name: PduR_EventSduExist
*
* Explanation: Check if the SduDataPtr parameter is NULL.
* (Synchronous)
*
* param: eventCode-> The event code used to identify the request.
*
* retval: PDUR_TRUE: The SduDataPtr parameter is not NULL.
*         PDUR_FALSE: The SduDataPtr parameter is NULL.
********************************************************************************
*/
PDUR_LOCAL_INLINE_CORE FUNC(boolean, PDUR_CODE) PduR_EventSduExist
(
    uint8 eventCode
)
{
    boolean retVal = PDUR_FALSE;

    /* Get the sdu exist flag */
    if( (eventCode & PDUR_SDU_NULL_MASK) != PDUR_SDU_NULL_MASK )
    {
        retVal = PDUR_TRUE;
    }

    return retVal;
}

/*
********************************************************************************
* Function Name: PduR_Cache_WriteData
*
* Explanation: Write data to cache.
* (Synchronous)
*
* param: cache-> Pointer to the cache to be used.
*        src-> Pointer to the source of data to be written.
*        num-> Length of data to be written.
*
* retval: None
********************************************************************************
*/
static FUNC(void, PDUR_CODE) PduR_Cache_WriteData
(
    P2VAR(PduR_CacheType, AUTOMATIC, PDUR_APPL_DATA) cache,
    P2CONST(void, AUTOMATIC, PDUR_APPL_CONST) src,
    uint32 num
)
{
    if( (NULL_PTR != cache->dataPtr) && (NULL_PTR != src) )
    {
        uint32 i = 0;

        for( i = 0; i < num; i++ )
        {
            /* Copies the values of num bytes from the location pointed to by
               source directly to the memory of the cache */
            cache->dataPtr[cache->pos + i] = ((const uint8*)src)[i];
        }

        cache->pos += num;
    }
}

/*
********************************************************************************
* Function Name: PduR_Cache_ReadData
*
* Explanation: Read data from cache.
* (Synchronous)
*
* param: cache-> Pointer to the cache to be used.
*        dst-> Pointer to the destination buffer where the data is to be copied.
*        num-> Length of data to be read.
*
* retval: None
********************************************************************************
*/
static FUNC(void, PDUR_CODE) PduR_Cache_ReadData
(
    P2VAR(PduR_CacheType, AUTOMATIC, PDUR_APPL_DATA) cache,
    P2VAR(void, AUTOMATIC, PDUR_APPL_DATA) dst,
    uint32 num
)
{
    if( (NULL_PTR != cache->dataPtr) && (NULL_PTR != dst) )
    {
        uint32 i = 0;

        for( i = 0; i < num; i++ )
        {
            /* Copies the values of num bytes from the cache directly
               to the memory pointed to by destination */
            ((uint8*)dst)[i] = cache->dataPtr[cache->pos + i];
        }

        cache->pos += num;
    }
}

/*
********************************************************************************
* Function Name: PduR_Cache_ReadPdu
*
* Explanation: Read Pdu from cache.
* (Synchronous)
*
* param: cache-> Pointer to the cache to be used.
*        info-> Pointer to the destination Pdu where the data is to be copied.
*        read_sdu-> Whether to read SduData.
*
* retval: None
********************************************************************************
*/
static FUNC(void, PDUR_CODE) PduR_Cache_ReadPdu
(
    P2VAR(PduR_CacheType, AUTOMATIC, PDUR_APPL_DATA) cache,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
    boolean readSdu
)
{
    /* Read sdu length */
    PduR_Cache_ReadData(cache, &info->SduLength, sizeof(info->SduLength));

    if( (PDUR_TRUE == readSdu) && (PDUR_INIT_0 != info->SduLength) )
    {
        /* Read SduDataPtr when not empty */
        info->SduDataPtr = &cache->dataPtr[cache->pos];
        cache->pos += info->SduLength;
    }
}

/*
********************************************************************************
* Function Name: PduR_Queue_Write_Id
*
* Explanation: Write PduId to cache.
* (Synchronous)
*
* param: buffer-> Pointer to the buffer associated with the queue.
*        eventCode-> The event code used to identify the request.
*        id-> PduId to be written.
*
* retval: PDUR_E_OK-> PduId is successfully written to the queue.
*         PDUR_E_NOT_OK-> Failed to write PduId to queue.
********************************************************************************
*/
static FUNC(Std_ReturnType, PDUR_CODE) PduR_Queue_Write_Id
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    uint8 eventCode,
    PduIdType id
)
{
    Std_ReturnType retVal = PDUR_E_NOT_OK;
    const uint32 dataSize = PDUR_EVENT_SIZE + PDUR_ID_SIZE;
    PduR_CacheType cache;

    if( E_OK == GetSpinlock(buffer->spinlockId) )
    {
        /* Allocate enough space for cache */
        cache.dataPtr = PduR_Buffer_Alloc(buffer, dataSize);
        cache.pos = 0;

        if( NULL_PTR != cache.dataPtr )
        {
            PduR_Cache_WriteData(&cache, &eventCode, sizeof(eventCode));
            PduR_Cache_WriteData(&cache, &id, sizeof(id));

            /* Write data to the queue */
            PduR_Buffer_Write(buffer, dataSize);

            retVal = PDUR_E_OK;
        }

        ReleaseSpinlock(buffer->spinlockId);
    }

    return retVal;
}

/*
********************************************************************************
* Function Name: PduR_Queue_Write_Pdu
*
* Explanation: Write Pdu to cache.
* (Synchronous)
*
* param: buffer-> Pointer to the buffer associated with the queue.
*        eventCode-> The event code used to identify the request.
*        id-> PduId to be written to the queue.
*        info-> Pdu to be written to the queue.
*
* retval: BUFREQ_OK-> Pdu is successfully written to the queue.
*         BUFREQ_E_NOT_OK-> Failed to write Pdu to queue.
*         BUFREQ_E_OVFL-> No buffer of the required length can be provided.
********************************************************************************
*/
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Queue_Write_Pdu
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    uint8 eventCode,
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
)
{
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
    const uint32 dataSize = PDUR_EVENT_SIZE + PDUR_PDU_SIZE(info->SduLength);
    PduR_CacheType cache;

    if( E_OK == GetSpinlock(buffer->spinlockId) )
    {
        /* Allocate enough space for cache */
        cache.dataPtr = PduR_Buffer_Alloc(buffer, dataSize);
        cache.pos = 0;

        if( NULL_PTR != cache.dataPtr )
        {
            if( NULL_PTR == info->SduDataPtr )
            {
                /* Set the flag while SudDataPtr is NULL */
                eventCode |= PDUR_SDU_NULL_MASK;
            }

            PduR_Cache_WriteData(&cache, &eventCode, sizeof(eventCode));
            PduR_Cache_WriteData(&cache, &id, sizeof(id));
            PduR_Cache_WriteData(&cache, &info->SduLength, sizeof(info->SduLength));
            PduR_Cache_WriteData(&cache, info->SduDataPtr, info->SduLength);

            /* Write data to the queue */
            PduR_Buffer_Write(buffer, dataSize);

            retVal = BUFREQ_OK;
        }
        else
        {
            retVal = BUFREQ_E_OVFL;
        }

        ReleaseSpinlock(buffer->spinlockId);
    }

    return retVal;
}

/*
********************************************************************************
* Function Name: PduR_Queue_Write_Pdu_Length
*
* Explanation: Write Pdu and TpSduLength to queue.
* (Synchronous)
*
* param: buffer-> Pointer to the buffer associated with the queue.
*        eventCode-> The event code used to identify the request.
*        id-> PduId to be written to the queue.
*        info-> Pdu to be written to the queue.
*        sduLength-> TpSduLength to be written to the queue.
*
* retval: BUFREQ_OK-> Pdu is successfully written to the queue.
*         BUFREQ_E_NOT_OK-> Failed to write Pdu to queue.
*         BUFREQ_E_OVFL-> No buffer of the required length can be provided.
********************************************************************************
*/
static FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Queue_Write_Pdu_Length
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    uint8 eventCode,
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
    PduLengthType sduLength
)
{
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
    const uint8* sduDataPtr = NULL_PTR;
    PduLengthType sduLengthOfPdu = PDUR_INIT_0;
    PduR_CacheType cache;

    if( NULL_PTR != info )
    {
        sduDataPtr = info->SduDataPtr;
        sduLengthOfPdu = info->SduLength;
    }
    else
    {
        /* Set the flag while SudDataPtr is NULL */
        eventCode |= PDUR_SDU_NULL_MASK;
    }

    if( E_OK == GetSpinlock(buffer->spinlockId) )
    {
        const uint32 dataSize = PDUR_EVENT_SIZE + PDUR_PDU_SIZE(sduLengthOfPdu) + PDUR_LENGTH_SIZE;

        /* Allocate enough space for cache */
        cache.dataPtr = PduR_Buffer_Alloc(buffer, dataSize);
        cache.pos = 0;

        if( NULL_PTR != cache.dataPtr )
        {
            PduR_Cache_WriteData(&cache, &eventCode, sizeof(eventCode));
            PduR_Cache_WriteData(&cache, &id, sizeof(id));
            PduR_Cache_WriteData(&cache, &sduLength, sizeof(sduLength));
            PduR_Cache_WriteData(&cache, &sduLengthOfPdu, sizeof(sduLengthOfPdu));
            PduR_Cache_WriteData(&cache, sduDataPtr, sduLengthOfPdu);

            /* Write data to the queue */
            PduR_Buffer_Write(buffer, dataSize);

            retVal = BUFREQ_OK;
        }
        else
        {
            retVal = BUFREQ_E_OVFL;
        }

        ReleaseSpinlock(buffer->spinlockId);
    }

    return retVal;
}

/*
********************************************************************************
* Function Name: PduR_Queue_Write_Result
*
* Explanation: Write Pdu and TpSduLength to queue.
* (Synchronous)
*
* param: buffer-> Pointer to the buffer associated with the queue.
*        eventCode-> The event code used to identify the request.
*        id-> PduId to be written to the queue.
*        result-> Result to be written to the queue.
*
* retval: PDUR_E_OK-> Pdu is successfully written to the queue.
*         PDUR_E_NOT_OK-> Failed to write Pdu to queue.
********************************************************************************
*/
static FUNC(Std_ReturnType, PDUR_CODE) PduR_Queue_Write_Result
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    uint8 eventCode,
    PduIdType id,
    Std_ReturnType result
)
{
    Std_ReturnType retVal = PDUR_E_NOT_OK;
    const uint32 dataSize = PDUR_EVENT_SIZE + PDUR_ID_SIZE + sizeof(result);
    PduR_CacheType cache;

    if( E_OK == GetSpinlock(buffer->spinlockId) )
    {
        /* Allocate enough space for cache */
        cache.dataPtr = PduR_Buffer_Alloc(buffer, dataSize);
        cache.pos = 0;

        if( NULL_PTR != cache.dataPtr )
        {
            PduR_Cache_WriteData(&cache, &eventCode, sizeof(eventCode));
            PduR_Cache_WriteData(&cache, &id, sizeof(id));
            PduR_Cache_WriteData(&cache, &result, sizeof(result));

            /* Write data to the queue */
            PduR_Buffer_Write(buffer, dataSize);

            retVal = PDUR_E_OK;
        }

        ReleaseSpinlock(buffer->spinlockId);
    }

    return retVal;
}

/*
********************************************************************************
* Function Name: PduR_Queue_Init
*
* Explanation: Initialize the PduR queue.
* (Synchronous)
*
* param: buffer-> Pointer to the buffer associated with the queue.
*
* retval: None.
********************************************************************************
*/
FUNC(void, PDUR_CODE) PduR_Queue_Init
(
	P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer
)
{
    /* Initialize the buffer associated with the queue */
    PduR_Buffer_Init(buffer);
}

/*
********************************************************************************
* Function Name: PduR_Queue_UpCancelReceive
*
* Explanation: Requests cancellation of an ongoing reception of an I-PDU in a
*              lower layer transport protocol module.
* (Synchronous)
*
* param: buffer -> Pointer to the buffer associated with the queue.
*        id -> Identification of the I-PDU to be cancelled.
*
* retval: E_OK -> The reception cancellation is accepted by PduR.
*         E_NOT_OK -> The reception cancellation is not accepted by PduR.
********************************************************************************
*/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Queue_UpCancelReceive
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    PduIdType id
)
{
    return PduR_Queue_Write_Id(buffer, PDUR_EVENT_CANCEL_RECEIVE, id);
}

/*
********************************************************************************
* Function Name: PduR_Queue_UpCancelTransmit
*
* Explanation: Requests cancellation of an ongoing transmission of an I-PDU in a
*              lower layer communication interface or transport protocol module.
* (Synchronous)
*
* param: buffer -> Pointer to the buffer associated with the queue.
*        id -> Identification of the I-PDU to be cancelled.
*
* retval: E_OK -> The transmit cancellation is accepted by PduR.
*         E_NOT_OK -> The transmit cancellation is not accepted by PduR..
********************************************************************************
*/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Queue_UpCancelTransmit
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    PduIdType id
)
{
    return PduR_Queue_Write_Id(buffer, PDUR_EVENT_CANCEL_TRANSMIT, id);
}

/*
********************************************************************************
* Function Name: PduR_Queue_UpTransmit
*
* Explanation: Requests transmission of an I-PDU.
* (Asynchronous)
*
* param: buffer -> Pointer to the buffer associated with the queue.
*        id -> Identification of the I-PDU.
*        info -> Length and pointer to the buffer of the I-PDU.
*
* retval: E_OK -> The Transmit request is accepted by PduR;
*                 transmission is continued.
*         E_NOT_OK -> The transmit request is not accepted by PduR;
*                     transmission is aborted.
********************************************************************************
*/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Queue_UpTransmit
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
)
{
    Std_ReturnType retVal = PDUR_E_NOT_OK;

    if( BUFREQ_OK == PduR_Queue_Write_Pdu(buffer, PDUR_EVENT_TRANSMIT, id, info) )
    {
        retVal = PDUR_E_OK;
    }

    return retVal;
}

/*
********************************************************************************
* Function Name: PduR_Queue_LoTxConfirmation
*
* Explanation: The lower layer communication interface module confirms the
*              transmission of an IPDU.
* (Synchronous)
*
* param: buffer -> Pointer to the buffer associated with the queue.
*        id -> ID of the I-PDU that has been transmitted.
*
* retval: None.
********************************************************************************
*/
FUNC(void, PDUR_CODE) PduR_Queue_LoTxConfirmation
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    PduIdType id
)
{
    (void) PduR_Queue_Write_Id(buffer, PDUR_EVENT_TXCONFIRMATION, id);
}

/*
********************************************************************************
* Function Name: PduR_Queue_LoRxIndication
*
* Explanation: Indication of a received I-PDU from a lower layer communication
*              interface module.
* (Synchronous)
*
* param: buffer -> Pointer to the buffer associated with the queue.
*        id -> ID of the received I-PDU.
*        info -> Contains the length (SduLength) of the received I-PDU and
*                      a pointer to a buffer (SduDataPtr) containing the I-PDU.
*
* retval: None.
********************************************************************************
*/
FUNC(void, PDUR_CODE) PduR_Queue_LoRxIndication
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
)
{
    (void) PduR_Queue_Write_Pdu(buffer, PDUR_EVENT_RXINDICATION, id, info);
}

/*
********************************************************************************
* Function Name: PduR_Queue_LoTpRxIndication
*
* Explanation: Called after an I-PDU has been received via the TP API, the result
*              indicates whether the transmission was successful or not.
* (Synchronous)
*
* param: buffer -> Pointer to the buffer associated with the queue.
*        id -> Identification of the received I-PDU.
*        result -> Result of the reception.
*
* retval: None.
********************************************************************************
*/
FUNC(void, PDUR_CODE) PduR_Queue_LoTpRxIndication
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    PduIdType id,
    Std_ReturnType result
)
{
    (void) PduR_Queue_Write_Result(buffer, PDUR_EVENT_TP_RXINDICATION, id, result);
}

/*
********************************************************************************
* Function Name: PduR_Queue_LoTpTxConfirmation
*
* Explanation: This function is called after the I-PDU has been transmitted on
*              its network, the result indicates whether the transmission was
*              successful or not.
* (Synchronous)
*
* param: buffer -> Pointer to the buffer associated with the queue.
*        id -> Identification of the transmitted I-PDU.
*        result -> Result of the transmission of the I-PDU.
*
* retval: None.
********************************************************************************
*/
FUNC(void, PDUR_CODE) PduR_Queue_LoTpTxConfirmation
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    PduIdType id,
    Std_ReturnType result
)
{
    (void) PduR_Queue_Write_Result(buffer, PDUR_EVENT_TP_TXCONFIRMATION, id, result);
}

/*
********************************************************************************
* Function Name: PduR_Queue_LoTpCopyRxData
*
* Explanation: This function is called to provide the received data of an I-PDU
*              segment (N-PDU) to the upper layer.
* (Synchronous)
*
* param: buffer -> Pointer to the buffer associated with the queue.
*        id -> Identification of the received I-PDU.
*        info -> Provides the source buffer (SduDataPtr) and the number of
*                   bytes to be copied (SduLength)
*        bufferSizePtr(out) -> Available receive buffer after data has been copied.
*
* retval: BUFREQ_OK: Data copied successfully
*         BUFREQ_E_NOT_OK: Data was not copied because an err occurred.
*         BUFREQ_E_OVFL: No buffer of the required length can be provided.
********************************************************************************
*/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Queue_LoTpCopyRxData
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr
)
{
    BufReq_ReturnType retVal = BUFREQ_OK;

    if( PDUR_QUEUE_LEN_0 != info->SduLength )
    {
        /* Write Pdu to the queue */
        retVal = PduR_Queue_Write_Pdu(buffer, PDUR_EVENT_TP_COPYRXDATA, id, info);
    }

    if( NULL_PTR != bufferSizePtr )
    {
        /* Available receive buffer after data has been copied */
        *bufferSizePtr = PduR_Buffer_GetSpace(buffer);
    }

    return retVal;
}

/*
********************************************************************************
* Function Name: PduR_Queue_LoTpStartOfReception
*
* Explanation: This function is called at the start of receiving an N-SDU.
* (Synchronous)
*
* param: buffer -> Pointer to the buffer associated with the queue.
*        id -> Identification of the I-PDU.
*        info -> Pointer to a PduInfoType structure containing the
*                   payload data (without protocol information) and
*                   payload length of the first frame or single frame
*                   of a transport protocol I-PDU reception.
*                   If neither first/single frame data nor MetaData
*                   are available, this parameter is set to NULL_PTR.
*        TpSduLength -> Total length of the N-SDU to be received.
*
* retval: BUFREQ_OK: The connection is accepted by PduR. reception is continued.
*         BUFREQ_E_NOT_OK: Data was not copied because an err occurred.
*         BUFREQ_E_OVFL: No buffer of the required length can be provided.
********************************************************************************
*/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Queue_LoTpStartOfReception
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
    PduLengthType TpSduLength
)
{
    return PduR_Queue_Write_Pdu_Length(buffer, PDUR_EVENT_TP_STARTOFRECEPTION, id, info, TpSduLength);
}

/*
********************************************************************************
* Function Name: PduR_Queue_LoTpStartOfReceptionCheck
*
* Explanation: This function is called at the start of receiving an N-SDU for
*              checking the destination.
*
* param: buffer -> Pointer to the buffer associated with the queue.
*        dstPduPtr ->Pointer to the dest pdu.
*        id -> Identification of the I-PDU.
*        info -> Pointer to a PduInfoType structure containing the
*                   payload data (without protocol information) and
*                   payload length of the first frame or single frame
*                   of a transport protocol I-PDU reception.
*                   If neither first/single frame data nor MetaData
*                   are available, this parameter is set to NULL_PTR.
*        TpSduLength -> Total length of the N-SDU to be received.
*
* retval: BUFREQ_OK: The connection is accepted by PduR. reception is continued.
*         BUFREQ_E_NOT_OK: Data was not copied because an err occurred.
*         BUFREQ_E_OVFL: No buffer of the required length can be provided.
********************************************************************************
*/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Queue_LoTpStartOfReceptionCheck
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer,
    P2CONST(PduRDestPdu_Type, AUTOMATIC, PDUR_APPL_CONST) dstPduPtr,
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
    PduLengthType TpSduLength
)
{
    BufReq_ReturnType retVal = BUFREQ_OK;

    PDUR_DUMMY_STATEMENT(id);
    if( E_OK == GetSpinlock(buffer->spinlockId) )
    {
#ifdef PDUR_MODULE_ID_DCM_UP
        if( PDUR_MODULE_ID_DCM_UP == PDUR_MODULE(dstPduPtr) )
        {
            retVal = Dcm_StartOfReceptionCheck(dstPduPtr->PduRDestPduHandleId, info, TpSduLength, NULL_PTR);
        }
#endif
        ReleaseSpinlock(buffer->spinlockId);
    }
    else
    {
        retVal = BUFREQ_E_NOT_OK;
    }
    return retVal;
}

/*
********************************************************************************
* Function Name: PduR_Queue_Process
*
* Explanation: Fetch the request from the queue and process it, this function is
*              called periodically in the MainFunction.
* (Synchronous)
*
* param: buffer -> Pointer to the buffer associated with the queue.
*
* retval: None.
********************************************************************************
*/
FUNC(void, PDUR_CODE) PduR_Queue_Process
(
    P2CONST(PduR_BufferType, AUTOMATIC, PDUR_APPL_CONST) buffer
)
{
    PduIdType id;
    PduInfoType info;
    PduInfoType* pduInfoPtr = NULL_PTR;
    PduLengthType sduLength;
    PduLengthType buffer_size;
    Std_ReturnType result;
    uint8 eventCode;

    info.SduDataPtr = NULL_PTR;
    info.SduLength = PDUR_INIT_0;

    /* Check if there is request in the queue */
    while( PDUR_TRUE != PduR_Buffer_Empty(buffer) )
    {
        if( E_OK == GetSpinlock(buffer->spinlockId) )
        {
            PduR_CacheType cache;

            /* Get available data from the queue */
            cache.dataPtr = PduR_Buffer_Get(buffer);
            cache.pos = 0;

            PduR_Cache_ReadData(&cache, &eventCode, sizeof(eventCode));

            switch( eventCode & PDUR_EVENT_MASK )
            {
            case PDUR_EVENT_CANCEL_RECEIVE:
                /* Get ID of the PDU to be cancelled */
                PduR_Cache_ReadData(&cache, &id, sizeof(id));

                /*
                SWS_PduR_00848
                For inter-partition routing paths, the call to the function PduR_-
                <User:UpTp>CancelReceive shall only execute code that is assigned to
                the same ECUC partition
                */
                (void) PduR_UpCancelReceive(id);
                break;

            case PDUR_EVENT_CANCEL_TRANSMIT:
                /* Get ID of the PDU to be cancelled */
                PduR_Cache_ReadData(&cache, &id, sizeof(id));

                /*
                SWS_PduR_00846
                For inter-partition routing paths, the call to the function PduR_-
                <User:Up/UpTp>CancelTransmit shall only execute code that is assigned
                to the same ECUC partition
                */
                (void) PduR_UpCancelTransmit(id);
                break;

            case PDUR_EVENT_TRANSMIT:
                /* Get ID of the PDU to be transmitted */
                PduR_Cache_ReadData(&cache, &id, sizeof(id));
                /* Get the PDU to be transmitted */
                PduR_Cache_ReadPdu(&cache, &info, PduR_EventSduExist(eventCode));

                /*
                SWS_PduR_00844
                For inter-partition routing paths, the call to the function PduR_-
                <User:Up>Transmit shall only execute code that is assigned to the
                same ECUC partition
                */
                (void) PduR_UpTransmit(id, &info);
                break;

            case PDUR_EVENT_TXCONFIRMATION:
                /* Get ID of the PDU that has been transmitted */
                PduR_Cache_ReadData(&cache, &id, sizeof(id));

                /*
                SWS_PduR_00850
                For inter-partition routing paths, the call to the function PduR_-
                <User:Lo>TxConfirmation shall only execute code that is assigned to the
                same ECUC partition
                */
                PduR_LoTxConfirmation(id);
                break;

            case PDUR_EVENT_RXINDICATION:
                /* Get ID of the received PDU */
                PduR_Cache_ReadData(&cache, &id, sizeof(id));
                /* Get the received PDU */
                PduR_Cache_ReadPdu(&cache, &info, PduR_EventSduExist(eventCode));

                /*
                SWS_PduR_00849
                For inter-partition routing paths, the call to the function PduR_-
                <User:Lo>RxIndication shall only execute code that is assigned to the
                same ECUC partition
                */
                PduR_LoRxIndication(id, &info);
                break;

            case PDUR_EVENT_TP_RXINDICATION:
                /* Get ID of the received PDU */
                PduR_Cache_ReadData(&cache, &id, sizeof(id));
                /* Get result of the reception */
                PduR_Cache_ReadData(&cache, &result, sizeof(result));

                /*
                SWS_PduR_00853
                For inter-partition routing paths, the call to the function PduR_-
                <User:LoTp>RxIndication shall only execute code that is assigned to the
                same ECUC partition
                */
                if( (PduR_RoutingPathFlagTable[PDUR_ROUTING_FLAG_INDEX(id)] & PDUR_ROUTING_FLAG_MASK(id))
                     == PDUR_ROUTING_FLAG_MASK(id) )
                {
                    PduR_RoutingPathFlagTable[PDUR_ROUTING_FLAG_INDEX(id)] &= ~PDUR_ROUTING_FLAG_MASK(id);
                    PduR_LoTpRxIndication(id, result);
                }
                break;

            case PDUR_EVENT_TP_TXCONFIRMATION:
                /* Get ID of the transmitted PDU */
                PduR_Cache_ReadData(&cache, &id, sizeof(id));
                /* Get result of the transmission of the PDU */
                PduR_Cache_ReadData(&cache, &result, sizeof(result));

                /*
                SWS_PduR_00858
                For inter-partition routing paths, the call to the function PduR_-
                <User:LoTp>TxConfirmation shall only execute code that is assigned to the
                same ECUC partition
                */
                PduR_LoTpTxConfirmation(id, result);
                break;

            case PDUR_EVENT_TP_COPYRXDATA:
                /* Get ID of the received PDU */
                PduR_Cache_ReadData(&cache, &id, sizeof(id));
                /* Get the received PDU */
                PduR_Cache_ReadPdu(&cache, &info, PduR_EventSduExist(eventCode));

                /*
                SWS_PduR_00851
                For inter-partition routing paths, the call to the function PduR_-
                <User:LoTp>CopyRxData shall only execute code that is assigned to the
                same ECUC partition
                */
                if( (PduR_RoutingPathFlagTable[PDUR_ROUTING_FLAG_INDEX(id)] & PDUR_ROUTING_FLAG_MASK(id))
                     == PDUR_ROUTING_FLAG_MASK(id) )
                {
                    if( BUFREQ_OK != PduR_LoTpCopyRxData(id, &info, &buffer_size) )
                    {
                        PduR_RoutingPathFlagTable[PDUR_ROUTING_FLAG_INDEX(id)] &= ~PDUR_ROUTING_FLAG_MASK(id);
                    }
                }
                break;

            case PDUR_EVENT_TP_STARTOFRECEPTION:
                /* Get ID of the PDU */
                PduR_Cache_ReadData(&cache, &id, sizeof(id));
                /* Get total length of the N-SDU to be received */
                PduR_Cache_ReadData(&cache, &sduLength, sizeof(sduLength));
                /* Get the received PDU */
                PduR_Cache_ReadPdu(&cache, &info, PduR_EventSduExist(eventCode));

                /*
                SWS_PduR_00854
                For inter-partition routing paths, the call to the function PduR_-
                <User:LoTp>StartOfReception shall only execute code that is assigned to
                the same ECUC partition
                */
                if( (PDUR_INIT_0 != info.SduLength) || (NULL_PTR != info.SduDataPtr) )
                {
                    pduInfoPtr = &info;
                }

                if( BUFREQ_OK == PduR_LoTpStartOfReception(id, pduInfoPtr, sduLength, &buffer_size) )
                {
                    PduR_RoutingPathFlagTable[PDUR_ROUTING_FLAG_INDEX(id)] |= PDUR_ROUTING_FLAG_MASK(id);
                }
                else
                {
                    PduR_RoutingPathFlagTable[PDUR_ROUTING_FLAG_INDEX(id)] &= ~PDUR_ROUTING_FLAG_MASK(id);
                }
                break;

            default:
                break;
            }

            /* Release the buffer after used */
            PduR_Buffer_Free(buffer, cache.pos);
            ReleaseSpinlock(buffer->spinlockId);
        }
    }
}


#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif /* #if (STD_OFF == PDUR_ZERO_COST_OPERATION) */
