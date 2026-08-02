/*
********************************************************************************
*
* File name: NeuLib.c
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
* Author/Date: KangJH/204.08.07
* Change: Add NeuLib_memcpy32 function.
* Cause: Update
********************************************************************************
* Version: 3.2
* Author/Date: KangJH/204.09.03
* Change: Remove the unused local variable "remSize" from the
*         "NeuLib_memcpy32" function.
* Cause: Update
********************************************************************************
* Version: 3.3
* Author/Date: TianG/2024.10.12
* Change: 1.Add a memory-map label to function.
*         2.Modify copyright.
*         3.Modify FUNC_P2VAR error.
* Cause: Bugfix
********************************************************************************
*/
#include "NeuLib.h"
#include "NeuLib_Def.h"

#if (NEULIB_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif  /* (NEULIB_DEV_ERROR_DETECT == STD_ON) */

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
#if (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON)
#define MEM_24_BIT_DISPLACEMENT             3
#define MEM_16_BIT_DISPLACEMENT             2
#define NEULIB_MEMCOPY_16_BYTE              16U
#define NEULIB_MEMCOPY_32_BYTE              32U

/* Used to mask internal parameters to ensure an upper limit of 3, respectively 31. */
#define NEULIB_MEMCOPY_MASK_3               0x03U
#define NEULIB_MEMCOPY_MASK_31              0x1FU

/* Return the number of bytes that are missing to the next 32-bit boundary */
#define MEM_ALIGN_OFFSET(ptr)               (uint8_least)((4U - (uint32_least)(ptr)) & NEULIB_MEMCOPY_MASK_3)

#endif  /* (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON) */

#ifndef __has_cpp_attribute
#define __has_cpp_attribute(x)  0U
#endif  /* __has_cpp_attribute */

#ifndef __has_c_attribute
#define __has_c_attribute(x)    0U
#endif  /* __has_c_attribute */

#ifndef __has_attribute
#define __has_attribute(x)      0U
#endif  /* __has_attribute */

#if __has_cpp_attribute(fallthrough) || __has_c_attribute(fallthrough)
    #define FALLTHROUGH [[fallthrough]]
#elif __has_attribute(fallthrough)
    #define FALLTHROUGH __attribute__((fallthrough))
/* Note, there could be more branches here, like using `[[gsl::suppress]]` for MSVC */
#else
    #define FALLTHROUGH
#endif  /* __has_cpp_attribute(fallthrough) || __has_c_attribute(fallthrough) */

#define UNALIGNED(X, Y)     (((uint32)X & (sizeof(uint32) - NEULIB_SHIFT_1)) | ((uint32)Y & (sizeof(uint32) - NEULIB_SHIFT_1)))
#define BIGBLOCKSIZE        (sizeof(uint32) << NEULIB_SHIFT_2)
#define LITTLEBLOCKSIZE     (sizeof(uint32))
#define TOO_SMALL(LEN)      ((LEN) < BIGBLOCKSIZE)

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
#if (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON)
LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemCopy_8_3(
    P2VAR(uint8, AUTOMATIC, NEULIB_APPL_DATA) pDst8,
    P2CONST(uint8, AUTOMATIC, NEULIB_APPL_CONST) pSrc8,
    uint8_least cnt
);

LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemCopy_8_31(
    P2VAR(uint8, AUTOMATIC, NEULIB_APPL_DATA) pDst8,
    P2CONST(uint8, AUTOMATIC, NEULIB_APPL_CONST) pSrc8,
    uint8_least cnt
);

LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemCopy_8_PartialWord(
    P2VAR(uint8, AUTOMATIC, NEULIB_APPL_DATA) pDst8,
    uint8_least cnt,
    P2VAR(uint32, AUTOMATIC, NEULIB_APPL_DATA) pPrev,
    P2VAR(uint32_least, AUTOMATIC, NEULIB_APPL_DATA) pDPos
);

LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemCopy_32_Aligned(
    P2VAR(uint32, AUTOMATIC, NEULIB_APPL_DATA) pDst32,
    P2CONST(uint32, AUTOMATIC, NEULIB_APPL_CONST) pSrc32,
    uint32_least cnt
);

LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemCopy_32_Unaligned(
    P2VAR(uint8, AUTOMATIC, NEULIB_APPL_DATA) pDst8,
    P2CONST(uint32, AUTOMATIC, NEULIB_APPL_CONST) pSrc32,
    uint32_least cnt,
    uint8_least dstOffset
);

LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemSet_8_3(
    P2VAR(uint8, AUTOMATIC, NEULIB_APPL_DATA) pDst8,
    uint8 value,
    uint8_least cnt
);

LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemSet_8_31(
    P2VAR(uint8, AUTOMATIC, NEULIB_APPL_DATA) pDst8,
    uint8 value,
    uint8_least cnt
);

LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemSet_32_Aligned(
    P2VAR(uint32, AUTOMATIC, NEULIB_APPL_DATA) pDst32,
    uint8 value,
    uint32_least cnt
);
#endif  /* (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON) */
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

#if (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON)
/*
********************************************************************************
* Function Name: NeuLib_MemCopy_8_3
*
* Explanation:   Copies up to 3 bytes from pSrc8 to pDst8 (any alignment).
* (Synchronous)
*
* param:         pDst8 DstPtr data pointer.
*                pSrc8 Source data.
*                cnt   Copy total length.
*
* retval:        None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemCopy_8_3(
    P2VAR(uint8, AUTOMATIC, NEULIB_APPL_DATA) pDst8,
    P2CONST(uint8, AUTOMATIC, NEULIB_APPL_CONST) pSrc8,
    uint8_least cnt
)
{
    /**
     * MISRA C:2012 16.1
     * All switch statements shall be well-formed.
     * Initialize up to 3 bytes using a jump table.
     */
    switch (cnt)
    {
    case NEULIB_CNT_3:                              /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_2] = pSrc8[NEULIB_IDX_2];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_2:                              /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_1] = pSrc8[NEULIB_IDX_1];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_1:                              /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_0] = pSrc8[NEULIB_IDX_0];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    default:
        /* Do nothing. */
        break;
    }
}

