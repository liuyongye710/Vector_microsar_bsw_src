/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 * 
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Rtm.c
 *      Project:  -
 *       Module:  RTM
 *    Generator:  -
 *
 *  Description:  This file provides functions and data for runtime measurements in the scope of RTM
 *  
 *********************************************************************************************************************/

#define RTM_SOURCE
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Rtm.h"

/*lint -e438 */ /* Suppress ID438 because value assigned to variable is not required */
/*lint -e550 */ /* Suppress ID550 because symbol is not required */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* vendor specific version information is BCD coded */
#if (  (RTM_SW_MAJOR_VERSION != (0x07u)) \
    || (RTM_SW_MINOR_VERSION != (0x03u)) \
    || (RTM_SW_PATCH_VERSION != (0x00u)) ) /* COV_RTM_MSR_CONFIG */
# error "Vendor specific version numbers of Rtm.c and Rtm.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

#if (RTM_MULTICORE_SUPPORT == STD_ON)
# define RTM_CPU_LOAD_MEASUREMENT_ID (0x00u)
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

#if (RTM_USE_32BIT_TIMER == STD_ON) && (RTM_MULTICORE_SUPPORT == STD_ON)
# define Rtm_FixTypeMismatch(word) (word) = ((word) >> 1u) /* PRQA S 3453  */  /* MD_MSR_FctLikeMacro */
#else
# define Rtm_FixTypeMismatch(word)
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

# define RTM_START_SEC_VAR_INIT_UNSPECIFIED_SAFE
# include "Rtm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# if (RTM_CONTROL == STD_ON)
VAR(uint8, RTM_VAR_INIT)                          Rtm_ControlState = RTM_CONTROL_STATE_ENABLED; /* = 1 */
# endif

# define RTM_STOP_SEC_VAR_INIT_UNSPECIFIED_SAFE
# include "Rtm_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */


# define RTM_START_SEC_VAR_INIT_UNSPECIFIED
# include "Rtm_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

# if (RTM_NET_RUNTIME_SUPPORT == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
VAR(uint32, RTM_VAR_INIT)                         Rtm_ActiveThreadId = RTM_NUMBER_OF_THREADS;
# endif

# define RTM_STOP_SEC_VAR_INIT_UNSPECIFIED
# include "Rtm_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */


# define RTM_START_SEC_VAR_CLEARED_8
# include "Rtm_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

# if (RTM_CONTROL == STD_ON)
VAR(uint8, RTM_VAR_CLEARED)                       Rtm_ControlDeniedCount = 0u; /*lint -e552 */ /* Suppress ID552 */
# endif

# if (RTM_TIMER_OVERRUN_SUPPORT == STD_ON)
VAR(uint8, RTM_VAR_CLEARED)                       Rtm_TimerOverrunCnt = 0u;
# endif

# define RTM_STOP_SEC_VAR_CLEARED_8
# include "Rtm_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */


# define RTM_START_SEC_VAR_CLEARED_UNSPECIFIED
# include "Rtm_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

# if (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
RTM_LOCAL VAR(Rtm_OverheadCorrectionType, RTM_VAR_CLEARED) Rtm_OverheadCorrection = { 0u, 0u }; /* PRQA S 3408 */  /* MD_Rtm_3408 */ /*lint -e552 */ /* Suppress ID552 */
# endif

# if (RTM_TIMER_OVERRUN_SUPPORT == STD_ON)
VAR(Rtm_MeasurementTimestampType, RTM_VAR_CLEARED) Rtm_PrevTimerValue = 0u;
# endif

# define RTM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# include "Rtm_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */


# define RTM_START_SEC_VAR_NO_INIT_UNSPECIFIED
# include "Rtm_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

# if (RTM_TASK_STACK_USAGE == STD_ON)
VAR(Rtm_MaxTaskStackUsageType, RTM_VAR_NO_INIT)    Rtm_MaxTaskStackUsage[RTM_NUMBER_OF_TASKS]; /* PRQA S 1514 */ /* MD_Rtm_1514 */
# endif

#if (RTM_TIME_MEASUREMENT == STD_ON)
RTM_LOCAL VAR(uint32, RTM_VAR_NO_INIT)             Rtm_LastCommandToEcu; /* PRQA S 3408 */  /* MD_Rtm_3408 */
RTM_LOCAL VAR(Rtm_TimestampType, RTM_VAR_NO_INIT)  Rtm_MeasurementTimer; /* PRQA S 3408 */  /* MD_Rtm_3408 */
RTM_LOCAL VAR(Rtm_TimestampType, RTM_VAR_NO_INIT)  Rtm_CalculatedCtrEndVal; /* PRQA S 3408 */  /* MD_Rtm_3408 */

# if (RTM_XCP_IS_PRESENT == STD_ON)
#  if (RTM_MULTICORE_SUPPORT == STD_ON)
VAR(uint8, RTM_VAR_NO_INIT)                        Rtm_XcpState; /*lint -e552 */ /* Suppress ID552 */
#  else
RTM_LOCAL VAR(uint8, RTM_VAR_NO_INIT)              Rtm_XcpState; /* PRQA S 3408 */  /* MD_Rtm_3408 */
#  endif
# endif

VAR(uint32, RTM_VAR_NO_INIT)                       Rtm_Cmd; /*lint -e552 */ /* Suppress ID552 */
VAR(uint32, RTM_VAR_NO_INIT)                       Rtm_Resp; /*lint -e552 */ /* Suppress ID552 */
VAR(sint32, RTM_VAR_NO_INIT)                       Rtm_MeasTimeCorrection; /*lint -e552 */ /* Suppress ID552 */

VAR(uint32, RTM_VAR_NO_INIT)                       Rtm_AverageMainFunctionCycleTime;
VAR(uint32, RTM_VAR_NO_INIT)                       Rtm_MainFunctionCounter;

# if (RTM_TIMER_OVERRUN_SUPPORT == STD_ON)
VAR(uint8, RTM_VAR_NO_INIT)                        Rtm_GetCurrentTimeCnt;
# endif

# if (RTM_NET_RUNTIME_SUPPORT == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
RTM_LOCAL VAR(Rtm_TaskType, RTM_VAR_NO_INIT)       Rtm_TaskIndex[RTM_NUMBER_OF_TASKS]; /* PRQA S 3408 */  /* MD_Rtm_3408 */
# endif

# if (RTM_MULTICORE_SUPPORT == STD_ON)
VAR(uint8, RTM_VAR_NO_INIT)                        Rtm_SendNextMainFunction;

# else
RTM_LOCAL VAR(uint8, RTM_VAR_NO_INIT)              Rtm_LiveMeasurement; /* PRQA S 3408 */  /* MD_Rtm_3408 */
# endif

RTM_LOCAL VAR(uint8, RTM_VAR_NO_INIT)              Rtm_EndlessMeasurement; /* PRQA S 3408 */  /* MD_Rtm_3408 */
RTM_LOCAL VAR(uint32, RTM_VAR_NO_INIT)             Rtm_LastMainFunctionTime; /* PRQA S 3408 */  /* MD_Rtm_3408 */
RTM_LOCAL VAR(uint32, RTM_VAR_NO_INIT)             Rtm_AvgMainFunctionCycleTimeCalcCounter; /* PRQA S 3408 */  /* MD_Rtm_3408 */
#endif /* (RTM_TIME_MEASUREMENT == STD_ON) */

# define RTM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
# include "Rtm_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/* ESCAN00080430 */
#define RTM_START_SEC_CODE
#include "Rtm_MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#if (RTM_TIME_MEASUREMENT == STD_ON)
/**********************************************************************************************************************
 *   HH      HH  EEEEEEEEEE  LL          PPPPPPPP    EEEEEEEEEE  RRRRRRRR
 *   HH      HH  EE          LL          PP      PP  EE          RR      RR
 *   HH      HH  EE          LL          PP      PP  EE          RR      RR
 *   HHHHHHHHHH  EEEEEEEE    LL          PPPPPPPP    EEEEEEEE    RRRRRRRR
 *   HH      HH  EE          LL          PP          EE          RR    RRR
 *   HH      HH  EE          LL          PP          EE          RR      RR
 *   HH      HH  EEEEEEEEEE  LLLLLLLLLL  PP          EEEEEEEEEE  RR      RR
 *********************************************************************************************************************/

# if (RTM_MULTICORE_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead()
 *********************************************************************************************************************/
/*! \brief       Calculates the overhead introduced by RTM's macros Rtm_Start and Rtm_Stop.
 *  \details     Calculates the runtime of all variants of macros Rtm_Start and Rtm_Stop.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and RTM_MULTICORE_SUPPORT == STD_OFF.
 *  \pre         -
 *  \ingroup     helper
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead(void);

/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead_GrossExecutionTime_EnableISR()
 *********************************************************************************************************************/
/*! \brief       Calculates the overhead of MPs measuring gross execution time with interrupts enabled.
 *  \details     Calculates the runtime of the macros Rtm_Start and Rtm_Stop.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and RTM_MULTICORE_SUPPORT == STD_OFF.
 *  \pre         -
 *  \ingroup     helper
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead_GrossExecutionTime_EnableISR(void);

/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead_GrossExecutionTime_DisableISR()
 *********************************************************************************************************************/
/*! \brief       Calculates the overhead of MPs measuring gross execution time with interrupts disabled.
 *  \details     Calculates the runtime of the macros Rtm_Start and Rtm_Stop.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and RTM_MULTICORE_SUPPORT == STD_OFF.
 *  \pre         -
 *  \ingroup     helper
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead_GrossExecutionTime_DisableISR(void);

#  if (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead_NetExecutionTime_EnableISR()
 *********************************************************************************************************************/
/*! \brief       Calculates the overhead of MPs measuring net executing time with interrupts enabled.
 *  \details     Calculates the runtime of the macros Rtm_Start and Rtm_Stop.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and 
 *               RTM_MULTICORE_SUPPORT == STD_OFF and
 *               RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON.
 *  \pre         -
 *  \ingroup     helper
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead_NetExecutionTime_EnableISR(void);

/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead_NetExecutionTime_DisableISR()
 *********************************************************************************************************************/
/*! \brief       Calculates the overhead of MPs measuring net executing time with interrupts disabled.
 *  \details     Calculates the runtime of the macros Rtm_Start and Rtm_Stop.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and 
 *               RTM_MULTICORE_SUPPORT == STD_OFF and
 *               RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON.
 *  \pre         -
 *  \ingroup     helper
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead_NetExecutionTime_DisableISR(void);
#  endif

#  if (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead_FlatExecutionTime_EnableISR()
 *********************************************************************************************************************/
/*! \brief       Calculates the overhead of MPs measuring flat executing time with interrupts enabled.
 *  \details     Calculates the runtime of the macros Rtm_Start and Rtm_Stop.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and 
 *               RTM_MULTICORE_SUPPORT == STD_OFF and
 *               RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON.
 *  \pre         -
 *  \ingroup     helper
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead_FlatExecutionTime_EnableISR(void);

/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead_FlatExecutionTime_DisableISR()
 *********************************************************************************************************************/
/*! \brief       Calculates the overhead of MPs measuring flat executing time with interrupts disabled.
 *  \details     Calculates the runtime of the macros Rtm_Start and Rtm_Stop.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and 
 *               RTM_MULTICORE_SUPPORT == STD_OFF and
 *               RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON.
 *  \pre         -
 *  \ingroup     helper
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead_FlatExecutionTime_DisableISR(void);
#  endif
# endif /* (RTM_MULTICORE_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 * Rtm_Hlp_SetMPStateOfAllMPs()
 *********************************************************************************************************************/
/*! \brief       Sets the MP state of all (requested) MPs.
 *  \details     Disables all MPs or enables all MPs requested by the RTM user.
 *  \param[in]   DisableAllMPs      Decides whether the MPs are disabled or set as RTM user requested.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON.
 *  \pre         -
 *  \ingroup     helper
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_SetMPStateOfAllMPs(
  boolean DisableAllMPs);


/**********************************************************************************************************************
 *     IIIIII    NN      NN    IIIIII    TTTTTTTTT
 *       II      NNN     NN      II         TT    
 *       II      NNNN    NN      II         TT    
 *       II      NN  NN  NN      II         TT    
 *       II      NN    NNNN      II         TT    
 *       II      NN     NNN      II         TT    
 *     IIIIII    NN      NN    IIIIII       TT    
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rtm_Init_PersistencyData()
 *********************************************************************************************************************/
/*! \brief       Initializes persisted data if it was not recovered from flash.
 *  \details     -
 *  \param[in]   CoreIndex           The core index on which the persistency data is checked and initialized.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON.
 *  \pre         -
 *  \ingroup     init
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_PersistencyData(
  uint16 CoreIndex);

# if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0)
/**********************************************************************************************************************
 * Rtm_Init_PersistencyDataOfCpuLoad()
 *********************************************************************************************************************/
/*! \brief       Initializes persisted data of CPU load histogram if it was not recovered from flash.
 *  \details     -
 *  \param[in]   CoreIndex           The core index on which the persistency data is checked and initialized.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and
 *               RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0.
 *  \pre         -
 *  \ingroup     init
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_PersistencyDataOfCpuLoad(
  uint16 CoreIndex);
# endif

# if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0)
/**********************************************************************************************************************
 * Rtm_Init_PersistencyDataOfTaskResponseTime()
 *********************************************************************************************************************/
/*! \brief       Initializes persisted data of TaskResponseTime histogram if it was not recovered from flash.
 *  \details     -
 *  \param[in]   CoreIndex           The core index on which the persistency data is checked and initialized.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and
 *               RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0.
 *  \pre         -
 *  \ingroup     init
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_PersistencyDataOfTaskResponseTime(
  uint16 CoreIndex);
# endif
#endif

#if (RTM_TASK_STACK_USAGE == STD_ON)
/**********************************************************************************************************************
 * Rtm_Init_PersistencyDataOfTaskStackUsage()
 *********************************************************************************************************************/
/*! \brief       Initializes persisted data of TaskStackUsage if it was not recovered from flash.
 *  \details     -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TASK_STACK_USAGE == STD_ON.
 *  \pre         -
 *  \ingroup     init
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_PersistencyDataOfTaskStackUsage(void);
#endif

#if (RTM_TIME_MEASUREMENT == STD_ON)
# if (RTM_NET_RUNTIME_SUPPORT == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 * Rtm_Init_TaskContext()
 *********************************************************************************************************************/
/*! \brief       Initializes task context related data.
 *  \details     -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and RTM_NET_RUNTIME_SUPPORT == STD_ON.
 *  \pre         -
 *  \ingroup     init
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_TaskContext(void);
# endif

# if (RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF)
/**********************************************************************************************************************
 * Rtm_Init_CpuLoadMeasurement()
 *********************************************************************************************************************/
/*! \brief       Calculates the overhead introduced by RTM's macros Rtm_Start and Rtm_Stop.
 *  \details     Calculates the runtime of the macros Rtm_Start and Rtm_Stop.
 *  \param[in]   CoreIndex         The core index on which the CPU load data is initialized.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and
 *               RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF and
 *               RTM_MULTICORE_SUPPORT == STD_OFF.
 *  \pre         -
 *  \ingroup     init
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_CpuLoadMeasurement(
  uint16 CoreIndex);

/**********************************************************************************************************************
 * Rtm_Init_ActivateCpuLoadMeasurementPointOfCoreIndex()
 *********************************************************************************************************************/
/*! \brief       Activates the CPU load MP if the autostart flag is set for it.
 *  \details     -
 *  \param[in]   CoreIndex         The core index for which the autostart flag is checked.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and
 *               RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF.
 *  \pre         -
 *  \ingroup     init
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_ActivateCpuLoadMeasurementPointOfCoreIndex(
  uint16 CoreIndex);
# endif

/**********************************************************************************************************************
 * Rtm_Init_MeasurementData()
 *********************************************************************************************************************/
/*! \brief       Initializes measurement related data.
 *  \details     -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON.
 *  \pre         -
 *  \ingroup     init
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_MeasurementData(void);

/**********************************************************************************************************************
 *   MM      MM  EEEEEEEEEE    AAAAAA      SSSSSS              CCCCCC      OOOOOO    NN      NN   TTTTTTTTT
 *   MMM    MMM  EE          AA      AA  SS      SS          CC      CC  OO      OO  NNN     NN      TT    
 *   MMMM  MMMM  EE          AA      AA  SS                  CC          OO      OO  NNNN    NN      TT    
 *   MM  MM  MM  EEEEEEEE    AAAAAAAAAA    SSSSSS    ======  CC          OO      OO  NN  NN  NN      TT    
 *   MM      MM  EE          AA      AA          SS          CC          OO      OO  NN    NNNN      TT    
 *   MM      MM  EE          AA      AA  SS      SS          CC      CC  OO      OO  NN     NNN      TT    
 *   MM      MM  EEEEEEEEEE  AA      AA    SSSSSS              CCCCCC      OOOOOO    NN      NN      TT    
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rtm_MeasCtr_MeasurementControl()
 *********************************************************************************************************************/
/*! \brief       Controls the measurement.
 *  \details     Starts, stops and proceeds measurements. Clears measurement results. Triggers response.
 *  \param[in]   CurrentTime        The time when this function is called.
 *  \param[in]   TimeToMeasure      Measurement duration.
 *  \param[in]   Command            The command to be executed.
 *  \return      FALSE              RTM data should not be transmitted.
 *  \return      TRUE               RTM data should be transmitted.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON.
 *  \pre         -
 *  \ingroup     measCtr
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_MeasurementControl(
  Rtm_MeasurementTimestampType CurrentTime,
  Rtm_TimestampType TimeToMeasure,
  uint8 Command);

# if (RTM_MULTICORE_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 * Rtm_MeasCtr_StartLiveMeasurement()
 *********************************************************************************************************************/
/*! \brief       Starts a live measurement.
 *  \details     Starts a live measurement in time-limited or endless mode.
 *  \param[in]   CurrentTime        The time when this function is called.
 *  \param[in]   TimeToMeasure      Measurement duration.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and RTM_MULTICORE_SUPPORT == STD_OFF.
 *  \pre         -
 *  \ingroup     measCtr
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_MeasCtr_StartLiveMeasurement(
  Rtm_MeasurementTimestampType CurrentTime,
  Rtm_TimestampType TimeToMeasure);

/**********************************************************************************************************************
 * Rtm_MeasCtr_ProceedLiveMeasurement()
 *********************************************************************************************************************/
/*! \brief       Proceeds with the currently running live measurement.
 *  \details     Proceeds with live measurement in time-limited and endless mode. Triggers response.
 *  \param[in]   CurrentTime        The time when this function is called.
 *  \return      FALSE              RTM data should not be transmitted.
 *  \return      TRUE               RTM data should be transmitted.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and RTM_MULTICORE_SUPPORT == STD_OFF.
 *  \pre         A live measurement must be running.
 *  \ingroup     measCtr
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_ProceedLiveMeasurement(
  Rtm_MeasurementTimestampType CurrentTime);
# endif

/**********************************************************************************************************************
 * Rtm_MeasCtr_StartSerialOrParallelMeasurement()
 *********************************************************************************************************************/
/*! \brief       Starts a serial or parallel measurement.
 *  \details     Starts a serial or parallel measurement in time-limited or endless mode. Triggers response.
 *  \param[in]   CurrentTime        The time when this function is called.
 *  \param[in]   TimeToMeasure      Measurement duration.
 *  \return      FALSE              RTM data should not be transmitted.
 *  \return      TRUE               RTM data should be transmitted.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON.
 *  \pre         -
 *  \ingroup     measCtr
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_StartSerialOrParallelMeasurement(
  Rtm_MeasurementTimestampType CurrentTime,
  Rtm_TimestampType TimeToMeasure);

/**********************************************************************************************************************
 * Rtm_MeasCtr_ProceedSerialOrParallelMeasurement()
 *********************************************************************************************************************/
/*! \brief       Proceeds with the currently running serial or parallel measurement.
 *  \details     Proceeds with measurement in time-limited and endless mode. Triggers response.
 *  \param[in]   CurrentTime        The time when this function is called.
 *  \return      FALSE              RTM data should not be transmitted.
 *  \return      TRUE               RTM data should be transmitted.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON.
 *  \pre         A serial or parallel measurement must be running.
 *  \ingroup     measCtr
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_ProceedSerialOrParallelMeasurement(
  Rtm_MeasurementTimestampType CurrentTime);

/**********************************************************************************************************************
 * Rtm_MeasCtr_StopEndlessMeasurement()
 *********************************************************************************************************************/
/*! \brief       Stops an endless measurement.
 *  \details     Stops an live, serial or parallel measurement in endless mode. Triggers response.
 *  \return      FALSE              RTM data should not be transmitted.
 *  \return      TRUE               RTM data should be transmitted.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON.
 *  \pre         An endless measurement must be running.
 *  \ingroup     measCtr
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_StopEndlessMeasurement(void);

/**********************************************************************************************************************
 * Rtm_MeasCtr_ClearMeasurementResults()
 *********************************************************************************************************************/
/*! \brief       Clears measurement results.
 *  \details     Clears all the latest measurement results.
 *  \return      FALSE              RTM data should not be transmitted.
 *  \return      TRUE               RTM data should be transmitted.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON.
 *  \pre         -
 *  \ingroup     measCtr
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_ClearMeasurementResults(void);

# if (RTM_IS_ANY_CPU_LOAD_MP_SET_TO_AUTOSTART == STD_ON)
/**********************************************************************************************************************
 * Rtm_MeasCtr_CheckAutostartCpuLoad()
 *********************************************************************************************************************/
/*! \brief       Activates all CPU load MPs if the autostart flag is set for it.
 *  \details     -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and
 *               RTM_IS_ANY_CPU_LOAD_MP_SET_TO_AUTOSTART == STD_ON.
 *  \pre         -
 *  \ingroup     init
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_CheckAutostartCpuLoad(void);
# endif

/**********************************************************************************************************************
 *     CCCCCC    PPPPPPPP    UU      UU
 *   CC      CC  PP      PP  UU      UU
 *   CC          PP      PP  UU      UU
 *   CC          PPPPPPPP    UU      UU
 *   CC          PP          UU      UU
 *   CC      CC  PP          UU      UU
 *     CCCCCC    PP            UUUUUU
 *********************************************************************************************************************/

# if (RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF)
#  if (RTM_MULTICORE_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 * Rtm_Cpu_CalculateCurrentCPULoad()
 *********************************************************************************************************************/
/*! \brief       Calculates current and cumulated measurement results of CPU load.
 *  \details     -
 *  \param[in]   CoreIndex               The core on which the CPU load is calculated.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and 
 *               RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF and
 *               RTM_MULTICORE_SUPPORT == STD_OFF.
 *  \pre         -
 *  \ingroup     cpuLoad
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Cpu_CalculateCurrentCPULoad(
  uint16 CoreIndex);
#  endif

/**********************************************************************************************************************
 * Rtm_Cpu_IsMeasurementIdValidCpuLoadMP()
 *********************************************************************************************************************/
/*! \brief       Indicates if the given MP id is a CPU load MP.
 *  \details     If valid, sets the CPU id of the given MP.
 *  \param[in]   MeasurementId       The MP to be checked.
 *  \param[out]  CoreIndex           The optionally set pointer to core index of the given MP.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \spec        requires CoreIndex != NULL_PTR;
 *  \endspec
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and 
 *               RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF.
 *  \pre         -
 *  \ingroup     cpuLoad
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(boolean, RTM_CODE) Rtm_Cpu_IsMeasurementIdValidCpuLoadMP(
  uint32 MeasurementId,
  P2VAR(uint16, AUTOMATIC, RTM_APPL_VAR) CoreIndex);
# endif

# if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0u)
/**********************************************************************************************************************
 * Rtm_CpuLoadHistogram_IsCoreIndexValidAndActive()
 *********************************************************************************************************************/
