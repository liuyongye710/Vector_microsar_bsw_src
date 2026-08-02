/*
********************************************************************************
*
*  File name: PduR_Diag.h
*
*  Copyright 2019-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: SunHQ/2023.01.24
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: LuQ/2024.04.02
* Change: 1.Modify the comments format.
*         2. Modify P2CONST member labels.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date: LuQ/2024.05.13
* Change: Add Memmap segment definition.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: LuQ/2024.09.20
* Change: Modify copyright information.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: LuQ/2024.09.23
* Change: Modify the comments format.
* Cause: Optimization
********************************************************************************
*/
#ifndef PDUR_DIAG_H_
#define PDUR_DIAG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "PduR.h"

#if (STD_OFF == PDUR_ZERO_COST_OPERATION)

#if (STD_ON == PDUR_SUPPORT_DIAG)

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
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"
extern FUNC(void, PDUR_CODE) PduR_Diag_ReqFlgSet
(
    PduIdType pduId
);

extern FUNC(void, PDUR_CODE) PduR_Diag_Entry
(
    PduIdType pduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) dstPduPtr
);

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* #if (STD_ON == PDUR_SUPPORT_DIAG) */

#endif /* #if (STD_OFF == PDUR_ZERO_COST_OPERATION) */

#endif /* #define PDUR_DIAG_H_ */
