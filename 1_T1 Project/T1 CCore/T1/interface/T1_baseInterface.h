/************************************************************************************/
/*! \file           T1_baseInterface.h
 *
 *  \brief          T1.base interface declarations and macros
 *
 *  \par Visibility
 *                  External
 *
 *  \author alexandrebau
 *
 *  \version 3.5.0.0 r67434
 *
 *  \copyright GLIWA embedded systems GmbH & Co. KG, Weilheim i.OB. All rights reserved
 ************************************************************************************/

#ifndef T1_BASE_INTERFACE_H_
#define T1_BASE_INTERFACE_H_ ( 1 )

/*!
 * \defgroup T1_base T1.base
 * \brief    Provides basic services for all T1 plugins
 *
 * see \ref T1_base_page
 *
 * @{
 */

/*!
 * \defgroup T1_base_interfaces Interface Functions
 * \brief    Functions and function like macros to interface with T1.base during
 *           runtime.
 * \ingroup  T1_base
 */

/*!
 * \defgroup T1_base_cert_interfaces T1-TARGET-SW-CERT Only Interface Functions
 * \ingroup  T1_base
 * \brief    Functions and function like macros to interface with T1.base during
 *           runtime.
 * \details  These are only functional in T1-TARGET-SW-CERT releases, it is
 *           however safe to call them in normal T1-TARGET-SW releases.
 */

/*!
 * \defgroup T1_base_callbacks User Callbacks
 * \brief    User callbacks provide notifications, which might be used by other SW
 *           components or the T1 integration itself.
 * \ingroup  T1_base
 */

/*!
 * \defgroup T1_base_callouts Callouts
 * \brief    Callouts are used to implement functionality, that can not be implemented
 *           as part of the T1-TARGET-SW library code.
 * \ingroup  T1_base
 */

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/* Set default single-core T1_GetCoreIdOffset before including T1_targetSpecifics.h */
#if !defined T1_GetCoreIdOffset && 1 == T1_NOF_CORES
#    define T1_GetCoreIdOffset( ) ( 0u )
#endif /* !defined T1_GetCoreIdOffset && 1 == T1_NOF_CORES */

#include "T1_targetSpecifics.h"

/*----------------------------------------------------------------------------------*/
/*--- macros -----------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#ifndef T1_EXTERN
#    if defined __cplusplus
#        define T1_EXTERN extern "C"
#    else
#        define T1_EXTERN extern
#    endif
#endif

#ifndef T1_FAR
#    define T1_FAR
#endif

#ifndef T1_FARPTR
#    define T1_FARPTR *
#endif

#ifdef T1_NEAR
#    define T1_USE_NEAR ( 1 )
#else
#    define T1_USE_NEAR ( 0 )
#    define T1_NEAR
#endif

#ifndef T1_NEARPTR
#    define T1_NEARPTR *
#endif

#ifndef T1_INSTRUCTION_REORDER_BARRIER
#    if defined T1_CHECKER_ARTEFACT
#        define T1_INSTRUCTION_REORDER_BARRIER( ) ( (void)0 )
#    elif defined __GNUC__ && !defined __ARMCC_VERSION /* Keil */
#        define T1_INSTRUCTION_REORDER_BARRIER( ) __asm( "" : : : "memory" )
#    else
#        define T1_INSTRUCTION_REORDER_BARRIER( ) __asm( "" )
#    endif
#endif

#ifndef T1_NULL
#    define T1_NULL ( (void *)0 )
#endif

#ifdef T1_DEBUG
#    define T1_MAYBE_INLINE /* Disable inlining for debugging */
#else
#    define T1_MAYBE_INLINE T1_INLINE
#endif /* defined T1_DEBUG */

#ifndef T1_NOINLINE
#    define T1_NOINLINE
#endif

#if defined T1_SEC_CONST_32
#    if defined T1_CHECKER_ARTEFACT
#        undef T1_SEC_CONST_32
#        define T1_SEC_CONST_32
#    endif /* defined T1_CHECKER_ARTEFACT */
#else      /* !defined T1_SEC_CONST_32 */
#    define T1_SEC_CONST_32
#endif /* defined T1_SEC_CONST_32 */

#ifndef T1_SEC_CONST_16
#    define T1_SEC_CONST_16
#endif

#ifndef T1_SEC_CONST_8
#    define T1_SEC_CONST_8
#endif

#ifndef T1_CLONE_SEC_CONST_32
#    define T1_CLONE_SEC_CONST_32
#endif

#ifndef T1_CLONE_SEC_CONST_16
#    define T1_CLONE_SEC_CONST_16
#endif

#ifndef T1_CLONE_SEC_CONST_8
#    define T1_CLONE_SEC_CONST_8
#endif

#ifndef T1_SEC_VAR_CLEARED_32
#    define T1_SEC_VAR_CLEARED_32
#endif

#if defined T1_CODE
#    if defined T1_CHECKER_ARTEFACT
#        undef T1_CODE
#        define T1_CODE
#    endif /* defined T1_CHECKER_ARTEFACT */
#else      /* !defined T1_CODE */
#    define T1_CODE
#endif /* defined T1_CODE */

#ifndef T1_CORE0_CODE
#    define T1_CORE0_CODE
#endif

#ifndef T1_CORE1_CODE
#    define T1_CORE1_CODE
#endif

#ifndef T1_CORE2_CODE
#    define T1_CORE2_CODE
#endif

#ifndef T1_CORE3_CODE
#    define T1_CORE3_CODE
#endif

#ifndef T1_CORE4_CODE
#    define T1_CORE4_CODE
#endif

#ifndef T1_CORE5_CODE
#    define T1_CORE5_CODE
#endif

#ifndef T1_CORE6_CODE
#    define T1_CORE6_CODE
#endif

#ifndef T1_CORE7_CODE
#    define T1_CORE7_CODE
#endif

#ifndef T1_CORE8_CODE
#    define T1_CORE8_CODE
#endif

#ifndef T1_CORE9_CODE
#    define T1_CORE9_CODE
#endif

#ifndef T1_CORE10_CODE
#    define T1_CORE10_CODE
#endif

#ifndef T1_CORE11_CODE
#    define T1_CORE11_CODE
#endif

#ifndef T1_CORE12_CODE
#    define T1_CORE12_CODE
#endif

#ifndef T1_CORE13_CODE
#    define T1_CORE13_CODE
#endif

#ifndef T1_CORE14_CODE
#    define T1_CORE14_CODE
#endif

#if defined T1_FAR_CODE
#    if defined T1_CHECKER_ARTEFACT
#        undef T1_FAR_CODE
#        define T1_FAR_CODE( type_ ) type_
#    endif /* defined T1_CHECKER_ARTEFACT */
#else      /* !defined T1_FAR_CODE */
#    define T1_FAR_CODE( type_ ) type_ T1_CODE
#endif /* defined T1_FAR_CODE */

#if defined T1_CODE_FAST
#    if defined T1_CHECKER_ARTEFACT
#        undef T1_CODE_FAST
#        define T1_CODE_FAST( type_ ) type_
#    endif /* defined T1_CHECKER_ARTEFACT */
#else      /* !defined T1_CODE_FAST */
#    define T1_CODE_FAST( type_ ) type_ T1_CODE
#endif /* defined T1_CODE_FAST */

#if defined T1_NEAR_CODE_FAST && defined T1_CHECKER_ARTEFACT
#    undef T1_NEAR_CODE_FAST
#endif /* defined T1_NEAR_CODE_FAST && defined T1_CHECKER_ARTEFACT */

#ifndef T1_CODE_OPT
#    define T1_CODE_OPT
#endif

#ifndef T1_TRACEBUFFER_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE0_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE0_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE1_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE1_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE2_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE2_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE3_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE3_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE4_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE4_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE5_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE5_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE6_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE6_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE7_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE7_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE8_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE8_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE9_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE9_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE10_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE10_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE11_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE11_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE12_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE12_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE13_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE13_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_TRACEBUFFER_CORE14_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_TRACEBUFFER_CORE14_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE0_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE0_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE1_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE1_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE2_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE2_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE3_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE3_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE4_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE4_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE5_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE5_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE6_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE6_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE7_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE7_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE8_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE8_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE9_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE9_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE10_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE10_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE11_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE11_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE12_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE12_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE13_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE13_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CHECKED_CORE14_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CHECKED_CORE14_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#    define T1_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE0_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE0_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE1_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE1_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE2_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE2_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE3_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE3_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE4_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE4_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE5_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE5_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE6_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE6_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE7_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE7_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE8_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE8_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE9_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE9_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE10_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE10_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE11_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE11_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE12_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE12_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE13_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE13_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE14_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE14_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE0_SEC_CONST_32
#    define T1_CORE0_SEC_CONST_32
#endif

