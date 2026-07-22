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
/*!        \file  vStreamProc_ProcessingNode_CRC.c
 *        \brief  vStreamProc CRC Sub Module Source Code File
 *      \details  Implementation of the CRC sub module for the vStreamProc framework
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
#define VSTREAMPROC_PROCESSINGNODE_CRC_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc_ProcessingNode_CRC.h"
#include "vStreamProc.h"
#include "vStreamProc_Port.h"

#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if (VSTREAMPROC_PROCESSINGNODE_CRC_CONFIG == STD_ON)
# include "Crc.h"

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

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_CRC_InitCRC()
 **********************************************************************************************************************/
/*! \brief        Initializes the workspace of the passed node.
 *  \details      -
 *  \param[in]    CfgPtr          Pointer to the config of the processing node.
 *  \param[out]   CrcValue        Pointer to the CRC value/workspace of the processing node.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_CRC_InitCRC(
  P2CONST(vStreamProc_ProcessingNode_CRC_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) CfgPtr,
  P2VAR(vStreamProc_CRC_ValueType, AUTOMATIC, VSTREAMPROC_APPL_VAR) CrcValue);

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_CRC_CalculateCRC()
 **********************************************************************************************************************/
/*! \brief        Calculate CRC with the passed workspace of the passed node.
 *  \details      -
 *  \param[in]    CfgPtr          Pointer to the config of the processing node.
 *  \param[in,out] CrcValue       Pointer to the CRC value/workspace of the processing node.
 *  \param[in]    Buffer          Pointer to the Buffer of the input data.
 *  \param[in]    BufferLen       Length of the input data.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_CRC_CalculateCRC(
  P2CONST(vStreamProc_ProcessingNode_CRC_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) CfgPtr,
  P2VAR(vStreamProc_CRC_ValueType, AUTOMATIC, VSTREAMPROC_APPL_VAR) CrcValue,
  P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) Buffer,
  CONST(uint32, AUTOMATIC) BufferLen);

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_CRC_WriteResult()
 **********************************************************************************************************************/
