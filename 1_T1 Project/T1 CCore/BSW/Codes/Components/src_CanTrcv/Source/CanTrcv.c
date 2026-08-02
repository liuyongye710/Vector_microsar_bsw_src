/*
********************************************************************************
*
*  File name:	CanTrcv.c
*
*  Copyright	Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: WangCong/2019.10.01
* Change: New
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: WangCong/2020.03.25
* Change: Solve the problem:
*         More than one 'break' statement has been used to terminate this iteration statement.
* Cause: Clear QAC warning.
********************************************************************************
* Version: 3.2
* Author/Date: WangCong/2020.05.12
* Change: Modify the code specification.
* Cause: Optimize.
********************************************************************************
* Version: 3.3
* Author/Date: lizhiheng/2020.07.01
* Change: Modify the code specification.
* Cause: Optimize.
********************************************************************************
* Version: 3.4
* Author/Date: WangC/2020.10.24
* Change: Modify the function name according to the AUTOSAR specification, add
*         MemMap.
* Cause: Optimize.
********************************************************************************
*/
/*
********************************************************************************
*    Include
********************************************************************************
*/
#include "CanTrcv.h"

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
#define CANTRCV_START_SEC_CODE
#include "CanTrcv_MemMap.h"

/*
********************************************************************************
* Function Name: CanTrcv_Init
*
* Explanation: Initializes the CanTrcv module.
*              (Synchronous)
*
* param: ConfigPtr: Pointer to driver configuration.(Not Used)
*
* retval: None
********************************************************************************
*/
FUNC(void, CANTRCV_CODE) CanTrcv_Init
(
	P2CONST(CanTrcv_ConfigType, AUTOMATIC, CANTRCV_APPL_CONST) ConfigPtr
)
{
	CanTrcv_119_Init(ConfigPtr);
}

/*
********************************************************************************
* Function Name: CanTrcv_SetOpMode
*
* Explanation: Sets the mode of the Transceiver to the value OpMode.
*              (Asynchronous)
*
* param: Transceiver: CAN transceiver to which API call has to be applied.
*		 OpMode: This parameter contains the desired operating mode.
*
* retval: E_OK: will be returned if the request for transceiver mode change has been accepted.
*		  E_NOT_OK: will be returned if the request for transceiver mode change has not been
*		            accepted or any parameter is out of the allowed range.
********************************************************************************
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetOpMode
(
	uint8 Transceiver,
 	CanTrcv_TrcvModeType OpMode
)
{
    Std_ReturnType stdRet = E_NOT_OK;

	stdRet = CanTrcv_119_SetOpMode(Transceiver, OpMode);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_GetOpMode
*
* Explanation: Gets the mode of the Transceiver and returns it in OpMode.
*              (Synchronous)
*
* param: Transceiver: CAN transceiver to which API call has to be applied.
*		 OpMode: Pointer to operation mode of the bus the API is applied to.
*
* retval: E_OK: will be returned if the operation mode was detected.
*		  E_NOT_OK: will be returned if the operation mode was not detected.
********************************************************************************
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_GetOpMode
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) OpMode
)
{
    Std_ReturnType stdRet = E_NOT_OK;

	stdRet = CanTrcv_119_GetOpMode(Transceiver, OpMode);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_GetBusWuReason
*
* Explanation: Gets the wakeup reason for the Transceiver and returns it in parameter Reason.
*              (Synchronous)
*
* param: Transceiver: CAN transceiver to which API call has to be applied.
*		 reason: Pointer to wake up reason of the bus the API is applied to.
*
* retval: E_OK: will be returned if the transceiver wakeup reason was provided.
*         E_NOT_OK: will be returned if no wake up reason is available or if the service request failed
*					due to development errors.
********************************************************************************
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_GetBusWuReason
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_APPL_DATA) reason
)
{
    Std_ReturnType stdRet = E_NOT_OK;

	stdRet = CanTrcv_119_GetBusWuReason(Transceiver, reason);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_GetVersionInfo
*
* Explanation: Gets the version of the module and returns it in VersionInfo.
*              (Synchronous)
*
* param: versioninfo: Pointer to version information of this module.
*
* retval: None
********************************************************************************
*/
FUNC(void, CANTRCV_CODE) CanTrcv_GetVersionInfo
(
	P2VAR(Std_VersionInfoType, AUTOMATIC, CANTRCV_APPL_DATA) versioninfo
)
{
	CanTrcv_119_GetVersionInfo(versioninfo);
}

