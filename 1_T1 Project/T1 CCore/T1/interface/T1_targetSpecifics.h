/************************************************************************************/
/*! \file           T1_targetSpecifics.h
 *
 *  \brief          T1-TARGET-SW header specific to NXP MPC5xxx architecture
 *
 *  \par Visibility
 *                  External
 *
 *  \author nick
 *
 *  \version 3.5.0.0 r64987
 *
 *  \copyright GLIWA embedded systems GmbH & Co. KG, Weilheim i.OB. All rights reserved
 ************************************************************************************/

#ifndef T1_TARGETSPECIFICS_H_
#define T1_TARGETSPECIFICS_H_ ( 1 )

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

typedef unsigned long T1_icuRegister_t;

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined __ghs__
#    define T1_FAR_CODE( type_ ) __farcall type_
#    define T1_NEAR_CODE_FAST    __attribute__( ( aligned( 16 ) ) )
#    define T1_CODE_FAST( type_ )                                                    \
        T1_FAR_CODE( type_ ) __attribute__( ( aligned( 16 ) ) )
#    define T1_CODE __attribute__( ( aligned( 8 ) ) )
#    include <ppc_ghs.h> /* Enable Green Hills intrisic __MFSPR */
#    define T1_GetPIR( )             __MFSPR( 286 )
#    define T1_DISABLE_INTERRUPTS( ) __asm( "wrteei 0" )
#    define T1_ENABLE_INTERRUPTS( )  __asm( "wrteei 1" )
#    define T1_GetMSR( )             __GETSR( )
#    if !defined T1_CHECKER_ARTEFACT                                                 \
        && defined                                                                   \
            __GNUC__ /* Without GNU C extensions, is is better to use plain C */
#        if defined __vle__
#            define T1_VLE_E_STR "e_"
#        else /* ! defined __vle__ */
#            define T1_VLE_E_STR ""
#        endif /* defined __vle__ */
#        define T1_INSERT32( dst_, ins_, offst_, len_ )                              \
            ( {                                                                      \
                T1_uint32_t rslt = ( dst_ );                                         \
                __asm( T1_VLE_E_STR "rlwimi %0, %2, %3, %4, %5"                      \
                       : "=r"( rslt )                                                \
                       : "0"( rslt ),                                                \
                         "r"( ins_ ),                                                \
                         "i"( offst_ ),                                              \
                         "i"( 32 - ( offst_ ) - ( len_ ) ),                          \
                         "i"( 31 - ( offst_ ) ) );                                   \
                rslt;                                                                \
            } )
#        define T1_ROTL32( x_, y_ )                                                  \
            ( {                                                                      \
                T1_uint32_t rslt;                                                    \
                __asm( T1_VLE_E_STR "rlwinm %0, %1, %2, 0, 31"                       \
                       : "=r"( rslt )                                                \
                       : "r"( x_ ), "i"( y_ ) );                                     \
                rslt;                                                                \
            } )
#    endif /* defined __GNUC__ */
#    define T1_TARGET_DSYNC( )      __MBAR( )
#    define T1_INVALID_CET_EVENT_ID ( 0u )

#elif defined __DCC__
#    define T1_CODE_FAST( type_ ) type_ __attribute__( ( aligned( 16 ) ) )
#    define T1_CODE               __attribute__( ( aligned( 8 ) ) )
typedef unsigned long T1_pir_t;
/* clang-format off */
asm __inline__ T1_pir_t T1_GetPIR( void )
{
!"r3"
    mfpir r3
}
/*----------------------------------------------------------------------------------*/
asm __inline__ void T1_DISABLE_INTERRUPTS( void )
{
!
    wrteei 0
}
/*----------------------------------------------------------------------------------*/
asm __inline__ void T1_ENABLE_INTERRUPTS( void )
{
!
    wrteei 1
}
/*----------------------------------------------------------------------------------*/
asm __inline__ T1_icuRegister_t T1_GetMSR( void )
{
!"r3"
    mfmsr r3
}
asm volatile __inline__ void T1_TARGET_DSYNC( void )
{
!
    mbar 0
}
/* clang-format on */
#elif defined __MWERKS__ || defined __GNUC__
#    define T1_FAR_CODE( type_ ) type_ __attribute__( ( longcall ) )
#    define T1_NEAR_CODE_FAST    __attribute__( ( aligned( 16 ) ) )
#    define T1_CODE_FAST( type_ )                                                    \
        T1_FAR_CODE( type_ ) __attribute__( ( aligned( 16 ) ) )
