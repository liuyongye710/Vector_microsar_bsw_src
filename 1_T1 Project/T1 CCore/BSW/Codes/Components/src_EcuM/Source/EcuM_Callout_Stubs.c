/*
********************************************************************************
*
* File name: EcuM_Callout_Stubs.c
*
* Copyright 2019-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
*  Version: 1.0
* Author/Date : yong.zhang/2019.11.26
*  Change: New created
*  Cause: New
********************************************************************************
* Version: 1.1
* Author/Date : Yaoxingjia/2020.02.18
* Change: Delete local variables and use parameters directly.
* Cause: Bugfix
********************************************************************************
* Version: 3.1
* Author/Date : yong.zhang/2020.07.02
* Change: Add release software number
* Cause: Update
********************************************************************************
* Version: 3.2
* Author/Date: fangtao/2020.09.15
* Change: Modify the function name according to the AUTOSAR specification, add
*         MemMap.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: guoziyang/2021.6.30
* Change: Modify the function name according to the AUTOSAR specification, add
*         MemMap.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: guoziyang/2021.6.30
* Change: Add EcuM_Callout_Init.h.
* Cause: Add
********************************************************************************
* Version: 3.4
* Author/Date: guoziyang/2021.6.30
* Change:  Add function of multicore in EcuM_ShutdownOS.
* Cause: Add
********************************************************************************
* Version: 3.5
* Author/Date: guoziyang/2021.6.30
* Change:  Add in parameters of EcuM_McuSetMode.
* Cause: Add
********************************************************************************
* Version: 3.6
* Author/Date: guoziyang/2021.8.9
* Change: Add return in empty function. 
* Cause: Add
********************************************************************************
* Version: 3.7
* Author/Date: GuoZY/2021.8.16
* Change: Modify code according to Autosar specification. 
* Cause: Optimization
********************************************************************************
* Version: 3.8
* Author/Date: GuoZY/2021.9.1
* Change: Modify compilation warning.
* Cause: Optimization
********************************************************************************
* Version: 3.9
* Author/Date: GuoZY/2021.10.28
* Change: Delete Os_Types.h 
* Cause: Optimization
********************************************************************************
* Version: 3.10
* Author/Date: GuoZY/2021.12.10
* Change: Add conditional compilation for EcuM_McuSetMode().
* Cause: Optimization
********************************************************************************
* Version: 3.11
* Author/Date: GuoZY/2021.12.13
* Change: Optimize Os header file inclusion.
* Cause: Optimization
********************************************************************************
* Version: 3.12
* Author/Date : WangXG/2022.09.22
* Change: Append ECUM supports processing that supports multi-core synchronization
*         Modify EcuM_AL_DriverInitZero EcuM_AL_DriverInitOne
* Cause: Optimization
********************************************************************************
* Version: 3.13
* Author/Date : LQiao/2023.7.31
* Change: create by neusarconfigurator
* Cause: Optimization
********************************************************************************
* Version: 3.14
* Author/Date: TianL/2024.8.5
* Change: Modify copyright.
* Cause: Update
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "EcuM.h"
#include "EcuM_Callout_Init.h"
#include "BswM.h"
#include "EcuM_Types.h"
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
#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.h"
#include "Dio_Cfg.h"

/*
********************************************************************************
* Function Name: EcuM_AL_SetProgrammableInterrupts
*
* Explanation: If the configuration parameter EcuMSetProgrammableInterrupts is set to true, this
*                callout EcuM_AL_SetProgrammableInterrupts is executed and shall set the
*                interrupts on ECUs with programmable interrupts.(Synchronous & Non Reentrant)
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_AL_SetProgrammableInterrupts(void)
{
    return;
}

#if( ECUM_POSTBUILD_VARIANT_SUPPORT == STD_ON )
/*
********************************************************************************
* Function Name: EcuM_DeterminePbConfiguration
*
* Explanation: This callout should evaluate some condition, like port pin or NVRAM value.(Synchronous & Non Reentrant)
*
* param: None
*
* retval: None
********************************************************************************
*/
const EcuM_ConfigType* EcuM_DeterminePbConfiguration(void)
{
    return NULL_PTR;
}
#endif