/*
********************************************************************************
* Function Name: NeuLib_MemCopy_8_31
*
* Explanation:   Copy up to 31 bytes from pSrc8 to pDst8 (any alignment).
* (Synchronous)
*
* param:         pDst8 DstPtr data pointer.
*                pSrc8 Source data.
*                cnt   Copy total length.
*
* retval:        None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemCopy_8_31(
    P2VAR(uint8, AUTOMATIC, NEULIB_APPL_DATA) pDst8,
    P2CONST(uint8, AUTOMATIC, NEULIB_APPL_CONST) pSrc8,
    uint8_least cnt
)
{
    /**
     * MISRA C:2012 16.1
     * All switch statements shall be well-formed.
     * Initialize up to 31 bytes using a jump table.
     */
    switch (cnt)
    {
    case NEULIB_CNT_31:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_30] = pSrc8[NEULIB_IDX_30];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_30:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_29] = pSrc8[NEULIB_IDX_29];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_29:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_28] = pSrc8[NEULIB_IDX_28];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_28:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_27] = pSrc8[NEULIB_IDX_27];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_27:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_26] = pSrc8[NEULIB_IDX_26];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_26:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_25] = pSrc8[NEULIB_IDX_25];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_25:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_24] = pSrc8[NEULIB_IDX_24];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_24:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_23] = pSrc8[NEULIB_IDX_23];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_23:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_22] = pSrc8[NEULIB_IDX_22];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_22:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_21] = pSrc8[NEULIB_IDX_21];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_21:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_20] = pSrc8[NEULIB_IDX_20];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_20:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_19] = pSrc8[NEULIB_IDX_19];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_19:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_18] = pSrc8[NEULIB_IDX_18];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_18:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_17] = pSrc8[NEULIB_IDX_17];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_17:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_16] = pSrc8[NEULIB_IDX_16];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_16:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_15] = pSrc8[NEULIB_IDX_15];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_15:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_14] = pSrc8[NEULIB_IDX_14];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_14:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_13] = pSrc8[NEULIB_IDX_13];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_13:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_12] = pSrc8[NEULIB_IDX_12];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_12:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_11] = pSrc8[NEULIB_IDX_11];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_11:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_10] = pSrc8[NEULIB_IDX_10];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_10:                                 /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_9] = pSrc8[NEULIB_IDX_9];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_9:                                  /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_8] = pSrc8[NEULIB_IDX_8];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_8:                                  /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_7] = pSrc8[NEULIB_IDX_7];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_7:                                  /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_6] = pSrc8[NEULIB_IDX_6];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_6:                                  /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_5] = pSrc8[NEULIB_IDX_5];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_5:                                  /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_4] = pSrc8[NEULIB_IDX_4];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_4:                                  /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_3] = pSrc8[NEULIB_IDX_3];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_3:                                  /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_2] = pSrc8[NEULIB_IDX_2];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_2:                                  /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_1] = pSrc8[NEULIB_IDX_1];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_1:                                  /*!< MISRA C:2012 16.3       */
        pDst8[NEULIB_IDX_0] = pSrc8[NEULIB_IDX_0];
        FALLTHROUGH;
        /*!< Intentionally no break. */
    default:
        /* Do nothing. */
        break;
    }
}

/*
********************************************************************************
* Function Name: NeuLib_MemCopy_8_PartialWord
*
* Explanation:   Copies a partial word of 1 to 3 bytes from srcPtr to pDst8 to
                 reach a 32-bit boundary (any alignment).
* (Synchronous)
*
* param:         pDst8 8-bit pointer to the memory location to copy to.
*                cnt   Number of bytes to copy, pDst8 must be valid for this amount.
*                pPrev Word to copy from (is modified and used by caller afterwards).
*                pDPos Index for pDst8 to copy to (is modified and used by caller afterwards).
*
* retval:        None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemCopy_8_PartialWord(
    P2VAR(uint8, AUTOMATIC, NEULIB_APPL_DATA) pDst8,
    uint8_least cnt,
    P2VAR(uint32, AUTOMATIC, NEULIB_APPL_DATA) pPrev,
    P2VAR(uint32_least, AUTOMATIC, NEULIB_APPL_DATA) pDPos
)
{
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    /**
     * Copy 1 to 3 bytes using a jump table and adapt '*pDPos' and '*pPrev' for little endian byte order.
     *
     * MISRA C:2012 16.1
     * All switch statements shall be well-formed.
     * Initialize up to 3 bytes using a jump table.
     */
    switch (cnt)
    {
    case NEULIB_CNT_3:                  /* MISRA C:2012 16.3 */
        pDst8[*pDPos] = (uint8)*pPrev;
        (*pDPos)++;
        (*pPrev) >>= NEULIB_SHIFT_8;
        FALLTHROUGH;
        /* Intentionally no break. */
    case NEULIB_CNT_2:                  /* MISRA C:2012 16.3 */
        pDst8[*pDPos] = (uint8)*pPrev;
        (*pDPos)++;
        (*pPrev) >>= NEULIB_SHIFT_8;
        FALLTHROUGH;
        /* Intentionally no break. */
    /* Case 1 - cnt is always in range [1..3] */
    default:
        pDst8[*pDPos] = (uint8)*pPrev;
        (*pDPos)++;
        (*pPrev) >>= NEULIB_SHIFT_8;
        break;
    }

