/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* PROJECT     : CCFC3007PT
* DESCRIPTION : common h file
* HISTORY     : Initial version
* @file     common.h
* @version  3.0.0
* @date     2023 - 01 - 01
* @brief    Initial version.
*
*****************************************************************************/
#ifndef COMMON_INC_COMMON_H_
#define COMMON_INC_COMMON_H_

#include "typedefs.h"
/*===================================================================================================
 *                                       LOCAL MEMMAP
 ====================================================================================================*/
#ifdef MEM_MAP
#include "CompilerDefinition.h"
#ifdef S32DS_C_CCFC30XX
#define COMMON_START_SEC_CONFIG_DATA           __attribute__((section(".mcal_common_rodata")))
#define COMMON_STOP_SEC_CONFIG_DATA
#define COMMON_START_SEC_CODE                  __attribute__((section(".mcal_common_text")))
#define COMMON_STOP_SEC_CODE
#define COMMON_START_SEC_VAR_NO_INIT           __attribute__((section(".mcal_common_bss")))
#define COMMON_STOP_SEC_VAR_NO_INIT
#define COMMON_START_SEC_VAR_INIT              __attribute__((section(".mcal_common_data")))
#define COMMON_STOP_SEC_VAR_INIT
#define COMMON_START_SEC_VAR_SHARED_INIT       __attribute__((section(".mcal_common_share")))
#define COMMON_STOP_SEC_VAR_SHARED_INIT
#define COMMON_START_SEC_VAR_SHARED_NO_INIT    __attribute__((section(".mcal_common_bss_share")))
#define COMMON_STOP_SEC_VAR_SHARED_NO_INIT
#endif /* S32DS_C_CCFC30XX */
#ifdef GHS_C_CCFC30XX
#define PRAGMA(x)                              _Pragma(#x)
#define COMMON_START_SEC_CONFIG_DATA           PRAGMA(ghs section rodata=".mcal_common_rodata")
#define COMMON_STOP_SEC_CONFIG_DATA            PRAGMA(ghs section)
#define COMMON_START_SEC_CODE                  PRAGMA(ghs section text=".mcal_common_text")
#define COMMON_STOP_SEC_CODE                   PRAGMA(ghs section)
#define COMMON_START_SEC_VAR_NO_INIT           PRAGMA(ghs section bss=".mcal_common_bss")
#define COMMON_STOP_SEC_VAR_NO_INIT            PRAGMA(ghs section)
#define COMMON_START_SEC_VAR_INIT              PRAGMA(ghs section data = ".mcal_common_data")
#define COMMON_STOP_SEC_VAR_INIT               PRAGMA(ghs section)
#define COMMON_START_SEC_VAR_SHARED_INIT       __attribute__((section(".mcal_common_share")))
#define COMMON_STOP_SEC_VAR_SHARED_INIT
#define COMMON_START_SEC_VAR_SHARED_NO_INIT    __attribute__((section(".mcal_common_bss_share")))
#define COMMON_STOP_SEC_VAR_SHARED_NO_INIT
#endif /* GHS_C_CCFC30XX */
#ifdef HITECH_C_CCFC30XX
#define PRAGMA(x)                              _Pragma(#x)
#define COMMON_START_SEC_CONFIG_DATA           PRAGMA(section ".mcal_common_rodata" a)
#define COMMON_STOP_SEC_CONFIG_DATA            PRAGMA(section)
#define COMMON_START_SEC_CODE                  PRAGMA(section ".mcal_common_text" avx)
#define COMMON_STOP_SEC_CODE                   PRAGMA(section)
#define COMMON_START_SEC_VAR_NO_INIT           PRAGMA(section ".mcal_common_bss")
#define COMMON_STOP_SEC_VAR_NO_INIT            PRAGMA(section)
#define COMMON_START_SEC_VAR_INIT              PRAGMA(section ".mcal_common_data")
#define COMMON_STOP_SEC_VAR_INIT               PRAGMA(section)
#define COMMON_START_SEC_VAR_SHARED_INIT       PRAGMA(section ".mcal_common_share")
#define COMMON_STOP_SEC_VAR_SHARED_INIT        PRAGMA(section)
#define COMMON_START_SEC_VAR_SHARED_NO_INIT    PRAGMA(section ".mcal_common_bss_share")
#define COMMON_STOP_SEC_VAR_SHARED_NO_INIT     PRAGMA(section)
#endif /* HITECH_C_CCFC30XX */
#else
#define COMMON_START_SEC_CONFIG_DATA
#define COMMON_STOP_SEC_CONFIG_DATA
#define COMMON_START_SEC_CODE
#define COMMON_STOP_SEC_CODE
#define COMMON_START_SEC_VAR_NO_INIT
#define COMMON_STOP_SEC_VAR_NO_INIT
#define COMMON_START_SEC_VAR_INIT
#define COMMON_STOP_SEC_VAR_INIT
#define COMMON_START_SEC_VAR_SHARED_INIT
#define COMMON_STOP_SEC_VAR_SHARED_INIT
#define COMMON_START_SEC_VAR_SHARED_NO_INIT
#define COMMON_STOP_SEC_VAR_SHARED_NO_INIT
#endif /* MEM_MAP */

extern void cc_memcpy(uint8_t *dest, const uint8_t *src, const uint32_t bytes);
extern void cc_memset(uint8_t *dest, const uint8_t val, const uint32_t bytes);
extern uint8_t cc_memcmp(const uint8_t *src1, const uint8_t *src2, uint32_t len);
extern uint32_t cc_strlen(const uint8_t * s);
extern uint8_t halfword_swap(const uint8_t * src, uint8_t * dest, uint32_t n);
extern void delay(volatile uint32_t x);
extern void delay_ms(uint32_t ms);

#endif /* COMMON_INC_COMMON_H_ */
