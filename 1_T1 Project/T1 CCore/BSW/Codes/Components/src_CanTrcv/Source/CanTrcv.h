/*
********************************************************************************
*
*  File name:   CanTrcv.h
*
*  Copyright    Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : WangCong/2019.10.01
* Change: New
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date : WangCong/2020.03.25
* Change: Modify header file reference
* Cause: Clear QAC warning.
********************************************************************************
* Version: 3.2
* Author/Date : WangCong/2020.05.12
* Change: Modify the code specification.
* Cause: Optimize.
********************************************************************************
* Version: 3.3
* Author/Date : lizhiheng/2020.06.08
* Change: Add release software number.
* Cause: Update
********************************************************************************
* Version: 3.4
* Author/Date: WangC/2020.10.24
* Change: Modify the function name according to the AUTOSAR specification, add
*         MemMap.
* Cause: Optimize.
********************************************************************************
*/
#ifndef CANTRCV_H_
#define CANTRCV_H_

/*
*******************************************************************************
*    Includes
*******************************************************************************
*/
#include "CanTrcv_119_TJA1145.h"
#include "CanTrcv_Cfg.h"

/*
*******************************************************************************
*    Global Macros
*******************************************************************************
*/
#define CanTrcv_119_Init                              CanTrcv_119_TJA1145_Init
#define CanTrcv_119_SetOpMode                         CanTrcv_119_TJA1145_SetOpMode
#define CanTrcv_119_GetOpMode                         CanTrcv_119_TJA1145_GetOpMode
#define CanTrcv_119_GetBusWuReason                    CanTrcv_119_TJA1145_GetBusWuReason
#define CanTrcv_119_GetVersionInfo                    CanTrcv_119_TJA1145_GetVersionInfo
#define CanTrcv_119_SetWakeupMode                     CanTrcv_119_TJA1145_SetWakeupMode
#define CanTrcv_119_GetTrcvSystemData                 CanTrcv_119_TJA1145_GetTrcvSystemData
#define CanTrcv_119_ClearTrcvWufFlag                  CanTrcv_119_TJA1145_ClearTrcvWufFlag
#define CanTrcv_119_ReadTrcvTimeoutFlag               CanTrcv_119_TJA1145_ReadTrcvTimeoutFlag
#define CanTrcv_119_ClearTrcvTimeoutFlag              CanTrcv_119_TJA1145_ClearTrcvTimeoutFlag
#define CanTrcv_119_ReadTrcvSilenceFlag               CanTrcv_119_TJA1145_ReadTrcvSilenceFlag
#define CanTrcv_119_CheckWakeup                       CanTrcv_119_TJA1145_CheckWakeup
#define CanTrcv_119_SetPNActivationState              CanTrcv_119_TJA1145_SetPNActivationState
#define CanTrcv_119_CheckWakeFlag                     CanTrcv_119_TJA1145_CheckWakeFlag
#define CanTrcv_119_MainFunction                      CanTrcv_119_TJA1145_MainFunction
#define CanTrcv_119_MainFunctionDiagnostics           CanTrcv_119_TJA1145_MainFunctionDiagnostics

/*
*******************************************************************************
*    Global Types
*******************************************************************************
*/
/*
*******************************************************************************
*    Global variables
*******************************************************************************
*/
/*
*******************************************************************************
*    Global Constants
*******************************************************************************
*/
/*
*******************************************************************************
*    Global Functions
*******************************************************************************
*/
extern FUNC(void, CANTRCV_CODE) CanTrcv_Init
(
	P2CONST(CanTrcv_ConfigType, AUTOMATIC, CANTRCV_APPL_CONST) ConfigPtr
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetOpMode
(
	uint8 Transceiver,
 	CanTrcv_TrcvModeType OpMode
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_GetOpMode
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) OpMode
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_GetBusWuReason
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_APPL_DATA) reason
);
extern FUNC(void, CANTRCV_CODE) CanTrcv_GetVersionInfo
(
	P2VAR(Std_VersionInfoType, AUTOMATIC, CANTRCV_APPL_DATA) versioninfo
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetWakeupMode
(
	uint8 Transceiver,
	CanTrcv_TrcvWakeupModeType TrcvWakeupMode
);

#if (CANTRCV_HWPNSUPPORT_ENABLE == STD_ON)
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_GetTrcvSystemData
(
	uint8 Transceiver,
	P2CONST(uint32, AUTOMATIC, CANTRCV_APPL_CONST) TrcvSysData
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ClearTrcvWufFlag
(
	uint8 Transceiver
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ReadTrcvTimeoutFlag
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ClearTrcvTimeoutFlag
(
	uint8 Transceiver
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ReadTrcvSilenceFlag
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState
);
#endif	/* CANTRCV_119_TJA1145_HWPNSUPPORT_ENABLE == STD_ON */

#if (CANTRCV_ECUMWUEVENT_CFG == STD_ON)
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_CheckWakeup
(
	uint8 Transceiver
);
#endif	/* CANTRCV_ECUMWUEVENT_CFG == STD_ON */

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetPNActivationState
(
	CanTrcv_PNActivationType ActivationState
);

#if (CANTRCV_ECUMWUEVENT_CFG == STD_ON)
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_CheckWakeFlag
(
	uint8 Transceiver
);
#endif	/* CANTRCV_ECUMWUEVENT_CFG == STD_ON */

extern FUNC(void, CANTRCV_CODE) CanTrcv_MainFunction
(
	void
);

#if (CANTRCV_CANBUSERRFLAG_CFG == STD_ON)
extern FUNC(void, CANTRCV_CODE) CanTrcv_MainFunctionDiagnostics
(
	void
);
#endif	/* CANTRCV_CANBUSERRFLAG_CFG == STD_ON */

#endif /* CANTRCV_H_ */

