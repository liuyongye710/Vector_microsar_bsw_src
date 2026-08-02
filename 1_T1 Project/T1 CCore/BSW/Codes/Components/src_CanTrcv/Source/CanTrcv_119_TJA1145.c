/*
********************************************************************************
*
*  File name:	CanTrcv_119_TJA1145.c
*
*  Copyright	Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: WangCong/2020.05.29
* Change: New
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: WangC/2020.10.24
* Change: Modify the function name according to the AUTOSAR specification, add
*         MemMap.
* Cause: Optimize.
********************************************************************************
* Version: 3.2
* Author/Date: WangC/2020.10.26
* Change: Modify the code according to QAC.
* Cause: Clear QAC warning.
********************************************************************************
* Version: 3.3
* Author/Date: ZhangDX/2020.11.04
* Change: Modify the wrong part of the segment definition.
* Cause: Update.
********************************************************************************
* Version: 3.4
* Author/Date: ZhangDX/2020.11.04
* Change: Modify the wrong part of the segment definition.
* Cause: Update.
********************************************************************************
* Version: 3.5
* Author/Date: WangJP/2021.03.18
* Change: Fix can transceiver data register assignment error in function
*         CanTrcv_119_TJA1145_CanWakeUp_DataMask.
* Cause: Bugfix.
********************************************************************************
* Version: 3.6
* Author/Date: HuangF/2021.09.16
* Change: Clear the Compiler warnings.
* Cause: Optimize.
********************************************************************************
* Version: 3.7
* Author/Date: HuangF/2023.02.23
* Change: 1.Modify CanTrcv mode check logic in the function 
*           CanTrcv_119_TJA1145_SetOpMode.
*         2.Clear PolySpace low level errors.
*         3.Clear the Compiler warnings.
* Cause: Bugfix.
********************************************************************************
* Version: 3.8
* Author/Date: HuangF/2023.03.21
* Change: 1.Fix can transceiver PN configuration logic in function 
*           CanTrcv_119_TJA1145_InitOneChn_Memory.
*         2.Remove can transceiver repeat judgmengt logic in function
*           CanTrcv_119_TJA1145_ToSleep.
* Cause: Bugfix.
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "CanTrcv_119_TJA1145.h"
#include "CanIf_Cbk.h"

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
#define CANTRCV_START_SEC_VAR_INIT
#include "CanTrcv_MemMap.h"

static VAR(boolean, CANTRCV_VAR_INIT) CanTrcv_119_TJA1145_InitFlag = FALSE;

#define CANTRCV_STOP_SEC_VAR_INIT
#include "CanTrcv_MemMap.h"

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
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_WriteOneReg
(
	P2CONST(CanTrcv_SpiAccessType, AUTOMATIC, CANTRCV_APPL_CONST) SpiAccessPtr,
 	uint8 addr,
 	uint8 data
);
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ReadOneReg
(
	P2CONST(CanTrcv_SpiAccessType, AUTOMATIC, CANTRCV_APPL_CONST) SpiAccessPtr,
 	uint8 addr,
 	P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) dataPtr
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_WriteOneReg_SpiRetry
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
 	uint8 addr,
 	uint8 data
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_ReadOneReg_SpiRetry
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
 	uint8 addr,
 	P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) dataPtr
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_MFunc_SetOpMode
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_GetOpMode_Process
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
	P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) OpMode
);
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ToNormal
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ToSleep
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ToStandBy
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_CANStandardWakeUp
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_CANPNWakeUp
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_CanWakeUp_ID
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
 	uint32 id,
 	boolean ide
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_CanWakeUp_IDMask
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
 	uint32 idMask,
	boolean ide
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_CanWakeUp_DataMask
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
 	P2CONST(uint8, AUTOMATIC, CANTRCV_APPL_CONST) data
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_CanWakeUp_FrameControl
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
 	boolean ide,
	boolean dataMask,
	uint8 dlc
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_Det_ErrorReport
(
	uint8 apiId,
 	uint8 errorId
);
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_InitOneChn
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_InitOneChn_Memory
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_CheckCanWakeUp
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_ClearStatusReg
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ChkAndClrSpiComTO
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ChkCanBusSilence
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
 	P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_ChkCanBusErr
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_Init_SetOpMode
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_ChkPor
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ChkBaudRate
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
);

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
* Function Name: CanTrcv_119_TJA1145_Init
*
* Explanation: Initializes the CanTrcv module.
*              (Synchronous)
*
* param: ConfigPtr: Pointer to driver configuration.(Not Used)
*
* retval: None
********************************************************************************
*/
FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_Init
(
	P2CONST(CanTrcv_ConfigType, AUTOMATIC, CANTRCV_APPL_CONST) ConfigPtr
)
{
	uint8 errorId = CANTRCV_E_NO_ERR;
    Std_ReturnType stdRet;
	uint8 chnIndex;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

    CANTRCV_DUMMY_STATEMENT(ConfigPtr);
	/* Init all CanTrcv channel. */
	for( chnIndex = CANTRCV_VALUE_ZERO; chnIndex < CANTRCV_119_TJA1145_CHN_ALL_NUM; chnIndex++ )
	{
		if( NULL_PTR != chnPtr[chnIndex].PnNetworkPtr )
		{
			stdRet = CanTrcv_119_TJA1145_InitOneChn(&chnPtr[chnIndex]);
			if( E_OK != stdRet )
			{
				/* There is no/incorrect communication. */
				errorId = CANTRCV_E_NO_TRCV_CONTROL;
			}
			else
			{
				stdRet = CanTrcv_119_TJA1145_Init_SetOpMode(&chnPtr[chnIndex]);
				if( E_OK != stdRet )
				{
					/* There is no/incorrect communication. */
					errorId = CANTRCV_E_NO_TRCV_CONTROL;
				}
				else
				{
					stdRet = CanTrcv_119_TJA1145_ChkBaudRate(&chnPtr[chnIndex]);
					if( E_OK != stdRet )
					{
						/* The configured baud rate is not supported by the transceiver. */
						errorId = CANTRCV_E_BAUDRATE_NOT_SUPPORTED;
					}
					else
					{
						/* Set initialization flag. */
						CanTrcv_119_TJA1145_InitFlag = TRUE;
					}
				}
			}
		}
		else
		{
			/* Init failed. */
			/* initFailed */
			break;
		}
	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_INIT,errorId);
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_SetOpMode
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
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_SetOpMode
(
	uint8 Transceiver,
 	CanTrcv_TrcvModeType OpMode
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
    Std_ReturnType stdRet = E_NOT_OK;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else if( CANTRCV_119_TJA1145_CHN_ALL_NUM <= Transceiver )
    {
		errorId = CANTRCV_E_INVALID_TRANSCEIVER;
	}
	else if( (CANTRCV_TRCVMODE_NORMAL != OpMode) && (CANTRCV_TRCVMODE_STANDBY != OpMode) &&
		     (CANTRCV_TRCVMODE_SLEEP != OpMode) )
	{
		errorId = CANTRCV_E_PARAM_TRCV_OPMODE;
	}
	else
	{
		/* Set the request of mode swicth. */
		if( chnPtr[Transceiver].chnVarPtr->currMode != OpMode )
		{
			chnPtr[Transceiver].chnVarPtr->reqMode = OpMode;
		}
		stdRet = E_OK;

#if (CANTRCV_119_TJA1145_ICUCHN_CFG == STD_ON)
		if( CANTRCV_TRCVMODE_STANDBY == OpMode )
		{
			Icu_EnableNotification(chnPtr[Transceiver].icuChnId);
		}
		else if( CANTRCV_TRCVMODE_NORMAL == OpMode )
		{
			Icu_DisableNotification(chnPtr[Transceiver].icuChnId);
		}
		else
		{
			/* Do nothing. */
		}
#endif	/* CANTRCV_119_TJA1145_ICUCHN_CFG == STD_ON */

#if (CANTRCV_119_TJA1145_HWPNSUPPORT_ENABLE == STD_ON)
		if( CANTRCV_TRCVMODE_NORMAL == OpMode )
		{
			CanIf_ConfirmPnAvailability(Transceiver);
		}
#endif	/* CANTRCV_119_TJA1145_HWPNSUPPORT_ENABLE == STD_ON */

	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_SETOPMODE, errorId);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_GetOpMode
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
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_GetOpMode
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) OpMode
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
    Std_ReturnType stdRet = E_NOT_OK;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else if( CANTRCV_119_TJA1145_CHN_ALL_NUM <= Transceiver )
    {
		errorId = CANTRCV_E_INVALID_TRANSCEIVER;
	}
	else if( NULL_PTR == OpMode )
	{
		errorId = CANTRCV_E_PARAM_POINTER;
	}
	else
	{
		stdRet = CanTrcv_119_TJA1145_GetOpMode_Process(&chnPtr[Transceiver],OpMode);
		if( E_OK != stdRet )
		{
			/* There is no/incorrect communication to the transceiver. */
			errorId = CANTRCV_E_NO_TRCV_CONTROL;
		}
	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_GETOPMODE, errorId);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_GetBusWuReason
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
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_GetBusWuReason
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_APPL_DATA) reason
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
    Std_ReturnType stdRet = E_NOT_OK;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else if( CANTRCV_119_TJA1145_CHN_ALL_NUM <= Transceiver )
    {
		errorId = CANTRCV_E_INVALID_TRANSCEIVER;
	}
	else if( NULL_PTR == reason )
	{
		errorId = CANTRCV_E_PARAM_POINTER;
	}
	else
	{
		/* Set the wake up reason. */
		*reason = chnPtr[Transceiver].chnVarPtr->wuReason;
	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_GETBUSWUREASON, errorId);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_GetVersionInfo
