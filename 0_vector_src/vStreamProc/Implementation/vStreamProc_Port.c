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
/*!        \file vStreamProc_Port.c
 *        \brief  vStreamProc processing node specific source code file
 *
 *      \details  Implementation of helpers for the vStreamProc processing node modules.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the vStreamProc module. >> vStreamProc.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vStreamProc.h.
 *********************************************************************************************************************/
# define VSTREAMPROC_PORT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc_Port.h"
#include "vStreamProc.h"

# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
#  include "Det.h"
# endif

/**********************************************************************************************************************
 *  MISRA & PClint
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
# if !defined (VSTREAMPROC_LOCAL)
#  define VSTREAMPROC_LOCAL static
# endif

# if !defined (VSTREAMPROC_LOCAL_INLINE)
#  define VSTREAMPROC_LOCAL_INLINE LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/*! Function pointer for input port operations (used by iterator). */
typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_InputPortOperationPtrType)(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfo);

/*! Function pointer for output port operations (used by iterator). */
typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_OutputPortOperationPtrType)(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo);

/*! Symbolic names of port operations (used by iterator). */
typedef enum
{
  VSTREAMPROC_PORT_OPERATION_PREPARE_INFO,
  VSTREAMPROC_PORT_OPERATION_GET_INFO,
  VSTREAMPROC_PORT_OPERATION_REQUEST_DATA,
  VSTREAMPROC_PORT_OPERATION_ACKNOWLEDGE,
  VSTREAMPROC_PORT_OPERATION_RELEASE,
  VSTREAMPROC_PORT_OPERATION_COUNT
} vStreamProc_PortOperationType;

/*! Configuration element for port operations (used by iterator). */
typedef struct
{
  vStreamProc_InputPortOperationPtrType   InputPortOperation;
  vStreamProc_OutputPortOperationPtrType  OutputPortOperation;
} vStreamProc_PortOperationConfigType;

/*! Parameter structure for port iterator. */
typedef struct
{
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo;
  vStreamProc_PortOperationType   Operation;
  boolean                         AbortOnError;
} vStreamProc_PortIteratorParamType;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * vStreamProc_Port_SetResultBySeverity()
 **********************************************************************************************************************/
/*! \brief          Set the result, taking severity into account.
 *  \details        Overwrite the output result by the input results, if the latter is more severe.
 *  \param[in]      InputResult   The current result value.
 *  \param[in,out]  OutputResult  In: The previous result value. Out: The new result value.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(void, VSTREAMPROC_CODE) vStreamProc_Port_SetResultBySeverity(
  vStreamProc_ReturnType InputResult,
  P2VAR(vStreamProc_ReturnType, AUTOMATIC, VSTREAMPROC_APPL_VAR) OutputResult);

/**********************************************************************************************************************
 * vStreamProc_Port_PrepareStorageInfo()
 **********************************************************************************************************************/
/*! \brief      Initialize storage info structure with default values.
 *  \details    -
 *  \param[out] StorageInfo   The storage info structure to be initialized.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_Port_PrepareStorageInfo(
  P2VAR(vStreamProc_StorageInfoType, AUTOMATIC, VSTREAMPROC_APPL_VAR) StorageInfo);

/**********************************************************************************************************************
 * vStreamProc_Port_InitPortIteratorParam()
 **********************************************************************************************************************/
/*! \brief          Initialize parameter structure for port iterator.
 *  \details        -
 *  \param[in]      ProcNodeInfo      The processing node information to operate on.
 *  \param[in]      Operation         The operation to apply to all port structures.
 *  \param[in]      AbortOnError      Abort the iteration in case any other result than VSTREAMPROC_OK is returned
 *                                    when applying the operation to an port structure.
 *  \return         Initialized vStreamProc_PortIteratorParamType structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_PortIteratorParamType, VSTREAMPROC_CODE) vStreamProc_Port_InitPortIteratorParam(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_PortOperationType Operation,
  boolean AbortOnError);

/**********************************************************************************************************************
 * vStreamProc_Port_IteratePortInfos()
 **********************************************************************************************************************/
/*! \brief          Iterate over all passed port structures and apply the given operation.
 *  \details        -
 *  \param[in]      IteratorParam     The iterator parameter structure.
 *  \param[in,out]  EntryPointInfos   Entry point information structures. NULL_PTR if not used.
 *  \param[in]      EntryPointCount   Number of entry point information structures.
 *  \param[in,out]  ExitPointInfos    Exit point information structures. NULL_PTR if not used.
 *  \param[in]      ExitPointCount    Number of exit point information structures.
 *  \return         VSTREAMPROC_FAILED                Operation failed for at least one port.
 *  \return         VSTREAMPROC_INSUFFICIENT_OUTPUT   At least one port cannot provide the requested minimum storage.
 *  \return         VSTREAMPROC_INSUFFICIENT_INPUT    At least one port cannot provide the requested minimum data.
 *  \return         VSTREAMPROC_OK                    Operation was successful for all ports.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_IteratePortInfos(
  vStreamProc_PortIteratorParamType IteratorParam,
  vStreamProc_InputPortInfoPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_OutputPortInfoPtrType OutputPortInfos,
  vStreamProc_OutputPortIdType OutputPortCount);

/**********************************************************************************************************************
 * vStreamProc_Port_RemapStorageNodeResult()
 **********************************************************************************************************************/
/*! \brief          Remap result of storage node operation to processing node result.
 *  \details        Exchange return codes for insufficient input and output, as those are switched from the
 *                  processing node point of view, compared to the pipe access points.
 *  \param[in]      StorageNodeResult  Result of storage node operation.
 *  \return         VSTREAMPROC_INSUFFICIENT_OUTPUT   Storage node result was VSTREAMPROC_INSUFFICIENT_INPUT.
 *  \return         VSTREAMPROC_INSUFFICIENT_INPUT    Storage node result was VSTREAMPROC_INSUFFICIENT_OUTPUT.
 *  \return         Value of StorageNodeResult        Otherwise.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_RemapStorageNodeResult(
  vStreamProc_ReturnType StorageNodeResult);

/**********************************************************************************************************************
 *  vStreamProc_Port_PrepareInputPortInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize input port information structure.
 * \details       -
 * \param[in,out] ProcNodeInfo              The processing node information to operate on.
 * \param[out]    InputPortInfo             Pointer to input port information structure.
 *                - Input
 *                  - SymbolicPortName                            A named input port of the processing node.
 *                - Output
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Set to vStreamProcConf_vStreamProcDataType_Undefined.
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Size   Set to zero.
 *                  - ReadRequest.StorageInfo.AvailableLength     Set to zero.
 *                  - ReadRequest.StorageInfo.RequestLength       Set to zero.
 *                  - ReadRequest.StorageInfo.ReleaseFlag         Set to TRUE.
 *                  - ReadRequest.Buffer                          Set to NULL_PTR.
 *                  - PortHandle                                  Set to handle matching the named input port.
 *                  - IsConnected                                 TRUE if port is connected, FALSE otherwise.
 * \return        VSTREAMPROC_OK      Operation was successful.
 * \return        VSTREAMPROC_FAILED  Operation was unsuccessful.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_PrepareInputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_Port_GetInputPortInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Get information about a processing node input port.
 * \details       -
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in,out] InputPortInfo     Pointer to input port information structure.
 *                - Input
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the expected data type of the storage node
 *                                                                connected to the port.
 *                                                                vStreamProcConf_vStreamProcDataType_Undefined if
 *                                                                no specific data type is expected.
 *                  - ReadRequest.StorageInfo.RequestLength       Requested minimum buffer length.
 *                  - PortHandle                                  Handle of an input port of the processing node.
 *                  - SymbolicPortName                            Named input port of the processing node.
 *                - Output
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the actual data type of the storage node
 *                                                                connected to the port.
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Size   Byte size of data type of the storage node
 *                                                                connected to the port.
 *                  - ReadRequest.StorageInfo.AvailableLength     Available buffer length.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    Requested minimum buffer length isn't available.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_GetInputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_Port_RequestInputPortData()
 *********************************************************************************************************************/