/*
********************************************************************************
* Function Name: EcuM_LoopDetection
*
* Explanation: If the configuration parameter EcuMResetLoopDetection is set to true, this callout
*            EcuM_LoopDetection is called on every startup.(Synchronous & Non Reentrant)
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(boolean, ECUM_CODE) EcuM_LoopDetection(void)
{
    return TRUE;
}

/*
********************************************************************************
* Function Name: EcuM_AL_SwitchOff
*
* Explanation: This callout shall take the code for shutting off the power supply of the ECU. If the
*            ECU cannot unpower itself, a reset may be an adequate reaction.(Synchronous &  Non Reentrant)
*
* param: ErrCode
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_AL_SwitchOff(void)
{
	unsigned char KeyState = STD_HIGH;

	KeyState = Dio_ReadChannel(DioConf_DioChannel_DI_IN_KL15);
	if(STD_LOW == KeyState)
	{
		Mcu_PerformReset();
	}
	while(1)
	{
		KeyState = Dio_ReadChannel(DioConf_DioChannel_DI_IN_KL15);
		if( STD_LOW == KeyState)
		{
			Mcu_PerformReset();
		}
	}
    return;
}

/*
********************************************************************************
* Function Name: EcuM_AL_Reset
*
* Explanation: This callout shall take the code for resetting the ECU.(Synchronous & Non Reentrant)
*
* param: reset: Type of reset to be performed.
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_AL_Reset(EcuM_ResetType reset)
{
    ECUM_DUMMY_STATEMENT(reset);
    return;
}

/*
********************************************************************************
* Function Name: EcuM_OnGoOffTwo
*
* Explanation: This call allows the system designer to notify that the GO OFF II state is about to
*                be entered.(Synchronous & Non Reentrant)
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_OnGoOffTwo(void)
{
    Ecu_PowerOff();/* WangM */
    return;
}

/*
********************************************************************************
* Function Name: EcuM_StartCheckWakeup
*
* Explanation: This API is called by the ECU Firmware to start the CheckWakeupTimer for the
*               corresponding WakeupSource.(Synchronous & Non Reentrant)
*
* param: WakeupSource: For this wakeup source the corresponding CheckWakeupTimer shall be started.
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_StartCheckWakeup(EcuM_WakeupSourceType WakeupSource)
{
    ECUM_DUMMY_STATEMENT(WakeupSource);
    return;
}

/*
********************************************************************************
* Function Name: EcuM_CheckWakeup
*
* Explanation: For this wakeup source the corresponding CheckWakeupTimer shall be started.
*           It shall also be called by the ISR of a wakeup source to set up the PLL
*           and check other wakeup sources that may be connected to the same interrupt..(Synchronous & Non Reentrant)
*
* param: WakeupSource:
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
    ECUM_DUMMY_STATEMENT(wakeupSource);
    return;
}

/*
********************************************************************************
* Function Name: EcuM_EndCheckWakeup
*
* Explanation: This API is called by any SW Module whose wakeup source is checked asynchronously (e.g. asynchronous Can Trcv Driver)
*            and the Check of the Wakeup returns a negative Result (no Wakeup by this Source). The API cancels the CheckWakeupTimer
*            for the WakeupSource. If the correponding CheckWakeupTimer is canceled the check of this wakeup source is finished.
*            (Synchronous & Non Reentrant)
*
* param: WakeupSource: For this wakeup source the corresponding CheckWakeupTimer shall be canceled.
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_EndCheckWakeup(EcuM_WakeupSourceType WakeupSource)
{
    ECUM_DUMMY_STATEMENT(WakeupSource);
    return;
}

/*
********************************************************************************
* Function Name: EcuM_AL_DriverRestart
*
* Explanation: This callout shall provide driver initialization and other hardware-related startup
*               activities in the wakeup case.(Synchronous & Non Reentrant)
*
* param: ConfigPtr: Pointer to the EcuM post-build configuration which contains pointers to
*                   all other BSW module post-build configurations.
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_AL_DriverRestart
(
    P2CONST(EcuM_ConfigType, AUTOMATIC, ECUM_APPL_CONST) ConfigPtr
)
{
    uint8 ecum_dummy = ECUM_ZERO;

    /* To avoid compiler warning. */
     if( NULL_PTR != ConfigPtr )
    {
        ECUM_DUMMY_STATEMENT(ecum_dummy);
    }

    return;
}

