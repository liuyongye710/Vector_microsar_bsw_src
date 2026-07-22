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
/*!        \file  vStreamProc_Pipe.h
 *        \brief  vStreamProc Pipe Sub Module Header File
 *
 *      \details  Header file of the vStreamProc Pipe sub module.
 *
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
# if !defined (VSTREAMPROC_PIPE_H)
# define VSTREAMPROC_PIPE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc_Cfg.h"
#include "vStreamProc_Types.h"
#include "vStreamProc_CfgTypes.h"

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

#define VSTREAMPROC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ 

/**********************************************************************************************************************
 *  vStreamProc_Pipe_Init()
 *********************************************************************************************************************/
/*!
 * \brief         Initializes a pipe.
 * \details       -
 * \param[in]     PipeId      Id of a pipe
 * \return        E_OK        Initialization was successful
 * \return        E_NOT_OK    Initialization was not successful
 * \pre           Must be called before call of any vStreamProc_Pipe function
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_Init(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_Open()
 *********************************************************************************************************************/
/*!
 * \brief         Opens a pipe based on the passed state.
 * \details       Sets the state to open in the pipe workspace.
 * \param[in]     PipeId        Id of a pipe
 * \return        E_OK          Pipe Opening was successful
 * \return        E_NOT_OK      Pipe Opening was unsuccessful
 * \pre           The pipe is not open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_Open(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_Close()
 *********************************************************************************************************************/
/*!
 * \brief         Closes a pipe.
 * \details       Performs neither any flush operation nor processes the pipe in any means.
 * \param[in]     PipeId        Id of a pipe
 * \return        E_OK          Pipe closing was successful
 * \return        E_NOT_OK      Pipe closing was unsuccessful
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_Close(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_Process()
 *********************************************************************************************************************/
 /*!
 * \brief        Starts the scheduler of the passed pipe.
 * \details      Calls the Scheduler and processes the ProcessingNodes from the corresponding pipe.
 * \param[in]    PipeId     Id of a pipe
 * \return       VSTREAMPROC_OK                 ProcessFctOfNode lead to a idle pipe
 * \return       VSTREAMPROC_PENDING              ProcessFctOfNode was executed but the pipe is pending
 * \return       VSTREAMPROC_FAILED               ProcessFctOfNode of the pipe failed
 * \return       VSTREAMPROC_INSUFFICIENT_INPUT   ProcessFctOfNode of the pipe disturbed due to an entry point containing
 *                                                not enough data
 * \return       VSTREAMPROC_INSUFFICIENT_OUTPUT  ProcessFctOfNode of the pipe disturbed due to an exit point
 *                                                containing not enough free memory space
 * \pre          The pipe is open.
 * \context      TASK|ISR
 * \reentrant    TRUE
 * \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_Process(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_Flush()
 *********************************************************************************************************************/
/*!
 * \brief        Flushes a passed pipe.
 * \details      The flushing of a pipe takes care that the configured nodes are flushed in a sequence that takes 
 *               the structural dependencies of the underlying data processing graph into account.
 * \param[in]    PipeId     Id of a pipe
 * \return       VSTREAMPROC_OK             FlushFctOfNode was successful
 * \return       VSTREAMPROC_PENDING              FlushFctOfNode is not yet finished
 * \return       VSTREAMPROC_FAILED               FlushFctOfNode failed
 * \return       VSTREAMPROC_INSUFFICIENT_INPUT   FlushFctOfNode disturbed due to an entry point containing not enough data
 * \return       VSTREAMPROC_INSUFFICIENT_OUTPUT  FlushFctOfNode disturbed due to an exit point containing not enough free
 *                                                memory space
 * \pre          The pipe is open.
 * \context      TASK|ISR
 * \reentrant    TRUE
 * \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_Flush(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_SetMode()
 *********************************************************************************************************************/
