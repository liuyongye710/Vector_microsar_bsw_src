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
 *              File: Os_XSignal_Lcfg.c
 *   Generation Time: 2020-07-28 15:56:23
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_XSIGNAL_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_XSignal_Lcfg.h"
#include "Os_XSignal.h"

/* Os kernel module dependencies */
#include "Os_Common.h"
#include "Os_Isr_Lcfg.h"
#include "Os_Lcfg.h"

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

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! X-Signal send port configuration data: OsCore0 -> OsCore1/XSignalIsr_OsCore1_Recv0 */
OS_LOCAL CONST(Os_XSigSendPortConfigType, OS_CONST) OsCfg_XSig_OsCore0_Send0;

/*! X-Signal send port configuration data: OsCore0 -> OsCore2/XSignalIsr_OsCore2_Recv0 */
OS_LOCAL CONST(Os_XSigSendPortConfigType, OS_CONST) OsCfg_XSig_OsCore0_Send1;

/*! X-Signal receive port configuration data: XSignalIsr_OsCore0_Recv0 <- OsCore1 */
OS_LOCAL CONST(Os_XSigRecvPortConfigType, OS_CONST) OsCfg_XSig_XSignalIsr_OsCore0_Recv0;

/*! X-Signal receive port configuration data: XSignalIsr_OsCore0_Recv1 <- OsCore2 */
OS_LOCAL CONST(Os_XSigRecvPortConfigType, OS_CONST) OsCfg_XSig_XSignalIsr_OsCore0_Recv1;

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! X-Signal send port configuration data: OsCore1 -> OsCore0/XSignalIsr_OsCore0_Recv0 */
OS_LOCAL CONST(Os_XSigSendPortConfigType, OS_CONST) OsCfg_XSig_OsCore1_Send0;

/*! X-Signal send port configuration data: OsCore1 -> OsCore2/XSignalIsr_OsCore2_Recv1 */
OS_LOCAL CONST(Os_XSigSendPortConfigType, OS_CONST) OsCfg_XSig_OsCore1_Send1;

/*! X-Signal receive port configuration data: XSignalIsr_OsCore1_Recv0 <- OsCore0 */
OS_LOCAL CONST(Os_XSigRecvPortConfigType, OS_CONST) OsCfg_XSig_XSignalIsr_OsCore1_Recv0;

/*! X-Signal receive port configuration data: XSignalIsr_OsCore1_Recv1 <- OsCore2 */
OS_LOCAL CONST(Os_XSigRecvPortConfigType, OS_CONST) OsCfg_XSig_XSignalIsr_OsCore1_Recv1;

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! X-Signal send port configuration data: OsCore2 -> OsCore1/XSignalIsr_OsCore1_Recv1 */
OS_LOCAL CONST(Os_XSigSendPortConfigType, OS_CONST) OsCfg_XSig_OsCore2_Send0;

/*! X-Signal send port configuration data: OsCore2 -> OsCore0/XSignalIsr_OsCore0_Recv1 */
OS_LOCAL CONST(Os_XSigSendPortConfigType, OS_CONST) OsCfg_XSig_OsCore2_Send1;

/*! X-Signal receive port configuration data: XSignalIsr_OsCore2_Recv0 <- OsCore0 */
OS_LOCAL CONST(Os_XSigRecvPortConfigType, OS_CONST) OsCfg_XSig_XSignalIsr_OsCore2_Recv0;

/*! X-Signal receive port configuration data: XSignalIsr_OsCore2_Recv1 <- OsCore1 */
OS_LOCAL CONST(Os_XSigRecvPortConfigType, OS_CONST) OsCfg_XSig_XSignalIsr_OsCore2_Recv1;

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Dynamic X-Signal send port data: OsCore0 -> OsCore1/XSignalIsr_OsCore1_Recv0 */
OS_LOCAL VAR(Os_XSigChannelSendType, OS_VAR_NOINIT) OsCfg_XSig_OsCore0_Send0_XSignalIsr_OsCore1_Recv0_Send_Dyn;
OS_LOCAL VAR(Os_XSigSendDataType, OS_VAR_NOINIT)
  OsCore0_Send0_Data[OS_CFG_SIZE_OSCORE0_SEND0_XSIGNALISR_OSCORE1_RECV0_BUFFER];

/* Dynamic X-Signal send port data: OsCore0 -> OsCore2/XSignalIsr_OsCore2_Recv0 */
OS_LOCAL VAR(Os_XSigChannelSendType, OS_VAR_NOINIT) OsCfg_XSig_OsCore0_Send1_XSignalIsr_OsCore2_Recv0_Send_Dyn;
OS_LOCAL VAR(Os_XSigSendDataType, OS_VAR_NOINIT)
  OsCore0_Send1_Data[OS_CFG_SIZE_OSCORE0_SEND1_XSIGNALISR_OSCORE2_RECV0_BUFFER];

/* Dynamic X-Signal receive port data: XSignalIsr_OsCore0_Recv0 <- OsCore1 */
OS_LOCAL VAR(Os_XSigChannelRecvType, OS_VAR_NOINIT) OsCfg_XSig_OsCore1_Send0_XSignalIsr_OsCore0_Recv0_Recv_Dyn;
OS_LOCAL VAR(Os_XSigRecvDataType, OS_VAR_NOINIT)
  XSignalIsr_OsCore0_Recv0_Data[OS_CFG_SIZE_OSCORE1_SEND0_XSIGNALISR_OSCORE0_RECV0_BUFFER];