#else   /* CPU_BYTE_ORDER == HIGH_BYTE_FIRST */

    /**
     * Copy 1 to 3 bytes using a jump table and adapt '*pDPos' and '*pPrev' for big endian byte order.
     *
     * MISRA C:2012 16.1
     * All switch statements shall be well-formed.
     * Initialize up to 3 bytes using a jump table.
     */
    switch (cnt)
    {
    case NEULIB_CNT_3:              /* MISRA C:2012 16.3 */
        pDst8[*pDPos] = (uint8)(*pPrev >> NEULIB_SHIFT_24);
        (*pDPos)++;
        *pPrev <<= NEULIB_SHIFT_8;
        /* Intentionally no break. */
    case NEULIB_CNT_2:              /* MISRA C:2012 16.3 */
        pDst8[*pDPos] = (uint8)(*pPrev >> NEULIB_SHIFT_24);
        (*pDPos)++;
        *pPrev <<= NEULIB_SHIFT_8;
        /* Intentionally no break. */
    /* Case 1 - cnt is always in range [1..3] */
    default:
        pDst8[*pDPos] = (uint8)(*pPrev >> NEULIB_SHIFT_24);
        (*pDPos)++;
        *pPrev <<= NEULIB_SHIFT_8;
        break;
    }
#endif  /* (CPU_BYTE_ORDER == LOW_BYTE_FIRST) */
}

/*
********************************************************************************
* Function Name: NeuLib_MemCopy_32_Aligned
*
* Explanation:   Copy 32-bit aligned data from pSrc32 to pDst32.
* (Synchronous)
*
* param:         pDst32 32-bit pointer to the memory location to copy to.
*                pSrc32 32-bit pointer to the memory location to copy from.
*                cnt:   Number of bytes to copy, pDst32 must be valid for this amount.
*
* retval:        None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemCopy_32_Aligned(
    P2VAR(uint32, AUTOMATIC, NEULIB_APPL_DATA) pDst32,
    P2CONST(uint32, AUTOMATIC, NEULIB_APPL_CONST) pSrc32,
    uint32_least cnt
)
{
    uint32 x0;
    uint32 x1;
    uint32 x2;
    uint32 x3;
    uint32 remSize;
    uint32 dstPos = NEULIB_INIT_0;

    /* Linearly copy 16-byte blocks using 32-bit accesses in a loop. */
    for (remSize = cnt; remSize >= NEULIB_MEMCOPY_16_BYTE; remSize -= 16u)
    {
        x0 = pSrc32[dstPos + NEULIB_SHIFT_0];
        x1 = pSrc32[dstPos + NEULIB_SHIFT_1];
        x2 = pSrc32[dstPos + NEULIB_SHIFT_2];
        x3 = pSrc32[dstPos + NEULIB_SHIFT_3];
        pDst32[dstPos + NEULIB_SHIFT_0] = x0;
        pDst32[dstPos + NEULIB_SHIFT_1] = x1;
        pDst32[dstPos + NEULIB_SHIFT_2] = x2;
        pDst32[dstPos + NEULIB_SHIFT_3] = x3;
        dstPos += NEULIB_SHIFT_4;
    }

    /**
     * Copy the remSize block using a jump table.
     *
     * MISRA C:2012 16.1
     * All switch statements shall be well-formed.
     * Initialize the remaining block using a jump table
     */
    switch (remSize)
    {
    case NEULIB_CNT_15:                 /*!< MISRA C:2012 16.3       */
    case NEULIB_CNT_14:                 /*!< MISRA C:2012 16.3       */
    case NEULIB_CNT_13:                 /*!< MISRA C:2012 16.3       */
    case NEULIB_CNT_12:                 /*!< MISRA C:2012 16.3       */
        pDst32[dstPos] = pSrc32[dstPos];
        dstPos++;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_11:                 /*!< MISRA C:2012 16.3       */
    case NEULIB_CNT_10:                 /*!< MISRA C:2012 16.3       */
    case NEULIB_CNT_9:                  /*!< MISRA C:2012 16.3       */
    case NEULIB_CNT_8:                  /*!< MISRA C:2012 16.3       */
        pDst32[dstPos] = pSrc32[dstPos];
        dstPos++;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_7:                 /*!< MISRA C:2012 16.3       */
    case NEULIB_CNT_6:                 /*!< MISRA C:2012 16.3       */
    case NEULIB_CNT_5:                 /*!< MISRA C:2012 16.3       */
    case NEULIB_CNT_4:                 /*!< MISRA C:2012 16.3       */
        pDst32[dstPos] = pSrc32[dstPos];
        dstPos++;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_3:                 /*!< MISRA C:2012 16.3       */
    case NEULIB_CNT_2:                 /*!< MISRA C:2012 16.3       */
    case NEULIB_CNT_1:                 /*!< MISRA C:2012 16.3       */
        NeuLib_MemCopy_8_3((uint8 *)&pDst32[dstPos], (uint8 *)&pSrc32[dstPos], (uint8)(remSize & NEULIB_MEMCOPY_MASK_3));
        FALLTHROUGH;
        /*!< Intentionally no break. */
    default:
        /* Do nothing. */
        break;
    }
}

