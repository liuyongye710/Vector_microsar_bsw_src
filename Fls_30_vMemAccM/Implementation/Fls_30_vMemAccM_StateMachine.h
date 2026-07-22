/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Fls_30_vMemAccM_StateMachine.h
 *        \brief  Fls_30_vMemAccM state machine header file
 *
 *      \details  Executes the states of the state machine.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (FLS_30_VMEMACCM_STATEMACHINE_H)
# define FLS_30_VMEMACCM_STATEMACHINE_H

#include "Std_Types.h"
#include "Fls_30_vMemAccM_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FLS_30_VMEMACCM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_Init
 *********************************************************************************************************************/
/*!
 * \brief       Sets the initial state (i.e idle).
 * \details     -
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_Init(void);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_SetBusy
 *********************************************************************************************************************/
/*!
 * \brief       Signals the state machine that there is something to do (i.e. new job arrived).
 * \details     Sets the state from idle to the first working state.
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_SetBusy(void);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_IsIdle
 *********************************************************************************************************************/
/*!
 * \brief       Checks if the state machine is idle.
 * \details     -
 * \return      TRUE:state machine is idle FALSE: state machine is not idle
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_IsIdle(void);

#if (FLS_30_VMEMACCM_POLLING_MODE == STD_ON)
/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_IsBusy
 *********************************************************************************************************************/
/*!
 * \brief       Checks if the state machine is busy.
 * \details     -
 * \return      TRUE:state machine is busy FALSE: state machine is not busy
 * \pre         POLLING mode enabled
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_IsBusy(void);
#endif

/**********************************************************************************************************************
 * Fls_30_vMemAccM_StateMachine_ExecuteState
 *********************************************************************************************************************/
/*!
 * \brief       Executes the current state machine state.
 * \details     -
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_StateMachine_ExecuteState(void);

#define FLS_30_VMEMACCM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

#endif /* FLS_30_VMEMACCM_STATEMACHINE_H */

/**********************************************************************************************************************
 *  END OF FILE: Fls_30_vMemAccM_StateMachine.h
 *********************************************************************************************************************/