/*
********************************************************************************
* Function Name: CanTrcv_SetWakeupMode
*
* Explanation: Enables, disables or clears wake-up events of the Transceiver according to TrcvWakeupMode.
*              (Synchronous)
*
* param: Transceiver: CAN transceiver to which API call has to be applied.
*		 TrcvWakeupMode: Requested transceiver wakeup reason.
*
* retval: E_OK: Will be returned, if the wakeup state has been changed to the requested mode.
*		  E_NOT_OK: Will be returned, if the wakeup state change has failed or the parameter
*					is out of the allowed range. The previous state has not been changed.
********************************************************************************
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetWakeupMode
(
	uint8 Transceiver,
	CanTrcv_TrcvWakeupModeType TrcvWakeupMode
)
{
    Std_ReturnType stdRet = E_NOT_OK;

	stdRet = CanTrcv_119_SetWakeupMode(Transceiver, TrcvWakeupMode);

	return stdRet;
}

#if (CANTRCV_HWPNSUPPORT_ENABLE == STD_ON)
/*
********************************************************************************
* Function Name: CanTrcv_GetTrcvSystemData
*
* Explanation: Reads the transceiver configuration/status data and returns it through parameterTrcvSysData.
*			   This API shall exist only if CanTrcvHwPnSupport = TRUE.
*              (Synchronous)
*
* param: Transceiver: CAN transceiver ID.
*		 TrcvSysData: Configuration/Status data of the transceiver.
*
* retval: E_OK: will be returned if the transceiver status is successfully read.
*		  E_NOT_OK: will be returned if the transceiver status data is not available or a development error occurs.
********************************************************************************
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_GetTrcvSystemData
(
	uint8 Transceiver,
	P2CONST(uint32, AUTOMATIC, CANTRCV_APPL_CONST) TrcvSysData
)
{
    Std_ReturnType stdRet = E_NOT_OK;

	stdRet = CanTrcv_119_GetTrcvSystemData(Transceiver, TrcvSysData);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_ClearTrcvWufFlag
*
* Explanation: Clears the WUF flag in the transceiver hardware.
*			   This API shall exist only if CanTrcvHwPnSupport = TRUE.
*              (Synchronous)
*
* param: Transceiver: CAN transceiver ID.
*
* retval: E_OK: will be returned if the WUF flag has been cleared.
*		  E_NOT_OK: will be returned if the WUF flag has not been cleared or a development error occurs.
********************************************************************************
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ClearTrcvWufFlag
(
	uint8 Transceiver
)
{

    Std_ReturnType stdRet = E_NOT_OK;

	stdRet = CanTrcv_119_ClearTrcvWufFlag(Transceiver);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_ReadTrcvTimeoutFlag
*
* Explanation: Reads the status of the timeout flag from the transceiver hardware.
*			   This API shall exist only if CanTrcvHwPnSupport = TRUE.
*              (Synchronous)
*
* param: Transceiver: CAN transceiver ID.
*		 FlagState: State of the timeout flag.
*
* retval: E_OK: Will be returned, if status of the timeout flag is successfully read.
*		  E_NOT_OK: Will be returned, if status of the timeout flag could not be read.
********************************************************************************
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ReadTrcvTimeoutFlag
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState
)
{
    Std_ReturnType stdRet = E_NOT_OK;

	stdRet = CanTrcv_119_ReadTrcvTimeoutFlag(Transceiver, FlagState);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_ClearTrcvTimeoutFlag
*
* Explanation: Clears the status of the timeout flag in the transceiver hardware.
*			   This API shall exist only if CanTrcvHwPnSupport = TRUE.
*              (Synchronous)
*
* param: Transceiver: CAN transceiver ID.
*		 FlagState: State of the silence flag.
*
* retval: E_OK: Will be returned, if the timeout flag is successfully cleared.
*		  E_NOT_OK: Will be returned, if the timeout flag could not be cleared.
********************************************************************************
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ClearTrcvTimeoutFlag
(
	uint8 Transceiver
)
{
    Std_ReturnType stdRet = E_NOT_OK;

	stdRet = CanTrcv_119_ClearTrcvTimeoutFlag(Transceiver);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_ReadTrcvSilenceFlag
*
* Explanation: Reads the status of the silence flag from the transceiver hardware.
*			   This API shall exist only if CanTrcvHwPnSupport = TRUE.
*              (Synchronous)
*
* param: Transceiver: CAN transceiver ID.
*		 FlagState: State of the silence flag.
*
* retval: E_OK: Will be returned, if status of the silence flag is successfully read.
*		  E_NOT_OK: Will be returned, if status of the silence flag could not be read.
********************************************************************************
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ReadTrcvSilenceFlag
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState
)
{
    Std_ReturnType stdRet = E_NOT_OK;

	stdRet = CanTrcv_119_ReadTrcvSilenceFlag(Transceiver, FlagState);

	return stdRet;
}
#endif	/* CANTRCV_119_TJA1145_HWPNSUPPORT_ENABLE == STD_ON */