#ifndef T1_CORE1_SEC_CONST_32
#    define T1_CORE1_SEC_CONST_32
#endif

#ifndef T1_CORE2_SEC_CONST_32
#    define T1_CORE2_SEC_CONST_32
#endif

#ifndef T1_CORE3_SEC_CONST_32
#    define T1_CORE3_SEC_CONST_32
#endif

#ifndef T1_CORE4_SEC_CONST_32
#    define T1_CORE4_SEC_CONST_32
#endif

#ifndef T1_CORE5_SEC_CONST_32
#    define T1_CORE5_SEC_CONST_32
#endif

#ifndef T1_CORE6_SEC_CONST_32
#    define T1_CORE6_SEC_CONST_32
#endif

#ifndef T1_CORE7_SEC_CONST_32
#    define T1_CORE7_SEC_CONST_32
#endif

#ifndef T1_CORE8_SEC_CONST_32
#    define T1_CORE8_SEC_CONST_32
#endif

#ifndef T1_CORE9_SEC_CONST_32
#    define T1_CORE9_SEC_CONST_32
#endif

#ifndef T1_CORE10_SEC_CONST_32
#    define T1_CORE10_SEC_CONST_32
#endif

#ifndef T1_CORE11_SEC_CONST_32
#    define T1_CORE11_SEC_CONST_32
#endif

#ifndef T1_CORE12_SEC_CONST_32
#    define T1_CORE12_SEC_CONST_32
#endif

#ifndef T1_CORE13_SEC_CONST_32
#    define T1_CORE13_SEC_CONST_32
#endif

#ifndef T1_CORE14_SEC_CONST_32
#    define T1_CORE14_SEC_CONST_32
#endif

#ifndef T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_16
#    define T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_16
#endif

#ifndef T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE_COMMS_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#    define T1_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#endif

#ifndef T1_SEC_VAR_POWER_ON_CLEARED_16
#    define T1_SEC_VAR_POWER_ON_CLEARED_16
#endif

#ifndef T1_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#    define T1_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE0_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE0_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE1_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE1_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE2_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE2_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE3_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE3_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE4_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE4_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE5_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE5_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE6_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE6_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE7_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE7_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE8_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE8_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE9_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE9_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE10_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE10_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE11_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE11_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE12_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE12_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE13_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE13_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CORE14_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CORE14_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_CLONE_SEC_VAR_POWER_ON_CLEARED_32
#    define T1_CLONE_SEC_VAR_POWER_ON_CLEARED_32
#endif

#ifndef T1_CLONE_SEC_VAR_POWER_ON_CLEARED_16
#    define T1_CLONE_SEC_VAR_POWER_ON_CLEARED_16
#endif

#ifndef T1_CLONE_SEC_VAR_POWER_ON_CLEARED_8
#    define T1_CLONE_SEC_VAR_POWER_ON_CLEARED_8
#endif

#ifndef T1_STRING
#    define T1_STRING T1_SEC_CONST_8
#endif

#ifndef T1_UNUSED
#    define T1_UNUSED( varDecl_ ) varDecl_
#endif

#ifndef T1_ALIGN_32
#    define T1_ALIGN_32 T1_ALIGN_VAR( 4 )
#endif

#if !defined T1_NOP
#    if defined T1_CHECKER_ARTEFACT
#        define T1_NOP( ) ( (void)0 )
#    elif defined __GNUC__ && !defined __ARMCC_VERSION /* Keil */
#        define T1_NOP( ) __asm volatile( "nop" : )
#    else
#        define T1_NOP( ) __asm( " nop" )
#    endif
#endif /* defined T1_NOP */

#if !defined T1_MULT_U32_U32_U32
#    define T1_MULT_U32_U32_U32( x_, y_, z_, shift_ )                                \
        ( (T1_uint32_t)( ( ( ( ( x_ ) * (T1_uint64_t)( y_ ) ) >> 32 )                \
                           + ( x_ ) * ( z_ ) )                                       \
                         >> ( (shift_)-32 ) ) )
#endif /* defined T1_MULT_U32_U32_U32 */

#if !defined T1_INSERT32
#    define T1_INSERT32( dst_, ins_, offst_, len_ )                                  \
        ( ( (T1_uint32_t)( dst_ )                                                    \
            & ~( ( 0xFFFFFFFFuL >> ( 32 - ( len_ ) ) ) << ( offst_ ) ) )             \
          | ( ( (T1_uint32_t)( ins_ ) & ( 0xFFFFFFFFuL >> ( 32 - ( len_ ) ) ) )      \
              << ( offst_ ) ) )
#endif

#if !defined T1_INSERT32_OR
#    define T1_INSERT32_OR( dst_, ins_, offst_, len_ )                               \
        ( (T1_uint32_t)( dst_ )                                                      \
          | ( ( (T1_uint32_t)( ins_ ) & ( 0xFFFFFFFFuL >> ( 32 - ( len_ ) ) ) )      \
              << ( offst_ ) ) )
#endif

#if !defined T1_INSERT64
#    define T1_INSERT64( dst_, ins_, offst_, len_ )                                  \
        ( ( (T1_uint64_t)( dst_ )                                                    \
            & ~( ( 0xFFFFFFFFFFFFFFFFuLL >> ( 64 - ( len_ ) ) ) << ( offst_ ) ) )    \
          | ( ( (T1_uint64_t)( ins_ )                                                \
                & ( 0xFFFFFFFFFFFFFFFFuLL >> ( 64 - ( len_ ) ) ) )                   \
              << ( offst_ ) ) )
#endif

#if !defined T1_INSERT64_OR
#    define T1_INSERT64_OR( dst_, ins_, offst_, len_ )                               \
        ( (T1_uint64_t)( dst_ )                                                      \
          | ( ( (T1_uint64_t)( ins_ )                                                \
                & ( 0xFFFFFFFFFFFFFFFFuLL >> ( 64 - ( len_ ) ) ) )                   \
              << ( offst_ ) ) )
#endif

#if !defined T1_ROTL32
#    define T1_ROTL32( x_, y_ )                                                      \
        T1_INSERT32_OR( ( x_ ) >> ( 32 - ( y_ ) ), ( x_ ), ( y_ ), ( 32 - ( y_ ) ) )
#endif

/*! \brief Declare a plugin for use in #T1_DeclarePluginTable. */
#define T1_DeclarePlugin( x_ )                                                       \
    T1_EXTERN struct T1_pluginStruct const T1_SEC_CONST_32( x_ )
/*! \brief Declare a plugin table for use in T1_Init. */
#define T1_DeclarePluginTable( x_ ) T1_EXTERN T1_pluginTable_t T1_SEC_CONST_32( x_ )
#define T1_DISABLED_PLUGIN          ( (T1_pPlugin_t)-1 )

#define T1_BASE_PLUGIN_ID           ( 0u )
#define T1_POSIX_PLUGIN_ID          ( 6u )

#define T1_GCP_STD_MSG_BYTES        ( 8u )

/*----------------------------------------------------------------------------------*/
#ifdef T1_ENABLE
/*! \brief T1.base entry in plugin table. */
#    define T1_basePlugin  ( &T1_basePluginStruct )
#    define T1_posixPlugin ( &T1_posixPluginStruct )
#else /* !defined T1_ENABLE */
#    define T1_basePlugin ( T1_DISABLED_PLUGIN )
#endif /* defined T1_ENABLE */

/*!
 * \defgroup T1_base_returncodes Return Codes
 * \brief    Return codes used by different T1-TARGET-SW interface functions.
 *
 * Details are provided with the description of the interface functions.
 *
 * @{
 */

/*! \brief return codes with this bit set indicate an error */
#define T1_ERR_MASK                ( (T1_status_t)0x80u )
/*! \brief return true if and only if the input code indicates an error */
#define T1_IS_ERROR( errCode_ )    ( ( (errCode_)&T1_ERR_MASK ) == T1_ERR_MASK )

/*! \brief the service completed correctly */
#define T1_OK                      ( (T1_status_t)0x00u )
#define T1_YES                     ( (T1_status_t)0x01u )
#define T1_NO                      ( (T1_status_t)0x02u )

/*! \brief the service did not perform any action */
#define T1_NOFUNC                  ( (T1_status_t)0x03u )

