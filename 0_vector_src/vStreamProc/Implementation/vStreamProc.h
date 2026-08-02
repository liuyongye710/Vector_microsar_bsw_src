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
/*!       \file  vStreamProc.h
 *        \brief  vStreamProc Header File
 *
 *      \details  Header file of the vStreamProc module.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2019-08-02  visdyb  STORY-11689   Scheduling of data processing tasks
 *                        visphh  STORY-11688   Buffer handling
 *                        visdyb  STORY-11973   Support of CRC32
 *                        viskjs  STORY-11235   Support signature/MAC verification
 *                        visdyb  STORY-11235   Support signature/MAC verification
 *  01.00.01  2019-08-05  visphh  ESCAN00103925 Flush failed for a pipe with a feedback path (circular)
 *  01.00.02  2019-08-05  visphh  ESCAN00103932 Missing SEC_VAR_NOINIT_UNSPECIFIED definition in MemMap.h
 *  01.00.03  2019-08-06  visphh  ESCAN00103932 Missing SEC_VAR_NOINIT_UNSPECIFIED definition in MemMap.h
 *  01.00.04  2019-08-16  visdyb  ESCAN00103952 Initialization of a pipe initializes the mode incorrect
 *                        visphh  ESCAN00104034 Does not return VSTREAMPROC_INSUFFICIENT_INPUT if StorageNode is not empty
 *  01.00.05  2019-08-23  visdyb                Removed DET check from vStreamProc_Helper_GetOutputOfProcessingNode to enable unused output ports
 *                        visphh  ESCAN00104084 Compiler error: Missing MemMap Macros
 *  01.00.06  2019-08-30  visphh  ESCAN00104127 Missing macro VSTREAMPROC_VAR_NOINIT 
 *                        visphh  ESCAN00104151 MAC/Signature: returns Failed instead of InsufficientInput
 *                        visphh  ESCAN00104161 More data than available can be produced.
 *                        visphh  ESCAN00104162 More data than available can be consumed.
 *                        visdyb  ESCAN00104165 A node with insufficient input data is executed again.
 *                        visdyb  ESCAN00104171 Byte compare node performs the wrong comparison for multi bytes
 *  01.00.07  2019-09-27  visdyb  ESCAN00104210 Failing CSM initialization may not be propagated
 *                        visdyb                Improved performance of byte compare processing node
 *  01.01.00  2019-10-25  visfsn  SWUP-35       Support encryption/decryption
 *                        visrr   ESCAN00104664 Compiler error: Expression must be a modifiable value
 *  01.02.00  2019-11-22  visdyb  ESCAN00104904 Added memory lock for read request
 *                        visjhg  ESCAN00105002 Use byte lengths for all buffer accesses in simple buffer storage node
 *                        visrr   ESCAN00105076 Harmonize error handling between flush and process
 *                        visrr   ESCAN00105077 Removed FINALIZED as return value of cipher node processing function
 *  01.03.00  2020-01-17  visdyb  ESCAN00105170 Added memory lock for write request
 *                        visrr   ESCAN00105079 CSM initialization was moved from init function into process calls
 *                        visrr   ESCAN00105357 Moved includes of CRC and CSM headers to avoid including when disabled
 *                        visrr   ESCAN00105360 Cipher: Use available instead of minimal output
 *  01.04.00  2020-01-14  visrr   SWUP-771      ByteCompare: Remove processing limitation of 256 Byte length
 *                        visrr   ESCAN00105612 Explicit casts from iteration types to ID types
 *  02.00.00  2021-03-12  visjhg  SWUP-824      Reworked mode/meta state handling.
 *                        visjhg  SWUP-883      Type-safe access to storage nodes.
 *                        visjhg  SWUP-923      Type-safe access to processing node workspaces and configurations.
 *                        visjhg  SWUP-1224     Reworked access point/port handling.
 *  02.01.00  2021-04-12  visshk  SWUP-1348     Extend ByteCompareNode to support all basic literal types.
 *  02.01.01  2021-07-09  visshk  SWUP-1581     Provide AvailableLength when ReadRequest reports INSUFFICIENT_INPUT.
 *  02.01.02  2021-09-24  visshk  ESCAN00109837 Unexpected re-processing of node during flush
 *                        visshk  ESCAN00109838 Pipe processing may not finish when output stream is requested
 *                        visshk  ESCAN00109839 Announced input stream may not be collected completely
 *                        visdlm  ESCAN00110064 Corrected symbolic name of InputPort for MAC verification
 *  02.01.03  2021-08-10  visrcn  ESCAN00110332 Data source buffers for memory write operations may not fit the
 *                                              alignment requirement of hardware
 *  02.01.04  2022-01-27  visrcn  ESCAN00111169 NullPointerException during configuration
 *********************************************************************************************************************/
