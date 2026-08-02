/*
********************************************************************************
*
*  File name: BswM_Lcfg.c
*
*  Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date : yong.zhang/2018.12.13
* Change: New created
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date : yong.zhang/2020.4.26
* Change: Add new configration item
* Cause: Update
********************************************************************************
*/
/*
********************************************************************************
*    Include
********************************************************************************
*/
#include "BswM.h"
#include "Com.h"
#include "BswM_Cfg.h"
#include "Rte_BswM.h"

#if( BSWM_ECUMENABLED == STD_ON )
#include "EcuM.h"
#endif

#if( BSWM_NVMENABLED == STD_ON )
#include "NvM.h"
#endif

#if( BSWM_CANSMENABLED == STD_ON )
#include "CanSM_BswM.h"
#endif

#if( BSWM_LINSMENABLED == STD_ON )
#include "LinSM.h"
#endif

#if( BSWM_LINTPENABLED == STD_ON )
#include "LinTp.h"
#endif

#if( BSWM_SDENABLED == STD_ON )
#include "Sd.h"
#endif

#if( BSWM_ETHSMENABLED == STD_ON)
#include "EthSM.h"
#endif

#if( BSWM_DCMENABLED == STD_ON)
#include "Dcm.h"
#endif

#if( BSWM_FRSMENABLED == STD_ON)
#include "FrSM.h"
#endif

#if( BSWM_NMENABLED == STD_ON )
#include "Nm.h"
#endif

#if( BSWM_J1939DCMENABLED == STD_ON)
#include "J1939Dcm.h"
#endif

#if( BSWM_J1939RMENABLED == STD_ON )
#include "J1939Rm.h"
#endif

#if( BSWM_COMMENABLED == STD_ON )
#include "ComM.h"
#endif

#if( BSWM_J1939NMENABLED == STD_ON )
#include "J1939Nm.h"
#endif

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
#define BSWM_GROUPCONTROL_IDLE   ((uint8)0x00U)
#define BSWM_GROUPCONTROL_NORMAL ((uint8)0x01U)
#define BSWM_GROUPCONTROL_REINIT ((uint8)0x02U)
#define BSWM_GROUPCONTROL_DM     ((uint8)0x04U)

#define BswM_SetIpduGroup(pduId, bitVal) Com_SetIpduGroup(BswM_ComIPduGroupState, (pduId), (bitVal))
#define BswM_SetIpduDMGroup(pduId, bitVal) Com_SetIpduGroup(BswM_ComRxIPduGroupDMState, (pduId), (bitVal))

#define BswM_MarkPduGroupControlInvocation(control) BswM_PduGroupControlInvocation |= (control)
#define BswM_MarkDmControlInvocation() BswM_PduGroupControlInvocation |= BSWM_GROUPCONTROL_DM

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
*    Local Functions
********************************************************************************
*/
#define BSWM_START_SEC_CODE
#include "BswM_MemMap.h"
#if( BSWM_RULEHANDLERENABLE == STD_ON )
static FUNC(Std_ReturnType, BSWM_CODE) BswM_Action_RuleHandler(uint8 handleId);
#endif

#if( BSWM_SIZE_TIMER > BSWM_ZERO )
LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_UpdateTimer(uint8 timerId, uint32 value);
#endif

static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_InitToWakeUp(void);
static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WakeUpToRun(void);
static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_RunToPostRun(void);
static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_PostRunToPreShutDown(void);
static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_PreShutDownToWaitforNvm(void);
static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WaitForNvmToShutDown(void);
static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WaitForNvmToWakeUp(void);

static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_InitToWakeUp(void);
static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_WakeUpToRun(void);
static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_RunToPostRun(void);
static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_PostRunToPreShutDown(void);
static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_PreShutDownToWaitForNvm(void);
static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_WaitForNvmToShutDown(void);
static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_WaitForNvmToWakeup(void);
#define BSWM_STOP_SEC_CODE
#include "BswM_MemMap.h"

