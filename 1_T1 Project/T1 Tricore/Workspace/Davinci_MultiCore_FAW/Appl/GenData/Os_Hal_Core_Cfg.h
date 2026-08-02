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
 *              File: Os_Hal_Core_Cfg.h
 *   Generation Time: 2020-07-28 16:23:23
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_HAL_CORE_CFG_H)                                                     /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_HAL_CORE_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/



/*! Number of interrupt sources initialized by the hardware init core. */
#define OS_CFG_NUM_SYSTEM_INTERRUPTSOURCEREFS                     (16UL)


/*! Number of interrupt sources initialized by core OsCore0 */
#define OS_CFG_NUM_CORE_OSCORE0_INTERRUPTSOURCEREFS           (0UL)
/*! Number of interrupt sources initialized by core OsCore1 */
#define OS_CFG_NUM_CORE_OSCORE1_INTERRUPTSOURCEREFS           (0UL)
/*! Number of interrupt sources initialized by core OsCore2 */
#define OS_CFG_NUM_CORE_OSCORE2_INTERRUPTSOURCEREFS           (0UL)



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


#endif /* OS_HAL_CORE_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Core_Cfg.h
 *********************************************************************************************************************/
