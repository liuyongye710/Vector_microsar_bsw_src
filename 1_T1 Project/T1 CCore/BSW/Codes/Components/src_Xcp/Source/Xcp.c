/*
********************************************************************************
*
* File name: Xcp.c
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: SunPF/2018.07.10
* Change: New created
* Cause: New
********************************************************************************
* Version: 2.0
* Author/Date: FangT/2020.01.17
* Change: Modify part of the code
* 1. Remove the number of devil in the code.
* 2. Modify local variables and structures that have no meaning.
* 3. If there is a goto statement, remove it.
* 4. function can only have one exit. (Misra-c)
* 5. Add comments as appropriate and use English.
* Cause: Update
********************************************************************************
* Version: 2.1
* Author/Date: FangT/2020.02.25
* Change: Modify part of the code
* Cause: Update
********************************************************************************
* Version: 2.2
* Author/Date: FangT/2020.03.12
* Change: Modify code based on configuration.
* Cause: Update
********************************************************************************
* Version: 3.0
* Author/Date: zhangyong/2020.03.27
* Change: Nothing
* Cause: Update to V3.0
********************************************************************************
* Version: 3.1
* Author/Date: zhangyong/2020.05.29
* Change: Delete index = XCP_FIVE;
* Cause: Update to V3.1
********************************************************************************
* Version: 3.2
* Author/Date: FangT/2020.08.11
* Change:
* 1. Configuration items available.
* 2. Implement block transfer function.
* 3. Add time stamp function.
* Cause: Bugfix
********************************************************************************
* Version: 3.3
* Author/Date: FangT/2020.08.21
* Change:
* 1. Remove continue from the code.
* 2. Add Det function.
* Cause: Bugfix
********************************************************************************
* Version: 3.4
* Author/Date: FangT/2020.09.15
* Change: Modify the function name according to the AUTOSAR specification, add
*         MemMap.
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: FangT/2020.10.12
* Change: Change Xcp_Main to Xcp_MainFunction.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: FangT/2021.03.03
* Change: Add checksum and Multi pudid functions.
* Cause: Optimization
********************************************************************************
* Version: 3.7
* Author/Date: FangT/2021.06.30
* Change: Modify code specifications.
* Cause: Optimization
********************************************************************************
* Version: 3.8
* Author/Date: FangT/2021.07.14
* Change: Add header file SchM_Xcp.h.
* Cause: Optimization
********************************************************************************
* Version: 3.9
* Author/Date: FangT/2021.07.19
* Change: Modify ApplXcpGetTimestamp local parameters.
* Cause: Optimization
********************************************************************************
* Version: 3.10
* Author/Date: FangT/2021.08.18
* Change: Modify the code specification.
* Cause: Optimization
********************************************************************************
* Version: 3.11
* Author/Date: FangT/2021.08.31
* Change: Eliminate compilation warnings.
* Cause: Optimization
********************************************************************************
* Version: 3.12
* Author/Date: FangT/2021.09.01
* Change: Eliminate compilation warnings.
* Cause: Optimization
********************************************************************************
* Version: 3.13
* Author/Date: FangT/2021.10.20
* Change: Modify the ether reply question.
* Cause: Optimization
********************************************************************************
* Version: 3.14
* Author/Date: FangT/2021.10.29
* Change: Modify coding style.
* Cause: Optimization
********************************************************************************
* Version: 3.15
* Author/Date: FangT/2021.11.1
* Change: Modify coding style.
* Cause: Optimization
********************************************************************************
* Version: 3.16
* Author/Date: FangT/2021.11.3
* Change: 1.Modify the timestamp acquisition problem.
*         2.Add relative Odt identification function.
* Cause: Optimization
********************************************************************************
* Version: 3.17
* Author/Date: FangT/2021.11.23
* Change:Resolve eth count errors.
* Cause: Optimization
********************************************************************************
* Version: 3.18
* Author/Date: FangT/2021.12.6
* Change: 1.Timestamp judgment condition plus priority brackets.
*         2.Modify the default page.
* Cause: Optimization
********************************************************************************
* Version: 3.19
* Author/Date: FangT/2021.12.13
* Change: 1.Modify the address offset mode and request the DAQ information again
*         after the page is switched. The address is incorrect.
*         2.Reinitialize the work page when disconnected.
*         3.Xcp_Init_cal_page change to Xcp_InitCalPage.
* Cause: Optimization
********************************************************************************
* Version: 3.19
* Author/Date: FangT/2021.12.17
* Change: 1.Add type conversion when pointer data is used.
*         2.Modify the length of the single-pointer RAM buffer to be configurable.
* Cause: Optimization
********************************************************************************
* Version: 3.20
* Author/Date: FangT/2021.12.23
* Change: Single-pointer calibration, the address will not be
*         incremented when the read/write range is exceeded.
* Cause: Optimization
********************************************************************************
* Version: 3.21
* Author/Date: FangT/2022.03.01
* Change: 1.ODT data transmission is not connected.
*         2.Alloc Odt Modify the error judgment order.
* Cause: Optimization
********************************************************************************
* Version: 3.22
* Author/Date: FangT/2022.03.16
* Change: 1.Modify the byte order of the Ethernet sending data header
*         2.Change the send length to uint32 type.
*         3.Modify code specification.
* Cause: Optimization
********************************************************************************
* Version: 3.23
* Author/Date: ShiRong/2022.06.21
* Change: Clear compile warnings.
* Cause: Optimization
********************************************************************************
* Version: 3.24
* Author/Date: ShiRong/2022.09.16
* Change: Add XcpOnCANFD function.
* Cause: Update
********************************************************************************
* Version: 3.25
* Author/Date: ShiRong/2022.10.12
* Change: 1.Modifying the Comment Mode.
* Cause: Update
********************************************************************************
* Version: 3.26
* Author/Date: ShiRong/2022.11.3
* Change: 1.Modifying the four bite time stamp.
* Cause: Update
********************************************************************************
* Version: 3.27
* Author/Date: ShiRong/2022.11.28
* Change: 1.Modify the bug with mismatched parentheses.
*         2.Add XCP_DAQMEMSIZE Configuration Item
* Cause: Update
********************************************************************************
* Version: 3.28
* Author/Date: ShiRong/2022.12.22
* Change: The modified ethereal measurement cannot exceed 255.
* Cause: Update
********************************************************************************
* Version: 3.29
* Author/Date: ShiRong/2023.02.09
* Change: 1.Add STIM function.
*         2.Add structure calibration method.
*         3.Add the observation method of collecting while sending.
* Cause: Update
********************************************************************************
* Version: 3.30
* Author/Date: ShiRong/2023.02.13
* Change: 1.Delete redundant comments.
* Cause: Update
********************************************************************************
* Version: 3.31
* Author/Date: ShiRong/2023.02.13
* Change: 1.Remove compilation warnings.
* Cause: Update
********************************************************************************
* Version: 3.32
* Author/Date: ShiRong/2023.03.09
* Change: 1.Modify the data processing of STIM function.
* Cause: Bugfix
********************************************************************************
* Version: 3.33
* Author/Date: ShiRong/2023.03.13
* Change: 1.Remove warning.
* Cause: Optimization
********************************************************************************
* Version: 3.34
* Author/Date: ShiRong/2023.03.21
* Change: 1.Modify the data type for the STIM function to calculate the queue
*           size.
*         2.Modify some logic of the STIM function.
*         3.Enable XCP_ ODT_ ENTRY_ SIZE_ Functions of STIM macros.
* Cause: Bugfix
********************************************************************************
* Version: 3.35
* Author/Date: ShiRong/2023.04.16
* Change: Add security algorithm functionality.
* Cause: Update
********************************************************************************
* Version: 3.36
* Author/Date: ShiRong/2023.05.06
* Change: 1.Add Block Transfer Mode.
*         2.Remove excess code.
* Cause: Update
********************************************************************************
* Version: 3.37
* Author/Date: ShiRong/2023.05.12
* Change: 1.Add storage RAM scaling to NVM functionality.
* Cause: Update
********************************************************************************
* Version: 3.38
* Author/Date: ShiRong/2023.05.16
* Change: The issue of modifying the polyspace.
* Cause: Optimization.
********************************************************************************
* Version: 3.39
* Author/Date: ShiRong/2023.05.19
* Change: 1.Add error replies related to security algorithms.
*         2.Fix timestamp adaptation byte alignment issues with STIM
*           functionality.
* Cause: Bugfix
********************************************************************************
* Version: 3.40
* Author/Date: ShiRong/2023.05.23
* Change: Modifying NVM Configuration Reference Issues.
* Cause: Bugfix
********************************************************************************
* Version: 3.41
* Author/Date: ShiRong/2023.05.31
* Change: The issue of missing address retrieval in modifying STIM timestamp
*           code writing.
* Cause: Bugfix
********************************************************************************
* Version: 3.42
* Author/Date: ShiRong/2023.06.25
* Change: Modifying single pointer calibration byte alignment issues.
* Cause: Bugfix
********************************************************************************
* Version: 3.43
* Author/Date: ShiRong/2023.08.01
* Change: 1.Add verification algorithms for XCP_ADD11 and XCP_CRC32.
*         2.Add flash writing function.
*         3.Add overlay calibration function.
* Cause: Update
********************************************************************************
* Version: 3.44
* Author/Date: ShiRong/2023.08.02
* Change: Add sending confirmation timeout judgment function.
* Cause: Update
********************************************************************************
* Version: 3.45
* Author/Date: ShiRong/2023.08.04
* Change: Modify compilation issues caused by validation enabled configuration
*         items.
* Cause: Update
********************************************************************************
* Version: 3.46
* Author/Date: ShiRong/2023.08.16
* Change: Modifying Compilation Warning Issues.
* Cause: Update
********************************************************************************
* Version: 3.47
* Author/Date: ShiRong/2023.08.17
* Change: 1.Modifying compilation issues when seed is enabled.
*         2.The sending confirmation time affects the block transmission
*           function.
* Cause: Update
********************************************************************************
* Version: 3.48
* Author/Date: ShiRong/2023.08.28
* Change: 1.The sending confirmation time affects the block transmission
*           function.
* Cause: Bugfix
********************************************************************************
* Version: 3.49
* Author/Date: ShiRong/2023.09.26
* Change: 1.Optimize observation cycle execution logic.
*         2.Clear Compilation Warnings.
* Cause: Bugfix
********************************************************************************
* Version: 3.50
* Author/Date: ChenQJ/2023.10.31
* Change: Fix compile warning.
* Cause: Bugfix
********************************************************************************
* Version: 3.51
* Author/Date: LinZhC/2023.12.14
* Change: 1.Modify the implementation methods of the functions
*           XcpEventCycleCalcule,XcpEventCycleInit,XcpEventCycleProcess.
*         2.Increase the compilation condition for calling the 
*           XcpEventCycleProcess function in Xcp_MainFunction.
*         3.Modified polyspace red warning: Modify the parameter type of the Xcp 
*           Command function.
* Cause: Bugfix
********************************************************************************
* Version: 3.52
* Author/Date: LinZhC/2024.01.10
* Change: 1.Modified compatibility of multi-bus and multi-PDU configurations.
*           The following changes have been modify:
*       (1) Resolve compilation problems when XCP_MULTIPDUIDSUPPORT=ON.
*       (2) The Xcp_CanGetStatus and Xcp_CanCommandTimeCounter variables were
*           moved from xcp.c to this file.
*       (3) The Xcp_MainFunction,Xcp_Send,Xcp_SendDtoFromQueue function adds
*           processing logic for different buses.
*       (4) Added the Xcp_ConnectionStatus variable to record the currently
*           connected bus information.
*       (5) The XCP_MAX_CTO, XCP_MAX_DTO, XCP_ODT_ENTRYS_COUNT,
*           XCP_TIMESTAMP_TYPE macros are changed to variables in the parameter
*           structure Xcp_ConnectionCfg. When switching to a different bus
*           connection, these variables will obtain the corresponding
*           configuration value.
*       (6) Modify the pQueueStim, pQueue operation logic in the 
*           Xcp_DataInformation structure, using queueUnit to record the DTO 
*            size of different buses.
*       (7) Re-initialize STIM queue parameters and reallocate memory after
*           successful connection(includes switching bus or PDU).
*         2.Modified QAC, Polyspace warnings and issues.The following changes 
*           have been modify:
*       (1) Xcp_CalPage and Xcp_WorkingPage are changed to macro definitions.
*       (2) The data parameter of the Xcp_Send,Xcp_SendDto,Xcp_SendEthDaq
*           function is changed to const.
*       (3) The Xcp_DataInformation.mta(in Whole file), dtoi (in the 
*           Xcp_SendDtoFromQueue function),Xcp_StimData(in stimData function)
*           pointer arithmetic is changed to take the address of the 
*           corresponding subscript element.
*       (4) The data parameters of Xcp_MemSet, Xcp_MemCpy8, Xcp_MemClr
*           functions are changed to void type, and the function implementation
*           is modified. and And remove the data type cast of the argument when
*           this function is applied.
*       (5) Xcp_ReadMta,Xcp_SendDtoFromQueue,Xcp_SendDtoMode improves the
*           if-else statement structure. and the Xcp_Command improves the
*           switch-break statement structure.
*       (6) "while( checksumSize )"change to "while( checksumSize > XCP_VALUE_0 )"
*       (7) The Xcp_Event,Xcp_DaqEvent function defines entrySize as U8 with a
*           risk of overflow, so it is changed to U16.
*       (8) Eliminate the devil numbers in Xcp_DaqEvent and Xcp_Event.
*       (9) Call a function that has a return value but does not use its return
*           value, so add void to modify it.
* Cause: Update
********************************************************************************
* Version: 3.53
* Author/Date: LinZhC/2024.02.26
* Change: 1.Modify the value to a functional macro.
*         2.Compatible with older configurations.
*         3.Fix compile warning.
* Cause: Update
********************************************************************************
* Version: 3.54
* Author/Date: LinZhC/2024.03.11
* Change: 1.#if...#endif appending.
*         2.fixed an issue with memsize calculation of DAQ queue.
*         3.fixed logical issues with security unlocking.
*         4.fixed and optimized logical issues with queue sending.
*         5.fixed an issue with QAC/Plyspace code check.
* Cause: Update
********************************************************************************
* Version: 3.55
* Author/Date: LinZhC/2024.04.01
* Change: 1.solve compilation problems.
*         2.If the checksum algorithm is CRC32, check the datasize.
*         3.If xcp reports an error, the running DAQ is stopped.
*         4.modify coding specification problems.
* Cause: Update
********************************************************************************
* Version: 3.56
* Author/Date: KangJH/2024.05.15
* Change: 1.Support the SHORT_DOWNLOAD command.
*         2.Support memory access function, Before calibrating or reading data,
*           it is necessary to check the access permissions of the address.
*         3.modify coding specification problems.
* Cause: Update
********************************************************************************
* Version: 3.57
* Author/Date: KangJH/2024.05.28
* Change: 1.Improve access permission functionality.
*         2.Set negative response code for Xcp_CC_ShortDownload function.
*         3.Add code comments to the Xcp_CC_SetDaqListMode function.
* Cause: Update
********************************************************************************
* Version: 3.58
* Author/Date: KangJH/2024.06.20
* Change: 1.Modify coding specification problems.
*         2.Add Memmap segment definition.
* Cause: Update
********************************************************************************
* Version: 3.59
* Author/Date: KangJH/2024.07.19
* Change: 1.Modify the DISCONNECT command and CONNECT command response message.
*         2.Replace the name of the Xcp_StimDate function.
*         3.Fix compile warning.
* Cause: Update
********************************************************************************
* Version: 3.60
* Author/Date: KangJH/2024.07.27
* Change: 1.Add negative response message sending conditions.
*         2.Set the address for MTA in the Xcp_CC_ShortDownload function.
* Cause: Bugfix
********************************************************************************
* Version: 3.61
* Author/Date: KangJH/2024.08.08
* Change: 1.Use the NeuLib.h library.
*         2.Delete Xcp_MemCpy32 function.
* Cause: Bugfix
********************************************************************************
* Version: 3.62
* Author/Date: KangJH/2024.08.12
* Change: 1.Add address offset in Xcp_CC_WriteDaq function.
*         2.Set the response message length based on the return value of the
*           Xcp_ReadMta function.
* Cause: Bugfix
********************************************************************************
* Version: 3.63
* Author/Date: KangJH/2024.08.12
* Change: Add address check in the OverLay calibration method.
* Cause: Bugfix
********************************************************************************
* Version: 3.64
* Author/Date: KangJH/2024.08.12
* Change: 1.Add address offset to the STIM function of the single-pointed method.
*         2.If the address is outside the range, data cannot be uploaded
*           (single pointed method,structure pointed method).
* Cause: Bugfix
********************************************************************************
* Version: 3.65
* Author/Date: KangJH/2024.08.26
* Change: Clear data information when executing the disconnect command.
* Cause: Bugfix
********************************************************************************
* Version: 3.66
* Author/Date: KangJH/2024.08.27
* Change: Modify the negative response code of the SHORT_DOWNLOAD command and
*         structure calibration.
* Cause: Bugfix
********************************************************************************
* Version: 3.67
* Author/Date: KangJH/2024.08.27
* Change: Add address offset to the STIM function of the structure method.
* Cause: Bugfix
********************************************************************************
* Version: 3.68
* Author/Date: KangJH/2024.08.30
* Change: 1.Add current page judgment in the STIM function.
*         2.Change clearing Xcp_DataInformation to clearing responseBuff
*           when executing the disconnect command.
* Cause: Bugfix
********************************************************************************
* Version: 3.69
* Author/Date: KangJH/2024.09.02
* Change: Add judgment for reading RAM addresses.
*         (single pointed method,structure pointed method).
* Cause: Bugfix
********************************************************************************
* Version: 3.70
* Author/Date: KangJH/2024.09.10
* Change: After completing the ODT transmission, set Xcp_EthDaqTxConfirmEnable
*         to true.
* Cause: Bugfix
********************************************************************************
* Version: 3.71
* Author/Date: KangJH/2024.09.18
* Change: Modify the check conditions for address access permissions of the
*         checksum function.
* Cause: Bugfix
********************************************************************************
* Version: 3.72
* Author/Date: KangJH/2024.09.30
* Change: Modify the coding specification.
* Cause: Optimization
********************************************************************************
* Version: 3.73
* Author/Date: KangJH/2024.10.10
* Change: Fix compile issues.
* Cause: Bugfix
********************************************************************************
* Version: 3.74
* Author/Date: KangJH/2024.10.12
* Change: Modify the encoding specification issue.
* Cause: Optimization
********************************************************************************
* Version: 3.75
* Author/Date: KangJH/2024.10.14
* Change: When obtaining the remaining part of seed in Get_Seed function, firstly
*         save the length of the remaining data.
* Cause: Bugfix
********************************************************************************
* Version: 3.76
* Author/Date: KangJH/2024.10.24
* Change: 1.Increase the available memory for DAQ measurement.
*         2.Support configuring the number of ODTs sent in one TASK cycle.
* Cause: Update
********************************************************************************
* Version: 3.77
* Author/Date: KangJH/2024.10.25
* Change: Cancel the cast of the local variable queueSizeStim in the
*         Xcp_AllocStimQueueMemory function.
* Cause: Update
********************************************************************************
* Version: 3.78
* Author/Date: KangJH/2024.10.26
* Change: Optimize STIM functionality.
* Cause: Update
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Xcp.h"
#include "NeuLib.h"
#if( XCP_ONCAN_ENABLE == STD_ON )
#include "CanXcp.h"
#endif  /* XCP_ONCAN_ENABLE == STD_ON */
#if( XCP_ONETHERNET_ENABLE == STD_ON )
#include "EthXcp.h"
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
#include "Os.h"
#include "SchM_Xcp.h"

#if( XCP_DEV_ERROR_DETECT == STD_ON )
#include "Det.h"
#endif  /* XCP_DEV_ERROR_DETECT == STD_ON */

#if( RTECALIBRATIONSUPPORT != XCP_CAL_METHOD_MMU )
#include "Rte.h"
#include "Rte_Type.h"
#endif  /* RTECALIBRATIONSUPPORT != XCP_CAL_METHOD_MMU */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
#include "Calibration.h"
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/*
********************************************************************************
*    Local Types
********************************************************************************
*/
/*
********************************************************************************
*    Local Variables
********************************************************************************
*/
#define XCP_START_SEC_VAR_INIT
#include "Xcp_MemMap.h"
VAR(Xcp_ConnectionStatusType, XCP_VAR_INIT) Xcp_ConnectionStatus = {
    XCP_STATE_DISCONNECTED,
    XCP_BUS_NULL,
    XCP_INVALID_CONNECTION_ID
};
static VAR(uint8, XCP_VAR_INIT) Xcp_ActionDoneFlag[XCP_BLOCK_NUM + XCP_VALUE_1] = {FALSE};
static VAR(uint8, XCP_VAR_INIT) Xcp_StationId[XCP_STATIONIDLENGTH] = XCP_STATIONIDSTRING;
static VAR(boolean, XCP_VAR_INIT) Xcp_SendFlag = TRUE;
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
static VAR(uint8, XCP_VAR_INIT) Xcp_OdtNumber = XCP_INIT_0;
static VAR(uint8, XCP_VAR_INIT) Xcp_DaqNumber = XCP_INIT_0;
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
#if( XCP_ENABLE_NVM_SAVE_DATA == STD_ON )
static VAR(uint8, XCP_VAR_INIT) Xcp_ReadBlockDone = FALSE;
#endif  /* XCP_ENABLE_NVM_SAVE_DATA == STD_ON */
#if( XCP_ENABLE_SEED_KEY == STD_ON )
static VAR(uint16, XCP_VAR_INIT) Xcp_SafeLen = XCP_INIT_0;
static VAR(uint16, XCP_VAR_INIT) Xcp_SafeAddLen = XCP_INIT_0;
/* Indicates that the host receives a request to obtain seeds. */
static VAR(boolean, XCP_VAR_INIT) Xcp_SafeFlag = FALSE;
static VAR(uint8, XCP_VAR_INIT) Xcp_SafeResoure = XCP_INIT_0;
#endif  /* XCP_ENABLE_SEED_KEY == STD_ON */
/* Single pointer calibration data. */
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT )
#if( XCP_ENABLE_CHECKSUM == STD_ON )
static VAR(boolean, XCP_VAR_INIT) Xcp_ChecksumFlag = FALSE;
#endif  /* XCP_ENABLE_CHECKSUM == STD_ON */
/* The data needs to be generated in the calibration RAM area. */
static VAR(uint8, XCP_VAR_INIT) Xcp_CalibGroupParaRamBuf[XCP_SINGCALRAM_SIZE] = {0U};
static P2VAR(uint8, XCP_VAR_INIT, XCP_APPL_DATA) Xcp_CalibGroupPtCnt = &Xcp_CalibGroupParaRamBuf[0];
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
static VAR(uint8, XCP_VAR_INIT) Xcp_MapPageIdx = XCP_INIT_0;
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM */
#define XCP_STOP_SEC_VAR_INIT
#include "Xcp_MemMap.h"

#define XCP_START_SEC_VAR_NO_INIT
#include "Xcp_MemMap.h"
static VAR(XCP_InfoDataType, XCP_VAR_NO_INIT) Xcp_DataInformation;

#if( XCP_ENABLE_SEND_QUEUE == STD_OFF )
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
static VAR(Xcp_DtoDataType, XCP_VAR_NO_INIT) Xcp_DtoData;
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
static VAR(Xcp_DtoDataType, XCP_VAR_NO_INIT) Xcp_DtoDataInfo;
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_OFF */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
static VAR(Xcp_Addr_st, XCP_VAR_NO_INIT) Xcp_RemapAddr[XCP_REMAPPING_CNT];
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM */

#if( XCP_ENABLE_SEED_KEY == STD_ON )
static VAR(uint8, XCP_VAR_NO_INIT) Xcp_ResourceMode;
#endif  /* XCP_ENABLE_SEED_KEY == STD_ON */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
static VAR(Xcp_VectListType, XCP_VAR_NO_INIT) Xcp_VectList;
static VAR(Xcp_DownloadCopyType, XCP_VAR_NO_INIT) Xcp_DownLoadCopyState;
static VAR(uint32, XCP_VAR_NO_INIT) Xcp_CalRamInfoMem[XCP_INDEX_5];
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */

#if( (XCP_EVENT_CHANNEL_NUM > XCP_VALUE_0)\
    && ((XCP_EVENT_BASE_PERIOD_SELECT == XCP_BASE_PERIOD_MAINFUNCTION)\
    || (XCP_EVENT_BASE_PERIOD_SELECT == XCP_BASE_PERIOD_USER_DEFINED)) )
static VAR(XcpEventMonitorType, XCP_VAR_NO_INIT) XcpEventchannelMonitor[XCP_EVENT_CHANNEL_NUM];
#endif
#define XCP_STOP_SEC_VAR_NO_INIT
#include "Xcp_MemMap.h"

/*
********************************************************************************
*    Local Constants
********************************************************************************
*/
/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
static FUNC(void, XCP_CODE) Xcp_RecordError
(
    uint8 err
);
static FUNC_P2VAR(uint8, XCP_APPL_DATA, XCP_CODE) Xcp_GetPointer
(
    uint8 extAddr,uint32 addr
);
static FUNC(uint8, XCP_CODE) Xcp_WriteMta
(
    uint8 size,
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST)data
);
static FUNC(uint8, XCP_CODE) Xcp_ReadMta
(
    uint8 size,
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA)data
);
#if( defined (XCP_ENABLE_SEND_EVENT) && (XCP_ENABLE_NVM_SAVE_DATA == STD_ON) )
static FUNC(Std_ReturnType, XCP_CODE) Xcp_SendEv(void);
#endif  /* defined (XCP_ENABLE_SEND_EVENT) && ( XCP_ENABLE_NVM_SAVE_DATA == STD_ON ) */

#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
static FUNC(void, XCP_CODE) Xcp_QueueInit(void);

#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
static FUNC(uint8, XCP_CODE) Xcp_SendDtoFromQueue(uint8 eventid);
#else
static FUNC(uint8, XCP_CODE) Xcp_SendDtoFromQueue(void);
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */

#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */

#ifdef XCP_ENABLE_DAQ
static FUNC(void, XCP_CODE) Xcp_FreeDaq(void);
static FUNC(uint8, XCP_CODE) Xcp_AllocMemory(void);
static FUNC(uint8, XCP_CODE) Xcp_AllocDaq(uint8 daqCount);
static FUNC(uint8, XCP_CODE) Xcp_AllocOdt(uint8 daq, uint8 odtCount);
static FUNC(uint8, XCP_CODE) Xcp_AllocOdtEntry
(
    uint8 daq, uint8 odt, uint8 odtEntryCount
);
static FUNC(void, XCP_CODE) Xcp_StartDaq(uint8 daq);
static FUNC(void, XCP_CODE) Xcp_StartAllSelectedDaq(void);
static FUNC(void, XCP_CODE) Xcp_StopDaq(uint8 daq);
static FUNC(void, XCP_CODE) Xcp_StopAllSelectedDaq(void);
static FUNC(void, XCP_CODE) Xcp_StopAllDaq(void);
#endif  /* #ifdef XCP_ENABLE_DAQ */

#ifdef XCP_ENABLE_STIM
static FUNC(uint8, XCP_CODE) Xcp_AllocStimQueueMemory(void);
#endif  /* #ifdef XCP_ENABLE_STIM */

static FUNC(void, XCP_CODE) Xcp_CC_Sync(void);

#ifdef XCP_ENABLE_COMM_MODE_INFO
static FUNC(void, XCP_CODE) Xcp_CC_GetCommModeInfo(void);
#endif  /* #ifdef XCP_ENABLE_COMM_MODE_INFO */

static FUNC(void, XCP_CODE) Xcp_CC_Disconnect(void);
static FUNC(void, XCP_CODE) Xcp_CC_GetID
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_GetStatus(void);

#if( XCP_ENABLE_SEED_KEY == STD_ON )
static FUNC(void, XCP_CODE) Xcp_CC_GetSeed
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_UnLock
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
#endif  /* XCP_ENABLE_SEED_KEY == STD_ON */

#ifdef XCP_ENABLE_CALIBRATION_PAGE
static FUNC(void, XCP_CODE) Xcp_CC_SetCalpage
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_GetCalPage
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_GetPagProcessorInfo(void);
#endif  /* #ifdef XCP_ENABLE_CALIBRATION_PAGE */

static FUNC(void, XCP_CODE) Xcp_CC_GetSegmentInfo
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_GetPageInfo
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);

#ifdef XCP_ENABLE_PAGE_COPY
static FUNC(void, XCP_CODE) Xcp_CC_CopyCalPage
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
#endif  /* #ifdef XCP_ENABLE_PAGE_COPY */

static FUNC(void, XCP_CODE) Xcp_CC_SetMta
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_Download
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
#if( XCP_BLOCK_DOWNLOAD == STD_ON )
static FUNC(void, XCP_CODE) Xcp_CC_DownloadNext
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */
static FUNC(void, XCP_CODE) Xcp_CC_DownloadMax
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_ShortDownload
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_UpLoad
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_ShortUplod
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);

#if( XCP_ENABLE_CHECKSUM == STD_ON )
static FUNC(void, XCP_CODE) Xcp_CC_BuildCheckSum
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
#endif  /* XCP_ENABLE_CHECKSUM == STD_ON */

#ifdef XCP_ENABLE_DAQ
static FUNC(void, XCP_CODE) Xcp_CC_GetDaqProcessorInfo(void);
static FUNC(void, XCP_CODE) Xcp_CC_GetDaqResolutionInfo(void);
static FUNC(void, XCP_CODE) Xcp_CC_GetDaqEventInfo
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_FreeDaq(void);
static FUNC(void, XCP_CODE) Xcp_CC_AllocDaq
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_AllocOdt
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_AllocOdtEntry
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_GetDaqListMode
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_SetDaqListMode
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_SetDaqPtr
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_WriteDaq
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_StartStopDaqList
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_StartStopSynch
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_GetDaqClock(void);
#endif  /* #ifdef XCP_ENABLE_DAQ */

#if( XCP_FLASH_PROGRAMING_ENABLE == STD_ON )
static FUNC(void, XCP_CODE) Xcp_CC_Program_Start(void);
static FUNC(void, XCP_CODE) Xcp_CC_Program_Clear
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
static FUNC(void, XCP_CODE) Xcp_CC_Program
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
#if( XCP_BLOCK_DOWNLOAD == STD_ON )
static FUNC(void, XCP_CODE) Xcp_CC_Program_Next
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */
static FUNC(void, XCP_CODE) Xcp_CC_Program_Max
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
#endif  /* XCP_FLASH_PROGRAMING_ENABLE == STD_ON */
#if( XCP_ENABLE_NVM_SAVE_DATA == STD_ON )
static FUNC(void, XCP_CODE) Xcp_CC_Set_Request
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
);
#endif  /* XCP_ENABLE_NVM_SAVE_DATA == STD_ON */

#if( (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT) && (XCP_ENABLE_CHECKSUM == STD_ON) )
static FUNC(void, XCP_CODE) Xcp_SinglePtrChecksum(uint32 checksumSize);
#endif  /* (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT) && (XCP_ENABLE_CHECKSUM == STD_ON) */
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT )
static FUNC(Std_ReturnType, XCP_CODE) Xcp_ModifyEntry(
    uint32 calibAddress,
    uint16 calibLength,
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA)calibGroupData
);
static FUNC(Std_ReturnType, XCP_CODE) Xcp_CalibParaRead(
    uint32 calibAddress,
    uint16 calibLength,
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA)calibGroupData
);
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT */

#if( (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM) && (XCP_ENABLE_CHECKSUM == STD_ON) )
static FUNC(void, XCP_CODE) Xcp_AddressRelocationChecksum(uint32 checksumSize);
#endif  /* (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM) && (XCP_ENABLE_CHECKSUM == STD_ON) */
#ifdef XCP_ENABLE_PAGE_COPY
static FUNC(uint8, XCP_CODE) ApplXcpCopyCalPage
(
    uint8 srcSeg, uint8 srcPage, uint8 dstSeg, uint8 dstPage
);
static FUNC(void, XCP_CODE) Xcp_CopyMemCpy
(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA)dest,
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST)src,
    uint16 num
);
#endif  /* #ifdef XCP_ENABLE_PAGE_COPY */

static FUNC(void, XCP_CODE) Xcp_InitCalPage(void);

#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
static FUNC(Std_ReturnType, XCP_CODE) Xcp_Send
(
    uint8 pduid,
    uint32 avcLen,
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST)avcpMsg
);
#else
static FUNC(Std_ReturnType, XCP_CODE) Xcp_Send
(
    uint32 avcLen,
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST)avcpMsg
);
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */

#if( (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT) && (XCP_ENABLE_CHECKSUM == STD_ON) )
static FUNC(void, XCP_CODE) Xcp_StructurePtChecksum
(
    uint32 checksumSize
);
#endif  /* (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT) && (XCP_ENABLE_CHECKSUM == STD_ON) */
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
static FUNC(void, XCP_CODE) Xcp_CalVectReset
(
    P2VAR(Xcp_VectListType, AUTOMATIC, XCP_APPL_DATA) vectPtr
);

static FUNC(uint16, XCP_CODE) Xcp_CalVectSearch
(
    P2VAR(Xcp_VectListType, AUTOMATIC, XCP_APPL_DATA) vectPtr,
    uint32 addrReq
);

static FUNC(uint8, XCP_CODE) Xcp_CalDownLoadHandle
(
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST) data,
    uint16 size
);

static FUNC(uint8, XCP_CODE) Xcp_CalUpLoadHandle
(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA) data,
    uint8 size
);

static FUNC(void, XCP_CODE) Xcp_CalMemInit(void);

static FUNC(void, XCP_CODE) Xcp_ReqCopy
(
    uint32 srcAddr,
    uint32 desAddr,
    uint32 size
);
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */

#ifdef XCP_ENABLE_CALIBRATION_PAGE
static FUNC(uint8, XCP_CODE) ApplXcpSetCalPage
(
    uint8 segment,
    uint8 page,
    uint8 mode
);
static FUNC(uint8, XCP_CODE) ApplXcpGetCalPage(uint8 avcSegment, uint8 avcMode);
#endif  /* #ifdef XCP_ENABLE_CALIBRATION_PAGE */

static FUNC(Xcp_TimestampType, XCP_CODE) ApplXcpGetTimestamp(void);

