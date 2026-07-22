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
/*!        \file  vStreamProc_ProcessingNode_Trigger.h
 *        \brief  vStreamProc Trigger Processing Node Header File
 *
 *      \details  Header file of the vStreamProc Trigger Processing Node module.
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
#if !defined (VSTREAMPROC_PROCESSINGNODE_TRIGGER_H)
# define VSTREAMPROC_PROCESSINGNODE_TRIGGER_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vStreamProc_Types.h"

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

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VSTREAMPROC_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Trigger_Init()
 *********************************************************************************************************************/
/*!
 *  \brief          Initializes the passed node.
 *  \details        -
 *  \param[in]      NodeInfo        The processing node information to operate on.
 *  \return         E_OK            Initialization was successful
 *  \return         E_NOT_OK        Initialization was unsuccessful
 *
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-227190
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Trigger_Init(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo);

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Trigger_Process()
 *********************************************************************************************************************/
/*!
 *  \brief          Processes the passed node.
 *  \details        Performs the compare functionality
 *  \param[in]      NodeInfo                        The processing node information to operate on.
 *  \return         VSTREAMPROC_OK                  Process has compared the available input data
 *  \return         VSTREAMPROC_FAILED              Process failed
 *  \return         VSTREAMPROC_INSUFFICIENT_INPUT  Process not possible due to insufficient input data
 *  \return         VSTREAMPROC_INSUFFICIENT_OUTPUT Process not possible due to limited output buffer
 *
 *  \pre            vStreamProc_ProcessingNode_Trigger_Init() must be called before.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-227190
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Trigger_Process(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo);

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Trigger_Flush()
 *********************************************************************************************************************/
/*!
 *  \brief          Flushes the passed node.
 *  \details        -
 *  \param[in]      NodeInfo                        The processing node information to operate on.
 *  \return         VSTREAMPROC_OK                  Flush was successful
 *  \return         VSTREAMPROC_PENDING             Flush is not yet finished
 *  \return         VSTREAMPROC_FAILED              Flush failed due to an internal error
 *  \return         VSTREAMPROC_INSUFFICIENT_OUTPUT Node can not be flushed due to limited output buffer
 *
 *  \pre            vStreamProc_ProcessingNode_Trigger_Init() must be called before.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-227190
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Trigger_Flush(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo);

# define VSTREAMPROC_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSTREAMPROC_PROCESSINGNODE_TRIGGER_H */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_ProcessingNode_Trigger.h
 *********************************************************************************************************************/
