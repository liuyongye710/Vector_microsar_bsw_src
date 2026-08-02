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
/*        \file  vFotaH_vSwUpdM.h
 *        \brief  vFotaH vSwUpdM header file
 *
 *      \details  -
 *
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to vFotaH.h.
 **********************************************************************************************************************/

#if !defined(VFOTAH_VSWUPDM_H)
#define VFOTAH_VSWUPDM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vFotaH.h"
#include "vSwUpdM.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define VFOTAH_PARTITION_INDEX_ACTIVE (0x00u) /*!< Partition: The 1st partition has index 0. */
#define VFOTAH_PARTITION_INDEX_INACTIVE (0x01u) /*!< Partition: The 2nd partition has index 1. */
#define VFOTAH_PARTITION_INDEX_BACKUP (0x02u) /*!< Partition: The 3rd partition has index 2. */

/* State Machine Identifier */
#define VFOTAH_ERASE_STATE_ID                       (0x00u)
#define VFOTAH_ERASE_STATE_IDLE                     (0x00u)
#define VFOTAH_ERASE_OPENPARTITION_OPENED           (0x01u)
#define VFOTAH_ERASE_MODULE_ERASED                  (0x02u)
#define VFOTAH_ERASE_MODULE_OPENED                  (0x03u)
#define VFOTAH_ERASE_SEGMENT_ERASED                 (0x04u)
#define VFOTAH_ERASE_MODULE_CLOSED                  (0x05u)
#define VFOTAH_ERASE_ERROR_DETECTED                 (0x06u)
#define VFOTAH_ERASE_ERROR_RESOLVED                 (0x07u)

#define VFOTAH_SYNCM_STATE_ID                       (0x01u)
#define VFOTAH_SYNCM_STATE_IDLE                     (0x00u)
#define VFOTAH_SYNCM_OPENPARTITION_OPENED           (0x01u)
#define VFOTAH_SYNCM_MODULE_SYNCED                  (0x02u)
#define VFOTAH_SYNCM_ERROR_DETECTED                 (0x03u)
#define VFOTAH_SYNCM_ERROR_RESOLVED                 (0x04u)

#define VFOTAH_SYNCP_STATE_ID                       (0x02u)
#define VFOTAH_SYNCP_STATE_IDLE                     (0x00u)
#define VFOTAH_SYNCP_OPENPARTITION_OPENED           (0x01u)
#define VFOTAH_SYNCP_PARTITION_SYNCED               (0x02u)
#define VFOTAH_SYNCP_PARTITION_VALIDATED            (0x03u)
#define VFOTAH_SYNCP_ERROR_DETECTED                 (0x04u)
#define VFOTAH_SYNCP_ERROR_RESOLVED                 (0x05u)

#define VFOTAH_VALIDATEP_STATE_ID                   (0x03u)
#define VFOTAH_VALIDATEP_STATE_IDLE                 (0x00u)
#define VFOTAH_VALIDATEP_OPENPARTITION_OPENED       (0x01u)
#define VFOTAH_VALIDATEP_PARTITION_VALIDATED        (0x02u)
#define VFOTAH_VALIDATEP_ERROR_DETECTED             (0x03u)

#define VFOTAH_VALIDATEM_STATE_ID                   (0x04u)
#define VFOTAH_VALIDATEM_STATE_IDLE                 (0x00u)
#define VFOTAH_VALIDATEM_OPENPARTITION_OPENED       (0x01u)
#define VFOTAH_VALIDATEM_MODULE_VALIDATED           (0x02u)
#define VFOTAH_VALIDATEM_ERROR_DETECTED             (0x03u)
#define VFOTAH_VALIDATEM_ERROR_RESOLVED             (0x04u)

#define VFOTAH_PREPAREDOWNLOAD_STATE_ID                   (0x05u)
#define VFOTAH_PREPAREDOWNLOAD_STATE_IDLE                 (0x00u)
#define VFOTAH_PREPAREDOWNLOAD_MODULE_CLOSED              (0x01u)
#define VFOTAH_PREPAREDOWNLOAD_OPENPARTITION_OPENED       (0x02u)
#define VFOTAH_PREPAREDOWNLOAD_MODULE_OPENED              (0x03u)
#define VFOTAH_PREPAREDOWNLOAD_SEGMENT_OPENED             (0x04u)
#define VFOTAH_PREPAREDOWNLOAD_STREAM_STARTED             (0x05u)
#define VFOTAH_PREPAREDOWNLOAD_ERROR_DETECTED             (0x06u)
#define VFOTAH_PREPAREDOWNLOAD_ERROR_RESOLVED             (0x07u)

