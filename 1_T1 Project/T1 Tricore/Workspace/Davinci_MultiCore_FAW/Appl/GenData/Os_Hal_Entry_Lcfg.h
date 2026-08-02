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
 *              File: Os_Hal_Entry_Lcfg.h
 *   Generation Time: 2020-07-28 15:56:23
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_HAL_ENTRY_LCFG_H)                                                   /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_HAL_ENTRY_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */

/* Os kernel module dependencies */

/* Os hal dependencies */
# include "Os_Hal_Core_Types.h"
# include "Os_Hal_Compiler.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/




/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define OS_START_SEC_INTVEC_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern uint8 _OS_INTVEC_CODE_START[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */
extern uint8 _OS_INTVEC_CODE_END[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */

# define OS_STOP_SEC_INTVEC_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_EXCVEC_CORE0_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern uint8 _OS_EXCVEC_CORE0_CODE_START[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */
extern uint8 _OS_EXCVEC_CORE0_CODE_END[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */

# define OS_STOP_SEC_EXCVEC_CORE0_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_INTVEC_CORE0_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern uint8 _OS_INTVEC_CORE0_CODE_START[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */
extern uint8 _OS_INTVEC_CORE0_CODE_END[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */

# define OS_STOP_SEC_INTVEC_CORE0_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_EXCVEC_CORE1_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern uint8 _OS_EXCVEC_CORE1_CODE_START[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */
extern uint8 _OS_EXCVEC_CORE1_CODE_END[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */

# define OS_STOP_SEC_EXCVEC_CORE1_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_INTVEC_CORE1_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern uint8 _OS_INTVEC_CORE1_CODE_START[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */
extern uint8 _OS_INTVEC_CORE1_CODE_END[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */

# define OS_STOP_SEC_INTVEC_CORE1_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_EXCVEC_CORE2_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern uint8 _OS_EXCVEC_CORE2_CODE_START[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */
extern uint8 _OS_EXCVEC_CORE2_CODE_END[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */

# define OS_STOP_SEC_EXCVEC_CORE2_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_INTVEC_CORE2_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern uint8 _OS_INTVEC_CORE2_CODE_START[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */
extern uint8 _OS_INTVEC_CORE2_CODE_END[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */

# define OS_STOP_SEC_INTVEC_CORE2_CODE
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* OS_HAL_ENTRY_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Entry_Lcfg.h
 *********************************************************************************************************************/