/* Dynamic X-Signal receive port data: XSignalIsr_OsCore0_Recv1 <- OsCore2 */
OS_LOCAL VAR(Os_XSigChannelRecvType, OS_VAR_NOINIT) OsCfg_XSig_OsCore2_Send1_XSignalIsr_OsCore0_Recv1_Recv_Dyn;
OS_LOCAL VAR(Os_XSigRecvDataType, OS_VAR_NOINIT)
  XSignalIsr_OsCore0_Recv1_Data[OS_CFG_SIZE_OSCORE2_SEND1_XSIGNALISR_OSCORE0_RECV1_BUFFER];

#define OS_STOP_SEC_CORE0_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Dynamic X-Signal send port data: OsCore1 -> OsCore0/XSignalIsr_OsCore0_Recv0 */
OS_LOCAL VAR(Os_XSigChannelSendType, OS_VAR_NOINIT) OsCfg_XSig_OsCore1_Send0_XSignalIsr_OsCore0_Recv0_Send_Dyn;
OS_LOCAL VAR(Os_XSigSendDataType, OS_VAR_NOINIT)
  OsCore1_Send0_Data[OS_CFG_SIZE_OSCORE1_SEND0_XSIGNALISR_OSCORE0_RECV0_BUFFER];

/* Dynamic X-Signal send port data: OsCore1 -> OsCore2/XSignalIsr_OsCore2_Recv1 */
OS_LOCAL VAR(Os_XSigChannelSendType, OS_VAR_NOINIT) OsCfg_XSig_OsCore1_Send1_XSignalIsr_OsCore2_Recv1_Send_Dyn;
OS_LOCAL VAR(Os_XSigSendDataType, OS_VAR_NOINIT)
  OsCore1_Send1_Data[OS_CFG_SIZE_OSCORE1_SEND1_XSIGNALISR_OSCORE2_RECV1_BUFFER];

/* Dynamic X-Signal receive port data: XSignalIsr_OsCore1_Recv0 <- OsCore0 */
OS_LOCAL VAR(Os_XSigChannelRecvType, OS_VAR_NOINIT) OsCfg_XSig_OsCore0_Send0_XSignalIsr_OsCore1_Recv0_Recv_Dyn;
OS_LOCAL VAR(Os_XSigRecvDataType, OS_VAR_NOINIT)
  XSignalIsr_OsCore1_Recv0_Data[OS_CFG_SIZE_OSCORE0_SEND0_XSIGNALISR_OSCORE1_RECV0_BUFFER];

/* Dynamic X-Signal receive port data: XSignalIsr_OsCore1_Recv1 <- OsCore2 */
OS_LOCAL VAR(Os_XSigChannelRecvType, OS_VAR_NOINIT) OsCfg_XSig_OsCore2_Send0_XSignalIsr_OsCore1_Recv1_Recv_Dyn;
OS_LOCAL VAR(Os_XSigRecvDataType, OS_VAR_NOINIT)
  XSignalIsr_OsCore1_Recv1_Data[OS_CFG_SIZE_OSCORE2_SEND0_XSIGNALISR_OSCORE1_RECV1_BUFFER];

#define OS_STOP_SEC_CORE1_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Dynamic X-Signal send port data: OsCore2 -> OsCore1/XSignalIsr_OsCore1_Recv1 */
OS_LOCAL VAR(Os_XSigChannelSendType, OS_VAR_NOINIT) OsCfg_XSig_OsCore2_Send0_XSignalIsr_OsCore1_Recv1_Send_Dyn;
OS_LOCAL VAR(Os_XSigSendDataType, OS_VAR_NOINIT)
  OsCore2_Send0_Data[OS_CFG_SIZE_OSCORE2_SEND0_XSIGNALISR_OSCORE1_RECV1_BUFFER];

/* Dynamic X-Signal send port data: OsCore2 -> OsCore0/XSignalIsr_OsCore0_Recv1 */
OS_LOCAL VAR(Os_XSigChannelSendType, OS_VAR_NOINIT) OsCfg_XSig_OsCore2_Send1_XSignalIsr_OsCore0_Recv1_Send_Dyn;
OS_LOCAL VAR(Os_XSigSendDataType, OS_VAR_NOINIT)
  OsCore2_Send1_Data[OS_CFG_SIZE_OSCORE2_SEND1_XSIGNALISR_OSCORE0_RECV1_BUFFER];

/* Dynamic X-Signal receive port data: XSignalIsr_OsCore2_Recv0 <- OsCore0 */
OS_LOCAL VAR(Os_XSigChannelRecvType, OS_VAR_NOINIT) OsCfg_XSig_OsCore0_Send1_XSignalIsr_OsCore2_Recv0_Recv_Dyn;
OS_LOCAL VAR(Os_XSigRecvDataType, OS_VAR_NOINIT)
  XSignalIsr_OsCore2_Recv0_Data[OS_CFG_SIZE_OSCORE0_SEND1_XSIGNALISR_OSCORE2_RECV0_BUFFER];

/* Dynamic X-Signal receive port data: XSignalIsr_OsCore2_Recv1 <- OsCore1 */
OS_LOCAL VAR(Os_XSigChannelRecvType, OS_VAR_NOINIT) OsCfg_XSig_OsCore1_Send1_XSignalIsr_OsCore2_Recv1_Recv_Dyn;
OS_LOCAL VAR(Os_XSigRecvDataType, OS_VAR_NOINIT)
  XSignalIsr_OsCore2_Recv1_Data[OS_CFG_SIZE_OSCORE1_SEND1_XSIGNALISR_OSCORE2_RECV1_BUFFER];