#    define T1_CODE __attribute__( ( aligned( 8 ) ) )
#    define T1_GetPIR( )                                                             \
        ( {                                                                          \
            T1_uint32_t regVal;                                                      \
            __asm( "mfpir %0" : "=r"( regVal ) : : );                                \
            regVal;                                                                  \
        } )
#    define T1_DISABLE_INTERRUPTS( ) __asm volatile( "wrteei 0" )
#    define T1_ENABLE_INTERRUPTS( )  __asm volatile( "wrteei 1" )
#    define T1_GetMSR( )                                                             \
        ( {                                                                          \
            T1_icuRegister_t msrVal_;                                                \
            __asm( "mfmsr %0" : "=r"( msrVal_ ) : : );                               \
            msrVal_;                                                                 \
        } )
#    define T1_TARGET_DSYNC( ) ( { __asm volatile( "mbar 0" ); } )
#    if !defined T1_CHECKER_ARTEFACT
#        define T1_INSERT32( dst_, ins_, offst_, len_ )                              \
            ( {                                                                      \
                T1_uint32_t rslt = ( dst_ );                                         \
                __asm( "rlwimi %0, %2, %3, %4, %5"                                   \
                       : "=r"( rslt )                                                \
                       : "0"( rslt ),                                                \
                         "r"( ins_ ),                                                \
                         "i"( offst_ ),                                              \
                         "i"( 32 - ( offst_ ) - ( len_ ) ),                          \
                         "i"( 31 - ( offst_ ) ) );                                   \
                rslt;                                                                \
            } )
#        define T1_ROTL32( x_, y_ )                                                  \
            ( {                                                                      \
                T1_uint32_t rslt;                                                    \
                __asm( "rlwinm %0, %1, %2, 0, 31"                                    \
                       : "=r"( rslt )                                                \
                       : "r"( x_ ), "i"( y_ ) );                                     \
                rslt;                                                                \
            } )
#    endif /* ! defined T1_CHECKER_ARTEFACT */
#endif     /* compiler */

#if !defined T1_GetCoreIdOffset
#    define T1_GetCoreIdOffset( ) ( T1_GetPIR( ) )
#endif /* ! defined T1_GetCoreIdOffset */

#define T1_MSR_EE_MASK               ( 0x00008000uL )

#define T1_INTERRUPTS_ARE_ENABLED( ) ( 0uL != ( T1_MSR_EE_MASK & T1_GetMSR( ) ) )

#define T1_INLINE                    static __inline__

#if defined __ghs__
#    define T1_NOINLINE __noinline
#else
#    define T1_NOINLINE __attribute__( ( noinline ) )
#endif

#define T1_CPU32BIT        ( 1 )

#define T1_FLEX_SINGLESTEP ( 1 )

#define T1_MPC5XXX         ( 1 )

#define T1_INSERT32_OR( dst_, ins_, offst_, len_ )                                   \
    T1_INSERT32( ( dst_ ), ( ins_ ), ( offst_ ), ( len_ ) )

#if defined __DCC__
#    define T1_ALIGN_32 __attribute__( ( aligned( 4 ) ) )
#    define T1_ALIGN_VAR( bytes_ )
#else /* These attributes provoke an issue in old Diab compilers. */
#    define T1_ALIGN_VAR( bytes_ ) __attribute__( ( aligned( bytes_ ) ) )
#endif /* ! defined __DCC__ */