*
* Explanation: Gets the version of the module and returns it in VersionInfo.
*              (Synchronous)
*
* param: versioninfo: Pointer to version information of this module.
*
* retval: None
********************************************************************************
*/
FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_GetVersionInfo
(
	P2VAR(Std_VersionInfoType, AUTOMATIC, CANTRCV_APPL_DATA) versioninfo
)
{
	uint8 errorId = CANTRCV_E_NO_ERR;

	/* Checking for development errors. */
	if( NULL_PTR == versioninfo )
	{
		errorId = CANTRCV_E_PARAM_POINTER;
	}
	else
	{
        versioninfo->vendorID = CANTRCV_119_TJA1145_VENDOR_ID;
        versioninfo->moduleID = CANTRCV_119_TJA1145_MODULE_ID;
        versioninfo->sw_major_version = CANTRCV_119_TJA1145_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = CANTRCV_119_TJA1145_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = CANTRCV_119_TJA1145_SW_PATCH_VERSION;
	}

	CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_GETVERSIONINFO, errorId);
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_SetWakeupMode
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
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_SetWakeupMode
(
	uint8 Transceiver,
	CanTrcv_TrcvWakeupModeType TrcvWakeupMode
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
    Std_ReturnType stdRet = E_NOT_OK;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else if( CANTRCV_119_TJA1145_CHN_ALL_NUM <= Transceiver )
    {
		errorId = CANTRCV_E_INVALID_TRANSCEIVER;
	}
	else if( CANTRCV_WUMODE_DISABLE < TrcvWakeupMode )
	{
		errorId = CANTRCV_E_PARAM_TRCV_WAKEUP_MODE;
	}
	else
	{
		/* Set wake up mode. */
		chnPtr[Transceiver].chnVarPtr->wuMode = TrcvWakeupMode;
	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_SETWAKEUPMODE, errorId);

	return stdRet;
}