/* the following return codes indicate the execution of the service failed */
/*! \brief the service failed in a way not described by a more specific code */
#define T1_FAILED                  ( (T1_status_t)0x80u )
/*! \brief T1_Handler() or T1_ContBgHandler() has been re-entered */
#define T1_BUSY                    ( (T1_status_t)0x81u )
/*! \brief T1_Handler() has been called before T1_Init() */
#define T1_NOTINITIALIZED          ( (T1_status_t)0x82u )
/*! \brief the service did not perform any action because its plugin is disabled */
#define T1_PLUGIN_NOT_AVAILABLE    ( (T1_status_t)0x83u )
/*! \brief an invalid input was supplied to the service */
#define T1_VALUE                   ( (T1_status_t)0x84u )
#define T1_INVALID_COMMAND         ( (T1_status_t)0x85u )
#define T1_NOT_IN_PRIVILEGED_MODE  ( (T1_status_t)0x86u )
#define T1_INVALID_ACCESS_MASK     ( (T1_status_t)0x87u )
#define T1_NOT_SUPPORTED_BY_TARGET ( (T1_status_t)0x88u )
#define T1_EXTERNAL_DEBUG          ( (T1_status_t)0x89u )
/**@}*/

#ifdef T1_ENABLE

/* Access macros for pluginsEnabledMask */
#    define T1_ENABLE_PLUGIN( baseGlobals_, pluginIdx_ )                             \
        ( ( baseGlobals_ ).pluginsEnabledMask |= ( 1u << pluginIdx_ ) >> 1 )
#    define T1_DISABLE_PLUGIN( baseGlobals_, pluginIdx_ )                            \
        ( ( baseGlobals_ ).pluginsEnabledMask &= ~( 1u << pluginIdx_ ) >> 1 )
#    define T1_IS_PLUGIN_ENABLED( baseGlobals_, pluginIdx )                          \
        ( 0u                                                                         \
          != ( ( 1u << pluginIdx ) & T1_GET_PLUGINS_ENABLED_MASK( baseGlobals_ ) ) )
#    define T1_GET_PLUGINS_ENABLED_MASK( baseGlobals_ )                              \
        ( ( ( ( baseGlobals_ ).pluginsEnabledMask << 1 ) | 1u ) & ALL_PLUGINS_MASK )
#    define ALL_PLUGINS_MASK ( ( 1u << T1_NOF_PLUGINS ) - 1 )

/*!
 * \def     T1_IsT1FlexEnabled
 * \brief   Test if the T1.flex is enabled on the T1 logical core ID of the calling
 * core. \ingroup T1_base_interfaces \returns non-zero if T1.flex is enabled.
 */

/*!
 * \def     T1_IsT1FlexEnabledPC
 * \brief   Test if the T1.flex is enabled.
 * \ingroup T1_base_interfaces
 * \param[in] coreId_ The T1 logical core ID of the calling core, see \ref PC
 * \returns non-zero if T1.flex is enabled.
 */
#    if defined T1_DISABLE_T1_FLEX
#        define T1_IsT1FlexEnabled( )           ( T1_FALSE )
#        define T1_IsT1FlexEnabledPC( coreId_ ) ( T1_FALSE )
#    else /* !defined T1_DISABLE_T1_FLEX */
#        define T1_IsT1FlexEnabled( ) T1_isT1FlexEnabledPC( T1_GetCoreIdOffset( ) )
#        define T1_IsT1FlexEnabledPC( coreId_ )                                      \
            T1_IS_PLUGIN_ENABLED( *( T1_baseGlobalsPC[coreId_] ), T1_FLEX_PLUGIN_ID )
#    endif /* defined T1_DISABLE_T1_FLEX */

/*!
 * \brief   Test if the given feature(mask) is enabled, see \ref APP_FEATURES.
 * \ingroup T1_base_interfaces
 * \param[in] mask_ the feature (mask) value
 * \returns non-zero if the feature mask is enabled.
 */
#    define T1_IsFeatureEnabled( mask_ )                                             \
        ( ( T1_featureMask & (T1_featureMask_t)( mask_ ) ) != 0uL )

/*!
 * \brief Define a T1-TARGET-SW plugin table with the given name.
 * See \ref SWITCH_PLUGINS.
 */
#    define T1_ALLOCATE_PLUGIN_TABLE( pluginTable_ )                                 \
        T1_pluginTable_t( pluginTable_ ) T1_SEC_CONST_32 = { T1_basePlugin,          \
                                                             T1_scopePlugin,         \
                                                             T1_flexPlugin,          \
                                                             T1_delayPlugin,         \
                                                             T1_modPlugin,           \
                                                             T1_contPlugin,          \
                                                             T1_DISABLED_PLUGIN };

/*!
 * \brief Define a T1-TARGET-SW plugin table with the given name.
 * Regardless of #T1_DISABLE_T1_FLEX, T1.flex is never enabled,
 * see \ref SWITCH_PLUGINS.
 */
#    define T1_ALLOCATE_PLUGIN_TABLE_NO_T1_FLEX( pluginTable_ )                      \
        T1_pluginTable_t( pluginTable_ ) T1_SEC_CONST_32 = { T1_basePlugin,          \
                                                             T1_scopePlugin,         \
                                                             T1_DISABLED_PLUGIN,     \
                                                             T1_delayPlugin,         \
                                                             T1_modPlugin,           \
                                                             T1_contPlugin,          \
                                                             T1_DISABLED_PLUGIN };

/*!
 * \brief Define a T1-TARGET-SW plugin table with the given name.
 * Regardless of #T1_DISABLE_T1_CONT, T1.cont is never enabled,
 * see \ref SWITCH_PLUGINS.
 */
#    define T1_ALLOCATE_PLUGIN_TABLE_NO_T1_CONT( pluginTable_ )                      \
        T1_pluginTable_t( pluginTable_ ) T1_SEC_CONST_32 = { T1_basePlugin,          \
                                                             T1_scopePlugin,         \
                                                             T1_flexPlugin,          \
                                                             T1_delayPlugin,         \
                                                             T1_modPlugin,           \
                                                             T1_DISABLED_PLUGIN,     \
                                                             T1_DISABLED_PLUGIN };

#    define T1_ALLOCATE_PLUGIN_TABLE_T1_POSIX( pluginTable_ )                        \
        T1_pluginTable_t( pluginTable_ ) T1_SEC_CONST_32 = { T1_basePlugin,          \
                                                             T1_scopePlugin,         \
                                                             T1_DISABLED_PLUGIN,     \
                                                             T1_delayPlugin,         \
                                                             T1_DISABLED_PLUGIN,     \
                                                             T1_DISABLED_PLUGIN,     \
                                                             T1_posixPlugin };

#    define T1_NOF_PLUGINS    ( 7u )
#    define T1_CAT_( x_, y_ ) x_##y_
#    define T1_CAT( x_, y_ )  T1_CAT_( x_, y_ )

#else /* !defined T1_ENABLE */

#    define T1_IsFeatureEnabled( mask_ ) ( 0 )
#    define T1_ALLOCATE_PLUGIN_TABLE( pluginTable_ )

#endif /* defined T1_ENABLE */

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*!
 * \typedef T1_uint8Least_t
 * \brief Unsigned integer with at least 8 bits. No modulo 256 arithmetic!
 */
/*!
 * \typedef T1_uint16Least_t
 * \brief Unsigned integer with at least 16 bits. No modulo 65536 arithmetic!
 */
/*!
 * \typedef T1_uint32Least_t
 * \brief Unsigned integer with at least 32 bits. No modulo 4294967296 arithmetic!
 */

/* Usually platform independent */
typedef char T1_char_t;             //!< Used only for strings
typedef signed char T1_sint8_t;     //!< Signed 8-bit integer
typedef unsigned char T1_uint8_t;   //!< Unsigned 8-bit integer
typedef signed short T1_sint16_t;   //!< Signed 16-bit integer
typedef unsigned short T1_uint16_t; //!< Unsigned 16-bit integer

#if defined T1_CPU8BIT /* CPU has 8-bit registers */
/*!
 * \def T1_CPU8BIT
 * \brief Internal: If defined, the CPU uses 8-bit registers.
 */
typedef unsigned long T1_uint32_t; //!< Unsigned 32-bit integer
typedef signed long T1_sint32_t;   //!< Signed 32-bit integer
typedef T1_uint8_t T1_uint8Least_t;
typedef T1_sint8_t T1_sint8Least_t;
typedef T1_uint16_t T1_uint16Least_t;
typedef T1_sint16_t T1_sint16Least_t;
typedef T1_uint32_t T1_uint32Least_t;
#elif defined T1_CPU16BIT /* CPU has 16-bit registers and no 8-bit registers */
/*!
 * \def T1_CPU16BIT
 * \brief Internal: If defined, the CPU uses 16-bit registers.
 */