#define T1_SEC_VAR_CLEARED_32                             T1_ALIGN_VAR( 4 )
#define T1_SEC_CONST_32                                   T1_ALIGN_VAR( 4 )
#define T1_SEC_VAR_POWER_ON_CLEARED_32                    T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_SEC_VAR_POWER_ON_CLEARED_32        T1_ALIGN_VAR( 4 )
#define T1_CHECKED_SEC_VAR_POWER_ON_CLEARED_32            T1_ALIGN_VAR( 4 )
#define T1_CORE0_SEC_CONST_32                             T1_ALIGN_VAR( 8 )
#define T1_CORE0_SEC_VAR_POWER_ON_CLEARED_32              T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE0_SEC_VAR_POWER_ON_CLEARED_32  T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE0_SEC_VAR_POWER_ON_CLEARED_32      T1_ALIGN_VAR( 4 )
#define T1_CORE1_SEC_CONST_32                             T1_ALIGN_VAR( 8 )
#define T1_CORE1_SEC_VAR_POWER_ON_CLEARED_32              T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE1_SEC_VAR_POWER_ON_CLEARED_32  T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE1_SEC_VAR_POWER_ON_CLEARED_32      T1_ALIGN_VAR( 4 )
#define T1_CORE2_SEC_CONST_32                             T1_ALIGN_VAR( 8 )
#define T1_CORE2_SEC_VAR_POWER_ON_CLEARED_32              T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE2_SEC_VAR_POWER_ON_CLEARED_32  T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE2_SEC_VAR_POWER_ON_CLEARED_32      T1_ALIGN_VAR( 4 )
#define T1_CORE3_SEC_CONST_32                             T1_ALIGN_VAR( 8 )
#define T1_CORE3_SEC_VAR_POWER_ON_CLEARED_32              T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE3_SEC_VAR_POWER_ON_CLEARED_32  T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE3_SEC_VAR_POWER_ON_CLEARED_32      T1_ALIGN_VAR( 4 )
#define T1_CORE4_SEC_CONST_32                             T1_ALIGN_VAR( 8 )
#define T1_CORE4_SEC_VAR_POWER_ON_CLEARED_32              T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE4_SEC_VAR_POWER_ON_CLEARED_32  T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE4_SEC_VAR_POWER_ON_CLEARED_32      T1_ALIGN_VAR( 4 )
#define T1_CORE5_SEC_CONST_32                             T1_ALIGN_VAR( 8 )
#define T1_CORE5_SEC_VAR_POWER_ON_CLEARED_32              T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE5_SEC_VAR_POWER_ON_CLEARED_32  T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE5_SEC_VAR_POWER_ON_CLEARED_32      T1_ALIGN_VAR( 4 )
#define T1_CORE6_SEC_CONST_32                             T1_ALIGN_VAR( 8 )
#define T1_CORE6_SEC_VAR_POWER_ON_CLEARED_32              T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE6_SEC_VAR_POWER_ON_CLEARED_32  T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE6_SEC_VAR_POWER_ON_CLEARED_32      T1_ALIGN_VAR( 4 )
#define T1_CORE7_SEC_CONST_32                             T1_ALIGN_VAR( 8 )
#define T1_CORE7_SEC_VAR_POWER_ON_CLEARED_32              T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE7_SEC_VAR_POWER_ON_CLEARED_32  T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE7_SEC_VAR_POWER_ON_CLEARED_32      T1_ALIGN_VAR( 4 )
#define T1_CORE8_SEC_CONST_32                             T1_ALIGN_VAR( 8 )
#define T1_CORE8_SEC_VAR_POWER_ON_CLEARED_32              T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE8_SEC_VAR_POWER_ON_CLEARED_32  T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE8_SEC_VAR_POWER_ON_CLEARED_32      T1_ALIGN_VAR( 4 )
#define T1_CORE9_SEC_CONST_32                             T1_ALIGN_VAR( 8 )
#define T1_CORE9_SEC_VAR_POWER_ON_CLEARED_32              T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE9_SEC_VAR_POWER_ON_CLEARED_32  T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE9_SEC_VAR_POWER_ON_CLEARED_32      T1_ALIGN_VAR( 4 )
#define T1_CORE10_SEC_CONST_32                            T1_ALIGN_VAR( 8 )
#define T1_CORE10_SEC_VAR_POWER_ON_CLEARED_32             T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE10_SEC_VAR_POWER_ON_CLEARED_32 T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE10_SEC_VAR_POWER_ON_CLEARED_32     T1_ALIGN_VAR( 4 )
#define T1_CORE11_SEC_CONST_32                            T1_ALIGN_VAR( 8 )
#define T1_CORE11_SEC_VAR_POWER_ON_CLEARED_32             T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE11_SEC_VAR_POWER_ON_CLEARED_32 T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE11_SEC_VAR_POWER_ON_CLEARED_32     T1_ALIGN_VAR( 4 )
#define T1_CORE12_SEC_CONST_32                            T1_ALIGN_VAR( 8 )
#define T1_CORE12_SEC_VAR_POWER_ON_CLEARED_32             T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE12_SEC_VAR_POWER_ON_CLEARED_32 T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE12_SEC_VAR_POWER_ON_CLEARED_32     T1_ALIGN_VAR( 4 )
#define T1_CORE13_SEC_CONST_32                            T1_ALIGN_VAR( 8 )
#define T1_CORE13_SEC_VAR_POWER_ON_CLEARED_32             T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE13_SEC_VAR_POWER_ON_CLEARED_32 T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE13_SEC_VAR_POWER_ON_CLEARED_32     T1_ALIGN_VAR( 4 )
#define T1_CORE14_SEC_CONST_32                            T1_ALIGN_VAR( 8 )
#define T1_CORE14_SEC_VAR_POWER_ON_CLEARED_32             T1_ALIGN_VAR( 4 )
#define T1_TRACEBUFFER_CORE14_SEC_VAR_POWER_ON_CLEARED_32 T1_ALIGN_VAR( 4 )
#define T1_CHECKED_CORE14_SEC_VAR_POWER_ON_CLEARED_32     T1_ALIGN_VAR( 4 )

