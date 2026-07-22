/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!       \file  vSwUpdM_ResumeProcNodeTypes.h
 *        \brief  vSwUpdM processing nodes type definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *********************************************************************************************************************/
#if !defined (VSWUPDM_RESUMEPROCNODETYPES_H)
# define VSWUPDM_RESUMEPROCNODETYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vSwUpdM_ProcNodeTypes.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Use AES block size of 16 bytes, unless overwritten from outside. */
#if !defined(VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE)
# define VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE    16u
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
  VSWUPDM_RESUME_PROC_NODE_STATE_INITIAL,
  VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_PROCESS_OPERATION,
  VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_INPUTS,
  VSWUPDM_RESUME_PROC_NODE_STATE_PENDING,
  VSWUPDM_RESUME_PROC_NODE_STATE_FINISHED,
  VSWUPDM_RESUME_PROC_NODE_STATE_SHUTDOWN,
  VSWUPDM_RESUME_PROC_NODE_STATE_FAILED
} vSwUpdM_ResumeProcNodeStateType;

typedef P2VAR(vSwUpdM_ResumeProcNodeStateType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_ResumeProcNodeStatePtrType;

typedef enum
{
  VSWUPMD_PROC_NODE_CIPHER_MODE_ENCRYPT,
  VSWUPMD_PROC_NODE_CIPHER_MODE_DECRYPT
} vSwUpdM_ProcNodeCipherModeType;

/******************************************************************************/
/* Specialized workspace                                                     */
/******************************************************************************/
typedef struct
{
  vSwUpdM_LinkedResultType            JobResult;
  vSwUpdM_RangeInfoType               ResumeRangeInfo;
  vSwUpdM_RangeInfoType               RemainderRangeInfo;

  uint32                              EntitiesInputPort;
  uint32                              OperationInputPort;
  uint32                              RangeInputPort;

  uint32                              OperationOutputPort;
  uint32                              ResumeRangeOutputPort;
  uint32                              RemainderRangeOutputPort;

  vSwUpdM_ResumeProcNodeStateType     State;
  vSwUpdM_ProcNodeCipherModeType      CipherMode;
  vSwUpdM_DataType                    InitVector[VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE];
  boolean                             RestartPending;
} vSwUpdM_ProcNodeReadCipherIvWorkspaceType;
typedef P2VAR(vSwUpdM_ProcNodeReadCipherIvWorkspaceType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_ProcNodeReadCipherIvWorkspacePtrType;

typedef struct
{
  vSwUpdM_ResumeProcNodeStateType     State;
  boolean                             RestartPending;
} vSwUpdM_ProcNodeEvalDecryptionIvWorkspaceType;
typedef P2VAR(vSwUpdM_ProcNodeEvalDecryptionIvWorkspaceType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_ProcNodeEvalDecryptionIvWorkspacePtrType;

typedef struct
{
  vSwUpdM_LengthType              Remainder;
  vSwUpdM_ResumeProcNodeStateType State;
  boolean                         RestartPending;
} vSwUpdM_ProcNodeResumePassthroughWorkspaceType;
typedef P2VAR(vSwUpdM_ProcNodeResumePassthroughWorkspaceType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_ProcNodeResumePassthroughWorkspacePtrType;

typedef struct
{
  vSwUpdM_ProcNodePaddingWorkspaceType    PaddingNodeWorkspace;

  vSwUpdM_LengthType                      Remainder;

  vStreamProc_InputPortSymbolicNameType   OperationInputPort;
  vStreamProc_OutputPortSymbolicNameType  OperationOutputPort;

  vSwUpdM_ResumeProcNodeStateType         State;

  boolean                                 RestartPending;
} vSwUpdM_ProcNodeResumePaddingWorkspaceType;

typedef P2VAR(vSwUpdM_ProcNodeResumePaddingWorkspaceType, AUTOMATIC, VSWUPDM_APPL_VAR)  vSwUpdM_ProcNodeResumePaddingWorkspacePtrType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif /* VSWUPDM_RESUMEPROCNODETYPES_H */

/**********************************************************************************************************************
*  END OF FILE: vSwUpdM_ResumeProcNodeTypes.h
*********************************************************************************************************************/

