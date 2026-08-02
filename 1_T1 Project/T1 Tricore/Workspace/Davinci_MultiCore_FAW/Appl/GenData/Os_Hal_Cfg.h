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
 *              File: Os_Hal_Cfg.h
 *   Generation Time: 2020-07-28 17:15:44
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_HAL_CFG_H)                                                          /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_HAL_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! HAL configuration major version identification. */
# define OS_CFG_HAL_MAJOR_VERSION                (2U)

/*! HAL configuration minor version identification. */
# define OS_CFG_HAL_MINOR_VERSION                (14U)

/* ISR core and level definitions */
# define OS_ISR_ADC0SR0_ISR_CORE      (1)
# define OS_ISR_ADC0SR0_ISR_LEVEL     (50)
# define OS_ISR_ADC1SR0_ISR_CORE      (1)
# define OS_ISR_ADC1SR0_ISR_LEVEL     (51)
# define OS_ISR_ADC2SR0_ISR_CORE      (1)
# define OS_ISR_ADC2SR0_ISR_LEVEL     (52)
# define OS_ISR_ADC3SR0_ISR_CORE      (1)
# define OS_ISR_ADC3SR0_ISR_LEVEL     (53)
# define OS_ISR_ADC4SR0_ISR_CORE      (1)
# define OS_ISR_ADC4SR0_ISR_LEVEL     (54)
# define OS_ISR_ADC5SR0_ISR_CORE      (1)
# define OS_ISR_ADC5SR0_ISR_LEVEL     (55)
# define OS_ISR_ADC6SR0_ISR_CORE      (1)
# define OS_ISR_ADC6SR0_ISR_LEVEL     (56)
# define OS_ISR_CANISR_0_CORE      (0)
# define OS_ISR_CANISR_0_LEVEL     (10)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE0_CORE      (0)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE0_LEVEL     (3)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE1_CORE      (1)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE1_LEVEL     (3)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE2_CORE      (2)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE2_LEVEL     (3)
# define OS_ISR_ISR_TIM02_CORE      (1)
# define OS_ISR_ISR_TIM02_LEVEL     (30)
# define OS_ISR_ISR_TIM03_CORE      (1)
# define OS_ISR_ISR_TIM03_LEVEL     (31)
# define OS_ISR_XSIGNALISR_OSCORE0_CORE      (0)
# define OS_ISR_XSIGNALISR_OSCORE0_LEVEL     (18)
# define OS_ISR_XSIGNALISR_OSCORE1_CORE      (1)
# define OS_ISR_XSIGNALISR_OSCORE1_LEVEL     (18)
# define OS_ISR_XSIGNALISR_OSCORE2_CORE      (2)
# define OS_ISR_XSIGNALISR_OSCORE2_LEVEL     (18)

/* Hardware counter timing macros */

/* Counter timing macros and constants: SystemTimer_Core0 */
# define OSMAXALLOWEDVALUE_SystemTimer_Core0     (1073741823UL) /* 0x3FFFFFFFUL */
# define OSMINCYCLE_SystemTimer_Core0            (1UL)
# define OSTICKSPERBASE_SystemTimer_Core0        (1UL)
# define OSTICKDURATION_SystemTimer_Core0        (10UL)

/* OSEK compatibility for the system timer. */
# define OSMAXALLOWEDVALUE     (OSMAXALLOWEDVALUE_SystemTimer_Core0)
# define OSMINCYCLE            (OSMINCYCLE_SystemTimer_Core0)
# define OSTICKSPERBASE        (OSTICKSPERBASE_SystemTimer_Core0)
# define OSTICKDURATION        (OSTICKDURATION_SystemTimer_Core0)

/*! Macro OS_NS2TICKS_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_Core0(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Macro OS_TICKS2NS_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_Core0(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Macro OS_US2TICKS_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_Core0(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Macro OS_TICKS2US_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_Core0(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Macro OS_MS2TICKS_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_Core0(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Macro OS_TICKS2MS_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_Core0(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Macro OS_SEC2TICKS_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_Core0(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Macro OS_TICKS2SEC_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_Core0(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */


/* Counter timing macros and constants: SystemTimer_Core1 */
# define OSMAXALLOWEDVALUE_SystemTimer_Core1     (1073741823UL) /* 0x3FFFFFFFUL */
# define OSMINCYCLE_SystemTimer_Core1            (1UL)
# define OSTICKSPERBASE_SystemTimer_Core1        (1UL)
# define OSTICKDURATION_SystemTimer_Core1        (10UL)

/*! Macro OS_NS2TICKS_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_Core1(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Macro OS_TICKS2NS_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_Core1(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Macro OS_US2TICKS_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_Core1(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Macro OS_TICKS2US_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_Core1(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Macro OS_MS2TICKS_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_Core1(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Macro OS_TICKS2MS_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_Core1(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Macro OS_SEC2TICKS_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_Core1(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Macro OS_TICKS2SEC_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_Core1(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */


/* Counter timing macros and constants: SystemTimer_Core2 */
# define OSMAXALLOWEDVALUE_SystemTimer_Core2     (1073741823UL) /* 0x3FFFFFFFUL */
# define OSMINCYCLE_SystemTimer_Core2            (1UL)
# define OSTICKSPERBASE_SystemTimer_Core2        (1UL)
# define OSTICKDURATION_SystemTimer_Core2        (10UL)

/*! Macro OS_NS2TICKS_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_Core2(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Macro OS_TICKS2NS_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_Core2(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Macro OS_US2TICKS_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_Core2(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Macro OS_TICKS2US_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_Core2(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Macro OS_MS2TICKS_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_Core2(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Macro OS_TICKS2MS_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_Core2(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Macro OS_SEC2TICKS_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_Core2(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Macro OS_TICKS2SEC_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_Core2(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) )     /* PRQA S 3453 */ /* MD_MSR_19.7 */




/* CAT0 and CAT1 ISR core and level definitions */



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


#endif /* OS_HAL_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Cfg.h
 *********************************************************************************************************************/