# if !defined (VSTREAMPROC_H)
# define VSTREAMPROC_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc_Types.h"
#include "vStreamProc_Cfg.h"
#include "vStreamProc_Lcfg.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Vendor and module identification */
# define VSTREAMPROC_VENDOR_ID                             (30u)
# define VSTREAMPROC_MODULE_ID                            (255u)
# define VSTREAMPROC_INSTANCE_ID_DET                        (0u)

/* AUTOSAR Software Specification Version Information */
#define VSTREAMPROC_AR_MAJOR_VERSION                      (0x04u)
#define VSTREAMPROC_AR_MINOR_VERSION                      (0x00u)
#define VSTREAMPROC_AR_PATCH_VERSION                      (0x03u)

/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define VSTREAMPROC_SW_MAJOR_VERSION                     (2u)
# define VSTREAMPROC_SW_MINOR_VERSION                     (1u)
# define VSTREAMPROC_SW_PATCH_VERSION                     (4u)

/* ----- API service IDs ----- */
# define VSTREAMPROC_API_ID_INIT_MEMORY                     (0x00u) /*!< Service ID: vStreamProc_InitMemory() */
# define VSTREAMPROC_API_ID_INIT                            (0x01u) /*!< Service ID: vStreamProc_Init() */
# define VSTREAMPROC_API_ID_INIT_PIPE                       (0x02u) /*!< Service ID: vStreamProc_InitPipe() */
# define VSTREAMPROC_API_ID_GET_VERSION_INFO                (0x03u) /*!< Service ID: vStreamProc_GetVersionInfo() */
# define VSTREAMPROC_API_ID_OPEN                            (0x04u) /*!< Service ID: vStreamProc_Open() */
# define VSTREAMPROC_API_ID_CLOSE                           (0x05u) /*!< Service ID: vStreamProc_Close() */
# define VSTREAMPROC_API_ID_PROCESS                         (0x06u) /*!< Service ID: vStreamProc_Process() */
# define VSTREAMPROC_API_ID_FLUSH                           (0x07u) /*!< Service ID: vStreamProc_Flush() */
# define VSTREAMPROC_API_ID_SET_MODE                        (0x08u) /*!< Service ID: vStreamProc_SetMode() */
# define VSTREAMPROC_API_ID_GET_MODE_BY_HANDLE              (0x09u) /*!< Service ID: vStreamProc_GetModeByHandle() */
# define VSTREAMPROC_API_ID_ANNOUNCE_STREAM                 (0x10u) /*!< Service ID: vStreamProc_AnnounceStream() */
# define VSTREAMPROC_API_ID_PREPARE_ENTRY_POINT_INFO        (0x11u) /*!< Service ID: vStreamProc_PrepareEntryPointInfo() */
# define VSTREAMPROC_API_ID_GET_ENTRY_POINT_INFO            (0x12u) /*!< Service ID: vStreamProc_GetEntryPointInfo() */
# define VSTREAMPROC_API_ID_REQUEST_ENTRY_POINT_DATA        (0x13u) /*!< Service ID: vStreamProc_RequestEntryPointData() */
# define VSTREAMPROC_API_ID_GET_WRITE_REQUEST_BUFFER        (0x14u) /*!< Service ID: vStreamProc_GetWriteRequestBuffer() */
# define VSTREAMPROC_API_ID_ACKNOWLEDGE_ENTRY_POINT         (0x15u) /*!< Service ID: vStreamProc_AcknowledgeEntryPoint() */
# define VSTREAMPROC_API_ID_REQUEST_STREAM                  (0x20u) /*!< Service ID: vStreamProc_RequestStream() */
# define VSTREAMPROC_API_ID_PREPARE_EXIT_POINT_INFO         (0x21u) /*!< Service ID: vStreamProc_PrepareExitPointInfo() */
# define VSTREAMPROC_API_ID_GET_EXIT_POINT_INFO             (0x22u) /*!< Service ID: vStreamProc_GetExitPointInfo() */
# define VSTREAMPROC_API_ID_REQUEST_EXIT_POINT_DATA         (0x23u) /*!< Service ID: vStreamProc_RequestExitPointData() */
# define VSTREAMPROC_API_ID_GET_READ_REQUEST_BUFFER         (0x24u) /*!< Service ID: vStreamProc_GetReadRequestBuffer() */
# define VSTREAMPROC_API_ID_ACKNOWLEDGE_EXIT_POINT          (0x25u) /*!< Service ID: vStreamProc_AcknowledgeExitPoint() */
# define VSTREAMPROC_API_ID_PREPARE_ACCESS_POINT_INFOS      (0x30u) /*!< Service ID: vStreamProc_PrepareAccessPointInfos() */
# define VSTREAMPROC_API_ID_PREPARE_ALL_ACCESS_POINT_INFOS  (0x31u) /*!< Service ID: vStreamProc_PrepareAllAccessPointInfos() */
# define VSTREAMPROC_API_ID_GET_ACCESS_POINT_INFOS          (0x32u) /*!< Service ID: vStreamProc_GetAccessPointInfos() */
# define VSTREAMPROC_API_ID_REQUEST_ACCESS_POINT_DATA       (0x33u) /*!< Service ID: vStreamProc_RequestAccessPointData() */
# define VSTREAMPROC_API_ID_ACKNOWLEDGE_ACCESS_POINTS       (0x34u) /*!< Service ID: vStreamProc_AcknowledgeAccessPoints() */
# define VSTREAMPROC_API_ID_RELEASE_ALL_ACCESS_POINTS       (0x35u) /*!< Service ID: vStreamProc_ReleaseAllAccessPoints() */