typedef unsigned long T1_uint32_t; //!< Unsigned 32-bit integer
typedef signed long T1_sint32_t;   //!< Signed 32-bit integer
typedef T1_uint16_t T1_uint8Least_t;
typedef T1_sint16_t T1_sint8Least_t;
typedef T1_uint16_t T1_uint16Least_t;
typedef T1_sint16_t T1_sint16Least_t;
typedef T1_uint32_t T1_uint32Least_t;
#elif defined T1_CPU32BIT || defined T1_CPU64BIT
typedef unsigned int T1_uint32_t; //!< Unsigned 32-bit integer
typedef signed int T1_sint32_t;   //!< Signed 32-bit integer
typedef T1_uint32_t T1_uint8Least_t;
typedef T1_sint32_t T1_sint8Least_t;
typedef T1_uint32_t T1_uint16Least_t;
typedef T1_sint32_t T1_sint16Least_t;
typedef unsigned long long T1_uint64_t; //!< Unsigned 64-bit integer
#    if defined T1_CPU32BIT
/*!
 * \def T1_CPU32BIT
 * \brief Internal: If defined, the CPU uses 32-bit registers.
 */
typedef T1_uint32_t T1_uint32Least_t;
#    else  /* 64-bit CPU */
/*!
 * \def T1_CPU64BIT
 * \brief Internal: If defined, the CPU uses 64-bit registers and 32-bit registers.
 */
typedef T1_uint64_t T1_uint32Least_t;
#    endif /* defined T1_CPU32BIT */
#else
#    error T1_CPU<n>BIT not defined
#endif

typedef T1_uint16_t T1_tick_t;          //!< Used for storage
typedef T1_uint16Least_t T1_tickUint_t; //!< Never used for storage

/*! \brief T1-TARGET-SW boolean type. */
typedef T1_uint8_t T1_bool_t;
/*! \brief T1-TARGET-SW boolean true value. */
#define T1_TRUE  ( (T1_bool_t)1u )
/*! \brief T1-TARGET-SW boolean false value. */
#define T1_FALSE ( (T1_bool_t)0u )

/*! \brief Return value from some T1-TARGET-SW API calls and callbacks. */
typedef T1_uint8Least_t T1_status_t;

/*! \brief Size of frames passed in T1_TransmitFrame() and T1_ReceiveFrame(). */
typedef T1_uint16_t T1_frameSize_t;

/*! \brief Internal: void-void function pointer used in T1_configGen.c. */
typedef void ( *T1_pVoidVoid_t )( void );

/*----------------------------------------------------------------------------------*/
/*! \brief Internal: Unique plugin identifier. */
typedef T1_uint8_t T1_pluginID_t;
/*----------------------------------------------------------------------------------*/
/* polyspace<MISRA-C3:1.3:Low:Justified> A structure forward declaration is intentional for information hiding */
struct T1_pluginStruct;
/*! \brief Internal: Pointer to const plugin data. */
typedef struct T1_pluginStruct const *T1_pPlugin_t;
#if defined T1_ENABLE
/*! \brief Internal: All plugins, whether enabled or not. */
typedef T1_pPlugin_t const T1_pluginTable_t[T1_NOF_PLUGINS];
#endif /* defined T1_ENABLE */
/*----------------------------------------------------------------------------------*/
/*! \brief Internal: Type for T1_featureMask. */
typedef T1_uint32_t T1_featureMask_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Type for T1_timeouts. */
typedef struct
{
    T1_uint16_t gcpRx;
    T1_uint16_t gcpTx;
    T1_uint16_t t1response;
} T1_timeouts_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Internal: Aligned container passed between T1-TARGET-SW and GCP. */
typedef union {
    T1_uint8_t u8[T1_GCP_STD_MSG_BYTES];
    T1_uint16_t u16[T1_GCP_STD_MSG_BYTES / 2];
    void *pAlignmentDummy[2];
} T1_fakeGcpBuf_t;
/*----------------------------------------------------------------------------------*/
/*! \brief Internal: Callback after successful packet transmission. */
typedef void ( *T1_pTxComplete_t )( T1_uint8Least_t coreId );
/*----------------------------------------------------------------------------------*/
/*! \brief T1.base global data for one core. */
typedef struct
{
    T1_uint8_t txBufferState;    //!< State machine for transmission
    T1_uint8_t gcpTid;           //!< GCP Target-ID
    T1_uint16_t responseTimeout; //!< Timeout on reaching zero
    T1_uint16_t txState;         //!< T1.base transmit queue
    T1_bool_t
#if !defined T1_CHECKER_ARTEFACT
        volatile
#endif                             /* defined T1_CHECKER_ARTEFACT */
        locked;                    //!< Lock out T1_Handler()
    T1_uint8_t pluginsEnabledMask; //!< One bit set per plugin, using its ID - 1
    T1_fakeGcpBuf_t txBuffer;      //!< Transmit interface with GCP
    T1_fakeGcpBuf_t rxBuffer;      //!< Receive interface with GCP
    T1_uint8_t pluginLicFragToTxId;
    T1_uint8_t volatile interruptNestCount; //!< Used by T1_SuspendAllInterrupts()
    T1_uint16_t txValue;                    //!< Queued data from T1_TxValue()
    T1_uint16_t checkSum;
    T1_uint16_t unused16;                                    //!< force alignment
    struct T1_pluginStruct const * const *activePluginTable; //!< Plugin table
    T1_pTxComplete_t pTxCompleteFn;
#if defined T1_ALLOC_GLOBAL_VAR
    T1_icuRegister_t savedIcuRegister; //!< Used by T1_SuspendAllInterrupts()
#endif                                 /* defined T1_ALLOC_GLOBAL_VAR */
    T1_uint16_t initTime;
    T1_uint8_t txValueState;      //!< State machine for txValue queue
    T1_bool_t featureMaskChanged; //!< Flag until T1_FeatureMaskChangedPC()
#if defined T1_CPU64BIT
    T1_uint32_t align32; //!< force alignment
#endif                   /* defined T1_CPU64BIT */
} T1_baseGlobals_t;

/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#ifdef T1_ENABLE

#    if defined T1_NO_INIT_SID
#        define T1_START_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"
T1_EXTERN T1_uint8_t T1_SEC_VAR_POWER_ON_CLEARED_8 T1_sid;
#        define T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#        include "T1_MemMap.h"
#    else /* !defined T1_NO_INIT_SID */
#        define T1_START_SEC_CONST_8
#        include "T1_MemMap.h"
T1_EXTERN const T1_uint8_t T1_SEC_CONST_8 T1_sid;
#        define T1_STOP_SEC_CONST_8
#        include "T1_MemMap.h"
#    endif /* defined T1_NO_INIT_SID */

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_DeclarePlugin( T1_basePluginStruct );
T1_DeclarePlugin( T1_posixPluginStruct );
T1_EXTERN const T1_uint32_t T1_SEC_CONST_32 T1_baseRevision;
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_EXTERN const T1_featureMask_t T1_SEC_CONST_32 T1_initFeatureMask;
T1_EXTERN T1_uint8_t const * const T1_SEC_CONST_32 T1_pBid;
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    define T1_START_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"
/* clang-format off */
/*! \brief Internal: Feature bit mask shared by all cores. See T1_IsFeatureEnabled() and \ref APP_FEATURES. */
/* clang-format on */
T1_EXTERN T1_featureMask_t T1_SEC_VAR_POWER_ON_CLEARED_32 T1_featureMask;
#    define T1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_8
#    include "T1_MemMap.h"

#    if defined T1_CPU32BIT || defined T1_CPU64BIT
T1_EXTERN const T1_uint8_t T1_SEC_CONST_8 T1_traceTimerBitLength;
T1_EXTERN const T1_uint8_t T1_SEC_CONST_8 T1_traceTimerBitLengthPC[];
#    endif /* defined T1_CPU32BIT || defined T1_CPU64BIT */

T1_EXTERN const T1_uint8_t T1_SEC_CONST_8 T1_nOfCores;
T1_EXTERN const T1_uint8_t T1_SEC_CONST_8 T1_commsCoreOffset;

#    define T1_STOP_SEC_CONST_8
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_16
#    include "T1_MemMap.h"
/* clang-format off */
/*! \brief GCP and T1-TARGET-SW timeout values as multiples of the T1_Handler period. */
/* clang-format on */
T1_EXTERN const T1_timeouts_t T1_SEC_CONST_16 T1_timeouts;
T1_EXTERN const T1_uint16_t T1_SEC_CONST_16 T1_featureMaskCallbackMask;
#    define T1_STOP_SEC_CONST_16
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_16
#    include "T1_MemMap.h"
/* polyspace<MISRA-C3:8.5:Not a defect:Justified> double declarations facilitate implementations */
T1_EXTERN const T1_frameSize_t T1_SEC_CONST_16 T1_maxTxFrameBytes;
/* polyspace<MISRA-C3:8.5:Not a defect:Justified> double declarations facilitate implementations */
T1_EXTERN const T1_frameSize_t T1_SEC_CONST_16 T1_maxRxFrameBytes;
#    define T1_STOP_SEC_CONST_16
#    include "T1_MemMap.h"

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
/*!
 * \brief Build ID uniquely identifies each linked ELF file.
 *
 * The build ID guards against a mismatch between the executing code and the
 * ELF file used by the T1-HOST-SW for translation between symbol names and addresses.
 * Ideally this should be generated every time an ELF file is linked but typically
 * it is only generated when the T1 configuration scripts are executed.
 */