#if (CANTRCV_119_TJA1145_HWPNSUPPORT_ENABLE == STD_ON)
/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_GetTrcvSystemData
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
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_GetTrcvSystemData
(
	uint8 Transceiver,
	P2CONST(uint32, AUTOMATIC, CANTRCV_APPL_CONST) TrcvSysData
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
    Std_ReturnType stdRet = E_NOT_OK;
	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else if( CANTRCV_119_TJA1145_CHN_ALL_NUM <= Transceiver )
    {
		errorId = CANTRCV_E_INVALID_TRANSCEIVER;
	}
	else if( NULL_PTR == TrcvSysData )
	{
		errorId = CANTRCV_E_PARAM_POINTER;
	}
	else
	{

	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_GETTRCVSYSTEMDATA, errorId);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ClearTrcvWufFlag
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
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ClearTrcvWufFlag
(
	uint8 Transceiver
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
    Std_ReturnType stdRet = E_NOT_OK;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else if( CANTRCV_119_TJA1145_CHN_ALL_NUM <= Transceiver )
    {
		errorId = CANTRCV_E_INVALID_TRANSCEIVER;
	}
	else
	{
		/* Clear the wake up falg. */
		chnPtr[Transceiver].chnVarPtr->wuReason = CANTRCV_WU_ERROR;
	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_CLEARTRCVWUFLAG, errorId);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ReadTrcvTimeoutFlag
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
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ReadTrcvTimeoutFlag
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
    Std_ReturnType stdRet = E_NOT_OK;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else if( CANTRCV_119_TJA1145_CHN_ALL_NUM <= Transceiver )
    {
		errorId = CANTRCV_E_INVALID_TRANSCEIVER;
	}
	else if( NULL_PTR == FlagState )
	{
		errorId = CANTRCV_E_PARAM_POINTER;
	}
	else
	{
		/* Check transceiver timeout flag. */
		if( FALSE == chnPtr[Transceiver].chnVarPtr->spiCommTimeoutFlag )
		{
			*FlagState = CANTRCV_FLAG_CLEARED;
		}
		else
		{
			*FlagState = CANTRCV_FLAG_SET;
		}
		stdRet = E_OK;
	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_READTRCVTIMEOUTFLAG, errorId);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ClearTrcvTimeoutFlag
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
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ClearTrcvTimeoutFlag
(
	uint8 Transceiver
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
    Std_ReturnType stdRet = E_NOT_OK;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else if( CANTRCV_119_TJA1145_CHN_ALL_NUM <= Transceiver )
    {
		errorId = CANTRCV_E_INVALID_TRANSCEIVER;
	}
	else
	{
		/* Clear transceiver timeout flag. */
		chnPtr[Transceiver].chnVarPtr->spiCommTimeoutFlag = FALSE;
		stdRet = E_OK;
	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_CLEARTIMEOUTFLAG, errorId);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ReadTrcvSilenceFlag
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
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ReadTrcvSilenceFlag
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
    Std_ReturnType stdRet = E_NOT_OK;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else if( CANTRCV_119_TJA1145_CHN_ALL_NUM <= Transceiver )
    {
		errorId = CANTRCV_E_INVALID_TRANSCEIVER;
	}
	else if( NULL_PTR == FlagState )
	{
		errorId = CANTRCV_E_PARAM_POINTER;
	}
	else
	{
		stdRet = CanTrcv_119_TJA1145_ChkCanBusSilence(&chnPtr[Transceiver],FlagState);
	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_READTRCVSILENCEFLAG, errorId);

	return stdRet;
}
#endif	/* CANTRCV_119_TJA1145_HWPNSUPPORT_ENABLE == STD_ON */

#if (CANTRCV_119_TJA1145_ECUMWUEVENT_CFG == STD_ON)
/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_CheckWakeup
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
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_CheckWakeup
(
	uint8 Transceiver
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
    Std_ReturnType stdRet = E_NOT_OK;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else if( CANTRCV_119_TJA1145_CHN_ALL_NUM <= Transceiver )
    {
		errorId = CANTRCV_E_INVALID_TRANSCEIVER;
	}
	else
	{
		if( CANTRCV_WU_ERROR != chnPtr[Transceiver].chnVarPtr->wuReason )
		{
			/* Set wake up event to EcuM. */
			EcuM_SetWakeupEvent((EcuM_WakeupSourceType)CANTRCV_VALUE_ONE << chnPtr[Transceiver].ecumWakeupSrcId);
		}
	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_CHECKWAKEUP, errorId);

	return stdRet;
}
#endif	/* CANTRCV_119_TJA1145_ECUMWUEVENT_CFG == STD_ON */

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_SetPNActivationState
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
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_SetPNActivationState
(
	CanTrcv_PNActivationType ActivationState
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
    Std_ReturnType stdRet = E_NOT_OK;
	uint8 chnIndex;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else
	{
		/* Set the PN avtivation flag to all channel. */
		for( chnIndex = CANTRCV_VALUE_ZERO; chnIndex < CANTRCV_119_TJA1145_CHN_ALL_NUM; chnIndex++ )
		{
			if( NULL_PTR != chnPtr[chnIndex].PnNetworkPtr )
			{
				chnPtr[chnIndex].chnVarPtr->pnAct = ActivationState;
			}
		}
		stdRet = E_OK;
	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_SETPNACTIVATIONSTATE, errorId);

	return stdRet;
}

#if (CANTRCV_119_TJA1145_ECUMWUEVENT_CFG == STD_ON)
/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_CheckWakeFlag
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
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_CheckWakeFlag
(
	uint8 Transceiver
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
    Std_ReturnType stdRet = E_NOT_OK;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else if( CANTRCV_119_TJA1145_CHN_ALL_NUM <= Transceiver )
    {
		errorId = CANTRCV_E_INVALID_TRANSCEIVER;
	}
	else
	{
		/* Check CAN wake up status flag. */
		stdRet = CanTrcv_119_TJA1145_CheckCanWakeUp(&chnPtr[Transceiver]);
		if( E_OK == stdRet )
		{
			/* Indicates that the check of the transceiver's wake-up flag has been finished. */
			CanIf_CheckTrcvWakeFlagIndication(Transceiver);
		}
	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_CHECKWAKEUPFLAG, errorId);

	return stdRet;
}
#endif	/* CANTRCV_119_TJA1145_ECUMWUEVENT_CFG == STD_ON */

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_MainFunction
*
* Explanation: Service to scan all busses for wake up events and perform these event.
*
* param: None.
*
* retval: None.
********************************************************************************
*/
FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_MainFunction
(
	void
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
	uint8 chnIndex;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else
	{
		/* Check CAN bus error flag for all channel. */
		for( chnIndex = CANTRCV_VALUE_ZERO; chnIndex < CANTRCV_119_TJA1145_CHN_ALL_NUM; chnIndex++ )
		{
			/* Processing mode switch. */
			CanTrcv_119_TJA1145_MFunc_SetOpMode(&chnPtr[chnIndex]);
		}
	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_MAINFUNCTION, errorId);
}

#if (CANTRCV_119_TJA1145_CANBUSERRFLAG_CFG == STD_ON)
/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_MainFunctionDiagnostics
*
* Explanation: Reads the transceiver diagnostic status periodically and sets product/development accordingly.
*
* param: None.
*
* retval: None.
********************************************************************************
*/
FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_MainFunctionDiagnostics
(
	void
)
{
    uint8 errorId = CANTRCV_E_NO_ERR;
	uint8 chnIndex;
	const CanTrcv_ChannelType* chnPtr = CanTrcv_119_TJA1145_ChannelInfo;

	/* Checking for development errors. */
	if( TRUE != CanTrcv_119_TJA1145_InitFlag )
    {
		errorId = CANTRCV_E_UNINIT;
	}
	else
	{
		/* Check CAN bus error flag for all channel. */
		for( chnIndex = CANTRCV_VALUE_ZERO; chnIndex < CANTRCV_119_TJA1145_CHN_ALL_NUM; chnIndex++ )
		{
			CanTrcv_119_TJA1145_ChkCanBusErr(&chnPtr[chnIndex]);
		}
	}

    CanTrcv_119_TJA1145_Det_ErrorReport(CANTRCV_SERVICEID_MAINFUNCTIONDIAGNOSTICS, errorId);
}
#endif	/* CANTRCV_119_TJA1145_CANBUSERRFLAG_CFG == STD_ON */
/*
********************************************************************************
* Function Name: CanTrcv_Tja1145_WriteOneReg
*
* Explanation: Tja1145 Chip Write One Register.
*              (Synchronous)
*
* param: SpiAccessPtr: Pointer to Spi Configuration parameters for CanTrcv.
*        addr: Address for register.
*        data: The data to be written.
*
* retval: E_OK: Write register successfully.
*		  E_NOT_OK: Write register not successfully.
********************************************************************************
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_WriteOneReg
(
	P2CONST(CanTrcv_SpiAccessType, AUTOMATIC, CANTRCV_APPL_CONST) SpiAccessPtr,
 	uint8 addr,
 	uint8 data
)
{
    Std_ReturnType stdRet;
    uint8 sendBuf[CANTRCV_VALUE_TWO] = {CANTRCV_VALUE_ZERO};
    uint8 sendBufRxBuf[CANTRCV_VALUE_TWO] = {CANTRCV_VALUE_ZERO};

    /* Process the sending data. */
    sendBuf[CANTRCV_VALUE_ZERO] = (addr << CANTRCV_VALUE_ONE);
    sendBuf[CANTRCV_VALUE_ONE] = data;
    /* Set Spi EB buffer. */
    stdRet = Spi_SetupEB(SpiAccessPtr->SpiChannelId, &sendBuf[CANTRCV_VALUE_ZERO],
        &sendBufRxBuf[CANTRCV_VALUE_ZERO], CANTRCV_VALUE_TWO);
    if( E_OK == stdRet )
    {
        /* Initiate Spi synchronous transmission. */
        stdRet = Spi_SyncTransmit(SpiAccessPtr->SpiSequenceId);
    }

    /* Test the Spi Rx data */
    /* sendBuf[CANTRCV_VALUE_ZERO] = CANTRCV_VALUE_ONE; */

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ReadOneReg
*
* Explanation: Tja1145 Chip Read One Register.
*              (Synchronous)
*
* param: SpiAccessPtr: Pointer to Spi Configuration parameters for CanTrcv.
*        addr: Address for register.
*        dataPtr: Pointer to data buffer.
*
* retval: E_OK: Read register successfully.
*		  E_NOT_OK: Read register not successfully.
********************************************************************************
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ReadOneReg
(
	P2CONST(CanTrcv_SpiAccessType, AUTOMATIC, CANTRCV_APPL_CONST) SpiAccessPtr,
 	uint8 addr,
 	P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) dataPtr
)
{
    Std_ReturnType stdRet;
    uint8 sendBuf[CANTRCV_VALUE_TWO] = {CANTRCV_VALUE_ZERO};
    uint8 sendBufRxBuf[CANTRCV_VALUE_TWO] = {CANTRCV_VALUE_ZERO};

    /* Process the sending data. */
    sendBuf[CANTRCV_VALUE_ZERO] = (uint8)(((uint32)addr << CANTRCV_VALUE_ONE) | CANTRCV_VALUE_ONE);
    sendBuf[CANTRCV_VALUE_ONE] = CANTRCV_VALUE_ZERO;
    /* Set Spi EB buffer. */
    stdRet = Spi_SetupEB(SpiAccessPtr->SpiChannelId, &sendBuf[CANTRCV_VALUE_ZERO],
        &sendBufRxBuf[CANTRCV_VALUE_ZERO], CANTRCV_VALUE_TWO);
    if( E_OK == stdRet )
    {
        /* Initiate Spi synchronous transmission. */
        stdRet = Spi_SyncTransmit(SpiAccessPtr->SpiSequenceId);
        if( E_OK == stdRet )
        {
            /* Data assignment. */
            dataPtr[CANTRCV_VALUE_ZERO] = sendBufRxBuf[CANTRCV_VALUE_ONE];
        }
    }

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_WriteOneReg_SpiRetry
*
* Explanation: Tja1145 Chip Write One Register with retries.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv Channel.
*        addr: Address for register.
*        data: The data to be written.
*
* retval: E_OK: Write register successfully.
*		  E_NOT_OK: Write register not successfully.
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_WriteOneReg_SpiRetry
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
 	uint8 addr,
 	uint8 data
)
{
    Std_ReturnType stdRet;

/* Enable Spi communication retry */
#if (CANTRCV_119_TJA1145_SPICOMM_RETRIES != CANTRCV_VALUE_ZERO)
	uint8 retryCnt = CANTRCV_VALUE_ZERO;

	for( retryCnt = CANTRCV_VALUE_ZERO; retryCnt < CANTRCV_119_TJA1145_SPICOMM_RETRIES; retryCnt++ )
	{
		stdRet = CanTrcv_119_TJA1145_WriteOneReg(chnPtr->SpiAccessPtr,addr,data);
		if( E_OK == stdRet )
		{
			break;
		}
	}
	if( retryCnt >= CANTRCV_119_TJA1145_SPICOMM_RETRIES )
	{
		/* Spi communication timeout. */
		chnPtr->chnVarPtr->spiCommTimeoutFlag = TRUE;
	}
#else	/* CANTRCV_119_TJA1145_SPICOMM_RETRIES != CANTRCV_VALUE_ZERO */
	stdRet = CanTrcv_119_TJA1145_WriteOneReg(chnPtr->SpiAccessPtr,addr,data);
	if( E_OK != stdRet )
	{
		/* Spi communication timeout. */
		chnPtr->chnVarPtr->spiCommTimeoutFlag = TRUE;
	}
#endif	/* CANTRCV_119_TJA1145_SPICOMM_RETRIES != CANTRCV_VALUE_ZERO */

}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ReadOneReg_SpiRetry
*
* Explanation: Tja1145 Chip Write One Register with retries.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv Channel.
*        addr: Address for register.
*        dataPtr: Pointer to data buffer.
*
* retval: E_OK: Write register successfully.
*		  E_NOT_OK: Write register not successfully.
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_ReadOneReg_SpiRetry
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
 	uint8 addr,
 	P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) dataPtr
)
{
    Std_ReturnType stdRet;

/* Enable Spi communication retry */
#if (CANTRCV_119_TJA1145_SPICOMM_RETRIES != CANTRCV_VALUE_ZERO)
	uint8 retryCnt = CANTRCV_VALUE_ZERO;

	for( retryCnt = CANTRCV_VALUE_ZERO; retryCnt < CANTRCV_119_TJA1145_SPICOMM_RETRIES; retryCnt++ )
	{
		stdRet = CanTrcv_119_TJA1145_ReadOneReg(chnPtr->SpiAccessPtr,addr,dataPtr);
		if( E_OK == stdRet )
		{
			break;
		}
	}
	if( retryCnt >= CANTRCV_119_TJA1145_SPICOMM_RETRIES )
	{
		/* Spi communication timeout. */
		chnPtr->chnVarPtr->spiCommTimeoutFlag = TRUE;
	}
#else	/* CANTRCV_119_TJA1145_SPICOMM_RETRIES != CANTRCV_VALUE_ZERO */
	stdRet = CanTrcv_119_TJA1145_ReadOneReg(chnPtr->SpiAccessPtr,addr,dataPtr);
	if( E_OK != stdRet )
	{
		/* Spi communication timeout. */
		chnPtr->chnVarPtr->spiCommTimeoutFlag = TRUE;
	}
#endif	/* CANTRCV_119_TJA1145_SPICOMM_RETRIES != CANTRCV_VALUE_ZERO */

}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_MFunc_SetOpMode
*
* Explanation: Sets the mode of the Transceiver to the value OpMode.
*              (Asynchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: None.
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_MFunc_SetOpMode
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
    Std_ReturnType stdRet = E_NOT_OK;

	if( chnPtr->chnVarPtr->currMode != chnPtr->chnVarPtr->reqMode )
	{
		switch (chnPtr->chnVarPtr->reqMode)
		{
			case CANTRCV_TRCVMODE_NORMAL:
				stdRet = CanTrcv_119_TJA1145_ToNormal(chnPtr);
				break;
			case CANTRCV_TRCVMODE_STANDBY:
				stdRet = CanTrcv_119_TJA1145_ToStandBy(chnPtr);
				break;
			case CANTRCV_TRCVMODE_SLEEP:
				stdRet = CanTrcv_119_TJA1145_ToSleep(chnPtr);
				break;
			default:
				break;
		}
		if ( E_OK == stdRet )
		{
			chnPtr->chnVarPtr->currMode = chnPtr->chnVarPtr->reqMode;
			/* Indicates a transceiver state transition to CanIf module. */
			CanIf_TrcvModeIndication(chnPtr->ChannelId, chnPtr->chnVarPtr->currMode);
		}
	}
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_GetOpMode
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
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_GetOpMode_Process
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
	P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) OpMode
)
{
    Std_ReturnType stdRet;
    uint8 data = CANTRCV_VALUE_ZERO;

	/* Read register of mode control */
    CanTrcv_119_TJA1145_ReadOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_MODECTRL, &data);
	/* Check Spi communication status. */
	stdRet = CanTrcv_119_TJA1145_ChkAndClrSpiComTO(chnPtr);
	if( E_OK == stdRet )
	{
		switch (data)
		{
			case CANTRCV_119_TJA1145_MC_NORMAL:
				*OpMode = CANTRCV_TRCVMODE_NORMAL;
				break;
			case CANTRCV_119_TJA1145_MC_STANDBY:
				*OpMode = CANTRCV_TRCVMODE_STANDBY;
				break;
			case CANTRCV_119_TJA1145_MC_SLEEP:
				*OpMode = CANTRCV_TRCVMODE_SLEEP;
				break;
			default:
				break;
		}
	}

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ToNormal
*
* Explanation: Set transceiver mode to NORMAL and Active CAN bus.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: E_OK: Operation successful.
*		  E_NOT_OK: Operation not successful.
********************************************************************************
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ToNormal
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
    Std_ReturnType stdRet;

	/* Register of Mode Control: MC = Normal mode. */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_MODECTRL, CANTRCV_119_TJA1145_MC_NORMAL);
	/* Register of CAN Control: CFDC = 1, CAN FD tolerance enabled. CMC = 0x01. */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_CANCTRL, CANTRCV_119_TJA1145_REGVALUE_CANCTRL);
	/* Check Spi communication status. */
	stdRet = CanTrcv_119_TJA1145_ChkAndClrSpiComTO(chnPtr);