/*
********************************************************************************
* Function Name: EcuM_GenerateRamHash
*
* Explanation: Generate Ram Hash.(Synchronous & Non Reentrant)
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_GenerateRamHash(void)
{

    return;
}

/*
********************************************************************************
* Function Name: EcuM_EnableWakeupSources
*
* Explanation: The ECU Manager Module calls EcuM_EnableWakeupSource to allow the system
*               designer to notify wakeup sources defined in the wakeupSource bitfield that
*               SLEEP will be entered and to adjust their source accordingly.(Synchronous & Non Reentrant)
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_EnableWakeupSources(EcuM_WakeupSourceType wakeupSource)
{
    ECUM_DUMMY_STATEMENT(wakeupSource);
    return;
}

/*
********************************************************************************
* Function Name: EcuM_DisableWakeupSources
*
* Explanation: The ECU Manager Module calls EcuM_DisableWakeupSources to set the wakeup
*            source(s) defined in the wakeupSource bitfield so that they are not able to wake
*            the ECU up.(Synchronous & Non Reentrant)
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_DisableWakeupSources(EcuM_WakeupSourceType wakeupSource)
{
    ECUM_DUMMY_STATEMENT(wakeupSource);
    return;
}

/*
********************************************************************************
* Function Name: EcuM_StartWakeupSources
*
* Explanation: The callout shall start the given wakeup source(s) so that they are ready to
*               perform wakeup validation.(Synchronous & Non Reentrant)
*
* param: wakeupSource
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_StartWakeupSources(EcuM_WakeupSourceType wakeupSource)
{
    ECUM_DUMMY_STATEMENT(wakeupSource);
    return;
}
/*
********************************************************************************
* Function Name: EcuM_CheckValidation
*
* Explanation: This callout is called by the EcuM to validate a wakeup source. If a valid wakeup
*            has been detected, it shall be reported to EcuM via
*            EcuM_ValidateWakeupEvent().(Synchronous & Non Reentrant)
*
* param: wakeupSource
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_CheckValidation(EcuM_WakeupSourceType wakeupSource)
{
   /* EcuM_ValidateWakeupEvent Can be called after successful verification.
    If the verification fails, BswM_EcuM_CurrentWakeup(wakeupSource, ECUM_WKSTATUS_EXPIRED) 
    and EcuM_StopWakeupSources(wakeupSource) can be called. */ 
    ECUM_DUMMY_STATEMENT(wakeupSource);
    return;
}

/*
********************************************************************************
* Function Name: EcuM_StopWakeupSources
*
* Explanation: The callout shall stop the given wakeup source(s) after unsuccessful wakeup
*               validation.(Synchronous & Non Reentrant)
*
* param: wakeupSource
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_StopWakeupSources(EcuM_WakeupSourceType wakeupSource)
{
    ECUM_DUMMY_STATEMENT(wakeupSource);
    return;
}



/*
********************************************************************************
* Function Name: EcuM_SleepActivity
*
* Explanation: This callout is invoked periodically in all reduced clock sleep modes.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_SleepActivity(void)
{
    return;
}

/*
********************************************************************************
* Function Name: EcuM_ErrorHook
*
* Explanation: The ECU State Manager will call the error hook if the error codes "ECUM_E_RAM_CHECK_FAILED" or
*            "ECUM_E_CONFIGURATION_DATA_INCONSISTENT" occur.(Synchronous & Non Reentrant)
*
* param: reason: Reason for calling the error hook.
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_ErrorHook(uint16 reason)
{
    ECUM_DUMMY_STATEMENT(reason);
    return;
}

/*
********************************************************************************
* Function Name: EcuM_OnGoOffOne
*
* Explanation: This call allows the system designer to notify that the GO OFF I state is about to
*               be entered.(Synchronous&Non Reentrant)
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_OnGoOffOne(void)
{
    return;
}

/*
********************************************************************************
* Function Name: EcuM_CheckRamHash
*
* Explanation: This callout is intended to provide a RAM integrity test. .(Synchronous&Non Reentrant)
*
* param: None
*
* retval: uint8: 0: RAM integrity test failed
*            else: RAM integrity test passed
********************************************************************************
*/
FUNC(uint8, ECUM_CODE) EcuM_CheckRamHash(void)
{
    return ECUM_ZERO;
}