/*
********************************************************************************
*    Local Constants
********************************************************************************
*/
/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
#define BSWM_START_SEC_VAR_NO_INIT
#include "BswM_MemMap.h"

#if( BSWM_SIZE_CANSM_CHANNEL > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_CanSMChannelState[BSWM_SIZE_CANSM_CHANNEL];   /* Variable to store current mode of BswMCanSMIndication mode request ports. */
#endif

#if( BSWM_SIZE_CANSMICOM_CHANNEL > 0U )
/* Variable to store current mode of BswMCanSMIcomIndication mode request ports. */
VAR(uint8, BSWM_VAR_NO_INIT) BswM_CanSMIcomChannelState[BSWM_SIZE_CANSMICOM_CHANNEL];
#endif

#if( BSWM_SIZE_COMM_CHANNEL > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_ComMChannelState[BSWM_SIZE_COMM_CHANNEL];     /* Variable to store current mode of BswMComMIndication mode request ports. */
#endif

#if( BSWM_SIZE_ETHSM_CHANNEL > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_EthSMChannelState[BSWM_SIZE_ETHSM_CHANNEL];   /* Variable to store current mode of BswMComMIndication mode request ports. */
#endif

#if( BSWM_SIZE_COMMPNC_CHANNEL > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_ComMPncChannelState[BSWM_SIZE_COMMPNC_CHANNEL];   /* Variable to store current mode of BswMComMPncRequest mode request ports. */
#endif

#if( BSWM_SIZE_GENERIC > 0U )
VAR(uint16, BSWM_VAR_NO_INIT) BswM_GenericState[BSWM_SIZE_GENERIC];             /* Variable to store current mode of BswMGenericRequest mode request ports. */
#endif

#if( BSWM_SIZE_NVM_JOB > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_NvMJobState[BSWM_SIZE_NVM_JOB];               /* Variable to store current mode of BswMNvMJobModeIndication mode request ports. */
#endif

#if( BSWM_SIZE_NVM_BLOCK > 0U )
/* Variable to store current mode of BswMNvMJobModeIndication mode request ports. */
VAR(uint8, BSWM_VAR_NO_INIT) BswM_NvMBlockState[BSWM_SIZE_NVM_BLOCK];
#endif

#if( BSWM_SIZE_ECUM_CHANNEL > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_EcuMChannelState[BSWM_SIZE_ECUM_CHANNEL];    /* Variable to store current mode of BswMEcuMIndication mode request ports. */
#endif

#if( BSWM_SIZE_ECUM_WAKEUP > 0U )
/* Variable to store current mode of EcuMwakeupindication mode request ports. */
VAR(uint8, BSWM_VAR_NO_INIT) BswM_EcuMWakeupState[BSWM_SIZE_ECUM_WAKEUP];
#endif

#if( BSWM_SIZE_DCM_CHANNEL > 0U )
/* Variable to store current mode of BswMDcmIndication mode request ports. */
VAR(uint8, BSWM_VAR_NO_INIT) BswM_DcmChannelState[BSWM_SIZE_DCM_CHANNEL];
#endif

#if( BSWM_SIZE_SDCLIENTSERVICE > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_SdClientServiceState[BSWM_SIZE_SDCLIENTSERVICE];
#endif

#if( BSWM_SIZE_CONSUMEDEVENTGROUP > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_SdConsumedEventGroupState[BSWM_SIZE_CONSUMEDEVENTGROUP];
#endif

#if( BSWM_SIZE_EVENTHANDLER > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_SdEventHandlerState[BSWM_SIZE_EVENTHANDLER];
#endif

#if( BSWM_SIZE_FRSM > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_FrSMState[BSWM_SIZE_FRSM];
#endif

#if( BSWM_SIZE_LINSMSCHEDULE > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_LinSMScheduleState[BSWM_SIZE_LINSMSCHEDULE];
#endif

#if( BSWM_SIZE_LINSM_CHANNEL > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_LinSMChannelState[BSWM_SIZE_LINSM_CHANNEL];
#endif