/*!
 * \brief        Sets a new mode for the passed pipe.
 * \details      Sets the activation signals to the configured value.
 * \param[in]    PipeId          Id of a pipe
 * \param[in]    PipeModeId      Id of the mode to activate
 * \return       E_OK            Mode setting was successful
 * \return       E_NOT_OK        Mode setting was unsuccessful
 * \pre          The pipe is open.
 * \context      TASK|ISR
 * \reentrant    TRUE
 * \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_SetMode(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId,
  CONST(vStreamProc_ModeIterType, AUTOMATIC) PipeModeId);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_AnnounceStream()
 *********************************************************************************************************************/
/*!
 * \brief        Announces a stream.
 * \details      The passed callback is triggered when the entry point is requesting data.
 * \param[in]    PipeId           Id of a pipe
 * \param[in]    EntryPointId     Id of a pipe entry point
 * \param[in]    Length           Length of the data to be produced
 * \param[in]    ProduceCbk       Callback function that is called when the entry point requests data
 * \return       E_OK             Stream annunciation was successful
 * \return       E_NOT_OK         Stream annunciation was unsuccessful
 * \pre          The pipe is open.
 * \context      TASK|ISR
 * \reentrant    TRUE
 * \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_AnnounceStream(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId,
  CONST(vStreamProc_EntryPointIterType, AUTOMATIC) EntryPointId,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  VAR(vStreamProc_ProduceCallbackType, AUTOMATIC) ProduceCbk);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_PrepareEntryPointInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize entry point information structure.
 * \details       -
 * \param[in]     PipeId              Id of the desired pipe.
 * \param[out]    EntryPointInfo      Pointer to entry point information structure.
 *                - WriteRequest.StorageInfo.DataTypeInfo.Id    Set to vStreamProcConf_vStreamProcDataType_Undefined.
 *                - WriteRequest.StorageInfo.DataTypeInfo.Size  Set to zero.
 *                - WriteRequest.StorageInfo.AvailableLength    Set to zero.
 *                - WriteRequest.StorageInfo.RequestLength      Set to zero.
 *                - WriteRequest.StorageInfo.ReleaseFlag        Set to TRUE.
 *                - WriteRequest.Buffer                         Set to NULL_PTR.
 * \return        VSTREAMPROC_OK      Operation was successful.
 * \return        VSTREAMPROC_FAILED  Operation was unsuccessful.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_PrepareEntryPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_GetEntryPointInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Get information about a pipe entry point.
 * \details       -
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in,out] EntryPointInfo    Pointer to entry point information structure.
 *                - Input
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the expected data type of the storage node
 *                                                                connected to the access point.
 *                                                                vStreamProcConf_vStreamProcDataType_Undefined if no
 *                                                                specific data type is expected.
 *                  - WriteRequest.StorageInfo.RequestLength      Requested minimum buffer length.
 *                  - EntryPointId                                Id of an entry point of the desired pipe.
 *                - Output
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the actual data type of the storage node
 *                                                                connected to the access point.
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Size  Byte size of data type of the storage node
 *                                                                connected to the access point.
 *                  - WriteRequest.StorageInfo.AvailableLength    Available buffer length.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    Requested minimum buffer length isn't available.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_GetEntryPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_RequestEntryPointData()
 *********************************************************************************************************************/
/*!
 * \brief         Requests a write action.
 * \details       This call does not write any data to a buffer. It rather provides the pointer and length information
 *                to the application. The application can then write its data to the provided pointer while the 
 *                maximum data amount is limited by the provided available length.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in,out] EntryPointInfo    Pointer to entry point information structure.
 *                - Input
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the expected data type of the storage node
 *                                                                connected to the access point.
 *                  - WriteRequest.StorageInfo.RequestLength      Requested minimum buffer length.
 *                  - EntryPointId                                Id of an entry point of the desired pipe.
 *                - Output
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the actual data type of the storage node
 *                                                                connected to the access point.
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Size  Byte size of data type of the storage node
 *                                                                connected to the access point.
 *                  - WriteRequest.StorageInfo.AvailableLength    Available buffer length.
 *                  - WriteRequest.StorageInfo.RequestLength      Requested minimum buffer length.
 *                  - WriteRequest.Buffer                         Pointer to available buffer.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    Requested minimum buffer length isn't available.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_RequestEntryPointData(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_AcknowledgeEntryPoint()
 *********************************************************************************************************************/