#define VFOTAH_TRANSFERDATA_STATE_ID                      (0x06u)
#define VFOTAH_TRANSFERDATA_STATE_IDLE                    (0x00u)
#define VFOTAH_TRANSFERDATA_WRITE_PENDING                 (0x01u)
#define VFOTAH_TRANSFERDATA_ERROR_DETECTED                (0x02u)
#define VFOTAH_TRANSFERDATA_ERROR_RESOLVED                (0x03u)

#define VFOTAH_FINALIZEDOWNLOAD_STATE_ID                  (0x07u)
#define VFOTAH_FINALIZEDOWNLOAD_STATE_IDLE                (0x00u)
#define VFOTAH_FINALIZEDOWNLOAD_STREAM_END                (0x01u)
#define VFOTAH_FINALIZEDOWNLOAD_SEGMENT_FINALIZED         (0x02u)
#define VFOTAH_FINALIZEDOWNLOAD_SEGMENT_CLOSED            (0x03u)
#define VFOTAH_FINALIZEDOWNLOAD_MODULE_CLOSED             (0x04u)
#define VFOTAH_FINALIZEDOWNLOAD_ERROR_DETECTED            (0x05u)
#define VFOTAH_FINALIZEDOWNLOAD_ERROR_RESOLVED            (0x06u)

#define VFOTAH_FINALIZESEGMENT_STATE_ID                   (0x08u)
#define VFOTAH_FINALIZESEGMENT_STATE_IDLE                 (0x00u)
#define VFOTAH_FINALIZESEGMENT_OPENPARTITION_OPENED       (0x01u)
#define VFOTAH_FINALIZESEGMENT_OPENMODULE_OPENED          (0x02u)
#define VFOTAH_FINALIZESEGMENT_SEGMENT_FINALIZED          (0x03u)
#define VFOTAH_FINALIZESEGMENT_SEGMENT_CLOSED             (0x04u)
#define VFOTAH_FINALIZESEGMENT_MODULE_CLOSED              (0x05u)
#define VFOTAH_FINALIZESEGMENT_ERROR_DETECTED             (0x06u)
#define VFOTAH_FINALIZESEGMENT_ERROR_RESOLVED             (0x07u)

#define VFOTAH_READRANGE_STATE_ID                       (0x09u)
#define VFOTAH_READRANGE_STATE_IDLE                     (0x00u)
#define VFOTAH_READRANGE_OPENPARTITION_OPENED           (0x01u)
#define VFOTAH_READRANGE_DATA_READ                      (0x02u)
#define VFOTAH_READRANGE_ERROR_DETECTED                 (0x03u)

#define VFOTAH_VERIFYMODULE_STATE_ID                    (0x0Au)
#define VFOTAH_VERIFYMODULE_STATE_IDLE                  (0x00u)
#define VFOTAH_VERIFYMODULE_OPENPARTITION_OPENED        (0x01u)
#define VFOTAH_VERIFYMODULE_MODULE_CLOSED               (0x02u)
#define VFOTAH_VERIFYMODULE_MODULE_OPENED               (0x03u)
#define VFOTAH_VERIFYMODULE_MODULE_FINALIZED            (0x04u)
#define VFOTAH_VERIFYMODULE_VERIFIED                    (0x05u)
#define VFOTAH_VERIFYMODULE_VALIDATED                   (0x06u)
#define VFOTAH_VERIFYMODULE_ERROR_DETECTED              (0x07u)
#define VFOTAH_VERIFYMODULE_ERROR_RESOLVED              (0x08u)

#define VFOTAH_SWITCHBANK_STATE_ID                      (0x0Bu)
#define VFOTAH_SWITCHBANK_STATE_IDLE                    (0x00u)
#define VFOTAH_SWITCHBANK_OPENPARTITION_OPENED          (0x01u)
#define VFOTAH_SWITCHBANK_PARTITION_CHECKED             (0x02u)
#define VFOTAH_SWITCHBANK_BANK_SWITCHED                 (0x03u)
#define VFOTAH_SWITCHBANK_ERROR_DETECTED                (0x04u)