/*! \brief       Indicates if the core index is valid and if its CPU load measurement is active.
 *  \details     The core index is used to access the Rtm local structures.
 *  \param[in]   CoreIndex           The core index for which the MP is checked.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and 
 *               RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0u.
 *  \pre         -
 *  \ingroup     cpuLoad
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(boolean, RTM_CODE) Rtm_CpuLoadHistogram_IsCoreIndexValidAndActive(
  uint16 CoreIndex);
# endif

# if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0u)
/**********************************************************************************************************************
 * Rtm_CpuLoadHistogram_AvoidOverrun()
 *********************************************************************************************************************/
/*! \brief       Checks if the overall percentile counter reached its limit and reduces all percentiles and the overall
 *               percentile by same factor to avoid a counter overrun.
 *  \details     -
 *  \param[in]   CoreIndex          The core index for which the counter overrun shall be checked.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and 
 *               RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0u.
 *  \pre         -
 *  \ingroup     cpuLoad
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_CpuLoadHistogram_AvoidOverrun(
  uint16 CoreIndex);

/**********************************************************************************************************************
 * Rtm_CpuLoadHistogram_GetCoreIndexOfCoreId()
 *********************************************************************************************************************/
/*! \brief       Returns the core index for given core id.
 *  \details     - 
 *  \param[in]   CoreId             The core id for which the core index is searched.
 *  \param[out]  CoreIndex          The corresponding core index.
 *  \return      E_NOT_OK           The core id is invalid.
 *  \return      E_OK               The core id is valid.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \spec        requires CoreIndex != NULL_PTR;
 *  \endspec
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and 
 *               RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0u.
 *  \pre         -
 *  \ingroup     cpuLoad
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(Std_ReturnType, RTM_CODE) Rtm_CpuLoadHistogram_GetCoreIndexOfCoreId(
  uint16 CoreId,
  P2VAR(uint16, AUTOMATIC, RTM_APPL_VAR) CoreIndex);
# endif

/**********************************************************************************************************************
 *   TTTTTTTTTT  RRRRRRRR    TTTTTTTTTT
 *       TT      RR      RR      TT    
 *       TT      RR      RR      TT    
 *       TT      RRRRRRRR        TT    
 *       TT      RR     RR       TT    
 *       TT      RR      RR      TT    
 *       TT      RR      RR      TT    
 *********************************************************************************************************************/

# if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0u)
/**********************************************************************************************************************
 * Rtm_TaskResponseTime_AvoidOverrun()
 *********************************************************************************************************************/
/*! \brief       Checks if the overall percentile counter reached its limit and reduces all percentiles and the overall
 *               percentile by same factor to avoid a counter overrun.
 *  \details     -
 *  \param[in]   CoreIndex          The core index for which the counter overrun shall be checked.
 *  \param[in]   TaskIndex          The task index for which the counter overrun shall be checked.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and 
 *               RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0u.
 *  \pre         -
 *  \ingroup     cpuLoad
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_TaskResponseTime_AvoidOverrun(
  uint16 CoreIndex,
  uint16 TaskIndex);
# endif
#endif

#if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0u)
/**********************************************************************************************************************
 * Rtm_TaskResponseTime_GetCoreIndexAndTaskIndexOfTaskId()
 *********************************************************************************************************************/
/*! \brief       Returns the core index and the task index of given task id.
 *  \details     -
 *  \param[in]   TaskId             The task id for which the core index and task index are requested.
 *  \param[out]  CoreIndex          The core index of the given task id.
 *  \param[out]  TaskIndex          The task index of the given task id.
 *  \return      E_NOT_OK           The task id is invalid.
 *  \return      E_OK               The task id is valid.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \spec        requires CoreIndex != NULL_PTR;
 *               requires TaskIndex != NULL_PTR;
 *  \endspec
 *  \config      Available only if RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0u.
 *  \pre         -
 *  \ingroup     taskResponseTime
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_TaskResponseTime_GetCoreIndexAndTaskIndexOfTaskId(
  const uint16 TaskId,
  P2VAR(uint8, AUTOMATIC, RTM_APPL_VAR) CoreIndex,
  P2VAR(uint8, AUTOMATIC, RTM_APPL_VAR) TaskIndex);

# if (RTM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 * Rtm_TaskResponseTime_IsInitializedOnCoreOfTaskId()
 *********************************************************************************************************************/
/*! \brief       Indicates if the core specific data is already initialized.
 *  \details     The corresponding core is determined by the given task id.
 *  \param[in]   TaskId             The task id to determine the relevant core id.
 *  \return      FALSE              The core id is invalid or the core specific data is not yet initialized.
 *  \return      TRUE               The core id is valid and the core specific data is initialized.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_DEV_ERROR_DETECT == STD_ON and
 *               RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0u.
 *  \pre         -
 *  \ingroup     taskResponseTime
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(boolean, RTM_CODE) Rtm_TaskResponseTime_IsInitializedOnCoreOfTaskId(
  const uint16 TaskId);
# endif
#endif

/**********************************************************************************************************************
 *   TTTTTTTTTT    SSSSSS    UU      UU
 *       TT      SS      SS  UU      UU
 *       TT      SS          UU      UU
 *       TT        SSSSSS    UU      UU
 *       TT              SS  UU      UU
 *       TT      SS      SS  UU      UU
 *       TT        SSSSSS      UUUUUU  
 *********************************************************************************************************************/

#if (RTM_DEV_ERROR_DETECT == STD_ON)
# if (RTM_TASK_STACK_USAGE == STD_ON)
/**********************************************************************************************************************
 * Rtm_TaskStackUsage_IsBswCoreInitialized()
 *********************************************************************************************************************/
/*! \brief       Indicates if the BSW core's specific Rtm data is already initialized.
 *  \details     -
 *  \return      FALSE              The BSW core's specific Rtm data is not yet initialized.
 *  \return      TRUE               The BSW core's specific Rtm data is initialized.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_DEV_ERROR_DETECT == STD_ON and
 *               RTM_TASK_STACK_USAGE == STD_ON.
 *  \pre         -
 *  \ingroup     taskStackUsage
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(boolean, RTM_CODE) Rtm_TaskStackUsage_IsBswCoreInitialized(void);
# endif
#endif

/**********************************************************************************************************************
 *   NN      NN  EEEEEEEEEE  TTTTTTTTTT  
 *   NNN     NN  EE              TT      
 *   NNNN    NN  EE              TT      
 *   NN  NN  NN  EEEEEEEE        TT      
 *   NN    NNNN  EE              TT      
 *   NN     NNN  EE              TT      
 *   NN      NN  EEEEEEEEEE      TT      
 *********************************************************************************************************************/

#if (RTM_TIME_MEASUREMENT == STD_ON)
# if (RTM_NET_RUNTIME_SUPPORT == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 * Rtm_Net_LeaveThread()
 *********************************************************************************************************************/
/*! \brief       Stores data of a preempted net measurement point.
 *  \details     If a net measurement section is active on preempted thread, this section is also preempted.
 *  \param[in]   LeaveThread             The thread which is preempted/terminated.
 *  \param[in]   CoreId                  The core on which the scheduling is performed.
 *  \param[in]   CurrentTime             The timestamp when the thread was preempted.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and RTM_NET_RUNTIME_SUPPORT == STD_ON.
 *  \pre         Must not be called if the APIs Rtm_EnterTaskFct/Rtm_LeaveTaskFct/Rtm_EnterIsrFctRtm_LeaveIsrFct
 *               are used.
 *  \note        Should be called by Rtm_Schedule or an API with equal behavior.
 *  \ingroup     netRuntime
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Net_LeaveThread(
  uint32 LeaveThread,
  uint16 CoreId,
  Rtm_MeasurementTimestampType CurrentTime);

/**********************************************************************************************************************
 * Rtm_Net_EnterThread()
 *********************************************************************************************************************/
/*! \brief       Preempts a thread and starts another thread.
 *  \details     If a net measurement section is active on preempted thread, this section is also preempted. If a net 
 *               measurement section was preempted on the entered thread, this section is also started.
 *  \param[in]   LeaveThread             The thread which is started (now active).
 *  \param[in]   CoreId                  The core on which the scheduling is performed.
 *  \param[in]   CurrentTime             The timestamp when the thread was preempted.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if RTM_TIME_MEASUREMENT == STD_ON and RTM_NET_RUNTIME_SUPPORT == STD_ON.
 *  \pre         Must not be called if the APIs Rtm_EnterTaskFct/Rtm_LeaveTaskFct/Rtm_EnterIsrFctRtm_LeaveIsrFct
 *               are used.
 *  \note        Should be called by Rtm_Schedule or an API with equal behavior.
 *  \ingroup     netRuntime
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Net_EnterThread(
  uint32 EnterThread,
  uint16 CoreId,
  Rtm_MeasurementTimestampType CurrentTime);
# endif

/**********************************************************************************************************************
 *   TTTTTTTTTT    IIIIII    MM      MM  EEEEEEEEEE  
 *       TT          II      MMMM  MMMM  EE              
 *       TT          II      MM MMMM MM  EE          
 *       TT          II      MM  MM  MM  EEEEEEEE    
 *       TT          II      MM      MM  EE          
 *       TT          II      MM      MM  EE          
 *       TT        IIIIII    MM      MM  EEEEEEEEEE  
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Rtm_Time_GetCounterDelta()
 *********************************************************************************************************************/
/*! \brief       Calculates and returns the delta value between two timer values.
 *  \details     -
 *  \param[in]   StartValue       The start value for the delta calculation.
 *  \param[in]   EndValue         The end value for the delta calculation.
 *  \param[out]  ResultPtr        The result delta time.
 *  \param[in]   MeasurementId    The measurement id for which the delta time is calculated.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \spec        requires ResultPtr != NULL_PTR;
 *  \endspec
 *  \pre         -
 *  \ingroup     time
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Time_GetCounterDelta(
  uint32 StartValue,
  uint32 EndValue,
  P2VAR(uint32, AUTOMATIC, RTM_APPL_VAR) ResultPtr,
  uint32 MeasurementId);

/**********************************************************************************************************************
 * Rtm_Time_GetCurrentTime()
 *********************************************************************************************************************/
/*! \brief       Returns the current time.
 *  \details     -
 *  \param[out]  Time             The current time.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \spec        requires Time != NULL_PTR;
 *  \endspec
 *  \pre         -
 *  \ingroup     time
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Time_GetCurrentTime(
  P2VAR(Rtm_MeasurementTimestampType, AUTOMATIC, RTM_APPL_VAR) Time);

/**********************************************************************************************************************
 * Rtm_Time_MainFunctionRuntimeUpdate()
 *********************************************************************************************************************/
/*! \brief       Calculates the delta and average runtime between the Rtm_MainFunctions.
 *  \details     -
 *  \param[in]   CurrentTime      The current time.
 *  \param[in]   CoreId           The core id time.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     time
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Time_MainFunctionRuntimeUpdate(
  Rtm_MeasurementTimestampType CurrentTime,
  uint16 CoreId);

#endif /* (RTM_TIME_MEASUREMENT == STD_ON) */

/**********************************************************************************************************************
 *     CCCCCC    RRRRRRRR
 *   CC      CC  RR      RR
 *   CC          RR      RR
 *   CC          RRRRRRRR  
 *   CC          RR    RRR
 *   CC      CC  RR      RR
 *     CCCCCC    RR      RR
 *********************************************************************************************************************/

# if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0)
/**********************************************************************************************************************
 * Rtm_CpuLoadHistogram_ClearResults()
 *********************************************************************************************************************/
/*! \brief       Clears the result of cpu load histogram.
 *  \details     -
 *  \param[in]   CoreIndex        The core index on which the results are cleared.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     clearResults
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_CpuLoadHistogram_ClearResults(
  uint16 CoreIndex);
# endif

# if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0)
/**********************************************************************************************************************
 * Rtm_TaskResponseTime_ClearResults()
 *********************************************************************************************************************/
/*! \brief       Clears the result of task response time histogram.
 *  \details     -
 *  \param[in]   CoreIndex        The core index on which the results are cleared.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     clearResults
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_TaskResponseTime_ClearResults(
  uint16 CoreIndex);
# endif

# if (RTM_TASK_STACK_USAGE == STD_ON)
/**********************************************************************************************************************
 * Rtm_TaskStackUsage_ClearResults()
 *********************************************************************************************************************/
/*! \brief       Clears the result of task stack usage.
 *  \details     -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     clearResults
 *********************************************************************************************************************/
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_TaskStackUsage_ClearResults(void);
# endif

#if (RTM_TIME_MEASUREMENT == STD_ON)

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *   HH      HH  EEEEEEEEEE  LL          PPPPPPPP    EEEEEEEEEE  RRRRRRRR
 *   HH      HH  EE          LL          PP      PP  EE          RR      RR
 *   HH      HH  EE          LL          PP      PP  EE          RR      RR
 *   HHHHHHHHHH  EEEEEEEE    LL          PPPPPPPP    EEEEEEEE    RRRRRRRR
 *   HH      HH  EE          LL          PP          EE          RR    RRR
 *   HH      HH  EE          LL          PP          EE          RR      RR
 *   HH      HH  EEEEEEEEEE  LLLLLLLLLL  PP          EEEEEEEEEE  RR      RR
 *********************************************************************************************************************/

# if (RTM_MULTICORE_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead(void)
{
  /* #10 Start and stop the overhead MPs. */
  Rtm_Hlp_CalculateOverhead_GrossExecutionTime_EnableISR();
  Rtm_Hlp_CalculateOverhead_GrossExecutionTime_DisableISR();
# if (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
  Rtm_Hlp_CalculateOverhead_NetExecutionTime_EnableISR();
  Rtm_Hlp_CalculateOverhead_NetExecutionTime_DisableISR();
# endif
# if (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
  Rtm_Hlp_CalculateOverhead_FlatExecutionTime_EnableISR();
  Rtm_Hlp_CalculateOverhead_FlatExecutionTime_DisableISR();
# endif
} /* Rtm_Hlp_CalculateOverhead */

/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead_GrossExecutionTime_EnableISR()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead_GrossExecutionTime_EnableISR(void)
{
  /* #10 Start and stop the overhead MPs for gross execution time with enabled interrupts. */
  Rtm_Start(RtmConf_RtmMeasurementPoint_Rtm_Overhead_GrossExecutionTime_EnableISRs);
  Rtm_Stop(RtmConf_RtmMeasurementPoint_Rtm_Overhead_GrossExecutionTime_EnableISRs);
} /* Rtm_Hlp_CalculateOverhead_GrossExecutionTime_EnableISR */

/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead_GrossExecutionTime_DisableISR()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead_GrossExecutionTime_DisableISR(void)
{
  /* #10 Start and stop the overhead MPs for gross execution time with disabled interrupts. */
  Rtm_Start(RtmConf_RtmMeasurementPoint_Rtm_Overhead_GrossExecutionTime_DisableISRs);
  Rtm_Stop(RtmConf_RtmMeasurementPoint_Rtm_Overhead_GrossExecutionTime_DisableISRs);
} /* Rtm_Hlp_CalculateOverhead_GrossExecutionTime_DisableISR */

#  if (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead_NetExecutionTime_EnableISR()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead_NetExecutionTime_EnableISR(void)
{
  /* #10 Start and stop the overhead MPs for net execution time with enabled interrupts. */
  Rtm_Start(RtmConf_RtmMeasurementPoint_Rtm_Overhead_NetExecutionTime_EnableISRs);
  Rtm_Stop(RtmConf_RtmMeasurementPoint_Rtm_Overhead_NetExecutionTime_EnableISRs);
} /* Rtm_Hlp_CalculateOverhead_NetExecutionTime_EnableISR */

/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead_NetExecutionTime_DisableISR()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead_NetExecutionTime_DisableISR(void)
{
  /* #10 Start and stop the overhead MPs for net execution time with disabled interrupts. */
  Rtm_Start(RtmConf_RtmMeasurementPoint_Rtm_Overhead_NetExecutionTime_DisableISRs);
  Rtm_Stop(RtmConf_RtmMeasurementPoint_Rtm_Overhead_NetExecutionTime_DisableISRs);
} /* Rtm_Hlp_CalculateOverhead_NetExecutionTime_DisableISR */
#  endif

#  if (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead_FlatExecutionTime_EnableISR()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6010 1 */ /* MD_MSR_STPTH */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead_FlatExecutionTime_EnableISR(void)
{
  Rtm_OverheadCorrection.execTime_Flat_EnableISRs = 0u;

  /* #10 Start and stop the overhead MPs for flat execution time with enabled interrupts. */
  Rtm_Start(RtmConf_RtmMeasurementPoint_Rtm_Overhead_FlatExecutionTime_EnableISRs_Outer);
  Rtm_Start(RtmConf_RtmMeasurementPoint_Rtm_Overhead_FlatExecutionTime_EnableISRs_Inner);
  Rtm_Stop(RtmConf_RtmMeasurementPoint_Rtm_Overhead_FlatExecutionTime_EnableISRs_Inner);
  Rtm_Stop(RtmConf_RtmMeasurementPoint_Rtm_Overhead_FlatExecutionTime_EnableISRs_Outer);

  /* #20 Calculate the correction value of flat MPs. */
  Rtm_OverheadCorrection.execTime_Flat_EnableISRs = Rtm_Results[RtmConf_RtmMeasurementPoint_Rtm_Overhead_FlatExecutionTime_EnableISRs_Outer].time
                                                    - Rtm_Results[RtmConf_RtmMeasurementPoint_Rtm_Overhead_FlatExecutionTime_EnableISRs_Inner].time;
} /* Rtm_Hlp_CalculateOverhead_FlatExecutionTime_EnableISR */

/**********************************************************************************************************************
 * Rtm_Hlp_CalculateOverhead_FlatExecutionTime_DisableISR()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6010 1 */ /* MD_MSR_STPTH */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_CalculateOverhead_FlatExecutionTime_DisableISR(void)
{
  Rtm_OverheadCorrection.execTime_Flat_DisableISRs = 0u;

  /* #10 Start and stop the overhead MPs for flat execution time with disabled interrupts. */
  Rtm_Start(RtmConf_RtmMeasurementPoint_Rtm_Overhead_FlatExecutionTime_DisableISRs_Outer);
  Rtm_Start(RtmConf_RtmMeasurementPoint_Rtm_Overhead_FlatExecutionTime_DisableISRs_Inner);
  Rtm_Stop(RtmConf_RtmMeasurementPoint_Rtm_Overhead_FlatExecutionTime_DisableISRs_Inner);
  Rtm_Stop(RtmConf_RtmMeasurementPoint_Rtm_Overhead_FlatExecutionTime_DisableISRs_Outer);

  /* #20 Calculate the correction value of flat MPs. */
  Rtm_OverheadCorrection.execTime_Flat_DisableISRs = Rtm_Results[RtmConf_RtmMeasurementPoint_Rtm_Overhead_FlatExecutionTime_DisableISRs_Outer].time
                                                     - Rtm_Results[RtmConf_RtmMeasurementPoint_Rtm_Overhead_FlatExecutionTime_DisableISRs_Inner].time;
} /* Rtm_Hlp_CalculateOverhead_FlatExecutionTime_DisableISR */
#  endif
# endif /* (RTM_MULTICORE_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 * Rtm_Hlp_SetMPStateOfAllMPs()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Hlp_SetMPStateOfAllMPs(
  boolean DisableAllMPs)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint16_least ctrlVecIndex;

  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 If requested disable all MPs. */
  if (DisableAllMPs == TRUE)
  {
    for (ctrlVecIndex = 0u; ctrlVecIndex < RTM_CTRL_VECTOR_LEN; ctrlVecIndex++)
    {
      Rtm_Ctrl[ctrlVecIndex] = (uint8) 0u;
    }
  }
  /* #20 Otherwise, set state of all MPs as requested by RTM user. */
  else
  {
    for (ctrlVecIndex = 0u; ctrlVecIndex < RTM_CTRL_VECTOR_LEN; ctrlVecIndex++)
    {
      Rtm_Ctrl[ctrlVecIndex] = Rtm_MeasurementConfig[ctrlVecIndex];
    }
  }
} /* Rtm_Hlp_SetMPStateOfAllMPs */


/**********************************************************************************************************************
 *     IIIIII    NN      NN    IIIIII    TTTTTTTTT
 *       II      NNN     NN      II         TT    
 *       II      NNNN    NN      II         TT    
 *       II      NN  NN  NN      II         TT    
 *       II      NN    NNNN      II         TT    
 *       II      NN     NNN      II         TT    
 *     IIIIII    NN      NN    IIIIII       TT    
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rtm_Init_PersistencyData()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_PersistencyData(
  uint16 CoreIndex)
{
  /* ----- Implementation -------------------------------------------------------------------- */
# if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0)
  Rtm_Init_PersistencyDataOfCpuLoad(CoreIndex);
# endif
# if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0)
  Rtm_Init_PersistencyDataOfTaskResponseTime(CoreIndex);
# endif
  RTM_DUMMY_STATEMENT(CoreIndex); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
} /* Rtm_Init_PersistencyData */

# if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0)
/**********************************************************************************************************************
 * Rtm_Init_PersistencyDataOfCpuLoad()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_PersistencyDataOfCpuLoad(
  uint16 CoreIndex)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
#  if (RTM_NVM_IS_USED_FOR_CPU_LOAD_HISTOGRAM == STD_ON)
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  NvM_RequestResultType requestResult = NVM_REQ_NOT_OK;

  /* ----- Implementation -------------------------------------------------------------------- */
  if (Rtm_IsCpuLoadNvMHandleUsedOfCommonConst(CoreIndex, 0u)) /* COV_RTM_CPULOADHISTOGRAM_NVMHANDLE */
  {
    retVal = NvM_GetErrorStatus(Rtm_GetNvMCpuLoadBlockSnvOfCommonConst(CoreIndex, 0u), &requestResult);
  }

  /* #-- If the NvM block is in a valid state, the RAM variables are initialized by restored flash data. */
  if ((retVal == E_OK)
   && (requestResult == NVM_REQ_OK))
  {
    /* Do nothing */
  }
  /* #-- Otherwise, the RAM variables must be initialized with default values. */
  else
#  endif
  {
    Rtm_CpuLoadHistogram_ClearResults(CoreIndex);
  }

  /* #-- Set the NvM block of CPU load histogram data dirty to trigger its persistency during ECU shutdown. */
#  if (RTM_NVM_IS_USED_FOR_CPU_LOAD_HISTOGRAM == STD_ON)
  if (Rtm_IsCpuLoadNvMHandleUsedOfCommonConst(CoreIndex, 0u)) /* COV_RTM_CPULOADHISTOGRAM_NVMHANDLE */
  {
    (void)NvM_SetRamBlockStatus((NvM_BlockIdType)Rtm_GetNvMCpuLoadBlockSnvOfCommonConst(CoreIndex, 0u), TRUE);
  }
#  endif
} /* Rtm_Init_PersistencyDataOfCpuLoad */
# endif

# if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0)
/**********************************************************************************************************************
 * Rtm_Init_PersistencyDataOfTaskResponseTime()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_PersistencyDataOfTaskResponseTime(
  uint16 CoreIndex)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
#  if (RTM_NVM_IS_USED_FOR_TASK_RESPONSE_TIME == STD_ON)
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  NvM_RequestResultType requestResult = NVM_REQ_NOT_OK;

  /* ----- Implementation -------------------------------------------------------------------- */
  if (Rtm_IsTaskResponseTimeNvMHandleUsedOfCommonConst(CoreIndex, 0u)) /* COV_RTM_TASKRESPONSETIME_NVMHANDLE */
  {
    retVal = NvM_GetErrorStatus(Rtm_GetNvMTaskResponseTimeBlockSnvOfCommonConst(CoreIndex, 0u), &requestResult);
  }

  /* #-- If the NvM block is in a valid state, the RAM variables are initialized by restored flash data. */
  if ((retVal == E_OK)
   && (requestResult == NVM_REQ_OK))
  {
    /* Do nothing */
  }
  /* #-- Otherwise, the RAM variables must be initialized with default values. */
  else
#  endif
  {
    Rtm_TaskResponseTime_ClearResults(CoreIndex);
  }

  /* #-- Set the NvM block of task response time histogram data dirty to trigger its persistency during ECU shutdown. */
