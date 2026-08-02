/*
********************************************************************************
*
* File name: BswM_Sd.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: FangT/2021.03.08
* Change: New created
* Cause: New
********************************************************************************
* Version: 3.0
* Author/Date: FangT/2021.08.17
* Change: Modify the code specification.
* Cause: Optimization
********************************************************************************
* Version: 3.1
* Author/Date: FangT/2021.10.29
* Change: Modify coding style.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date: HeHao/2024.04.02
* Change: Modify comments and code style.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: LuQ/2024.08.28
* Change: Modify copyright.
* Cause: Optimization
********************************************************************************
*/
#ifndef BSWM_SD_H_
#define BSWM_SD_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Sd.h"

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
#define BSWM_START_SEC_CODE
#include "BswM_MemMap.h"
extern FUNC(void, BSWM_CODE) BswM_Sd_ClientServiceCurrentState
(
    uint16 SdClientServiceHandleId,
    Sd_ClientServiceCurrentStateType CurrentClientState
);
extern FUNC(void, BSWM_CODE) BswM_Sd_ConsumedEventGroupCurrentState(
	uint16 SdConsumedEventGroupHandleId,
    Sd_ConsumedEventGroupCurrentStateType ConsumedEventGroupState
);
extern FUNC(void, BSWM_CODE) BswM_Sd_EventHandlerCurrentState(
	uint16 SdEventHandlerHandleId,
    Sd_EventHandlerCurrentStateType EventHandlerStatus
);
#define BSWM_STOP_SEC_CODE
#include "BswM_MemMap.h"

#endif /* BSWM_SD_H_ */