#if( BSWM_SIZE_LINTP_CHANNEL > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_LinTpChannelState[BSWM_SIZE_LINTP_CHANNEL];
#endif

#if( BSWM_SIZE_J1939DCM_CHANNEL > 0U )
VAR(uint16, BSWM_VAR_NO_INIT) BswM_J1939DcmChannelState[BSWM_SIZE_J1939DCM_CHANNEL];
#endif

#if( BSWM_SIZE_J1939NM_CHANNEL > 0U )
VAR(uint8, BSWM_VAR_NO_INIT) BswM_J1939NmChannelState[BSWM_SIZE_J1939NM_CHANNEL];
#endif

VAR(Com_IpduGroupVector, BSWM_VAR_NO_INIT) BswM_ComIPduGroupState;
VAR(Com_IpduGroupVector, BSWM_VAR_NO_INIT) BswM_ComRxIPduGroupDMState;
VAR(uint8, BSWM_VAR_NO_INIT) BswM_PduGroupControlInvocation;


#define BSWM_STOP_SEC_VAR_NO_INIT
#include "BswM_MemMap.h"

#define BSWM_START_SEC_VAR_INIT
#include "BswM_MemMap.h"

#if( BSWM_SIZE_RULE > 0U )
VAR(uint8, BSWM_VAR_INIT) BswM_RuleStates[BSWM_SIZE_RULE] =
{
	TRUE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
};
#endif


#if( BSWM_SIZE_ACTIONLIST > 0U )
VAR(BswM_ActionListState_st, BSWM_VAR_INIT) BswM_ActionListQueue[BSWM_SIZE_ACTIONLIST] = 
{
	{ 3U, BSWM_ACTIONLIST_IDLE },
	{ 3U, BSWM_ACTIONLIST_IDLE },
	{ 3U, BSWM_ACTIONLIST_IDLE },
	{ 3U, BSWM_ACTIONLIST_IDLE },
	{ 3U, BSWM_ACTIONLIST_IDLE },
	{ 3U, BSWM_ACTIONLIST_IDLE },
	{ 3U, BSWM_ACTIONLIST_IDLE },
};
#endif


#if( BSWM_SIZE_IMMEDIATE_USER > 0U )
VAR(BswM_ModeRequest_st, BSWM_VAR_INIT) BswM_ModeRequestQueue[BSWM_SIZE_IMMEDIATE_USER] = 
{
	{ 3U, BSWM_REQUEST_IDLE },
};
#endif

#if( BSWM_SIZE_TIMER > 0U )
VAR(BswM_TimerValue_st, BSWM_VAR_INIT) BswM_TimerState[BSWM_SIZE_TIMER] = 
{
	{ 3U, BSWM_TIMER_STOPPED,  0U},
	{ 3U, BSWM_TIMER_STOPPED,  0U},
	{ 3U, BSWM_TIMER_STOPPED,  0U},
};
#endif

#if( BSWM_BSWMCONFIG_SIZE > 0U)
VAR(BswM_InitState_st, BSWM_VAR_INIT) BswM_Initialized[BSWM_BSWMCONFIG_SIZE] = 
{
	{ 3U, FALSE},
};
#endif


#define BSWM_STOP_SEC_VAR_INIT
#include "BswM_MemMap.h"
/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define BSWM_START_SEC_CONFIG_DATA
#include "BswM_MemMap.h"

/* BswM/BswMConfigs/BswMConfig/BswMModeControl/BswMActionLists */
CONST(BswM_ActionListsType, BSWM_CONFIG_DATA) BswM_ActionLists[BSWM_SIZE_ACTIONLIST] = 
{
	{ BswM_ActionList_ESH_AL_InitToWakeUp },
	{ BswM_ActionList_ESH_AL_WakeUpToRun },
	{ BswM_ActionList_ESH_AL_RunToPostRun },
	{ BswM_ActionList_ESH_AL_PostRunToPreShutDown },
	{ BswM_ActionList_ESH_AL_PreShutDownToWaitforNvm },
	{ BswM_ActionList_ESH_AL_WaitForNvmToShutDown },
	{ BswM_ActionList_ESH_AL_WaitForNvmToWakeUp },
};

