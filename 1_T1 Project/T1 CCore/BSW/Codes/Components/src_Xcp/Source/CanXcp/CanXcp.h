/*
********************************************************************************
*
* File name: CanXcp.h
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
* Version: 3.0
* Author/Date: YongZ/2020.07.02
* Change: Add release software number
* Cause: Update
********************************************************************************
* Version: 3.1
* Author/Date: FangT/2020.09.15
* Change: Modify the function name according to the AUTOSAR specification, add
*         MemMap.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date: FangT/2021.03.03
* Change: Add checksum and Multi pudid functions.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: FangT/2021.08.18
* Change: Modify the code specification.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: FangT/2021.10.29
* Change: Modify coding style.
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: ShiRong/2022.09.16
* Change: Add XcpOnCANFD function.
* Cause: Update
********************************************************************************
* Version: 3.6
* Author/Date: LinZhC/2024.01.10
* Change: Modified compatibility of multi-bus and multi-PDU configurations.
*         The following changes have been modify:
*         New Xcp_CanGetStatus, Xcp_CanCommandTimeCounter variable and
*         CanXcp_GetRxMsg function declaration.
* Cause: Update
*******************************************************************************
* Version: 3.7
* Author/Date: LinZhC/2024.04.01
* Change: Modify coding specification problems.
* Cause: Update
*******************************************************************************
* Version: 3.8
* Author/Date: KangJH/2024.05.22
* Change: Modify coding specification problems.
* Cause: Update
*******************************************************************************
* Version: 3.9
* Author/Date: KangJH/2024.06.20
* Change: 1.Modify coding specification problems.
*         2.Add Memmap segment definition.
* Cause: Update
********************************************************************************
* Version: 3.10
* Author/Date: KangJH/2024.10.13
* Change: Disable related functions when CanXcp is disabled.
* Cause: Bugfix
********************************************************************************
* Version: 3.11
* Author/Date: KangJH/2024.10.14
* Change: Move the header file Xcp.h reference to CanXcp.h.
* Cause: Bugfix
********************************************************************************
*/
#ifndef CANXCP_H_
#define CANXCP_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "CanIf.h"
#include "Xcp.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
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
#if( XCP_ONCAN_ENABLE == STD_ON )
#define XCP_START_SEC_VAR_INIT
#include "Xcp_MemMap.h"
extern VAR(uint8, XCP_VAR_INIT) Xcp_CanGetStatus;
#define XCP_STOP_SEC_VAR_INIT
#include "Xcp_MemMap.h"

/*
********************************************************************************
*    Global Functions
********************************************************************************
*/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
extern FUNC(void, XCP_CODE) Xcp_CanIfRxIndication
(
    PduIdType XcpRxPduId,
    P2CONST(PduInfoType, AUTOMATIC, XCP_APPL_CONST) XcpRxPduPtr
);
extern FUNC(uint8, XCP_CODE) CanXcp_GetRxMsg
(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA) avcpDlc,
    P2VAR(uint32, AUTOMATIC, XCP_APPL_DATA) avlpId,
    P2VAR(uint32, AUTOMATIC, XCP_APPL_DATA) avlpData
);
extern FUNC(void, XCP_CODE) Xcp_CanIfTxConfirmation(PduIdType XcpTxPduId);
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"
#endif  /* XCP_ONCAN_ENABLE == STD_ON */

#endif  /* CANXCP_H_ */