#if( XCP_ENABLE_NVM_SAVE_DATA == STD_ON )
static FUNC(uint8, XCP_CODE) Xcp_ActionForBlock
(
    uint8 mode
);
#endif  /* XCP_ENABLE_NVM_SAVE_DATA == STD_ON */
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

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

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
/*
********************************************************************************
* Function Name: Xcp_CalVectRegister
*
* Explanation: Register the calibration partition.
*
* param: ptr: The address of the partition start address.
*        size: The amount of data in the calibration partition, in bytes.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_CalVectRegister
(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_CONST)* ptr,
    uint16 size
)
{
    uint16 idx;
    Xcp_VectListType* vectListptr;
    Xcp_RamListType* ramPtr;

    vectListptr = &Xcp_VectList;
    ramPtr = Xcp_DataInformation.ramPtr;

    idx = (vectListptr->vectCnt)++;
    vectListptr->vectInfo[idx].calVecAddr = (uint32)ptr;
    vectListptr->vectInfo[idx].calVecWpAddr = (uint32)*ptr;
    vectListptr->vectInfo[idx].calVecRpAddr = (uint32)*ptr;
    vectListptr->vectInfo[idx].calVecLen = (uint32)size;

    ramPtr->ramCfg[ramPtr->ramNum].ramCurAddr += (uint32)sizeof(Xcp_VectInfoType);
}

/*
********************************************************************************
* Function Name: Xcp_CalVectReset
*
* Explanation: Reset the calibration partition.
*
* param: Vect_ptr: The partition start address.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_CalVectReset
(
    P2VAR(Xcp_VectListType, AUTOMATIC, XCP_APPL_DATA) vectPtr
)
{
    uint16 vectidx;
    uint32* calVecAddr;
    Xcp_RamListType* ramPtr;

    ramPtr = Xcp_DataInformation.ramPtr;

    for( vectidx = XCP_INDEX_0; vectidx < vectPtr->vectCnt; vectidx++ )
    {
        calVecAddr = (uint32*)(vectPtr->vectInfo[vectidx].calVecAddr);
        *calVecAddr = vectPtr->vectInfo[vectidx].calVecRpAddr;
        vectPtr->vectInfo[vectidx].calVecWpAddr = vectPtr->vectInfo[vectidx].calVecRpAddr;
    }

    ramPtr->ramCfg[ramPtr->ramNum].ramCurAddr = (uint32)&(vectPtr->vectInfo[vectidx]);
}

/*
********************************************************************************
* Function Name: Xcp_CalVectSearch
*
* Explanation: Find the partition index of the calibration address.
*
* param: vectPtr: The partition start address.
*        addrReq: The calibration address.
*
* retval: vectIdx: The partition index.
********************************************************************************
*/
FUNC(uint16, XCP_CODE) Xcp_CalVectSearch
(
    P2VAR(Xcp_VectListType, AUTOMATIC, XCP_APPL_DATA) vectPtr,
    uint32 addrReq
)
{
    uint16 vectIdx;

    for( vectIdx = XCP_INDEX_0; vectIdx < vectPtr->vectCnt; vectIdx++ )
    {
        if( (addrReq >= vectPtr->vectInfo[vectIdx].calVecRpAddr) &&
            (addrReq < (vectPtr->vectInfo[vectIdx].calVecRpAddr + vectPtr->vectInfo[vectIdx].calVecLen)) )
        {
            break;
        }
    }

    return vectIdx;
}

/*
********************************************************************************
* Function Name: Xcp_CalDownLoadHandle
*
* Explanation: Perform data calibration.
*
* param: size: Data calibration size.
*        data: Data calibration start address.
*
* retval: Calibration operation result.
********************************************************************************
*/
FUNC(uint8, XCP_CODE) Xcp_CalDownLoadHandle
(
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST) data,
    uint16 size
)
{
    uint8 retVal = XCP_E_NOT_OK;
    uint16 vectIdx;
    uint32 addr;
    uint32 downsize;
    uint32* calVecAddr;
    Xcp_RamListType* ramPtr;
    Xcp_VectListType* vectPtr;

    addr = (uint32)Xcp_DataInformation.mta;
    ramPtr = Xcp_DataInformation.ramPtr;
    vectPtr = &Xcp_VectList;
    vectIdx = Xcp_CalVectSearch(vectPtr, addr);

    if( vectIdx < vectPtr->vectCnt )
    {
        if( vectPtr->vectInfo[vectIdx].calVecWpAddr == vectPtr->vectInfo[vectIdx].calVecRpAddr )
        {
            /* The first time to calibrate the partition, data copy is required. */
            Xcp_ReqCopy(vectPtr->vectInfo[vectIdx].calVecRpAddr,
                        ramPtr->ramCfg[ramPtr->ramNum].ramCurAddr,
                        vectPtr->vectInfo[vectIdx].calVecLen);
            vectPtr->vectInfo[vectIdx].calVecWpAddr = ramPtr->ramCfg[ramPtr->ramNum].ramCurAddr;
            calVecAddr = (uint32*)(vectPtr->vectInfo[vectIdx].calVecAddr);
            *calVecAddr = ramPtr->ramCfg[ramPtr->ramNum].ramCurAddr;
            ramPtr->ramCfg[ramPtr->ramNum].ramCurAddr += vectPtr->vectInfo[vectIdx].calVecLen;
            if( ramPtr->ramCfg[ramPtr->ramNum].ramLen < vectPtr->vectInfo[vectIdx].calVecLen )
            {
                retVal = XCP_CRC_OUT_OF_RANGE;
            }
            else
            {
                ramPtr->ramCfg[ramPtr->ramNum].ramLen -= vectPtr->vectInfo[vectIdx].calVecLen;
                Xcp_DownLoadCopyState.downSize = size;
                Xcp_DownLoadCopyState.downData = data;
                Xcp_SendFlag = FALSE;
                retVal = XCP_CMD_PENDING;
            }
        }
        else
        {
            /* WP is already in RAM, excute write action. */
            addr = vectPtr->vectInfo[vectIdx].calVecWpAddr + (addr - vectPtr->vectInfo[vectIdx].calVecRpAddr);

            downsize = size;
            while( downsize > XCP_VALUE_0 )
            {
                XCP_WRITE_BYTE_2_ADDR((uint8*)addr, *data);
                addr++;
                data++;
                downsize--;
            }
            retVal = XCP_E_OK;
        }
    }
#if( XCPBLOCK_SIZE > XCP_VALUE_0 )
    else
    {
        retVal = XCP_E_NOT_OK;
    }
#endif  /* XCPBLOCK_SIZE > XCP_VALUE_0 */

    return retVal;
}

/*
********************************************************************************
* Function Name: Xcp_CalUpLoadHandle
*
* Explanation: Perform data upload.
*
* param: size: Data upload size.
*        data: Data upload start address.
*
* retval: Upload operation result.
********************************************************************************
*/
FUNC(uint8, XCP_CODE) Xcp_CalUpLoadHandle
(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA) data,
    uint8 size
)
{
    uint8 retVal = XCP_E_NOT_OK;
    uint16 vectIdx;
    uint32 addr;
    Xcp_VectListType* vectPtr;

    addr = (uint32)Xcp_DataInformation.mta;
    vectPtr = &Xcp_VectList;

    vectIdx = Xcp_CalVectSearch(vectPtr, addr);
    if( vectIdx < vectPtr->vectCnt )
    {
        addr = vectPtr->vectInfo[vectIdx].calVecWpAddr + (addr - vectPtr->vectInfo[vectIdx].calVecRpAddr);

        while( size > XCP_VALUE_0 )
        {
            *(data) = XCP_READ_BYTE_FROM_ADDR((uint8*)addr);
            addr++;
            data++;
            size--;
        }
        retVal = XCP_E_OK;
    }

    return retVal;
}

/*
********************************************************************************
* Function Name: Xcp_CalMemInit
*
* Explanation: Calibration partition initialization.
*
* param: None
*
* retval: Upload operation result.
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_CalMemInit(void)
{
    uint8 ramIdx = XCP_INIT_0;
    Xcp_RamListType* ptr;

    Xcp_DataInformation.ramPtr = (Xcp_RamListType*)(&Xcp_CalRamInfoMem[XCP_INDEX_0]);
    ptr = Xcp_DataInformation.ramPtr;

    /* Calibration ram info init. */
    ptr->ramCnt = XCP_INIT_1;
    ptr->ramNum = XCP_INIT_0;
    ptr->ramCfg = (Xcp_RamType*)((uint8*)(ptr) + sizeof(*(ptr)));
    ptr->ramCfg[ramIdx].ramStaAddr = Xcp_Addr_Stru[XCP_INDEX_0].addr_wp;
    ptr->ramCfg[ramIdx].ramCurAddr = Xcp_Addr_Stru[XCP_INDEX_0].addr_wp;

    for( ramIdx = XCP_INDEX_0; ramIdx < XCP_RAM_CNT; ramIdx++ )
    {
        ptr->ramCfg[XCP_INDEX_0].ramLen += Xcp_Addr_Stru[ramIdx].len;
    }

    Xcp_VectList.vectCnt = XCP_INIT_0;
    Xcp_VectList.vectInfo = (Xcp_VectInfoType*)(ptr->ramCfg[XCP_INDEX_0].ramCurAddr);
}

#if( (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT) && (XCP_ENABLE_CHECKSUM == STD_ON) )
/*
********************************************************************************
* Function Name: Xcp_StructurePtChecksum
*
* Explanation: Check data size.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_StructurePtChecksum(uint32 checksumSize)
{
    uint16 vectIdx = XCP_INIT_0;
    uint32 addr = (uint32)Xcp_DataInformation.mta;
    uint32 calVecLen = XCP_INIT_0;
    Xcp_VectListType* vectPtr = &Xcp_VectList;
    uint8* addrOfs = NULL_PTR;

    /* Working Page. */
    if( XCP_WORKING_PAGE == Xcp_DataInformation.pageInd )
    {
        while( checksumSize > XCP_VALUE_0 )
        {
            vectIdx = Xcp_CalVectSearch(vectPtr, addr);
#if( (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) )
            /* In the calibration area. */
            if( vectIdx < vectPtr->vectCnt )
            {
                addrOfs = (uint8*)vectPtr->vectInfo[vectIdx].calVecWpAddr;
                calVecLen = vectPtr->vectInfo[vectIdx].calVecLen;

                if( vectPtr->vectInfo[vectIdx].calVecRpAddr == vectPtr->vectInfo[vectIdx].calVecWpAddr )
                {
                    while( calVecLen > XCP_VALUE_0 )
                    {
                        Xcp_DataInformation.checkSum += (tXcpChecksumSumType)XCP_READ_CHECKSUMVALUE_FROM_ADDR(Xcp_DataInformation.mta);
                        Xcp_DataInformation.mta = &Xcp_DataInformation.mta[sizeof(tXcpChecksumAddType)];
                        checksumSize -= (uint8)sizeof(tXcpChecksumAddType);
                        calVecLen -= (uint8)sizeof(tXcpChecksumAddType);
                    }
                }
                else
                {
                    while( calVecLen > XCP_VALUE_0 )
                    {
                        Xcp_DataInformation.checkSum += (tXcpChecksumSumType)XCP_READ_CHECKSUMVALUE_FROM_ADDR(addrOfs);
                        Xcp_DataInformation.mta = &Xcp_DataInformation.mta[sizeof(tXcpChecksumAddType)];
                        checksumSize -= (uint8)sizeof(tXcpChecksumAddType);
                        calVecLen -= (uint8)sizeof(tXcpChecksumAddType);
                        addrOfs += (uint8)sizeof(tXcpChecksumAddType);
                    }
                }
            }
            else
            {
                Xcp_DataInformation.checkSum += (tXcpChecksumSumType)XCP_READ_CHECKSUMVALUE_FROM_ADDR(Xcp_DataInformation.mta);
                Xcp_DataInformation.mta = &Xcp_DataInformation.mta[sizeof(tXcpChecksumAddType)];
                checksumSize -= (uint8)sizeof(tXcpChecksumAddType);
            }
            addr = (uint32)Xcp_DataInformation.mta;
#else
            /* In the calibration area. */
            if( vectIdx < vectPtr->vectCnt )
            {
                addrOfs = (uint8*)vectPtr->vectInfo[vectIdx].calVecWpAddr;
                calVecLen = vectPtr->vectInfo[vectIdx].calVecLen;

                if( vectPtr->vectInfo[vectIdx].calVecRpAddr == vectPtr->vectInfo[vectIdx].calVecWpAddr )
                {
                    if( TRUE == Xcp_DataInformation.crc32Flag )
                    {

                        Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta, calVecLen, (uint32)XCP_CRC_STARTVALUE, TRUE);
                        Xcp_DataInformation.crc32Flag = FALSE;
                    }
                    else
                    {
                        Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta, calVecLen, 
                                                                (uint32)Xcp_DataInformation.checkSum, FALSE);
                    }
                }
                else
                {
                    if( TRUE == Xcp_DataInformation.crc32Flag )
                    {

                        Xcp_DataInformation.checkSum = Crc_CalculateCRC32(addrOfs, calVecLen, (uint32)XCP_CRC_STARTVALUE, TRUE);
                        Xcp_DataInformation.crc32Flag = FALSE;
                    }
                    else
                    {
                        Xcp_DataInformation.checkSum = Crc_CalculateCRC32(addrOfs, calVecLen, (uint32)Xcp_DataInformation.checkSum, FALSE);
                    }
                }
                Xcp_DataInformation.mta += (uint8)calVecLen;
                checksumSize -= (uint8)calVecLen;
            }
            else
            {
                if( TRUE == Xcp_DataInformation.crc32Flag )
                {
                    Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta,
                                                   XCP_VALUE_1, (uint32)XCP_CRC_STARTVALUE, TRUE);
                    Xcp_DataInformation.crc32Flag = FALSE;
                    Xcp_DataInformation.mta += (uint8)XCP_VALUE_1;
                    checksumSize -= (uint8)XCP_VALUE_1;
                }
                else
                {
                    Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta,
                                                   XCP_VALUE_1, (uint32)Xcp_DataInformation.checkSum, FALSE);
                    Xcp_DataInformation.mta += (uint8)XCP_VALUE_1;
                    checksumSize -= (uint8)XCP_VALUE_1;
                }
            }
            addr = (uint32)Xcp_DataInformation.mta;
#endif  /* (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) */
        }
    }
    else
    {
#if( (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) )
        while( checksumSize > XCP_VALUE_0 )
        {
            Xcp_DataInformation.checkSum += (tXcpChecksumSumType)XCP_READ_CHECKSUMVALUE_FROM_ADDR(Xcp_DataInformation.mta);
            Xcp_DataInformation.mta = &Xcp_DataInformation.mta[sizeof(tXcpChecksumAddType)];
            checksumSize -= (uint8)sizeof(tXcpChecksumAddType);
        }
#else
        if( TRUE == Xcp_DataInformation.crc32Flag )
        {
            Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta,
                                           checksumSize, (uint32)XCP_CRC_STARTVALUE, TRUE);
            Xcp_DataInformation.crc32Flag = FALSE;
            Xcp_DataInformation.mta += (uint8)checksumSize;
        }
        else
        {
            Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta,
                                           checksumSize, (uint32)Xcp_DataInformation.checkSum, FALSE);
            Xcp_DataInformation.mta += (uint8)checksumSize;
        }
#endif  /* (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) */
    }
}
#endif  /* (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT) && (XCP_ENABLE_CHECKSUM == STD_ON) */

/*
********************************************************************************
* Function Name: Xcp_ReqCopy
*
* Explanation: Request data copy before calibration.
*
* param: srcAddr: Source data address.
*        desAddr: Copy destination.
*        size: Data copy size.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_ReqCopy
(
    uint32 srcAddr,
    uint32 desAddr,
    uint32 size
)
{
    /* First request, setting the copy size. */
    Xcp_DownLoadCopyState.copyAddrDest = desAddr;
    Xcp_DownLoadCopyState.copyAddrSrc = srcAddr;
    Xcp_DownLoadCopyState.copyLen = size;
    Xcp_DownLoadCopyState.copyReqState = XCP_REQ_COPY;

}
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */

#if( XCP_VERSION_INFO_API == STD_ON )
/*
********************************************************************************
* Function Name: XCP_GetVersionInfo
*
* Explanation: Returns the version information of this module.
*
* param: versioninfo: Pointer to standard version information structure.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, XCP_APPL_DATA) versioninfo
)
{
    uint8 errType = XCP_E_NO_ERROR;

    if( NULL_PTR != versioninfo )
    {
        versioninfo->vendorID = XCP_VENDOR_ID;
        versioninfo->moduleID = XCP_MODULE_ID;
        versioninfo->sw_major_version = XCP_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = XCP_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = XCP_SW_PATCH_VERSION;
    }
    else
    {
        errType = XCP_E_PARAM_POINTER;
    }
    Xcp_Det_ErrorReport(XCP_SID_GET_VERSIONINFO, errType);
}
#endif  /* XCP_VERSION_INFO_API == STD_ON */

/*
********************************************************************************
* Function Name: Xcp_MainFunction
*
* Explanation: XCP main function.Transfer to the command processing function
*              or EventChannel according to the received message.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_MainFunction(void)
{
#if( (RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY) || (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM) )
    uint8 addrIndex;
#endif  /* (RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY) || (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM) */

#if( XCP_ENABLE_NVM_SAVE_DATA == STD_ON )
    uint8 retValue = XCP_E_OK;
    retValue = Xcp_ActionForBlock(XCP_ACTION_READ);
    if( XCP_E_OK == retValue )
    {
#endif  /* XCP_ENABLE_NVM_SAVE_DATA == STD_ON */
        switch( Xcp_ConnectionStatus.busType )
        {
            case XCP_BUS_NULL:
#if( XCP_ONETHERNET_ENABLE == STD_ON )
                EthXcp_MainFunction();
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */

#if( XCP_ONCAN_ENABLE == STD_ON )
                CanXcp_MainFunction();
#endif  /* XCP_ONCAN_ENABLE == STD_ON */
                break;
#if( XCP_ONCAN_ENABLE == STD_ON )
            case XCP_BUS_CAN:
            case XCP_BUS_CANFD:
                CanXcp_MainFunction();
                break;
#endif  /* XCP_ONCAN_ENABLE == STD_ON */
#if( XCP_ONETHERNET_ENABLE == STD_ON )
            case XCP_BUS_ETHERNET:
                EthXcp_MainFunction();
                break;
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
            default:
                Xcp_Det_ErrorReport(XCP_SID_MAINFUNCTION, XCP_E_PARAM_ERROR);
                break;
        }

    /* Traverse events that reach the trigger time. */
#if( (XCP_EVENT_CHANNEL_NUM > XCP_VALUE_0) && (XCP_EVENT_BASE_PERIOD_SELECT == XCP_BASE_PERIOD_MAINFUNCTION) )
        XcpEventCycleProcess();
#endif  /* (XCP_EVENT_CHANNEL_NUM > XCP_VALUE_0) && (XCP_EVENT_BASE_PERIOD_SELECT == XCP_BASE_PERIOD_MAINFUNCTION) */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
        for( addrIndex = XCP_INDEX_0; addrIndex < XCP_REMAPPING_CNT; addrIndex++ )
        {
            if( XCP_VALUE_0 < Xcp_RemapAddr[addrIndex].len )
            {
                if( XCP_COPY_LEN < Xcp_RemapAddr[addrIndex].len )
                {
                    Xcp_RemapAddr[addrIndex].len -= XCP_COPY_LEN;
                    NeuLib_memcpy32((void*)Xcp_RemapAddr[addrIndex].addr_wp, (void*)Xcp_RemapAddr[addrIndex].addr_rp, XCP_COPY_LEN);
                    Xcp_RemapAddr[addrIndex].addr_rp += XCP_COPY_LEN;
                    Xcp_RemapAddr[addrIndex].addr_wp += XCP_COPY_LEN;
                }
                else
                {
                    NeuLib_memcpy32((void*)Xcp_RemapAddr[addrIndex].addr_wp, (void*)Xcp_RemapAddr[addrIndex].addr_rp, Xcp_RemapAddr[addrIndex].len);
                    Xcp_RemapAddr[addrIndex].addr_rp += Xcp_RemapAddr[addrIndex].len;
                    Xcp_RemapAddr[addrIndex].addr_wp += Xcp_RemapAddr[addrIndex].len;
                    Xcp_RemapAddr[addrIndex].len = XCP_VALUE_0;
                }
            }
        }
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM */

#if( RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY )
        for( addrIndex = XCP_INDEX_0; addrIndex < XCP_OVERLAY_CNT; addrIndex++ )
        {
            if( Xcp_Addr_Temp[addrIndex].len > XCP_VALUE_0 )
            {
                if( Xcp_Addr_Temp[addrIndex].len > XCP_COPY_LEN )
                {
                    Xcp_Addr_Temp[addrIndex].len -= XCP_COPY_LEN;
                    NeuLib_memcpy32((void*)Xcp_Addr_Temp[addrIndex].addr_wp, (void*)Xcp_Addr_Temp[addrIndex].addr_rp, XCP_COPY_LEN);
                    Xcp_Addr_Temp[addrIndex].addr_rp += XCP_COPY_LEN;
                    Xcp_Addr_Temp[addrIndex].addr_wp += XCP_COPY_LEN;
                }
                else
                {
                    NeuLib_memcpy32((void*)Xcp_Addr_Temp[addrIndex].addr_wp, (void*)Xcp_Addr_Temp[addrIndex].addr_rp, Xcp_Addr_Temp[addrIndex].len);
                    Xcp_Addr_Temp[addrIndex].addr_rp += Xcp_Addr_Temp[addrIndex].len;
                    Xcp_Addr_Temp[addrIndex].addr_wp += Xcp_Addr_Temp[addrIndex].len;
                    Xcp_Addr_Temp[addrIndex].len = XCP_VALUE_0;
                }
            }
        }
#endif  /* RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY */

        (void)Xcp_Background();

#if( XCP_ENABLE_NVM_SAVE_DATA == STD_ON )
        if( Xcp_DataInformation.storeFlag == XCP_SS_STORE_CAL_REQ )
        {
            retValue = Xcp_ActionForBlock(XCP_ACTION_WRITE);
            if ( XCP_E_OK == retValue )
            {
                XCP_CRM_EV_ID = XCP_PID_EV;
                XCP_CRM_EV_CODE = XCP_EV_STORE_CAL;
                Xcp_DataInformation.eventDataLen = XCP_VALUE_2;
                Xcp_DataInformation.storeFlag = XCP_CLEAN_NVM_FLAG;
                (void)Xcp_SendEv();
            }
            else
            {
                /* Do nothing. */
            }
        }
    }
#endif  /* XCP_ENABLE_NVM_SAVE_DATA == STD_ON */
}

#if( XCP_ENABLE_NVM_SAVE_DATA == STD_ON )
/*
********************************************************************************
* Function Name: Xcp_ActionForBlock
*
* Explanation: Xcp_ActionForBlock.
*              Calibration block for reading or writing all RAM.
*
* param: mode: XCP_ACTION_READ:Indicates the use of read.
*              XCP_ACTION_WRITE:Indicates the use of write.
*
*
* retval: XCP_E_OK:Indicates completion of reading or writing.
*         XCP_E_NOT_OK:Indicates whether to read or write without complete.
*
********************************************************************************
*/
static FUNC(uint8, XCP_CODE) Xcp_ActionForBlock
(
    uint8 mode
)
{
    uint8 retVal = XCP_E_OK;
    uint8 errorStatus = XCP_E_OK;
    uint16 blockIndex;

    if( (XCP_SS_STORE_CAL_REQ == Xcp_DataInformation.storeFlag) && (XCP_ACTION_WRITE == mode) )
    {
        retVal = XCP_E_NOT_OK;
    }
    else
    {
        if( (uint8)TRUE == Xcp_ReadBlockDone )
        {
            retVal = XCP_E_OK;
        }
        else
        {
            retVal = XCP_E_NOT_OK;
        }
    }

    if( XCP_E_NOT_OK == retVal )
    {
        /* Action block id data. */
        for( blockIndex = XCP_INDEX_0; blockIndex != XCP_BLOCK_NUM; blockIndex++ )
        {
            /* No data in not needed to option, set invalid block id. */
            if( XCP_U16_MASK == Xcp_NvmBlockId[blockIndex].BlockId )
            {
                Xcp_ActionDoneFlag[blockIndex] = TRUE;
                Xcp_NvmBlockId[blockIndex].ReadResp = XCP_E_OK;
                Xcp_NvmBlockId[blockIndex].RequestResp = XCP_E_OK;
            }
            /* If data buffer is null, set option done. */
            else if( NULL_PTR == Xcp_NvmBlockId[blockIndex].DataPtr )
            {
                Xcp_ActionDoneFlag[blockIndex] = TRUE;
                Xcp_NvmBlockId[blockIndex].ReadResp = XCP_E_OK;
                Xcp_NvmBlockId[blockIndex].RequestResp = XCP_E_OK;
            }
            else
            {
                if( (uint8)XCP_E_NOT_OK == Xcp_NvmBlockId[blockIndex].RequestResp )
                {
                    if( (XCP_SS_STORE_CAL_REQ == Xcp_DataInformation.storeFlag) && (XCP_ACTION_WRITE == mode) )
                    {
                        /* Write nvm block data. */
                        retVal = NvM_WriteBlock(Xcp_NvmBlockId[blockIndex].BlockId,
                                                Xcp_NvmBlockId[blockIndex].DataPtr);
                    }
                    else
                    {   /* Read nvm block data. */
                        retVal = NvM_ReadBlock(Xcp_NvmBlockId[blockIndex].BlockId,
                                                Xcp_NvmBlockId[blockIndex].DataPtr);
                    }
                    if( (uint8)XCP_E_OK == retVal )
                    {
                        Xcp_NvmBlockId[blockIndex].RequestResp = XCP_E_OK;
                        Xcp_NvmBlockId[blockIndex].ReadResp = XCP_E_NOT_OK;
                    }
                }
                else if( (uint8)XCP_E_NOT_OK == Xcp_NvmBlockId[blockIndex].ReadResp )
                {
                    /* Get the nvm error status. */
                    (void)NvM_GetErrorStatus(Xcp_NvmBlockId[blockIndex].BlockId, &errorStatus);

                    if( (uint8)XCP_E_NOT_OK == errorStatus )
                    {
                        /* Do nothing. */
                    }
                    else if( NVM_REQ_PENDING == errorStatus )
                    {
                        /* Do nothing. */
                    }
                    else
                    {
                        Xcp_ActionDoneFlag[blockIndex] = TRUE;
                        Xcp_NvmBlockId[blockIndex].ReadResp = XCP_E_OK;
                    }
                }
                else
                {
                    /* Do nothing. */
                }
            }
        }

        /* Determine if all blocks have completed the operation. */
        for( blockIndex = XCP_INDEX_0; blockIndex != XCP_BLOCK_NUM; blockIndex++ )
        {
            if( (uint8)FALSE == Xcp_ActionDoneFlag[blockIndex] )
            {
                break;
            }
        }

        if( XCP_BLOCK_NUM == blockIndex )
        {
            /* Recovery status. */
            for( blockIndex = XCP_INDEX_0; blockIndex != XCP_BLOCK_NUM; blockIndex++ )
            {
                Xcp_NvmBlockId[blockIndex].RequestResp = XCP_E_NOT_OK;
                Xcp_NvmBlockId[blockIndex].ReadResp = XCP_E_NOT_OK;
                Xcp_ActionDoneFlag[blockIndex] = FALSE;
            }
            if( XCP_SS_STORE_CAL_REQ != Xcp_DataInformation.storeFlag )
            {
                Xcp_ReadBlockDone = TRUE;
            }
            retVal = XCP_E_OK;
        }
        else
        {
            retVal = XCP_E_NOT_OK;
        }
    }

    return retVal;
}
#endif  /* XCP_ENABLE_NVM_SAVE_DATA == STD_ON */

/*
********************************************************************************
* Function Name: XCP_GetPointer
*
* Explanation: Get the address of the data to be measured or calibrated.
*
* param: extAddr: Address extension.
*        addr: Address of DAQ element.
*
* retval: Storage address.
********************************************************************************
*/
static FUNC_P2VAR(uint8, XCP_APPL_DATA, XCP_CODE) Xcp_GetPointer
(
    uint8 extAddr, uint32 addr
)
{
    uint8* retValue = NULL_PTR;

    XCP_DUMMY_STATEMENT(extAddr);
    /* Add error handling later. */
    retValue = (uint8*)addr;

    return retValue;
}

/*
********************************************************************************
* Function Name: XCP_MemSet
*
* Explanation: Initialize n bytes starting from address p with b.
*
* param: destAddr: Pointer to start address.
*        num: Number of data bytes.
*        byte: Data byte to initialize with.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_MemSet
(
    P2VAR(void, AUTOMATIC, XCP_APPL_DATA)destAddr,
    uint16 num,
    uint8 byte
)
{
    uint8* dest_pt = (uint8*)destAddr;

    for( ; num > XCP_VALUE_0; num-- )
    {
        *dest_pt = byte;
        dest_pt++;
    }
}

/*
********************************************************************************
* Function Name: Xcp_MemCpy8
*
* Explanation: Copy n bytes from src to dest.
*              A maximum of 255 Bytes can be copied at once.
*
* param: dest: pointer to destination address.
*        src: pointer to source address.
*        num: number of data bytes to copy.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_MemCpy8
(
    P2VAR(void, AUTOMATIC, XCP_APPL_DATA) dest,
    P2CONST(void, AUTOMATIC, XCP_APPL_CONST) src,
    uint32 num
)
{
    uint8* dest_ptr = (uint8*)dest;
    const uint8* src_ptr = (const uint8*)src;

    for( ; num > XCP_VALUE_0; num-- )
    {
        XCP_WRITE_BYTE_2_ADDR(dest_ptr, *src_ptr);
        dest_ptr++;
        src_ptr++;
    }
}

/*
********************************************************************************
* Function Name: XCP_WriteMta
*
* Explanation: Write n bytes.
*              Copying of size bytes from data to Xcp_DataInformation.mta.
*
* param: size: Size of copies of data.
*        data: Copied data.
*
* retval: XCP_E_OK: XCP_WriteMta success.
*         Any other: XCP_WriteMta not success.
********************************************************************************
*/
static FUNC(uint8, XCP_CODE) Xcp_WriteMta
(
    uint8 size,
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST) data
)
{
    uint8 errCode = XCP_E_NO_ERROR;

#if( (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT) || (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT) )
    uint8 retValue = XCP_E_NOT_OK;
#endif  /* (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT) || (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT) */

    if( NULL_PTR == Xcp_DataInformation.mta )
    {
        errCode = XCP_CRC_MEMORY_OVERFLOW;
    }
    else
    {
#if( RTECALIBRATIONSUPPORT != XCP_CAL_METHOD_MMU )
        errCode = Xcp_MtaCheckValid((uint32)Xcp_DataInformation.mta, size, XCP_ACCESS_SCOPE_CALIBRATION, XCP_ACCESS_TYPE_WRITE);
#else
        errCode = XCP_E_NO_ERROR;
#endif  /* RTECALIBRATIONSUPPORT != XCP_CAL_METHOD_MMU */
    }
    if( XCP_E_NO_ERROR == errCode )
    {
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT )
        retValue = Xcp_ModifyEntry((uint32)Xcp_DataInformation.mta, (uint16)size, (uint8*)data);
        if( XCP_E_OK == retValue )
        {
            Xcp_DataInformation.mta += size;
            errCode = XCP_E_NO_ERROR;
        }
        else
        {
            errCode = XCP_CRC_PAGE_NOT_VALID;
        }
#elif( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
        retValue = Xcp_CalDownLoadHandle((uint8*)data, size);

        if( XCP_E_OK == retValue )
        {
            Xcp_DataInformation.mta += size;
            errCode = XCP_E_NO_ERROR;
        }
        else if( XCP_CMD_PENDING == retValue )
        {
            errCode = XCP_CRC_PENGDING;
        }
        else
        {
           errCode = XCP_CRC_PAGE_NOT_VALID;
        }

#else

        while( size > XCP_VALUE_0 )
        {
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
            if( ((uint32)Xcp_DataInformation.mta >= XCP_CALFLASH_ADDR(Xcp_MapPageIdx)) &&
                ((uint32)Xcp_DataInformation.mta < (XCP_CALFLASH_ADDR(Xcp_MapPageIdx) + XCP_CALRAM_SIZE(Xcp_MapPageIdx))) )
            {
                XCP_WRITE_BYTE_2_ADDR(Xcp_DataInformation.mta + XcpCalOffset, *data);
            }
            else
            {
                XCP_WRITE_BYTE_2_ADDR(Xcp_DataInformation.mta, *data);
            }
#else
          XCP_WRITE_BYTE_2_ADDR(Xcp_DataInformation.mta, *data);
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM */

            Xcp_DataInformation.mta++;
            data++;
            size--;
        }
#endif
    }
    else
    {
        /* Do nothing. */
    }

    Xcp_RecordError(errCode);

    return errCode;
}

/*
********************************************************************************
* Function Name: XCP_ReadMta
*
* Explanation: Read n bytes.
*              Copying of size bytes from Xcp_DataInformation.mta to data.
*
* param: size: Size of copies of data.
*        data: Copied data.
*
* retval: XCP_E_OK: XCP_ReadMta success.
*         Any other: XCP_ReadMta not success.
********************************************************************************
*/
static FUNC(uint8, XCP_CODE) Xcp_ReadMta
(
    uint8 size,
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA)data
)
{
    uint8 errCode = XCP_E_NO_ERROR;

#if( (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT) || (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT) )
    uint8 retValue = XCP_E_NOT_OK;
#endif  /* (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT) || (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT) */

    if( NULL_PTR == Xcp_DataInformation.mta )
    {
        errCode = XCP_CRC_MEMORY_OVERFLOW;
    }
    else
    {
#if( RTECALIBRATIONSUPPORT != XCP_CAL_METHOD_MMU )
        errCode = Xcp_MtaCheckValid((uint32)Xcp_DataInformation.mta, size, XCP_ACCESS_SCOPE_ALL, XCP_ACCESS_TYPE_READ);
#else
        errCode = XCP_E_NO_ERROR;
#endif  /* RTECALIBRATIONSUPPORT != XCP_CAL_METHOD_MMU */
    }
    if( XCP_E_NO_ERROR == errCode )
    {
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT )
        retValue = Xcp_CalibParaRead((uint32)Xcp_DataInformation.mta, (uint16)size, (uint8*)data);
        if( XCP_E_OK == retValue )
        {
            Xcp_DataInformation.mta += size;
        }
#if( XCP_ENABLE_CHECKSUM == STD_ON )
        else if( XCP_CHECK_EVENTADDR((uint32)Xcp_DataInformation.mta) || (TRUE == Xcp_ChecksumFlag) )
#else  /* XCP_ENABLE_CHECKSUM == STD_ON */
        else if( XCP_CHECK_EVENTADDR((uint32)Xcp_DataInformation.mta) )
#endif
        {
            while( size > XCP_VALUE_0 )
            {
                *(data) = XCP_READ_BYTE_FROM_ADDR(Xcp_DataInformation.mta);
                data++;
                Xcp_DataInformation.mta++;
                size--;
            }
        }
        else
        {
            errCode = XCP_CRC_PAGE_NOT_VALID;
        }
#elif( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
        retValue = Xcp_CalUpLoadHandle(data, size);

        if( XCP_E_OK == retValue )
        {
            Xcp_DataInformation.mta += size;
        }
        else if( XCP_CHECK_EVENTADDR((uint32)Xcp_DataInformation.mta) ||
                 XCP_CHECK_STRUCTURE_RAMADDR((uint32)Xcp_DataInformation.mta) )
        {
            while( size > XCP_VALUE_0 )
            {
                *(data) = XCP_READ_BYTE_FROM_ADDR(Xcp_DataInformation.mta);
                data++;
                Xcp_DataInformation.mta++;
                size--;
            }
        }
        else
        {
            errCode = XCP_CRC_PAGE_NOT_VALID;
        }

#else
        while( size > XCP_VALUE_0 )
        {
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
            if( ((uint32)Xcp_DataInformation.mta >= XCP_CALFLASH_ADDR(Xcp_MapPageIdx)) &&
                ((uint32)Xcp_DataInformation.mta < (XCP_CALFLASH_ADDR(Xcp_MapPageIdx) + XCP_CALRAM_SIZE(Xcp_MapPageIdx))) )
            {
                *(data) = XCP_READ_BYTE_FROM_ADDR(Xcp_DataInformation.mta + XcpCalOffset);
            }
            else
            {
                *(data) = XCP_READ_BYTE_FROM_ADDR(Xcp_DataInformation.mta);
            }
#else
            *(data) = XCP_READ_BYTE_FROM_ADDR(Xcp_DataInformation.mta);
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM */

            data++;
            Xcp_DataInformation.mta++;
            size--;
        }
#endif
    }
    else
    {
        /* Do nothing. */
    }

    Xcp_RecordError(errCode);

    return errCode;
}

