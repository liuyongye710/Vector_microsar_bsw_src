/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Os
 *           Program: MSR_Vector_SLP4
 *          Customer: China FAW Group Corporation
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC297TA
 *    License Scope : The usage is restricted to CBD1600956_D02
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_Alarm_Lcfg.c
 *   Generation Time: 2020-07-28 16:23:22
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_ALARM_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Alarm_Lcfg.h"
#include "Os_Alarm.h"

/* Os kernel module dependencies */
#include "Os_Application_Lcfg.h"
#include "Os_Cfg.h"
#include "Os_Common.h"
#include "Os_Counter_Lcfg.h"
#include "Os_Counter.h"
#include "Os_Task_Lcfg.h"
#include "Os_Timer.h"

/* Os hal dependencies */


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic alarm data: Rte_Al_TE2_TaskSchM_Core0_0_10ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE2_TaskSchM_Core0_0_10ms_Dyn;

/*! Dynamic alarm data: Rte_Al_TE2_TaskSchM_Core0_0_20ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE2_TaskSchM_Core0_0_20ms_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1000ms_Core0 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1000ms_Core0_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable100ms_Core0 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable100ms_Core0_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable10ms_Core0 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable10ms_Core0_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1ms_Core0 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1ms_Core0_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable200ms_Core0 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable200ms_Core0_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable20ms_Core0 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable20ms_Core0_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable500ms_Core0 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable500ms_Core0_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable50ms_Core0 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable50ms_Core0_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable5ms_Core0 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable5ms_Core0_Dyn;

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic alarm data: Rte_Al_TE2_EcuM_EcuM_MainFunction */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE2_EcuM_EcuM_MainFunction_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1000ms_Core1 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1000ms_Core1_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable100ms_Core1 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable100ms_Core1_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable10ms_Core1 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable10ms_Core1_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1ms_Core1 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1ms_Core1_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable200ms_Core1 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable200ms_Core1_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable20ms_Core1 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable20ms_Core1_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable500ms_Core1 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable500ms_Core1_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable50ms_Core1 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable50ms_Core1_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable5ms_Core1 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable5ms_Core1_Dyn;

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic alarm data: Rte_Al_TE3_EcuM_EcuM_MainFunction */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE3_EcuM_EcuM_MainFunction_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1000ms_Core2 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1000ms_Core2_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable100ms_Core2 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable100ms_Core2_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable10ms_Core2 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable10ms_Core2_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1ms_Core2 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1ms_Core2_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable200ms_Core2 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable200ms_Core2_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable20ms_Core2 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable20ms_Core2_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable500ms_Core2 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable500ms_Core2_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable50ms_Core2 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable50ms_Core2_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable5ms_Core2 */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable5ms_Core2_Dyn;

#define OS_STOP_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Alarm configuration data: Rte_Al_TE2_TaskSchM_Core0_0_10ms */
CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_TaskSchM_Core0_0_10ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE2_TaskSchM_Core0_0_10ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core0),
      /* .Callback = */ Os_AlarmActionSetEvent
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0
  },
  /* .Task  = */ &OsCfg_Task_TaskSchM_Core0,
  /* .Mask  = */ Rte_Ev_Cyclic2_TaskSchM_Core0_0_10ms
};