/*
********************************************************************************
* Function Name: NeuLib_MemCopy_32_Unaligned
*
* Explanation:   Copies data from 32-bit aligned pSrc to unaligned pDst8.
* (Synchronous)
*
* param:         pDst8     8-bit pointer to the memory location to copy to.
*                pSrc32    32-bit pointer to the memory location to copy from.
*                cnt       Number of bytes to copy, pDst8 must be valid for this amount.
*                dstOffset DstPtr offset to the next 32-bit boundary.
*
* retval:        None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemCopy_32_Unaligned(
    P2VAR(uint8, AUTOMATIC, NEULIB_APPL_DATA) pDst8,
    P2CONST(uint32, AUTOMATIC, NEULIB_APPL_CONST) pSrc32,
    uint32_least cnt,
    uint8_least dstOffset
)
{
    uint32 dstPos = NEULIB_INIT_0;
    uint32 sPos = NEULIB_INIT_0;
    uint32 remSize = cnt;

    /* If more than 32 bytes have to be copied. */
    if (remSize >= NEULIB_MEMCOPY_32_BYTE)
    {
        uint32 prev;
        P2VAR(uint32, AUTOMATIC, NEULIB_VAR_FAR) dst32Ptr;

        /* Copy the first partial word to reach the 32-bit boundary and adjust the destination pointer. */
        prev = pSrc32[sPos];

        remSize -= NEULIB_SHIFT_4;
        NeuLib_MemCopy_8_PartialWord(pDst8, dstOffset, &prev, &dstPos);

        /* At this point 'pDst8[dstPos]' is aligned to a 32-bit boundary */
        dst32Ptr = (uint32 *)(void *)&pDst8[dstPos];
        dstPos = NEULIB_INIT_0;
        sPos++;

        /* Linearly copy 16-byte blocks using 32-bit accesses by correcting the byte displacement of dst and src. */
        if (MEM_24_BIT_DISPLACEMENT == dstOffset) /* 24-bit displacement */
        {
            uint32 x0;
            uint32 x1;
            uint32 x2;
            uint32 x3;
            uint32 x4;

            for (; remSize >= NEULIB_MEMCOPY_16_BYTE; remSize -= NEULIB_SHIFT_16)
            {
                x1 = pSrc32[sPos + NEULIB_SHIFT_0];
                x2 = pSrc32[sPos + NEULIB_SHIFT_1];
                x3 = pSrc32[sPos + NEULIB_SHIFT_2];
                x4 = pSrc32[sPos + NEULIB_SHIFT_3];

#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
                x0 = prev | (x1 << NEULIB_SHIFT_8);
                x1 = (x1 >> NEULIB_SHIFT_24) | (x2 << NEULIB_SHIFT_8);
                x2 = (x2 >> NEULIB_SHIFT_24) | (x3 << NEULIB_SHIFT_8);
                x3 = (x3 >> NEULIB_SHIFT_24) | (x4 << NEULIB_SHIFT_8);
                prev = x4 >> NEULIB_SHIFT_24;
#else   /* CPU_BYTE_ORDER == HIGH_BYTE_FIRST */
                x0 = prev | (x1 >> NEULIB_SHIFT_8);
                x1 = (x1 << NEULIB_SHIFT_24) | (x2 >> NEULIB_SHIFT_8);
                x2 = (x2 << NEULIB_SHIFT_24) | (x3 >> NEULIB_SHIFT_8);
                x3 = (x3 << NEULIB_SHIFT_24) | (x4 >> NEULIB_SHIFT_8);
                prev = x4 << NEULIB_SHIFT_24;
#endif  /* (CPU_BYTE_ORDER == LOW_BYTE_FIRST) */

                dst32Ptr[dstPos + NEULIB_SHIFT_0] = x0;
                dst32Ptr[dstPos + NEULIB_SHIFT_1] = x1;
                dst32Ptr[dstPos + NEULIB_SHIFT_2] = x2;
                dst32Ptr[dstPos + NEULIB_SHIFT_3] = x3;

                sPos += NEULIB_SHIFT_4;
                dstPos += NEULIB_SHIFT_4;
            }
        }
        /* 16-bit displacement */
        else if (MEM_16_BIT_DISPLACEMENT == dstOffset)
        {
            uint32 x0;
            uint32 x1;
            uint32 x2;
            uint32 x3;
            uint32 x4;

            for (; remSize >= NEULIB_MEMCOPY_16_BYTE; remSize -= NEULIB_SHIFT_16)
            {
                x1 = pSrc32[sPos + NEULIB_SHIFT_0];
                x2 = pSrc32[sPos + NEULIB_SHIFT_1];
                x3 = pSrc32[sPos + NEULIB_SHIFT_2];
                x4 = pSrc32[sPos + NEULIB_SHIFT_3];

#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
                x0 = prev | (x1 << NEULIB_SHIFT_16);
                x1 = (x1 >> NEULIB_SHIFT_16) | (x2 << NEULIB_SHIFT_16);
                x2 = (x2 >> NEULIB_SHIFT_16) | (x3 << NEULIB_SHIFT_16);
                x3 = (x3 >> NEULIB_SHIFT_16) | (x4 << NEULIB_SHIFT_16);
                prev = x4 >> 16u;
#else /* CPU_BYTE_ORDER == HIGH_BYTE_FIRST */
                x0 = prev | (x1 >> NEULIB_SHIFT_16);
                x1 = (x1 << NEULIB_SHIFT_16) | (x2 >> NEULIB_SHIFT_16);
                x2 = (x2 << NEULIB_SHIFT_16) | (x3 >> NEULIB_SHIFT_16);
                x3 = (x3 << NEULIB_SHIFT_16) | (x4 >> NEULIB_SHIFT_16);
                prev = x4 << NEULIB_SHIFT_16;
#endif  /* (CPU_BYTE_ORDER == LOW_BYTE_FIRST) */

                dst32Ptr[dstPos + NEULIB_SHIFT_0] = x0;
                dst32Ptr[dstPos + NEULIB_SHIFT_1] = x1;
                dst32Ptr[dstPos + NEULIB_SHIFT_2] = x2;
                dst32Ptr[dstPos + NEULIB_SHIFT_3] = x3;

                dstPos += NEULIB_SHIFT_4;
                sPos += NEULIB_SHIFT_4;
            }
        }
        else /* dstOffset == 1 - 8-bit displacement */
        {
            uint32 x0;
            uint32 x1;
            uint32 x2;
            uint32 x3;
            uint32 x4;

            for (; remSize >= NEULIB_MEMCOPY_16_BYTE; remSize -= NEULIB_SHIFT_16)
            {
                x1 = pSrc32[sPos + NEULIB_SHIFT_0];
                x2 = pSrc32[sPos + NEULIB_SHIFT_1];
                x3 = pSrc32[sPos + NEULIB_SHIFT_2];
                x4 = pSrc32[sPos + NEULIB_SHIFT_3];

#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
                x0 = prev | (x1 << NEULIB_SHIFT_24);
                x1 = (x1 >> NEULIB_SHIFT_8) | (x2 << NEULIB_SHIFT_24);
                x2 = (x2 >> NEULIB_SHIFT_8) | (x3 << NEULIB_SHIFT_24);
                x3 = (x3 >> NEULIB_SHIFT_8) | (x4 << NEULIB_SHIFT_24);
                prev = x4 >> NEULIB_SHIFT_8;
#else /* CPU_BYTE_ORDER == HIGH_BYTE_FIRST */
                x0 = prev | (x1 >> NEULIB_SHIFT_24);
                x1 = (x1 << NEULIB_SHIFT_8) | (x2 >> NEULIB_SHIFT_24);
                x2 = (x2 << NEULIB_SHIFT_8) | (x3 >> NEULIB_SHIFT_24);
                x3 = (x3 << NEULIB_SHIFT_8) | (x4 >> NEULIB_SHIFT_24);
                prev = x4 << NEULIB_SHIFT_8;
#endif  /* (CPU_BYTE_ORDER == LOW_BYTE_FIRST) */

                dst32Ptr[dstPos + NEULIB_SHIFT_0] = x0;
                dst32Ptr[dstPos + NEULIB_SHIFT_1] = x1;
                dst32Ptr[dstPos + NEULIB_SHIFT_2] = x2;
                dst32Ptr[dstPos + NEULIB_SHIFT_3] = x3;

                dstPos += NEULIB_SHIFT_4;
                sPos += NEULIB_SHIFT_4;
            }
        }
        /* Linearly copy the remSize words using a loop. */
        {
            uint32 x0;
            uint32 x1;
            uint8 prevShift = (dstOffset << NEULIB_SHIFT_3) & NEULIB_MEMCOPY_MASK_31;
            uint8 xShift = NEULIB_CNT_32 - prevShift;

            /* At this point remSize is < 16 byte */
            for (; remSize >= NEULIB_CNT_4; remSize -= NEULIB_SHIFT_4)
            {
                x1 = pSrc32[sPos];

#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
                x0 = prev | (x1 << xShift);
                prev = x1 >> prevShift;
#else   /* CPU_BYTE_ORDER == HIGH_BYTE_FIRST */
                x0 = prev | (x1 >> xShift);
                prev = x1 << prevShift;
#endif  /* (CPU_BYTE_ORDER == LOW_BYTE_FIRST) */
                dst32Ptr[dstPos] = x0;

                dstPos++;
                sPos++;
            }
        }

        /* Copy the remSize partial word using a byte-wise algorithm. */
        pDst8 = (uint8 *)&dst32Ptr[dstPos];
        dstPos = NEULIB_SHIFT_0;
        NeuLib_MemCopy_8_PartialWord(pDst8, (NEULIB_CNT_4 - dstOffset), &prev, &dstPos);
    }

    /* Copy the remSize bytes using a byte-wise algorithm. */
    NeuLib_MemCopy_8_31(&pDst8[dstPos], (const uint8*)&pSrc32[sPos], (uint8)(remSize & NEULIB_MEMCOPY_MASK_31));
}