#if defined __GNUC__ && !defined __ghs__
#    define T1_CODE_OPT                                                              \
        __attribute__( ( optimize( "O2" ), visibility( "protected" ) ) )
#    define T1_UNUSED( varDecl_ ) varDecl_ __attribute__( ( unused ) )
#endif /* defined __GNUC__ */

/*----------------------------------------------------------------------------------*/
/*--- dedicated registers ----------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#ifdef T1_BMWUKL
#    pragma global_register __dummy = r14
#endif /* T1_BMWUKL */

/*----------------------------------------------------------------------------------*/
/*--- declarations of exception handlers -------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*
 * These declarations are required to allow C code to configure exception vectoring.
 * Do not call them as C functions, they are exception handlers.
 */
void T1_OuterExceptionHandler( void );
void T1_OuterExceptionHandlerCore0( void );
void T1_OuterExceptionHandlerCore1( void );
void T1_OuterExceptionHandlerCore2( void );
void T1_OuterExceptionHandlerCore3( void );
void T1_OuterExceptionHandlerCore4( void );
void T1_OuterExceptionHandlerCore5( void );
void T1_OuterExceptionHandlerCore6( void );
void T1_OuterExceptionHandlerCore7( void );
void T1_OuterExceptionHandlerCore8( void );
void T1_OuterExceptionHandlerCore9( void );
void T1_OuterExceptionHandlerCore10( void );
void T1_OuterExceptionHandlerCore11( void );
void T1_OuterExceptionHandlerCore12( void );
void T1_OuterExceptionHandlerCore13( void );

#endif /* T1_TARGETSPECIFICS_H_ */