/*
********************************************************************************
* Function Name: XCP_MemClr
*
* Explanation: Initialize n bytes starting from address p 0.
*
* param: straddr: Pointer to start address.
*        num: Number of data bytes.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_MemClr
(
    P2VAR(void, AUTOMATIC, XCP_APPL_DATA)straddr,
    uint16 num
)
{
    Xcp_MemSet(straddr, num, XCP_INIT_0);
}

/*
********************************************************************************
* Function Name: XCP_Send
*
* Explanation: XCP send a message.
*
* param: avcLen: length of send data.
*       avcpMsg: the data send.
*
* retval: XCP_E_OK: Transmit request has been accepted.
*         XCP_E_NOT_OK: Transmit request has not been accepted.
********************************************************************************
*/
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
static FUNC(Std_ReturnType, XCP_CODE) Xcp_Send
(
    uint8 pduid, uint32 avcLen,
    P2CONST(uint8, AUTOMATIC, XCP_APPL_DATA)avcpMsg
)
{
    Std_ReturnType stdRet = XCP_E_NOT_OK;

    stdRet = CanXcp_Send(pduid, avcLen, avcpMsg);

    return stdRet;
}
#else
static FUNC(Std_ReturnType, XCP_CODE) Xcp_Send
(
    uint32 avcLen,
    P2CONST(uint8, AUTOMATIC, XCP_APPL_DATA)avcpMsg
)
{
    Std_ReturnType stdRet = XCP_E_NOT_OK;

    switch( Xcp_ConnectionStatus.busType )
    {
#if( XCP_ONCAN_ENABLE == STD_ON )
        case XCP_BUS_CAN:
        case XCP_BUS_CANFD:
            stdRet = CanXcp_Send(avcLen, avcpMsg);
            break;
#endif  /* XCP_ONCAN_ENABLE == STD_ON */
#if( XCP_ONETHERNET_ENABLE == STD_ON )
        case XCP_BUS_ETHERNET:
        /* Fill the Ethernet data frame header. */
#if( CPU_BYTE_ORDER == LOW_BYTE_FIRST )
            Xcp_EthResData[XCP_INDEX_1] = (uint8)( (avcLen & XCP_DATA_MASK_FF00) >> XCP_SHIFT_8 );
            Xcp_EthResData[XCP_INDEX_0] = (uint8)( avcLen & XCP_DATA_MASK_00FF );
            Xcp_EthResData[XCP_INDEX_3] = (uint8)( (Xcp_EthCtrTx & XCP_DATA_MASK_FF00) >> XCP_SHIFT_8 );
            Xcp_EthResData[XCP_INDEX_2] = (uint8)( Xcp_EthCtrTx & XCP_DATA_MASK_00FF );
#else  /* CPU_BYTE_ORDER == LOW_BYTE_FIRST */
            Xcp_EthResData[XCP_INDEX_0] = (uint8)( (avcLen & XCP_DATA_MASK_FF00) >> XCP_SHIFT_8 );
            Xcp_EthResData[XCP_INDEX_1] = (uint8)( avcLen & XCP_DATA_MASK_00FF );
            Xcp_EthResData[XCP_INDEX_2] = (uint8)( (Xcp_EthCtrTx & XCP_DATA_MASK_FF00) >> XCP_SHIFT_8 );
            Xcp_EthResData[XCP_INDEX_3] = (uint8)( Xcp_EthCtrTx & XCP_DATA_MASK_00FF );
#endif  /* CPU_BYTE_ORDER == LOW_BYTE_FIRST */
            Xcp_EthCtrTx++;
            Xcp_MemCpy8(&Xcp_EthResData[XCP_ETH_DAQ_DTO_DAT_OFFSET], avcpMsg, avcLen);
            stdRet = EthXcp_Send((uint16)(avcLen + XCP_ETH_DAQ_DTO_HEAD_LEN), &Xcp_EthResData[XCP_INDEX_0]);
            break;
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
        default:
            Xcp_Det_ErrorReport(XCP_SID_SEND, XCP_E_PARAM_ERROR);
            break;
    }

    return stdRet;
}
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */

#if( defined (XCP_ENABLE_SEND_EVENT) && ( XCP_ENABLE_NVM_SAVE_DATA == STD_ON ) )
/*
********************************************************************************
* Function Name: XCP_SendEv
*
* Explanation: Send a EV or SERV message, if no other message is pending.
*
* param: None
*
* retval: XCP_E_OK: Transmit request has been accepted.
*         XCP_E_NOT_OK: Transmit request has not been accepted.
********************************************************************************
*/
static FUNC(Std_ReturnType, XCP_CODE) Xcp_SendEv(void)
{
    Std_ReturnType stdRte = XCP_E_NOT_OK;

#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
    stdRte = Xcp_Send(Xcp_DataInformation.eventDataLen, Xcp_DataInformation.eventDataBuff.bytes);
    if( XCP_E_OK == stdRte )
    {
        Xcp_DataInformation.eventDataLen = XCP_VALUE_0;
    }
    else
    {
        Xcp_DataInformation.sendStatus |= (uint8)XCP_EVT_REQUEST;
    }
#else
    stdRte = Xcp_Send(Xcp_DataInformation.eventDataLen, Xcp_DataInformation.eventDataBuff.bytes);
    Xcp_DataInformation.eventDataLen = XCP_VALUE_0;
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */

    return stdRte;
}
#endif  /* defined (XCP_ENABLE_SEND_EVENT) && ( XCP_ENABLE_NVM_SAVE_DATA == STD_ON ) */

#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
/*
********************************************************************************
* Function Name: XCP_SendDtoFromQueue
*
* Explanation: Send a DTO from the queue.
*
* param: None
*
* retval: XCP_E_OK: XCP_SendDtoFromQueue success.
*         Any other: XCP_SendDtoFromQueue not success.
********************************************************************************
*/
static FUNC(uint8, XCP_CODE) Xcp_SendDtoFromQueue(uint8 eventid)
{
    uint8 retValue = XCP_E_NOT_OK;
    uint8 daq = Xcp_DataInformation.daq.eventDaq[eventid];

    /* A pending flag indicates that XCP_Send() is in progress. */
    if( (XCP_VALUE_0 == (Xcp_DataInformation.sendStatus[eventid] & (uint8)XCP_SEND_PENDING)) &&
        (XCP_VALUE_0 != Xcp_DataInformation.queueLen[daq]) )
    {
        Xcp_DataInformation.sendStatus[eventid] |= (uint8)XCP_DTO_PENDING;
        /* Send Dto. */
        Xcp_SendDto(eventid, Xcp_pDataQueue(daq, Xcp_DataInformation.queueRp[daq]));
        Xcp_DataInformation.queueRp[daq]++;
        if( Xcp_DataInformation.queueRp[daq] >= Xcp_DataInformation.queueSize[daq] )
        {
            Xcp_DataInformation.queueRp[daq] = XCP_VALUE_0;
        }
        Xcp_DataInformation.queueLen[daq]--;
        retValue = XCP_E_OK;
    }

    return retValue;
}
#else
static FUNC(uint8, XCP_CODE) Xcp_SendDtoFromQueue(void)
{
    uint8 retValue = XCP_E_NOT_OK;
    uint16 length = XCP_INIT_0;
#if( XCP_ONETHERNET_ENABLE == STD_ON )
    Xcp_EthDtoType ethData = {XCP_INIT_0, {XCP_INIT_0}};
    uint8* dtoi = NULL_PTR;
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */

    /* A pending flag indicates that XCP_Send() is in progress. */
    if( (XCP_BUS_CAN == Xcp_ConnectionStatus.busType) || (XCP_BUS_CANFD == Xcp_ConnectionStatus.busType) )
    {
#if( XCP_ONCAN_ENABLE == STD_ON )
        /* Send Dto. */
        retValue = Xcp_SendDto( Xcp_pDataQueue(Xcp_DataInformation.queueRp) );
#endif  /* XCP_ONCAN_ENABLE == STD_ON */
    }
    else if( XCP_BUS_ETHERNET == Xcp_ConnectionStatus.busType )
    {
#if( XCP_ONETHERNET_ENABLE == STD_ON )
        dtoi = &ethData.bytes[XCP_INDEX_0];
#if( CPU_BYTE_ORDER == LOW_BYTE_FIRST )
        length = (uint16)Xcp_pDataQueue(Xcp_DataInformation.queueRp)->length;
        dtoi[XCP_INDEX_1] = Xcp_WordGetHiByte(length);
        dtoi[XCP_INDEX_0] = Xcp_WordGetLoByte(length);
        dtoi[XCP_INDEX_3] = Xcp_WordGetHiByte(Xcp_EthCtrTx);
        dtoi[XCP_INDEX_2] = Xcp_WordGetLoByte(Xcp_EthCtrTx);
#else  /* CPU_BYTE_ORDER == LOW_BYTE_FIRST */
        dtoi[XCP_INDEX_0] = Xcp_WordGetHiByte(length);
        dtoi[XCP_INDEX_1] = Xcp_WordGetLoByte(length);
        dtoi[XCP_INDEX_2] = Xcp_WordGetHiByte(Xcp_EthCtrTx);
        dtoi[XCP_INDEX_3] = Xcp_WordGetLoByte(Xcp_EthCtrTx);
#endif  /* CPU_BYTE_ORDER == LOW_BYTE_FIRST */
        Xcp_EthCtrTx++;
        dtoi = &dtoi[XCP_ETH_DAQ_DTO_DAT_OFFSET];
        Xcp_MemCpy8(dtoi,
                    &(Xcp_pDataQueue(Xcp_DataInformation.queueRp)->bytes[XCP_INDEX_0]),
                    Xcp_pDataQueue(Xcp_DataInformation.queueRp)->length);
        ethData.length += (Xcp_pDataQueue(Xcp_DataInformation.queueRp)->length + XCP_ETH_DAQ_DTO_HEAD_LEN);
        retValue = Xcp_SendEthDaq(&ethData);
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
    }
    else
    {
        Xcp_Det_ErrorReport(XCP_SID_SENDDTOFROMQUEUE, XCP_E_PARAM_ERROR);
    }
    if( XCP_E_OK == retValue )
    {
        Xcp_DataInformation.queueRp++;
        if( Xcp_DataInformation.queueRp >= Xcp_DataInformation.queueSize )
        {
            Xcp_DataInformation.queueRp = XCP_VALUE_0;
        }
    }
    else
    {
        Xcp_DataInformation.sendStatus |= (uint8)XCP_DTO_PENDING;
    }

    return retValue;
}
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */

/*
********************************************************************************
* Function Name: XCP_QueueInit
*
* Explanation: XCP transmission queue initialization.
*
* param: None
*
* retval: None
********************************************************************************
*/
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
static FUNC(void, XCP_CODE) Xcp_QueueInit(void)
{
    uint8 index;

    for( index = XCP_INDEX_0; index < XCP_EVENT_CHANNEL_NUM ; index++ )
    {
        Xcp_DataInformation.queueLen[index] = XCP_INIT_0;
        Xcp_DataInformation.queueRp[index] = XCP_INIT_0;
    }
}
#else
static FUNC(void, XCP_CODE) Xcp_QueueInit(void)
{
    Xcp_DataInformation.queueWp = XCP_INIT_0;
    Xcp_DataInformation.queueRp = XCP_INIT_0;
    /* Clear Xcp_OdtNumber. */
    Xcp_OdtNumber = XCP_INIT_0;
}
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */

#ifdef XCP_ENABLE_DAQ
/*
********************************************************************************
* Function Name: XCP_FreeDaq
*
* Explanation: Free all dynamic DAQ lists.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_FreeDaq(void)
{
    Xcp_DataInformation.sessionStatus &= (uint8)(~XCP_SS_DAQ) & XCP_U8_MASK;

    Xcp_DataInformation.daq.daqCount = XCP_INIT_0;
    Xcp_DataInformation.daq.odtCount = XCP_INIT_0;
    Xcp_DataInformation.daq.odtEntryCount = XCP_INIT_0;

    Xcp_DataInformation.pOdt = NULL_PTR;
    Xcp_DataInformation.pOdtEntryAddr = NULL_PTR;
    Xcp_DataInformation.pOdtEntrySize = NULL_PTR;
    Xcp_DataInformation.maxOdt = XCP_INIT_0;

    /* Clear daq data 2048 byte. */
    Xcp_MemClr(&Xcp_DataInformation.daq.daqSizeInfo.daqMemSize[XCP_INDEX_0], XCP_DAQMEMSIZE);
    Xcp_MemSet(&Xcp_DataInformation.daq.eventDaq[XCP_INDEX_0],
        sizeof(Xcp_DataInformation.daq.eventDaq), XCP_U8_MASK);

#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
    Xcp_QueueInit();
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
}

/*
********************************************************************************
* Function Name: XCP_AllocMemory
*
* Explanation: Allocate Memory for daq,odt,odtEntries and Queue
*              according to DaqCount, OdtCount and OdtEntryCount.
*
* param: None
*
* retval: XCP_E_OK: XCP_AllocMemory success.
*         Any other: XCP_AllocMemory not success.
********************************************************************************
*/
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
static FUNC(uint8, XCP_CODE) Xcp_AllocMemory(void)
{
    uint8 retValue = XCP_E_OK;
    uint8 odtIndex;
    uint16 size = XCP_INIT_0;
    uint16 queueSize = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = NULL_PTR;

    if( XCP_CONNECTION_CFG_NUM > Xcp_ConnectionStatus.connectionId )
    {
        xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
        /* Check memory overflow. */
        /* 6 bytes sizeof(Xcp_DaqListInfoType) */
        /* 4 bytes sizeof(Xcp_OdtNumType) */
        /* 5 bytes sizeof(uint8*) + sizeof(uint8) */
        size = (uint16)(((uint16)Xcp_DataInformation.daq.daqCount * sizeof(Xcp_DaqListInfoType)) +
                ((uint16)Xcp_DataInformation.daq.odtCount * sizeof(Xcp_OdtNumType)) +
                (Xcp_DataInformation.daq.odtEntryCount * (sizeof(uint8*) + sizeof(uint8))));
        /* 4-byte alignment */
        size = ( size + XCP_VALUE_3 ) & (uint8)(~XCP_VALUE_3);
        if( (uint16)XCP_DAQMEMSIZE <= size)
        {
            retValue = (uint8)XCP_CRC_MEMORY_OVERFLOW;
        }
        else
        {
            /* Force WORD alignment for ODTs. */
            /* Allign to dwords. */
            Xcp_DataInformation.pOdt = (Xcp_OdtNumType*)((((uint32)(&Xcp_DataInformation.daq.daqSizeInfo.daqList[Xcp_DataInformation.daq.daqCount]))+
                            (uint32)XCP_VALUE_3) & (uint32)XCP_DATA_MASK_FFFFFFFC);
            /* Force DWORD alignment for ODT entries. */
            Xcp_DataInformation.pOdtEntryAddr = (uint8**) ((((uint32)&Xcp_DataInformation.pOdt[Xcp_DataInformation.daq.odtCount])+
                                    (uint32)XCP_VALUE_3) & (uint32)XCP_DATA_MASK_FFFFFFFC);
            Xcp_DataInformation.pOdtEntrySize = (uint8*)&Xcp_DataInformation.pOdtEntryAddr[Xcp_DataInformation.daq.odtEntryCount];

#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
            /* Force WORD alignment for the queue. */
            /* Allign to dwords. */
            Xcp_DataInformation.queueUnit = (uint8)(sizeof(Xcp_DtoDataType) - XCP_MAX_DTO + xcpConnCfgPtr->Xcp_Max_Dto);
            /* 4-byte alignment. */
            Xcp_DataInformation.queueUnit = ( Xcp_DataInformation.queueUnit + XCP_VALUE_3 ) & (uint8)(~XCP_VALUE_3);

            for( odtIndex = XCP_INDEX_0; odtIndex < XCP_EVENT_CHANNEL_NUM; odtIndex++ )
            {
                if( XCP_VALUE_0 == odtIndex )
                {
                    Xcp_DataInformation.pQueue[odtIndex] = (uint8*)
                        ((((uint32)(&Xcp_DataInformation.pOdtEntrySize[Xcp_DataInformation.daq.odtEntryCount])) +
                                                (uint32)XCP_VALUE_3) & (uint32)XCP_DATA_MASK_FFFFFFFC);
                }
                else
                {
                    Xcp_DataInformation.pQueue[odtIndex] = (uint8*)((((uint32)Xcp_DataInformation.pQueue[odtIndex - XCP_VALUE_1])+
                                                (Xcp_DaqListOdtCount(odtIndex - XCP_VALUE_1) + XCP_VALUE_0) *
                                                Xcp_DataInformation.queueUnit + (uint32)XCP_VALUE_3) & (uint32)XCP_DATA_MASK_FFFFFFFC);
                }
                size += ((uint16)(Xcp_DaqListOdtCount(odtIndex) * Xcp_DataInformation.queueUnit));
                /* 4-byte alignment. */
                size = ( size + XCP_VALUE_3 ) & (uint8)(~XCP_VALUE_3);

                queueSize = Xcp_DaqListOdtCount(odtIndex);
                if( XCP_MAX_QUEUE_SIZE < queueSize )
                {
                    /* Maximum possible size because of the modulo operation in XcpQueueWrite. */
                    Xcp_DataInformation.queueSize[odtIndex] = XCP_MAX_QUEUE_SIZE;
                }
                else
                {
                    Xcp_DataInformation.queueSize[odtIndex] = (uint8)queueSize;
                }
                /* At least one queue entry per odt. */
            }
            if( (uint16)XCP_DAQMEMSIZE <= size )
            {
                retValue = (uint8)XCP_CRC_MEMORY_OVERFLOW;
            }
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
        }
    }
    else
    {
        Xcp_Det_ErrorReport(XCP_SID_SENDDTOMODE, XCP_E_PARAM_ERROR);
    }

    return retValue;
}

#else
static FUNC(uint8, XCP_CODE) Xcp_AllocMemory(void)
{
    uint8 retValue = XCP_E_OK;
    /* size:xcp_daq size, queuesize:queue size. */
    uint16 totalSize = XCP_INIT_0;
    uint16 headInfoSize = XCP_INIT_0;
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
    uint16 queueSize = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = NULL_PTR;
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */

    if( XCP_CONNECTION_CFG_NUM > Xcp_ConnectionStatus.connectionId )
    {
        /* Check memory overflow. */
        /* 6 bytes sizeof(Xcp_DaqListInfoType) */
        /* 4 bytes sizeof(Xcp_OdtNumType) */
        /* 5 bytes sizeof(uint8*) + sizeof(uint8) */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
        xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
        Xcp_DataInformation.queueUnit = (uint8)(sizeof(Xcp_DtoDataType) + xcpConnCfgPtr->Xcp_Max_Dto - XCP_MAX_DTO);
        /* 4-byte alignment. */
        Xcp_DataInformation.queueUnit = SET_VALUE_ALIGN(Xcp_DataInformation.queueUnit, uint8, XCP_SEND_QUEUE_ALIGN_SIZE);
        headInfoSize = (uint16)(((uint16)Xcp_DataInformation.daq.daqCount * sizeof(Xcp_DaqListInfoType)) +
                ((uint16)Xcp_DataInformation.daq.odtCount * sizeof(Xcp_OdtNumType)) +
                (Xcp_DataInformation.daq.odtEntryCount * (sizeof(uint8*) + sizeof(uint8))));
        totalSize = headInfoSize + ((uint16)Xcp_DataInformation.maxOdt * (uint16)Xcp_DataInformation.queueUnit);
#else
        headInfoSize = (uint16)(((uint16)Xcp_DataInformation.daq.daqCount * sizeof(Xcp_DaqListInfoType)) +
                ((uint16)Xcp_DataInformation.daq.odtCount * sizeof(Xcp_OdtNumType)) +
                (Xcp_DataInformation.daq.odtEntryCount * (sizeof(uint8*) + sizeof(uint8))));
        totalSize = headInfoSize;
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
        /* 4-byte alignment. */
        totalSize = SET_VALUE_ALIGN(totalSize, uint16, XCP_SEND_QUEUE_ALIGN_SIZE);
        if( (uint16)XCP_DAQMEMSIZE <= totalSize )
        {
            retValue = (uint8)XCP_CRC_MEMORY_OVERFLOW;
        }
        else
        {
            /* Force WORD alignment for ODTs. */
            /* Allign to dwords. */
            Xcp_DataInformation.pOdt = (Xcp_OdtNumType*)((((uint32)(&Xcp_DataInformation.daq.daqSizeInfo.daqList[Xcp_DataInformation.daq.daqCount]))+
                            (uint32)XCP_VALUE_3) & (uint32)XCP_DATA_MASK_FFFFFFFC);
            /* Force DWORD alignment for ODT entries. */
            Xcp_DataInformation.pOdtEntryAddr = (uint8**) ((((uint32)&Xcp_DataInformation.pOdt[Xcp_DataInformation.daq.odtCount])+
                                    (uint32)XCP_VALUE_3) & (uint32)XCP_DATA_MASK_FFFFFFFC);
            Xcp_DataInformation.pOdtEntrySize = (uint8*)&Xcp_DataInformation.pOdtEntryAddr[Xcp_DataInformation.daq.odtEntryCount];

#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
            /* Force WORD alignment for the queue. */
            /* Allign to dwords. */
            Xcp_DataInformation.pQueue = (uint8*)((((uint32)(&Xcp_DataInformation.pOdtEntrySize[Xcp_DataInformation.daq.odtEntryCount]))+
                            (uint32)XCP_VALUE_3) & (uint32)XCP_DATA_MASK_FFFFFFFC);

            queueSize = ((uint16)XCP_DAQMEMSIZE - headInfoSize) / Xcp_DataInformation.queueUnit;
            if( XCP_MAX_QUEUE_SIZE < queueSize )
            {
                /* Maximum possible size because of the modulo operation in XcpQueueWrite. */
                Xcp_DataInformation.queueSize = XCP_MAX_QUEUE_SIZE;
            }
            else
            {
                Xcp_DataInformation.queueSize = queueSize;
            }
            /* At least one queue entry per odt. */
            if( Xcp_DataInformation.queueSize < Xcp_DataInformation.daq.odtCount )
            {
                retValue = (uint8)XCP_CRC_MEMORY_OVERFLOW;
            }
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
        }
    }
    else
    {
        Xcp_Det_ErrorReport(XCP_SID_SENDDTOMODE, XCP_E_PARAM_ERROR);
    }

    return retValue;
}
#endif

#if( XCP_MULTIPDUIDSUPPORT == STD_OFF )
#ifdef XCP_ENABLE_STIM_QUEUE
/*
********************************************************************************
* Function Name: Xcp_AllocStimQueueMemory
*
* Explanation: Allocate Stim Data Receive queue.
*
* retval: XCP_E_OK: Alloc success.
*         XCP_E_NOT_OK: Alloc not success.
********************************************************************************
*/
static FUNC(uint8, XCP_CODE) Xcp_AllocStimQueueMemory(void)
{
    uint8 retValue = XCP_E_OK;
    uint16 queueSizeStim = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = NULL_PTR;

    if( XCP_CONNECTION_CFG_NUM > Xcp_ConnectionStatus.connectionId )
    {
        xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
        Xcp_DataInformation.pQueueStim = (uint8*)Xcp_DataInformation.daq.stimDateBuffer;
        Xcp_DataInformation.queueUnitSize = (uint8)(sizeof(Xcp_StimDtoType) - (XCP_MAX_DTO & XCP_U8_MASK) +
                                        xcpConnCfgPtr->Xcp_Max_Dto);
        /* 4-byte alignment. */
        Xcp_DataInformation.queueUnitSize = SET_VALUE_ALIGN(Xcp_DataInformation.queueUnitSize, uint8, XCP_SEND_QUEUE_ALIGN_SIZE);
        queueSizeStim = XCP_DAQMEMSIZE_STIM / Xcp_DataInformation.queueUnitSize;

        if( XCP_MAX_QUEUE_SIZE < queueSizeStim )
        {
            /* Maximum possible size because of the modulo operation in XcpQueueWrite. */
            Xcp_DataInformation.queueSizeStim = XCP_MAX_QUEUE_SIZE;
        }
        else
        {
            Xcp_DataInformation.queueSizeStim = queueSizeStim;
        }
        /* At least one queue entry per odt. */
        if( Xcp_DataInformation.queueSizeStim < Xcp_DataInformation.daq.odtCount )
        {
            retValue = (uint8)XCP_CRC_MEMORY_OVERFLOW;
        }
    }
    else
    {
        Xcp_Det_ErrorReport(XCP_SID_SENDDTOMODE, XCP_E_PARAM_ERROR);
    }

    return retValue;
}
#endif  /* #ifdef XCP_ENABLE_STIM_QUEUE */
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_OFF */

/*
********************************************************************************
* Function Name: Xcp_AllocDaq
*
* Explanation: Allocate DAQ list.
*
* param: daqCount: Number of daqs in DAQ list.
*
* retval: XCP_E_OK: XCP_AllocDaq success.
*         XCP_E_NOT_OK: XCP_AllocDaq not success.
********************************************************************************
*/
static FUNC(uint8, XCP_CODE) Xcp_AllocDaq(uint8 daqCount)
{
    uint8 retValue = XCP_E_NOT_OK;

    if( (XCP_VALUE_0 != Xcp_DataInformation.daq.odtCount) || (XCP_VALUE_0 != Xcp_DataInformation.daq.odtEntryCount) )
    {
        retValue = (uint8)XCP_CRC_SEQUENCE;
    }
    else
    {
        if( (XCP_DAQ_COUNT + XCP_MIN_DAQ) < daqCount )
        {
            retValue = XCP_CRC_OUT_OF_RANGE;
        }
        else
        {
            Xcp_DataInformation.daq.daqCount = daqCount;
            retValue = Xcp_AllocMemory();
        }
    }

    return retValue;
}

/*
********************************************************************************
* Function Name: Xcp_AllocOdt
*
* Explanation: Allocate all ODTs in a DAQ list.
*
* param: daqCount: Number of odt in DAQ.
*
* retval: XCP_E_OK: XCP_AllocOdt success.
*         Any other: XCP_AllocOdt not success.
********************************************************************************
*/
static FUNC(uint8, XCP_CODE) Xcp_AllocOdt(uint8 daq, uint8 odtCount)
{
    uint8 retValue = XCP_E_NOT_OK;

    if( daq >= Xcp_DataInformation.daq.daqCount )
    {
        retValue = (uint8)XCP_CRC_OUT_OF_RANGE;
    }
    else
    {
        if( XCP_ODT_COUNT < odtCount )
        {
            retValue = XCP_CRC_OUT_OF_RANGE;
        }
        else
        {
            Xcp_DataInformation.daq.daqSizeInfo.daqList[daq].firstOdt = Xcp_DataInformation.daq.odtCount;
            Xcp_DataInformation.daq.odtCount += odtCount;
            Xcp_DataInformation.daq.daqSizeInfo.daqList[daq].lastOdt = Xcp_DataInformation.daq.odtCount - XCP_VALUE_1;
            if( Xcp_DataInformation.maxOdt < odtCount )
            {
                Xcp_DataInformation.maxOdt = odtCount;
            }
            retValue = Xcp_AllocMemory();
        }
    }

    return retValue;
}

/*
********************************************************************************
* Function Name: Xcp_AllocOdtEntry
*
* Explanation: Allocate all OdtEntry in a ODT.
*
* param: daq: Currently initialized DAQ.
*        odt: ODT in current DAQ.
*        odtEntryCount: Number of ODT entries in ODT.
*
* retval: XCP_E_OK: XCP_AllocOdtEntry success.
*         Any other: XCP_AllocOdtEntry not success.
********************************************************************************
*/
static FUNC(uint8, XCP_CODE) Xcp_AllocOdtEntry(uint8 daq, uint8 odt, uint8 odtEntryCount)
{
    uint8 retValue = XCP_E_NOT_OK;
    uint8 xcpFirstOdt = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];

    if( (XCP_VALUE_0 == Xcp_DataInformation.daq.daqCount) || (XCP_VALUE_0 == Xcp_DataInformation.daq.odtCount) )
    {
        retValue = (uint8)XCP_CRC_SEQUENCE;
    }
    else
    {
        /* Absolute ODT entry count count must fit in a WORD. */
        if( Xcp_DataInformation.daq.odtEntryCount > (XCP_U16_MASK - odtEntryCount) )
        {
            retValue = (uint8)XCP_CRC_MEMORY_OVERFLOW;
        }
        else
        {
            if( xcpConnCfgPtr->XcpOdtEntriesCount < odtEntryCount )
            {
                retValue = XCP_CRC_OUT_OF_RANGE;
            }
            else
            {
                xcpFirstOdt = Xcp_DataInformation.daq.daqSizeInfo.daqList[daq].firstOdt;
                Xcp_DataInformation.pOdt[xcpFirstOdt + odt].firstOdtEntry = Xcp_DataInformation.daq.odtEntryCount;
                Xcp_DataInformation.daq.odtEntryCount += (uint16)odtEntryCount;
                Xcp_DataInformation.pOdt[xcpFirstOdt + odt].lastOdtEntry = (uint16)(Xcp_DataInformation.daq.odtEntryCount - XCP_VALUE_1);
                retValue = Xcp_AllocMemory();
            }
        }
    }

    return retValue;
}

/*
********************************************************************************
* Function Name: Xcp_StartDaq
*
* Explanation: Start the transfer of the specified DAQ list.
*
* param: daq: The daq list you want to start.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_StartDaq(uint8 daq)
{
    /* Initialize the DAQ list. */
    Xcp_DaqListFlags(daq) |= (uint8)XCP_DAQ_FLAG_RUNNING;

#if( XCP_PRESCALER_SUPPORTED == STD_ON )
    Xcp_DaqListCycle(daq) = XCP_VALUE_1;
#endif  /* XCP_PRESCALER_SUPPORTED == STD_ON */

    Xcp_DataInformation.sessionStatus |= (uint8)XCP_SS_DAQ;
}

/*
********************************************************************************
* Function Name: Xcp_StartAllSelectedDaq
*
* Explanation: Start all selected DAQs.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_StartAllSelectedDaq(void)
{
    uint8 daq;

    /* Start all selected DAQs. */
    for( daq = XCP_INDEX_0; daq < Xcp_DataInformation.daq.daqCount; daq++ )
    {
        if( (Xcp_DaqListFlags(daq) & (uint8)XCP_DAQ_FLAG_SELECTED) != XCP_VALUE_0 )
        {
            Xcp_StartDaq(daq);
            Xcp_DaqListFlags(daq) &= (uint8)(~XCP_DAQ_FLAG_SELECTED) & XCP_U8_MASK;
        }
    }
}

/*
********************************************************************************
* Function Name: Xcp_StopDaq
*
* Explanation: Stop DAQ.
*
* param: daq: The daq list you want to stop.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_StopDaq(uint8 daq)
{
    uint8 acIndex;
    uint8 reValue = XCP_INIT_0;

    Xcp_DaqListFlags(daq) &= (uint8)(XCP_DAQ_FLAG_DIRECTION | XCP_DAQ_FLAG_TIMESTAMP | XCP_DAQ_FLAG_NO_PID);

    /* Check if all DAQ lists are stopped. */
    for( acIndex = XCP_INDEX_0; acIndex < Xcp_DataInformation.daq.daqCount; acIndex++ )
    {
        if( XCP_VALUE_0 != (Xcp_DaqListFlags(acIndex) & (uint8)XCP_DAQ_FLAG_RUNNING) )
        {
            reValue = XCP_VALUE_1;
        }
    }
    if( XCP_VALUE_0 == reValue )
    {
        Xcp_DataInformation.sessionStatus &= (uint8)(~XCP_SS_DAQ) & XCP_U8_MASK;
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
        Xcp_QueueInit();
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
    }
}

/*
********************************************************************************
* Function Name: Xcp_StopAllSelectedDaq
*
* Explanation: Stop all selected DAQs.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_StopAllSelectedDaq(void)
{
    uint8 daq;

    for( daq = XCP_INDEX_0; daq < Xcp_DataInformation.daq.daqCount; daq++ )
    {
        if( XCP_VALUE_0 != (Xcp_DaqListFlags(daq) & (uint8)XCP_DAQ_FLAG_SELECTED) )
        {
            Xcp_StopDaq(daq);
            Xcp_DaqListFlags(daq) &= (uint8)(~XCP_DAQ_FLAG_SELECTED) & XCP_U8_MASK;
        }
    }
}

/*
********************************************************************************
* Function Name: Xcp_StopAllDaq
*
* Explanation: Stop all DAQs.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_StopAllDaq(void)
{
    uint8 daq;

    for( daq = XCP_INDEX_0; daq < Xcp_DataInformation.daq.daqCount; daq++ )
    {
        Xcp_DaqListFlags(daq) &= (uint8)(XCP_DAQ_FLAG_DIRECTION | XCP_DAQ_FLAG_TIMESTAMP | XCP_DAQ_FLAG_NO_PID);
    }
    Xcp_DataInformation.sessionStatus &= (uint8)(~XCP_SS_DAQ) & XCP_U8_MASK;

#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
    Xcp_QueueInit();
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
    Xcp_FreeDaq();
}
#endif  /* #ifdef XCP_ENABLE_DAQ */

/*
********************************************************************************
* Function Name: XCP_RecordError
*
* Explanation: xcp command handles error jumps.
*
* param: err: Return Codes
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_RecordError(uint8 err)
{
    if( XCP_E_NO_ERROR != err )
    {
        /* The type of err is CRP_CMd_BUSY. */
        if( XCP_CRC_CMD_BUSY == err )
        {
            Xcp_DataInformation.respDataLen = XCP_VALUE_2;
            XCP_CRM_CMD = (uint8)XCP_PID_ERR;
            XCP_CRM_ERR = (uint8)err;
        }
        /* Set negative response message information. */
        else if( XCP_CRC_PENGDING != err )
        {
            Xcp_DataInformation.respDataLen = XCP_VALUE_2;
            XCP_CRM_CMD = (uint8)XCP_PID_ERR;
            XCP_CRM_ERR = (uint8)err;
            if( XCP_VALUE_0 != (Xcp_DataInformation.sessionStatus & XCP_SS_DAQ) )
            {
                /* Stop all DAQ. */
                Xcp_StopAllDaq();
            }
        }
        else  /* XCP_CRC_PENGDING == err */
        {
            /* Do nothing. */
        }
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_Sync
*
* Explanation: Execute command CC_Sync.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_Sync(void)
{
    /* Always return a negative response with the error code ERR_CMD_SYNCH. */
    Xcp_DataInformation.respDataLen = XCP_CRM_SYNCH_LEN;
    /* CRM[0] */
    XCP_CRM_CMD = XCP_PID_ERR;
    /* CRM[1] */
    XCP_CRM_ERR = XCP_CRC_CMD_SYNCH;
}