/*
********************************************************************************
* Function Name: NeuLib_MemSet_8_3
*
* Explanation:   Initializes up to 3 bytes at dstPtr to the character value (any alignment).
* (Synchronous)
*
* param:         dstPtr 8-bit pointer to the memory location to be initialized.
*                value  The character to be used to initialize the memory.
*                cnt    Number of bytes to initialize, pDst must be valid for this amount.
*
* retval:        None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemSet_8_3(
    P2VAR(uint8, AUTOMATIC, NEULIB_APPL_DATA) pDst8,
    uint8 value,
    uint8_least cnt
)
{
    /**
     * Initialize up to 3 bytes using a jump table.
     *
     * MISRA C:2012 16.1
     * All switch statements shall be well-formed.
     * Initialize up to 3 bytes using a jump table.
     */
    switch (cnt)
    {
    case NEULIB_CNT_3:                /* MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_2] = value;
        FALLTHROUGH;
        /* Intentionally no break. */
    case NEULIB_CNT_2:                /* MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_1] = value;
        FALLTHROUGH;
        /* Intentionally no break. */
    case NEULIB_CNT_1:                /* MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_0] = value;
        FALLTHROUGH;
        /* Intentionally no break. */
    default:
        /* Do nothing. */
        break;
    }
}

/*
********************************************************************************
* Function Name: NeuLib_MemSet_8_31
*
* Explanation:   Initializes up to 31 bytes at dstPtr to the character value (any alignment).
* (Synchronous)
*
* param:         dstPtr 8-bit pointer to the memory location to be initialized.
*                value  The character to be used to initialize the memory.
*                cnt    Number of bytes to initialize, pDst must be valid for this amount.
*
* retval:        None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemSet_8_31(
    P2VAR(uint8, AUTOMATIC, NEULIB_APPL_DATA) pDst8,
    uint8 value,
    uint8_least cnt
)
{
    /**
     * MISRA C:2012 16.1
     * All switch statements shall be well-formed.
     * Initialize up to 31 bytes using a jump table.
     */
    switch (cnt)
    {
    case NEULIB_CNT_31:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_30] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_30:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_29] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_29:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_28] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_28:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_27] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_27:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_26] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_26:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_25] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_25:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_24] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_24:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_23] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_23:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_22] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_22:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_21] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_21:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_20] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_20:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_19] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_19:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_18] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_18:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_17] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_17:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_16] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_16:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_15] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_15:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_14] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_14:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_13] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_13:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_12] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_12:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_11] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_11:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_10] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_10:     /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_9] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_9:      /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_8] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_8:      /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_7] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_7:      /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_6] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_6:      /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_5] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_5:      /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_4] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_4:      /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_3] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_3:      /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_2] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_2:      /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_1] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_1:      /*!< MISRA C:2012 16.3 */
        pDst8[NEULIB_IDX_0] = value;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    default:
        /* Nothing to do. */
        break;
    }
}

