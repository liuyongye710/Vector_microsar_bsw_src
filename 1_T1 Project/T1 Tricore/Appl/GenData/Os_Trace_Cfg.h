/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Os
 *           Program: MSR_Vector_SLP4
 *          Customer: China FAW Group Corporation
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC297TA
 *    License Scope : The usage is restricted to CBD1600956_D02
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_Trace_Cfg.h
 *   Generation Time: 2020-07-28 16:23:29
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_TRACE_CFG_H)                                                        /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_TRACE_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Defines whether ORTI is active (STD_ON) or not (STD_OFF). */
# define OS_CFG_ORTI                             (STD_OFF)

/*! Defines whether ORTI tracing is active (STD_ON) or not (STD_OFF). */
# define OS_CFG_ORTI_ADDITIONAL                  (STD_OFF)

/*! Defines whether Vector timing hooks are active (STD_ON) or not (STD_OFF). */
# define OS_CFG_OSTIMINGHOOKS                    (STD_ON)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


#endif /* OS_TRACE_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Trace_Cfg.h
 *********************************************************************************************************************/