#define OS_STOP_SEC_CORE2_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! X-Signal used services map. */
CONST(OSServiceIdType, OS_CONST) OsCfg_XSig_ServiceMap[OS_XSIGFUNCTIONIDX_USEDCOUNT + 1] =
{
  OSServiceId_ActivateTask,
  OSServiceId_CancelAlarm,
  OSServiceId_ControlIdle,
  OSServiceId_GetAlarm,
  OSServiceId_GetApplicationState,
  OSServiceId_GetCounterValue,
  OSServiceId_GetErrorHookStackUsage,
  OSServiceId_GetEvent,
  OSServiceId_GetISRStackUsage,
  OSServiceId_GetKernelStackUsage,
  OSServiceId_GetProtectionHookStackUsage,
  OSServiceId_GetScheduleTableStatus,
  OSServiceId_GetShutdownHookStackUsage,
  OSServiceId_GetStartupHookStackUsage,
  OSServiceId_GetTaskStackUsage,
  OSServiceId_GetTaskState,
  OSServiceId_HookCallCallback,
  OSServiceId_NextScheduleTable,
  OSServiceId_SetAbsAlarm,
  OSServiceId_SetEvent,
  OSServiceId_SetRelAlarm,
  OSServiceId_ShutdownAllCores,
  OSServiceId_StartScheduleTableAbs,
  OSServiceId_StartScheduleTableRel,
  OSServiceId_StopScheduleTable,
  OSServiceId_TerminateApplication,
  OSSERVICEID_COUNT
};

/*! X-Signal data buffer: OsCore0 -> OsCore1/XSignalIsr_OsCore1_Recv0 */
OS_LOCAL CONST(Os_XSigComDataConfigType, OS_CONST) OsCfg_XSig_OsCore0_Send0_XSignalIsr_OsCore1_Recv0_Buffer_Dyn[OS_CFG_SIZE_OSCORE0_SEND0_XSIGNALISR_OSCORE1_RECV0_BUFFER] =
{
  {
    /* .SendData = */ &(OsCore0_Send0_Data[0]),
    /* .RecvData = */ &(XSignalIsr_OsCore1_Recv0_Data[0]),
    /* .Idx      = */ 0
  },
  {
    /* .SendData = */ &(OsCore0_Send0_Data[1]),
    /* .RecvData = */ &(XSignalIsr_OsCore1_Recv0_Data[1]),
    /* .Idx      = */ 1
  }
};

/*! X-Signal data buffer: OsCore0 -> OsCore2/XSignalIsr_OsCore2_Recv0 */
OS_LOCAL CONST(Os_XSigComDataConfigType, OS_CONST) OsCfg_XSig_OsCore0_Send1_XSignalIsr_OsCore2_Recv0_Buffer_Dyn[OS_CFG_SIZE_OSCORE0_SEND1_XSIGNALISR_OSCORE2_RECV0_BUFFER] =
{
  {
    /* .SendData = */ &(OsCore0_Send1_Data[0]),
    /* .RecvData = */ &(XSignalIsr_OsCore2_Recv0_Data[0]),
    /* .Idx      = */ 0
  },
  {
    /* .SendData = */ &(OsCore0_Send1_Data[1]),
    /* .RecvData = */ &(XSignalIsr_OsCore2_Recv0_Data[1]),
    /* .Idx      = */ 1
  }
};

/*! X-Signal data buffer: OsCore1 -> OsCore0/XSignalIsr_OsCore0_Recv0 */
OS_LOCAL CONST(Os_XSigComDataConfigType, OS_CONST) OsCfg_XSig_OsCore1_Send0_XSignalIsr_OsCore0_Recv0_Buffer_Dyn[OS_CFG_SIZE_OSCORE1_SEND0_XSIGNALISR_OSCORE0_RECV0_BUFFER] =
{
  {
    /* .SendData = */ &(OsCore1_Send0_Data[0]),
    /* .RecvData = */ &(XSignalIsr_OsCore0_Recv0_Data[0]),
    /* .Idx      = */ 0
  },
  {
    /* .SendData = */ &(OsCore1_Send0_Data[1]),
    /* .RecvData = */ &(XSignalIsr_OsCore0_Recv0_Data[1]),
    /* .Idx      = */ 1
  }
};

/*! X-Signal data buffer: OsCore1 -> OsCore2/XSignalIsr_OsCore2_Recv1 */
OS_LOCAL CONST(Os_XSigComDataConfigType, OS_CONST) OsCfg_XSig_OsCore1_Send1_XSignalIsr_OsCore2_Recv1_Buffer_Dyn[OS_CFG_SIZE_OSCORE1_SEND1_XSIGNALISR_OSCORE2_RECV1_BUFFER] =
{
  {
    /* .SendData = */ &(OsCore1_Send1_Data[0]),
    /* .RecvData = */ &(XSignalIsr_OsCore2_Recv1_Data[0]),
    /* .Idx      = */ 0
  },
  {
    /* .SendData = */ &(OsCore1_Send1_Data[1]),
    /* .RecvData = */ &(XSignalIsr_OsCore2_Recv1_Data[1]),
    /* .Idx      = */ 1
  }
};

/*! X-Signal data buffer: OsCore2 -> OsCore1/XSignalIsr_OsCore1_Recv1 */
OS_LOCAL CONST(Os_XSigComDataConfigType, OS_CONST) OsCfg_XSig_OsCore2_Send0_XSignalIsr_OsCore1_Recv1_Buffer_Dyn[OS_CFG_SIZE_OSCORE2_SEND0_XSIGNALISR_OSCORE1_RECV1_BUFFER] =
{
  {
    /* .SendData = */ &(OsCore2_Send0_Data[0]),
    /* .RecvData = */ &(XSignalIsr_OsCore1_Recv1_Data[0]),
    /* .Idx      = */ 0
  },
  {
    /* .SendData = */ &(OsCore2_Send0_Data[1]),
    /* .RecvData = */ &(XSignalIsr_OsCore1_Recv1_Data[1]),
    /* .Idx      = */ 1
  }
};

