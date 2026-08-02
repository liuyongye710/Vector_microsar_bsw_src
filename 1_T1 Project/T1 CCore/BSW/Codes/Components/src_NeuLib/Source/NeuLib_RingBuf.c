/*
********************************************************************************
*
* File name: NeuLib_RingBuf.c
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
* Author/Date: ChenQJ/2023.08.25
* Change: Modify ptrclass definition of NeuLibRb_OutPtrForOffset().
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: TianG/2024.10.12
* Change: 1.Add a memory-map label to function.
*         2.Modify copyright.
*         3.Modify FUNC_P2VAR error.
* Cause: Bugfix
********************************************************************************
*/
#include "NeuLib_RingBuf.h"
#include "NeuLib_Def.h"
#include "NeuLib.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/* Ring buffer action flag. */
typedef enum
{
    NEULIB_RB_POLL, /*!< Push the data but do not change the pointer.       */
    NEULIB_RB_POP,  /*!< The pointer is modified as the data is pushed out. */
    NEULIB_RB_DROP  /*!< Does not push the data but modifies the pointer.   */
} NeuLibRbAction_Type;

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
#define NEULIB_START_SEC_CODE
#include "NeuLib_MemMap.h"
static FUNC(NeuLibRbSize_Type, NEULIB_CODE) NeuLibRb_Action(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb,
    P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) data,
    NeuLibRbSize_Type len,
    NeuLibRbAction_Type action
);
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
/*
********************************************************************************
* Function Name: NeuLibRb_Action
*
* Explanation:   The ring buffer performs the specified action.
* (Synchronous)
*
* param:         rb     The ring buffer object.
*                data   A pointer to data.
*                len    Data length.
*                action Ring buffer action flag.
*
* retval:        The length of the operation buffer.
********************************************************************************
*/
static FUNC(NeuLibRbSize_Type, NEULIB_CODE) NeuLibRb_Action(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb,
    P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) data,
    NeuLibRbSize_Type len,
    NeuLibRbAction_Type action
)
{
    NeuLibRbSize_Type ret = 0u;
    NeuLibRbSize_Type doSz;
    NeuLibRbSize_Type in, out;
    NeuLibRbSize_Type min, max;
    char *buffer;

    buffer = rb->buffer;
    in = rb->variant->in;
    out = rb->variant->out;
    min = rb->min;
    max = rb->max;

    NEULIB_ASSERT("NeuLib_RingBuf", (len % min) == NEULIB_SIZE_0);

    if (out == in)
    {
        /* already empty */
        return ret;
    }

    out++;
    if (out >= max)
    {
        out = NEULIB_SIZE_0;
    }

    if (out <= in)
    {
        ret = in - out + NEULIB_SHIFT_1;
        if (ret > len)
        {
            ret = len;
        }
        if (action != NEULIB_RB_DROP)
        {
            NeuLib_memcpy(data, &buffer[out], ret);
        }
        out += ret - NEULIB_SHIFT_1;

        if (action != NEULIB_RB_POLL)
        {
            rb->variant->out = out;
        }
    }
    else
    {
        doSz = max - out;
        if (doSz > len)
        {
            doSz = len;
        }
        if (action != NEULIB_RB_DROP)
        {
            NeuLib_memcpy(data, &buffer[out], doSz);
        }
        out += doSz;
        ret += doSz;
        len = len - doSz;

        if (out >= max)
        {
            out = NEULIB_INIT_0;
        }

        if (len > NEULIB_SIZE_0)
        {
            doSz = in - out + NEULIB_SHIFT_1;
            if (doSz > len)
            {
                doSz = len;
            }
            if (action != NEULIB_RB_DROP)
            {
                NeuLib_memcpy(&((uint8 *)data)[ret], &buffer[out], doSz);
            }
            out += doSz;
            ret += doSz;
        }

        if (action != NEULIB_RB_POLL)
        {
            if (NEULIB_SIZE_0 == out)
            {
                rb->variant->out = max - NEULIB_SHIFT_1;
            }
            else
            {
                rb->variant->out = out - NEULIB_SHIFT_1;
            }
        }
    }
    NEULIB_DUMMY_STATEMENT(min);
    return ret;
}

/*
********************************************************************************
* Function Name: NeuLibRb_Init
*
* Explanation:   Init ring buffer.
* (Synchronous)
*
* param:         rb The ring buffer object.
*
* retval:        None
********************************************************************************
*/
FUNC(void, NEULIB_CODE) NeuLibRb_Init(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb
)
{
    rb->variant->in = rb->max - NEULIB_SHIFT_1;
    rb->variant->out = rb->max - NEULIB_SHIFT_1;
}

