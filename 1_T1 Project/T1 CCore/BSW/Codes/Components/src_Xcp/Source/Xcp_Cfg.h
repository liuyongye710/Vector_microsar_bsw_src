/*
********************************************************************************
*
* File name: Xcp_Cfg.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: yong.zhang/2018.12.28
* Change: New created
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date: fangtao/2020.08.11
* Change: Delete event name.
* Cause: Bugfix
********************************************************************************
* Version: 3.0
* Author/Date: FangT/2021.03.03
* Change: Add checksum and Multi pudid functions.
* Cause: Optimization
********************************************************************************
* Version: 3.1
* Author/Date: lqiao/2022.09.16
* Change: Add struct CanXcpFrame_st
* Cause: New
********************************************************************************
* Version: 3.2
* Author/Date: zxt/2022.12.27
* Change: Delete #define XCP_DaqMemSize
* Cause: Bugfix
********************************************************************************
* Version: 3.3
* Author/Date: lqiao/2024.03.14
* Change: Delete XCP_ONCDD_ENABLE、XCP_ONETHERNET_ENABLE、XCP_ONFLEXRAY_ENABLE、
          XCP_PRESCALER_SUPPORTED、XCP_SUPPRESS_TX_SUPPORT
* Cause:Optimization.
********************************************************************************
* Version: 3.4
* Author/Date: lqiao/2024.03.26
* Change: Resume XCP_ONETHERNET_ENABLE
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: lqiao/2024.05.16
* Change: Delete CALRAM_ADDR、CALFLASH_ADDR、CALRAM_SIZE.
          Modify and add new define.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: lqiao/2024.05.27
* Change: Delete ХСР_CHECKSUMBLOCKSIZE.
* Cause: Optimization
********************************************************************************
* Version: 3.7
* Author/Date: KangJH/2024.06.20
* Change: Modify coding specification problems.
* Cause: Update
********************************************************************************
*/
#ifndef XCP_CFG_H_
#define XCP_CFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define XCP_STATIONIDLENGTH             (7U) /* Slave device identification length */
#define XCP_STATIONIDSTRING             "NEUXCP"

/* Standard commands */
#define XCP_ENABLE_COMM_MODE_INFO /* Get communication mode info */

/* Synchronous Data Acquisition (DAQ) */
#define XCP_ENABLE_DAQ  /* Daq */
#define XCP_ENABLE_DAQ_PRESCALER          /* Daq Prescaler */
#define XCP_ENABLE_DAQ_OVERRUN_INDICATION /* Daq OverRun Indication */

/* Synchronous Data Stimulation (STIM) */
#define XCP_ENABLE_STIM
#define XCP_ENABLE_STIM_QUEUE

/* Add a macro with multiple daqs under one channel */
#define XCP_ENABLE_MULDAQ_EVENT

/* Page switching */
#define XCP_ENABLE_CALIBRATION_PAGE                 /* Calibration Page */
#define XCP_MAXSEGMENT                         (1U) /* Segment */
#define XCP_MAXPAGES                           (2U)

/* Verify Algorithm Type */
#define XCP_ADD11                              (1U)
#define XCP_ADD12                              (2U)
#define XCP_CRC32                              (3U)

/* Programming */

/* Motorola */
#define XCP_CPUTYPE_BIGENDIAN

#define XCP_STACKSIZE                          (10U)

/* Xcp/XcpGeneral */
#define DAQ_DEFAULT                            (0x00U)
#define DAQ_DYNAMIC                            (0x01U)
#define DAQ_STATIC                             (0x02U)

#define XCP_ID_TYPE_DEFAULT                        (0U)
#define XCP_ID_TYPE_ABSOLUTE                       (1U)
#define XCP_ID_TYPE_RELATIVE_BYTE                  (2U)
#define XCP_ID_TYPE_RELATIVE_WORD                  (3U)
#define XCP_ID_TYPE_RELATIVE_WORD_ALIGNED          (4U)

#define XCPTS_NO_TIME_STAMP                    (0U)
#define XCPTS_ONE_BYTE                         (1U)
#define XCPTS_TWO_BYTE                         (2U)
#define XCPTS_NOT_ALLOWED                      (3U)
#define XCPTS_FOUR_BYTE                        (4U)

#define XCP_RTE_CAL_METHOD_INITRAM             (0U)
#define XCP_RTE_CAL_METHOD_SINGLEPT            (1U)
#define XCP_CAL_METHOD_MMU                     (2U)
#define XCP_CAL_METHOD_OVERLAY                 (3U)
#define XCP_RTE_CAL_METHOD_STRUCTUREPT         (8U)