/*!
 * \brief         Acknowledges a write action.
 * \details       The application shall have requested a write request which then can be acknowledge by calling 
 *                this function. The write request only provides a maximum amount of data to be produced, but it does
 *                not specify a precise amount of data which shall be produced. Therefore, the amount of produced
 *                data must be provided by calling this function.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in,out] EntryPointInfo    Pointer to entry point information structure.
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the expected data type of the storage node
 *                                                                connected to the access point.
 *                                                                Only required when storage lock is kept.
 *                  - WriteRequest.StorageInfo.RequestLength      The amount of produced data which needs to be acknowledged.
 *                  - WriteRequest.StorageInfo.ReleaseFlag        Flag to control release of storage lock.
 *                    - TRUE: Release storage lock.
 *                    - FALSE: Keep storage locked.
 *                  - EntryPointId                                Id of an entry point of the desired pipe.
 *                - Output
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the actual data type of the storage node
 *                                                                connected to the access point.
 *                                                                Only set when storage lock is kept.
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Size  Byte size of data type of the storage node
 *                                                                connected to the access point.
 *                                                                Only set when storage lock is kept.
 *                  - WriteRequest.StorageInfo.AvailableLength    Updated available buffer length.
 *                                                                Zero if storage lock was released.
 *                  - WriteRequest.StorageInfo.RequestLength      Passed produced length value.
 *                                                                Zero if storage lock was released.
 *                  - WriteRequest.Buffer                         Updated pointer to available buffer.
 *                                                                NULL_PTR if storage lock was released.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_AcknowledgeEntryPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_RequestStream()
 *********************************************************************************************************************/
/*!
 * \brief         Registers a callback to a specific pipe exit point.
 * \details       The node being connected to the exit point stores the passed callback information. 
 * \param[in]     PipeId          Id of a pipe
 * \param[in]     ExitPointId     Id of a pipe exit point
 * \param[in]     Length          Length of the data to be consumed
 * \param[out]    ConsumeCbk      Callback function which should be used to handle stream operations
 * \return        E_OK            Stream request was successful
 * \return        E_NOT_OK        Stream request was unsuccessful
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_RequestStream(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId,
  CONST(vStreamProc_ExitPointIterType, AUTOMATIC) ExitPointId,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  VAR(vStreamProc_ConsumeCallbackType, AUTOMATIC) ConsumeCbk);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_PrepareExitPointInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize exit point information structure.
 * \details       -
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[out]    ExitPointInfo     Pointer to exit point information structure.
 *                - ReadRequest.StorageInfo.DataTypeInfo.Id    Set to vStreamProcConf_vStreamProcDataType_Undefined.
 *                - ReadRequest.StorageInfo.DataTypeInfo.Size  Set to zero.
 *                - ReadRequest.StorageInfo.AvailableLength    Set to zero.
 *                - ReadRequest.StorageInfo.RequestLength      Set to zero.
 *                - ReadRequest.StorageInfo.ReleaseFlag        Set to TRUE.
 *                - ReadRequest.Buffer                         Set to NULL_PTR.
 * \return        VSTREAMPROC_OK      Operation was successful.
 * \return        VSTREAMPROC_FAILED  Operation was unsuccessful.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_PrepareExitPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_GetExitPointInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Get information about a pipe exit point.
 * \details       -
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in,out] ExitPointInfo     Pointer to exit point information structure.
 *                - Input
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the expected data type of the storage node
 *                                                                connected to the access point.
 *                                                                vStreamProcConf_vStreamProcDataType_Undefined if no
 *                                                                specific data type is expected.
 *                  - ReadRequest.StorageInfo.RequestLength       Requested minimum buffer length.
 *                  - ExitPointId                                 Id of an exit point of the desired pipe.
 *                - Output
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the actual data type of the storage node
 *                                                                connected to the access point.
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Size   Byte size of data type of the storage node
 *                                                                connected to the access point.
 *                  - ReadRequest.StorageInfo.AvailableLength     Available buffer length.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-205145
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_GetExitPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_RequestExitPointData()
 *********************************************************************************************************************/