/*
********************************************************************************
* Function Name: NeuLibRb_Push
*
* Explanation:   Push data into the circular queue.
* (Synchronous)
*
* param:         rb   The ring buffer object.
*                data The data to push.
*                len  The length of the data to push.
*
* retval:        The actual pushed length.
********************************************************************************
*/
FUNC(NeuLibRbSize_Type, NEULIB_CODE) NeuLibRb_Push(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb,
    P2CONST(void, AUTOMATIC, NEULIB_APPL_DATA) data,
    NeuLibRbSize_Type len
)
{
    NeuLibRbSize_Type ret;
    NeuLibRbSize_Type doSz;
    NeuLibRbSize_Type in;
    NeuLibRbSize_Type out;
    NeuLibRbSize_Type min;
    NeuLibRbSize_Type max;
    uint8 *buffer;

    buffer = (uint8 *)rb->buffer;
    in = rb->variant->in;
    out = rb->variant->out;
    min = rb->min;
    max = rb->max;

    NEULIB_ASSERT("NeuLib_RingBuf", (len % min) == NEULIB_SIZE_0);

    in++;
    if (in >= max)
    {
        in = NEULIB_SIZE_0;
    }

    ret = NEULIB_SIZE_0;
    if ((in + min - NEULIB_SHIFT_1) == out)
    {
        /* full, do nothing */
    }
    else if (in <= out)
    {
        ret = out - in + NEULIB_SHIFT_1;
        if (ret > len)
        {
            ret = len;
        }
        else
        {
            ret = ret - min;
        }

        if (data != NULL_PTR)
        {
            NeuLib_memcpy(&buffer[in], data, ret);
        }
        in += ret - NEULIB_SHIFT_1;

        rb->variant->in = in;
    }
    else /* in > out */
    {
        doSz = max - in;
        if (doSz > len)
        {
            doSz = len;
        }
        if (data != NULL_PTR)
        {
            NeuLib_memcpy(&buffer[in], data, doSz);
        }

        in += doSz;
        ret += doSz;
        len = len - doSz;

        if (in >= max)
        {
            in = NEULIB_SIZE_0;
        }

        if (len > NEULIB_SIZE_0)
        {
            doSz = out - in + NEULIB_SHIFT_1;
            if (doSz > len)
            {
                doSz = len;
            }
            else
            {
                doSz = doSz - min;
            }
            if (data != NULL_PTR)
            {
                NeuLib_memcpy(&buffer[in], &((char *)data)[ret], doSz);
            }
            in += doSz;
            ret += doSz;
        }

        if (NEULIB_SIZE_0 == in)
        {
            rb->variant->in = max - NEULIB_SHIFT_1;
        }
        else
        {
            rb->variant->in = in - NEULIB_SHIFT_1;
        }
    }

    return ret;
}

/*
********************************************************************************
* Function Name: NeuLibRb_Pop
*
* Explanation:   Cast data and move the pointer to the circular queue.
* (Synchronous)
*
* param:         rb   The ring buffer object.
*                data The data to push.
*                len  The length of the data to push.
*
* retval:        The actual pushed length.
********************************************************************************
*/
FUNC(NeuLibRbSize_Type, NEULIB_CODE) NeuLibRb_Pop(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb,
    P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) data,
    NeuLibRbSize_Type len
)
{
    return NeuLibRb_Action(rb, data, len, NEULIB_RB_POP);
}

/*
********************************************************************************
* Function Name: NeuLibRb_Poll
*
* Explanation:   Casts data but does not move the pointer to the circular queue.
* (Synchronous)
*
* param:         rb   The ring buffer object.
*                data The data to push.
*                len  The length of the data to push.
*
* retval:        The actual pushed length.
********************************************************************************
*/
FUNC(NeuLibRbSize_Type, NEULIB_CODE) NeuLibRb_Poll(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb,
    P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) data,
    NeuLibRbSize_Type len
)
{
    return NeuLibRb_Action(rb, data, len, NEULIB_RB_POLL);
}

/*
********************************************************************************
* Function Name: NeuLibRb_Drop
*
* Explanation:   Move the pointer of the circular queue.
* (Synchronous)
*
* param:         rb   The ring buffer object.
*                len  The length of the data to push.
*
* retval:        The actual pushed length.
********************************************************************************
*/
FUNC(NeuLibRbSize_Type, NEULIB_CODE) NeuLibRb_Drop(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb,
    NeuLibRbSize_Type len
)
{
    return NeuLibRb_Action(rb, NULL_PTR, len, NEULIB_RB_DROP);
}