#if (CANTRCV_119_TJA1145_TIMER_TYPE == CANTRCV_TIMERTYPE_16BIT1US)
	if( E_OK == stdRet )
	{
		Tm_BusyWait1us16bit(CANTRCV_119_TJA1145_WAIT_TIME);
	}
#endif	/* CANTRCV_119_TJA1145_TIMER_TYPE == CANTRCV_TIMERTYPE_16BIT1US */

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ToSleep
*
* Explanation: Set transceiver mode to SLEEP.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: E_OK: Operation successful.
*		  E_NOT_OK: Operation not successful.
********************************************************************************
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ToSleep
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
	Std_ReturnType stdRet;

	/* Clear status register. */
	CanTrcv_119_TJA1145_ClearStatusReg(chnPtr);
	if( PN_DISABLED == chnPtr->chnVarPtr->pnAct )
	{
		/* CAN Standard wake up. */
		CanTrcv_119_TJA1145_CANStandardWakeUp(chnPtr);
	}
	else
	{
		/* CAN PN wake up. */
		CanTrcv_119_TJA1145_CANPNWakeUp(chnPtr);
	}
	/* Register of Mode Control: MC = Sleep mode. */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_MODECTRL, CANTRCV_119_TJA1145_MC_SLEEP);
	/* Check Spi communication status. */
	stdRet = CanTrcv_119_TJA1145_ChkAndClrSpiComTO(chnPtr);

