/*
********************************************************************************
*
* File name: Xcp.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: YongZ/2018.12.13
* Change: New created
* Cause: New
********************************************************************************
* Version: 3.0
* Author/Date: YongZ/2020.07.02
* Change: Add release software number
* Cause: Update
********************************************************************************
* Version: 3.1
* Author/Date: YongZ/2020.08.11
* Change: Delete macro definition of timestamp.
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: FangT/2020.08.21
* Change: Add Det function.
* Cause: Bugfix
********************************************************************************
* Version: 3.3
* Author/Date: FangT/2020.09.15
* Change: Modify the function name according to the AUTOSAR specification, add
*         MemMap.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: FangT/2021.03.03
* Change: Add checksum and Multi pudid functions.
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: FangT/2021.06.30
* Change: Modify code specifications.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: FangT/2021.08.18
* Change: Modify the code specification.
* Cause: Optimization
********************************************************************************
* Version: 3.7
* Author/Date: FangT/2021.10.20
* Change: Modified version number.
* Cause: Optimization
********************************************************************************
* Version: 3.8
* Author/Date: FangT/2021.10.29
* Change: Modify coding style.
* Cause: Optimization
********************************************************************************
* Version: 3.9
* Author/Date: FangT/2021.11.01
* Change: Update software version to 3.3.1.
* Cause: Update
********************************************************************************
* Version: 3.10
* Author/Date: FangT/2021.11.12
* Change: Update software version to 3.3.2.
* Cause: Update
********************************************************************************
* Version: 3.10
* Author/Date: FangT/2021.12.07
* Change: Update software version to 3.3.3.
* Cause: Update
********************************************************************************
* Version: 3.11
* Author/Date: FangT/2021.12.17
* Change: Modify the length of the single-pointer RAM buffer to be configurable.
* Cause: Optimization
********************************************************************************
* Version: 3.12
* Author/Date: FangT/2021.12.23
* Change: Update software version to 3.3.4.
* Cause: Update
********************************************************************************
* Version: 3.13
* Author/Date: FangT/2022.03.16
* Change: 1.Modify the byte order of the Ethernet sending data header
*         2.Change the send length to uint32 type.
*         3.Modify code specification.
* Cause: Optimization
********************************************************************************
* Version: 3.14
* Author/Date: FangT/2022.06.21
* Change: Update software version to 3.3.5.
* Cause: Update
********************************************************************************
* Version: 3.15
* Author/Date: ShiRong/2022.09.16
* Change: Update software version to 3.3.6.
* Cause: Update
*******************************************************************************
* Version: 3.16
* Author/Date: ShiRong/2022.10.12
* Change: Add structure Xcp_Addr_st.
* Cause: Update
*******************************************************************************
* Version: 3.17
* Author/Date: ShiR/2022.11.3
* Change: Modify the adaptive length of Ethernet dto and cto.
* Cause: Update
********************************************************************************
* Version: 3.18
* Author/Date: ShiRong/2022.11.28
* Change: 1.Modify the bug with mismatched parentheses .
*         2.Add XCP_DAQMEMSIZE Configuration Item
* Cause: Update
*******************************************************************************
* Version: 3.19
* Author/Date: ShiRong/2023.02.09
* Change: 1.Add STIM function.
*         2.Add structure calibration method.
*         3.Add the observation method of collecting while sending.
* Cause: Update
********************************************************************************
* Version: 3.20
* Author/Date: ShiRong/2023.02.13
* Change: 1.Delete redundant comments.
* Cause: Update
********************************************************************************
* Version: 3.21
* Author/Date: ShiRong/2023.02.13
* Change: 1.Remove compilation warnings.
* Cause: Update
********************************************************************************
* Version: 3.22
* Author/Date: ShiRong/2023.02.13
* Change: Update software version to 3.3.12.
* Cause: Update
********************************************************************************
* Version: 3.23
* Author/Date: ShiRong/2023.03.09
* Change: 1.Modify the data processing of STIM function.
* Cause: Bug
********************************************************************************
* Version: 3.24
* Author/Date: ShiRong/2023.03.13
* Change: 1.Update software version to 3.3.14.
* Cause: Update
********************************************************************************
* Version: 3.25
* Author/Date: ShiRong/2023.03.21
* Change: 1.Update software version to 3.3.15.
* Cause: Update
********************************************************************************
* Version: 3.26
* Author/Date: ShiRong/2023.04.16
* Change: 1.Add security algorithm functionality.
*         2.Update software version to 3.3.16
* Cause: Update
********************************************************************************
* Version: 3.27
* Author/Date: ShiRong/2023.05.06
* Change: 1.Add Block Transfer Mode.
*         2.Update software version to 3.3.17.
* Cause: Update
********************************************************************************
* Version: 3.28
* Author/Date: ShiRong/2023.05.12
* Change: 1.Add storage RAM scaling to NVM functionality.
*         2.Update software version to 3.3.18.
* Cause: Update
********************************************************************************
* Version: 3.29
* Author/Date: ShiRong/2023.05.16
* Change: 1.The issue of modifying the polyspace.
*         2.Update software version to 3.3.19.
* Cause: Update
********************************************************************************
* Version: 3.30
* Author/Date: ShiRong/2023.05.19
* Change: 1.Add error replies related to security algorithms.
*         2.Fix timestamp adaptation byte alignment issues with STIM
*           functionality.
*         3.Update software version to 3.3.20.
* Cause: Update
********************************************************************************
* Version: 3.31
* Author/Date: ShiRong/2023.05.23
* Change: 1.Modifying NVM Configuration Reference Issues.
*         2.Update software version to 3.3.21.
* Cause: Bug.
********************************************************************************
* Version: 3.32
* Author/Date: ShiRong/2023.05.24
* Change: 1.Adaptation STIM message cannot reach 1400.
*         2.Update software version to 3.3.22.
* Cause: Update
********************************************************************************
* Version: 3.33
* Author/Date: ShiRong/2023.05.31
* Change: 1.The issue of missing address retrieval in modifying STIM timestamp
*           code writing.
*         2.Add XCP_SW_REVISION_VERSION and Update to version 3.7.0.1
* Cause: Update
********************************************************************************
* Version: 3.34
* Author/Date: ShiRong/2023.06.25
* Change: 1.Modifying single pointer calibration byte alignment issues.
*         2.Update software version to 3.8.0.0
* Cause: Bugfix
********************************************************************************
* Version: 3.35
* Author/Date: ShiRong/2023.08.01
* Change: 1.Add verification algorithms for XCP_ADD11 and XCP_CRC32.
*         2.Add flash writing function.
*         3.Update software version to 3.8.0.1
* Cause: Update
********************************************************************************
* Version: 3.36
* Author/Date: ShiRong/2023.08.01
* Change: Update software version to 3.8.0.2
* Cause: Update
********************************************************************************
* Version: 3.37
* Author/Date: ShiRong/2023.08.02
* Change: 1.Add sending confirmation timeout judgment function.
*         2.Update software version to 3.8.0.3
* Cause: Update
********************************************************************************
* Version: 3.38
* Author/Date: ShiRong/2023.08.04
* Change: 1.Modify compilation issues caused by validation enabled configuration
*           items.
*         2.Update software version to 3.8.0.4
* Cause: Update
********************************************************************************
* Version: 3.39
* Author/Date: ShiRong/2023.08.16
* Change: 1.Modifying Compilation Warning Issues.
*         2.Update software version to 3.8.0.5.
* Cause: Update
********************************************************************************
* Version: 3.40
* Author/Date: ShiRong/2023.08.17
* Change: 1.Modifying compilation issues when seed is enabled.
*         2.The sending confirmation time affects the block transmission function.
*         3.Update software version to 3.8.0.6.
* Cause: Bugfix
********************************************************************************
* Version: 3.41
* Author/Date: ShiRong/2023.08.28
* Change: 1.The sending confirmation time affects the block transmission function.
*         2.Update software version to 3.8.0.7.
* Cause: Bugfix
********************************************************************************
* Version: 3.42
* Author/Date: ShiRong/2023.09.26
* Change: 1.Optimize observation cycle execution logic.
*         2.Update software version to 3.9.0.1.
* Cause: Bugfix
********************************************************************************
* Version: 3.43
* Author/Date: ChenQJ/2023.10.31
* Change: 1. Remove Xcp_Cfg.h headfile including, already include in Xcp_Lcfg.h.
*         2. Update software version to 3.9.0.2.
* Cause: Bugfix
********************************************************************************
* Version: 3.44
* Author/Date: LinZhC/2023.12.14
* Change: 1. Change the struct XcpEventInfo name to XcpEventMonitorType, and
*           change the data type of the member(eventChannelMaxCycCnt and
*           eventChannelCurCnt).
*         2. Delete the CALCULATE and GETTIMER macros.
*         3.Update software version to 3.9.0.3.
* Cause: Bugfix
********************************************************************************
* Version: 3.45
* Author/Date: LinZhC/2024.01.10
* Change: 1.Modified compatibility of multi-bus and multi-PDU configurations.
*           The following changes have been modify:
*       (1) Add a custom (non-AUTOSAR) DET error code and SID.
*       (2) Modify the Xcp_DtoType, Xcp_StimDtoType, Xcp_EthDtoType, and
*           XCP_InfoDataType data structures.
*       (3) New Xcp_StateType, Xcp_ConnectionStatusType data structures.
*       (4) Modified the implementation of Xcp_StimOdt and Xcp_StimData,
*           and added Xcp_pDataQueue.
*         2.Modified QAC, Polyspace warnings and issues.The following changes
*           have been modify:
*       (1) The Xcp_StimOdt,Xcp_StimData,Xcp_pDataQueue pointer arithmetic is
*           changed to take the address of the corresponding subscript element.
*       (2) Added XCP_WORKING_PAGE and REFERENCE_PAGE macro definitions.
*         3.Update software version to 3.10.0.1.
* Cause: Update
********************************************************************************
* Version: 3.46
* Author/Date: LinZhC/2024.02.26
* Change: 1.Compatible with older configurations.
* Cause: Update
********************************************************************************
* Version: 3.47
* Author/Date: LinZhC/2024.03.11
* Change: 1.Update software version to 3.10.0.2
*         2.add macro XCP_CRM_DOWNLOAD_DATA_OFFSET,XCP_GET_SEED_FIRST_PART,
*           XCP_GET_SEED_REST_PART.
*         3.XCP_InfoDataType Increases the maximum ODT recorded by maxOdt.
*         4.Fixed and optimized logical issues with queue sending.
* Cause: Update
********************************************************************************
* Version: 3.48
* Author/Date: LinZhC/2024.04.01
* Change: 1.Unified xcp error interface.
*         2.Update software version to 3.10.0.4.
*         3.Modify coding specification problems.
* Cause: Update
********************************************************************************
* Version: 3.49
* Author/Date: KangJH/2024.05.22
* Change: 1.Update software version to 3.11.0.5.
*         2.Modify coding specification problems.
* Cause: Update
********************************************************************************
* Version: 3.50
* Author/Date: KangJH/2024.06.20
* Change: 1.Modify coding specification problems.
*         2.Add Memmap segment definition.
* Cause: Update
********************************************************************************
* Version: 3.51
* Author/Date: KangJH/2024.08.12
* Change: Fixed bug where unable to retrieve the last 3 bytes of data
*         within the calibration range.
* Cause: Bugfix
********************************************************************************
* Version: 3.52
* Author/Date: KangJH/2024.08.12
* Change: Add the XCP_CHECK_EVENTADDR macro definition to check the
*         XcpEventName address.
* Cause: Update
********************************************************************************
* Version: 3.53
* Author/Date: KangJH/2024.08.30
* Change: Add the XCP_DATA_MASK_FFC macro definition.
* Cause: Update
********************************************************************************
* Version: 3.56
* Author/Date: KangJH/2024.09.02
* Change: Add a macro definition of XCP_CHECK_STRUCTURE_RAMADDR for RAM address
*         check in structure calibration.
* Cause: Update
********************************************************************************
* Version: 3.57
* Author/Date: KangJH/2024.09.13
* Change: Update software version to 3.11.0.6.
* Cause: Update
********************************************************************************
* Version: 3.58
* Author/Date: KangJH/2024.09.30
* Change: 1.Modify the coding specification.
*         2.Update software version to 3.11.0.7.
* Cause: Optimization
********************************************************************************
* Version: 3.59
* Author/Date: KangJH/2024.10.10
* Change: 1.Fix compile issues.
*         2.Update software version to 3.11.0.8.
* Cause: Bugfix
********************************************************************************
* Version: 3.60
* Author/Date: KangJH/2024.10.12
* Change: Update software version to 3.11.0.9.
* Cause: Bugfix
********************************************************************************
* Version: 3.61
* Author/Date: KangJH/2024.10.12
* Change: Delete the condition of using header file CanXcp_Cfg.h and EthXcp_Cfg.h.
* Cause: Bugfix
********************************************************************************
* Version: 3.62
* Author/Date: KangJH/2024.10.13
* Change: Update software version to 3.11.0.10.
* Cause: Bugfix
********************************************************************************
* Version: 3.63
* Author/Date: KangJH/2024.10.23
* Change: 1.Update software version to 3.12.0.11.
*         2.Increase the available memory for DAQ measurement.
* Cause: Update
********************************************************************************
* Version: 3.64
* Author/Date: KangJH/2024.10.25
* Change: Modify the definition type of the structural variable queueSizeStim.
* Cause: Update
********************************************************************************
*/
#ifndef XCP_H_
#define XCP_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Xcp_Cfg.h"
#include "Xcp_Lcfg.h"
#if( XCP_FLASH_PROGRAMING_ENABLE == STD_ON )
#include "Fls.h"
#endif  /* XCP_FLASH_PROGRAMING_ENABLE == STD_ON */