#ifdef XCP_ENABLE_COMM_MODE_INFO
/*
********************************************************************************
* Function Name: Xcp_CC_GetCommModeInfo
*
* Explanation: Execute command CC_GetCommModeInfo.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_GetCommModeInfo(void)
{
    Xcp_DataInformation.respDataLen = XCP_CRM_GET_COMM_MODE_INFO_LEN;

#if( XCP_BLOCK_DOWNLOAD == STD_ON )
    /* CRM[2] */
    XCP_CRM_GET_COMM_MODE_INFO_COMM_OPTIONAL = XCP_CMO_MASTER_BLOCK_MODE;
    /* CRM[4] */
    XCP_CRM_GET_COMM_MODE_INFO_MAX_BS = XCPBLOCK_SIZE;
    /* CRM[5] */
    XCP_CRM_GET_COMM_MODE_INFO_MIN_ST = XCPBLOCK_MIN_ST;
#else
    /* CRM[2] */
    XCP_CRM_GET_COMM_MODE_INFO_COMM_OPTIONAL = XCP_VALUE_0;
    /* CRM[4] */
    XCP_CRM_GET_COMM_MODE_INFO_MAX_BS = XCP_VALUE_0;
    /* CRM[5] */
    XCP_CRM_GET_COMM_MODE_INFO_MIN_ST = XCP_VALUE_0;
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */
    /* CRM[6] */
    XCP_CRM_GET_COMM_MODE_INFO_QUEUE_SIZE = XCP_VALUE_0;
    /* CRM[7] */
    XCP_CRM_GET_COMM_MODE_INFO_DRIVER_VERSION = (uint8)(((XCP_VERSION & XCP_DATA_MASK_0F00) >> XCP_SHIFT_4)
                                                    | (XCP_VERSION & XCP_DATA_MASK_000F));
}
#endif  /* #ifdef XCP_ENABLE_COMM_MODE_INFO */

/*
********************************************************************************
* Function Name: Xcp_InitCalPage
*
* Explanation: xcp init calibration page.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_InitCalPage(void)
{
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
    XcpCalOffset = (sint32)XCP_INIT_0;
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM */
    Xcp_DataInformation.pageInd = XCP_INIT_0;
}

/*
********************************************************************************
* Function Name: Xcp_CC_Disconnect
*
* Explanation: Execute command CC_disconnect.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_Disconnect(void)
{
    Xcp_DataInformation.respDataLen = XCP_CRM_DISCONNECT_LEN;
    Xcp_Disconnect();
    /* xcp init calibration page. */
    Xcp_InitCalPage();
}

/*
********************************************************************************
* Function Name: Xcp_CC_GetID
*
* Explanation: Execute command CC_GetID.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_GetID
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    Xcp_DataInformation.respDataLen = XCP_CRM_GET_ID_LEN;
    XCP_CRM_GET_ID_MODE = XCP_VALUE_0;
    XCP_CRM_GET_ID_LENGTH = XCP_VALUE_0;
    /* Which types are supported by the slave device is implementation specific.
       Type = ASAM MC2 , only support this style. */
    if( XCP_CRO_GET_ID_TYPE == XCP_IDT_ASAM_NAME )
    {
        XCP_CRM_GET_ID_LENGTH = (uint32)XCP_STATIONIDLENGTH;
        XCP_SETMTA(Xcp_GetPointer(XCP_U8_MASK, (uint32)(&Xcp_StationId[XCP_INDEX_0])), XCP_U8_MASK);
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_GetStatus
*
* Explanation: Execute command CC_GetStatus.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_GetStatus(void)
{
    Xcp_DataInformation.respDataLen = XCP_CRM_GET_STATUS_LEN;
    /* CRM[1] */
    XCP_CRM_GET_STATUS_STATUS = Xcp_DataInformation.sessionStatus;
#if( XCP_ENABLE_SEED_KEY == STD_ON )
    /* Return current resource protection status. If a bit is one,
       the associated resource is locked. */
    XCP_CRM_GET_STATUS_PROTECTION = Xcp_DataInformation.protectionStatus;
#else
    /* CRM[2] */
    XCP_CRM_GET_STATUS_PROTECTION = XCP_VALUE_0;
#endif  /* XCP_ENABLE_SEED_KEY == STD_ON */
    /* Session configuration ID not available. CRM[4] CRM[5] */
    XCP_CRM_GET_STATUS_CONFIG_ID = XCP_VALUE_0;
}

#if( XCP_ENABLE_SEED_KEY == STD_ON )
/*
********************************************************************************
* Function Name: Xcp_CC_GetSeed
*
* Explanation: Execute command CC_GetSeed.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_GetSeed
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
    uint8 maxCto = xcpConnCfgPtr->Xcp_Max_Cto;
    uint16 maxLen = maxCto - XCP_CRO_GET_SEED_HEAD_LEN;

    Xcp_ResourceMode = XCP_CRO_GET_SEED_RESOURCE;

    if( XCP_RM_CAL_PAG == Xcp_ResourceMode ||
        XCP_RM_DAQ == Xcp_ResourceMode ||
        XCP_RM_STIM == Xcp_ResourceMode ||
        XCP_RM_PGM == Xcp_ResourceMode )
    {
        if( XCP_CRO_GET_SEED_MODE == XCP_GET_SEED_REST_PART )
        {
            /* Determine if the order of instructions is correct. */
            if( Xcp_ResourceMode == Xcp_SafeResoure )
            {
                Xcp_SafeLen -= maxLen;
                XCP_CRM_GET_SEED_LENGTH = Xcp_SafeLen;
                if( Xcp_SafeLen > maxLen )
                {
                    Xcp_MemCpy8(XCP_CRM_GET_SEED_DATA, &Xcp_Resource_Array[Xcp_SafeAddLen], (uint32)maxLen);
                    Xcp_DataInformation.respDataLen = maxCto;
                    Xcp_SafeAddLen += maxLen;
                }
                else
                {
                    Xcp_MemCpy8(XCP_CRM_GET_SEED_DATA, &Xcp_Resource_Array[Xcp_SafeAddLen], (uint32)Xcp_SafeLen);
                    Xcp_DataInformation.respDataLen = (Xcp_SafeLen + XCP_CRO_GET_SEED_HEAD_LEN);
                    Xcp_SafeLen = XCP_VALUE_0;
                    Xcp_SafeResoure = XCP_VALUE_0;
                }
            }
            else
            {
                /* Command 1 not sent after command 0. */
                Xcp_RecordError(XCP_CRC_SEQUENCE);
                /* Recovery status. */
                Xcp_SafeResoure = XCP_VALUE_0;
                Xcp_SafeFlag = FALSE;
                Xcp_SafeAddLen = XCP_VALUE_0;
                Xcp_SafeLen = XCP_VALUE_0;
            }
        }
        else
        {
            /* locked */
            if( (Xcp_DataInformation.protectionStatus & XCP_CRO_GET_SEED_RESOURCE) != XCP_VALUE_0 )
            {
                /* Determine whether the previous seed acquisition was completed. */
                if( (XCP_VALUE_0 == Xcp_SafeLen) && (XCP_VALUE_0 == Xcp_SafeResoure) && (FALSE == Xcp_SafeFlag) )
                {
                    (void)XcpGetSeed();
                    Xcp_SafeResoure = XCP_CRO_GET_SEED_RESOURCE;
                    Xcp_SafeFlag = TRUE;
                    Xcp_SafeAddLen = XCP_VALUE_0;
                    Xcp_SafeLen = XCP_SAFELEN;
                    XCP_CRM_GET_SEED_LENGTH = XCP_SAFELEN;
                    if( XCP_SAFELEN <= maxLen )
                    {
                        Xcp_MemCpy8(XCP_CRM_GET_SEED_DATA, Xcp_Resource_Array, (uint32)XCP_SAFELEN);
                        Xcp_DataInformation.respDataLen = XCP_CRM_GET_SEED_LEN;
                        Xcp_SafeLen = XCP_VALUE_0;
                        Xcp_SafeResoure = XCP_VALUE_0;
                    }
                    else
                    {
                        Xcp_MemCpy8(XCP_CRM_GET_SEED_DATA, Xcp_Resource_Array, (uint32)maxLen);
                        Xcp_DataInformation.respDataLen = maxCto;
                        Xcp_SafeAddLen += maxLen;
                    }
                }
                else
                {
                    /* Seed acquisition not completed, proceed to obtain new seeds. */
                    Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
                    /* Recovery status. */
                    Xcp_SafeResoure = XCP_VALUE_0;
                    Xcp_SafeFlag = FALSE;
                    Xcp_SafeAddLen = XCP_VALUE_0;
                    Xcp_SafeLen = XCP_VALUE_0;
                }
            }
            else  /* Unlocked */
            {
                /* Return 0 if the resource is unprotected. */
                Xcp_DataInformation.respDataLen = XCP_CRO_GET_SEED_HEAD_LEN;
                XCP_CRM_GET_SEED_LENGTH = XCP_VALUE_0;
            }
        }
    }
    else
    {
        /* Request ID error. */
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
        Xcp_SafeResoure = XCP_VALUE_0;
        Xcp_SafeFlag = FALSE;
        Xcp_SafeAddLen = XCP_VALUE_0;
        Xcp_SafeLen = XCP_VALUE_0;
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_UnLock
*
* Explanation: Execute command CC_UnLock.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_UnLock
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
    boolean unlockFlag = FALSE;
    uint8 maxCto = xcpConnCfgPtr->Xcp_Max_Cto;
    uint8 maxLen = maxCto - XCP_VALUE_2;
    uint8 reVal = XCP_E_NOT_OK;

    if( (TRUE == Xcp_SafeFlag) && (XCP_VALUE_0 == Xcp_SafeLen) )/* WangM */
    {
        if( XCP_CRO_UNLOCK_LENGTH > maxLen )
        {
            reVal = XcpUnlock(XCP_CRO_UNLOCK_KEY, maxLen);
        }
        else
        {
            reVal = XcpUnlock(XCP_CRO_UNLOCK_KEY, XCP_CRO_UNLOCK_LENGTH);
            unlockFlag = TRUE;
            Xcp_SafeFlag = FALSE;
        }
        if( XCP_E_NOT_OK == reVal )
        {
            /* Key wrong! */
            /* Send ERR_ACCESS_LOCKED and go to disconnected state. */
            Xcp_Disconnect();
            Xcp_RecordError(XCP_CRC_ACCESS_LOCKED);
            Xcp_SafeFlag = FALSE;
        }
        else if( FALSE == unlockFlag )
        {
            XCP_CRM_UNLOCK_PROTECTION = Xcp_DataInformation.protectionStatus;
            Xcp_DataInformation.respDataLen = XCP_CRM_UNLOCK_LEN;
        }
        else
        {
            /* Nnlock (reset) the appropriate resource protection mask bit. */
            Xcp_DataInformation.protectionStatus &= (uint8)~Xcp_ResourceMode;
            /* And return the current resource protection status. */
            XCP_CRM_UNLOCK_PROTECTION = Xcp_DataInformation.protectionStatus;
            Xcp_DataInformation.respDataLen = XCP_CRM_UNLOCK_LEN;
        }
		//Xcp_SafeLen = XCP_VALUE_0;/* WangM */
    }
    else
    {
        Xcp_RecordError(XCP_CRC_SEQUENCE);
        /* Recovery status. */
        Xcp_SafeFlag = FALSE;
        Xcp_SafeAddLen = XCP_VALUE_0;
        Xcp_SafeLen = XCP_VALUE_0;
    }
}
#endif  /* XCP_ENABLE_SEED_KEY == STD_ON */

#ifdef XCP_ENABLE_CALIBRATION_PAGE
/*
********************************************************************************
* Function Name: ApplXcpSetCalPage
*
* Explanation: Set calibration page.
*
* param: segment: calibration segment.
*        page: calibration page.
*        mode: calibration mode.
*
* retval: uint8: Always return 0.
********************************************************************************
*/
static FUNC(uint8, XCP_CODE) ApplXcpSetCalPage(uint8 segment, uint8 page, uint8 mode)
{
    /* Reserved */
    XCP_DUMMY_STATEMENT(segment);
    XCP_DUMMY_STATEMENT(page);
    XCP_DUMMY_STATEMENT(mode);

    return XCP_VALUE_0;
}

/*
********************************************************************************
* Function Name: ApplXcpGetCalPage
*
* Explanation: Get calibration page.
*
* param: avcSegment: calibration segment.
*        avcMode: calibration mode.
*
* retval: uint8: calibration page.
********************************************************************************
*/
static FUNC(uint8, XCP_CODE) ApplXcpGetCalPage(uint8 avcSegment, uint8 avcMode)
{
    uint8 returnValue = XCP_INIT_0;

    XCP_DUMMY_STATEMENT(avcSegment);

    if( (avcMode & (XCP_CAL_ECU | XCP_CAL_XCP)) == XCP_CAL_ECU )
    {
        returnValue = REFERENCE_PAGE;
    }
    else if( (avcMode & (XCP_CAL_ECU | XCP_CAL_XCP)) == XCP_CAL_XCP )
    {
        returnValue = XCP_WORKING_PAGE;
    }
    else
    {
        returnValue = XCP_WORKING_PAGE;
    }

    return returnValue;
}
#endif  /* #ifdef XCP_ENABLE_CALIBRATION_PAGE */

#ifdef XCP_ENABLE_CALIBRATION_PAGE
/*
********************************************************************************
* Function Name: Xcp_CC_SetCalpage
*
* Explanation: Execute command CC_SetCalpage.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_SetCalpage
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
#if( RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY )
    uint8 ret = XCP_E_NOT_OK;
#endif  /* RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY */
    /* Judge whether the segment and page is out of range. */
    if( XCP_CRO_SET_CAL_PAGE_SEGMENT < XCP_VALUE_2 )
    {
        if( XCP_CRO_SET_CAL_PAGE_PAGE < XCP_VALUE_2 )
        {
            Xcp_DataInformation.pageInd = XCP_CRO_SET_CAL_PAGE_PAGE;

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
            /* Working Page. */
            if( XCP_WORKING_PAGE == Xcp_DataInformation.pageInd )
            {
                XcpCalOffset = (sint32)(XCP_CALRAM_ADDR(Xcp_MapPageIdx) - XCP_CALFLASH_ADDR(Xcp_MapPageIdx));
            }
            else
            {
                XcpCalOffset = (sint32)XCP_VALUE_0;
            }
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
            if( REFERENCE_PAGE == Xcp_DataInformation.pageInd )
            {
                Xcp_CalVectReset(&Xcp_VectList);
            }
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */
            /* Sets the access mode for a calibration data segment. */
            (void)ApplXcpSetCalPage(XCP_CRO_SET_CAL_PAGE_SEGMENT, XCP_CRO_SET_CAL_PAGE_PAGE, XCP_CRO_SET_CAL_PAGE_MODE);
#if( RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY )
            ret = XcpOverlayMapping(XCP_CRO_SET_CAL_PAGE_SEGMENT, XCP_CRO_SET_CAL_PAGE_PAGE, XCP_CRO_SET_CAL_PAGE_MODE);
            if( XCP_E_NOT_OK == ret )
            {
                Xcp_RecordError(XCP_CRC_PAGE_MODE_NOT_VALID);
            }
#endif  /* RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY */
        }
        else
        {
            Xcp_RecordError(XCP_CRC_PAGE_NOT_VALID);
        }
    }
    else
    {
        Xcp_RecordError(XCP_CRC_SEGMENT_NOT_VALID);
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_GetCalPage
*
* Explanation: Execute command CC_GetCalPage.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_GetCalPage
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    Xcp_DataInformation.respDataLen = XCP_CRM_GET_CAL_PAGE_LEN;
    /* CRM[3] */
    XCP_CRM_GET_CAL_PAGE_PAGE = ApplXcpGetCalPage(
                                XCP_CRO_GET_CAL_PAGE_SEGMENT,
                                XCP_CRO_GET_CAL_PAGE_MODE);
}

/*
********************************************************************************
* Function Name: Xcp_CC_GetPagProcessorInfo
*
* Explanation: Execute command CC_GetPagProcessorInfo.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_GetPagProcessorInfo(void)
{
    Xcp_DataInformation.respDataLen = XCP_CRM_GET_PAG_PROCESSOR_INFO_LEN;
    /* CRM[1] */
    XCP_CRM_GET_PAG_PROCESSOR_INFO_MAX_SEGMENT = (uint8)XCP_MAXSEGMENT;
#ifdef XCP_ENABLE_PAGE_FREEZE
    /* CRM[2] */
    /* FREEZE_SUPPORTED = 1 */
    XCP_CRM_GET_PAG_PROCESSOR_INFO_PROPERTIES = XCP_VALUE_1;
#else
    /* FREEZE_SUPPORTED = 0 */
    XCP_CRM_GET_PAG_PROCESSOR_INFO_PROPERTIES = XCP_VALUE_0;
#endif  /* #ifdef XCP_ENABLE_PAGE_FREEZE */
}
#endif  /* #ifdef XCP_ENABLE_CALIBRATION_PAGE */

/*
********************************************************************************
* Function Name: Xcp_CC_GetSegmentInfo
*
* Explanation: Execute command CC_GetSegmentInfo.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_GetSegmentInfo
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    if( XCP_CRO_GET_SEGMENT_INFO_NUMBER >= (uint8)XCP_MAXSEGMENT )
    {
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
    }
    else
    {
        Xcp_DataInformation.respDataLen = XCP_CRM_GET_SEGMENT_INFO_LEN;
        /*  Get standard info for a segment.
            SEGMENT_INFO and MAPPING_INDEX are don't care.
        */
        if( XCP_CRO_GET_SEGMENT_INFO_MODE == XCP_GET_SEGMENT_STANDARD_INFO )
        {
            /* CRM[1] */
            XCP_CRM_GET_SEGMENT_INFO_MAX_PAGES = XCP_VALUE_2;
            /* CRM[2] */
            XCP_CRM_GET_SEGMENT_INFO_ADDRESS_EXTENSION = XCP_VALUE_0;
            /* CRM[3] */
            XCP_CRM_GET_SEGMENT_INFO_MAX_MAPPING = XCP_VALUE_0;
            /* CRM[4] */
            XCP_CRM_GET_SEGMENT_INFO_COMPRESSION = XCP_VALUE_0;
            /* CRM[5] */
            XCP_CRM_GET_SEGMENT_INFO_ENCRYPTION = XCP_VALUE_0;
        }
        /* Get basic address info for a segment:
           SEGMENT_INFO contains address range information and
           MAPPING_INDEX is don't care
           Get address mapping for a segment:
           SEGMENT_INFO contains address range information and
           MAPPING_INDEX indicates the range MAPPING_INFO belongs to
        */
        if( (XCP_CRO_GET_SEGMENT_INFO_MODE == XCP_GET_SEGMENT_BASIC_ADDR_INFO) ||
            (XCP_CRO_GET_SEGMENT_INFO_MODE == XCP_GET_SEGMENT_ADDR_MAPPING_INFO) )
        {
        /* mode = 0
           If SEGMENT_INFO = 0 , this command returns the
           address of this SEGMENT in BASIC_INFO.
           If SEGMENT_INFO = 1 , this command returns the
           length of this SEGMENT in BASIC_INFO.

           mode = 2
           If SEGMENT_INFO = 0 , this command returns the source
           address for this MAPPING_INDEX in MAPPING_INFO.
           If SEGMENT_INFO = 1 , this command returns the
           destination address for this MAPPING_INDEX in MAPPING_INFO.
           If SEGMENT_INFO = 2 , this command returns the
           length for this MAPPING_INDEX in MAPPING_INFO.
        */
            XCP_CRM_GET_SEGMENT_INFO_MAPPING_INFO = XCP_VALUE_0;
        }
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_GetPageInfo
*
* Explanation: Execute command CC_GetPageInfo.
*
* param: pCmd: Accept instructions and parameters.
*        err: error code.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_GetPageInfo
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    /* Determine if segments and pages to view are out of range. */
    if( (XCP_CRO_GET_PAGE_INFO_SEGMENT_NUMBER > ((uint8)(XCP_MAXSEGMENT - XCP_VALUE_1) & XCP_U8_MASK)) ||
        (XCP_CRO_GET_PAGE_INFO_PAGE_NUMBER > ((uint8)(XCP_MAXPAGES - XCP_VALUE_1) & XCP_U8_MASK)) )
    {
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
    }
    else
    {
        Xcp_DataInformation.respDataLen = XCP_CRM_GET_PAGE_INFO_LEN;
        /* CRM[1] */
        XCP_CRM_GET_PAGE_INFO_PROPERTIES = XCP_VALUE_0;
        /* A subsequent return value should be added. */
    }
}

#ifdef XCP_ENABLE_PAGE_COPY
/*
********************************************************************************
* Function Name: Xcp_CC_CopyCalPage
*
* Explanation: Execute command CC_CopyCalPage.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_CopyCalPage
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd,
)
{
    uint8 err = XCP_INIT_0;

    Xcp_DataInformation.respDataLen = XCP_CRM_COPY_CAL_PAGE_LEN;
    /* Copy one calibration page to another. */
    err = ApplXcpCopyCalPage( XCP_CRO_COPY_CAL_PAGE_SRC_SEGMENT,
                              XCP_CRO_COPY_CAL_PAGE_SRC_PAGE,
                              XCP_CRO_COPY_CAL_PAGE_DEST_SEGMENT,
                              XCP_CRO_COPY_CAL_PAGE_DEST_PAGE);
    if( (uint8)XCP_CMD_PENDING == err )
    {
        /* Reserved */
    }
    else if( XCP_VALUE_0 != err )
    {
        Xcp_RecordError(err);
    }
    else
    {
        /* Do nothing. */
    }
}
#endif  /* #ifdef XCP_ENABLE_PAGE_COPY */

/*
********************************************************************************
* Function Name: Xcp_CC_SetMta
*
* Explanation: Execute command CC_SetMta.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_SetMta
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    /* Initialize a pointer (XCP_CRO_SET_MTA_ADDR + XCP_CRO_SET_MTA_EXT). */
    XCP_SETMTA(Xcp_GetPointer(XCP_CRO_SET_MTA_EXT, XCP_CRO_SET_MTA_ADDR), XCP_CRO_SET_MTA_EXT);
}

/*
********************************************************************************
* Function Name: Xcp_CC_Download
*
* Explanation: Execute command CC_Download.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_Download
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 size = XCP_INIT_0;
    uint8 err = XCP_CMD_DENIED;
    uint8 prgramMaxSize = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];

    prgramMaxSize = (uint8)((xcpConnCfgPtr->Xcp_Max_Cto - XCP_CRM_DOWNLOAD_DATA_OFFSET) / XCP_AG);

    XCP_CHECK_RESOURCE_PROTECTION(XCP_RM_CAL_PAG)
    /* Check whether there are enough resources available in order to cover the complete download request. */
    size = XCP_CRO_DOWNLOAD_SIZE;
#if( XCP_BLOCK_DOWNLOAD == STD_ON )
    Xcp_DataInformation.nextDownloadSize = XCP_CRO_DOWNLOAD_SIZE;
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */

    if( prgramMaxSize < size )
    {
        size = prgramMaxSize;
#if( XCP_ONCAN_ENABLE == STD_ON )
        Xcp_CanGetStatus = TRUE;
#endif  /* XCP_ONCAN_ENABLE == STD_ON */
#if( XCP_ONETHERNET_ENABLE == STD_ON )
        Xcp_EthGetStatus = TRUE;
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
    }
    err = Xcp_WriteMta(size, XCP_CRO_DOWNLOAD_DATA);

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
    if( (uint8)XCP_CMD_PENDING == err )
    {
        /* When the download is successful, set the wait bit and reduce the download volume. */
#if( XCP_BLOCK_DOWNLOAD == STD_ON )
        Xcp_DataInformation.nextDownloadSize -= size;
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */
        /* Send pending */
        Xcp_SendFlag = FALSE;
    }
#elif( RTECALIBRATIONSUPPORT != XCP_CAL_METHOD_MMU )
    if( (uint8)XCP_CMD_DENIED == err )
    {
        Xcp_RecordError(XCP_CRC_WRITE_PROTECTED);
    }
#else
    XCP_DUMMY_STATEMENT(err);
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */
    /* When the download is successful, set the wait bit and reduce the download volume. */
#if( XCP_BLOCK_DOWNLOAD == STD_ON )
    Xcp_DataInformation.nextDownloadSize -= size;
    if( Xcp_DataInformation.nextDownloadSize > XCP_VALUE_0 )
    {
        /* Send pending. */
        Xcp_SendFlag = FALSE;
    }
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */
}

#if( XCP_BLOCK_DOWNLOAD == STD_ON )
/*
********************************************************************************
* Function Name: Xcp_CC_DownloadNext
*
* Explanation: Execute command CC_Download.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_DownloadNext
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 size = XCP_INIT_0;
    uint8 err = XCP_CMD_DENIED;
    uint8 prgramNextMaxSize = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];

    /* XCP_CRO_DOWNLOAD_NEXT_MAX_SIZE */
    prgramNextMaxSize = (uint8)((xcpConnCfgPtr->Xcp_Max_Cto - XCP_VALUE_2) / XCP_AG);
    XCP_CHECK_RESOURCE_PROTECTION(XCP_RM_CAL_PAG)
    /* Check whether there are enough resources available in order to cover the complete download request. */
    size = XCP_CRO_DOWNLOAD_NEXT_SIZE;

    if( XCP_CRO_DOWNLOAD_NEXT_SIZE != Xcp_DataInformation.nextDownloadSize )
    {
        Xcp_RecordError(XCP_CRC_SEQUENCE);
    }
    else
    {
        /* Copying of size bytes from XCP_CRO_DOWNLOAD_DATA to Xcp_DataInformation.mta. */
        if( prgramNextMaxSize < size )
        {
            err = Xcp_WriteMta(prgramNextMaxSize, XCP_CRO_DOWNLOAD_DATA);
            Xcp_DataInformation.nextDownloadSize -= prgramNextMaxSize;
#if( XCP_ONCAN_ENABLE == STD_ON )
            Xcp_CanGetStatus = TRUE;
#endif  /* XCP_ONCAN_ENABLE == STD_ON */
#if( XCP_ONETHERNET_ENABLE == STD_ON )
            Xcp_EthGetStatus = TRUE;
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
        }
        else
        {
            err = Xcp_WriteMta(size, XCP_CRO_DOWNLOAD_NEXT_DATA);
            Xcp_DataInformation.nextDownloadSize = XCP_VALUE_0;
            /* When using block transfer, resetting the pending bit is performed here. */
            Xcp_SendFlag = TRUE;
        }
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
        if( (uint8)XCP_CMD_PENDING == err )
        {
            /* pending */
        }
#elif( RTECALIBRATIONSUPPORT != XCP_CAL_METHOD_MMU )
        if( (uint8)XCP_CMD_DENIED == err )
        {
            Xcp_RecordError(XCP_CRC_WRITE_PROTECTED);
        }
        else
        {
            /* Do nothing. */
        }
#else
    XCP_DUMMY_STATEMENT(err);
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */
    }
}
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */

/*
********************************************************************************
* Function Name: Xcp_CC_DownloadMax
*
* Explanation: Execute command CC_DownloadMax.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_DownloadMax
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 errCode = XCP_E_NO_ERROR;
    uint8 downloadMaxSize = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];

    /* XCP_CRO_DOWNLOAD_MAX_MAX_SIZE */
    downloadMaxSize = (uint8)(xcpConnCfgPtr->Xcp_Max_Cto - XCP_VALUE_1);
    XCP_CHECK_RESOURCE_PROTECTION(XCP_RM_CAL_PAG)
    /* Copying of XCP_CRO_DOWNLOAD_MAX_MAX_SIZE bytes from
       XCP_CRO_DOWNLOAD_MAX_DATA to Xcp_DataInformation.mta. */
    errCode = Xcp_WriteMta(downloadMaxSize, XCP_CRO_DOWNLOAD_MAX_DATA);

    if( XCP_E_NO_ERROR != errCode )
    {
        Xcp_RecordError(errCode);
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_ShortDownload
*
* Explanation: Execute command CC_ShortDownload.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_ShortDownload
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 ret = XCP_CMD_DENIED;
    uint8 errorCode = XCP_E_NO_ERROR;
    uint8 size = XCP_INIT_0;
    uint8 downloadMaxSize = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];

    /* Get parameters from command string. */
    size = XCP_CRO_SHORT_DOWNLOAD_SIZE;

#if( XCP_SEED_KEY == STD_ON )
    CheckResourceProtection( XCP_RM_CAL_PAG );
#endif  /* XCP_SEED_KEY == STD_ON */

    /* Perform initial check of download size, resource protection. */
    if( XCP_CRO_SHORT_DOWNLOAD_CMD_LEN >= xcpConnCfgPtr->Xcp_Max_Cto )
    {
        errorCode = XCP_CRC_OUT_OF_RANGE;
        Xcp_RecordError(errorCode);
    }
    /* If checks passed, set MTA and copy data. MTA is incremented in WriteMta call. */
    else
    {
        /* Assign a pointer to a mta. */
        XCP_SETMTA(Xcp_GetPointer(XCP_CRO_SHORT_DOWNLOAD_EXT, XCP_CRO_SHORT_DOWNLOAD_ADDR), XCP_CRO_SHORT_DOWNLOAD_EXT);
        downloadMaxSize = (xcpConnCfgPtr->Xcp_Max_Cto - XCP_CRO_SHORT_DOWNLOAD_CMD_LEN) / XCP_AG;
        if( size > downloadMaxSize )
        {
            /* If the number of elements exceeds (MAX-CTO-8)/AG, error code ERR_OUT_OF_RANGE will be returned. */
            errorCode = XCP_CRC_OUT_OF_RANGE;
        }
        /* If checks passed, set MTA and copy data. MTA is incremented in WriteMta call. */
        else
        {
            size = size * XCP_AG;
            ret = Xcp_WriteMta(size, XCP_CRO_SHORT_DOWNLOAD_DATA);
            if( (XCP_CMD_OK != ret) && (XCP_E_NO_ERROR != errorCode) )
            {
                Xcp_RecordError(errorCode);
            }
        }
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_UpLoad
*
* Explanation: Execute command CC_UpLoad.
*
* param: pCmd: Accept instructions and parameters.
*        err: Error code.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_UpLoad
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 errCode = XCP_E_NO_ERROR;
    uint8 size = XCP_CRO_UPLOAD_SIZE;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
    /* XCP_CRM_UPLOAD_MAX_SIZE */
    uint8 uploadMaxSize = (uint8)(xcpConnCfgPtr->Xcp_Max_Cto - XCP_VALUE_1);

#if( XCP_BLOCK_UPLOAD == STD_ON )
    /* #20 If the number of requested bytes to be uploaded exceeds max CTO-1:
       Store missing number of bytes to be uploaded and copy maximum valid
       number of bytes from MTA. */
    if( (uint8)uploadMaxSize < size )
    {
        Xcp_DataInformation.nextDataBlockSize = size - (uint8)uploadMaxSize;
        size = (uint8)uploadMaxSize;
        errCode = Xcp_ReadMta(size, XCP_CRM_UPLOAD_DATA);
        if( XCP_E_NO_ERROR == errCode )
        {
            Xcp_DataInformation.respDataLen = (uint8)((XCP_CRM_UPLOAD_LEN + size) & XCP_U8_MASK);
            Xcp_DataInformation.sessionStatus |= (uint8)XCP_SS_BLOCK_UPLOAD;
        }
    }
    else
#else
    if( uploadMaxSize < size )
    {
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
    }
    else
#endif  /* XCP_BLOCK_UPLOAD == STD_ON */
    {
        /* Transfer data from mta to CRM[]. */
        errCode = Xcp_ReadMta(size, XCP_CRM_UPLOAD_DATA);
        if( XCP_E_NO_ERROR == errCode )
        {
            Xcp_DataInformation.respDataLen = (uint8)((XCP_CRM_UPLOAD_LEN + size) & XCP_U8_MASK);
        }
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_ShortUplod
*
* Explanation: Execute command CC_ShortUplod.
*
* param: pCmd: Accept instructions and parameters.
*        err: Error code.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_ShortUplod
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 errCode = XCP_E_NO_ERROR;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
    /* XCP_CRM_SHORT_UPLOAD_MAX_SIZE */
    uint8 shortUploadMaxSize = (uint8)(xcpConnCfgPtr->Xcp_Max_Cto - XCP_VALUE_1);

    if( XCP_CRO_SHORT_UPLOAD_SIZE > (uint8)shortUploadMaxSize )
    {
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
    }
    else
    {
        /* Get calibration address to Xcp_DataInformation.mta. */
        XCP_SETMTA(Xcp_GetPointer(XCP_CRO_SHORT_UPLOAD_EXT, XCP_CRO_SHORT_UPLOAD_ADDR), XCP_CRO_SHORT_UPLOAD_EXT);
        /* The content in Xcp_DataInformation.mta is copied to Xcp_DataInformation.responseBuff.bytes [x] for sending to the master. */
        errCode = Xcp_ReadMta(XCP_CRO_SHORT_UPLOAD_SIZE, XCP_CRM_SHORT_UPLOAD_DATA);
        if( XCP_E_NO_ERROR == errCode )
        {
            Xcp_DataInformation.respDataLen = (uint8)((XCP_CRM_SHORT_UPLOAD_LEN + XCP_CRO_SHORT_UPLOAD_SIZE) & XCP_U8_MASK);
        }
    }
}

#if( XCP_ENABLE_CHECKSUM == STD_ON )
/*
********************************************************************************
* Function Name: Xcp_CC_BuildCheckSum
*
* Explanation: Execute command CC_BuildCheckum.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_BuildCheckSum
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 errorCode = XCP_E_NO_ERROR;
    uint32 check_size = XCP_INIT_0;

    /* Initialization of checksum calculation. */
    Xcp_DataInformation.checkSum = (tXcpChecksumSumType)XCP_INIT_0;
    check_size = XCP_CRO_BUILD_CHECKSUM_SIZE;

    if( NULL_PTR == Xcp_DataInformation.mta )
    {
        errorCode = XCP_CRC_MEMORY_OVERFLOW;
    }
    else
    {
        errorCode = Xcp_MtaCheckValid((uint32)Xcp_DataInformation.mta, check_size, XCP_ACCESS_SCOPE_ALL, XCP_ACCESS_TYPE_READ);
    }

    if( XCP_E_NO_ERROR != errorCode )
    {
        Xcp_DataInformation.respDataLen = XCP_CRM_BUILD_CHECKSUM_LEN;
        /* Response length is arbitrary. */
        Xcp_RecordError(errorCode);
    }
    else
    {
        /* If the blocksize exceeds the allowed maximum transmit negative response. */
        if( check_size > XCP_CHECKSUMBLOCKSIZE )
        {
            /* Range, max. 64K-1 */
            XCP_CRM_BUILD_CHECKSUM_RESULT = XCP_CHECKSUMBLOCKSIZE;
            Xcp_DataInformation.respDataLen = XCP_CRM_BUILD_CHECKSUM_LEN;
            /* Response length is arbitrary. */
            Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
        }
        else
        {
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT )
            /* Used for checksum to read data. */
            Xcp_ChecksumFlag = TRUE;
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT */
            Xcp_DataInformation.checkSumSize = check_size * XCP_AG;
#if( XCP_CRC32 == XCP_CHECKSUM_TYPE )
            Xcp_DataInformation.crc32Flag = TRUE;
#endif  /* XCP_CRC32 == XCP_CHECKSUM_TYPE */
        }
    }
    /* Checksum calculation will be performed by XcpBackground(). */
}
#endif  /* XCP_ENABLE_CHECKSUM == STD_ON */

