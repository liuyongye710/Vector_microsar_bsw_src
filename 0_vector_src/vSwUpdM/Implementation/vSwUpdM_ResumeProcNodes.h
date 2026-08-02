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
/*!       \file  vSwUpdM_ResumeProcNodes.h
 *        \brief  vSwUpdM processing nodes implementation header file
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vSwUpdM.h.
 *********************************************************************************************************************/
#if !defined (VSWUPDM_RESUMEPROCNODES_H)
# define VSWUPDM_RESUMEPROCNODES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vSwUpdM_ProcNodes.h"

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

#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * PROCESSING NODE: READ CIPHER IV
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 *  vSwUpdM_ProcNodeReadEncryptionIv_Init
 *********************************************************************************************************************/
/*! \brief         Initializes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo        NodeInfo structure of a generic node containing a read encryption IV processing node.
 *  \return        E_OK            Initialization was successful
 *  \return        E_NOT_OK        Initialization was unsuccessful
 *  \pre           Must be called before call of any vSwUpdM_ProcNodeReadCipherIv function
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeReadEncryptionIv_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

 /**********************************************************************************************************************
 *  vSwUpdM_ProcNodeReadDecryptionIv_Init
 *********************************************************************************************************************/
/*! \brief         Initializes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo        NodeInfo structure of a generic node containing a read decryption IV processing node.
 *  \return        E_OK            Initialization was successful
 *  \return        E_NOT_OK        Initialization was unsuccessful
 *  \pre           Must be called before call of any vSwUpdM_ProcNodeReadDecryptionIv function
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeReadDecryptionIv_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeReadCipherIv_Process
 *********************************************************************************************************************/
/*! \brief         Processes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo        NodeInfo structure of a read decryption IV processing node.
 *  \return        VSTREAMPROC_OK                 Process has handled the available input data or process not started
 *                                                  yet because of missing range information or entity IDs.
 *  \return        VSTREAMPROC_PENDING              Process is not finished yet.
 *  \return        VSTREAMPROC_FAILED               Process failed.
 *  \return        VSTREAMPROC_INSUFFICIENT_OUTPUT  Process interrupted as input data exceeds available output storage.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeReadCipherIv_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

  /**********************************************************************************************************************
 *  vSwUpdM_ProcNodeReadCipherIv_Flush
 **********************************************************************************************************************/
/*! \brief         Flushes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo        NodeInfo structure of a read decryption IV processing node.
 *  \return        VSTREAMPROC_FINISHED             Flush was successful. Complete input data copied and padded.
 *                                                  Resulting unpadded/padded end addresses and lengths provided.
 *  \return        VSTREAMPROC_PENDING              Flush is not finished yet.
 *  \return        VSTREAMPROC_INSUFFICIENT_OUTPUT  Node can not be flushed as pending input data exceeds available
 *                                                  output storage.
 *  \return        VSTREAMPROC_FAILED               Flush failed.
 *  \pre          -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeReadCipherIv_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 * PROCESSING NODE: EVAL DECRYPTION IV
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeEvalDecryptionIv_Init
 *********************************************************************************************************************/
/*! \brief         Initializes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo        NodeInfo structure of a generic node containing an eval decryption IV processing node.
 *  \return        E_OK            Initialization was successful
 *  \return        E_NOT_OK        Initialization was unsuccessful
 *  \pre           Must be called before call of any vSwUpdM_ProcNodeEvalDecryptionIv function
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeEvalDecryptionIv_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeEvalDecryptionIv_Process
 *********************************************************************************************************************/
/*! \brief         Processes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo        NodeInfo structure of a generic node containing an eval decryption IV processing node.
 *  \return        VSTREAMPROC_OK                   Process has handled the available input data or process not started
 *                                                  yet because of missing range information or entity IDs.
 *  \return        VSTREAMPROC_PENDING              Process is not finished yet.
 *  \return        VSTREAMPROC_FAILED               Process failed.
 *  \return        VSTREAMPROC_INSUFFICIENT_OUTPUT  Process interrupted as input data exceeds available output storage.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeEvalDecryptionIv_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeEvalDecryptionIv_Flush
 **********************************************************************************************************************/