#include "CanXcp_Types.h"              /* Type definitions for XCP on CAN ASR. */
#include "CanXcp_Cfg.h"                /* Include configuration of XCP on CAN. */
#if( XCP_ONCAN_ENABLE == STD_ON )
#include "CanXcp_Lcfg.h"
#endif  /* XCP_ONCAN_ENABLE == STD_ON */

#include "EthXcp_Cfg.h"                /* Include configuration of XCP on ETH. */
#if( XCP_ONETHERNET_ENABLE == STD_ON )
#include "EthXcp_Lcfg.h"
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */

#if( XCP_ENABLE_NVM_SAVE_DATA == STD_ON )
#include "NvM.h"                       /* Contains the configuration used by XCP in NVM. */
#endif  /* XCP_ENABLE_NVM_SAVE_DATA == STD_ON */

#if( XCP_ENABLE_CHECKSUM == STD_ON )
#include "Crc.h"
#endif  /* XCP_ENABLE_CHECKSUM == STD_ON */

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define XCP_40                 (40U)
#define XCP_62                 (62U)
#define XCP_63                 (63U)
#define XCP_64                 (64U)
#define XCP_100                (100U)
#define XCP_1000               (1000U)
#define XCP_1000000            (1000000U)
#define XCP_1000000000         (1000000000UL)
#define XCP_FFFF0000           (0xFFFF0000UL)

#define XCP_MASK_BYTE_80       (0x80U)
#define XCP_MAX_QUEUE_SIZE     (1024U)
#define XCP_COPY_LEN           (512U)
#define XCP_ETH_DATA_SIZE      (1500U)
#define XCP_BYTE_ALIGNMENT_4   (4U)
#define XCP_CRC_STARTVALUE     (0U)
#define XCP_CLEAN_NVM_FLAG     (0U)
#define XCP_CLEAN_SEND_FLAG    (0U)
#define XCP_REQ_COPY           (1U)
#define XCP_CLEAN_COPY_FLAG    (0U)
/* MASK */
#define XCP_U8_MASK            (0xFFU)
#define XCP_U16_MASK           (0xFFFFU)
#define XCP_U32_MASK           (0xFFFFFFFFUL)
#define XCP_DATA_MASK_FFC      (0xFFCU)
#define XCP_DATA_MASK_FF00     (0xFF00U)
#define XCP_DATA_MASK_00FF     (0x00FFU)
#define XCP_DATA_MASK_0F00     (0x0F00U)
#define XCP_DATA_MASK_000F     (0x000FU)
#define XCP_DATA_MASK_FFFFFFFC (0xFFFFFFFCUL)
/* Used for value calculation. */
#define XCP_VALUE_0            (0U)
#define XCP_VALUE_1            (1U)
#define XCP_VALUE_2            (2U)
#define XCP_VALUE_3            (3U)
#define XCP_VALUE_4            (4U)
#define XCP_VALUE_5            (5U)
#define XCP_VALUE_6            (6U)
#define XCP_VALUE_7            (7U)
#define XCP_VALUE_8            (8U)
#define XCP_VALUE_9            (9U)
/* Used to initialize data. */
#define XCP_INIT_0             (0U)
#define XCP_INIT_1             (1U)
#define XCP_INIT_2             (2U)
#define XCP_INIT_3             (3U)
#define XCP_INIT_4             (4U)
#define XCP_INIT_5             (5U)
#define XCP_INIT_6             (6U)
#define XCP_INIT_7             (7U)
#define XCP_INIT_8             (8U)
#define XCP_INIT_9             (9U)
/* Used for array index. */
#define XCP_INDEX_0            (0U)
#define XCP_INDEX_1            (1U)
#define XCP_INDEX_2            (2U)
#define XCP_INDEX_3            (3U)
#define XCP_INDEX_4            (4U)
#define XCP_INDEX_5            (5U)
#define XCP_INDEX_6            (6U)
#define XCP_INDEX_7            (7U)
#define XCP_INDEX_8            (8U)
#define XCP_INDEX_9            (9U)
/* Used for shifting. */
#define XCP_SHIFT_4            (4U)
#define XCP_SHIFT_8            (8U)
#define XCP_SHIFT_16           (16U)
#define XCP_SHIFT_24           (24U)
#define XCP_SHIFT_32           (32U)

#define XCP_E_OK               (E_OK)
#define XCP_E_NOT_OK           (E_NOT_OK)

/* Xcp error id. */
#define XCP_E_NO_ERROR         (0x00U)
#define XCP_E_INV_POINTER      (0x01U)
#define XCP_E_NOT_INITIALIZED  (0x02U)
#define XCP_E_INVALID_PDUID    (0x03U)
#define XCP_E_INIT_FAILED      (0x04U)
#define XCP_E_PARAM_POINTER    (0x12U)
/* Neusar define error id. */
#define XCP_E_PARAM_ERROR      (0x40U)

/* Check Enable seed key. */
#if( XCP_ENABLE_SEED_KEY == STD_ON )
    #define XCP_CHECK_RESOURCE_PROTECTION(resource)   \
           if( (Xcp_DataInformation.protectionStatus & (resource)) != 0U ) { Xcp_RecordError(XCP_CRC_ACCESS_LOCKED); return; }
#else
    #define XCP_CHECK_RESOURCE_PROTECTION(resource)
#endif  /* XCP_ENABLE_SEED_KEY == STD_ON */

#define XCP_SETMTA(p, e)                            (Xcp_DataInformation.mta = (p))  /* Assign a pointer to a mta. */


#define XCP_WRITE_BYTE_2_ADDR(addr, data)           (*(addr) = (data))
#define XCP_READ_BYTE_FROM_ADDR(addr)               (*(addr))

#define XCP_READ_CHECKSUMVALUE_FROM_ADDR(addr)      (*((tXcpChecksumAddType*)addr))
#define XCP_DUMMY_STATEMENT(v)                      ((v) = (v))

/* Version */
#define XCP_TRANSPORT_LAYER_VERSION         (0x0100U)
#define XCP_VERSION                         (0x0125U)
#define XCP_PROTOCOL_VERSION                (0x0100U)

#define XCP_VENDOR_ID                       (119U)
#define XCP_MODULE_ID                       (212U)
#define XCP_SW_MAJOR_VERSION                (3U)
#define XCP_SW_MINOR_VERSION                (12U)
#define XCP_SW_PATCH_VERSION                (0U)
#define XCP_SW_REVISION_VERSION             (11U)
#define XCP_INSTANCE_ID                     (0U)
#define XCP_AR_RELEASE_MAJOR_VERSION        (4U)
#define XCP_AR_RELEASE_MINOR_VERSION        (2U)
#define XCP_AR_RELEASE_REVISION_VERSION     (2U)

#define XCP_SID_GET_VERSIONINFO             (0x01U)
#define XCP_SID_TXCONFIRMATION              (0x02U)
#define XCP_SID_RXINDICATION                (0x03U)
#define XCP_SID_MAINFUNCTION                (0x04U)  /* SWS_Xcp_00823 */

/* Neusar define. */
#define XCP_SID_SENDDTOMODE                 (0x40U)
#define XCP_SID_READMTA                     (0x41U)
#define XCP_SID_SENDDTOFROMQUEUE            (0x42U)
#define XCP_SID_SEND                        (0x43U)


/* Packet Identifiers Slave -> Master. */
#define XCP_PID_RES                         (0xFFU)    /* Response packet. */
#define XCP_PID_ERR                         (0xFEU)    /* Error packet. */
#define XCP_PID_EV                          (0xFDU)    /* Event packet. */
#define XCP_PID_SERV                        (0xFCU)    /* Service request packet. */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT )
#define XCP_CALIBGROUP_PARABUF_ADDRSTART    ((uint32)&Xcp_CalibGroupParaRamBuf[0])
#define XCP_CALIBGROUP_PARABUF_ADDREND      (((uint32)&Xcp_CalibGroupParaRamBuf[0]) + Xcp_SinglePt_Addr[XCP_INIT_0].len)
#endif

/* Commands */
/* Standard Commands. */

#define XCP_CC_CONNECT                      (0xFFU)
#define XCP_CC_DISCONNECT                   (0xFEU)
#define XCP_CC_GET_STATUS                   (0xFDU)
#define XCP_CC_SYNC                         (0xFCU)

#define XCP_CC_GET_COMM_MODE_INFO           (0xFBU)
#define XCP_CC_GET_ID                       (0xFAU)
#define XCP_CC_SET_REQUEST                  (0xF9U)
#define XCP_CC_GET_SEED                     (0xF8U)
#define XCP_CC_UNLOCK                       (0xF7U)
#define XCP_CC_SET_MTA                      (0xF6U)
#define XCP_CC_UPLOAD                       (0xF5U)
#define XCP_CC_SHORT_UPLOAD                 (0xF4U)
#define XCP_CC_BUILD_CHECKSUM               (0xF3U)

#define XCP_CC_TRANSPORT_LAYER_CMD          (0xF2U)
#define XCP_CC_USER_CMD                     (0xF1U)

/* Calibration Commands. */
#define XCP_CC_DOWNLOAD                     (0xF0U)
#define XCP_CC_DOWNLOAD_NEXT                (0xEFU)
#define XCP_CC_DOWNLOAD_MAX                 (0xEEU)
#define XCP_CC_SHORT_DOWNLOAD               (0xEDU)
#define XCP_CC_MODIFY_BITS                  (0xECU)

/* Page switching Commands (PAG). */
#define XCP_CC_SET_CAL_PAGE                 (0xEBU)
#define XCP_CC_GET_CAL_PAGE                 (0xEAU)
#define XCP_CC_GET_PAG_PROCESSOR_INFO       (0xE9U)
#define XCP_CC_GET_SEGMENT_INFO             (0xE8U)
#define XCP_CC_GET_PAGE_INFO                (0xE7U)
#define XCP_CC_SET_SEGMENT_MODE             (0xE6U)
#define XCP_CC_GET_SEGMENT_MODE             (0xE5U)
#define XCP_CC_COPY_CAL_PAGE                (0xE4U)

/* DATA Acquisition and Stimulation Commands (DAQ/STIM). */
#define XCP_CC_SET_DAQ_PTR                  (0xE2U)
#define XCP_CC_WRITE_DAQ                    (0xE1U)
#define XCP_CC_SET_DAQ_LIST_MODE            (0xE0U)
#define XCP_CC_START_STOP_DAQ_LIST          (0xDEU)
#define XCP_CC_START_STOP_SYNCH             (0xDDU)
#define XCP_CC_WRITE_DAQ_MULIPLE            (0xC7U)
#define XCP_CC_READ_DAQ                     (0xDBU)
#define XCP_CC_GET_DAQ_CLOCK                (0xDCU)
#define XCP_CC_GET_DAQ_PROCESSOR_INFO       (0xDAU)
#define XCP_CC_GET_DAQ_RESOLUTION_INFO      (0xD9U)
#define XCP_CC_GET_DAQ_LIST_MODE            (0xDFU)
#define XCP_CC_GET_DAQ_EVENT_INFO           (0xD7U)
#define XCP_CC_CLEAR_DAQ_LIST               (0xE3U)
#define XCP_CC_GET_DAQ_LIST_INFO            (0xD8U)
#define XCP_CC_FREE_DAQ                     (0xD6U)
#define XCP_CC_ALLOC_DAQ                    (0xD5U)
#define XCP_CC_ALLOC_ODT                    (0xD4U)
#define XCP_CC_ALLOC_ODT_ENTRY              (0xD3U)

/* Non volatile memory Programming Commands PGM */
#define XCP_CC_PROGRAM_START                (0xD2U)
#define XCP_CC_PROGRAM_CLEAR                (0xD1U)
#define XCP_CC_PROGRAM                      (0xD0U)
#define XCP_CC_PROGRAM_RESET                (0xCFU)
#define XCP_CC_GET_PGM_PROCESSOR_INFO       (0xCEU)
#define XCP_CC_GET_SECTOR_INFO              (0xCDU)
#define XCP_CC_PROGRAM_PREPARE              (0xCCU)
#define XCP_CC_PROGRAM_FORMAT               (0xCBU)
#define XCP_CC_PROGRAM_NEXT                 (0xCAU)
#define XCP_CC_PROGRAM_MAX                  (0xC9U)
#define XCP_CC_PROGRAM_VERIFY               (0xC8U)