/* ----- API service IDs of processing node functions ----- */
# define VSTREAMPROC_API_ID_GET_TYPED_WORKSPACE_OF_PROCESSING_NODE  (0x40u) /*!< Service ID: vStreamProc_GetTypedWorkspaceOfProcessingNode() */
# define VSTREAMPROC_API_ID_GET_TYPED_CONFIG_OF_PROCESSING_NODE     (0x41u) /*!< Service ID: vStreamProc_GetTypedConfigOfProcessingNode() */

/* ----- API service IDs of storage node functions ----- */
# define VSTREAMPROC_API_ID_WRITE_INFO                      (0x50u) /*!< Service ID: vStreamProc_<storage node>_WriteInfo() */
# define VSTREAMPROC_API_ID_WRITE_REQUEST                   (0x51u) /*!< Service ID: vStreamProc_<storage node>_WriteRequest() */
# define VSTREAMPROC_API_ID_WRITE_ACK                       (0x52u) /*!< Service ID: vStreamProc_<storage node>_WriteAck() */
# define VSTREAMPROC_API_ID_READ_REQUEST                    (0x53u) /*!< Service ID: vStreamProc_<storage node>_ReadInfo() */
# define VSTREAMPROC_API_ID_READ_INFO                       (0x54u) /*!< Service ID: vStreamProc_<storage node>_ReadRequest() */
# define VSTREAMPROC_API_ID_READ_ACK                        (0x55u) /*!< Service ID: vStreamProc_<storage node>_ReadAck() */

/* ----- Error codes ----- */
# define VSTREAMPROC_E_NO_ERROR                           (0x00u) /*!< Used to check if no error occurred - use a value unequal to any error code. */
# define VSTREAMPROC_E_PARAM_POINTER                      (0x01u) /*!< Error code: API service used with invalid pointer parameter (NULL). */
# define VSTREAMPROC_E_PARAM_POINTER_SIZE                 (0x02u) /*!< Error code: API service used with invalid pointer length (0). */
# define VSTREAMPROC_E_PARAM_SIZE                         (0x03u) /*!< Error code: API service used with invalid length (0). */
# define VSTREAMPROC_E_ID_PARAM                           (0x04u) /*!< Error code: API service used with invalid id param. */
# define VSTREAMPROC_E_PIPE_STATE                         (0x05u) /*!< Error code: API service used while pipe is in unexpected state. */
# define VSTREAMPROC_E_INVALID_META_STATE_SWITCHING       (0x06u) /*!< Error code: Meta state switched while data is pending. */
# define VSTREAMPROC_E_NO_NAMED_INPUT_PORT                (0x07u) /*!< Error code: API helper function used to resolve named input ports failed. */
# define VSTREAMPROC_E_NO_NAMED_OUTPUT_PORT               (0x08u) /*!< Error code: API helper function used to resolve named output ports failed. */
# define VSTREAMPROC_E_UNINIT                             (0x09u) /*!< Error code: API service used without module initialization. */
# define VSTREAMPROC_E_ALREADY_INITIALIZED                (0x0Au) /*!< Error code: The service vStreamProc_Init() is called while the module is already initialized. */