/*
********************************************************************************
* Function Name: ApplXcpGetTimestamp
*
* Explanation: Get time stamp.
*
* param: None
*
* retval: Xcp_TimestampType: The value of time stamp.
********************************************************************************
*/
static FUNC(Xcp_TimestampType, XCP_CODE) ApplXcpGetTimestamp(void)
{
    /* XCP timestamp. */
    Xcp_TimestampType xcpTimestamp = XCP_INIT_0;
    TickType counterTick = XCP_INIT_0;

    (void)GetCounterValue((CounterType)XCP_COUNTER_REF, &counterTick);
    xcpTimestamp = (Xcp_TimestampType)(counterTick);

    return xcpTimestamp;
}

#ifdef XCP_ENABLE_DAQ
/*
********************************************************************************
* Function Name: Xcp_CC_GetDaqProcessorInfo
*
* Explanation: Execute command CC_GetDaqProcessorInfo.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_GetDaqProcessorInfo(void)
{
    uint8 daqPropertyTimestamp = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];

    Xcp_DataInformation.respDataLen = XCP_CRM_GET_DAQ_PROCESSOR_INFO_LEN;

    if( XCPTS_NO_TIME_STAMP != xcpConnCfgPtr->XcpTimestampType )
    {
        daqPropertyTimestamp = XCP_DAQ_PROPERTY_TIMESTAMP;
    }

    /* CRM[1] */
    XCP_CRM_GET_DAQ_PROCESSOR_INFO_PROPERTIES = (uint8)( XCPDAQCONFIGTYPE
#if( XCP_PRESCALER_SUPPORTED == STD_ON )
        | XCP_DAQ_PROPERTY_PRESCALER
#endif  /* XCP_PRESCALER_SUPPORTED == STD_ON */
        | daqPropertyTimestamp
#ifdef XCP_ENABLE_DAQ_OVERRUN_INDICATION    /* XCP_DAQ_PROPERTY_OVERLOAD_INDICATION */
        | (uint8)XCP_DAQ_OVERLOAD_INDICATION_PID);
#endif  /* #ifdef XCP_ENABLE_DAQ_OVERRUN_INDICATION */
    /* CRM[2] CRM[3] */
    XCP_CRM_GET_DAQ_PROCESSOR_INFO_MAX_DAQ = Xcp_DataInformation.daq.daqCount;
#ifdef XCP_MAX_EVENT
    /* CRM[4] CRM[5] */
    XCP_CRM_GET_DAQ_PROCESSOR_INFO_MAX_EVENT = XCP_MAX_EVENT;
#else
    /* CRM[4] CRM[5] */
    XCP_CRM_GET_DAQ_PROCESSOR_INFO_MAX_EVENT = XCP_VALUE_0;
#endif  /* #ifdef XCP_MAX_EVENT */
    /* CRM[6] */
    XCP_CRM_GET_DAQ_PROCESSOR_INFO_MIN_DAQ = XCP_MIN_DAQ;
    /* DTO identification field type: Absolute ODT number. */
#if( XCP_IDENTIFICATION_FIELD_TYPE == XCP_ID_TYPE_ABSOLUTE )
    /* CRM[7] */
    XCP_CRM_GET_DAQ_PROCESSOR_INFO_DAQ_KEY_BYTE = (uint8)XCP_DAQ_HDR_PID;
#else
    /* CRM[7] */
    XCP_CRM_GET_DAQ_PROCESSOR_INFO_DAQ_KEY_BYTE = (uint8)XCP_DAQ_HDR_ODT_DAQB;
#endif  /* XCP_IDENTIFICATION_FIELD_TYPE == XCP_ID_TYPE_ABSOLUTE */
}

/*
********************************************************************************
* Function Name: Xcp_CC_GetDaqResolutionInfo
*
* Explanation: Execute command CC_GetDaqResolutionInfo.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_GetDaqResolutionInfo(void)
{
    uint8 timestampMode = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];

    Xcp_DataInformation.respDataLen = XCP_CRM_GET_DAQ_RESOLUTION_INFO_LEN;

    /* CRM[1] */
    XCP_CRM_GET_DAQ_RESOLUTION_INFO_GRANULARITY_DAQ = GRANULARITY_ODT_ENTRY_SIZE;
    /* CRM[2] */
    XCP_CRM_GET_DAQ_RESOLUTION_INFO_MAX_SIZE_DAQ = (uint8)XCP_ODT_ENTRY_SIZE_DAQ; 
    /* CRM[3] */
    XCP_CRM_GET_DAQ_RESOLUTION_INFO_GRANULARITY_STIM = GRANULARITY_ODT_ENTRY_SIZE;
    /* CRM[4] */
    XCP_CRM_GET_DAQ_RESOLUTION_INFO_MAX_SIZE_STIM = (uint8)XCP_ODT_ENTRY_SIZE_STIM;

    if( XCP_VALUE_0 < xcpConnCfgPtr->XcpTimestampType )
    {
        timestampMode = xcpConnCfgPtr->XcpTimestampType | XCP_TIMESTAMP_UNIT;
    }
    else
    {
        timestampMode = XCP_VALUE_0;
    }
    /* CRM[5] */
    XCP_CRM_GET_DAQ_RESOLUTION_INFO_TIMESTAMP_MODE = timestampMode;
    /* BCD coded */
    /* CRM[6] CRM[7] */
    XCP_CRM_GET_DAQ_RESOLUTION_INFO_TIMESTAMP_TICKS = XCP_TIMESTAMP_TICKS;
}

/*
********************************************************************************
* Function Name: Xcp_CC_GetDaqEventInfo
*
* Explanation: Execute command CC_GetDaqEventInfo.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_GetDaqEventInfo
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 event = (uint8)XCP_CRO_GET_DAQ_EVENT_INFO_EVENT;

    if( (uint8)XCP_MAX_EVENT <= event )
    {
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
    }
    else
    {
        Xcp_DataInformation.respDataLen = XCP_CRM_GET_DAQ_EVENT_INFO_LEN;
        XCP_CRM_GET_DAQ_EVENT_INFO_PROPERTIES = Xcp_EventChannel[event].XcpEventChannelType;
        XCP_CRM_GET_DAQ_EVENT_INFO_MAX_DAQ_LIST = Xcp_EventChannel[event].XcpEventChannelMaxDaqList;
        XCP_CRM_GET_DAQ_EVENT_INFO_NAME_LENGTH = XcpEventNameLength[event];
        XCP_CRM_GET_DAQ_EVENT_INFO_TIME_CYCLE = Xcp_EventChannel[event].XcpEventChannelTimeCycle;
        XCP_CRM_GET_DAQ_EVENT_INFO_TIME_UNIT = Xcp_EventChannel[event].XcpEventChannelTimeUnit >> XCP_SHIFT_4;
        /* 0U Event channel prioritization is not supported. */
        XCP_CRM_GET_DAQ_EVENT_INFO_PRIORITY = Xcp_EventChannel[event].XcpEventChannelPriority;
        XCP_SETMTA( Xcp_GetPointer(XCP_U8_MASK, (uint32)(XcpEventName[event])), XCP_U8_MASK);
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_FreeDaq
*
* Explanation: Execute command CC_FreeDaq.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_FreeDaq(void)
{
    XCP_CHECK_RESOURCE_PROTECTION(XCP_RM_DAQ)
    Xcp_FreeDaq();
}

/*
********************************************************************************
* Function Name: Xcp_CC_AllocDaq
*
* Explanation: Execute command CC_AllocDaq.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_AllocDaq
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 err = XCP_INIT_0;
    uint8 count = (uint8)XCP_CRO_ALLOC_DAQ_COUNT;

    err = Xcp_AllocDaq(count);

    if( XCP_VALUE_0 != err )
    {
        Xcp_RecordError(err);
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_AllocOdt
*
* Explanation: Execute command CC_AllocOdt.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_AllocOdt
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 err = XCP_INIT_0;
    /* Obtain the DAQ number that needs to be modified. */
    uint8 daq = (uint8)XCP_CRO_ALLOC_ODT_DAQ;
    uint8 count = XCP_CRO_ALLOC_ODT_COUNT;

    if( (XCP_VALUE_0 == Xcp_DataInformation.daq.daqCount) || (XCP_VALUE_0 != Xcp_DataInformation.daq.odtEntryCount) )
    {
        Xcp_RecordError(XCP_CRC_SEQUENCE);
    }
    else
    {
        err = Xcp_AllocOdt(daq, count);
        if( XCP_VALUE_0 != err )
        {
            Xcp_RecordError(err);
        }
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_AllocOdtEntry
*
* Explanation: Execute command CC_AllocOdtEntry.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_AllocOdtEntry
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 err = XCP_INIT_0;
    uint8 daq = (uint8)XCP_CRO_ALLOC_ODT_ENTRY_DAQ;
    uint8 odt = XCP_CRO_ALLOC_ODT_ENTRY_ODT;
    uint8 count = XCP_CRO_ALLOC_ODT_ENTRY_COUNT;

    if( (daq >= Xcp_DataInformation.daq.daqCount) || (odt >= (uint8)Xcp_DaqListOdtCount(daq)) )
    {
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
    }
    else
    {
        err = Xcp_AllocOdtEntry(daq, odt, count);
        if( XCP_VALUE_0 != err )
        {
            Xcp_RecordError(err);
        }
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_GetDaqListMode
*
* Explanation: Execute command CC_GetDaqListMode.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_GetDaqListMode
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 daq = (uint8)XCP_CRO_GET_DAQ_LIST_MODE_DAQ;

    if( daq >= Xcp_DataInformation.daq.daqCount )
    {
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
    }
    else
    {
        Xcp_DataInformation.respDataLen = XCP_CRM_GET_DAQ_LIST_MODE_LEN;
        /* CRM[1] */
        XCP_CRM_GET_DAQ_LIST_MODE_MODE = Xcp_DaqListFlags(daq);
#ifdef XCP_MAX_EVENT
        /* Lookup in eventDaq[] / Xcp_DaqListEventChannel(daq). */
        XCP_CRM_GET_DAQ_LIST_MODE_EVENTCHANNEL = XcpConf_XcpEventChannel_0;
#else
        XCP_CRM_GET_DAQ_LIST_MODE_EVENTCHANNEL = Xcp_DaqListEventChannel(daq);
#endif  /* #ifdef XCP_MAX_EVENT */

#if( XCP_PRESCALER_SUPPORTED == STD_ON )
        /* CRM[6] */
        XCP_CRM_GET_DAQ_LIST_MODE_PRESCALER = Xcp_DaqListPrescaler(daq);
#else
        /* CRM[6] */
        XCP_CRM_GET_DAQ_LIST_MODE_PRESCALER = XCP_DAQ_LIST_PRESCALER;
#endif  /* XCP_PRESCALER_SUPPORTED == STD_ON */
        /* DAQ-list prioritization is not supported. */
        XCP_CRM_GET_DAQ_LIST_MODE_PRIORITY = XCP_DAQ_LIST_PRIORITY;
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_SetDaqListMode
*
* Explanation: Execute command CC_SetDaqListMode.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_SetDaqListMode
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 errorCode = XCP_E_NO_ERROR;
    uint8 daq = (uint8)XCP_CRO_SET_DAQ_LIST_MODE_DAQ;
    uint8 xcpPrescaler = XCP_CRO_SET_DAQ_LIST_MODE_PRESCALER;
    uint8 event = (uint8)(XCP_CRO_SET_DAQ_LIST_MODE_EVENTCHANNEL & XCP_U8_MASK);
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];

    if( (daq >= Xcp_DataInformation.daq.daqCount) || ((uint8)XCP_MAX_EVENT <= event) )
    {
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
    }

    if( XCP_VALUE_0 == xcpConnCfgPtr->XcpTimestampType )
    {
        if( (XCP_CRO_SET_DAQ_LIST_MODE_MODE & XCP_DAQ_LIST_TIMESTAMP) > XCP_VALUE_0 )
        {
            Xcp_RecordError(XCP_CRC_CMD_SYNTAX);
        }
    }

    /* Priorization is not supported. */
    if( XCP_CRO_SET_DAQ_LIST_MODE_PRIORITY != XCP_VALUE_0 )
    {
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
    }

#if( XCP_PRESCALER_SUPPORTED == STD_OFF )
    if( xcpPrescaler != XCP_DAQ_LIST_PRESCALER )
    {
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
    }
#endif  /* XCP_PRESCALER_SUPPORTED == STD_OFF */

    if( XCP_PID_ERR != XCP_CRM_CMD )
    {
#if( XCP_PRESCALER_SUPPORTED == STD_ON )
        if( XCP_VALUE_0 == xcpPrescaler )
        {
            xcpPrescaler = XCP_DAQ_LIST_PRESCALER;
        }
        Xcp_DaqListPrescaler(daq) = xcpPrescaler;
#endif  /* XCP_PRESCALER_SUPPORTED == STD_ON */

#if( defined (XCP_MAX_EVENT) && ! defined (XCP_ENABLE_MULDAQ_EVENT) )
        Xcp_DataInformation.daq.eventDaq[event] = daq;
#else
        Xcp_DaqListEventChannel(daq) = event;
#endif  /* defined (XCP_MAX_EVENT) && ! defined (XCP_ENABLE_MULDAQ_EVENT) */
        Xcp_DaqListFlags(daq) = XCP_CRO_SET_DAQ_LIST_MODE_MODE;
        /* STIM or DAQ */
        if( XCP_VALUE_0 != (Xcp_DaqListFlags(daq) & XCP_DAQ_FLAG_DIRECTION) )
        {
#if( (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT) || (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT) )
            /* Check the current page type. */
            if( XCP_WORKING_PAGE == Xcp_DataInformation.pageInd )
            {
#endif  /* (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT) || (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT) */
                /* Check if STIM mode is supported. */
                errorCode = Xcp_MtaCheckValid((uint32)Xcp_DataInformation.pOdtEntryAddr[XCP_INDEX_0], Xcp_DataInformation.pOdtEntrySize[XCP_INDEX_0],
                                            XCP_ACCESS_SCOPE_DAQ_STIM, XCP_ACCESS_TYPE_WRITE);
#if( (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT) || (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT) )
            }
            else
            {
                /* STIM mode is not supported. */
                Xcp_RecordError(XCP_CRC_RESOURCETEMPORARY_NOT_ACCESSIBLE);
            }
#endif  /* (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT) || (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT) */
        }
        else
        {
            /* Check if DAQ mode is supported. */
            errorCode = Xcp_MtaCheckValid((uint32)Xcp_DataInformation.pOdtEntryAddr[XCP_INDEX_0], Xcp_DataInformation.pOdtEntrySize[XCP_INDEX_0],
                                          XCP_ACCESS_SCOPE_DAQ_STIM, XCP_ACCESS_TYPE_READ);
        }
        if( XCP_E_NO_ERROR != errorCode )
        {
            Xcp_RecordError(errorCode);
        }
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_SetDaqPtr
*
* Explanation: Execute command CC_SetDaqPtr.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_SetDaqPtr
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 daq = (uint8) (XCP_CRO_SET_DAQ_PTR_DAQ & XCP_U8_MASK);
    /* ODT_NUMBER [0,1,..MAX_ODT(DAQ list)-1]  relative ODT number. */
    uint8 odt = XCP_CRO_SET_DAQ_PTR_ODT;
    /* ODT_ENTRY_NUMBER */
    uint8 idx = XCP_CRO_SET_DAQ_PTR_IDX;
    /* Absolute odt number. */
    uint16 odt0 = Xcp_DaqListFirstOdt(daq) + odt;

    /* Determine if DAQ, ODT, ODT entry is out of range. */
    if( (daq >= Xcp_DataInformation.daq.daqCount) || (odt >= (uint8)Xcp_DaqListOdtCount(daq)) ||
        (idx >= (uint8)Xcp_DaqListOdtEntryCount(odt0)) )
    {
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
    }
    else
    {
        Xcp_DataInformation.respDataLen = XCP_CRM_SET_DAQ_PTR_LEN;
        Xcp_DataInformation.daqListPtr = Xcp_DaqListOdtFirstEntry(odt0) + idx;
        Xcp_DataInformation.daqListNum = daq;
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_WriteDaq
*
* Explanation: Execute command CC_WriteDaq.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_WriteDaq
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 errorCode = XCP_E_NO_ERROR;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
    /* XCP_MAX_ODT_ENTRY_SIZE */
    uint8 maxOdtEntrySize = (uint8)(xcpConnCfgPtr->Xcp_Max_Dto - XCP_VALUE_1);
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT )
    uint32 alCalibGroupNum;
#endif
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
    uint16 vectIdx;
    uint32 ramDaqAddr;
    Xcp_VectListType* vectPtr;
#endif

    XCP_CHECK_RESOURCE_PROTECTION(XCP_RM_DAQ)

    errorCode = Xcp_MtaCheckValid(XCP_CRO_WRITE_DAQ_ADDR, XCP_CRO_WRITE_DAQ_SIZE,
                                  XCP_ACCESS_SCOPE_DAQ_STIM, XCP_ACCESS_TYPE_READ_WRITE);

    if( XCP_E_NO_ERROR != errorCode )
    {
        Xcp_RecordError(errorCode);
    }
    else
    {
        /* Determine if DAQ, ODT, ODT entry is out of range. */
        if( ((uint8)XCP_CRO_WRITE_DAQ_SIZE == (uint8)XCP_VALUE_0) ||
            (XCP_CRO_WRITE_DAQ_SIZE > maxOdtEntrySize ) )
        {
            Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
        }
        else
        {
            Xcp_DataInformation.respDataLen = XCP_CRM_WRITE_DAQ_LEN;
            Xcp_OdtEntrySize(Xcp_DataInformation.daqListPtr) = XCP_CRO_WRITE_DAQ_SIZE;
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
            /* Check if the address is within the calibration area. */
            if( (XCP_CRO_WRITE_DAQ_ADDR >= XCP_CALFLASH_ADDR(Xcp_MapPageIdx)) &&
                (XCP_CRO_WRITE_DAQ_ADDR < (XCP_CALFLASH_ADDR(Xcp_MapPageIdx) + XCP_CALRAM_SIZE(Xcp_MapPageIdx))) )
            {
                /* Address offset. */
                Xcp_OdtEntryAddr(Xcp_DataInformation.daqListPtr) = (uint8*)Xcp_GetPointer(
                                                                XCP_CRO_WRITE_DAQ_EXT,
                                                                XCP_CRO_WRITE_DAQ_ADDR) + XcpCalOffset;
            }
            else
            {
                /* Write daq addr. */
                Xcp_OdtEntryAddr(Xcp_DataInformation.daqListPtr) = (uint8*)Xcp_GetPointer(
                                                                XCP_CRO_WRITE_DAQ_EXT,
                                                                XCP_CRO_WRITE_DAQ_ADDR);
            }
#elif( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT )
            /* Check if the address is within the calibration area. */
            for( alCalibGroupNum = XCP_VALUE_0; alCalibGroupNum < RTE_CALIBGROUPNUM; alCalibGroupNum++ )
            {
                /* Find CalibGroup Num. */
                if( (Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress <= XCP_CRO_WRITE_DAQ_ADDR) &&
                    ((Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress +
                        Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupLength) > XCP_CRO_WRITE_DAQ_ADDR) )
                {
                    break;
                }
            }
            if( RTE_CALIBGROUPNUM <= alCalibGroupNum )
            {
                /* The address is not within the range. */
                Xcp_RecordError(XCP_CRC_PAGE_NOT_VALID);
            }
            else
            {
                /* Check the current page type. */
                if( XCP_WORKING_PAGE == Xcp_DataInformation.pageInd )
                {
                    /* Check whether the calibration data is mapped to RAM. */
                    if( (XCP_CALIBGROUP_PARABUF_ADDREND >= (*(Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupPtBuf))) &&
                    (XCP_CALIBGROUP_PARABUF_ADDRSTART <= (*(Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupPtBuf))) )
                    {
                        /* Address offset. */
                        Xcp_OdtEntryAddr(Xcp_DataInformation.daqListPtr) = (uint8*)Xcp_GetPointer(
                                                                        XCP_CRO_WRITE_DAQ_EXT,
                                                                        *(Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupPtBuf));
                    }
                    else
                    {
                        /* No mapping returned a negative response. */
                        Xcp_RecordError(XCP_CRC_RESOURCETEMPORARY_NOT_ACCESSIBLE);
                    }
                }
                /* Reference page. */
                else if( REFERENCE_PAGE == Xcp_DataInformation.pageInd )
                {
                    /* Write daq addr. */
                    Xcp_OdtEntryAddr(Xcp_DataInformation.daqListPtr) = (uint8*)Xcp_GetPointer(
                                                                    XCP_CRO_WRITE_DAQ_EXT,
                                                                    XCP_CRO_WRITE_DAQ_ADDR);
                }
                else
                {
                    /* Do nothing. */
                }
            }
#elif( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
        vectPtr = &Xcp_VectList;
        vectIdx = Xcp_CalVectSearch(vectPtr, XCP_CRO_WRITE_DAQ_ADDR);
        /* Check if the address is within the calibration area. */
        if( vectIdx < vectPtr->vectCnt )
        {
            /* Check the current page type. */
            if( XCP_WORKING_PAGE == Xcp_DataInformation.pageInd )
            {
                ramDaqAddr = XCP_CRO_WRITE_DAQ_ADDR;
                /* Check if the data has been copied to the RAM area. */
                if( vectPtr->vectInfo[vectIdx].calVecWpAddr != vectPtr->vectInfo[vectIdx].calVecRpAddr )
                {
                    /* Address offset. */
                    ramDaqAddr = vectPtr->vectInfo[vectIdx].calVecWpAddr +
                                             (ramDaqAddr - vectPtr->vectInfo[vectIdx].calVecRpAddr);
                    /* Write daq addr. */
                    Xcp_OdtEntryAddr(Xcp_DataInformation.daqListPtr) = (uint8*)Xcp_GetPointer(
                                                                    XCP_CRO_WRITE_DAQ_EXT,
                                                                    ramDaqAddr);
                }
                else
                {
                    /* No mapping returned a negative response. */
                    Xcp_RecordError(XCP_CRC_RESOURCETEMPORARY_NOT_ACCESSIBLE);
                }
            }
            /* Reference page. */
            else if( REFERENCE_PAGE == Xcp_DataInformation.pageInd )
            {
                /* Write daq addr. */
                Xcp_OdtEntryAddr(Xcp_DataInformation.daqListPtr) = (uint8*)Xcp_GetPointer(
                                                                XCP_CRO_WRITE_DAQ_EXT,
                                                                XCP_CRO_WRITE_DAQ_ADDR);
            }
            else
            {
                /* Do nothing. */
            }
        }
        else
        {
            /* The address is not within the range. */
            Xcp_RecordError(XCP_CRC_PAGE_NOT_VALID);
        }
#else
            /* Write daq addr. */
            Xcp_OdtEntryAddr(Xcp_DataInformation.daqListPtr) = (uint8*)Xcp_GetPointer(
                                                            XCP_CRO_WRITE_DAQ_EXT,
                                                            XCP_CRO_WRITE_DAQ_ADDR);
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM */
            /* Autoincrement */
            Xcp_DataInformation.daqListPtr++;
        }
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_StartStopDaqList
*
* Explanation: Execute command CC_StartStopDaqList.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_StartStopDaqList
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    /* DAQ_LIST_NUMBER */
    uint8 daq = (uint8)(XCP_CRO_START_STOP_DAQ & XCP_U8_MASK);

    XCP_CHECK_RESOURCE_PROTECTION(XCP_RM_DAQ)
    if( daq >= Xcp_DataInformation.daq.daqCount )
    {
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
    }
    /* 1 = start, 2 = select */
    else
    {
        if( (XCP_CRO_START_STOP_MODE == XCP_START_DAQ_LIST) || (XCP_CRO_START_STOP_MODE == XCP_SELECT_DAQ_LIST) )
        {
            Xcp_DaqListFlags(daq) |= (uint8)XCP_DAQ_FLAG_SELECTED;
            if( XCP_CRO_START_STOP_MODE == XCP_START_DAQ_LIST )
            {
                Xcp_StartDaq(daq);
            }
            Xcp_DataInformation.respDataLen = XCP_CRM_START_STOP_LEN;

            /* FIRST_PID is the absolute ODT number in the DTO Packet
            of the first ODT transferred by this DAQ list. */
            XCP_CRM_START_STOP_FIRST_PID = Xcp_DaqListFirstPid(daq);
        }
        else
        {
            Xcp_StopDaq(daq);
        }
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_StartStopSynch
*
* Explanation: Execute command CC_StartStopSynch.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_StartStopSynch
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    XCP_CHECK_RESOURCE_PROTECTION(XCP_RM_DAQ)

    /* Check STARTSTOP-SYNCH mode. */
    if( XCP_CRO_START_STOP_MODE == XCP_STOP_SELECT_DAQ_LIST_SYNCH )
    {
        /* Stop selected. */
        Xcp_StopAllSelectedDaq();
    }
    else
    {
        if( XCP_CRO_START_STOP_MODE == XCP_START_SELECT_DAQ_LIST_SYNCH )
        {
            /* start selected. */
            Xcp_StartAllSelectedDaq();
        }
        else if( XCP_CRO_START_STOP_MODE == XCP_STOP_ALL_DAQ_LIST_SYNCH )
        {
            /* XCP_CRO_START_STOP_MODE==0 : stop all */
            Xcp_StopAllDaq();
        }
        else
        {
            /* Do nothing. */
        }
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_GetDaqClock
*
* Explanation: Execute command CC_GetDaqClock.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_GetDaqClock(void)
{
    Xcp_DataInformation.respDataLen = XCP_CRM_GET_DAQ_CLOCK_LEN;
    XCP_CRM_GET_DAQ_CLOCK_TIME = (uint32)ApplXcpGetTimestamp();
}
#endif  /* #ifdef XCP_ENABLE_DAQ */

#if( XCP_FLASH_PROGRAMING_ENABLE == STD_ON )
/*
********************************************************************************
* Function Name: Xcp_CC_Program_Start
*
* Explanation: Execute command Xcp_CC_Program_Start.
*
* param: None
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_Program_Start(void)
{
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];

    XCP_CHECK_RESOURCE_PROTECTION(XCP_RM_PGM)
    XCP_CRM_PROGRAM_COMM_MODE_PGM = XCP_VALUE_0;
    XCP_CRM_PROGRAM_MAX_CTO_PGM = xcpConnCfgPtr->Xcp_Max_Cto;
#if( XCP_BLOCK_UPLOAD == STD_ON )
    XCP_CRM_PROGRAM_COMM_MODE_PGM |= XCP_PI_PGM_BLOCK_UPLOAD;
#endif  /* XCP_BLOCK_UPLOAD == STD_ON */
#if( XCP_BLOCK_DOWNLOAD == STD_ON )
    XCP_CRM_PROGRAM_COMM_MODE_PGM |= XCP_PI_PGM_BLOCK_DOWNLOAD;
    XCP_CRM_PROGRAM_MAX_BS_PGM = XCPBLOCK_SIZE;
    XCP_CRM_PROGRAM_MIN_ST_PGM = XCPBLOCK_MIN_ST;
#else
    XCP_CRM_PROGRAM_MAX_BS_PGM = XCP_VALUE_0;
    XCP_CRM_PROGRAM_MIN_ST_PGM = XCP_VALUE_0;
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */
    XCP_CRM_PROGRAM_QUEUE_SIZE_PGM = XCP_VALUE_0;
    Xcp_DataInformation.respDataLen = XCP_CRM_PROGRAM_START_LEN;
}

/*
********************************************************************************
* Function Name: Xcp_CC_Program_Clear
*
* Explanation: Execute command Xcp_CC_Program_Clear.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_Program_Clear
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 ret = XCP_E_NOT_OK;

    /* Absolute access mode is active. */
    if( XCP_CRO_PROGRAM_CLEAR_MODE == XCP_VALUE_0 )
    {
        ret = XcpAppl_FlashClear((uint32)Xcp_DataInformation.mta, XCP_CRO_PROGRAM_CLEAR_SIZE);
        if( ret != XCP_E_OK )
        {
            Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
        }
        else
        {
            /* Do nothing. */
        }
    }
    else
    {   /* Not support. */
        Xcp_RecordError(XCP_CRC_CMD_SYNTAX);
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_Program
*
* Explanation: Execute command Xcp_CC_Program.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_Program
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 ret = XCP_E_NOT_OK;
    uint8 prgramMaxSize = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
    /* XCP_CRO_PROGRAM_MAX_SIZE */
    prgramMaxSize = (uint8)((xcpConnCfgPtr->Xcp_Max_Cto - XCP_VALUE_2) / XCP_AG);

    if( XCP_CRO_PROGRAM_SIZE > prgramMaxSize )
    {
        ret = XcpAppl_FlashProgram((uint32)Xcp_DataInformation.mta, (uint8*)XCP_CRO_PROGRAM_DATA, prgramMaxSize);
        if( ret != XCP_E_OK )
        {
            Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
        }
        else
        {
#if( XCP_BLOCK_DOWNLOAD == STD_ON )
            Xcp_DataInformation.nextDownloadSize = (XCP_CRO_PROGRAM_SIZE - prgramMaxSize);
            Xcp_SendFlag = FALSE;
#if( XCP_ONCAN_ENABLE == STD_ON )
            Xcp_CanGetStatus = TRUE;
#endif  /* XCP_ONCAN_ENABLE == STD_ON */
#if( XCP_ONETHERNET_ENABLE == STD_ON )
            Xcp_EthGetStatus = TRUE;
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
            Xcp_DataInformation.mta += prgramMaxSize;
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */
        }
    }
    else
    {
        ret = XcpAppl_FlashProgram((uint32)Xcp_DataInformation.mta, (uint8*)XCP_CRO_PROGRAM_DATA, XCP_CRO_PROGRAM_SIZE);
        if( ret != XCP_E_OK )
        {
            Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
        }
        else
        {
            Xcp_DataInformation.mta += XCP_CRO_PROGRAM_SIZE;
        }
    }
}

#if( XCP_BLOCK_DOWNLOAD == STD_ON )
/*
********************************************************************************
* Function Name: Xcp_CC_Program_Next
*
* Explanation: Execute command Xcp_CC_Program_Next.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_Program_Next
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 ret = XCP_E_NOT_OK;
    uint8 prgramNextMaxSize = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
    /* XCP_CRO_PROGRAM_NEXT_MAX_SIZE */
    prgramNextMaxSize = (uint8)((xcpConnCfgPtr->Xcp_Max_Cto - XCP_VALUE_2) / XCP_AG);

    if( XCP_CRO_PROGRAM_NEXT_SIZE == Xcp_DataInformation.nextDownloadSize )
    {
        if ( XCP_CRO_PROGRAM_NEXT_SIZE > prgramNextMaxSize )
        {
            ret = XcpAppl_FlashProgram((uint32) Xcp_DataInformation.mta,(uint8*)XCP_CRO_PROGRAM_NEXT_DATA,prgramNextMaxSize);
            if( ret != XCP_E_OK )
            {
                Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
            }
            else
            {
                Xcp_DataInformation.nextDownloadSize = (XCP_CRO_PROGRAM_NEXT_SIZE - prgramNextMaxSize);
                Xcp_DataInformation.mta += prgramNextMaxSize;
            }
#if( XCP_ONCAN_ENABLE == STD_ON )
            Xcp_CanGetStatus = TRUE;
#endif  /* XCP_ONCAN_ENABLE == STD_ON */
#if( XCP_ONETHERNET_ENABLE == STD_ON )
            Xcp_EthGetStatus = TRUE;
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
        }
        else
        {
            ret = XcpAppl_FlashProgram((uint32) Xcp_DataInformation.mta,(uint8*)XCP_CRO_PROGRAM_NEXT_DATA, XCP_CRO_PROGRAM_NEXT_SIZE);
            if( ret != XCP_E_OK )
            {
                Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
            }
            else
            {
                Xcp_DataInformation.nextDownloadSize = XCP_VALUE_0;
                Xcp_SendFlag = TRUE;
                Xcp_DataInformation.mta += XCP_CRO_PROGRAM_NEXT_SIZE;
            }
        }
    }
    else
    {
        Xcp_RecordError(XCP_CRC_SEQUENCE);
        XCP_CRM_PROGRAM_NEXT_SIZE_EXPECTED_DATA = Xcp_DataInformation.nextDownloadSize;
    }
}
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */

/*
********************************************************************************
* Function Name: Xcp_CC_Program_Max
*
* Explanation: Execute command Xcp_CC_Program_Max.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_Program_Max
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    uint8 ret = XCP_E_NOT_OK;
    uint8 prgramMaxSize = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
    /* XCP_CRO_PROGRAM_MAX_MAX_SIZE */
    prgramMaxSize = (uint8)((xcpConnCfgPtr->Xcp_Max_Cto - XCP_AG) / XCP_AG);

    ret = XcpAppl_FlashProgram((uint32)Xcp_DataInformation.mta, (uint8*)XCP_CRO_PROGRAM_MAX_DATA, prgramMaxSize);
    if( ret != XCP_E_OK )
    {
        Xcp_RecordError(XCP_CRC_OUT_OF_RANGE);
    }
    else
    {
        Xcp_DataInformation.mta += prgramMaxSize;
    }
}

/*
********************************************************************************
* Function Name: Xcp_CC_Program_Reset
*
* Explanation: Execute command CC_StartStopSynch.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_Program_Reset
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    XCP_DUMMY_STATEMENT(pCmd);
    Xcp_Disconnect();
    /* May not return. */
    (void)XcpAppl_Reset();
}
#endif  /* XCP_FLASH_PROGRAMING_ENABLE == STD_ON */

#if( XCP_ENABLE_NVM_SAVE_DATA == STD_ON )
/*
********************************************************************************
* Function Name: Xcp_CC_Set_Request
*
* Explanation: Execute command CC_StartStopSynch.
*
* param: pCmd: Accept instructions and parameters.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CC_Set_Request
(
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST)pCmd
)
{
    Xcp_DataInformation.storeFlag = XCP_CRO_SET_REQUEST_MODE;
    Xcp_DataInformation.sessionId = XCP_CRO_SET_REQUEST_CONFIG_ID;

    if( (XCP_CRO_SET_REQUEST_MODE & XCP_SS_STORE_DAQ_REQ) == XCP_SS_STORE_DAQ_REQ )
    {
        Xcp_DataInformation.storeFlag = (XCP_CRO_SET_REQUEST_MODE & XCP_SS_STORE_DAQ_REQ);
        Xcp_DataInformation.sessionStatus |= (uint8)XCP_SS_RESUME;
    }
    else if( (XCP_CRO_SET_REQUEST_MODE&XCP_SS_STORE_CAL_REQ) == XCP_SS_STORE_CAL_REQ )
    {
        Xcp_DataInformation.storeFlag = (XCP_CRO_SET_REQUEST_MODE & XCP_SS_STORE_CAL_REQ);
    }
    else
    {
        /* Do nothing. */
    }
}
#endif  /* XCP_ENABLE_NVM_SAVE_DATA == STD_ON */