/* Command Return Codes. */
#define XCP_CRC_CMD_SYNCH                   (0x00U)
#define XCP_CRC_CMD_BUSY                    (0x10U)
#define XCP_CRC_DAQ_ACTIVE                  (0x11U)
#define XCP_CRC_PRM_ACTIVE                  (0x12U)
#define XCP_CRC_CMD_UNKNOWN                 (0x20U)
#define XCP_CRC_CMD_SYNTAX                  (0x21U)
#define XCP_CRC_OUT_OF_RANGE                (0x22U)
#define XCP_CRC_WRITE_PROTECTED             (0x23U)
#define XCP_CRC_ACCESS_DENIED               (0x24U)
#define XCP_CRC_ACCESS_LOCKED               (0x25U)
#define XCP_CRC_PAGE_NOT_VALID              (0x26U)
#define XCP_CRC_PAGE_MODE_NOT_VALID         (0x27U)
#define XCP_CRC_SEGMENT_NOT_VALID           (0x28U)
#define XCP_CRC_SEQUENCE                    (0x29U)
#define XCP_CRC_DAQ_CONDIF                  (0x2AU)
#define XCP_CRC_MEMORY_OVERFLOW             (0x30U)
#define XCP_CRC_GENERIC                     (0x31U)
#define XCP_CRC_VERIFY                      (0x32U)
#define XCP_CRC_RESOURCETEMPORARY_NOT_ACCESSIBLE (0x33U)
#define XCP_CRC_PENGDING                    (0x60U)

/* Event Codes. */
#define XCP_EV_RESUME_MODE                  (0x00U)
#define XCP_EV_CLEAR_DAQ                    (0x01U)
#define XCP_EV_STORE_DAQ                    (0x02U)
#define XCP_EV_STORE_CAL                    (0x03U)
#define XCP_EV_CMD_PENDING                  (0x05U)
#define XCP_EV_DAQ_OVERLOAD                 (0x06U)
#define XCP_EV_SESSION_TERMINATED           (0x07U)
#define XCP_EV_TIME_SYNC                    (0x08U)
#define XCP_EV_STIM_TIMEOUT                 (0x09U)
#define XCP_EV_USER                         (0xFEU)
#define XCP_EV_TRANSPORT                    (0xFFU)

/* PID MASK. */
#define XCP_PID_STIM_START                  (0x00U)
#define XCP_PID_STIM_END                    (0xBFU)

/* Service Request Codes. */
/* Slave requesting to be reset. */
#define XCP_SERV_RESET                      (0x00U)
/* Plain ASCII text null terminated. */
#define XCP_SERV_TEXT                       (0x01U)

/* Definitions */
/* ResourceMask (CONNECT) */

#define XCP_RM_CAL_PAG                      (0x01U)
#define XCP_RM_DAQ                          (0x04U)
#define XCP_RM_STIM                         (0x08U)
#define XCP_RM_PGM                          (0x10U)
#define XCP_RM_DAQ_STIM                     (0x0CU)

/* CommModeBasic (CONNECT) */
#define XCP_PI_INTEL                        (0x00U)
#define XCP_PI_MOTOROLA                     (0x01U)

#define XCP_CMB_BYTE_ORDER                  (0x01U << 0U)
#define XCP_CMB_ADDRESS_GRANULARITY         (0x03U << 1U)
#define XCP_CMB_SLAVE_BLOCK_MODE            (0x01U << 6U)
#define XCP_CMB_OPTIONAL                    (0x01U << 7U)

#define XCP_CMB_ADDRESS_GRANULARITY_BYTE    (0U << 1U)
#define XCP_CMB_ADDRESS_GRANULARITY_WORD    (1U << 1U)
#define XCP_CMB_ADDRESS_GRANULARITY_DWORD   (2U << 1U)
#define XCP_CMB_ADDRESS_GRANULARITY_QWORD   (3U << 1U)

/* Protocol Info (GET_COMM_MODE_INFO - COMM_OPTIONAL). */
#define XCP_CMO_MASTER_BLOCK_MODE           (0x01U)
#define XCP_CMO_INTERLEAVED_MODE            (0x02U)

/* Session Status (GET_STATUS and SET_REQUEST). */
#define XCP_SS_STORE_CAL_REQ                (0x01U)
#define XCP_SS_BLOCK_UPLOAD                 (0x02U)  /* Internal */
#define XCP_SS_STORE_DAQ_REQ                (0x04U)
#define XCP_SS_CLEAR_DAQ_REQ                (0x08U)
#define XCP_SS_ERROR                        (0x10U)  /* Internal */
#define XCP_SS_CONNECTED                    (0x20U)  /* Internal */
#define XCP_SS_DAQ                          (0x40U)
#define XCP_SS_RESUME                       (0x80U)

/* Define for SET_REQUEST. */
#define XCP_ACTION_READ                     (1U)
#define XCP_ACTION_WRITE                    (0U)

/* Identifier Type (GET_ID). */
#define XCP_IDT_ASCII                       (0U)
#define XCP_IDT_ASAM_NAME                   (1U)
#define XCP_IDT_ASAM_PATH                   (2U)
#define XCP_IDT_ASAM_URL                    (3U)
#define XCP_IDT_ASAM_UPLOAD                 (4U)
#define XCP_IDT_VECTOR_MAPNAMES             (0xDBU)

/* Checksum Types (BUILD_CHECKSUM). */
#define XCP_CHECKSUM_TYPE_ADD11             (0x01U)  /* Add BYTE into a BYTE checksum, ignore overflows. */
#define XCP_CHECKSUM_TYPE_ADD12             (0x02U)  /* Add BYTE into a WORD checksum, ignore overflows.*/
#define XCP_CHECKSUM_TYPE_ADD14             (0x03U)  /* Add BYTE into a DWORD checksum, ignore overflows. */
#define XCP_CHECKSUM_TYPE_ADD22             (0x04U)  /* Add WORD into a WORD checksum, ignore overflows,
                                                        blocksize must be modulo 2. */
#define XCP_CHECKSUM_TYPE_ADD24             (0x05U)  /* Add WORD into a DWORD checksum, ignore overflows,
                                                        blocksize must be modulo 2. */
#define XCP_CHECKSUM_TYPE_ADD44             (0x06U)  /* Add DWORD into DWORD, ignore overflows,
                                                        blocksize must be modulo 4. */
#define XCP_CHECKSUM_TYPE_CRC16             (0x07U)  /* See CRC error detection algorithms. */
#define XCP_CHECKSUM_TYPE_CRC16CCITT        (0x08U)  /* See CRC error detection algorithms. */
#define XCP_CHECKSUM_TYPE_CRC32             (0x09U)  /* See CRC error detection algorithms. */
#define XCP_CHECKSUM_TYPE_DLL               (0xFFU)  /* User defined, ASAM MCD 2MC DLL Interface. */

/* Page Mode (SET_CAL_PAGE). */
#define XCP_CAL_ECU                         (0x01U)
#define XCP_CAL_XCP                         (0x02U)
#define XCP_CAL_ALL                         (0x80U)  /* Not supported. */

/* PAG_PROPERTIES (GET_PAG_PROCESSOR_INFO). */
#define XCP_PAG_PROPERTY_FREEZE             (0x01U)

/* PAGE_PROPERTIES (GET_PAGE_INFO). */
#define XCP_ECU_ACCESS_TYPE                 (0x03U)
#define XCP_READ_ACCESS_TYPE                (0x0CU)
#define XCP_WRITE_ACCESS_TYPE               (0x30U)

/* XCP_ECU_ACCESS_TYPE */
#define XCP_ECU_ACCESS_NONE                 (0U << 0U)
#define XCP_ECU_ACCESS_WITHOUT              (1U << 0U)
#define XCP_ECU_ACCESS_WITH                 (2U << 0U)
#define XCP_ECU_ACCESS_DONT_CARE            (3U << 0U)

/* XCP_READ_ACCESS_TYPE */
#define XCP_READ_ACCESS_NONE                (0U << 2U)
#define XCP_READ_ACCESS_WITHOUT             (1U << 2U)
#define XCP_READ_ACCESS_WITH                (2U << 2U)
#define XCP_READ_ACCESS_DONT_CARE           (3U << 2U)

/* XCP_WRITE_ACCESS_TYPE */
#define XCP_WRITE_ACCESS_NONE               (0U << 4U)
#define XCP_WRITE_ACCESS_WITHOUT            (1U << 4U)
#define XCP_WRITE_ACCESS_WITH               (2U << 4U)
#define XCP_WRITE_ACCESS_DONT_CARE          (3U << 4U)

/* SEGMENT_MODE (GET_SEGMENT_MODE, SET_SEGMENT_MODE) */
#define XCP_SEGMENT_FLAG_FREEZE             (0x01U)

/* DAQ_LIST_MODE (GET_DAQ_LIST_MODE, SET_DAQ_LIST_MODE) */
#define XCP_DAQ_FLAG_SELECTED               (0x01U)
#define XCP_DAQ_FLAG_DIRECTION              (0x02U)  /* Data Stimulation Mode. */
#define XCP_DAQ_FLAG_TIMESTAMP              (0x10U)  /* Timestamps */
#define XCP_DAQ_FLAG_NO_PID                 (0x20U)  /* No PID. */
#define XCP_DAQ_FLAG_RUNNING                (0x40U)  /* Is started. */
#define XCP_DAQ_FLAG_RESUME                 (0x80U)  /* Resume Mode. */
#define XCP_DAQ_FLAG_RESERVED               (0x08U)
#define XCP_DAQ_FLAG_OVERRUN                (0x08U)  /* Overun (Internal Use) */

#define XCP_DAQ_LIST_PRESCALER              (1U)
#define XCP_DAQ_LIST_PRIORITY               (0U)

/* GET_DAQ_PROCESSOR_INFO */
/* DAQ_PROPERTIES */
#define XCP_DAQ_PROPERTY_CONFIG_TYPE        (0x01U)
#define XCP_DAQ_PROPERTY_PRESCALER          (0x02U)
#define XCP_DAQ_PROPERTY_RESUME             (0x04U)
#define XCP_DAQ_PROPERTY_BIT_STIM           (0x08U)
#define XCP_DAQ_PROPERTY_TIMESTAMP          (0x10U)
#define XCP_DAQ_PROPERTY_NO_PID             (0x20U)
#define XCP_DAQ_PROPERTY_OVERLOAD_INDICATION  (0xC0U)

/* DAQ Overload Indication Type */
#define XCP_DAQ_OVERLOAD_INDICATION_NONE    (0U << 6U)
#define XCP_DAQ_OVERLOAD_INDICATION_PID     (1U << 6U)
#define XCP_DAQ_OVERLOAD_INDICATION_EVENT   (2U << 6U)

#define XCP_DAQ_OVERLOAD_PID                (0x80U)  /* Overloay pid. */
#if( XCP_ID_TYPE_ABSOLUTE == XCP_IDENTIFICATION_FIELD_TYPE )
#define XCP_DAQ_DTO_PID_LEN                 (1U)
#else
#define XCP_DAQ_ABS_ODT_PID_IDX_OFFSET      (0U)
#define XCP_DAQ_ABS_ODT_DAQ_LIST_IDX_OFFSET (1U)
#define XCP_DAQ_DTO_PID_LEN                 (2U)
#endif

/* DAQ_KEY_BYTE */
#define XCP_DAQ_OPT_TYPE                    (0x0FU)
#define XCP_DAQ_EXT_TYPE                    (0x30U)
#define XCP_DAQ_HDR_TYPE                    (0xC0U)

/* DAQ Optimisation Type. */
#define XCP_DAQ_OPT_DEFAULT                 (0U << 0U)
#define XCP_DAQ_OPT_ODT_16                  (1U << 0U)
#define XCP_DAQ_OPT_ODT_32                  (2U << 0U)
#define XCP_DAQ_OPT_ODT_64                  (3U << 0U)
#define XCP_DAQ_OPT_ALIGNMENT               (4U << 0U)
#define XCP_DAQ_OPT_MAX_ENTRY_SIZE          (5U << 0U)

/* DAQ Address Extension Scope. */
#define XCP_DAQ_EXT_FREE                    (0U << 4U)
#define XCP_DAQ_EXT_ODT                     (1U << 4U)
#define XCP_DAQ_EXT_DAQ                     (3U << 4U)

/* DAQ Identification Field Type. */
#define XCP_DAQ_HDR_PID                     (0U << 6U)
#define XCP_DAQ_HDR_ODT_DAQB                (1U << 6U)
#define XCP_DAQ_HDR_ODT_DAQW                (2U << 6U)
#define XCP_DAQ_HDR_ODT_FIL_DAQW            (3U << 6U)

/* GET_DAQ_RESOLUTION_INFO */
/* TIMESTAMP_MODE */
#define XCP_DAQ_TIMESTAMP_SIZE              (0x07U)
#define XCP_DAQ_TIMESTAMP_FIXED             (0x08U)
#define XCP_DAQ_TIMESTAMP_UNIT              (0xF0U)
#define GRANULARITY_ODT_ENTRY_SIZE          (1U)

/* DAQ Timestamp Size. */
#define XCP_DAQ_TIMESTAMP_OFF               (0U << 0U)
#define XCP_DAQ_TIMESTAMP_BYTE              (1U << 0U)
#define XCP_DAQ_TIMESTAMP_WORD              (2U << 0U)
#define XCP_DAQ_TIMESTAMP_DWORD             (4U << 0U)

/* DAQ_LIST_PROPERTIES (GET_DAQ_LIST_INFO) */
#define XCP_DAQ_LIST_PREDEFINED             (0x01U)
#define XCP_DAQ_LIST_FIXED_EVENT            (0x02U)
#define XCP_DAQ_LIST_DIR_DAQ                (0x04U)
#define XCP_DAQ_LIST_DIR_STIM               (0x08U)

/* EVENT_PROPERTY (GET_DAQ_EVENT_INFO) */