#  if (RTM_NVM_IS_USED_FOR_TASK_RESPONSE_TIME == STD_ON)
  if (Rtm_IsTaskResponseTimeNvMHandleUsedOfCommonConst(CoreIndex, 0u)) /* COV_RTM_TASKRESPONSETIME_NVMHANDLE */
  {
    (void)NvM_SetRamBlockStatus((NvM_BlockIdType)Rtm_GetNvMTaskResponseTimeBlockSnvOfCommonConst(CoreIndex, 0u), TRUE);
  }
#  endif
} /* Rtm_Init_PersistencyDataOfTaskResponseTime */
# endif
#endif /* (RTM_TIME_MEASUREMENT == STD_ON) */

#if (RTM_TASK_STACK_USAGE == STD_ON)
/**********************************************************************************************************************
 * Rtm_Init_PersistencyDataOfTaskStackUsage()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_PersistencyDataOfTaskStackUsage(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;
  NvM_RequestResultType requestResult = NVM_REQ_NOT_OK;

  /* ----- Implementation -------------------------------------------------------------------- */
  retVal = NvM_GetErrorStatus(Rtm_GetTaskStackNvMSnv(0u), &requestResult);

  /* #-- If the NvM block is in a valid state, the RAM variables are initialized by restored flash data. */
  if ((retVal == E_OK)
   && (requestResult == NVM_REQ_OK))
  {
    /* Do nothing */
  }
  /* #-- Otherwise, the RAM variables must be initialized with default values. */
  else
  {
    Rtm_TaskStackUsage_ClearResults();
  }
} /* Rtm_Init_PersistencyDataOfTaskStackUsage */
#endif

#if (RTM_TIME_MEASUREMENT == STD_ON)
# if (RTM_NET_RUNTIME_SUPPORT == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 * Rtm_Init_TaskContext()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_TaskContext(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint16_least index;
  uint32 rtmInactive = RTM_INACTIVE;
  
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 Invalidate the task indices. */
  for (index = 0u; index < RTM_NUMBER_OF_TASKS; index++)
  {
    Rtm_TaskIndex[index] = (Rtm_TaskType)rtmInactive;
  }

  /* Assign each Rtm_TaskIndex index to the corresponding Rtm_TaskContext:
   *  In Rtm_TaskContext the Task IDs are specified but unsorted.
   *  Rtm_TaskIndex is used to point to Rtm_TaskContext, example:
   *    Rtm_TaskIndex[0] = 3 -> Rtm_TaskContext[3].taskId = 0
   */
  /* #20 Map real unsorted task IDs to local sorted task IDs. */
  for (index = 0u; index < RTM_NUMBER_OF_TASKS; index++)
  {
    /* Each task ID must be unique, thus this condition should not fail. */
    if (Rtm_TaskIndex[Rtm_TaskContext[index].taskId] == (Rtm_TaskType)rtmInactive)
    {
      Rtm_TaskIndex[Rtm_TaskContext[index].taskId] = (Rtm_TaskType)index;
    }
  }

#  if (RTM_DEV_ERROR_DETECT == STD_ON)
  /* #30 If there is still an unmapped task index, indicate an error. */
  for (index = 0u; index < RTM_NUMBER_OF_TASKS; index++)
  {
    if (Rtm_TaskIndex[index] == (Rtm_TaskType)rtmInactive)
    {
      Rtm_DetReportError(RTM_SID_INIT, RTM_E_INVALID_CONFIGURATION);
    }
  }
#  endif
} /* Rtm_Init_TaskContext */
# endif /* (RTM_NET_RUNTIME_SUPPORT == STD_ON) */

# if (RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF)
/**********************************************************************************************************************
 * Rtm_Init_CpuLoadMeasurement()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_CpuLoadMeasurement(
  uint16 CoreIndex)
{
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 Initialize all CPU load related variables. */
  uint32 cpuLoadMPId = Rtm_GetCPULoadMeasurementIdOfCommonConst(CoreIndex, 0u);

  /* PRQA S 2991, 2995 1 */ /* MD_Rtm_2991, MD_Rtm_2995 */
  if (cpuLoadMPId < RTM_MEAS_SECTION_COUNT) /* COV_RTM_CPULOAD_MPS_ALL_ENABLED */
  {
    Rtm_Results[cpuLoadMPId].count = 0x00u;
    Rtm_Results[cpuLoadMPId].time = 0x00u;
    Rtm_Results[cpuLoadMPId].min = 0xFFFFFFFFu;
    Rtm_Results[cpuLoadMPId].max = 0x00u;

    Rtm_SetIsCpuLoadMPResultOverflownOfCpuLoadData(0u, FALSE, CoreIndex);
    Rtm_SetMeasurementWasStoppedOfCpuLoadData(0u, FALSE, CoreIndex);
    Rtm_SetCpuLoadTime(0u, CoreIndex);
    Rtm_SetStartTimeStampOfCpuLoadData(0u, RTM_GET_TIME_MEASUREMENT_FCT(), CoreIndex);
    Rtm_SetLastTicksOfCpuLoadData(0u, 0u, CoreIndex);
  }
} /* Rtm_Init_CpuLoadMeasurement */

/**********************************************************************************************************************
 * Rtm_Init_ActivateCpuLoadMeasurementPointOfCoreIndex()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_ActivateCpuLoadMeasurementPointOfCoreIndex(
  uint16 CoreIndex)
{
  /* ----- Implementation -------------------------------------------------------------------- */
  if (Rtm_IsCPULoadAutostartOfCommonConst(CoreIndex, 0u)) /* COV_RTM_CONFIG_CONDITION_ALWAYS_TRUE_OR_ALWAYS_FALSE */
  {
    Rtm_SetSendResultOfCpuLoadData(0u, 0x01u, CoreIndex);
    Rtm_SetMeasurementActiveOfCpuLoadData(0u, TRUE, CoreIndex);
  }
  else
  {
    Rtm_SetMeasurementActiveOfCpuLoadData(0u, FALSE, CoreIndex);
  }
} /* Rtm_Init_ActivateCpuLoadMeasurementPointOfCoreIndex */
# endif /* (RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF) */

# if (RTM_IS_ANY_CPU_LOAD_MP_SET_TO_AUTOSTART == STD_ON)
/**********************************************************************************************************************
 * Rtm_MeasCtr_CheckAutostartCpuLoad()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_CheckAutostartCpuLoad(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint16 coreIndex;
  uint8 sendingRequest = FALSE;

  /* ----- Implementation -------------------------------------------------------------------- */
  for (coreIndex = 0u; coreIndex < Rtm_GetSizeOfCommonConst(0u); coreIndex++)
  {
    if (Rtm_IsCPULoadAutostartOfCommonConst(coreIndex, 0u)) /* COV_RTM_CONFIG_CONDITION_ALWAYS_TRUE_OR_ALWAYS_FALSE */
    {
      if (Rtm_GetSendResultOfCpuLoadData(0u, coreIndex) == 0x01u)
      {
        Rtm_SetMeasurementActiveOfCpuLoadData(0u, FALSE, coreIndex);
        Rtm_SetSendResultOfCpuLoadData(0u, 0x00u, coreIndex);
        sendingRequest = TRUE;
      }
    }
  }

  return sendingRequest;
} /* Rtm_MeasCtr_CheckAutostartCpuLoad */
# endif

/**********************************************************************************************************************
 * Rtm_Init_MeasurementData()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Init_MeasurementData(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint16_least measurementIndex;
# if (RTM_NET_RUNTIME_SUPPORT == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
  uint16_least taskIndex;
# endif
  
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 Initialize MP specific data. */
  for (measurementIndex = 0u; measurementIndex < RTM_MEAS_SECTION_COUNT; measurementIndex++)
  {
# if (RTM_NESTING_COUNTER == STD_ON)
    Rtm_MeasurementNestingCtr[measurementIndex] = (sint8)0;
# endif
# if (RTM_TIMER_OVERRUN_SUPPORT == STD_ON)
    Rtm_PrevOverrunCounterValues[measurementIndex] = Rtm_TimerOverrunCnt;
# endif
# if (RTM_NET_RUNTIME_SUPPORT == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
    Rtm_MeasurementPointInfo[measurementIndex].intermediateTime = 0u;
    Rtm_MeasurementPointInfo[measurementIndex].prevActive = RTM_INACTIVE;
    Rtm_MeasurementPointInfo[measurementIndex].threadContext = RTM_NUMBER_OF_THREADS;
# endif
  }

# if (RTM_TIMER_OVERRUN_SUPPORT == STD_ON)    
  Rtm_GetCurrentTimeCnt = 0u;
# endif

  /* #20 If net runtime measurement is enabled reset all context specific data. */
# if (RTM_NET_RUNTIME_SUPPORT == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
  Rtm_ActiveMeasurementId = RTM_INACTIVE;
  
  for (taskIndex = 0u; taskIndex < RTM_NUMBER_OF_TASKS; taskIndex++)
  {
    Rtm_TaskContext[taskIndex].intermediateTime = Rtm_TaskContextInit[taskIndex].intermediateTime;
    Rtm_TaskContext[taskIndex].prevActive = Rtm_TaskContextInit[taskIndex].prevActive;
    Rtm_TaskContext[taskIndex].startTime = Rtm_TaskContextInit[taskIndex].startTime;
  }

  Rtm_IsrContext.intermediateTime = Rtm_IsrContextInit.intermediateTime;
  Rtm_IsrContext.prevActive = Rtm_IsrContextInit.prevActive;
  Rtm_IsrContext.startTime = Rtm_IsrContextInit.startTime;
  Rtm_IsrContext.isrId = Rtm_IsrContextInit.isrId;
# endif /* (RTM_NET_RUNTIME_SUPPORT == STD_ON) */

  /* #30 Clear active command and indicate success in response. */
  Rtm_Cmd = RTM_NULL;
  Rtm_Resp = ((uint32) RTM_RESP_OK << 28);
} /* Rtm_Init_MeasurementData */


/**********************************************************************************************************************
 *   MM      MM  EEEEEEEEEE    AAAAAA      SSSSSS              CCCCCC      OOOOOO    NN      NN  TTTTTTTTTT
 *   MMM    MMM  EE          AA      AA  SS      SS          CC      CC  OO      OO  NNN     NN      TT    
 *   MMMM  MMMM  EE          AA      AA  SS                  CC          OO      OO  NNNN    NN      TT    
 *   MM  MM  MM  EEEEEEEE    AAAAAAAAAA    SSSSSS    ======  CC          OO      OO  NN  NN  NN      TT    
 *   MM      MM  EE          AA      AA          SS          CC          OO      OO  NN    NNNN      TT    
 *   MM      MM  EE          AA      AA  SS      SS          CC      CC  OO      OO  NN     NNN      TT    
 *   MM      MM  EEEEEEEEEE  AA      AA    SSSSSS              CCCCCC      OOOOOO    NN      NN      TT    
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rtm_MeasCtr_MeasurementControl()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_MeasurementControl(
  Rtm_MeasurementTimestampType CurrentTime,
  Rtm_TimestampType TimeToMeasure,
  uint8 Command)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8 sendingRequest = FALSE;

  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 If a valid command is passed, execute it accordingly. */
  switch(Command)
  {
  /* Start Serial Measurement: */
  case(RTM_CMD_START_SERIAL_MEASUREMENT) :
    /* Only time-limited mode supported for serial measurement. */
    if (TimeToMeasure > 0u)
    {
      sendingRequest = Rtm_MeasCtr_StartSerialOrParallelMeasurement(CurrentTime, TimeToMeasure);
    }
    break;

  /* Start Parallel Measurement: */
  case(RTM_CMD_START_PARALLEL_MEASUREMENT) :
    sendingRequest = Rtm_MeasCtr_StartSerialOrParallelMeasurement(CurrentTime, TimeToMeasure);
    break;

# if (RTM_MULTICORE_SUPPORT == STD_OFF)
  /* Start Live Measurement: */
  case(RTM_CMD_START_LIVE_MEASUREMENT) :
    Rtm_MeasCtr_StartLiveMeasurement(CurrentTime, TimeToMeasure);
    break;
# endif

  /* Stop an endless measurement: */
  case(RTM_CMD_STOP_MEASUREMENT) :
    if (Rtm_EndlessMeasurement == TRUE)
    {
# if (RTM_MULTICORE_SUPPORT == STD_OFF)
      sendingRequest = Rtm_MeasCtr_StopEndlessMeasurement();
# else
      Rtm_SendNextMainFunction = Rtm_MeasCtr_StopEndlessMeasurement();
# endif
    }
    break;

  /* Clear all measurement results: */
  case(RTM_CMD_CLEAR_RESULTS) :
    sendingRequest = Rtm_MeasCtr_ClearMeasurementResults();
    break;

  /* #20 Otherwise: */
  default :
    /* #30 If a measurement is currently running, proceed it. */
# if (RTM_MULTICORE_SUPPORT == STD_OFF)
    if (Rtm_LastCommandToEcu != RTM_NULL)
    {
      if (Rtm_LiveMeasurement == TRUE)
      {
        /* Process Live Measurement: */
        sendingRequest = Rtm_MeasCtr_ProceedLiveMeasurement(CurrentTime);
      }
      else
      {
        /* Process Serial/Parallel Measurement: */
        sendingRequest = Rtm_MeasCtr_ProceedSerialOrParallelMeasurement(CurrentTime);
      }
    }
# else
    /* Process Serial/Parallel Measurement: */
    if (Rtm_LastCommandToEcu != RTM_NULL)
    {
      Rtm_SendNextMainFunction = Rtm_MeasCtr_ProceedSerialOrParallelMeasurement(CurrentTime);
    }
# endif
    break;
  }

  return sendingRequest;
} /* Rtm_MeasCtr_MeasurementControl */

/**********************************************************************************************************************
 * Rtm_MeasCtr_StartSerialOrParallelMeasurement()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_StartSerialOrParallelMeasurement(
  Rtm_MeasurementTimestampType CurrentTime,
  Rtm_TimestampType TimeToMeasure)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8 sendingRequest = FALSE; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 Start all requested MPs. */
  Rtm_Hlp_SetMPStateOfAllMPs(FALSE);

  /* #20 If measurement should be started in endless mode, prepare measurement. */
  if (TimeToMeasure == ((Rtm_TimestampType) 0u))
  {
    Rtm_MeasurementTimer = 0u;
    Rtm_EndlessMeasurement = TRUE;
    Rtm_LastMainFunctionTime = CurrentTime;
    Rtm_AvgMainFunctionCycleTimeCalcCounter = 0u;
  }
  /* #30 Otherwise, measurement is started in time-limited mode. Calculate predicted measurement end (Tcycle * timeToMeasure [ms]). */
  else
  {
    Rtm_MeasurementTimestampType cycleTime = (RTM_TICKS_PER_MILISECOND) * (RTM_MAINFCT_CYCLE_TIME);

    Rtm_MeasurementTimer = TimeToMeasure;
    Rtm_EndlessMeasurement = FALSE;

    Rtm_CalculatedCtrEndVal = (Rtm_TimestampType)((Rtm_TimestampType)CurrentTime
                                                + (((Rtm_TimestampType)Rtm_MeasurementTimer + 1u)
                                                 * (Rtm_TimestampType)cycleTime));
    Rtm_FixTypeMismatch(Rtm_CalculatedCtrEndVal);
  }

# if (RTM_MULTICORE_SUPPORT == STD_OFF)
  /* #40 Calculate overhead runtime of Rtm_Start and Rtm_Stop macros. */
  Rtm_Hlp_CalculateOverhead();
# endif

  /* #50 Remember the measurement mode. */
  Rtm_LastCommandToEcu = Rtm_Cmd;
  Rtm_Cmd = RTM_NULL;

# if (RTM_IS_ANY_CPU_LOAD_MP_SET_TO_AUTOSTART == STD_ON)
  /* #60 If CPU load measurement is started from ECU start-up:
   *       Indicate to transmit results and stop CPU load measurement. */
  sendingRequest = Rtm_MeasCtr_CheckAutostartCpuLoad();
# endif

  return sendingRequest;
} /* Rtm_MeasCtr_StartSerialOrParallelMeasurement */

# if (RTM_MULTICORE_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 * Rtm_MeasCtr_StartLiveMeasurement()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_MeasCtr_StartLiveMeasurement(
  Rtm_MeasurementTimestampType CurrentTime,
  Rtm_TimestampType TimeToMeasure)
{
  /* ----- Implementation -------------------------------------------------------------------- */
  Rtm_LiveMeasurement = TRUE;
  
  /* #10 Start all requested MPs. */
  Rtm_Hlp_SetMPStateOfAllMPs(FALSE);

  /* #20 If measurement should be started in endless mode, prepare measurement. */
  if (TimeToMeasure == ((Rtm_TimestampType) 0u))
  {
    Rtm_MeasurementTimer = 0u;
    Rtm_EndlessMeasurement = TRUE;
    Rtm_MainFunctionCounter = 1u;
  }
  /* #30 Otherwise, measurement is started in time-limited mode.
   *       Calculate predicted measurement end (Tcycle * timeToMeasure [ms]). */
  else
  {
    Rtm_MeasurementTimestampType cycleTime = (RTM_TICKS_PER_MILISECOND) * (RTM_MAINFCT_CYCLE_TIME);

    Rtm_MeasurementTimer = TimeToMeasure;
    Rtm_EndlessMeasurement = FALSE;

    Rtm_CalculatedCtrEndVal = (Rtm_TimestampType)((Rtm_TimestampType)CurrentTime + ((Rtm_MeasurementTimer + 1u) * (Rtm_TimestampType)cycleTime));
  }

  /* #40 Calculate overhead runtime of Rtm_Start and Rtm_Stop macros. */
  Rtm_Hlp_CalculateOverhead();

  /* #50 Remember the measurement mode. */
  Rtm_LastCommandToEcu = Rtm_Cmd;
  Rtm_Cmd = RTM_NULL;
} /* Rtm_MeasCtr_StartLiveMeasurement */
# endif

/**********************************************************************************************************************
 * Rtm_MeasCtr_StopEndlessMeasurement()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_StopEndlessMeasurement(void)
{
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 Stop all MPs, reset all measurement related data and trigger transmission. */
  Rtm_EndlessMeasurement = FALSE;
# if (RTM_MULTICORE_SUPPORT == STD_OFF)
  Rtm_LiveMeasurement = FALSE;
# endif
  Rtm_MeasurementTimer = 0u;
  Rtm_LastMainFunctionTime = 0u;
  Rtm_LastCommandToEcu = 0u;
  Rtm_AvgMainFunctionCycleTimeCalcCounter = 0u;

  Rtm_Hlp_SetMPStateOfAllMPs(TRUE);

  Rtm_Init_MeasurementData();
  
  return TRUE;
} /* Rtm_MeasCtr_StopEndlessMeasurement */

/**********************************************************************************************************************
 * Rtm_MeasCtr_ClearMeasurementResults()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_ClearMeasurementResults(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint16_least measurementIndex;
  uint16_least controlIndex;

  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 Clear all MP's measurement results and reset all measurement related data. */
  Rtm_AverageMainFunctionCycleTime = 0u;
  Rtm_MainFunctionCounter = 0u;

  for (measurementIndex = 0u; measurementIndex < RTM_MEAS_SECTION_COUNT; measurementIndex++)
  {
    Rtm_Results[measurementIndex].time  = (uint32) 0u;
    Rtm_Results[measurementIndex].count = (uint32) 0u;
    Rtm_Results[measurementIndex].min   = (uint32) 0xFFFFFFFFu;
    Rtm_Results[measurementIndex].max   = (uint32) 0u;
  }

  for (controlIndex = 0u; controlIndex < RTM_CTRL_VECTOR_LEN; controlIndex++)
  {
    Rtm_Ctrl[controlIndex] = 0u;
  }

  Rtm_Init_MeasurementData();

#if (RTM_CPU_LOAD_CONTROL_MODE == RTM_CPU_LOAD_CONTROL_XCP)
  {
    uint16_least locCoreId;

    for (locCoreId = 0u; locCoreId < RTM_NUMBER_OF_CORES; locCoreId++)
    {
      Rtm_SetLastTicksOfCpuLoadData(0u, 0u, locCoreId);
      Rtm_SetMeasurementActiveOfCpuLoadData(0u, FALSE, locCoreId);
      Rtm_SetCpuLoadTime(0u, locCoreId);
    }
  }
#endif

  return TRUE;
} /* Rtm_MeasCtr_ClearMeasurementResults */

# if (RTM_MULTICORE_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 * Rtm_MeasCtr_ProceedLiveMeasurement()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_ProceedLiveMeasurement(
  Rtm_MeasurementTimestampType CurrentTime)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8 sendingRequest = FALSE; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 If XCP is disconnected, deactivate live measurement. */
#  if (RTM_XCP_IS_PRESENT == STD_ON)
  if (Rtm_XcpState != XCP_EVENT_DAQ)
  {
    /* Measurements are going to get deactivated */
    Rtm_LiveMeasurement = FALSE;
    Rtm_MeasurementTimer = 0u;
    Rtm_EndlessMeasurement = FALSE;
  }
  /* #20 Otherwise: */
  else
#  endif
  {
    /* #30 If the live measurement is time-limited: */
    if (Rtm_EndlessMeasurement == FALSE)
    {
      Rtm_MeasurementTimestampType deltaTime = ((Rtm_MeasurementTimestampType)Rtm_CalculatedCtrEndVal - CurrentTime);
      /* #40 Calculate the correction value for live measurement. */
      Rtm_MeasTimeCorrection = (sint32)(deltaTime);
      Rtm_CalculatedCtrEndVal = (Rtm_TimestampType) (CurrentTime + (1u * RTM_TICKS_PER_MILISECOND * RTM_MAINFCT_CYCLE_TIME));

      /* #50 If the measurement duration is over: Stop all measurement points.
       *     Otherwise, move main function counter. */
      if (Rtm_MeasurementTimer == 0u)
      {
        Rtm_Hlp_SetMPStateOfAllMPs(TRUE);

        Rtm_LastCommandToEcu = RTM_NULL;
        Rtm_LiveMeasurement = FALSE;
      }
      else
      {
        Rtm_MeasurementTimer--;
      }
    }
    /* #60 Otherwise, the measurement is endless. Calculate last main function duration. */
    else
    {
      Rtm_Time_GetCounterDelta(Rtm_LastMainFunctionTime, CurrentTime, &Rtm_AverageMainFunctionCycleTime, 0u);
      Rtm_LastMainFunctionTime = CurrentTime;
    }

    /* #70 Always send OK in main function during live measurement. */
    Rtm_Resp = ((uint32) RTM_RESP_OK << 28u); /* ESCAN00076777 */
    sendingRequest = TRUE;
  }

  return sendingRequest;
} /* Rtm_MeasCtr_ProceedLiveMeasurement */
# endif /* RTM_MULTICORE_SUPPORT == STD_OFF */

