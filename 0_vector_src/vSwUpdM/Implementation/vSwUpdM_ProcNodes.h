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
/*!       \file  vSwUpdM_ProcNodes.h
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
#if !defined (VSWUPDM_PROCNODES_H)
# define VSWUPDM_PROCNODES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vSwUpdM_Cfg.h"
#include "vStreamProc_Types.h"
#include "vSwUpdM_ProcNodeTypes.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define VSWUPDM_PROCNODES_MIN(a, b) (((a) < (b)) ? (a) : (b))

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_DATA) vSwUpdM_ProcNodeInfoPtrType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  vSwUpdM_ProcNode_PreparePorts
 **********************************************************************************************************************/
/*! \brief      Prepares all input/output ports of a node and checks their data type.
 *  \details    -
 *  \param[in]     NodeInfo                  NodeInfo structure of the current node.
 *  \param[in,out] Ports                     The structure for generalized port access.
 *  \return        VSTREAMPROC_OK            On success
 *  \return        VSTREAMPROC_FAIL          Else
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre         -
 **********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNode_PreparePorts(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNode_RequestPorts
 **********************************************************************************************************************/
/*! \brief       Requests all input/output ports of a node according to the request lengths in Ports.
 *  \details     -
 *  \param[in]   NodeInfo                        NodeInfo structure of the current node.
 *  \param[in]   Ports                           The structure for generalized port access.
 *  \return      VSTREAMPROC_OK                  On success
 *  \return      VSTREMAPROC_INSUFFICIENT_INPUT  Input data request was unsuccessful
 *  \return      VSTREMAPROC_INSUFFICIENT_OUTPUT Output data request was unsuccessful
 *  \return      VSTREAMPROC_FAIL                An error occured.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 **********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNode_RequestPorts(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNode_AcknowledgePorts
 **********************************************************************************************************************/
/*! \brief       Acknowledges all input/output ports of a node according to the request lengths in Ports.
 *  \details     -
 *  \param[in]   NodeInfo         NodeInfo structure of the current node.
 *  \param[in]   Ports            The structure for generalized port access.
 *  \return      VSTREAMPROC_OK   On success
 *  \return      VSTREAMPROC_FAIL Else
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 **********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNode_AcknowledgePorts(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/**********************************************************************************************************************
 * PROCESSING NODE: PADDING
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNode_IsInputDataAvailable()
 *********************************************************************************************************************/
/*! \brief       Iterate over InputPortInfos, return TRUE if at least one has data available.
 *  \details     Most Nodes will remain "idle" (Process() returns OK) until at least one input port provides data.
 *               From this point, the node will go to a "processing state": It will expect data on all required inputs,
 *               otherwise it will return INSUFFICIENT_INPUT. It will return to "idle" when all input data is consumed.
 *               This function helps to serve this pattern.
 *  \param[in]   InputPortInfos List of input ports to check.
 *  \param[in]   Count          Length of list
 *  \return      TRUE           At least one input port has data available.
 *  \return      FALSE          Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_ProcNode_IsInputDataAvailable(
  vStreamProc_InputPortInfoConstPtrType InputPortInfos,
  vStreamProc_InputPortIdType Count);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_Init
 *********************************************************************************************************************/
/*! \brief         Initializes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo        NodeInfo structure of a padding processing node.
 *  \return        E_OK            Initialization was successful
 *  \return        E_NOT_OK        Initialization was unsuccessful
 *  \pre           Must be called before call of any vSwUpdM_ProcNodePadding function
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_Process
 *********************************************************************************************************************/
/*! \brief         Processes the passed node.
 *  \details       This node pads the input data to align with the page boundaries of the memory to be written.
 *                 The padding at the end is added when the node is flushed.
 *  \param[in]     NodeInfo        NodeInfo structure of a padding processing node.
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
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_Flush
 **********************************************************************************************************************/
/*! \brief         Flushes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo                        NodeInfo structure of a padding processing node.
 *  \return        VSTREAMPROC_OK                  Flush was successful. Complete input data copied and padded.
 *                                                 Resulting unpadded/padded end addresses and lengths provided.
 *  \return        VSTREAMPROC_PENDING             Flush is not finished yet.
 *  \return        VSTREAMPROC_INSUFFICIENT_OUTPUT Node can not be flushed as pending input data exceeds available
 *                                                 output storage.
 *  \return        VSTREAMPROC_FAILED              Flush failed.
 *  \pre          -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_ProcessInternal
 *********************************************************************************************************************/