#define XCP_DAQ_EVENT_DIRECTION_DAQ         (0x04U)
#define XCP_DAQ_EVENT_DIRECTION_STIM        (0x08U)
#define XCP_DAQ_EVENT_DIRECTION_DAQ_STIM    (0x0CU)

/* Comm mode programming parameter (PROGRAM_START). */
#define XCP_PI_PGM_BLOCK_DOWNLOAD           (0x01U)
#define XCP_PI_PGM_BLOCK_UPLOAD             (0x40U)
#define XCP_PI_PGM_BLOCK_MODE               (0x41U)

/* PGM_PROPERTIES (GET_PGM_PROCESSOR_INFO) */
#define XCP_PGM_ACCESS_TYPE                 (0x03U)
#define XCP_PGM_COMPRESSION_TYPE            (0x0CU)
#define XCP_PGM_ENCRYPTION_TYPE             (0x30U)
#define XCP_PGM_NON_SEQ_TYPE                (0xC0U)

/* PGM Access Mode. */
#define XCP_PGM_ACCESS_ABSOLUTE             (1U << 0U)
#define XCP_PGM_ACCESS_FUNCTIONAL           (2U << 0U)
#define XCP_PGM_ACCESS_FREE                 (3U << 0U)

/* PGM Compression type. */
#define XCP_PGM_COMPRESSION_NONE            (0U << 2U)
#define XCP_PGM_COMPRESSION_SUPPORTED       (1U << 2U)
#define XCP_PGM_COMPRESSION_REQUIRED        (3U << 2U)

/* PGM Encryption type. */
#define XCP_PGM_ENCRYPTION_NONE             (0U << 4U)
#define XCP_PGM_ENCRYPTION_SUPPORTED        (1U << 4U)
#define XCP_PGM_ENCRYPTION_REQUIRED         (3U << 4U)

/* PGM non sequential programming type. */
#define XCP_PGM_NON_SEQ_NONE                (0U << 6U)
#define XCP_PGM_NON_SEQ_SUPPORTED           (1U << 6U)
#define XCP_PGM_NON_SEQ_REQUIRED            (3U << 6U)

/* Compatibility defines. */
#define XCP_MAXCTO_AG                       (XCP_MAX_CTO)
#define XCP_MAXDTO_AG                       (XCP_MAX_DTO)
#define XCP_AG                              (1U)

/* XCP Commands and Responces, Type Definition. */
/* Protocol command structure definition. */
#define XCP_CRO_CMD                                     (XCP_CRO_BYTE(0U))
#define XCP_CRM_CMD                                     (XCP_CRM_BYTE(0U))
#define XCP_CRM_ERR                                     (XCP_CRM_BYTE(1U))
/* CONNECT */
#define XCP_CRO_CONNECT_LEN                             (2U)
#define XCP_CRO_CONNECT_MODE                            (XCP_CRO_BYTE(1U))
#define XCP_CRM_CONNECT_LEN                             (8U)
#define XCP_CRM_CONNECT_RESOURCE                        (XCP_CRM_BYTE(1U))
#define XCP_CRM_CONNECT_COMM_BASIC                      (XCP_CRM_BYTE(2U))
#define XCP_CRM_CONNECT_MAX_CTO_SIZE                    (XCP_CRM_BYTE(3U))
#define XCP_CRM_CONNECT_MAX_DTO_SIZE                    (XCP_CRM_WORD(2U))
#define XCP_CRM_CONNECT_PROTOCOL_VERSION                (XCP_CRM_BYTE(6U))
#define XCP_CRM_CONNECT_TRANSPORT_VERSION               (XCP_CRM_BYTE(7U))

/* DISCONNECT */
#define XCP_CRO_DISCONNECT_LEN                          (1U)
#define XCP_CRM_DISCONNECT_LEN                          (1U)

/* GET_STATUS */
#define XCP_CRO_GET_STATUS_LEN                          (1U)
#define XCP_CRM_GET_STATUS_LEN                          (6U)
#define XCP_CRM_GET_STATUS_STATUS                       (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_STATUS_PROTECTION                   (XCP_CRM_BYTE(2U))
#define XCP_CRM_GET_STATUS_CONFIG_ID                    (XCP_CRM_WORD(2U))

/* SYNCH */
#define XCP_CRO_SYNCH_LEN                               (1U)
#define XCP_CRM_SYNCH_LEN                               (2U)
#define XCP_CRM_SYNCH_RESULT                            (XCP_CRM_BYTE(1U))

/* GET_COMM_MODE_INFO */
#define XCP_CRO_GET_COMM_MODE_INFO_LEN                  (1U)
#define XCP_CRM_GET_COMM_MODE_INFO_LEN                  (8U)
#define XCP_CRM_GET_COMM_MODE_INFO_COMM_OPTIONAL        (XCP_CRM_BYTE(2U))
#define XCP_CRM_GET_COMM_MODE_INFO_MAX_BS               (XCP_CRM_BYTE(4U))
#define XCP_CRM_GET_COMM_MODE_INFO_MIN_ST               (XCP_CRM_BYTE(5U))
#define XCP_CRM_GET_COMM_MODE_INFO_QUEUE_SIZE           (XCP_CRM_BYTE(6U))
#define XCP_CRM_GET_COMM_MODE_INFO_DRIVER_VERSION       (XCP_CRM_BYTE(7U))

/* GET_ID */
#define XCP_CRO_GET_ID_LEN                              (2U)
#define XCP_CRO_GET_ID_TYPE                             (XCP_CRO_BYTE(1U))
#define XCP_CRM_GET_ID_LEN                              (8U)
#define XCP_CRM_GET_ID_MODE                             (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_ID_LENGTH                           (XCP_CRM_DWORD(1U))
#define XCP_CRM_GET_ID_DATA                             (&XCP_CRM_BYTE(8U))

/* SET_REQUEST */
#define XCP_CRO_SET_REQUEST_LEN                         (4U)
#define XCP_CRO_SET_REQUEST_MODE                        (XCP_CRO_BYTE(1U))
#define XCP_CRO_SET_REQUEST_CONFIG_ID                   (XCP_CRO_WORD(1U))
#define XCP_CRM_SET_REQUEST_LEN                         (1U)
/* SET_REQUEST EV  */
#define XCP_CRM_EV_ID                                   (XCP_EV_BYTE(0U))
#define XCP_CRM_EV_CODE                                 (XCP_EV_BYTE(1U))
#define XCP_CRM_SET_REQUEST_EV_CODE                     (XCP_CRM_BYTE(1U))

/* GET_SEED */
#define XCP_CRO_GET_SEED_LEN                            (3U)
#define XCP_CRO_GET_SEED_MODE                           (XCP_CRO_BYTE(1U))
#define XCP_CRO_GET_SEED_RESOURCE                       (XCP_CRO_BYTE(2U))
#define XCP_CRM_GET_SEED_LEN                            (XCP_CRM_GET_SEED_LENGTH + 2U)
#define XCP_CRM_GET_SEED_LENGTH                         (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_SEED_DATA                           (&XCP_CRM_BYTE(2U))
#define XCP_CRO_GET_SEED_HEAD_LEN                       (2U)

#if( defined XCP_GET_SEED_FIRST_PART )
#error XCP_GET_SEED_FIRST_PART redefinition
#endif
/** \brief The host requests the first part of the seed. */
#define XCP_GET_SEED_FIRST_PART                         (0U)

#if( defined XCP_GET_SEED_REST_PART )
#error XCP_GET_SEED_REST_PART redefinition
#endif
/** \brief The host requests the rest of the seed. */
#define XCP_GET_SEED_REST_PART                          (1U)

/* UNLOCK */
#define XCP_CRO_UNLOCK_LEN                              (8U)
#define XCP_CRO_UNLOCK_LENGTH                           (XCP_CRO_BYTE(1U))
#define XCP_CRO_UNLOCK_KEY                              (&XCP_CRO_BYTE(2U))
#define XCP_CRM_UNLOCK_LEN                              (2U)
#define XCP_CRM_UNLOCK_PROTECTION                       (XCP_CRM_BYTE(1U))

/* SET_MTA */
#define XCP_CRO_SET_MTA_LEN                             (8U)
#define XCP_CRO_SET_MTA_EXT                             (XCP_CRO_BYTE(3U))
#define XCP_CRO_SET_MTA_ADDR                            (XCP_CRO_DWORD(1U))
#define XCP_CRM_SET_MTA_LEN                             (1U)

/* UPLOAD */
#define XCP_CRM_UPLOAD_MAX_SIZE                         ((uint8)(XCP_MAXCTO_AG - 1U))
#define XCP_CRO_UPLOAD_LEN                              (2U)
#define XCP_CRO_UPLOAD_SIZE                             (XCP_CRO_BYTE(1U))
#define XCP_CRM_UPLOAD_LEN                              (1U)  /* +XCP_CRO_UPLOAD_SIZE */
#define XCP_CRM_UPLOAD_DATA                             (&XCP_CRM_BYTE(1U))

/* SHORT_UPLOAD */
#define XCP_CRO_SHORT_UPLOAD_LEN                        (8U)
#define XCP_CRO_SHORT_UPLOAD_SIZE                       (XCP_CRO_BYTE(1U))
#define XCP_CRO_SHORT_UPLOAD_EXT                        (XCP_CRO_BYTE(3U))
#define XCP_CRO_SHORT_UPLOAD_ADDR                       (XCP_CRO_DWORD(1U))
#define XCP_CRM_SHORT_UPLOAD_MAX_SIZE                   ((uint8)(XCP_MAXCTO_AG - 1U))
#define XCP_CRM_SHORT_UPLOAD_LEN                        (1U)  /* +XCP_CRO_SHORT_UPLOAD_SIZE */
#define XCP_CRM_SHORT_UPLOAD_DATA                       (&XCP_CRM_BYTE(1U))

/* BUILD_CHECKSUM */
#define XCP_CRO_BUILD_CHECKSUM_LEN                      (8U)
#define XCP_CRO_BUILD_CHECKSUM_SIZE                     (XCP_CRO_DWORD(1U))
#define XCP_CRM_BUILD_CHECKSUM_LEN                      (8U)
#define XCP_CRM_BUILD_CHECKSUM_TYPE                     (XCP_CRM_BYTE(1U))
#define XCP_CRM_BUILD_CHECKSUM_RESULT                   (XCP_CRM_DWORD(1U))

/* DOWNLOAD */
#define XCP_CRO_DOWNLOAD_MAX_SIZE                       ((uint8)((XCP_MAX_CTO - 2U) / XCP_AG))
#define XCP_CRO_DOWNLOAD_LEN                            (2U)  /* + XCP_CRO_DOWNLOAD_SIZE */
#define XCP_CRO_DOWNLOAD_SIZE                           (XCP_CRO_BYTE(1U))
#define XCP_CRO_DOWNLOAD_DATA                           (&XCP_CRO_BYTE(2U))
#define XCP_CRM_DOWNLOAD_LEN                            (1U)
#define XCP_CRM_DOWNLOAD_DATA_OFFSET                    (2U)

/* DOWNLOAD_NEXT */
#define XCP_CRO_DOWNLOAD_NEXT_MAX_SIZE                  ((uint8)((XCP_MAX_CTO - 2U) / XCP_AG))
#define XCP_CRO_DOWNLOAD_NEXT_LEN                       (2U)  /* + size */
#define XCP_CRO_DOWNLOAD_NEXT_SIZE                      (XCP_CRO_BYTE(1U))
#define XCP_CRO_DOWNLOAD_NEXT_DATA                      (&XCP_CRO_BYTE(2U))
#define XCP_CRM_DOWNLOAD_NEXT_LEN                       (1U)

/* DOWNLOAD_MAX */
#define XCP_CRO_DOWNLOAD_MAX_MAX_SIZE                   ((uint8)(XCP_MAXCTO_AG - 1U))
#define XCP_CRO_DOWNLOAD_MAX_DATA                       (&XCP_CRO_BYTE(1U))
#define XCP_CRM_DOWNLOAD_MAX_LEN                        (1U)

/* SHORT_DOWNLOAD */
#define XCP_CRO_SHORT_DOWNLOAD_CMD_LEN                  (8U)
#define XCP_CRO_SHORT_DOWNLOAD_SIZE                     (XCP_CRO_BYTE(1U))
#define XCP_CRO_SHORT_DOWNLOAD_EXT                      (XCP_CRO_BYTE(3U))
#define XCP_CRO_SHORT_DOWNLOAD_ADDR                     (XCP_CRO_DWORD(1U))
#define XCP_CRO_SHORT_DOWNLOAD_DATA                     (&XCP_CRO_BYTE(8U))
#define XCP_CRM_SHORT_DOWNLOAD_MAX_SIZE                 ((uint8)((XCP_MAX_CTO - 8U) / XCP_AG))
#define XCP_CRM_SHORT_DOWNLOAD_LEN                      (1U)  /* +XCP_CRO_SHORT_UPLOAD_SIZE */

/* MODIFY_BITS */
#define XCP_CRO_MODIFY_BITS_LEN                         (6U)
#define XCP_CRO_MODIFY_BITS_SHIFT                       (XCP_CRO_BYTE(1U))
#define XCP_CRO_MODIFY_BITS_AND                         (XCP_CRO_WORD(1U))
#define XCP_CRO_MODIFY_BITS_XOR                         (XCP_CRO_WORD(2U))
#define XCP_CRM_MODIFY_BITS_LEN                         (1U)