/*!
 * \brief         Requests a read action.
 * \details       This call does not read any data from the buffer. It rather provides pointer and length information.
 *                The application then has to do the data reading based on this information. If data is available, the
 *                provided pointer does not change until a read acknowledge is issued. Defragmentation may be blocked
 *                due to a pending read request. A read request that indicates data must always be acknowledged to release
 *                the defragmentation lock.
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in,out] InputPortInfo     Pointer to input port information structure.
 *                - Input
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the expected data type of the storage node
 *                                                                connected to the port.
 *                  - ReadRequest.StorageInfo.RequestLength       Requested minimum buffer length.
 *                  - PortHandle                                  Handle of an input port of the processing node.
 *                  - SymbolicPortName                            Named input port of the processing node.
 *                - Output
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the actual data type of the storage node
 *                                                                connected to the port.
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Size   Byte size of data type of the storage node
 *                                                                connected to the port.
 *                  - ReadRequest.StorageInfo.AvailableLength     Available buffer length.
 *                  - ReadRequest.Buffer                          Pointer to available buffer.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    Requested minimum buffer length isn't available.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_RequestInputPortData(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_Port_AcknowledgeInputPort()
 *********************************************************************************************************************/
/*!
 * \brief         Acknowledges a read action.
 * \details       The processing node shall have issued a read request which then can be acknowledge by calling this
 *                function. Therefore, the amount of consumed data must be provided. By acknowledging a read request
 *                a possible defragmentation lock is being released.
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in,out] InputPortInfo     Pointer to input port information structure.
 *                - Input
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the expected data type of the storage node
 *                                                                connected to the port.
 *                                                                Only required when storage lock is kept.
 *                  - ReadRequest.StorageInfo.RequestLength       The amount of consumed data which needs to be acknowledged.
 *                  - ReadRequest.StorageInfo.ReleaseFlag         Flag to control release of storage lock.
 *                    - TRUE: Release storage lock.
 *                    - FALSE: Keep storage locked.
 *                  - PortHandle                                  Handle of an input port of the processing node.
 *                  - SymbolicPortName                            Named input port of the processing node.
 *                - Output
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the actual data type of the storage node
 *                                                                connected to the port.
 *                                                                Only set when storage lock is kept.
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Size   Byte size of data type of the storage node
 *                                                                connected to the port.
 *                                                                Only set when storage lock is kept.
 *                  - ReadRequest.StorageInfo.AvailableLength     Updated available buffer length.
 *                                                                Zero if storage lock was released.
 *                  - ReadRequest.StorageInfo.RequestLength       Passed produced length value.
 *                                                                Zero if storage lock was released.
 *                  - ReadRequest.Buffer                          Updated pointer to available buffer.
 *                                                                NULL_PTR if storage lock was released.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_AcknowledgeInputPort(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_Port_ReleaseInputPort()
 *********************************************************************************************************************/
/*!
 * \brief         Releases storage lock of an input port.
 * \details       -
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in]     InputPortInfo     Pointer to input port information structure.
 *                - PortHandle                                  Handle of an input port of the processing node.
 *                - SymbolicPortName                            Named input port of the processing node.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_ReleaseInputPort(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_Port_PrepareOutputPortInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize output port information structure.
 * \details       -
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in]     SymbolicNameOfOutputPort  A named output port of the processing node.
 * \param[out]    OutputPortInfo            Pointer to output port information structure.
 *                - Input
 *                  - SymbolicPortName                            A named output port of the processing node.
 *                - Output
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Set to vStreamProcConf_vStreamProcDataType_Undefined.
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Size  Set to zero.
 *                  - WriteRequest.StorageInfo.AvailableLength    Set to zero.
 *                  - WriteRequest.StorageInfo.RequestLength      Set to zero.
 *                  - WriteRequest.StorageInfo.ReleaseFlag        Set to TRUE.
 *                  - WriteRequest.Buffer                         Set to NULL_PTR.
 *                  - PortHandle                                  Set to handle matching the named output port.
 *                  - IsConnected                                 TRUE if port is connected, FALSE otherwise.
 * \return        VSTREAMPROC_OK      Operation was successful.
 * \return        VSTREAMPROC_FAILED  Operation was unsuccessful.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_PrepareOutputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_Port_GetOutputPortInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Get information about a processing node output port.
 * \details       -
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in,out] OutputPortInfo    Pointer to output port information structure.
 *                - Input
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the expected data type of the storage node
 *                                                                connected to the port.
 *                                                                vStreamProcConf_vStreamProcDataType_Undefined if
 *                                                                no specific data type is expected.
 *                  - WriteRequest.StorageInfo.RequestLength      Requested minimum buffer length.
 *                  - PortHandle                                  Handle of an output port of the processing node.
 *                  - SymbolicPortName                            Named output port of the processing node.
 *                - Output
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the actual data type of the storage node
 *                                                                connected to the port.
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Size  Byte size of data type of the storage node
 *                                                                connected to the port.
 *                  - WriteRequest.StorageInfo.AvailableLength    Available buffer length.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_GetOutputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_Port_RequestOutputPortData()
 *********************************************************************************************************************/
/*!
 * \brief         Requests a write action.
 * \details       This call does not write any data to a buffer. It rather provides the pointer and length information
 *                to the application. The application can then write its data to the provided pointer while the
 *                maximum data amount is limited by the provided available length.
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in,out] OutputPortInfo    Pointer to output port information structure.
 *                - Input
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the expected data type of the storage node
 *                                                                connected to the port.
 *                  - WriteRequest.StorageInfo.RequestLength      Requested minimum buffer length.
 *                  - PortHandle                                  Handle of an output port of the processing node.
 *                  - SymbolicPortName                            Named output port of the processing node.
 *                - Output
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the actual data type of the storage node
 *                                                                connected to the port.
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Size  Byte size of data type of the storage node
 *                                                                connected to the port.
 *                  - WriteRequest.StorageInfo.AvailableLength    Available buffer length.
 *                  - WriteRequest.Buffer                         Pointer to available buffer.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_RequestOutputPortData(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_Port_AcknowledgeOutputPort()
 *********************************************************************************************************************/