/* ----- Modes ----- */
# define VSTREAMPROC_UNINIT                               (0x00u) /*!< Module not initialized yet. */
# define VSTREAMPROC_INIT                                 (0x01u) /*!< Module is initialized. */

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
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vStreamProc_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Initialization for *_INIT_*-variables
 *  \details     Service to initialize module global variables at power up. This function initializes the
 *               variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \pre         Module is uninitialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       CREQ-278315
 *********************************************************************************************************************/
FUNC(void, VSTREAMPROC_CODE) vStreamProc_InitMemory(void);

/**********************************************************************************************************************
 * vStreamProc_Init()
 *********************************************************************************************************************/
/*! \brief       Initialization function
 *  \details     Service to initialize the module vStreamProc. It initializes all variables and sets the module state
 *               to initialized.
 *  \param[in]   ConfigPtr               Configuration structure for initializing the module
 *  \pre         Interrupts are disabled.
 *  \pre         Module is uninitialized.
 *  \pre         vStreamProc_InitMemory has been called unless vStreamProc_ModuleInitialized is initialized by
 *               start-up code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       CREQ-278315
 *********************************************************************************************************************/
FUNC(void, VSTREAMPROC_CODE) vStreamProc_Init(
  P2CONST(vStreamProc_ConfigType, AUTOMATIC, VSTREAMPROC_PBCFG) ConfigPtr);

/**********************************************************************************************************************
 *  vStreamProc_InitPipe()
 *********************************************************************************************************************/
/*! \brief       Initializes the vStreamProc pipe.
 *  \details     -
 *  \param[in]   PipeId    Id of the pipe to initialize
 *  \return      E_OK      Initialization was successful
 *  \return      E_NOT_OK  Initialization was unsuccessful
 *  \pre         Must be called before calling any other vStreamProc function.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-205141
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_InitPipe(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId);

#if (VSTREAMPROC_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vStreamProc_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information.
 *  \details     Returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  VersionInfoPtr       Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE 
 *  \trace       CREQ-205142
 *  \config      VSTREAMPROC_VERSION_INFO_API
 *********************************************************************************************************************/
FUNC(void, VSTREAMPROC_CODE) vStreamProc_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, VSTREAMPROC_APPL_VAR) VersionInfoPtr);
#endif /* (VSTREAMPROC_VERSION_INFO_API == STD_ON) */

/**********************************************************************************************************************
 *  vStreamProc_Open()
 *********************************************************************************************************************/
/*!
 * \brief         Opens a pipe and allows the usage of the pipe.
 * \details       -
 * \param[in]     PipeId     Id of the desired pipe
 * \return        E_OK       Open was successful
 * \return        E_NOT_OK   Open was unsuccessful
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-211332
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Open(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId);

/**********************************************************************************************************************
 *  vStreamProc_Close()
 *********************************************************************************************************************/
/*!
 * \brief         Closes a pipe.
 * \details       Performs neither any flush operation nor processes the pipe in any means.
 * \param[in]     PipeId     Id of the desired pipe
 * \return        E_OK       Close was successful
 * \return        E_NOT_OK   Close was unsuccessful
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-211331
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Close(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId);

/**********************************************************************************************************************
 *  vStreamProc_Process()
 *********************************************************************************************************************/
/*!
 * \brief         Processes the passed pipe.
 * \details       Calls the Scheduler and processes the ProcessingNodes from the corresponding pipe.
 * \param[in]     PipeId      Id of the desired pipe
 * \return        VSTREAMPROC_OK                    Processing lead to an idle pipe.
 * \return        VSTREAMPROC_PENDING               Processing of the pipe is still pending.
 * \return        VSTREAMPROC_FAILED                Processing of the pipe failed.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    Processing of the pipe disturbed due to an entry point not providing
  *                                                 enough data.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   Processing of the pipe disturbed due to an exit point not providing
 *                                                  enough free memory space.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-205151
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Process(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId);

/**********************************************************************************************************************
 *  vStreamProc_Flush()
 *********************************************************************************************************************/