/* SET_CAL_PAGE */
#define XCP_CRO_SET_CAL_PAGE_LEN                        (4U)
#define XCP_CRO_SET_CAL_PAGE_MODE                       (XCP_CRO_BYTE(1U))
#define XCP_CRO_SET_CAL_PAGE_SEGMENT                    (XCP_CRO_BYTE(2U))
#define XCP_CRO_SET_CAL_PAGE_PAGE                       (XCP_CRO_BYTE(3U))
#define XCP_CRM_SET_CAL_PAGE_LEN                        (1U)

/* GET_CAL_PAGE */
#define XCP_CRO_GET_CAL_PAGE_LEN                        (3U)
#define XCP_CRO_GET_CAL_PAGE_MODE                       (XCP_CRO_BYTE(1U))
#define XCP_CRO_GET_CAL_PAGE_SEGMENT                    (XCP_CRO_BYTE(2U))
#define XCP_CRM_GET_CAL_PAGE_LEN                        (4U)
#define XCP_CRM_GET_CAL_PAGE_PAGE                       (XCP_CRM_BYTE(3U))

/* GET_PAG_PROCESSOR_INFO */
#define XCP_CRO_GET_PAG_PROCESSOR_INFO_LEN              (1U)
#define XCP_CRM_GET_PAG_PROCESSOR_INFO_LEN              (3U)
#define XCP_CRM_GET_PAG_PROCESSOR_INFO_MAX_SEGMENT      (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_PAG_PROCESSOR_INFO_PROPERTIES       (XCP_CRM_BYTE(2U))

/* GET_SEGMENT_INFO */
#define XCP_CRO_GET_SEGMENT_INFO_LEN                    (5U)
#define XCP_CRO_GET_SEGMENT_INFO_MODE                   (XCP_CRO_BYTE(1U))
#define XCP_CRO_GET_SEGMENT_INFO_NUMBER                 (XCP_CRO_BYTE(2U))
#define XCP_CRO_GET_SEGMENT_INFO_MAPPING_INDEX          (XCP_CRO_BYTE(3U))
#define XCP_CRO_GET_SEGMENT_INFO_MAPPING                (XCP_CRO_BYTE(4U))
#define XCP_CRM_GET_SEGMENT_INFO_LEN                    (8U)
#define XCP_CRM_GET_SEGMENT_INFO_MAX_PAGES              (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_SEGMENT_INFO_ADDRESS_EXTENSION      (XCP_CRM_BYTE(2U))
#define XCP_CRM_GET_SEGMENT_INFO_MAX_MAPPING            (XCP_CRM_BYTE(3U))
#define XCP_CRM_GET_SEGMENT_INFO_COMPRESSION            (XCP_CRM_BYTE(4U))
#define XCP_CRM_GET_SEGMENT_INFO_ENCRYPTION             (XCP_CRM_BYTE(5U))
#define XCP_CRM_GET_SEGMENT_INFO_MAPPING_INFO           (XCP_CRM_DWORD(1U))

#define XCP_GET_SEGMENT_BASIC_ADDR_INFO                 (0U)
#define XCP_GET_SEGMENT_STANDARD_INFO                   (1U)
#define XCP_GET_SEGMENT_ADDR_MAPPING_INFO               (2U)

/* GET_PAGE_INFO */
#define XCP_CRO_GET_PAGE_INFO_LEN                       (4U)
#define XCP_CRO_GET_PAGE_INFO_SEGMENT_NUMBER            (XCP_CRO_BYTE(2U))
#define XCP_CRO_GET_PAGE_INFO_PAGE_NUMBER               (XCP_CRO_BYTE(3U))
#define XCP_CRM_GET_PAGE_INFO_LEN                       (3U)
#define XCP_CRM_GET_PAGE_INFO_PROPERTIES                (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_PAGE_INFO_INIT_SEGMENT              (XCP_CRM_BYTE(2U))

/* SET_SEGMENT_MODE */
#define XCP_CRO_SET_SEGMENT_MODE_LEN                    (3U)
#define XCP_CRO_SET_SEGMENT_MODE_MODE                   (XCP_CRO_BYTE(1U))
#define XCP_CRO_SET_SEGMENT_MODE_SEGMENT                (XCP_CRO_BYTE(2U))
#define XCP_CRM_SET_SEGMENT_MODE_LEN                    (1U)

/* GET_SEGMENT_MODE */
#define XCP_CRO_GET_SEGMENT_MODE_LEN                    (3U)
#define XCP_CRO_GET_SEGMENT_MODE_SEGMENT                (XCP_CRO_BYTE(2U))
#define XCP_CRM_GET_SEGMENT_MODE_LEN                    (3U)
#define XCP_CRM_GET_SEGMENT_MODE_MODE                   (XCP_CRM_BYTE(2U))

/* COPY_CAL_PAGE */
#define XCP_CRO_COPY_CAL_PAGE_LEN                       (5U)
#define XCP_CRO_COPY_CAL_PAGE_SRC_SEGMENT               (XCP_CRO_BYTE(1U))
#define XCP_CRO_COPY_CAL_PAGE_SRC_PAGE                  (XCP_CRO_BYTE(2U))
#define XCP_CRO_COPY_CAL_PAGE_DEST_SEGMENT              (XCP_CRO_BYTE(3U))
#define XCP_CRO_COPY_CAL_PAGE_DEST_PAGE                 (XCP_CRO_BYTE(4U))
#define XCP_CRM_COPY_CAL_PAGE_LEN                       (1U)

/* CLEAR_DAQ_LIST */
#define XCP_CRO_CLEAR_DAQ_LIST_LEN                      (4U)
#define XCP_CRO_CLEAR_DAQ_LIST_DAQ                      (XCP_CRO_WORD(1U))
#define XCP_CRM_CLEAR_DAQ_LIST_LEN                      (1U)

/* SET_DAQ_PTR */
#define XCP_CRO_SET_DAQ_PTR_LEN                         (6U)
#define XCP_CRO_SET_DAQ_PTR_DAQ                         (XCP_CRO_WORD(1U))
#define XCP_CRO_SET_DAQ_PTR_ODT                         (XCP_CRO_BYTE(4U))
#define XCP_CRO_SET_DAQ_PTR_IDX                         (XCP_CRO_BYTE(5U))
#define XCP_CRM_SET_DAQ_PTR_LEN                         (1U)

/* WRITE_DAQ */
#define XCP_CRO_WRITE_DAQ_LEN                           (8U)
#define XCP_CRO_WRITE_DAQ_BITOFFSET                     (XCP_CRO_BYTE(1U))
#define XCP_CRO_WRITE_DAQ_SIZE                          (XCP_CRO_BYTE(2U))
#define XCP_CRO_WRITE_DAQ_EXT                           (XCP_CRO_BYTE(3U))
#define XCP_CRO_WRITE_DAQ_ADDR                          (XCP_CRO_DWORD(1U))
#define XCP_CRM_WRITE_DAQ_LEN                           (1U)

/* WRITE_DAQ_MULTIPLE */
#define XCP_CRO_WRITE_DAQ_MULIPLE_LEN                   (8U)
#define XCP_CRO_WRITE_DAQ_MULTIPLE_COMMAND              (XCP_CRO_BYTE(1U))
#define XCP_CRO_WRITE_DAQ_MULTIPLE_NODAQ                (XCP_CRO_BYTE(2U))
#define XCP_CRO_WRITE_DAQ_MULIPLE_BITOFFSET(i)          (XCP_CRO_BYTE(8U + (8U * (i))))
#define XCP_CRO_WRITE_DAQ_MULIPLE_SIZE(i)               (XCP_CRO_BYTE(9U + (8U * (i))))
#define XCP_CRO_WRITE_DAQ_MULIPLE_EXT(i)                (XCP_CRO_BYTE(10U + (8U * (i))))
#define XCP_CRO_WRITE_DAQ_MULIPLE_ADDR(i)               (XCP_CRO_DWORD(1U + (2U * (i))))
#define XCP_CRM_WRITE_DAQ_MULIPLE_LEN                   (1U)

/* SET_DAQ_LIST_MODE */
#define XCP_CRO_SET_DAQ_LIST_MODE_LEN                   (8U)
#define XCP_CRO_SET_DAQ_LIST_MODE_MODE                  (XCP_CRO_BYTE(1U))
#define XCP_CRO_SET_DAQ_LIST_MODE_DAQ                   (XCP_CRO_WORD(1U))
#define XCP_CRO_SET_DAQ_LIST_MODE_EVENTCHANNEL          (XCP_CRO_WORD(2U))
#define XCP_CRO_SET_DAQ_LIST_MODE_PRESCALER             (XCP_CRO_BYTE(6U))
#define XCP_CRO_SET_DAQ_LIST_MODE_PRIORITY              (XCP_CRO_BYTE(7U))
#define XCP_CRM_SET_DAQ_LIST_MODE_LEN                   (6U)
#define XCP_DAQ_LIST_TIMESTAMP                          (0x10U)

/* GET_DAQ_LIST_MODE */
#define XCP_CRO_GET_DAQ_LIST_MODE_LEN                   (4U)
#define XCP_CRO_GET_DAQ_LIST_MODE_DAQ                   (XCP_CRO_WORD(1U))
#define XCP_CRM_GET_DAQ_LIST_MODE_LEN                   (8U)
#define XCP_CRM_GET_DAQ_LIST_MODE_MODE                  (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_DAQ_LIST_MODE_EVENTCHANNEL          (XCP_CRM_WORD(2U))
#define XCP_CRM_GET_DAQ_LIST_MODE_PRESCALER             (XCP_CRM_BYTE(6U))
#define XCP_CRM_GET_DAQ_LIST_MODE_PRIORITY              (XCP_CRM_BYTE(7U))

/* START_STOP_DAQ_LIST */
#define XCP_CRO_START_STOP_LEN                          (4U)
#define XCP_CRO_START_STOP_MODE                         (XCP_CRO_BYTE(1U))
#define XCP_CRO_START_STOP_DAQ                          (XCP_CRO_WORD(1U))
#define XCP_CRM_START_STOP_LEN                          (2U)
#define XCP_CRM_START_STOP_FIRST_PID                    (XCP_CRM_BYTE(1U))
#define XCP_STOP_DAQ_LIST                               (0U)
#define XCP_START_DAQ_LIST                              (1U)
#define XCP_SELECT_DAQ_LIST                             (2U)

/* START_STOP_SYNCH */
#define XCP_CRO_START_STOP_SYNC_LEN                     (2U)
#define XCP_CRO_START_STOP_SYNC_MODE                    (XCP_CRO_BYTE(1U))
#define XCP_CRM_START_STOP_SYNC_LEN                     (1U)
#define XCP_STOP_ALL_DAQ_LIST_SYNCH                     (0U)
#define XCP_START_SELECT_DAQ_LIST_SYNCH                 (1U)
#define XCP_STOP_SELECT_DAQ_LIST_SYNCH                  (2U)

/* GET_DAQ_CLOCK */
#define XCP_CRO_GET_DAQ_CLOCK_LEN                       (1U)
#define XCP_CRM_GET_DAQ_CLOCK_LEN                       (8U)
#define XCP_CRM_GET_DAQ_CLOCK_TIME                      (XCP_CRM_DWORD(1U))

/* READ_DAQ */
#define XCP_CRO_READ_DAQ_LEN                            (1U)
#define XCP_CRM_READ_DAQ_LEN                            (8U)
#define XCP_CRM_READ_DAQ_BITOFFSET                      (XCP_CRM_BYTE(1U))
#define XCP_CRM_READ_DAQ_SIZE                           (XCP_CRM_BYTE(2U))
#define XCP_CRM_READ_DAQ_EXT                            (XCP_CRM_BYTE(3U))
#define XCP_CRM_READ_DAQ_ADDR                           (XCP_CRM_DWORD(1U))

/* GET_DAQ_PROCESSOR_INFO */
#define XCP_CRO_GET_DAQ_PROCESSOR_INFO_LEN              (1U)
#define XCP_CRM_GET_DAQ_PROCESSOR_INFO_LEN              (8U)
#define XCP_CRM_GET_DAQ_PROCESSOR_INFO_PROPERTIES       (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_DAQ_PROCESSOR_INFO_MAX_DAQ          (XCP_CRM_WORD(1U))
#define XCP_CRM_GET_DAQ_PROCESSOR_INFO_MAX_EVENT        (XCP_CRM_WORD(2U))
#define XCP_CRM_GET_DAQ_PROCESSOR_INFO_MIN_DAQ          (XCP_CRM_BYTE(6U))
#define XCP_CRM_GET_DAQ_PROCESSOR_INFO_DAQ_KEY_BYTE     (XCP_CRM_BYTE(7U))