/**********************************************************************************************************************
 * Rtm_MeasCtr_ProceedSerialOrParallelMeasurement()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
RTM_LOCAL_INLINE FUNC(uint8, RTM_CODE) Rtm_MeasCtr_ProceedSerialOrParallelMeasurement(
  Rtm_MeasurementTimestampType CurrentTime)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Rtm_MeasurementTimestampType currentTime = CurrentTime;
  uint8 sendingRequest = FALSE;

  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 If endless measurement is currently active, calculate the average main function duration. */
  if (Rtm_EndlessMeasurement == TRUE)
  {
    uint32 currentMainFuncCycleTime;

    Rtm_Time_GetCounterDelta(Rtm_LastMainFunctionTime, currentTime, &currentMainFuncCycleTime, 0u);

    if (Rtm_AvgMainFunctionCycleTimeCalcCounter < 32u)
    {
      Rtm_AvgMainFunctionCycleTimeCalcCounter++;
    }
    Rtm_AverageMainFunctionCycleTime = ((Rtm_AverageMainFunctionCycleTime
                                      * (Rtm_AvgMainFunctionCycleTimeCalcCounter - 1u)) 
                                      + currentMainFuncCycleTime)
                                      / Rtm_AvgMainFunctionCycleTimeCalcCounter;

    Rtm_MainFunctionCounter++;
    Rtm_LastMainFunctionTime = currentTime;
  }
  /* #20 Otherwise, the measurement is time-limited: */
  else
  {
    /* #30 If the measurement is over:
     *       Stop all MPs, indicate to transmit Xcp_Event and calculate the measurement correction. */
    if (Rtm_MeasurementTimer == 0u)
    {
      Rtm_Hlp_SetMPStateOfAllMPs(TRUE);

      Rtm_LastCommandToEcu = RTM_NULL;
      Rtm_Resp = ((uint32) RTM_RESP_OK << 28u); /* ESCAN00076777 */
      sendingRequest = TRUE;

      Rtm_FixTypeMismatch(currentTime); /* PRQA S 3109 */ /* MD_MSR_14.3 */
      Rtm_MeasTimeCorrection = (sint32)((sint32)Rtm_CalculatedCtrEndVal - (sint32)currentTime);
    }
    /* #40 Otherwise, move main function counter. */
    else
    {
      Rtm_MeasurementTimer--;
    }
  }

  return sendingRequest;
} /* Rtm_MeasCtr_ProceedSerialOrParallelMeasurement */


/**********************************************************************************************************************
 *     CCCCCC    PPPPPPPP    UU      UU
 *   CC      CC  PP      PP  UU      UU
 *   CC          PP      PP  UU      UU
 *   CC          PPPPPPPP    UU      UU
 *   CC          PP          UU      UU
 *   CC      CC  PP          UU      UU
 *     CCCCCC    PP            UUUUUU
 *********************************************************************************************************************/

# if (RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF)
/**********************************************************************************************************************
 * Rtm_Cpu_CalculateCurrentCPULoad()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
#  if (RTM_MULTICORE_SUPPORT == STD_OFF)
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Cpu_CalculateCurrentCPULoad(
  uint16 CoreIndex)
#  else
FUNC(void, RTM_CODE) Rtm_Cpu_CalculateCurrentCPULoad(
  uint16 CoreIndex)
#  endif
{
  /* ----- Local Variables --------------------------------------------------------------------- */
#  if (RTM_TIMER_OVERRUN_SUPPORT == STD_ON) || (RTM_CPU_LOAD_CONTROL_MODE == RTM_CPU_LOAD_CONTROL_XCP)
  uint32 cpuLoadMPId = Rtm_GetCPULoadMeasurementIdOfCommonConst(CoreIndex, 0u);
#  endif
#  if (RTM_CPU_LOAD_CONTROL_MODE == RTM_CPU_LOAD_CONTROL_XCP)
  boolean rtmCpuLoadMeasurementWasActive;
#  endif

  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 Remember current CPU load measurement result and reset the collection of new result. */
  Rtm_SetCpuLoadTime(Rtm_GetCollectedTimeOfCpuLoadData(0u, CoreIndex), CoreIndex);
  Rtm_SetCollectedTimeOfCpuLoadData(0u, 0u, CoreIndex);

#  if (RTM_TIMER_OVERRUN_SUPPORT == STD_ON)
  if (cpuLoadMPId < RTM_MEAS_SECTION_COUNT) /* COV_RTM_CPULOAD_MPS_ALL_ENABLED */
  {
    Rtm_PrevOverrunCounterValues[cpuLoadMPId] = Rtm_TimerOverrunCnt;
  }
#  endif

  /* #20 If the CPU load measurement is currently active: */
#  if (RTM_CPU_LOAD_CONTROL_MODE == RTM_CPU_LOAD_CONTROL_C_API)
  if (Rtm_IsMeasurementActiveOfCpuLoadData(0u, CoreIndex))
  {
    /* #30 If CPU load measurement was stopped previously, Initialize CPU load MP and make reference measurement.
     *     Otherwise, cumulate the CPU load measurement results and handle possible result overruns. */
    /* If new CPU load measurement cycle is triggered, the old results are cleaned */
    if (Rtm_IsMeasurementWasStoppedOfCpuLoadData(0u, CoreIndex))
    {
      Rtm_Init_CpuLoadMeasurement(CoreIndex);
    }
  }
#  endif
#  if (RTM_CPU_LOAD_CONTROL_MODE == RTM_CPU_LOAD_CONTROL_XCP)
  /* #40 Remember whether CPU load measurement is currently active. */
  if (Rtm_IsMeasurementActiveOfCpuLoadData(0u, CoreIndex))
  {
    rtmCpuLoadMeasurementWasActive = TRUE;
  }
  else
  {
    rtmCpuLoadMeasurementWasActive = FALSE;
  }

  /* #50 Start or stop CPU load measurement. */
  if (cpuLoadMPId < RTM_MEAS_SECTION_COUNT) /* COV_RTM_CPULOAD_MPS_ALL_ENABLED */
  {
    uint32 ctrlIndexOfCpuLoadMp;
    uint8 maskOfCpuLoadMp;

    ctrlIndexOfCpuLoadMp = cpuLoadMPId / 8u;
    maskOfCpuLoadMp = 1u << (cpuLoadMPId % 8u);

    if ((maskOfCpuLoadMp) == ((maskOfCpuLoadMp) & Rtm_Ctrl[(ctrlIndexOfCpuLoadMp)]))
    {
      Rtm_SetMeasurementActiveOfCpuLoadData(0u, TRUE, CoreIndex);
    }
    else
    {
      Rtm_SetMeasurementActiveOfCpuLoadData(0u, FALSE, CoreIndex);
    }
  }

  /* #60 If CPU load measurement is started:
   *       Initialize CPU load MP and make reference measurement. */
  if ( (Rtm_IsMeasurementActiveOfCpuLoadData(0u, CoreIndex))
    && ((rtmCpuLoadMeasurementWasActive == FALSE) 
    ||  (Rtm_IsMeasurementWasStoppedOfCpuLoadData(0u, CoreIndex)))
     )
  {
    Rtm_Init_CpuLoadMeasurement(CoreIndex);
  }
#  endif
} /* Rtm_Cpu_CalculateCurrentCPULoad */

/**********************************************************************************************************************
 * Rtm_Cpu_IsMeasurementIdValidCpuLoadMP()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(boolean, RTM_CODE) Rtm_Cpu_IsMeasurementIdValidCpuLoadMP(
  uint32 MeasurementId,
  P2VAR(uint16, AUTOMATIC, RTM_APPL_VAR) CoreIndex)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  boolean isMpValid = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation -------------------------------------------------------------------- */
  if (MeasurementId < RTM_MEAS_SECTION_COUNT)
  {
    uint16 coreIndex;

    for (coreIndex = 0u; coreIndex < Rtm_GetSizeOfCommonConst(0u); coreIndex++)
    {
      if (MeasurementId == Rtm_GetCPULoadMeasurementIdOfCommonConst(coreIndex, 0u))
      {
        *CoreIndex = coreIndex;
        isMpValid = TRUE;
        break;
      }
    }
  }

  if (isMpValid == FALSE)
  {
    Rtm_DetReportError(RTM_SID_GETMEASUREMENTITEM, RTM_E_WRONG_PARAMETERS);
  }

  return isMpValid;
} /* Rtm_Cpu_IsMeasurementIdValidCpuLoadMP */
# endif /* (RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF) */

# if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0u)
/**********************************************************************************************************************
 * Rtm_CpuLoadHistogram_IsCoreIndexValidAndActive()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(boolean, RTM_CODE) Rtm_CpuLoadHistogram_IsCoreIndexValidAndActive(
  uint16 CoreIndex)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  boolean isCoreIdValid = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation -------------------------------------------------------------------- */
  if (CoreIndex < RTM_NUMBER_OF_CORES)
  {
    uint32 mpId = Rtm_GetCPULoadMeasurementIdOfCommonConst(CoreIndex, 0u);

    /* PRQA S 2991, 2995 1 */ /* MD_Rtm_2991, MD_Rtm_2995 */
    if (mpId < RTM_MEAS_SECTION_COUNT) /* COV_RTM_CPULOAD_MPS_ALL_ENABLED */
    {
      isCoreIdValid = TRUE;
    }
  }

  return isCoreIdValid;
} /* Rtm_CpuLoadHistogram_IsCoreIndexValidAndActive */
# endif

# if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0u)
/**********************************************************************************************************************
 * Rtm_CpuLoadHistogram_AvoidOverrun()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_CpuLoadHistogram_AvoidOverrun(
  uint16 CoreIndex)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint32 overallPercentileCount = Rtm_GetCpuLoadOverallPercentileCountOfCpuLoadPersistencyData(0u, CoreIndex);

  /* ----- Implementation -------------------------------------------------------------------- */
  /* #-- If the overall percentile count of task response time histogram is overlapsed: */
  if (overallPercentileCount >= RTM_HISTOGRAM_OVERFLOW_THRESHOLD)
  {
    uint32 percentileIndex;

    overallPercentileCount = 0u;

    /* #-- Rightshift all percentiles and accumulate the remaining percentile counts. */
    for (percentileIndex = 0u; percentileIndex < RTM_SIZE_OF_CPULOAD_PERCENTILES; percentileIndex++)
    {
      uint32 percentileCount = Rtm_GetCpuLoadPercentilesOfCpuLoadPersistencyData(0u, CoreIndex)[percentileIndex];

      percentileCount = (uint32)(percentileCount >> RTM_HISTOGRAM_RIGHTSHIFTLENGTH);
      Rtm_GetCpuLoadPercentilesOfCpuLoadPersistencyData(0u, CoreIndex)[percentileIndex] = percentileCount;
      overallPercentileCount += percentileCount;
    }

    /* #-- Set the overall percentile count to the accumulated remaining percentile count. */
    Rtm_SetCpuLoadOverallPercentileCountOfCpuLoadPersistencyData(0u, overallPercentileCount, CoreIndex);
  }
} /* Rtm_CpuLoadHistogram_AvoidOverrun */

/**********************************************************************************************************************
 * Rtm_CpuLoadHistogram_GetCoreIndexOfCoreId()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(Std_ReturnType, RTM_CODE) Rtm_CpuLoadHistogram_GetCoreIndexOfCoreId(
  uint16 CoreId,
  P2VAR(uint16, AUTOMATIC, RTM_APPL_VAR) CoreIndex)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint16 coreIndex;

  /* ----- Implementation ---------------------------------------------------------------------- */
  for (coreIndex = 0u; coreIndex < Rtm_GetSizeOfCommonConst(0u); coreIndex++)
  {
    if (CoreId == Rtm_GetCoreIdOfCommonConst(coreIndex, 0u))
    {
      retVal = E_OK;
      *CoreIndex = coreIndex;
      break;
    }
  }

  return retVal;
} /* Rtm_CpuLoadHistogram_GetCoreIndexOfCoreId */
# endif

/**********************************************************************************************************************
 *   TTTTTTTTTT  RRRRRRRR    TTTTTTTTTT
 *       TT      RR      RR      TT    
 *       TT      RR      RR      TT    
 *       TT      RRRRRRRR        TT    
 *       TT      RR     RR       TT    
 *       TT      RR      RR      TT    
 *       TT      RR      RR      TT    
 *********************************************************************************************************************/

# if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0u)
/**********************************************************************************************************************
 * Rtm_TaskResponseTime_AvoidOverrun()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_TaskResponseTime_AvoidOverrun(
  uint16 CoreIndex,
  uint16 TaskIndex)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint32 overallPercentileCount = Rtm_GetTaskResponseTimeDataPtrOfCommonConst(CoreIndex, 0u)[TaskIndex].OverallPercentiles;

  /* ----- Implementation -------------------------------------------------------------------- */
  /* #-- If the overall percentile count of task response time histogram is overlapsed: */
  if (overallPercentileCount >= RTM_HISTOGRAM_OVERFLOW_THRESHOLD)
  {
    uint32 percentileIndex;

    overallPercentileCount = 0u;

    /* #-- Rightshift all percentiles and accumulate the remaining percentile counts. */
    for (percentileIndex = 0u; percentileIndex < RTM_SIZE_OF_TASKRESPONSETIME_PERCENTILES; percentileIndex++)
    {
      uint32 percentileCount = Rtm_GetTaskResponseTimeDataPtrOfCommonConst(CoreIndex, 0u)[TaskIndex].PercentileCount[percentileIndex];

      percentileCount = (uint32)(percentileCount >> RTM_HISTOGRAM_RIGHTSHIFTLENGTH);
      Rtm_GetTaskResponseTimeDataPtrOfCommonConst(CoreIndex, 0u)[TaskIndex].PercentileCount[percentileIndex] = percentileCount;
      overallPercentileCount += percentileCount;
    }

    /* #-- Set the overall percentile count to the accumulated remaining percentile count. */
    Rtm_GetTaskResponseTimeDataPtrOfCommonConst(CoreIndex, 0u)[TaskIndex].OverallPercentiles = overallPercentileCount;
  }
} /* Rtm_TaskResponseTime_AvoidOverrun */
# endif
#endif /* RTM_TIME_MEASUREMENT == STD_ON */

#if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0u)
/**********************************************************************************************************************
 * Rtm_TaskResponseTime_GetCoreIndexAndTaskIndexOfTaskId()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3673 3 */ /* MD_Rtm_3673 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_TaskResponseTime_GetCoreIndexAndTaskIndexOfTaskId(
  const uint16 TaskId,
  P2VAR(uint8, AUTOMATIC, RTM_APPL_VAR) CoreIndex,
  P2VAR(uint8, AUTOMATIC, RTM_APPL_VAR) TaskIndex)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8_least coreIndex;

  /* ----- Implementation ---------------------------------------------------------------------- */
  for (coreIndex = 0u; coreIndex < Rtm_GetSizeOfCommonConst(0u); coreIndex++)
  {
    uint8_least taskIndex;
    uint8 startIndex = Rtm_GetOsTaskInfoStartIdxOfCommonConst(coreIndex, 0u);

    for (taskIndex = startIndex; taskIndex < Rtm_GetOsTaskInfoEndIdxOfCommonConst(coreIndex, 0u); taskIndex++)
    {
      if (Rtm_GetTaskIdOfOsTaskInfo(taskIndex, 0u) == TaskId)
      {
        *CoreIndex = (uint8)coreIndex;
        *TaskIndex = (uint8)(taskIndex - startIndex);
        break;
      }
    }
  }
} /* Rtm_TaskResponseTime_GetCoreIndexAndTaskIndexOfTaskId */
#endif

#if (RTM_DEV_ERROR_DETECT == STD_ON)
# if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0u)
/**********************************************************************************************************************
 * Rtm_TaskResponseTime_IsInitializedOnCoreOfTaskId()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(boolean, RTM_CODE) Rtm_TaskResponseTime_IsInitializedOnCoreOfTaskId(
  const uint16 TaskId)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8 coreIndex = RTM_NUMBER_OF_CORES;
  uint8 taskIndex = RTM_NUMBER_OF_TASKS;
  boolean isCoreInitialized = FALSE;

  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Get the core index of the task id. */
  /*@ assert &coreIndex != NULL_PTR; */ /* VCA_RTM_VALID_POINTER */
  /*@ assert &taskIndex != NULL_PTR; */ /* VCA_RTM_VALID_POINTER */
  Rtm_TaskResponseTime_GetCoreIndexAndTaskIndexOfTaskId(TaskId, &coreIndex, &taskIndex);

  /* #-- If the core index is valid and the core specific data of Rtm is initialized, indicate this. */
  if ((coreIndex < RTM_NUMBER_OF_CORES)
   && (Rtm_InitState[coreIndex] == RTM_INITIALIZED))
  {
    isCoreInitialized = TRUE;
  }

  return isCoreInitialized;
} /* Rtm_TaskResponseTime_IsInitializedOnCoreOfTaskId */
# endif
#endif

#if (RTM_DEV_ERROR_DETECT == STD_ON)
# if (RTM_TASK_STACK_USAGE == STD_ON)
/**********************************************************************************************************************
 * Rtm_TaskStackUsage_IsBswCoreInitialized()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(boolean, RTM_CODE) Rtm_TaskStackUsage_IsBswCoreInitialized(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint16_least coreIndex;
  boolean isCoreInitialized = FALSE;

  /* ----- Implementation ---------------------------------------------------------------------- */
  for (coreIndex = 0u; coreIndex < Rtm_GetSizeOfCommonConst(0u); coreIndex++)
  {
    /* #-- If the core specific data of Rtm is initialized, indicate this. */
    if (Rtm_InitState[coreIndex] == RTM_INITIALIZED)
    {
      if (Rtm_IsBSWCoreOfCommonConst(coreIndex, 0u)) /* COV_RTM_CONDITION_ALWAYS_TRUE */
      {
        isCoreInitialized = TRUE;
        break;
      }
    }
  }

  return isCoreInitialized;
} /* Rtm_TaskStackUsage_IsBswCoreInitialized */
# endif
#endif /* (RTM_DEV_ERROR_DETECT == STD_ON) */

/**********************************************************************************************************************
 *   NN      NN  EEEEEEEEEE  TTTTTTTTTT  
 *   NNN     NN  EE              TT      
 *   NNNN    NN  EE              TT      
 *   NN  NN  NN  EEEEEEEE        TT      
 *   NN    NNNN  EE              TT      
 *   NN     NNN  EE              TT      
 *   NN      NN  EEEEEEEEEE      TT      
 *********************************************************************************************************************/

#if (RTM_TIME_MEASUREMENT == STD_ON)
# if (RTM_NET_RUNTIME_SUPPORT == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 * Rtm_Net_LeaveThread()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Net_LeaveThread(
  uint32 LeaveThread,
  uint16 CoreId,
  Rtm_MeasurementTimestampType CurrentTime)
{
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 If the Thread is in valid range:
   *       Remember which MP is preempted and when this happened. */
  if (LeaveThread < RTM_NUMBER_OF_THREADS)
  {
    Rtm_ThreadContext[LeaveThread].prevActiveMP = Rtm_ActiveMeasurementId;
    Rtm_ThreadContext[LeaveThread].preemptionTime = CurrentTime;
  }

  RTM_DUMMY_STATEMENT(CoreId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
} /* Rtm_Net_LeaveThread */

/**********************************************************************************************************************
 * Rtm_Net_EnterThread()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Net_EnterThread(
  uint32 EnterThread,
  uint16 CoreId,
  Rtm_MeasurementTimestampType CurrentTime)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
#   if (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
  uint32_least i;
  uint32 locPrevActive;
#   endif
  
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #20 If a Thread is started,
   *       and the Thread has interrupted a MP: */
  if (EnterThread < RTM_NUMBER_OF_THREADS)
  {
    Rtm_ActiveThreadId = EnterThread;
    Rtm_ActiveMeasurementId = Rtm_ThreadContext[EnterThread].prevActiveMP;

    if (Rtm_ActiveMeasurementId < RTM_MEAS_SECTION_COUNT)
    {
      Rtm_MeasurementTimestampType deltaTime;

      /* #30 Calculate the preemption time. */
      Rtm_Time_GetCounterDelta(Rtm_ThreadContext[EnterThread].preemptionTime, CurrentTime, &deltaTime, Rtm_ActiveMeasurementId);

      /* #40 If there are MPs of net and flat type, add preemption time to last active MP and all interrupted
       *     net MPs. */
#   if (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) && (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
      Rtm_MeasurementPointInfo[Rtm_ActiveMeasurementId].intermediateTime += deltaTime;
      locPrevActive = Rtm_MeasurementPointInfo[Rtm_ActiveMeasurementId].prevActive;

      for ( i = 1u; 
            (i < RTM_MEAS_SECTION_COUNT) && 
            (locPrevActive < RTM_MEAS_SECTION_COUNT) &&
            (Rtm_MeasurementPointInfo[locPrevActive].threadContext == (uint32)EnterThread);
            i++ )
      {
        if (Rtm_MeasurementPointConfigInfo[locPrevActive].measurementType == RTM_MEASUREMENT_TYPE_NET_EXECUTIONTIME)
        {
          Rtm_MeasurementPointInfo[locPrevActive].intermediateTime += deltaTime;
        }

        locPrevActive = Rtm_MeasurementPointInfo[locPrevActive].prevActive;
      }
#   else

      /* #50 If all MPs are of net type, add preemption time to all interrupted MPs. */
#    if (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
      locPrevActive = Rtm_ActiveMeasurementId;

      for ( i = 0u; 
            (i < RTM_MEAS_SECTION_COUNT) && 
            (locPrevActive < RTM_MEAS_SECTION_COUNT) &&
            (Rtm_MeasurementPointInfo[locPrevActive].threadContext == (uint32)EnterThread);
            i++ )
      {
        Rtm_MeasurementPointInfo[locPrevActive].intermediateTime += deltaTime;

        locPrevActive = Rtm_MeasurementPointInfo[locPrevActive].prevActive;
      }
#    endif

      /* #60 If all MPs are of flat type, add preemption time to the last active MP. */
#    if (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
      Rtm_MeasurementPointInfo[Rtm_ActiveMeasurementId].intermediateTime += deltaTime;
#    endif

#   endif
    }
  }
  /* #-- Otherwise, no new context started, therefore no MP is currently active. */
  else
  {
    Rtm_ActiveMeasurementId = RTM_INACTIVE;
    Rtm_ActiveThreadId = RTM_NUMBER_OF_THREADS;
  }

  RTM_DUMMY_STATEMENT(CoreId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
} /* Rtm_Net_EnterThread */
# endif

/**********************************************************************************************************************
 *   TTTTTTTTTT    IIIIII    MM      MM  EEEEEEEEEE  
 *       TT          II      MMMM  MMMM  EE              
 *       TT          II      MM MMMM MM  EE          
 *       TT          II      MM  MM  MM  EEEEEEEE    
 *       TT          II      MM      MM  EE          
 *       TT          II      MM      MM  EE          
 *       TT        IIIIII    MM      MM  EEEEEEEEEE  
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Rtm_Time_GetCounterDelta()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Time_GetCounterDelta(
  uint32 StartValue,
  uint32 EndValue,
  P2VAR(uint32, AUTOMATIC, RTM_APPL_VAR) ResultPtr,
  uint32 MeasurementId)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
  /* Only for valid MPs the overrun handling is supported. */
# if (RTM_TIMER_OVERRUN_SUPPORT == STD_ON)
  if (MeasurementId < RTM_MEAS_SECTION_COUNT)
  {
#  if (RTM_CTR_DIRECTION == RTM_UP)
    /* If no overrun occurred: */
    if ((EndValue) >= (StartValue))
    {
      if (Rtm_TimerOverrunCnt >= Rtm_PrevOverrunCounterValues[MeasurementId])
      {
        *ResultPtr = ((((uint32)Rtm_TimerOverrunCnt - (uint32)Rtm_PrevOverrunCounterValues[MeasurementId]) * ((uint32)RTM_MEASUREMENT_MAX_VAL) ) + EndValue) - StartValue;
      }
      else
      {
        *ResultPtr = ((((uint32)(((uint32)256u - (uint32)Rtm_PrevOverrunCounterValues[MeasurementId]) + (uint32)Rtm_TimerOverrunCnt)) * ((uint32)RTM_MEASUREMENT_MAX_VAL) ) + EndValue) - StartValue;
      }
    }
    /* Otherwise, overrun occurred: */
    else
    {
      if (Rtm_TimerOverrunCnt > Rtm_PrevOverrunCounterValues[MeasurementId])
      {
        *ResultPtr = ((((uint32)((uint32)Rtm_TimerOverrunCnt - (uint32)Rtm_PrevOverrunCounterValues[MeasurementId])) * ((uint32)RTM_MEASUREMENT_MAX_VAL) ) - StartValue) + EndValue;
      }
      else
      {
        if (Rtm_TimerOverrunCnt == Rtm_PrevOverrunCounterValues[MeasurementId])
        {
          *ResultPtr = ((((uint32)1u) * ((uint32)RTM_MEASUREMENT_MAX_VAL) ) - StartValue) + EndValue;
        }
        else
        {
          *ResultPtr = ((((uint32)(((uint32)256u - (uint32)Rtm_PrevOverrunCounterValues[MeasurementId]) + (uint32)Rtm_TimerOverrunCnt)) * ((uint32)RTM_MEASUREMENT_MAX_VAL) ) - StartValue) + EndValue;
        }
      }
    }
#  else /* if (RTM_CTR_DIRECTION == RTM_DOWN) */
    if (EndValue <= StartValue)
    {
      if (Rtm_TimerOverrunCnt >= Rtm_PrevOverrunCounterValues[MeasurementId])
      {
        *ResultPtr = ((((uint32)((uint32)Rtm_TimerOverrunCnt - (uint32)Rtm_PrevOverrunCounterValues[MeasurementId])) * ((uint32)RTM_MEASUREMENT_MAX_VAL)) + StartValue) - EndValue;
      }
      else
      {
        *ResultPtr = ((((uint32)(((uint32)256u - (uint32)Rtm_PrevOverrunCounterValues[MeasurementId]) + (uint32)Rtm_TimerOverrunCnt)) * ((uint32)RTM_MEASUREMENT_MAX_VAL)) + StartValue) - EndValue;
      }
    }
    else
    {
      if (Rtm_TimerOverrunCnt > Rtm_PrevOverrunCounterValues[MeasurementId])
      {
        *ResultPtr = ((((uint32)((uint32)Rtm_TimerOverrunCnt - (uint32)Rtm_PrevOverrunCounterValues[MeasurementId])) * ((uint32)RTM_MEASUREMENT_MAX_VAL)) - EndValue) + StartValue;
      }
      else
      {
        if (Rtm_TimerOverrunCnt == Rtm_PrevOverrunCounterValues[MeasurementId])
        {
          *ResultPtr = (((uint32)(1u) * ((uint32)RTM_MEASUREMENT_MAX_VAL)) - EndValue) + StartValue;
        }
        else
        {
          *ResultPtr = ((((uint32)((uint32)256u - (uint32)Rtm_PrevOverrunCounterValues[MeasurementId]) + (uint32)Rtm_TimerOverrunCnt) * ((uint32)RTM_MEASUREMENT_MAX_VAL)) - EndValue) + StartValue;
        }
      }
    }
#  endif /* (RTM_CTR_DIRECTION == RTM_UP) */
  }
  else
# endif /* (RTM_TIMER_OVERRUN_SUPPORT == STD_ON) */
  {
#  if (RTM_CTR_DIRECTION == RTM_UP)
    if (EndValue >= StartValue)
    {
      *ResultPtr = EndValue - StartValue;
    }
    else
    {
      *ResultPtr = (RTM_MEASUREMENT_MAX_VAL - StartValue) + EndValue;
    }
#  else /* if (RTM_CTR_DIRECTION == RTM_DOWN) */
    if (EndValue <= StartValue)
    {
      *ResultPtr = StartValue - EndValue;
    }
    else
    {
      *ResultPtr = (RTM_MEASUREMENT_MAX_VAL - EndValue) + StartValue;
    }
#  endif /* (RTM_CTR_DIRECTION == RTM_UP) */
  }

  RTM_DUMMY_STATEMENT(MeasurementId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
} /* Rtm_Time_GetCounterDelta */

/**********************************************************************************************************************
 * Rtm_Time_GetCurrentTime()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Time_GetCurrentTime(
  P2VAR(Rtm_MeasurementTimestampType, AUTOMATIC, RTM_APPL_VAR) Time)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
# if (RTM_TIMER_OVERRUN_SUPPORT == STD_ON)
  /* #10 If timer overrun support is enabled:
   *       Get current time.
   *       If this is API is currently not executed by another thread.
   *         If a timer overrun is detected, increment the overrun counter and remember current time. */
#  if (RTM_CTR_DIRECTION == RTM_UP)
  Rtm_GetCurrentTimeCnt++;
  *Time = (Rtm_MeasurementTimestampType)RTM_GET_TIME_MEASUREMENT_FCT();

  if (Rtm_GetCurrentTimeCnt == 1u)
  {
    if (*Time < Rtm_PrevTimerValue)
    {
      Rtm_TimerOverrunCnt++;
    }
    Rtm_PrevTimerValue = *Time;
  }

  Rtm_GetCurrentTimeCnt--;
#  else
  Rtm_GetCurrentTimeCnt++;

  *Time = (Rtm_MeasurementTimestampType)RTM_GET_TIME_MEASUREMENT_FCT();

  if (Rtm_GetCurrentTimeCnt == 1u)
  {
    if (*Time > Rtm_PrevTimerValue)
    {
      Rtm_TimerOverrunCnt++;
    }
    Rtm_PrevTimerValue = *Time;
  }

  Rtm_GetCurrentTimeCnt--;
#  endif
# else /* if (RTM_TIMER_OVERRUN_SUPPORT == STD_OFF) */
  /* #20 Otherwise, just get current time and return it. */
  *Time = RTM_GET_TIME_MEASUREMENT_FCT();
# endif /* (RTM_TIMER_OVERRUN_SUPPORT == STD_ON) */
} /* Rtm_Time_GetCurrentTime */