/*!
 * \brief        Flushes the passed pipe.
 * \details      The flushing of a pipe takes care that the configured nodes are flushed in a sequence that takes 
 *               the structural dependencies of the underlying data processing graph into account.
 * \param[in]    PipeId      Id of the desired pipe
 * \return       VSTREAMPROC_OK                   Flushing of the pipe successfully finished.
 * \return       VSTREAMPROC_PENDING              Flushing of the pipe is not yet finished.
 * \return       VSTREAMPROC_FAILED               Flushing of the pipe failed.
 * \return       VSTREAMPROC_INSUFFICIENT_INPUT   Flushing of the pipe disturbed due to an entry point not providing
 *                                                enough data.
 * \return       VSTREAMPROC_INSUFFICIENT_OUTPUT  Flushing of the pipe disturbed due to an exit point not providing
 *                                                enough free memory space.
 * \pre          The pipe is open.
 * \context      TASK|ISR
 * \reentrant    TRUE
 * \synchronous  TRUE
 * \trace        CREQ-205147
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Flush(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId);

/**********************************************************************************************************************
 *  vStreamProc_SetMode()
 *********************************************************************************************************************/
/*!
 * \brief         Sets the mode of the passed pipe.
 * \details       The pipe is going to set the activation signals depending on the configured mode.
 * \param[in]     PipeId           Id of the desired pipe
 * \param[in]     PipeModeId       Id of a valid mode of the passed pipe
 * \return        E_OK             Setting of the mode was successful
 * \return        E_NOT_OK         Setting of the mode was unsuccessful
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-211269
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_SetMode(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId,
  CONST(vStreamProc_ModeIdType, AUTOMATIC) PipeModeId);

/**********************************************************************************************************************
 *  vStreamProc_GetModeByHandle()
 *********************************************************************************************************************/
/*!
 * \brief         Fetches a mode based on the passed handle id.
 * \details       -
 * \param[in]     PipeId           Id of the desired pipe
 * \param[in]     HandleId         Handle id of a valid meta state of the passed pipe
 * \return        <ModeId>         The mode that is associated with the passed handle id.
 * \return        VSTREAMPROC_NO_MODE   If no mode was found that is identified by the passed handle id.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-211270
 *********************************************************************************************************************/
FUNC(vStreamProc_ModeIdType, VSTREAMPROC_CODE) vStreamProc_GetModeByHandle(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId,
  CONST(vStreamProc_ModeHandleIdType, AUTOMATIC) HandleId);

/**********************************************************************************************************************
 *  vStreamProc_AnnounceStream()
 *********************************************************************************************************************/
/*!
 * \brief         Registers/announces a callback for a passed pipe entry point.
 * \details       The callback is triggered when the entry point is requesting application data. The application must 
 *                then provide the data. If the requested Length amount of data was produced by the application, the 
 *                callback is not being called again. The application must then re-register its callback.
 * \param[in]     PipeId           Id of the desired pipe
 * \param[in]     EntryPointId     Id of an entry point of the desired pipe
 * \param[in]     Length           Length of the data to be produced
 * \param[in]     ProduceCbk       Callback function that is called when the entry point requests data
 * \return        E_OK             Callback registration was successful
 * \return        E_NOT_OK         Callback registration was unsuccessful
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-205146
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_AnnounceStream(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId,
  CONST(vStreamProc_EntryPointIdType, AUTOMATIC) EntryPointId,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  VAR(vStreamProc_ProduceCallbackType, AUTOMATIC) ProduceCbk);

/**********************************************************************************************************************
 *  vStreamProc_PrepareEntryPointInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize entry point information structure.
 * \details       -
 * \param[in]     PipeId              Id of the desired pipe.
 * \param[in]     EntryPointId        Id of an entry point of the desired pipe.
 * \param[out]    EntryPointInfo      Pointer to entry point information structure.
 *                - WriteRequest.StorageInfo.DataTypeInfo.Id    Set to vStreamProcConf_vStreamProcDataType_Undefined.
 *                - WriteRequest.StorageInfo.DataTypeInfo.Size  Set to zero.
 *                - WriteRequest.StorageInfo.AvailableLength    Set to zero.
 *                - WriteRequest.StorageInfo.RequestLength      Set to zero.
 *                - WriteRequest.StorageInfo.ReleaseFlag        Set to TRUE.
 *                - WriteRequest.Buffer                         Set to NULL_PTR.
 *                - EntryPointId                                Set to passed entry point ID value.
 * \return        VSTREAMPROC_OK      Operation was successful.
 * \return        VSTREAMPROC_FAILED  Operation was unsuccessful.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-278316
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareEntryPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointIdType EntryPointId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_GetEntryPointInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Get information about a pipe entry point.
 * \details       -
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in]     DataTypeId        Id of the expected data type of the storage node connected to the access point.
 *                                  vStreamProcConf_vStreamProcDataType_Undefined if no specific data type is expected.
 * \param[in,out] EntryPointInfo    Pointer to entry point information structure.
 *                - Input
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
 * \trace         CREQ-278316
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_GetEntryPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_RequestEntryPointData()
 *********************************************************************************************************************/