T1_EXTERN const T1_uint32_t T1_SEC_CONST_32 T1_bid;
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    if defined T1_MULTICORE_CLONE

#        define T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_baseGlobals_t T1_CLONE_SEC_VAR_POWER_ON_CLEARED_32 T1_baseGlobals;
#        define T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"

#    else /* !defined T1_MULTICORE_CLONE */

#        define T1_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_baseGlobals_t * const T1_SEC_CONST_32 T1_baseGlobalsPC[];
#        define T1_STOP_SEC_CONST_32
#        include "T1_MemMap.h"

#    endif /* defined T1_MULTICORE_CLONE */

#endif /* defined T1_ENABLE */

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for global functions ------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_START_SEC_CODE
#include "T1_MemMap.h"

/*!
 * \internal
 * \brief Forwards received payload to the T1-TARGET-SW.
 */
T1_EXTERN T1_status_t T1_CODE T1_ReceiveFrame_( T1_uint8_t const T1_FARPTR pData,
                                                T1_frameSize_t nOfBytes );

/*!
 * \brief   Forwards received payload to the T1-TARGET-SW.
 * \ingroup T1_base_interfaces
 * \retval  The current version of T1_ReceiveFrame always returns #T1_OK.
 * \param[in] pData_    Pointer to the received payload. The referenced data will not
 *                     actually be read until the next T1_Handler(), so the data must
 *                     be buffered.
 * \param[in] nOfBytes_ Size in bytes of the received payload
 *
 * Note that, on a multi-core processor, the target side of the target interface is
 * serviced by just one core, the communication core. This means that T1_ReceiveFrame
 * must be called only on that communication core only.
 *
 * - The T1 communication core can be configured with the invocation file
 *   parameter [-commsCoreOffset](@ref commsCoreOffset).
 * - The configured T1 communication core can be determined by reading
 *   - the macro #T1_COMMS_CORE_OFFSET, or
 *   - the constant #T1_commsCoreOffset
 */
#define T1_ReceiveFrame( pData_, nOfBytes_ )                                         \
    ( (void)T1_ReceiveFrame_( ( pData_ ), ( nOfBytes_ ) ), T1_OK )

/*!
 * \brief Callback function to transmit frame data.
 *
 * Called by T1_HandlerPC()
 *
 * \ingroup T1_base_callbacks
 * \param[in] pData    pointer to the data the T1-TARGET-SW wants to send
 * \param[in] nOfBytes size of the frame that the T1-TARGET-SW wants to send in bytes
 * \par Default Implementation
 * This function only needs to be modified if a different buffering system is
 * required. In this default implementation, we use #T1_txFrameBuffer and
 * #T1_txFrameBufferAllocated. See T1_TxBufferRequest().
 *
 */
T1_EXTERN T1_status_t T1_CODE T1_TransmitFrame( T1_uint8_t const T1_FARPTR pData,
                                                T1_frameSize_t nOfBytes );

/*!
 * \brief Callback function to (re)initialize communications.
 * \ingroup T1_base_callbacks
 *
 * Called by T1_InitPC() and T1_HandlerPC()
 *
 * \par Default Implementation
 * This function only needs to be modified if a different buffering system is
 * required. In this default implementation, we initialize #T1_txFrameBufferAllocated.
 * See T1_TransmitFrame().
 *
 */
T1_EXTERN void T1_CODE T1_InitCommunications( void );

/*!
 * \brief Callback function to allocate a frame.
 * \ingroup T1_base_callbacks
 * \param[in] nOfBytes size of the frame that the T1-TARGET-SW wants to allocate
 *                     memory for in bytes
 *
 * Called by T1_HandlerPC()
 *
 * \par Default Implementation
 * This function only needs to be modified if a different buffering system is
 * required. In this default implementation, we use #T1_txFrameBuffer and
 * #T1_txFrameBufferAllocated. See T1_TransmitFrame().
 *
 */
T1_EXTERN T1_uint8_t T1_FARPTR T1_CODE T1_TxBufferRequest( T1_frameSize_t nOfBytes );

/*
 * For safety reasons, the services T1_SuspendAllInterrupts() and
 * T1_ResumeAllInterrupts() are present even if T1_ENABLE is not defined, i.e.
 * T1-TARGET-SW is disabled. Thus, these services are not encapsulated by
 * #ifdef T1_ENABLE / #endif
 *
 * These functions must be able to be nested. For example,
 * T1_SuspendAllInterrupts shall not assume that interrupts
 * are enabled on entry and T1_ResumeAllInterrupts shall not
 * unconditionally enable interrupts.
 *
 * These functions must be able to be called from user mode, unless
 * all T1-TARGET-SW API calls are made at supervisor level.
 *
 * These functions are actually not implemented in the T1-TARGET-SW libraries but in
 * T1_config.c and the default map to T1-TARGET-SW library functions that are
 * simplistic and generally NOT safe from user-mode. During integration, these are
 * typically adapted to map to OS functions, firstly to meet the requirement that they
 * are safe to call from user-mode and secondly to avoid useless code duplication.
 */

/*!
 * \brief Callout function implemented in T1_config.c to inhibit all interrupts.
 *        See \ref PC and \ref INTRPT.
 * \ingroup T1_base_callouts
 * \param[in] coreId the T1 logical ID of the calling core
 *
 * This callout is used by the T1-TARGET-SW to inhibit all interrupts.
 * - It must be possible to nest calls to T1_SuspendAllInterruptsPC().
 * - The callout function T1_ResumeAllInterruptsPC() is used to enable interrupts
 *   after these were disabled by T1_SuspendAllInterruptsPC().
 * - The two callout functions T1_SuspendAllInterruptsPC() and
 *   T1_ResumeAllInterruptsPC() are always called pairwise (calls are balanced).
 *
 * \par Default Implementation
 * The default implementation calls the library function T1_SuspendAllInterruptsPC_().
 * This needs to be changed if T1-TARGET-SW APIs are called from user-mode, as the
 * default implementation might fail to inhibit interrupts from user-mode.
 *
 */
T1_EXTERN void T1_CODE T1_SuspendAllInterruptsPC( T1_uint8Least_t coreId );

/*!
 * \brief   Internal library helper function for default T1_SuspendAllInterruptsPC().
 *          See \ref PC and \ref INTRPT.
 * \ingroup T1_base_interfaces
 * \param[in] coreId the T1 logical ID of the calling core
 *
 * This helper function might fail to inhibit interrupts if called from user-mode.
 *
 */
T1_EXTERN void T1_CODE T1_SuspendAllInterruptsPC_( T1_uint8Least_t coreId );

/*!
 * \brief Callout function implemented in T1_config.c to enable interrupts that have
 *        before been inhibited by T1_SuspendAllInterrupts().
 *        See \ref PC and \ref INTRPT.
 * \ingroup T1_base_callouts
 * \param[in] coreId the T1 logical ID of the calling core
 *
 * Callout function used by the T1-TARGET-SW to enable interrupts that have
 * before been inhibited by T1_SuspendAllInterrupts().
 * - It must be possible to nest calls to T1_ResumeAllInterruptsPC().
 *
 * \par Default Implementation
 * The default implementation calls the library function T1_ResumeAllInterruptsPC_().
 * This needs to be changed if T1-TARGET-SW APIs are called from user-mode, as the
 * default implementation might fail to enable interrupts from user-mode.
 *
 */
T1_EXTERN void T1_CODE T1_ResumeAllInterruptsPC( T1_uint8Least_t coreId );

/*!
 * \brief   Internal library helper function for default T1_ResumeAllInterruptsPC().
 *        See \ref PC and \ref INTRPT.
 * \ingroup T1_base_interfaces
 * \param[in] coreId the T1 logical ID of the calling core
 *
 * This helper function might fail to enable interrupts if called from user-mode.
 *
 */
T1_EXTERN void T1_CODE T1_ResumeAllInterruptsPC_( T1_uint8Least_t coreId );

/*!
 * \brief Inhibit all interrupts.
 *        See T1_SuspendAllInterruptsPC() and \ref INTRPT.
 * \ingroup T1_base_interfaces
 */
#define T1_SuspendAllInterrupts( ) T1_SuspendAllInterruptsPC( T1_GetCoreIdOffset( ) )

/*!
 * \brief Permit interrupts as before T1_SuspendAllInterrupts.
 *        See T1_ResumeAllInterruptsPC() and \ref INTRPT.
 * \ingroup T1_base_interfaces
 */