/*!
 * \brief         Requests a read action.
 * \details       This call does not read any data from the buffer. It rather provides pointer and length information. 
 *                The application then has to do the data reading based on this information. If data is available, the 
 *                provided pointer does not change until a read acknowledge is issued. Defragmentation may be blocked 
 *                due to a pending read request. A read request that indicates data must always be acknowledged to release
 *                the defragmentation lock.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in,out] ExitPointInfo     Pointer to exit point information structure.
 *                - Input
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the expected data type of the storage node
 *                                                                connected to the access point.
 *                  - ReadRequest.StorageInfo.RequestLength       Requested minimum buffer length.
 *                  - ExitPointId                                 Id of an exit point of the desired pipe.
 *                - Output
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Size   Byte size of data type of the storage node
 *                                                                connected to the access point.
 *                  - ReadRequest.StorageInfo.AvailableLength     Available buffer length.
 *                  - ReadRequest.Buffer                          Pointer to available buffer.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-205145
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_RequestExitPointData(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_AcknowledgeExitPoint()
 *********************************************************************************************************************/
/*!
 * \brief         Acknowledges a read action.
 * \details       The application shall have issued a read request which then can be acknowledge by calling this 
 *                function. Therefore, the amount of consumed data must be provided. By acknowledging a read request
 *                a possible defragmentation lock is being released.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in,out] ExitPointInfo     Pointer to exit point information structure.
 *                - Input
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the expected data type of the storage node
 *                                                                connected to the access point.
 *                                                                Only required when storage lock is kept.
 *                  - ReadRequest.StorageInfo.RequestLength       The amount of consumed data which needs to be acknowledged.
 *                  - ReadRequest.StorageInfo.ReleaseFlag         Flag to control release of storage lock.
 *                    - TRUE: Release storage lock.
 *                    - FALSE: Keep storage locked.
 *                  - ExitPointId                                 Id of an exit point of the desired pipe.
 *                - Output
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the actual data type of the storage node
 *                                                                connected to the access point.
 *                                                                Only set when storage lock is kept.
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Size   Byte size of data type of the storage node
 *                                                                connected to the access point.
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
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_AcknowledgeExitPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_PrepareAccessPointInfos()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize multiple access point information structures.
 * \details       See #vStreamProc_Pipe_PrepareEntryPointInfo and #vStreamProc_Pipe_PrepareExitPointInfo for details.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[out]    EntryPointInfos   Entry point information structures. NULL_PTR if not used.
 * \param[in]     EntryPointCount   Number of entry point information structures.
 * \param[out]    ExitPointInfos    Exit point information structures. NULL_PTR if not used.
 * \param[in]     ExitPointCount    Number of exit point information structures.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one access point.
 * \return        VSTREAMPROC_OK                    Operation was successful for all access points.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_PrepareAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_PrepareAllAccessPointInfos()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize information structures for all access points of a pipe.
 * \details       See #vStreamProc_Pipe_PrepareEntryPointInfo and #vStreamProc_Pipe_PrepareExitPointInfo for details.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[out]    EntryPointInfos   Entry point information structures. NULL_PTR if not used.
 *                - EntryPointId      Set to value matching the index.
 *                - <Other members>   Initialized to default values. See #vStreamProc_Pipe_PrepareEntryPointInfo.
 * \param[in]     EntryPointCount   Number of entry point information structures.
 * \param[out]    ExitPointInfos    Exit point information structures. NULL_PTR if not used.
 *                - ExitPointId       Set to value matching the index.
 *                - <Other members>   Initialized to default values. See #vStreamProc_Pipe_PrepareExitPointInfo.
 * \param[in]     ExitPointCount    Number of exit point information structures.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one access point.
 * \return        VSTREAMPROC_OK                    Operation was successful for all access points.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_PrepareAllAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_GetAccessPointInfos()
 *********************************************************************************************************************/