/**********************************************************************************************************************
 * Rtm_Time_MainFunctionRuntimeUpdate()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_Time_MainFunctionRuntimeUpdate(
  Rtm_MeasurementTimestampType CurrentTime,
  uint16 CoreId)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint32 lastCall = Rtm_GetLastCallOfMainFunctionRuntimeData(0u, CoreId);
  uint32 delta = Rtm_GetDeltaOfMainFunctionRuntimeData(0u, CoreId);
  uint32 average = Rtm_GetAverageOfMainFunctionRuntimeData(0u, CoreId);
  uint32 newAverage;
  uint32 averageCounter = (uint32)Rtm_GetAverageCounterOfMainFunctionRuntimeData(0u, CoreId);
  uint32 cpuLoadMPId = Rtm_GetCPULoadMeasurementIdOfCommonConst(CoreId, 0u);

  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 Calculate the delta runtime between last call of main function and present call. */
  Rtm_Time_GetCounterDelta(lastCall, CurrentTime, &delta, cpuLoadMPId);

  /* #20 Remember current ticks as last call of main function and remember the delta runtime. */
  Rtm_SetLastCallOfMainFunctionRuntimeData(0u, CurrentTime, CoreId);
  Rtm_SetDeltaOfMainFunctionRuntimeData(0u, delta, CoreId);

  /* #30 If the counter did not reach its limit yet, increment it. */
  if (averageCounter < 128u)
  {
    averageCounter++;
    Rtm_SetAverageCounterOfMainFunctionRuntimeData(0u, (uint8)averageCounter, CoreId);
  }

  /* #40 Calculate and remember the new average main function runtime. */
  newAverage = ((average * (averageCounter - 1u)) + delta) / averageCounter;
  Rtm_SetAverageOfMainFunctionRuntimeData(0u, newAverage, CoreId);
} /* Rtm_Time_MainFunctionRuntimeUpdate */

/**********************************************************************************************************************
 *     CCCCCC    RRRRRRRR
 *   CC      CC  RR      RR
 *   CC          RR      RR
 *   CC          RRRRRRRR  
 *   CC          RR    RRR
 *   CC      CC  RR      RR
 *     CCCCCC    RR      RR
 *********************************************************************************************************************/

# if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0)
/**********************************************************************************************************************
 * Rtm_CpuLoadHistogram_ClearResults()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_CpuLoadHistogram_ClearResults(
  uint16 CoreIndex)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8_least percentileIndex;

  /* ----- Implementation ---------------------------------------------------------------------- */
  Rtm_SetCpuLoadOverallPercentileCountOfCpuLoadPersistencyData(0u, 0u, CoreIndex);

  for (percentileIndex = 0u; percentileIndex < RTM_SIZE_OF_CPULOAD_PERCENTILES; percentileIndex++)
  {
    Rtm_GetCpuLoadPercentilesOfCpuLoadPersistencyData(0u, CoreIndex)[percentileIndex] = 0u;
  }

#  if (RTM_NVM_IS_USED_FOR_CPU_LOAD_HISTOGRAM == STD_ON)
  if (Rtm_IsCpuLoadNvMHandleUsedOfCommonConst(CoreIndex, 0u)) /* COV_RTM_CPULOADHISTOGRAM_NVMHANDLE */
  {
    (void)NvM_SetRamBlockStatus((NvM_BlockIdType)Rtm_GetNvMCpuLoadBlockSnvOfCommonConst(CoreIndex, 0u), TRUE);
  }
#  endif
} /* Rtm_CpuLoadHistogram_ClearResults */
# endif

# if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0)
/**********************************************************************************************************************
 * Rtm_TaskResponseTime_ClearResults()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_TaskResponseTime_ClearResults(
  uint16 CoreIndex)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint16_least taskIndex;

  /* ----- Implementation ---------------------------------------------------------------------- */
  for (taskIndex = 0u; taskIndex < Rtm_GetOsTaskInfoLengthOfCommonConst(CoreIndex, 0u); taskIndex++)
  {
    uint8_least percentileIndex;

    /*@ assert taskIndex < Rtm_CommonConst[CoreIndex].OsTaskInfoLengthOfCommonConst; */ /* VCA_RTM_VALID_NUMBER_OF_CORE_SPECIFIC_TASKS */

    Rtm_GetTaskResponseTimeDataPtrOfCommonConst(CoreIndex, 0u)[taskIndex].MaxRuntimeInTicks = 0u;
    Rtm_GetTaskResponseTimeDataPtrOfCommonConst(CoreIndex, 0u)[taskIndex].OverallPercentiles = 0u;

    for (percentileIndex = 0u; percentileIndex < RTM_SIZE_OF_TASKRESPONSETIME_PERCENTILES; percentileIndex++)
    {
      Rtm_GetTaskResponseTimeDataPtrOfCommonConst(CoreIndex, 0u)[taskIndex].PercentileCount[percentileIndex] = 0u; /* VCA_RTM_TASK_RESPONSE_TIME_PERCENTILE_INDEX */
    }
  }

#  if (RTM_NVM_IS_USED_FOR_TASK_RESPONSE_TIME == STD_ON)
  if (Rtm_IsTaskResponseTimeNvMHandleUsedOfCommonConst(CoreIndex, 0u)) /* COV_RTM_TASKRESPONSETIME_NVMHANDLE */
  {
    (void)NvM_SetRamBlockStatus((NvM_BlockIdType)Rtm_GetNvMTaskResponseTimeBlockSnvOfCommonConst(CoreIndex, 0u), TRUE);
  }
#  endif
} /* Rtm_TaskResponseTime_ClearResults */
# endif
#endif /* (RTM_TIME_MEASUREMENT == STD_ON) */

#if (RTM_TASK_STACK_USAGE == STD_ON)
/**********************************************************************************************************************
 * Rtm_TaskStackUsage_ClearResults()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
RTM_LOCAL_INLINE FUNC(void, RTM_CODE) Rtm_TaskStackUsage_ClearResults(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint16_least osTaskIndex;

  /* ----- Implementation ---------------------------------------------------------------------- */
  for (osTaskIndex = 0u; osTaskIndex < RTM_NUMBER_OF_TASKS; osTaskIndex++)
  {
    Rtm_MaxTaskStackUsage[osTaskIndex] = 0u;
  }

  (void)NvM_SetRamBlockStatus((NvM_BlockIdType)Rtm_GetTaskStackNvMSnv(0u), TRUE);
} /* Rtm_TaskStackUsage_ClearResults */
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Rtm_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, RTM_CODE) Rtm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, RTM_APPL_VAR) Versioninfo)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8 errorCode = RTM_E_NO_ERROR;

  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #10 If Rtm's functionality is enabled: */
# if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
# endif
  {
    /* ----- Development Error Checks ------------------------------------------------------------ */
    /* #20 If parameter is invalid, indicate error.
     *     Otherwise, return version info. */
# if (RTM_DEV_ERROR_DETECT == STD_ON)
    if (Versioninfo == NULL_PTR)
    {
      errorCode = RTM_E_WRONG_PARAMETERS;
    }
    else
# endif
    {
      Versioninfo->vendorID = RTM_VENDOR_ID;
      Versioninfo->moduleID = RTM_MODULE_ID;
      Versioninfo->sw_major_version = (uint8)RTM_SW_MAJOR_VERSION;
      Versioninfo->sw_minor_version = (uint8)RTM_SW_MINOR_VERSION;
      Versioninfo->sw_patch_version = (uint8)RTM_SW_PATCH_VERSION;
    }

      /* ----- Development Error Report ------------------------------------------------------------ */
# if (RTM_DEV_ERROR_REPORT == STD_ON)
    if (errorCode != RTM_E_NO_ERROR)
    {
      Rtm_DetReportError(RTM_SID_GETVERSIONINFO, errorCode);
    }
# else
    RTM_DUMMY_STATEMENT(errorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif
  }
# if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
# endif
} /* Rtm_GetVersionInfo */

#if (RTM_TIME_MEASUREMENT == STD_ON)
/**********************************************************************************************************************
 * Rtm_StartMeasurementFct()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6030 3 */ /* MD_MSR_STCYC */
/* PRQA S 6010 2 */ /* MD_MSR_STPTH */
FUNC(void, RTM_CODE) Rtm_StartMeasurementFct(
  uint32 measurementId) /* ESCAN00076464 */
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Rtm_MeasurementTimestampType currentTime;
  uint8 errorCode = RTM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #10 If the parameter is invalid, indicate an error. */
# if (RTM_DEV_ERROR_DETECT == STD_ON)
  if (measurementId >= RTM_MEAS_SECTION_COUNT)
  {
    errorCode = RTM_E_WRONG_PARAMETERS;
  }
  else
  /* If the MP is assigned to one specific core, the MP must be executed on this core. */
#  if (RTM_MULTICORE_SUPPORT == STD_ON)
  if ( (Rtm_MeasurementPointConfigInfo[measurementId].coreId < RTM_NUMBER_OF_CORES)
    && ((uint16)Rtm_GetCoreId() != Rtm_MeasurementPointConfigInfo[measurementId].coreId)
     ) /* COV_RTM_CONFIG_CONDITION_NO_CROSSCORE_MP */
  {
    errorCode = RTM_E_INVALID_CONFIGURATION;
  }
  else