#if( (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM) && (XCP_ENABLE_CHECKSUM == STD_ON) )
/*
********************************************************************************
* Function Name: Xcp_AddressRelocationChecksum
*
* Explanation: Address relocation is used to check sum.
*
* param: checksumSize: Number of checksums.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_AddressRelocationChecksum(uint32 checksumSize)
{
    /* Working Page. */
    if( XCP_WORKING_PAGE == Xcp_DataInformation.pageInd )
    {
#if( (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) )
        while( checksumSize > XCP_VALUE_0 )
        {
            /* Checksum calculation method: XCP_ADD_xx. */
            Xcp_DataInformation.checkSum += (tXcpChecksumSumType)(XCP_READ_CHECKSUMVALUE_FROM_ADDR(Xcp_DataInformation.mta + XcpCalOffset));
            Xcp_DataInformation.mta = &Xcp_DataInformation.mta[sizeof(tXcpChecksumAddType)];
            checksumSize -= (uint8)sizeof(tXcpChecksumAddType);
        }
#else
        if( TRUE == Xcp_DataInformation.crc32Flag )
        {
            Xcp_DataInformation.checkSum = Crc_CalculateCRC32((Xcp_DataInformation.mta + XcpCalOffset),
                                                    checksumSize, (uint32)XCP_CRC_STARTVALUE, TRUE);
            Xcp_DataInformation.crc32Flag = FALSE;
            Xcp_DataInformation.mta += checksumSize;
        }
        else
        {
            Xcp_DataInformation.checkSum = Crc_CalculateCRC32((Xcp_DataInformation.mta + XcpCalOffset),
                                                    checksumSize, (uint32)Xcp_DataInformation.checkSum, FALSE);
            Xcp_DataInformation.mta += checksumSize;
        }
#endif  /* (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) */
    }
    else  /* Reference Page. */
    {
#if( (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) )
        while( checksumSize > XCP_VALUE_0 )
        {
            /* Checksum calculation method: XCP_ADD_xx. */
            Xcp_DataInformation.checkSum += (tXcpChecksumSumType)(XCP_READ_CHECKSUMVALUE_FROM_ADDR(Xcp_DataInformation.mta));
            Xcp_DataInformation.mta = &Xcp_DataInformation.mta[sizeof(tXcpChecksumAddType)];
            checksumSize -= (uint8)sizeof(tXcpChecksumAddType);
        }
#else
        if( TRUE == Xcp_DataInformation.crc32Flag )
        {
            Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta, checksumSize, (uint32)XCP_CRC_STARTVALUE, TRUE);
            Xcp_DataInformation.crc32Flag = FALSE;
            Xcp_DataInformation.mta += checksumSize;
        }
        else
        {
            Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta, checksumSize, (uint32)Xcp_DataInformation.checkSum, FALSE);
            Xcp_DataInformation.mta += checksumSize;
        }
#endif  /* (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) */
    }
}
#endif  /* (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM) && (XCP_ENABLE_CHECKSUM == STD_ON) */

#if( (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT) && (XCP_ENABLE_CHECKSUM == STD_ON) )
/*
********************************************************************************
* Function Name: Xcp_SinglePtrChecksum
*
* Explanation: Implementation of checksum with single pointer.
*
* param: checksumSize: Number of checksums.
*
* retval: None
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_SinglePtrChecksum(uint32 checksumSize)
{
    uint32 alCalibGroupNum;
    uint32 length = XCP_INIT_0;
    uint8* checksumAddr = NULL_PTR;

    /* Working Page. */
    if( XCP_WORKING_PAGE == Xcp_DataInformation.pageInd )
    {
        while( checksumSize > XCP_VALUE_0 )
        {
            /* Checksum calculation method: XCP_ADD_12. */
            for( alCalibGroupNum = XCP_VALUE_0; alCalibGroupNum < RTE_CALIBGROUPNUM; alCalibGroupNum++ )
            {
                /* Find CalibGroup Num. */
                if( (Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress <= (uint32)Xcp_DataInformation.mta)&&
                    ((Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress +
                      Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupLength) > (uint32)Xcp_DataInformation.mta) )
                {
                    break;
                }
                else
                {
                    /* Do nothing. */
                }
            }
            if( (alCalibGroupNum < RTE_CALIBGROUPNUM) &&
                (Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress !=
                *(Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupPtBuf)) )
            {
                length = Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupLength;
                checksumAddr = (uint8*)(*(Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupPtBuf));
#if( (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) )
                while(length)
                {
                    Xcp_DataInformation.checkSum += (tXcpChecksumSumType)(XCP_READ_CHECKSUMVALUE_FROM_ADDR(checksumAddr));
                    checksumAddr++;
                    length--;
                }
#else
                if( TRUE == Xcp_DataInformation.crc32Flag )
                {
                    Xcp_DataInformation.checkSum = Crc_CalculateCRC32(checksumAddr, length, (uint32)XCP_CRC_STARTVALUE, TRUE);
                    Xcp_DataInformation.crc32Flag = FALSE;

                }
                else
                {
                    Xcp_DataInformation.checkSum = Crc_CalculateCRC32(checksumAddr, length, (uint32)Xcp_DataInformation.checkSum, FALSE);
                }
#endif  /* (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) */

                Xcp_DataInformation.mta += Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupLength;
                checksumSize -= Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupLength;
            }
            else
            {
#if( (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) )
                Xcp_DataInformation.checkSum += (tXcpChecksumSumType)(XCP_READ_CHECKSUMVALUE_FROM_ADDR(Xcp_DataInformation.mta));
                Xcp_DataInformation.mta = &Xcp_DataInformation.mta[sizeof(tXcpChecksumAddType)];
                checksumSize -= (uint8)sizeof(tXcpChecksumAddType);
#else
                if( TRUE == Xcp_DataInformation.crc32Flag )
                {
                    Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta, (uint32)XCP_VALUE_1,
                                                                     (uint32)XCP_CRC_STARTVALUE, TRUE);
                    Xcp_DataInformation.crc32Flag = FALSE;
                }
                else
                {
                    Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta, (uint32)XCP_VALUE_1,
                                                                     (uint32)Xcp_DataInformation.checkSum, FALSE);
                }
                Xcp_DataInformation.mta += (uint8)XCP_VALUE_1;
                checksumSize -= (uint8)XCP_VALUE_1;
#endif  /* (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) */
            }
        }
    }
    else  /* Reference Page. */
    {

#if( (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) )
        while( checksumSize > XCP_VALUE_0 )
        {
            /* Checksum calculation method: XCP_ADD_xx. */
            Xcp_DataInformation.checkSum += (tXcpChecksumSumType)(XCP_READ_CHECKSUMVALUE_FROM_ADDR(Xcp_DataInformation.mta));
            Xcp_DataInformation.mta = &Xcp_DataInformation.mta[sizeof(tXcpChecksumAddType)];
            checksumSize -= (uint8)sizeof(tXcpChecksumAddType);
        }
#else
        if( TRUE == Xcp_DataInformation.crc32Flag )
        {
            Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta, checksumSize, (uint32)XCP_CRC_STARTVALUE, TRUE);
            Xcp_DataInformation.crc32Flag = FALSE;
            Xcp_DataInformation.mta += checksumSize;
        }
        else
        {
            Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta, checksumSize, (uint32)Xcp_DataInformation.checkSum, FALSE);
            Xcp_DataInformation.mta += checksumSize;
        }
#endif  /* (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) */
    }
}
#endif  /* (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT) && (XCP_ENABLE_CHECKSUM == STD_ON) */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT )
/*
********************************************************************************
* Function Name: XCP_ModifyEntry
*
* Explanation: Address conversion with single pointer.
*
* param: calibAddress: Calibration address.
*        calibLength: Calibration data length.
*        calibGroupData: Calibration data value.
*
* retval: XCP_E_OK: Address conversion complete.
*         XCP_E_NOT_OK: The calibration RAM area is full or
*                   the calibration address is out of range.
********************************************************************************
*/
FUNC(Std_ReturnType, XCP_CODE) Xcp_ModifyEntry
(
    uint32 calibAddress,
    uint16 calibLength,
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA)calibGroupData
)
{
    uint8 returnValue = XCP_E_NOT_OK;
    uint32 alCalibGroupNum;
    uint32 alIndex;

    for( alCalibGroupNum = XCP_VALUE_0; alCalibGroupNum < RTE_CALIBGROUPNUM; alCalibGroupNum++ )
    {
        /* Find CalibGroup Num. */
        if( (Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress <= calibAddress) &&
            ((Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress +
              Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupLength) > calibAddress) )
        {

            if( (Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress +
                 Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupLength) >= (calibAddress + calibLength) )
            {
                returnValue = XCP_E_OK;
                break;
            }
            else
            {
                /* A2L Error. */
                returnValue = XCP_E_NOT_OK;
            }
        }
    }
    if( XCP_E_OK == returnValue )
    {
        if( RTE_CALIBGROUPNUM <= alCalibGroupNum )
        {
            /* A2L Error. */
            returnValue = XCP_E_NOT_OK;
        }
        /* Check the group Calibration completed or not. */
        else
        {
            if( (XCP_CALIBGROUP_PARABUF_ADDREND >= (*(Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupPtBuf))) &&
                (XCP_CALIBGROUP_PARABUF_ADDRSTART <= (*(Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupPtBuf))) )
            {
                /* Not First calibration. */
                for( alIndex = XCP_INDEX_0; alIndex<calibLength; alIndex++ )
                {
                    ((uint8*)((*(Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupPtBuf)) +
                    (calibAddress - Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress)))[alIndex] =
                     calibGroupData[alIndex];
                }
            }
            else  /* First calibration. */
            {
                /* Supports 2-byte alignment. */
                if( (XCP_VALUE_0 == Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupLength % XCP_VALUE_2) &&
                    (XCP_VALUE_0 != ((uint32)Xcp_CalibGroupPtCnt & XCP_VALUE_1)) )
                {
                    Xcp_CalibGroupPtCnt = Xcp_CalibGroupPtCnt + XCP_VALUE_1;
                }
                /* The CalibGroup_RAMBuf overflow or not. */
                if( XCP_CALIBGROUP_PARABUF_ADDREND <
                    ((uint32)Xcp_CalibGroupPtCnt + Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupLength) )
                {
                    /* RAM overflow Error. */
                    returnValue = XCP_E_NOT_OK;
                }
                else
                {
                    /* Fill a RAM buffer with the Init calibration parameter values. */
                    for( alIndex = XCP_INDEX_0;
                         alIndex < Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupLength;
                         alIndex++ )
                    {
                        Xcp_CalibGroupPtCnt[alIndex] =
                        ((uint8*)Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress)[alIndex];
                    }

                    /* Fill a RAM buffer with the modify calibration parameter values. */
                    for( alIndex = XCP_INDEX_0; alIndex < calibLength; alIndex++ )
                    {
                        ((uint8*)(((uint32)Xcp_CalibGroupPtCnt) +
                        (calibAddress - Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress)))[alIndex] =
                         calibGroupData[alIndex];
                    }
                    /* Modify Entry. */
                    *(Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupPtBuf) = (uint32)Xcp_CalibGroupPtCnt;
                    /* Change the Xcp_CalibGroupPtCnt to the next. */
                    Xcp_CalibGroupPtCnt = (uint8*)((uint32)Xcp_CalibGroupPtCnt +
                                          Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupLength);
                }
            }
        }
    }

    return returnValue;
}

/*
********************************************************************************
* Function Name: XCP_CalibParaRead
*
* Explanation: Reading calibration data with single pointer.
*
* param: calibAddress: Calibration address.
*        calibLength: Calibration data length.
*        calibGroupData: Calibration data value.
*
* retval: XCP_E_OK: Check value read completed.
*         XCP_E_NOT_OK: The calibration address is out of range.
********************************************************************************
*/
FUNC(Std_ReturnType, XCP_CODE) Xcp_CalibParaRead(
    uint32 calibAddress,
    uint16 calibLength,
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA)calibGroupData
)
{
    uint8 returnValue = XCP_E_OK;
    uint32 alCalibGroupNum;
    uint32 alIndex;

    for( alCalibGroupNum = XCP_VALUE_0; alCalibGroupNum < RTE_CALIBGROUPNUM; alCalibGroupNum++ )
    {
        /* Find CalibGroup Num. */
        if( (Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress <= calibAddress) &&
            ((Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress +
            Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupLength) > calibAddress) )
        {
            if( (Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress +
                 Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupLength) >= (calibAddress + calibLength) )
            {
                break;
            }
            else
            {
                /* A2L Error. */
                returnValue = XCP_E_NOT_OK;
            }
        }
    }
    if( XCP_E_OK == returnValue )
    {
        if( RTE_CALIBGROUPNUM <= alCalibGroupNum )
        {
            /* Not Calib. */
            returnValue = XCP_E_NOT_OK;
        }
        else
        {
            /* Read calibration para value. */
            for( alIndex = XCP_INDEX_0; alIndex < calibLength; alIndex++ )
            {
                calibGroupData[alIndex] = ((uint8*)((*(Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupPtBuf)) +
                            (calibAddress-Rte_CalibGroupCfg[alCalibGroupNum].Rte_CalibGroupHAddress)))[alIndex];
            }
        }
    }

    return returnValue;
}
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT */

/*
********************************************************************************
* Function Name: ApplXcpCopyCalPage
*
* Explanation: Copy calibration page.
*
* param: srcSeg: source segment.
*        srcPage: source page.
*        dstSeg: destination segment.
*        dstPage: destination page.
*
* retval: uint8: calibration page.
********************************************************************************
*/
#ifdef XCP_ENABLE_PAGE_COPY
FUNC(uint8, XCP_CODE) ApplXcpCopyCalPage
(
    uint8 srcSeg, uint8 srcPage, uint8 dstSeg, uint8 dstPage
)
{
    uint8 returnValue = XCP_INIT_0;
    uint16 awSize;

    if( (XCPTS_NO_TIME_STAMP != srcSeg) || (XCP_VALUE_0 != dstSeg) )
    {
        /* Segments are not supported. */
        returnValue = XCP_CRC_SEGMENT_NOT_VALID;
    }
    else if( dstPage == srcPage )
    {
        /* Can not copy on itself. */
        returnValue = XCP_CRC_PAGE_NOT_VALID;
    }
    else if( XCP_VALUE_0 == dstPage )
    {
        /* Can not copy to FLASH page. */
        returnValue = XCP_CRC_ACCESS_DENIED;
    }
    else
    {
        awSize = XCP_CALRAM_SIZE(Xcp_MapPageIdx);
        if( CALPAGE_RAM(Xcp_MapPageIdx) == XCP_WORKING_PAGE )
        {
            ApplXcpSetCalPage(XCP_VALUE_0, CALPAGE_FLASH(Xcp_MapPageIdx), XCP_CAL_ECU);
            Xcp_CopyMemCpy((void*)XCP_CALRAM_ADDR(Xcp_MapPageIdx), (void*)XCP_CALFLASH_ADDR(Xcp_MapPageIdx), awSize);
            ApplXcpSetCalPage(XCP_VALUE_0, CALPAGE_RAM(Xcp_MapPageIdx), XCP_CAL_ECU);
        }
        else
        {
            Xcp_CopyMemCpy((void*)XCP_CALRAM_ADDR(Xcp_MapPageIdx), (void*)XCP_CALFLASH_ADDR(Xcp_MapPageIdx), awSize);
        }
    }

    return returnValue;
}

/*
********************************************************************************
* Function Name: Xcp_CopyMemCpy
*
* Explanation: Copy n bytes from src to dest.
*
* param: dest: pointer to destination address.
*        src: pointer to source address.
*        n: number of data bytes to copy.
*
* retval: uint8: calibration page.
********************************************************************************
*/
static FUNC(void, XCP_CODE) Xcp_CopyMemCpy
(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA)dest,
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST)src,
    uint16 num
)
{
    for( ; num > XCP_VALUE_0; num-- )
    {
        XCP_WRITE_BYTE_2_ADDR(dest, *src);
        dest++;
        src++;
    }
}
#endif  /* #ifdef XCP_ENABLE_PAGE_COPY */

#if( (XCP_EVENT_CHANNEL_NUM > XCP_VALUE_0)\
    && ((XCP_EVENT_BASE_PERIOD_SELECT == XCP_BASE_PERIOD_MAINFUNCTION)\
    || (XCP_EVENT_BASE_PERIOD_SELECT == XCP_BASE_PERIOD_USER_DEFINED)) )
/*
********************************************************************************
* Function Name: XcpEventCycleCalcule
*
* Explanation: Calculate the counter value of the event.
*
* param: uintConverter: Conversion units currently calculated.
* param: eventIndex: Current calculated event.
*
* retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, XCP_CODE) XcpEventCycleCalcule
(
    float32 uintConverter,
    uint8 eventIndex
)
{
    uint32 eventTimer = XCP_INIT_0;
    float32 xcpF32EventTimer;

    /* Calculate the parameters of the configuration. */
    xcpF32EventTimer = (float32)((sint32)((uint32)Xcp_EventChannel[eventIndex].XcpEventChannelTimeCycle)) * uintConverter;
    /* Obtain the calculated number of counters. */
    eventTimer = (uint32)xcpF32EventTimer / XCP_EVENT_BASE_PERIOD;
    /* Set corresponding parameters. */
    if( eventTimer > XCP_VALUE_0 )
    {
        XcpEventchannelMonitor[eventIndex].eventChanlNumber =
                Xcp_EventChannel[eventIndex].XcpEventChannelNumber;
        XcpEventchannelMonitor[eventIndex].eventChannelActive = TRUE;
        XcpEventchannelMonitor[eventIndex].eventChannelMaxCycCnt = eventTimer;
        XcpEventchannelMonitor[eventIndex].eventChannelCurCnt =
                XcpEventchannelMonitor[eventIndex].eventChannelMaxCycCnt;
    }
    else
    {
        XcpEventchannelMonitor[eventIndex].eventChannelActive = FALSE;
        XcpEventchannelMonitor[eventIndex].eventChannelMaxCycCnt = XCP_VALUE_0;
        XcpEventchannelMonitor[eventIndex].eventChannelCurCnt =
                XcpEventchannelMonitor[eventIndex].eventChannelMaxCycCnt;
    }
}

/*
********************************************************************************
* Function Name: XcpEventCycleInit
*
* Explanation: Initialize the counter of the event.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) XcpEventCycleInit(void)
{
    uint8 eventIndex;
    uint8 xcpEventUint;

    /* Initialize the counter of the event. */
    for( eventIndex = XCP_INDEX_0; eventIndex < XCP_EVENT_CHANNEL_NUM; eventIndex++ )
    {
        xcpEventUint = Xcp_EventChannel[eventIndex].XcpEventChannelTimeUnit;

        switch(xcpEventUint)
        {
        case DAQ_TIMESTAMP_UNIT_1NS:
            XcpEventCycleCalcule(DAQ_TIMESTAMP_UNIT_TICK_1NS, eventIndex);
            break;
        case DAQ_TIMESTAMP_UNIT_10NS:
            XcpEventCycleCalcule(DAQ_TIMESTAMP_UNIT_TICK_10NS, eventIndex);
            break;
        case DAQ_TIMESTAMP_UNIT_100NS:
            XcpEventCycleCalcule(DAQ_TIMESTAMP_UNIT_TICK_100NS, eventIndex);
            break;
        case DAQ_TIMESTAMP_UNIT_1US:
            XcpEventCycleCalcule(DAQ_TIMESTAMP_UNIT_TICK_1US, eventIndex);
            break;
        case DAQ_TIMESTAMP_UNIT_10US:
            XcpEventCycleCalcule(DAQ_TIMESTAMP_UNIT_TICK_10US, eventIndex);
            break;
        case DAQ_TIMESTAMP_UNIT_100US:
            XcpEventCycleCalcule(DAQ_TIMESTAMP_UNIT_TICK_100US, eventIndex);
            break;
        case DAQ_TIMESTAMP_UNIT_1MS:
            XcpEventCycleCalcule(DAQ_TIMESTAMP_UNIT_TICK_1MS, eventIndex);
            break;
        case DAQ_TIMESTAMP_UNIT_10MS:
            XcpEventCycleCalcule(DAQ_TIMESTAMP_UNIT_TICK_10MS, eventIndex);
            break;
        case DAQ_TIMESTAMP_UNIT_100MS:
            XcpEventCycleCalcule(DAQ_TIMESTAMP_UNIT_TICK_100MS, eventIndex);
            break;
        case DAQ_TIMESTAMP_UNIT_1S:
            XcpEventCycleCalcule(DAQ_TIMESTAMP_UNIT_TICK_1S, eventIndex);
            break;
        case DAQ_TIMESTAMP_UNIT_1PS:
            XcpEventCycleCalcule(DAQ_TIMESTAMP_UNIT_TICK_1PS, eventIndex);
            break;
        case DAQ_TIMESTAMP_UNIT_10PS:
            XcpEventCycleCalcule(DAQ_TIMESTAMP_UNIT_TICK_10PS, eventIndex);
            break;
        case DAQ_TIMESTAMP_UNIT_100PS:
            XcpEventCycleCalcule(DAQ_TIMESTAMP_UNIT_TICK_100PS, eventIndex);
            break;
        default:
            break;
        }
    }
}

/*
********************************************************************************
* Function Name: Xcp_ProcessEvents
*
* Explanation: Trigger Event.
*
* param: event:Trigger corresponding events.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_ProcessEvents(uint8 event)
{
    (void)Xcp_Event(event);
}

/*
********************************************************************************
* Function Name: XcpEventCycleProcess
*
* Explanation: Traverse events that reach the trigger time.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) XcpEventCycleProcess(void)
{
    uint8 eventIndex;

    for( eventIndex = XCP_INDEX_0; eventIndex < XCP_EVENT_CHANNEL_NUM; eventIndex++ )
    {
        /* Determine whether the current event can be triggered. */
        if( TRUE == XcpEventchannelMonitor[eventIndex].eventChannelActive )
        {
            XcpEventchannelMonitor[eventIndex].eventChannelCurCnt--;
            /* Determine whether the current event is triggered. */
            if( XCP_VALUE_0 == XcpEventchannelMonitor[eventIndex].eventChannelCurCnt )
            {
                Xcp_ProcessEvents(XcpEventchannelMonitor[eventIndex].eventChanlNumber);
                /* Restore counter value .*/
                XcpEventchannelMonitor[eventIndex].eventChannelCurCnt =
                        XcpEventchannelMonitor[eventIndex].eventChannelMaxCycCnt;
            }
        }
    }
}
#endif

/*
********************************************************************************
* Function Name: XCP_Init
*
* Explanation: Initialization of the XCP Protocol Layer.
*              Application specific initialization.
*              ( e.g. Vector XCP on CAN Transport Layer )
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_Init(void)
{
#if( (XCP_MULTIPDUIDSUPPORT == STD_ON) ||\
    (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT) ||\
    (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM) ||\
    (RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY) )
    uint8 index;
#endif
    /* Xcp init calibration page.*/
    Xcp_InitCalPage();
    /* Initialize all XCP variables to zero. */
    Xcp_MemClr( &Xcp_DataInformation, sizeof(Xcp_DataInformation) );
    /* Clear the current connection bus type and id. */
    Xcp_ConnectionStatus.busType = XCP_BUS_NULL;
    Xcp_ConnectionStatus.connectionId = XCP_INVALID_CONNECTION_ID;

    /* Initialize the session status. */
    Xcp_DataInformation.sessionStatus = (uint8)XCP_INIT_0;
    Xcp_DataInformation.storeFlag = XCP_INIT_0;
#if( XCP_BLOCK_DOWNLOAD == STD_ON )
    Xcp_DataInformation.nextDownloadSize = XCP_INIT_0;
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */
#if( XCP_BLOCK_UPLOAD == STD_ON )
    Xcp_DataInformation.nextDataBlockSize = XCP_INIT_0;
#endif  /* XCP_BLOCK_UPLOAD == STD_ON */

#if( (XCP_EVENT_CHANNEL_NUM > XCP_VALUE_0)\
    && ((XCP_EVENT_BASE_PERIOD_SELECT == XCP_BASE_PERIOD_MAINFUNCTION)\
    || (XCP_EVENT_BASE_PERIOD_SELECT == XCP_BASE_PERIOD_USER_DEFINED)) )
    XcpEventCycleInit();
#endif

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
    for( index = XCP_INDEX_0; index < XCP_REMAPPING_CNT; index++ )
    {
        Xcp_RemapAddr[index].addr_wp = Xcp_InitRam_Addr[index].addr_wp;
        Xcp_RemapAddr[index].addr_rp = Xcp_InitRam_Addr[index].addr_rp;
        Xcp_RemapAddr[index].len = Xcp_InitRam_Addr[index].len;
    }
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM */
#if( RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY )
    for( index = XCP_INDEX_0; index < XCP_OVERLAY_CNT; index++ )
    {
        Xcp_Addr_Temp[index].len = Xcp_Overlay_Addr[index].len;
        Xcp_Addr_Temp[index].addr_rp = Xcp_Overlay_Addr[index].addr_rp;
        Xcp_Addr_Temp[index].addr_wp = Xcp_Overlay_Addr[index].addr_wp;
    }
#endif  /* RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY */

#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
    /* Initialize the transmit queue. */
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
    for( index = XCP_INDEX_0; index < XCP_TXPDU_LIST; index++ )
    {
        Xcp_DataInformation.sendStatus[index] = (uint8)XCP_CLEAN_SEND_FLAG;
    }
#else
    Xcp_DataInformation.sendStatus = (uint8)XCP_CLEAN_SEND_FLAG;
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */

#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
    Xcp_CalMemInit();

    for( index = XCP_INDEX_0; index < XCP_REGISTER_NUM; index++ )
    {
        Xcp_RegisterFunList[index].FctPtrOfRegister();
    }
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */
}

/*
********************************************************************************
* Function Name: Xcp_Det_ErrorReport
*
* Explanation: Function to report Error to Det.
*
* param: apiId: Unique Api ID of ComM manager service.
*        errorId: Det Error ID of ComM manager.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_Det_ErrorReport(uint8 apiId, uint8 errorId)
{
#if( XCP_DEV_ERROR_DETECT == STD_ON )
    /* Error detected. */
    if( XCP_E_NO_ERROR != errorId )
    {
        /* Report Error to Det. */
        (void)Det_ReportError(XCP_MODULE_ID, XCP_INSTANCE_ID, apiId, errorId);
    }
#else
    XCP_DUMMY_STATEMENT(apiId);
    XCP_DUMMY_STATEMENT(errorId);
#endif  /* XCP_DEV_ERROR_DETECT == STD_ON */
}

/*
********************************************************************************
* Function Name: XCP_InterruptDisable
*
* Explanation: xcp interrupt disable.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_InterruptDisable(void)
{
    SchM_Enter_Xcp_XCP_EXCLUSIVE_AREA_0();
}

/*
********************************************************************************
* Function Name: XCP_InterruptEnable
*
* Explanation: xcp interrupt enable.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_InterruptEnable(void)
{
    SchM_Exit_Xcp_XCP_EXCLUSIVE_AREA_0();
}

/*
********************************************************************************
* Function Name: XCP_SendCallBack
*
* Explanation: Notifies the XCP Protocol Layer about the successful.
*              transmission of a XCP packet.
*
* param: None
*
* retval: XCP_E_OK: XCP_SendCallBack success.
*         Any other: XCP_SendCallBack not success.
********************************************************************************
*/
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
FUNC(uint8, XCP_CODE) Xcp_SendCallBack(uint8 eventid)
{
    uint8 retValue = XCP_E_NOT_OK;
    uint8 index;
#if( XCP_BLOCK_UPLOAD == STD_ON )
    /* Used to call upload again. */
    Xcp_CtoType nextCmd = {XCP_INIT_0};
#endif  /* XCP_BLOCK_UPLOAD == STD_ON */

#ifdef XCP_ENABLE_DAQ
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
    /* Clear all pending flags. */
    /* A pending flag indicates that XCP_Send() is in progress. */
    for( index = XCP_INDEX_0; index < XCP_TXPDU_LIST; index++ )
    {
        Xcp_DataInformation.sendStatus[index] &= (uint8)(~XCP_SEND_PENDING) & XCP_U8_MASK;
    }

    /* Now check if there is another transmit request. */
    if( (Xcp_DataInformation.sendStatus[eventid] & (uint8)XCP_CRM_REQUEST) != XCP_VALUE_0 )
    {
        /* Send a RES or ERR (CRM) message. */
        Xcp_DataInformation.sendStatus[eventid] &= (uint8)(~XCP_CRM_REQUEST) & XCP_U8_MASK;
        (void)Xcp_SendCrm();
        retValue = XCP_E_OK;
    }

#if( defined (XCP_ENABLE_SEND_EVENT) && (XCP_ENABLE_NVM_SAVE_DATA == STD_ON) )
    else if( (Xcp_DataInformation.sendStatus & (uint8)XCP_EVT_REQUEST) != XCP_VALUE_0 )
    {
        /* Send a EV or SERV message. */
        Xcp_DataInformation.sendStatus &= (uint8)(~XCP_EVT_REQUEST) & XCP_U8_MASK;
        (void)Xcp_SendEv();
        retValue = XCP_E_OK;
    }
#endif  /* (XCP_ENABLE_SEND_EVENT) && (XCP_ENABLE_NVM_SAVE_DATA == STD_ON) */
    else
    {
        if( ((Xcp_DataInformation.sessionStatus & (uint8)XCP_SS_DAQ) != XCP_VALUE_0) && (eventid < XCP_EVENT_CHANNEL_NUM) )
        {
            /* Send a DAQ message from the queue or from the buffer. */
            if( XCP_E_OK == Xcp_SendDtoFromQueue(eventid) )
            {
                retValue = XCP_E_OK;
            }
        }
    }
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
#endif  /* #ifdef XCP_ENABLE_DAQ */

#if( XCP_BLOCK_UPLOAD == STD_ON )
    /* #80 Otherwise, if pending upload data exist: */
    if( (Xcp_DataInformation.sessionStatus & XCP_SS_BLOCK_UPLOAD) != XCP_VALUE_0 )
    {
        nextCmd.bytes[XCP_INDEX_0] = (uint8)XCP_CC_UPLOAD;
        nextCmd.bytes[XCP_INDEX_1] = (uint8)Xcp_DataInformation.nextDataBlockSize;
        /* #90 Reset PENDING flag, execute upload command and send the frame. */
        Xcp_DataInformation.sessionStatus &= (uint8)(~XCP_SS_BLOCK_UPLOAD);
        Xcp_Command((uint8)Xcp_ConnectionStatus.connectionId, (const Xcp_CtoType*)nextCmd);
    }
#endif  /* XCP_BLOCK_UPLOAD == STD_ON */

    return retValue;
}

#else
FUNC(uint8, XCP_CODE) Xcp_SendCallBack(void)
{
#if( XCP_BLOCK_UPLOAD == STD_ON )
    /* Used to call upload again. */
    Xcp_CtoType nextCmd = {XCP_INIT_0};
#endif  /* XCP_BLOCK_UPLOAD == STD_ON */
    uint8 retValue = XCP_E_NOT_OK;

#ifdef XCP_ENABLE_DAQ
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
    /* A pending flag indicates that XCP_Send() is in progress. */
    /* Now check if there is another transmit request. */
    if( (Xcp_DataInformation.sendStatus & (uint8)XCP_CRM_REQUEST) != XCP_VALUE_0 )
    {
        /* Send a RES or ERR (CRM) message. */
        retValue = Xcp_SendCrm();
        if( XCP_E_OK == retValue )
        {
            Xcp_DataInformation.sendStatus &= (uint8)(~XCP_CRM_REQUEST) & XCP_U8_MASK;
        }
    }
    else if( (Xcp_DataInformation.sendStatus & (uint8)XCP_DTO_PENDING) != XCP_VALUE_0 )
    {
        /* Send Dto. */
        retValue = Xcp_SendDtoFromQueue();
        if( XCP_E_OK == retValue )
        {
            Xcp_DataInformation.sendStatus &= (uint8)(~XCP_DTO_PENDING) & XCP_U8_MASK;
        }
    }
#if( defined (XCP_ENABLE_SEND_EVENT) && (XCP_ENABLE_NVM_SAVE_DATA == STD_ON) )
    else if( (Xcp_DataInformation.sendStatus & (uint8)XCP_EVT_REQUEST) != XCP_VALUE_0 )
    {
        /* Send a EV or SERV message. */
        retValue = Xcp_SendEv();
        if( XCP_E_OK == retValue )
        {
            Xcp_DataInformation.eventDataLen = XCP_VALUE_0;
            Xcp_DataInformation.sendStatus &= (uint8)(~XCP_EVT_REQUEST) & XCP_U8_MASK;
        }
    }
#endif  /* defined (XCP_ENABLE_SEND_EVENT) && (XCP_ENABLE_NVM_SAVE_DATA == STD_ON) */
    else
    {
        /* Do nothing. */
    }
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
#endif  /* #ifdef XCP_ENABLE_DAQ */

#if( XCP_BLOCK_UPLOAD == STD_ON )
    /* #80 Otherwise, if pending upload data exist: */
    if( (Xcp_DataInformation.sessionStatus & XCP_SS_BLOCK_UPLOAD) != XCP_VALUE_0 )
    {
#if( XCP_ONCAN_ENABLE == STD_ON )
        Xcp_CanGetStatus = FALSE;
#endif  /* XCP_ONCAN_ENABLE == STD_ON */
#if( XCP_ONETHERNET_ENABLE == STD_ON )
        Xcp_EthGetStatus = FALSE;
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
        nextCmd.bytes[XCP_INIT_0] = (uint8)XCP_CC_UPLOAD;
        nextCmd.bytes[XCP_INIT_1] = (uint8)Xcp_DataInformation.nextDataBlockSize;
        /* #90 Reset PENDING flag, execute upload command and send the frame. */
        Xcp_DataInformation.sessionStatus &= (uint8)(~XCP_SS_BLOCK_UPLOAD);
        Xcp_Command((uint8)Xcp_ConnectionStatus.connectionId, (const Xcp_CtoType*)&nextCmd);
    }
    else
    {
#if( XCP_ONCAN_ENABLE == STD_ON )
        Xcp_CanGetStatus = TRUE;
#endif  /* XCP_ONCAN_ENABLE == STD_ON  */
#if( XCP_ONETHERNET_ENABLE == STD_ON )
        Xcp_EthGetStatus = TRUE;
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
    }
#endif  /* XCP_BLOCK_UPLOAD == STD_ON */

    return retValue;
}
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */

/*
********************************************************************************
* Function Name: XCP_Background
*
* Explanation: perform background calculation of checksum.
*
* param: None
*
* retval: XCP_E_OK: XCP_Background success.
*         Any other: XCP_Background not success.
********************************************************************************
*/
FUNC(uint8, XCP_CODE) Xcp_Background(void)
{
    uint8 retValue = XCP_E_OK;
#if( XCP_ENABLE_CHECKSUM == STD_ON )
    /* checksumsize: Xcp_DataInformation.checkSumSize. */
    uint32 checksumSize;
#endif  /* XCP_ENABLE_CHECKSUM == STD_ON */

#if( XCP_ENABLE_CHECKSUM == STD_ON )
    /* Checksum calculation in progress. */
    if( XCP_VALUE_0 < Xcp_DataInformation.checkSumSize )
    {
        if( Xcp_DataInformation.checkSumSize <= XCP_CHECKSUMBLOCKSIZE )
        {
            checksumSize = Xcp_DataInformation.checkSumSize;
            Xcp_DataInformation.checkSumSize = XCP_VALUE_0;
        }
        else
        {
            checksumSize = XCP_CHECKSUMBLOCKSIZE;
            Xcp_DataInformation.checkSumSize -= XCP_CHECKSUMBLOCKSIZE;
        }
        /* Single pointer checksum. */
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
        Xcp_StructurePtChecksum(checksumSize);
#elif( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT )
        Xcp_SinglePtrChecksum(checksumSize);
#elif( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
        Xcp_AddressRelocationChecksum(checksumSize);
#else
#if( (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) )
        while( checksumSize > XCP_VALUE_0 )
        {
            /* Checksum calculation method: XCP_ADD_xx. */
            Xcp_DataInformation.checkSum += (tXcpChecksumSumType)(XCP_READ_CHECKSUMVALUE_FROM_ADDR(Xcp_DataInformation.mta));
            Xcp_DataInformation.mta = &Xcp_DataInformation.mta[sizeof(tXcpChecksumAddType)];
            checksumSize -= (uint8)sizeof(tXcpChecksumAddType);
        }
#else
        if( TRUE == Xcp_DataInformation.crc32Flag )
        {
            Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta, (uint32)checksumSize,
                                                             (uint32)XCP_CRC_STARTVALUE, TRUE);
            Xcp_DataInformation.crc32Flag = FALSE;
            Xcp_DataInformation.mta = &Xcp_DataInformation.mta[checksumSize];
        }
        else
        {
            Xcp_DataInformation.checkSum = Crc_CalculateCRC32(Xcp_DataInformation.mta, (uint32)checksumSize,
                                                    (uint32)Xcp_DataInformation.checkSum, FALSE);
            Xcp_DataInformation.mta = &Xcp_DataInformation.mta[checksumSize];
        }
#endif  /* (XCP_ADD12 == XCP_CHECKSUM_TYPE) || (XCP_ADD11 == XCP_CHECKSUM_TYPE) */
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */
        /* Checksum calculation finished? */
        if( XCP_VALUE_0 != (Xcp_DataInformation.checkSumSize) )
        {
            /* Still pending. */
            retValue = XCP_E_NOT_OK;
        }
        else
        {
#if( XCP_ADD12 == XCP_CHECKSUM_TYPE )
            XCP_CRM_BUILD_CHECKSUM_TYPE = XCP_CHECKSUM_TYPE_ADD12;
#elif( XCP_ADD11 == XCP_CHECKSUM_TYPE )
            XCP_CRM_BUILD_CHECKSUM_TYPE = XCP_CHECKSUM_TYPE_ADD11;
#elif( XCP_CRC32== XCP_CHECKSUM_TYPE )
            XCP_CRM_BUILD_CHECKSUM_TYPE = XCP_CHECKSUM_TYPE_CRC32;
#endif  /* XCP_ADD12 == XCP_CHECKSUM_TYPE */
            XCP_CRM_BUILD_CHECKSUM_RESULT = Xcp_DataInformation.checkSum;
            Xcp_DataInformation.respDataLen = XCP_CRM_BUILD_CHECKSUM_LEN;
            Xcp_SendFlag = TRUE;
            (void)Xcp_SendCrm();
            retValue = XCP_E_OK;
        }
    }  /* Xcp_DataInformation.checkSumSize */
#endif  /* XCP_ENABLE_CHECKSUM == STD_ON */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
    if( XCP_REQ_COPY == Xcp_DownLoadCopyState.copyReqState )
    {
        if( Xcp_DownLoadCopyState.copyLen > XCP_COPY_LEN )
        {
            Xcp_MemCpy8((uint8*)Xcp_DownLoadCopyState.copyAddrDest,
                        (uint8*)Xcp_DownLoadCopyState.copyAddrSrc,
                        XCP_COPY_LEN);
            Xcp_DownLoadCopyState.copyLen -= XCP_COPY_LEN;
        }
        else
        {
            Xcp_MemCpy8((uint8*)Xcp_DownLoadCopyState.copyAddrDest,
                        (uint8*)Xcp_DownLoadCopyState.copyAddrSrc,
                        Xcp_DownLoadCopyState.copyLen);
            Xcp_DownLoadCopyState.copyReqState = XCP_CLEAN_COPY_FLAG;
            retValue = Xcp_CalDownLoadHandle(Xcp_DownLoadCopyState.downData, Xcp_DownLoadCopyState.downSize);
            if( XCP_E_OK == retValue )
            {
                Xcp_DataInformation.mta += Xcp_DownLoadCopyState.downSize;
#if( XCP_BLOCK_DOWNLOAD == STD_ON )
                if( Xcp_DataInformation.nextDownloadSize == XCP_VALUE_0 )
                {
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */
                    XCP_CRM_CMD = XCP_PID_RES;
                    Xcp_DataInformation.respDataLen = XCP_VALUE_1;
                    Xcp_SendFlag = TRUE;
                    (void)Xcp_SendCrm();
#if( XCP_BLOCK_DOWNLOAD == STD_ON )
                }
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */
            }
        }
    }
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT */

    return retValue;
}

/*
********************************************************************************
* Function Name: XCP_Disconnect
*
* Explanation: If the XCP slave is connected to a XCP master a call of this
*              function discontinues the connection
*              (transition to disconnected state).If the XCP
*              slave is not connected this function performs no action.
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_Disconnect(void)
{
    /* Send a positive response before clearing Xcp_ConnectionStatus. */
    (void)Xcp_Send(Xcp_DataInformation.respDataLen, &Xcp_DataInformation.responseBuff.bytes[XCP_INDEX_0]);
    /* Clear the current connection bus type and id. */
    Xcp_ConnectionStatus.busType = XCP_BUS_NULL;
    Xcp_ConnectionStatus.connectionId = XCP_INVALID_CONNECTION_ID;
    /* Clear the current responseBuff. */
    Xcp_MemClr(Xcp_DataInformation.responseBuff.bytes, ((XCP_MAX_CTO + XCP_VALUE_3) & XCP_DATA_MASK_FFC));
    /* Clear the current connection Unprocessed buff. */
#if( XCP_ONETHERNET_ENABLE == STD_ON )
    EthXcp_Init();
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */

#if( XCP_ONCAN_ENABLE == STD_ON )
    CanXcp_Init();
#endif  /* XCP_ONCAN_ENABLE == STD_ON */
    /* Set the current session status. */
    Xcp_DataInformation.sessionStatus &= (uint8)(~XCP_SS_CONNECTED) & XCP_U8_MASK;

#ifdef XCP_ENABLE_DAQ
    Xcp_StopAllDaq();
#endif  /* #ifdef XCP_ENABLE_DAQ */

#if( XCP_ENABLE_SEED_KEY == STD_ON )
    /* Lock all resources. */
    Xcp_DataInformation.protectionStatus = (uint8)(XCP_RM_CAL_PAG | XCP_RM_DAQ | XCP_RM_PGM | XCP_RM_STIM);
#endif  /* XCP_ENABLE_SEED_KEY == STD_ON */
}

/*
********************************************************************************
* Function Name: Xcp_SendCrm
*
* Explanation: Transmission of a command response packet (RES),
*               or error packet (ERR) if no other packet is pending.
* param: None
*
* retval: XCP_E_OK: Transmit request has been accepted.
*         XCP_E_NOT_OK: Transmit request has not been accepted.
********************************************************************************
*/
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
FUNC(Std_ReturnType, XCP_CODE) Xcp_SendCrm(void)
{
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
    /* Judge Send Occupation. */
    if( (Xcp_DataInformation.sendStatus[XCP_EVENT_CHANNEL_NUM] & (uint8)XCP_CRM_PENDING) != XCP_VALUE_0 )
    {
        Xcp_DataInformation.sessionStatus |= (uint8)XCP_CRM_PENDING;
        /* Mark command reply request. */
        Xcp_DataInformation.sendStatus[XCP_EVENT_CHANNEL_NUM] |= (uint8)XCP_CRM_PENDING;
    }
    else
    {
        stdRet = Xcp_Send(XCP_EVENT_CHANNEL_NUM, Xcp_DataInformation.respDataLen, &Xcp_DataInformation.responseBuff.bytes[XCP_INDEX_0]);
        if( XCP_E_OK != stdRet )
        {
            Xcp_DataInformation.sendStatus[XCP_EVENT_CHANNEL_NUM] |= (uint8)XCP_CRM_PENDING;
        }
    }
#else
    Xcp_Send(XCP_EVENT_CHANNEL_NUM, Xcp_DataInformation.respDataLen, &Xcp_DataInformation.responseBuff.bytes[XCP_INDEX_0]);
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
}

#else
FUNC(Std_ReturnType, XCP_CODE) Xcp_SendCrm(void)
{
    Std_ReturnType stdRet = XCP_E_NOT_OK;

#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
    /* Judge Send Occupation. */
    stdRet = Xcp_Send(Xcp_DataInformation.respDataLen, &Xcp_DataInformation.responseBuff.bytes[XCP_INDEX_0]);
    if( XCP_E_OK != stdRet )
    {
        Xcp_DataInformation.sendStatus |= (uint8)XCP_CRM_REQUEST;
    }
#else
    stdRet = Xcp_Send(Xcp_DataInformation.respDataLen, &Xcp_DataInformation.responseBuff.bytes[XCP_INDEX_0]);
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */

    return stdRet;
}
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */

#ifdef XCP_ENABLE_DAQ
/*
********************************************************************************
* Function Name: XCP_SendDto
*
* Explanation: Send a DTO.
*
* param: astpDto: pointer to XCP packet type definition
*
* retval: XCP_E_OK: Transmit request has been accepted.
*         XCP_E_NOT_OK: Transmit request has not been accepted.
********************************************************************************
*/
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
FUNC(Std_ReturnType, XCP_CODE) Xcp_SendDto(uint8 eventid, P2CONST(Xcp_DtoDataType, AUTOMATIC, XCP_APPL_CONST)astpDto)
{
    Std_ReturnType stdRet = XCP_E_NOT_OK;

    stdRet = Xcp_Send(eventid, astpDto->length, &astpDto->bytes[XCP_INDEX_0]);

    return stdRet;
}
#else
FUNC(Std_ReturnType, XCP_CODE) Xcp_SendDto(P2CONST(Xcp_DtoDataType, AUTOMATIC, XCP_APPL_CONST)astpDto)
{
    Std_ReturnType stdRet = XCP_E_NOT_OK;

    stdRet = Xcp_Send(astpDto->length, &astpDto->bytes[XCP_INDEX_0]);

    return stdRet;
}

/*
********************************************************************************
* Function Name: Xcp_SendEthDaq
*
* Explanation: Send a EthDAQ.
*
* param: astpDto: pointer to XCP packet type definition.
*
* retval: XCP_E_OK: Transmit request has been accepted.
*         XCP_E_NOT_OK: Transmit request has not been accepted.
********************************************************************************
*/
#if( XCP_ONETHERNET_ENABLE == STD_ON )
FUNC(Std_ReturnType, XCP_CODE) Xcp_SendEthDaq(P2CONST(Xcp_EthDtoType, AUTOMATIC, XCP_APPL_CONST)astpDto)
{
    Std_ReturnType stdRet = XCP_E_NOT_OK;

    stdRet = EthXcp_Send((uint16)astpDto->length, &astpDto->bytes[XCP_INDEX_0]);

    return stdRet;
}
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
#endif  /* #ifdef XCP_ENABLE_DAQ */

/*
********************************************************************************
* Function Name: Xcp_SendDtoMode
*
* Explanation: Select the sending method of dto.
*
* param: astpDto: pointer to XCP packet type definition.
*
* retval: None
********************************************************************************
*/
#if( (XCP_ENABLE_SEND_QUEUE == STD_OFF) && (XCP_MULTIPDUIDSUPPORT == STD_OFF) )
FUNC(void, XCP_CODE) Xcp_SendDtoMode(P2VAR(Xcp_DtoDataType, AUTOMATIC, XCP_APPL_DATA)astpDto)
{
#if( XCP_ONETHERNET_ENABLE == STD_ON )
    Xcp_EthDtoType ethData = {XCP_INIT_0, {XCP_INIT_0}};
    uint8* dtoi = NULL_PTR;
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */

    if( (XCP_BUS_CAN == Xcp_ConnectionStatus.busType) || (XCP_BUS_CANFD == Xcp_ConnectionStatus.busType) )
    {
#if( XCP_ONCAN_ENABLE == STD_ON )
        Xcp_SendDto(astpDto);
#endif  /* XCP_ONCAN_ENABLE == STD_ON */
    }
    else if( XCP_BUS_ETHERNET == Xcp_ConnectionStatus.busType )
    {
#if( XCP_ONETHERNET_ENABLE == STD_ON )
        dtoi = &ethData.bytes[XCP_INDEX_0];
        (*(uint8*)(dtoi + XCP_VALUE_0)) = (uint8)((astpDto->length) & XCP_U8_MASK);
        (*(uint8*)(dtoi + XCP_VALUE_1)) = (uint8)((astpDto->length >> XCP_SHIFT_8) & XCP_U8_MASK);
        (*(uint8*)(dtoi + XCP_VALUE_2)) = (uint8)((Xcp_EthCtrTx) & XCP_U8_MASK);
        (*(uint8*)(dtoi + XCP_VALUE_3)) = (uint8)((Xcp_EthCtrTx >> XCP_SHIFT_8) & XCP_U8_MASK);
        Xcp_EthCtrTx++;
        dtoi = &dtoi[XCP_ETH_DAQ_DTO_DAT_OFFSET];
        Xcp_MemCpy8(dtoi, &astpDto->bytes[XCP_INDEX_0], astpDto->length);
        ethData.length += (astpDto->length + XCP_ETH_DAQ_DTO_HEAD_LEN);
        Xcp_SendEthDaq(&ethData);
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
    }
    else
    {
        Xcp_Det_ErrorReport(XCP_SID_SENDDTOMODE, XCP_E_PARAM_ERROR);
    }
}
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_OFF && XCP_MULTIPDUIDSUPPORT == STD_OFF */

/*
********************************************************************************
* Function Name: XCP_Event
*
* Explanation: Handling of data acquisition or stimulation event channel.
*
* param: avcEvent: event channel number to process.
*
* retval: None
********************************************************************************
*/
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
FUNC(uint8, XCP_CODE) Xcp_Event(uint8 avcEvent)
{
    /* Return value. */
    uint8 status = XCP_INIT_0;
    uint8 daq;
    uint8 odt = XCP_INIT_0;
    /* Dto data start location. */
    uint8 index = XCP_INIT_0;
    uint8 curTimestampType = xcpConnCfgPtr->XcpTimestampType;
    /* Xcp_OdtEntrySize */
    uint16 entrySize = XCP_INIT_0;
    uint16 firstEntry = XCP_INIT_0;
    uint16 lastEntry = XCP_INIT_0;
    Std_ReturnType retValue = XCP_E_NOT_OK;
    /* DAQ timestamp. */
    Xcp_TimestampType xcpTimeStamp;
    /* Dto pointer. */
    Xcp_DtoDataType* dtop = NULL_PTR;
    uint8* dtoi = NULL_PTR;
    const Xcp_ConnectionCfgType *xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];

    status = (uint8)XCP_INIT_0;
    /* daq did not startup, return; */
    if( (Xcp_DataInformation.sessionStatus & (uint8)XCP_SS_DAQ) == XCP_VALUE_0 )
    {
        retValue = (uint8)XCP_EVENT_NOP;
    }
    else  /* if( (Xcp_DataInformation.sessionStatus & (uint8)XCP_SS_DAQ) == XCP_VALUE_0 ) */
    {
        /* Event send. */
#if( defined (XCP_MAX_EVENT) && ! defined (XCP_ENABLE_MULDAQ_EVENT) )
        if( (uint8)XCP_MAX_EVENT <= avcEvent )
        {
            retValue = (uint8)XCP_EVENT_NOP;
        }
        else  /* if( (uint8)XCP_MAX_EVENT <= avcEvent ) */
        {
            daq = Xcp_DataInformation.daq.eventDaq[avcEvent];
            /* DAQ is less than daqcount and belongs to the channel. */
            if( ((daq < Xcp_DataInformation.daq.daqCount) &&
                ((Xcp_DaqListFlags(daq) & (uint8)XCP_DAQ_FLAG_RUNNING) != XCP_VALUE_0)) )
            {

#else  /* defined (XCP_MAX_EVENT) && ! defined (XCP_ENABLE_MULDAQ_EVENT) */

            for( daq = XCP_VALUE_0; daq < Xcp_DataInformation.daq.daqCount; daq++ )
            {
                /* Is DAQ started? */
                if( (Xcp_DaqListFlags(daq)& (uint8)XCP_DAQ_FLAG_RUNNING) != XCP_VALUE_0 )
                {
                    /* Judge whether DAQ belongs to the channel. */
                    if( Xcp_DaqListEventChannel(daq) == avcEvent )
                    {
#endif  /* defined (XCP_MAX_EVENT) && ! defined (XCP_ENABLE_MULDAQ_EVENT) */
                        /* pre send. */
#if( XCP_PRESCALER_SUPPORTED == STD_ON )
                        Xcp_DaqListCycle(daq)--;
                        if( Xcp_DaqListCycle(daq) == (uint8)XCP_VALUE_0 )
                        {
                            Xcp_DaqListCycle(daq) = Xcp_DaqListPrescaler(daq);
#endif  /* XCP_PRESCALER_SUPPORTED == STD_ON */
                            /* Data Stimulation (STIM) */
                            for( odt = Xcp_DaqListFirstOdt(daq); odt <= Xcp_DaqListLastOdt(daq); odt++ )
                            {
                                status |= (uint8)XCP_EVENT_DAQ;
                                /* The following code is not reentrant. */
                                Xcp_InterruptDisable();

#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
                                /* Check if there is space in the queue for this ODT. */
                                if( Xcp_DataInformation.queueLen[daq] >= Xcp_DataInformation.queueSize[daq] )
                                {
                                    /* Queue overflow. */
                                    status |= (uint8)XCP_EVENT_DAQ_OVERRUN;
                                    Xcp_DaqListFlags(daq) |= (uint8)XCP_DAQ_FLAG_OVERRUN;
                                }
                                else
                                {
                                    /* Xcp_DataInformation.queueLen >= Xcp_DataInformation.queueSize. */
                                    /* Positioning the dtop to a valid location on the queue. */
                                    dtop = &Xcp_pDataQueue(daq, ((Xcp_DataInformation.queueRp[daq] + Xcp_DataInformation.queueLen[daq])
                                            % Xcp_DataInformation.queueSize[daq]));
                                    Xcp_DataInformation.queueLen[daq]++;
#else  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
                                    dtop = &Xcp_DtoData;
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
                            /* Is ODT absolute or relative? This procedure is absolute. */
#if( XCP_ID_TYPE_ABSOLUTE == XCP_IDENTIFICATION_FIELD_TYPE )
                                    /* PID */
                                    dtop->bytes[XCP_INDEX_0] = odt;
                                    index = XCP_VALUE_1;
#else  /* XCP_ID_TYPE_ABSOLUTE == XCP_IDENTIFICATION_FIELD_TYPE */
                                    /* ODT,DAQ */
                                    /* Relative odt number. */
                                    dtop->bytes[XCP_INDEX_0] = odt - Xcp_DaqListFirstOdt(daq);
                                    dtop->bytes[XCP_INIT_1] = daq;
                                    index = XCP_VALUE_2;
#endif  /* XCP_ID_TYPE_ABSOLUTE == XCP_IDENTIFICATION_FIELD_TYPE */
                                    curTimestampType = xcpConnCfgPtr->XcpTimestampType;
                                    if( XCP_VALUE_0 < curTimestampType )
                                    {
                                        /* If it is the first ODT and timestamp mode is enabled,
                                        acquire timestamp and insert in response frame. */
                                        if( (Xcp_DaqListFirstOdt(daq) == odt) &&
                                            ((Xcp_DaqListFlags(daq) & XCP_DAQ_FLAG_TIMESTAMP) != XCP_VALUE_0) )
                                        {
                                            /* Acquire timestamp. */
                                            xcpTimeStamp = ApplXcpGetTimestamp();
                                            /* Add a timestamp to the ODT according to the length of the timestamp. */
                                            if( XCPTS_ONE_BYTE == curTimestampType )
                                            {
                                                dtop->bytes[index] = (uint8)xcpTimeStamp;
                                            }
                                            else if( XCPTS_TWO_BYTE == curTimestampType )
                                            {
                                                dtop->bytes[index] = (uint8)((xcpTimeStamp) & XCP_U8_MASK);
                                                dtop->bytes[index + XCP_VALUE_1] = (uint8)(((xcpTimeStamp) >> XCP_SHIFT_8) & XCP_U8_MASK);
                                            }
                                            else
                                            {
                                                dtop->bytes[index] = (uint8)((xcpTimeStamp) & XCP_U8_MASK);
                                                dtop->bytes[index + XCP_VALUE_1] = (uint8)(((xcpTimeStamp) >> XCP_SHIFT_8) & XCP_U8_MASK);
                                                dtop->bytes[index + XCP_VALUE_2] = (uint8)(((xcpTimeStamp) >> XCP_SHIFT_16) & XCP_U8_MASK);
                                                dtop->bytes[index + XCP_VALUE_3] = (uint8)(((xcpTimeStamp) >> XCP_SHIFT_24) & XCP_U8_MASK);
                                            }
                                            index += curTimestampType;
                                        }
                                    }

                                    /* Use BIT7 of PID or ODT to indicate overruns. */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )

#ifdef XCP_ENABLE_DAQ_OVERRUN_INDICATION
                                    if( (Xcp_DaqListFlags(daq) & (uint8)XCP_DAQ_FLAG_OVERRUN) != XCP_VALUE_0 )
                                    {
                                        dtop->bytes[XCP_INDEX_0] |= (uint8)XCP_MASK_BYTE_80;
                                        Xcp_DaqListFlags(daq) &= (~XCP_DAQ_FLAG_OVERRUN & XCP_U8_MASK);
                                    }
#endif  /* defined (XCP_ENABLE_DAQ_OVERRUN_INDICATION) */

#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
                                    /* Sample data sampling data cycle the entire ODT table reads the corresponding
                                    data into dtop - > daqMemSize [] according to the odtentryaddr in each odtentry. */
                                    /* This is the inner loop, optimize here. */
                                    firstEntry = Xcp_DaqListOdtFirstEntry(odt);
                                    dtoi = (uint8*)&dtop->bytes[index];
                                    if( Xcp_OdtEntrySize(firstEntry) == XCP_VALUE_0 )
                                    {
                                    /* goto next_odt. */
                                        dtop->length = (uint32)(dtoi-(&dtop->bytes[XCP_INDEX_0]));
                                    }
                                    else
                                    {
                                        lastEntry = Xcp_DaqListOdtLastEntry(odt);
                                        entrySize = XCP_VALUE_0;
                                        while( firstEntry <= lastEntry )
                                        {
                                            entrySize += Xcp_OdtEntrySize(firstEntry);
                                            firstEntry++;
                                        }
                                        /* Determine if it is out of range. */
                                        if( xcpConnCfgPtr->Xcp_Max_Dto < (entrySize + index) )
                                        {
                                            break;
                                        }
                                        firstEntry = Xcp_DaqListOdtFirstEntry(odt);
                                        while( firstEntry <= lastEntry )
                                        {
                                            entrySize = Xcp_OdtEntrySize(firstEntry);
                                            if( XCP_VALUE_0 == entrySize )
                                            {
                                                break;
                                            }
                                            if( NULL_PTR == Xcp_OdtEntryAddr(firstEntry) )
                                            {
                                                /* Suppress warning for MISRA rule 101 (pointer arithmetic) */
                                                dtoi = &dtoi[entrySize];
                                            }
                                            else
                                            {
                                                /* Copy data from ODT to SEND_QUEUE. */
                                                Xcp_MemCpy8(dtoi, Xcp_OdtEntryAddr(firstEntry), entrySize);
                                                /* Suppress warning for MISRA rule 101 (pointer arithmetic). */
                                                dtoi= &dtoi[entrySize];
                                            }
                                            firstEntry++;
                                        }
                                        dtop->length = (uint32)(dtoi-(&dtop->bytes[XCP_INDEX_0]));
                                    /* XCP_ASSERT(dtop->l<=XCP_MAX_DTO); */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
#else
                                        Xcp_SendDto(avcEvent, &Xcp_DtoData);
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */

                                    }  /* Xcp_OdtEntrySize(firstEntry) == XCP_VALUE_0 */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
                                }  /* Xcp_DataInformation.queueLen >= Xcp_DataInformation.queueSize */
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
                                Xcp_InterruptEnable();
                            }  /* for( odt = Xcp_DaqListFirstOdt(daq); odt <= Xcp_DaqListLastOdt(daq); odt++ ) */
                            retValue = status;

#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
                            (void)Xcp_SendDtoFromQueue(avcEvent);
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */

#if( XCP_PRESCALER_SUPPORTED == STD_ON )
                        }
#endif  /* XCP_PRESCALER_SUPPORTED == STD_ON */

#if !(defined (XCP_MAX_EVENT) && ! defined (XCP_ENABLE_MULDAQ_EVENT))
                    }
                }
            }
#else  /* #if !(defined (XCP_MAX_EVENT) && ! defined (XCP_ENABLE_MULDAQ_EVENT)) */
            }
        }
#endif  /* #if !(defined (XCP_MAX_EVENT) && ! defined (XCP_ENABLE_MULDAQ_EVENT)) */

    }  /* if( (Xcp_DataInformation.sessionStatus & (uint8)XCP_SS_DAQ) == XCP_VALUE_0 ) */

    return retValue;
}
#else
FUNC(uint8, XCP_CODE) Xcp_Event(uint8 avcEvent)
{
    uint8 daq;
    /* Return value. */
    uint8 status = XCP_INIT_0;
    Std_ReturnType retValue = XCP_E_NOT_OK;

    /* daq did not startup, return; */
    if( (Xcp_DataInformation.sessionStatus & (uint8)XCP_SS_DAQ) == XCP_VALUE_0 )
    {
        retValue = (uint8)XCP_EVENT_NOP;
    }
    else
    {
        /* Event send. */
#if( defined (XCP_MAX_EVENT) && ! defined (XCP_ENABLE_MULDAQ_EVENT) )
        if( (uint8)XCP_MAX_EVENT <= avcEvent )
        {
            retValue = (uint8)XCP_EVENT_NOP;
        }
        else
        {
            daq = Xcp_DataInformation.daq.eventDaq[avcEvent];
            /* DAQ is less than daqcount and belongs to the channel. */
            if( ((daq < Xcp_DataInformation.daq.daqCount) &&
                ((Xcp_DaqListFlags(daq) & (uint8)XCP_DAQ_FLAG_RUNNING) != XCP_VALUE_0)) )
            {
#else
            /* Send DAQ list or receive STIM. */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
                for( daq = Xcp_DaqNumber; daq < Xcp_DataInformation.daq.daqCount; daq++ )
#else
                for( daq = XCP_VALUE_0; daq < Xcp_DataInformation.daq.daqCount; daq++ )
#endif  /*  XCP_ENABLE_SEND_QUEUE == STD_ON */
                {
                    /* Is DAQ started? */
                    if( (Xcp_DaqListFlags(daq)& (uint8)XCP_DAQ_FLAG_RUNNING) != XCP_VALUE_0 )
                    {
                        /* Judge whether DAQ belongs to the channel. */
                        if( Xcp_DaqListEventChannel(daq) == avcEvent )
                        {
#endif  /* defined (XCP_MAX_EVENT) && ! defined (XCP_ENABLE_MULDAQ_EVENT) */
                            if( (Xcp_DaqListFlags(daq) & (uint8)XCP_DAQ_FLAG_DIRECTION) != XCP_VALUE_0 )
                            {
                                status = Xcp_StimEvent(daq);
                            }
                            else
                            {
                                status = Xcp_DaqEvent(daq);
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
                                /* Check if all ODT in the current Daq list have been sent. */
                                if( Xcp_OdtNumber != XCP_VALUE_0 )
                                {
                                    /* It is necessary to continue sending the current DAQ list in the next cycle. */
                                    Xcp_DaqNumber = daq;
                                    break;
                                }
#endif  /*  XCP_ENABLE_SEND_QUEUE == STD_ON */
                            }
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
                            /* Check the DAQ list count. */
                            if( daq >= (Xcp_DataInformation.daq.daqCount - XCP_VALUE_1) )
                            {
                                /* Clear Xcp_DaqNumber. */
                                Xcp_DaqNumber = XCP_VALUE_0;
                            }
#endif  /*  XCP_ENABLE_SEND_QUEUE == STD_ON */
                            retValue = status;
#ifdef XCP_ENABLE_MULDAQ_EVENT
                        }
                    }
                }  /* daq */
#else
            }
        }
#endif  /* #ifdef XCP_ENABLE_MULDAQ_EVENT */
    }

    return retValue;
}
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */

#if( XCP_MULTIPDUIDSUPPORT == STD_OFF )
/*
********************************************************************************
* Function Name: Xcp_StimEvent
*
* Explanation: xcp stim active process.
*
* param: daq: the daq belong to chanel.
*
* retval: None
********************************************************************************
*/
FUNC(uint8, XCP_CODE) Xcp_StimEvent(uint8 daq)
{
    uint8 indexFromRp = XCP_INIT_0;
    uint8 indexFromZero = XCP_INIT_0;
    uint8 indexStop = XCP_INIT_0;
    uint8 entrySize = XCP_INIT_0;
    uint8 status = XCP_INIT_0;
    /* Current queue. */
    uint16 nowQueue = XCP_INIT_0;
    uint16 odt = XCP_INIT_0;
    uint16 firstEntry = XCP_INIT_0;
    uint16 lastEntry = XCP_INIT_0;
    Std_ReturnType retValue = XCP_E_NOT_OK;
    uint8* ptrData = NULL_PTR;

    /* Pre send. */
#if( XCP_PRESCALER_SUPPORTED == STD_ON )
    Xcp_DaqListCycle(daq)--;
    if( (uint8)XCP_VALUE_0 == Xcp_DaqListCycle(daq) )
    {
        Xcp_DaqListCycle(daq) = Xcp_DaqListPrescaler(daq);
#endif  /* XCP_PRESCALER_SUPPORTED == STD_ON */
        Xcp_InterruptDisable();
        if( Xcp_DataInformation.queueLenStim > Xcp_DataInformation.queueSizeStim )
        {
            /* Queue overflow. */
            status |= (uint8)XCP_EVENT_STIM_OVERRUN;
            Xcp_DaqListFlags(daq) |= (uint8)XCP_DAQ_FLAG_OVERRUN;
        }
        else
        {
            status |= (uint8)XCP_EVENT_STIM;
            indexFromRp = XCP_VALUE_0;
            while( indexFromRp < Xcp_DataInformation.queueLenStim )
            {
                nowQueue = Xcp_DataInformation.queueRpStim + indexFromRp;
                if( nowQueue > Xcp_DataInformation.queueSizeStim )
                {
                    nowQueue = nowQueue - Xcp_DataInformation.queueSizeStim - XCP_VALUE_1;
                }

                if( (Xcp_StimOdt(nowQueue) >= Xcp_DaqListFirstOdt(daq)) &&
                    (Xcp_StimOdt(nowQueue) <= Xcp_DaqListLastOdt(daq)) )
                {
                    odt = Xcp_StimOdt(nowQueue);
                    ptrData = Xcp_StimData(nowQueue);
                    firstEntry = Xcp_DaqListOdtFirstEntry(odt);
                    lastEntry = Xcp_DaqListOdtLastEntry(odt);
                    while( firstEntry <= lastEntry )
                    {
                        entrySize = Xcp_OdtEntrySize(firstEntry);
                        if( NULL_PTR == Xcp_OdtEntryAddr(firstEntry) )
                        {
                            /* Suppress warning for MISRA rule 101 (pointer arithmetic), Skip this data. */
                            ptrData = &ptrData[entrySize];
                        }
                        else
                        {
                            /* Copy data from RECEIVE_QUEUE to ODT. */
                            Xcp_MemCpy8(Xcp_OdtEntryAddr(firstEntry), ptrData, entrySize);
                            ptrData = &ptrData[entrySize];
                        }
                        firstEntry++;
                    }

                    if( (Xcp_DataInformation.queueRpStim + Xcp_DataInformation.queueLenStim) < Xcp_DataInformation.queueSizeStim )
                    {
                        /* Move the ODT in the back one position forward. */
                        for( ; nowQueue < (Xcp_DataInformation.queueSizeStim - XCP_VALUE_1); nowQueue++ )
                        {
                            Xcp_MemCpy8(&Xcp_DataInformation.pQueueStim[nowQueue*Xcp_DataInformation.queueUnitSize],
                                        &Xcp_DataInformation.pQueueStim[(nowQueue + XCP_VALUE_1)*Xcp_DataInformation.queueUnitSize],
                                        Xcp_DataInformation.queueUnitSize);
                        }
                    }
                    else
                    {
                        for( ; nowQueue < (Xcp_DataInformation.queueSizeStim - XCP_VALUE_1); nowQueue++ )
                        {
                            Xcp_MemCpy8(&Xcp_DataInformation.pQueueStim[nowQueue*Xcp_DataInformation.queueUnitSize],
                                        &Xcp_DataInformation.pQueueStim[(nowQueue + XCP_VALUE_1)*Xcp_DataInformation.queueUnitSize],
                                        Xcp_DataInformation.queueUnitSize);
                        }

                        indexStop = Xcp_DataInformation.queueLenStim - (Xcp_DataInformation.queueSizeStim - Xcp_DataInformation.queueRpStim);
                        if( XCP_VALUE_0 == indexStop )
                        {
                            Xcp_MemCpy8(
                                    &Xcp_DataInformation.pQueueStim[(Xcp_DataInformation.queueSizeStim - XCP_VALUE_1)*Xcp_DataInformation.queueUnitSize],
                                    &Xcp_DataInformation.pQueueStim[XCP_INDEX_0],
                                    Xcp_DataInformation.queueUnitSize);

                            for( indexFromZero = XCP_VALUE_1; indexFromZero < indexStop; indexFromZero++ )
                            {
                                Xcp_MemCpy8(&Xcp_DataInformation.pQueueStim[indexFromZero*Xcp_DataInformation.queueUnitSize],
                                            &Xcp_DataInformation.pQueueStim[(indexFromZero + XCP_VALUE_1)*Xcp_DataInformation.queueUnitSize],
                                            Xcp_DataInformation.queueUnitSize);
                            }
                        }
                        else
                        {
                            Xcp_RecordError(XCP_CRC_MEMORY_OVERFLOW);
                            (void)Xcp_SendCrm();
                        }
                    }
                    Xcp_DataInformation.queueLenStim--;
                }
                else
                {
                    indexFromRp++;
                }
            }
        }
        Xcp_InterruptEnable();

        retValue = status;
#if( XCP_PRESCALER_SUPPORTED == STD_ON )
    }
#endif  /* XCP_PRESCALER_SUPPORTED == STD_ON */

    return retValue;
}

