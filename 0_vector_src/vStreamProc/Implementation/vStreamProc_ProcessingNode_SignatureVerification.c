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
/*!        \file  vStreamProc_ProcessingNode_SignatureVerification.c
 *        \brief  vStreamProc Hash Sub Module Source Code File
 *      \details  Implementation of the signature verification sub module for the vStreamProc framework
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
#define VSTREAMPROC_PROCESSINGNODE_SIGNATURE_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc_ProcessingNode_SignatureVerification.h"
#include "vStreamProc.h"
#include "vStreamProc_Port.h"

#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if (VSTREAMPROC_PROCESSINGNODE_SIGNATUREVERIFICATION_CONFIG == STD_ON)
# include "Csm.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined (VSTREAMPROC_LOCAL)
# define VSTREAMPROC_LOCAL static
#endif

#define VSTREAMPROC_SIGNATURE_VERIFICATION_RESULT_LENGTH 1u

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
 *  vStreamProc_ProcessingNode_SignatureVerification_Init
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_SignatureVerification_Init(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;
  P2VAR(vStreamProc_SignatureVerification_StateType, AUTOMATIC, VSTREAMPROC_APPL_CONST) sigState;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's workspace. */
  /* PRQA S 0316 1 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  sigState = vStreamProc_GetTypedWorkspaceOfProcessingNode_SignatureVerification_StateType(NodeInfo);

  /* #10 Initialize state value of workspace. */
  *sigState = VSTREAMPROC_WS_STATE_INITIALIZED;

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_SignatureVerification_Process
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_SignatureVerification_Process(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType  retVal = VSTREAMPROC_FAILED;
  Std_ReturnType          csmResult;

  P2CONST(vStreamProc_ProcessingNode_SignatureVerification_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) specializedCfgPtr;
  P2VAR(vStreamProc_SignatureVerification_StateType, AUTOMATIC, VSTREAMPROC_APPL_CONST) sigState;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's configuration and workspace. */
  /* PRQA S 0316 2 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  specializedCfgPtr = vStreamProc_GetTypedConfigOfProcessingNode_SignatureVerification_Config(NodeInfo);
  sigState = vStreamProc_GetTypedWorkspaceOfProcessingNode_SignatureVerification_StateType(NodeInfo);

  if (*sigState == VSTREAMPROC_WS_STATE_INITIALIZED)
  {
    /* #10 Initialize the processing node's signature verification. */
    csmResult = Csm_SignatureVerify(specializedCfgPtr->CsmJobIdOfProcessingNode_SignatureVerification_Config,
      CRYPTO_OPERATIONMODE_START, NULL_PTR, 0u,
      NULL_PTR, 0u, NULL_PTR);

    /* In case everything went fine set next state. */
    if (csmResult == E_OK)
    {
      *sigState = VSTREAMPROC_WS_STATE_PROCESSING;
    }
  }

  if (*sigState == VSTREAMPROC_WS_STATE_PROCESSING)
  {
    vStreamProc_InputPortInfoType inputPortInfo;

    if (vStreamProc_PrepareInputPortInfo(NodeInfo, vStreamProcConf_Internal_SignatureVerificationNode_InputData, &inputPortInfo) == VSTREAMPROC_OK)
    {
      retVal = vStreamProc_RequestInputPortData(NodeInfo, vStreamProcConf_vStreamProcDataType_uint8, 0u, &inputPortInfo);
    }

    if (retVal == VSTREAMPROC_OK)
    {
      vStreamProc_LengthType availableLength = inputPortInfo.ReadRequest.StorageInfo.AvailableLength;

      if (availableLength > 0u)
      {
        /* #20 Update the CSM with the available data. */
        csmResult = Csm_SignatureVerify(specializedCfgPtr->CsmJobIdOfProcessingNode_SignatureVerification_Config,
          CRYPTO_OPERATIONMODE_UPDATE, vStreamProc_GetTypedReadRequestBuffer_uint8(&inputPortInfo.ReadRequest), availableLength,
          NULL_PTR, 0u, NULL_PTR);

        retVal = vStreamProc_AcknowledgeInputPort(NodeInfo, availableLength, TRUE, &inputPortInfo);

        if (csmResult != E_OK)
        {
          retVal = VSTREAMPROC_FAILED;
        }
      }
    }
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_SignatureVerification_Flush
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_SignatureVerification_Flush(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  P2CONST(vStreamProc_ProcessingNode_SignatureVerification_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) specializedCfgPtr;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's configuration and workspace */
  /* PRQA S 0316 2 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  specializedCfgPtr = vStreamProc_GetTypedConfigOfProcessingNode_SignatureVerification_Config(NodeInfo);

  /* #10 Process any pending input. */
  retVal = vStreamProc_ProcessingNode_SignatureVerification_Process(NodeInfo);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #20 Fetch the reference signature value, finalize the signature verification and propagate the result. */
    vStreamProc_InputPortInfoType   sigReferencePortInfo;
    vStreamProc_OutputPortInfoType  sigResultPortInfo;

    vStreamProc_StorageInfoPtrType  sigReferenceStorageInfo = &sigReferencePortInfo.ReadRequest.StorageInfo;
    vStreamProc_StorageInfoPtrType  sigResultStorageInfo    = &sigResultPortInfo.WriteRequest.StorageInfo;

    sigReferencePortInfo.SymbolicPortName = vStreamProcConf_Internal_SignatureVerificationNode_SignatureReferenceData;
    sigResultPortInfo.SymbolicPortName    = vStreamProcConf_Internal_SignatureVerificationNode_ResultData;

    retVal = vStreamProc_PreparePortInfos(NodeInfo, &sigReferencePortInfo, 1u, &sigResultPortInfo, 1u);

    if (retVal == VSTREAMPROC_OK)
    {
      /* Issue a read request to get the reference signature. */
      sigReferenceStorageInfo->RequestLength    = 1u;
      sigReferenceStorageInfo->DataTypeInfo.Id  = vStreamProcConf_vStreamProcDataType_uint8;
      sigResultStorageInfo->RequestLength       = VSTREAMPROC_SIGNATURE_VERIFICATION_RESULT_LENGTH;
      sigResultStorageInfo->DataTypeInfo.Id     = vStreamProcConf_vStreamProcDataType_Std_ReturnType;

      retVal = vStreamProc_RequestPortData(NodeInfo, &sigReferencePortInfo, 1u, &sigResultPortInfo, 1u);
    }

    if (retVal == VSTREAMPROC_OK)
    {
      Std_ReturnType          csmResult;
      Crypto_VerifyResultType sigResultValue  = CRYPTO_E_VER_NOT_OK;
      vStreamProc_LengthType  availableLength = sigReferenceStorageInfo->AvailableLength;
      uint8                   dummy           = 0;

      /* Finalize the signature verification. */
      csmResult = Csm_SignatureVerify(
        specializedCfgPtr->CsmJobIdOfProcessingNode_SignatureVerification_Config, CRYPTO_OPERATIONMODE_FINISH,
        &dummy, 0u, vStreamProc_GetTypedReadRequestBuffer_uint8(&sigReferencePortInfo.ReadRequest), availableLength, &sigResultValue);

      if (csmResult == E_OK)
      {
        P2VAR(Std_ReturnType, AUTOMATIC, VSTREAMPROC_APPL_VAR) outputBuffer =
          vStreamProc_GetTypedWriteRequestBuffer_Std_ReturnType(&sigResultPortInfo.WriteRequest);
        Std_ReturnType sigVerifyResult;

        if (sigResultValue == CRYPTO_E_VER_OK)
        {
          sigVerifyResult = E_OK;
        }
        else
        {
          sigVerifyResult = E_NOT_OK;
        }

        /* Propagate the result. */
        /* Copy signature verification result to storage node. */
        outputBuffer[0u] = sigVerifyResult;

        sigReferenceStorageInfo->RequestLength = availableLength;

        retVal = vStreamProc_AcknowledgePorts(NodeInfo, &sigReferencePortInfo, 1u, &sigResultPortInfo, 1u);
      }
      else
      {
        (void)vStreamProc_ReleaseAllPorts(NodeInfo);
        retVal = VSTREAMPROC_FAILED;
      }
    }
  }

  return retVal;
} /* PRQA S 6050  */ /* MD_MSR_STCAL */

# define VSTREAMPROC_STOP_SEC_CODE
# include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (VSTREAMPROC_PROCESSINGNODE_SIGNATUREVERIFICATION_CONFIG == STD_ON) */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* Justification for module-specific MISRA deviations:
 */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_ProcessingNode_SignatureVerification.c
 *********************************************************************************************************************/