/* /AUTOSAR/EcucDefs/BswM/BswMConfig/BswMArbitration/BswMRule */
CONST(BswM_RulesType, BSWM_CONFIG_DATA) BswM_Rules[BSWM_SIZE_RULE] = 
{
	{ BswM_Rule_ESH_InitToWakeUp },
	{ BswM_Rule_ESH_WakeUpToRun },
	{ BswM_Rule_ESH_RunToPostRun },
	{ BswM_Rule_ESH_PostRunToPreShutDown },
	{ BswM_Rule_ESH_PreShutDownToWaitForNvm },
	{ BswM_Rule_ESH_WaitForNvmToShutDown },
	{ BswM_Rule_ESH_WaitForNvmToWakeup },
};

/* /AUTOSAR/EcucDefs/BswM/BswMConfig/BswMArbitration/BswMRule Not BswMNestedExecutionOnly */
CONST(uint8, BSWM_CONFIG_DATA) BswM_RulesInd[BSWM_SIZE_RULEIND] = 
{
	0U,
	1U,
	2U,
	3U,
	4U,
	5U,
	6U,
};

/* Contains all immediate request ports. */
CONST(BswM_ImmediateUserType, BSWM_CONFIG_DATA) BswM_ImmediateUser[BSWM_SIZE_IMMEDIATE_USER] = 
{
	{ 0x03U, 6U, 0U },
};