#  endif
# endif
  /* #20 Otherwise, if the MP is started the first time:
   *       Store current time. */
  {
    /* ----- Implementation -------------------------------------------------------------------- */
# if (RTM_NESTING_COUNTER == STD_ON)
    Rtm_MeasurementNestingCtr[measurementId]++;
    if (Rtm_MeasurementNestingCtr[measurementId] == (sint8)1)
# else
#  if (RTM_DEV_ERROR_DETECT == STD_ON)
    Rtm_MeasurementNestingCtr[measurementId]++;
#  endif
# endif
    {
      /*@ assert &currentTime != NULL_PTR; */ /* VCA_RTM_VALID_POINTER */
      Rtm_Time_GetCurrentTime(&currentTime);

      Rtm_StartTimeStamps[measurementId] = currentTime;
# if (RTM_TIMER_OVERRUN_SUPPORT == STD_ON)
      Rtm_PrevOverrunCounterValues[measurementId] = Rtm_TimerOverrunCnt;    
# endif
    }

    /* #30 If the MP was started too often, indicate error. */
# if (RTM_DEV_ERROR_REPORT == STD_ON)
    if (Rtm_MeasurementNestingCtr[measurementId] >= (sint8)100)
    {
      errorCode = RTM_E_UNBALANCED;
    }
# endif
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
# if (RTM_DEV_ERROR_REPORT == STD_ON)
  if (errorCode != RTM_E_NO_ERROR)
  {
    Rtm_DetReportError(RTM_SID_STARTMEASUREMENT, errorCode);
  }
# else
  RTM_DUMMY_STATEMENT(errorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif
} /* Rtm_StartMeasurementFct */

/**********************************************************************************************************************
 * Rtm_StopMeasurementFct()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 4 */ /* MD_MSR_STMIF */
/* PRQA S 6030 3 */ /* MD_MSR_STCYC */
/* PRQA S 6010 2 */ /* MD_MSR_STPTH */
FUNC(void, RTM_CODE) Rtm_StopMeasurementFct(
  uint32 measurementId) /* ESCAN00076464 */
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Rtm_MeasurementTimestampType currentTime;
  uint8 errorCode = RTM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #10 If the parameter is invalid, indicate an error. */
# if (RTM_DEV_ERROR_DETECT == STD_ON)
  if (measurementId >= RTM_MEAS_SECTION_COUNT)
  {
    errorCode = RTM_E_WRONG_PARAMETERS;
  }
  else
  /* If the MP is assigned to one specific core, the MP must be executed on this core. */
#  if (RTM_MULTICORE_SUPPORT == STD_ON)
  if ( (Rtm_MeasurementPointConfigInfo[measurementId].coreId < RTM_NUMBER_OF_CORES)
    && ((uint16)Rtm_GetCoreId() != Rtm_MeasurementPointConfigInfo[measurementId].coreId)
     ) /* COV_RTM_CONFIG_CONDITION_NO_CROSSCORE_MP */
  {
    errorCode = RTM_E_INVALID_CONFIGURATION;
  }
  else
#  endif
# endif
  /* #20 Otherwise: */
  {
    /* ----- Implementation -------------------------------------------------------------------- */
    /* #30 If the MP was started prior:
     *       Calculate time difference since measurement start.
     *       Check for new minimum and maximum value.
     *       Cumulate the overall runtime.
     *       Reset results if overflow occurred and indicate an error.
     *       Call callback if threshold exceeded. */
# if (RTM_NESTING_COUNTER == STD_ON)
    Rtm_MeasurementNestingCtr[measurementId]--;
    if (Rtm_MeasurementNestingCtr[measurementId] == (sint8)0) /* ESCAN00076464 */
# else
#  if (RTM_DEV_ERROR_DETECT == STD_ON)
    Rtm_MeasurementNestingCtr[measurementId]--;
#  endif
# endif
    {
      Rtm_Time_GetCurrentTime(&currentTime);
      Rtm_Time_GetCounterDelta(Rtm_StartTimeStamps[measurementId], currentTime, &currentTime, measurementId);

      if (currentTime > Rtm_Results[measurementId].max)
      {
        Rtm_Results[measurementId].max = currentTime;
      }
      if (currentTime < Rtm_Results[measurementId].min)
      {
        Rtm_Results[measurementId].min = currentTime;
      }

      Rtm_Results[measurementId].time = Rtm_Results[measurementId].time + currentTime;
      Rtm_Results[measurementId].count = Rtm_Results[measurementId].count + 1u;

      if (Rtm_Results[measurementId].time < currentTime)
      {
        Rtm_Results[measurementId].time = (uint32) currentTime;
        Rtm_Results[measurementId].count = (uint32) 1u;
        Rtm_Results[measurementId].max = currentTime;
        Rtm_Results[measurementId].min = currentTime;
# if (RTM_REPORT_DET_FOR_MEASUREMENT_POINT_RESULT_OVERFLOW == STD_ON)
        errorCode = RTM_E_MEASUREMENT_POINT_RESULT_OVERFLOWN;
# endif
      }

# if (RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF)
      if (Rtm_MeasurementPointConfigInfo[measurementId].mpType == RTM_MP_TYPE_CPU_LOAD)
      {
        Rtm_AddCollectedTimeOfCpuLoadData(0u, currentTime, Rtm_MeasurementPointConfigInfo[measurementId].coreId);
      }
# endif

# if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0)
      if (Rtm_MeasurementPointConfigInfo[measurementId].mpType == RTM_MP_TYPE_TASK)
      {
        uint32 precentileIndex;
        uint16 coreIndex = Rtm_MeasurementPointConfigInfo[measurementId].coreId;
        uint16 taskIndex = Rtm_MeasurementPointConfigInfo[measurementId].taskRespTimeIdx;
        uint8 numberOfPercentiles = Rtm_GetNumberofTaskResponseTimePercentilesOfCommonConst(coreIndex, 0u);

        precentileIndex = (uint32)(((uint64)currentTime * Rtm_MeasurementPointConfigInfo[measurementId].targetRTFactor) >> 32u);

        if (precentileIndex > numberOfPercentiles)
        {
          precentileIndex = numberOfPercentiles;
        }
        Rtm_GetTaskResponseTimeDataPtrOfCommonConst(coreIndex, 0u)[taskIndex].PercentileCount[precentileIndex]++;
        Rtm_GetTaskResponseTimeDataPtrOfCommonConst(coreIndex, 0u)[taskIndex].OverallPercentiles++;
        /* Note: the TaskId of TaskResponseTimeDataPtr is already set during initialization. */

        if (Rtm_Results[measurementId].max > Rtm_GetTaskResponseTimeDataPtrOfCommonConst(coreIndex, 0u)[taskIndex].MaxRuntimeInTicks)
        {
          Rtm_GetTaskResponseTimeDataPtrOfCommonConst(coreIndex, 0u)[taskIndex].MaxRuntimeInTicks = Rtm_Results[measurementId].max;
        }

        Rtm_TaskResponseTime_AvoidOverrun(coreIndex, taskIndex);
      }
# endif

      if ((0u < Rtm_ThresholdTimes[measurementId]) && (Rtm_ThresholdTimes[measurementId] < currentTime))
      {
        (Rtm_ThresholdCbkFctArr[measurementId]) (currentTime);
      }
    }

    /* #40 If the MP was stopped twice, indicate an error. */
# if (RTM_DEV_ERROR_REPORT == STD_ON)
    if (Rtm_MeasurementNestingCtr[measurementId] < (sint8)0)
    {
      errorCode = RTM_E_UNBALANCED;
    }
# endif
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
# if (RTM_DEV_ERROR_REPORT == STD_ON)
  if (errorCode != RTM_E_NO_ERROR)
  {
    Rtm_DetReportError(RTM_SID_STOPMEASUREMENT, errorCode);
  }
# else
  RTM_DUMMY_STATEMENT(errorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif
} /* Rtm_StopMeasurementFct */

# if (RTM_MULTICORE_SUPPORT == STD_OFF)
#  if (RTM_NET_RUNTIME_SUPPORT == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 * Rtm_StartNetMeasurementFct()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 4 */ /* MD_MSR_STMIF */
/* PRQA S 6030 3 */ /* MD_MSR_STCYC */
/* PRQA S 6010 2 */ /* MD_MSR_STPTH */
FUNC(void, RTM_CODE) Rtm_StartNetMeasurementFct(
  uint32 measurementId) /* ESCAN00076464 */
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Rtm_MeasurementTimestampType currentTime;
  uint8 errorCode = RTM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #10 If the parameter is invalid, indicate an error. */
#   if (RTM_DEV_ERROR_DETECT == STD_ON)
  if (measurementId >= RTM_MEAS_SECTION_COUNT)
  {
    errorCode = RTM_E_WRONG_PARAMETERS;
  }
  else
#   endif
  /* #20 Otherwise: */
  {
    /* ----- Implementation -------------------------------------------------------------------- */
    /* #30 If the MP is started the first time and running on a valid thread:
     *       Store current time.
     *     Otherwise, indicate an error. */
#   if (RTM_NESTING_COUNTER == STD_ON)
    Rtm_MeasurementNestingCtr[measurementId]++;
    if (Rtm_MeasurementNestingCtr[measurementId] == (sint8)1)
#   else
#    if (RTM_DEV_ERROR_DETECT == STD_ON)
    Rtm_MeasurementNestingCtr[measurementId]++;
#    endif
#   endif
    {
      /* #-- A MP of type execution time has to be running in context of a thread. */
      if (Rtm_ActiveThreadId < RTM_NUMBER_OF_THREADS)
      {
        Rtm_MeasurementPointInfo[measurementId].threadContext = Rtm_ActiveThreadId;
        Rtm_MeasurementPointInfo[measurementId].prevActive = Rtm_ActiveMeasurementId;
    
        Rtm_ActiveMeasurementId = measurementId;

        Rtm_Time_GetCurrentTime(&currentTime);
        Rtm_StartTimeStamps[measurementId] = currentTime;

#   if (RTM_TIMER_OVERRUN_SUPPORT == STD_ON)
        Rtm_PrevOverrunCounterValues[measurementId] = Rtm_TimerOverrunCnt;    
#   endif
      }
      /* #-- Otherwise, report an DET error. */
      else
      {
        errorCode = RTM_E_INVALID_CONFIGURATION;
      }
    }

#   if (RTM_DEV_ERROR_REPORT == STD_ON)
    if (Rtm_MeasurementNestingCtr[measurementId] >= (sint8)100)
    {
      errorCode = RTM_E_UNBALANCED;
    }
#   endif
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#   if (RTM_DEV_ERROR_REPORT == STD_ON)
  if (errorCode != RTM_E_NO_ERROR)
  {
    Rtm_DetReportError(RTM_SID_STARTNETMEASUREMENT, errorCode);
  }
#   else
  RTM_DUMMY_STATEMENT(errorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#   endif
} /* Rtm_StartNetMeasurementFct */

/**********************************************************************************************************************
 * Rtm_StopNetMeasurementFct()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 4 */ /* MD_MSR_STMIF */
/* PRQA S 6030 3 */ /* MD_MSR_STCYC */
/* PRQA S 6010 2 */ /* MD_MSR_STPTH */
FUNC(void, RTM_CODE) Rtm_StopNetMeasurementFct(
  uint32 measurementId) /* ESCAN00076464 */
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Rtm_MeasurementTimestampType currentTime;
  uint32 interTime;
  uint32 interruptedMeasId;
  uint8  errorCode = RTM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #10 If the parameter is invalid, indicate an error. */
#   if (RTM_DEV_ERROR_DETECT == STD_ON)
  if (measurementId >= RTM_MEAS_SECTION_COUNT)
  {
    errorCode = RTM_E_WRONG_PARAMETERS;
  }
  else
#   endif
  /* #20 Otherwise: */
  {
    /* ----- Implementation -------------------------------------------------------------------- */
    /* #30 If the MP was started prior: */
#   if (RTM_NESTING_COUNTER == STD_ON)
    Rtm_MeasurementNestingCtr[measurementId]--;
    if (Rtm_MeasurementNestingCtr[measurementId] == (sint8)0) /* ESCAN00076464 */
#   else
#    if (RTM_DEV_ERROR_DETECT == STD_ON)
    Rtm_MeasurementNestingCtr[measurementId]--;
#    endif
#   endif
    {
      /* #40 If the currently active MP is stopped: */
      if (Rtm_ActiveMeasurementId == measurementId)
      {
        /* #50 Calculate time difference since measurement start. */
        Rtm_Time_GetCurrentTime(&currentTime);
        interTime = Rtm_MeasurementPointInfo[measurementId].intermediateTime;
        Rtm_Time_GetCounterDelta(Rtm_StartTimeStamps[measurementId], currentTime, &currentTime, measurementId);

        interruptedMeasId = Rtm_MeasurementPointInfo[measurementId].prevActive;

        /* #60 If the interrupted measurement point is of type flat execution time:
         *       Add gross runtime of now stopped MP and overhead correction value to the intermediateTime of the interrupted MP. */
#   if (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
        if ((interruptedMeasId < RTM_MEAS_SECTION_COUNT)
#    if (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
          && (Rtm_MeasurementPointConfigInfo[interruptedMeasId].measurementType == RTM_MEASUREMENT_TYPE_FLAT_EXECUTIONTIME)
#    endif
           )
        {
          Rtm_MeasurementPointInfo[interruptedMeasId].intermediateTime = Rtm_MeasurementPointInfo[interruptedMeasId].intermediateTime + currentTime; /* Add brutto runtime of current measurement point */
          if (Rtm_MeasurementPointConfigInfo[interruptedMeasId].interruptsDisabled == TRUE)
          {
            Rtm_MeasurementPointInfo[interruptedMeasId].intermediateTime = Rtm_MeasurementPointInfo[interruptedMeasId].intermediateTime + Rtm_OverheadCorrection.execTime_Flat_DisableISRs;
          }
          else
          {
            Rtm_MeasurementPointInfo[interruptedMeasId].intermediateTime = Rtm_MeasurementPointInfo[interruptedMeasId].intermediateTime + Rtm_OverheadCorrection.execTime_Flat_EnableISRs;
          }
        }
#   endif

        /* #70 Activate the interrupted MP. */
        Rtm_MeasurementPointInfo[measurementId].threadContext = RTM_NUMBER_OF_THREADS;
        Rtm_ActiveMeasurementId = interruptedMeasId;
        Rtm_MeasurementPointInfo[measurementId].intermediateTime = 0u;

        /* #80 Subtract intermediateTime from current result. */
        if (interTime < currentTime)
        {
          currentTime = currentTime - interTime;
        }
        else
        {
          currentTime = 0u;
        }

        /* #90 Check for new minimum and maximum value. */
        if (currentTime > Rtm_Results[measurementId].max)
        {
          Rtm_Results[measurementId].max = currentTime;
        }
        if (currentTime < Rtm_Results[measurementId].min)
        {
          Rtm_Results[measurementId].min = currentTime;
        }

        /* #100 Cumulate the overall runtime, reset results if overflow detected and indicate an error. */
        Rtm_Results[measurementId].time = Rtm_Results[measurementId].time + currentTime;
        Rtm_Results[measurementId].count = Rtm_Results[measurementId].count + 1u;

        if (Rtm_Results[measurementId].time < currentTime)
        {
          /* Overflow occurred, reset results to defined state */
          Rtm_Results[measurementId].time = (uint32) currentTime;
          Rtm_Results[measurementId].count = (uint32) 1u;
          Rtm_Results[measurementId].max = currentTime;
          Rtm_Results[measurementId].min = currentTime;
# if (RTM_REPORT_DET_FOR_MEASUREMENT_POINT_RESULT_OVERFLOW == STD_ON)
          errorCode = RTM_E_MEASUREMENT_POINT_RESULT_OVERFLOWN;
# endif
        }

        /* #110 Call callback if threshold exceeded. */
        if ((0u < Rtm_ThresholdTimes[measurementId]) && (Rtm_ThresholdTimes[measurementId] < currentTime))
        {
          (Rtm_ThresholdCbkFctArr[measurementId]) (currentTime);
        }
      }
      /* #120 Otherwise, inconsistent Start/Stop sequence detected; Only the active MP is allowed to be stopped. */
      else
      {
        errorCode = RTM_E_UNBALANCED;
      }
    }

#   if (RTM_DEV_ERROR_REPORT == STD_ON)
    if (Rtm_MeasurementNestingCtr[measurementId] < (sint8)0)
    {
      errorCode = RTM_E_UNBALANCED;
    }
#   endif
  }
  
  /* ----- Development Error Report ------------------------------------------------------------ */
#   if (RTM_DEV_ERROR_REPORT == STD_ON)
  if (errorCode != RTM_E_NO_ERROR)
  {
    Rtm_DetReportError(RTM_SID_STOPNETMEASUREMENT, errorCode);
  }
#   else
  RTM_DUMMY_STATEMENT(errorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#   endif
} /* Rtm_StopNetMeasurementFct */

/**********************************************************************************************************************
 * Rtm_Schedule()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, RTM_CODE) Rtm_Schedule(
  uint32 FromThreadId,
  uint32 ToThreadId,
  uint16 CoreId)
{
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 If Rtm's functionality is enabled: */
#   if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
#   endif
  {
    Rtm_MeasurementTimestampType currentTime = 0u;

    /* #15 If the active MP is interrupted or if a interrupted MP is resumed, get the current time. */
    if ((Rtm_ActiveMeasurementId != RTM_INACTIVE) 
     || ((ToThreadId < RTM_NUMBER_OF_THREADS)
     &&  (Rtm_ThreadContext[ToThreadId].prevActiveMP < RTM_MEAS_SECTION_COUNT)))
    {
      Rtm_Time_GetCurrentTime(&currentTime);
    }

    /* #20 If a Thread is suspended/preempted:
     *       Store the preempted MP and the current time. */
    Rtm_Net_LeaveThread(FromThreadId, CoreId, currentTime);

    /* #30 If a Thread is started and the Thread interrupted a net MP:
     *       Start the preempted net MP and add the preemption runtime to this MP and all interrupted net MPs. */
    Rtm_Net_EnterThread(ToThreadId, CoreId, currentTime);
  }
#   if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
#   endif

  RTM_DUMMY_STATEMENT(CoreId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
} /* Rtm_Schedule */

/**********************************************************************************************************************
 * Rtm_EnterTaskFct()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(void, RTM_CODE) Rtm_EnterTaskFct(void)
{
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 If Rtm's functionality is enabled: */
#   if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
#   endif
  {
    uint8 errorCode = RTM_E_NO_ERROR;

    /* Only active measurements can be interrupted */
    Rtm_TaskType locTaskId;

    GetTaskID((TaskRefType)&locTaskId); /* PRQA S 3200 */ /* MD_Rtm_3200 */
  
    if (locTaskId < RTM_NUMBER_OF_TASKS)
    {
      Rtm_ThreadContext[locTaskId].prevActiveMP = Rtm_ActiveThreadId;
      Rtm_ActiveThreadId = locTaskId;

      if (Rtm_TaskContext[Rtm_TaskIndex[locTaskId]].prevActive < RTM_MEAS_SECTION_COUNT)
      {
#   if (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
        uint16_least i;
#   endif
        uint32 locPrevActive = Rtm_TaskContext[Rtm_TaskIndex[locTaskId]].prevActive;
        Rtm_MeasurementTimestampType currentTime;

        Rtm_Time_GetCurrentTime(&currentTime);
        /* Get the intermediate time */
        Rtm_Time_GetCounterDelta(Rtm_TaskContext[Rtm_TaskIndex[locTaskId]].startTime, currentTime, &currentTime, locPrevActive);

        /* There are measurement points set to net execution time and flat execution time. */
#   if (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) && (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */

        /* The first and all interrupted net MPs get the interrupting task runtime. */
        for (i = 0u; (i < RTM_MEAS_SECTION_COUNT) && (locPrevActive < RTM_MEAS_SECTION_COUNT); i++)
        {
          if ((i == 0u) || (Rtm_MeasurementPointConfigInfo[locPrevActive].measurementType == RTM_MEASUREMENT_TYPE_NET_EXECUTIONTIME))
          {
            Rtm_MeasurementPointInfo[locPrevActive].intermediateTime = Rtm_MeasurementPointInfo[locPrevActive].intermediateTime + currentTime;
          }

          locPrevActive = Rtm_MeasurementPointInfo[locPrevActive].prevActive;
        }
#   else

        /* All measurement points set to execution time are not nestable. */
#    if (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
        /* Add task runtime to each measurement point's intermediate time which is set to execution time. */
        for (i = 0u; (i < RTM_MEAS_SECTION_COUNT) && (locPrevActive < RTM_MEAS_SECTION_COUNT); i++)
        {
          Rtm_MeasurementPointInfo[locPrevActive].intermediateTime = Rtm_MeasurementPointInfo[locPrevActive].intermediateTime + currentTime;

          locPrevActive = Rtm_MeasurementPointInfo[locPrevActive].prevActive;
        }
#    endif

        /* All measurement points set to execution time are also nestable. */
#    if (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
        /* Add task runtime to the single interrupted measurement point (only one can simultaneously be active). */
        /* The following line cannot be executed with previous for loops, thus a memory corruption is not possible here. */
        Rtm_MeasurementPointInfo[locPrevActive].intermediateTime = Rtm_MeasurementPointInfo[locPrevActive].intermediateTime + currentTime;
#    endif

#   endif /* (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) && (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) */
        Rtm_ActiveMeasurementId = Rtm_TaskContext[Rtm_TaskIndex[locTaskId]].prevActive;
        Rtm_TaskContext[Rtm_TaskIndex[locTaskId]].prevActive = RTM_MEAS_SECTION_COUNT;
      }
    }
    else
    {
      errorCode = RTM_E_INVALID_CONFIGURATION;
    }

    /* ----- Development Error Report ------------------------------------------------------------ */
#   if (RTM_DEV_ERROR_REPORT == STD_ON)
    if (errorCode != RTM_E_NO_ERROR)
    {
      Rtm_DetReportError(RTM_SID_ENTERTASKFCT, errorCode);
    }
#   else
    RTM_DUMMY_STATEMENT(errorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#   endif
  }
#   if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
#   endif
} /* Rtm_EnterTaskFct */

/**********************************************************************************************************************
 * Rtm_LeaveTaskFct()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(void, RTM_CODE) Rtm_LeaveTaskFct(void)
{
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 If Rtm's functionality is enabled: */
#   if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
#   endif
  {
    uint8 errorCode = RTM_E_NO_ERROR;

    Rtm_TaskType locTaskId;
    GetTaskID((TaskRefType)&locTaskId); /* PRQA S 3200 */ /* MD_Rtm_3200 */

    if (locTaskId < RTM_NUMBER_OF_TASKS)
    {
      Rtm_ActiveThreadId = Rtm_ThreadContext[locTaskId].prevActiveMP;
    
      /* Only active measurements can be interrupted */
      if (Rtm_ActiveMeasurementId < RTM_MEAS_SECTION_COUNT)
      {
        Rtm_MeasurementTimestampType currentTime;
        Rtm_TaskContext[Rtm_TaskIndex[locTaskId]].prevActive = Rtm_ActiveMeasurementId;
        Rtm_ActiveMeasurementId = RTM_INACTIVE;
        Rtm_Time_GetCurrentTime(&currentTime);

        Rtm_TaskContext[Rtm_TaskIndex[locTaskId]].startTime = currentTime;
      }
    }
    else
    {
      errorCode = RTM_E_INVALID_CONFIGURATION;
    }

    /* ----- Development Error Report ------------------------------------------------------------ */
#   if (RTM_DEV_ERROR_REPORT == STD_ON)
    if (errorCode != RTM_E_NO_ERROR)
    {
      Rtm_DetReportError(RTM_SID_LEAVETASKFCT, errorCode);
    }
#   else
    RTM_DUMMY_STATEMENT(errorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#   endif
  }
#   if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
#   endif
} /* Rtm_LeaveTaskFct */

/**********************************************************************************************************************
 * Rtm_EnterIsrFct()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(void, RTM_CODE) Rtm_EnterIsrFct(void)
{
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 If Rtm's functionality is enabled: */
#   if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
#   endif
  {
    uint32 locIsrId = GetISRID();

    if (locIsrId < RTM_NUMBER_OF_ISRS)
    {
      Rtm_ThreadContext[locIsrId + RTM_NUMBER_OF_TASKS].prevActiveMP = Rtm_ActiveThreadId;
      Rtm_ActiveThreadId = locIsrId + RTM_NUMBER_OF_TASKS;
    }

    /* Only active measurements can be interrupted */
    if (Rtm_ActiveMeasurementId < RTM_MEAS_SECTION_COUNT)
    {
      /* Only the outer ISR may change the runtime of measurement points */
      if (Rtm_IsrContext.isrId == RTM_NUMBER_OF_ISRS)
      {
        Rtm_MeasurementTimestampType currentTime;
        Rtm_IsrContext.isrId = locIsrId;
        /* Safe measurement context */
        Rtm_IsrContext.prevActive = Rtm_ActiveMeasurementId;
        Rtm_ActiveMeasurementId = (uint32)RTM_PAUSED_BY_ISR;
        Rtm_Time_GetCurrentTime(&currentTime);
        Rtm_IsrContext.startTime = currentTime;
      }
    }
  }
#   if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
#   endif
} /* Rtm_EnterIsrFct */

/**********************************************************************************************************************
 * Rtm_LeaveIsrFct()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(void, RTM_CODE) Rtm_LeaveIsrFct(void)
{
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 If Rtm's functionality is enabled: */
#   if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
#   endif
  {
    uint32 locIsrId = GetISRID();

    if (locIsrId < RTM_NUMBER_OF_ISRS)
    {
      Rtm_ActiveThreadId = Rtm_ThreadContext[locIsrId + RTM_NUMBER_OF_TASKS].prevActiveMP;
    }

    /* Only active measurements can be interrupted */
    if (Rtm_ActiveMeasurementId == RTM_PAUSED_BY_ISR)
    {
      if (Rtm_IsrContext.isrId == locIsrId)
      {
#   if (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
        uint16_least i;
#   endif
        Rtm_MeasurementTimestampType currentTime;
        uint32 locPrevActive = Rtm_IsrContext.prevActive;
        /* Restore measurement context */
        Rtm_Time_GetCurrentTime(&currentTime);
        Rtm_Time_GetCounterDelta(Rtm_IsrContext.startTime, currentTime, &currentTime, locPrevActive);

        /* There are measurement points set to net execution time and flat execution time. */
#   if (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) && (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
        /* The last active measurement point and all net measurement points get the interrupting task runtime. */
        for (i = 0u; (i < RTM_MEAS_SECTION_COUNT) && (locPrevActive < RTM_MEAS_SECTION_COUNT); i++)
        {
          if ((i == 0u) || (Rtm_MeasurementPointConfigInfo[locPrevActive].measurementType == RTM_MEASUREMENT_TYPE_NET_EXECUTIONTIME))
          {
            Rtm_MeasurementPointInfo[locPrevActive].intermediateTime = Rtm_MeasurementPointInfo[locPrevActive].intermediateTime + currentTime;
          }

          locPrevActive = Rtm_MeasurementPointInfo[locPrevActive].prevActive;
        }
#   else

        /* If no measurement point is set to flat execution time. */
#    if (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
        /* Add task runtime to each measurement point's intermediate time which is set to execution time. */
        for (i = 0u; (i < RTM_MEAS_SECTION_COUNT) && (locPrevActive < RTM_MEAS_SECTION_COUNT); i++)
        {
          Rtm_MeasurementPointInfo[locPrevActive].intermediateTime = Rtm_MeasurementPointInfo[locPrevActive].intermediateTime + currentTime;

          locPrevActive = Rtm_MeasurementPointInfo[locPrevActive].prevActive;
        }
#    endif /* (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) */

        /* If no measurement point is set to net execution time. */
#    if (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
        /* Add task runtime to the single interrupted measurement point (only one can simultaneously be active). */
        Rtm_MeasurementPointInfo[locPrevActive].intermediateTime = Rtm_MeasurementPointInfo[locPrevActive].intermediateTime + currentTime;
#    endif /* (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) */

#   endif /* (RTM_NET_EXECUTION_TIME_AVAILABLE == STD_ON) && (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) */

        Rtm_ActiveMeasurementId = Rtm_IsrContext.prevActive;
        Rtm_IsrContext.prevActive = RTM_MEAS_SECTION_COUNT;
        Rtm_IsrContext.isrId = RTM_NUMBER_OF_ISRS;
      }
    }
  }
#   if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
#   endif
} /* Rtm_LeaveIsrFct */
#  endif /* (RTM_NET_RUNTIME_SUPPORT == STD_ON) */
# endif /* (RTM_MULTICORE_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 * Rtm_CheckTimerOverrun()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
 /* ESCAN00078841 */
FUNC(void, RTM_CODE) Rtm_CheckTimerOverrun(void) 
{
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 If Rtm's functionality is enabled:
   *       Enter exclusive area 0.
   *       Detect and handle counter overflow.
   *       Leave exclusive area 0. */
# if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
# endif
  {
    Rtm_MeasurementTimestampType currentTime;
    SchM_Enter_Rtm_RTM_EXCLUSIVE_AREA_0();
    Rtm_Time_GetCurrentTime(&currentTime);
    SchM_Exit_Rtm_RTM_EXCLUSIVE_AREA_0();

    RTM_DUMMY_STATEMENT(currentTime); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  }
# if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
# endif
} /* Rtm_CheckTimerOverrun */

/**********************************************************************************************************************
 * Rtm_GetCpuLoadHistogram()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6030 5 */ /* MD_MSR_STCYC */
/* PRQA S 6080 4 */ /* MD_MSR_STMIF */
/* PRQA S 3673 3 */ /* MD_Rtm_3673 */
FUNC(Std_ReturnType, RTM_CODE) Rtm_GetCpuLoadHistogram(
  const uint16 CoreId, 
  P2VAR(Rtm_CpuLoadHistogramType, AUTOMATIC, RTM_APPL_VAR) CpuLoadHistogram)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorCode = RTM_E_NO_ERROR;

  /* #10 If Rtm's functionality is enabled: */
# if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
# endif
  {
    /* ----- Development Error Checks ------------------------------------------------------------ */
    /* #20 If the parameters are invalid, indicate an error. */
# if (RTM_DEV_ERROR_DETECT == STD_ON)
    if (CoreId >= RTM_NUMBER_OF_CORES)
    {
      errorCode = RTM_E_WRONG_PARAMETERS;
    }
    else
    if (Rtm_InitState[CoreId] == RTM_UNINITIALIZED)
    {
      errorCode = RTM_E_UNINIT;
    }
    else
    if (CpuLoadHistogram == NULL_PTR)
    {
      errorCode = RTM_E_WRONG_PARAMETERS;
    }
    else
# endif
    /* ----- Implementation -------------------------------------------------------------------- */
    /* #30 Otherwise: */
    {
# if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0u)
      boolean isCoreIdValid;
      uint16 coreIndex = 0u;

      retVal = Rtm_CpuLoadHistogram_GetCoreIndexOfCoreId(CoreId, &coreIndex);

      if (retVal == E_OK) /* COV_RTM_CONFIG_CORE_INDEX_FROM_CORE_ID_ALWAYS_VALID_WHEN_DET_CHECKS_ENABLED */
      {
        isCoreIdValid = Rtm_CpuLoadHistogram_IsCoreIndexValidAndActive(coreIndex);

        /* #40 If the given core id is valid and its CPU load measurement is active: */
        /* PRQA S 2991, 2995 1 */ /* MD_Rtm_2991, MD_Rtm_2995 */
        if (isCoreIdValid == TRUE) /* COV_RTM_CPULOAD_MPS_ALL_ENABLED */
        {
          uint8_least percentileIndex;

          uint32 overallPercentileCount = Rtm_GetCpuLoadOverallPercentileCountOfCpuLoadPersistencyData(0u, coreIndex);

          /* #50 If there is any measured result, calculate the result percentiles and report them. */
          if (overallPercentileCount > 0u)
          {
            for (percentileIndex = 0u; percentileIndex < RTM_SIZE_OF_CPULOAD_PERCENTILES; percentileIndex++)
            {
              uint32 percentileCount = Rtm_GetCpuLoadPercentilesOfCpuLoadPersistencyData(0u, coreIndex)[percentileIndex];
              CpuLoadHistogram->Percentiles[percentileIndex] = (uint8)(((uint64)percentileCount * 100u) / overallPercentileCount);
            }
          }
          /* #60 Otherwise, there is no result yet, therefore set the results to default values. */
          else
          {
            for (percentileIndex = 0u; percentileIndex < RTM_SIZE_OF_CPULOAD_PERCENTILES; percentileIndex++)
            {
              CpuLoadHistogram->Percentiles[percentileIndex] = 0u;
            }
          }

          /* #70 Indicate success. */
          retVal = E_OK;
        }
      }
# else
      RTM_DUMMY_STATEMENT_CONST(CoreId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
      RTM_DUMMY_STATEMENT(CpuLoadHistogram); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif
    }

    /* ----- Development Error Report ------------------------------------------------------------ */
# if (RTM_DEV_ERROR_REPORT == STD_ON)
    if (errorCode != RTM_E_NO_ERROR)
    {
      Rtm_DetReportError(RTM_SID_GETCPULOADHISTOGRAM, errorCode);
    }
# else
    RTM_DUMMY_STATEMENT(errorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif
  }
# if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
# endif

  return retVal;
} /* Rtm_GetCpuLoadHistogram */

/**********************************************************************************************************************
 * Rtm_GetTaskResponseTimeHistogram()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 4 */ /* MD_MSR_STMIF */
/* PRQA S 3673 3 */ /* MD_Rtm_3673 */
FUNC(Std_ReturnType, RTM_CODE) Rtm_GetTaskResponseTimeHistogram(
  const uint16 TaskId, 
  P2VAR(Rtm_TaskResponseTimeHistogramType, AUTOMATIC, RTM_APPL_VAR) TaskResponseTimeHistogram)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorCode = RTM_E_NO_ERROR;

  /* #10 If Rtm's functionality is enabled: */
# if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
# endif
  {
    /* ----- Development Error Checks ------------------------------------------------------------ */
    /* #20 If the parameters are invalid, indicate an error. */
# if (RTM_DEV_ERROR_DETECT == STD_ON)
    if (TaskId >= RTM_NUMBER_OF_TASKS)
    {
      errorCode = RTM_E_WRONG_PARAMETERS;
    }
#  if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0u)
    else
    if (Rtm_TaskResponseTime_IsInitializedOnCoreOfTaskId(TaskId) == FALSE)
    {
      errorCode = RTM_E_UNINIT;
    }
#  endif
    else
    if (TaskResponseTimeHistogram == NULL_PTR)
    {
      errorCode = RTM_E_WRONG_PARAMETERS;
    }
    else
# endif
    /* ----- Implementation -------------------------------------------------------------------- */
    /* #30 Otherwise: */
    {
# if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0u)
      uint8 taskIndex = RTM_NUMBER_OF_TASKS;
      uint8 coreIndex = Rtm_GetSizeOfCommonConst(0u);

      /* #40 Try to get the core index and the task index required to access Rtm_CommonConst. */
      /*@ assert &coreIndex != NULL_PTR; */ /* VCA_RTM_VALID_POINTER */
      /*@ assert &taskIndex != NULL_PTR; */ /* VCA_RTM_VALID_POINTER */
      Rtm_TaskResponseTime_GetCoreIndexAndTaskIndexOfTaskId(TaskId, &coreIndex, &taskIndex);

      /* #50 If the given task id is valid: */
      if ((coreIndex < Rtm_GetSizeOfCommonConst(0u))
       && (taskIndex < Rtm_GetOsTaskInfoLengthOfCommonConst(coreIndex, 0u))) /* COV_RTM_TASKRESPONSETIME_COREANDTASKINDEX_ALWAYS_VALID_WHEN_DET_CHECKS_ENABLED */
      {
        uint8_least percentileIndex;

        uint32 overallPercentileCount = Rtm_GetTaskResponseTimeDataPtrOfCommonConst(coreIndex, 0u)[taskIndex].OverallPercentiles;

        /* #60 If there is any measured result, calculate the result percentiles and report them. */
        if (overallPercentileCount > 0u)
        {
          TaskResponseTimeHistogram->MaxRuntimeInUs = (Rtm_GetTaskResponseTimeDataPtrOfCommonConst(coreIndex, 0u)[taskIndex].MaxRuntimeInTicks * 1000u) / RTM_TICKS_PER_MILISECOND; /* VCA_RTM_STRUCT_WRT_UNCHANGED */

          for (percentileIndex = 0u; percentileIndex < RTM_SIZE_OF_TASKRESPONSETIME_PERCENTILES; percentileIndex++)
          {
            uint32 percentileCount = Rtm_GetTaskResponseTimeDataPtrOfCommonConst(coreIndex, 0u)[taskIndex].PercentileCount[percentileIndex];
            TaskResponseTimeHistogram->Percentiles[percentileIndex] = (uint8)(((uint64)percentileCount * 100u) / overallPercentileCount); /* VCA_RTM_TASK_RESPONSE_TIME_PERCENTILE_INDEX */
          }
        }
        /* #70 Otherwise, there is no result yet, therefore set the results to default values. */
        else
        {
          TaskResponseTimeHistogram->MaxRuntimeInUs = 0u; /* VCA_RTM_STRUCT_WRT_UNCHANGED */

          for (percentileIndex = 0u; percentileIndex < RTM_SIZE_OF_TASKRESPONSETIME_PERCENTILES; percentileIndex++)
          {
            TaskResponseTimeHistogram->Percentiles[percentileIndex] = 0u; /* VCA_RTM_TASK_RESPONSE_TIME_PERCENTILE_INDEX */
          }
        }

        /* #80 Indicate success. */
        retVal = E_OK;
      }
# else
      RTM_DUMMY_STATEMENT_CONST(TaskId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
      RTM_DUMMY_STATEMENT(TaskResponseTimeHistogram); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif
    }

    /* ----- Development Error Report ------------------------------------------------------------ */
# if (RTM_DEV_ERROR_REPORT == STD_ON)
    if (errorCode != RTM_E_NO_ERROR)
    {
      Rtm_DetReportError(RTM_SID_GETTASKRESPONSETIMEHISTOGRAM, errorCode);
    }
# else
    RTM_DUMMY_STATEMENT(errorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif
  }
# if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
# endif

  return retVal;
} /* Rtm_GetTaskResponseTimeHistogram */

#endif

/**********************************************************************************************************************
 * Rtm_GetTaskStackUsage()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 4 */ /* MD_MSR_STMIF */
/* PRQA S 3673 3 */ /* MD_Rtm_3673 */
FUNC(Std_ReturnType, RTM_CODE) Rtm_GetTaskStackUsage(
  const uint16 TaskId, 
  P2VAR(Rtm_TaskStackUsageInfoType, AUTOMATIC, RTM_APPL_VAR) TaskStackUsage)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorCode = RTM_E_NO_ERROR;

  /* #10 If Rtm's functionality is enabled: */
#if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
#endif
  {
    /* ----- Development Error Checks ------------------------------------------------------------ */
    /* #20 If the parameters are invalid, indicate an error. */
#if (RTM_DEV_ERROR_DETECT == STD_ON)
    if (TaskId >= RTM_NUMBER_OF_TASKS)
    {
      errorCode = RTM_E_WRONG_PARAMETERS;
    }
# if (RTM_TASK_STACK_USAGE == STD_ON)
    else
    if (Rtm_TaskStackUsage_IsBswCoreInitialized() == FALSE)
    {
      errorCode = RTM_E_UNINIT;
    }
# endif
    else
    if (TaskStackUsage == NULL_PTR)
    {
      errorCode = RTM_E_WRONG_PARAMETERS;
    }
    else
#endif
    /* ----- Implementation -------------------------------------------------------------------- */
    /* #30 Otherwise: */
    {
#if (RTM_TASK_STACK_USAGE == STD_ON)
      /* #40 Set the return values and indicate success. */
      TaskStackUsage->MaxStackUsage = Rtm_MaxTaskStackUsage[TaskId];
      TaskStackUsage->TaskStackSize = Rtm_GetMaxStackOfOsTaskInfo(Rtm_GetTaskIndexToOsTaskInfoOfIndexToOsTaskInfo(TaskId, 0u), 0u);

      retVal = E_OK;
#else
      RTM_DUMMY_STATEMENT_CONST(TaskId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
      RTM_DUMMY_STATEMENT(TaskStackUsage); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif
    }

    /* ----- Development Error Report ------------------------------------------------------------ */
#if (RTM_DEV_ERROR_REPORT == STD_ON)
    if (errorCode != RTM_E_NO_ERROR)
    {
      Rtm_DetReportError(RTM_SID_GETTASKSTACKUSAGE, errorCode);
    }
#else
    RTM_DUMMY_STATEMENT(errorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif
  }
#if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
#endif

  return retVal;
} /* Rtm_GetTaskStackUsage */

/**********************************************************************************************************************
 * Rtm_ClearResults()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6030 4 */ /* MD_MSR_STCYC */
/* PRQA S 6080 3 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, RTM_CODE) Rtm_ClearResults(
  const uint16 CoreId,
  Rtm_ClearResultsType ResultsToBeCleared)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorCode = RTM_E_NO_ERROR;

  /* #10 If Rtm's functionality is enabled: */
# if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
# endif
  {
    /* ----- Development Error Checks ------------------------------------------------------------ */
    /* #20 If the parameters are invalid, indicate an error. */
# if (RTM_DEV_ERROR_DETECT == STD_ON)
    if (CoreId >= RTM_NUMBER_OF_CORES)
    {
      errorCode = RTM_E_WRONG_PARAMETERS;
    }
    else
    if (Rtm_InitState[CoreId] == RTM_UNINITIALIZED)
    {
      errorCode = RTM_E_UNINIT;
    }
    else
# endif
    /* ----- Implementation -------------------------------------------------------------------- */
    /* #30 Otherwise: */
    {
      RTM_DUMMY_STATEMENT_CONST(CoreId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
      /* #40 Indicate success. */
      retVal = E_OK;

      switch(ResultsToBeCleared)
      {
      /* #50 If all results are to be cleared, clear CPU load histogram, task response time, and task stack usage
       *       results. */
        case(RTM_ALL_RESULTS): /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
# if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0)
          Rtm_CpuLoadHistogram_ClearResults(CoreId);
# endif
# if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0)
          Rtm_TaskResponseTime_ClearResults(CoreId);
# endif
# if (RTM_TASK_STACK_USAGE == STD_ON)
          if (Rtm_IsBSWCoreOfCommonConst(CoreId, 0u)) /* COV_RTM_CONDITION_ALWAYS_TRUE */
          {
            Rtm_TaskStackUsage_ClearResults();
          }
# endif
          break;

      /* #60 Otherwise if CPU load histogram results are to be cleared, forward the request. */
        case(RTM_CPU_LOAD_HISTOGRAM_RESULTS): /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
# if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0)
          Rtm_CpuLoadHistogram_ClearResults(CoreId);
# endif
          break;

      /* #70 Otherwise if task response time results are to be cleared, forward the request. */
        case(RTM_TASK_RESPONSE_TIME_RESULTS): /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
# if (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES > 0)
          Rtm_TaskResponseTime_ClearResults(CoreId);
# endif
          break;

      /* #80 Otherwise if task stack usage results are to be cleared and the selected core is the BSW core:
       *       Forward the request. */
        case(RTM_TASK_STACK_USAGE_RESULTS): /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
# if (RTM_TASK_STACK_USAGE == STD_ON)
          if (Rtm_IsBSWCoreOfCommonConst(CoreId, 0u)) /* COV_RTM_CONDITION_ALWAYS_TRUE */
          {
            Rtm_TaskStackUsage_ClearResults();
          }
          else
          {
            retVal = E_NOT_OK;
          }
# endif
          break;

      /* #90 Otherwise, indicate that the service failed. */
        default:
          retVal = E_NOT_OK;
          break;
      }
    }

    /* ----- Development Error Report ------------------------------------------------------------ */
# if (RTM_DEV_ERROR_REPORT == STD_ON)
    if (errorCode != RTM_E_NO_ERROR)
    {
      Rtm_DetReportError(RTM_SID_CLEARRESULTS, errorCode);
    }
# else
    RTM_DUMMY_STATEMENT(errorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif
  }
# if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
# endif

  return retVal;
} /* Rtm_ClearResults */

#if (RTM_TIME_MEASUREMENT == STD_ON)

/**********************************************************************************************************************
 * Rtm_GetMeasurementItem()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 7 */ /* MD_MSR_STMIF */
/* PRQA S 6030 6 */ /* MD_MSR_STCYC */
/* PRQA S 6010 5 */ /* MD_MSR_STPTH */
/* PRQA S 3673 4 */ /* MD_Rtm_3673 */
FUNC(Std_ReturnType, RTM_CODE) Rtm_GetMeasurementItem(
  const uint32 MeasurementId, 
  const Rtm_ItemType ItemType, 
  P2VAR(uint32, AUTOMATIC, RTM_APPL_VAR) ItemValuePtr)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorCode = RTM_E_NO_ERROR;

  /* #10 If Rtm's functionality is enabled: */
# if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
# endif
  {
    /* ----- Development Error Checks ------------------------------------------------------------ */
    /* #20 If the parameters are invalid, indicate an error. */
# if (RTM_DEV_ERROR_DETECT == STD_ON)
    if (ItemValuePtr == NULL_PTR)
    {
      errorCode = RTM_E_WRONG_PARAMETERS;
    }
    else
# endif
    /* #30 Otherwise: */
    {
      /* ----- Implementation -------------------------------------------------------------------- */
# if (RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF)
      uint32 locMeasId = MeasurementId;
      uint16 locCoreIndex = RTM_NUMBER_OF_CORES;
      boolean isMpValid = Rtm_Cpu_IsMeasurementIdValidCpuLoadMP(locMeasId, &locCoreIndex);

      if (isMpValid == TRUE)
      {
        /*@ assert locCoreIndex < RTM_NUMBER_OF_CORES; */ /* VCA_RTM_VALID_CORE_INDEX */

        uint32 averageRuntime = Rtm_GetAverageOfMainFunctionRuntimeData(0u, locCoreIndex);

        if (averageRuntime == 0u)
        {
          averageRuntime = RTM_MAINFCT_CYCLE_TIME * RTM_TICKS_PER_MILISECOND;
          Rtm_SetAverageOfMainFunctionRuntimeData(0u, averageRuntime, locCoreIndex);
        }

        switch(ItemType)
        {
        /* #50 If the average CPU load is requested:
         *       Enter exclusive area 0.
         *       Calculate the average CPU load.
         *       Leave exclusive area 0. */
        case (RTM_ITEM_CPU_LOAD_AVERAGE):
          SchM_Enter_Rtm_RTM_EXCLUSIVE_AREA_0();

          if (Rtm_Results[locMeasId].count > 0u)
          {
            *ItemValuePtr = (uint32)((100u * (((Rtm_Results[locMeasId].time) / (Rtm_Results[locMeasId].count)))) 
                                   / averageRuntime);
          }
          else
          {
            *ItemValuePtr = 0u;
          }
          retVal = E_OK;
          SchM_Exit_Rtm_RTM_EXCLUSIVE_AREA_0();
        break;

        /* #60 Otherwise, if the current CPU load is requested:
         *       Enter exclusive area 0.
         *       Calculate the current CPU load.
         *       Leave exclusive area 0. */
        case (RTM_ITEM_CPU_LOAD_CURRENT): /* ESCAN00079844 */
          {
            uint32 deltaTime;
            SchM_Enter_Rtm_RTM_EXCLUSIVE_AREA_0();

            deltaTime = Rtm_GetDeltaOfMainFunctionRuntimeData(0u, locCoreIndex);

            if (deltaTime == 0u)
            {
              deltaTime = (RTM_MAINFCT_CYCLE_TIME * RTM_TICKS_PER_MILISECOND);
              Rtm_SetDeltaOfMainFunctionRuntimeData(0u, deltaTime, locCoreIndex);
            }
            *ItemValuePtr = (uint32)((100u * Rtm_GetCpuLoadTime(locCoreIndex)) / deltaTime);

            retVal = E_OK;
            SchM_Exit_Rtm_RTM_EXCLUSIVE_AREA_0();
          }
        break;

        /* #70 Otherwise, if the minimum CPU load is requested, calculate it. */
        case (RTM_ITEM_MIN):
          if (Rtm_Results[locMeasId].min < 0xFFFFFFFFu)
          {
            *ItemValuePtr = (uint32)((100u * (Rtm_Results[locMeasId].min)) / averageRuntime);
          }
          else
          {
            *ItemValuePtr = 0u;
          }
          retVal = E_OK;
        break;

        /* #80 Otherwise, if the maximum CPU load is requested, calculate it. */
        case (RTM_ITEM_MAX):
          *ItemValuePtr = (uint32)((100u * (Rtm_Results[locMeasId].max)) / averageRuntime);
          retVal = E_OK;
        break;

        /* #90 Otherwise, request is invalid. */
        default: /* PRQA S 2018 */ /* MD_Rtm_2018 */
          *ItemValuePtr = 0u;
        break;
        }

        if (*ItemValuePtr > 100u)
        {
          *ItemValuePtr = 100u;
        }
      }
# else /* (RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF) */
      RTM_DUMMY_STATEMENT_CONST(MeasurementId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
      RTM_DUMMY_STATEMENT_CONST(ItemType); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
      RTM_DUMMY_STATEMENT(ItemValuePtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif /* (RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF) */
    }
    
    /* ----- Development Error Report ------------------------------------------------------------ */
#  if (RTM_DEV_ERROR_REPORT == STD_ON)
    if (errorCode != RTM_E_NO_ERROR)
    {
      Rtm_DetReportError(RTM_SID_GETMEASUREMENTITEM, errorCode);
    }
#  else
    RTM_DUMMY_STATEMENT(errorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#  endif
  }
# if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
# endif

  return retVal;
} /* Rtm_GetMeasurementItem */

# if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0u)
/**********************************************************************************************************************
 * Rtm_CpuLoadHistogram_Calculate()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, RTM_CODE) Rtm_CpuLoadHistogram_Calculate(
  uint16 CoreIndex)
{
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #-- If the CPU load measurement is active: */
  if (Rtm_IsMeasurementActiveOfCpuLoadData(0u, CoreIndex))
  {
    uint32 cpuLoadTime;
    uint32 accumulatedTime = Rtm_GetAccumulatedTimeOfHyperPeriodData(0u, CoreIndex);
    uint16 mainFunctionCounter;

    cpuLoadTime = Rtm_GetCpuLoadTime(CoreIndex);

    /* #-- Accumulate the current CPU load and increment the main function counter. */
    accumulatedTime += cpuLoadTime;
    Rtm_SetAccumulatedTimeOfHyperPeriodData(0u, accumulatedTime, CoreIndex);

    Rtm_IncMainFunctionCounterOfHyperPeriodData(0u, CoreIndex);

    mainFunctionCounter = Rtm_GetMainFunctionCounterOfHyperPeriodData(0u, CoreIndex);

    /* #-- If the hyperperiod is over:
     *       Calculate and set the percentile.
     *       If the percentile index is out of range, change it to maximum valid value.
     *       Increment the overall percentile count and the percentile indicated by the index.
     *       Reset the hyperperiod main function counter and the accumulated CPU load. */
    if (mainFunctionCounter >= RTM_CPULOAD_HYPERPERIOD_MAX_MFC)
    {
      uint32 percentileCount;
      uint32 hyperPeriodCpuLoad = 0u;
      uint32 average;
      uint16 percentileIndex;

      average = Rtm_GetAverageOfMainFunctionRuntimeData(0u, CoreIndex);

      if (average > 0u)
      {
        hyperPeriodCpuLoad = (uint32)((accumulatedTime * 100u) / (RTM_CPULOAD_HYPERPERIOD_MAX_MFC * average));
      }
      percentileIndex = (uint16)(hyperPeriodCpuLoad / RTM_NUMBER_OF_CPULOAD_PERCENTILES);

      if (percentileIndex > RTM_NUMBER_OF_CPULOAD_PERCENTILES)
      {
        percentileIndex = RTM_NUMBER_OF_CPULOAD_PERCENTILES;
      }
      Rtm_IncCpuLoadOverallPercentileCountOfCpuLoadPersistencyData(0u, CoreIndex);
      percentileCount = Rtm_GetCpuLoadPercentilesOfCpuLoadPersistencyData(0u, CoreIndex)[percentileIndex];
      percentileCount++;
      Rtm_GetCpuLoadPercentilesOfCpuLoadPersistencyData(0u, CoreIndex)[percentileIndex] = percentileCount;
      Rtm_SetMainFunctionCounterOfHyperPeriodData(0u, 0u, CoreIndex);
      Rtm_SetAccumulatedTimeOfHyperPeriodData(0u, 0u, CoreIndex);

      Rtm_CpuLoadHistogram_AvoidOverrun(CoreIndex);
    }
  }
} /* Rtm_CpuLoadHistogram_Calculate */
# endif
#endif /* RTM_TIME_MEASUREMENT == STD_ON */

/**********************************************************************************************************************
 * Rtm_InitMemory()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6010 1 */ /* MD_MSR_STPTH */
FUNC(void, RTM_CODE) Rtm_InitMemory(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint16_least i;
  
  /* ----- Implementation ---------------------------------------------------------------------- */
#if (RTM_TIME_MEASUREMENT == STD_ON)
  /* #10 Initialize MP specific data. */
  for (i = 0u; i < RTM_MEAS_SECTION_COUNT; i++)
  {
# if (RTM_NET_RUNTIME_SUPPORT == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
    Rtm_MeasurementPointInfo[i].intermediateTime = 0u;
    Rtm_MeasurementPointInfo[i].prevActive = RTM_INACTIVE;
    Rtm_MeasurementPointInfo[i].threadContext = RTM_NUMBER_OF_THREADS;
# endif
# if ((RTM_NESTING_COUNTER == STD_ON) || (RTM_DEV_ERROR_DETECT == STD_ON)) /* COV_RTM_CONFIG_CONDITION_DEV_DETECT_ALWAYS_TRUE */
    Rtm_MeasurementNestingCtr[i] = (sint8)0;
# endif
    Rtm_StartTimeStamps[i] = 0u;
    Rtm_Results[i].time = 0u;
    Rtm_Results[i].count = 0u;
    Rtm_Results[i].min = (uint32) 0xFFFFFFFFu;
    Rtm_Results[i].max = 0u;
# if (RTM_TIMER_OVERRUN_SUPPORT == STD_ON)
    Rtm_PrevOverrunCounterValues[i] = 0u;
# endif
  }

  for (i = 0u; i < RTM_CTRL_VECTOR_LEN; i++)
  {
    Rtm_MeasurementConfig[i] = 0u;
    Rtm_Ctrl[i] = Rtm_CtrlConfig[i]; /* ESCAN00077449 */
  }

# if (RTM_NET_RUNTIME_SUPPORT == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
  /* #20 Initialize thread context specific data. */
  for (i = 0u; i < RTM_NUMBER_OF_TASKS; i++)
  {
    Rtm_TaskContext[i].intermediateTime = Rtm_TaskContextInit[i].intermediateTime;
    Rtm_TaskContext[i].prevActive = Rtm_TaskContextInit[i].prevActive;
    Rtm_TaskContext[i].startTime = Rtm_TaskContextInit[i].startTime;
    Rtm_TaskContext[i].taskId = Rtm_TaskContextInit[i].taskId; /* ESCAN00087879 */
  }

  for (i = 0u; i < RTM_NUMBER_OF_THREADS; i++)
  {
    Rtm_ThreadContext[i].preemptionTime = Rtm_ThreadContextInit[i].preemptionTime;
    Rtm_ThreadContext[i].prevActiveMP = Rtm_ThreadContextInit[i].prevActiveMP;
  }

  /* Initialize ISR context */
  Rtm_ActiveMeasurementId = RTM_INACTIVE;
  Rtm_ActiveThreadId = RTM_NUMBER_OF_THREADS;

  Rtm_IsrContext.intermediateTime = Rtm_IsrContextInit.intermediateTime;
  Rtm_IsrContext.prevActive = Rtm_IsrContextInit.prevActive;
  Rtm_IsrContext.startTime = Rtm_IsrContextInit.startTime;
  Rtm_IsrContext.isrId = Rtm_IsrContextInit.isrId;
# endif

# if (RTM_FLAT_EXECUTION_TIME_AVAILABLE == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
  Rtm_OverheadCorrection.execTime_Flat_EnableISRs = 0u;
  Rtm_OverheadCorrection.execTime_Flat_DisableISRs = 0u;
# endif

  /* #30 Initialize timer overrun specific data. */
# if (RTM_TIMER_OVERRUN_SUPPORT == STD_ON)
  Rtm_TimerOverrunCnt = 0u;
  Rtm_PrevTimerValue = 0u;
# endif

  /* #40 Initialize multicore specific data. */
# if (RTM_MULTICORE_SUPPORT == STD_ON)
  for (i = 0u; i < RTM_NUMBER_OF_DISABLED_INT; i++)
  {
    Rtm_DisableInterruptFlag[i] = 0u;
  }
# endif
#endif /* RTM_TIME_MEASUREMENT == STD_ON */

  /* #60 Set RTM state on all cores to uninitialized. */
  for (i = 0u; i < RTM_NUMBER_OF_CORES; i++)
  {
    Rtm_InitState[i] = RTM_UNINITIALIZED;
  }

  /* #70 Initialize SafeBSW specific data. */
#if (RTM_CONTROL == STD_ON)
  Rtm_ControlState       = RTM_CONTROL_STATE_ENABLED;
  Rtm_ControlDeniedCount = 0u;
#endif
} /* Rtm_InitMemory */

/**********************************************************************************************************************
 * Rtm_Init()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
#if (RTM_MULTICORE_SUPPORT == STD_OFF)
FUNC(void, RTM_CODE) Rtm_Init(void)
#else
FUNC(void, RTM_CODE) Rtm_Init(
  const uint16 CoreIndex)
#endif
{
  /* ----- Implementation -------------------------------------------------------------------- */
  /* #10 If Rtm's functionality is enabled: */
#if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
#endif
  {
#if (RTM_MULTICORE_SUPPORT == STD_OFF)
    uint16 coreIndex = 0u;
#else
    uint16 coreIndex = CoreIndex;
#endif

#if (RTM_TIME_MEASUREMENT == STD_ON)

    /* #20 Initialized the CPU load histogram, the task response time histogram, and task stack usage data. */
    Rtm_Init_PersistencyData(coreIndex);

    /* #30 Set task mapping. */
# if (RTM_NET_RUNTIME_SUPPORT == STD_ON) /* COV_RTM_MSR_UNSUPPORTED */
    Rtm_Init_TaskContext();
# endif

    Rtm_SetDeltaOfMainFunctionRuntimeData(0u, 0u, coreIndex);
    Rtm_SetLastCallOfMainFunctionRuntimeData(0u, 0u, coreIndex);
    Rtm_SetAverageOfMainFunctionRuntimeData(0u, 0u, coreIndex);
    Rtm_SetAverageCounterOfMainFunctionRuntimeData(0u, 0u, coreIndex);

    /* #40 Initialize CPU load specific data. */
# if (RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF)
    Rtm_Init_ActivateCpuLoadMeasurementPointOfCoreIndex(coreIndex);

    Rtm_SetThresholdOfCpuLoadData(0u, 0u, coreIndex);
    Rtm_SetCollectedTimeOfCpuLoadData(0u, 0u, coreIndex);
    Rtm_SetStartTimeStampOfCpuLoadData(0u, 0u, coreIndex);
    Rtm_SetMeasurementWasStoppedOfCpuLoadData(0u, TRUE, coreIndex);

    Rtm_SetLastTicksOfCpuLoadData(0u, 0u, coreIndex);

    Rtm_SetCpuLoadTime(0u, coreIndex);
# endif

    /* #50 Initialize Cpu load histogram specific data. */
#  if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0u)
    Rtm_SetAccumulatedTimeOfHyperPeriodData(0u, 0u, coreIndex);
    Rtm_SetMainFunctionCounterOfHyperPeriodData(0u, 0u, coreIndex);
#  endif

    /* #60 If the currently active core is the BSW core: */
    if (Rtm_IsBSWCoreOfCommonConst(coreIndex, 0u)) /* COV_RTM_CONDITION_ALWAYS_TRUE */
    {
      /* #70 Initialize common Rtm control data. */
# if (RTM_MULTICORE_SUPPORT == STD_ON)
      Rtm_SendNextMainFunction = FALSE;
# else
      Rtm_LiveMeasurement = FALSE;
# endif

      Rtm_CalculatedCtrEndVal = 0x00u;
      Rtm_MeasTimeCorrection = 0x00;
      Rtm_MeasurementTimer = 0x00u;

      Rtm_LastCommandToEcu = RTM_NULL;
      Rtm_Cmd = RTM_NULL;
      Rtm_Resp = RTM_NULL;
# if (RTM_XCP_IS_PRESENT == STD_ON)
      Rtm_XcpState = XCP_EVENT_NOP;
# endif

      Rtm_AverageMainFunctionCycleTime = 0x00u;
      Rtm_MainFunctionCounter = 0x00u;
      Rtm_EndlessMeasurement = FALSE;
      Rtm_AvgMainFunctionCycleTimeCalcCounter = 0x00u;
      Rtm_LastMainFunctionTime = 0x00u;
    }
#endif /* RTM_TIME_MEASUREMENT == STD_ON */

#if (RTM_TASK_STACK_USAGE == STD_ON)
    if (Rtm_IsBSWCoreOfCommonConst(coreIndex, 0u)) /* COV_RTM_CONDITION_ALWAYS_TRUE */
    {
      Rtm_Init_PersistencyDataOfTaskStackUsage();
    }
#endif

    /* #80 Set the Rtm for this core to initialized. */
    Rtm_InitState[coreIndex] = RTM_INITIALIZED;
  }
#if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
#endif
} /* Rtm_Init */

/**********************************************************************************************************************
 * Rtm_Shutdown()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, RTM_CODE) Rtm_Shutdown(void)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #10 If Rtm's functionality is enabled: */
# if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
# endif
  {
# if (RTM_TASK_STACK_USAGE == STD_ON)
    uint16_least osTaskIndex;
    boolean hasAnythingChanged = FALSE;

    /* #20 Iterate over all available tasks. */
    for (osTaskIndex = 0u; osTaskIndex < RTM_NUMBER_OF_TASKS; osTaskIndex++)
    {
      uint32 maxStackUsage = Os_GetTaskStackUsage(Rtm_GetTaskIdOfOsTaskInfo(Rtm_GetTaskIndexToOsTaskInfoOfIndexToOsTaskInfo(osTaskIndex, 0u), 0u));

      /* #30 Check for each task that if the current max stack usage is higher than the cached value.
       *       Cache the higher values. */
      if (maxStackUsage > Rtm_MaxTaskStackUsage[osTaskIndex])
      {
        Rtm_MaxTaskStackUsage[osTaskIndex] = maxStackUsage;
        hasAnythingChanged = TRUE;
      }
    }

    /* #40 If any max stack usage value changed, request to persist all values. */
    if (hasAnythingChanged == TRUE)
    {
      (void)NvM_SetRamBlockStatus((NvM_BlockIdType)Rtm_GetTaskStackNvMSnv(0u), TRUE);
    }
# endif
  }
# if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
# endif

  return E_OK;
} /* Rtm_Shutdown */

/**********************************************************************************************************************
 * Rtm_MainFunction()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 6 */ /* MD_MSR_STCAL */
/* PRQA S 6080 5 */ /* MD_MSR_STMIF */
#if (RTM_MULTICORE_SUPPORT == STD_ON)
FUNC(uint8, RTM_CODE) Rtm_MainFunction(
  const uint16 CoreIndex)
#else
FUNC(void, RTM_CODE) Rtm_MainFunction(void)
#endif
{
  /* ----- Local Variables --------------------------------------------------------------------- */
#if (RTM_TIME_MEASUREMENT == STD_ON)
  uint8 sendEvent0 = FALSE; /* PRQA S 2981 */ /* MD_Rtm_2981 */
  uint8 errorCode = RTM_E_NO_ERROR;
#endif

  /* #10 If the Rtm is currently enabled: */
#if (RTM_CONTROL == STD_ON)
  if (Rtm_ControlState == RTM_CONTROL_STATE_ENABLED)
#endif
  {
    /* #20 If the core ID is invalid, report a DET error. */
    /* #30 If the current core is the BSW core: */
#if (RTM_TIME_MEASUREMENT == STD_ON)
# if (RTM_MULTICORE_SUPPORT == STD_ON)
    /* ----- Development Error Checks ------------------------------------------------------------ */
#  if (RTM_DEV_ERROR_DETECT == STD_ON)
    if (CoreIndex >= RTM_NUMBER_OF_CORES)
    {
      errorCode = RTM_E_WRONG_PARAMETERS;
    }
    else
#  endif
    if (Rtm_InitState[CoreIndex] == RTM_INITIALIZED)
    {
      Rtm_MeasurementTimestampType currentTime;

      Rtm_Time_GetCurrentTime(&currentTime);

      Rtm_Time_MainFunctionRuntimeUpdate(currentTime, CoreIndex);

      if (Rtm_IsBSWCoreOfCommonConst(CoreIndex, 0u)) /* COV_RTM_CONDITION_ALWAYS_TRUE */
# endif
      {
        /* ----- Implementation -------------------------------------------------------------------- */
        /* #40 If Rtm is already initialized: */
# if (RTM_MULTICORE_SUPPORT == STD_OFF)
        if (Rtm_InitState[0u] == RTM_INITIALIZED)
# endif
        {
          Rtm_TimestampType timeToMeasure;
          uint8 cmd;

# if (RTM_MULTICORE_SUPPORT == STD_OFF)
          Rtm_MeasurementTimestampType currentTime;

          /* #50 Enter exclusive area 2. */
          SchM_Enter_Rtm_RTM_EXCLUSIVE_AREA_2();

          Rtm_Time_GetCurrentTime(&currentTime);

          Rtm_Time_MainFunctionRuntimeUpdate(currentTime, 0u);

# endif

          /* #60 Get requested command and requested measurement duration. */
          cmd = (uint8)(Rtm_Cmd >> 28u);
          timeToMeasure = (uint16)Rtm_Cmd;

          /* #70 If delayed sending was requested, send in this Rtm_MainFunction-Cycle.
           *     Otherwise, execute the requested command. */
# if (RTM_MULTICORE_SUPPORT == STD_ON)
          if (Rtm_SendNextMainFunction == TRUE)
          {
            Rtm_SendNextMainFunction = FALSE;
            sendEvent0 = TRUE;
          }
          else
# endif
          {
            sendEvent0 = Rtm_MeasCtr_MeasurementControl(currentTime, timeToMeasure, cmd);
          }

          /* #80 Calculate new CPU load measurement result. */
# if (RTM_MULTICORE_SUPPORT == STD_OFF)
#  if (RTM_CPU_LOAD_CONTROL_MODE != RTM_CPU_LOAD_CONTROL_OFF)
          Rtm_Cpu_CalculateCurrentCPULoad(0u);
#  endif

#  if (RTM_NUMBER_OF_CPULOAD_PERCENTILES > 0u)
          /* #-- Calculate the percentile of CPU load measurement if hyperperiod is elapsed and CPU load measurement is active. */
          Rtm_CpuLoadHistogram_Calculate(0u);
#  endif

          /* #90 Leave exclusive area 2. */
          SchM_Exit_Rtm_RTM_EXCLUSIVE_AREA_2();

          /* #100 Transmit current data if requested. */
#  if (RTM_XCP_IS_PRESENT == STD_ON)
          if ((sendEvent0 == TRUE) || (Rtm_LiveMeasurement == TRUE))
          {
            Rtm_XcpState = Xcp_Event(EV_RTM);
          }
#  else
          RTM_DUMMY_STATEMENT(sendEvent0); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#  endif
# endif
        }
      }
# if (RTM_MULTICORE_SUPPORT == STD_ON)
    }
    else
    {
      /* Intentionally do nothing. */
    }
# endif

    /* ----- Development Error Report ------------------------------------------------------------ */
# if (RTM_DEV_ERROR_REPORT == STD_ON) && (RTM_MULTICORE_SUPPORT == STD_ON)
    if (errorCode != RTM_E_NO_ERROR)
    {
      Rtm_DetReportError(RTM_SID_MAINFUNCTION, errorCode);
    }
# else
    RTM_DUMMY_STATEMENT(errorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif

#else /* (RTM_TIME_MEASUREMENT == STD_ON) */
# if (RTM_MULTICORE_SUPPORT == STD_ON)
    RTM_DUMMY_STATEMENT(CoreIndex); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif
#endif /* (RTM_TIME_MEASUREMENT == STD_ON) */
  }
#if (RTM_CONTROL == STD_ON)
  else
  {
    Rtm_ControlDeniedCount++;
  }
#endif

#if (RTM_MULTICORE_SUPPORT == STD_ON)
# if (RTM_TIME_MEASUREMENT == STD_ON)
  return sendEvent0;
# else
  return FALSE;
# endif
#endif
} /* Rtm_MainFunction */

#define RTM_STOP_SEC_CODE
#include "Rtm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * GLOBAL MISRA / PCLINT JUSTIFICATION
 ********************************************************************************************************************/
/* module specific MISRA deviations:

   MD_Rtm_883:      MISRA rule: 19.15: Precautions shall be taken in order to prevent the contents of a header file
                                       being included twice.
     Reason:        QAC does not find the "#if !defined / #define / #endif" in Rtm_Cfg.h although it exists.
     Risk:          Could be removed without being detected by QAC (=> Compile Error).
     Prevention:    Code inspection and test of the different variants in the component test.

   MD_Rtm_1297:     MISRA rule: 10.3: The value of an expression shall not be assigned to an object with a narrower
                                      essential type or of a different essential type category.
     Reason:        The ComStackLib automatically generates the OS type 'CoreIdType' for the partitionSNV, but a SNV
                    is usually an integer value.
     Risk:          No risk.
     Prevention:    Not required.

   MD_Rtm_1514:     MISRA rule: 8.9: The object '%2s' is only referenced by function '%1s', in the translation unit
                                     where it is defined.
     Reason:        If the array 'Rtm_MaxTaskStackUsage' exists, it is used as RAM block by NvM. Therefore, it must
                    be externally visible.
     Risk:          No risk.
     Prevention:    Not required.

   MD_Rtm_2018:     MISRA rule: 14.1: There shall be no unreachable code.
     Reason:        The default path cannot be reached if DET is enabled, but a default path in a switch or
                    if-/if-else-statement is always required.
     Risk:          No risk.
     Prevention:    Not required.

   MD_Rtm_2981:     MISRA rule: 2.2: This initialization is redundant. The value of this object is never used before being modified.
     Reason:        Depending on the configuration it is possible that the variable is always overwritten. No error expected.
     Risk:          No risk.
     Prevention:    Not required.

   MD_Rtm_2991:     MISRA rule: 14.3: The value of this 'if' controlling expression is always 'true'.
     Reason:        Depending on the configuration it is possible that the variable is always 'true'. No error expected.
     Risk:          No risk.
     Prevention:    Not required.

   MD_Rtm_2995:     MISRA rule: 2.2: The result of this logical operation is always 'true'.
     Reason:        Depending on the configuration it is possible that the variable is always 'true'. No error expected.
     Risk:          No risk.
     Prevention:    Not required.

   MD_Rtm_3200:     MISRA rule: 17.7: '%s' returns a value which is not being used.
     Reason:        The API is defined by OS. To be robust against defining GetTaskID as code 
                    ("#define GetTaskID { ... }") the void cast is omitted.
     Risk:          The return value is not handled by RTM, thus the compiler has to care about it.
     Prevention:    Not required.

   MD_Rtm_3408:     MISRA rule: 8.4: '%s' has external linkage and is being defined without any previous declaration.
     Reason:        This violation only occurs if RTM_LOCAL is defined to nothing.
     Risk:          The global variables could be re-defined in another file.
     Prevention:    Define RTM_LOCAL as static.

   MD_Rtm_3673:     MISRA rule: 8.13: The object addressed by the pointer parameter '%s' is not modified and so the
                                      pointer could be of type 'pointer to const'.
     Reason:        This violation only occurs if RTM_CPU_LOAD_CONTROL_MODE is set to RTM_CPU_LOAD_CONTROL_OFF 
                    because the function Rtm_GetMeasurementItem does not return a value in this case.
     Risk:          The return value is not handled by RTM, thus the compiler has to care about it.
     Prevention:    Not required.
*/

/* COV_JUSTIFICATION_BEGIN

\ID COV_RTM_MSR_COMPATIBILITY
\ACCEPT TX
\ACCEPT XF
\ACCEPT XX
\REASON [COV_MSR_COMPATIBILITY]

\ID COV_RTM_MSR_CONFIG
\ACCEPT XF
\ACCEPT XX
\ACCEPT XF xx xx xf
\REASON [COV_MSR_CONFIG]

\ID COV_RTM_MSR_UNSUPPORTED
\ACCEPT XF
\ACCEPT TF xf tf tf
\REASON [COV_MSR_UNSUPPORTED]

\ID COV_RTM_CONDITION_ALWAYS_TRUE
\ACCEPT TX
\REASON The check of Rtm_IsBSWCoreOfCommonConst(CoreId, 0u) is always true in single core configurations.

\ID COV_RTM_CONFIG_CONDITION_DEV_DETECT_ALWAYS_TRUE
\ACCEPT TX tf tx
\REASON The check of (RTM_DEV_ERROR_DETECT == STD_ON) is always true, in an or condition the standard justification does not work.

\ID COV_RTM_CONFIG_CONDITION_ALWAYS_TRUE_OR_ALWAYS_FALSE
\ACCEPT TX
\ACCEPT XF
\REASON The check of Rtm_IsCPULoadAutostartOfCommonConst(CoreIndex, 0u) is always true or always false if autostart
        flag of all CPU load MPs is set equally. Therefore, all single core configurations and some multicore
        configurations are affected and can therefore not be tested completely.

\ID COV_RTM_CONFIG_CONDITION_NO_CROSSCORE_MP
\ACCEPT TF tx tf
\REASON The check (Rtm_MeasurementPointConfigInfo[measurementId].coreId < RTM_NUMBER_OF_CORES) can only become false if
        at least one cross core mp is configured (not mapped to a specific core).

\ID COV_RTM_TASKRESPONSETIME_NVMHANDLE
\ACCEPT TX
\ACCEPT XF
\REASON The check Rtm_IsTaskResponseTimeNvMHandleUsedOfCommonConst(CoreIndex, 0u) (respectively
        Rtm_CommonConst[].TaskResponseTimeNvMHandleUsed == TRUE) is always true or always false depending on
        configuration of /MICROSAR/Rtm/RtmCoreDefinition/RtmNvMTaskResponseTimePersistencyBlock.

\ID COV_RTM_CPULOADHISTOGRAM_NVMHANDLE
\ACCEPT TX
\ACCEPT XF
\REASON The check Rtm_IsCpuLoadNvMHandleUsedOfCommonConst(CoreIndex, 0u) (respectively
        Rtm_CommonConst[].CpuLoadNvMHandleUsed == TRUE) is always true or always false depending on configuration of 
        /MICROSAR/Rtm/RtmCoreDefinition/RtmNvMCpuLoadPersistencyBlock.

\ID COV_RTM_CPULOAD_MPS_ALL_ENABLED
\ACCEPT TX
\REASON The check cpuLoadMPId < RTM_MEAS_SECTION_COUNT (respectively
        Rtm_GetCPULoadMeasurementIdOfCommonConst(CoreIndex, 0u) < RTM_MEAS_SECTION_COUNT) is always true if all CPU
        load mps are enabled (/MICROSAR/Rtm/RtmMeasurementPoint/RtmMeasurementEnabled of all
        Rtm_CpuLoadMeasurement<_coreId> mps is enabled).

\ID COV_RTM_CONFIG_CORE_INDEX_FROM_CORE_ID_ALWAYS_VALID_WHEN_DET_CHECKS_ENABLED
\ACCEPT TX
\REASON The check Rtm_CpuLoadHistogram_GetCoreIndexOfCoreId(CoreId, &coreIndex) == E_OK is always true if
        RTM_DEV_ERROR_DETECT is STD_ON as the DET checks already validated the CoreId.

\ID COV_RTM_TASKRESPONSETIME_COREANDTASKINDEX_ALWAYS_VALID_WHEN_DET_CHECKS_ENABLED
\ACCEPT TX tx tx
\REASON The checks of coreIndex and taskIndex after gather them with Rtm_TaskResponseTime_GetCoreIndexAndTaskIndexOfTaskId(TaskId, &coreIndex, &taskIndex)
        are always true if RTM_DEV_ERROR_DETECT is STD_ON as the DET checks already validated the TaskId.

COV_JUSTIFICATION_END */

/* SBSW_JUSTIFICATION_BEGIN

 \ID             VCA_RTM_STRUCT_WRT_UNCHANGED
 \DESCRIPTION    Write access to the members of a struct using an unchanged pointer.
 \COUNTERMEASURE \N The original caller guarantees that the pointer references a valid struct.

 \ID             VCA_RTM_TASK_RESPONSE_TIME_PERCENTILE_INDEX
 \DESCRIPTION    The percentileIndex is in range between 0 and RTM_SIZE_OF_TASKRESPONSETIME_PERCENTILES.
                 RTM_SIZE_OF_TASKRESPONSETIME_PERCENTILES is defined as (RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES + 1u).
                 The accessed array is of same size: PercentileCount[RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES + 1u];
 \COUNTERMEASURE \M [CM_RTM_TASK_RESPONSE_TIME_PERCENTILE_INDEX]

 \ID             VCA_RTM_VALID_CORE_INDEX
 \DESCRIPTION    The locCoreIndex is determined by calling Rtm_Cpu_IsMeasurementIdValidCpuLoadMP().
                 This function loops for Rtm_GetSizeOfCommonConst() which is configured and equals to
                 RTM_NUMBER_OF_CORES. locCoreIndex is only used if Rtm_Cpu_IsMeasurementIdValidCpuLoadMP() returns
                 TRUE.
 \COUNTERMEASURE \R Result of Rtm_Cpu_IsMeasurementIdValidCpuLoadMP() has to be checked against TRUE before
                    locCoreIndex.
                 \M [CM_RTM_VALID_CORE_INDEX]

 \ID             VCA_RTM_VALID_POINTER
 \DESCRIPTION    It is verified that the pointer is not a NULL_PTR.
 \COUNTERMEASURE \N The variables are declared locally. Only those addresses are used as pointer targets, therefore it
                    is not possible that it is a NULL_PTR.

 \ID             VCA_RTM_VALID_NUMBER_OF_CORE_SPECIFIC_TASKS
 \DESCRIPTION    The taskIndex is in range between 0 and Rtm_CommonConst[<CoreIndex>].OsTaskInfoLengthOfCommonConst.
 \COUNTERMEASURE \M [CM_RTM_VALID_NUMBER_OF_CORE_SPECIFIC_TASKS]
                 \M [CM_RTM_VALID_SIZE_OF_CORE_SPECIFIC_TASKS]

  SBSW_JUSTIFICATION_END */
 
/* ------------------------------------------------------------------------------------------------------------------ */
/* Silent BSW Countermeasures                                                                                         */
/* ------------------------------------------------------------------------------------------------------------------ */
/*
--- MSSV Plugin ---
\CM CM_RTM_PRECOMPILEOPTIONS To ensure that all mandatory / excluded features are as expected, the following must be verified by MSSV:
                               - RTM_FLAT_EXECUTION_TIME_AVAILABLE is STD_OFF
                               - RTM_NET_EXECUTION_TIME_AVAILABLE is STD_OFF
                               
\CM CM_RTM_TASK_RESPONSE_TIME_PERCENTILE_INDEX
                             To ensure that the array access to 
                             Rtm_TaskResponseTimeStruct_<CoreIndex>[<TaskIndex>].PercentileCount[<percentileIndex>] is valid the
                             following must be verified by MSSV for each configured core:
                              - AssertArraySize(Rtm_TaskResponseTimeStruct_<CoreIndex>[<TaskIndex>].PercentileCount[], Equal, RTM_NUMBER_OF_TASKRESPONSETIME_PERCENTILES + 1)

\CM CM_RTM_VALID_CORE_INDEX To ensure that the array access to Rtm_PCPartitionConfig[] is valid the following must be verified by MSSV:
                              - AssertArraySize(Rtm_PCPartitionConfig[], Equal, RTM_NUMBER_OF_CORES)
                               
\CM CM_RTM_VALID_NUMBER_OF_CORE_SPECIFIC_TASKS
                             To ensure that the array access to Rtm_TaskResponseTimeStruct_<CoreIndex>[]
                             is valid the following must be verified by MSSV for each configured core:
                              - AssertArraySize(Rtm_TaskResponseTimeStruct_<CoreIndex>[], Equal, RTM_NUMBER_OF_TASKS_ON_CORE_<CoreIndex>)
                               
\CM CM_RTM_VALID_SIZE_OF_CORE_SPECIFIC_TASKS
                             To ensure that the array access to Rtm_TaskResponseTimeStruct_<CoreIndex>[]
                             is valid the following must be verified by MSSV for each configured core:
                              - Assert(Rtm_CommonConst[<CoreIndex>].OsTaskInfoLengthOfCommonConst, Equal, RTM_NUMBER_OF_TASKS_ON_CORE_<CoreIndex>)
*/

/**********************************************************************************************************************
 *  END OF FILE: Rtm.c
 *********************************************************************************************************************/