/*
********************************************************************************
* Function Name: NeuLibRb_PopRow
*
* Explanation:   Pulls contiguous data in the ring buffer.
* (Synchronous)
*
* param:         rb  The ring buffer object.
*                len The length of the data to push.
*
* retval:        The actual pushed length.
********************************************************************************
*/
FUNC(NeuLibRbSize_Type, NEULIB_CODE) NeuLibRb_PopRow(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb,
    NeuLibRbSize_Type len
)
{
    NeuLibRbSize_Type ret;
    NeuLibRbSize_Type doSz;
    NeuLibRbSize_Type in, out;
    NeuLibRbSize_Type min, max;

    in = rb->variant->in;
    out = rb->variant->out;
    min = rb->min;
    max = rb->max;

    NEULIB_ASSERT("NeuLib_RingBuf", (len % min) == NEULIB_SIZE_0);

    if (out == in)
    {
        /* already empty */
        return NEULIB_SIZE_0;
    }

    out++;
    if (out >= max)
    {
        out = NEULIB_SIZE_0;
    }

    ret = NEULIB_SIZE_0;
    if (out <= in)
    {
        ret = in - out + NEULIB_SHIFT_1;
        if (ret > len)
        {
            ret = len;
        }
        out += ret - NEULIB_SHIFT_1;
        rb->variant->out = out;
    }
    else
    {
        doSz = max - out;
        if (doSz > len)
        {
            doSz = len;
        }
        out += doSz;
        ret += doSz;

        if (out >= max)
        {
            out = NEULIB_SIZE_0;
        }

        if (NEULIB_SIZE_0 == out)
        {
            rb->variant->out = max - NEULIB_SHIFT_1;
        }
        else
        {
            rb->variant->out = out - NEULIB_SHIFT_1;
        }
    }
    NEULIB_DUMMY_STATEMENT(min);
    return ret;
}

/*
********************************************************************************
* Function Name: NeuLibRb_Row
*
* Explanation:   Retrieves the length of continuous data in the ring buffer without moving the pointer.
* (Synchronous)
*
* param:         rb     Ring buffer object.
*                len    The length of the data to pop.
*
* retval:        The actual poped length.
********************************************************************************
*/
FUNC(NeuLibRbSize_Type, NEULIB_CODE) NeuLibRb_Row(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb,
    NeuLibRbSize_Type len
)
{
    NeuLibRbSize_Type ret = 0U;
    NeuLibRbSize_Type doSz;
    NeuLibRbSize_Type in = rb->variant->in;
    NeuLibRbSize_Type out = rb->variant->out;
#if NEU_DEBUG
    NeuLibRbSize_Type min = rb->min;
#endif  /* NEU_DEBUG */
    NeuLibRbSize_Type max = rb->max;

    NEULIB_ASSERT("The input length does not meet the defined minimum length requirement.", (len % min) == 0U);

    if (out == in)
    {
        /* already empty */
        return 0U;
    }

    out++;
    if (out >= max)
    {
        out = 0U;
    }

    if (out <= in)
    {
        ret = in - out + NEULIB_SHIFT_1;
        if (ret > len)
        {
            ret = len;
        }
    }
    else
    {
        doSz = max - out;
        if (doSz > len)
        {
            doSz = len;
        }
        ret += doSz;
    }

    return ret;
}

/*
********************************************************************************
* Function Name: NeuLibRb_OutP
*
* Explanation:   Get the address of the tail buffer of the ring queue.
* (Synchronous)
*
* param:         rb The ring buffer object.
*
* retval:        Pointer to the address of the buffer.
********************************************************************************
*/
FUNC_P2VAR(void, NEULIB_APPL_DATA, NEULIB_CODE) NeuLibRb_OutP(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb
)
{
    uint8 *buffer;
    NeuLibRbSize_Type in;
    NeuLibRbSize_Type out;
    NeuLibRbSize_Type max;

    buffer = rb->buffer;
    in = rb->variant->in;
    out = rb->variant->out;
    max = rb->max;

    if (out == in)
    {
        buffer = NULL_PTR;
    }
    else
    {
        out++;
        if (out >= max)
        {
            out = NEULIB_SIZE_0;
        }

        buffer = &buffer[out];
    }

    return buffer;
}