/*!
 * \brief         Acknowledges a write action.
 * \details       The processing node shall have requested a write request which then can be acknowledge by calling
 *                this function. The write request only provides a maximum amount of data to be produced, but it does
 *                not specify a precise amount of data which shall be produced. Therefore, the amount of produced
 *                data must be provided by calling this function.
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in,out] OutputPortInfo    Pointer to output port information structure.
 *                - Input
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the expected data type of the storage node
 *                                                                connected to the port.
 *                                                                Only required when storage lock is kept.
 *                  - WriteRequest.StorageInfo.RequestLength      The amount of produced data which needs to be acknowledged.
 *                  - WriteRequest.StorageInfo.ReleaseFlag        Flag to control release of storage lock.
 *                    - TRUE: Release storage lock.
 *                    - FALSE: Keep storage locked.
 *                  - PortHandle                                  Handle of an output port of the processing node.
 *                  - SymbolicPortName                            Named output port of the processing node.
 *                - Output
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the actual data type of the storage node
 *                                                                connected to the port.
 *                                                                Only set when storage lock is kept.
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Size  Byte size of data type of the storage node
 *                                                                connected to the port.
 *                                                                Only set when storage lock is kept.
 *                  - WriteRequest.StorageInfo.AvailableLength  Updated available buffer length.
 *                                                              Zero if storage lock was released.
 *                  - WriteRequest.StorageInfo.RequestLength      Passed produced length value.
 *                                                                Zero if storage lock was released.
 *                  - WriteRequest.StorageInfo.ReleaseFlag        Passed release flag value.
 *                  - WriteRequest.Buffer                       Updated pointer to available buffer.
 *                                                              NULL_PTR if storage lock was released.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_AcknowledgeOutputPort(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_Port_ReleaseOutputPort()
 *********************************************************************************************************************/
/*!
 * \brief         Releases storage lock of an output port.
 * \details       -
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in]     OutputPortInfo    Pointer to output port information structure.
 *                - PortHandle                                  Handle of an output port of the processing node.
 *                - SymbolicPortName                            Named output port of the processing node.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_ReleaseOutputPort(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo);

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

# define VSTREAMPROC_START_SEC_CODE
# include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vStreamProc_Port_SetResultBySeverity()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL_INLINE FUNC(void, VSTREAMPROC_CODE) vStreamProc_Port_SetResultBySeverity(
  vStreamProc_ReturnType InputResult,
  P2VAR(vStreamProc_ReturnType, AUTOMATIC, VSTREAMPROC_APPL_VAR) OutputResult)
{
  /* #10 Overwrite the output result by the input results, if the latter is more severe. */
  if (InputResult > *OutputResult)
  {
    *OutputResult = InputResult;
  }
}

/**********************************************************************************************************************
 *  vStreamProc_Port_PrepareStorageInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_Port_PrepareStorageInfo(
  P2VAR(vStreamProc_StorageInfoType, AUTOMATIC, VSTREAMPROC_APPL_VAR) StorageInfo)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize storage info structure with default values. */
  StorageInfo->DataTypeInfo.Id    = vStreamProcConf_vStreamProcDataType_Undefined;
  StorageInfo->DataTypeInfo.Size  = 0u;
  StorageInfo->AvailableLength    = 0u;
  StorageInfo->RequestLength      = 0u;
  StorageInfo->ReleaseFlag        = TRUE;
}

/**********************************************************************************************************************
 *  vStreamProc_Port_IteratePortInfos()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_PortIteratorParamType, VSTREAMPROC_CODE) vStreamProc_Port_InitPortIteratorParam(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_PortOperationType Operation,
  boolean AbortOnError)
{
  vStreamProc_PortIteratorParamType iteratorParam;

  /* #10 Assign passed parameters to structure members and return by value. */
  iteratorParam.ProcNodeInfo  = ProcNodeInfo;
  iteratorParam.Operation     = Operation;
  iteratorParam.AbortOnError  = AbortOnError;

  return iteratorParam;
}