#if (CANTRCV_119_TJA1145_TIMER_TYPE == CANTRCV_TIMERTYPE_16BIT1US)
	if( E_OK == stdRet )
	{
		Tm_BusyWait1us16bit(CANTRCV_119_TJA1145_WAIT_TIME);
	}
#endif	/* CANTRCV_119_TJA1145_TIMER_TYPE == CANTRCV_TIMERTYPE_16BIT1US */

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ToStandBy
*
* Explanation: Set transceiver mode to StandBy.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: E_OK: Operation successful.
*		  E_NOT_OK: Operation not successful.
********************************************************************************
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ToStandBy
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
	Std_ReturnType stdRet;

	/* Register of Mode Control: MC = StandBy mode. */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_MODECTRL, CANTRCV_119_TJA1145_MC_STANDBY);
	/* Check Spi communication status. */
	stdRet = CanTrcv_119_TJA1145_ChkAndClrSpiComTO(chnPtr);

#if (CANTRCV_119_TJA1145_TIMER_TYPE == CANTRCV_TIMERTYPE_16BIT1US)
	if( E_OK == stdRet )
	{
		Tm_BusyWait1us16bit(CANTRCV_119_TJA1145_WAIT_TIME);
	}
#endif	/* CANTRCV_119_TJA1145_TIMER_TYPE == CANTRCV_TIMERTYPE_16BIT1US */

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_CANStandardWakeUp
*
* Explanation: Unlock the register.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: None.
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_CANStandardWakeUp
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
	/* Write Register: CANCTRL: PNCOK = 0, CPNC = 0, CFDC = 1. */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_CANCTRL, CANTRCV_119_TJA1145_CANCTRL_STAWU);
    /* Write Register: TRCVEVENT_EN: CWE = 1. */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_TRCVEVENT_EN, CANTRCV_119_TJA1145_TRCVEVENT_EN_CANWUEN);
}

