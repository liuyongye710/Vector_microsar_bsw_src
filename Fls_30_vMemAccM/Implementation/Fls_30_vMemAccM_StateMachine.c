/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Fls_30_vMemAccM_StateMachine.c
 *        \brief  Fls_30_vMemAccM state machine source file
 *
 *      \details  This is the implementation of the module Fls_30_vMemAccM_StateMachine
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define FLS_30_VMEMACCM_STATEMACHINE_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fls_30_vMemAccM_StateMachine.h"
#include "Fls_30_vMemAccM_Job.h"


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (FLS_30_VMEMACCM_LOCAL)/* COV_FLS_30_VMEMACCM_COMPATIBILITY */
# define FLS_30_VMEMACCM_LOCAL static
#endif

#if !defined (FLS_30_VMEMACCM_LOCAL_INLINE)/* COV_FLS_30_VMEMACCM_COMPATIBILITY */
# define FLS_30_VMEMACCM_LOCAL_INLINE LOCAL_INLINE
#endif


# define FLS_30_VMEMACCM_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */


typedef P2FUNC(void, AUTOMATIC, Fls_30_vMemAccM_StatePtrType)(void); /*!< Type of state function pointer to execute and store the state machine states */

FLS_30_VMEMACCM_LOCAL Fls_30_vMemAccM_StatePtrType Fls_30_vMemAccM_CurrentState;  /*!< Store the current state.*/

# define FLS_30_VMEMACCM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#define FLS_30_VMEMACCM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */


/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_StatePrepareNextvMemAccMJob
 *********************************************************************************************************************/
/*!
 * \brief       Execute state PrepareNextvMemAccMJob.
 * \details     Execute state PrepareNextvMemAccMJob.
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_StatePrepareNextvMemAccMJob(void);

/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_StateWaitForvMemAccM
 *********************************************************************************************************************/
/*!
 * \brief       Execute state WaitForvMemAccM.
 * \details     Execute state WaitForvMemAccM.
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_StateWaitForvMemAccM(void);

/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_StateIdle
 *********************************************************************************************************************/
/*!
 * \brief       Execute state Idle.
 * \details     Execute state Idle.
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_StateIdle(void);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_StatePrepareNextvMemAccMJob
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_StatePrepareNextvMemAccMJob(void)
{
  if (Fls_30_vMemAccM_Job_IsJobFinished() == TRUE)
  {
    Fls_30_vMemAccM_CurrentState = Fls_30_vMemAccM_StateMachine_StateIdle;
  }
  else
  {
    if (Fls_30_vMemAccM_Job_ProcessNextJobStep() == TRUE)
    {
      Fls_30_vMemAccM_CurrentState = Fls_30_vMemAccM_StateMachine_StateWaitForvMemAccM;
    }
    else
    {
      Fls_30_vMemAccM_CurrentState = Fls_30_vMemAccM_StateMachine_StateIdle;
    }   
  }
}

/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_StateWaitForvMemAccM
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_StateWaitForvMemAccM(void)
{
#if (FLS_30_VMEMACCM_POLLING_MODE == STD_ON)
  if (Fls_30_vMemAccM_Job_IsCurrentStepStillRunning() == FALSE)
  {
    Fls_30_vMemAccM_CurrentState = Fls_30_vMemAccM_StateMachine_StatePrepareNextvMemAccMJob;
  } 
#endif /* (FLS_30_VMEMACCM_POLLING_MODE == STD_ON) */
}

/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_StateIdle
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_StateIdle(void)
{
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_Init(void)
{
  Fls_30_vMemAccM_CurrentState = Fls_30_vMemAccM_StateMachine_StateIdle;
}

/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_SetBusy
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_SetBusy(void)
{

  Fls_30_vMemAccM_CurrentState = Fls_30_vMemAccM_StateMachine_StatePrepareNextvMemAccMJob;
}

/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_IsIdle
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_IsIdle(void)
{
  return Fls_30_vMemAccM_CurrentState == Fls_30_vMemAccM_StateMachine_StateIdle;
}

#if (FLS_30_VMEMACCM_POLLING_MODE == STD_ON)
/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_IsBusy
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_IsBusy(void)
{
  return Fls_30_vMemAccM_CurrentState == Fls_30_vMemAccM_StateMachine_StatePrepareNextvMemAccMJob;
}
#endif
/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_ExecuteState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_ExecuteState(void)
{
  Fls_30_vMemAccM_CurrentState(); /* SBSW_FLS_30_VMEMACCM_FUNCTIONPOINTER */
}

#define FLS_30_VMEMACCM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

/**********************************************************************************************************************
 *  END OF FILE: Fls_30_vMemAccM_StateMachine.c
 *********************************************************************************************************************/
