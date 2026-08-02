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
/*!        \file  vStreamProc_ProcessingNode_Hash.c
 *        \brief  vStreamProc Hash Sub Module Source Code File
 *      \details  Implementation of the Hash sub module for the vStreamProc framework
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
#define VSTREAMPROC_PROCESSINGNODE_HASH_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc_ProcessingNode_Hash.h"
#include "vStreamProc.h"
#include "vStreamProc_Port.h"

#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if (VSTREAMPROC_PROCESSINGNODE_HASH_CONFIG == STD_ON)
# include "Csm.h"

/**********************************************************************************************************************
 *  DEFINES
 *********************************************************************************************************************/
# define MAXIMUM_HASH_LENGTH 64u

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined (VSTREAMPROC_LOCAL)
#  define VSTREAMPROC_LOCAL static
# endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VSTREAMPROC_START_SEC_CODE
# include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Hash_WriteResult()
 **********************************************************************************************************************/
/*! \brief        Writes the hash result to the output StorageNode.
 *  \details      -
 *  \param[in]    NodeInfo            The processing node information to operate on.
 *  \param[in]    HashValue           Pointer to Hash result
 *  \param[in]    HashLength          Length of the Hash result.
 *  \return       VSTREAMPROC_OK                    Operation succeeded.
 *  \return       VSTREAMPROC_FAILED                Operation failed.
 *  \return       VSTREAMPROC_INSUFFICIENT_OUTPUT   Not enough buffer available to report result.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Hash_WriteResult(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo,
  P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) HashValue,
  uint32 HashLength);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Hash_WriteResult
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Hash_WriteResult(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo,
  P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) HashValue,
  uint32 HashLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType          retVal = VSTREAMPROC_FAILED;
  vStreamProc_OutputPortInfoType  outputPortInfo;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write the passed hash value to the output port. */
  if (vStreamProc_PrepareOutputPortInfo(NodeInfo, vStreamProcConf_Internal_HashNode_OutputData, &outputPortInfo) == VSTREAMPROC_OK)
  {
    retVal = vStreamProc_RequestOutputPortData(NodeInfo, vStreamProcConf_vStreamProcDataType_uint8, HashLength, &outputPortInfo);
  }

  if (retVal == VSTREAMPROC_OK)
  {
    P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) outputBuffer = vStreamProc_GetTypedWriteRequestBuffer_uint8(&outputPortInfo.WriteRequest);
    vStreamProc_StorageNodeBufferIterType index;

    /* Copy hash value to output buffer. */
    for (index = 0u; index < HashLength; index++)
    {
      outputBuffer[index] = HashValue[index];
    }

    /* Acknowledge the write. */
    retVal = vStreamProc_AcknowledgeOutputPort(NodeInfo, HashLength, TRUE, &outputPortInfo);
  }

  return retVal;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Hash_Init
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Hash_Init(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;
  P2VAR(vStreamProc_Hash_StateType, AUTOMATIC, VSTREAMPROC_APPL_CONST) hashState;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's workspace */
  /* PRQA S 0316 1 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  hashState = vStreamProc_GetTypedWorkspaceOfProcessingNode_Hash_StateType(NodeInfo);

  /* #10 Initialize state value of workspace. */
  *hashState = VSTREAMPROC_WS_STATE_INITIALIZED;

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Hash_Process
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Hash_Process(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType  retVal = VSTREAMPROC_FAILED;
  Std_ReturnType          stdRetVal;

  P2CONST(vStreamProc_ProcessingNode_Hash_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) specializedCfgPtr;
  P2VAR(vStreamProc_Hash_StateType, AUTOMATIC, VSTREAMPROC_APPL_CONST) hashState;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's configuration and workspace. */
  /* PRQA S 0316 2 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  specializedCfgPtr = vStreamProc_GetTypedConfigOfProcessingNode_Hash_Config(NodeInfo);
  hashState = vStreamProc_GetTypedWorkspaceOfProcessingNode_Hash_StateType(NodeInfo);

  if (*hashState == VSTREAMPROC_WS_STATE_INITIALIZED)
  {
    /* #10 Initialize the processing node's hash calculation. */
    stdRetVal = Csm_Hash(specializedCfgPtr->CsmJobIdOfProcessingNode_Hash_Config, CRYPTO_OPERATIONMODE_START,
      NULL_PTR, 0u, NULL_PTR, NULL_PTR);

    /* In case everything went fine set next state. */
    if (stdRetVal == E_OK)
    {
      *hashState = VSTREAMPROC_WS_STATE_PROCESSING;
    }
  }

  if (*hashState == VSTREAMPROC_WS_STATE_PROCESSING)
  {
    vStreamProc_InputPortInfoType   inputPortInfo;

    if (vStreamProc_PrepareInputPortInfo(NodeInfo, vStreamProcConf_Internal_HashNode_InputData, &inputPortInfo) == VSTREAMPROC_OK)
    {
      retVal = vStreamProc_RequestInputPortData(NodeInfo, vStreamProcConf_vStreamProcDataType_uint8, 0u, &inputPortInfo);
    }

    if (retVal == VSTREAMPROC_OK)
    {
      vStreamProc_LengthType availableLength = inputPortInfo.ReadRequest.StorageInfo.AvailableLength;

      if (availableLength > 0u)
      {
        /* #20 Update the CSM with the available data and acknowledge the handled data. */
        stdRetVal = Csm_Hash(specializedCfgPtr->CsmJobIdOfProcessingNode_Hash_Config,
                                  CRYPTO_OPERATIONMODE_UPDATE, vStreamProc_GetTypedReadRequestBuffer_uint8(&inputPortInfo.ReadRequest), availableLength,
                                  NULL_PTR, NULL_PTR);

        if (stdRetVal == E_OK)
        {
          retVal = vStreamProc_AcknowledgeInputPort(NodeInfo, availableLength, TRUE, &inputPortInfo);
        }
        else
        {
          (void)vStreamProc_ReleaseAllPorts(NodeInfo);
          retVal = VSTREAMPROC_FAILED;
        }
      }
    }
  }

  return retVal;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Hash_Flush
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
  */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Hash_Flush(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  P2CONST(vStreamProc_ProcessingNode_Hash_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) specializedCfgPtr;

  /* ----- Implementation ----------------------------------------------- */
  /* PRQA S 0316 2 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  specializedCfgPtr = vStreamProc_GetTypedConfigOfProcessingNode_Hash_Config(NodeInfo);

  /* #10 Process any pending input. */
  retVal = vStreamProc_ProcessingNode_Hash_Process(NodeInfo);

  if (retVal == VSTREAMPROC_OK)
  {
    uint32  resultLength = MAXIMUM_HASH_LENGTH;
    uint8   hashValue[MAXIMUM_HASH_LENGTH];

    /* #20 Finalize the hash calculation and write result to the output port. */
    if (Csm_Hash(specializedCfgPtr->CsmJobIdOfProcessingNode_Hash_Config, CRYPTO_OPERATIONMODE_FINISH, NULL_PTR, 0u, &(hashValue[0u]), &resultLength) == E_OK)
    {
      retVal = vStreamProc_ProcessingNode_Hash_WriteResult(NodeInfo, &(hashValue[0u]), resultLength);
    }
    else
    {
      retVal = VSTREAMPROC_FAILED;
    }
  }

  return retVal;
}

# define VSTREAMPROC_STOP_SEC_CODE
# include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (VSTREAMPROC_PROCESSINGNODE_HASH_CONFIG == STD_ON) */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* Justification for module-specific MISRA deviations:
 */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_ProcessingNode_Hash.c
 *********************************************************************************************************************/
