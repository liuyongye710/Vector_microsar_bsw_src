/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vStreamProc_Scheduler.h
 *        \brief  vStreamProc Scheduler Sub Module Header File
 *
 *      \details  Header file of the vStreamProc Scheduler sub module.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vStreamProc.h.
 *********************************************************************************************************************/
# if !defined (VSTREAMPROC_SCHEDULER_H)
# define VSTREAMPROC_SCHEDULER_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "vStreamProc_Types.h"
# include "vStreamProc_Lcfg.h"
# include "vStreamProc_CfgTypes.h"

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

# define VSTREAMPROC_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vStreamProc_Scheduler_Init()
 *********************************************************************************************************************/
/*!
 * \brief         Initializes the passed scheduler.
 * \details       -
 * \param[in]     SchedulerId   Id of the scheduler workspace.
 * \return        E_OK          Initialization was successful.
 * \return        E_NOT_OK      Initialization failed
 * \pre           Must be called before call of any vStreamProc_Scheduler function
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Scheduler_Init(
  CONST(vStreamProc_SchedulerIterType, AUTOMATIC) SchedulerId);

/**********************************************************************************************************************
 *  vStreamProc_Scheduler_Process()
 *********************************************************************************************************************/
/*!
 * \brief         Starts the executing of the given scheduler.
 * \details       Loops over the scheduler entries and process the ProcessingNodes.
 * \param[in]     SchedulerId                      Id of the scheduler workspace. Parameter must not be NULL
 * \return        VSTREAMPROC_OK                 The scheduler is idle
 * \return        VSTREAMPROC_PENDING              The scheduler is pending and needs to be called again
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT   The scheduler was disturbed due to insufficient input data 
 *                                                 of an entry point
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT  The scheduler was disturbed due to insufficient output data 
 *                                                 of an exit point 
 * \return        VSTREAMPROC_FAILED   The scheduler failed
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Scheduler_Process(
  CONST(vStreamProc_SchedulerIterType, AUTOMATIC) SchedulerId);

/**********************************************************************************************************************
 *  vStreamProc_Scheduler_HandleStreamAvailableCallout()
 *********************************************************************************************************************/
/*!
 * \brief        Handles the stream available callout of a storage node.
 * \details      The scheduler adds the provided node to its schedule table
 * \param[in]    NodeId               Id of the storage node that issued the callout
 * \param[in]    SchedulerId          Id of the associated scheduler
 * \pre          -
 * \note         The additional argument shall be a pointer to a scheduler.
 * \context      TASK|ISR
 * \reentrant    TRUE
 * \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, VSTREAMPROC_CODE) vStreamProc_Scheduler_HandleStreamAvailableCallout(
  CONST(vStreamProc_NodeIdType, AUTOMATIC) NodeId,
  CONST(vStreamProc_SchedulerIdType, AUTOMATIC) SchedulerId);

/**********************************************************************************************************************
 *  vStreamProc_Scheduler_HandleDataAvailableCallout()
 *********************************************************************************************************************/
/*!
 * \brief        Handles the data available callout of a storage node.
 * \details      The scheduler adds the given consumer to the its schedule table.
 * \param[in]    OutputPortId         Id of the output port that caused the callout
 * \param[in]    SchedulerId          Id of the associated scheduler
 * \pre          -
 * \note         The additional argument shall be a pointer to a scheduler.
 * \context      TASK|ISR
 * \reentrant    TRUE
 * \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, VSTREAMPROC_CODE) vStreamProc_Scheduler_HandleDataAvailableCallout(
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortId,
  CONST(vStreamProc_SchedulerIdType, AUTOMATIC) SchedulerId);

/**********************************************************************************************************************
 *  vStreamProc_Scheduler_HandleStorageAvailableCallout()
 *********************************************************************************************************************/
/*!
 * \brief        Handles the storage available callout of a storage node.
 * \details      The scheduler adds the given producer to the its schedule table.
 * \param[in]    InputPortId          Id of the input port that caused the callout
 * \param[in]    SchedulerId          Id of the associated scheduler
 * \pre          -
 * \note         The additional argument shall be a pointer to a scheduler.
 * \context      TASK|ISR
 * \reentrant    TRUE
 * \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, VSTREAMPROC_CODE) vStreamProc_Scheduler_HandleStorageAvailableCallout(
  vStreamProc_InputPortIdType InputPortId,
  CONST(vStreamProc_SchedulerIdType, AUTOMATIC) SchedulerId);

/**********************************************************************************************************************
 *  vStreamProc_Scheduler_RemoveFromScheduleTable()
 *********************************************************************************************************************/
/*!
 * \brief         Removes a passed node from the schedule table
 * \details       The scheduler removes the passed node from its schedule table.
 * \param[in]     SchedulerId     Id of a scheduler workspace.
 * \param[in]     NodeToRemove    Id of the node which should be removed from the schedule table
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, AUTOMATIC) vStreamProc_Scheduler_RemoveFromScheduleTable(
  CONST(vStreamProc_SchedulerIterType, AUTOMATIC) SchedulerId,
  CONST(vStreamProc_NodeIterType, AUTOMATIC) NodeToRemove);

/**********************************************************************************************************************
 *  vStreamProc_Scheduler_IsStarvedInputPortConnectedToEntryPoint
 *********************************************************************************************************************/
/*!
 * \brief         Check if a starved input port of the passed node is connected to an entry point.
 * \details       Port is starved, if the specific result is VSTREAMPROC_INSUFFICIENT_INPUT.
 * \param[in]     ProcNodeInfo    Information structure of the processing node.
 * \return        TRUE   Starved input port of the passed node is connected to an entry point
 * \return        FALSE  No starved input port of the passed node is connected to an entry point.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(boolean, AUTOMATIC) vStreamProc_Scheduler_IsStarvedInputPortConnectedToEntryPoint(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo);

/**********************************************************************************************************************
 *  vStreamProc_Scheduler_IsStarvedOutputPortConnectedToExitPoint
 *********************************************************************************************************************/
/*!
 * \brief         Check if a starved output port of the passed node is connected to an exit point.
 * \details       Port is starved, if the specific result is VSTREAMPROC_INSUFFICIENT_OUTPUT.
 * \param[in]     ProcNodeInfo    Information structure of the processing node.
 * \return        TRUE   Starved output port of the passed node is connected to an exit point
 * \return        FALSE  No starved output port of the passed node is connected to an exit point.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(boolean, AUTOMATIC) vStreamProc_Scheduler_IsStarvedOutputPortConnectedToExitPoint(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo);

# define VSTREAMPROC_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# endif /* VSTREAMPROC_SCHEDULER_H */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_Scheduler.h
 *********************************************************************************************************************/