/*
********************************************************************************
* Function Name: Xcp_DaqEvent
*
* Explanation: xcp daq active process.
*
* param: daq: the daq belong to chanel.
*
* retval: None
********************************************************************************
*/
FUNC(uint8, XCP_CODE) Xcp_DaqEvent(uint8 daq)
{
    uint8 odtNum = XCP_INIT_0;
    /* Return value. */
    uint8 status = XCP_INIT_0;
    uint16 odt = XCP_INIT_0;
    /* Dto data start location. */
    uint8 index = XCP_INIT_0;
    uint16 firstEntry = XCP_INIT_0;
    uint16 lastEntry = XCP_INIT_0;
    /* Xcp_OdtEntrySize */
    uint16 entrySize = XCP_INIT_0;
    Std_ReturnType retValue = XCP_E_NOT_OK;
    /* Dto pointer. */
    Xcp_DtoDataType* dtop = NULL_PTR;
    /* DAQ timestamp. */
    Xcp_TimestampType xcpTimeStamp;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
    uint8 curTimestampType = xcpConnCfgPtr->XcpTimestampType;
    uint8* dtoi = NULL_PTR;

    status = (uint8)XCP_INIT_0;

    /* Pre send. */
#if( XCP_PRESCALER_SUPPORTED == STD_ON )
    Xcp_DaqListCycle(daq)--;
    if( Xcp_DaqListCycle(daq) == (uint8)XCP_VALUE_0 )
    {
        Xcp_DaqListCycle(daq) = Xcp_DaqListPrescaler(daq);
#endif  /* XCP_PRESCALER_SUPPORTED == STD_ON */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
        /* If the data of the last period is not sent, the system discards it. */
        if( XCP_VALUE_0 != (Xcp_DataInformation.sendStatus & (XCP_DTO_REQUEST | XCP_DTO_PENDING)) )
        {
            Xcp_DataInformation.sendStatus &= (uint8)~(XCP_DTO_REQUEST | XCP_DTO_PENDING);
            /* daq overloay. */
            Xcp_DaqListFlags(daq) |= (uint8)XCP_DAQ_FLAG_OVERRUN;
        }
        else
        {
            Xcp_DaqListFlags(daq) &= (uint8)~XCP_DAQ_FLAG_OVERRUN;
        }
        if( XCP_VALUE_0 == Xcp_OdtNumber )
        {
            Xcp_QueueInit();
#if( XCP_ONETHERNET_ENABLE == STD_ON )
            Xcp_EthDaqTxConfirmEnable = FALSE;
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
            /* Data Stimulation (STIM) */
            for( odt = Xcp_DaqListFirstOdt(daq); odt <= Xcp_DaqListLastOdt(daq); odt++ )
            {
                status |= (uint8)XCP_EVENT_DAQ;
                /* The following code is not reentrant. */
                Xcp_InterruptDisable();
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
                /* Positioning the dtop to a valid location on the queue. */
                dtop = Xcp_pDataQueue(Xcp_DataInformation.queueWp);
                Xcp_DataInformation.queueWp++;
                if( Xcp_DataInformation.queueWp >= Xcp_DataInformation.queueSize )
                {
                    /* The memorysize space is insufficient. */
                    status |= (uint8)XCP_EVENT_DAQ_OVERRUN;
                }
#else
                dtop = &Xcp_DtoDataInfo;
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
                /* Is ODT absolute or relative? This procedure is absolute. */
#if( XCP_ID_TYPE_ABSOLUTE == XCP_IDENTIFICATION_FIELD_TYPE )
                /* PID */
                dtop->bytes[XCP_INDEX_0] = odt;
                index = XCP_DAQ_DTO_PID_LEN;
#else
                /* ODT,DAQ */
                /* Relative odt number. */
                dtop->bytes[XCP_DAQ_ABS_ODT_PID_IDX_OFFSET] = odt - Xcp_DaqListFirstOdt(daq);
                dtop->bytes[XCP_DAQ_ABS_ODT_DAQ_LIST_IDX_OFFSET] = daq;
                index = XCP_DAQ_DTO_PID_LEN;
#endif  /* XCP_ID_TYPE_ABSOLUTE == XCP_IDENTIFICATION_FIELD_TYPE */

                if( XCP_VALUE_0 < curTimestampType )
                {
                    /* If it is the first ODT and timestamp mode is enabled,
                    acquire timestamp and insert in response frame. */
                    if( (Xcp_DaqListFirstOdt(daq) == odt) &&
                        ((Xcp_DaqListFlags(daq) & XCP_DAQ_FLAG_TIMESTAMP) != XCP_VALUE_0) )
                    {
                        /* Acquire timestamp. */
                        xcpTimeStamp = ApplXcpGetTimestamp();
                        /* Add a timestamp to the ODT according to the length of the timestamp. */
                        if( XCPTS_ONE_BYTE == curTimestampType )
                        {
                            dtop->bytes[index] = (uint8)xcpTimeStamp;
                        }
                        else if( XCPTS_TWO_BYTE == curTimestampType )
                        {
                            dtop->bytes[index] = (uint8)((xcpTimeStamp) & XCP_U8_MASK);
                            dtop->bytes[index + XCP_VALUE_1] = (uint8)(((xcpTimeStamp) >> XCP_SHIFT_8) & XCP_U8_MASK);
                        }
                        else
                        {
                            dtop->bytes[index] = (uint8)((xcpTimeStamp) & XCP_U8_MASK);
                            dtop->bytes[index + XCP_VALUE_1] = (uint8)(((xcpTimeStamp) >> XCP_SHIFT_8) & XCP_U8_MASK);
                            dtop->bytes[index + XCP_VALUE_2] = (uint8)(((xcpTimeStamp) >> XCP_SHIFT_16) & XCP_U8_MASK);
                            dtop->bytes[index + XCP_VALUE_3] = (uint8)(((xcpTimeStamp) >> XCP_SHIFT_24) & XCP_U8_MASK);
                        }
                        index += curTimestampType;
                    }
                }

/* Use BIT7 of PID or ODT to indicate overruns. */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )

#ifdef XCP_ENABLE_DAQ_OVERRUN_INDICATION
                if( (Xcp_DaqListFlags(daq) & (uint8)XCP_DAQ_FLAG_OVERRUN) != XCP_VALUE_0 )
                {
                    dtop->bytes[XCP_INDEX_0] |= XCP_DAQ_OVERLOAD_PID;
                    Xcp_DaqListFlags(daq) &= ((uint8)~XCP_DAQ_FLAG_OVERRUN & XCP_U8_MASK);
                }
#endif  /* #ifdef XCP_ENABLE_DAQ_OVERRUN_INDICATION */

#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
                /* Sample data sampling data cycle the entire ODT table reads the corresponding data
                into dtop - > daqMemSize [] according to the odtentryaddr in each odtentry. */
                /* This is the inner loop, optimize here. */
                firstEntry = Xcp_DaqListOdtFirstEntry(odt);
                dtoi = (uint8*)&dtop->bytes[index];
                if( Xcp_OdtEntrySize(firstEntry) == XCP_VALUE_0 )
                {
                    /* goto next_odt. */
                    dtop->length = (uint32)index;
                }
                else
                {
                    lastEntry = Xcp_DaqListOdtLastEntry(odt);
                    entrySize = XCP_VALUE_0;
                    while( firstEntry <= lastEntry )
                    {
                        entrySize += Xcp_OdtEntrySize(firstEntry);
                        firstEntry++;
                    }
                    /* Determine if it is out of range. */
                    if( xcpConnCfgPtr->Xcp_Max_Dto < (entrySize + index) )
                    {
                        break;
                    }
                    firstEntry = Xcp_DaqListOdtFirstEntry(odt);
                    while( firstEntry <= lastEntry )
                    {
                        entrySize = Xcp_OdtEntrySize(firstEntry);
                        if( NULL_PTR == Xcp_OdtEntryAddr(firstEntry) )
                        {
                            /* Suppress warning for MISRA rule 101 (pointer arithmetic) */
                            dtoi = &dtoi[entrySize];
                        }
                        else
                        {
                            /* Copy data from ODT to SEND_QUEUE. */
                            Xcp_MemCpy8(dtoi, Xcp_OdtEntryAddr(firstEntry), entrySize);
                            /* Suppress warning for MISRA rule 101 (pointer arithmetic) */
                            dtoi= &dtoi[entrySize];
                        }
                        firstEntry++;
                    }
                    dtop->length = (uint32)(dtoi-(&dtop->bytes[XCP_INDEX_0]));
                    /* XCP_ASSERT(dtop->l<=XCP_MAX_DTO);. */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
#else
                   Xcp_SendDtoMode(&Xcp_DtoDataInfo);
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */

                }  /*Xcp_OdtEntrySize(firstEntry) == XCP_VALUE_0 */
                Xcp_InterruptEnable();
            }  /* odt */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
        }
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
        /* Check the current DAQ quantity. */
        if( XCP_SEND_ODTNUM <= (Xcp_DaqListLastOdt(daq) - Xcp_DaqListFirstOdt(daq)) )
        {
            for( odt = Xcp_DaqListFirstOdt(daq) + Xcp_OdtNumber; odt <= Xcp_DaqListLastOdt(daq); odt++ )
            {
                /* Quantity sent at once: XCP_SEND_ODTNUM. */
                odtNum++;
                /* Send ODT. */
                retValue = Xcp_SendDtoFromQueue();
                /* Check the number of ODTs sent. */
                if( (XCP_SEND_ODTNUM == odtNum) || (XCP_E_OK != retValue) )
                {
                    break;
                }
            }
            Xcp_OdtNumber +=  odtNum;
            /* Check if all ODT in the current Daq list have been sent. */
            if( Xcp_OdtNumber > (Xcp_DaqListLastOdt(daq) - Xcp_DaqListFirstOdt(daq)) )
            {
                /* Clear Xcp_OdtNumber. */
                Xcp_OdtNumber = XCP_VALUE_0;
            }
        }
        else
        {
            /* Cycle sending all ODT. */
            for( odt = Xcp_DaqListFirstOdt(daq); odt <= Xcp_DaqListLastOdt(daq); odt++ )
            {
                /* Send ODT. */
                retValue = Xcp_SendDtoFromQueue();
                if( XCP_E_OK != retValue )
                {
                    break;
                }
            }
        }
#if( XCP_ONETHERNET_ENABLE == STD_ON )
        Xcp_EthDaqTxConfirmEnable = TRUE;
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
        retValue = status;

#if( XCP_PRESCALER_SUPPORTED == STD_ON )
    }
#endif  /* XCP_PRESCALER_SUPPORTED == STD_ON */

    return retValue;
}
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_OFF */

/*
********************************************************************************
* Function Name: XCP_Command
*
* Explanation: xcp command process.
*
* param: avlpCommand: data of received CTO message.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_Command
(
    uint8 connectionId,
    P2CONST(Xcp_CtoType, AUTOMATIC, XCP_APPL_CONST) avlpCommand
)
{
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
    uint8 index;
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
    Std_ReturnType stdRet = XCP_E_NOT_OK;
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
    const Xcp_CtoType* pCmd = (const Xcp_CtoType*) avlpCommand;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = NULL_PTR;

    if( XCP_CONNECTION_CFG_NUM > connectionId )
    {
        xcpConnCfgPtr = &Xcp_ConnectionCfg[connectionId];
        /* CONNECT */
        if( XCP_CRO_CMD == XCP_CC_CONNECT )
        {
		    CalAppl_ChangeOVC();/* WangM */
            /* Prepare the default response. */
            /* No Error. */
            XCP_CRM_CMD = XCP_PID_RES;
            /* Length = 1 */
            Xcp_DataInformation.respDataLen = XCP_VALUE_1;
            /* Reset DAQ. */
            /* Do not reset DAQ if in resume mode. */
#ifdef XCP_ENABLE_DAQ
            if( (Xcp_DataInformation.sessionStatus & (uint8)XCP_SS_RESUME) == XCP_VALUE_0 )
            {
                Xcp_FreeDaq();
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )

#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
                for( index = XCP_INDEX_0; index < XCP_TXPDU_LIST; index++ )
                {
                    /* Clear all transmission flags. */
                    Xcp_DataInformation.sendStatus[index] = XCP_CLEAN_SEND_FLAG;
                }
#else  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
                /* Clear all transmission flags. */
                Xcp_DataInformation.sendStatus = XCP_CLEAN_SEND_FLAG;
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */

#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
            }
#endif  /* #ifdef XCP_ENABLE_DAQ */

#if( XCP_ENABLE_SEED_KEY == STD_ON )
            /* Lock all resources. */
            Xcp_DataInformation.protectionStatus = (uint8)(XCP_RM_CAL_PAG | XCP_RM_DAQ | XCP_RM_PGM | XCP_RM_STIM);
#endif  /* XCP_ENABLE_SEED_KEY == STD_ON */
            /* Reset Session Status. */
            Xcp_DataInformation.sessionStatus = XCP_SS_CONNECTED;
            /* Records the bus type and connectionID of the current connection. */
            Xcp_ConnectionStatus.connectionId = connectionId;
            Xcp_ConnectionStatus.busType = xcpConnCfgPtr->XcpBusType;

            Xcp_DataInformation.respDataLen = XCP_CRM_CONNECT_LEN;

#ifdef XCP_ENABLE_CALIBRATION_PAGE
            /* CRM[1] */
            XCP_CRM_CONNECT_RESOURCE |= XCP_RM_CAL_PAG;
#else  /* #ifdef XCP_ENABLE_CALIBRATION_PAGE */
            XCP_CRM_CONNECT_RESOURCE = XCP_VALUE_0;
#endif  /* #ifdef XCP_ENABLE_CALIBRATION_PAGE */

#ifdef XCP_ENABLE_DAQ
            /* Data Acquisition. */
            XCP_CRM_CONNECT_RESOURCE |= (uint8)XCP_RM_DAQ_STIM;
#endif  /* #ifdef XCP_ENABLE_DAQ */

#if( XCP_FLASH_PROGRAMING_ENABLE == STD_ON )
            XCP_CRM_CONNECT_RESOURCE |= (uint8)XCP_RM_PGM;
#endif  /* XCP_FLASH_PROGRAMING_ENABLE == STD_ON */

#ifdef XCP_ENABLE_COMM_MODE_INFO
            XCP_CRM_CONNECT_COMM_BASIC |= (uint8)XCP_CMB_OPTIONAL;
#endif  /* #ifdef XCP_ENABLE_COMM_MODE_INFO */

            /* CRM[2] */
            XCP_CRM_CONNECT_COMM_BASIC |= (uint8)XCP_CMB_ADDRESS_GRANULARITY_BYTE;
#if( CPU_BYTE_ORDER == LOW_BYTE_FIRST )
            XCP_CRM_CONNECT_COMM_BASIC |= (uint8)XCP_PI_INTEL;
#else  /* CPU_BYTE_ORDER == LOW_BYTE_FIRST */
            XCP_CRM_CONNECT_COMM_BASIC |= (uint8)XCP_PI_MOTOROLA;
#endif  /* CPU_BYTE_ORDER == LOW_BYTE_FIRST */
#if( XCP_BLOCK_UPLOAD == STD_ON )
            XCP_CRM_CONNECT_COMM_BASIC |= (uint8)XCP_CMB_SLAVE_BLOCK_MODE;
#endif  /* XCP_BLOCK_UPLOAD == STD_ON */
            /* CRM[3] */
            XCP_CRM_CONNECT_MAX_CTO_SIZE = xcpConnCfgPtr->Xcp_Max_Cto;
            /* CRM[4] */
            XCP_CRM_CONNECT_MAX_DTO_SIZE = xcpConnCfgPtr->Xcp_Max_Dto;
            /* CRM[6] */
            XCP_CRM_CONNECT_PROTOCOL_VERSION = (uint8)( (uint16)XCP_PROTOCOL_VERSION >> XCP_SHIFT_8);
            /* CRM[7] */
            XCP_CRM_CONNECT_TRANSPORT_VERSION = (uint8)( (uint16)XCP_TRANSPORT_LAYER_VERSION >> XCP_SHIFT_8);
            (void)Xcp_SendCrm();
#if( XCP_MULTIPDUIDSUPPORT == STD_OFF )
#ifdef XCP_ENABLE_STIM_QUEUE
            Xcp_DataInformation.queueSizeStim = XCP_INIT_0;
            Xcp_DataInformation.queueLenStim = XCP_INIT_0;
            Xcp_DataInformation.queueRpStim = XCP_INIT_0;
            Xcp_DataInformation.queueUnitSize = XCP_INIT_0;
            (void)Xcp_AllocStimQueueMemory();
#endif  /* #ifdef XCP_ENABLE_STIM_QUEUE */
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_OFF */
        }
        /* XCP_CRO_CMD == XCP_CC_CONNECT */
        /* Handle other commands only if connected. */
        else  /* XCP_CC_CONNECT */
        {
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
            if( (Xcp_DataInformation.sendStatus & XCP_CRM_REQUEST) != XCP_VALUE_0 )
            {
                Xcp_DataInformation.sendStatusReqTimCnt++;
                stdRet = Xcp_SendCrm();
                if( XCP_E_OK == stdRet )
                {
                    Xcp_DataInformation.sendStatus &= (uint8)~XCP_CRM_REQUEST;
                }
                else
                {
                    if( TRANSMITTIMEOUT > Xcp_DataInformation.sendStatusReqTimCnt )
                    {
                        Xcp_DataInformation.sessionStatus |= (uint8)XCP_SS_ERROR;
                        Xcp_DataInformation.sendStatusReqTimCnt = XCP_VALUE_0;
                        Xcp_DataInformation.sendStatus &= (uint8)~XCP_CRM_REQUEST;
                    }
                }
            }
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
            if( (Xcp_DataInformation.sessionStatus & (uint8)XCP_SS_CONNECTED) != XCP_VALUE_0 )
            {
                /* Ignore commands if the previous command sequence has not been completed. */
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )

#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
                if( (Xcp_DataInformation.sendStatus[XCP_EVENT_CHANNEL_NUM] &
                    (uint8)(XCP_CRM_PENDING | XCP_CRM_REQUEST)) != XCP_VALUE_0 )
                {
                    Xcp_DataInformation.sessionStatus |= (uint8)XCP_SS_ERROR;
                    /* No response. */
                }
#else  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
                if( (Xcp_DataInformation.sendStatus & XCP_CRM_REQUEST) != XCP_VALUE_0 )
                {
                    /* Wait for a reply to the previous command. */
                }
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
                else
                {
#else  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
                    /* Prepare the default response. */
                    XCP_CRM_CMD = XCP_PID_RES;
                    Xcp_DataInformation.respDataLen = XCP_VALUE_1;
                    switch( XCP_CRO_CMD )
                    {
                        case XCP_CC_SYNC:
                        {
                            /* Always return a negative response with the error code ERR_CMD_SYNCH. */
                            Xcp_CC_Sync();
                        }
                        break;

#ifdef XCP_ENABLE_COMM_MODE_INFO
                        case XCP_CC_GET_COMM_MODE_INFO:
                        {
                            Xcp_CC_GetCommModeInfo();
                        }
                        break;
#endif  /* #ifdef XCP_ENABLE_COMM_MODE_INFO */

                        case XCP_CC_DISCONNECT:
                        {
                            Xcp_CC_Disconnect();
                        }
                        break;
                        case XCP_CC_GET_ID:
                        {
                            Xcp_CC_GetID(pCmd);
                        }
                        break;
                        case XCP_CC_GET_STATUS:
                        {
                            Xcp_CC_GetStatus();
                        }
                        break;

#if( XCP_ENABLE_SEED_KEY == STD_ON )
                        case XCP_CC_GET_SEED:
                        {
                            /* Check whether the first part or a remaining part of the seed is requested. */
                            Xcp_CC_GetSeed(pCmd);
                        }
                        break;
                        case XCP_CC_UNLOCK:
                        {
                            Xcp_CC_UnLock(pCmd);
                        }
                        break;
#endif  /* XCP_ENABLE_SEED_KEY == STD_ON */

#ifdef XCP_ENABLE_CALIBRATION_PAGE
                        case XCP_CC_SET_CAL_PAGE:
                        {
                            Xcp_CC_SetCalpage(pCmd);
                        }
                        break;
                        case XCP_CC_GET_CAL_PAGE:
                        {
                            Xcp_CC_GetCalPage(pCmd);
                        }
                        break;
                        /* Paging Information optional. */
                        case XCP_CC_GET_PAG_PROCESSOR_INFO:
                        {
                            Xcp_CC_GetPagProcessorInfo();
                        }
                        break;
#endif  /* #ifdef XCP_ENABLE_CALIBRATION_PAGE */

                        case XCP_CC_GET_SEGMENT_INFO:
                        {
                            Xcp_CC_GetSegmentInfo(pCmd);
                        }
                        break;
                        case XCP_CC_GET_PAGE_INFO:
                        {
                            Xcp_CC_GetPageInfo(pCmd);
                        }
                        break;
                        /* Paging freeze mode support. */
#ifdef XCP_ENABLE_PAGE_FREEZE
                        case XCP_CC_SET_SEGMENT_MODE:
                        {
                        }
                        break;
                        case XCP_CC_GET_SEGMENT_MODE:
                        {
                        }
                        break;
#endif  /* #ifdef XCP_ENABLE_PAGE_FREEZE */

                        /* Copy cal page support. */
#ifdef XCP_ENABLE_PAGE_COPY
                        case XCP_CC_COPY_CAL_PAGE:
                        {
                            Xcp_CC_CopyCalPage(pCmd);
                        }
                        break;
#endif  /* #ifdef XCP_ENABLE_PAGE_COPY */
                        case XCP_CC_SET_MTA:
                        {
                            Xcp_CC_SetMta(pCmd);
                        }
                        break;
                        case XCP_CC_DOWNLOAD:
                        {
                            Xcp_CC_Download(pCmd);
                        }
                        break;
#if( XCP_BLOCK_DOWNLOAD == STD_ON )
                        case XCP_CC_DOWNLOAD_NEXT:
                        {
                            Xcp_CC_DownloadNext(pCmd);
                        }
                        break;
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */
                        case XCP_CC_DOWNLOAD_MAX:
                        {
                            Xcp_CC_DownloadMax(pCmd);
                        }
                        break;
                        case XCP_CC_SHORT_DOWNLOAD:
                        {
                            Xcp_CC_ShortDownload(pCmd);
                        }
                        break;
                        case XCP_CC_UPLOAD:
                        {
                            Xcp_CC_UpLoad(pCmd);
                        }
                        break;
                        case XCP_CC_SHORT_UPLOAD:
                        {
                            Xcp_CC_ShortUplod(pCmd);
                        }
                        break;

#if( XCP_ENABLE_CHECKSUM == STD_ON )
                        case XCP_CC_BUILD_CHECKSUM:
                        {
                            Xcp_CC_BuildCheckSum(pCmd);
                            if( XCP_CRM_CMD != XCP_PID_ERR )
                            {
                                Xcp_SendFlag = FALSE;
                            }
                        }
                        break;
#endif  /* XCP_ENABLE_CHECKSUM == STD_ON */

#ifdef XCP_ENABLE_DAQ
                        case XCP_CC_GET_DAQ_PROCESSOR_INFO:
                        {
                            Xcp_CC_GetDaqProcessorInfo();
                        }
                        break;
                        case XCP_CC_GET_DAQ_RESOLUTION_INFO:
                        {
                            Xcp_CC_GetDaqResolutionInfo();
                        }
                        break;
                        case XCP_CC_GET_DAQ_EVENT_INFO:
                        {
                            Xcp_CC_GetDaqEventInfo(pCmd);
                        }
                        break;
                        case XCP_CC_FREE_DAQ:
                        {
                            Xcp_CC_FreeDaq();
                        }
                        break;
                        case XCP_CC_ALLOC_DAQ:
                        {
                            Xcp_CC_AllocDaq(pCmd);
                        }
                        break;
                        case XCP_CC_ALLOC_ODT:
                        {
                            Xcp_CC_AllocOdt(pCmd);
                        }
                        break;
                        case XCP_CC_ALLOC_ODT_ENTRY:
                        {
                            Xcp_CC_AllocOdtEntry(pCmd);
                        }
                        break;
                        case XCP_CC_GET_DAQ_LIST_MODE:
                        {
                            Xcp_CC_GetDaqListMode(pCmd);
                        }
                        break;
                        case XCP_CC_SET_DAQ_LIST_MODE:
                        {
                            Xcp_CC_SetDaqListMode(pCmd);
                        }
                        break;
                        case XCP_CC_SET_DAQ_PTR:
                        {
                            /* Set DAQ ODT entry ptr. */
                            Xcp_CC_SetDaqPtr(pCmd);
                        }
                        break;
                        case XCP_CC_WRITE_DAQ:
                        {
                            /* Write DAQ ODT entry addr and size. */
                            Xcp_CC_WriteDaq(pCmd);
                        }
                        break;
                        case XCP_CC_START_STOP_DAQ_LIST:
                        {
                            Xcp_CC_StartStopDaqList(pCmd);
                        }
                        break;
                        case XCP_CC_START_STOP_SYNCH:
                        {
                            Xcp_CC_StartStopSynch(pCmd);
                        }
                        break;
                        case XCP_CC_GET_DAQ_CLOCK:
                        {
                            Xcp_CC_GetDaqClock();
                        }
                        break;
#endif  /* #ifdef XCP_ENABLE_DAQ */
#if( XCP_FLASH_PROGRAMING_ENABLE == STD_ON )

                        case XCP_CC_PROGRAM_START:
                        {
                            Xcp_CC_Program_Start();
                        }
                        break;

                        case XCP_CC_PROGRAM_CLEAR:
                        {
                            Xcp_CC_Program_Clear(pCmd);
                        }
                        break;

                        case XCP_CC_PROGRAM:
                        {
                            Xcp_CC_Program(pCmd);
                        }
                        break;
#if( XCP_BLOCK_DOWNLOAD == STD_ON )
                        case XCP_CC_PROGRAM_NEXT:
                        {
                            Xcp_CC_Program_Next(pCmd);
                        }
                        break;
#endif  /* XCP_BLOCK_DOWNLOAD == STD_ON */
                        case XCP_CC_PROGRAM_MAX:
                        {
                            Xcp_CC_Program_Max(pCmd);
                        }
                        break;

                        case XCP_CC_PROGRAM_RESET:
                        {
                            Xcp_CC_Program_Reset(pCmd);
                        }
                        break;
#endif  /* XCP_FLASH_PROGRAMING_ENABLE == STD_ON */

#if( XCP_ENABLE_NVM_SAVE_DATA == STD_ON )
                        case XCP_CC_SET_REQUEST:
                        {
                            Xcp_CC_Set_Request(pCmd);
                        }
                        break;
#endif  /* XCP_ENABLE_NVM_SAVE_DATA == STD_ON */

#ifdef XCP_ENABLE_USER_COMMAND
                        case XCP_CC_USER_CMD:
                        {
                        }
                        break;
#endif  /* #ifdef XCP_ENABLE_USER_COMMAND */

                        default:  /* unknown */
                        {
                            Xcp_RecordError(XCP_CRC_CMD_UNKNOWN);
                        }
                        break;
                    }  /* switch */
                    if( Xcp_SendFlag == TRUE )
                    {
                        (void)Xcp_SendCrm();
                    }
#if( XCP_ENABLE_SEND_QUEUE == STD_ON )
                }
#endif  /* XCP_ENABLE_SEND_QUEUE == STD_ON */
            }
            /* Not connected. */
            else
            {
                /* Do nothing. */
            }
        }  /* XCP_CC_CONNECT */
    }
}

#if( XCP_MULTIPDUIDSUPPORT == STD_OFF )
/*
********************************************************************************
* Function Name: Xcp_StimDataProcess
*
* Explanation: STIM data processing function.
*
* param: stimData: STIM data pointer.
*        dateLen: Data length.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_StimDataProcess
(
    P2CONST(uint8, AUTOMATIC, XCP_APPL_DATA) stimData,
    uint32 dateLen
)
{
    uint8 indexDaq;
    uint8 firstOdtFlag = FALSE;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
    uint8 curTimestampType = xcpConnCfgPtr->XcpTimestampType;
    Xcp_StimDtoType* dtoStimp;
    const uint8* stimDataPtr = stimData;

    if( (*stimDataPtr) <= XCP_PID_STIM_END )
    {
        XCP_CRM_CMD = XCP_PID_RES;
        Xcp_DataInformation.respDataLen = XCP_VALUE_1;
        if( Xcp_DataInformation.queueLenStim > Xcp_DataInformation.queueSizeStim )
        {
            Xcp_RecordError(XCP_CRC_MEMORY_OVERFLOW);
            (void)Xcp_SendCrm();
        }
        else
        {
            dtoStimp = (Xcp_StimDtoType*)(&Xcp_DataInformation.pQueueStim[
                    ((Xcp_DataInformation.queueRpStim+Xcp_DataInformation.queueLenStim) % Xcp_DataInformation.queueSizeStim) * Xcp_DataInformation.queueUnitSize]);
            Xcp_DataInformation.queueLenStim++;
#if( XCP_ID_TYPE_ABSOLUTE == XCP_IDENTIFICATION_FIELD_TYPE )
            dtoStimp->stimOdt = *stimDataPtr;
            stimDataPtr = &stimDataPtr[XCP_INIT_1];
#else
            /* ODT,DAQ */
            dtoStimp->stimDaq = *(stimDataPtr + XCP_VALUE_1);
            dtoStimp->stimOdt = *stimDataPtr + Xcp_DaqListFirstOdt(dtoStimp->stimDaq);
            stimDataPtr = stimDataPtr + XCP_VALUE_2;
#endif  /* XCP_ID_TYPE_ABSOLUTE == XCP_IDENTIFICATION_FIELD_TYPE */
            for( indexDaq = XCP_INDEX_0; indexDaq < Xcp_DataInformation.daq.daqCount; indexDaq++ )
            {
                if( dtoStimp->stimOdt == Xcp_DaqListFirstOdt(indexDaq) )
                {
                    firstOdtFlag = TRUE;
                    break;
                }
            }

            if( TRUE == firstOdtFlag )
            {
                if( XCP_VALUE_0 < curTimestampType )
                {
                    if( XCPTS_ONE_BYTE == curTimestampType )
                    {
                        Xcp_MemCpy8(&dtoStimp->stimTimeStamp, stimDataPtr, XCP_VALUE_1);
                        stimDataPtr++;
                    }
                    else if( XCPTS_TWO_BYTE == curTimestampType )
                    {
                        Xcp_MemCpy8(&dtoStimp->stimTimeStamp, stimDataPtr, XCP_VALUE_2);
                        stimDataPtr = &stimDataPtr[XCP_INDEX_2];
                    }
                    else
                    {
                        Xcp_MemCpy8(&dtoStimp->stimTimeStamp, stimDataPtr, XCP_VALUE_4);
                        stimDataPtr = &stimDataPtr[XCP_INDEX_4];
                    }
                }
                Xcp_MemCpy8(dtoStimp->bytes, stimDataPtr,
                            dateLen - curTimestampType - XCP_IDENTIFICATION_FIELD_TYPE);
            }
            else
            {
                Xcp_MemCpy8(dtoStimp->bytes, stimDataPtr,
                dateLen - XCP_IDENTIFICATION_FIELD_TYPE);
            }
        }
    }
}
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_OFF */

/*
********************************************************************************
* Function Name: Xcp_MtaCheckValid
*
* Explanation: Check the scope and permission of the write operation address.
*
* param: addr: address of need to check.
*        size: size of need to check.
*        accessScope: access scope calibration or DAQ/STIM
*
* retval: error code.
********************************************************************************
*/
FUNC(ErrorCodeType, XCP_CODE) Xcp_MtaCheckValid(uint32 addr, uint32 size, uint8 accessScope, uint8 accessType)
{
    uint8 errorCode = XCP_E_NO_ERROR;
#if( RTECALIBRATIONSUPPORT != XCP_CAL_METHOD_MMU )
    uint8 index = XCP_INIT_0;
    uint8 typePermit = XCP_INIT_0;
    uint8 scopePermit = XCP_INIT_0;
    const Xcp_Addr_st* xcpCalPageCfg_ptr;
#else
    XCP_DUMMY_STATEMENT(size);
    XCP_DUMMY_STATEMENT(accessScope);
    XCP_DUMMY_STATEMENT(accessType);
#endif  /* RTECALIBRATIONSUPPORT != XCP_CAL_METHOD_MMU */

#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT )
    xcpCalPageCfg_ptr = &Xcp_SinglePt_Addr[XCP_INDEX_0];
#elif( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_STRUCTUREPT )
    xcpCalPageCfg_ptr = &Xcp_Addr_Stru[XCP_INDEX_0];
#elif( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
    uint8 maxSegmentNum = XCP_REMAPPING_CNT;
    xcpCalPageCfg_ptr = &Xcp_InitRam_Addr[XCP_INDEX_0];
#elif( RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY )
    uint8 maxSegmentNum = XCP_OVERLAY_CNT;
    xcpCalPageCfg_ptr = &Xcp_Overlay_Addr[XCP_INDEX_0];
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_SINGLEPT */
    /* If it is within the address range of Xcp-EventChannel, there is no need to check the address. */
    if( !XCP_CHECK_EVENTADDR(addr) )
    {
#if( (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM) || (RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY) )
        /* Check if the address is within the calibration area. */
        for( ; index < maxSegmentNum; index++ )
        {
            /* Check RAM address range. */
            if( XCP_ADDRESS_CHECK(addr, size, xcpCalPageCfg_ptr[index].addr_wp, xcpCalPageCfg_ptr[index].len) )
            {
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
                Xcp_MapPageIdx = index;
                /* Set address offset. */
                XcpCalOffset = (sint32)XCP_VALUE_0;
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM */
                errorCode = XCP_E_NO_ERROR;
                break;
            }
            /* Check ROM address range. */
            else if( XCP_ADDRESS_CHECK(addr, size, xcpCalPageCfg_ptr[index].addr_rp, xcpCalPageCfg_ptr[index].len) )
            {
#if( RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM )
                Xcp_MapPageIdx = index;
                /* Set address offset. */
                XcpCalOffset = (sint32)(XCP_CALRAM_ADDR(Xcp_MapPageIdx) - XCP_CALFLASH_ADDR(Xcp_MapPageIdx));
#endif  /* RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM */
                errorCode = XCP_E_NO_ERROR;
                break;
            }
            else
            {
                /* Do nothing. */
            }
        }
        if( maxSegmentNum <= index )
        {
            errorCode = XCP_CRC_PAGE_NOT_VALID;
        }
#endif  /* (RTECALIBRATIONSUPPORT == XCP_RTE_CAL_METHOD_INITRAM) || (RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY) */
#if( RTECALIBRATIONSUPPORT != XCP_CAL_METHOD_MMU )
        if( XCP_E_NO_ERROR == errorCode )
        {
            /* Address meets the conditions, check function access permissions */
            typePermit = xcpCalPageCfg_ptr[index].accessType & accessType;
            scopePermit = xcpCalPageCfg_ptr[index].accessScope & accessScope;
            /* Check address write permissions. */
            if( (uint8)XCP_ACCESS_TYPE_WRITE == accessType )
            {
                if( (XCP_VALUE_0 != typePermit) && (XCP_VALUE_0 != scopePermit) )
                {
                    errorCode = XCP_E_NO_ERROR;
                }
                else
                {
                    errorCode = XCP_CRC_ACCESS_DENIED;
                }
            }
            else
            {
                /* Check address read permissions. */
                if( (XCP_VALUE_0 != typePermit) && (XCP_VALUE_0 != scopePermit) )
                {
                    errorCode = XCP_E_NO_ERROR;
                }
                else
                {
                    errorCode = XCP_CRC_ACCESS_DENIED;
                }
            }
        }
#endif  /* RTECALIBRATIONSUPPORT != XCP_CAL_METHOD_MMU */
    }

    return errorCode;
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"