/*! \brief         Processes the passed node.
 *  \details       This node pads the input data to align with the page boundaries of the memory to be written.
 *                 The padding at the end is added when the node is flushed.
 *  \param[in]     NodeInfo                        NodeInfo structure of a padding processing node.
 *  \param[in]     Workspace                       Workspace of the processing node.
 *  \param[in]     Ports                           The structure for generalized port access.
 *  \return        VSTREAMPROC_OK                  Process has handled the available input data or process not started
 *                                                 yet because of missing range information or entity IDs.
 *  \return        VSTREAMPROC_PENDING             Process is not finished yet.
 *  \return        VSTREAMPROC_FAILED              Process failed.
 *  \return        VSTREAMPROC_INSUFFICIENT_OUTPUT Process interrupted as input data exceeds available output storage.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_ProcessInternal(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodePaddingWorkspacePtrType Workspace,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_FlushInternal
 **********************************************************************************************************************/
/*! \brief         Flushes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo                        NodeInfo structure of a padding processing node.
 *  \param[in]     Workspace                       Workspace of the processing node.
 *  \param[in]     Ports                           The structure for generalized port access.
 *  \return        VSTREAMPROC_OK                  Flush was successful. Complete input data copied and padded.
 *                                                 Resulting unpadded/padded end addresses and lengths provided.
 *  \return        VSTREAMPROC_PENDING             Flush is not finished yet.
 *  \return        VSTREAMPROC_INSUFFICIENT_OUTPUT Node can not be flushed as pending input data exceeds available
 *                                                 output storage.
 *  \return        VSTREAMPROC_FAILED              Flush failed.
 *  \pre          -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_FlushInternal(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodePaddingWorkspacePtrType Workspace,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/**********************************************************************************************************************
 * PROCESSING NODE: WRITE
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeWrite_Init
 *********************************************************************************************************************/
/*! \brief         Initializes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo NodeInfo structure of a write processing node.
 *  \return        E_OK     Initialization was successful
 *  \return        E_NOT_OK Initialization was unsuccessful
 *  \pre           Must be called before call of any vSwUpdM_ProcNodeWrite function
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWrite_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeWrite_Process
 *********************************************************************************************************************/
/*! \brief         Processes the passed node.
 *  \details       This node writes the input data to the requested memory range.
 *  \param[in]     NodeInfo            NodeInfo structure of a write processing node.
 *  \return        VSTREAMPROC_OK      Process has handled the available input data or process not started
 *                                     yet because of missing range information or entity IDs.
 *  \return        VSTREAMPROC_PENDING Process is not finished yet.
 *  \return        VSTREAMPROC_FAILED  Process failed.
 *  \pre           Requested range and input data must be aligned to page boundaries.
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWrite_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeWrite_Flush
 **********************************************************************************************************************/
/*! \brief         Flushes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo            NodeInfo structure of a write processing node.
 *  \return        VSTREAMPROC_OK      Flush was successful. Complete input data written.
 *  \return        VSTREAMPROC_PENDING Flush is not yet finished.
 *  \return        VSTREAMPROC_FAILED  Flush failed.
 *  \pre           Requested range and input data must be aligned to page boundaries.
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWrite_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 * PROCESSING NODE: READ
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeRead_Init
 *********************************************************************************************************************/
/*! \brief         Initializes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo NodeInfo structure of a read processing node.
 *  \return        E_OK     Initialization was successful
 *  \return        E_NOT_OK Initialization was unsuccessful
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeRead_Process
 *********************************************************************************************************************/
/*! \brief         Processes the passed node.
 *  \details       This node reads the requested memory range.
 *  \param[in]     NodeInfo                        NodeInfo structure of a read processing node.
 *  \return        VSTREAMPROC_OK                  Process has handled the available input data or process not started
 *                                                 yet because of missing range information or entity IDs.
 *  \return        VSTREAMPROC_PENDING             Process is not finished yet.
 *  \return        VSTREAMPROC_FAILED              Process failed.
 *  \return        VSTREAMPROC_INSUFFICIENT_OUTPUT Process interrupted as remaining data to be read exceeds available
 *                                                 output storage.
 *  \pre           vSwUpdM_ProcNodeRead_Init() must be called before.
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeRead_Flush
 **********************************************************************************************************************/
