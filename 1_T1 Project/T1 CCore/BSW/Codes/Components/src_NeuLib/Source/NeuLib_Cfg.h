/*
********************************************************************************
*
* File name: NeuLib_Cfg.h
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
* Change: Modify copyright.
* Cause: Bugfix
********************************************************************************
*/
#ifndef NEULIB_CFG_H_
#define NEULIB_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

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
 * If the Default Error Tracer (Det) shall be used, this parameter shall be set
 * to TRUE. Otherwise, it shall be set to FALSE.
 */
#define NEULIB_DEV_ERROR_DETECT             STD_OFF

/* Choose whether to enable memory optimization. */
#if (CPU_TYPE == CPU_TYPE_32 || CPU_TYPE == CPU_TYPE_64)
#define NEULIB_MEM_OPERATION_OPTIMIZATION   STD_ON
#else   /* (CPU_TYPE == CPU_TYPE_32 || CPU_TYPE == CPU_TYPE_64) */
#define NEULIB_MEM_OPERATION_OPTIMIZATION   STD_OFF
#endif  /* (CPU_TYPE == CPU_TYPE_32 || CPU_TYPE == CPU_TYPE_64) */

/* Eliminates compiler warning about unused arguments (GCC -Wextra -Wunused). */
#define NEU_UNUSED_ARG(x)                   (void)x

#if NEU_DEBUG
#define FLS     "Fls"
#define FLSAC   "FlsAc"
#define ERROR   "Error"

    #if ELOG_ENABLED
    #define NEULIB_DEBUG_LOG(_tag, _info, ...)                                          \
            do                                                                          \
            {                                                                           \
                elog_debug(_tag, _info, ##__VA_ARGS__);                                 \
            } while (0U)
    /* NeuLib asserts and prints a message. */
    #define NEULIB_ASSERT_MSG(_tag, _message, _expression)                              \
            do                                                                          \
            {                                                                           \
                if (!(_expression))                                                     \
                {                                                                       \
                    elog_assert(_tag,_message);                                         \
                    while (1);                                                          \
                }                                                                       \
            } while (0U)
    #define NEULIB_ASSERT(_message, _assertion)                                         \
        do                                                                              \
        {                                                                               \
            if (!(_assertion))                                                          \
            {                                                                           \
                elog_assert("Assertion \"%s\" failed at line %d in %s\n", _message);    \
                abort();                                                                \
            }                                                                           \
        } while (0)

    #else   /* ELOG_ENABLED */
    #include "stdio.h"
    #define NEULIB_DEBUG_LOG(_tag, _info, ...)                                          \
            do                                                                          \
            {                                                                           \
                printf(_tag, ":");                                                      \
                printf(_info, ##__VA_ARGS__);                                           \
            } while (0U)
    /* NeuLib asserts and prints a message. */
    #define NEULIB_ASSERT_MSG(_tag, _message, _expression)                              \
            do                                                                          \
            {                                                                           \
                if (!(_expression))                                                     \
                {                                                                       \
                    printf(_tag, ":");                                                  \
                    printf(_message);                                                   \
                    while (1);                                                          \
                }                                                                       \
            } while (0U)
    #define NEULIB_ASSERT(_message, _assertion)                                         \
        do                                                                              \
        {                                                                               \
            if (!(_assertion))                                                          \
            {                                                                           \
                printf("Assertion \"%s\" failed at line %d in %s\n", _message);         \
                abort();                                                                \
            }                                                                           \
        } while (0)
    #endif  /* ELOG_ENABLED */
#else   /* NEU_DEBUG */

#define FLS
#define MAIN_NEULIB
#define FLSAC
#define ERROR

#define NEULIB_DEBUG_LOG(_tag, _info, ...)
#define NEULIB_ASSERT(_message, _assertion)
#define NEULIB_ASSERT_MSG(_tag, _message, _expression)
#endif  /* NEU_DEBUG */
#define NEULIB_DUMMY_STATEMENT(v)              ((v)=(v))


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

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* NEULIB_CFG_H_ */