/*
********************************************************************************
* Function Name: SPIIF_TJA1145_0_Register_Unlock
*
* Explanation: Unlock the register.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: None.
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_CANPNWakeUp
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
	uint8 wakeUpBitRate;
	const CanTrcv_PartialNetworkType* PnNetworkPtr = chnPtr->PnNetworkPtr;

    /* Get parameter of CAN baud rate. */
    if( CANTRCV_119_TJA1145_BAUDRATE_1M == PnNetworkPtr->BaudRate )
    {
        wakeUpBitRate = CANTRCV_119_TJA1145_BITRATE_1M;
    }
    else if( CANTRCV_119_TJA1145_BAUDRATE_500K == PnNetworkPtr->BaudRate )
    {
        wakeUpBitRate = CANTRCV_119_TJA1145_BITRATE_500K;
    }
    else if( CANTRCV_119_TJA1145_BAUDRATE_250K == PnNetworkPtr->BaudRate )
    {
        wakeUpBitRate = CANTRCV_119_TJA1145_BITRATE_250K;
    }
    else if( CANTRCV_119_TJA1145_BAUDRATE_125K == PnNetworkPtr->BaudRate )
    {
        wakeUpBitRate = CANTRCV_119_TJA1145_BITRATE_125K;
    }
    else
    {
        wakeUpBitRate = CANTRCV_119_TJA1145_BITRATE_500K;
    }
    /* Set the baud rate parameter of CAN wake up function. */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_DATARATE, wakeUpBitRate);
    /* Set the CANID and CANID type parameters of CAN wake up function. */
    CanTrcv_119_TJA1145_CanWakeUp_ID(chnPtr, PnNetworkPtr->PnFrameCanId,PnNetworkPtr->PnCanIdIsExtended);
    /* Set the CANID mask parameter of CAN wake up function. */
    CanTrcv_119_TJA1145_CanWakeUp_IDMask(chnPtr, PnNetworkPtr->PnFrameCanIdMask,PnNetworkPtr->PnCanIdIsExtended);
    if( PnNetworkPtr->PnFrameDlc == CANTRCV_VALUE_ZERO )
    {
        /* Data length code and data field are ¡®don¡¯t care¡¯ for wake-up */
        CanTrcv_119_TJA1145_CanWakeUp_FrameControl(chnPtr, PnNetworkPtr->PnCanIdIsExtended,FALSE,PnNetworkPtr->PnFrameDlc);
    }
    else
    {
        /* Set the data mask parameter of CAN wake up function. */
        CanTrcv_119_TJA1145_CanWakeUp_FrameControl(chnPtr, PnNetworkPtr->PnCanIdIsExtended,TRUE,PnNetworkPtr->PnFrameDlc);
        CanTrcv_119_TJA1145_CanWakeUp_DataMask(chnPtr, &PnNetworkPtr->PnFrameDataMask[CANTRCV_VALUE_ZERO]);
    }
	/* Write Register: CANCTRL: PNCOK = 1, CPNC = 1, CFDC = 1. */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_CANCTRL, CANTRCV_119_TJA1145_CANCTRL_PNWU);
    /* Write Register: TRCVEVENT_EN: CWE = 1. */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_TRCVEVENT_EN, CANTRCV_119_TJA1145_TRCVEVENT_EN_CANWUEN);
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_CanWakeUp_ID
*
* Explanation: Set the CANID and CANID type parameters of CAN wake up function.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*        id: The CANID data to be written.
*        ide: The CANID type data to be written.
*
* retval: None.
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_CanWakeUp_ID
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
	uint32 id,
 	boolean ide
)
{
	uint8 data[CANTRCV_VALUE_FOUR] = {CANTRCV_VALUE_ZERO};

    if( FALSE == ide )
    {
		/* Standard frame. Disassemble the data according to the register definition. */
		data[CANTRCV_VALUE_ONE] = (uint8)((CANTRCV_VALUE_0x000007C0 & id) >> CANTRCV_VALUE_SIX);
        data[CANTRCV_VALUE_ZERO] = (uint8)((CANTRCV_VALUE_0x0000003F & id) << CANTRCV_VALUE_TWO);
		/* Write Register: ID2, ID3. */
		CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_ID2, data[CANTRCV_VALUE_ZERO]);
		CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_ID3, data[CANTRCV_VALUE_ONE]);
    }
    else
    {
		/* Externded frame. Disassemble the data according to the register definition. */
		data[CANTRCV_VALUE_THREE] = (uint8)((CANTRCV_VALUE_0x1F000000 & id)>>CANTRCV_VALUE_TWENTYFOUR);
        data[CANTRCV_VALUE_TWO] = (uint8)((CANTRCV_VALUE_0x00FF0000 & id)>>CANTRCV_VALUE_SIXTEEN);
        data[CANTRCV_VALUE_ONE] = (uint8)((CANTRCV_VALUE_0x0000FF00 & id)>>CANTRCV_VALUE_EIGHT);
        data[CANTRCV_VALUE_ZERO] = (uint8)(CANTRCV_VALUE_0x000000FF & id);
		/* Write Register: ID0, ID1, ID2, ID3. */
		CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_ID0, data[CANTRCV_VALUE_ZERO]);
		CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_ID1, data[CANTRCV_VALUE_ONE]);
		CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_ID2, data[CANTRCV_VALUE_TWO]);
		CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_ID3, data[CANTRCV_VALUE_THREE]);
    }
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_CanWakeUp_IDMask
*
* Explanation: Set the CANID and CANID type parameters of CAN wake up function.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*        idMask: The CANID mask data to be written.
*        ide: The CANID type data to be written.
*
* retval: None.
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_CanWakeUp_IDMask
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
 	uint32 idMask,
	boolean ide
)
{
	uint8 data[CANTRCV_VALUE_FOUR] = {CANTRCV_VALUE_ZERO};

    if( FALSE == ide )
    {
		/* Standard frame. Disassemble the data according to the register definition. */
		data[CANTRCV_VALUE_ONE] = (uint8)((CANTRCV_VALUE_0x000007C0 & idMask) >> CANTRCV_VALUE_SIX);
        data[CANTRCV_VALUE_ZERO] = (uint8)((CANTRCV_VALUE_0x0000003F & idMask) << CANTRCV_VALUE_TWO);
		/* Write Register: IDMASK2, IDMASK3. */
		CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_IDMASK2, data[CANTRCV_VALUE_ZERO]);
		CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_IDMASK3, data[CANTRCV_VALUE_ONE]);
    }
    else
    {
		/* Externded frame. Disassemble the data according to the register definition. */
		data[CANTRCV_VALUE_THREE] = (uint8)((CANTRCV_VALUE_0x1F000000 & idMask)>>CANTRCV_VALUE_TWENTYFOUR);
        data[CANTRCV_VALUE_TWO] = (uint8)((CANTRCV_VALUE_0x00FF0000 & idMask)>>CANTRCV_VALUE_SIXTEEN);
        data[CANTRCV_VALUE_ONE] = (uint8)((CANTRCV_VALUE_0x0000FF00 & idMask)>>CANTRCV_VALUE_EIGHT);
        data[CANTRCV_VALUE_ZERO] = (uint8)(CANTRCV_VALUE_0x000000FF & idMask);
		/* Write Register: IDMASK0, IDMASK1, IDMASK2, IDMASK3. */
		CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_IDMASK0, data[CANTRCV_VALUE_ZERO]);
		CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_IDMASK1, data[CANTRCV_VALUE_ONE]);
		CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_IDMASK2, data[CANTRCV_VALUE_TWO]);
		CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_IDMASK3, data[CANTRCV_VALUE_THREE]);
    }
}