/*
********************************************************************************
* Function Name: NeuLib_MemSet_32_Aligned
*
* Explanation:   Initializes memory at dstPtr to the character value (32-bit aligned).
* (Synchronous)
*
* param:         dstPtr 32-bit pointer to the memory location to be initialized.
*                value  The character to be used to initialize the memory.
*                cnt    Number of bytes to initialize, pDst must be valid for this amount.
*
* retval:        None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, NEULIB_CODE) NeuLib_MemSet_32_Aligned(
    P2VAR(uint32, AUTOMATIC, NEULIB_APPL_DATA) pDst32,
    uint8 value,
    uint32_least cnt
)
{
    uint32 remSize;
    uint32 dPos    = NEULIB_INIT_0;
    uint32 value32 = (((uint32)value << NEULIB_SHIFT_24) |
                      ((uint32)value << NEULIB_SHIFT_16) |
                      ((uint32)value << NEULIB_SHIFT_8 ) | value);

    /* Linearly initialize 16-byte blocks using 32-bit accesses in a loop. */
    for (remSize = cnt; remSize >= NEULIB_MEMCOPY_16_BYTE; remSize -= NEULIB_SHIFT_16)
    {
        pDst32[dPos + NEULIB_SHIFT_0] = value32;
        pDst32[dPos + NEULIB_SHIFT_1] = value32;
        pDst32[dPos + NEULIB_SHIFT_2] = value32;
        pDst32[dPos + NEULIB_SHIFT_3] = value32;
        dPos += NEULIB_SHIFT_4;
    }

    /**
     * Initialize the remSize block using a jump table.
     *
     * MISRA C:2012 16.1
     * All switch statements shall be well-formed.
     * Initialize the remaining block using a jump table
     */
    switch (remSize)
    {
    case NEULIB_CNT_15:  /*!< MISRA C:2012 16.3 */
    case NEULIB_CNT_14:  /*!< MISRA C:2012 16.3 */
    case NEULIB_CNT_13:  /*!< MISRA C:2012 16.3 */
    case NEULIB_CNT_12:  /*!< MISRA C:2012 16.3 */
        pDst32[dPos] = value32;
        dPos++;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_11:  /*!< MISRA C:2012 16.3 */
    case NEULIB_CNT_10:  /*!< MISRA C:2012 16.3 */
    case NEULIB_CNT_9:   /*!< MISRA C:2012 16.3 */
    case NEULIB_CNT_8:   /*!< MISRA C:2012 16.3 */
        pDst32[dPos] = value32;
        dPos++;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_7:   /*!< MISRA C:2012 16.3 */
    case NEULIB_CNT_6:   /*!< MISRA C:2012 16.3 */
    case NEULIB_CNT_5:   /*!< MISRA C:2012 16.3 */
    case NEULIB_CNT_4:   /*!< MISRA C:2012 16.3 */
        pDst32[dPos] = value32;
        dPos++;
        FALLTHROUGH;
        /*!< Intentionally no break. */
    case NEULIB_CNT_3:   /*!< MISRA C:2012 16.3 */
    case NEULIB_CNT_2:   /*!< MISRA C:2012 16.3 */
    case NEULIB_CNT_1:   /*!< MISRA C:2012 16.3 */
        NeuLib_MemSet_8_3((uint8 *)&pDst32[dPos], value, (uint8_least)(remSize & NEULIB_MEMCOPY_MASK_3));
        FALLTHROUGH;
        /*!< Intentionally no break. */
    default:
        /* Do nothing. */
        break;
    }
}
#endif  /* (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON) */

/*
********************************************************************************
* Function Name: NeuLib_memcpy
*
* Explanation:   This function will copy memory content from source address to destination address.
* (Synchronous)
*
* param:         dstPtr The address of destination memory.
*                srcPtr The address of source memory.
*                size   The copied length.
*
* retval:        None
********************************************************************************
*/
FUNC(void, NEULIB_CODE) NeuLib_memcpy(
    P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) dstPtr,
    P2CONST(void, AUTOMATIC, NEULIB_APPL_CONST) srcPtr,
    CONST(uint32, NEULIB_CONST) size
)
{
    uint32 remSize;
#if (NEULIB_MEM_OPERATION_OPTIMIZATION != STD_ON)
    uint8 *dst = (uint8 *)dstPtr;
    uint8 *src = (uint8 *)srcPtr;
    uint32 *alignedDst;
    uint32 *alignedSrc;
    uint32 len = size;
#endif  /* (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON) */

    /* Pointer check. */
    NeuLib_CheckDetReturnVoid(dstPtr != NULL_PTR, NEULIB_SID_MEM_COPY, NEULIB_E_PARAM_POINTER);
    NeuLib_CheckDetReturnVoid(srcPtr != NULL_PTR, NEULIB_SID_MEM_COPY, NEULIB_E_PARAM_POINTER);

#if (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON)
    remSize = size;
    if (remSize < NEULIB_MEMCOPY_32_BYTE)
    {
        /* Use a byte-wise algorithm. */
        NeuLib_MemCopy_8_31((uint8*)dstPtr, (const uint8*)srcPtr, (uint8_least)(size & NEULIB_MEMCOPY_MASK_31));
    }
    else
    {
        /* Get the source pointer offset to the next 32-bit boundary. */
        uint8 srcOffset = MEM_ALIGN_OFFSET(srcPtr);
        uint8 dstOffset;

        /* If the source is not aligned. */
        if (NEULIB_SHIFT_0 != srcOffset)
        {
            /* Copy the amount of bytes to reach the boundary on 'pSrc' and adjust the pointers. */
            NeuLib_MemCopy_8_3((uint8*)dstPtr, (const uint8*)srcPtr, srcOffset);
            srcPtr = &((const uint8*)srcPtr)[srcOffset];
            dstPtr = &((uint8*)dstPtr)[srcOffset];
            remSize -= srcOffset;
        }

        /* Get the destination pointer offset to the next 32-bit boundary. */
        dstOffset = MEM_ALIGN_OFFSET(dstPtr);

        /* If destination is aligned. */
        if (NEULIB_SHIFT_0 == dstOffset)
        {
            /* Both pointers are aligned, use the 32-bit aligned memcpy. */
            NeuLib_MemCopy_32_Aligned((uint32*)dstPtr, (const uint32*)srcPtr, remSize);
        }
        else
        {
            /* Use the 32-bit unaligned memcpy. */
            NeuLib_MemCopy_32_Unaligned((uint8*)dstPtr, (const uint32*)srcPtr, remSize, dstOffset);
        }
    }
#else   /* (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON) */

    /**
     * If the size is small, or either SRC or DST is unaligned,
     * then punt into the byte copy loop.  This should be rare.
     */
    if (!TOO_SMALL(len) && !UNALIGNED(src, dst))
    {
        alignedDst = (uint32 *)dst;
        alignedSrc = (uint32 *)src;

        /* Copy 4X uint32 words at a time if possible. */
        while (len >= BIGBLOCKSIZE)
        {
            *alignedDst++ = *alignedSrc++;
            *alignedDst++ = *alignedSrc++;
            *alignedDst++ = *alignedSrc++;
            *alignedDst++ = *alignedSrc++;
            len -= BIGBLOCKSIZE;
        }

        /* Copy one uint32 word at a time if possible. */
        while (len >= LITTLEBLOCKSIZE)
        {
            *alignedDst++ = *alignedSrc++;
            len -= LITTLEBLOCKSIZE;
        }

        /* Pick up any residual with a byte copier. */
        dst = (uint8 *)alignedDst;
        src = (uint8 *)alignedSrc;
    }

    while (len--)
    {
        *dst++ = *src++;
    }

#endif  /* (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON) */
}