/*! \brief         Flushes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo        NodeInfo structure of a generic node containing an eval decryption IV processing node.
 *  \return        VSTREAMPROC_FINISHED             Flush was successful. Complete input data copied and padded.
 *                                                  Resulting unpadded/padded end addresses and lengths provided.
 *  \return        VSTREAMPROC_PENDING              Flush is not finished yet.
 *  \return        VSTREAMPROC_INSUFFICIENT_OUTPUT  Node can not be flushed as pending input data exceeds available
 *                                                  output storage.
 *  \return        VSTREAMPROC_FAILED               Flush failed.
 *  \pre          -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeEvalDecryptionIv_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 * PROCESSING NODE: PASS-THROUGH
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeResumePassthrough_Init
 *********************************************************************************************************************/
/*! \brief         Initializes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo        NodeInfo structure of a generic node containing a resume pass-through processing node.
 *  \return        E_OK            Initialization was successful
 *  \return        E_NOT_OK        Initialization was unsuccessful
 *  \pre           Must be called before call of any vSwUpdM_ProcNodeResumePassthrough function
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeResumePassthrough_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeResumePassthrough_Process
 *********************************************************************************************************************/
/*! \brief         Processes the passed node.
 *  \details       This node pads the input data to align with the page boundaries of the memory to be written.
 *                 The padding at the end is added when the node is flushed.
 *  \param[in]     NodeInfo        NodeInfo structure of a generic node containing a resume pass-through processing node.
 *  \return        VSTREAMPROC_OK                   Process has handled the available input data or process not started
 *                                                  yet because of missing range information or entity IDs.
 *  \return        VSTREAMPROC_PENDING              Process is not finished yet.
 *  \return        VSTREAMPROC_FAILED               Process failed.
 *  \return        VSTREAMPROC_INSUFFICIENT_OUTPUT  Process interrupted as input data exceeds available output storage.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeResumePassthrough_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeResumePassthrough_Flush
 **********************************************************************************************************************/
/*! \brief         Flushes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo        NodeInfo structure of a generic node containing a resume pass-through processing node.
 *  \return        VSTREAMPROC_FINISHED             Flush was successful. Complete input data copied and padded.
 *                                                  Resulting unpadded/padded end addresses and lengths provided.
 *  \return        VSTREAMPROC_PENDING              Flush is not finished yet.
 *  \return        VSTREAMPROC_INSUFFICIENT_OUTPUT  Node can not be flushed as pending input data exceeds available
 *                                                  output storage.
 *  \return        VSTREAMPROC_FAILED               Flush failed.
 *  \pre          -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeResumePassthrough_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 * PROCESSING NODE: PADDING (RESUME)
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeResumePadding_Init
 *********************************************************************************************************************/
/*! \brief         Initializes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo        NodeInfo structure of a generic node containing a resume padding processing node.
 *  \return        E_OK            Initialization was successful
 *  \return        E_NOT_OK        Initialization was unsuccessful
 *  \pre           Must be called before call of any vSwUpdM_ProcNodeResumePadding function
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeResumePadding_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeResumePadding_Process
 *********************************************************************************************************************/
/*! \brief         Processes the passed node.
 *  \details       This node pads the input data to align with the page boundaries of the memory to be written.
 *                 The padding at the end is added when the node is flushed.
 *  \param[in]     NodeInfo        NodeInfo structure of a generic node containing a resume padding processing node.
 *  \return        VSTREAMPROC_OK                   Process has handled the available input data or process not started
 *                                                  yet because of missing range information or entity IDs.
 *  \return        VSTREAMPROC_PENDING              Process is not finished yet.
 *  \return        VSTREAMPROC_FAILED               Process failed.
 *  \return        VSTREAMPROC_INSUFFICIENT_OUTPUT  Process interrupted as input data exceeds available output storage.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeResumePadding_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeResumePadding_Flush
 **********************************************************************************************************************/
/*! \brief         Flushes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo        NodeInfo structure of a generic node containing a resume padding processing node.
 *  \return        VSTREAMPROC_FINISHED             Flush was successful. Complete input data copied and padded.
 *                                                  Resulting unpadded/padded end addresses and lengths provided.
 *  \return        VSTREAMPROC_PENDING              Flush is not finished yet.
 *  \return        VSTREAMPROC_INSUFFICIENT_OUTPUT  Node can not be flushed as pending input data exceeds available
 *                                                  output storage.
 *  \return        VSTREAMPROC_FAILED               Flush failed.
 *  \pre          -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeResumePadding_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_RESUMEPROCNODES_H */

/**********************************************************************************************************************
*  END OF FILE: vSwUpdM_ResumeProcNodes.h
*********************************************************************************************************************/