#define T1_ResumeAllInterrupts( )  T1_ResumeAllInterruptsPC( T1_GetCoreIdOffset( ) )

#ifdef T1_ENABLE

/*!
 * \brief     Call periodically to service communication with T1-HOST-SW. See \ref PC.
 * \ingroup   T1_base_interfaces
 * \param[in] coreId the T1 logical ID of the calling core
 * \returns   #T1_VALUE if an invalid message was received at the last call to
 *            T1_ReceiveFrame(),
 *            #T1_BUSY if T1_HandlerPC() is already running due to unsupported
 *            re-entrancy,
 *            #T1_NOTINITIALIZED if T1_InitPC() has not yet completed,
 *            #T1_OK otherwise
 */
T1_EXTERN T1_status_t T1_CODE T1_HandlerPC( T1_uint8Least_t coreId );

/*!
 * \brief     Call periodically to service communication with T1-HOST-SW. See \ref PC.
 * \ingroup   T1_base_interfaces
 * \returns   #T1_VALUE if an invalid message was received at the last call to
 *            T1_ReceiveFrame(),
 *            #T1_BUSY if T1_Handler() is already running due to unsupported
 *            re-entrancy,
 *            #T1_NOTINITIALIZED if T1_Init() has not yet completed,
 *            #T1_OK otherwise
 */
#    define T1_Handler( ) T1_HandlerPC( T1_GetCoreIdOffset( ) )

/*!
 * \brief     Call, with supervisor privileges, after reset and before any other
 *            T1-TARGET-SW service. See \ref PC and \ref RESBUF.
 * \ingroup   T1_base_interfaces
 * \param[in] coreId      the T1 logical ID of the calling core
 * \param[in] pluginTable the T1-TARGET-SW plugin table
 * \returns   #T1_VALUE if coreId is out of the range defined by T1_NOF_CORES,
 *            #T1_OK otherwise
 */
T1_EXTERN T1_status_t T1_CODE T1_InitPC( T1_uint8Least_t coreId,
                                         T1_pluginTable_t pluginTable );

/*!
 * \brief     Call, with supervisor privileges, after reset and before any other
 *            T1-TARGET-SWservice. See \ref PC and \ref RESBUF.
 * \ingroup   T1_base_interfaces
 * \param[in] pluginTable_ the T1-TARGET-SW plugin table
 * \returns   #T1_OK
 */
#    define T1_Init( pluginTable_ )                                                  \
        T1_InitPC( T1_GetCoreIdOffset( ), ( pluginTable_ ) )

/*
 * T1_DisableT1Handler must inhibit scheduling of the task
 * that calls T1_Handler.
 * T1_EnableT1Handler must restore scheduling again.
 * The default implementations, in T1_config.c disable and
 * reenable interrupts using T1_SuspendAllInterrupts and
 * T1_ResumeAllInterrupts so they have to be modified
 * by the integrator if T1_ContBgHandler is called from
 * contexts without permission to directly disable
 * interrupts. For example, OS resource locks might be
 * used to achieve the required mutual exclusion.
 * For efficiency, they can also be empty functions, if
 * the task that calls T1_Handler cannot, in any case,
 * preempt the background task.
 */
/*!
 * \brief Callout function implemented in T1_config.c to obtain mutual exclusion with
 *        T1_Handler() on the specified core.
 * \ingroup T1_base_callouts
 * \param[in] coreId the core with which to obtain mutual exclusion
 *
 * \par Default Implementation
 * By default maps to T1_SuspendAllInterruptsPC() unless #T1_CONT_REMOTE is defined.
 *
 */
T1_EXTERN void T1_CODE T1_DisableT1HandlerPC( T1_uint8Least_t coreId );

/*!
 * \brief Callout function implemented in T1_config.c to release mutual exclusion with
 *        T1_Handler() on the specified core.
 * \ingroup T1_base_callouts
 * \param[in] coreId the core with which to release mutual exclusion
 *
 * \par Default Implementation
 * By default maps to T1_ResumeAllInterruptsPC() unless #T1_CONT_REMOTE is defined.
 *
 */
T1_EXTERN void T1_CODE T1_EnableT1HandlerPC( T1_uint8Least_t coreId );

/*!
 * Transmit 16-bit data to the T1-HOST-SW as soon as possible, not via the T1.scope
 * trace buffer. You can construct a matching handler at the T1-HOST-SW to react to
 * the data. See \ref PC.
 * \ingroup        T1_base_interfaces
 * \param[in] val_ the value to be transmitted
 * \returns        #T1_FAILED if the transmit buffer is blocked because the previous
 *                 value has not yet been transmitted
 */
#    define T1_TxValue( val_ ) T1_TxValuePC( T1_GetCoreIdOffset( ), ( val_ ) )

/*!
 * Transmit 16-bit data to the T1-HOST-SW as soon as possible, not via the T1.scope
 * trace buffer. You can construct a matching handler at the T1-HOST-SW to react to
 * the data. See \ref PC.
 * \ingroup          T1_base_interfaces
 * \param[in] coreId the T1 logical ID of the calling core
 * \param[in] val    the value to be transmitted
 * \returns          #T1_FAILED if the transmit buffer is blocked because the previous
 *                   value has not yet been transmitted
 */
T1_EXTERN T1_status_t T1_CODE T1_TxValuePC( T1_uint8Least_t coreId, T1_uint16_t val );

/*!
 * \internal
 * \brief   Prepare for T1_InitExtra2().
 * \ingroup T1_base_cert_interfaces
 */
T1_EXTERN void T1_CODE T1_InitExtra1PC_( T1_uint8Least_t coreId );

/*!
 * \internal
 * \brief   Prepare for T1_InitExtra3().
 * \ingroup T1_base_cert_interfaces
 */
T1_EXTERN void T1_CODE T1_InitExtra2PC_( T1_uint8Least_t coreId );

/*!
 * \internal
 * \brief   Enable 'disruptive' plugins.
 * \ingroup T1_base_cert_interfaces
 */
T1_EXTERN void T1_CODE T1_InitExtra3PC_( T1_uint8Least_t coreId );

/*!
 * \brief Prepare for T1_InitExtra2().
 * \ifnot CERT_SECTION
 *   \copydetails T1_base_cert_interfaces
 * \endif
 * \ingroup T1_base_cert_interfaces
 * \details   This is part of the Multi-Step Initialization Procedure
 */
#    define T1_InitExtra1( )           T1_InitExtra1PC_( T1_GetCoreIdOffset( ) )

/*!
 * \brief Prepare for T1_InitExtra3().
 * \ifnot CERT_SECTION
 *   \copydetails T1_base_cert_interfaces
 * \endif
 * \ingroup T1_base_cert_interfaces
 * \details   This is part of the Multi-Step Initialization Procedure
 */
#    define T1_InitExtra2( )           T1_InitExtra2PC_( T1_GetCoreIdOffset( ) )
/*!
 * \brief Enable 'disruptive' plugins.
 * \ifnot CERT_SECTION
 *   \copydetails T1_base_cert_interfaces
 * \endif
 * \ingroup T1_base_cert_interfaces
 * \details   This is part of the Multi-Step Initialization Procedure
 */
#    define T1_InitExtra3( )           T1_InitExtra3PC_( T1_GetCoreIdOffset( ) )

/*!
 * \brief Prepare for T1_InitExtra2PC().
 * \ifnot CERT_SECTION
 *   \copydetails T1_base_cert_interfaces
 * \endif
 * \ingroup T1_base_cert_interfaces
 * \details   This is part of the Multi-Step Initialization Procedure
 * \param[in] coreId_ the T1 logical ID of the calling core
 */
#    define T1_InitExtra1PC( coreId_ ) T1_InitExtra1PC_( coreId_ )

/*!
 * \brief Prepare for T1_InitExtra3PC().
 * \ifnot CERT_SECTION
 *   \copydetails T1_base_cert_interfaces
 * \endif
 * \ingroup T1_base_cert_interfaces
 * \details   This is part of the Multi-Step Initialization Procedure
 * \param[in] coreId_ the T1 logical ID of the calling core
 */
#    define T1_InitExtra2PC( coreId_ ) T1_InitExtra2PC_( coreId_ )

/*!
 * \brief Enable 'disruptive' plugins.
 * \ifnot CERT_SECTION
 *   \copydetails T1_base_cert_interfaces
 * \endif
 * \ingroup T1_base_cert_interfaces
 * \details   This is part of the Multi-Step Initialization Procedure
 * \param[in] coreId_ the T1 logical ID of the calling core
 */
#    define T1_InitExtra3PC( coreId_ ) T1_InitExtra3PC_( coreId_ )