#if (CANTRCV_ECUMWUEVENT_CFG == STD_ON)
/*
********************************************************************************
* Function Name: CanTrcv_CheckWakeup
*
* Explanation: Service is called by underlying CANIF in case a wake up interrupt is detected.
*              (Synchronous)
*
* param: Transceiver: CAN transceiver to which API call has to be applied.
*
* retval: E_OK: API call has been accepted.
*		  E_NOT_OK: API call has not been accepted.
********************************************************************************
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_CheckWakeup
(
	uint8 Transceiver
)
{
    Std_ReturnType stdRet = E_NOT_OK;

	stdRet = CanTrcv_119_CheckWakeup(Transceiver);

	return stdRet;
}
#endif	/* CANTRCV_ECUMWUEVENT_CFG == STD_ON */

/*
********************************************************************************
* Function Name: CanTrcv_SetPNActivationState
*
* Explanation: The API configures the wake-up of the transceiver for Standby and Sleep Mode:
*			   Either the CAN transceiver is woken up by a remote wake-up pattern (standard
*              CAN wake-up) or by the configured remote wake-up frame.
*              (Synchronous)
*
* param: ActivationState: PN_ENABLED: PN wakeup functionality in CanTrcv shall be enabled.
*						  PN_DIABLED: PN wakeup functionality in CanTrcv shall be disabled.
*
* retval: E_OK: Will be returned, if the PN has been changed to the requested configuration.
*		  E_NOT_OK: Will be returned, if the PN configuration change has failed. The previous configuration has not been changed.
********************************************************************************
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetPNActivationState
(
	CanTrcv_PNActivationType ActivationState
)
{
    Std_ReturnType stdRet = E_NOT_OK;

	stdRet = CanTrcv_119_SetPNActivationState(ActivationState);

	return stdRet;
}

#if (CANTRCV_ECUMWUEVENT_CFG == STD_ON)
/*
********************************************************************************
* Function Name: CanTrcv_CheckWakeFlag
*
* Explanation: Requests to check the status of the wakeup flag from the transceiver hardware.
*              (Synchronous)
*
* param: Transceiver: CAN transceiver ID.
*
* retval: E_OK: Will be returned, if the request for checking the wakeup flag has been accepted.
*		  E_NOT_OK: Will be returned, if the request for checking the wakeup flag has not been accepted.
********************************************************************************
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_CheckWakeFlag
(
	uint8 Transceiver
)
{
    Std_ReturnType stdRet = E_NOT_OK;

	stdRet = CanTrcv_119_CheckWakeFlag(Transceiver);

	return stdRet;
}
#endif	/* CANTRCV_ECUMWUEVENT_CFG == STD_ON */

/*
********************************************************************************
* Function Name: CanTrcv_MainFunction
*
* Explanation: Service to scan all busses for wake up events and perform these event.
*
* param: None.
*
* retval: None.
********************************************************************************
*/
FUNC(void, CANTRCV_CODE) CanTrcv_MainFunction
(
	void
)
{
	CanTrcv_119_MainFunction();
}

#if (CANTRCV_CANBUSERRFLAG_CFG == STD_ON)
/*
********************************************************************************
* Function Name: CanTrcv_MainFunctionDiagnostics
*
* Explanation: Reads the transceiver diagnostic status periodically and sets product/development accordingly.
*
* param: None.
*
* retval: None.
********************************************************************************
*/
FUNC(void, CANTRCV_CODE) CanTrcv_MainFunctionDiagnostics
(
	void
)
{
	CanTrcv_119_MainFunctionDiagnostics();
}

#endif	/* CANTRCV_CANBUSERRFLAG_CFG == STD_ON */

#define CANTRCV_STOP_SEC_CODE
#include "CanTrcv_MemMap.h"