#define VFOTAH_GETMODULEINFO_STATE_ID                   (0x0Cu)
#define VFOTAH_GETMODULEINFO_STATE_IDLE                 (0x00u)
#define VFOTAH_GETMODULEINFO_OPENPARTITION_OPENED       (0x01u)
#define VFOTAH_GETMODULEINFO_ERROR_DETECTED             (0x02u)

#define VFOTAH_NUMBER_OF_SM                             (0x0Du)
#define VFOTAH_ANY_STATE_IDLE                           (0x00u)

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
#define VFOTAH_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/*
 * APIs called by vFotaH:
 */

/**********************************************************************************************************************
 *  vFotaH_vSwUpdMSyncModule()
 *********************************************************************************************************************/
/*! \brief       Copies a single module from the active partition to the target partition.
 *  \details     -
 *  \param[in]   ModuleHd         The handle of the module to be copied.
 *  \param[in]   PartitionState   The target partition.
 *  \return      E_OK             Copying successfully finished.
 *  \return      VFOTAH_E_PENDING Copying in progress.
 *  \return      E_NOT_OK         Copying failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMService
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMSyncModule(vSwUpdM_ModuleHandleIdType ModuleHd, vSwUpdM_PartitionStateType PartitionState);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMSyncPartition()
*********************************************************************************************************************/
/*! \brief       Copies the active partition to the target partition.
 *  \details     -
 *  \param[in]   PartitionState   The target partition.
 *  \return      E_OK             Copying successfully finished.
 *  \return      VFOTAH_E_PENDING Copying in progress.
 *  \return      E_NOT_OK         Copying failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMSyncPartition(vSwUpdM_PartitionStateType PartitionState);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMValidatePartition()
*********************************************************************************************************************/
/*! \brief       Validates a partition.
 *  \details     -
 *  \param[in]   PartitionState   The target partition.
 *  \return      E_OK             Validation successfully finished.
 *  \return      VFOTAH_E_PENDING Validation in progress.
 *  \return      E_NOT_OK         Validation failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMValidatePartition(vSwUpdM_PartitionStateType PartitionState);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMValidateModule()
*********************************************************************************************************************/
/*! \brief       Validates a module.
 *  \details     -
 *  \param[in]   PartitionState   The target partition.
 *  \param[in]   ModuleHd         The handle of the selected module.
 *  \return      E_OK             Validation successfully finished.
 *  \return      VFOTAH_E_PENDING Validation in progress.
 *  \return      E_NOT_OK         Validation failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMValidateModule(vSwUpdM_PartitionStateType PartitionState, vSwUpdM_ModuleHandleIdType ModuleHd);

/**********************************************************************************************************************
 *  vFotaH_vSwUpdMEraseModule()
 *********************************************************************************************************************/
