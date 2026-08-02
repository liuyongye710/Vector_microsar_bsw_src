/*********************************************************************************//*!
*   \file           T1_targetSpecifics.h
*
*   \brief          T1-TARGET-SW header specific to Infineon TriCore architecture
*
*   \par Visibility
*                   External
*
*   \author nick
*
*   \version 2.5.5.0 r39439
*
*   \copyright GLIWA GmbH embedded systems, Weilheim i.OB. All rights reserved
*************************************************************************************/

#ifndef T1_TARGETSPECIFICS_H_
#define T1_TARGETSPECIFICS_H_ (1)

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined __TASKING__
#   define T1_FAR                               __far
#   define T1_INLINE                            static inline
#   if defined T1_NOF_CORES
#       define T1_FAR_CODE                      __indirect
#       if ! defined T1_GetCoreIdOffset
#           if 6 <= T1_NOF_CORES
                /* CPU5 has CORE_ID = 6, re-map to T1 core ID 5. */
#               define T1_GetCoreIdOffset( )    ( ( 5u + 7u * __mfcr(0xFE1C) ) >> 3 )
#           else /* fewer than 6 cores */
#               define T1_GetCoreIdOffset( )    __mfcr( 0xFE1C )
#           endif /* 6 <= T1_NOF_CORES */
#       endif /* ! defined T1_GetCoreIdOffset */
#   endif /* defined T1_NOF_CORES */
#   if !defined __TC13__ && (defined __TC16__ || defined __CORE_TC16__ || defined __CORE_TC16X__ || defined __CORE_TC162__ || defined __TC161__ || defined __TC162__)
#       define T1_DISABLE_INTERRUPTS( )         \
        do { T1_icuRegister_t const T1_oldIcr = __disable_and_save( )
#       define T1_ENABLE_INTERRUPTS( )          __restore( T1_oldIcr ); } while( 0 )
#   else /* TC1.3.1 */
#       define T1_INTERRUPTS_ARE_ENABLED( )     ( 0uL != (__mfcr(0xFE1C) & (0x1uL << 8)) )
#       define T1_DISABLE_INTERRUPTS( )         __disable( )
#       define T1_ENABLE_INTERRUPTS( )          __enable( )
#   endif
#elif defined __ghs__
#   define T1_FAR
#   define T1_FAR_CODE                          __farcall
#   define T1_INLINE                            static __inline__
#   if defined __gnu_asm /* Substantially more efficient */
#       define T1_DISABLE_INTERRUPTS( )         \
        do { T1_icuRegister_t T1_oldIcr; __asm volatile ( "disable %0" : "=d"(T1_oldIcr) )
#       define T1_ENABLE_INTERRUPTS( )          \
        __asm volatile ( "restore %0" : : "d"(T1_oldIcr) ); } while( 0 )
#   else /* ! defined __gnu_asm less efficient without GCC asm extensions */
#       define T1_DISABLE_INTERRUPTS( )         \
        do { T1_icuRegister_t const T1_oldIcr = T1_disableInterrupts( )
#       define T1_ENABLE_INTERRUPTS( )          \
        T1_enableInterrupts( ); } while( 0 )
#   endif /* defined __gnu_asm */
__asm unsigned T1_disableInterrupts( void )
{
    disable D2
}
__asm void T1_enableInterrupts( unsigned oldIcr )
{
%dreg oldIcr
    enable oldIcr
}
#   if defined T1_NOF_CORES && ! defined T1_GetCoreIdOffset
#       if 6 <= T1_NOF_CORES
            /* CPU5 has CORE_ID = 6, re-map to T1 core ID 5. */
#           if defined __GNUC__ /* Somewhat more efficient */
#               define T1_GetCoreIdOffset( )    \
({ T1_uint8Least_t coreId_; __asm( "mfcr %0, 0xFE1C" : "=d"(coreId_) ); coreId_ - (coreId_ >= 6u ? 1 : 0); })
#           else /* ! defined __GNUC___ without statement expressions */
#               include <intrinsics.h> /* Enable __mfcr intrinsic */
#               define T1_GetCoreIdOffset( )    ( ( 5u + 7u * __mfcr(0xFE1C) ) >> 3 )
#           endif /* defined __GNUC__ */
#       else /* fewer than 6 cores */
#           include <intrinsics.h> /* Enable __mfcr intrinsic */
#           define T1_GetCoreIdOffset( )        __mfcr( 0xFE1C )
#       endif /* 6 <= T1_NOF_CORES */
#   endif /* defined T1_NOF_CORES */
#elif defined __GNUC__
#   define T1_FAR
#   define T1_INLINE                            static inline
#   define T1_UNUSED( varDecl_ )                varDecl_ __attribute__((unused))
#   if defined T1_NOF_CORES
#       define T1_FAR_CODE                      __attribute__((longcall))
#       if ! defined T1_GetCoreIdOffset
#           if 6 <= T1_NOF_CORES
                /* CPU5 has CORE_ID = 6, re-map to T1 core ID 5. */
#               define T1_GetCoreIdOffset( )     \
({ T1_uint8Least_t coreId_; __asm( "mfcr %0, 0xFE1C" : "=d"(coreId_) ); coreId_ - (coreId_ >= 6u ? 1 : 0); })
#           else /* fewer than 6 cores */
#               define T1_GetCoreIdOffset( )     \
({ T1_uint8Least_t coreId_; __asm( "mfcr %0, 0xFE1C" : "=d"(coreId_) ); coreId_; })
#           endif /* if 6 <= T1_NOF_CORES */
#       endif /* ! defined T1_GetCoreIdOffset */
#   endif /* defined T1_NOF_CORES */
#   if !defined __TC13__ && (defined __TC16__ || defined __CORE_TC16__ || defined __CORE_TC16X__ || defined __CORE_TC162__ || defined __TC161__ || defined __TC162__)
#       define T1_DISABLE_INTERRUPTS( )         \
        do { T1_icuRegister_t T1_oldIcr; __asm volatile ( "disable %0" : "=d"(T1_oldIcr) )
#       define T1_ENABLE_INTERRUPTS( )          \
        __asm volatile ( "restore %0" : : "d"(T1_oldIcr) ); } while( 0 )
#   else /* TC1.3.1 */
#       define T1_INTERRUPTS_ARE_ENABLED( )     \
        ({ T1_icuRegister_t icr_; __asm volatile ( "mfcr %0, 0xFE2C" : "=d"(icr_) ); 0uL != ((icr_) & (0x1uL << 8)); })
#       define T1_DISABLE_INTERRUPTS( )         __asm volatile ( "disable" )
#       define T1_ENABLE_INTERRUPTS( )          __asm volatile ( "enable" )
#   endif
#   if defined __TOOL_VERSION__
#       define T1_OLD_GCC                       (1)
#   endif /* defined __TOOL_VERSION__ */
#elif defined __DCC__
#   include <tcasm.h>
#   define T1_FAR
#   define T1_INLINE                            static __inline__
#   if defined T1_NOF_CORES
#       define T1_FAR_CODE                      /* TODO */
#       if ! defined T1_GetCoreIdOffset
#           if 6 <= T1_NOF_CORES
                /* CPU5 has CORE_ID = 6, re-map to T1 core ID 5. */
#               define T1_GetCoreIdOffset( )    ( ( 5u + 7u * _mfcr( 0xFE1C ) ) >> 3 )
#           else /* fewer than 6 cores */
#               define T1_GetCoreIdOffset( )    _mfcr( 0xFE1C )
#           endif /* 6 <= T1_NOF_CORES */
#       endif /* ! defined T1_GetCoreIdOffset */
#   endif /* defined T1_NOF_CORES */
asm unsigned T1_SUSPEND_INTERRUPTS( void )
{
! "%d2"
    .long 0x03C0020D
}
#       define T1_DISABLE_INTERRUPTS( )         \
        do { T1_icuRegister_t const T1_oldIcr = T1_SUSPEND_INTERRUPTS( )
#       define T1_ENABLE_INTERRUPTS( )          \
        _resume( T1_oldIcr ); } while( 0 )
#else
#   error No recognised compiler
#endif

#define T1_NOINLINE                             __attribute__((noinline))

#define T1_CPU32BIT                             (1)

#define T1_LITTLE_ENDIAN                        (1)

/*! \brief Where applicable, select TriCore-specific code. */
#define T1_TRICORE                              (1)

#if defined __TASKING__

#   define T1_SEC_CONST_32                      __attribute__(( __align(4) ))
#   define T1_SEC_NEAR_NO_INIT_32               __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32                    __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER        __attribute__(( __align(4) ))
#   define T1_SEC_CONST_32_CORE0                __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_CORE0              __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE0  __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE0          __attribute__(( __align(64) ))
#   define T1_SEC_CONST_32_CORE1                __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_CORE1              __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE1  __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE1          __attribute__(( __align(64) ))
#   define T1_SEC_CONST_32_CORE2                __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_CORE2              __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE2  __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE2          __attribute__(( __align(64) ))
#   define T1_SEC_CONST_32_CORE3                __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_CORE3              __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE3  __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE3          __attribute__(( __align(64) ))
#   define T1_SEC_CONST_32_CORE4                __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_CORE4              __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE4  __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE4          __attribute__(( __align(64) ))
#   define T1_SEC_CONST_32_CORE4                __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_CORE5              __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE5  __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE5          __attribute__(( __align(64) ))
#   define T1_SEC_CONST_32_CORE6                __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_CORE6              __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE6  __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE6          __attribute__(( __align(64) ))
#   define T1_SEC_CONST_32_CORE7                __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_CORE7              __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE7  __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE7          __attribute__(( __align(64) ))
#   define T1_SEC_CONST_32_CORE8                __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_CORE8              __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE8  __attribute__(( __align(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE8          __attribute__(( __align(64) ))
#   define T1_SEC_NO_INIT_32_CLONE              __attribute__(( __align(4) ))
#   define T1_ALIGN_VAR( bytes_ )               __attribute__(( __align(bytes_) ))

#else /* Wind River or HighTec compiler */

#   define T1_SEC_CONST_32                      __attribute__(( aligned(4) ))
#   define T1_SEC_NEAR_NO_INIT_32               __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32                    __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER        __attribute__(( aligned(4) ))
#   define T1_SEC_CONST_32_CORE0                __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_CORE0              __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE0  __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE0          __attribute__(( aligned(64) ))
#   define T1_SEC_CONST_32_CORE1                __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_CORE1              __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE1  __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE1          __attribute__(( aligned(64) ))
#   define T1_SEC_CONST_32_CORE2                __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_CORE2              __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE2  __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE2          __attribute__(( aligned(64) ))
#   define T1_SEC_CONST_32_CORE3                __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_CORE3              __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE3  __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE3          __attribute__(( aligned(64) ))
#   define T1_SEC_CONST_32_CORE4                __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_CORE4              __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE4  __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE4          __attribute__(( aligned(64) ))
#   define T1_SEC_CONST_32_CORE4                __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_CORE5              __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE5  __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE5          __attribute__(( aligned(64) ))
#   define T1_SEC_CONST_32_CORE6                __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_CORE6              __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE6  __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE6          __attribute__(( aligned(64) ))
#   define T1_SEC_CONST_32_CORE7                __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_CORE7              __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE7  __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE7          __attribute__(( aligned(64) ))
#   define T1_SEC_CONST_32_CORE8                __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_CORE8              __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE8  __attribute__(( aligned(4) ))
#   define T1_SEC_NO_INIT_32_DCX_CORE8          __attribute__(( aligned(64) ))
#   define T1_SEC_NO_INIT_32_CLONE              __attribute__(( aligned(4) ))
#   define T1_ALIGN_VAR( bytes_ )               __attribute__(( aligned(bytes_) ))

#endif /* compiler */

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

typedef unsigned long                           T1_icuRegister_t;

#endif /* T1_TARGETSPECIFICS_H_ */