/*!
 * \brief         Requests a write action.
 * \details       This call does not write any data to a buffer. It rather provides the pointer and length information
 *                to the application. The application can then write its data to the provided pointer while the 
 *                maximum data amount is limited by the provided available length.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in]     DataTypeId        Id of the expected data type of the storage node connected to the access point.
 * \param[in]     RequestLength     Requested minimum buffer length.
 * \param[in,out] EntryPointInfo    Pointer to entry point information structure.
 *                - Input
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
 * \trace         CREQ-205145
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestEntryPointData(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_LengthType RequestLength,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_GetWriteRequestBuffer()
 *********************************************************************************************************************/
/*!
 * \brief         Get the pointer to the buffer of a write request.
 * \details       Returns the buffer pointer stored in a write request, while performing a DET check against the
 *                expected data type.
 * \param[in]     RequestBufferPtr  Pointer to a request structure. Parameter must not be NULL
 * \param[in]     DataTypeId        Id of the expected data type.
 * \return        Pointer to buffer DET check enabled and data type matches or DET checks disabled.
 * \return        NULL_PTR          DET check enabled and data type doesn't match.
 * \pre           Passed write request struct filled by vStreamProc_RequestEntryPointData or
 *                vStreamProc_RequestAccessPointData.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-252056
 *********************************************************************************************************************/
FUNC(P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR), VSTREAMPROC_CODE) vStreamProc_GetWriteRequestBuffer(
  P2CONST(vStreamProc_WriteRequestType, AUTOMATIC, VSTREAMPROC_APPL_CONST) RequestBufferPtr,
  vStreamProc_DataTypeIdType DataTypeId);

/**********************************************************************************************************************
 *  vStreamProc_AcknowledgeEntryPoint()
 *********************************************************************************************************************/
/*!
 * \brief         Acknowledges a write action.
 * \details       The application shall have requested a write request which then can be acknowledge by calling 
 *                this function. The write request only provides a maximum amount of data to be produced, but it does
 *                not specify a precise amount of data which shall be produced. Therefore, the amount of produced
 *                data must be provided by calling this function.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in]     ProducedLength    The amount of produced data which needs to be acknowledged.
 * \param[in]     ReleaseFlag       Flag to control release of storage lock.
 *                - TRUE: Release storage lock.
 *                - FALSE: Keep storage locked.
 * \param[in,out] EntryPointInfo    Pointer to entry point information structure.
 *                - Input
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the expected data type of the storage node
 *                                                                connected to the access point.
 *                                                                Only required when storage lock is kept.
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
 *                  - WriteRequest.StorageInfo.ReleaseFlag        Passed release flag value.
 *                  - WriteRequest.Buffer                         Updated pointer to available buffer.
 *                                                                NULL_PTR if storage lock was released.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-205145
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_AcknowledgeEntryPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_LengthType ProducedLength,
  boolean ReleaseFlag,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_RequestStream()
 *********************************************************************************************************************/
/*!
 * \brief         Registers a callback to receive data from a specific pipe exit point.
 * \details       This callback is triggered when unconsumed data is available at the passed exit point.
 * \param[in]     PipeId           Id of the desired pipe
 * \param[in]     ExitPointId      Id of a pipe exit point
 * \param[in]     Length           Maximum length of data to be consumed
 * \param[in]     ConsumeCbk       Callback function which is triggered when unconsumed data is available 
 *                                 at the exit point
 * \return        E_OK             Registration of callback was successful
 * \return        E_NOT_OK         Registration of callback was unsuccessful
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-205146
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestStream(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId,
  CONST(vStreamProc_ExitPointIdType, AUTOMATIC) ExitPointId,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  VAR(vStreamProc_ConsumeCallbackType, AUTOMATIC) ConsumeCbk);

/**********************************************************************************************************************
 *  vStreamProc_PrepareExitPointInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize exit point information structure.
 * \details       -
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in]     ExitPointId       Id of an exit point of the desired pipe.
 * \param[out]    ExitPointInfo     Pointer to exit point information structure.
 *                - ReadRequest.StorageInfo.DataTypeInfo.Id    Set to vStreamProcConf_vStreamProcDataType_Undefined.
 *                - ReadRequest.StorageInfo.DataTypeInfo.Size  Set to zero.
 *                - ReadRequest.StorageInfo.AvailableLength    Set to zero.
 *                - ReadRequest.StorageInfo.RequestLength      Set to zero.
 *                - ReadRequest.StorageInfo.ReleaseFlag        Set to TRUE.
 *                - ReadRequest.Buffer                         Set to NULL_PTR.
 *                - ExitPointId                                Set to passed exit point ID value.
 * \return        VSTREAMPROC_OK      Operation was successful.
 * \return        VSTREAMPROC_FAILED  Operation was unsuccessful.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-278316
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareExitPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointIdType ExitPointId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_GetExitPointInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Get information about a pipe exit point.
 * \details       -
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in]     DataTypeId        Id of the expected data type of the storage node connected to the access point.
 *                                  vStreamProcConf_vStreamProcDataType_Undefined if no specific data type is expected.
 * \param[in,out] ExitPointInfo     Pointer to exit point information structure.
 *                - Input
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
 * \trace         CREQ-278316
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_GetExitPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_RequestExitPointData()
 *********************************************************************************************************************/
