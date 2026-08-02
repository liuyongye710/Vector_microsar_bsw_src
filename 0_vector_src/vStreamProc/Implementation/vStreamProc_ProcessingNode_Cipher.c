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
/*!        \file  vStreamProc_ProcessingNode_Cipher.c
 *        \brief  vStreamProc Cipher Sub Module Source Code File
 *      \details  Implementation of the cipher sub module for the vStreamProc framework
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
#define VSTREAMPROC_PROCESSINGNODE_CIPHER_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc_ProcessingNode_Cipher.h"
#include "vStreamProc.h"
#include "vStreamProc_Port.h"

#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if (VSTREAMPROC_PROCESSINGNODE_CIPHER_CONFIG == STD_ON)
# include "Csm.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined (VSTREAMPROC_LOCAL)
#  define VSTREAMPROC_LOCAL static
# endif

# if !defined (VSTREAMPROC_LOCAL_INLINE)
#  define VSTREAMPROC_LOCAL_INLINE LOCAL_INLINE
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

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Cipher_InitLocal()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize CSM cipher job.
 * \details       -
 * \param[in]     NodeInfo        The processing node information to operate on.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Cipher_InitLocal(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo);

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Cipher_ProcessLocal()
 *********************************************************************************************************************/
/*!
 * \brief         Generic function to handle process and flush.
 * \details       -
 * \param[in]     NodeInfo        The processing node information to operate on.
 * \param[in]     CryptoOpMode    Crypto operation (update or finish).
 * \return        VSTREAMPROC_OK                    Process has handled the available input data.
 * \return        VSTREAMPROC_FAILED                Process failed.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    Process not possible due to insufficient available input buffer.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   Process not possible due to insufficient available output buffer.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Cipher_ProcessLocal(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo,
  Crypto_OperationModeType CryptoOpMode);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Cipher_InitLocal
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Cipher_InitLocal(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  P2CONST(vStreamProc_ProcessingNode_Cipher_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST)  specializedCfgPtr;
  P2VAR(vStreamProc_Cipher_StateType, AUTOMATIC, VSTREAMPROC_APPL_VAR)                      cipherState;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's configuration and workspace */
  /* PRQA S 0316 2 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  specializedCfgPtr = vStreamProc_GetTypedConfigOfProcessingNode_Cipher_Config(NodeInfo);
  cipherState = vStreamProc_GetTypedWorkspaceOfProcessingNode_Cipher_StateType(NodeInfo);

  if (*cipherState == VSTREAMPROC_WS_STATE_INITIALIZED)
  {
    Std_ReturnType csmResult;

    /* #10 Initialize the encryption/decryption CSM Job */
    if (specializedCfgPtr->CipherModeOfProcessingNode_Cipher_Config == VSTREAMPROC_DECRYPTION_CIPHERMODEOFPROCESSINGNODE_CIPHER_CONFIG)
    {
      csmResult = Csm_Decrypt(specializedCfgPtr->CsmJobIdOfProcessingNode_Cipher_Config,
                            CRYPTO_OPERATIONMODE_START, NULL_PTR, 0u,
                            NULL_PTR, NULL_PTR);
    }
    else /* == VSTREAMPROC_ENCRYPTION_CIPHERMODEOFPROCESSINGNODE_CIPHER_CONFIG */
    {
      csmResult = Csm_Encrypt(specializedCfgPtr->CsmJobIdOfProcessingNode_Cipher_Config,
                            CRYPTO_OPERATIONMODE_START, NULL_PTR, 0u,
                            NULL_PTR, NULL_PTR);
    }

    /* In case everything went fine fall through to next state. */
    if (csmResult == E_OK)
    {
      /* Initialize the encryption/decryption CSM Job */
      *cipherState = VSTREAMPROC_WS_STATE_PROCESSING;
    }
  }
}

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Cipher_ProcessLocal()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Cipher_ProcessLocal(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo,
  Crypto_OperationModeType CryptoOpMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType  retVal        = VSTREAMPROC_FAILED;                                                           /* PRQA S 2981 */ /* MD_MSR_RetVal */

  P2CONST(vStreamProc_ProcessingNode_Cipher_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) specializedCfgPtr; /**< Holds config of cipher processing node */

  vStreamProc_InputPortInfoType   inputPortInfo;
  vStreamProc_OutputPortInfoType  outputPortInfo;

  Crypto_OperationModeType  cryptoOpMode  = CryptoOpMode;
  vStreamProc_LengthType    inputLength   = 0u;                                                                         /* PRQA S 2981 */ /* MD_vStreamProc_Rule2.2_2981_2892_RedundantInitialization */
  vStreamProc_LengthType    outputLength;
  vStreamProc_LengthType    minOutputLength;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize local variables with known values. */
  /* Infer the processing node's configuration. */
  /* PRQA S 0316 1 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  specializedCfgPtr = vStreamProc_GetTypedConfigOfProcessingNode_Cipher_Config(NodeInfo);

  /* Set output length to default value. */
  minOutputLength = specializedCfgPtr->MinOutputLengthOfProcessingNode_Cipher_Config;
  outputLength    = minOutputLength;

  /* #20 Get input information. */
  if (vStreamProc_PrepareAllPortInfos(NodeInfo, &inputPortInfo, 1u, &outputPortInfo, 1u) == VSTREAMPROC_OK)
  {
    retVal = vStreamProc_GetInputPortInfo(NodeInfo, vStreamProcConf_vStreamProcDataType_uint8, &inputPortInfo);
  }

  if (retVal == VSTREAMPROC_OK)
  {
    retVal      = VSTREAMPROC_PENDING;
    inputLength = inputPortInfo.ReadRequest.StorageInfo.AvailableLength;

    /* #30 Check input data length for plausibility. */
    if (inputLength == 0u)
    {
      if (cryptoOpMode == CRYPTO_OPERATIONMODE_UPDATE)
      {
        /* No new data available - just wait for it. */
        retVal = VSTREAMPROC_OK;
      }
      else /* cryptoOpMode == CRYPTO_OPERATIONMODE_FINISH */
      {
        /* Expected use case: No input data for flush. */

        /* #40 Minimum output length must be adapted for finishing encryption.
         *  Encryption with enabled padding may require one outputLength for encrypted data and another one for padding.
         */
        if (specializedCfgPtr->CipherModeOfProcessingNode_Cipher_Config == VSTREAMPROC_ENCRYPTION_CIPHERMODEOFPROCESSINGNODE_CIPHER_CONFIG)
        {
          outputLength = 2u * outputLength;
        }
      }
    }
  }

  if (retVal == VSTREAMPROC_PENDING)
  {
    /* #50 Get input and output buffers. */
    outputPortInfo.WriteRequest.StorageInfo.RequestLength   = outputLength; /* Request minimum aligned result buffer to trigger defragmentation. */
    outputPortInfo.WriteRequest.StorageInfo.DataTypeInfo.Id = vStreamProcConf_vStreamProcDataType_uint8;
    retVal = vStreamProc_RequestPortData(NodeInfo, &inputPortInfo, 1u, &outputPortInfo, 1u);

    /* No data acknowledged per default. */
    inputPortInfo.ReadRequest.StorageInfo.RequestLength   = 0u;
    outputPortInfo.WriteRequest.StorageInfo.RequestLength = 0u;

    if (retVal == VSTREAMPROC_OK)
    {
      /* Set output length to maximum for CSM API call. */
      outputLength = outputPortInfo.WriteRequest.StorageInfo.AvailableLength;

      if (inputLength > 0u)
      {
        /* #60 Calculate max input length based on available output buffer. */
        /* Max input length is always capped to a multiple of the minimum output length due to the unknown number of buffered bytes in the crypto driver. */
        vStreamProc_LengthType maxInputLength = (outputLength / minOutputLength) * minOutputLength;

        /* #70 Align input length to max input length. */
        if (maxInputLength < inputLength)
        {
          inputLength = maxInputLength;
        }

        /* #80 Check aligned input data length for plausibility. */
        if (inputLength == 0u)
        {
          /* Data is provided but the alignment caused reducing inputLength to 0. So we don't have enough output buffer to accept the input data. */
          retVal                          = VSTREAMPROC_INSUFFICIENT_OUTPUT;
          NodeInfo->OutputPortResults[0u] = VSTREAMPROC_INSUFFICIENT_OUTPUT;
        }
        else
        {
          /* Aligned and not processed data in input buffer -> update necessary.
           * In case flush was called and there are remaining data: Update until input data is consumed */
          if (cryptoOpMode == CRYPTO_OPERATIONMODE_FINISH)
          {
            cryptoOpMode = CRYPTO_OPERATIONMODE_UPDATE;
          }
        }
      }
    }

    if (retVal == VSTREAMPROC_OK)
    {
      Std_ReturnType csmResult;
      P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) inputBuffer   = vStreamProc_GetTypedReadRequestBuffer_uint8(&inputPortInfo.ReadRequest);
      P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR)   outputBuffer  = vStreamProc_GetTypedWriteRequestBuffer_uint8(&outputPortInfo.WriteRequest);

      /* #90 Process encryption/decryption. */
      if (specializedCfgPtr->CipherModeOfProcessingNode_Cipher_Config == VSTREAMPROC_DECRYPTION_CIPHERMODEOFPROCESSINGNODE_CIPHER_CONFIG)
      {
        /* Process the decryption. */
        csmResult = Csm_Decrypt(specializedCfgPtr->CsmJobIdOfProcessingNode_Cipher_Config,
                                    cryptoOpMode, inputBuffer, inputLength,
                                    outputBuffer, &outputLength);
      }
      else /* == VSTREAMPROC_ENCRYPTION_CIPHERMODEOFPROCESSINGNODE_CIPHER_CONFIG */
      {
        /* Process the encryption. */
        csmResult = Csm_Encrypt(specializedCfgPtr->CsmJobIdOfProcessingNode_Cipher_Config,
                                    cryptoOpMode, inputBuffer, inputLength,
                                    outputBuffer, &outputLength);
      }

      /* #100 Handle CSM results. */
      switch (csmResult)
      {
        case E_OK:
        /* #110 If OK: Acknowledge the read and written bytes. */
        {
          inputPortInfo.ReadRequest.StorageInfo.RequestLength   = inputLength;
          outputPortInfo.WriteRequest.StorageInfo.RequestLength = outputLength;

          break;
        }
        case CRYPTO_E_BUSY:
        case CRYPTO_E_QUEUE_FULL:
        /* #120 If CSM is busy or queue is full: Try again in next cycle. */
        {
          retVal = VSTREAMPROC_PENDING;

          break;
        }
        default:
        /* #130 Else: Treat all other return values as error. */
        {
          retVal = VSTREAMPROC_FAILED;
          break;
        }
      }
    }

    /* Acknowledge any processed data or simply unlock buffers. */
    if (vStreamProc_AcknowledgePorts(NodeInfo, &inputPortInfo, 1u, &outputPortInfo, 1u) != VSTREAMPROC_OK)
    {
      retVal = VSTREAMPROC_FAILED;
    }
  }

  return retVal;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Cipher_Init
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Cipher_Init(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;
  P2VAR(vStreamProc_Cipher_StateType, AUTOMATIC, VSTREAMPROC_APPL_VAR) cipherState;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's workspace */
  /* PRQA S 0316 1 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  cipherState = vStreamProc_GetTypedWorkspaceOfProcessingNode_Cipher_StateType(NodeInfo);

  /* #10 Initialize state value of workspace */
  *cipherState = VSTREAMPROC_WS_STATE_INITIALIZED;

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Cipher_Process
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Cipher_Process(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;
  P2CONST(vStreamProc_Cipher_StateType, AUTOMATIC, VSTREAMPROC_APPL_VAR) cipherState;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's configuration and workspace */
  /* PRQA S 0316 2 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  cipherState = vStreamProc_GetTypedWorkspaceOfProcessingNode_Cipher_StateType(NodeInfo);

  /* #10 Initialize the encryption/decryption CSM Job if necessary. */
  vStreamProc_ProcessingNode_Cipher_InitLocal(NodeInfo);

  /* #20 Forward request to common processing function. */
  if(*cipherState == VSTREAMPROC_WS_STATE_PROCESSING)
  {
    retVal = vStreamProc_ProcessingNode_Cipher_ProcessLocal(NodeInfo, CRYPTO_OPERATIONMODE_UPDATE);
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Cipher_Flush
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Cipher_Flush(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;
  P2CONST(vStreamProc_Cipher_StateType, AUTOMATIC, VSTREAMPROC_APPL_VAR) cipherState;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's workspace */
  /* PRQA S 0316 1 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  cipherState = vStreamProc_GetTypedWorkspaceOfProcessingNode_Cipher_StateType(NodeInfo);

  /* #10 Initialize the encryption/decryption CSM Job if necessary. */
  vStreamProc_ProcessingNode_Cipher_InitLocal(NodeInfo);

  /* #20 Forward request to common processing function. */
  if (*cipherState == VSTREAMPROC_WS_STATE_PROCESSING)
  {
    retVal = vStreamProc_ProcessingNode_Cipher_ProcessLocal(NodeInfo, CRYPTO_OPERATIONMODE_FINISH);
  }

  return retVal;
}

# define VSTREAMPROC_STOP_SEC_CODE
# include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (VSTREAMPROC_PROCESSINGNODE_CIPHER_CONFIG == STD_ON) */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* Justification for module-specific MISRA deviations:
*/

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_ProcessingNode_Cipher.c
 *********************************************************************************************************************/