/**********************************************************************************************************************
 *  vStreamProc_Port_IteratePortInfos()
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
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_IteratePortInfos(
  vStreamProc_PortIteratorParamType IteratorParam,
  vStreamProc_InputPortInfoPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_OutputPortInfoPtrType OutputPortInfos,
  vStreamProc_OutputPortIdType OutputPortCount)
{
  /* ----- Local Constants ---------------------------------------------- */
  /*! Lookup table for port operation functions. */
  CONST(vStreamProc_PortOperationConfigType, AUTOMATIC) vStreamProc_PortOperationConfig[VSTREAMPROC_PORT_OPERATION_COUNT] =
  {
    { vStreamProc_Port_PrepareInputPortInfo,    vStreamProc_Port_PrepareOutputPortInfo },
    { vStreamProc_Port_GetInputPortInfo,        vStreamProc_Port_GetOutputPortInfo },
    { vStreamProc_Port_RequestInputPortData,    vStreamProc_Port_RequestOutputPortData },
    { vStreamProc_Port_AcknowledgeInputPort,    vStreamProc_Port_AcknowledgeOutputPort },
    { vStreamProc_Port_ReleaseInputPort,        vStreamProc_Port_ReleaseOutputPort }
  };


  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType        retVal = VSTREAMPROC_OK;
  vStreamProc_ReturnType        opRetVal;
  vStreamProc_InputPortIdType   inputPortIndex;
  vStreamProc_OutputPortIdType  outputPortIndex;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For all input port infos */
  for (inputPortIndex = 0u; inputPortIndex < InputPortCount; inputPortIndex++)
  {
    /* #20 Execute input port operation. */
    opRetVal = vStreamProc_PortOperationConfig[IteratorParam.Operation].InputPortOperation(IteratorParam.ProcNodeInfo, &InputPortInfos[inputPortIndex]);

    /* Results with higher severity overwrite existing value. */
    if (opRetVal > retVal)
    {
      retVal = opRetVal;

      /* #30 Abort further processing if requested. */
      if (IteratorParam.AbortOnError == TRUE)
      {
        break;
      }
    }
  }

  if ( (retVal == VSTREAMPROC_OK) || (IteratorParam.AbortOnError == FALSE) )
  {
    /* #40 For all exit point infos */
    for (outputPortIndex = 0u; outputPortIndex < OutputPortCount; outputPortIndex++)
    {
      /* #50 Execute exit point operation. */
      opRetVal = vStreamProc_PortOperationConfig[IteratorParam.Operation].OutputPortOperation(IteratorParam.ProcNodeInfo, &OutputPortInfos[outputPortIndex]);

      /* Results with higher severity overwrite existing value. */
      if (opRetVal > retVal)
      {
        retVal = opRetVal;

        /* #60 Abort further processing if requested. */
        if (IteratorParam.AbortOnError == TRUE)
        {
          break;
        }
      }
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Port_IteratePortInfos()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_RemapStorageNodeResult(
  vStreamProc_ReturnType StorageNodeResult)
{
  vStreamProc_ReturnType retVal;

  /* #10 Exchange return codes for insufficient input and output. */
  switch (StorageNodeResult)
  {
    case VSTREAMPROC_INSUFFICIENT_INPUT:
    {
      retVal = VSTREAMPROC_INSUFFICIENT_OUTPUT;
      break;
    }
    case VSTREAMPROC_INSUFFICIENT_OUTPUT:
    {
      retVal = VSTREAMPROC_INSUFFICIENT_INPUT;
      break;
    }
    default:
    {
      /* #20 Other return codes remain unchanged. */
      retVal = StorageNodeResult;
      break;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Port_PrepareInputPortInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_PrepareInputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType                retVal        = VSTREAMPROC_FAILED;                                             /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_InputPortSymbolicNameType symbolicName  = InputPortInfo->SymbolicPortName;
  P2VAR(vStreamProc_ReadRequestType, AUTOMATIC, VSTREAMPROC_APPL_VAR) readRequest = &InputPortInfo->ReadRequest;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize read request with default values. */
  readRequest->Buffer = NULL_PTR;
  vStreamProc_Port_PrepareStorageInfo(&readRequest->StorageInfo);

  /* #20 Evaluate port handle and connection status for given symbolic name. */
  retVal = vStreamProc_GetInputPortHandle(ProcNodeInfo->ProcessingNodeId, symbolicName, &InputPortInfo->PortHandle, &InputPortInfo->IsConnected);

  /* #30 Return port specific result. Only overwrite when severity is higher. */
  vStreamProc_Port_SetResultBySeverity(retVal, &ProcNodeInfo->InputPortResults[symbolicName]);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Port_GetInputPortInfo()
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
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_GetInputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType          retVal = VSTREAMPROC_FAILED;                                                          /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_OutputPortIdType    storageOutputPortId   = InputPortInfo->PortHandle.OutputPortId;
  vStreamProc_StorageNodeIdType   storageNodeId         = InputPortInfo->PortHandle.StorageNodeId;
  vStreamProc_StorageInfoPtrType  storageInfo           = &InputPortInfo->ReadRequest.StorageInfo;
  vStreamProc_DataTypeIdType      expectedDataTypeId    = storageInfo->DataTypeInfo.Id;
  vStreamProc_ReturnType          storageResult;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If port is connected */
  if (InputPortInfo->IsConnected == TRUE)
  {
    /* #20 Issue stream request to associated storage node. */
    storageResult = vStreamProc_CallReadInfoOfStorageNode(storageNodeId, storageInfo, storageOutputPortId);
    retVal        = vStreamProc_Port_RemapStorageNodeResult(storageResult);

    /* #30 Check against expected data type, unless no specific data type is requested. */
    if ( (retVal != VSTREAMPROC_FAILED)
      && (storageInfo->DataTypeInfo.Id != expectedDataTypeId) )
    {
      if (expectedDataTypeId != (vStreamProc_DataTypeIdType)vStreamProcConf_vStreamProcDataType_Undefined)
      {
        retVal = VSTREAMPROC_FAILED;
      }
    }
  }
  /* #40 Otherwise: */
  else
  {
    /* #50 Report insufficient input if any data was requested. Success otherwise. */
    if (storageInfo->RequestLength > 0u)
    {
      retVal = VSTREAMPROC_INSUFFICIENT_INPUT;
    }
    else
    {
      /* Failed result would interfere with batch requests for nodes with unconnected optional ports. */
      retVal = VSTREAMPROC_OK;
    }

    /* #60 Reset storage info to default values. */
    vStreamProc_Port_PrepareStorageInfo(storageInfo);
  }

  /* #70 Return port specific result. */
  ProcNodeInfo->InputPortResults[InputPortInfo->SymbolicPortName] = retVal;

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Port_RequestInputPortData()
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
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_RequestInputPortData(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType          retVal = VSTREAMPROC_FAILED;                                                          /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_OutputPortIdType    storageOutputPortId   = InputPortInfo->PortHandle.OutputPortId;
  vStreamProc_StorageNodeIdType   storageNodeId         = InputPortInfo->PortHandle.StorageNodeId;
  vStreamProc_StorageInfoPtrType  storageInfo           = &InputPortInfo->ReadRequest.StorageInfo;
  vStreamProc_DataTypeIdType      expectedDataTypeId    = storageInfo->DataTypeInfo.Id;
  vStreamProc_ReturnType          storageResult;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If port is connected */
  if (InputPortInfo->IsConnected == TRUE)
  {
    /* #20 Issue stream request to associated storage node */
    storageResult = vStreamProc_CallReadRequestOfStorageNode(storageNodeId, &InputPortInfo->ReadRequest, storageOutputPortId);
    retVal        = vStreamProc_Port_RemapStorageNodeResult(storageResult);

    /* #30 Check against expected data type */
    if ( (retVal != VSTREAMPROC_FAILED)
      && (storageInfo->DataTypeInfo.Id != expectedDataTypeId) )
    {
      retVal = VSTREAMPROC_FAILED;
      /* #40 Release port in case of mismatch. */
      (void)vStreamProc_Port_ReleaseInputPort(ProcNodeInfo, InputPortInfo);
    }
  }
  /* #50 Otherwise: */
  else
  {
    /* #60 Report insufficient input if any data was requested. Success otherwise. */
    if (storageInfo->RequestLength > 0u)
    {
      retVal = VSTREAMPROC_INSUFFICIENT_INPUT;
    }
    else
    {
      /* Failed result would interfere with batch requests for nodes with unconnected optional ports. */
      retVal = VSTREAMPROC_OK;
    }

    /* #70 Reset storage info to default values. */
    vStreamProc_Port_PrepareStorageInfo(storageInfo);
  }

  /* #80 Return port specific result. */
  ProcNodeInfo->InputPortResults[InputPortInfo->SymbolicPortName] = retVal;

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Port_AcknowledgeInputPort()
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
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_AcknowledgeInputPort(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType          retVal = VSTREAMPROC_FAILED;                                                          /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_OutputPortIdType    storageOutputPortId   = InputPortInfo->PortHandle.OutputPortId;
  vStreamProc_StorageNodeIdType   storageNodeId         = InputPortInfo->PortHandle.StorageNodeId;
  vStreamProc_StorageInfoPtrType  storageInfo           = &InputPortInfo->ReadRequest.StorageInfo;
  vStreamProc_ReturnType          storageResult;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If port is connected */
  if (InputPortInfo->IsConnected == TRUE)
  {
    /* #20 Issue stream request to associated storage node. */
    storageResult = vStreamProc_CallReadAckOfStorageNode(storageNodeId, storageInfo->RequestLength, storageOutputPortId);
    retVal        = vStreamProc_Port_RemapStorageNodeResult(storageResult);

    /*#30 If storage release is requested, reset buffer and available length. */
    if (storageInfo->ReleaseFlag == TRUE)
    {
      InputPortInfo->ReadRequest.Buffer = NULL_PTR;
      storageInfo->AvailableLength      = 0u;
    }
    /* #40 Otherwise, re-issue data request. */
    else
    {
      if (retVal == VSTREAMPROC_OK)
      {
        storageInfo->RequestLength = 0u;

        retVal = vStreamProc_Port_RequestInputPortData(ProcNodeInfo, InputPortInfo);
      }
    }
  }
  /* #50 Otherwise: */
  else
  {
    /* #60 Report success if zero acknowledge length was requested. General error otherwise. */
    if (storageInfo->RequestLength == 0u)
    {
      retVal = VSTREAMPROC_OK;
    }
  }

  /* #70 Return port specific result. Only overwrite when severity is higher. */
  vStreamProc_Port_SetResultBySeverity(retVal, &ProcNodeInfo->InputPortResults[InputPortInfo->SymbolicPortName]);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Port_ReleaseInputPort()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_ReleaseInputPort(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfo) /* PRQA S 3673 */ /* MD_vStreamProc_Rule8.13_3673_NonConstPtrParam */
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType        retVal = VSTREAMPROC_FAILED;                                                            /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_ReturnType        storageResult;
  vStreamProc_OutputPortIdType  storageOutputPortId   = InputPortInfo->PortHandle.OutputPortId;
  vStreamProc_StorageNodeIdType storageNodeId         = InputPortInfo->PortHandle.StorageNodeId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If port is connected */
  if (InputPortInfo->IsConnected == TRUE)
  {
    /* #20 Issue stream request to passed pipe/port */
    storageResult = vStreamProc_CallReadAckOfStorageNode(storageNodeId, 0u, storageOutputPortId);
    retVal        = vStreamProc_Port_RemapStorageNodeResult(storageResult);
  }
  /* #30 Otherwise, report success. */
  else
  {
    retVal = VSTREAMPROC_OK;
  }

  /* #40 Return port specific result. Only overwrite when severity is higher. */
  vStreamProc_Port_SetResultBySeverity(retVal, &ProcNodeInfo->InputPortResults[InputPortInfo->SymbolicPortName]);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Port_PrepareOutputPortInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_PrepareOutputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType                retVal = VSTREAMPROC_FAILED;                                                    /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_InputPortSymbolicNameType symbolicName  = OutputPortInfo->SymbolicPortName;
  P2VAR(vStreamProc_WriteRequestType, AUTOMATIC, VSTREAMPROC_APPL_VAR) writeRequest =
    &OutputPortInfo->WriteRequest;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize write request with default values. */
  writeRequest->Buffer = NULL_PTR;
  vStreamProc_Port_PrepareStorageInfo(&writeRequest->StorageInfo);

  /* #20 Evaluate port handle and connection status for given symbolic name. */
  retVal = vStreamProc_GetOutputPortHandle(ProcNodeInfo->ProcessingNodeId, symbolicName, &OutputPortInfo->PortHandle, &OutputPortInfo->IsConnected);

  /* #30 Return port specific result. Only overwrite when severity is higher. */
  vStreamProc_Port_SetResultBySeverity(retVal, &ProcNodeInfo->OutputPortResults[symbolicName]);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Port_GetOutputPortInfo()
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
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_GetOutputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType          retVal = VSTREAMPROC_FAILED;                                                          /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_StorageNodeIdType   storageNodeId         = OutputPortInfo->PortHandle;
  vStreamProc_StorageInfoPtrType  storageInfo           = &OutputPortInfo->WriteRequest.StorageInfo;
  vStreamProc_DataTypeIdType      expectedDataTypeId    = storageInfo->DataTypeInfo.Id;
  vStreamProc_ReturnType          storageResult;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If port is connected */
  if (OutputPortInfo->IsConnected == TRUE)
  {
    /* #20 Issue write requested to associated storage node. */
    storageResult = vStreamProc_CallWriteInfoOfStorageNode(storageNodeId, storageInfo);
    retVal        = vStreamProc_Port_RemapStorageNodeResult(storageResult);

    /* #30 Check against expected data type, unless no specific data type is requested. */
    if ( (retVal != VSTREAMPROC_FAILED)
      && (storageInfo->DataTypeInfo.Id != expectedDataTypeId) )
    {
      if (expectedDataTypeId != (vStreamProc_DataTypeIdType)vStreamProcConf_vStreamProcDataType_Undefined)
      {
        retVal = VSTREAMPROC_FAILED;
      }
    }
  }
  /* #40 Otherwise: */
  else
  {
    /* #50 Report insufficient output if any storage was requested. Success otherwise. */
    if (storageInfo->RequestLength > 0u)
    {
      retVal = VSTREAMPROC_INSUFFICIENT_OUTPUT;
    }
    else
    {
      /* Failed result would interfere with batch requests for nodes with unconnected optional ports. */
      retVal = VSTREAMPROC_OK;
    }

    /* #60 Reset storage info to default values. */
    vStreamProc_Port_PrepareStorageInfo(storageInfo);
  }

  /* #70 Return port specific result. */
  ProcNodeInfo->OutputPortResults[OutputPortInfo->SymbolicPortName] = retVal;

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Port_RequestOutputPortData()
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
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_RequestOutputPortData(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType          retVal = VSTREAMPROC_FAILED;                                                          /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_StorageNodeIdType   storageNodeId         = OutputPortInfo->PortHandle;
  vStreamProc_StorageInfoPtrType  storageInfo           = &OutputPortInfo->WriteRequest.StorageInfo;
  vStreamProc_DataTypeIdType      expectedDataTypeId    = storageInfo->DataTypeInfo.Id;
  vStreamProc_ReturnType          storageResult;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If port is connected */
  if (OutputPortInfo->IsConnected == TRUE)
  {
    /* #20 Issue write requested to associated storage node. */
    storageResult = vStreamProc_CallWriteRequestOfStorageNode(storageNodeId, &OutputPortInfo->WriteRequest);
    retVal        = vStreamProc_Port_RemapStorageNodeResult(storageResult);

    /* #30 Check against expected data type */
    if ( (retVal != VSTREAMPROC_FAILED)
      && (storageInfo->DataTypeInfo.Id != expectedDataTypeId) )
    {
      retVal = VSTREAMPROC_FAILED;
      /* #40 Release port in case of mismatch. */
      (void)vStreamProc_Port_ReleaseOutputPort(ProcNodeInfo, OutputPortInfo);
    }
  }
  else
  {
    /* #50 Report insufficient output if any storage was requested. Success otherwise. */
    if (storageInfo->RequestLength > 0u)
    {
      retVal = VSTREAMPROC_INSUFFICIENT_OUTPUT;
    }
    else
    {
      /* Failed result would interfere with batch requests for nodes with unconnected optional ports. */
      retVal = VSTREAMPROC_OK;
    }

    /* #60 Reset storage info to default values. */
    vStreamProc_Port_PrepareStorageInfo(storageInfo);
  }

  /* #70 Return port specific result. */
  ProcNodeInfo->OutputPortResults[OutputPortInfo->SymbolicPortName] = retVal;

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Port_AcknowledgeOutputPort()
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
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_AcknowledgeOutputPort(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType          retVal = VSTREAMPROC_FAILED;                                                          /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_StorageNodeIdType   storageNodeId         = OutputPortInfo->PortHandle;
  vStreamProc_StorageInfoPtrType  storageInfo           = &OutputPortInfo->WriteRequest.StorageInfo;
  vStreamProc_ReturnType          storageResult;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If port is connected */
  if (OutputPortInfo->IsConnected == TRUE)
  {
    /* #20 Issue write acknowledgment to associated storage node. */
    storageResult = vStreamProc_CallWriteAckOfStorageNode(storageNodeId, storageInfo->RequestLength);
    retVal        = vStreamProc_Port_RemapStorageNodeResult(storageResult);

    /*# 30 If storage release is requested, reset buffer and available length. */
    if (storageInfo->ReleaseFlag == TRUE)
    {
      OutputPortInfo->WriteRequest.Buffer = NULL_PTR;
      storageInfo->AvailableLength        = 0u;
    }
    /* #30 Otherwise, re-issue storage request. */
    else
    {
      if (retVal == VSTREAMPROC_OK)
      {
        storageInfo->RequestLength = 0u;

        retVal = vStreamProc_Port_RequestOutputPortData(ProcNodeInfo, OutputPortInfo);
      }
    }
  }
  /* #40 Otherwise: */
  else
  {
    /* #50 Report success if zero acknowledge length was requested. General error otherwise. */
    if (storageInfo->RequestLength == 0u)
    {
      retVal = VSTREAMPROC_OK;
    }
  }

  /* #60 Return port specific result. Only overwrite when severity is higher. */
  vStreamProc_Port_SetResultBySeverity(retVal, &ProcNodeInfo->OutputPortResults[OutputPortInfo->SymbolicPortName]);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Port_ReleaseOutputPort()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Port_ReleaseOutputPort(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo) /* PRQA S 3673 */ /* MD_vStreamProc_Rule8.13_3673_NonConstPtrParam */
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType        retVal = VSTREAMPROC_FAILED;                                                            /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_ReturnType        storageResult;
  vStreamProc_StorageNodeIdType storageNodeId         = OutputPortInfo->PortHandle;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If port is connected */
  if (OutputPortInfo->IsConnected == TRUE)
  {
    /* #20 Issue write acknowledgment to passed pipe/port */
    storageResult = vStreamProc_CallWriteAckOfStorageNode(storageNodeId, 0u);
    retVal        = vStreamProc_Port_RemapStorageNodeResult(storageResult);
  }
  /* #30 Otherwise, report success. */
  else
  {
    retVal = VSTREAMPROC_OK;
  }

  /* #40 Return port specific result. Only overwrite when severity is higher. */
  vStreamProc_Port_SetResultBySeverity(retVal, &ProcNodeInfo->OutputPortResults[OutputPortInfo->SymbolicPortName]);

  return retVal;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  vStreamProc_InitProcessingNodeInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSTREAMPROC_CODE) vStreamProc_InitProcessingNodeInfo(
  vStreamProc_ProcessingNodeIdType ProcessingNodeId,
  P2VAR(vStreamProc_ReturnType, AUTOMATIC, VSTREAMPROC_APPL_DATA) InputPortResults,
  P2VAR(vStreamProc_ReturnType, AUTOMATIC, VSTREAMPROC_APPL_DATA) OutputPortResults,
  P2VAR(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  vStreamProc_ProcessingNodeDefIterType procNodeDefIdx  = vStreamProc_GetProcessingNodeDefIdxOfProcessingNode(ProcessingNodeId);
  vStreamProc_NamedInputPorts2ActualPortsIterType   inputPortIndex;
  vStreamProc_NamedOutputPorts2ActualPortsIterType  outputPortIndex;

  /* #10 Initialize node information attributes. */
  NodeInfo->ProcessingNodeId        = ProcessingNodeId;
  NodeInfo->SliceHandle             = vStreamProc_GetSliceOfProcessingNode(ProcessingNodeId);

  NodeInfo->InputPortResults        = InputPortResults;
  NodeInfo->OutputPortResults       = OutputPortResults;

  NodeInfo->InputPortCount          =
    (vStreamProc_InputPortIdType)vStreamProc_GetRequiredInputPortsOfProcessingNodeDef(procNodeDefIdx)
    + (vStreamProc_InputPortIdType)vStreamProc_GetOptionalInputPortsOfProcessingNodeDef(procNodeDefIdx);
  NodeInfo->OutputPortCount         =
    (vStreamProc_OutputPortIdType)vStreamProc_GetRequiredOutputPortsOfProcessingNodeDef(procNodeDefIdx)
    + (vStreamProc_OutputPortIdType)vStreamProc_GetOptionalOutputPortsOfProcessingNodeDef(procNodeDefIdx);

  NodeInfo->WorkspaceInfo.Pointer   = vStreamProc_GetWorkspaceOfProcessingNode(ProcessingNodeId);
  NodeInfo->WorkspaceInfo.TypeId    = vStreamProc_GetWorkspaceTypeOfProcessingNodeDef(procNodeDefIdx);

  NodeInfo->ConfigInfo.Pointer      = vStreamProc_GetConfigOfProcessingNodeDef(procNodeDefIdx);
  NodeInfo->ConfigInfo.TypeId       = vStreamProc_GetConfigTypeOfProcessingNodeDef(procNodeDefIdx);

  /* #20 Reset port specific results. */
  for (inputPortIndex = 0u; inputPortIndex < NodeInfo->InputPortCount; inputPortIndex++)
  {
    InputPortResults[inputPortIndex] = VSTREAMPROC_OK;
  }

  for (outputPortIndex = 0u; outputPortIndex < NodeInfo->OutputPortCount; outputPortIndex++)
  {
    OutputPortResults[outputPortIndex] = VSTREAMPROC_OK;
  }
}

/***********************************************************************************************************************
 *  vStreamProc_GetInputPortHandle
 **********************************************************************************************************************/
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
 */
FUNC(vStreamProc_ReturnType, AUTOMATIC) vStreamProc_GetInputPortHandle(
  vStreamProc_ProcessingNodeIdType ProcessingNodeId,
  vStreamProc_InputPortSymbolicNameType SymbolicNameOfInputPort,
  P2VAR(vStreamProc_InputPortHandleType, AUTOMATIC, VSTREAMPROC_APPL_DATA) InputPortHandle,
  P2VAR(boolean, AUTOMATIC, VSTREAMPROC_APPL_DATA) IsConnected)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;

  vStreamProc_ProcessingNodeDefIterType           procNodeDefId           =
    vStreamProc_GetProcessingNodeDefIdxOfProcessingNode(ProcessingNodeId);
  vStreamProc_NamedInputPorts2ActualPortsIterType requiredInputPortCount  =
    vStreamProc_GetRequiredInputPortsOfProcessingNodeDef(procNodeDefId);
  vStreamProc_NamedInputPorts2ActualPortsIterType inputPortCount          =
    requiredInputPortCount + vStreamProc_GetOptionalInputPortsOfProcessingNodeDef(procNodeDefId);

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Check for valid symbolic name. */
  if (SymbolicNameOfInputPort < inputPortCount)
  {
    boolean isConnected = FALSE;
    vStreamProc_NamedInputPorts2ActualPortsIterType inputPortIdx =
      vStreamProc_GetNamedInputPorts2ActualPortsStartIdxOfProcessingNode(ProcessingNodeId)
      + (vStreamProc_NamedInputPorts2ActualPortsIterType)SymbolicNameOfInputPort;

    /* #20 None of the optional ports may be mapped in the configuration at all. */
    if (inputPortIdx < vStreamProc_GetNamedInputPorts2ActualPortsEndIdxOfProcessingNode(ProcessingNodeId))
    {
      vStreamProc_ProcNode_StorageOutputPortsInputPortDynIterType indirectionIdx =
        vStreamProc_GetProcNode_StorageOutputPortsInputPortDynIdxOfNamedInputPorts2ActualPorts(inputPortIdx);

      /* #30 Check whether port is currently connected:
       *  + Mapped in configuration (valid entry in indirection table).
       *  + Dynamic mapping contains valid storage node output port.
       *  + Storage node output port is active. */
      if (indirectionIdx != VSTREAMPROC_NO_PROCNODE_STORAGEOUTPUTPORTSINPUTPORTDYNIDXOFNAMEDINPUTPORTS2ACTUALPORTS)
      {
        vStreamProc_OutputPortIdType  storageOutputPortId = vStreamProc_GetProcNode_StorageOutputPortsInputPortDyn(indirectionIdx);
        vStreamProc_StorageNodeIdType storageNodeId       = vStreamProc_GetStorageNodeIdxOfStorageOutputPort(storageOutputPortId);

        if ( (storageOutputPortId != VSTREAMPROC_NO_STORAGEOUTPUTPORTIDXOFEDGE)
          && (vStreamProc_IsActiveInformationOfStorageOutputPortInfo(storageOutputPortId) == TRUE) )                    /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
        {
          isConnected = TRUE;
        }

        InputPortHandle->StorageNodeId = storageNodeId;
        InputPortHandle->OutputPortId  = storageOutputPortId;
      }
    }

    *IsConnected = isConnected;

    /* #40 Required ports MUST be connected. Otherwise this is an error! */
    if ( (isConnected == TRUE)
      || (SymbolicNameOfInputPort >= requiredInputPortCount) )
    {
      retVal = VSTREAMPROC_OK;
    }
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_GetInputPortHandle
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, AUTOMATIC) vStreamProc_GetOutputPortHandle(
  vStreamProc_ProcessingNodeIdType ProcessingNodeId,
  vStreamProc_OutputPortSymbolicNameType SymbolicNameOfOutputPort,
  P2VAR(vStreamProc_OutputPortHandleType, AUTOMATIC, VSTREAMPROC_APPL_DATA) OutputPortHandle,
  P2VAR(boolean, AUTOMATIC, VSTREAMPROC_APPL_DATA) IsConnected)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;

  vStreamProc_ProcessingNodeDefIterType             procNodeDefId           =
    vStreamProc_GetProcessingNodeDefIdxOfProcessingNode(ProcessingNodeId);
  vStreamProc_NamedOutputPorts2ActualPortsIterType  requiredOutputPortCount =
    vStreamProc_GetRequiredOutputPortsOfProcessingNodeDef(procNodeDefId);
  vStreamProc_NamedOutputPorts2ActualPortsIterType  outputPortCount         =
    requiredOutputPortCount + vStreamProc_GetOptionalOutputPortsOfProcessingNodeDef(procNodeDefId);

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Check for valid symbolic name. */
  if (SymbolicNameOfOutputPort < outputPortCount)
  {
    boolean isConnected = FALSE;
    vStreamProc_NamedOutputPorts2ActualPortsIterType outputPortIdx =
      vStreamProc_GetNamedOutputPorts2ActualPortsStartIdxOfProcessingNode(ProcessingNodeId)
      + (vStreamProc_NamedOutputPorts2ActualPortsIterType)SymbolicNameOfOutputPort;

    /* #20 None of the optional ports may be mapped in the configuration at all. */
    if (outputPortIdx < vStreamProc_GetNamedOutputPorts2ActualPortsEndIdxOfProcessingNode(ProcessingNodeId))
    {
      vStreamProc_StorageNodeIdxOfNamedOutputPorts2ActualPortsType storageNodeId  =
        (vStreamProc_NamedOutputPorts2ActualPortsIterType)vStreamProc_GetStorageNodeIdxOfNamedOutputPorts2ActualPorts(outputPortIdx);

      /* #30 Check whether port is currently connected:
       *  + Mapped in configuration (valid entry in indirection table).
       */
      if (storageNodeId != VSTREAMPROC_NO_STORAGENODEIDXOFNAMEDOUTPUTPORTS2ACTUALPORTS)
      {
        /* Output port is always active when mapped. */
        isConnected = TRUE;
      }

      *OutputPortHandle = storageNodeId;
    }

    *IsConnected = isConnected;

    /* #40 Required ports MUST be connected. Otherwise this is an error! */
    if ( (isConnected == TRUE)
      || (SymbolicNameOfOutputPort >= requiredOutputPortCount) )
    {
      retVal = VSTREAMPROC_OK;
    }
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_GetTypedWorkspaceOfProcessingNode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_GenericNodeWorkspaceType, VSTREAMPROC_CODE) vStreamProc_GetTypedWorkspaceOfProcessingNode(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_WorkspaceTypeIdType WorkspaceTypeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8                                 errorID       = VSTREAMPROC_E_NO_ERROR;
  vStreamProc_GenericNodeWorkspaceType  workspacePtr  = NULL_PTR;                                                       /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters */
  /* Check if ProcessingNodeId is an invalid ID */
  if (ProcNodeInfo == NULL_PTR)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  /* Compare workspace type of processing node against expected one. */
  else if (ProcNodeInfo->WorkspaceInfo.TypeId != WorkspaceTypeId)
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Return workspace pointer of processing node */
    workspacePtr = ProcNodeInfo->WorkspaceInfo.Pointer;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_GET_TYPED_WORKSPACE_OF_PROCESSING_NODE, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(WorkspaceTypeId);                                                                         /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return workspacePtr;
}

/***********************************************************************************************************************
 *  vStreamProc_GetTypedConfigOfProcessingNode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_GenericNodeConfigType, VSTREAMPROC_CODE) vStreamProc_GetTypedConfigOfProcessingNode(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_ConfigTypeIdType ConfigTypeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8                             errorID   = VSTREAMPROC_E_NO_ERROR;
  vStreamProc_GenericNodeConfigType configPtr = NULL_PTR;                                                               /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters */
  /* Check if ProcessingNodeId is an invalid ID */
  if (ProcNodeInfo == NULL_PTR)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  /* Compare configuration type of processing node definition against expected one. */
  else if (ProcNodeInfo->ConfigInfo.TypeId != ConfigTypeId)
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Return configuration pointer of processing node definition */
    configPtr = ProcNodeInfo->ConfigInfo.Pointer;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_GET_TYPED_CONFIG_OF_PROCESSING_NODE, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(ConfigTypeId);                                                                            /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return configPtr;
}

/**********************************************************************************************************************
 *  vStreamProc_PrepareInputPortInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareInputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortSymbolicNameType SymbolicNameOfInputPort,
  vStreamProc_InputPortInfoPtrType InputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set symbolic name in info structure.  */
  InputPortInfo->SymbolicPortName = SymbolicNameOfInputPort;

  /* #20 Issue prepare request to passed port. */
  retVal = vStreamProc_Port_PrepareInputPortInfo(ProcNodeInfo, InputPortInfo);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_GetInputPortInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_GetInputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_InputPortInfoPtrType InputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set data type in info structure. */
  InputPortInfo->ReadRequest.StorageInfo.DataTypeInfo.Id = DataTypeId;

  /* #20 Issue getter request to passed port. */
  retVal = vStreamProc_Port_GetInputPortInfo(ProcNodeInfo, InputPortInfo);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_RequestInputPortData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestInputPortData(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_LengthType RequestLength,
  vStreamProc_InputPortInfoPtrType InputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set data type and request length in info structure. */
  InputPortInfo->ReadRequest.StorageInfo.DataTypeInfo.Id  = DataTypeId;
  InputPortInfo->ReadRequest.StorageInfo.RequestLength    = RequestLength;

  /* #20 Issue request to passed port. */
  retVal = vStreamProc_Port_RequestInputPortData(ProcNodeInfo, InputPortInfo);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_AcknowledgeInputPort()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_AcknowledgeInputPort(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_LengthType ConsumedLength,
  boolean ReleaseFlag,
  vStreamProc_InputPortInfoPtrType InputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set request length and release flag in info structure. */
  InputPortInfo->ReadRequest.StorageInfo.RequestLength  = ConsumedLength;
  InputPortInfo->ReadRequest.StorageInfo.ReleaseFlag    = ReleaseFlag;

  /* #20 Issue acknowledge request to passed port. */
  retVal = vStreamProc_Port_AcknowledgeInputPort(ProcNodeInfo, InputPortInfo);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_PrepareOutputPortInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareOutputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_OutputPortSymbolicNameType SymbolicNameOfOutputPort,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set symbolic name in info structure. */
  OutputPortInfo->SymbolicPortName = SymbolicNameOfOutputPort;

  /* #20 Issue prepare request to passed port. */
  retVal = vStreamProc_Port_PrepareOutputPortInfo(ProcNodeInfo, OutputPortInfo);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_GetOutputPortInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_GetOutputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set data type in info structure. */
  OutputPortInfo->WriteRequest.StorageInfo.DataTypeInfo.Id = DataTypeId;

  /* #20 Issue getter request to passed port. */
  retVal = vStreamProc_Port_GetOutputPortInfo(ProcNodeInfo, OutputPortInfo);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_RequestOutputPortData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestOutputPortData(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_LengthType RequestLength,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set data type and request length in info structure. */
  OutputPortInfo->WriteRequest.StorageInfo.DataTypeInfo.Id  = DataTypeId;
  OutputPortInfo->WriteRequest.StorageInfo.RequestLength    = RequestLength;

  /* #20 Issue request to passed port. */
  retVal = vStreamProc_Port_RequestOutputPortData(ProcNodeInfo, OutputPortInfo);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_AcknowledgeOutputPort()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_AcknowledgeOutputPort(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_LengthType ProducedLength,
  boolean ReleaseFlag,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set request length and release flag in info structure. */
  OutputPortInfo->WriteRequest.StorageInfo.RequestLength  = ProducedLength;
  OutputPortInfo->WriteRequest.StorageInfo.ReleaseFlag    = ReleaseFlag;

  /* #20 Issue acknowledge request to passed port. */
  retVal = vStreamProc_Port_AcknowledgeOutputPort(ProcNodeInfo, OutputPortInfo);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_PreparePortInfos()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PreparePortInfos(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_OutputPortInfoPtrType OutputPortInfos,
  vStreamProc_OutputPortIdType OutputPortCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all passed port structures and apply prepare operation. */
  retVal = vStreamProc_Port_IteratePortInfos(
    vStreamProc_Port_InitPortIteratorParam(ProcNodeInfo, VSTREAMPROC_PORT_OPERATION_PREPARE_INFO, FALSE),
    InputPortInfos, InputPortCount, OutputPortInfos, OutputPortCount);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_PrepareAllPortInfos()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareAllPortInfos(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_OutputPortInfoPtrType OutputPortInfos,
  vStreamProc_OutputPortIdType OutputPortCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType        retVal = VSTREAMPROC_FAILED;                                                            /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_InputPortIdType   inputPortIndex;
  vStreamProc_OutputPortIdType  outputPortIndex;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize symbolic names of passed port structures to be equal to the zero-based index. */
  for (inputPortIndex = 0u; inputPortIndex < InputPortCount; inputPortIndex++)
  {
    InputPortInfos[inputPortIndex].SymbolicPortName = inputPortIndex;
  }

  for (outputPortIndex = 0u; outputPortIndex < OutputPortCount; outputPortIndex++)
  {
    OutputPortInfos[outputPortIndex].SymbolicPortName = outputPortIndex;
  }

  /* #20 Iterate over all passed ports infos and apply prepare operation. */
  retVal = vStreamProc_Port_IteratePortInfos(
    vStreamProc_Port_InitPortIteratorParam(ProcNodeInfo, VSTREAMPROC_PORT_OPERATION_PREPARE_INFO, FALSE),
    InputPortInfos, InputPortCount, OutputPortInfos, OutputPortCount);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_GetPortInfos()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_GetPortInfos(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_OutputPortInfoPtrType OutputPortInfos,
  vStreamProc_OutputPortIdType OutputPortCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all passed port infos and apply getter operation. */
  retVal = vStreamProc_Port_IteratePortInfos(
    vStreamProc_Port_InitPortIteratorParam(ProcNodeInfo, VSTREAMPROC_PORT_OPERATION_GET_INFO, FALSE),
    InputPortInfos, InputPortCount, OutputPortInfos, OutputPortCount);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_RequestPortData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestPortData(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_OutputPortInfoPtrType OutputPortInfos,
  vStreamProc_OutputPortIdType OutputPortCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all passed port infos and apply request operation. */
  retVal = vStreamProc_Port_IteratePortInfos(
    vStreamProc_Port_InitPortIteratorParam(ProcNodeInfo, VSTREAMPROC_PORT_OPERATION_REQUEST_DATA, FALSE),
    InputPortInfos, InputPortCount, OutputPortInfos, OutputPortCount);

  /* #20 If operation failed, iterate over all port point infos and apply release operation. */
  if (retVal != VSTREAMPROC_OK)
  {
    (void)vStreamProc_Port_IteratePortInfos(
      vStreamProc_Port_InitPortIteratorParam(ProcNodeInfo, VSTREAMPROC_PORT_OPERATION_RELEASE, FALSE),
      InputPortInfos, InputPortCount, OutputPortInfos, OutputPortCount);
  }

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_AcknowledgePorts()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_AcknowledgePorts(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_OutputPortInfoPtrType OutputPortInfos,
  vStreamProc_OutputPortIdType OutputPortCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all passed port infos and apply acknowledge operation. */
  retVal = vStreamProc_Port_IteratePortInfos(
    vStreamProc_Port_InitPortIteratorParam(ProcNodeInfo, VSTREAMPROC_PORT_OPERATION_ACKNOWLEDGE, FALSE),
    InputPortInfos, InputPortCount, OutputPortInfos, OutputPortCount);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_AcknowledgePorts()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ReleaseAllPorts(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType              retVal      = VSTREAMPROC_FAILED;                                                 /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_ProcessingNodeIdType    procNodeId  = ProcNodeInfo->ProcessingNodeId;
  vStreamProc_InputPortInfoType       inputPortInfos[vStreamProcConf_MaxInputPortCount];
  vStreamProc_OutputPortInfoType      outputPortInfos[vStreamProcConf_MaxOutputPortCount];
  vStreamProc_InputPortIdType         inputPortCount  =
    (vStreamProc_InputPortIdType)vStreamProc_GetNamedInputPorts2ActualPortsLengthOfProcessingNode(procNodeId);
  vStreamProc_OutputPortIdType        outputPortCount =
    (vStreamProc_OutputPortIdType)vStreamProc_GetNamedOutputPorts2ActualPortsLengthOfProcessingNode(procNodeId);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare all port infos, e.g. initialize symbolic names and port handles.  */
  retVal = vStreamProc_PrepareAllPortInfos(ProcNodeInfo, inputPortInfos, inputPortCount, outputPortInfos, outputPortCount);

  /* #20 Iterate over all access point infos and apply prepare operation. */
  if (retVal == VSTREAMPROC_OK)
  {
    /* #30 Iterate over all passed port infos and apply release operation. */
    retVal = vStreamProc_Port_IteratePortInfos(
      vStreamProc_Port_InitPortIteratorParam(ProcNodeInfo, VSTREAMPROC_PORT_OPERATION_RELEASE, FALSE),
      inputPortInfos, inputPortCount, outputPortInfos, outputPortCount);
  }

  return retVal;
}

# define VSTREAMPROC_STOP_SEC_CODE
# include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_Port.c
 *********************************************************************************************************************/