/*!
 * \brief Callback called on a change to #T1_featureMask
 * \ingroup T1_base_callbacks
 * \param[in] coreId      the T1 logical ID of the calling core
 * \param[in] featureMask a "safe" copy of the actual T1_featureMask
 *
 * Called from T1_Handler() on cores for which the invocation parameter
 * [-featureMaskCallback](@ref featureMaskCallback) is set to true when the
 * T1-HOST-SW updates #T1_featureMask. See also T1_IsFeatureEnabled() and
 * \ref APP_FEATURES.
 * Although the core ID is passed as an argument, remember that #T1_featureMask is
 * shared by all cores and do not attempt write #T1_featureMask, as write access would
 * not be thread-safe.
 *
 */
T1_EXTERN void T1_CODE T1_FeatureMaskChangedPC( T1_uint8Least_t coreId,
                                                T1_featureMask_t featureMask );

#else /* !defined T1_ENABLE */

#    define T1_Handler( )                 ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_Init( pPluginTable_ )      ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_TxValue( val_ )            ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_TxValuePC( coreId_, val_ ) ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_InitExtra1( )              ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_InitExtra2( )              ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_InitExtra3( )              ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_InitExtra1PC( coreId_ )    ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_InitExtra2PC( coreId_ )    ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_InitExtra3PC( coreId_ )    ( T1_PLUGIN_NOT_AVAILABLE )
#    define T1_baseRevision               ( 0uL )

#endif /* defined T1_ENABLE */

/*----------------------------------------------------------------------------------*/

#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

/**@}*/

/*----------------------------------------------------------------------------------*/
/*--- documentation ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_DOXYGEN_ONLY
/* clang-format off */

/*!
 * \def T1_BUILD_ID
 * Build ID value, see \ref BUILD_BUILD_ID.
 */

/*!
 * \def T1_ALIGN_VAR
 * \brief Macro used to select optimal alignment when possible.
 */

/*!
 * \page T1_base_page T1.base
 *
 * Provides basic services for all T1 plugins, such as calling the respective
 * initialization functions, cyclic handlers and handling the communication between
 * the T1-TARGET-SW and T1-HOST-SW.
 *
 * - \subpage APP_FEATURES
 * - \subpage PC
 * - \subpage INTRPT
 * - \subpage SWITCH
 *
 */

/*!
 * \page PC API calls with and without explicit core ID
 *
 * All T1-TARGET-SW API calls are available in two versions. One version has a 'PC'
 * (per core) suffix and an additional, first parameter that explicitly states the T1
 * logical identifier of the core to be processed. The other version has no 'PC'
 * suffix and obtains the T1 logical identifier of the calling core by invoking
 * T1_GetCoreIdOffset(). For example, see T1_Init( T1_pluginTable_t pluginTable ) and
 * T1_InitPC( T1_uint8Least_t coreId, T1_pluginTable_t pluginTable ). The integrator
 * selects the most appropriate version for your integration.
 *
 * The 'PC' version is provided for two reasons.
 * -# Some implementations of T1_GetCoreIdOffset() are very slow, for example because
 *    a trap to supervisor mode is required in order to read the core ID register. By
 *    using the 'PC' version, the integrator controls exactly when
 *    T1_GetCoreIdOffset() is called and can cache the result to minimize the number
 *    of calls.
 * -# When using the 'remote core' configuration of T1.cont, T1_ContBgHandlerPC() and
 *    some associated callbacks are automatically called with a core ID other than
 *    the running core.
 *
 * \note
 * When using the 'PC' version for user instrumentation, the T1 logical core
 * identifier of the <b>calling</b> core must be used. When in doubt, the version
 * without the 'PC' suffix should be used.
 */

/*!
 * \page INTRPT API use of interrupt locks
 *
 * The T1-TARGET-SW scalable multi-core concept requires that, as much as possible,
 * services run exclusively on one core. Thus, for multi-core and for single core
 * implementations of T1-TARGET-SW, mutual exclusion requires only an interrupt
 * lock. However, disabling interrupts is typically not allowed in user mode. In
 * order to provide a balance of convenience and performance, the T1-TARGET-SW
 * provides two different concepts for thread-safety:
 * -# Apart from T1_Init() and the family of API calls starting T1_Trace...,
 *    T1-TARGET-SW API calls can safely be called in user mode. Interrupts are
 *    disabled and enabled via T1_SuspendAllInterrupts() and T1_ResumeAllInterrupts()
 *    and the integrator can provide implementations that operate correctly in user
 *    mode.
 * -# The family of API calls starting T1_Trace... are too time-critical to use
 *    callouts to T1_SuspendAllInterrupts() and T1_ResumeAllInterrupts().
 *    - Generally, the integrator should manage the disabling of interrupts outside
 *      of T1-TARGET-SW and call these API calls after interrupts have been
 *      disabled. For each T1_Trace... API call there is a version with the suffix
 *      NoSusp that does not attempt to suspend interrupts, on the assumption that
 *      they are already disabled. See T1_TraceStartNoSusp(), for example.
 *    - If the integrator knows that the code is executing with sufficient privileges
 *      to disable interrupts and interrupts may or may not be disabled, they can
 *      call the version with no suffix and it will suspend and restore interrupts as
 *      required by reading and writing to the single bit in the relevant processor
 *      register. See T1_TraceStart(), for example.
 *    - If the integrator knows that the code is executing with sufficient privileges
 *      to disable interrupts and interrupts are certainly enabled, they can
 *      call the version with the ...Fast suffix and it will disable and enable
 *      interrupts as required by writing to the single bit in the relevant processor
 *      register. See T1_TraceStartFast(), for example.
 *    - To interface between the less time-critical functions that can run in user
 *      mode and the more time-critical functions that require supervisor privileges,
 *      there exists a set of 'UM' callouts to allow library code that might run at
 *      user level, to trace an event, see T1_TraceEventUMPC(). These should not
 *      normally be called directly from user code.
 */

/*!
 * \page APP_FEATURES Application features

T1 user events, user data events and stopwatches all consume entries in the trace
buffer and, if they are very frequent, can significantly reduce the amount of
time captured and visualized in one trace buffer. In order to optimize the density
of relevant events in each trace, it is often necessary to enable and disable user
events and stopwatches at run-time.

To support this, T1 provides application features, which can be independently enabled
and disabled from the T1-HOST-SW and that can be tested in the application code.

There is always one, global application feature mask, even when multiple cores
are configured, see #T1_featureMask. This allows related events on different cores to
be enabled and disabled simultaneously.

Configuration {#APPFEATURES_CONFIG}
=============

Invocation File Parameter Method
--------------------------------

Application features can be configured using the parameter
[-allocateAF](\ref allocateAF) in order for the T1-HOST-SW to offer run-time control
of that feature.

Example configuration:

~~~~~~~~~~~~~~~
-allocateAF=TRACE_STARTUP,     "Capture Startup Trace",    true
-allocateAF=ALLOW_TRIGGER,     "Allow on Target Trigger",  true
-allocateAF=ALLOW_TRACEDATA,   "Allow T1 Trace Data",      false
-allocateAF=CHECK_INTEGRATION, "Enable Check Integration", false
~~~~~~~~~~~~~~~

This will create the following macros into *T1_config.h*:

~~~~~~~~~~~~~~~{.c}
...*/

/*----------------------------------------------------------------------------------*/
/*--- Application Features ---------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_AF_TRACE_STARTUP                           (0x00000001uL) /*!< Capture Startup Trace */
#define T1_AF_ALLOW_TRIGGER                           (0x00000002uL) /*!< Allow on Target Trigger */
#define T1_AF_ALLOW_TRACEDATA                         (0x00000004uL) /*!< Allow T1 Trace Data */
#define T1_AF_CHECK_INTEGRATION                       (0x00000008uL) /*!< Enable Check Integration */

/* ... */

/*!
 * \brief Initial value of application feature mask.
 */
#define T1_INIT_FEATURE_MASK                          (T1_AF_TRACE_STARTUP | T1_AF_ALLOW_TRIGGER)

/*...
~~~~~~~~~~~~~~~

And XML elements in the T1 project files, which are used by the T1-HOST-SW for
displaying purposes:

~~~~~~~~~~~~~~~{.xml}
<AppFeature Name="Capture Startup Trace">
  <Mask>1</Mask>
</AppFeature>
<AppFeature Name="Allow on Target Trigger">
  <Mask>2</Mask>
</AppFeature>
<AppFeature Name="Allow T1 Trace Data">
  <Mask>4</Mask>
</AppFeature>
<AppFeature Name="Enable Check Integration">
  <Mask>8</Mask>
</AppFeature>
~~~~~~~~~~~~~~~

Inline XML Method (legacy)
--------------------------

The application feature must be declared in T1_AppInterface.h in order for the
T1-HOST-SW to offer run-time control of that feature:

~~~~~~~~~~~~~~~{.c}
...*/