/* Maps the external id of BswMCanSMIndication to an internal id and references immediate request ports. */
#if( BSWM_SIZE_CANSM_CHANNEL > 0U )
CONST(BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_CanSMChannelMapping[BSWM_SIZE_CANSM_CHANNEL] = 
{
};
#endif

#if( BSWM_SIZE_ECUM_WAKEUP > 0U )
CONST(BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_EcuMWakeUpMapping[BSWM_SIZE_ECUM_WAKEUP] = 
{
};
#endif

#if( BSWM_SIZE_ECUM_CHANNEL > 0U )
CONST(BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_EcuMChannelMapping[BSWM_SIZE_ECUM_CHANNEL] = 
{
};
#endif

#if( BSWM_SIZE_DCM_CHANNEL > 0U )
CONST(BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_DcmChannelMapping[BSWM_SIZE_DCM_CHANNEL] = 
{
};
#endif

/* /AUTOSAR/EcucDefs/BswM/BswMConfig/BswMArbitration/BswMModeRequestPort/BswMModeRequestSource */
#if( BSWM_SIZE_SDCLIENTSERVICE > 0U )
CONST(BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_SdClientServiceMapping[BSWM_SIZE_SDCLIENTSERVICE] = 
{
};
#endif

/* /AUTOSAR/EcucDefs/BswM/BswMConfig/BswMArbitration/BswMModeRequestPort/BswMModeRequestSource */
#if( BSWM_SIZE_CONSUMEDEVENTGROUP > 0U )
CONST(BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_SdConsumedEventGroupMapping[BSWM_SIZE_CONSUMEDEVENTGROUP] = 
{
};
#endif
/* /AUTOSAR/EcucDefs/BswM/BswMConfig/BswMArbitration/BswMModeRequestPort/BswMModeRequestSource/BswMSdEventHandlerCurrentState */
#if( BSWM_SIZE_EVENTHANDLER > 0U )
CONST(BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_SdEventHandlerMapping[BSWM_SIZE_EVENTHANDLER] = 
{
};
#endif
/* Maps the external id of BswMComMIndication to an internal id and references immediate request ports. */
#if( BSWM_SIZE_COMM_CHANNEL > 0U )
CONST(BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_ComMChannelMapping[BSWM_SIZE_COMM_CHANNEL] = 
{
	{ 0, BSWM_NO_IMMEUSER, BSWM_NO_IMMEUSER, 3U, COMM_NO_COMMUNICATION },
	{ 1, BSWM_NO_IMMEUSER, BSWM_NO_IMMEUSER, 3U, COMM_NO_COMMUNICATION },
	{ 2, BSWM_NO_IMMEUSER, BSWM_NO_IMMEUSER, 3U, COMM_NO_COMMUNICATION },
	{ 3, BSWM_NO_IMMEUSER, BSWM_NO_IMMEUSER, 3U, COMM_NO_COMMUNICATION },
};
#endif

/* Maps the external id of BswMComMPncRequest to an internal id and references immediate request ports. */
#if( BSWM_SIZE_COMMPNC_CHANNEL > 0U )
CONST( BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_ComMPncChannelMapping[BSWM_SIZE_COMMPNC_CHANNEL] = 
{
};
#endif

/* Maps the external id of BswMEthSMIndication to an internal id and references immediate request ports. */
#if( BSWM_SIZE_ETHSM_CHANNEL > 0U )
CONST( BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_EthSMChannelMapping[BSWM_SIZE_ETHSM_CHANNEL] =
{
};
#endif

#if( BSWM_SIZE_FRSM > 0U )
CONST( BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_FrSMMapping[BSWM_SIZE_FRSM] =
{
};
#endif

#if( BSWM_SIZE_LINSMSCHEDULE > 0U )
CONST(BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_LinSMScheduleMapping[BSWM_SIZE_LINSMSCHEDULE] =
{
};
#endif

#if( BSWM_SIZE_LINSM_CHANNEL > 0U )
CONST(BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_LinSMChannelMapping[BSWM_SIZE_LINSM_CHANNEL] =
{
};
#endif

#if( BSWM_SIZE_CANSMICOM_CHANNEL > 0U )
CONST(BswM_CanSMIcomChannelMappingType, BSWM_CONFIG_DATA) BswM_CanSMIcomChannelMapping[BSWM_SIZE_CANSMICOM_CHANNEL] =
{
};
#endif

#if( BSWM_SIZE_LINTP_CHANNEL > 0U )
CONST(BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_LinTpChannelMapping[BSWM_SIZE_LINTP_CHANNEL] =
{
};
#endif

#if( BSWM_SIZE_NVM_BLOCK > 0U )
CONST(BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_NvMBlockMapping[BSWM_SIZE_NVM_BLOCK] =
{
};
#endif

#if( BSWM_SIZE_NVM_JOB > 0U )
CONST(BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_NvMJobMapping[BSWM_SIZE_NVM_JOB] =
{
	{ NVM_READ_ALL, BSWM_NO_IMMEUSER, BSWM_NO_IMMEUSER, 3U, NVM_REQ_NOT_OK },
	{ NVM_WRITE_ALL, BSWM_NO_IMMEUSER, BSWM_NO_IMMEUSER, 3U, NVM_REQ_NOT_OK },
};
#endif

#if( BSWM_SIZE_J1939DCM_CHANNEL > 0U )
CONST( BswM_ChannelMappingType, BSWM_CONFIG_DATA) BswM_J1939DcmChannelMapping[BSWM_SIZE_J1939DCM_CHANNEL] = 
{
};
#endif

#if( BSWM_SIZE_J1939NM_CHANNEL > 0U )
CONST( BswM_J1939NmStateChangeMappingType, BSWM_CONFIG_DATA) BswM_J1939NmChannelMapping[BSWM_SIZE_J1939NM_CHANNEL] = 
{
};
#endif

#if( BSWM_SIZE_DEFERRED_RULE > 0U )
/* BswM_DeferredRules */
CONST(BswM_DeferredRulesType, BSWM_CONFIG_DATA) BswM_DeferredRules[BSWM_SIZE_DEFERRED_RULE] = 
{
	{ 3U, 2U },
	{ 3U, 5U },
	{ 3U, 6U },
};
#endif
#if( BSWM_SIZE_GENERIC > 0U )
/* Maps the external id of BswMGenericRequest to an internal id and references immediate request ports. */
CONST(BswM_GenericMappingType, BSWM_CONFIG_DATA) BswM_GenericMapping[BSWM_SIZE_GENERIC] = 
{
	{ 0, 1U, 0U, 3U, 0U, BSWM_GENERICVALUE_ESH_State_Init },
	{ 1, BSWM_NO_IMMEUSER, BSWM_NO_IMMEUSER, 3U, 0U, BSWM_GENERICVALUE_ESH_ModeWakeUpEventValid },
};
#endif

#if( BSWM_MULTIPARTITION == STD_ON )
CONST(BswM_ApplMapping_st, BSWM_CONFIG_DATA) BswM_ApplMapping[BSWM_BSWMCONFIG_SIZE] = 
{
    {3U, 1U, &BswM_PartApplMapping0[0]}
};
CONST(BswM_CoreIdMapping_st, BSWM_CONFIG_DATA) BswM_CoreIdMapping[BSWM_COREIDMAPPING_SIZE] = 
{
    {0U, (CoreIdType)0U}
};
CONST(uint8, BSWM_CONFIG_DATA) BswM_PartApplMapping0[1] = {0U};
#endif

#define BSWM_STOP_SEC_CONFIG_DATA
#include "BswM_MemMap.h"

#define BSWM_START_SEC_CODE
#include "BswM_MemMap.h"
#if( BSWM_RULEHANDLERENABLE == STD_ON )
/*
********************************************************************************
* Function Name:   BswM_Action_RuleHandler
*
* Explanation: BswM_Action_RuleHandler
*
* param:    handleId: id of rule
*
* retval:   void
********************************************************************************
*/
static FUNC(Std_ReturnType, BSWM_CODE) BswM_Action_RuleHandler(uint8 handleId)
{
    uint8 actionListIndex;
    Std_ReturnType retVal = E_NOT_OK;

    actionListIndex = BswM_Rules[handleId].FctPtrOfRules();
    if( actionListIndex < BSWM_SIZE_ACTIONLIST )
    {
        retVal = BswM_ActionLists[actionListIndex].FctPtrOfActionLists();
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif
/*
********************************************************************************
* Function Name:   BswM_UpdateTimer
*
* Explanation: BswM_UpdateTimer
*
* param:    timerId: id of timer
*           value: value of timer
*
* retval:   void
********************************************************************************
*/
#if( BSWM_SIZE_TIMER > BSWM_ZERO )
LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_UpdateTimer
(
    uint8 timerId,
    uint32 value
)
{
    if( timerId < BSWM_SIZE_TIMER )
    {
        BswM_TimerState[timerId].Timevalue = value;

        if( BSWM_ZERO == value )
        {
            BswM_TimerState[timerId].Timestate = BSWM_TIMER_STOPPED;
        }
        else
        {
            BswM_TimerState[timerId].Timestate = BSWM_TIMER_STARTED;
        }
    }

    return;
}
#endif
/*
********************************************************************************
* Function Name: BswM_ExecuteIpduGroupControl
*
* Explanation: BswM_ExecuteIpduGroupControl
*
* param: void
*
* retval: void
********************************************************************************
*/
FUNC(void, BSWM_CODE) BswM_ExecuteIpduGroupControl(void)
{
    Com_IpduGroupVector ipduGroupState;
    Com_IpduGroupVector dmState;
    uint16 iCnt;
    uint8 controlInvocation = BSWM_GROUPCONTROL_IDLE;
    
    if(BswM_PduGroupControlInvocation != BSWM_GROUPCONTROL_IDLE)
    {
        if((BswM_PduGroupControlInvocation & BSWM_GROUPCONTROL_NORMAL) != 0u)
        {
            iCnt = COM_PDUGRP_VECTOR_SIZE;
            while(iCnt-- > (uint16)0x0000)
            {
                ipduGroupState[iCnt] = BswM_ComIPduGroupState[iCnt];
            }
        }

        if((BswM_PduGroupControlInvocation & BSWM_GROUPCONTROL_DM) != 0u)
        {
            iCnt = COM_PDUGRP_VECTOR_SIZE;
            while(iCnt-- > (uint16)0x0000)
            {
                dmState[iCnt] = BswM_ComRxIPduGroupDMState[iCnt];
            }
        }

        controlInvocation = BswM_PduGroupControlInvocation;
        BswM_PduGroupControlInvocation = BSWM_GROUPCONTROL_IDLE;
    }

    if(controlInvocation != BSWM_GROUPCONTROL_IDLE)
    {
        if((controlInvocation & BSWM_GROUPCONTROL_NORMAL) != 0u)
        {
            Com_IpduGroupControl(ipduGroupState, FALSE);
        }
        if((controlInvocation & BSWM_GROUPCONTROL_DM) != 0u)
        {
            Com_ReceptionDMControl(dmState);
        }
    }

}

static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_InitToWakeUp(void)
{
	 BswM_Dcm_Init();
	 BswM_Fee_Init();
	 BswM_NvM_Init();
	 BswM_Init_Nvm_Read_All();
	 BswM_XcpInit();
	 BswM_CanIf_Init();
	 BswM_CanTrcv_Init();
	 BswM_CanSM_Init();
	 BswM_CanNm_Init();
	 BswM_CanTp_Init();
	 BswM_Com_Init();
	 BswM_ComM_Init();
	 BswM_PduR_Init();
	 BswM_J1939Tp_Init();
	 BswM_CDS_Init();
	 BswM_ComMRequestFullComMode();
	BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_WakeUp);

    return E_OK;
}

static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WakeUpToRun(void)
{
	 BswM_Dem_Init();
	ComM_CommunicationAllowed(0, (TRUE));
	ComM_CommunicationAllowed(1, (TRUE));
	ComM_CommunicationAllowed(2, (TRUE));
	ComM_CommunicationAllowed(3, (TRUE));
	BswM_SetIpduGroup(0, TRUE);
	BswM_MarkPduGroupControlInvocation(BSWM_GROUPCONTROL_NORMAL);
	BswM_SetIpduGroup(1, TRUE);
	BswM_MarkPduGroupControlInvocation(BSWM_GROUPCONTROL_NORMAL);
	BswM_SetIpduGroup(2, TRUE);
	BswM_MarkPduGroupControlInvocation(BSWM_GROUPCONTROL_NORMAL);
	BswM_SetIpduGroup(3, TRUE);
	BswM_MarkPduGroupControlInvocation(BSWM_GROUPCONTROL_NORMAL);
	BswM_SetIpduGroup(4, TRUE);
	BswM_MarkPduGroupControlInvocation(BSWM_GROUPCONTROL_NORMAL);
	BswM_SetIpduGroup(5, TRUE);
	BswM_MarkPduGroupControlInvocation(BSWM_GROUPCONTROL_NORMAL);
	BswM_UpdateTimer(BSWM_TMR_ESH_Req_SelfRunReqTimer, 250);
	BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_Run);

    return E_OK;
}

static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_RunToPostRun(void)
{
	BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_PostRun);

    return E_OK;
}

static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_PostRunToPreShutDown(void)
{
	BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_PreShutDown);
	 BswM_Dcm_Shutdown();

    return E_OK;
}

static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_PreShutDownToWaitforNvm(void)
{
	BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_WaitForNvM);
	BswM_UpdateTimer(BSWM_TMR_ESH_Req_WaitforNvMTimer, 4000);
	 BswM_Init_Nvm_Write_All();

    return E_OK;
}

static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WaitForNvmToShutDown(void)
{
	BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_ShutDown);
    EcuM_SelectShutdownTarget(ECUM_STATE_OFF, 0U);
    EcuM_GoDown(0U);

    return E_OK;
}

static FUNC(Std_ReturnType, BSWM_CODE) BswM_ActionList_ESH_AL_WaitForNvmToWakeUp(void)
{
	BswM_RequestMode(BSWM_GENERIC_ESH_State, BSWM_GENERICVALUE_ESH_State_WakeUp);
	 BswM_Init_Nvm_CancelWrite_All();
	BswM_UpdateTimer(BSWM_TMR_ESH_Req_CancelWaitforNvMTimer, 2000);

    return E_OK;
}


static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_InitToWakeUp(void)
{
	uint8 retVal = BSWM_NO_ACTIONLIST;

	if (BswM_GenericState[0] == BSWM_GENERICVALUE_ESH_State_Init)
	{
		retVal = BSWM_ID_AL_ESH_AL_InitToWakeUp;
	}
	return retVal;
}

static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_WakeUpToRun(void)
{
	uint8 retVal = BSWM_NO_ACTIONLIST;

	if (BswM_GenericState[0] == BSWM_GENERICVALUE_ESH_State_WakeUp)
	{
		retVal = BSWM_ID_AL_ESH_AL_WakeUpToRun;
	}
	return retVal;
}

static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_RunToPostRun(void)
{
	uint8 retVal = BSWM_NO_ACTIONLIST;

	if ((BswM_GenericState[0] == BSWM_GENERICVALUE_ESH_State_Run) &&
	(BswM_TimerState[0].Timestate == BSWM_TIMER_EXPIRED) &&
	(BswM_ComMChannelState[1] == COMM_NO_COMMUNICATION) &&
	(BswM_GenericState[1] == BSWM_GENERICVALUE_ESH_ModeWakeUpEventInvalid))
	{
		retVal = BSWM_ID_AL_ESH_AL_RunToPostRun;
	}
	return retVal;
}

static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_PostRunToPreShutDown(void)
{
	uint8 retVal = BSWM_NO_ACTIONLIST;

	if (BswM_GenericState[0] == BSWM_GENERICVALUE_ESH_State_PostRun)
	{
		retVal = BSWM_ID_AL_ESH_AL_PostRunToPreShutDown;
	}
	return retVal;
}

static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_PreShutDownToWaitForNvm(void)
{
	uint8 retVal = BSWM_NO_ACTIONLIST;

	if (BswM_GenericState[0] == BSWM_GENERICVALUE_ESH_State_PreShutDown)
	{
		retVal = BSWM_ID_AL_ESH_AL_PreShutDownToWaitforNvm;
	}
	return retVal;
}

static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_WaitForNvmToShutDown(void)
{
	uint8 retVal = BSWM_NO_ACTIONLIST;

	if ((BswM_GenericState[0] == BSWM_GENERICVALUE_ESH_State_WaitForNvM) &&
	((BswM_TimerState[1].Timestate == BSWM_TIMER_EXPIRED) ||
	(BswM_NvMJobState[1] != NVM_REQ_PENDING)))
	{
		retVal = BSWM_ID_AL_ESH_AL_WaitForNvmToShutDown;
	}
	return retVal;
}

static FUNC(uint8, BSWM_CODE) BswM_Rule_ESH_WaitForNvmToWakeup(void)
{
	uint8 retVal = BSWM_NO_ACTIONLIST;

	if ((BswM_GenericState[0] == BSWM_GENERICVALUE_ESH_State_WaitForNvM) &&
	(BswM_GenericState[1] == BSWM_GENERICVALUE_ESH_ModeWakeUpEventValid))
	{
		retVal = BSWM_ID_AL_ESH_AL_WaitForNvmToWakeUp;
	}
	return retVal;
}



#if( BSWM_SWCMODEREQUEST_DATA_INIT == STD_ON )
FUNC(void, BSWM_CODE) BswM_SwcModeRequestDataInit
(
    uint8 partitionId
)
{
    BSWM_DUMMY_STATEMENT(partitionId);
}
#endif

#define BSWM_STOP_SEC_CODE
#include "BswM_MemMap.h"

