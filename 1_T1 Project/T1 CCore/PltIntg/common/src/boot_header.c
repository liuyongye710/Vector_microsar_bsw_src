#include "typedefs.h"
/* PRQA S 1534 EOF */
#define BOOT_HEADER_MAGIC_WORD      0x005A0000U

#define BOOT_ENABLE_CPU_Z7_0        0x00000002U
#define BOOT_ENABLE_CPU_Z7_1        0x00000008U
#define BOOT_ENABLE_CPU_Z4_2        0x00000001U
#ifdef CPU_Z4_2
const volatile uint32_t __attribute__ ((section(".boot_header"))) boot_header1 = (BOOT_HEADER_MAGIC_WORD | BOOT_ENABLE_CPU_Z4_2); /* PRQA S 3408 */


#if defined(TURN_ON_CPU_Z7_0)
extern uint32_t __CPU_Z7_0_FLASH_BASE_ADDR;
const volatile uint32_t __attribute__ ((section(".cpu0_reset_vector"))) boot_header2_0 = (uint32_t)&__CPU_Z7_0_FLASH_BASE_ADDR; /* PRQA S 3408 */
#endif
#if defined(TURN_ON_CPU_Z7_1)
extern uint32_t __CPU_Z7_1_FLASH_BASE_ADDR;
const volatile uint32_t __attribute__ ((section(".cpu1_reset_vector"))) boot_header2_1 = (uint32_t)&__CPU_Z7_1_FLASH_BASE_ADDR; /* PRQA S 3408 */
#endif
#if defined(TURN_ON_CPU_Z4_2)
extern uint32_t __CPU_Z4_2_FLASH_BASE_ADDR;
const volatile uint32_t __attribute__ ((section(".cpu2_reset_vector"))) boot_header2_2 = (uint32_t)&__CPU_Z4_2_FLASH_BASE_ADDR; /* PRQA S 3408 */
#endif
#endif
