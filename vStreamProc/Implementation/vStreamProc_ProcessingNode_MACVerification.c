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
/*!        \file  vStreamProc_ProcessingNode_MACVerification.c
 *        \brief  vStreamProc MAC Verification Sub Module Source Code File
 *      \details  Implementation of the MAC verification sub module for the vStreamProc framework
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
#define VSTREAMPROC_PROCESSINGNODE_MAC_VERIFICATION_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc_ProcessingNode_MACVerification.h"
#include "vStreamProc.h"
#include "vStreamProc_Port.h"

#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if (VSTREAMPROC_PROCESSINGNODE_MACVERIFICATION_CONFIG == STD_ON)
# include "Csm.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined (VSTREAMPROC_LOCAL)
#  define VSTREAMPROC_LOCAL static
# endif

# define VSTREAMPROC_MAC_VERIFICATION_RESULT_LENGTH 1u

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
 *  vStreamProc_ProcessingNode_MACVerification_Init
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_MACVerification_Init(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;
  P2VAR(vStreamProc_MACVerification_StateType, AUTOMATIC, VSTREAMPROC_APPL_VAR) macState;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's workspace. */
  /* PRQA S 0316 1 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  macState = vStreamProc_GetTypedWorkspaceOfProcessingNode_MACVerification_StateType(NodeInfo);

  /* #10 Initialize state value of workspace. */
  *macState = VSTREAMPROC_WS_STATE_INITIALIZED;

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_MACVerification_Process
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_MACVerification_Process(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType    retVal = VSTREAMPROC_FAILED;
  Std_ReturnType            csmResult;

  P2CONST(vStreamProc_ProcessingNode_MACVerification_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) specializedCfgPtr;
  P2VAR(vStreamProc_MACVerification_StateType, AUTOMATIC, VSTREAMPROC_APPL_VAR) macState;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's configuration and workspace. */
  /* PRQA S 0316 2 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  specializedCfgPtr = vStreamProc_GetTypedConfigOfProcessingNode_MACVerification_Config(NodeInfo);
  macState = vStreamProc_GetTypedWorkspaceOfProcessingNode_MACVerification_StateType(NodeInfo);

  if (*macState == VSTREAMPROC_WS_STATE_INITIALIZED)
  {
    /* #10 Initialize the processing node's MAC verification. */
    csmResult = Csm_MacVerify(specializedCfgPtr->CsmJobIdOfProcessingNode_MACVerification_Config,
                           CRYPTO_OPERATIONMODE_START, NULL_PTR, 0u,
                           NULL_PTR, 0u, NULL_PTR);

    /* In case everything went fine set next state. */
    if (csmResult == E_OK)
    {
      *macState = VSTREAMPROC_WS_STATE_PROCESSING;
    }
  }

  if (*macState == VSTREAMPROC_WS_STATE_PROCESSING)
  {
    vStreamProc_InputPortInfoType   inputPortInfo;

    if (vStreamProc_PrepareInputPortInfo(NodeInfo, vStreamProcConf_Internal_MACVerificationNode_InputData, &inputPortInfo) == VSTREAMPROC_OK)
    {
      retVal = vStreamProc_RequestInputPortData(NodeInfo, vStreamProcConf_vStreamProcDataType_uint8, 0u, &inputPortInfo);
    }

    if (retVal == VSTREAMPROC_OK)
    {
      vStreamProc_LengthType availableLength = inputPortInfo.ReadRequest.StorageInfo.AvailableLength;

      if (availableLength > 0u)
      {
        /* #20 Update the MAC verification calculation based on the available data. */
        csmResult = Csm_MacVerify(specializedCfgPtr->CsmJobIdOfProcessingNode_MACVerification_Config,
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
 *  vStreamProc_ProcessingNode_MACVerification_Flush
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_MACVerification_Flush(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  P2CONST(vStreamProc_ProcessingNode_MACVerification_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) specializedCfgPtr;

  /* ----- Implementation ----------------------------------------------- */
  /* PRQA S 0316 2 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  specializedCfgPtr = vStreamProc_GetTypedConfigOfProcessingNode_MACVerification_Config(NodeInfo);

  /* #10 Process any pending input. */
  retVal = vStreamProc_ProcessingNode_MACVerification_Process(NodeInfo);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #20 Finalize the MAC verification and propagate the result. */
    vStreamProc_InputPortInfoType   macReferencePortInfo;
    vStreamProc_OutputPortInfoType  macResultPortInfo;

    vStreamProc_StorageInfoPtrType  macReferenceStorageInfo = &macReferencePortInfo.ReadRequest.StorageInfo;
    vStreamProc_StorageInfoPtrType  macResultStorageInfo    = &macResultPortInfo.WriteRequest.StorageInfo;

    macReferencePortInfo.SymbolicPortName = vStreamProcConf_Internal_MACVerificationNode_MACReferenceData;
    macResultPortInfo.SymbolicPortName    = vStreamProcConf_Internal_MACVerificationNode_ResultData;

    retVal = vStreamProc_PreparePortInfos(NodeInfo, &macReferencePortInfo, 1u, &macResultPortInfo, 1u);

    if (retVal == VSTREAMPROC_OK)
    {
      /* Issue a read request to get the reference MAC. */
      macReferenceStorageInfo->RequestLength    = 1u;
      macReferenceStorageInfo->DataTypeInfo.Id  = vStreamProcConf_vStreamProcDataType_uint8;
      macResultStorageInfo->RequestLength       = VSTREAMPROC_MAC_VERIFICATION_RESULT_LENGTH;
      macResultStorageInfo->DataTypeInfo.Id     = vStreamProcConf_vStreamProcDataType_Std_ReturnType;

      retVal = vStreamProc_RequestPortData(NodeInfo, &macReferencePortInfo, 1u, &macResultPortInfo, 1u);
    }

    if (retVal == VSTREAMPROC_OK)
    {
      Std_ReturnType          csmResult;
      Crypto_VerifyResultType macResultValue  = CRYPTO_E_VER_NOT_OK;
      vStreamProc_LengthType  availableLength = macReferenceStorageInfo->AvailableLength;

      /* Consume all available data if there is any. */
      csmResult = Csm_MacVerify(specializedCfgPtr->CsmJobIdOfProcessingNode_MACVerification_Config,
        CRYPTO_OPERATIONMODE_FINISH, NULL_PTR, 0u,
        vStreamProc_GetTypedReadRequestBuffer_uint8(&macReferencePortInfo.ReadRequest), availableLength, &macResultValue);

      if (csmResult == E_OK)
      {
        P2VAR(Std_ReturnType, AUTOMATIC, VSTREAMPROC_APPL_VAR) outputBuffer =
          vStreamProc_GetTypedWriteRequestBuffer_Std_ReturnType(&macResultPortInfo.WriteRequest);
        Std_ReturnType macVerifyResult;

        if (macResultValue == CRYPTO_E_VER_OK)
        {
          macVerifyResult = E_OK;
        }
        else
        {
          macVerifyResult = E_NOT_OK;
        }

        /* Propagate the result. */
        /* Copy MAC verification result to storage node. */
        outputBuffer[0u] = macVerifyResult;

        macReferenceStorageInfo->RequestLength = availableLength;

        retVal = vStreamProc_AcknowledgePorts(NodeInfo, &macReferencePortInfo, 1u, &macResultPortInfo, 1u);
      }
      else
      {
        (void)vStreamProc_ReleaseAllPorts(NodeInfo);
        retVal = VSTREAMPROC_FAILED;
      }
    }
  }

  return retVal;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

# define VSTREAMPROC_STOP_SEC_CODE
# include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (VSTREAMPROC_PROCESSINGNODE_MACVERIFICATION_CONFIG == STD_ON) */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* Justification for module-specific MISRA deviations:
 */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_ProcessingNode_MACVerification.c
 *********************************************************************************************************************/