/*
********************************************************************************
* Function Name: NeuLibRb_OutPtrForOffset
*
* Explanation:   Gets the address of the specified ring queue tail buffer based on the offset.
* (Synchronous)
*
* param:         rb     Ring buffer object.
*                offset The offset specified.
*
* retval:        Pointer to the address of the buffer.
********************************************************************************
*/
FUNC_P2VAR(void, NEULIB_APPL_DATA, NEULIB_CODE) NeuLibRb_OutPtrForOffset(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb,
    uint16 offset
)
{
    NeuLibRbSize_Type leftLen;
    NeuLibRbSize_Type in = rb->variant->in;
    NeuLibRbSize_Type out = rb->variant->out;
#if NEU_DEBUG
    NeuLibRbSize_Type min = rb->min;
#endif  /* NEU_DEBUG */
    NeuLibRbSize_Type max = rb->max;
    void *ret;

    NEULIB_ASSERT("The input length does not meet the defined minimum length requirement.", (offset % min) == 0U);

    if (out == in)
    {
        /* Already empty */
        return NULL_PTR;
    }

    /* Check the tail pointer position. */
    out++;
    if (out >= max)
    {
        out = 0U;
    }

    /* Init. */
    leftLen = 0U;

    if (out <= in)
    {
        /* When the tail pointer is not larger than the head pointer. */
        leftLen = in - out + NEULIB_SHIFT_1;
        if (leftLen > offset)
        {
            leftLen = offset;
        }

        /* Sets the tail pointer. */
        out += leftLen - NEULIB_SHIFT_1;

        /* Gets a pointer to the specified buffer tail queue. */
        ret = &(((uint8 *)rb->buffer)[out]);
    }
    /* A ring queue rollover occurred. */
    else
    {
        NeuLibRbSize_Type doSz = max - out;

        /* Gets the maximum data length you can use. */
        if (doSz > offset)
        {
            doSz = offset;
        }

        out += doSz;
        offset = offset - doSz;

        if (out >= max)
        {
            out = 0U;
        }

        if (offset > 0U)
        {
            /* Retrieves the available queue length. */
            doSz = in - out + NEULIB_SHIFT_1;
            if (doSz > offset)
            {
                doSz = offset;
            }

            out += doSz;
        }

        if (0U == out)
        {
            /* Gets a pointer to the specified buffer tail queue. */
            ret = &(((uint8 *)rb->buffer)[max - NEULIB_SHIFT_1]);
        }
        else
        {
            /* Gets a pointer to the specified buffer tail queue. */
            ret = &(((uint8 *)rb->buffer)[out - NEULIB_SHIFT_1]);
        }
    }

    return ret;
}

/*
********************************************************************************
* Function Name: NeuLibRb_InP
*
* Explanation:   Get the start buffer address of the ring queue.
* (Synchronous)
*
* param:         rb The ring buffer object.
*
* retval:        Pointer to the address of the buffer.
********************************************************************************
*/
FUNC_P2VAR(void, NEULIB_APPL_DATA, NEULIB_CODE) NeuLibRb_InP(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb
)
{
    uint8 *buffer;
    NeuLibRbSize_Type in;
    NeuLibRbSize_Type out;
    NeuLibRbSize_Type min;
    NeuLibRbSize_Type max;

    buffer = rb->buffer;
    in = rb->variant->in;
    out = rb->variant->out;
    min = rb->min;
    max = rb->max;

    in++;
    if (in >= max)
    {
        in = NEULIB_SIZE_0;
    }

    if ((in + min - NEULIB_SHIFT_1) == out)
    {
        buffer = NULL_PTR;
    }
    else
    {
        buffer = &buffer[in];
    }

    return buffer;
}

/*
********************************************************************************
* Function Name: NeuLibRb_Left
*
* Explanation:   Get the remaining buffer length of the ring queue.
* (Synchronous)
*
* param:         rb The ring buffer object.
*
* retval:        Free length.
********************************************************************************
*/
FUNC(NeuLibRbSize_Type, NEULIB_CODE) NeuLibRb_Left(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb
)
{
    NeuLibRbSize_Type left;

    if (rb->variant->in < rb->variant->out)
    {
        left = rb->variant->out - rb->variant->in - rb->min;
    }
    else
    {
        left = rb->max - rb->variant->in + rb->variant->out - rb->min;
    }

    return left;
}

/*
********************************************************************************
* Function Name: NeuLibRb_Size
*
* Explanation:   Get the ring buffer size.
* (Synchronous)
*
* param:         rb The ring buffer object.
*
* retval:        size
********************************************************************************
*/
FUNC(NeuLibRbSize_Type, NEULIB_CODE) NeuLibRb_Size(
    P2CONST(NeuLibRingBuffer_Type, AUTOMATIC, NEULIB_APPL_CONST) rb
)
{
    NeuLibRbSize_Type size;

    if (rb->variant->in < rb->variant->out)
    {
        size = rb->max - rb->variant->out + rb->variant->in;
    }
    else
    {
        size = rb->variant->in - rb->variant->out;
    }

    return size;
}

#define NEULIB_STOP_SEC_CODE
#include "NeuLib_MemMap.h"