/* GET_DAQ_RESOLUTION_INFO */
#define XCP_CRO_GET_DAQ_RESOLUTION_INFO_LEN             (1U)
#define XCP_CRM_GET_DAQ_RESOLUTION_INFO_LEN             (8U)
#define XCP_CRM_GET_DAQ_RESOLUTION_INFO_GRANULARITY_DAQ (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_DAQ_RESOLUTION_INFO_MAX_SIZE_DAQ    (XCP_CRM_BYTE(2U))
#define XCP_CRM_GET_DAQ_RESOLUTION_INFO_GRANULARITY_STIM  (XCP_CRM_BYTE(3U))
#define XCP_CRM_GET_DAQ_RESOLUTION_INFO_MAX_SIZE_STIM   (XCP_CRM_BYTE(4U))
#define XCP_CRM_GET_DAQ_RESOLUTION_INFO_TIMESTAMP_MODE  (XCP_CRM_BYTE(5U))
#define XCP_CRM_GET_DAQ_RESOLUTION_INFO_TIMESTAMP_TICKS (XCP_CRM_WORD(3U))

/* GET_DAQ_LIST_INFO */
#define XCP_CRO_GET_DAQ_LIST_INFO_LEN                   (4U)
#define XCP_CRO_GET_DAQ_LIST_INFO_DAQ                   (XCP_CRO_WORD(1U))
#define XCP_CRM_GET_DAQ_LIST_INFO_LEN                   (6U)
#define XCP_CRM_GET_DAQ_LIST_INFO_PROPERTIES            (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_DAQ_LIST_INFO_MAX_ODT               (XCP_CRM_BYTE(2U))
#define XCP_CRM_GET_DAQ_LIST_INFO_MAX_ODT_ENTRY         (XCP_CRM_BYTE(3U))
#define XCP_CRM_GET_DAQ_LIST_INFO_FIXED_EVENT           (XCP_CRM_WORD(2U))

/* GET_DAQ_EVENT_INFO */
#define XCP_CRO_GET_DAQ_EVENT_INFO_LEN                  (4U)
#define XCP_CRO_GET_DAQ_EVENT_INFO_EVENT                (XCP_CRO_WORD(1U))
#define XCP_CRM_GET_DAQ_EVENT_INFO_LEN                  (7U)
#define XCP_CRM_GET_DAQ_EVENT_INFO_PROPERTIES           (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_DAQ_EVENT_INFO_MAX_DAQ_LIST         (XCP_CRM_BYTE(2U))
#define XCP_CRM_GET_DAQ_EVENT_INFO_NAME_LENGTH          (XCP_CRM_BYTE(3U))
#define XCP_CRM_GET_DAQ_EVENT_INFO_TIME_CYCLE           (XCP_CRM_BYTE(4U))
#define XCP_CRM_GET_DAQ_EVENT_INFO_TIME_UNIT            (XCP_CRM_BYTE(5U))
#define XCP_CRM_GET_DAQ_EVENT_INFO_PRIORITY             (XCP_CRM_BYTE(6U))

/* FREE_DAQ */
#define XCP_CRO_FREE_DAQ_LEN                            (1U)
#define XCP_CRM_FREE_DAQ_LEN                            (1U)

/* ALLOC_DAQ */
#define XCP_CRO_ALLOC_DAQ_LEN                           (4U)
#define XCP_CRO_ALLOC_DAQ_COUNT                         (XCP_CRO_WORD(1U))
#define XCP_CRM_ALLOC_DAQ_LEN                           (1U)

/* ALLOC_ODT */
#define XCP_CRO_ALLOCODT_LEN                            (3U)
#define XCP_CRO_ALLOCODT_DAQ                            (XCP_CRO_WORD(1U))
#define XCP_CRO_ALLOCODT_COUNT                          (XCP_CRO_BYTE(1U))
#define XCP_CRO_ALLOC_ODT_LEN                           (5U)
#define XCP_CRO_ALLOC_ODT_DAQ                           (XCP_CRO_WORD(1U))
#define XCP_CRO_ALLOC_ODT_COUNT                         (XCP_CRO_BYTE(4U))
#define XCP_CRM_ALLOC_ODT_LEN                           (1U)

/* ALLOC_ODT_ENTRY */
#define XCP_CRO_ALLOC_ODT_ENTRY_LEN                     (6U)
#define XCP_CRO_ALLOC_ODT_ENTRY_DAQ                     (XCP_CRO_WORD(1U))
#define XCP_CRO_ALLOC_ODT_ENTRY_ODT                     (XCP_CRO_BYTE(4U))
#define XCP_CRO_ALLOC_ODT_ENTRY_COUNT                   (XCP_CRO_BYTE(5U))
#define XCP_CRM_ALLOC_ODT_ENTRY_LEN                     (1U)

/* PROGRAM_START */
#define XCP_CRO_PROGRAM_START_LEN                       (1U)
#define XCP_CRM_PROGRAM_START_LEN                       (7U)
#define XCP_CRM_PROGRAM_COMM_MODE_PGM                   (XCP_CRM_BYTE(2U))
#define XCP_CRM_PROGRAM_MAX_CTO_PGM                     (XCP_CRM_BYTE(3U))
#define XCP_CRM_PROGRAM_MAX_BS_PGM                      (XCP_CRM_BYTE(4U))
#define XCP_CRM_PROGRAM_MIN_ST_PGM                      (XCP_CRM_BYTE(5U))
#define XCP_CRM_PROGRAM_QUEUE_SIZE_PGM                  (XCP_CRM_BYTE(6U))

/* PROGRAM_CLEAR */
#define XCP_CRO_PROGRAM_CLEAR_LEN                       (8U)
#define XCP_CRO_PROGRAM_CLEAR_MODE                      (XCP_CRO_BYTE(1U))
#define XCP_CRO_PROGRAM_CLEAR_SIZE                      (XCP_CRO_DWORD(1U))
#define XCP_CRM_PROGRAM_CLEAR_LEN                       (1U)

/* PROGRAM */
#define XCP_CRO_PROGRAM_MAX_SIZE                        ((uint8)((XCP_MAX_CTO - 2U) / XCP_AG))
#define XCP_CRO_PROGRAM_LEN                             (2U)  /* + XCP_CRO_PROGRAM_SIZE */
#define XCP_CRO_PROGRAM_SIZE                            (XCP_CRO_BYTE(1U))
#define XCP_CRO_PROGRAM_DATA                            (&XCP_CRO_BYTE(2U))
#define XCP_CRM_PROGRAM_LEN                             (1U)

/* PROGRAM RESET */
#define XCP_CRO_PROGRAM_RESET_LEN                       (1U)
#define XCP_CRM_PROGRAM_RESET_LEN                       (1U)

/*GET_PGM_PROCESSOR_INFO*/
#define XCP_CRO_GET_PGM_PROCESSOR_INFO_LEN              (1U)
#define XCP_CRM_GET_PGM_PROCESSOR_INFO_LEN              (3U)
#define XCP_CRM_GET_PGM_PROCESSOR_INFO_PROPERTIES       (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_PGM_PROCESSOR_INFO_MAX_SECTOR       (XCP_CRM_BYTE(2U))

/* GET_SECTOR_INFO */
#define XCP_CRO_PROGRAM_GET_SECTOR_INFO_LEN             (3U)
#define XCP_CRO_PROGRAM_GET_SECTOR_INFO_MODE            (XCP_CRO_BYTE(1U))
#define XCP_CRO_PROGRAM_GET_SECTOR_INFO_NUMBER          (XCP_CRO_BYTE(2U))
#define XCP_CRM_PROGRAM_GET_SECTOR_INFO_LEN             (8U)
#define XCP_CRM_PROGRAM_GET_SECTOR_CLEAR_SEQ_NUM        (XCP_CRM_BYTE(1U))
#define XCP_CRM_PROGRAM_GET_SECTOR_PGM_SEQ_NUM          (XCP_CRM_BYTE(2U))
#define XCP_CRM_PROGRAM_GET_SECTOR_PGM_METHOD           (XCP_CRM_BYTE(3U))
#define XCP_CRM_PROGRAM_GET_SECTOR_SECTOR_INFO          (XCP_CRM_DWORD(1U))

/* PROGRAM_PREPARE */
#define XCP_CRO_PROGRAM_PREPARE_LEN                     (4U)
#define XCP_CRO_PROGRAM_PREPARE_SIZE                    (XCP_CRO_WORD(1U))
#define XCP_CRM_PROGRAM_PREPARE_LEN                     (1U)

/* PROGRAM_FORMAT */
#define XCP_CRO_PROGRAM_FORMAT_LEN                      (5U)
#define XCP_CRO_PROGRAM_FORMAT_COMPRESSION_METHOD       (XCP_CRO_BYTE(1U))
#define XCP_CRO_PROGRAM_FORMAT_ENCRYPTION_METHOD        (XCP_CRO_BYTE(2U))
#define XCP_CRO_PROGRAM_FORMAT_PROGRAMMING_METHOD       (XCP_CRO_BYTE(3U))
#define XCP_CRO_PROGRAM_FORMAT_ACCESS_METHOD            (XCP_CRO_BYTE(4U))
#define XCP_CRM_PROGRAM_FORMAT_LEN                      (1U)

/* PROGRAM_NEXT */
#define XCP_CRO_PROGRAM_NEXT_MAX_SIZE                   ((uint8)((XCP_MAX_CTO - 2U) / XCP_AG))
#define XCP_CRO_PROGRAM_NEXT_LEN                        (2U)  /* + size */
#define XCP_CRO_PROGRAM_NEXT_SIZE                       (XCP_CRO_BYTE(1U))
#define XCP_CRO_PROGRAM_NEXT_DATA                       (&XCP_CRO_BYTE(2U))
#define XCP_CRM_PROGRAM_NEXT_LEN                        (3U)
#define XCP_CRM_PROGRAM_NEXT_ERR_SEQUENCE               (XCP_CRM_BYTE(1U))
#define XCP_CRM_PROGRAM_NEXT_SIZE_EXPECTED_DATA         (XCP_CRM_BYTE(2U))

/* PROGRAM_MAX */
#define XCP_CRO_PROGRAM_MAX_MAX_SIZE                    ((uint8)((XCP_MAX_CTO - XCP_AG) / XCP_AG))
#define XCP_CRO_PROGRAM_MAX_DATA                        (&XCP_CRO_BYTE(1U))
#define XCP_CRM_PROGRAM_MAX_LEN                         (1U)

/* PROGRAM_VERIFY */
#define XCP_CRO_PROGRAM_VERIFY_LEN                      (8U)
#define XCP_CRO_PROGRAM_VERIFY_MODE                     (XCP_CRO_BYTE(1U))
#define XCP_CRO_PROGRAM_VERIFY_TYPE                     (XCP_CRO_WORD(1U))
#define XCP_CRO_PROGRAM_VERIFY_VALUE                    (XCP_CRO_DWORD(1U))
#define XCP_CRM_PROGRAM_VERIFY_LEN                      (1U)

/* GET_SLAVE_ID */
#define XCP_CRO_GET_SLAVE_ID_LEN                        (6U)
#define XCP_CRO_GET_SLAVE_ID_SUB_CODE                   (XCP_CRO_BYTE(1U))
#define XCP_CRO_GET_SLAVE_ID_X                          (XCP_CRO_BYTE(2U))
#define XCP_CRO_GET_SLAVE_ID_C                          (XCP_CRO_BYTE(3U))
#define XCP_CRO_GET_SLAVE_ID_P                          (XCP_CRO_BYTE(4U))
#define XCP_CRO_GET_SLAVE_ID_MODE                       (XCP_CRO_BYTE(5U))
#define XCP_CRM_GET_SLAVE_ID_LEN                        (8U)
#define XCP_CRM_GET_SLAVE_ID_X                          (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_SLAVE_ID_C                          (XCP_CRM_BYTE(2U))
#define XCP_CRM_GET_SLAVE_ID_P                          (XCP_CRM_BYTE(3U))
#define XCP_CRM_GET_SLAVE_ID_CAN_ID_CMD_STIM            (XCP_CRM_DWORD(1U))

/* GET_DAQ_ID */
#define XCP_CRO_GET_DAQ_ID_LEN                          (3U)
#define XCP_CRO_GET_DAQ_ID_SUB_CODE                     (XCP_CRO_BYTE(1U))
#define XCP_CRO_GET_DAQ_ID_DAQ                          (XCP_CRO_WORD(1U))
#define XCP_CRM_GET_DAQ_ID_LEN                          (8U)
#define XCP_CRM_GET_DAQ_ID_FIXED                        (XCP_CRM_BYTE(1U))
#define XCP_CRM_GET_DAQ_ID_ID                           (XCP_CRM_DWORD(1U))

/* SET_DAQ_ID */
#define XCP_CRO_SET_DAQ_ID_LEN                          (8U)
#define XCP_CRO_SET_DAQ_ID_SUB_CODE                     (XCP_CRO_BYTE(1U))
#define XCP_CRO_SET_DAQ_ID_DAQ                          (XCP_CRO_WORD(1U))
#define XCP_CRO_SET_DAQ_ID_ID                           (XCP_CRO_DWORD(1U))
#define XCP_CRM_SET_DAQ_ID_LEN                          (1U)

/* SET_SLAVE_PORT */
#define XCP_CRO_SET_SLAVE_PORT_LEN                      (4U)
#define XCP_CRO_SET_SLAVE_PORT_SUB_CODE                 (XCP_CRO_BYTE(1U))
#define XCP_CRO_SET_SLAVE_PORT_PORT                     (XCP_CRO_WORD(1U))

#define XCP_CRM_SET_SLAVE_PORT                          (1U)

/* Implementation */
#if( defined (XCP_ENABLE_SEND_EVENT) && (XCP_ENABLE_NVM_SAVE_DATA == STD_ON) )
#define XCP_EV_BYTE(x)                  (Xcp_DataInformation.eventDataBuff.bytes[x])
#endif