#define XCP_ACCESS_TYPE_READ                   ((uint8)(0x01U<<0U))
#define XCP_ACCESS_TYPE_WRITE                  ((uint8)(0x01U<<1U))
#define XCP_ACCESS_TYPE_READ_WRITE             (XCP_ACCESS_TYPE_READ|XCP_ACCESS_TYPE_WRITE)

#define XCP_ACCESS_SCOPE_CALIBRATION           ((uint8)(0x01U<<0U))
#define XCP_ACCESS_SCOPE_DAQ_STIM              ((uint8)(0x01U<<1U))
#define XCP_ACCESS_SCOPE_ALL                   (XCP_ACCESS_SCOPE_CALIBRATION|XCP_ACCESS_SCOPE_DAQ_STIM)

#define XCP_MULTIPDUIDSUPPORT                  (STD_OFF)

#define XCP_TIMESTAMP_UINT_DEFAULT             (0U)

#define XCP_ENABLE_SEND_EVENT
#define XCPDAQCONFIGTYPE                       (DAQ_DYNAMIC)
#define XCP_DAQ_COUNT                          (3U)
#define XCP_DEV_ERROR_DETECT                   (STD_ON)
#define XCP_FLASH_PROGRAMING_ENABLE            (STD_ON)
#define XCP_IDENTIFICATION_FIELD_TYPE          (XCP_ID_TYPE_ABSOLUTE)
#define XCP_MAINFUNCTION_PERIOD                (10U)
#define XCP_MAX_EVENT                          (3U)
#define XCP_MIN_DAQ                            (0U)
#define XCP_ODT_COUNT                          (127U)
#define XCP_ODT_ENTRY_SIZE_DAQ                 (4U)
#define XCP_ODT_ENTRY_SIZE_STIM                (0U)
#define XCP_ONCAN_ENABLE                       (STD_ON)
#define XCP_ONETHERNET_ENABLE                  (STD_OFF)
#define XCP_TIMESTAMP_TICKS                    (0U)
#define XCP_TIMESTAMP_UNIT                     ((uint8)(DAQ_TIMESTAMP_UNIT_10MS))
#define XCP_VERSION_INFO_API                   (STD_ON)
#define XCP_COUNTER_REF                        (SYSTEMTIMER_CORE2)
#define XCP_NVRAM_BLOCK_REF                    (0U)
#define XCP_DAQMEMSIZE                         (5120U)
#define XCP_ENABLE_SEND_QUEUE                  (STD_ON)
#define XCP_ENABLE_NVM_SAVE_DATA               (STD_OFF)
#define XCP_ENABLE_SEED_KEY                    (STD_OFF)/* WangM */
#define XCPBLOCK_SIZE                          (2U)
#define XCPBLOCK_MIN_ST                        (0U)
#define XCP_CHECKSUM_TYPE                      (XCP_ADD12)
#define XCP_BLOCK_DOWNLOAD                     (STD_OFF)
#define XCP_BLOCK_UPLOAD                       (STD_OFF)
#define XCP_ENABLE_CHECKSUM                    (STD_OFF)
#define RTECALIBRATIONSUPPORT                  (2U)
#define TRANSMITTIMEOUT                        (3U)
#define XCP_BASE_PERIOD_NULL                   (0U)
#define XCP_BASE_PERIOD_MAINFUNCTION           (1U)
#define XCP_BASE_PERIOD_USER_DEFINED           (2U)
#define XCP_EVENT_BASE_PERIOD_SELECT           (XCP_BASE_PERIOD_MAINFUNCTION)
#define XCP_EVENT_BASE_PERIOD                  (XCP_MAINFUNCTION_PERIOD)
#define XCP_CAN_MAX_CTO                        (8U)
#define XCP_CANFD_MAX_CTO                      (8U)
#define XCP_ETHERNET_MAX_CTO                   (8U)
#define XCP_MAX_CTO                            (XCP_ETHERNET_MAX_CTO)
#define XCP_CAN_MAX_DTO                        (8U)
#define XCP_CANFD_MAX_DTO                      (8U)
#define XCP_ETHERNET_MAX_DTO                   (8U)
#define XCP_MAX_DTO                            (XCP_ETHERNET_MAX_DTO)
#define XCP_CHECKSUMBLOCKSIZE                  (2048U)
#define XCP_SEND_ODTNUM                        (7U)
#define XCP_DAQMEMSIZE_STIM                    (2048U)
#define XCP_ON_TCP_ENABLE                      (STD_OFF)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
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

#endif  /* XCP_CFG_H_ */