/*! \brief       Erases a module.
 *  \details     -
 *  \param[in]   ModuleHd         The handle of the module to erase.
 *  \return      E_OK             Erase finished successfully.
 *  \return      VFOTAH_E_PENDING Erase in progress.
 *  \return      E_NOT_OK         Erase failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMService
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMEraseModule(vSwUpdM_ModuleHandleIdType ModuleHd);


/**********************************************************************************************************************
*  vFotaH_vSwUpdMVerifyModule()
*********************************************************************************************************************/
/*! \brief       Verifies a module with a CRC or Signature.
 *  \details     -
 *  \param[in]   VerifyData    The verification data (e.g. CRC or Signature).
 *  \param[in]   VerifySize    The size of the verification data.
 *  \param[in]   ModuleHd      The module handle of the selected module.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMVerifyModule(P2CONST(uint8, AUTOMATIC, VFOTAH_APPL_VAR) VerifyData, uint16 VerifySize, vSwUpdM_ModuleHandleIdType ModuleHd);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMGetModuleIdByRange()
*********************************************************************************************************************/
/*! \brief       Get the Module ID of the range.
 *  \details     -
 *  \param[in]   MemAddr          The target memory addres of the download.
 *  \param[in]   MemLength        The target memory length of the download.
 *  \param[out]  ModuleId         The module id of the opened module.
 *  \return      E_OK             Preparation finished successfully.
 *  \return      E_NOT_OK         Preparation failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMGetModuleIdByRange(P2VAR(vSwUpdM_ModuleIdType, AUTOMATIC, VFOTAH_APPL_VAR) ModuleId, vFotaH_AddrType MemAddr, vFotaH_LengthType MemLength);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMPrepareDownload()
*********************************************************************************************************************/
/*! \brief       Make preparations (creation of segments) for a pending download.
 *  \details     -
 *  \param[in]   MemAddr          The target memory addres of the download.
 *  \param[in]   MemLength        The target memory length of the download.
 *  \return      E_OK             Preparation finished successfully.
 *  \return      VFOTAH_E_PENDING Preparation in progress.
 *  \return      E_NOT_OK         Preparation failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMPrepareDownload(vFotaH_AddrType MemAddr, vFotaH_LengthType MemLength, vSwUpdM_ProcessingOperationType Dfi);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMTransferData()
*********************************************************************************************************************/
/*! \brief       Flashes a chunk of data.
 *  \details     -
 *  \param[in]   DownloadDatap     A pointer to the structure describing the chunk.
 *  \return      E_OK              Chunk successfully flashed.
 *  \return      VFOTAH_E_PENDING  Flashing in progress.
 *  \return      E_NOT_OK          Flashing failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMTransferData(P2VAR(vFotaH_DownloadDataType, AUTOMATIC, VFOTAH_VAR_NOINIT) DownloadDatap);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMFinalizeDownload()
*********************************************************************************************************************/
/*! \brief       Finalizes a download sequence.
 *  \details     -
 *  \return      E_OK             Sequence finalized successfully.
 *  \return      VFOTAH_E_PENDING In progress.
 *  \return      E_NOT_OK         Finalizing failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMFinalizeDownload(void);


/**********************************************************************************************************************
*  vFotaH_vSwUpdMCheckFinalizeSegment()
*********************************************************************************************************************/
/*! \brief       Finalizes a unfinished segment.
 *  \details     Checks if the segment is filled completely and in that case finalizes it.
 *  \return      E_OK             Segment finalized successfully.
 *  \return      VFOTAH_E_PENDING In progress.
 *  \return      E_NOT_OK         Finalizing failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMCheckFinalizeSegment(vSwUpdM_AddressType SegmentAddress);


/**********************************************************************************************************************
*  vFotaH_vSwUpdMSwitchBank()
*********************************************************************************************************************/
/*! \brief      Perform a partition switch to the target partition.
 *  \details     -
 *  \param[in]   PartitionState    The partition to switch to.
 *  \return      E_OK              Switch request successfully processed.
 *  \return      VFOTAH_E_PENDING  Switch request in progress.
 *  \return      E_NOT_OK          Switch request failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMSwitchBank(vSwUpdM_PartitionStateType PartitionState);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMReadRange()
*********************************************************************************************************************/
/*! \brief       Reads a memory range.
 *  \details     -
 *  \param[out]  target           A pointer to the target range the data will be written to.
 *  \param[in]   address          The virtual address to read from.
 *  \param[in]   length           The number of bytes to read.
 *  \param[in]   psType           The partition to read from.
 *  \return      E_OK             Data successfully read.
 *  \return      VFOTAH_E_PENDING Read in progress.
 *  \return      E_NOT_OK         Read failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMReadRange(P2VAR(uint8, AUTOMATIC, VFOTAH_APPL_VAR) target, uint32 address, uint32 length, vSwUpdM_PartitionStateType psType);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMGetModulePartitionInfo()
*********************************************************************************************************************/
/*! \brief        Return info about the selected module and the partition.
 *  \details       -
 *  \param[out]    ModuleInfo       Pointer to module info struct.
 *  \param[out]    PartitionInfo    Pointer to partition info struct.
 *  \param[in]     ModuleHd         The module handle of the selected module.
 *  \param[in]     PartitionState   The partition state of the selected module.
 *  \return        E_OK             Valid Module Info retrieved.
 *  \return        E_NOT_OK         Get Module Info failed, invalid handle.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 *  \ingroup       vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMGetModulePartitionInfo(P2VAR(vSwUpdM_ModuleInfoType, AUTOMATIC, VFOTAH_APPL_VAR) ModuleInfo, P2VAR(vSwUpdM_PartitionInfoType, AUTOMATIC, VFOTAH_APPL_VAR) PartitionInfo, vSwUpdM_ModuleHandleIdType ModuleHd, vSwUpdM_PartitionStateType PartitionState);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMHasActivePartitionLaterSoftware()
*********************************************************************************************************************/
/*! \brief        Indicates if the latest software is installed on currently active partition.
 *  \details       -
 *  \param[out]    LaterSW          Boolean about state of active partition.
 *  \return        E_OK             The LaterSW state could be determined.
 *  \return        E_NOT_OK         Needed partition revisions could not be determined.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMHasActivePartitionLaterSoftware(P2VAR(boolean, AUTOMATIC, VFOTAH_APPL_VAR) LaterSW);


/**********************************************************************************************************************
*  vFotaH_vSwUpdMIsBasicUseCase()
*********************************************************************************************************************/
/*! \brief        Returns if Basic use case is active.
 *  \details       -
 *  \return        FALSE            No Basic use case.
 *  \return        TRUE             Basic use case.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       vSwUpdMService
*********************************************************************************************************************/
FUNC(boolean, VFOTAH_CODE) vFotaH_vSwUpdMIsBasicUseCase(void);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMGetNumberOfRegionsOfModule()
*********************************************************************************************************************/
/*! \brief         Returns the number of regions of the reuested module.
 *  \details       -
 *  \param[out]    NumberOfRegions  The number of regions of this module.
 *  \param[in]     ModuleId         The module id that information is requested from.
 *  \return        E_OK             The operation succeeded.
 *  \return        E_NOT_OK         The operation failed.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMGetNumberOfRegionsOfModule(P2VAR(uint32, AUTOMATIC, VFOTAH_VAR_NOINIT) NumberOfRegions, vSwUpdM_ModuleHandleIdType ModuleHd);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMGetRegionInfoOfId()
*********************************************************************************************************************/
/*! \brief         Returns the region info of the reuested module and Index.
 *  \details       -
 *  \param[out]    RegionInfo       The region info.
 *  \param[in]     ModuleId         The module id that information is requested from.
 *  \param[in]     Index            The index of the region.
 *  \return        E_OK             The operation succeeded.
 *  \return        E_NOT_OK         The operation failed.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       vSwUpdMService
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMGetRegionInfoOfId(P2VAR(vSwUpdM_RegionInfoType, AUTOMATIC, VFOTAH_VAR_NOINIT) RegionInfo, vSwUpdM_ModuleHandleIdType ModuleHd, uint16 Index);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMReset()
*********************************************************************************************************************/
/*! \brief       Reset the state machines of vFotaH.
 *  \details     -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     vSwUpdMService
*********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_vSwUpdMReset(void);

/**********************************************************************************************************************
 *  vFotaH_vSwUpdMInit()
 *********************************************************************************************************************/
