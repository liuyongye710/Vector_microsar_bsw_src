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
/*!        \file  vStreamProc_ProcessingNode_Copy.c
 *        \brief  vStreamProc Copy Sub Module Source Code File
 *      \details  Implementation of the Copy sub module for the vStreamProc framework.
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
#define VSTREAMPROC_PROCESSINGNODE_BYTE_COMPARE_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc.h"
#include "vStreamProc_Port.h"

#if defined(vStreamProcConf_External_vStreamProcProcessingNode_Copy_InputData)
# include "vStreamProc_ProcessingNode_Copy.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

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

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Copy_Init
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Copy_Init(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Fetch and initialize the workspace. */
  VSTREAMPROC_DUMMY_STATEMENT_CONST(NodeInfo);                                                                          /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */

  return E_OK;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Copy_Process
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Copy_Process(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType          retVal = VSTREAMPROC_FAILED;

  vStreamProc_InputPortInfoType   inputPortInfo;
  vStreamProc_OutputPortInfoType  outputPortInfo;

  vStreamProc_StorageInfoPtrType  inputStorageInfo  = &inputPortInfo.ReadRequest.StorageInfo;
  vStreamProc_StorageInfoPtrType  outputStorageInfo = &outputPortInfo.WriteRequest.StorageInfo;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get input and output information. */
  if (vStreamProc_PrepareAllPortInfos(NodeInfo, &inputPortInfo, 1u, &outputPortInfo, 1u) == VSTREAMPROC_OK)
  {
    retVal = vStreamProc_GetPortInfos(NodeInfo, &inputPortInfo, 1u, &outputPortInfo, 1u);
  }

  if (retVal == VSTREAMPROC_OK)
  {
    retVal = VSTREAMPROC_FAILED;

    /* Data types of input and output must match. */
    if (inputStorageInfo->DataTypeInfo.Id == outputStorageInfo->DataTypeInfo.Id)
    {
      vStreamProc_LengthType  inputLength = inputStorageInfo->AvailableLength;
      vStreamProc_LengthType  maxDataToCopy;

      /* #20 Copy as much data as possible. */
      if (outputStorageInfo->AvailableLength < inputLength)
      {
        maxDataToCopy = outputStorageInfo->AvailableLength;
      }
      else
      {
        maxDataToCopy = inputLength;
      }

      inputStorageInfo->RequestLength   = maxDataToCopy;
      outputStorageInfo->RequestLength  = maxDataToCopy;

      if (vStreamProc_RequestPortData(NodeInfo, &inputPortInfo, 1u, &outputPortInfo, 1u) == VSTREAMPROC_OK)
      {
        P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) inputBuffer   = inputPortInfo.ReadRequest.Buffer;
        P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR)   outputBuffer  = outputPortInfo.WriteRequest.Buffer;
        vStreamProc_StorageNodeBufferIterType           index;

        /* Perform byte-wise copy. */
        maxDataToCopy *= inputStorageInfo->DataTypeInfo.Size;

        /* #30 Copy data from one StorageNode to another. */
        for (index = 0; index < maxDataToCopy; index++)
        {
          outputBuffer[index] = inputBuffer[index];
        }

        if (vStreamProc_AcknowledgePorts(NodeInfo, &inputPortInfo, 1u, &outputPortInfo, 1u) == VSTREAMPROC_OK)
        {
          if (inputLength == maxDataToCopy)
          {
            retVal = VSTREAMPROC_OK;
          }
          else if (maxDataToCopy == 0u)
          {
            retVal = VSTREAMPROC_INSUFFICIENT_OUTPUT;
          }
          else
          {
            retVal = VSTREAMPROC_PENDING;
          }
        }
      }
    }
  }

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Copy_Flush
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Copy_Flush(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy data from one StorageNode to another */
  retVal = vStreamProc_ProcessingNode_Copy_Process(NodeInfo);

  return retVal;
}

# define VSTREAMPROC_STOP_SEC_CODE
# include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* vStreamProcConf_External_vStreamProcProcessingNode_Copy_InputData */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* Justification for module-specific MISRA deviations:
*/

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_ProcessingNode_Copy.c
 *********************************************************************************************************************/