/*
********************************************************************************
* Function Name: SPIIF_TJA1145_0_CanWakeUp_DataMask
*
* Explanation: Set the data mask parameter of CAN wake up function.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*        data: Pointer to data to be written.
*
* retval: None.
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_CanWakeUp_DataMask
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
 	P2CONST(uint8, AUTOMATIC, CANTRCV_APPL_CONST) data
)
{
	/* Write Register: DATAMASK0, DATAMASK1, DATAMASK2, DATAMASK3, DATAMASK4, DATAMASK5, DATAMASK6, DATAMASK7. */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_DATAMASK7, data[CANTRCV_VALUE_SEVEN]);
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_DATAMASK6, data[CANTRCV_VALUE_SIX]);
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_DATAMASK5, data[CANTRCV_VALUE_FIVE]);
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_DATAMASK4, data[CANTRCV_VALUE_FOUR]);
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_DATAMASK3, data[CANTRCV_VALUE_THREE]);
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_DATAMASK2, data[CANTRCV_VALUE_TWO]);
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_DATAMASK1, data[CANTRCV_VALUE_ONE]);
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_DATAMASK0, data[CANTRCV_VALUE_ZERO]);
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_CanWakeUp_FrameControl
*
* Explanation: Set the data mask flag and Dlc parameters of CAN wake up function.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*		 ide: The CANID type data to be written.
*        dataMask: The CAN DataMask flag data to be written.
*        dlc: The CAN dlc data to be written.
*
* retval: None.
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_CanWakeUp_FrameControl
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
 	boolean ide,
	boolean dataMask,
	uint8 dlc
)
{
	uint8 data = CANTRCV_VALUE_ZERO;

    if( TRUE == ide )
    {
		/* Extended frame format. IDE = 1. */
		data |= CANTRCV_119_TJA1145_FRAMECTRL_IDE;
    }
    if(TRUE == dataMask)
    {
		/* Data length code and data field are evaluated at wake-up. PNDM = 1. */
		data |= CANTRCV_119_TJA1145_FRAMECTRL_PNDM;
    }
    data |= (CANTRCV_VALUE_CLEAR_0x0F & dlc);
	/* Write Register: FRAMECTRL. */
    CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_FRAMECTRL, data);
}

/*
********************************************************************************
* Function Name: CanTrcv_Tja1145_Det_ErrorReport
*
* Explanation: Report error to Det Module.
*
* param: apiId: the Api Service Id of CanTrcv.
*        errorId: Error Id defined in CanTrcv_Types.h.
*
* retval: None
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_Det_ErrorReport
(
	uint8 apiId,
 	uint8 errorId
)
{

#if ( CANTRCV_119_TJA1145_DEV_ERROR_DETECT == STD_ON )
    if( errorId != CANTRCV_E_NO_ERR )      /* Error detected. */
    {
        (void)Det_ReportError(CANTRCV_119_TJA1145_MODULE_ID, CANTRCV_119_TJA1145_INSTANCE_ID_DET, apiId, errorId);    /* Report Error to Det. */
    }
#else
    {
        CANTRCV_DUMMY_STATEMENT(apiId);
        CANTRCV_DUMMY_STATEMENT(errorId);
    }
#endif

}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_InitOneChn
*
* Explanation: Init one CanTrcv channel.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: E_OK: Operation successful.
*		  E_NOT_OK: Operation not successful.
********************************************************************************
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_InitOneChn
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
	Std_ReturnType stdRet;
	uint8 trcvEventStaData = CANTRCV_VALUE_ZERO;

	/* Init memory for one CanTrcv channel. */
    CanTrcv_119_TJA1145_InitOneChn_Memory(chnPtr);
	/* Write Register: LOCK CONTROL. Unlock all register. */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_LOCKCTRL, CANTRCV_119_TJA1145_UNLOCKALL);
	/* Read Register: Trcv event status. */
	CanTrcv_119_TJA1145_ReadOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_TRCVEVENT_STA, &trcvEventStaData);
	/* Check CAN wake-up event. */
	if( CANTRCV_VALUE_ZERO != (trcvEventStaData & CANTRCV_119_TJA1145_REGVALUE_CW))
	{
		chnPtr->chnVarPtr->wuReason = CANTRCV_WU_BY_BUS;

#if (CANTRCV_ECUMWUEVENT_CFG == STD_ON)
		EcuM_SetWakeupEvent(((EcuM_WakeupSourceType)CANTRCV_VALUE_ONE) << chnPtr->ecumWakeupSrcId);
#endif	/* CANTRCV_ECUMWUEVENT_CFG == STD_ON */

	}
	/* Check CAN bus error. */
	CanTrcv_119_TJA1145_ChkCanBusErr(chnPtr);
	/* Check power on flag. */
	CanTrcv_119_TJA1145_ChkPor(chnPtr);
	/* Clear the status register. */
	CanTrcv_119_TJA1145_ClearStatusReg(chnPtr);
	/* Check Spi communication status. */
	stdRet = CanTrcv_119_TJA1145_ChkAndClrSpiComTO(chnPtr);

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_InitOneChn
*
* Explanation: Init memory for one CanTrcv channel.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: None.
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_InitOneChn_Memory
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
	/* Check PN Cfg. */
	if( FALSE != chnPtr->PnNetworkPtr->PnEnabled )
	{
		chnPtr->chnVarPtr->pnAct = PN_ENABLED;
	}
	else
	{
		chnPtr->chnVarPtr->pnAct = PN_DISABLED;
	}
	/* Set the initial value. */
	chnPtr->chnVarPtr->spiCommTimeoutFlag = FALSE;
	chnPtr->chnVarPtr->reqMode = chnPtr->InitState;
	chnPtr->chnVarPtr->currMode = chnPtr->InitState;
	chnPtr->chnVarPtr->wuMode = CANTRCV_WUMODE_ENABLE;
	chnPtr->chnVarPtr->wuReason = CANTRCV_WU_ERROR;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_CheckCanWakeUp