/*! \brief       Initializes the vSwUpdM specific global data of vFotaH.
 *  \details     -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     vSwUpdMService
 *********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_vSwUpdMInit(void);


/**********************************************************************************************************************
 *  vFotaH_vSwUpdMShutdown()
 *********************************************************************************************************************/
/*! \brief         Forwards the shutdown request to vSwUpdM.
 *  \details       -
 *  \param[in]     RestartSelect  Select whether a restart shall be performed. Use either VFOTAH_PERFORM_RESTART to tell
 *                                the vFotaH to be available again or VFOTAH_PERFORM_NO_RESTART to prepare it for reset.
 *  \return        E_OK       The request has been accepted, check shutdown result with vSwUpdM_GetState.
 *  \return        E_NOT_OK   The request has been rejected.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       vSwUpdMService
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMShutdown(uint8 RestartSelect);


/**********************************************************************************************************************
 *  vFotaH_vSwUpdMResetDownloadInProgress()
 *********************************************************************************************************************/
/*! \brief         Resets a download when one is in progress.
 *  \details       -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       vSwUpdMService
 *********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_vSwUpdMResetDownloadInProgress(void);


#define VFOTAH_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

#endif /* VFOTAH_VSWUPDM_H */

/**********************************************************************************************************************
 *  END OF FILE: vFotaH_vSwUpdM.h
 *********************************************************************************************************************/
