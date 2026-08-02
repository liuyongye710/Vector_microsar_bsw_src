/*********************************************************************************//*!
*   \file           T1_modInterface.h
*
*   \brief          T1.mod interface declarations and macros
*
*   \par Visibility
*                   External
*
*   \author nick
*
*   \version 2.5.5.0 r37714
*
*   \copyright GLIWA GmbH embedded systems, Weilheim i.OB. All rights reserved
*************************************************************************************/

#ifndef T1_MOD_INTERFACE_H_
#define T1_MOD_INTERFACE_H_ (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_baseInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_MOD_PLUGIN_ID                        (4u)

#if defined T1_ENABLE && !defined T1_DISABLE_T1_MOD
/*! \brief T1.mod entry in plugin table. */
#   define T1_modPlugin                         (&T1_modPluginStruct)
#else
#   define T1_modPlugin                         (T1_DISABLED_PLUGIN)
#endif


/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_MOD
#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_DeclarePlugin( T1_modPluginStruct );
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"
#endif

#endif /* T1_MOD_INTERFACE_H_ */