#define XCP_CRO_BYTE(x)                 (pCmd->bytes[x])    /* pcmd: Orders accepted. */
#define XCP_CRO_WORD(x)                 (pCmd->words[x])
#define XCP_CRO_DWORD(x)                (pCmd->dwords[x])
#define XCP_CRM_BYTE(x)                 (Xcp_DataInformation.responseBuff.bytes[x])
#define XCP_CRM_WORD(x)                 (Xcp_DataInformation.responseBuff.words[x])
#define XCP_CRM_DWORD(x)                (Xcp_DataInformation.responseBuff.dwords[x])

#define XCP_MAX_ODT_ENTRY_SIZE          (XCP_MAX_DTO - 1U)

/* XCP Driver Variables, Type Definition. */
/* Return values. */
#define XCP_CMD_OK                      (0U)
#define XCP_CMD_DENIED                  (1U)
#define XCP_CMD_PENDING                 (2U)
#define XCP_CMD_SYNTAX                  (3U)
#define XCP_CMD_BUSY                    (4U)
#define XCP_CMD_UNKNOWN                 (5U)
#define XCP_CMD_OUT_OF_RANGE            (6U)
#define XCP_MODE_NOT_VALID              (7U)
#define XCP_CMD_ERROR                   (0xFFU)

/* Return values for XcpEvent(). */
#define XCP_EVENT_NOP                   (0x00U)   /* Inactive (DAQ not running, Event not configured). */
#define XCP_EVENT_DAQ                   (0x01U)   /* DAQ active. */
#define XCP_EVENT_DAQ_OVERRUN           (0x02U)   /* DAQ queue overflow. */
#define XCP_EVENT_STIM                  (0x04U)   /* STIM active. */
#define XCP_EVENT_STIM_OVERRUN          (0x08U)   /* STIM data not available. */

/* Bitmasks for xcp.sendStatus. */
#define XCP_CRM_REQUEST                 (0x01U)
#define XCP_DTO_REQUEST                 (0x02U)
#define XCP_EVT_REQUEST                 (0x04U)
#define XCP_CRM_PENDING                 (0x10U)
#define XCP_DTO_PENDING                 (0x20U)
#define XCP_EVT_PENDING                 (0x40U)
#define XCP_SEND_PENDING                (XCP_DTO_PENDING | XCP_CRM_PENDING | XCP_EVT_PENDING)
#define XCP_SEND_REQUEST                (XCP_DTO_REQUEST | XCP_CRM_REQUEST | XCP_EVT_REQUEST)

/* Shortcuts */
/* j is absolute odt number. */
#define Xcp_DaqListOdtEntryCount(j)     ((Xcp_DataInformation.pOdt[j].lastOdtEntry - \
                                          Xcp_DataInformation.pOdt[j].firstOdtEntry) + 1U)
#define Xcp_DaqListOdtLastEntry(j)      (Xcp_DataInformation.pOdt[j].lastOdtEntry)
#define Xcp_DaqListOdtFirstEntry(j)     (Xcp_DataInformation.pOdt[j].firstOdtEntry)
#define Xcp_DaqListOdtStimBuffer(j)     (Xcp_DataInformation.pOdt[j].pStimBuffer)

/* n is absolute odtEntry number. */
#define Xcp_OdtEntrySize(n)             (Xcp_DataInformation.pOdtEntrySize[n])
#define Xcp_OdtEntryAddr(n)             (Xcp_DataInformation.pOdtEntryAddr[n])

/* i is daq number. */
#define Xcp_DaqListOdtCount(i)          ((Xcp_DataInformation.daq.daqSizeInfo.daqList[i].lastOdt - \
                                          Xcp_DataInformation.daq.daqSizeInfo.daqList[i].firstOdt) + 1U)
#define Xcp_DaqListLastOdt(i)           (Xcp_DataInformation.daq.daqSizeInfo.daqList[i].lastOdt)
#define Xcp_DaqListFirstOdt(i)          (Xcp_DataInformation.daq.daqSizeInfo.daqList[i].firstOdt)
#define Xcp_DaqListFirstPid(i)          (Xcp_DataInformation.daq.daqSizeInfo.daqList[i].firstOdt)
#define Xcp_DaqListFlags(i)             (Xcp_DataInformation.daq.daqSizeInfo.daqList[i].flags)
#define Xcp_DaqListEventChannel(i)      (Xcp_DataInformation.daq.daqSizeInfo.daqList[i].eventChannel)
#define Xcp_DaqListPrescaler(i)         (Xcp_DataInformation.daq.daqSizeInfo.daqList[i].prescaler)
#define Xcp_DaqListCycle(i)             (Xcp_DataInformation.daq.daqSizeInfo.daqList[i].cycle)

/* x is current queue. */
#define Xcp_StimOdt(x)       (((Xcp_StimDtoType*)(&Xcp_DataInformation.pQueueStim[(x)*Xcp_DataInformation.queueUnitSize]))->stimOdt)
#define Xcp_StimData(x)      (((Xcp_StimDtoType*)(&Xcp_DataInformation.pQueueStim[(x)*Xcp_DataInformation.queueUnitSize]))->bytes)

#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
#define Xcp_pDataQueue(daq,x)          ((Xcp_DtoDataType*)(Xcp_DataInformation.pQueue[daq] + ((x)*Xcp_DataInformation.queueUnit[daq])))
#else  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
#define Xcp_pDataQueue(x)              ((Xcp_DtoDataType*)(&Xcp_DataInformation.pQueue[(x)*Xcp_DataInformation.queueUnit]))
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */

#define XCP_ADDRESS_CHECK(addr, size, mem_start, mem_size) \
    ((addr >= mem_start) && ((addr + size) <= (mem_start + mem_size)))

#define IS_WRITE_ALIGN(addr, size, align_len)    (((size) >= (align_len)) && (0U == (((uint32)(addr)) % (align_len))))
#define SET_VALUE_ALIGN(val, type, align_len)    ((type)(((val) + (align_len) - 1U)&((type)~((uint32)(align_len) - 1U))))

/* Word converted to byte. */
#define Xcp_WordGetHiByte(data)                ((uint8)(((uint16)data & 0xFF00U) >> 8U))
#define Xcp_WordGetLoByte(data)                ((uint8)((uint16)data & 0x00FFU))

#if( defined XCP_INVALID_XCP_PDU_ID )
#error XCP_INVALID_XCP_PDU_ID redefinition
#endif
/* Invalid XCP PDU ID. */
#define XCP_INVALID_XCP_PDU_ID                   (0xFFU)

#if( defined XCP_INVALID_CONNECTION_ID )
#error XCP_INVALID_CONNECTION_ID redefinition
#endif
/* Invalid connection ID. */
#define XCP_INVALID_CONNECTION_ID                (0xFFU)


#if( defined XCP_CONNECTION_OVER_CAN )
#error XCP_CONNECTION_OVER_CAN redefinition
#endif
/** \brief The type of connection is over CAN. */
#define XCP_CONNECTION_OVER_CAN                  (0U)

#if( defined XCP_CONNECTION_OVER_CANFD )
#error XCP_CONNECTION_OVER_CANFD redefinition
#endif
/** \brief The type of connection is over CANFD. */
#define XCP_CONNECTION_OVER_CANFD                (1U)

#if( defined XCP_CONNECTION_OVER_ETHERNET )
#error XCP_CONNECTION_OVER_ETHERNET redefinition
#endif
/** \brief The type of connection is over Ethernet. */
#define XCP_CONNECTION_OVER_ETHERNET             (2U)

#if( defined XCP_DIRECTION_TX )
#error XCP_DIRECTION_TX redefinition
#endif
/** \brief The type of connection is over Ethernet. */
#define XCP_DIRECTION_TX                         (1U)

#if( defined XCP_DIRECTION_RX )
#error XCP_DIRECTION_RX redefinition
#endif
/** \brief The type of connection is over Ethernet. */
#define XCP_DIRECTION_RX                         (2U)

#if( defined XCP_WORKING_PAGE )
#error XCP_WORKING_PAGE redefinition
#endif
/** \brief The type of connection is over Ethernet. */
#define XCP_WORKING_PAGE                         (1U)

#if( defined REFERENCE_PAGE )
#error REFERENCE_PAGE redefinition
#endif
/** \brief The type of connection is over Ethernet. */
#define REFERENCE_PAGE                           (0U)

#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
#define XCP_RESERVED_QUEUE_SIZE                  (3U)
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */

#define XCP_ETH_DAQ_DTO_LEN_OFFSET               (0U)
#define XCP_ETH_DAQ_DTO_CNT_OFFSET               (2U)
#define XCP_ETH_DAQ_DTO_DAT_OFFSET               (4U)
#define XCP_ETH_DAQ_DTO_HEAD_LEN                 (4U)

#define XCP_SEND_QUEUE_ALIGN_SIZE                (4U)

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
#define XCP_CALRAM_ADDR(index)                   (Xcp_InitRam_Addr[index].addr_wp)
#define XCP_CALFLASH_ADDR(index)                 (Xcp_InitRam_Addr[index].addr_rp)
#define XCP_CALRAM_SIZE(index)                   (Xcp_InitRam_Addr[index].len)
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT )
#define XCP_SINGCALRAM_SIZE                      (4096U)
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT */

#define XCP_CHECK_EVENTADDR(x)                   ( (x >= (uint32)&XcpEventName[XCP_INDEX_0][XCP_INDEX_0]) && \
                                                 (x <= ((uint32)&XcpEventName[XCP_INDEX_0][XCP_INDEX_0] + sizeof(XcpEventName))) )
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
#define XCP_CHECK_STRUCTURE_RAMADDR(x)           ( (x >= (Xcp_Addr_Stru[XCP_INDEX_0].addr_wp)) && \
                                                 (x < (Xcp_Addr_Stru[XCP_INDEX_0].addr_wp + Xcp_Addr_Stru[XCP_INDEX_0].len)) )
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/* Xcp Connection State type definition. */
typedef enum
{
    XCP_STATE_CONNECTED = 0U,   /* Defines connection status of XCP module for connected. */
    XCP_STATE_DISCONNECTED,     /* Defines connection status of XCP module for disconnected. */
    XCP_STATE_RESUME            /* Defines connection status of XCP module for resume mode. */
}Xcp_StateType;

/* Xcp Connection Status type definition. */
typedef struct
{
    Xcp_StateType state;            /* Reserve, connection state. */
    Xcp_BusType busType;         /* Xcp Transport Layer Bus type. */
    uint8 connectionId;             /* The ID of the selected connection. */
}Xcp_ConnectionStatusType;

/* XCP Packet Type Definition. */
typedef struct{
    uint32 length;
    uint8 bytes[XCP_MAX_DTO];
}Xcp_DtoDataType;


typedef uint32 Xcp_TimestampType;  /* <! Timestamp used during DAQ measurement. */

typedef struct{
    uint8 stimDaq;
    uint8 stimOdt;
    Xcp_TimestampType stimTimeStamp;     /* STIM timetamp. */
#if( XCP_MAX_DTO > XCP_U8_MASK )
    uint8 bytes[XCP_U8_MASK];
#else
    uint8 bytes[XCP_MAX_DTO];
#endif  /* XCP_MAX_DTO > XCP_U8_MASK */
}Xcp_StimDtoType;

#if( XCP_ONETHERNET_ENABLE == STD_ON )
typedef struct{
    uint32 length;
    uint8 bytes[XCP_ETHERNET_MAX_DTO + XCP_VALUE_4];
}Xcp_EthDtoType;
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */

typedef union{
    /* There might be a loss of up to 3 bytes. */
    uint8 bytes[ ((XCP_MAX_CTO + 3U) & 0xFFCU) ];
    uint16 words[ ((XCP_MAX_CTO + 3U) & 0xFFCU) / 2U ];
    uint32 dwords[ ((XCP_MAX_CTO + 3U) & 0xFFCU) / 4U ];
}Xcp_CtoType;

/* ODT */
/* Size must be even. */
#ifdef XCP_ENABLE_DAQ

typedef struct{
    uint16 firstOdtEntry;       /* Absolute */
    uint16 lastOdtEntry;        /* Absolute */
}Xcp_OdtNumType;

/* DAQ list */
typedef struct{
    uint16 lastOdt;
    uint16 firstOdt;
    /* bit 0: alternating, bit1: direction, bit4: timestamp, bit5: pid_off, bit6: running, bit7: resume. */
    uint8 flags;
    uint8 eventChannel;
#if( XCP_PRESCALER_SUPPORTED == STD_ON )
    uint8 prescaler;
    uint8 cycle;
#endif  /* XCP_PRESCALER_SUPPORTED == STD_ON */
}Xcp_DaqListInfoType;

/* Dynamic DAQ list structures. */
typedef struct{
    union{
        uint8 daqMemSize[XCP_DAQMEMSIZE];
        Xcp_DaqListInfoType daqList[XCP_MIN_DAQ + XCP_DAQ_COUNT];
    }daqSizeInfo;
    uint8 stimDateBuffer[XCP_DAQMEMSIZE_STIM];
    uint8 daqOverload;
    uint8 daqCount;
    uint16 odtCount;                /* Absolute count. */
    uint16 odtEntryCount;          /* Absolute count. */
    uint8 eventDaq[XCP_MAX_EVENT];  /* Event-daq association array. */
}Xcp_DaqType;
/* DAQ Lists, Type Definition. */
#endif  /* #ifdef XCP_ENABLE_DAQ */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
/* Ram definition. */
typedef struct{
    uint32 ramStaAddr;
    uint32 ramCurAddr;
    uint32 ramLen;
}Xcp_RamType;
/* Ram list. */
typedef struct{
    uint8 ramCnt;
    uint8 ramNum;
    Xcp_RamType* ramCfg;
}Xcp_RamListType;