/* @T1@ <AppFeature Name="T1_AF_TRACE_STARTUP"> */
#define T1_AF_TRACE_STARTUP                 0x00000001uL /* capture start-up of the ECU */
/* @T1@ </AppFeature> */
/* @T1@ <AppFeature Name="T1_AF_ALLOW_TRIGGER"> */
#define T1_AF_ALLOW_TRIGGER                 0x00000002uL /* permit triggering (trace capture) */
/* @T1@ </AppFeature> */
/* @T1@ <AppFeature Name="T1_AF_ALLOW_TRACEDATA"> */
#define T1_AF_ALLOW_TRACEDATA               0x00000004uL /* permit T1_TraceData */
/* @T1@ </AppFeature> */
/* @T1@ <AppFeature Name="T1_AF_CHECK_INTEGRATION"> */
#define T1_AF_CHECK_INTEGRATION             0x00000008uL /* trace the stopwatch T1_SW_CHECK_INTEGRATION_COREx */
/* @T1@ </AppFeature> */

/*...
~~~~~~~~~~~~~~~

The comment of the declaration must be like the example above, because it need to be
read also by T1-HOST-SW. Only the names in comment can be changed by user.
The value has to be defined to 1uL << shift, where shift is in the range 0..31.

Usage {#APPFEATURES_USAGE}
=====
The API call T1_IsFeatureEnabled() can be placed anywhere in the code where
conditional tracing or conditional triggering must be used.

~~~~~~~~~~~~~~~{.c}
...*/

/* If the application feature T1_AF_CHECK_INTEGRATION is enabled, trace the
 * static stopwatch T1_SW_CHECK_INTEGRATION_COREx which has the ID 0 by default.
 */
if( T1_IsFeatureEnabled( T1_AF_CHECK_INTEGRATION ) )
{
    T1_TraceEventPC( coreId, T1_STOPWATCH_START, T1_SW_CHECK_INTEGRATION_CORE_ALL );
    T1_CheckIntegrationHandlerPC( coreId );
    T1_TraceEventPC( coreId, T1_STOPWATCH_STOP, T1_SW_CHECK_INTEGRATION_CORE_ALL );
}

/*...
~~~~~~~~~~~~~~~

Multiple examples can be found in T1_AppInterface.c and T1_config.c to either trace
additional information or halt the tracing.

Additionally, the callback T1_FeatureMaskChangedPC() can be called on change requested
by the T1-HOST-SW, see the \ref featureMaskCallback.

Trace per feature {#APPFEATURES_TRACE}
=================
There are additional variants of the T1_TraceEvent() calls that only log an event
if a particular feature is enabled. See T1_TraceEventPerFeature(),
T1_TraceEventFastPerFeature() and T1_TraceEventNoSuspPerFeature().

 */

/*!
 * \page SWITCH Switch on/off the T1-TARGET-SW or its plugins

T1-TARGET-SW Switch {#SWITCH_GLOBAL}
===================

The T1 headers are implemented in a way that T1 is present only if the compiler
macro #T1_ENABLE is defined. The definition can be placed in a header which
is included by all relevant files such as T1_AppInterface.h or preferably
through a compiler command line switch e.g. -DT1_ENABLE.
If this macro is not defined, all forward declarations of the T1-TARGET-SW API
are mapped to empty macros or to a sensible return code.
As a result, all references to the T1-TARGET-SW symbols vanish and no T1 objects
from any T1 library should be linked.

Successfully removing the T1-TARGET-SW depends on the correctness of the
project's build process which is not provided by GLIWA. If the absence of T1
is essential, for example when using the non ISO 26262 certified T1-TARGET-SW
in a safety-relevant context, we strongly recommend to additionally remove
or rename the T1 libraries. If the build process is faulty, the linker will
generate errors rather than accidentally link parts of the T1-TARGET-SW.

The compiler macro #T1_ENABLE can also be used to disable completely the
glue code which functions as a project-specific interface between the
T1-TARGET-SW and the application. By default, the compiler macro #T1_ENABLE
inhibit the content of the wrapper functions called by the application, such as
T1_AppHandler(). If this glue code has to be removed when T1 is disabled,
the call of the function can be done depending on the compiler macro:
~~~~~~~~~~~~~~~{.c}
...*/
#include T1_AppInterface.h

TASK( myPeriodicTask )
{
    ...
#if defined T1_ENABLE
    T1_AppHandler( );
#endif
    ...
}
/*...
~~~~~~~~~~~~~~~

If T1.flex is used, reference to the T1.flex exception-handler also has to be
made conditional on the compiler macro #T1_ENABLE and #T1_DISABLE_T1_FLEX,
or manually removed when T1 or T1.flex are disabled:
~~~~~~~~~~~~~~~{.c}
...*/
#if !defined T1_DISABLE_T1_FLEX && defined T1_ENABLE
/* referencing T1.flex exception-handler */
#endif
/*...
~~~~~~~~~~~~~~~

Plugins Switch {#SWITCH_PLUGINS}
==============
Note that T1.base and T1.scope cannot be disabled when the T1-TARGET-SW is enabled.
There are two ways to disable the other T1 plugins:
1. Using the invocation file parameter -disableT1<plugin> which will define the macro
T1_DISABLE_T1_<plugin> in T1_config.h before all includes, see
[-disableT1Cont](@ref disableT1Cont), [-disableT1Delay](@ref disableT1Delay),
[-disableT1Flex](@ref disableT1Flex), [-disableT1Mod](@ref disableT1Mod).
2. By defining T1_DISABLE_T1_<plugin> before all includes in T1_AppInterface.h
or as a compiler macro, see #T1_DISABLE_T1_CONT, #T1_DISABLE_T1_FLEX,
#T1_DISABLE_T1_MOD, #T1_DISABLE_T1_DELAY.
3. By disabling certain T1 plugins in the T1_pluginTable that gets passed to T1_Init().
See \ref SWITCH_PLUGINTABLE.

The approaches differ in their working principle. While the first and second inhibit
referencing (and thus linking) any symbol of the specified plugin, the third
approach leads to linking all objects but inhibits initialization of the undesired
plugins.

T1 Plugin-Table {#SWITCH_PLUGINTABLE}
---------------
The initialization routine T1_Init() requires a plugin-table to be passed. The
plugin-table defines the set of active T1 plugins and the content depends on which
plugins are enabled/disabled via the T1_DISABLE_T1_<PLUGIN> macros.
The variable T1_pluginTable can have any name, it is a C variable declared
in T1_AppInterface.h using the macro #T1_DeclarePluginTable( T1_pluginTable ).
The macro #T1_ALLOCATE_PLUGIN_TABLE is used in T1_config.c in order to define
the plugin-table.
When T1 is started, the plugin-table variable is passed to T1_Init(), for example as
T1_Init( T1_pluginTable ).

There are two use-cases where we wish to disable T1.flex without using the intended
macro #T1_DISABLE_T1_FLEX:
-# Decision at run-time, whether to enable or disable T1.flex
-# The integration unconditionally links the T1.flex libraries and a linker error
arises if #T1_DISABLE_T1_FLEX is defined. This can happen as a result of hard-coding
the T1.flex exception handler symbol(s) into the application vector table. The
correct solution would have been to provide null-handlers in T1_AppInterface.c
when #T1_DISABLE_T1_FLEX is defined but this is not always possible.

In order to handle these use-cases, an additional macro
#T1_ALLOCATE_PLUGIN_TABLE_NO_T1_FLEX is provided that declares a plugin-table where
T1.flex is always disabled, regardless of the macro #T1_DISABLE_T1_FLEX.
For example, in order to conditionally initialize T1.flex at run-time, we can use the
following approach:
~~~~~~~~~~~~~~~{.c}
...*/

/* in T1_AppInterface.h */
T1_DeclarePluginTable( T1_pluginTable );
T1_DeclarePluginTable( T1_pluginTableNoFlex );

/* in T1_config.c */
T1_ALLOCATE_PLUGIN_TABLE( T1_pluginTable );
T1_ALLOCATE_PLUGIN_TABLE_NO_T1_FLEX( T1_pluginTableNoFlex );

/* in T1_AppInit in T1_AppInterface.c */
if( T1_NO_FLEX == CODING_PARAMETER )
{
    T1_Init( T1_pluginTableNoFlex );
}
else
{
    T1_Init( T1_pluginTable );
}
/*...
~~~~~~~~~~~~~~~

This conditional implementation allows to have a common software release allowing
to disable for example T1.flex prior to a drive on the track where the usage of
T1.flex must be inhibited. However, it is required to reinitialize the target after
having changed the parameter (power on reset is required for T1.flex).

 */

/* clang-format on */
#endif /* defined T1_DOXYGEN_ONLY */

#endif /* T1_BASE_INTERFACE_H_ */
