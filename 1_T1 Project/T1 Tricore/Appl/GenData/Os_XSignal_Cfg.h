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
 *              File: Os_XSignal_Cfg.h
 *   Generation Time: 2020-07-28 15:56:23
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_XSIGNAL_CFG_H)                                                      /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_XSIGNAL_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Defines whether the X-Signal module is active (STD_ON) or not (STD_OFF). */
# define OS_CFG_XSIGNAL                          (STD_ON)

/*! Defines whether cross core calls shall be performed asynchronous (STD_ON) or not (STD_OFF). */
# define OS_CFG_XSIG_USEASYNC                    (STD_OFF)

/* X-Signal defines for core: OsCore0 */
# define OS_CFG_NUM_XSIG_OSCORE0_ISRS     (1UL)
# define OS_CFG_SIZE_OSCORE0_SEND0_XSIGNALISR_OSCORE1_RECV0_BUFFER     (2UL)
# define OS_CFG_SIZE_OSCORE0_SEND1_XSIGNALISR_OSCORE2_RECV0_BUFFER     (2UL)
# define OS_CFG_NUM_ISR_XSIGNALISR_OSCORE0_PORTS     (2UL)

/* X-Signal defines for core: OsCore1 */
# define OS_CFG_NUM_XSIG_OSCORE1_ISRS     (1UL)
# define OS_CFG_SIZE_OSCORE1_SEND0_XSIGNALISR_OSCORE0_RECV0_BUFFER     (2UL)
# define OS_CFG_SIZE_OSCORE1_SEND1_XSIGNALISR_OSCORE2_RECV1_BUFFER     (2UL)
# define OS_CFG_NUM_ISR_XSIGNALISR_OSCORE1_PORTS     (2UL)

/* X-Signal defines for core: OsCore2 */
# define OS_CFG_NUM_XSIG_OSCORE2_ISRS     (1UL)
# define OS_CFG_SIZE_OSCORE2_SEND0_XSIGNALISR_OSCORE1_RECV1_BUFFER     (2UL)
# define OS_CFG_SIZE_OSCORE2_SEND1_XSIGNALISR_OSCORE0_RECV1_BUFFER     (2UL)
# define OS_CFG_NUM_ISR_XSIGNALISR_OSCORE2_PORTS     (2UL)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


#endif /* OS_XSIGNAL_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_XSignal_Cfg.h
 *********************************************************************************************************************/
