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
 *              File: Os_Scheduler_Lcfg.c
 *   Generation Time: 2020-07-28 15:56:23
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_SCHEDULER_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Scheduler_Cfg.h"
#include "Os_Scheduler_Lcfg.h"
#include "Os_Scheduler.h"

/* Os kernel module dependencies */
#include "Os_BitArray.h"
#include "Os_Common.h"
#include "Os_Deque.h"

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

/*! Dynamic scheduler data: OsCore0 */
OS_LOCAL VAR(Os_SchedulerType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore0_Dyn;
OS_LOCAL VAR(Os_BitArrayType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore0_BitArray_Dyn;
OS_LOCAL OS_BITARRAY_DECLARE(OsCfg_Scheduler_OsCore0_BitField_Dyn, OS_CFG_NUM_TASKQUEUES, OS_VAR_NOINIT);

/*! Dynamic task queues data: OsCore0 */
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue0_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes0_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE0_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue1_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes1_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE1_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue2_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes2_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE2_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue3_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes3_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE3_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue4_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes4_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE4_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue5_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes5_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE5_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue6_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes6_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE6_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue7_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes7_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE7_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue8_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes8_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE8_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue9_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes9_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE9_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue10_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes10_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE10_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue11_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes11_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE11_OSCORE0_SLOTS];

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic scheduler data: OsCore1 */
OS_LOCAL VAR(Os_SchedulerType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore1_Dyn;
OS_LOCAL VAR(Os_BitArrayType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore1_BitArray_Dyn;
OS_LOCAL OS_BITARRAY_DECLARE(OsCfg_Scheduler_OsCore1_BitField_Dyn, OS_CFG_NUM_TASKQUEUES, OS_VAR_NOINIT);

/*! Dynamic task queues data: OsCore1 */
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue0_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes0_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE0_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue1_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes1_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE1_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue2_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes2_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE2_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue3_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes3_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE3_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue4_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes4_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE4_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue5_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes5_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE5_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue6_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes6_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE6_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue7_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes7_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE7_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue8_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes8_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE8_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue9_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes9_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE9_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue10_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes10_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE10_OSCORE1_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue11_OsCore1_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes11_OsCore1_Dyn[OS_CFG_NUM_TASKQUEUE11_OSCORE1_SLOTS];

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic scheduler data: OsCore2 */
OS_LOCAL VAR(Os_SchedulerType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore2_Dyn;
OS_LOCAL VAR(Os_BitArrayType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore2_BitArray_Dyn;
OS_LOCAL OS_BITARRAY_DECLARE(OsCfg_Scheduler_OsCore2_BitField_Dyn, OS_CFG_NUM_TASKQUEUES, OS_VAR_NOINIT);

/*! Dynamic task queues data: OsCore2 */
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue0_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes0_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE0_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue1_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes1_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE1_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue2_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes2_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE2_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue3_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes3_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE3_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue4_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes4_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE4_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue5_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes5_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE5_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue6_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes6_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE6_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue7_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes7_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE7_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue8_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes8_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE8_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue9_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes9_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE9_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue10_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes10_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE10_OSCORE2_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue11_OsCore2_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes11_OsCore2_Dyn[OS_CFG_NUM_TASKQUEUE11_OSCORE2_SLOTS];

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

/*! Task queues configuration data: OsCore0 */
OS_LOCAL CONST(Os_DequeConfigType, OS_CONST) OsCfg_Scheduler_OsCore0_TaskQueues[OS_CFG_NUM_TASKQUEUES] =
{
  /* [0] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue0_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes0_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE0_OSCORE0_SLOTS
  },
  /* [1] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue1_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes1_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE1_OSCORE0_SLOTS
  },
  /* [2] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue2_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes2_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE2_OSCORE0_SLOTS
  },
  /* [3] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue3_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes3_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE3_OSCORE0_SLOTS
  },
  /* [4] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue4_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes4_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE4_OSCORE0_SLOTS
  },
  /* [5] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue5_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes5_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE5_OSCORE0_SLOTS
  },
  /* [6] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue6_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes6_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE6_OSCORE0_SLOTS
  },
  /* [7] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue7_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes7_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE7_OSCORE0_SLOTS
  },
  /* [8] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue8_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes8_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE8_OSCORE0_SLOTS
  },
  /* [9] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue9_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes9_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE9_OSCORE0_SLOTS
  },
  /* [10] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue10_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes10_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE10_OSCORE0_SLOTS
  },
  /* [11] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue11_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes11_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE11_OSCORE0_SLOTS
  }
};

/*! Scheduler configuration data: OsCore0 */
CONST(Os_SchedulerConfigType, OS_CONST) OsCfg_Scheduler_OsCore0 =
{
  /* .BitArray           = */
  {
    /* .Dyn       = */ &OsCfg_Scheduler_OsCore0_BitArray_Dyn,
    /* .Data      = */ OsCfg_Scheduler_OsCore0_BitField_Dyn,
    /* .Size      = */ OS_BITARRAY_SIZE(OS_CFG_NUM_TASKQUEUES),
    /* .BitLength = */ OS_BITARRAY_LENGTH(OS_CFG_NUM_TASKQUEUES),
  },
  /* .Dyn                = */ &OsCfg_Scheduler_OsCore0_Dyn,
  /* .TaskQueues         = */ OsCfg_Scheduler_OsCore0_TaskQueues,
  /* .NumberOfPriorities = */ OS_CFG_NUM_TASKQUEUES
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Task queues configuration data: OsCore1 */
OS_LOCAL CONST(Os_DequeConfigType, OS_CONST) OsCfg_Scheduler_OsCore1_TaskQueues[OS_CFG_NUM_TASKQUEUES] =
{
  /* [0] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue0_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes0_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE0_OSCORE1_SLOTS
  },
  /* [1] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue1_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes1_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE1_OSCORE1_SLOTS
  },
  /* [2] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue2_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes2_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE2_OSCORE1_SLOTS
  },
  /* [3] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue3_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes3_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE3_OSCORE1_SLOTS
  },
  /* [4] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue4_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes4_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE4_OSCORE1_SLOTS
  },
  /* [5] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue5_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes5_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE5_OSCORE1_SLOTS
  },
  /* [6] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue6_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes6_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE6_OSCORE1_SLOTS
  },
  /* [7] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue7_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes7_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE7_OSCORE1_SLOTS
  },
  /* [8] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue8_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes8_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE8_OSCORE1_SLOTS
  },
  /* [9] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue9_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes9_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE9_OSCORE1_SLOTS
  },
  /* [10] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue10_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes10_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE10_OSCORE1_SLOTS
  },
  /* [11] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue11_OsCore1_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes11_OsCore1_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE11_OSCORE1_SLOTS
  }
};

/*! Scheduler configuration data: OsCore1 */
CONST(Os_SchedulerConfigType, OS_CONST) OsCfg_Scheduler_OsCore1 =
{
  /* .BitArray           = */
  {
    /* .Dyn       = */ &OsCfg_Scheduler_OsCore1_BitArray_Dyn,
    /* .Data      = */ OsCfg_Scheduler_OsCore1_BitField_Dyn,
    /* .Size      = */ OS_BITARRAY_SIZE(OS_CFG_NUM_TASKQUEUES),
    /* .BitLength = */ OS_BITARRAY_LENGTH(OS_CFG_NUM_TASKQUEUES),
  },
  /* .Dyn                = */ &OsCfg_Scheduler_OsCore1_Dyn,
  /* .TaskQueues         = */ OsCfg_Scheduler_OsCore1_TaskQueues,
  /* .NumberOfPriorities = */ OS_CFG_NUM_TASKQUEUES
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Task queues configuration data: OsCore2 */
OS_LOCAL CONST(Os_DequeConfigType, OS_CONST) OsCfg_Scheduler_OsCore2_TaskQueues[OS_CFG_NUM_TASKQUEUES] =
{
  /* [0] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue0_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes0_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE0_OSCORE2_SLOTS
  },
  /* [1] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue1_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes1_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE1_OSCORE2_SLOTS
  },
  /* [2] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue2_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes2_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE2_OSCORE2_SLOTS
  },
  /* [3] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue3_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes3_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE3_OSCORE2_SLOTS
  },
  /* [4] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue4_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes4_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE4_OSCORE2_SLOTS
  },
  /* [5] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue5_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes5_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE5_OSCORE2_SLOTS
  },
  /* [6] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue6_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes6_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE6_OSCORE2_SLOTS
  },
  /* [7] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue7_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes7_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE7_OSCORE2_SLOTS
  },
  /* [8] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue8_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes8_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE8_OSCORE2_SLOTS
  },
  /* [9] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue9_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes9_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE9_OSCORE2_SLOTS
  },
  /* [10] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue10_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes10_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE10_OSCORE2_SLOTS
  },
  /* [11] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue11_OsCore2_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes11_OsCore2_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE11_OSCORE2_SLOTS
  }
};

/*! Scheduler configuration data: OsCore2 */
CONST(Os_SchedulerConfigType, OS_CONST) OsCfg_Scheduler_OsCore2 =
{
  /* .BitArray           = */
  {
    /* .Dyn       = */ &OsCfg_Scheduler_OsCore2_BitArray_Dyn,
    /* .Data      = */ OsCfg_Scheduler_OsCore2_BitField_Dyn,
    /* .Size      = */ OS_BITARRAY_SIZE(OS_CFG_NUM_TASKQUEUES),
    /* .BitLength = */ OS_BITARRAY_LENGTH(OS_CFG_NUM_TASKQUEUES),
  },
  /* .Dyn                = */ &OsCfg_Scheduler_OsCore2_Dyn,
  /* .TaskQueues         = */ OsCfg_Scheduler_OsCore2_TaskQueues,
  /* .NumberOfPriorities = */ OS_CFG_NUM_TASKQUEUES
};

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
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
 *  END OF FILE: Os_Scheduler_Lcfg.c
 *********************************************************************************************************************/
