/************************************************************************************/
/*! \file           T1_modInterface.h
 *
 *  \brief          T1.mod interface declarations and macros
 *
 *  \par Visibility
 *                  External
 *
 *  \author nick
 *
 *  \version 3.5.0.0 r65384
 *
 *  \copyright GLIWA embedded systems GmbH & Co. KG, Weilheim i.OB. All rights reserved
 ************************************************************************************/

#ifndef T1_MOD_INTERFACE_H_
#define T1_MOD_INTERFACE_H_ ( 1 )

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_baseInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_MOD_PLUGIN_ID ( 4u )

#if defined T1_ENABLE && !defined T1_DISABLE_T1_MOD
/*! \brief T1.mod entry in plugin table. */
#    define T1_modPlugin ( &T1_modPluginStruct )
#else
#    define T1_modPlugin   ( T1_DISABLED_PLUGIN )
#    define T1_modRevision ( 0uL )
#endif

/*----------------------------------------------------------------------------------*/
/*--- types ------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*! \brief T1.mod global data for one core. */
typedef struct
{
    T1_uint8_t T1_FARPTR pWrite;
    T1_uint32_t data;
    T1_uint8_t modTxState;
#if defined T1_CPU16BIT || defined T1_CPU32BIT || defined T1_CPU64BIT
    T1_uint8_t unused8; //!< force alignment
#    if defined T1_CPU32BIT || defined T1_CPU64BIT
    T1_uint16_t unused16; //!< force alignment
#    endif                /* defined T1_CPU32BIT || defined T1_CPU64BIT */
#endif /* defined T1_CPU16BIT || defined T1_CPU32BIT || defined T1_CPU64BIT */
} T1_modGlobals_t;

/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_MOD

#    define T1_START_SEC_CONST_32
#    include "T1_MemMap.h"
T1_DeclarePlugin( T1_modPluginStruct );
T1_EXTERN const T1_uint32_t T1_SEC_CONST_32 T1_modRevision;
#    define T1_STOP_SEC_CONST_32
#    include "T1_MemMap.h"

#    if !defined T1_MULTICORE_CLONE

#        define T1_START_SEC_CONST_32
#        include "T1_MemMap.h"
T1_EXTERN T1_modGlobals_t * const T1_SEC_CONST_32 T1_modGlobalsPC[];
#        define T1_STOP_SEC_CONST_32
#        include "T1_MemMap.h"

#    else /* clone */

#        define T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"
T1_EXTERN T1_modGlobals_t T1_CLONE_SEC_VAR_POWER_ON_CLEARED_32 T1_modGlobals;
#        define T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#        include "T1_MemMap.h"

#    endif /* ! defined T1_MULTICORE_CLONE */

#endif

/*----------------------------------------------------------------------------------*/
/*--- documentation ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_DOXYGEN_ONLY

/*!
 * \page T1_mod_page T1.mod
 *
 * T1.mod is a plugin of T1 that allows for reading from and writing to arbitrary
 * memory locations. T1.mod is controlled from the T1-HOST-SW.
 *
 */

#endif /* T1_DOXYGEN_ONLY */

#endif /* T1_MOD_INTERFACE_H_ */