/*
********************************************************************************
* Function Name: NeuLib_memcpy32
*
* Explanation: 32-bit data copy.
* (Synchronous)
*
* param: dstPtr: The address of destination memory.
*        srcPtr: The address of source memory.
*        size: The copied length.
*
* retval: None
********************************************************************************
*/
FUNC(void, NEULIB_CODE) NeuLib_memcpy32(
    P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) dstPtr,
    P2CONST(void, AUTOMATIC, NEULIB_APPL_CONST) srcPtr,
    CONST(uint32, NEULIB_CONST) size
)
{
    uint8* dst = (uint8*)dstPtr;
    uint8* src = (uint8*)srcPtr;
    uint32* alignedDst;
    uint32* alignedSrc;
    uint32 len = size;

    /* Pointer check. */
    NeuLib_CheckDetReturnVoid(dstPtr != NULL_PTR, NEULIB_SID_MEM_COPY, NEULIB_E_PARAM_POINTER);
    NeuLib_CheckDetReturnVoid(srcPtr != NULL_PTR, NEULIB_SID_MEM_COPY, NEULIB_E_PARAM_POINTER);

    /*
     * If the size is small, or either SRC or DST is unaligned,
     * then punt into the byte copy loop.  This should be rare.
     */
    if( !TOO_SMALL(len) && !UNALIGNED(src, dst) )
    {
        alignedDst = (uint32*)dst;
        alignedSrc = (uint32*)src;

        /* Copy 4X uint32 words at a time if possible. */
        while( len >= BIGBLOCKSIZE )
        {
            *alignedDst++ = *alignedSrc++;
            *alignedDst++ = *alignedSrc++;
            *alignedDst++ = *alignedSrc++;
            *alignedDst++ = *alignedSrc++;
            len -= BIGBLOCKSIZE;
        }

        /* Copy one uint32 word at a time if possible. */
        while( len >= LITTLEBLOCKSIZE )
        {
            *alignedDst++ = *alignedSrc++;
            len -= LITTLEBLOCKSIZE;
        }

        /* Pick up any residual with a byte copier. */
        dst = (uint8*)alignedDst;
        src = (uint8*)alignedSrc;
    }

    while( len-- )
    {
        *dst++ = *src++;
    }
}

/*
********************************************************************************
* Function Name: NeuLib_memset
*
* Explanation:   Memory set value.
* (Synchronous)
*
* param:         dstPtr DstPtr data pointer.
*                value  Set value.
*                len    Copy total length.
*
* retval:        None
********************************************************************************
*/
FUNC(void, NEULIB_CODE) NeuLib_memset(
    volatile P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) dstPtr,
    uint8 value,
    CONST(uint32, NEULIB_CONST) len
)
{
    uint32 remSize;
#if (NEULIB_MEM_OPERATION_OPTIMIZATION != STD_ON)
    uint8 *u8DstPtr = (uint8 *)dstPtr;
#endif  /* (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON) */

    NeuLib_CheckDetReturnVoid(dstPtr != NULL_PTR, NEULIB_SID_MEM_SET, NEULIB_E_PARAM_POINTER);

    remSize = len;
#if (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON)

    /* If less than 32 bytes have to be initialized. */
    if (remSize < NEULIB_MEMCOPY_32_BYTE)
    {
        /* Use a byte-wise algorithm. */
        NeuLib_MemSet_8_31((uint8 *)dstPtr, value, (uint8)(remSize & NEULIB_MEMCOPY_MASK_31));
    }
    else
    {
        /* Get the destination pointer offset to the next 32-bit boundary */
        uint8 dstOffset = MEM_ALIGN_OFFSET(dstPtr);

        /* If the destination is not aligned. */
        if (dstOffset != NEULIB_SHIFT_0)
        {
            /* Initialize the amount of bytes to reach the boundary on 'dstPtr' and adjust the pointer */
            NeuLib_MemSet_8_3((uint8 *)dstPtr, value, dstOffset);
            dstPtr = &((uint8 *)dstPtr)[dstOffset];
            remSize -= dstOffset;
        }

        /* The pointer is aligned, use the 32-bit aligned std_memset. */
        NeuLib_MemSet_32_Aligned((uint32 *)dstPtr, value, remSize);
    }
#else   /* (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON) */

    while (remSize--)
    {
        *u8DstPtr = value;
        u8DstPtr++;
    }
#endif  /* (NEULIB_MEM_OPERATION_OPTIMIZATION == STD_ON) */
}

