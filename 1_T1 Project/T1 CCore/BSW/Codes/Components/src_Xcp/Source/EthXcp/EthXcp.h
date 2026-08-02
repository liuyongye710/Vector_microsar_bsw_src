/*
********************************************************************************
*
* File name: EthXcp.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: FangT/2021.03.03
* Change: New created
* Cause: New
********************************************************************************
* Version: 3.0
* Author/Date: FangT/2021.05.08
* Change: Modify the EthXcp code specification according to AutoSar requirements.
* Cause: Updata
********************************************************************************
* Version: 3.1
* Author/Date: FangT/2021.08.18
* Change: Modify the code specification.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date: FangT/2021.10.29
* Change: Modify coding style.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: FangT/2021.11.1
* Change: Modify coding style.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: LinZhC/2024.01.10
* Change: 1.Modified compatibility of multi-bus and multi-PDU configurations.
*           The following changes have been modify:
*       (1) Synchronize count and status code and logic from XcpOnCan to XcpOnEth.
* Cause: Update
********************************************************************************
* Version: 3.5
* Author/Date: LinZhC/2024.03.13
* Change: Add macro XCP_ETH_FRAME_MIN_LEN.
* Cause: Update
********************************************************************************
* Version: 3.6
* Author/Date: LinZhC/2024.04.01
* Change: 1.Add Xcp_EthDaqTxConfirmEnable.
*         2.Modify coding specification problems.
* Cause: Update
********************************************************************************
* Version: 3.7
* Author/Date: KangJH/2024.05.22
* Change: Modify coding specification problems.
* Cause: Update
********************************************************************************
* Version: 3.8
* Author/Date: KangJH/2024.06.20
* Change: 1.Modify coding specification problems.
*         2.Add Memmap segment definition.
* Cause: Update
********************************************************************************
* Version: 3.9
* Author/Date: KangJH/2024.08.13
* Change: Modify copyright information.
* Cause: Update
********************************************************************************
* Version: 3.10
* Author/Date: KangJH/2024.10.13
* Change: Disable related functions when EthXcp is disabled.
* Cause: Bugfix
********************************************************************************
*/
#ifndef ETHXCP_H_
#define ETHXCP_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "ComStack_Types.h"
#include "Xcp.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#if( XCP_ONETHERNET_ENABLE == STD_ON )
#define XCP_ETH_FRAME_MIN_LEN     (8U)

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
#define XCP_START_SEC_VAR_INIT
#include "Xcp_MemMap.h"
extern VAR(uint8, XCP_VAR_INIT) Xcp_EthResData[XCP_ETHERNET_MAX_CTO + XCP_VALUE_4];
extern VAR(uint16, XCP_VAR_INIT) Xcp_EthCtrTx;
extern VAR(uint8, XCP_VAR_INIT) Xcp_EthGetStatus;
extern VAR(uint8, XCP_VAR_INIT) Xcp_EthDaqTxConfirmEnable;
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
extern FUNC(void, XCP_CODE) Xcp_SoAdIfRxIndication
(
    PduIdType XcpRxPduId,
    P2CONST(PduInfoType, AUTOMATIC, XCP_APPL_CONST)XcpRxPduPtr
);
extern FUNC(void, XCP_CODE) Xcp_SoAdIfTxConfirmation(PduIdType XcpTxPduId);
extern FUNC(uint8, XCP_CODE) EthXcp_GetRxMsg
(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_CONST) avcpDlc,
    P2VAR(uint32, AUTOMATIC, XCP_APPL_CONST) avlpId,
    P2VAR(uint32, AUTOMATIC, XCP_APPL_CONST) avlpData
);
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */

#endif  /* ETHXCP_H_ */