/*! \brief         Flushes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo                        NodeInfo structure of a read processing node.
 *  \return        VSTREAMPROC_OK                  Flush was successful. Data read completely.
 *  \return        VSTREAMPROC_PENDING             Flush is not yet finished.
 *  \return        VSTREAMPROC_FAILED              Flush failed.
 *  \return        VSTREAMPROC_INSUFFICIENT_OUTPUT Node can not be flushed as remaining data to be read exceeds
 *                 vSwUpdM_ProcNodeRead_Init() must be called before.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 * PROCESSING NODE: TRACK COMPARE PROGRESS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeTrackCompareProgress_Init
 *********************************************************************************************************************/
/*! \brief         Initializes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo NodeInfo structure of a processing node which tracks the progress of a comparison.
 *  \return        E_OK     Initialization was successful
 *  \return        E_NOT_OK Initialization was unsuccessful
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeTrackCompareProgress_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeTrackCompareProgress_Process
 *********************************************************************************************************************/
/*! \brief         Processes the passed node.
 *  \details       This node updates the address of the current segment based on the progress of a comparison.
 *  \param[in]     NodeInfo            NodeInfo structure of a processing node which tracks the progress of
 *                                     a comparison.
 *  \return        VSTREAMPROC_OK      Comparison covered the announced range or process not started
 *                                     yet because of missing range information or entity IDs.
 *  \return        VSTREAMPROC_PENDING Process is not finished yet.
 *  \return        VSTREAMPROC_FAILED  Process failed.
 *  \pre           vSwUpdM_ProcNodeTrackCompareProgress_Init() must be called before.
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeTrackCompareProgress_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeTrackCompareProgress_Flush
 **********************************************************************************************************************/
/*! \brief         Flushes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo            NodeInfo structure of a processing node which tracks the progress of
 *                                     a comparison.
 *  \return        VSTREAMPROC_OK      Flush was successful. Complete announced range covered by comparison.
 *  \return        VSTREAMPROC_PENDING Flush is not finished yet.
 *  \return        VSTREAMPROC_FAILED  Flush failed.
 *  \pre           vSwUpdM_ProcNodeTrackCompareProgress_Init() must be called before.
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeTrackCompareProgress_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 * PROCESSING NODE: REMOTE
 *********************************************************************************************************************/

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeRemote_Init
 *********************************************************************************************************************/
/*! \brief         Initializes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo NodeInfo structure of a generic node containing a remote processing node.
 *  \return        E_OK     Initialization was successful
 *  \return        E_NOT_OK Initialization was unsuccessful
 *  \pre           Must be called before call of any vSwUpdM_ProcNodeRemote function
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRemote_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeRemote_Process
 *********************************************************************************************************************/
/*! \brief         Processes the passed node.
 *  \details       This node transfers the input data to the remote node which is owner of current segment.
 *  \param[in]     NodeInfo            NodeInfo structure of a generic node containing a remote processing node.
 *  \return        VSTREAMPROC_OK      Process has handled the available input data or process not started
 *                                     yet because of entity IDs.
 *  \return        VSTREAMPROC_PENDING Process is not finished yet.
 *  \return        VSTREAMPROC_FAILED  Process failed.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRemote_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeRemote_Flush
 **********************************************************************************************************************/
/*! \brief         Flushes the passed node.
 *  \details       -
 *  \param[in]     NodeInfo            NodeInfo structure of a generic node containing a remote processing node.
 *  \return        VSTREAMPROC_OK      Flush was successful. Complete input data transferred.
 *  \return        VSTREAMPROC_PENDING Flush is not yet finished.
 *  \return        VSTREAMPROC_FAILED  Flush failed.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRemote_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo);

#endif

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_PROCNODES_H */

/**********************************************************************************************************************
*  END OF FILE: vSwUpdM_ProcNodes.h
*********************************************************************************************************************/