/*! \brief        Writes the CRC result to the output StorageNode.
 *  \details      -
 *  \param[in]    NodeInfo          The processing node information to operate on.
 *  \param[in]    CfgPtr            Pointer to the config of the processing node.
 *  \param[out]   CrcValue          Pointer to the CRC value/workspace of the processing node.
 * \return        VSTREAMPROC_OK                    Writing CRC result to output StorageNode was successful.
 * \return        VSTREAMPROC_FAILED                Writing CRC result to output StorageNode was unsuccessful.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   Not enough buffer available to CRC result.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_CRC_WriteResult(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo,
  P2CONST(vStreamProc_ProcessingNode_CRC_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) CfgPtr,
  P2CONST(vStreamProc_CRC_ValueType, AUTOMATIC, VSTREAMPROC_APPL_VAR) CrcValue);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_CRC_InitCRC
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_CRC_InitCRC(
  P2CONST(vStreamProc_ProcessingNode_CRC_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) CfgPtr,
  P2VAR(vStreamProc_CRC_ValueType, AUTOMATIC, VSTREAMPROC_APPL_VAR) CrcValue)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the workspace based on the configured CRC type */
  switch (CfgPtr->CRCTypeOfProcessingNode_CRC_Config)
  {
    case VSTREAMPROC_CRC8_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      *CrcValue = Crc_CalculateCRC8(NULL_PTR, 0u, 0u, TRUE);
      break;
    }
    case VSTREAMPROC_CRC8H2F_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      *CrcValue = Crc_CalculateCRC8H2F(NULL_PTR, 0u, 0u, TRUE);
      break;
    }
    case VSTREAMPROC_CRC16_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      *CrcValue = Crc_CalculateCRC16(NULL_PTR, 0u, 0u, TRUE);
      break;
    }
    case VSTREAMPROC_CRC32_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      *CrcValue = Crc_CalculateCRC32(NULL_PTR, 0u, 0u, TRUE);
      break;
    }
    case VSTREAMPROC_CRC32P4_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      *CrcValue = Crc_CalculateCRC32P4(NULL_PTR, 0u, 0u, TRUE);
      break;
    }
    case VSTREAMPROC_CRC64_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      *CrcValue = Crc_CalculateCRC64(NULL_PTR, 0u, 0u, TRUE);
      break;
    }
    default:
    {
      /* Intentionally left empty */
      break;
    }
  }
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_CRC_CalculateCRC
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_CRC_CalculateCRC(
  P2CONST(vStreamProc_ProcessingNode_CRC_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) CfgPtr,
  P2VAR(vStreamProc_CRC_ValueType, AUTOMATIC, VSTREAMPROC_APPL_VAR) CrcValue,
  P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) Buffer,
  CONST(uint32, AUTOMATIC) BufferLen)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate the CRC value based on the configured CRC type */
  switch (CfgPtr->CRCTypeOfProcessingNode_CRC_Config)
  {
    case VSTREAMPROC_CRC8_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      *CrcValue = Crc_CalculateCRC8(Buffer, BufferLen,
          (uint8)(*CrcValue & 0x00000000000000FFuLL), FALSE);
      break;
    }
    case VSTREAMPROC_CRC8H2F_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      *CrcValue = Crc_CalculateCRC8H2F(Buffer, BufferLen,
          (uint8)(*CrcValue & 0x00000000000000FFuLL), FALSE);
      break;
    }
    case VSTREAMPROC_CRC16_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      *CrcValue = Crc_CalculateCRC16(Buffer, BufferLen,
          (uint16)(*CrcValue & 0x000000000000FFFFuLL), FALSE);
      break;
    }
    case VSTREAMPROC_CRC32_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      *CrcValue = Crc_CalculateCRC32(Buffer, BufferLen,
          (uint32)(*CrcValue & 0x00000000FFFFFFFFuLL), FALSE);
      break;
    }
    case VSTREAMPROC_CRC32P4_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      *CrcValue = Crc_CalculateCRC32P4(Buffer, BufferLen,
          (uint32)(*CrcValue & 0x00000000FFFFFFFFuLL), FALSE);
      break;
    }
    case VSTREAMPROC_CRC64_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      *CrcValue = Crc_CalculateCRC64(Buffer, BufferLen, *CrcValue, FALSE);
      break;
    }
    default:
    {
      /* Intentionally left empty */
      break;
    }
  }
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_CRC_WriteResult
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_CRC_WriteResult(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo,
  P2CONST(vStreamProc_ProcessingNode_CRC_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) CfgPtr,
  P2CONST(vStreamProc_CRC_ValueType, AUTOMATIC, VSTREAMPROC_APPL_VAR) CrcValue)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType          retVal = VSTREAMPROC_FAILED;
  vStreamProc_OutputPortInfoType  outputPortInfo;
  vStreamProc_LengthType          crcSize;

  /* ----- Implementation ----------------------------------------------- */
  /* Get the CRC's size in bytes */
  /* #10 Infer the size of the CRC value in bytes. */
  switch (CfgPtr->CRCTypeOfProcessingNode_CRC_Config)
  {
    case VSTREAMPROC_CRC8_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      crcSize = 1u;
      break;
    }
    case VSTREAMPROC_CRC8H2F_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      crcSize = 1u;
      break;
    }
    case VSTREAMPROC_CRC16_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      crcSize = 2u;
      break;
    }
    case VSTREAMPROC_CRC32_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      crcSize = 4u;
      break;
    }
    case VSTREAMPROC_CRC32P4_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      crcSize = 4u;
      break;
    }
    case VSTREAMPROC_CRC64_CRCTYPEOFPROCESSINGNODE_CRC_CONFIG:
    {
      crcSize = 8u;
      break;
    }
    default:
    {
      crcSize = 0u;
      break;
    }
  }

  /* #20 Write the CRC value to the associated storage node. */
  /* Issue a write request and write the data to the passed storage node. */
  if (vStreamProc_PrepareOutputPortInfo(NodeInfo, vStreamProcConf_Internal_CRCNode_OutputData, &outputPortInfo) == VSTREAMPROC_OK)
  {
    retVal = vStreamProc_RequestOutputPortData(NodeInfo, vStreamProcConf_vStreamProcDataType_uint8, crcSize, &outputPortInfo);
  }

  if (retVal == VSTREAMPROC_OK)
  {
    P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) outputBuffer = vStreamProc_GetTypedWriteRequestBuffer_uint8(&outputPortInfo.WriteRequest);
    vStreamProc_StorageNodeBufferIterType index;
    uint64 crcOutputValue = *CrcValue;

    /* Write CRC value to the output buffer  */
    for (index = 0; index < crcSize; index++)
    {
      /* Store CRC in little endian format (LSB first) */
      outputBuffer[index] = (uint8)(crcOutputValue & 0x00000000000000FFuLL);
      crcOutputValue >>= 8u;
    }

    /* Acknowledge the write */
    retVal = vStreamProc_AcknowledgeOutputPort(NodeInfo, crcSize, TRUE, &outputPortInfo);
  }

  return retVal;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_CRC_Init
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_CRC_Init(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  P2CONST(vStreamProc_ProcessingNode_CRC_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) specializedCfgPtr;
  P2VAR(vStreamProc_CRC_ValueType, AUTOMATIC, VSTREAMPROC_APPL_VAR) crcValue;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's configuration and workspace. */
  /* PRQA S 0316 2 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  specializedCfgPtr = vStreamProc_GetTypedConfigOfProcessingNode_CRC_Config(NodeInfo);
  crcValue = vStreamProc_GetTypedWorkspaceOfProcessingNode_CRC_ValueType(NodeInfo);

  /* #10 Initialize the associated workspace. */
  vStreamProc_ProcessingNode_CRC_InitCRC(specializedCfgPtr, crcValue);

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_CRC_Process
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_CRC_Process(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;

  vStreamProc_InputPortInfoType inputPortInfo;
  P2CONST(vStreamProc_ProcessingNode_CRC_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) specializedCfgPtr;
  P2VAR(vStreamProc_CRC_ValueType, AUTOMATIC, VSTREAMPROC_APPL_VAR) crcValue;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's configuration and workspac.e */
  /* PRQA S 0316 2 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  specializedCfgPtr = vStreamProc_GetTypedConfigOfProcessingNode_CRC_Config(NodeInfo);
  crcValue = vStreamProc_GetTypedWorkspaceOfProcessingNode_CRC_ValueType(NodeInfo);

  /* #10 Try to fetch input data and forward it to the CRC. */
  /* Issue a read request and if data is available then handle it. */
  if (vStreamProc_PrepareInputPortInfo(NodeInfo, vStreamProcConf_Internal_CRCNode_InputData, &inputPortInfo) == VSTREAMPROC_OK)
  {
    retVal = vStreamProc_RequestInputPortData(NodeInfo, vStreamProcConf_vStreamProcDataType_uint8, 0u, &inputPortInfo);
  }

  if (retVal == VSTREAMPROC_OK)
  {
    vStreamProc_LengthType availableLength = inputPortInfo.ReadRequest.StorageInfo.AvailableLength;

    if (availableLength > 0u)
    {
      /* Calculate the CRC and acknowledge the consumed data. */
      vStreamProc_ProcessingNode_CRC_CalculateCRC(specializedCfgPtr, crcValue, vStreamProc_GetTypedReadRequestBuffer_uint8(&inputPortInfo.ReadRequest), availableLength);

      retVal = vStreamProc_AcknowledgeInputPort(NodeInfo, availableLength, TRUE, &inputPortInfo);
    }
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_CRC_Flush
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_CRC_Flush(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR(vStreamProc_ReturnType, AUTOMATIC) retVal;

  P2CONST(vStreamProc_ProcessingNode_CRC_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) specializedCfgPtr;
  P2CONST(vStreamProc_CRC_ValueType, AUTOMATIC, VSTREAMPROC_APPL_VAR) crcValue;

  /* ----- Implementation ----------------------------------------------- */
  /* Infer the processing node's configuration and workspace. */
  /* PRQA S 0316 2 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  specializedCfgPtr = vStreamProc_GetTypedConfigOfProcessingNode_CRC_Config(NodeInfo);
  crcValue = vStreamProc_GetTypedWorkspaceOfProcessingNode_CRC_ValueType(NodeInfo);

  /* #10 Finalize the CRC calculation. */
  retVal = vStreamProc_ProcessingNode_CRC_Process(NodeInfo);

  /* #20 Write result to output StorageNode. */
  if (retVal == VSTREAMPROC_OK)
  {
    retVal = vStreamProc_ProcessingNode_CRC_WriteResult(NodeInfo, specializedCfgPtr, crcValue);
  }

  return retVal;
}

# define VSTREAMPROC_STOP_SEC_CODE
# include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (VSTREAMPROC_PROCESSINGNODE_CRC_CONFIG == STD_ON) */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* Justification for module-specific MISRA deviations:
 */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_ProcessingNode_CRC.c
 *********************************************************************************************************************/