/*!
 * \brief         Requests a read action.
 * \details       This call does not read any data from the buffer. It rather provides pointer and length information. 
 *                The application then has to do the data reading based on this information. If data is available, the 
 *                provided pointer does not change until a read acknowledge is issued. Defragmentation may be blocked 
 *                due to a pending read request. A read request that indicates data must always be acknowledged to release
 *                the defragmentation lock.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in]     DataTypeId        Id of the expected data type of the storage node connected to the access point.
 * \param[in]     RequestLength     Requested minimum buffer length.
 * \param[in,out] ExitPointInfo     Pointer to exit point information structure.
 *                - Input
 *                  - ExitPointId                                 Id of an exit point of the desired pipe.
 *                - Output
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the actual data type of the storage node
 *                                                                connected to the access point.
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Size   Byte size of data type of the storage node
 *                                                                connected to the access point.
 *                  - ReadRequest.StorageInfo.AvailableLength     Available buffer length.
 *                  - WriteRequest.StorageInfo.RequestLength      Requested minimum buffer length.
 *                  - ReadRequest.Buffer                          Pointer to available buffer.
 * \return        E_OK              Read request was successful
 * \return        E_NOT_OK          Read request was unsuccessful
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-205145
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestExitPointData(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_LengthType RequestLength,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_GetReadRequestBuffer()
 *********************************************************************************************************************/
/*!
 * \brief         Get the pointer to the buffer of a read request.
 * \details       Returns the buffer pointer stored in a read request, while performing a DET check against the
 *                expected data type.
 * \param[in]     RequestBufferPtr  Pointer to a request structure. Parameter must not be NULL
 * \param[in]     DataTypeId        Id of the expected data type.
 * \return        Pointer to buffer DET check enabled and data type matches or DET checks disabled.
 * \return        NULL_PTR          DET check enabled and data type doesn't match.
 * \pre           Passed read request struct filled by vStreamProc_ReadRequest.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-252056
 *********************************************************************************************************************/
FUNC(P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR), VSTREAMPROC_CODE) vStreamProc_GetReadRequestBuffer(
  P2CONST(vStreamProc_ReadRequestType, AUTOMATIC, VSTREAMPROC_APPL_VAR) RequestBufferPtr,
  vStreamProc_DataTypeIdType DataTypeId);

/**********************************************************************************************************************
 *  vStreamProc_AcknowledgeExitPoint()
 *********************************************************************************************************************/
