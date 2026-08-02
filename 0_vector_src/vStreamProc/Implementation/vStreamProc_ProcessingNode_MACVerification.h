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
/*!        \file  vStreamProc_ProcessingNode_MACVerification.h
 *        \brief  vStreamProc MAC Verification Sub Module Header File
 *
 *      \details  Header file of the vStreamProc mac verification sub module.
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
#if !defined (VSTREAMPROC_PROCESSINGNODE_MAC_VERIFICATION_H)
# define VSTREAMPROC_PROCESSINGNODE_MAC_VERIFICATION_H

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
 *  vStreamProc_ProcessingNode_MACVerification_Init()
 *********************************************************************************************************************/
/*!
 *  \brief          Initializes the passed node.
 *  \details        -
 *  \param[in]      NodeInfo        The processing node information to operate on.
 *  \return         E_OK            Initialization was successful
 *  \return         E_NOT_OK        Initialization was unsuccessful
 *
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-211279
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_MACVerification_Init(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo);

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_MACVerification_Process()
 *********************************************************************************************************************/
/*!
 *  \brief          Processes the passed node.
 *  \details        This node calculates a mac value based on handled data and compares it with the passed 
 *                  reference data. It does not generate the result output data unless it is flushed.
 *  \param[in]      NodeInfo                        The processing node information to operate on.
 *  \return         VSTREAMPROC_OK                  Process has handled the available input data
 *  \return         VSTREAMPROC_FAILED              Process failed
 *  \return         VSTREAMPROC_INSUFFICIENT_INPUT  Process not possible due to insufficient input data
 *
 *  \pre            vStreamProc_ProcessingNode_MACVerification_Init() must be called before.
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-211279
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_MACVerification_Process(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo);

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_MACVerification_Flush()
 *********************************************************************************************************************/
/*!
 *  \brief          Flushes the passed node.
 *  \details        -
 *  \param[in]      NodeInfo                        The processing node information to operate on.
 *  \return         VSTREAMPROC_OK                  Flush was successful - MAC verification result was generated
 *  \return         VSTREAMPROC_PENDING             Flush is not yet finished
 *  \return         VSTREAMPROC_FAILED              Flush failed due to an internal error
 *  \return         VSTREAMPROC_INSUFFICIENT_OUTPUT Node can not be flushed due to limited output buffer
 *
 *  \pre            vStreamProc_ProcessingNode_MACVerification_Init() must be called before.
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-211279
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_MACVerification_Flush(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo);

# define VSTREAMPROC_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSTREAMPROC_PROCESSINGNODE_MAC_VERIFICATION_H */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_ProcessingNode_MACVerification.h
 *********************************************************************************************************************/