/*! X-Signal data buffer: OsCore2 -> OsCore0/XSignalIsr_OsCore0_Recv1 */
OS_LOCAL CONST(Os_XSigComDataConfigType, OS_CONST) OsCfg_XSig_OsCore2_Send1_XSignalIsr_OsCore0_Recv1_Buffer_Dyn[OS_CFG_SIZE_OSCORE2_SEND1_XSIGNALISR_OSCORE0_RECV1_BUFFER] =
{
  {
    /* .SendData = */ &(OsCore2_Send1_Data[0]),
    /* .RecvData = */ &(XSignalIsr_OsCore0_Recv1_Data[0]),
    /* .Idx      = */ 0
  },
  {
    /* .SendData = */ &(OsCore2_Send1_Data[1]),
    /* .RecvData = */ &(XSignalIsr_OsCore0_Recv1_Data[1]),
    /* .Idx      = */ 1
  }
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! X-Signal send port configuration data: OsCore0 -> OsCore1/XSignalIsr_OsCore1_Recv0 */
OS_LOCAL CONST(Os_XSigSendPortConfigType, OS_CONST) OsCfg_XSig_OsCore0_Send0 =
{
  /* .SendChannel = */
  {
    /* .Dyn        = */ &OsCfg_XSig_OsCore0_Send0_XSignalIsr_OsCore1_Recv0_Send_Dyn,
    /* .Receive    = */ &OsCfg_XSig_OsCore0_Send0_XSignalIsr_OsCore1_Recv0_Recv_Dyn,
    /* .Buffer     = */ OsCfg_XSig_OsCore0_Send0_XSignalIsr_OsCore1_Recv0_Buffer_Dyn,
    /* .BufferSize = */ OS_CFG_SIZE_OSCORE0_SEND0_XSIGNALISR_OSCORE1_RECV0_BUFFER
  },
  /* .XSigIsr     = */ &OsCfg_Isr_XSignalIsr_OsCore1,
  /* .RecvPort    = */ &OsCfg_XSig_XSignalIsr_OsCore1_Recv0,
  /* .SendCore    = */ &OsCfg_Core_OsCore0
};

/*! X-Signal send port configuration data: OsCore0 -> OsCore2/XSignalIsr_OsCore2_Recv0 */
OS_LOCAL CONST(Os_XSigSendPortConfigType, OS_CONST) OsCfg_XSig_OsCore0_Send1 =
{
  /* .SendChannel = */
  {
    /* .Dyn        = */ &OsCfg_XSig_OsCore0_Send1_XSignalIsr_OsCore2_Recv0_Send_Dyn,
    /* .Receive    = */ &OsCfg_XSig_OsCore0_Send1_XSignalIsr_OsCore2_Recv0_Recv_Dyn,
    /* .Buffer     = */ OsCfg_XSig_OsCore0_Send1_XSignalIsr_OsCore2_Recv0_Buffer_Dyn,
    /* .BufferSize = */ OS_CFG_SIZE_OSCORE0_SEND1_XSIGNALISR_OSCORE2_RECV0_BUFFER
  },
  /* .XSigIsr     = */ &OsCfg_Isr_XSignalIsr_OsCore2,
  /* .RecvPort    = */ &OsCfg_XSig_XSignalIsr_OsCore2_Recv0,
  /* .SendCore    = */ &OsCfg_Core_OsCore0
};

/*! X-Signal receive port configuration data: XSignalIsr_OsCore0_Recv0 <- OsCore1 */
OS_LOCAL CONST(Os_XSigRecvPortConfigType, OS_CONST) OsCfg_XSig_XSignalIsr_OsCore0_Recv0 =
{
  /* .RecvChannel = */
  {
    /* .Dyn        = */ &OsCfg_XSig_OsCore1_Send0_XSignalIsr_OsCore0_Recv0_Recv_Dyn,
    /* .Send       = */ &OsCfg_XSig_OsCore1_Send0_XSignalIsr_OsCore0_Recv0_Send_Dyn,
    /* .Buffer     = */ OsCfg_XSig_OsCore1_Send0_XSignalIsr_OsCore0_Recv0_Buffer_Dyn,
    /* .BufferSize = */ OS_CFG_SIZE_OSCORE1_SEND0_XSIGNALISR_OSCORE0_RECV0_BUFFER
  },
  /* .SendPort    = */ &OsCfg_XSig_OsCore1_Send0
};

/*! X-Signal receive port configuration data: XSignalIsr_OsCore0_Recv1 <- OsCore2 */
OS_LOCAL CONST(Os_XSigRecvPortConfigType, OS_CONST) OsCfg_XSig_XSignalIsr_OsCore0_Recv1 =
{
  /* .RecvChannel = */
  {
    /* .Dyn        = */ &OsCfg_XSig_OsCore2_Send1_XSignalIsr_OsCore0_Recv1_Recv_Dyn,
    /* .Send       = */ &OsCfg_XSig_OsCore2_Send1_XSignalIsr_OsCore0_Recv1_Send_Dyn,
    /* .Buffer     = */ OsCfg_XSig_OsCore2_Send1_XSignalIsr_OsCore0_Recv1_Buffer_Dyn,
    /* .BufferSize = */ OS_CFG_SIZE_OSCORE2_SEND1_XSIGNALISR_OSCORE0_RECV1_BUFFER
  },
  /* .SendPort    = */ &OsCfg_XSig_OsCore2_Send1
};

/*! X-Signal ISR function table: XSignalIsr_OsCore0 */
CONST(Os_XSigFunctionTableConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore0_FuncTable =
{
  /* .FunctionDescription = */
  {
    { Os_XSigRecv_ActivateTask }, /* OSServiceId_ActivateTask */
    { Os_XSigRecv_CancelAlarm }, /* OSServiceId_CancelAlarm */
    { Os_XSigRecv_ControlIdle }, /* OSServiceId_ControlIdle */
    { Os_XSigRecv_GetAlarm }, /* OSServiceId_GetAlarm */
    { Os_XSigRecv_GetApplicationState }, /* OSServiceId_GetApplicationState */
    { Os_XSigRecv_GetCounterValue }, /* OSServiceId_GetCounterValue */
    { Os_XSigRecv_GetErrorHookStackUsage }, /* OSServiceId_GetErrorHookStackUsage */
    { Os_XSigRecv_GetEvent }, /* OSServiceId_GetEvent */
    { Os_XSigRecv_GetISRStackUsage }, /* OSServiceId_GetISRStackUsage */
    { Os_XSigRecv_GetKernelStackUsage }, /* OSServiceId_GetKernelStackUsage */
    { Os_XSigRecv_GetProtectionHookStackUsage }, /* OSServiceId_GetProtectionHookStackUsage */
    { Os_XSigRecv_GetScheduleTableStatus }, /* OSServiceId_GetScheduleTableStatus */
    { Os_XSigRecv_GetShutdownHookStackUsage }, /* OSServiceId_GetShutdownHookStackUsage */
    { Os_XSigRecv_GetStartupHookStackUsage }, /* OSServiceId_GetStartupHookStackUsage */
    { Os_XSigRecv_GetTaskStackUsage }, /* OSServiceId_GetTaskStackUsage */
    { Os_XSigRecv_GetTaskState }, /* OSServiceId_GetTaskState */
    { Os_XSigRecv_HookCallCallback }, /* OSServiceId_HookCallCallback */
    { Os_XSigRecv_NextScheduleTable }, /* OSServiceId_NextScheduleTable */
    { Os_XSigRecv_SetAbsAlarm }, /* OSServiceId_SetAbsAlarm */
    { Os_XSigRecv_SetEvent }, /* OSServiceId_SetEvent */
    { Os_XSigRecv_SetRelAlarm }, /* OSServiceId_SetRelAlarm */
    { Os_XSigRecv_ShutdownAllCores }, /* OSServiceId_ShutdownAllCores */
    { Os_XSigRecv_StartScheduleTableAbs }, /* OSServiceId_StartScheduleTableAbs */
    { Os_XSigRecv_StartScheduleTableRel }, /* OSServiceId_StartScheduleTableRel */
    { Os_XSigRecv_StopScheduleTable }, /* OSServiceId_StopScheduleTable */
    { Os_XSigRecv_TerminateApplication }, /* OSServiceId_TerminateApplication */
    { NULL_PTR }
  }
};

/*! X-Signal ISR receive ports reference table: XSignalIsr_OsCore0 */
CONST(Os_XSigRecvPortConfigRefType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore0_PortRefs[OS_CFG_NUM_ISR_XSIGNALISR_OSCORE0_PORTS + 1] =
{
  &OsCfg_XSig_XSignalIsr_OsCore0_Recv0,
  &OsCfg_XSig_XSignalIsr_OsCore0_Recv1,
  NULL_PTR
};

/*! X-Signal receiver ISRs reference table: OsCore0 */
OS_LOCAL CONST(Os_XSigIsrConfigRefType, OS_CONST) OsCfg_XSig_OsCore0_IsrRefs[OS_CFG_NUM_XSIG_OSCORE0_ISRS + 1] =
{
  &OsCfg_Isr_XSignalIsr_OsCore0,
  NULL_PTR
};

/*! X-Signal configuration data: OsCore0 */
CONST(Os_XSigConfigType, OS_CONST) OsCfg_XSig_OsCore0 =
{
  /* .XSigSendPorts    = */ 
  {
    /* [0] = */ NULL_PTR, /* OsCore0 */
    /* [1] = */ &OsCfg_XSig_OsCore0_Send0, /* OsCore1 */
    /* [2] = */ &OsCfg_XSig_OsCore0_Send1 /* OsCore2 */
  },
  /* .XSigRecvIsrRefs  = */ OsCfg_XSig_OsCore0_IsrRefs,
  /* .XSigRecvIsrCount = */ OS_CFG_NUM_XSIG_OSCORE0_ISRS
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! X-Signal send port configuration data: OsCore1 -> OsCore0/XSignalIsr_OsCore0_Recv0 */
OS_LOCAL CONST(Os_XSigSendPortConfigType, OS_CONST) OsCfg_XSig_OsCore1_Send0 =
{
  /* .SendChannel = */
  {
    /* .Dyn        = */ &OsCfg_XSig_OsCore1_Send0_XSignalIsr_OsCore0_Recv0_Send_Dyn,
    /* .Receive    = */ &OsCfg_XSig_OsCore1_Send0_XSignalIsr_OsCore0_Recv0_Recv_Dyn,
    /* .Buffer     = */ OsCfg_XSig_OsCore1_Send0_XSignalIsr_OsCore0_Recv0_Buffer_Dyn,
    /* .BufferSize = */ OS_CFG_SIZE_OSCORE1_SEND0_XSIGNALISR_OSCORE0_RECV0_BUFFER
  },
  /* .XSigIsr     = */ &OsCfg_Isr_XSignalIsr_OsCore0,
  /* .RecvPort    = */ &OsCfg_XSig_XSignalIsr_OsCore0_Recv0,
  /* .SendCore    = */ &OsCfg_Core_OsCore1
};

/*! X-Signal send port configuration data: OsCore1 -> OsCore2/XSignalIsr_OsCore2_Recv1 */
OS_LOCAL CONST(Os_XSigSendPortConfigType, OS_CONST) OsCfg_XSig_OsCore1_Send1 =
{
  /* .SendChannel = */
  {
    /* .Dyn        = */ &OsCfg_XSig_OsCore1_Send1_XSignalIsr_OsCore2_Recv1_Send_Dyn,
    /* .Receive    = */ &OsCfg_XSig_OsCore1_Send1_XSignalIsr_OsCore2_Recv1_Recv_Dyn,
    /* .Buffer     = */ OsCfg_XSig_OsCore1_Send1_XSignalIsr_OsCore2_Recv1_Buffer_Dyn,
    /* .BufferSize = */ OS_CFG_SIZE_OSCORE1_SEND1_XSIGNALISR_OSCORE2_RECV1_BUFFER
  },
  /* .XSigIsr     = */ &OsCfg_Isr_XSignalIsr_OsCore2,
  /* .RecvPort    = */ &OsCfg_XSig_XSignalIsr_OsCore2_Recv1,
  /* .SendCore    = */ &OsCfg_Core_OsCore1
};

/*! X-Signal receive port configuration data: XSignalIsr_OsCore1_Recv0 <- OsCore0 */
OS_LOCAL CONST(Os_XSigRecvPortConfigType, OS_CONST) OsCfg_XSig_XSignalIsr_OsCore1_Recv0 =
{
  /* .RecvChannel = */
  {
    /* .Dyn        = */ &OsCfg_XSig_OsCore0_Send0_XSignalIsr_OsCore1_Recv0_Recv_Dyn,
    /* .Send       = */ &OsCfg_XSig_OsCore0_Send0_XSignalIsr_OsCore1_Recv0_Send_Dyn,
    /* .Buffer     = */ OsCfg_XSig_OsCore0_Send0_XSignalIsr_OsCore1_Recv0_Buffer_Dyn,
    /* .BufferSize = */ OS_CFG_SIZE_OSCORE0_SEND0_XSIGNALISR_OSCORE1_RECV0_BUFFER
  },
  /* .SendPort    = */ &OsCfg_XSig_OsCore0_Send0
};

/*! X-Signal receive port configuration data: XSignalIsr_OsCore1_Recv1 <- OsCore2 */
OS_LOCAL CONST(Os_XSigRecvPortConfigType, OS_CONST) OsCfg_XSig_XSignalIsr_OsCore1_Recv1 =
{
  /* .RecvChannel = */
  {
    /* .Dyn        = */ &OsCfg_XSig_OsCore2_Send0_XSignalIsr_OsCore1_Recv1_Recv_Dyn,
    /* .Send       = */ &OsCfg_XSig_OsCore2_Send0_XSignalIsr_OsCore1_Recv1_Send_Dyn,
    /* .Buffer     = */ OsCfg_XSig_OsCore2_Send0_XSignalIsr_OsCore1_Recv1_Buffer_Dyn,
    /* .BufferSize = */ OS_CFG_SIZE_OSCORE2_SEND0_XSIGNALISR_OSCORE1_RECV1_BUFFER
  },
  /* .SendPort    = */ &OsCfg_XSig_OsCore2_Send0
};

/*! X-Signal ISR function table: XSignalIsr_OsCore1 */
CONST(Os_XSigFunctionTableConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore1_FuncTable =
{
  /* .FunctionDescription = */
  {
    { Os_XSigRecv_ActivateTask }, /* OSServiceId_ActivateTask */
    { Os_XSigRecv_CancelAlarm }, /* OSServiceId_CancelAlarm */
    { Os_XSigRecv_ControlIdle }, /* OSServiceId_ControlIdle */
    { Os_XSigRecv_GetAlarm }, /* OSServiceId_GetAlarm */
    { Os_XSigRecv_GetApplicationState }, /* OSServiceId_GetApplicationState */
    { Os_XSigRecv_GetCounterValue }, /* OSServiceId_GetCounterValue */
    { Os_XSigRecv_GetErrorHookStackUsage }, /* OSServiceId_GetErrorHookStackUsage */
    { Os_XSigRecv_GetEvent }, /* OSServiceId_GetEvent */
    { Os_XSigRecv_GetISRStackUsage }, /* OSServiceId_GetISRStackUsage */
    { Os_XSigRecv_GetKernelStackUsage }, /* OSServiceId_GetKernelStackUsage */
    { Os_XSigRecv_GetProtectionHookStackUsage }, /* OSServiceId_GetProtectionHookStackUsage */
    { Os_XSigRecv_GetScheduleTableStatus }, /* OSServiceId_GetScheduleTableStatus */
    { Os_XSigRecv_GetShutdownHookStackUsage }, /* OSServiceId_GetShutdownHookStackUsage */
    { Os_XSigRecv_GetStartupHookStackUsage }, /* OSServiceId_GetStartupHookStackUsage */
    { Os_XSigRecv_GetTaskStackUsage }, /* OSServiceId_GetTaskStackUsage */
    { Os_XSigRecv_GetTaskState }, /* OSServiceId_GetTaskState */
    { Os_XSigRecv_HookCallCallback }, /* OSServiceId_HookCallCallback */
    { Os_XSigRecv_NextScheduleTable }, /* OSServiceId_NextScheduleTable */
    { Os_XSigRecv_SetAbsAlarm }, /* OSServiceId_SetAbsAlarm */
    { Os_XSigRecv_SetEvent }, /* OSServiceId_SetEvent */
    { Os_XSigRecv_SetRelAlarm }, /* OSServiceId_SetRelAlarm */
    { Os_XSigRecv_ShutdownAllCores }, /* OSServiceId_ShutdownAllCores */
    { Os_XSigRecv_StartScheduleTableAbs }, /* OSServiceId_StartScheduleTableAbs */
    { Os_XSigRecv_StartScheduleTableRel }, /* OSServiceId_StartScheduleTableRel */
    { Os_XSigRecv_StopScheduleTable }, /* OSServiceId_StopScheduleTable */
    { Os_XSigRecv_TerminateApplication }, /* OSServiceId_TerminateApplication */
    { NULL_PTR }
  }
};

/*! X-Signal ISR receive ports reference table: XSignalIsr_OsCore1 */
CONST(Os_XSigRecvPortConfigRefType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore1_PortRefs[OS_CFG_NUM_ISR_XSIGNALISR_OSCORE1_PORTS + 1] =
{
  &OsCfg_XSig_XSignalIsr_OsCore1_Recv0,
  &OsCfg_XSig_XSignalIsr_OsCore1_Recv1,
  NULL_PTR
};

/*! X-Signal receiver ISRs reference table: OsCore1 */
OS_LOCAL CONST(Os_XSigIsrConfigRefType, OS_CONST) OsCfg_XSig_OsCore1_IsrRefs[OS_CFG_NUM_XSIG_OSCORE1_ISRS + 1] =
{
  &OsCfg_Isr_XSignalIsr_OsCore1,
  NULL_PTR
};

/*! X-Signal configuration data: OsCore1 */
CONST(Os_XSigConfigType, OS_CONST) OsCfg_XSig_OsCore1 =
{
  /* .XSigSendPorts    = */ 
  {
    /* [0] = */ &OsCfg_XSig_OsCore1_Send0, /* OsCore0 */
    /* [1] = */ NULL_PTR, /* OsCore1 */
    /* [2] = */ &OsCfg_XSig_OsCore1_Send1 /* OsCore2 */
  },
  /* .XSigRecvIsrRefs  = */ OsCfg_XSig_OsCore1_IsrRefs,
  /* .XSigRecvIsrCount = */ OS_CFG_NUM_XSIG_OSCORE1_ISRS
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! X-Signal send port configuration data: OsCore2 -> OsCore1/XSignalIsr_OsCore1_Recv1 */
OS_LOCAL CONST(Os_XSigSendPortConfigType, OS_CONST) OsCfg_XSig_OsCore2_Send0 =
{
  /* .SendChannel = */
  {
    /* .Dyn        = */ &OsCfg_XSig_OsCore2_Send0_XSignalIsr_OsCore1_Recv1_Send_Dyn,
    /* .Receive    = */ &OsCfg_XSig_OsCore2_Send0_XSignalIsr_OsCore1_Recv1_Recv_Dyn,
    /* .Buffer     = */ OsCfg_XSig_OsCore2_Send0_XSignalIsr_OsCore1_Recv1_Buffer_Dyn,
    /* .BufferSize = */ OS_CFG_SIZE_OSCORE2_SEND0_XSIGNALISR_OSCORE1_RECV1_BUFFER
  },
  /* .XSigIsr     = */ &OsCfg_Isr_XSignalIsr_OsCore1,
  /* .RecvPort    = */ &OsCfg_XSig_XSignalIsr_OsCore1_Recv1,
  /* .SendCore    = */ &OsCfg_Core_OsCore2
};

/*! X-Signal send port configuration data: OsCore2 -> OsCore0/XSignalIsr_OsCore0_Recv1 */
OS_LOCAL CONST(Os_XSigSendPortConfigType, OS_CONST) OsCfg_XSig_OsCore2_Send1 =
{
  /* .SendChannel = */
  {
    /* .Dyn        = */ &OsCfg_XSig_OsCore2_Send1_XSignalIsr_OsCore0_Recv1_Send_Dyn,
    /* .Receive    = */ &OsCfg_XSig_OsCore2_Send1_XSignalIsr_OsCore0_Recv1_Recv_Dyn,
    /* .Buffer     = */ OsCfg_XSig_OsCore2_Send1_XSignalIsr_OsCore0_Recv1_Buffer_Dyn,
    /* .BufferSize = */ OS_CFG_SIZE_OSCORE2_SEND1_XSIGNALISR_OSCORE0_RECV1_BUFFER
  },
  /* .XSigIsr     = */ &OsCfg_Isr_XSignalIsr_OsCore0,
  /* .RecvPort    = */ &OsCfg_XSig_XSignalIsr_OsCore0_Recv1,
  /* .SendCore    = */ &OsCfg_Core_OsCore2
};

/*! X-Signal receive port configuration data: XSignalIsr_OsCore2_Recv0 <- OsCore0 */
OS_LOCAL CONST(Os_XSigRecvPortConfigType, OS_CONST) OsCfg_XSig_XSignalIsr_OsCore2_Recv0 =
{
  /* .RecvChannel = */
  {
    /* .Dyn        = */ &OsCfg_XSig_OsCore0_Send1_XSignalIsr_OsCore2_Recv0_Recv_Dyn,
    /* .Send       = */ &OsCfg_XSig_OsCore0_Send1_XSignalIsr_OsCore2_Recv0_Send_Dyn,
    /* .Buffer     = */ OsCfg_XSig_OsCore0_Send1_XSignalIsr_OsCore2_Recv0_Buffer_Dyn,
    /* .BufferSize = */ OS_CFG_SIZE_OSCORE0_SEND1_XSIGNALISR_OSCORE2_RECV0_BUFFER
  },
  /* .SendPort    = */ &OsCfg_XSig_OsCore0_Send1
};

/*! X-Signal receive port configuration data: XSignalIsr_OsCore2_Recv1 <- OsCore1 */
OS_LOCAL CONST(Os_XSigRecvPortConfigType, OS_CONST) OsCfg_XSig_XSignalIsr_OsCore2_Recv1 =
{
  /* .RecvChannel = */
  {
    /* .Dyn        = */ &OsCfg_XSig_OsCore1_Send1_XSignalIsr_OsCore2_Recv1_Recv_Dyn,
    /* .Send       = */ &OsCfg_XSig_OsCore1_Send1_XSignalIsr_OsCore2_Recv1_Send_Dyn,
    /* .Buffer     = */ OsCfg_XSig_OsCore1_Send1_XSignalIsr_OsCore2_Recv1_Buffer_Dyn,
    /* .BufferSize = */ OS_CFG_SIZE_OSCORE1_SEND1_XSIGNALISR_OSCORE2_RECV1_BUFFER
  },
  /* .SendPort    = */ &OsCfg_XSig_OsCore1_Send1
};

/*! X-Signal ISR function table: XSignalIsr_OsCore2 */
CONST(Os_XSigFunctionTableConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore2_FuncTable =
{
  /* .FunctionDescription = */
  {
    { Os_XSigRecv_ActivateTask }, /* OSServiceId_ActivateTask */
    { Os_XSigRecv_CancelAlarm }, /* OSServiceId_CancelAlarm */
    { Os_XSigRecv_ControlIdle }, /* OSServiceId_ControlIdle */
    { Os_XSigRecv_GetAlarm }, /* OSServiceId_GetAlarm */
    { Os_XSigRecv_GetApplicationState }, /* OSServiceId_GetApplicationState */
    { Os_XSigRecv_GetCounterValue }, /* OSServiceId_GetCounterValue */
    { Os_XSigRecv_GetErrorHookStackUsage }, /* OSServiceId_GetErrorHookStackUsage */
    { Os_XSigRecv_GetEvent }, /* OSServiceId_GetEvent */
    { Os_XSigRecv_GetISRStackUsage }, /* OSServiceId_GetISRStackUsage */
    { Os_XSigRecv_GetKernelStackUsage }, /* OSServiceId_GetKernelStackUsage */
    { Os_XSigRecv_GetProtectionHookStackUsage }, /* OSServiceId_GetProtectionHookStackUsage */
    { Os_XSigRecv_GetScheduleTableStatus }, /* OSServiceId_GetScheduleTableStatus */
    { Os_XSigRecv_GetShutdownHookStackUsage }, /* OSServiceId_GetShutdownHookStackUsage */
    { Os_XSigRecv_GetStartupHookStackUsage }, /* OSServiceId_GetStartupHookStackUsage */
    { Os_XSigRecv_GetTaskStackUsage }, /* OSServiceId_GetTaskStackUsage */
    { Os_XSigRecv_GetTaskState }, /* OSServiceId_GetTaskState */
    { Os_XSigRecv_HookCallCallback }, /* OSServiceId_HookCallCallback */
    { Os_XSigRecv_NextScheduleTable }, /* OSServiceId_NextScheduleTable */
    { Os_XSigRecv_SetAbsAlarm }, /* OSServiceId_SetAbsAlarm */
    { Os_XSigRecv_SetEvent }, /* OSServiceId_SetEvent */
    { Os_XSigRecv_SetRelAlarm }, /* OSServiceId_SetRelAlarm */
    { Os_XSigRecv_ShutdownAllCores }, /* OSServiceId_ShutdownAllCores */
    { Os_XSigRecv_StartScheduleTableAbs }, /* OSServiceId_StartScheduleTableAbs */
    { Os_XSigRecv_StartScheduleTableRel }, /* OSServiceId_StartScheduleTableRel */
    { Os_XSigRecv_StopScheduleTable }, /* OSServiceId_StopScheduleTable */
    { Os_XSigRecv_TerminateApplication }, /* OSServiceId_TerminateApplication */
    { NULL_PTR }
  }
};

/*! X-Signal ISR receive ports reference table: XSignalIsr_OsCore2 */
CONST(Os_XSigRecvPortConfigRefType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore2_PortRefs[OS_CFG_NUM_ISR_XSIGNALISR_OSCORE2_PORTS + 1] =
{
  &OsCfg_XSig_XSignalIsr_OsCore2_Recv0,
  &OsCfg_XSig_XSignalIsr_OsCore2_Recv1,
  NULL_PTR
};

/*! X-Signal receiver ISRs reference table: OsCore2 */
OS_LOCAL CONST(Os_XSigIsrConfigRefType, OS_CONST) OsCfg_XSig_OsCore2_IsrRefs[OS_CFG_NUM_XSIG_OSCORE2_ISRS + 1] =
{
  &OsCfg_Isr_XSignalIsr_OsCore2,
  NULL_PTR
};

/*! X-Signal configuration data: OsCore2 */
CONST(Os_XSigConfigType, OS_CONST) OsCfg_XSig_OsCore2 =
{
  /* .XSigSendPorts    = */ 
  {
    /* [0] = */ &OsCfg_XSig_OsCore2_Send1, /* OsCore0 */
    /* [1] = */ &OsCfg_XSig_OsCore2_Send0, /* OsCore1 */
    /* [2] = */ NULL_PTR /* OsCore2 */
  },
  /* .XSigRecvIsrRefs  = */ OsCfg_XSig_OsCore2_IsrRefs,
  /* .XSigRecvIsrCount = */ OS_CFG_NUM_XSIG_OSCORE2_ISRS
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
 *  END OF FILE: Os_XSignal_Lcfg.c
 *********************************************************************************************************************/