/*!
 * \brief         Acknowledges a read action.
 * \details       The application shall have issued a read request which then can be acknowledge by calling this 
 *                function. Therefore, the amount of consumed data must be provided. By acknowledging a read request
 *                a possible defragmentation lock is being released.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in]     ConsumedLength    The amount of consumed data which needs to be acknowledged.
 * \param[in]     ReleaseFlag       Flag to control release of storage lock.
 *                - TRUE: Release storage lock.
 *                - FALSE: Keep storage locked.
 * \param[in,out] ExitPointInfo     Pointer to exit point information structure.
 *                - Input
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the expected data type of the storage node
 *                                                                connected to the access point.
 *                                                                Only required when storage lock is kept.
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
 *                  - ReadRequest.StorageInfo.ReleaseFlag         Passed release flag value.
 *                  - ReadRequest.Buffer                          Updated pointer to available buffer.
 *                                                                NULL_PTR if storage lock was released.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-205145
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_AcknowledgeExitPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_LengthType ConsumedLength,
  boolean ReleaseFlag,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_PrepareAccessPointInfos()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize multiple access point information structures.
 * \details       See #vStreamProc_PrepareEntryPointInfo and #vStreamProc_PrepareExitPointInfo for details.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[out]    EntryPointInfos   Entry point information structures. NULL_PTR if not used.
 * \param[in]     EntryPointCount   Number of entry point information structures.
 * \param[out]    ExitPointInfos    Exit point information structures. NULL_PTR if not used.
 * \param[in]     ExitPointCount    Number of exit point information structures.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one port.
 * \return        VSTREAMPROC_OK                    Operation was successful for all ports.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-278316
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount);

/**********************************************************************************************************************
 *  vStreamProc_PrepareAllAccessPointInfos()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize information structures for all access points of a pipe.
 * \details       See #vStreamProc_PrepareEntryPointInfo and #vStreamProc_PrepareExitPointInfo for details.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[out]    EntryPointInfos   Entry point information structures. NULL_PTR if not used.
 *                - EntryPointId      Set to value matching the index.
 *                - <Other members>   Initialized to default values. See #vStreamProc_PrepareEntryPointInfo.
 * \param[in]     EntryPointCount   Number of entry point information structures.
 * \param[out]    ExitPointInfos    Exit point information structures. NULL_PTR if not used.
 *                - ExitPointId       Set to value matching the index.
 *                - <Other members>   Initialized to default values. See #vStreamProc_PrepareExitPointInfo.
 * \param[in]     ExitPointCount    Number of exit point information structures.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one port.
 * \return        VSTREAMPROC_OK                    Operation was successful for all ports.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-278316
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareAllAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount);

/**********************************************************************************************************************
 *  vStreamProc_GetAccessPointInfos()
 *********************************************************************************************************************/
/*!
 * \brief         Get information about multiple pipe access points.
 * \details       See #vStreamProc_GetEntryPointInfo and #vStreamProc_GetExitPointInfo for details.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in,out] EntryPointInfos   Entry point information structures. NULL_PTR if not used.
 * \param[in]     EntryPointCount   Number of entry point information structures.
 * \param[in,out] ExitPointInfos    Exit point information structures. NULL_PTR if not used.
 * \param[in]     ExitPointCount    Number of exit point information structures.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one port.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   At least one port cannot provide the requested minimum data.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    At least one port cannot provide the requested minimum storage.
 * \return        VSTREAMPROC_OK                    Operation was successful for all ports.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-278316
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_GetAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount);

/**********************************************************************************************************************
 *  vStreamProc_RequestAccessPointData()
 *********************************************************************************************************************/
/*!
 * \brief         Requests multiple read and write actions.
 * \details       See #vStreamProc_RequestEntryPointData and #vStreamProc_RequestExitPointData for details.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in,out] EntryPointInfos   Entry point information structures. NULL_PTR if not used.
 * \param[in]     EntryPointCount   Number of entry point information structures.
 * \param[in,out] ExitPointInfos   Exit point information structures. NULL_PTR if not used.
 * \param[in]     ExitPointCount    Number of exit point information structures.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one port.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   At least one port cannot provide the requested minimum data.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    At least one port cannot provide the requested minimum storage.
 * \return        VSTREAMPROC_OK                    Operation was successful for all ports.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-205145
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestAccessPointData(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount);

/**********************************************************************************************************************
 *  vStreamProc_AcknowledgeAccessPoints()
 *********************************************************************************************************************/
/*!
 * \brief         Acknowledges multiple read and write actions.
 * \details       See #vStreamProc_AcknowledgeEntryPoint and #vStreamProc_AcknowledgeExitPoint for details.
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in,out] EntryPointInfos   Entry point information structures. NULL_PTR if not used.
 * \param[in]     EntryPointCount   Number of entry point information structures.
 * \param[in,out] ExitPointInfos   Exit point information structures. NULL_PTR if not used.
 * \param[in]     ExitPointCount    Number of exit point information structures.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one port.
 * \return        VSTREAMPROC_OK                    Operation was successful for all ports.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-205145
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_AcknowledgeAccessPoints(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_ExitPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_EntryPointIdType ExitPointCount);

/**********************************************************************************************************************
 *  vStreamProc_ReleaseAllAccessPoints()
 *********************************************************************************************************************/
/*!
 * \brief         Releases storage lock of all access points.
 * \details       -
 * \param[in]     PipeId            Id of the desired pipe.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one port.
 * \return        VSTREAMPROC_OK                    Operation was successful for all ports.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 * \trace         CREQ-205145
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ReleaseAllAccessPoints(
  vStreamProc_PipeIdType PipeId);

#define VSTREAMPROC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSTREAMPROC_H */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc.h
 *********************************************************************************************************************/
