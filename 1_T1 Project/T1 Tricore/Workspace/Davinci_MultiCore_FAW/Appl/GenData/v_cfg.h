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
 *            Module: EcuC
 *           Program: MSR_Vector_SLP4
 *          Customer: China FAW Group Corporation
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC297TA
 *    License Scope : The usage is restricted to CBD1600956_D02
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: v_cfg.h
 *   Generation Time: 2020-07-28 15:56:22
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

#if !defined(__V_CFG_H__)
#define __V_CFG_H__


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#ifndef V_USE_DUMMY_FUNCTIONS
#define V_USE_DUMMY_FUNCTIONS STD_OFF /* /MICROSAR/EcuC/EcucGeneral/DummyFunction */
#endif
#ifndef V_USE_DUMMY_STATEMENT
#define V_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/EcuC/EcucGeneral/DummyStatement */
#endif
#ifndef V_DUMMY_STATEMENT
#define V_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_19.7 */  /* /MICROSAR/EcuC/EcucGeneral/DummyStatementKind */
#endif
#ifndef V_DUMMY_STATEMENT_CONST
#define V_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_19.7 */  /* /MICROSAR/EcuC/EcucGeneral/DummyStatementKind */
#endif
#ifndef V_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define V_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef V_ATOMIC_VARIABLE_ACCESS
#define V_ATOMIC_VARIABLE_ACCESS 32U /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef V_PROCESSOR_TC297
#define V_PROCESSOR_TC297
#endif
#ifndef V_COMP_TASKING
#define V_COMP_TASKING
#endif
#ifndef V_GEN_GENERATOR_MSR
#define V_GEN_GENERATOR_MSR
#endif
#ifndef V_CPUTYPE_BITORDER_LSB2MSB
#define V_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/EcuC/EcucGeneral/BitOrder */
#endif
#ifndef V_CONFIGURATION_VARIANT_PRECOMPILE
#define V_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef V_CONFIGURATION_VARIANT_LINKTIME
#define V_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef V_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define V_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef V_CONFIGURATION_VARIANT
#define V_CONFIGURATION_VARIANT V_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef V_POSTBUILD_VARIANT_SUPPORT
#define V_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

#ifndef C_USE_DUMMY_FUNCTIONS
#define C_USE_DUMMY_FUNCTIONS STD_OFF /* /MICROSAR/EcuC/EcucGeneral/DummyFunction */
#endif
#ifndef C_USE_DUMMY_STATEMENT
#define C_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/EcuC/EcucGeneral/DummyStatement */
#endif
#ifndef C_DUMMY_STATEMENT
#define C_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_19.7 */  /* /MICROSAR/EcuC/EcucGeneral/DummyStatementKind */
#endif
#ifndef C_DUMMY_STATEMENT_CONST
#define C_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_19.7 */  /* /MICROSAR/EcuC/EcucGeneral/DummyStatementKind */
#endif
#ifndef C_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define C_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef C_ATOMIC_VARIABLE_ACCESS
#define C_ATOMIC_VARIABLE_ACCESS 32U /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef C_PROCESSOR_TC297
#define C_PROCESSOR_TC297
#endif
#ifndef C_COMP_TASKING
#define C_COMP_TASKING
#endif
#ifndef C_GEN_GENERATOR_MSR
#define C_GEN_GENERATOR_MSR
#endif
#ifndef C_CPUTYPE_BITORDER_LSB2MSB
#define C_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/EcuC/EcucGeneral/BitOrder */
#endif
#ifndef C_CONFIGURATION_VARIANT_PRECOMPILE
#define C_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef C_CONFIGURATION_VARIANT_LINKTIME
#define C_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef C_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define C_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef C_CONFIGURATION_VARIANT
#define C_CONFIGURATION_VARIANT C_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef C_POSTBUILD_VARIANT_SUPPORT
#define C_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


#define V_DISABLE_USE_DUMMY_FUNCTIONS
#define V_ENABLE_USE_DUMMY_STATEMENT
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif /* __V_CFG_H__ */
/**********************************************************************************************************************
 *  END OF FILE: v_cfg.h
 *********************************************************************************************************************/    