typedef struct{
    uint32 calVecAddr;
    uint32 calVecWpAddr;
    uint32 calVecRpAddr;
    uint32 calVecLen;
}Xcp_VectInfoType;

typedef struct{
    uint16 vectCnt;
    Xcp_VectInfoType* vectInfo;
}Xcp_VectListType;

typedef struct{
    uint16 downSize;
    uint32 copyAddrSrc;
    uint32 copyAddrDest;
    uint32 copyLen;
    uint8 copyReqState;
    const uint8* downData;
}Xcp_DownloadCopyType;
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */

/* Checksum, Type Definition. */
typedef uint8 tXcpChecksumAddType;     /* Data type (width) of the data to be added. */
#if( XCP_ADD12 == XCP_CHECKSUM_TYPE )
typedef uint16 tXcpChecksumSumType;    /* Data type (width) of the actually checksum. */
#elif( XCP_ADD11 == XCP_CHECKSUM_TYPE )
typedef uint8 tXcpChecksumSumType;     /* Data type (width) of the actually checksum. */
#elif( XCP_CRC32== XCP_CHECKSUM_TYPE )
typedef uint32 tXcpChecksumSumType;
#endif

typedef uint8 ErrorCodeType;

typedef struct {
    Xcp_CtoType responseBuff;           /* RES,ERR Message buffer. */
    uint32 respDataLen;                 /* RES,ERR Message length. */
    uint16 sessionId;                   /* Record Session ID. */
    uint8 storeFlag;                    /* Store NVM's block flag. */
    uint8 pageInd;                      /* Flag of WP or RP. */
#if( defined (XCP_ENABLE_SEND_EVENT) && (XCP_ENABLE_NVM_SAVE_DATA == STD_ON) )
    Xcp_CtoType eventDataBuff;          /* EV,SERV Message buffer. */
    uint8 eventDataLen;                 /* EV,SERV Message length. */
#endif  /* (XCP_ENABLE_SEND_EVENT) && ( XCP_ENABLE_NVM_SAVE_DATA == STD_ON ) */

    uint8 sessionStatus;
    uint8* mta;                        /* Memory Transfer Address. */
#if( XCP_ENABLE_SEED_KEY == STD_ON )
    uint8 protectionStatus;            /* Resource Protection Status. */
#endif  /* XCP_ENABLE_SEED_KEY == STD_ON */

#if( XCP_ENABLE_CHECKSUM == STD_ON )
    uint32 checkSumSize;               /* Counter for checksum calculation. */
    tXcpChecksumSumType checkSum;      /* Actual checksum. */
    uint8 crc32Flag;
#endif  /* XCP_ENABLE_CHECKSUM == STD_ON */

#if( XCP_BLOCK_UPLOAD == STD_ON )
    uint8 nextDataBlockSize;
#endif  /* XCP_BLOCK_UPLOAD == STD_ON */
#if( XCP_BLOCK_DOWNLOAD == STD_ON )
    uint8 nextDownloadSize;
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */
    /* Dynamic DAQ list structures
    This structure should be stored in resume mode. */
#ifdef XCP_ENABLE_DAQ
    uint8 maxOdt;  /* The maximum number of odts in a daq list. */
    Xcp_DaqType daq;
    Xcp_OdtNumType* pOdt;
    uint8** pOdtEntryAddr;
    uint8* pOdtEntrySize;

    /* Transmit Queue. */
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )

#if ( XCP_ENABLE_SEND_QUEUE == STD_ON )
    uint8* pQueue[XCP_EVENT_CHANNEL_NUM];    /* Queue data pointer. */
    uint8 queueSize[XCP_EVENT_CHANNEL_NUM];  /* Number of packets. */
    uint8 queueUnit[XCP_EVENT_CHANNEL_NUM];  /* Size of one DTO. */
    uint8 queueLen[XCP_EVENT_CHANNEL_NUM];   /* Number of queued packets. */
    uint8 queueRp[XCP_EVENT_CHANNEL_NUM];    /* Index of the packet being processed. */
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
    /* Transmit Status. */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
    uint8 sendStatus[XCP_TXPDU_LIST];
#endif  /*  XCP_ENABLE_SEND_QUEUE == STD_ON */

#else  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
    uint8* pQueue;    /* Queue data pointer. */
    uint16 queueSize;  /* Number of packets. */
    uint8 queueUnit;  /* Size of one DTO. */
    uint8 queueWp;    /* Number of queued packets (Wp). */
    uint8 queueRp;    /* Index of the packet being processed. */
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */

#ifdef XCP_ENABLE_STIM_QUEUE
    uint8* pQueueStim;    /* STIM location in the cache. */
    uint16 queueSizeStim;  /* The number of STIMs that can be allocated to a queue. */
    uint8 queueLenStim;
    uint8 queueUnitSize;  /* Memory size of DTO. */
    uint8 queueRpStim;    /* The STIM position of the current operation in the queue. */
#endif  /* #ifdef XCP_ENABLE_STIM_QUEUE */

    /* Transmit Status. */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
    uint8 sendStatus;
    uint8 sendStatusReqTimCnt;
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
    /* Pointer for SET_DAQ_PTR */
    uint16 daqListPtr;   /* ODT_entry ptr. */
    uint16 daqListNum;   /* DAQ list index. */
#endif  /* #ifdef XCP_ENABLE_DAQ */
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
    Xcp_RamListType* ramPtr;
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */
}XCP_InfoDataType;

typedef struct {
    uint8 eventChanlNumber;                   /* Event corresponding to mapping. */
    uint8 eventChannelActive;                 /* Configured time parameter executable flag. */
    uint32 eventChannelMaxCycCnt;             /* The total counter value of the current event. */
    uint32 eventChannelCurCnt;                /* The currently executing counter. */
}XcpEventMonitorType;

/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
#define XCP_START_SEC_VAR_INIT
#include "Xcp_MemMap.h"
extern VAR(Xcp_ConnectionStatusType, XCP_VAR_INIT) Xcp_ConnectionStatus;
#define XCP_STOP_SEC_VAR_INIT
#include "Xcp_MemMap.h"

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
/*
********************************************************************************
*    Global Functions
********************************************************************************
*/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
#if( XCP_VERSION_INFO_API == STD_ON )
extern FUNC(void, XCP_CODE) Xcp_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, XCP_APPL_DATA) versioninfo
);
#endif  /* XCP_VERSION_INFO_API == STD_ON */

extern FUNC(void, XCP_CODE) Xcp_Init(void);
extern FUNC(void, XCP_CODE) Xcp_Command
(
    uint8 connectionId,
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST) avlpCommand
);

extern FUNC(uint8, XCP_CODE) Xcp_Event(uint8 avcEvent);
#if( XCP_MULTIPDUIDSUPPORT == STD_OFF )
extern FUNC(uint8, XCP_CODE) Xcp_StimEvent(uint8 daq);
extern FUNC(uint8, XCP_CODE) Xcp_DaqEvent(uint8 daq);
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_OFF */

extern FUNC(uint8, XCP_CODE) Xcp_Background(void);
extern FUNC(void, XCP_CODE) Xcp_Disconnect(void);
extern FUNC(Std_ReturnType, XCP_CODE) Xcp_SendCrm(void);
#if ( XCP_MULTIPDUIDSUPPORT == STD_ON )
extern FUNC(uint8, XCP_CODE) Xcp_SendCallBack(uint8 eventid);
#else
extern FUNC(uint8, XCP_CODE) Xcp_SendCallBack(void);
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */

#ifdef XCP_ENABLE_DAQ

#if ( XCP_MULTIPDUIDSUPPORT == STD_ON )
extern FUNC(Std_ReturnType, XCP_CODE) Xcp_SendDto
(
    uint8 eventid,
    P2CONST(Xcp_DtoDataType, AUTOMATIC, XCP_APPL_CONST)astpDto
);
#else
extern FUNC(Std_ReturnType, XCP_CODE) Xcp_SendDto
(
    P2CONST(Xcp_DtoDataType, AUTOMATIC, XCP_APPL_CONST)astpDto
);
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
#endif  /* #ifdef XCP_ENABLE_DAQ */

extern FUNC(void, XCP_CODE) Xcp_MemSet
(
    P2VAR(void, AUTOMATIC, XCP_APPL_DATA)destAddr,
    uint16 num, uint8 byte
);
extern FUNC(void, XCP_CODE) Xcp_MemCpy8
(
    P2VAR(void, AUTOMATIC, XCP_APPL_DATA) dest,
    P2CONST(void, AUTOMATIC, XCP_APPL_CONST)src,
    uint32 num
);
extern FUNC(void, XCP_CODE) Xcp_MemClr
(
    P2VAR(void, AUTOMATIC, XCP_APPL_DATA)straddr,
    uint16 num
);
extern FUNC(void, XCP_CODE) Xcp_MainFunction(void);
extern FUNC(void, XCP_CODE) Xcp_Det_ErrorReport(uint8 apiId, uint8 errorId);
extern FUNC(void, XCP_CODE) Xcp_InterruptDisable(void);
extern FUNC(void, XCP_CODE) Xcp_InterruptEnable(void);

#if( XCP_ONCAN_ENABLE == STD_ON )
extern FUNC(void, XCP_CODE) CanXcp_Init(void);
extern FUNC(void, XCP_CODE) CanXcp_MainFunction(void);

#if ( XCP_MULTIPDUIDSUPPORT == STD_ON )
extern FUNC(Std_ReturnType, XCP_CODE) CanXcp_Send
(
    uint8 pduid, uint32 len,
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST) msg
);
#else
extern FUNC(Std_ReturnType, XCP_CODE) CanXcp_Send
(
    uint32 len,
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST) msg
);
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */

extern FUNC(uint8, XCP_CODE) CanXcp_GetRxMsg(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_CONST) avcpDlc,
    P2VAR(uint32, AUTOMATIC, XCP_APPL_CONST) avlpId,
    P2VAR(uint32, AUTOMATIC, XCP_APPL_CONST) avlpData
);
#endif  /* XCP_ONCAN_ENABLE == STD_ON */

#if( XCP_ONETHERNET_ENABLE == STD_ON )
extern FUNC(Std_ReturnType, XCP_CODE) Xcp_SendEthDaq
(
    P2CONST(Xcp_EthDtoType, AUTOMATIC, XCP_APPL_CONST)astpDto
);
extern FUNC(void, XCP_CODE) EthXcp_Init(void);
extern FUNC(void, XCP_CODE) EthXcp_MainFunction(void);
extern FUNC(Std_ReturnType, XCP_CODE) EthXcp_Send(uint16 len, P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST) msg);
extern FUNC(uint8, XCP_CODE) EthXcp_GetRxMsg(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_CONST) avcpDlc,
    P2VAR(uint32, AUTOMATIC, XCP_APPL_CONST) avlpId,
    P2VAR(uint32, AUTOMATIC, XCP_APPL_CONST) avlpData
);
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
extern FUNC(void, XCP_CODE) Xcp_CalVectRegister
(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_CONST)* ptr,
    uint16 size
);
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */

#if( (XCP_ENABLE_SEND_QUEUE == STD_OFF) && (XCP_MULTIPDUIDSUPPORT == STD_OFF) )
extern FUNC(void, XCP_CODE) Xcp_SendDtoMode(P2VAR(Xcp_DtoDataType, AUTOMATIC, XCP_APPL_DATA)astpDto);
#endif  /* (XCP_ENABLE_SEND_QUEUE == STD_OFF) && (XCP_MULTIPDUIDSUPPORT == STD_OFF) */

#if ( XCP_MULTIPDUIDSUPPORT == STD_OFF )
extern FUNC(void, XCP_CODE) Xcp_StimDataProcess
(
    P2CONST(uint8, AUTOMATIC, XCP_APPL_DATA) stimData,
    uint32 dateLen
);
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_OFF */

#if( (XCP_EVENT_CHANNEL_NUM > XCP_VALUE_0)\
    && ((XCP_EVENT_BASE_PERIOD_SELECT == XCP_BASE_PERIOD_MAINFUNCTION)\
    || (XCP_EVENT_BASE_PERIOD_SELECT == XCP_BASE_PERIOD_USER_DEFINED)) )
extern FUNC(void, XCP_CODE) XcpEventCycleProcess(void);
extern FUNC(void, XCP_CODE) Xcp_ProcessEvents(uint8 event);
extern FUNC(void, XCP_CODE) XcpEventCycleInit(void);
LOCAL_INLINE FUNC(void, XCP_CODE)XcpEventCycleCalcule
(
    float32 uintConverter,
    uint8 eventIndex
);
#endif

extern FUNC(ErrorCodeType, XCP_CODE) Xcp_MtaCheckValid(uint32 addr, uint32 size, uint8 accessScope, uint8 accessType);

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#endif  /* XCP_H */
