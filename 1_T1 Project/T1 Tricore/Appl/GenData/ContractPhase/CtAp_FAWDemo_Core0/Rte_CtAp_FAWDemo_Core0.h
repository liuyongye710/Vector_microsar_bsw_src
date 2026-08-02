/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Rte_CtAp_FAWDemo_Core0.h
 *        Config:  X:/Projects/FAW_OS/TASKING_V6.0r1/FAW_MultiCore297_Demo/01_MV4_ECU_V01/Workspace/Davinci_MultiCore_FAW/FAW_MultiCore297_Demo.dpa
 *     SW-C Type:  CtAp_FAWDemo_Core0
 *  Generated at:  Tue Jul 28 16:54:44 2020
 *
 *     Generator:  MICROSAR RTE Generator Version 4.18.0
 *                 RTE Core Version 1.18.0
 *       License:  Unlimited license CBD1600956 for China FAW Group Corporation
 *
 *   Description:  Application header file for SW-C <CtAp_FAWDemo_Core0> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_CTAP_FAWDEMO_CORE0_H
# define _RTE_CTAP_FAWDEMO_CORE0_H

# ifdef RTE_APPLICATION_HEADER_FILE
#  error Multiple application header files included.
# endif
# define RTE_APPLICATION_HEADER_FILE
# ifndef RTE_PTR2ARRAYBASETYPE_PASSING
#  define RTE_PTR2ARRAYBASETYPE_PASSING
# endif

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_CtAp_FAWDemo_Core0_Type.h"
# include "Rte_DataHandleType.h"


/**********************************************************************************************************************
 * Component Data Structures and Port Data Structures
 *********************************************************************************************************************/

struct Rte_CDS_CtAp_FAWDemo_Core0
{
  /* dummy entry */
  uint8 _dummy;
};

# define RTE_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONSTP2CONST(struct Rte_CDS_CtAp_FAWDemo_Core0, RTE_CONST, RTE_CONST) Rte_Inst_CtAp_FAWDemo_Core0; /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

typedef P2CONST(struct Rte_CDS_CtAp_FAWDemo_Core0, TYPEDEF, RTE_CONST) Rte_Instance;


# define CtAp_FAWDemo_Core0_START_SEC_CODE
# include "CtAp_FAWDemo_Core0_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *
 * Runnable Entity Name: Runnable1000ms_Core0
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 1s
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_Runnable1000ms_Core0 Runnable1000ms_Core0
FUNC(void, CtAp_FAWDemo_Core0_CODE) Runnable1000ms_Core0(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Runnable100ms_Core0
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 100ms
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_Runnable100ms_Core0 Runnable100ms_Core0
FUNC(void, CtAp_FAWDemo_Core0_CODE) Runnable100ms_Core0(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Runnable10ms_Core0
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_Runnable10ms_Core0 Runnable10ms_Core0
FUNC(void, CtAp_FAWDemo_Core0_CODE) Runnable10ms_Core0(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Runnable1ms_Core0
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 1ms
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_Runnable1ms_Core0 Runnable1ms_Core0
FUNC(void, CtAp_FAWDemo_Core0_CODE) Runnable1ms_Core0(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Runnable200ms_Core0
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 200ms
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_Runnable200ms_Core0 Runnable200ms_Core0
FUNC(void, CtAp_FAWDemo_Core0_CODE) Runnable200ms_Core0(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Runnable20ms_Core0
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 20ms
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_Runnable20ms_Core0 Runnable20ms_Core0
FUNC(void, CtAp_FAWDemo_Core0_CODE) Runnable20ms_Core0(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Runnable500ms_Core0
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 500ms
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_Runnable500ms_Core0 Runnable500ms_Core0
FUNC(void, CtAp_FAWDemo_Core0_CODE) Runnable500ms_Core0(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Runnable50ms_Core0
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 50ms
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_Runnable50ms_Core0 Runnable50ms_Core0
FUNC(void, CtAp_FAWDemo_Core0_CODE) Runnable50ms_Core0(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Runnable5ms_Core0
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 5ms
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_Runnable5ms_Core0 Runnable5ms_Core0
FUNC(void, CtAp_FAWDemo_Core0_CODE) Runnable5ms_Core0(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define CtAp_FAWDemo_Core0_STOP_SEC_CODE
# include "CtAp_FAWDemo_Core0_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_CTAP_FAWDEMO_CORE0_H */