/*
********************************************************************************
* Function Name: EcuM_AL_DriverInitZero
*
* Explanation: This callout shall provide driver initialization and other hardware-related startup
*               activities for loading the post-build configuration data. Beware: Here only precompile
*               and link-time configurable modules may be used.(Synchronous & Non Reentrant)
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_AL_DriverInitZero(void)
{
    EcuM_CoreIDType CoreID;
    CoreID = GetCoreID();
    if( EcuM_DriverInitFuncTbl[CoreID].EcuM_InitZeroFunc_P != NULL )
    {
        EcuM_DriverInitFuncTbl[CoreID].EcuM_InitZeroFunc_P();
    }

    return;
}


/*
********************************************************************************
* Function Name: EcuM_AL_DriverInitOne
*
* Explanation: This callout shall provide driver initialization and other hardware-related startup
*            activities in case of a power on reset.(Synchronous & Non Reentrant)
*
* param: ConfigPtr: Pointer to the EcuM post-build configuration which contains pointers to
*                   all other BSW module post-build configurations.
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_AL_DriverInitOne
(
    P2CONST(EcuM_ConfigType, AUTOMATIC, ECUM_APPL_CONST) ConfigPtr
)
{
    EcuM_CoreIDType CoreID;
    CoreID = GetCoreID();
    if( EcuM_DriverInitFuncTbl[CoreID].EcuM_InitOneFunc_P != NULL )
    {
        EcuM_DriverInitFuncTbl[CoreID].EcuM_InitOneFunc_P();
    }
	/* To avoid compiler warning. */
    if( NULL_PTR != ConfigPtr)
    {
        ECUM_DUMMY_STATEMENT(CoreID);
    }

    return;
}

/*
********************************************************************************
* Function Name: EcuM_StartOS
*
* Explanation: Start OS
*
* param: appMode
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_StartOS(AppModeType appMode)
{
#if ( ECUM_NUMBER_OF_CORES > ECUM_ONE )
    uint8 coreId;
    StatusType status;
    if( GetCoreID()==ECUM_CORE_ID_MASTER )
    {
        for(coreId = ECUM_ZERO; coreId < ECUM_NUMBER_OF_CORES; coreId++)
        {
            if( coreId!=ECUM_CORE_ID_MASTER )
            {
                StartCore((CoreIdType)coreId, &status);
            }
        }
    }
#endif

    StartOS(appMode);
    return;
}

/*
********************************************************************************
* Function Name: EcuM_ShutdownOS
*
* Explanation: Shutdown OS
*
* param: ErrCode
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_ShutdownOS(Std_ReturnType ErrCode)
{
#if ( ECUM_NUMBER_OF_CORES > ECUM_ONE )
    ShutdownAllCores(ErrCode);
#else
    ShutdownOS(ErrCode);
#endif

    return;
}

#if( ECUM_NORMAL_MCU_MODEREF != ECUM_FF )
/*
********************************************************************************
* Function Name: EcuM_McuSetMode
*
* Explanation: Use Mcu_SetMode to set Mcu mode.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, ECUM_CODE) EcuM_McuSetMode(Mcu_ModeType McuMode)
{
/*
********************************************************************************
* Start of user code before invoking Mcu_SetMode
********************************************************************************
*/
/*** For example: 1.Enable Global Interrupt with API EnableAllInterrupts();
                           (Prevent some MCU can't wake up with Global interrupt disabled.)
                           2.Enable Wakeup Sources Interrupts.
                           3.Stop Os Counter.
***/

/*
********************************************************************************
* End of user code before invoking Mcu_SetMode
********************************************************************************
*/

    Mcu_SetMode(McuMode);
    
/*
********************************************************************************
* Start of user code before invoking Mcu_SetMode
********************************************************************************
*/
/*** For example: 1.Disable Global Interrupt with API DisableAllInterrupts();
                           2.Disable Wakeup Sources Interrupts.
                           3.Start Os Counter.
***/

/*
********************************************************************************
* End of user code before invoking Mcu_SetMode
********************************************************************************
*/

    return;
}

#endif

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"