*
* Explanation: Check CAN wake up status flag.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: E_OK: Operation successful.
*		  E_NOT_OK: Operation not successful.
********************************************************************************
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_CheckCanWakeUp
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
	Std_ReturnType stdRet;
	uint8 trcvEventStaData = CANTRCV_VALUE_ZERO;

	/* Read Register: Trcv event status. */
	CanTrcv_119_TJA1145_ReadOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_TRCVEVENT_STA, &trcvEventStaData);
	/* Check Spi communication status. */
	stdRet = CanTrcv_119_TJA1145_ChkAndClrSpiComTO(chnPtr);
	if( E_OK == stdRet )
	{
		/* Check CAN wake-up event. */
		if( CANTRCV_VALUE_ZERO != (trcvEventStaData & CANTRCV_119_TJA1145_REGVALUE_CW))
		{
			chnPtr->chnVarPtr->wuReason = CANTRCV_WU_BY_BUS;
		}
	}

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_InitOneChn
*
* Explanation: Init one CanTrcv channel.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: None.
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_ClearStatusReg
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
	/* Clear the register of System event status */
    CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_SYSEVENT_STA, CANTRCV_VALUE_CLEARREG_0xFF);
    /* Clear the register of Event capture status */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_EVENTCAP_STA, CANTRCV_VALUE_CLEARREG_0xFF);
    /* Clear the register of Transceiver event status */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_TRCVEVENT_STA, CANTRCV_VALUE_CLEARREG_0xFF);
    /* Clear the register of WAKE pin event status */
	CanTrcv_119_TJA1145_WriteOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_WPINEVENT_STA, CANTRCV_VALUE_CLEARREG_0xFF);
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ChkAndClrSpiComTO
*
* Explanation: Init one CanTrcv channel.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: E_OK: Spi communication normal.
*		  E_NOT_OK: Spi communication timeout.
********************************************************************************
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ChkAndClrSpiComTO
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
	Std_ReturnType stdRet = E_OK;

	/* Check the Spi communication timeout flag. */
	if( TRUE == chnPtr->chnVarPtr->spiCommTimeoutFlag )
	{
		stdRet = E_NOT_OK;
		/* Clear timeout flag. */
		chnPtr->chnVarPtr->spiCommTimeoutFlag = FALSE;
	}

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ChkCanBusSilence
*
* Explanation: Check CAN bus silence Flag.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*		 FlagState: State of the silence flag.
*
* retval: E_OK: Operation successful.
*		  E_NOT_OK: Operation not successful.
********************************************************************************
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ChkCanBusSilence
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr,
 	P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState
)
{
	Std_ReturnType stdRet;
	uint8 trcvEventStaData = CANTRCV_VALUE_ZERO;

	/* Read Register: Trcv event status. */
	CanTrcv_119_TJA1145_ReadOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_TRCVEVENT_STA, &trcvEventStaData);
	/* Check Spi communication status. */
	stdRet = CanTrcv_119_TJA1145_ChkAndClrSpiComTO(chnPtr);
	if( E_OK == stdRet )
	{
		/* Check CAN silence. */
		if( CANTRCV_VALUE_ZERO != (trcvEventStaData & CANTRCV_119_TJA1145_REGVALUE_CBS))
		{
			*FlagState = CANTRCV_FLAG_SET;
		}
		else
		{
			*FlagState = CANTRCV_FLAG_CLEARED;
		}
	}

	return stdRet;

}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ChkCanBusErr
*
* Explanation: Check CAN bus error flag.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: None.
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_ChkCanBusErr
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
	Std_ReturnType stdRet;
	uint8 trcvEventStaData = CANTRCV_VALUE_ZERO;

	/* Read Register: Trcv event status. */
	CanTrcv_119_TJA1145_ReadOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_TRCVEVENT_STA, &trcvEventStaData);
	/* Check Spi communication status. */
	stdRet = CanTrcv_119_TJA1145_ChkAndClrSpiComTO(chnPtr);
	if( E_OK == stdRet )
	{
		/* Check CAN bus error. */
		if( CANTRCV_VALUE_ZERO != (trcvEventStaData & CANTRCV_119_TJA1145_REGVALUE_CF))
		{
			chnPtr->chnVarPtr->busErrFlag = TRUE;

#if (CANTRCV_119_TJA1145_DEMEVENT_CFG == STD_ON)
			if( CANTRCV_NO_BUSERREVENTID  == chnPtr->eventIdBusErr )
			{
				Dem_ReportErrorStatus(chnPtr->eventIdBusErr, DEM_EVENT_STATUS_FAILED);
			}
#endif	/* CANTRCV_119_TJA1145_DEMEVENT_CFG == STD_ON */

		}
		else
		{
			chnPtr->chnVarPtr->busErrFlag = FALSE;

#if (CANTRCV_119_TJA1145_DEMEVENT_CFG == STD_ON)
			if( CANTRCV_NO_BUSERREVENTID  == chnPtr->eventIdBusErr )
			{
				Dem_ReportErrorStatus(chnPtr->eventIdBusErr, DEM_EVENT_STATUS_PASSED);
			}
#endif	/* CANTRCV_119_TJA1145_DEMEVENT_CFG == STD_ON */

		}
	}
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_Init_SetOpMode
*
* Explanation: Sets the mode of the Transceiver to the value OpMode.
*              (Asynchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: E_OK: will be returned if the request for transceiver mode change has been accepted.
*		  E_NOT_OK: will be returned if the request for transceiver mode change has not been
*		            accepted or any parameter is out of the allowed range.
********************************************************************************
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_Init_SetOpMode
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
    Std_ReturnType stdRet = E_NOT_OK;

	/* Set Op mode based on CanTrcvInitState. */
	switch (chnPtr->InitState)
	{
		case CANTRCV_TRCVMODE_NORMAL:
			stdRet = CanTrcv_119_TJA1145_ToNormal(chnPtr);
			break;
		case CANTRCV_TRCVMODE_STANDBY:
			stdRet = CanTrcv_119_TJA1145_ToStandBy(chnPtr);
			break;
		case CANTRCV_TRCVMODE_SLEEP:
			stdRet = CanTrcv_119_TJA1145_ToSleep(chnPtr);
			break;
		default:
			break;
	}

	return stdRet;
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ChkPor
*
* Explanation: Check power on flag.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: None.
********************************************************************************
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_ChkPor
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
	Std_ReturnType stdRet;
	uint8 staData = CANTRCV_VALUE_ZERO;

	/* Read Register: Trcv system event. */
	CanTrcv_119_TJA1145_ReadOneReg_SpiRetry(chnPtr, CANTRCV_119_TJA1145_REGADDR_SYSEVENT_STA, &staData);
	/* Check Spi communication status. */
	stdRet = CanTrcv_119_TJA1145_ChkAndClrSpiComTO(chnPtr);
	if( E_OK == stdRet )
	{
		/* Check CAN bus error. */
		if( CANTRCV_VALUE_ZERO != (staData & CANTRCV_119_TJA1145_REGVALUE_PO))
		{
			chnPtr->chnVarPtr->porFlag = TRUE;

#if (CANTRCV_ECUMWUEVENT_CFG == STD_ON)
			EcuM_SetWakeupEvent(((EcuM_WakeupSourceType)CANTRCV_VALUE_ONE) << chnPtr->ecumPorWakeupSrcId);
#endif	/* CANTRCV_ECUMWUEVENT_CFG == STD_ON */

		}
		else
		{
			chnPtr->chnVarPtr->porFlag = FALSE;
		}
	}
}

/*
********************************************************************************
* Function Name: CanTrcv_119_TJA1145_ChkBaudRate
*
* Explanation: Check power on flag.
*              (Synchronous)
*
* param: chnPtr: Pointer to CanTrcv channel information.
*
* retval: E_OK: Baud rate configuration is correct.
*		  E_NOT_OK: Baud rate configuration is not correct.
********************************************************************************
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ChkBaudRate
(
	P2CONST(CanTrcv_ChannelType, AUTOMATIC, CANTRCV_APPL_CONST) chnPtr
)
{
	Std_ReturnType stdRet = E_OK;
	uint16 baudRate = chnPtr->PnNetworkPtr->BaudRate;

	/* Check the baud rate configuration. */
	if( (CANTRCV_119_TJA1145_BAUDRATE_50K != baudRate)
		&& (CANTRCV_119_TJA1145_BAUDRATE_100K != baudRate)
		&& (CANTRCV_119_TJA1145_BAUDRATE_125K != baudRate)
		&& (CANTRCV_119_TJA1145_BAUDRATE_250K != baudRate)
		&& (CANTRCV_119_TJA1145_BAUDRATE_500K != baudRate)
		&& (CANTRCV_119_TJA1145_BAUDRATE_1M != baudRate) )
	{
		stdRet = E_NOT_OK;
	}

	return stdRet;
}

#define CANTRCV_STOP_SEC_CODE
#include "CanTrcv_MemMap.h"