/*
********************************************************************************
* Function Name: NeuLib_memcmp
*
* Explanation:   This function will compare two areas of memory.
* (Synchronous)
*
* param:         dstPtr One area of memory.
*                srcPtr Another area of memory.
*                count  The size of the area
*
* retval:        When dstPtr < srcPtr, the return value is <0 FALSE.
*                When dstPtr = srcPtr, the return value = TRUE
*                When dstPtr > srcPtr, the return value is> 0 FALSE.
********************************************************************************
*/
FUNC(boolean, NEULIB_CODE) NeuLib_memcmp(
    P2CONST(void, AUTOMATIC, NEULIB_APPL_CONST) dstPtr,
    P2CONST(void, AUTOMATIC, NEULIB_APPL_CONST) srcPtr,
    uint32 count
)
{
    P2CONST(uint8, AUTOMATIC, NEULIB_APPL_CONST) dst;
    P2CONST(uint8, AUTOMATIC, NEULIB_APPL_CONST) src;

    /* Pointer check. */
    NeuLib_CheckDetReturnValue(dstPtr != NULL_PTR, NEULIB_SID_MEM_CMP, NEULIB_E_PARAM_POINTER, FALSE);
    NeuLib_CheckDetReturnValue(srcPtr != NULL_PTR, NEULIB_SID_MEM_CMP, NEULIB_E_PARAM_POINTER, FALSE);
    NeuLib_CheckDetReturnValue(count > NEULIB_CNT_0, NEULIB_SID_MEM_CMP, NEULIB_E_PARAM_POINTER, FALSE);

    dst = (const uint8 *)dstPtr;
    src = (const uint8 *)srcPtr;
    for (; count > NEULIB_CNT_0; count--)
    {
        if (*dst != *src)
        {
            return FALSE;
        }

        /* Move memory. */
        dst++;
        src++;
    }

    return TRUE;
}

/*
********************************************************************************
* Function Name: NeuLib_memmove
*
* Explanation:   This function will move memory content from source address to destination address.
* (Synchronous)
*
* param:         dstPtr The address of destination memory.
*                srcPtr The address of source memory.
*                count  The copied length.
*
* retval:        None
********************************************************************************
*/
FUNC_P2VAR(void, NEULIB_APPL_DATA, NEULIB_CODE) NeuLib_memmove(
    P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) dstPtr,
    P2CONST(void, AUTOMATIC, NEULIB_APPL_CONST) srcPtr,
    uint32 count
)
{
    sint8 *s;
    sint8 *tmp;

    NeuLib_CheckDetReturnVoid(dstPtr != NULL_PTR, NEULIB_SID_MEM_MOVE, NEULIB_E_PARAM_POINTER);
    NeuLib_CheckDetReturnVoid(srcPtr != NULL_PTR, NEULIB_SID_MEM_MOVE, NEULIB_E_PARAM_POINTER);
    NeuLib_CheckDetReturnVoid(count != 0u, NEULIB_SID_MEM_MOVE, NEULIB_E_PARAM_POINTER);

    tmp = (sint8 *)dstPtr;
    s = (sint8 *)srcPtr;

    if (s < tmp && tmp < s + count)
    {
        tmp += count;
        s += count;

        while (count--)
        {
            *(--tmp) = *(--s);
        }
    }
    else
    {
        while (count--)
        {
            *tmp++ = *s++;
        }
    }

    return dstPtr;
}

/*
********************************************************************************
* Function Name: NeuLib_strlen
*
* Explanation:   This function will return the length of a string, which terminate
                 will null character.
* (Synchronous)
*
* param:         str The string to be calculated.
*
* retval:        String length (not 0).
********************************************************************************
*/
FUNC(uint32, NEULIB_CODE) NeuLib_strlen(
    P2CONST(char, AUTOMATIC, NEULIB_APPL_CONST) str
)
{
    const char* sc;
    NeuLib_CheckDetReturnValue(str != NULL_PTR, NEULIB_SID_STR_LEN, NEULIB_E_PARAM_POINTER, 0);

    for (sc = str; *sc != '\0'; ++sc)
    {
        /* Do nothing. */
    }

    /* Return length. */
    return (uint32)(sc - str);
}

/*
********************************************************************************
* Function Name: NeuLib_strcmp
*
* Explanation:   Compares the string pointed to by str1 with the string pointed to by str2.
* (Synchronous)
*
* param:         str1 The first string to compare against.
*                str2 The second string to compare against.
*
* retval:        If the return value is less than 0, it means str1 is less than str2.
*                If the return value is greater than 0, it means str1 is greater than str2.
*                If the return value is equal to 0, it means str1 is equal to str2.
********************************************************************************
*/
FUNC(sint8, NEULIB_CODE) NeuLib_strcmp(
    P2CONST(char, AUTOMATIC, NEULIB_APPL_CONST) str1,
    P2CONST(char, AUTOMATIC, NEULIB_APPL_CONST) str2
)
{
    while ((*str1 != '\0') && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

    return (*str1 - *str2);
}

/*
********************************************************************************
* Function Name: NeuLib_strncmp
*
* Explanation:   Compare str1 and str2, at most the first n bytes.
* (Synchronous)
*
* param:         str1 The first string to compare against.
*                str2 The second string to compare against.
*                cnt  The maximum number of characters to compare.
*
* retval:        If the return value < 0, it means str1 is less than str2.
*                If the return value > 0, it means str1 is greater than str2.
*                If the return value = 0, it means str1 is equal to str2.
********************************************************************************
*/
FUNC(sint8, NEULIB_CODE) NeuLib_strncmp (
    P2CONST(char, AUTOMATIC, NEULIB_APPL_CONST) str1,
    P2CONST(char, AUTOMATIC, NEULIB_APPL_CONST) str2,
    uint32 cnt
)
{
    NeuLib_CheckDetReturnValue(str1 != NULL_PTR, NEULIB_SID_STR_NCMP, NEULIB_E_PARAM_POINTER, -1);
    NeuLib_CheckDetReturnValue(str2 != NULL_PTR, NEULIB_SID_STR_NCMP, NEULIB_E_PARAM_POINTER, -1);

    if (NEULIB_CNT_0 == cnt)
    {
        return NEULIB_CNT_0;
    }

    while(--cnt && *str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

    return (*str1 - *str2);
}

#define NEULIB_STOP_SEC_CODE
#include "NeuLib_MemMap.h"