/*! Alarm configuration data: Rte_Al_TE2_TaskSchM_Core0_0_20ms */
CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_TaskSchM_Core0_0_20ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE2_TaskSchM_Core0_0_20ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core0),
      /* .Callback = */ Os_AlarmActionSetEvent
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0
  },
  /* .Task  = */ &OsCfg_Task_TaskSchM_Core0,
  /* .Mask  = */ Rte_Ev_Cyclic2_TaskSchM_Core0_0_20ms
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1000ms_Core0 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1000ms_Core0 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1000ms_Core0_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core0),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0
  },
  /* .Task  = */ &OsCfg_Task_Task1000ms_Core0
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable100ms_Core0 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable100ms_Core0 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable100ms_Core0_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core0),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0
  },
  /* .Task  = */ &OsCfg_Task_Task100ms_Core0
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable10ms_Core0 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable10ms_Core0 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable10ms_Core0_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core0),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0
  },
  /* .Task  = */ &OsCfg_Task_Task10ms_Core0
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1ms_Core0 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1ms_Core0 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1ms_Core0_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core0),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0
  },
  /* .Task  = */ &OsCfg_Task_Task1ms_Core0
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable200ms_Core0 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable200ms_Core0 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable200ms_Core0_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core0),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0
  },
  /* .Task  = */ &OsCfg_Task_Task200ms_Core0
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable20ms_Core0 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable20ms_Core0 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable20ms_Core0_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core0),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0
  },
  /* .Task  = */ &OsCfg_Task_Task20ms_Core0
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable500ms_Core0 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable500ms_Core0 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable500ms_Core0_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core0),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0
  },
  /* .Task  = */ &OsCfg_Task_Task500ms_Core0
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable50ms_Core0 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable50ms_Core0 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable50ms_Core0_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core0),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0
  },
  /* .Task  = */ &OsCfg_Task_Task50ms_Core0
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable5ms_Core0 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable5ms_Core0 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable5ms_Core0_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core0),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0
  },
  /* .Task  = */ &OsCfg_Task_Task5ms_Core0
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Alarm configuration data: Rte_Al_TE2_EcuM_EcuM_MainFunction */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_EcuM_EcuM_MainFunction =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE2_EcuM_EcuM_MainFunction_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core1),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1
  },
  /* .Task  = */ &OsCfg_Task_TaskSchM_Core1
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1000ms_Core1 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1000ms_Core1 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1000ms_Core1_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core1),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1
  },
  /* .Task  = */ &OsCfg_Task_Task1000ms_Core1
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable100ms_Core1 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable100ms_Core1 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable100ms_Core1_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core1),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1
  },
  /* .Task  = */ &OsCfg_Task_Task100ms_Core1
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable10ms_Core1 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable10ms_Core1 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable10ms_Core1_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core1),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1
  },
  /* .Task  = */ &OsCfg_Task_Task10ms_Core1
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1ms_Core1 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1ms_Core1 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1ms_Core1_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core1),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1
  },
  /* .Task  = */ &OsCfg_Task_Task1ms_Core1
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable200ms_Core1 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable200ms_Core1 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable200ms_Core1_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core1),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1
  },
  /* .Task  = */ &OsCfg_Task_Task200ms_Core1
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable20ms_Core1 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable20ms_Core1 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable20ms_Core1_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core1),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1
  },
  /* .Task  = */ &OsCfg_Task_Task20ms_Core1
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable500ms_Core1 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable500ms_Core1 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable500ms_Core1_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core1),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1
  },
  /* .Task  = */ &OsCfg_Task_Task500ms_Core1
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable50ms_Core1 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable50ms_Core1 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable50ms_Core1_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core1),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1
  },
  /* .Task  = */ &OsCfg_Task_Task50ms_Core1
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable5ms_Core1 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable5ms_Core1 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable5ms_Core1_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core1),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1
  },
  /* .Task  = */ &OsCfg_Task_Task5ms_Core1
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Alarm configuration data: Rte_Al_TE3_EcuM_EcuM_MainFunction */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE3_EcuM_EcuM_MainFunction =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE3_EcuM_EcuM_MainFunction_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core2),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2
  },
  /* .Task  = */ &OsCfg_Task_TaskSchM_Core2
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1000ms_Core2 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1000ms_Core2 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1000ms_Core2_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core2),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2
  },
  /* .Task  = */ &OsCfg_Task_Task1000ms_Core2
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable100ms_Core2 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable100ms_Core2 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable100ms_Core2_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core2),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2
  },
  /* .Task  = */ &OsCfg_Task_Task100ms_Core2
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable10ms_Core2 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable10ms_Core2 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable10ms_Core2_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core2),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2
  },
  /* .Task  = */ &OsCfg_Task_Task10ms_Core2
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1ms_Core2 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1ms_Core2 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1ms_Core2_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core2),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2
  },
  /* .Task  = */ &OsCfg_Task_Task1ms_Core2
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable200ms_Core2 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable200ms_Core2 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable200ms_Core2_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core2),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2
  },
  /* .Task  = */ &OsCfg_Task_Task200ms_Core2
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable20ms_Core2 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable20ms_Core2 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable20ms_Core2_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core2),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2
  },
  /* .Task  = */ &OsCfg_Task_Task20ms_Core2
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable500ms_Core2 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable500ms_Core2 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable500ms_Core2_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core2),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2
  },
  /* .Task  = */ &OsCfg_Task_Task500ms_Core2
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable50ms_Core2 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable50ms_Core2 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable50ms_Core2_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core2),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2
  },
  /* .Task  = */ &OsCfg_Task_Task50ms_Core2
};

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable5ms_Core2 */
CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable5ms_Core2 =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable5ms_Core2_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core2),
      /* .Callback = */ Os_AlarmActionActivateTask
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0UL, /* 0.0 sec */
      /* .Cycle            = */ 0UL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2
  },
  /* .Task  = */ &OsCfg_Task_Task5ms_Core2
};

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for alarms. */
CONSTP2CONST(Os_AlarmConfigType, OS_CONST, OS_CONST) OsCfg_AlarmRefs[OS_ALARMID_COUNT + 1] =
{
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE2_EcuM_EcuM_MainFunction),
  OS_ALARM_CASTCONFIG_ALARMSETEVENT_2_ALARM(OsCfg_Alarm_Rte_Al_TE2_TaskSchM_Core0_0_10ms),
  OS_ALARM_CASTCONFIG_ALARMSETEVENT_2_ALARM(OsCfg_Alarm_Rte_Al_TE2_TaskSchM_Core0_0_20ms),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE3_EcuM_EcuM_MainFunction),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1000ms_Core0),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable100ms_Core0),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable10ms_Core0),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1ms_Core0),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable200ms_Core0),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable20ms_Core0),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable500ms_Core0),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable50ms_Core0),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable5ms_Core0),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1000ms_Core1),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable100ms_Core1),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable10ms_Core1),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1ms_Core1),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable200ms_Core1),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable20ms_Core1),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable500ms_Core1),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable50ms_Core1),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable5ms_Core1),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1000ms_Core2),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable100ms_Core2),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable10ms_Core2),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1ms_Core2),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable200ms_Core2),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable20ms_Core2),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable500ms_Core2),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable50ms_Core2),
  OS_ALARM_CASTCONFIG_ALARMACTIVATETASK_2_ALARM(OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable5ms_Core2),
  NULL_PTR
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  END OF FILE: Os_Alarm_Lcfg.c
 *********************************************************************************************************************/