/*!
 * \brief         Get information about multiple pipe access points.
 * \details       See #vStreamProc_Pipe_GetEntryPointInfo and #vStreamProc_Pipe_GetExitPointInfo for details.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in,out] EntryPointInfos   Entry point information structures. NULL_PTR if not used.
 * \param[in]     EntryPointCount   Number of entry point information structures.
 * \param[in,out] ExitPointInfos    Exit point information structures. NULL_PTR if not used.
 * \param[in]     ExitPointCount    Number of exit point information structures.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one access point.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   At least one port cannot provide the requested minimum data.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    At least one port cannot provide the requested minimum storage.
 * \return        VSTREAMPROC_OK                    Operation was successful for all access points.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_GetAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_RequestAccessPointData()
 *********************************************************************************************************************/
/*!
 * \brief         Requests multiple read and write actions.
 * \details       See #vStreamProc_Pipe_RequestEntryPointData and #vStreamProc_Pipe_RequestExitPointData for details.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in,out] EntryPointInfos   Entry point information structures. NULL_PTR if not used.
 * \param[in]     EntryPointCount   Number of entry point information structures.
 * \param[in,out] ExitPointInfos    Exit point information structures. NULL_PTR if not used.
 * \param[in]     ExitPointCount    Number of exit point information structures.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one access point.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   At least one port cannot provide the requested minimum data.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    At least one port cannot provide the requested minimum storage.
 * \return        VSTREAMPROC_OK                    Operation was successful for all access points.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_RequestAccessPointData(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_AcknowledgeAccessPoints()
 *********************************************************************************************************************/
/*!
 * \brief         Acknowledges multiple read and write actions.
 * \details       See #vStreamProc_Pipe_AcknowledgeEntryPoint and #vStreamProc_Pipe_AcknowledgeExitPoint for details.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in,out] EntryPointInfos   Entry point information structures. NULL_PTR if not used.
 * \param[in]     EntryPointCount   Number of entry point information structures.
 * \param[in,out] ExitPointInfos   Exit point information structures. NULL_PTR if not used.
 * \param[in]     ExitPointCount    Number of exit point information structures.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one access point.
 * \return        VSTREAMPROC_OK                    Operation was successful for all access points.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_AcknowledgeAccessPoints(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_ExitPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_EntryPointIdType ExitPointCount);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_ReleaseAllAccessPoints()
 *********************************************************************************************************************/
/*!
 * \brief         Releases storage lock of all access points.
 * \details       -
 * \param[in]     PipeId            Id of the desired pipe.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one access point.
 * \return        VSTREAMPROC_OK                    Operation was successful for all access points.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_ReleaseAllAccessPoints(
  vStreamProc_PipeIdType PipeId);

#if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  vStreamProc_Pipe_DetChecksAccessPointInfos()
 *********************************************************************************************************************/
/*!
 * \brief         Performs common DET checks for APIs operating on multiple access point info structures.
 * \details       Return code and ErrorId output parameter contain the same value.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in]     EntryPointInfos   Entry point information structures. NULL_PTR if not used.
 *                - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the expected data type of the storage node
 *                                                              connected to the access point.
 *                                                              vStreamProcConf_vStreamProcDataType_Undefined if no
 *                                                              specific data type is expected.
 *                - EntryPointId                                Id of an entry point of the desired pipe.
 * \param[in]     EntryPointCount   Number of entry point information structures.
 * \param[in]     ExitPointInfos    Exit point information structures. NULL_PTR if not used.
 *                - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the expected data type of the storage node
 *                                                              connected to the access point.
 *                                                              vStreamProcConf_vStreamProcDataType_Undefined if no
 *                                                              specific data type is expected.
 *                - ExitPointId                                 Id of an exit point of the desired pipe.
 * \param[in]     ExitPointCount    Number of exit point information structures.
 * \return        VSTREAMPROC_FAILED                Check failed for at least one access point.
 * \return        VSTREAMPROC_OK                    Check was successful for all access points.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_Pipe_DetChecksAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId);
#endif

#define VSTREAMPROC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSTREAMPROC_PIPE_H */

/**********************************************************************************************************************
*  END OF FILE: vStreamProc_Pipe.h
*********************************************************************************************************************/
