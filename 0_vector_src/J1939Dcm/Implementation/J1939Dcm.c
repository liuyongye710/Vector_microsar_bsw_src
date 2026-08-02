/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  J1939Dcm.c
 *    Component:  MICROSAR Diagnostic Communication Manager for SAE J1939
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  implementation file for J1939 DCM
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define J1939DCM_SOURCE

/* ********************************************************************************************************************
 *  GLOBAL MISRA / PCLINT VIOLATIONS
 *********************************************************************************************************************/
 /*lint --e{438} */
 /*lint --e{506} */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/*! Module definitions */
#include "J1939Dcm.h"

/*! Used modules */
#if(J1939DCM_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif
#include "SchM_J1939Dcm.h"
#include "BswM_J1939Dcm.h"
#include "J1939Rm.h"
#include "J1939Nm.h"
#include "Dem_J1939Dcm.h"
#include "PduR_J1939Dcm.h"
#include "ComM.h"

#if (J1939DCM_CONFIGURATION_VARIANT == J1939DCM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
/*! Post-build error reporting */
# include "EcuM_Error.h"
#endif

/*! Internal definitions */
#include "J1939Dcm_Priv.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/*! Vendor specific version information is BCD coded */
#if ((J1939DCM_SW_MAJOR_VERSION != 15u) || \
    (J1939DCM_SW_MINOR_VERSION !=  1u) || \
    (J1939DCM_SW_PATCH_VERSION != 0u))
# error "Vendor specific version numbers of J1939Dcm.c and J1939Dcm.h are inconsistent"
#endif

#if ((J1939DCM_CBK_MAJOR_VERSION != 15u) || \
    (J1939DCM_CBK_MINOR_VERSION !=  1u) || \
    (J1939DCM_CBK_PATCH_VERSION !=  0u))
# error "Vendor specific version numbers of J1939Dcm.c and J1939Dcm_Cbk.h are inconsistent"
#endif

#if ((J1939DCM_PRIV_MAJOR_VERSION != 15u) || \
    (J1939DCM_PRIV_MINOR_VERSION !=  1u) || \
    (J1939DCM_PRIV_PATCH_VERSION !=  0u))
# error "Vendor specific version numbers of J1939Dcm.c and J1939Dcm_Priv.h are inconsistent"
#endif

#if ((J1939DCM_TYPES_MAJOR_VERSION != 15u) || \
    (J1939DCM_TYPES_MINOR_VERSION !=  1u) || \
    (J1939DCM_TYPES_PATCH_VERSION !=  0u))
# error "Vendor specific version numbers of J1939Dcm.c and J1939Dcm_Types.h are inconsistent"
#endif

/*! Versions of all included configuration header files shall be checked */
#if ((J1939DCM_CFG_SW_MAJOR_VERSION != 15u) || \
    (J1939DCM_CFG_SW_MINOR_VERSION !=  1u) || \
    (J1939DCM_CFG_SW_PATCH_VERSION !=  0u))
# error "Version numbers of J1939Dcm.c and J1939Dcm_Cfg.h are inconsistent!"
#endif

#if ((J1939DCM_CFG_LCFG_MAJOR_VERSION != 15u) || \
    (J1939DCM_CFG_LCFG_MINOR_VERSION !=  1u) || \
    (J1939DCM_CFG_LCFG_PATCH_VERSION !=  0u))
# error "Version numbers of J1939Dcm.c and J1939Dcm_Lcfg.h are inconsistent!"
#endif

#if ((J1939DCM_CFG_PBCFG_MAJOR_VERSION != 15u) || \
    (J1939DCM_CFG_PBCFG_MINOR_VERSION !=  1u) || \
    (J1939DCM_CFG_PBCFG_PATCH_VERSION !=  0u))
# error "Version numbers of J1939Dcm.c and J1939Dcm_PBcfg.h are inconsistent!"
#endif

#if ((J1939DCM_CFG_GEN_MAJOR_VERSION != 15u) || \
    (J1939DCM_CFG_GEN_MINOR_VERSION !=  1u) || \
    (J1939DCM_CFG_GEN_PATCH_VERSION !=  0u))
# error "Incompatible configuration file version used!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#if !defined (J1939DCM_LOCAL)                                                                                                                        /* COV_J1939DCM_MACRO_OVERRIDE */
# define J1939DCM_LOCAL                                              static
#endif

#if !defined (J1939DCM_LOCAL_INLINE)                                                                                                                 /* COV_J1939DCM_MACRO_OVERRIDE */
# if defined (LOCAL_INLINE)                                                                                                                          /* COV_J1939DCM_MACRO_OVERRIDE */
#  define J1939DCM_LOCAL_INLINE                                      LOCAL_INLINE
# else
#  define J1939DCM_LOCAL_INLINE                                      J1939DCM_LOCAL
# endif
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/
/*! Assertions */
#if(J1939DCM_DEV_ERROR_REPORT == STD_ON)
# define J1939Dcm_DetAssertAlways(apiId, errorId)                    (void)Det_ReportError(J1939DCM_MODULE_ID, J1939DCM_INSTANCE_ID, (apiId), (errorId));
# define J1939Dcm_DetAssert(check, apiId, errorId)                   {if(!(check)) {J1939Dcm_DetAssertAlways( (apiId), (errorId))}}
#else
# define J1939Dcm_DetAssertAlways(apiId, errorId)
# define J1939Dcm_DetAssert(check, apiId, errorId)
#endif

#define J1939Dcm_IsValidNodeHdl(nodeHdl)                             ((nodeHdl) < J1939Dcm_Cfg_GetNodeTableSize())                                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define J1939Dcm_IsValidChannelHdl(channelHdl)                       ((channelHdl) < J1939Dcm_Cfg_GetChannelTableSize())                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#define J1939Dcm_NetIsNodeChannelSupported(nodeHdl, channelHdl)      (J1939Dcm_Cfg_GetChannelSupported((nodeHdl), (channelHdl)))                     /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! EcuM */
#if !defined (J1939DCM_EcuMReportBswError)                                                                                                           /* COV_J1939DCM_MACRO_OVERRIDE */
# if (J1939DCM_CONFIGURATION_VARIANT == J1939DCM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
#  define J1939DCM_EcuMReportBswError(errorId)                       (EcuM_BswErrorHook((uint16) J1939DCM_MODULE_ID, (errorId)));                    /* PRQA S 3412 */ /* MD_MSR_FctLikeMacro */
# else
#  define J1939DCM_EcuMReportBswError(errorId)
# endif
#endif

/*! critical sections */
#define J1939Dcm_EnterCritical()                                     SchM_Enter_J1939Dcm_J1939DCM_EXCLUSIVE_AREA_0()                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define J1939Dcm_ExitCritical()                                      SchM_Exit_J1939Dcm_J1939DCM_EXCLUSIVE_AREA_0()                                  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/*! Indicates the initial state */
typedef uint8 J1939Dcm_InitStateType;
#define J1939DCM_STATE_UNINIT                                        (J1939Dcm_InitStateType)(0x00u)
#define J1939DCM_STATE_INIT                                          (J1939Dcm_InitStateType)(0x01u)

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/
#define J1939DCM_START_SEC_VAR_INIT_8
#include "J1939Dcm_MemMap.h"                                                                                                                         /* PRQA S 5087 */ /* MD_MSR_MemMap */

J1939DCM_LOCAL VAR(J1939Dcm_InitStateType, J1939DCM_VAR_INIT) J1939Dcm_InitState = J1939DCM_STATE_UNINIT;

#define J1939DCM_STOP_SEC_VAR_INIT_8
#include "J1939Dcm_MemMap.h"                                                                                                                         /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define J1939DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "J1939Dcm_MemMap.h"                                                                                                                         /* PRQA S 5087 */ /* MD_MSR_MemMap */

J1939DCM_LOCAL VAR(J1939Dcm_DiagContextType, J1939DCM_VAR_NOINIT) J1939Dcm_DiagContext;

#define J1939DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "J1939Dcm_MemMap.h"                                                                                                                         /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* --- Global Config Pointer --------------------------------------------------------------------------------------- */
#if (J1939DCM_USE_INIT_POINTER == STD_ON)
# define J1939DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
# include "J1939Dcm_MemMap.h"                                                                                                                        /* PRQA S 5087 */ /* MD_MSR_MemMap */
J1939DCM_LOCAL P2CONST(J1939Dcm_ConfigType, J1939DCM_VAR_NOINIT, J1939DCM_INIT_DATA)  J1939Dcm_ConfigDataPtr;
# define J1939DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
# include "J1939Dcm_MemMap.h"                                                                                                                        /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  CONSISTENCY CHECKS
 **********************************************************************************************************************/
#if (J1939DCM_MAX_NUM_CHANNELS > 16)
# error "Currently, the J1939Dcm does not support more than 16 channels"
#endif

#if ((J1939DCM_FF_HEADER_LENGTH != 5) || \
    (J1939DCM_FF_MAX_DATA_LENGTH != 251))
# error "J1939DCM_MAX_FF_SIZE_CONFORM does not correctly indicates whether the configuration is capable to receive a freeze frame with the maximum applicable size"
#endif

#if (J1939DCM_FF_DATA_OFFSET > J1939DCM_FF_HEADER_LENGTH)
# error "J1939DCM_FF_DATA_OFFSET must not be greater than J1939DCM_FF_HEADER_LENGTH."
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define J1939DCM_START_SEC_CODE
#include "J1939Dcm_MemMap.h"                                                                                                                         /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (J1939DCM_NEED_DTC_HANDLER == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DtcHandlerStateInit()
 *********************************************************************************************************************/
/*! \brief          Initializes managed DTC handler state.
 *  \details        -
 *  \param[in]      pDtcHandlerState    DTC handler state to be initialized
 *  \param[in]      pBufferContext      Pointer to DM message buffer context
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerStateInit(
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState,
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext
  );
#endif

#if (J1939DCM_NEED_DTC_HANDLER == STD_ON)
/**********************************************************************************************************************
 *  J1939Dcm_DtcHandlerProvideResDataAsU8()
 *********************************************************************************************************************/
/*! \brief          Sets UINT8 Value in response buffer and updates response buffer parameters.
 *  \details        -
 *  \param[in]      pDtcHandlerState    DTC handler state for response transmission
 *  \param[in]      value               Value to be written to response buffer
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-J1939Dcm21123
 *  \pre            -
 *********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerProvideResDataAsU8(
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState,
  uint8 value
  );
#endif

#if (J1939DCM_NEED_DTC_HANDLER_FF == STD_ON)
/**********************************************************************************************************************
 *  J1939Dcm_DtcHandlerCommitResData()
 *********************************************************************************************************************/
/*! \brief          Committs nbrBytes in response buffer.
 *  \details        -
 *  \param[in]      pDtcHandlerState    DTC handler state for response transmission
 *  \param[in]      nbrBytes            Number of bytes to be committed in response buffer
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-J1939Dcm21123
 *  \pre            -
 *********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
  J1939Dcm_DtcHandlerCommitResData(
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState,
  PduLengthType nbrBytes
  );
#endif

#if ((J1939DCM_NEED_DTC_HANDLER_SPN  == STD_ON) || \
    (J1939DCM_NEED_DTC_HANDLER_FF   == STD_ON) || \
    (J1939DCM_NEED_DTC_HANDLER_LAMP == STD_ON))
/**********************************************************************************************************************
 *  J1939Dcm_DtcHandlerProvideResDataAsU24()
 *********************************************************************************************************************/
/*! \brief          Sets UINT24 Value in response buffer and updates response buffer parameters.
 *  \details        -
 *  \param[in]      pDtcHandlerState    DTC handler state for response transmission
 *  \param[in]      value               Value to be written to response buffer
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-J1939Dcm21123
 *  \pre            -
 *********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerProvideResDataAsU24(
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState,
  uint32 value
  );
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueuedTxConfirmation()
 **********************************************************************************************************************/
/*! \brief          Handles queued DM1 Tx confirmation.
 *  \details        -
 *  \param[in]      pDM1Queue  Pointer to DM1 queue. Copy of the pointer to the global volatile queue.
 *  \param[in,out]  pDM1State  Pointer to DM1 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported.
 *  \trace          DSGN-J1939DcmDiag1952
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueuedTxConfirmation(
  J1939Dcm_DM1QueueReadPtrType pDM1Queue,
  J1939Dcm_DM1StatePtrType pDM1State
  );
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueuedFailedTxConfirmation()
 **********************************************************************************************************************/
/*! \brief          Handles queued DM1 failed Tx confirmation.
 *  \details        -
 *  \param[in]      pDM1Queue  Pointer to DM1 queue. Copy of the pointer to the global volatile queue.
 *  \param[in,out]  pDM1State  Pointer to DM1 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported.
 *  \trace          DSGN-J1939DcmDiag1952
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueuedFailedTxConfirmation(
  J1939Dcm_DM1QueueReadPtrType pDM1Queue,
  J1939Dcm_DM1StatePtrType pDM1State
  );
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueuedCommunicationStateChange()
 **********************************************************************************************************************/
/*! \brief          Handles queued DM1 communication state change.
 *  \details        -
 *  \param[in]      pDM1Queue  Pointer to DM1 queue. Copy of the pointer to the global volatile queue.
 *  \param[in,out]  pDM1State  Pointer to DM1 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported.
 *  \trace          DSGN-J1939DcmDiag1952
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueuedCommunicationStateChange(
  J1939Dcm_DM1QueueReadPtrType pDM1Queue,
  J1939Dcm_DM1StatePtrType pDM1State
  );
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueuedRequest()
 **********************************************************************************************************************/
/*! \brief          Handles queued DM1 requests.
 *  \details        -
 *  \param[in]      pDM1Queue  Pointer to DM1 queue. Copy of the pointer to the global volatile queue.
 *  \param[out]     pSendNACK  Pointer to a negative acknowledgement flag.
 *  \param[in,out]  pDM1State  Pointer to DM1 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported.
 *  \trace          DSGN-J1939DcmDiag1952
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueuedRequest(
  J1939Dcm_DM1QueueReadPtrType pDM1Queue,
  CONSTP2VAR(boolean, AUTOMATIC, J1939DCM_INTERNAL_DATA) pSendNACK,
  J1939Dcm_DM1StatePtrType pDM1State
  );
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueuedDtcStatusChange()
 **********************************************************************************************************************/
/*! \brief          Handles queued DM1 DTC status change.
 *  \details        -
 *  \param[in]      pDM1Queue  Pointer to DM1 queue. Copy of the pointer to the global volatile queue.
 *  \param[in,out]  pDM1State  Pointer to DM1 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported.
 *  \trace          DSGN-J1939DcmDiag1952
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueuedDtcStatusChange(
  J1939Dcm_DM1QueueReadPtrType pDM1Queue,
  J1939Dcm_DM1StatePtrType pDM1State
  );
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleTimer()
 **********************************************************************************************************************/
/*! \brief          Handles DM1 timer.
 *  \details        -
 *  \param[in,out]  pDM1State  Pointer to DM1 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported.
 *  \trace          DSGN-J1939DcmDiag1952, DSGN-J1939Dcm20861
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleTimer(
  J1939Dcm_DM1StatePtrType pDM1State
  );
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueuedInfos()
 **********************************************************************************************************************/
/*! \brief          Handles DM1 queued information.
 *  \details        -
 *  \param[in]      pDM1Queue  Pointer to DM1 queue. Copy of the pointer to the global volatile queue.
 *  \param[out]     pSendNACK  Pointer to a NACK flag.
 *  \param[in,out]  pDM1State  Pointer to DM1 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported.
 *  \trace          DSGN-J1939DcmDiag1952
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueuedInfos(
  J1939Dcm_DM1QueueReadPtrType pDM1Queue,
  CONSTP2VAR(boolean, AUTOMATIC, J1939DCM_INTERNAL_DATA) pSendNACK,
  J1939Dcm_DM1StatePtrType pDM1State
  );
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueue()
 **********************************************************************************************************************/
/*! \brief          Handles DM1 queue.
 *  \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported.
 *  \trace          DSGN-J1939DcmDiag1952
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueue(
  J1939Dcm_NodeContextPtrType pNodeContext
  );
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1AssembleMessage()
 **********************************************************************************************************************/
/*! \brief          Assembles DM1 message.
 *  \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \param[out]     pAcknowledge  Pointer to an acknowledgement code.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported.
 *  \trace          DSGN-J1939Dcm20740
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1AssembleMessage(
  J1939Dcm_NodeContextPtrType pNodeContext,
  CONSTP2VAR(J1939Rm_AckCode, AUTOMATIC, J1939DCM_INTERNAL_DATA) pAcknowledge
  );
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1Broadcast()
 **********************************************************************************************************************/
/*! \brief          Broadcasts DM1.
 *  \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported.
 *  \trace          DSGN-J1939Dcm20773, DSGN-J1939Dcm21099
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Broadcast(
  J1939Dcm_NodeContextPtrType pNodeContext
  );
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1Unicast()
 **********************************************************************************************************************/
/*! \brief          Unicasts DM1.
 *  \details        -
 *  \param[in,out]  pDM1State  Pointer to DM1 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported.
 *  \trace          DSGN-J1939Dcm21099
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Unicast(
  J1939Dcm_DM1StatePtrType pDM1State
  );
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1Transmit()
 **********************************************************************************************************************/
/*! \brief          Transmits DM1 message.
 *  \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported.
 *  \trace          DSGN-J1939Dcm20773, DSGN-J1939Dcm21099, DSGN-J1939Dcm21783
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Transmit(
  J1939Dcm_NodeContextPtrType pNodeContext
  );
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleAssemblyFailure()
 **********************************************************************************************************************/
/*! \brief          Handles failure of DM1 Assembly.
 *  \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \param[in]      acknowledge   An acknowledgement code.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported.
 *  \trace          DSGN-J1939Dcm21783
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleAssemblyFailure(
  J1939Dcm_NodeContextPtrType pNodeContext,
  J1939Rm_AckCode acknowledge
  );
#endif

#if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM13UpdateBroadcastStatus()
 **********************************************************************************************************************/
/*! \brief       Updates broadcast status.
 *  \details     -
 *  \param[in]   pDM13Queue              Pointer to DM13 queue. Copy of the pointer to the global volatile queue.
 *  \param[out]  pBroadcastStateChanged  Indicates whether broadcast was changed.
 *  \param[out]  pRestartTimeout         Indicates whether timout should be restarted.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \config      This function is available only if DM13 is supported.
 *  \trace       DSGN-J1939DcmDiag1957
 *  \pre         -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM13UpdateBroadcastStatus(
  J1939Dcm_DM13QueueReadPtrType pDM13Queue,
  CONSTP2VAR(boolean, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBroadcastStateChanged,
  CONSTP2VAR(boolean, AUTOMATIC, J1939DCM_INTERNAL_DATA) pRestartTimeout
  );
#endif

#if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM13HandleQueue()
 **********************************************************************************************************************/
/*! \brief       Handles DM13 queue.
 *  \details     -
 *  \param[out]  pBroadcastStateChanged  Indicates whether broadcast was changed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \config      This function is available only if DM13 is supported.
 *  \trace       DSGN-J1939DcmDiag1957, DSGN-J1939Dcm20820
 *  \pre         -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM13HandleQueue(
  CONSTP2VAR(boolean, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBroadcastStateChanged
  );
#endif

#if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM13HandleTimer()
 **********************************************************************************************************************/
/*! \brief       Handles DM13 timer.
 *  \details     -
 *  \param[out]  pBroadcastStateChanged  Indicates whether broadcast was changed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \config      This function is available only if DM13 is supported.
 *  \trace       DSGN-J1939DcmDiag1957
 *  \pre         -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM13HandleTimer(
  CONSTP2VAR(boolean, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBroadcastStateChanged
  );
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM35HandleQueuedTxConfirmation()
 **********************************************************************************************************************/
/*! \brief          Handles queued DM35 Tx confirmation.
 *  \details        -
 *  \param[in]      pDM35Queue  Pointer to DM35 queue. Copy of the pointer to the global volatile queue.
 *  \param[in,out]  pDM35State  Pointer to DM35 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM35 is supported.
 *  \trace          DSGN-J1939DcmDiag1950
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleQueuedTxConfirmation(
  J1939Dcm_DM35QueueReadPtrType pDM35Queue,
  J1939Dcm_DM35StatePtrType pDM35State
  );
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM35HandleQueuedCommunicationStateChange()
 **********************************************************************************************************************/
/*! \brief          Handles queued DM35 communication state change.
 *  \details        -
 *  \param[in]      pDM35Queue  Pointer to DM35 queue. Copy of the pointer to the global volatile queue.
 *  \param[in,out]  pDM35State  Pointer to DM35 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM35 is supported.
 *  \trace          DSGN-J1939DcmDiag1950
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleQueuedCommunicationStateChange(
  J1939Dcm_DM35QueueReadPtrType pDM35Queue,
  J1939Dcm_DM35StatePtrType pDM35State
  );
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM35HandleQueuedRequest()
 **********************************************************************************************************************/
/*! \brief          Handles queued DM35 requests.
 *  \details        -
 *  \param[in]      pDM35Queue  Pointer to DM35 queue. Copy of the pointer to the global volatile queue.
 *  \param[in,out]  pDM35State  Pointer to DM35 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM35 is supported.
 *  \trace          DSGN-J1939DcmDiag1950, DSGN-J1939Dcm20738, DSGN-J1939Dcm20741
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleQueuedRequest(
  J1939Dcm_DM35QueueReadPtrType pDM35Queue,
  J1939Dcm_DM35StatePtrType pDM35State
  );
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM35HandleTimer()
 **********************************************************************************************************************/
/*! \brief          Handles DM35 timer.
 *  \details        -
 *  \param[in,out]  pDM35State  Pointer to DM35 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM35 is supported.
 *  \trace          DSGN-J1939DcmDiag1950, DSGN-J1939Dcm20738, DSGN-J1939Dcm20741
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleTimer(
  J1939Dcm_DM35StatePtrType pDM35State
  );
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM35HandleQueuedInfos()
 **********************************************************************************************************************/
/*! \brief          Handles DM35 queued information.
 *  \details        -
 *  \param[in]      pDM35Queue  Pointer to DM35 queue. Copy of the pointer to the global volatile queue.
 *  \param[in,out]  pDM35State  Pointer to DM35 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM35 is supported.
 *  \trace          DSGN-J1939DcmDiag1950, DSGN-J1939Dcm20738, DSGN-J1939Dcm20741
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleQueuedInfos(
  J1939Dcm_DM35QueueReadPtrType pDM35Queue,
  J1939Dcm_DM35StatePtrType pDM35State
  );
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM35HandleQueue()
 **********************************************************************************************************************/
/*! \brief          Handles DM35 Queue.
 *  \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM35 is supported.
 *  \trace          DSGN-J1939DcmDiag1950, DSGN-J1939Dcm20738, DSGN-J1939Dcm20741
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleQueue(
  J1939Dcm_NodeContextPtrType pNodeContext
  );
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM35AssembleMessage()
 **********************************************************************************************************************/
/*! \brief          Assembles DM35 message.
 *  \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM35 is supported.
 *  \trace          DSGN-J1939Dcm20741
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35AssembleMessage(
  J1939Dcm_NodeContextPtrType pNodeContext
  );
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM35Transmit()
 **********************************************************************************************************************/
/*! \brief          Transmits DM35 message.
 *  \details        -
 *  \param[in,out]  pDM1State  Pointer to DM1 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM35 is supported.
 *  \trace          DSGN-J1939Dcm20741
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35Transmit(
  J1939Dcm_NodeContextPtrType pNodeContext
  );
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM35HandleAssemblyFailure()
 **********************************************************************************************************************/
/*! \brief          Handles DM35 assembly failure.
 *  \details        -
 *  \param[in,out]  pDM35State  Pointer to DM35 state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM35 is supported.
 *  \trace          DSGN-J1939Dcm20741
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleAssemblyFailure(
  J1939Dcm_DM35StatePtrType pDM35State
  );
#endif

/**********************************************************************************************************************
 *  J1939Dcm_UtiProvideDataAsU8()
 *********************************************************************************************************************/
/*! \brief          Sets UINT8 Value in message buffer and updates message buffer parameters.
 *  \details        -
 *  \param[in]      pBufferContext   Pointer to message buffer context which has to be updated
 *  \param[in]      value            Value to be written to message buffer
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-J1939Dcm21123
 *  \pre            -
 *********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_UtiProvideDataAsU8(
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  uint8 value
  );

/**********************************************************************************************************************
*  J1939Dcm_UtiProvideMetaDataAsU8()
*********************************************************************************************************************/
/*! \brief          Copies the meta data value from the provided meta data buffer at the specified position
/                   to the message buffer and updates message buffer parameters.
*  \details        -
*  \param[in]      pBufferContext   Pointer to message buffer context which has to be updated
*  \param[in]      pTxHandler       Pointer to Tx handler context, which contains the meta data
*  \param[in]      metaDataLength   Length of the meta data
*  \param[in]      offset           Position within pMetaData from which the value has to be read
*  \context        TASK
*  \reentrant      FALSE
*  \synchronous    TRUE
*  \trace          DSGN-J1939Dcm22992
*  \pre            -
*********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_UtiProvideMetaDataAsU8(
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  J1939Dcm_TxHandlerPtrType pTxHandler,
  uint8 metaDataLength,
  uint8 offset
  );

#if (J1939DCM_DM24_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  J1939Dcm_UtiMemCopySafe()
 *********************************************************************************************************************/
/*! \brief          Copies data from the given source pointer to the target pointer.
 *  \details        This function is a wrapper for J1939Dcm_UtiMemCopy with additional checks of the input parameter.
 *  \param[in]      sourcePtr     Pointer to the source buffer
 *  \param[in]      targetPtr     Pointer to the target buffer
 *  \param[in]      targetPos     Buffer position where the data should be written to
 *  \param[in]      targetSize    Size of the target buffer
 *  \param[in]      length        Amount of data which should be written
 *  \return         lCopiedLength Number of written data bytes
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-J1939Dcm21123
 *  \pre            -
 *********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(PduLengthType, J1939DCM_CODE)
J1939Dcm_UtiMemCopySafe(
  CONSTP2CONST(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) sourcePtr,
  CONSTP2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) targetPtr,
  CONST(PduLengthType, J1939DCM_INTERNAL_DATA) targetPos,
  CONST(PduLengthType, J1939DCM_INTERNAL_DATA) targetSize,
  CONST(PduLengthType, J1939DCM_INTERNAL_DATA) length
  );
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleQueuedRequest()
 **********************************************************************************************************************/
/*! \brief          Handles queued DMx requests.
 *  \details        -
 *  \param[in]      pDMxQueue     Pointer to DMx queue. Copy of the pointer to the global volatile queue.
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DMx is supported.
 *  \trace          DSGN-J1939DcmDiag2027
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleQueuedRequest(
  J1939Dcm_DMxQueueReadPtrType pDMxQueue,
  J1939Dcm_NodeContextPtrType pNodeContext
  );
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleQueuedTxConfirmation()
 **********************************************************************************************************************/
/*! \brief          Handles queued DMx Tx confirmation.
 *  \details        -
 *  \param[in]      pDMxQueue  Pointer to DMx queue. Copy of the pointer to the global volatile queue.
 *  \param[in,out]  pDMxState  Pointer to DMx state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DMx is supported.
 *  \trace          DSGN-J1939DcmDiag2027
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleQueuedTxConfirmation(
  J1939Dcm_DMxQueueReadPtrType pDMxQueue,
  J1939Dcm_DMxStatePtrType pDMxState
  );
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleQueuedFailedTxConfirmation()
 **********************************************************************************************************************/
/*! \brief          Handles queued DMx failed Tx confirmation.
 *  \details        -
 *  \param[in]      pDM1Queue  Pointer to DMx queue. Copy of the pointer to the global volatile queue.
 *  \param[in,out]  pDMxState  Pointer to DMx state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DMx is supported.
 *  \trace          DSGN-J1939DcmDiag2027
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleQueuedFailedTxConfirmation(
  J1939Dcm_DMxQueueReadPtrType pDMxQueue,
  J1939Dcm_DMxStatePtrType pDMxState
  );
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleQueuedCommunicationStateChange()
 **********************************************************************************************************************/
/*! \brief          Handles queued DMx communication state change.
 *  \details        -
 *  \param[in]      pDMxQueue  Pointer to DMx queue. Copy of the pointer to the global volatile queue.
 *  \param[in,out]  pDMxState  Pointer to DMx state.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DMx is supported.
 *  \trace          DSGN-J1939DcmDiag2027, DSGN-J1939Dcm21783
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleQueuedCommunicationStateChange(
  J1939Dcm_DMxQueueReadPtrType pDMxQueue,
  J1939Dcm_DMxStatePtrType pDMxState
  );
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleQueuedInfos()
 **********************************************************************************************************************/
/*! \brief          Handles DMx queued information.
 *  \details        -
 *  \param[in]      pDMxQueue     Pointer to DMx queue. Copy of the pointer to the global volatile queue.
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DMx is supported.
 *  \trace          DSGN-J1939DcmDiag2027, DSGN-J1939Dcm21783
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleQueuedInfos(
  J1939Dcm_DMxQueueReadPtrType pDMxQueue,
  J1939Dcm_NodeContextPtrType pNodeContext
  );
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleQueue()
 **********************************************************************************************************************/
/*! \brief          Handles DMx queue.
 *  \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DMx is supported.
 *  \trace          DSGN-J1939DcmDiag2027, DSGN-J1939Dcm21783
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleQueue(
  J1939Dcm_NodeContextPtrType pNodeContext
  );
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxPrearrangeAssembly()
 **********************************************************************************************************************/
/*! \brief          Prearranges DMx assembly.
 *  \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \param[in]      diagMessage   Diagnostic message.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DMx is supported.
 *  \trace          DSGN-J1939Dcm21607, DSGN-J1939Dcm21671, DSGN-J1939Dcm21825, DSGN-J1939Dcm21887, DSGN-J1939Dcm21712,
 *                  DSGN-J1939Dcm21806, DSGN-J1939Dcm21830, DSGN-J1939Dcm22671, DSGN-J1939Dcm21722, DSGN-J1939Dcm21722,
 *                  DSGN-J1939Dcm22674, DSGN-J1939Dcm22667
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxPrearrangeAssembly(
  J1939Dcm_NodeContextPtrType pNodeContext,
  uint8_least diagMessage
  );
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxTriggerAssembly()
 **********************************************************************************************************************/
/*! \brief          Triggers DMx message assembly.
 *  \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \param[out]     pAcknowledge  Pointer to an acknowledgement code.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DMx is supported.
 *  \trace          DSGN-J1939DcmDiag2045, DSGN-J1939DcmDiag2019, DSGN-J1939DcmDiag2061
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxTriggerAssembly(
  J1939Dcm_NodeContextPtrType pNodeContext,
  CONSTP2VAR(J1939Rm_AckCode, AUTOMATIC, J1939DCM_INTERNAL_DATA) pAcknowledge
  );
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxAssembleMessage()
 **********************************************************************************************************************/
/*! \brief          Assembles DMx message.
 *  \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \param[out]     pAcknowledge  Pointer to an acknowledgement code.
 *  \param[in]      diagMessage   Diagnostic message.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DMx is supported.
 *  \trace          DSGN-J1939DcmDiag2061, DSGN-J1939Dcm21783
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxAssembleMessage(
  J1939Dcm_NodeContextPtrType pNodeContext,
  CONSTP2VAR(J1939Rm_AckCode, AUTOMATIC, J1939DCM_INTERNAL_DATA) pAcknowledge,
  uint8_least diagMessage
  );
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxTransmit()
 **********************************************************************************************************************/
/*! \brief          Transmits DMx message.
 *  \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \param[in]      diagMessage   Diagnostic message.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DMx is supported.
 *  \trace          DSGN-J1939DcmDiag2061, DSGN-J1939Dcm21783
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxTransmit(
  J1939Dcm_NodeContextPtrType pNodeContext,
  uint8_least diagMessage
  );
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleAssemblyFailure()
 **********************************************************************************************************************/
/*! \brief          Handles DMx assembly failure.
 *  \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \param[in]      acknowledge   An acknowledgement code.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DMx is supported.
 *  \trace          DSGN-J1939DcmDiag2061, DSGN-J1939Dcm21783
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleAssemblyFailure(
  J1939Dcm_NodeContextPtrType pNodeContext,
  J1939Rm_AckCode acknowledgement
  );
#endif

#if (J1939DCM_DM1_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1ConfirmTx()
 **********************************************************************************************************************/
/*! \brief          Indicates DM1 transmission success or failure.
    \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \param[in]      result        Transmission result
 *  \context        ANY
 *  \reentrant      FALSE
 *  \trace          DSGN-J1939DcmDiag1952
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1ConfirmTx(
  J1939Dcm_NodeContextPtrType pNodeContext,
  Std_ReturnType result
  );
#endif

#if ((J1939DCM_DM2_SUPPORT == STD_ON) || \
    (J1939DCM_DM4_SUPPORT == STD_ON) || \
    (J1939DCM_DM5_SUPPORT == STD_ON) || \
    (J1939DCM_DM24_SUPPORT == STD_ON) || \
    (J1939DCM_DM25_SUPPORT == STD_ON) || \
    (J1939DCM_DM27_SUPPORT == STD_ON) || \
    (J1939DCM_DM31_SUPPORT == STD_ON) || \
    (J1939DCM_DM53_SUPPORT == STD_ON) || \
    (J1939DCM_DM54_SUPPORT == STD_ON))
/**********************************************************************************************************************
 * J1939Dcm_DMxConfirmTx()
 **********************************************************************************************************************/
/*! \brief          Indicates DMx transmission success or failure.
    \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \param[in]      result        Transmission result
 *  \context        ANY
 *  \reentrant      FALSE
 *  \trace          DSGN-J1939DcmDiag2027
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxConfirmTx(
  J1939Dcm_NodeContextPtrType pNodeContext,
  Std_ReturnType result
  );
#endif

#if (J1939DCM_DM35_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM35ConfirmTx()
 **********************************************************************************************************************/
/*! \brief          Indicates DM35 transmission success or failure.
    \details        -
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \context        ANY
 *  \reentrant      FALSE
 *  \trace          DSGN-J1939DcmDiag1950
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35ConfirmTx(
  J1939Dcm_NodeContextPtrType pNodeContext
  );
#endif

#if (J1939DCM_DM15_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_NetTxHandlerConfirmMemRes()
 **********************************************************************************************************************/
/*! \brief      Indicates DM15 transmission success or failure.
    \details    -
 *  \param[in]  result  Transmission result
 *  \param[in]  apiId   Api Id
 *  \context    ANY
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939DcmDiag2092
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_NetTxHandlerConfirmMemRes(
  Std_ReturnType result,
  uint8 apiId
  );
#endif

#if ((J1939DCM_DM16_SUPPORT  == STD_ON) || \
    (J1939DCM_DM18_SUPPORT == STD_ON))
/**********************************************************************************************************************
 * J1939Dcm_NetTxHandlerConfirmMemData()
 **********************************************************************************************************************/
/*! \brief      Indicates DM16 and DM18 transmission success or failure.
    \details    -
 *  \param[in]  DataKind  Either DM16 or DM18
 *  \param[in]  result    Transmission result
 *  \param[in]  apiId     API Id
 *  \context    ANY
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939DcmDiag2093
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_NetTxHandlerConfirmMemData(
  J1939Dcm_MemDataType DataKind,
  Std_ReturnType result,
  uint8 apiId
  );
#endif

/**********************************************************************************************************************
 * J1939Dcm_NetUpdateQueuedCommStateChange()
 **********************************************************************************************************************/
/*! \brief          Updates queued communication state change.
 *  \details        -
 *  \param[in]      newState      New state the J1939Dcm shall enter
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \context        ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          DSGN-J1939Dcm20848
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_NetUpdateQueuedCommStateChange(
  J1939Dcm_StateType newState,
  J1939Dcm_NodeContextPtrType pNodeContext
  );

#if (J1939DCM_NEED_MEM_ACCESS == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_MemHandlerTransmit()
 **********************************************************************************************************************/
/*! \brief      Transmits memory message.
 *  \details    -
 *  \param[in]  diagMessage Diagnostic message
 *  \param[out] pTxResult   Pointer to tx result
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     This function is available only when any from DM14 to DM18 is supported.
 *  \trace      DSGN-J1939DcmDiag2097
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_MemHandlerTransmit(
  uint8 diagMessage,
  CONSTP2VAR(Std_ReturnType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pTxResult
  );
#endif

#if (J1939DCM_NEED_MEM_ACCESS == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_MemHandlerHandleTransmissionFailure()
 **********************************************************************************************************************/
/*! \brief      Handles memory message trasmission failure.
 *  \details    -
 *  \param[in]  diagMessage Diagnostic message
 *  \param[in]  txResult    Tx result
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     This function is available only when any from DM14 to DM18 is supported.
 *  \trace      DSGN-J1939DcmDiag2097
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_MemHandlerHandleTransmissionFailure(
  uint8 diagMessage,
  Std_ReturnType txResult
  );
#endif

/**********************************************************************************************************************
 * J1939Dcm_NetCalculateResponseAddress()
 **********************************************************************************************************************/
/*! \brief        Calculates response address.
 *  \details      -
 *  \param[in]    sourceAddress     Address of the node that sent the Requested DM
 *  \param[in]    destAddress       Address of this node or 0xFF for broadcast
 *  \return       lResponseAddress  Response address.
 *  \context      ISR1|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        DSGN-J1939Dcm20773
 *  \pre          -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(uint8, J1939DCM_CODE)
J1939Dcm_NetCalculateResponseAddress(
  uint8 sourceAddress,
  uint8 destAddress
  );

#if (J1939DCM_DM1_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1Receive()
 **********************************************************************************************************************/
/*! \brief          Receives DM1.
 *  \details        -
 *  \param[in,out]  pNodeContext     Pointer to node context.
 *  \param[in]      channelHdl       Internal channel handle
 *  \param[in]      requestedPgn     PGN of the requested DM
 *  \param[in]      responseAddress  Address of the node to respond to or 0xFF for broadcast
 *  \param[in]      priority         Priority of the Request PG
 *  \context        ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          DSGN-J1939DcmDiag1952
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Receive(
  J1939Dcm_NodeContextPtrType pNodeContext,
  J1939Dcm_ChannelHdlType channelHdl,
  uint32 requestedPgn,
  uint8 responseAddress,
  uint8 priority
  );
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR)
/**********************************************************************************************************************
 * J1939Dcm_DMxReceive()
 **********************************************************************************************************************/
/*! \brief          Receives DMx.
 *  \details        -
 *  \param[in,out]  pNodeContext     Pointer to node context.
 *  \param[in]      channelHdl       Internal channel handle
 *  \param[in]      requestedPgn     PGN of the requested DM
 *  \param[in]      responseAddress  Address of the node to respond to or 0xFF for broadcast
 *  \param[in]      priority         Priority of the Request PG
 *  \context        ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          DSGN-J1939DcmDiag2027
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxReceive(
  J1939Dcm_NodeContextPtrType pNodeContext,
  J1939Dcm_ChannelHdlType channelHdl,
  uint32 requestedPgn,
  uint8 responseAddress,
  uint8 priority
  );
#endif

#if (J1939DCM_DM35_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM35Receive()
 **********************************************************************************************************************/
/*! \brief          Receives DM35.
 *  \details        -
 *  \param[in,out]  pDM35Queue  Pointer to DM35 queue.
 *  \param[in]      channelHdl  Internal channel handle
 *  \context        ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          DSGN-J1939DcmDiag1950
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35Receive(
  J1939Dcm_DM35QueuePtrType pDM35Queue,
  J1939Dcm_ChannelHdlType channelHdl
  );
#endif

#if (J1939DCM_NEED_DEM == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_NetHandleRmInterrupt()
 **********************************************************************************************************************/
/*! \brief          Handles request manager interrupt.
 *  \details        -
 *  \param[in,out]  pNodeContext     Pointer to node context.
 *  \param[in]      channelHdl       Internal channel handle
 *  \param[in]      requestedPgn     PGN of the requested DM
 *  \param[in]      responseAddress  Address of the node to respond to or 0xFF for broadcast
 *  \param[in]      priority         Priority of the Request PG
 *  \context        ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          DSGN-J1939Dcm20833
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_NetHandleRmInterrupt(
  J1939Dcm_NodeContextPtrType pNodeContext,
  J1939Dcm_ChannelHdlType channelHdl,
  uint32 requestedPgn,
  uint8 responseAddress,
  uint8 priority
  );
#endif

/**********************************************************************************************************************
 * J1939Dcm_NetHandleRmErroneousInterrupt()
 **********************************************************************************************************************/
/*! \brief        Handles reuest manager erroneous interrupt.
 *  \details      -
 *  \param[in]    nodeHdl          Internal node handle
 *  \param[in]    channelHdl       Internal channel handle
 *  \param[in]    requestedPgn     PGN of the requested DM
 *  \param[in]    responseAddress  Address of the node to respond to or 0xFF for broadcast
 *  \param[in]    priority         Priority of the Request PG
 *  \context      ISR1|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        DSGN-J1939Dcm20833
 *  \pre          -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_NetHandleRmErroneousInterrupt(
  J1939Dcm_NodeHdlType nodeHdl,
  J1939Dcm_ChannelHdlType channelHdl,
  uint32 requestedPgn,
  uint8 responseAddress,
  uint8 priority
  );

#if (J1939DCM_DM13_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM13Receive()
 **********************************************************************************************************************/
/*! \brief       Receives DM13.
 *  \details     -
 *  \param[in]   currentNetwork          Network on which request has been received
 *  \param[in]   PduInfoPtr->SduLength   Length of the received I-PDU
 *               PduInfoPtr->SduDataPtr  Pointer to buffer containing the I-PDU
 *  \context     ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       DSGN-J1939Dcm20833
 *  \pre         -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM13Receive(
  J1939Dcm_NetworkType currentNetwork,
  P2CONST(PduInfoType, AUTOMATIC, J1939DCM_APPL_DATA) PduInfoPtr
  );
#endif

#if (J1939DCM_DM14_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM14Receive()
 **********************************************************************************************************************/
/*! \brief        Receives DM14.
 *  \details      -
 *  \param[in]    currentChannelId        Id of Channel on which request has been received
 *  \param[in]    PduInfoPtr->SduLength   Length of the received I-PDU
 *                PduInfoPtr->SduDataPtr  Pointer to buffer containing the I-PDU
 *  \param[in]    sourceAddress           Source address
 *  \param[in]    destinationAddress      Destination address
 *  \param[in]    payloadLength           Paylaod length
 *  \context      ISR1|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        DSGN-J1939Dcm20833, DSGN-J1939DcmDiag2094
 *  \pre          -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM14Receive(
  NetworkHandleType currentChannelId,
  P2CONST(PduInfoType, AUTOMATIC, J1939DCM_APPL_DATA) PduInfoPtr,
  uint8 sourceAddress,
  uint8 destinationAddress,
  PduLengthType payloadLength
  );
#endif

#if (J1939DCM_DM17_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM17Receive()
 **********************************************************************************************************************/
/*! \brief        Receives DM17.
 *  \details      -
 *  \param[in]    currentChannelId        Id of Channel on which request has been received
 *  \param[in]    PduInfoPtr->SduLength   Length of the received I-PDU
 *                PduInfoPtr->SduDataPtr  Pointer to buffer containing the I-PDU
 *  \param[in]    sourceAddress           Source address
 *  \param[in]    destinationAddress      Destination address
 *  \param[in]    payloadLength           Paylaod length
 *  \context      ISR1|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        DSGN-J1939Dcm20833, DSGN-J1939DcmDiag2095
 *  \pre          -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM17Receive(
  NetworkHandleType currentChannelId,
  P2CONST(PduInfoType, AUTOMATIC, J1939DCM_APPL_DATA) PduInfoPtr,
  uint8 sourceAddress,
  uint8 destinationAddress,
  PduLengthType payloadLength
  );
#endif

#if (J1939DCM_NEED_IF_RECEPTION == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_NetIsNodeOnline()
 **********************************************************************************************************************/
/*! \brief        Finds out whether a node is online.
 *  \details      In case of broadcast address find out if any node is online
 *  \param[in]    currentChannel      Channel on which request has been received
 *  \param[in]    destinationAddress  Destination address
 *  \context      ISR1|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        DSGN-J1939Dcm20822
 *  \pre          -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(boolean, J1939DCM_CODE)
J1939Dcm_NetIsNodeOnline(
  J1939Dcm_ChannelHdlType currentChannel,
  uint8 destinationAddress
  );
#endif

#if (((J1939DCM_NEED_IF_RECEPTION  == STD_ON) || \
    (J1939DCM_NEED_TP_RECEPTION == STD_ON)) && \
    (J1939DCM_DEV_ERROR_DETECT == STD_ON))                                                                                                           /* COV_J1939DCM_REQUIRED_BY_SAFEBSW */
/**********************************************************************************************************************
 * J1939Dcm_NetIsRxPduIdValid()
 **********************************************************************************************************************/
/*! \brief        Validates Rx Pdu Id.
 *  \details      -
 *  \param[in]    id     ID of the received I-PDU
 *  \return       TRUE   If Rx Pdu Id is valid
 *  \return       FALSE  If Rx Pdu Id is invalid
 *  \context      ISR1|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \traces       DSGN-J1939Dcm20822, DSGN-J1939DcmDiag1994, DSGN-J1939DcmDiag1990, DSGN-J1939DcmDiag1995
 *  \pre          -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(boolean, J1939DCM_CODE)
J1939Dcm_NetIsRxPduIdValid(
  PduIdType id
  );
#endif

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_NetIsTxPduIdValid()
 **********************************************************************************************************************/
/*! \brief        Validates Tx Pdu Id.
 *  \details      -
 *  \param[in]    id     ID of the received I-PDU
 *  \return       TRUE   If Tx Pdu Id is valid
 *  \return       FALSE  If Tx Pdu Id is invalid
 *  \context      ISR1|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        DSGN-J1939Dcm20840, DSGN-J1939Dcm20839, DSGN-J1939Dcm20838
 *  \pre          -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(boolean, J1939DCM_CODE)
J1939Dcm_NetIsTxPduIdValid(
  PduIdType id
  );
#endif

/**********************************************************************************************************************
 * J1939Dcm_NetIsValidOnlineNodeChannel()
 **********************************************************************************************************************/
/*! \brief        Validates node channel combination.
 *  \details      -
 *  \param[in]    apiId       The API identifier for DET reporting
 *  \param[in]    nodeHdl     Internal node handle
 *  \Param[in]    channelHdl  Internal channel handle
 *  \return       TRUE        All parameters are valid
 *  \return       FALSE       At least one parameter is invalid
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        DSGN-J1939Dcm20848
 *  \pre          -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(boolean, J1939DCM_CODE)
J1939Dcm_NetIsValidOnlineNodeChannel(
  uint8 apiId,
  J1939Dcm_NodeHdlType nodeHdl,
  J1939Dcm_ChannelHdlType channelHdl
  );

/**********************************************************************************************************************
 * J1939Dcm_UtiBufferContextInit()
 **********************************************************************************************************************/
/*! \brief          Initializes the buffer context.
 *  \details        -
 *  \param[in]      pBufferContext Buffer context to be initialized
 *  \param[in]      pBuffer        Pointer to message buffer
 *  \param[in]      sduLength      Actual used buffer length
 *  \param[in]      bufferLength   Available buffer length
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_UtiBufferContextInit(
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBuffer,
  PduLengthType sduLength,
  PduLengthType bufferLength
  );

/*! Common functions */
/**********************************************************************************************************************
 * J1939Dcm_Reset()
 **********************************************************************************************************************/
/*! \brief      Resets internal states of J1939 DCM.
 *  \details    Sets communication state of all node-channel pairs to offline, frees DEM resources,
 *              resets all the handlers.
 *  \context    ISR1|ISR2
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939Dcm20848
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_Reset(
  void
  );

#if (J1939DCM_NEED_DEM == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DtcHandlerDemSemaphoreLock()
 **********************************************************************************************************************/
/*! \brief       Locks DEM semaphore
 *  \details     Checks the availability of the DEM resources before it locks the semaphore.
 *  \param[out]  pUserSemaphore  Result of the locking process
 *  \context     TASK
 *  \reentrant   FALSE
 *  \trace       DSGN-J1939Dcm21783, DSGN-J1939DcmDiag2056
 *  \pre         -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerDemSemaphoreLock(
  P2VAR(boolean, AUTOMATIC, J1939DCM_VAR_NOINIT) pUserSemaphore
  );
#endif

#if (J1939DCM_NEED_DEM == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DtcHandlerDemSemaphoreRelease()
 **********************************************************************************************************************/
/*! \brief       Unlocks DEM semaphore
 *  \details     Checks first that DEM resources are locked by the handler that releases the semaphore before it
 *               unlocks the resources.
 *  \param[out]  pUserSemaphore  Result of the locking process
 *  \context     TASK
 *  \reentrant   FALSE
 *  \trace       DSGN-J1939Dcm21783, DSGN-J1939DcmDiag2056
 *  \pre         -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerDemSemaphoreRelease(
  P2VAR(boolean, AUTOMATIC, J1939DCM_VAR_NOINIT) pUserSemaphore
  );
#endif

/**********************************************************************************************************************
 * J1939Dcm_NetGetNodeHdlById()
 **********************************************************************************************************************/
/*! \brief      Returns an index to access a node configuration for a give NM node Id.
 *  \details    Determines whether the NM node has a valid J1939Dcm handle.
 *  \param[in]  node                       Id defined by NM
 *  \return     nodeHd                     If the node handle is valid
 *  \return     J1939DCM_INVALID_NODE_HDL  If the node handle is invalid
 *  \context    ISR1|ISR2
 *  \reentrant  TRUE
 *  \trace      DSGN-J1939Dcm20737
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(J1939Dcm_NodeHdlType, J1939DCM_CODE)
J1939Dcm_NetGetNodeHdlById(
  uint8_least node
  );

#if ((J1939DCM_DM15_SUPPORT == STD_ON) || \
    (J1939DCM_NEED_TP_RECEPTION == STD_ON) || \
    (J1939DCM_NEED_IF_RECEPTION == STD_ON))
/**********************************************************************************************************************
 * J1939Dcm_NetGetNodeHdlByAddr()
 **********************************************************************************************************************/
/*! \brief      Returns an index to access a node configuration for a give node address.
 *  \details    Determines whether the node address has a valid J1939Dcm handle.
 *  \param[in]  nodeAddress                Node address
 *  \return     nodeHd                     If the node handle is valid
 *  \return     J1939DCM_INVALID_NODE_HDL  If the node handle is invalid
 *  \context    ISR1|ISR2
 *  \reentrant  TRUE
 *  \trace      DSGN-J1939Dcm20737
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(J1939Dcm_NodeHdlType, J1939DCM_CODE)
J1939Dcm_NetGetNodeHdlByAddr(
  uint8_least nodeAddress
  );
#endif

/**********************************************************************************************************************
 * J1939Dcm_NetGetChannelHdlById()
 **********************************************************************************************************************/
/*! \brief      Returns an index to access a channel configuration for a give ComM channel Id.
 *  \details    Determines whether the ComM channel has a valid J1939Dcm handle.
 *  \param[in]  channel                       Id defined by ComM
 *  \return     channelHd                     If the channel handle is valid
 *  \return     J1939DCM_INVALID_CHANNEL_HDL  If the channel handle is invalid
 *  \context    ISR1|ISR2
 *  \reentrant  TRUE
 *  \trace      DSGN-J1939Dcm20737
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(J1939Dcm_ChannelHdlType, J1939DCM_CODE)
J1939Dcm_NetGetChannelHdlById(
  uint8_least channel
  );

#if(J1939DCM_NEED_DEM == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_UtiGetMsgHdlByPGN()
 **********************************************************************************************************************/
/*! \brief      Finds a local ID of a given DM in the message table.
 *  \details    Verifies a particular DM belongs to a particular pair of node and channel. Upon success, a valid local
 *              ID (index) in the message table for the requested DM is returned.
 *  \param[in]  requestedPgn                  Requested PGN
 *  \param[in]  nodeHdl                       Node by which the request was received
 *  \param[in]  channelHdl                    Handle of the current channel on which DM is received
 *  \param[in]  apiId                         API id
 *  \return     messageHdl                    A valid index in the message table
 *  \return     J1939DCM_INVALID_MESSAGE_HDL  Invalid handle
 *  \context    ISR1|ISR2
 *  \reentrant  TRUE
 *  \trace      DSGN-J1939Dcm20737
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(J1939Dcm_MessageHdlType, J1939DCM_CODE)
J1939Dcm_UtiGetMsgHdlByPGN(
  uint32 requestedPgn,
  J1939Dcm_NodeHdlType nodeHdl,
  J1939Dcm_ChannelHdlType channelHdl,
  uint8 apiId
  );
#endif

#if(J1939DCM_NEED_DEM == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_UtiGetDiagMsgByPGN()
 **********************************************************************************************************************/
/*! \brief      Finds a Diagnostic messge based on a request PGN.
 *  \details    -
 *  \param[in]  requestedPgn       Requested PGN
 *  \param[in]  nodeHdl            Node by which the request was received
 *  \param[in]  channelHdl         Handle of the current channel on which DM is received
 *  \param[in]  apiId              API Id
 *  \return     diagMsg            diagnostic message
 *  \return     J1939DCM_DM_UNDEF  Invalid diagnostic message
 *  \context    ISR1|ISR2
 *  \reentrant  TRUE
 *  \trace      DSGN-J1939Dcm20737
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(uint8, J1939DCM_CODE)
J1939Dcm_UtiGetDiagMsgByPGN(
  uint32 requestedPgn,
  J1939Dcm_NodeHdlType nodeHdl,
  J1939Dcm_ChannelHdlType channelHdl,
  uint8 apiId
  );
#endif

/**********************************************************************************************************************
 * J1939Dcm_UtiGetPeerTxPduContextByDM()
 **********************************************************************************************************************/
/*! \brief      Gets the corresponding peer TxPdu context, which contains the Pdu Id and the meta data length of a 
 *              given node, channel and DM.
 *  \details    Determines the validity of the requested TxPdu Id.
 *  \param[in]  nodeHdl                  Internal Node Handle
 *  \param[in]  channelHdl               Internal Channel Handle
 *  \param[in]  diagMessage              DM for which the PduId shall be retrieved
 *  \return     Peer TxPdu context       In case of invalid TxPdu Id, the PduId of the context contains 
 *                                       J1939DCM_INVALID_PDU_ID
 *  \context    ANY
 *  \reentrant  TRUE
 *  \trace      DSGN-J1939Dcm20737
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(J1939Dcm_TxPduContextType, J1939DCM_CODE)
J1939Dcm_UtiGetPeerTxPduContextByDM(
  J1939Dcm_NodeHdlType nodeHdl,
  J1939Dcm_ChannelHdlType channelHdl,
  uint8_least diagMessage
  );

#if (J1939DCM_NEED_TP_RECEPTION == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_NetRxHandlerReset()
 **********************************************************************************************************************/
/*! \brief      Resets handler when reception is complete or aborted.
 *  \details    Resets handler state.
 *  \context    ISR1|ISR2
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939Dcm20848
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_NetRxHandlerReset(
  void
  );
#else
# define J1939Dcm_NetRxHandlerReset()
#endif


/*! Message processors */
#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1Init()
 **********************************************************************************************************************/
/*! \brief      Resets DM1 structures
 *  \details    Initializes DM1 state and queue of events. Obtains DM1 Tx Pdu for each channel.
 *  \context    ISR1|ISR2
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939Dcm20848
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Init(
  void
  );

/**********************************************************************************************************************
 * J1939Dcm_DM1Task()
 **********************************************************************************************************************/
/*! \brief      Executes the task elements of DM1.
 *  \details    Prepares for DM1 processing and triggers DM1 processor.
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     This function is available only if DM1 is supported.
 *  \trace      DSGN-J1939DcmDiag2009
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Task(
  void
  );

/**********************************************************************************************************************
 * J1939Dcm_DM1Processor()
 **********************************************************************************************************************/
/*! \brief          Processes DM1 message.
 *  \details        Prepares for a DM1 response and triggers transmit for a response or an acknowledgement.
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM1 is supported
 *  \trace          DSGN-J1939DcmDiag1952
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Processor(
  J1939Dcm_NodeContextPtrType pNodeContext
  );
#else
# define J1939Dcm_DM1Init()
# define J1939Dcm_DM1Task()
#endif

#if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM13Init()
 **********************************************************************************************************************/
/*! \brief      Resets DM13 structures.
 *  \details    Activates the broadcast for all configured channels and frees resources to accept new requests.
 *  \context    ISR1|ISR2
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939Dcm20848
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM13Init(
  void
  );

/**********************************************************************************************************************
 * J1939Dcm_DM13Task()
 **********************************************************************************************************************/
/*! \brief      Executes the task elements of DM13.
 *  \details    Prepares and processes DM13.
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     This function is available only if DM13 is supported.
 *  \trace      DSGN-J1939DcmDiag2007
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM13Task(
  void
  );
#else
# define J1939Dcm_DM13Init()
# define J1939Dcm_DM13Task()
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM35Init()
 **********************************************************************************************************************/
/*! \brief      Resets DM35 structures
 *  \details    Initializes DM35 state and queue of events. Obtains DM35 Tx Pdu for each channel.
 *  \context    ISR1|ISR2
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939Dcm20848
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35Init(
  void
  );

/**********************************************************************************************************************
 * J1939Dcm_DM35Task()
 **********************************************************************************************************************/
/*! \brief      Executes the task elements of DM35.
 *  \details    Prepares for DM35 processing and triggers DM35 processor.
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     This function is available only if DM35 is supported.
 *  \trace      DSGN-J1939DcmDiag2048
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35Task(
  void
  );

/**********************************************************************************************************************
 * J1939Dcm_DM35Processor()
 **********************************************************************************************************************/
/*! \brief          Processes DM35 message.
 *  \details        Prepares for a DM35 response and triggers transmit for a response.
 *  \param[in,out]  pNodeContext  Pointer to node context
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if DM35 is supported
 *  \trace          DSGN-J1939DcmDiag1950
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35Processor(
  J1939Dcm_NodeContextPtrType pNodeContext
  );
#else
# define J1939Dcm_DM35Init()
# define J1939Dcm_DM35Task()
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxInit()
 **********************************************************************************************************************/
/*! \brief      Resets DMx structures
 *  \details    Initializes DMx state and queue of events.
 *  \context    ISR1|ISR2
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939Dcm20848
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxInit(
  void
  );

/**********************************************************************************************************************
 * J1939Dcm_DMxTask()
 **********************************************************************************************************************/
/*! \brief      Executes task elements for a generic DM.
 *  \details    Prepares for a generic DM processing and triggers DMx processor.
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     This function is available only if at least one of the diagnostic messages DM2-DM5, DM11, DM24, DM25,
 *              DM27, DM31, and DM53-DM55, is supported.
 *  \trace      DSGN-J1939DcmDiag2041
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxTask(
  void
  );

/**********************************************************************************************************************
 * J1939Dcm_DMxProcessor()
 **********************************************************************************************************************/
/*! \brief          Processes a generic DM message.
 *  \details        Prepares for a response to a requested DM and triggers transmit for a response or an acknowledgement.
 *  \param[in,out]  pNodeContext  Pointer to node context.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         This function is available only if at least one of the diagnostic messages DM2-DM5, DM11, DM24, DM25,
 *                  DM27, DM31, and DM53-DM55, is supported.
 *  \trace          DSGN-J1939DcmDiag2027
 *  \pre            -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxProcessor(
  J1939Dcm_NodeContextPtrType pNodeContext
  );
#else
# define J1939Dcm_DMxInit()
# define J1939Dcm_DMxTask()
#endif

/*! Tx handler */
/**********************************************************************************************************************
 * J1939Dcm_NetTxHandlerPrepare()
 **********************************************************************************************************************/
/*! \brief      Prepares for message transmission.
 *  \details    Decides whether to append the meta data according to the transmission path. Triggers transmission.
 *  \param[in]  pBufferContext          Pointer to message buffer context which contains the data to be copied
 *  \param[in]  diagMessage             DM to be transmitted
 *  \param[in]  nodeHdl                 Requested node
 *  \param[in]  responseAddress         Address to be added to meta data
 *  \param[in]  metaDataLength          Length of the meta data
 *  \return     E_OK                    Transmission request accepted
 *  \return     E_NOT_OK                Transmission is in progress, request not accepted
 *  \context    TASK
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939Dcm21123, DSGN-J1939Dcm21919, DSGN-J1939Dcm21920
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(Std_ReturnType, J1939DCM_CODE)
J1939Dcm_NetTxHandlerPrepare(
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  uint8_least diagMessage,
  J1939Dcm_NodeHdlType nodeHdl,
  uint8_least responseAddress,
  uint8 metaDataLength
  );

/**********************************************************************************************************************
 * J1939Dcm_NetTxHandlerTransmit()
 **********************************************************************************************************************/
/*! \brief      Prepares for message transmission.
 *  \details    Triggers the PduR transmit function. Checks whether the transmission has been confirmed.
 *  \param[in]  TxPduId     PduId
 *  \param[in]  channelHdl  Channel on which transmission shall start
 *  \return     E_OK        Transmission request accepted
 *  \return     E_NOT_OK    Transmission failed
 *  \context    TASK
 *  \reentrant  FALSE
 *  \trance     DSGN-J1939Dcm21123
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(Std_ReturnType, J1939DCM_CODE)
J1939Dcm_NetTxHandlerTransmit(
  PduIdType TxPduId,
  J1939Dcm_ChannelHdlType channelHdl
  );

/**********************************************************************************************************************
 * J1939Dcm_NetTxHandlerConfirm()
 **********************************************************************************************************************/
/*! \brief      Indicates transmission success or failure.
    \details    Triggers transmission finalization or negative acknowledgement.
 *  \param[in]  nodeHdl      Node which is confirmed
 *  \param[in]  diagMessage  Message which is confirmed
 *  \param[in]  result       Transmission result
 *  \param[in]  apiId        API id
 *  \context    ANY
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939Dcm21123
 *  \pre        -
 *  \note       Is used to finalize a transmission when TpTxConfirmation, TxConfirmation or timeout occurs
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_NetTxHandlerConfirm(
  J1939Dcm_NodeHdlType nodeHdl,
  uint8_least diagMessage,
  Std_ReturnType result,
  uint8 apiId
  );

/**********************************************************************************************************************
 * J1939Dcm_ComStateReset()
 **********************************************************************************************************************/
/*! \brief      Resets communication state during initialization.
 *  \details    Resets communication state.
 *  \context    ANY
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939Dcm20848
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_ComStateReset(
  void
  );

/**********************************************************************************************************************
 * J1939Dcm_NetTxHandlerReset()
 **********************************************************************************************************************/
/*! \brief      Resets handler when transmission is complete or aborted.
 *  \details    Resets handler state.
 *  \context    ANY
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939Dcm20848
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_NetTxHandlerReset(
  void
  );

/**********************************************************************************************************************
 * J1939Dcm_NetTxHandlerTask
 **********************************************************************************************************************/
/*! \brief      Supervises transmission connections
 *  \details    Indicates failed transmission if no confirmation was received within the transmission timeout.
 *  \context    TASK
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939DcmDiag1970
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_NetTxHandlerTask(
  void
  );

/*! Memory handler */
#if (J1939DCM_NEED_MEM_ACCESS == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_MemHandlerReset()
 **********************************************************************************************************************/
/*! \brief      Resets handler when transmission is complete or aborted.
 *  \details    Resets handler state.
 *  \context    ANY
 *  \reentrant  FALSE
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_MemHandlerReset(
  void
  );

/**********************************************************************************************************************
 * J1939Dcm_MemHandlerTask()
 **********************************************************************************************************************/
/*! \brief      Executes the task elements of a memory message transmission.
 *  \details    Transmits and retries transmission of memory message.
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     This function is available only when any from DM14 to DM18 is supported.
 *  \trace      DSGN-J1939DcmDiag2064
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_MemHandlerTask(
  void
  );
#else
# define J1939Dcm_MemHandlerReset()
# define J1939Dcm_MemHandlerTask()
#endif

/*! DTC handler */
#if (J1939DCM_NEED_DTC_HANDLER_SPN == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DtcHandlerSetDtcFilter()
 **********************************************************************************************************************/
/*! \brief       Handles DTC diagnostic message.
 *  \details     Prepares read sequence, sets DTC filter, and gets lamp status.
 *  \param[out]  pDMProcessorState  Pointer to state of DM processor
 *  \param[in]   pBufferContext     Pointer to DM message buffer context
 *  \param[in]   pFilterHandler     Pointer to filtering criteria and requested node.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \trace       DSGN-J1939DcmDiag2019
 *  \pre         -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerSetDtcFilter(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState,
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  P2CONST(J1939Dcm_FilterHandlerType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pFilterHandler
  );

/**********************************************************************************************************************
 * J1939Dcm_DtcHandlerGetDTCs()
 **********************************************************************************************************************/
/*! \brief       Gets DTCs and adds them to the message buffer.
 *  \details     Makes sure that the filtered DTCs are added to the message buffer even if more than one main function
 *               call are required.
 *  \param[out]  pDMProcessorState  Pointer to state of DM processor
 *  \param[in]   maxNumDtcs         Number of DTCs after which the message shall be transmitted
 *  \param[in]   nodeHdl            The requested node
 *  \context     TASK
 *  \reentrant   FALSE
 *  \trace       DSGN-J1939DcmDiag2019
 *  \pre         -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerGetDTCs(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState,
  uint16_least maxNumDtcs,
  J1939Dcm_NodeHdlType nodeHdl
  );
#endif

#if (J1939DCM_NEED_DTC_HANDLER_LAMP == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DtcHandlerSetLampFilter()
 **********************************************************************************************************************/
/*! \brief      Handles lamp status diagnostic message.
 *  \details    Initiate read sequence from DEM.
 *  \param[in]  pBufferContext    Pointer to DM message buffer context
 *  \param[in]  nodeHdl           The requested node
 *  \context    TASK
 *  \reentrant  FALSE
 *  \trace      DSGN-J1939DcmDiag2045
 *  \pre        -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerSetLampFilter(
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  J1939Dcm_NodeHdlType nodeHdl
  );

/**********************************************************************************************************************
 * J1939Dcm_DtcHandlerGetLampDTCs()
 **********************************************************************************************************************/
/*! \brief       Gets DTCs with lamp status and adds them to the message buffer.
 *  \details     Makes sure that the filtered DTCs with the associated lamp status are added to the message buffer
 *               even if more than one main function call are required.
 *  \param[out]  pDMProcessorState  Pointer to state of DM processor
 *  \param[in]   nodeHdl            The requested node
 *  \context     TASK
 *  \reentrant   FALSE
 *  \trace       DSGN-J1939DcmDiag2045
 *  \pre         -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerGetLampDTCs(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState,
  J1939Dcm_NodeHdlType nodeHdl
  );
#endif

#if (J1939DCM_NEED_DTC_HANDLER_FF == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DtcHandlerSetFFFilter()
 **********************************************************************************************************************/
/*! \brief       Handles freeze frame diagnostic messages.
 *  \details     Prepares read sequence and sets freeze frame filter.
 *  \param[out]  pDMProcessorState  Pointer to state of DM processor
 *  \param[in]   pBufferContext     Pointer to DM message buffer context
 *  \param[in]   freezeFrameKind    Freeze frame kind parameter for DEM
 *  \param[in]   nodeHdl            Node for which the filter need to be set
 *  \context     TASK
 *  \reentrant   FALSE
 *  \trace       DSGN-J1939DcmDiag2061
 *  \pre         -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerSetFFFilter(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState,
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  Dem_J1939DcmSetFreezeFrameFilterType freezeFrameKind,
  J1939Dcm_NodeHdlType nodeHdl
  );

# if (J1939DCM_DM24_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DtcHandlerGetSupportedSPNs()
 **********************************************************************************************************************/
/*! \brief       Constructs DM24.
 *  \details     Gets the list of supported SPNs of a specific node and calcualte the length of the DM24.
 *  \param[out]  pBufferContext Pointer to DM message buffer context
 *  \param[in]   nodeHdl        The requested node
 *  \context     TASK
 *  \reentrant   FALSE
 *  \trace       DSGN-J1939Dcm21806
 *  \pre         -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerGetSupportedSPNs(
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  J1939Dcm_NodeHdlType nodeHdl
  );
# endif

/**********************************************************************************************************************
 * J1939Dcm_DtcHandlerGetFFs()
 **********************************************************************************************************************/
/*! \brief       Handles freeze frames diagnostic messages.
 *  \details     Gets a Freeze Frame of a DTC and adds it to the message buffer.
 *  \param[out]  pDMProcessorState  Pointer to state of DM processor
 *  \param[in]   nodeHdl            Node for which the filter need to be set
 *  \context     TASK
 *  \reentrant   FALSE
 *  \trace       DSGN-J1939DcmDiag2061
 *  \pre         -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerGetFFs(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState,
  J1939Dcm_NodeHdlType nodeHdl
  );
#endif

#if (J1939DCM_NEED_DTC_HANDLER_OBD == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DtcHandlerGetReadiness()
 **********************************************************************************************************************/
/*! \brief       Handles Readiness diagnostic message.
 *  \details     Collects Readniness data and Copies the data to the diagnositc message buffer.
 *  \param[out]  pDMProcessorState  Pointer to state of DM processor
 *  \param[in]   diagMessage        Incomming Readiness DM (DM5, DM21, or DM26)
 *  \param[in]   nodeHdl            Requested Node handle.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \trace       DSGN-J1939Dcm21887
 *  \pre         -
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerGetReadiness(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState,
  uint8 diagMessage,
  J1939Dcm_NodeHdlType nodeHdl
  );
#endif

/*! Clear handler */
#if (J1939DCM_NEED_CLEAR_HANDLER == STD_ON)

/**********************************************************************************************************************
 * J1939Dcm_DMxClearHandler()
 **********************************************************************************************************************/
/*! \brief       Forwards clear requests to DEM.
 *  \details     Updates processing state and sets acknowledgement code based on the result of clearing DTC.
 *  \param[out]  pDMProcessorState     pointer to state of DM processor
 *  \return      J1939RM_ACK_POSITIVE  DEM accepted the clear request or the clear is pending.
 *  \return      J1939RM_ACK_NEGATIVE  DEM did not accept the clear request.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \config      If supported any DM that needs the clear handler.
 *  \trace       DSGN-J1939DcmDiag2037
 *  \pre         Lock for DEM resources is obtained.
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(J1939Rm_AckCode, J1939DCM_CODE)
J1939Dcm_DMxClearHandler(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState
  );
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

#if (J1939DCM_NEED_DTC_HANDLER == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DtcHandlerStateInit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
*********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerStateInit(
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState,
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext
  )
{
  pDtcHandlerState->MessageData                   = pBufferContext;
  pDtcHandlerState->MessageData->Buffer.SduLength = 0;                                                                                               /* VCA_J1939DCM_FALSE_POSITIVE */
  pDtcHandlerState->NumDTCsInCycle                = 0;
  pDtcHandlerState->NumDTCs                       = 0;
}
#endif

#if (J1939DCM_NEED_DTC_HANDLER == STD_ON)
/**********************************************************************************************************************
 *  J1939Dcm_DtcHandlerProvideResDataAsU8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
  J1939Dcm_DtcHandlerProvideResDataAsU8(
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState,                                                                                                       /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  uint8 value
  )
{
  J1939Dcm_UtiProvideDataAsU8(pDtcHandlerState->MessageData, value);
}
#endif

#if (J1939DCM_NEED_DTC_HANDLER_FF == STD_ON)
/**********************************************************************************************************************
 *  J1939Dcm_DtcHandlerCommitResData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
*********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
  J1939Dcm_DtcHandlerCommitResData(
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState,                                                                                                       /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  PduLengthType nbrBytes
  )
{
# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  if((pDtcHandlerState->MessageData->Buffer.SduLength + nbrBytes) > pDtcHandlerState->MessageData->AvailLen)
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_MAINFUNCTION,
      J1939DCM_E_PARAM_CONFIG
      )
  }
  else
# endif
  {
    pDtcHandlerState->MessageData->Buffer.SduLength += nbrBytes;                                                                                     /* VCA_J1939DCM_WRITE_DTC_HANDLER_STATE */
  }
}
#endif

#if ((J1939DCM_NEED_DTC_HANDLER_SPN  == STD_ON) || \
    (J1939DCM_NEED_DTC_HANDLER_FF   == STD_ON) || \
    (J1939DCM_NEED_DTC_HANDLER_LAMP == STD_ON))
/**********************************************************************************************************************
 *  J1939Dcm_DtcHandlerProvideResDataAsU24()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerProvideResDataAsU24(
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState,                                                                                                       /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  uint32 value
  )
{
  J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, J1939Dcm_UtiGetHiLoByte(value));
  J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, J1939Dcm_UtiGetLoHiByte(value));
  J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, J1939Dcm_UtiGetLoLoByte(value));
}
#endif

 /***********************************************************************************************************************
 * J1939Dcm_NetGetNodeHdlById()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(J1939Dcm_NodeHdlType, J1939DCM_CODE)
J1939Dcm_NetGetNodeHdlById(
  uint8_least node
  )
{
  J1939Dcm_NodeHdlType    lResult;
  J1939Dcm_NodeHdlOptType lNodeHdl;

  lResult = J1939DCM_INVALID_NODE_HDL;

  for (lNodeHdl = 0u; lNodeHdl < J1939Dcm_GetSizeOfCfg_NodeTable(); ++lNodeHdl)
  {
    if(node == J1939Dcm_Cfg_GetNodeId(lNodeHdl))
    {
      lResult = (J1939Dcm_NodeHdlType)lNodeHdl;
      break;
    }
  }

  return lResult;
}

#if ((J1939DCM_DM15_SUPPORT == STD_ON) || \
    (J1939DCM_NEED_TP_RECEPTION == STD_ON) || \
    (J1939DCM_NEED_IF_RECEPTION == STD_ON))
 /***********************************************************************************************************************
 * J1939Dcm_NetGetNodeHdlByAddr()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(J1939Dcm_NodeHdlType, J1939DCM_CODE)
J1939Dcm_NetGetNodeHdlByAddr(
  uint8_least nodeAddress
  )
{
  J1939Dcm_NodeHdlType    lResult;
  J1939Dcm_NodeHdlOptType lNodeHdl;

  lResult = J1939DCM_INVALID_NODE_HDL;

  for (lNodeHdl = 0u; lNodeHdl < J1939Dcm_GetSizeOfCfg_NodeTable(); ++lNodeHdl)
  {
    if (nodeAddress == J1939Dcm_Cfg_GetNodeAddress(lNodeHdl))
    {
      lResult = (J1939Dcm_NodeHdlType)lNodeHdl;
      break;
    }
  }

  return lResult;
}
#endif

/***********************************************************************************************************************
 * J1939Dcm_NetGetChannelHdlById()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(J1939Dcm_ChannelHdlType, J1939DCM_CODE)
J1939Dcm_NetGetChannelHdlById(
  uint8_least channel
  )
{
  J1939Dcm_ChannelHdlType    lResult;
  J1939Dcm_ChannelHdlOptType lChannelHdl;

   lResult = J1939DCM_INVALID_CHANNEL_HDL;

  for (lChannelHdl = 0u; lChannelHdl < J1939Dcm_GetSizeOfCfg_ChannelTable(); ++lChannelHdl)
  {
    if(channel == J1939Dcm_Cfg_GetChannelId(lChannelHdl))
    {
      lResult = (J1939Dcm_ChannelHdlType)lChannelHdl;
      break;
    }
  }

  return lResult;
}

#if(J1939DCM_NEED_DEM == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_UtiGetMsgHdlByPGN ()
 **********************************************************************************************************************/
/*!
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
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(J1939Dcm_MessageHdlType, J1939DCM_CODE)
J1939Dcm_UtiGetMsgHdlByPGN(
  uint32 requestedPgn,                                                                                                                               /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_NodeHdlType nodeHdl,                                                                                                                      /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_ChannelHdlType channelHdl,                                                                                                                /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  uint8 apiId                                                                                                                                        /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  /* Start binary search routine based on the ascendingly sorted PGN number for each channel in the message table. */
  J1939Dcm_MessageHdlType lResultHdl = J1939DCM_INVALID_MESSAGE_HDL;
  uint8_least             lUpLimit;
  uint8_least             lLoLimit;
  J1939Dcm_MessageHdlType lTmpHdl;
  J1939Dcm_MessageHdlType lMessageHdl;

  J1939Dcm_IgnoreUnusedArgument(nodeHdl)         /* parameter not used in single node configurations */                                              /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(channelHdl)                                                                                                          /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(apiId)                                                                                                               /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /*
   * #11 Obtain the initial start and end search indices for messages that belong to a channel handle in
   *     the message table.
   */
  lLoLimit = J1939Dcm_GetCfg_MessageTableStartIdxOfCfg_ChannelTable(channelHdl);                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
  lUpLimit = J1939Dcm_GetCfg_MessageTableEndIdxOfCfg_ChannelTable(channelHdl);                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */

  /* #12 Set an initial position for the message handle in the middle of a range specified by the initial start
   *     and end search indices.
   */
  lMessageHdl = (J1939Dcm_MessageHdlType)(lLoLimit + (uint8_least)((uint8_least)(lUpLimit - lLoLimit) >> 1));                                        /* PRQA S 2985 */ /* MD_J1939Dcm_Rule2.2_2985 */

  /* #13 Iterate over the DMs. */
  do
  {
    /* #14 Update the iterator with the previously calculated message handle. */
    lTmpHdl = lMessageHdl;

    /* #16 If the looked-up-for PGN in the message table is equal to the requested PGN: */
    if (J1939Dcm_Cfg_GetMessagePGN(lMessageHdl) == requestedPgn)                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
    {
      /* #18 If the DM is not configured in the requested node: */
      if (J1939Dcm_Cfg_GetPeerTxPdu(nodeHdl, lMessageHdl) == J1939DCM_INVALID_PDU_ID)                                                                /* VCA_J1939DCM_FALSE_POSITIVE */
      {
        /* #19 It is already indicated that the message is not found. */
      }
      else
      /* #20 Otherwise (if the DM is configured in the requested node or a single node is configured): */
      {
        /* #21 Indicates that the message is found. */
        lResultHdl = lMessageHdl;
      }
      break;
    }
    /* #22 If the looked-up-for PGN in the message table is greater than the requested PGN: */
    else if (J1939Dcm_Cfg_GetMessagePGN(lMessageHdl) > requestedPgn)                                                                                 /* VCA_J1939DCM_FALSE_POSITIVE */
    {
      /* Message exists in the lower half of the binary search domain. */
      /* #23 Update the end search index with the previously calculated message handle. */
      lUpLimit = lMessageHdl;
    }
    /* #24 If the looked-up-for PGN in the message table is smaller than the requested PGN: */
    else
    {
      /* Message exists in the upper half of the binary search domain. */
      /* #25 Update the start search index with the previously calculated message handle. */
      lLoLimit = lMessageHdl;
    }
    /* #26 Update the message handle to be in the middle of the newly calculated binary search domain. */
    lMessageHdl = (J1939Dcm_MessageHdlType)(lLoLimit + (uint8_least)((uint8_least)(lUpLimit - lLoLimit) >> 1));
  } while (lMessageHdl != lTmpHdl); /* #27 Terminate iteration when the start and end search indices coincide. */                                    /* COV_J1939DCM_ONLY_ONE_DM_CONFIGURED */

  return lResultHdl;
}                                                                                                                                                    /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if(J1939DCM_NEED_DEM == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_UtiGetDiagMsgByPGN()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(uint8, J1939DCM_CODE)
J1939Dcm_UtiGetDiagMsgByPGN(
  uint32 requestedPgn,                                                                                                                               /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_NodeHdlType nodeHdl,                                                                                                                      /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_ChannelHdlType channelHdl,                                                                                                                /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  uint8 apiId
  )
{
  J1939Dcm_MessageHdlType lMessageHdl;
  uint8                   lDiagMessage;

  /* #18 Calculate the local ID of the requested diagnostic message. */
  lMessageHdl = J1939Dcm_UtiGetMsgHdlByPGN(
                  requestedPgn,
                  nodeHdl,
                  channelHdl,
                  apiId
                  );

  /* #19 If the local ID of the requested DM is valid: */
  if (lMessageHdl < J1939Dcm_Cfg_GetMessageTableSize())
  {
    /* #20 Calculate the corresponding message handle. */
    lDiagMessage = J1939Dcm_Cfg_GetMessageDM(lMessageHdl);
  }
  /* #21 Otherwise (if a no valid local ID for the requested DM was found): */
  else
  {
    /* #22 Set the message handle to undefined. */
    lDiagMessage = J1939DCM_DM_UNDEF;
    /* No need for assertion here. Invalid PGN is assert in a later time point. */
  }
  return lDiagMessage;
}
#endif

/***********************************************************************************************************************
 * J1939Dcm_UtiGetPeerTxPduContextByDM()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(J1939Dcm_TxPduContextType, J1939DCM_CODE)
J1939Dcm_UtiGetPeerTxPduContextByDM(
  J1939Dcm_NodeHdlType nodeHdl,                                                                                                                      /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_ChannelHdlType channelHdl,                                                                                                                /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  uint8_least diagMessage                                                                                                                            /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  J1939Dcm_MessageHdlOptType lMessageHdl;
  boolean                    lIsSupported;
  J1939Dcm_TxPduContextType  lTxPduContext;

  J1939Dcm_IgnoreUnusedArgument(channelHdl)                                                                                                          /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  lTxPduContext.PduId          = J1939DCM_INVALID_PDU_ID;
  lTxPduContext.MetaDataLength = 0;

  /* #10 Obtain whether the requested node references the requested channel. */
  lIsSupported = J1939Dcm_NetIsNodeChannelSupported(nodeHdl, channelHdl);                                                                            /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* VCA_J1939DCM_FALSE_POSITIVE */

  /* #11 If the requested node references the requested channel: */
  if (lIsSupported == TRUE)                                                                                                                          /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_NODE_CHANNEL_SUPPORTED */
  {
    /* #12 Find the start index of the diagnostic messages supported by the requested channel in the message table. */
    lMessageHdl = J1939Dcm_GetCfg_MessageTableStartIdxOfCfg_ChannelTable(channelHdl);
    /* #13 Iterate over the diagnostic messages supported by the requested channel in the message table. */
    do
    {
      /* #14 If the requested diagnostic message is consistent with obtained from the message table: */
      if(diagMessage == J1939Dcm_Cfg_GetMessageDM(lMessageHdl))
      {
        /* #15 obtain the local Id and the meta data length of the requested Tx Pdu. */
        lTxPduContext.PduId          = J1939Dcm_Cfg_GetPeerTxPdu(nodeHdl, lMessageHdl);                                                              /* PRQA S 2986 */ /* MD_J1939Dcm_Rule2.2_2986 */ /* VCA_J1939DCM_FALSE_POSITIVE */
        lTxPduContext.MetaDataLength = J1939Dcm_Cfg_GetPeerTxPduMetaDataLength(nodeHdl, lMessageHdl);                                                /* PRQA S 2986 */ /* MD_J1939Dcm_Rule2.2_2986 */ /* VCA_J1939DCM_FALSE_POSITIVE */
        break;
      }
      lMessageHdl++;
    } while (lMessageHdl < J1939Dcm_GetCfg_MessageTableEndIdxOfCfg_ChannelTable(channelHdl) );                                                       /* PRQA S 2993, 2996 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_MESSAGE_TABLE_START_END_IDX */
  } /* else : channel is not referenced by node at all */

  return lTxPduContext;
}                                                                                                                                                    /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM1Init()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Init(
  void
  )
{
  J1939Dcm_NodeHdlOptType    lNodeHdl;
  J1939Dcm_ChannelHdlOptType lChannelHdl;

  /* #10 Iterate over the configured nodes. */
  for (lNodeHdl = 0u; lNodeHdl < J1939Dcm_GetSizeOfCfg_NodeTable(); ++lNodeHdl)
  {
    J1939Dcm_NodeContextPtrType pNodeContext = &J1939Dcm_DiagContext.NodeContext[lNodeHdl];                                                          /* VCA_J1939DCM_VERIFIED_NODE_ACCESS */
    J1939Dcm_TxPduContextType   lTxPduContext;

    /* #11 initialize DM1 state. */
    pNodeContext->DM1State.ProcessingState                 = J1939DCM_MSG_STATE_IDLE;                                                                /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM1State.Timer                           = J1939DCM_DM1_TIMEOUT;                                                                   /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM1State.ChannelHdl                      = J1939DCM_INVALID_CHANNEL_HDL;                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM1State.ResponseDA                      = J1939DCM_ADDRESS_BROADCAST;                                                             /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM1State.DTCSTatusChanged                = FALSE;                                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM1State.HasDemAccess                    = FALSE;                                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM1State.IsTimerExpired                  = FALSE;                                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */

    J1939Dcm_UtiBufferContextInit(&pNodeContext->DM1State.BufferContext,
                                  &pNodeContext->DM1State.Buffer[0],
                                  0,
                                  J1939DCM_BUFFERSIZE_DM1);

    /* #12 Initialize DM1 queue of events. */
    pNodeContext->DM1Queue.RequestPending        = J1939DCM_QUEUE_EMPTY;                                                                             /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM1Queue.StateChangeRequest    = J1939DCM_STATE_OFFLINE;                                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM1Queue.ChannelHdl            = J1939DCM_INVALID_CHANNEL_HDL;                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM1Queue.ResponseDA            = J1939DCM_ADDRESS_BROADCAST;                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */

    /* #13 Obtain DM1 Tx Pdus for each channel from the configuration. */
    for (lChannelHdl = 0u; lChannelHdl < J1939Dcm_GetSizeOfCfg_ChannelTable(); ++lChannelHdl)
    {
      lTxPduContext = J1939Dcm_UtiGetPeerTxPduContextByDM(                                                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
                        (J1939Dcm_NodeHdlType)(lNodeHdl),
                        (J1939Dcm_ChannelHdlType)(lChannelHdl),
                        J1939DCM_DM1
                        );

      pNodeContext->DM1State.TxPdus[lChannelHdl] = lTxPduContext.PduId;                                                                              /* VCA_J1939DCM_VERIFIED_CHANNEL_ACCESS */
    }
  }
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM13Init()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM13Init(
  void
  )
{
  J1939Dcm_ChannelHdlOptType lChannelHdl;
  J1939Dcm_CommonContextPtrType pCommonContext = &J1939Dcm_DiagContext.CommonContext;

  /* #10 Activate the broadcast for all configured channels. */
  pCommonContext->DM13State.NumActiveBroadcastChannels = J1939Dcm_Cfg_GetChannelTableSize();
  pCommonContext->DM13State.BroadcastStatusInformation = J1939Dcm_Cfg_GetInitBroadcastStatus();  /* SWS_J1939Dcm_00129 */
  /* #11 Reset DM13 timer. */
  pCommonContext->DM13State.BroadcastDisableTimer = 0;
  /* #12 Get ready to accept new DM13 requests. */
  pCommonContext->DM13Queue.RequestPending = FALSE;

  /* #13 Clear queue for all configured channels. */
  for (lChannelHdl = 0u; lChannelHdl < J1939Dcm_GetSizeOfCfg_ChannelTable(); ++lChannelHdl)
  {
    pCommonContext->DM13Queue.BroadcastCommand[lChannelHdl] = J1939DCM_DM13_BROADCAST_DC;                                                            /* VCA_J1939DCM_VERIFIED_CHANNEL_ACCESS */
  }
}
#endif /* (J1939DCM_NEED_DM13_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM35Init()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35Init(
  void
  )
{
  J1939Dcm_NodeHdlOptType    lNodeHdl;
  J1939Dcm_ChannelHdlOptType lChannelHdl;

  /* #10 Iterate over the configured nodes. */
  for (lNodeHdl = 0u; lNodeHdl < J1939Dcm_GetSizeOfCfg_NodeTable(); ++lNodeHdl)
  {
    J1939Dcm_NodeContextPtrType pNodeContext = &J1939Dcm_DiagContext.NodeContext[lNodeHdl];                                                          /* VCA_J1939DCM_VERIFIED_NODE_ACCESS */
    J1939Dcm_TxPduContextType   lTxPduContext;

    /* #11 initialize DM35 state. */
    pNodeContext->DM35State.ProcessingState                 = J1939DCM_MSG_STATE_IDLE;                                                               /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM35State.Timer                           = J1939DCM_DM35_TIMEOUT;                                                                 /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM35State.ActiveChannels                  = 0;                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM35State.HasDemAccess                    = FALSE;                                                                                 /* VCA_J1939DCM_FALSE_POSITIVE */

    J1939Dcm_UtiBufferContextInit(&pNodeContext->DM35State.BufferContext,
                                  &pNodeContext->DM35State.Buffer[0],
                                  0,
                                  J1939DCM_BUFFERSIZE_COMMON);

    /* #12 Initialize DM35 queue of events. */
    pNodeContext->DM35Queue.RequestPending     = J1939DCM_QUEUE_EMPTY;                                                                               /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM35Queue.StateChangeRequest = J1939DCM_STATE_OFFLINE;                                                                             /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DM35Queue.RequestedChannels  = 0;                                                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */

    /* #13 Obtain DM35 Tx Pdus for each channel from the configuration. */
    for (lChannelHdl = 0u; lChannelHdl < J1939Dcm_GetSizeOfCfg_ChannelTable(); ++lChannelHdl)
    {
      lTxPduContext = J1939Dcm_UtiGetPeerTxPduContextByDM(                                                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
                        (J1939Dcm_NodeHdlType)(lNodeHdl),
                        (J1939Dcm_ChannelHdlType)(lChannelHdl),
                        J1939DCM_DM35
                        );

      pNodeContext->DM35State.TxPdus[lChannelHdl] = lTxPduContext.PduId;                                                                             /* VCA_J1939DCM_VERIFIED_CHANNEL_ACCESS */
    }
  }
}
#endif /* (J1939DCM_NEED_DM35_PROCESSOR == STD_ON) */

/**********************************************************************************************************************
 *  J1939Dcm_UtiProvideDataAsU8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_UtiProvideDataAsU8(
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  uint8 value
  )
{
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  if(pBufferContext->Buffer.SduLength >= pBufferContext->AvailLen)
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_MAINFUNCTION,
      J1939DCM_E_PARAM_CONFIG
      )
  }
  else
#endif
  {
    pBufferContext->Buffer.SduDataPtr[pBufferContext->Buffer.SduLength] = value;                                                                     /* VCA_J1939DCM_WRITE_BUFFER_CONTEXT */
    pBufferContext->Buffer.SduLength += 1u;                                                                                                          /* VCA_J1939DCM_WRITE_BUFFER_CONTEXT */
  }
}

/**********************************************************************************************************************
*  J1939Dcm_UtiProvideMetaDataAsU8()
*********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_UtiProvideMetaDataAsU8(
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  J1939Dcm_TxHandlerPtrType pTxHandler,                                                                                                              /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  uint8 metaDataLength,
  uint8 offset
)
{
  if ((offset < metaDataLength) && (offset < J1939DCM_MAX_TX_METADATA_LEN))
  {
    J1939Dcm_UtiProvideDataAsU8(pBufferContext, pTxHandler->MetaData[offset]);
  }
}

#if (J1939DCM_DM24_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  J1939Dcm_UtiMemCopySafe()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(PduLengthType, J1939DCM_CODE)
J1939Dcm_UtiMemCopySafe(
  CONSTP2CONST(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) sourcePtr,
  CONSTP2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) targetPtr,
  CONST(PduLengthType, J1939DCM_INTERNAL_DATA) targetPos,
  CONST(PduLengthType, J1939DCM_INTERNAL_DATA) targetSize,                                                                                           /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  CONST(PduLengthType, J1939DCM_INTERNAL_DATA) length
)
{
  PduLengthType lCopiedLength;

  J1939Dcm_IgnoreUnusedArgument_CONST(targetSize);                                                                                                   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /*
   * targetSize and targetPos are in not trusted relation (passed separately) so must be verified for correct relation,
   * so the subtraction can be assumed valid
   */
  if((targetSize < targetPos) || ((targetSize - targetPos) < length))
  {
    J1939Dcm_DetAssertAlways(
          J1939DCM_API_MAINFUNCTION,
          J1939DCM_E_PARAM_CONFIG
          )

    lCopiedLength = 0;
  }
  else
# endif
  {
    J1939Dcm_UtiMemCopy(sourcePtr, &(targetPtr[targetPos]), length)                                                                                  /* VCA_J1939DCM_POINTER_MEMCPY_BUFFER */

    lCopiedLength = length;
  }

  return lCopiedLength;
}
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DMxInit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxInit(
  void
  )
{
  J1939Dcm_NodeHdlOptType lNodeHdl;

  /* #10 Iterate over the configured nodes. */
  for (lNodeHdl = 0u; lNodeHdl < J1939Dcm_GetSizeOfCfg_NodeTable(); ++lNodeHdl)
  {
    J1939Dcm_NodeContextPtrType pNodeContext = &J1939Dcm_DiagContext.NodeContext[lNodeHdl];                                                          /* VCA_J1939DCM_VERIFIED_NODE_ACCESS */

    /* #11 initialize DMx state. */
    pNodeContext->DMxState.ProcessingState                 = J1939DCM_MSG_STATE_IDLE;                                                                /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DMxState.ChannelHdl                      = J1939DCM_INVALID_CHANNEL_HDL;                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DMxState.MessageHdl                      = J1939DCM_INVALID_MESSAGE_HDL;                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DMxState.ResponseDA                      = J1939DCM_ADDRESS_BROADCAST;                                                             /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DMxState.HasDemAccess                    = FALSE;                                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */

    J1939Dcm_UtiBufferContextInit(&pNodeContext->DMxState.BufferContext,
                                  &pNodeContext->DMxState.Buffer[0],
                                  0,
                                  J1939DCM_BUFFERSIZE_COMMON);

    /* #12 Initialize DMx queue of events. */
    pNodeContext->DMxQueue.RequestPending = J1939DCM_QUEUE_EMPTY;                                                                                    /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DMxQueue.ChannelHdl     = J1939DCM_INVALID_CHANNEL_HDL;                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DMxQueue.MessageHdl     = J1939DCM_INVALID_MESSAGE_HDL;                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
    pNodeContext->DMxQueue.ResponseDA     = J1939DCM_ADDRESS_BROADCAST;                                                                              /* VCA_J1939DCM_FALSE_POSITIVE */
  }
}
#endif /* (J1939DCM_NEED_DMX_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DEM == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DtcHandlerDemSemaphoreLock()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerDemSemaphoreLock(
  P2VAR(boolean, AUTOMATIC, J1939DCM_VAR_NOINIT) pUserSemaphore
  )
{
  /* #10 If DEM resources are free: */
  if (J1939Dcm_DtcHandlerDemSemaphoreGetLocked() == FALSE)
  {
    /* #11 Lock DEM resources. */
    J1939Dcm_DtcHandlerDemSemaphoreSetLocked(TRUE);
    /* #12 Inform the callee that the DEM resources are locked. */
    *pUserSemaphore = TRUE;                                                                                                                          /* VCA_J1939DCM_FALSE_POSITIVE */
  }
  /* #13 Otherwise (if DEM resources are not free): */
  else
  {
    /* #14 Inform the calle that the DEM resources are used by another handler. */
    *pUserSemaphore = FALSE;                                                                                                                         /* VCA_J1939DCM_FALSE_POSITIVE */
  }
}
#endif

#if (J1939DCM_NEED_DEM == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DtcHandlerDemSemaphoreRelease()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerDemSemaphoreRelease(
  P2VAR(boolean, AUTOMATIC, J1939DCM_VAR_NOINIT) pUserSemaphore
  )
{
  /* #10 If the DEM semaphore is in use by the handler who requires releasing the semaphore: */
  if ((J1939Dcm_DtcHandlerDemSemaphoreGetLocked() == TRUE) && (*pUserSemaphore == TRUE))
  {
    /* #11 Unlock DEM resources. */
    J1939Dcm_DtcHandlerDemSemaphoreSetLocked(FALSE);
    /* #12 Inform the callee that the DEM resources are unlocked. */
    *pUserSemaphore = FALSE;                                                                                                                         /* VCA_J1939DCM_FALSE_POSITIVE */
  }
  /* else: the semaphore is in use by another user or has already been released */
}
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueuedTxConfirmation()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueuedTxConfirmation(
  J1939Dcm_DM1QueueReadPtrType pDM1Queue,                                                                                                            /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_DM1StatePtrType pDM1State
  )
{
  J1939Dcm_IgnoreUnusedArgument_CONST(pDM1Queue)                                                                                                     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #20 If a transmission of a diagnostic message was triggered in the previous task: */
  if (pDM1State->ProcessingState == J1939DCM_MSG_STATE_TXCONF)
  {
    /* #30 Set Processing state to not busy because TxConfirmation for all transmitting channels were received. */
    pDM1State->ProcessingState = J1939DCM_MSG_STATE_WAIT;                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
  } /* else: TxConfirmation no longer awaited (e.g. because of change to offline); ignore */

  /* #40 Reset transmission because the TxHandler is still in use even if the confirmation is no longer expected. */
  J1939Dcm_NetTxHandlerReset();
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueuedFailedTxConfirmation()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueuedFailedTxConfirmation(
  J1939Dcm_DM1QueueReadPtrType pDM1Queue,                                                                                                            /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_DM1StatePtrType pDM1State
  )
{
  J1939Dcm_IgnoreUnusedArgument_CONST(pDM1Queue)                                                                                                     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #20 If a transmission of a diagnostic message was triggered in the previous task: */
  if (pDM1State->ProcessingState == J1939DCM_MSG_STATE_TXCONF)
  {
    /* #30 Set the processing state to send acknowledgement. TxConfiramtion was failed and thus NACK is required. */
    pDM1State->ProcessingState = J1939DCM_MSG_STATE_SENDACK;                                                                                         /* VCA_J1939DCM_FALSE_POSITIVE */
  } /* else: TxConfirmation no longer awaited (e.g. because of change to offline); ignore */

  /* #40 Reset transmission because the TxHandler is still in use even if the confirmation is no longer expected. */
  J1939Dcm_NetTxHandlerReset();
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueuedCommunicationStateChange()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueuedCommunicationStateChange(
  J1939Dcm_DM1QueueReadPtrType pDM1Queue,
  J1939Dcm_DM1StatePtrType pDM1State
  )
{
  /* #20 If the communication state went from offline to online: */
  if (pDM1Queue->StateChangeRequest == J1939DCM_STATE_ONLINE)
  {
    /* #30 If processing state indicates idle: */
    if (pDM1State->ProcessingState == J1939DCM_MSG_STATE_IDLE)
    {
      /* #40 Set processing state to not busy. */
      pDM1State->ProcessingState = J1939DCM_MSG_STATE_WAIT;                                                                                          /* VCA_J1939DCM_FALSE_POSITIVE */
    } /* else: node is already online; do not change internal state */
  }
  /* #50 Otherwise (if the communication state went from online to offline): */
  else
  {
    /* #60 Release DEM resources. */
    J1939Dcm_DtcHandlerDemSemaphoreRelease(&pDM1State->HasDemAccess);
    /* #70 Set processing state to idle. */
    pDM1State->ProcessingState = J1939DCM_MSG_STATE_IDLE;                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
  }
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueuedRequest()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueuedRequest(
  J1939Dcm_DM1QueueReadPtrType pDM1Queue,
  CONSTP2VAR(boolean, AUTOMATIC, J1939DCM_INTERNAL_DATA) pSendNACK,
  J1939Dcm_DM1StatePtrType pDM1State
  )
{
  /*
   * #20 If the processing state indicates not busy (insure that DM1 processor is inactive in order
   *      to trigger a single transmission):
   */
  if (pDM1State->ProcessingState == J1939DCM_MSG_STATE_WAIT)
  {
    /*
     * #30 Prepare for message processing by updating the processing state to start message preparation
     *     and copying the queue of events into the state of the diagnostic message.
     */
    pDM1State->ProcessingState = J1939DCM_MSG_STATE_PREP_START;                                                                                      /* VCA_J1939DCM_FALSE_POSITIVE */
    pDM1State->ResponseDA      = pDM1Queue->ResponseDA;                                                                                              /* VCA_J1939DCM_FALSE_POSITIVE */
    pDM1State->ChannelHdl      = pDM1Queue->ChannelHdl;                                                                                              /* VCA_J1939DCM_FALSE_POSITIVE */
  }
  /* #40 Otherwise (if the processing state indicates busy): */
  else
  {
    /* #50 If the response address of the requested diagnostic message is not global: */
    if (pDM1Queue->ResponseDA != J1939DCM_ADDRESS_BROADCAST)
    {
      /*
       * #60 Trigger sending a negative acknowledgement for non-broadcast requests and do not change
       *     processing state because transmission is already in progress.
       */
      *pSendNACK = TRUE;
    }
  }
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueuedDtcStatusChange()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueuedDtcStatusChange(
  J1939Dcm_DM1QueueReadPtrType pDM1Queue,                                                                                                            /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_DM1StatePtrType pDM1State
  )
{
  J1939Dcm_IgnoreUnusedArgument_CONST(pDM1Queue)                                                                                                     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* If the change is the first in this one-second period, and if the processing state indicates not busy: */
  if ((pDM1State->DTCSTatusChanged == FALSE) && /* first DTC status change this 1sec period? */
      (J1939DCM_MSG_STATE_WAIT == pDM1State->ProcessingState)) /* is DM1 already processed? */
  {
    /* #20 Indicate the occurrence of the first DTC status change in this one-second period. */
    pDM1State->DTCSTatusChanged = TRUE;                                                                                                              /* VCA_J1939DCM_FALSE_POSITIVE */

    /* DM1 processor is inactive; trigger broadcast transmission. */
    /*
     * #30 Prepare for message processing by updating the processing state to start message preparation
     * and the state of the diagnostic message to broadcast transmission via all online channels.
     */
    pDM1State->ProcessingState   = J1939DCM_MSG_STATE_PREP_START;                                                                                    /* VCA_J1939DCM_FALSE_POSITIVE */
    pDM1State->ResponseDA        = J1939DCM_ADDRESS_BROADCAST;                                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */
    pDM1State->ChannelHdl        = J1939DCM_INVALID_CHANNEL_HDL;                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
  } /* else: ignore eventually pending requests */
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleTimer()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleTimer(
  J1939Dcm_DM1StatePtrType pDM1State
  )
{
  /* #10 If the one-second period is not expired: */
  if (pDM1State->Timer > 0u)
  {
    /* #11 If DM13 is supported, then at least one channel has to be active. */
    /*
     * [J1939-73] Requests that are generated during the Stop Broadcast state should be responded to.
     * However, devices that may be programmed to periodically issue requests should postpone these
     * requests until stop Broadcast is exited.
     */
# if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
    if (J1939Dcm_DiagContext.CommonContext.DM13State.NumActiveBroadcastChannels != 0u)
# endif /* if broadcast is disabled for all channels, there's no need to count */
    {
      /* #12 Decrement the one-second timer. */
      pDM1State->Timer--;                                                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
    }
  }

  /* --- check for timeout --- */
  /* #13 If the one-second period timer expired: */
  if (pDM1State->Timer == 0u)
  {
    /* timeout; try to trigger broadcast response */
    /* #14 Indicate a none occurrence of any DTC status change in this one-second period. */
    pDM1State->DTCSTatusChanged = FALSE; /* 1sec period is up; allow DTC status change trigger */                                                    /* VCA_J1939DCM_FALSE_POSITIVE */
    /* #15 If the processing state indicates not busy: */
    if (pDM1State->ProcessingState == J1939DCM_MSG_STATE_WAIT)
    {
      /* #16 If DEM resources are free: */
      if (J1939Dcm_DtcHandlerDemSemaphoreGetLocked() == FALSE)
      {
        /* DM1 processor is inactive; trigger broadcast transmission */
        /*
         * #17 Prepare for message processing by updating the processing state to start message preparation and
         *     the state of the diagnostic message to broadcast transmission via all online channels.
         */
        pDM1State->ProcessingState  = J1939DCM_MSG_STATE_PREP_START;                                                                                 /* VCA_J1939DCM_FALSE_POSITIVE */
        pDM1State->ResponseDA       = J1939DCM_ADDRESS_BROADCAST;                                                                                    /* VCA_J1939DCM_FALSE_POSITIVE */
        pDM1State->ChannelHdl       = J1939DCM_INVALID_CHANNEL_HDL;                                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */
        /*
         * #18 Indicate the one-second timer expiration if any channel conforms with ISOBUS and
         *     reset the one-second timer.
         */
        pDM1State->IsTimerExpired   = TRUE;                                                                                                          /* VCA_J1939DCM_FALSE_POSITIVE */
        pDM1State->Timer            = J1939DCM_DM1_TIMEOUT;                                                                                          /* VCA_J1939DCM_FALSE_POSITIVE */
      }
      /* else: DEM is in use; postpone timer reload until DEM becomes available */
    }
    /* #19 Otherwise (if processing state indicates busy): */
    else
    {
      /* #20 If DM1 processor prepares for broadcast: */
      if (pDM1State->ChannelHdl == J1939DCM_INVALID_CHANNEL_HDL)
      {
        /* #21 Reload the one-second period timer. */
        pDM1State->Timer = J1939DCM_DM1_TIMEOUT;                                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
      }
      /* else: DM1 processor is preparing a single response; postpone timer reload until transmission is done */
    }
  }
  /* else: no timeout */
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueuedInfos()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueuedInfos(
  J1939Dcm_DM1QueueReadPtrType pDM1Queue,
  CONSTP2VAR(boolean, AUTOMATIC, J1939DCM_INTERNAL_DATA) pSendNACK,
  J1939Dcm_DM1StatePtrType pDM1State
  )
{
  /* If a transmission of a diagnostic message is confirmed in the current task: */
  if (J1939Dcm_QueueBitOpTest(pDM1Queue, J1939DCM_QUEUE_TXCONF))
  {
    J1939Dcm_DM1HandleQueuedTxConfirmation(
      pDM1Queue,
      pDM1State
      );
  }

  /* If a transmission of a diagnostic message is failed in the current task: */
  if (J1939Dcm_QueueBitOpTest(pDM1Queue, J1939DCM_QUEUE_TXFAIL))
  {
    J1939Dcm_DM1HandleQueuedFailedTxConfirmation(
      pDM1Queue,
      pDM1State
      );
  }

  /* If the communication state was changed: */
  if (J1939Dcm_QueueBitOpTest(pDM1Queue, J1939DCM_QUEUE_STATE))
  {
    J1939Dcm_DM1HandleQueuedCommunicationStateChange(
      pDM1Queue,
      pDM1State
      );
  }

  /* If a new diagnostic message is requested: */
  if (J1939Dcm_QueueBitOpTest(pDM1Queue, J1939DCM_QUEUE_REQ))
  {
    J1939Dcm_DM1HandleQueuedRequest(
      pDM1Queue,
      pSendNACK,
      pDM1State
      );
  }

  /* If DTC status change occurred: */
  if (J1939Dcm_QueueBitOpTest(pDM1Queue, J1939DCM_QUEUE_DTC))
  {
    J1939Dcm_DM1HandleQueuedDtcStatusChange(
      pDM1Queue,
      pDM1State
      );
  }
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1HandleQueue()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleQueue(
  J1939Dcm_NodeContextPtrType pNodeContext
  )
{
  J1939Dcm_DM1QueuePtrType pDM1Queue = &pNodeContext->DM1Queue;
  /* #10 If any of the interrupt service routine functions updated the queue of events of a diagnostic message: */
  if (pDM1Queue->RequestPending != J1939DCM_QUEUE_EMPTY)
  {
    J1939Dcm_DM1QueueType lTmpQueueData;
    boolean               lSendNACK;

    lSendNACK = FALSE;

    /*
     * #20 Enter critical section (Reason: protect data consistency of the queue of events against request
     *     manager interruptions).
     */
    J1939Dcm_EnterCritical();

    /* #30 Copy the queue of events into a local parameter and clear the queue of events. */
    lTmpQueueData.ResponseDA         = pDM1Queue->ResponseDA;
    lTmpQueueData.ChannelHdl         = pDM1Queue->ChannelHdl;
    lTmpQueueData.StateChangeRequest = pDM1Queue->StateChangeRequest;
    lTmpQueueData.RequestPending     = pDM1Queue->RequestPending;

    J1939Dcm_QueueBitOPClrAll(pDM1Queue);                                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */

    /* #40 Leave critical section. */
    J1939Dcm_ExitCritical();

    /* #50 Handle queued information. */
    J1939Dcm_DM1HandleQueuedInfos(
      &lTmpQueueData,
      &lSendNACK,
      &pNodeContext->DM1State
      );

    /* #60 If sending a negative acknowledgement was triggered: */
    if (lSendNACK == TRUE)
    {
      /* #70 Request sending negative acknowledgement from the request manager. */
      (void)J1939Rm_SendAck(                                                                                                                         /* VCA_J1939DCM_POINTER_FORWARD_NULL */
              J1939Dcm_Cfg_GetNodeUserId(pNodeContext->NodeHdl),                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
              J1939Dcm_Cfg_GetChannelId(lTmpQueueData.ChannelHdl),                                                                                   /* VCA_J1939DCM_FALSE_POSITIVE */
              J1939DCM_DM1_PGN,
              NULL_PTR,
              J1939RM_ACK_CANNOT_RESPOND,
              lTmpQueueData.ResponseDA,
              J1939DCM_DM1_PRIORITY,
              FALSE
              );
    }
  } /* J1939DCM_QUEUE_EMPTY */
}
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1Task()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Task(
  void
  )
{
  J1939Dcm_NodeHdlOptType    lNodeHdl;

  /* #10 Iterate over the defined nodes because the queue of events of a diagnostic message is node dependent. */
  for (lNodeHdl = 0u; lNodeHdl < J1939Dcm_GetSizeOfCfg_NodeTable(); ++lNodeHdl)
  {
    J1939Dcm_NodeContextPtrType pNodeContext = &J1939Dcm_DiagContext.NodeContext[lNodeHdl];                                                          /* VCA_J1939DCM_VERIFIED_NODE_ACCESS */

    /* #20 Handle queue. */
    J1939Dcm_DM1HandleQueue(pNodeContext);

    /* #30 If the processing state does not indicate idle: */
    if (pNodeContext->DM1State.ProcessingState != J1939DCM_MSG_STATE_IDLE)
    {
      /* Node is currently online */

      /* #40 Update timers. */
      J1939Dcm_DM1HandleTimer(&pNodeContext->DM1State);

      /* --- handle message preparation and transmission --- */
      /* #50 If the processing state indicates busy:
                                           ( If a new DM1 is requested
                                         Or  If any DTC status change in the current one-second period occurred
                                         or  If the 1 second period expired in the current task
                                         Or  If the DM1 processing has not been completed in the previous task
                                         Or  If the DM1 transmission was failed in the current task) */
      if (pNodeContext->DM1State.ProcessingState > J1939DCM_MSG_STATE_WAIT)
      {
        /* #60 Trigger the processing of the diagnostic message. */
        J1939Dcm_DM1Processor(pNodeContext);
      } /* end: state > J1939DCM_MSG_STATE_WAIT */

    } /* end: not J1939DCM_MSG_STATE_IDLE */
  }
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
 /***********************************************************************************************************************
 * J1939Dcm_DM1AssembleMessage()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1AssembleMessage(
  J1939Dcm_NodeContextPtrType pNodeContext,
  CONSTP2VAR(J1939Rm_AckCode, AUTOMATIC, J1939DCM_INTERNAL_DATA) pAcknowledge
  )
{
  J1939Dcm_FilterHandlerType  lFilterHandler;
  J1939Dcm_DM1StatePtrType pDM1State = &pNodeContext->DM1State;

  /* --- start DM1 processing: filter DTCs --- */
  /* #10 If the processing state indicates message preparation start (a new request was received): */
  if (pDM1State->ProcessingState == J1939DCM_MSG_STATE_PREP_START)
  {
    /* #20 Get a lock on DEM resources in order to import the required data from DEM for the incoming DM request. */
    J1939Dcm_DtcHandlerDemSemaphoreLock(&pDM1State->HasDemAccess);
    /* #30 If a lock on DEM resources is successfully obtained: */
    if (pDM1State->HasDemAccess == TRUE )
    {
      /* #40 Update the local DTC filter according to DM01 requirements. Trigger read Dtc Handler. */
      lFilterHandler.StatusFilter = DEM_J1939DTC_ACTIVE;
      lFilterHandler.DTCKind = DEM_DTC_KIND_ALL_DTCS;
      lFilterHandler.DTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
      lFilterHandler.FiltredNode = pNodeContext->NodeHdl;

      J1939Dcm_DtcHandlerSetDtcFilter(
        &pDM1State->ProcessingState,
        &pDM1State->BufferContext,
        &lFilterHandler
        );
    }
    /* #50 Otherwise: */
    else
    {
      /*
       * #60 Skip processing because DEM is currently in use (set processing state to send acknowledgement
       *     with code: cannot respond).
       */
      pDM1State->ProcessingState = J1939DCM_MSG_STATE_SENDACK;                                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */
      *pAcknowledge = J1939RM_ACK_CANNOT_RESPOND;
    }
  }

  /* --- finalize DM1 processing: get DTCs --- */
  /* #70 Get matching DTCs, if the processing state is set to get DTCs. */
  if (pDM1State->ProcessingState == J1939DCM_MSG_STATE_PREP_DTCS)
  {
    J1939Dcm_DtcHandlerGetDTCs(
      &pDM1State->ProcessingState,
      J1939DCM_DM1_MAX_DTCS,
      pNodeContext->NodeHdl
      );
  }
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
 /***********************************************************************************************************************
 * J1939Dcm_DM1Broadcast()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Broadcast(
  J1939Dcm_NodeContextPtrType pNodeContext
  )
{
  Std_ReturnType TxResult;
  boolean lAnyTxSucceeded;
  J1939Dcm_ChannelHdlOptType lChannelHdl;
  J1939Dcm_DM1StatePtrType pDM1State = &pNodeContext->DM1State;

  /* #10 If ISOBUS feature is configured, indicate whether an error is currently active. */
# if (J1939DCM_DM1_ISOBUS_CONFORM == STD_ON)
  boolean lIsErrorInactive = (boolean)(0u == J1939Dcm_DiagContext.CommonContext.DtcHandlerState.NumDTCs);                                            /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
# endif

  /* #15 Set processing state to wait for TxConfirmation. */
  pDM1State->ProcessingState = J1939DCM_MSG_STATE_TXCONF;                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
  lAnyTxSucceeded = FALSE;

  /* broadcast: transmit on all channels which support DM1 */
  /* #20 Iterate over the available channels. */
  for (lChannelHdl = 0u; lChannelHdl < J1939Dcm_GetSizeOfCfg_ChannelTable(); ++lChannelHdl)
  {
    /* #25 If the incoming TxPdu is valid and the communication state of the node-channel pair is online: */
    if( (pDM1State->TxPdus[lChannelHdl] != J1939DCM_INVALID_PDU_ID)                                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */
      &&(J1939Dcm_ComStateIsOnline(pNodeContext->NodeHdl, lChannelHdl)) )                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
    {
      /* #30 If DM13 is supported, then at least one channel has to be active. */
      /*
       * [J1939-73] Requests that are generated during the Stop Broadcast state should be responded to.
       * However, devices that may be programmed to periodically issue requests should postpone these
       * requests until stop Broadcast is exited.
       */
# if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
      if (J1939Dcm_DM13IsBroadcastStatusActive(lChannelHdl))
# endif
      {
        /* channel is online, broadcast is active and it supports DM1 */
        /*
         * #35 If ISOBUS feature is configured, and by the end of the one-second period an error
         *     was not active, suppress the transmission.
         */
# if (J1939DCM_DM1_ISOBUS_CONFORM == STD_ON)
        if ( (pDM1State->IsTimerExpired == TRUE) &&
             (lIsErrorInactive == TRUE) &&
             (J1939Dcm_Cfg_GetChannelIsobus(lChannelHdl) == TRUE))                                                                                   /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_J1939DCM_SINGLE_CHANNEL_ISOBUS_CHARACTERISTIC */
        {
          /* Do not indicate success for transmission preparation. */
          /*
           * If all other not-ISOBUS channels failed transmission, the processing state of that particular
           * node will be set to not busy (reset processor).
           */
        }
        /* #40 Otherwise: */
        else
# endif
        {
          /* #45 Trigger transmission and register the transmission results. */
          TxResult = J1939Dcm_NetTxHandlerTransmit(
                       pDM1State->TxPdus[lChannelHdl],
                       (J1939Dcm_ChannelHdlType)(lChannelHdl)
                       );

          lAnyTxSucceeded = (boolean)((TxResult == E_OK)? TRUE : FALSE);
        }
      }
    }
  }

  /*
   * #50 If ISOBUS feature is configured, reset the active error flag and the flag that indicates
   *     the expiration of the one-second period.
   */
  pDM1State->IsTimerExpired = FALSE;                                                                                                                 /* VCA_J1939DCM_FALSE_POSITIVE */

  /* #55 If the transmission over all the referenced channels by the requested node was failed:  */
  if (lAnyTxSucceeded == FALSE)
  {
    /* #60 Reset state machine.  */
    pDM1State->ProcessingState = J1939DCM_MSG_STATE_WAIT;                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
    J1939Dcm_NetTxHandlerReset();
  }
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM1Unicast()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Unicast(
  J1939Dcm_DM1StatePtrType pDM1State
  )
{
  Std_ReturnType TxResult;
  /* channel supports DM1 */

  /* #10 Set processing state to wait for TxConfirmation. */
  pDM1State->ProcessingState = J1939DCM_MSG_STATE_TXCONF;                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */

  TxResult = J1939Dcm_NetTxHandlerTransmit(
               pDM1State->TxPdus[pDM1State->ChannelHdl],                                                                                             /* VCA_J1939DCM_FALSE_POSITIVE */
               pDM1State->ChannelHdl
               );

  /* #30 If the triggering for transmission is failed: */
  if (TxResult != E_OK)
  {
    /* #40 Cancel transmission by resetting Txhandler. Update processing state to send acknowledgement. */
    pDM1State->ProcessingState = J1939DCM_MSG_STATE_SENDACK;                                                                                         /* VCA_J1939DCM_FALSE_POSITIVE */
    J1939Dcm_NetTxHandlerReset();
  }
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
 /***********************************************************************************************************************
 * J1939Dcm_DM1HandleAssemblyFailure()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1HandleAssemblyFailure(
  J1939Dcm_NodeContextPtrType pNodeContext,
  J1939Rm_AckCode acknowledge
  )
{
  /* --- transmit NACK --- */
  J1939Dcm_DM1StatePtrType pDM1State = &pNodeContext->DM1State;

  /* #10 If the processing state indicates sending acknowledgement: */
  if (pDM1State->ProcessingState == J1939DCM_MSG_STATE_SENDACK)
  {
    /* #20 Release DEM resources.*/
    J1939Dcm_DtcHandlerDemSemaphoreRelease(&pDM1State->HasDemAccess);

    /* #30 If the source address of the requested message is specific: */
    if (pDM1State->ResponseDA != J1939DCM_ADDRESS_BROADCAST)
    {
      (void)J1939Rm_SendAck(                                                                                                                         /* VCA_J1939DCM_POINTER_FORWARD_NULL */
              J1939Dcm_Cfg_GetNodeUserId(pNodeContext->NodeHdl),                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
              J1939Dcm_Cfg_GetChannelId(pDM1State->ChannelHdl),                                                                                      /* VCA_J1939DCM_FALSE_POSITIVE */
              J1939DCM_DM1_PGN,
              NULL_PTR,
              acknowledge,
              pDM1State->ResponseDA,
              J1939DCM_DM1_PRIORITY,
              FALSE
              );
    }

    /* else: skip NACK; directly reset DM1 processor */
    /* #50 Set processing state to not busy (reset DM1 processor). */
    pDM1State->ProcessingState = J1939DCM_MSG_STATE_WAIT;                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */

  }
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
 /***********************************************************************************************************************
 * J1939Dcm_DM1Transmit()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Transmit(
  J1939Dcm_NodeContextPtrType pNodeContext
  )
{
  J1939Dcm_DM1StatePtrType pDM1State = &pNodeContext->DM1State;
    /* #10 If the processing state indicates that the DM is ready for transmission: */
  if (pDM1State->ProcessingState == J1939DCM_MSG_STATE_TX)
  {
    Std_ReturnType TxResult;

    /* #20 Release DEM semaphore. */
    J1939Dcm_DtcHandlerDemSemaphoreRelease(&pDM1State->HasDemAccess);

    /* #30 Prepare for transmission. Meta Data Length is not relevant for DM1 messages and is set to 0. */
    TxResult = J1939Dcm_NetTxHandlerPrepare(
                 &pDM1State->BufferContext,
                 J1939DCM_DM1,
                 pNodeContext->NodeHdl,
                 pDM1State->ResponseDA,
                 0
                 );

    /* #50 If preparation for transmission was succeeded: */
    if (TxResult == E_OK)
    {
      /* transmission prepared; trigger transmit */
      /* #60 If the transmission is global broadcast: */
      if (pDM1State->ChannelHdl == J1939DCM_INVALID_CHANNEL_HDL)
      {
        /* #70 Broadcast DM1. */
        J1939Dcm_DM1Broadcast(pNodeContext);
      }
      /* #80 Otherwise (if single transmission): */
      else
      {
        /* #90 Unicast DM1. */
        J1939Dcm_DM1Unicast(pDM1State);
      }
    } /* else: transmit handler is busy; retry later */
  }
}
#endif

#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
 /***********************************************************************************************************************
 * J1939Dcm_DM1Processor()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Processor(
  J1939Dcm_NodeContextPtrType pNodeContext
  )
{
  J1939Rm_AckCode lAcknowledge;

  lAcknowledge = J1939RM_ACK_NEGATIVE;

  /* #10 Assemble message. */
  J1939Dcm_DM1AssembleMessage(
    pNodeContext,
    &lAcknowledge
    );

  /* #20 Transmit prepared DM1 message. */
  J1939Dcm_DM1Transmit(pNodeContext);

  /* #30 Handle message assembly failure. */
  J1939Dcm_DM1HandleAssemblyFailure(
    pNodeContext,
    lAcknowledge
    );
}
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM13UpdateBroadcastStatus()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM13UpdateBroadcastStatus(
  J1939Dcm_DM13QueueReadPtrType pDM13Queue,
  CONSTP2VAR(boolean, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBroadcastStateChanged,
  CONSTP2VAR(boolean, AUTOMATIC, J1939DCM_INTERNAL_DATA) pRestartTimeout
  )
{
  J1939Dcm_ChannelHdlOptType lChannelHdl;
  /* #10 Start iteration over the configured channels. */
  for (lChannelHdl = 0u; lChannelHdl < J1939Dcm_GetSizeOfCfg_ChannelTable(); ++lChannelHdl)
  {
    /* #15 If the broadcast command of a channel indicates start broadcast: */
    if (pDM13Queue->BroadcastCommand[lChannelHdl] == J1939DCM_DM13_BROADCAST_START)                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */
    {
      /* #20 If the channel is inactive: */
      if (!J1939Dcm_DM13IsBroadcastStatusActive(lChannelHdl))
      {
        /* #25 Re-activate the channel. */
        J1939Dcm_DiagContext.CommonContext.DM13State.NumActiveBroadcastChannels++;
        J1939Dcm_DM13SetBroadcastStatusActive(lChannelHdl);
        /* #30 Indicate a change in the broadcast state. */
        *pBroadcastStateChanged = TRUE;
      } /* else: nothing to be done; broadcast is already active */
    }
    /* #35 Otherwise (if the broadcast command of a channel indicates stop broadcast or do not care): */
    else
    {
      /* #40 If the broadcast command of a channel indicates stop broadcast: */
      if (pDM13Queue->BroadcastCommand[lChannelHdl] == J1939DCM_DM13_BROADCAST_STOP)
      {
        /* #45 If the channel is active: */
        if (J1939Dcm_DM13IsBroadcastStatusActive(lChannelHdl))
        {
          /* #50 Deactivate the channel. */
          J1939Dcm_DiagContext.CommonContext.DM13State.NumActiveBroadcastChannels--;
          J1939Dcm_DM13ClearBroadcastStatusActive(lChannelHdl);
          /* #55 Indicate a change in the broadcast state. */
          *pBroadcastStateChanged = TRUE;
        } /* else: nothing to be done; broadcast is already inactive */

        /* valid DM13 received and any channel is stopped: restart timeout */
        /* #60 Trigger reloading DM13 timer. */
        *pRestartTimeout = TRUE;
      } /* else: neither start nor stop, ignore (do not care) */
    }
  }
}
#endif

#if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM13HandleTimer()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM13HandleTimer(
  CONSTP2VAR(boolean, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBroadcastStateChanged
  )
{
  J1939Dcm_DM13StatePtrType pDM13State = &J1939Dcm_DiagContext.CommonContext.DM13State;
  /* #10 If DM13 timer has not been expired: */
  if (pDM13State->BroadcastDisableTimer != 0u)
  {
    /* #20 Decrement DM13 timer. */
    pDM13State->BroadcastDisableTimer--;

    /* #30 If DM13 is expired: */
    if (pDM13State->BroadcastDisableTimer == 0u)
    {
      /* #40 Re-activate normal state (start broadcast of all available channels). */
      pDM13State->NumActiveBroadcastChannels = J1939Dcm_Cfg_GetChannelTableSize();
      pDM13State->BroadcastStatusInformation = J1939Dcm_Cfg_GetInitBroadcastStatus();
      /*#50 Indicate a change in the broadcast state. */
      *pBroadcastStateChanged = TRUE;
    }
  }
}
#endif

#if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM13HandleQueue()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM13HandleQueue(
  CONSTP2VAR(boolean, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBroadcastStateChanged
  )
{
  J1939Dcm_CommonContextPtrType pCommonContext = &J1939Dcm_DiagContext.CommonContext;
  J1939Dcm_DM13StatePtrType pDM13State = &pCommonContext->DM13State;
  J1939Dcm_DM13QueuePtrType pDM13Queue = &pCommonContext->DM13Queue;
  /* #10 If DM13 has been received but has not yet processed: */
  if (pDM13Queue->RequestPending == TRUE)
  {
    J1939Dcm_DM13QueueType     lTmpQueueData;
    J1939Dcm_ChannelHdlOptType lChannelHdl;

    boolean lRestartTimeout = FALSE;

    /*
     * #15 Enter critical section (Reason: protect data consistency of the queue of events against PduR interruptions).
     */
    J1939Dcm_EnterCritical();

    /* #20 Copy the queue of events into a local parameter and indicate that DM13 has been processed. */
    lTmpQueueData.HoldSignal     = pDM13Queue->HoldSignal;

    for (lChannelHdl = 0u; lChannelHdl < J1939Dcm_GetSizeOfCfg_ChannelTable(); ++lChannelHdl)
    {
      lTmpQueueData.BroadcastCommand[lChannelHdl] = pDM13Queue->BroadcastCommand[lChannelHdl];                                                       /* VCA_J1939DCM_VERIFIED_CHANNEL_ACCESS */
    }

    pDM13Queue->RequestPending = FALSE;

    /* #25 Leave critical section. */
    J1939Dcm_ExitCritical();

    /* --- handle queued DM13 requests --- */

    /* #30 If the purpose of the incoming DM13 is to modify the broadcast status (setup Message): */
    if (lTmpQueueData.HoldSignal == J1939DCM_DM13_HOLD_NA)   /* SWS_J1939Dcm_00054 */
    {
      /* #35 Udpate broadcast status. */
      J1939Dcm_DM13UpdateBroadcastStatus(&lTmpQueueData, pBroadcastStateChanged, &lRestartTimeout);
    }
    /* #40 If the purpose of the incoming DM13 is to hold the broadcast status (hold Message): */
    else
    {
      /* #45 If the hold signal applies to all available channels: */
      if ((lTmpQueueData.HoldSignal == J1939DCM_DM13_HOLD_ALL)
# if (J1939DCM_DM13_HS_MODIFIED_ENABLED == STD_ON)
          || (lTmpQueueData.HoldSignal == J1939DCM_DM13_HOLD_STATE_MODIFIED)
# endif
         )
      {
        /* #50 Trigger reloading DM13 timer. */
        lRestartTimeout = TRUE;
      }
      /* else: unknown hold signal; ignore (hold signal to a partial set of the available channels is not supported) */
    }

    /* #55 If all the available channels are active: */
    if (J1939Dcm_Cfg_GetInitBroadcastStatus() == pDM13State->BroadcastStatusInformation)
    {
      /* #60 Stop timeout supervision. */
      pDM13State->BroadcastDisableTimer = 0;
    }
    /* #65 Otherwise (if at least one channel is inactive): */
    else
    {
      /* #70 If the reloading of DM13 timer was triggered: */
      if (lRestartTimeout == TRUE)
      {
        /* #75 Reload DM13 timer. */
        pDM13State->BroadcastDisableTimer = J1939DCM_DM13_TIMEOUT;
      }
    }
  }
}
#endif

#if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM13Task()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM13Task(
  void
  )
{
  boolean lBroadcastStateChanged = FALSE;

  /* #10 Handle queue. */
  J1939Dcm_DM13HandleQueue(&lBroadcastStateChanged);

  /* #20 Update channel timer. */
  J1939Dcm_DM13HandleTimer(&lBroadcastStateChanged);

  /* -- report new broadcast status to BswM, if needed --- */
  /* #30 If a change in the broadcast occurred: */
  if (lBroadcastStateChanged == TRUE)
  {
    /* #40 Inform BswM with the new broadcast status. */
    BswM_J1939DcmBroadcastStatus(J1939Dcm_DiagContext.CommonContext.DM13State.BroadcastStatusInformation);
  }
}
#endif /* (J1939DCM_NEED_DM13_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM35HandleQueuedTxConfirmation()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleQueuedTxConfirmation(
  J1939Dcm_DM35QueueReadPtrType pDM35Queue,                                                                                                          /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_DM35StatePtrType pDM35State
  )
{
  J1939Dcm_IgnoreUnusedArgument_CONST(pDM35Queue)                                                                                                    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #20 If a transmission of a diagnostic message was triggered in the previous task: */
  if (pDM35State->ProcessingState == J1939DCM_MSG_STATE_TXCONF)
  {
    /* #30 Set Processing state to unbusy because TxConfirmation for all transmitting channels were received. */
    pDM35State->ProcessingState = J1939DCM_MSG_STATE_WAIT;                                                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
  } /* else: TxConfirmation no longer awaited (e.g. because of change to offline); ignore */

  /* #40 Reset transmission because TxHandler is still in use even if the confirmation is no longer expected. */
  J1939Dcm_NetTxHandlerReset();
}
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM35HandleQueuedCommunicationStateChange()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleQueuedCommunicationStateChange(
  J1939Dcm_DM35QueueReadPtrType pDM35Queue,
  J1939Dcm_DM35StatePtrType pDM35State
  )
{
  /* #20 If the communication state went from online to offline: */
  if (pDM35Queue->StateChangeRequest == J1939DCM_STATE_OFFLINE)
  {
    /* #30 Release DEM resources. */
    J1939Dcm_DtcHandlerDemSemaphoreRelease(&pDM35State->HasDemAccess);
    /* #40 Set processing state to idle. */
    pDM35State->ProcessingState = J1939DCM_MSG_STATE_IDLE;                                                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
    /* #50 Stop the periodic transmission and reset the one-second timer. */
    pDM35State->ActiveChannels = 0;                                                                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */
    pDM35State->Timer = J1939DCM_DM35_TIMEOUT;                                                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */
  } /* else: offline -> online: has no effect, DM35 must be explicitly requested */
}
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM35HandleQueuedRequest()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleQueuedRequest(
  J1939Dcm_DM35QueueReadPtrType pDM35Queue,
  J1939Dcm_DM35StatePtrType pDM35State
  )
{
  /* #20 Update the active channel mask. */
  pDM35State->ActiveChannels |= pDM35Queue->RequestedChannels;                                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */

  /* #30 If the processing state indicates idle: */
  if (pDM35State->ProcessingState == J1939DCM_MSG_STATE_IDLE)
  {
    /* first channel to be activated; start DM35 state machine */
    /* #40 Set processing state to not busy. */
    pDM35State->ProcessingState   = J1939DCM_MSG_STATE_WAIT;                                                                                         /* VCA_J1939DCM_FALSE_POSITIVE */
  }
}
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM35HandleTimer()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleTimer(
  J1939Dcm_DM35StatePtrType pDM35State
  )
{
  /* #10 If the one-second period is not expired: */
  if (pDM35State->Timer > 0u)
  {
    /* #20 If DM13 is supported, then at least one channel has to be active. */
    /*
     * [J1939-73] Requests that are generated during the Stop Broadcast state should be responded to.
     * However, devices that may be programmed to periodically issue requests should postpone these
     * requests until stop Broadcast is exited.
     */
# if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
    if (J1939Dcm_DiagContext.CommonContext.DM13State.NumActiveBroadcastChannels != 0u)
# endif /* else: broadcast is disabled for all channels; there's no need to count */
    {
      /* #30 Decrement the one-second timer. */
      pDM35State->Timer--;                                                                                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
    }
  }

  /* --- check for timeout --- */
  /* #40 If the one-second period timer expired: */
  if (pDM35State->Timer == 0u)
  {
    /*
     * DET check: if previous DM35 message is not yet completed, it took longer than 1sec
     * and we certainly have a problem
     */
    /* #50 Make sure that the processing state indicates not busy. */
    J1939Dcm_DetAssert(
      (J1939DCM_MSG_STATE_WAIT == pDM35State->ProcessingState),
      J1939DCM_API_MAINFUNCTION,
      J1939DCM_E_OVERRUN
      )

    /* #60 If DEM resources are free: */
    if (J1939Dcm_DtcHandlerDemSemaphoreGetLocked() == FALSE)
    {
      /* #70 Trigger broadcast transmission and reload the one-second timer. */
      pDM35State->ProcessingState  = J1939DCM_MSG_STATE_PREP_START;      /* SWS_J1939Dcm_00082 */                                                    /* VCA_J1939DCM_FALSE_POSITIVE */
      pDM35State->Timer = J1939DCM_DM35_TIMEOUT;                                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
    }
    /* else: DEM is in use; postpone timer reload until DEM becomes available */
  }
  /* else: no timeout */
}
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM35HandleQueuedInfos()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleQueuedInfos(
  J1939Dcm_DM35QueueReadPtrType pDM35Queue,
  J1939Dcm_DM35StatePtrType pDM35State
  )
{
  /* If a transmission of a diagnostic message is confirmed in the current task: */
  if (J1939Dcm_QueueBitOpTest(pDM35Queue, J1939DCM_QUEUE_TXCONF))
  {
    J1939Dcm_DM35HandleQueuedTxConfirmation(
      pDM35Queue,
      pDM35State
      );
  }

  /* If the communication state was changed: */
  if (J1939Dcm_QueueBitOpTest(pDM35Queue, J1939DCM_QUEUE_STATE))
  {
    J1939Dcm_DM35HandleQueuedCommunicationStateChange(
      pDM35Queue,
      pDM35State
      );
  }

  /* If a new diagnostic message is requested: */
  if (J1939Dcm_QueueBitOpTest(pDM35Queue, J1939DCM_QUEUE_REQ))
  {
    J1939Dcm_DM35HandleQueuedRequest(
      pDM35Queue,
      pDM35State
      );
  }
}
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM35HandleQueue()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleQueue(
  J1939Dcm_NodeContextPtrType pNodeContext
  )
{
  J1939Dcm_DM35QueuePtrType pDM35Queue = &pNodeContext->DM35Queue;
  /* #10 If any of the interrupt service routine functions updated the queue of events of a diagnostic message: */
  if (pDM35Queue->RequestPending != J1939DCM_QUEUE_EMPTY)
  {
    J1939Dcm_DM35QueueType lTmpQueueData;
    /*
     * #20 Enter critical section
     *     (Reason: protect data consistency of the queue of events against request manager interruptions).
     */
    J1939Dcm_EnterCritical();

    /* #30 Copy the queue of events into a local parameter, clear the queue of events, and the channel bitmask. */
    lTmpQueueData.RequestedChannels  = pDM35Queue->RequestedChannels;
    lTmpQueueData.StateChangeRequest = pDM35Queue->StateChangeRequest;
    lTmpQueueData.RequestPending     = pDM35Queue->RequestPending;

    J1939Dcm_QueueBitOPClrAll(pDM35Queue);                                                                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
    pDM35Queue->RequestedChannels = 0;                                                                                                               /* VCA_J1939DCM_FALSE_POSITIVE */

    /* #40 Leave critical section. */
    J1939Dcm_ExitCritical();

    /* #50 Handle queued information. */
    J1939Dcm_DM35HandleQueuedInfos(
      &lTmpQueueData,
      &pNodeContext->DM35State
      );
  } /* J1939DCM_QUEUE_EMPTY */
}
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM35Task()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35Task(
  void
  )
{
  J1939Dcm_NodeHdlOptType lNodeHdl;

  /* #10 Iterate over the defined nodes because the queue of events of a diagnostic message is node dependent. */
  for (lNodeHdl = 0u; lNodeHdl < J1939Dcm_GetSizeOfCfg_NodeTable(); ++lNodeHdl)
  {
    J1939Dcm_NodeContextPtrType pNodeContext = &J1939Dcm_DiagContext.NodeContext[lNodeHdl];                                                          /* VCA_J1939DCM_VERIFIED_NODE_ACCESS */

    /* #20 Handle queue. */
    J1939Dcm_DM35HandleQueue(pNodeContext);

    /* #30 If the processing state does not indicate idle: */
    if (pNodeContext->DM35State.ProcessingState != J1939DCM_MSG_STATE_IDLE)
    {
      /* DM35 has been activated */

      /* #40 Update timers. */
      J1939Dcm_DM35HandleTimer(&pNodeContext->DM35State);

      /* --- handle message preparation and transmission --- */
      /*
       * #50 If the processing state indicates busy:
       *                                      (   If the 1 second period expired in the current task
       *                                      Or  If the DM1 processing has not been completed in the previous task)
       */
      if (pNodeContext->DM35State.ProcessingState > J1939DCM_MSG_STATE_WAIT)
      {
        /* #60 Trigger the processing of the diagnostic message. */
        J1939Dcm_DM35Processor(pNodeContext);
      } /* end: state > J1939DCM_MSG_STATE_WAIT */

    } /* end: not J1939DCM_MSG_STATE_IDLE */
  }
}
#endif /* (J1939DCM_NEED_DM35_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM35AssembleMessage()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35AssembleMessage(
  J1939Dcm_NodeContextPtrType pNodeContext
  )
{
  J1939Dcm_FilterHandlerType  lFilterHandler;
  J1939Dcm_DM35StatePtrType pDM35State = &pNodeContext->DM35State;
  /* --- start DM35 processing: filter DTCs --- */
  /* #10 If the processing state indicates message preparation start (a new request was received): */
  if (pDM35State->ProcessingState == J1939DCM_MSG_STATE_PREP_START)
  {
    /* #20 Get a lock on DEM resources in order to import the required data from DEM for the incoming DM request. */
    J1939Dcm_DtcHandlerDemSemaphoreLock(&pDM35State->HasDemAccess);
    /* #30 If a lock on DEM resources is successfully obtained: */
    if (pDM35State->HasDemAccess == TRUE)
    {
      /* #40 Update the local DTC filter according to DM01 requirements. Trigger read Dtc Handler. */
      lFilterHandler.StatusFilter = DEM_J1939DTC_CURRENTLY_ACTIVE;
      lFilterHandler.DTCKind = DEM_DTC_KIND_ALL_DTCS;
      lFilterHandler.DTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
      lFilterHandler.FiltredNode = pNodeContext->NodeHdl;

      J1939Dcm_DtcHandlerSetDtcFilter(
        &pDM35State->ProcessingState,
        &pDM35State->BufferContext,
        &lFilterHandler
        );
    }
    /* #50 Otherwise: */
    else
    {
      /*
       * #60 Skip processing because DEM is currently in use
       *     (set processing state to send acknowledgement with code: cannot respond).
       */
      pDM35State->ProcessingState = J1939DCM_MSG_STATE_SENDACK;                                                                                      /* VCA_J1939DCM_FALSE_POSITIVE */
    }
  }

  /* --- finalize DM35 processing: get DTCs --- */
  /* #70 Get matching DTCs, if the processing state is set to get DTCs. */
  if (pDM35State->ProcessingState == J1939DCM_MSG_STATE_PREP_DTCS)
  {
    J1939Dcm_DtcHandlerGetDTCs(
      &pDM35State->ProcessingState,
      J1939DCM_DM_MAX_DTCS,
      pNodeContext->NodeHdl
      );
  }
}
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM35Transmit()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35Transmit(
  J1939Dcm_NodeContextPtrType pNodeContext
  )
{
  J1939Dcm_DM35StatePtrType pDM35State = &pNodeContext->DM35State;
  /* #10 If the processing state indicates that the DM is ready for transmission: */
  if (pDM35State->ProcessingState == J1939DCM_MSG_STATE_TX)
  {
    Std_ReturnType TxResult;
    J1939Dcm_ChannelHdlOptType lChannelHdl;

    /* #15 Release DEM semaphore. */
    J1939Dcm_DtcHandlerDemSemaphoreRelease(&pDM35State->HasDemAccess);

    /* #20 Prepare for transmission. Meta Data Length is not relevant for DM35 messages and is set to 0. */
    TxResult = J1939Dcm_NetTxHandlerPrepare(
                 &pDM35State->BufferContext,
                 J1939DCM_DM35,
                 pNodeContext->NodeHdl,
                 J1939DCM_ADDRESS_BROADCAST,
                 0
                 );

    /* #30 If preparation for transmission was succeeded: */
    if (TxResult == E_OK)
    {
      boolean lAnyTxSucceeded;

      lAnyTxSucceeded = FALSE;

      /* transmission prepared; trigger transmit */
      /* #35 Set processing state to wait for TxConfirmation. */
      pDM35State->ProcessingState = J1939DCM_MSG_STATE_TXCONF;                                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */

      /* #40 Iterate over the available channels. */
      for (lChannelHdl = 0u; lChannelHdl < J1939Dcm_GetSizeOfCfg_ChannelTable(); ++lChannelHdl)
      {
        /* #45 If DM35 was requested on the incoming channel and the node-channel pair is online: */
        if( (J1939Dcm_DM35ChannelIsActive(pDM35State->ActiveChannels, lChannelHdl))
          &&(J1939Dcm_ComStateIsOnline(pNodeContext->NodeHdl, lChannelHdl)) )                                                                        /* VCA_J1939DCM_FALSE_POSITIVE */
        {
          /* #50 If DM13 is supported, then at least one channel has to be active. */
          /*
           * [J1939-73] Requests that are generated during the Stop Broadcast state should be responded to.
           * However, devices that may be programmed to periodically issue requests should postpone these
           * requests until stop Broadcast is exited.
           */
# if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
          if (J1939Dcm_DM13IsBroadcastStatusActive(lChannelHdl))
# endif
          {
            /* channel is online, broadcast is active and DM35 has been requested */
            /* #55 Trigger transmission and register the transmission results. */
            TxResult = J1939Dcm_NetTxHandlerTransmit(
                         pDM35State->TxPdus[lChannelHdl],                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
                         (J1939Dcm_ChannelHdlType)(lChannelHdl)
                         );
            lAnyTxSucceeded = (boolean)((TxResult == E_OK) ? TRUE : FALSE);
          }
        }
      }

      /* #60 If the transmission over all the referenced channels by the requested node was failed:*/
      if (lAnyTxSucceeded == FALSE)
      {
        /* #65 Reset state machine. */
        pDM35State->ProcessingState = J1939DCM_MSG_STATE_WAIT;                                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */
        J1939Dcm_NetTxHandlerReset();
      }
    } /* else: transmit handler is busy; retry later */
  }
}                                                                                                                                                    /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM35HandleAssemblyFailure()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35HandleAssemblyFailure(
  J1939Dcm_DM35StatePtrType pDM35State
  )
{
  /* #10 If the processing state indicates sending acknowledgement: */
  if (pDM35State->ProcessingState == J1939DCM_MSG_STATE_SENDACK)
  {
    /* #20 Release DEM resources. */
    J1939Dcm_DtcHandlerDemSemaphoreRelease(&pDM35State->HasDemAccess);

    /* No need to send a NACK for because DM35 once requested, it is issued periodically. */
    /* NACK would be needed for a single response DM which is not the case for DM35. */
    /* #30 Set processing state to not busy (reset DM1 processor). */
    pDM35State->ProcessingState = J1939DCM_MSG_STATE_WAIT;                                                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
  }
}
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM35Processor()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35Processor(
  J1939Dcm_NodeContextPtrType pNodeContext
  )
{
  /* #10 Assemble message. */
  J1939Dcm_DM35AssembleMessage(pNodeContext);

  /* #11 Transmit prepared DM35 message. */
  J1939Dcm_DM35Transmit(pNodeContext);

  /* #12 Handle assembly failure. */
  J1939Dcm_DM35HandleAssemblyFailure(&pNodeContext->DM35State);
}
#endif /* (J1939DCM_NEED_DM35_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleQueuedRequest()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleQueuedRequest(
  J1939Dcm_DMxQueueReadPtrType pDMxQueue,
  J1939Dcm_NodeContextPtrType pNodeContext
  )
{
  J1939Dcm_DMxStatePtrType pDMxState = &pNodeContext->DMxState;

  /* #20 If processsing state indicates waiting, Prepare for message processing or else send NACK. */
  if (J1939DCM_MSG_STATE_WAIT == pDMxState->ProcessingState)
  {
    pDMxState->ProcessingState   = J1939DCM_MSG_STATE_PREP_START;                                                                                    /* VCA_J1939DCM_FALSE_POSITIVE */
    pDMxState->ChannelHdl        = pDMxQueue->ChannelHdl;                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
    pDMxState->MessageHdl        = pDMxQueue->MessageHdl;                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
    pDMxState->ResponseDA        = pDMxQueue->ResponseDA;                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
  }
  else
  {
    /* Never send NACK globally. */
    if (pDMxQueue->ResponseDA != J1939DCM_ADDRESS_BROADCAST)
    {
      (void)J1939Rm_SendAck(                                                                                                                         /* VCA_J1939DCM_POINTER_FORWARD_NULL */
              J1939Dcm_Cfg_GetNodeUserId(pNodeContext->NodeHdl),                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
              J1939Dcm_Cfg_GetChannelId(pDMxState->ChannelHdl),                                                                                      /* VCA_J1939DCM_FALSE_POSITIVE */
              J1939Dcm_Cfg_GetMessagePGN(pDMxState->MessageHdl),                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
              NULL_PTR,
              J1939RM_ACK_CANNOT_RESPOND,
              pDMxState->ResponseDA,
              J1939DCM_PRIORITY_DEFAULT,
              FALSE
              );
    }
  }
}
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleQueuedTxConfirmation()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleQueuedTxConfirmation(
  J1939Dcm_DMxQueueReadPtrType pDMxQueue,                                                                                                            /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_DMxStatePtrType pDMxState
  )
{
  J1939Dcm_IgnoreUnusedArgument_CONST(pDMxQueue)                                                                                                     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #20 If a transmission of a diagnostic message was triggered in the previous task: */
  if (pDMxState->ProcessingState == J1939DCM_MSG_STATE_TXCONF)
  {
   /* #30 Set Processing state to not busy because TxConfirmation for all transmitting channels were received. */
    pDMxState->ProcessingState = J1939DCM_MSG_STATE_WAIT;                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
  } /* else: TxConfirmation no longer awaited (e.g. because of change to offline); ignore */

  /*
   * #40 Reset transmission because the TxHandler is still in use even if the confirmation is no longer expected.
   */
  J1939Dcm_NetTxHandlerReset();
}
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleQueuedFailedTxConfirmation()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleQueuedFailedTxConfirmation(
  J1939Dcm_DMxQueueReadPtrType pDMxQueue,                                                                                                            /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_DMxStatePtrType pDMxState
  )
{
  J1939Dcm_IgnoreUnusedArgument_CONST(pDMxQueue)                                                                                                     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #20 If a transmission of a diagnostic message was triggered in the previous task: */
  if (pDMxState->ProcessingState == J1939DCM_MSG_STATE_TXCONF)
  {
    /*
     * #30 Set the processing state to send acknowledgement because TxConfiramtion was failed
     *     and thus NACK is required.
     */
    pDMxState->ProcessingState = J1939DCM_MSG_STATE_SENDACK;                                                                                         /* VCA_J1939DCM_FALSE_POSITIVE */
  } /* else: TxConfirmation no longer awaited (e.g. because of change to offline); ignore */

  /*
   * #40 Reset transmission because the TxHandler is still in use even if the confirmation is no longer expected.
   */
  J1939Dcm_NetTxHandlerReset();
}
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleQueuedCommunicationStateChange()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleQueuedCommunicationStateChange(
  J1939Dcm_DMxQueueReadPtrType pDMxQueue,
  J1939Dcm_DMxStatePtrType pDMxState
  )
{
  /* #20 If the communication state went from offline to online: */
  if (pDMxQueue->StateChangeRequest == J1939DCM_STATE_ONLINE)
  {
    /* #30 If processing state indicates idle: */
    if (pDMxState->ProcessingState == J1939DCM_MSG_STATE_IDLE)
    {
      /* #40 Set processing state to not busy. */
      pDMxState->ProcessingState = J1939DCM_MSG_STATE_WAIT;                                                                                          /* VCA_J1939DCM_FALSE_POSITIVE */
    } /* else: node is already online; do not change internal state */
  }
  /* #50 Otherwise (If the communication state went from online to offline): */
  else
  {
    /* #60 Release DEM resources. */
    J1939Dcm_DtcHandlerDemSemaphoreRelease(&pDMxState->HasDemAccess);
    /* #70 Set processing state to idle. */
    pDMxState->ProcessingState = J1939DCM_MSG_STATE_IDLE;                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
  }
}
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleQueuedInfos()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleQueuedInfos(
  J1939Dcm_DMxQueueReadPtrType pDMxQueue,
  J1939Dcm_NodeContextPtrType pNodeContext
  )
{
  J1939Dcm_DMxStatePtrType pDMxState = &pNodeContext->DMxState;

  /* If a new diagnostic message is requested: */
  if (J1939Dcm_QueueBitOpTest(pDMxQueue, J1939DCM_QUEUE_REQ))
  {
    J1939Dcm_DMxHandleQueuedRequest(
      pDMxQueue,
      pNodeContext
      );
  }

  /* If a transmission of a diagnostic message is confirmed in the current task: */
  if (J1939Dcm_QueueBitOpTest(pDMxQueue, J1939DCM_QUEUE_TXCONF))
  {
    J1939Dcm_DMxHandleQueuedTxConfirmation(
      pDMxQueue,
      pDMxState
      );
  }

  /* If a transmission of a diagnostic message is failed in the current task: */
  if (J1939Dcm_QueueBitOpTest(pDMxQueue, J1939DCM_QUEUE_TXFAIL))
  {
    J1939Dcm_DMxHandleQueuedFailedTxConfirmation(
      pDMxQueue,
      pDMxState
      );
  }

  /* If the communication state was changed: */
  if (J1939Dcm_QueueBitOpTest(pDMxQueue, J1939DCM_QUEUE_STATE))
  {
    J1939Dcm_DMxHandleQueuedCommunicationStateChange(
      pDMxQueue,
      pDMxState
      );
  }
}
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleQueue()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleQueue(
  J1939Dcm_NodeContextPtrType pNodeContext
  )
{
  J1939Dcm_DMxQueuePtrType pDMxQueue = &pNodeContext->DMxQueue;
  /* #10 If any of the interrupt service routine functions updated the queue of events of a diagnostic message: */
  if (pDMxQueue->RequestPending != J1939DCM_QUEUE_EMPTY)
  {
    J1939Dcm_DMxQueueType lTmpQueueData;

    /*
     * #20 Enter critical section
     *     (Reason: protect data consistency of the queue of events against request manager interruptions).
     */
    J1939Dcm_EnterCritical();

    /* #30 Copy the queue of events into a local parameter and clear the queue of events. */
    lTmpQueueData.ChannelHdl         = pDMxQueue->ChannelHdl;
    lTmpQueueData.MessageHdl         = pDMxQueue->MessageHdl;
    lTmpQueueData.ResponseDA         = pDMxQueue->ResponseDA;
    lTmpQueueData.StateChangeRequest = pDMxQueue->StateChangeRequest;
    lTmpQueueData.RequestPending     = pDMxQueue->RequestPending;

    J1939Dcm_QueueBitOPClrAll(pDMxQueue);                                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */

    /* #40 Leave critical section. */
    J1939Dcm_ExitCritical();

    /* #50 Handle DMx queued information. */
    J1939Dcm_DMxHandleQueuedInfos(
      &lTmpQueueData,
      pNodeContext
      );
  }
}
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxTask()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxTask(
  void
  )
{
  J1939Dcm_NodeHdlOptType    lNodeHdl;

  /* #10 Iterate over the defined nodes because the queue of events of a diagnostic message is node dependent. */
  for (lNodeHdl = 0u; lNodeHdl < J1939Dcm_GetSizeOfCfg_NodeTable(); ++lNodeHdl)
  {
    J1939Dcm_NodeContextPtrType pNodeContext = &J1939Dcm_DiagContext.NodeContext[lNodeHdl];                                                          /* VCA_J1939DCM_VERIFIED_NODE_ACCESS */

    /* #20 Handle queue. */
    J1939Dcm_DMxHandleQueue(pNodeContext);

    /* #30 If processing state indicates busy: (If a new DM is requested in the current task
                                            Or If a DM processing has not been completed in the previous task
                                            Or If a DM transmission was failed in the current task) */
    if (pNodeContext->DMxState.ProcessingState > J1939DCM_MSG_STATE_WAIT)
    {
      /* #40 Trigger the processing of the diagnostic message. */
      J1939Dcm_DMxProcessor(pNodeContext);
    } /* end: state > J1939DCM_MSG_STATE_WAIT */
  }
}
#endif /* (J1939DCM_NEED_DMX_PROCESSOR == STD_ON) */

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxPrearrangeAssembly()
 **********************************************************************************************************************/
/*!
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
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxPrearrangeAssembly(
  J1939Dcm_NodeContextPtrType pNodeContext,
  uint8_least diagMessage
  )
{
# if ((J1939DCM_DM2_SUPPORT == STD_ON) || \
     (J1939DCM_DM27_SUPPORT == STD_ON) || \
     (J1939DCM_DM53_SUPPORT == STD_ON) || \
     (J1939DCM_DM54_SUPPORT == STD_ON))
  J1939Dcm_FilterHandlerType  lFilterHandler;
# endif

# if (J1939DCM_NEED_CLEAR_HANDLER == STD_ON)
  J1939Dcm_ClearHandlerPtrType pClearHandler = &J1939Dcm_DiagContext.CommonContext.ClearHandlerState;
# endif

  J1939Dcm_DMxStatePtrType pDMxState = &pNodeContext->DMxState;
  /*
   * #10 Process the requested DM:
   *     In case of DM02: Update the local DTC filter according to DM02 requirements. Trigger read Dtc Handler.
   *     In case of DM03: Update the state of the clear handler according to DM03 requirements.
   *                      Set the processing state to clear DTCs.
   *     In case of DM04: Trigger freeze frame handler.
   *     In case of DM05: Trigger readiness 1 handler.
   *     In case of DM11: Update the state of the clear handler according to DM11 requirements.
   *                      Set the processing state to clear DTCs.
   *     In case of DM24: Trigger SPN handler. Set the processing state to trigger transmission of message.
   *     In case of DM25: Trigger freeze frame handler.
   *     In case of DM27: Update local DTC filter according to DM27 requirements. Trigger read Dtc Handler.
   *     In case of DM31: Trigger status lamp handler. Set the processing state to get DTC with lamp status.
   *     In case of DM53: Update local DTC filter according to DM53 requirements. Trigger read Dtc Handler.
   *     In case of DM54: Update local DTC filter according to DM54 requirements. Trigger read Dtc Handler.
   *     In case of DM55: Update the state of the clear handler according to DM55 requirements.
   *                      Set the processing state to clear DTCs.
   *     Otherwise: Set the processing state to send acknowledgement according to J1939-21.
   */

  switch (diagMessage)
  {
# if (J1939DCM_DM2_SUPPORT == STD_ON)
    case J1939DCM_DM2:
      lFilterHandler.StatusFilter = DEM_J1939DTC_PREVIOUSLY_ACTIVE;
      lFilterHandler.DTCKind = DEM_DTC_KIND_ALL_DTCS;
      lFilterHandler.DTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
      lFilterHandler.FiltredNode = pNodeContext->NodeHdl;

      J1939Dcm_DtcHandlerSetDtcFilter(
        &pDMxState->ProcessingState,
        &pDMxState->BufferContext,
        &lFilterHandler
        );
      break;
# endif

# if (J1939DCM_DM3_SUPPORT == STD_ON)
    case J1939DCM_DM3:
      pDMxState->ProcessingState = J1939DCM_MSG_STATE_CLEAR;                                                                                         /* VCA_J1939DCM_FALSE_POSITIVE */
      pClearHandler->ClearFilter = DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE;
      pClearHandler->ClearNode = pNodeContext->NodeHdl;
      pClearHandler->DTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
      break;
# endif

# if (J1939DCM_DM4_SUPPORT == STD_ON)
    case J1939DCM_DM4:

      J1939Dcm_DtcHandlerSetFFFilter(
        &pDMxState->ProcessingState,
        &pDMxState->BufferContext,
        DEM_J1939DCM_FREEZEFRAME,
        pNodeContext->NodeHdl
        );
      break;
# endif

# if (J1939DCM_DM5_SUPPORT == STD_ON)
    case J1939DCM_DM5:
      pDMxState->ProcessingState = J1939DCM_MSG_STATE_READINESS;                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
      J1939Dcm_DtcHandlerStateInit(&J1939Dcm_DiagContext.CommonContext.DtcHandlerState, &pDMxState->BufferContext);
      break;
# endif

# if (J1939DCM_DM11_SUPPORT == STD_ON)
    case J1939DCM_DM11:
      pDMxState->ProcessingState = J1939DCM_MSG_STATE_CLEAR;                                                                                         /* VCA_J1939DCM_FALSE_POSITIVE */
      pClearHandler->ClearFilter = DEM_J1939DTC_CLEAR_ACTIVE;
      pClearHandler->ClearNode = pNodeContext->NodeHdl;
      pClearHandler->DTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
      break;
# endif

# if (J1939DCM_DM24_SUPPORT == STD_ON)
    case J1939DCM_DM24:
      J1939Dcm_DtcHandlerGetSupportedSPNs(
        &pDMxState->BufferContext,
        pNodeContext->NodeHdl
        );
      pDMxState->ProcessingState = J1939DCM_MSG_STATE_TX;                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
      break;
# endif

# if (J1939DCM_DM25_SUPPORT == STD_ON)
    case J1939DCM_DM25:

      J1939Dcm_DtcHandlerSetFFFilter(
        &pDMxState->ProcessingState,
        &pDMxState->BufferContext,
        DEM_J1939DCM_EXPANDED_FREEZEFRAME,
        pNodeContext->NodeHdl
        );
      break;
# endif

# if (J1939DCM_DM27_SUPPORT == STD_ON)
    case J1939DCM_DM27:
      lFilterHandler.StatusFilter = DEM_J1939DTC_PENDING;
      lFilterHandler.DTCKind = DEM_DTC_KIND_ALL_DTCS;
      lFilterHandler.DTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
      lFilterHandler.FiltredNode = pNodeContext->NodeHdl;

      J1939Dcm_DtcHandlerSetDtcFilter(
        &pDMxState->ProcessingState,
        &pDMxState->BufferContext,
        &lFilterHandler
        );
      break;
# endif

# if (J1939DCM_DM31_SUPPORT == STD_ON)
    case J1939DCM_DM31:
      J1939Dcm_DtcHandlerSetLampFilter(
        &pDMxState->BufferContext,
        pNodeContext->NodeHdl
        );
      pDMxState->ProcessingState = J1939DCM_MSG_STATE_PREP_LAMPDTC;                                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */
      break;
# endif

# if (J1939DCM_DM53_SUPPORT == STD_ON)
    case J1939DCM_DM53:
      lFilterHandler.StatusFilter = DEM_J1939DTC_ACTIVE;
      lFilterHandler.DTCKind = DEM_DTC_KIND_ALL_DTCS;
      lFilterHandler.DTCOrigin = DEM_DTC_ORIGIN_SECONDARY_MEMORY;
      lFilterHandler.FiltredNode = pNodeContext->NodeHdl;

      J1939Dcm_DtcHandlerSetDtcFilter(
        &pDMxState->ProcessingState,
        &pDMxState->BufferContext,
        &lFilterHandler
        );
      break;
# endif

# if (J1939DCM_DM54_SUPPORT == STD_ON)
    case J1939DCM_DM54:
      lFilterHandler.StatusFilter = DEM_J1939DTC_PREVIOUSLY_ACTIVE;
      lFilterHandler.DTCKind = DEM_DTC_KIND_ALL_DTCS;
      lFilterHandler.DTCOrigin = DEM_DTC_ORIGIN_SECONDARY_MEMORY;
      lFilterHandler.FiltredNode = pNodeContext->NodeHdl;

      J1939Dcm_DtcHandlerSetDtcFilter(
        &pDMxState->ProcessingState,
        &pDMxState->BufferContext,
        &lFilterHandler
        );
      break;
# endif

# if (J1939DCM_DM55_SUPPORT == STD_ON)
    case J1939DCM_DM55:
      pDMxState->ProcessingState = J1939DCM_MSG_STATE_CLEAR;                                                                                         /* VCA_J1939DCM_FALSE_POSITIVE */
      pClearHandler->ClearFilter = DEM_J1939DTC_CLEAR_ACTIVE_AND_PREVIOUSLY_ACTIVE;
      pClearHandler->ClearNode = pNodeContext->NodeHdl;
      pClearHandler->DTCOrigin = DEM_DTC_ORIGIN_SECONDARY_MEMORY;
      break;
# endif

    default:
      /*
       * [J1939-21] A response is always required from the specified destination(not global)
       * even if it is a NACK indicating that the particular PGN value is not supported.
       */
      pDMxState->ProcessingState = J1939DCM_MSG_STATE_SENDACK;                                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */
      break;
  }
}                                                                                                                                                    /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxTriggerAssembly()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxTriggerAssembly(
  J1939Dcm_NodeContextPtrType pNodeContext,
  CONSTP2VAR(J1939Rm_AckCode, AUTOMATIC, J1939DCM_INTERNAL_DATA) pAcknowledge                                                                        /* PRQA S 3206, 3673 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  J1939Dcm_DMxStatePtrType pDMxState = &pNodeContext->DMxState;

  J1939Dcm_IgnoreUnusedArgument_CONST(pAcknowledge)                                                                                                  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #20 If supported any DM that needs SPN: */
# if (J1939DCM_NEED_DTC_HANDLER_SPN == STD_ON)
  /* #25 Get matching DTCs, if the processing state is set to get DTCs. */
  if (pDMxState->ProcessingState == J1939DCM_MSG_STATE_PREP_DTCS)
  {
    /* Start adding the DTCs to the message buffer. */
    J1939Dcm_DtcHandlerGetDTCs(
      &pDMxState->ProcessingState,
      J1939DCM_DM_MAX_DTCS,
      pNodeContext->NodeHdl
      );
  }
# endif

  /* #30 If DM31 is supported: */
# if (J1939DCM_NEED_DTC_HANDLER_LAMP == STD_ON)
  /* #35 Get DTCs with lamp status, if the processing state is set to get lamp status. */
  if (pDMxState->ProcessingState == J1939DCM_MSG_STATE_PREP_LAMPDTC)
  {
    /* Start adding lamp status in the message buffer. */
    J1939Dcm_DtcHandlerGetLampDTCs(
      &pDMxState->ProcessingState,
      pNodeContext->NodeHdl
      );
  }
# endif

  /* #40 If supported any DM that needs freeze frame: */
# if (J1939DCM_NEED_DTC_HANDLER_FF == STD_ON)
  /* #45 Get freeze frames, if the processing state is set to get freeze frames. */
  if (pDMxState->ProcessingState == J1939DCM_MSG_STATE_PREP_FF)
  {
    /* Start adding the freeze frames in the message buffer. */
    J1939Dcm_DtcHandlerGetFFs(
      &pDMxState->ProcessingState,
      pNodeContext->NodeHdl
      );
  }
# endif

  /* #50 If supported any DM that needs clear handler: */
# if (J1939DCM_NEED_CLEAR_HANDLER == STD_ON)
  /* #55 Clear DTCs and store locally the clear acknowledgement code, if the processing state is set to clear DTCs. */
  if (pDMxState->ProcessingState == J1939DCM_MSG_STATE_CLEAR)
  {
    *pAcknowledge = J1939Dcm_DMxClearHandler(&pDMxState->ProcessingState);
  }
# endif

# if (J1939DCM_NEED_DTC_HANDLER_OBD == STD_ON)
  /* #55 Clear DTCs and store locally the clear acknowledgement code, if the processing state is set to clear DTCs. */
  if (pDMxState->ProcessingState == J1939DCM_MSG_STATE_READINESS)
  {
    J1939Dcm_DtcHandlerGetReadiness(
      &pDMxState->ProcessingState,
      J1939DCM_DM5,
      pNodeContext->NodeHdl
      );
  }
# endif
}
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxTransmit()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxTransmit(
  J1939Dcm_NodeContextPtrType pNodeContext,
  uint8_least diagMessage
  )
{
  J1939Dcm_DMxStatePtrType pDMxState = &pNodeContext->DMxState;
  /* #10 If the processing state indicates that the DM is ready for transmission: */
  if (pDMxState->ProcessingState == J1939DCM_MSG_STATE_TX)
  {
    Std_ReturnType TxResult;

    /* #20 Release DEM semaphore. */
    J1939Dcm_DtcHandlerDemSemaphoreRelease(&pDMxState->HasDemAccess);

    /* #30 Prepare for transmission. */
    TxResult = J1939Dcm_NetTxHandlerPrepare(
                 &pDMxState->BufferContext,
                 diagMessage,
                 pNodeContext->NodeHdl,
                 pDMxState->ResponseDA,
                 J1939Dcm_Cfg_GetPeerTxPduMetaDataLength(pNodeContext->NodeHdl, pDMxState->MessageHdl)                                               /* VCA_J1939DCM_FALSE_POSITIVE */
                 );

    /* #50 If preparation for transmission was succeeded: */
    if (TxResult == E_OK)
    {
      /* #60 Set processing state to wait for TxConfirmation. */
      pDMxState->ProcessingState = J1939DCM_MSG_STATE_TXCONF;                                                                                        /* VCA_J1939DCM_FALSE_POSITIVE */

      /* #70 Trigger transmission. */
      TxResult = J1939Dcm_NetTxHandlerTransmit(
                   J1939Dcm_Cfg_GetPeerTxPdu(pNodeContext->NodeHdl, pDMxState->MessageHdl),                                                          /* PRQA S 2986 */ /* MD_J1939Dcm_Rule2.2_2986 */ /* VCA_J1939DCM_FALSE_POSITIVE */
                   pDMxState->ChannelHdl
                   );

      /* #80 If triggering for transmission is failed: */
      if (TxResult != E_OK)
      {
        /* #90 Cancel transmission by resetting Txhandler. Update processing state to send acknowledgement. */
        J1939Dcm_NetTxHandlerReset();
        pDMxState->ProcessingState = J1939DCM_MSG_STATE_SENDACK;                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
      }
    } /* else: Transmit handler is busy; retry later */
  }
}                                                                                                                                                    /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxHandleAssemblyFailure()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxHandleAssemblyFailure(
  J1939Dcm_NodeContextPtrType pNodeContext,
  J1939Rm_AckCode acknowledgement
  )
{
  J1939Dcm_DMxStatePtrType pDMxState = &pNodeContext->DMxState;
  /* #10 If the processing state indicates sending acknowledgement: */
  if (pDMxState->ProcessingState == J1939DCM_MSG_STATE_SENDACK)
  {
    /* #20 Release DEM resources. */
    J1939Dcm_DtcHandlerDemSemaphoreRelease(&pDMxState->HasDemAccess);

    /* #30 If the source address of the requested message is specific: */
    if (pDMxState->ResponseDA != J1939DCM_ADDRESS_BROADCAST)
    {
      (void)J1939Rm_SendAck(                                                                                                                         /* VCA_J1939DCM_POINTER_FORWARD_NULL */
              J1939Dcm_Cfg_GetNodeUserId(pNodeContext->NodeHdl),                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
              J1939Dcm_Cfg_GetChannelId(pDMxState->ChannelHdl),                                                                                      /* VCA_J1939DCM_FALSE_POSITIVE */
              J1939Dcm_Cfg_GetMessagePGN(pDMxState->MessageHdl),                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
              NULL_PTR,
              acknowledgement,
              pDMxState->ResponseDA,
              J1939DCM_PRIORITY_DEFAULT,
              FALSE
              );
    }/* else: Skip NACK */

    /* #50 Reset DM processor. */
    pDMxState->ProcessingState = J1939DCM_MSG_STATE_WAIT;                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */

  } /* End J1939DCM_MSG_STATE_SENDACK */
}
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxAssembleMessage()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxAssembleMessage(
  J1939Dcm_NodeContextPtrType pNodeContext,
  CONSTP2VAR(J1939Rm_AckCode, AUTOMATIC, J1939DCM_INTERNAL_DATA) pAcknowledge,
  uint8_least diagMessage
  )
{
  J1939Dcm_DMxStatePtrType pDMxState = &pNodeContext->DMxState;
  /* #10 If the processing state indicates message preparation start (a new request was received): */
  if (pDMxState->ProcessingState == J1939DCM_MSG_STATE_PREP_START)
  {
    /* #20 Get a lock on DEM resources in order to import the required data from DEM for the incoming DM request. */
    J1939Dcm_DtcHandlerDemSemaphoreLock(&pDMxState->HasDemAccess);
    /* #30 If a lock on DEM resources is successfully obtained: */
    if (pDMxState->HasDemAccess == TRUE )
    {
      /* #40 Prearrange assembly. */
      J1939Dcm_DMxPrearrangeAssembly(
        pNodeContext,
        diagMessage
        );
    }
    /* #50 Otherwise: */
    else
    {
      /*
       * #60 Skip processing because DEM is currently in use
       *     (set processing state to send acknowledgement with code: cannot respond).
       */
      pDMxState->ProcessingState = J1939DCM_MSG_STATE_SENDACK;                                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */
      *pAcknowledge = J1939RM_ACK_CANNOT_RESPOND;
    }
  }

  /* #70 Assemble message. */
  J1939Dcm_DMxTriggerAssembly(
    pNodeContext,
    pAcknowledge
    );
}
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DMxProcessor()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxProcessor(
  J1939Dcm_NodeContextPtrType pNodeContext
  )
{
  uint8_least     lDiagnosticMessage;
  J1939Rm_AckCode lAcknowledge;

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  if(pNodeContext->DMxState.MessageHdl >= J1939Dcm_Cfg_GetMessageTableSize())
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_MAINFUNCTION,
      J1939DCM_E_PARAM_CONFIG
      )
  }
  else
# endif
  {
    lDiagnosticMessage = J1939Dcm_Cfg_GetMessageDM(pNodeContext->DMxState.MessageHdl);                                                               /* VCA_J1939DCM_FALSE_POSITIVE */

    /* Default acknowledge code in case anything fails. */
    lAcknowledge = J1939RM_ACK_NEGATIVE;

    /* --- Start DM processing --- */
    /* #10 Assemble message. */
    J1939Dcm_DMxAssembleMessage(
      pNodeContext,
      &lAcknowledge,
      lDiagnosticMessage
      );

    /* #20 Transmit message. */
    J1939Dcm_DMxTransmit(
      pNodeContext,
      lDiagnosticMessage
      );

    /* #30 Handle assembly failure. */
    J1939Dcm_DMxHandleAssemblyFailure(
      pNodeContext,
      lAcknowledge
      );
  }
}
#endif /* (J1939DCM_NEED_DMX_PROCESSOR == STD_ON) */

/***********************************************************************************************************************
 * J1939Dcm_NetTxHandlerTask()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_NetTxHandlerTask(
  void
  )
{
  J1939Dcm_NodeHdlType      lNodeHdl;
  uint8_least               lDiagMessage;
  J1939Dcm_TxHandlerPtrType pTxHandler = &J1939Dcm_DiagContext.CommonContext.TxHandlerState;

  /* #10 Assume the current transmitted diagnostic message is confirmed. */
  lDiagMessage = J1939DCM_DM_UNDEF;                                                                                                                  /* PRQA S 2982 */ /* MD_J1939Dcm_Rule2.2_2982 */
  lNodeHdl = J1939DCM_INVALID_NODE_HDL;                                                                                                              /* PRQA S 2982 */ /* MD_J1939Dcm_Rule2.2_2982 */

  /*
   * #11 Enter critical section
   * (Reason: protect data consistency of the transmission handler state against a new confirmation).
   */
  J1939Dcm_EnterCritical();

  /* #12 If the transmission timer has not been expired: */
  if (pTxHandler->TxTimer != 0u)
  {
    /* #13 Decrement the timer. */
    pTxHandler->TxTimer--;

    /* #14 If the timer has been expired: */
    if (pTxHandler->TxTimer == 0u)
    {
      /* #15 Register whether the current transmission is confirmed. */
      lNodeHdl = pTxHandler->NodeHdl;
      lDiagMessage = pTxHandler->DM;
    }
  }

  /* #16 Leave critical section. */
  J1939Dcm_ExitCritical();

  /* #17 If the current transmission has not been confirmed while the transmission timer has been already expired: */
  if(lNodeHdl != J1939DCM_INVALID_NODE_HDL)                                                                                                          /* PRQA S 2995 */ /* MD_J1939Dcm_ConstExpr */
  {
    /* #18 Indicate failed transmission. */
    J1939Dcm_NetTxHandlerConfirm(
      lNodeHdl,
      lDiagMessage,
      E_NOT_OK,
      J1939DCM_API_MAINFUNCTION
      );
  }
}

#if (J1939DCM_NEED_DTC_HANDLER_SPN == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DtcHandlerSetDtcFilter()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerSetDtcFilter(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState,
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  P2CONST(J1939Dcm_FilterHandlerType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pFilterHandler
  )
{
  Std_ReturnType                                lFilterReturn;
  Dem_J1939DcmLampStatusType                    lLampStatus;
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState = &J1939Dcm_DiagContext.CommonContext.DtcHandlerState;

  /* #10 Set up DEM DTC interface (Update DTC handler state). */
  J1939Dcm_DtcHandlerStateInit(pDtcHandlerState, pBufferContext);

  /* #11 Set filter and obtain the lamp status. */
  lFilterReturn = Dem_J1939DcmSetDTCFilter(                                                                                                          /* VCA_J1939DCM_POINTER_FORWARD_LOCAL */
                    pFilterHandler->StatusFilter,
                    pFilterHandler->DTCKind,
                    pFilterHandler->DTCOrigin,
                    J1939Dcm_Cfg_GetNodeDemClientId(pFilterHandler->FiltredNode),                                                                    /* VCA_J1939DCM_FALSE_POSITIVE */
                    &lLampStatus
                    );

  /* #12 If the requested filter is accepted by DEM: */
  if (lFilterReturn == E_OK)
  {
    /* #13 Copy the lamp status to the buffer of the DTC handler state. */
    J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, lLampStatus.LampStatus);
    J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, lLampStatus.FlashLampStatus);
    /* #14 Prepare to retrive DTCs. */
    *pDMProcessorState = J1939DCM_MSG_STATE_PREP_DTCS;                                                                                               /* VCA_J1939DCM_FALSE_POSITIVE */
  }
  /* #15 Otherwise (if the filtering is failed): */
  else
  {
    /* #16 Reset the DM processor (set the processing state to send NACK). */
    *pDMProcessorState = J1939DCM_MSG_STATE_SENDACK;                                                                                                 /* VCA_J1939DCM_FALSE_POSITIVE */
  }
}
#endif /* (J1939DCM_NEED_DTC_HANDLER_SPN == STD_ON) */

#if (J1939DCM_NEED_DTC_HANDLER_LAMP == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DtcHandlerSetLampFilter()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerSetLampFilter(
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  J1939Dcm_NodeHdlType nodeHdl                                                                                                                       /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState = &J1939Dcm_DiagContext.CommonContext.DtcHandlerState;
  J1939Dcm_IgnoreUnusedArgument(nodeHdl)         /* parameter not used in single node configurations */                                              /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Set up DEM DTC interface (Update DTC handler state). */
  J1939Dcm_DtcHandlerStateInit(pDtcHandlerState, pBufferContext);

  /* #11 Initiate a sequence of obtaining DTC and the associated lamp status in DEM. */
  Dem_J1939DcmFirstDTCwithLampStatus(J1939Dcm_Cfg_GetNodeDemClientId(nodeHdl));                                                                      /* VCA_J1939DCM_FALSE_POSITIVE */
}
#endif /* (J1939DCM_NEED_DTC_HANDLER_LAMP == STD_ON) */

#if (J1939DCM_NEED_DTC_HANDLER_FF == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DtcHandlerSetFFFilter()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerSetFFFilter(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState,
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  Dem_J1939DcmSetFreezeFrameFilterType freezeFrameKind,
  J1939Dcm_NodeHdlType nodeHdl                                                                                                                       /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  Std_ReturnType  lFilterReturn;
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState = &J1939Dcm_DiagContext.CommonContext.DtcHandlerState;

  J1939Dcm_IgnoreUnusedArgument(nodeHdl)         /* parameter not used in single node configurations */                                              /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Set up DEM DTC interface (Update DTC handler state). */
  J1939Dcm_DtcHandlerStateInit(pDtcHandlerState, pBufferContext);

  /* #11 Set freeze frame filter. */
  lFilterReturn = Dem_J1939DcmSetFreezeFrameFilter(
                    freezeFrameKind,
                    J1939Dcm_Cfg_GetNodeDemClientId(nodeHdl)                                                                                         /* VCA_J1939DCM_FALSE_POSITIVE */
                    );

  /* #12 If the requested filter is accepted by DEM: */
  if (lFilterReturn == E_OK)
  {
    /* #13 Prepare to retrieve freeze frames. */
    *pDMProcessorState = J1939DCM_MSG_STATE_PREP_FF;                                                                                                 /* VCA_J1939DCM_FALSE_POSITIVE */
  }
  /* #14 Otherwise (if the requested filter is not accepted by DEM): */
  else
  {
    /* #15 Reset the DM processor (set the processing state to send NACK). */
    *pDMProcessorState = J1939DCM_MSG_STATE_SENDACK;                                                                                                 /* VCA_J1939DCM_FALSE_POSITIVE */
  }
}
#endif /* (J1939DCM_NEED_DTC_HANDLER_FF == STD_ON) */

#if (J1939DCM_NEED_DTC_HANDLER_SPN == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DtcHandlerGetDTCs()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerGetDTCs(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState,
  uint16_least maxNumDtcs,
  J1939Dcm_NodeHdlType nodeHdl                                                                                                                       /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  Std_ReturnType             lGetDtcResult;
  uint32                     lDTCNumber;
  uint8                      lOccurrenceCounter;
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState = &J1939Dcm_DiagContext.CommonContext.DtcHandlerState;

  J1939Dcm_IgnoreUnusedArgument(nodeHdl)                                                                                                             /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* #10 Iterate over filtered DTCs as long as: enough buffer is availabe,
                                                maximum number of allowed DTC per main function call is not reached,
                                                there are still more filtered DTCs to obtain,
                                                DEM is done with processing the filtered DTCs. */
  do
  {
    /* #11 Try to obtain a filtered DTC. */
    lGetDtcResult = Dem_J1939DcmGetNextFilteredDTC(                                                                                                  /* VCA_J1939DCM_POINTER_FORWARD_LOCAL */
                      &lDTCNumber,
                      &lOccurrenceCounter,
                      J1939Dcm_Cfg_GetNodeDemClientId(nodeHdl)                                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */
                      );

    switch (lGetDtcResult)
    {
      /* #12 In case of a DTC is available matches the filtering criteria: */
      case E_OK:
        /* #13 Add the filtered DTC to the buffer. */
        J1939Dcm_DtcHandlerProvideResDataAsU24(pDtcHandlerState, lDTCNumber);
        J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, lOccurrenceCounter);

        /* #14 Register the number of the filtered DTCs collected in this main function call. */
        pDtcHandlerState->NumDTCsInCycle++;
        /* #15 Register the number of the filtered DTCs collected for the next transmsission task. */
        pDtcHandlerState->NumDTCs++;

        /* #16 If there is a space for more filtered DTCs to add to the response before the next transmission task: */
        if (pDtcHandlerState->NumDTCs < maxNumDtcs)
        {
          /*
           * #17 If the number of filtered DTCs collected in this main function call exceeds the predetermined limit:
           */
          if (pDtcHandlerState->NumDTCsInCycle >= J1939DCM_MAX_DTCS_PER_CYCLE)
          {
            /*
             * #18 Indicate that the maximum number of collected DTCs in this cycle reached but there is
             *     more to collect in the next cycle.
             */
            /*
             * Do not change DM processor state to be able to collected more filtered DTC for the DM
             * response in the next main function call.
             */
            lGetDtcResult = DEM_PENDING;
            /* #19 Reset the number of the filtered DTC collected in this main function call. */
            pDtcHandlerState->NumDTCsInCycle = 0;
          }
        }
        /*
         * #20 Otherwise
         * (If there is no space for more filtered DTCs to add to the response before the next transmission task):
         */
        else
        {
          /* #21 Set processing state to trigger transmission of message. */
          *pDMProcessorState = J1939DCM_MSG_STATE_TX;                                                                                                /* VCA_J1939DCM_FALSE_POSITIVE */
          /*
           * #22 Indicate there are no more filtered DTCs to collect from DEM
           *     (Even though there could be more DTCs filtered by DEM but the DM response matured).
           */
          lGetDtcResult = DEM_NO_SUCH_ELEMENT;
        }
        break;

      /* #23 In case of DEM is not done with processing the filtered DTCs: */
      case DEM_PENDING:
        /* Do not change DM processor state and retry on next task cycle. */
        /* #24 Reset the number of the filtered DTC collected in this main function call. */
        pDtcHandlerState->NumDTCsInCycle = 0;
        break;

      /* #25 In case of there are no more filtered DTCs to collect from DEM: */
      case DEM_NO_SUCH_ELEMENT:
        /* #26 If there are no filtered DTCs have been prepared to be sent in the next transmission task: */
        if (pDtcHandlerState->NumDTCs == 0u)
        {
          /* #27 Set up default message [J1939-73]. */
          J1939Dcm_DtcHandlerProvideResDataAsU24(pDtcHandlerState, 0u);    /* Zero DTC */
          J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 0u);     /* Zero occurance number */
        }

        /* #28 Set processing state to trigger transmission of message. */
        *pDMProcessorState = J1939DCM_MSG_STATE_TX;                                                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */
        break;

      /* #29 In case of DEM is not capable of obtaining the filtered DTCs: */
      default:
        /* #30 Set processing state to send NAK. */
        *pDMProcessorState = J1939DCM_MSG_STATE_SENDACK;                                                                                             /* VCA_J1939DCM_FALSE_POSITIVE */
        break;
    }
  } while (E_OK == lGetDtcResult);
}                                                                                                                                                    /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (J1939DCM_NEED_DTC_HANDLER_SPN == STD_ON) */

#if (J1939DCM_NEED_DTC_HANDLER_LAMP == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DtcHandlerGetLampDTCs()
 **********************************************************************************************************************/
/*!
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
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerGetLampDTCs(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState,
  J1939Dcm_NodeHdlType nodeHdl                                                                                                                       /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  Std_ReturnType             lGetDtcResult;
  uint32                     lDTCNumber;
  uint8                      lOccurrenceCounter;
  Dem_J1939DcmLampStatusType lLampStatus;
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState = &J1939Dcm_DiagContext.CommonContext.DtcHandlerState;

  J1939Dcm_IgnoreUnusedArgument(nodeHdl)                                                                                                             /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* #10 Iterate over the filtered DTCs as long as: enough buffer is availabe,
                                                    maximum number of DTCs per main function call is not reached,
                                                    there are still more filtered DTCs to obtain,
                                                    DEM is done with processing the filtered DTCs. */
  do
  {
    /* #11 Try to obtain a filtered DTC and its assciated lamp status. */
    lGetDtcResult = Dem_J1939DcmGetNextDTCwithLampStatus(                                                                                            /* VCA_J1939DCM_POINTER_FORWARD_LOCAL */
                      &lLampStatus,
                      &lDTCNumber,
                      &lOccurrenceCounter,
                      J1939Dcm_Cfg_GetNodeDemClientId(nodeHdl)                                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */
                      );

    switch (lGetDtcResult)
    {
      /* #12 In case of a DTC is available matches the filtering criteria: */
      case E_OK:
        /* #13 Add the filtered DTC and its associated lamp status to the buffer. */
        J1939Dcm_DtcHandlerProvideResDataAsU24(pDtcHandlerState, lDTCNumber);
        J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, lOccurrenceCounter);
        J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, lLampStatus.LampStatus);
        J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, lLampStatus.FlashLampStatus);
        /* #14 Register the number of the filtered DTCs collected in this main function call. */
        pDtcHandlerState->NumDTCsInCycle++;
        /* #15 Register the number of the filtered DTCs collected for the next transmsission task. */
        pDtcHandlerState->NumDTCs++;

        /* #16 If the number of filtered DTCs collected in this main function call exceeds the predetermined limit: */
        if (pDtcHandlerState->NumDTCsInCycle >= J1939DCM_MAX_DTCS_PER_CYCLE)
        {
          /*
           * #17 Indicate that the maximum number of collected DTCs in this cycle reached but
           *     there is more to collect in the next cycle.
           */
          /*
           * Do not change DM processor state to be able to collected more filtered DTC for
           * the DM response in the next main function call.
           */
          lGetDtcResult = DEM_PENDING;
          /* #18 Reset the number of the filtered DTC collected in this main function call. */
          pDtcHandlerState->NumDTCsInCycle = 0;
        }
        break;

      /* #19 In case of DEM is not done with processing the filtered DTCs: */
      case DEM_PENDING:
        /* Do not change DM processor state and retry on next task cycle. */
        /* #20 Reset the number of the filtered DTC collected in this main function call. */
        pDtcHandlerState->NumDTCsInCycle = 0;
        break;

      /* #21 In case of there are no more filtered DTCs to collect from DEM: */
      case DEM_NO_SUCH_ELEMENT:
        /* #22 If there are no filtered DTCs have been prepared to be sent in the next transmission task: */
        if (pDtcHandlerState->NumDTCs == 0u)
        {
          /* #23 Set up default message [J1939-73]. */
          J1939Dcm_DtcHandlerProvideResDataAsU24(pDtcHandlerState, 0u);   /* Zero DTC */
          J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 0u);    /* Zero occurance number */
          J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 0u);    /* zero lamp status */
          J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 0xFF);  /* Default flash lamp status */
        }

        if (pDtcHandlerState->NumDTCs <= 1u)
        {
          /* one or no DTC, fill up last bytes and start transmission immediately */
          J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 0xFF);  /* Padding byte */
          J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 0xFF);  /* Padding byte */
        }

        /* #24 Set processing state to trigger transmission of message. */
        *pDMProcessorState = J1939DCM_MSG_STATE_TX;                                                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */
        break;

      /* #25 In case of DEM is not capable of obtaining the filtered DTCs and the associated lamp status: */
      default:
        /* #26 Notify DET: Something's wrong! Maybe buffer is too small? */
        J1939Dcm_DetAssertAlways(
          J1939DCM_API_MAINFUNCTION,
          J1939DCM_E_INVALID_STATE
          )
        /* #27 Set processing state to send NAK. */
        *pDMProcessorState = J1939DCM_MSG_STATE_SENDACK;                                                                                             /* VCA_J1939DCM_FALSE_POSITIVE */
        break;
    }
  } while (E_OK == lGetDtcResult);
}
#endif /* (J1939DCM_NEED_DTC_HANDLER_LAMP == STD_ON) */

#if (J1939DCM_DM24_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DtcHandlerGetSupportedSPNs()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerGetSupportedSPNs(
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  J1939Dcm_NodeHdlType nodeHdl                                                                                                                       /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  PduLengthType lDM24Length;
  PduLengthType lStartIndex;

  J1939Dcm_IgnoreUnusedArgument(nodeHdl)                                                                                                             /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /*
   * Calcuate the length of the DM24 Message.
   *   Each SPN configured in DaVinci configurator generated as four bytes in the SPN array.
   *   Each of those four bytes occupies an entry of the SPN array.
   *   The length of the SPN plus the SPN identity is 3 bytes. Therefore, the forth byte (high byte) is always zero.
   *   If the SPN identity is expanded FF, then it is configured by DEM.
   *   If the SPN identity is data stream, then it is configured by J1939Dcm.
   */
  lDM24Length = J1939Dcm_DM24GetLength(nodeHdl);                                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
  lStartIndex = J1939Dcm_GetCfg_SPNArrayStartIdxOfCfg_NodeTable(nodeHdl);                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */

  /* #10 Copy the SPN and its identity to the buffer (high byte first). */
  pBufferContext->Buffer.SduLength = J1939Dcm_UtiMemCopySafe(                                                                                        /* VCA_J1939DCM_FALSE_POSITIVE */
                                       &J1939Dcm_GetCfg_SPNArray(lStartIndex),                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */
                                       pBufferContext->Buffer.SduDataPtr,
                                       0,
                                       pBufferContext->AvailLen,
                                       lDM24Length);
}
#endif /* (J1939DCM_DM24_SUPPORT == STD_ON) */

#if (J1939DCM_NEED_DTC_HANDLER_FF == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DtcHandlerGetFFs()
 **********************************************************************************************************************/
/*!
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
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerGetFFs(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState,
  J1939Dcm_NodeHdlType nodeHdl                                                                                                                       /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  Std_ReturnType             lGetFFResult;
  uint32                     lDTCNumber;
  uint8                      lOccurenceCounter;
  uint8                      *lFreezeFramePtr;
  PduLengthType              lFreezeFrameBufferLength;
  uint8                      lFreezeFrameDataLength;
  J1939Dcm_DtcHandlerPtrType pDtcHandlerState = &J1939Dcm_DiagContext.CommonContext.DtcHandlerState;

  lDTCNumber = 0;
  lOccurenceCounter = 0;
  J1939Dcm_IgnoreUnusedArgument(nodeHdl)                                                                                                             /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /*
   * #10 Iterate over filtered freeze frames as long as:
   *                           enough buffer is available,
   *                           maximum number of freeze frames per main function call is not reached,
   *                           there are still more filtered freeze frames to obtain,
   *                           DEM is done with processing the filtered freeze frames.
   */
  do
  {
    /* #11 Determine the position in the buffer where the next freeze frame will be stored. */
    lFreezeFramePtr = &pDtcHandlerState->MessageData->Buffer.SduDataPtr[pDtcHandlerState->MessageData->Buffer.SduLength];
    /* #12 Calculate the available length in the buffer for the next freeze frame. */
    lFreezeFrameBufferLength = (PduLengthType)J1939DCM_BUFFERSIZE_COMMON - pDtcHandlerState->MessageData->Buffer.SduLength;
    /*
     * Length of one single freeze frame with its associated DTC is limited to a uint8 by SAE / AR DEM Spec
     * 5 bytes for freeze frame header (1 byte freeze frame length + 4 bytes DTC) have to be subtracted
     * from the maximum capacity of a uint8 to express the maximum size of one freeze frame.
     * Thus, DEM is limited to write 251 bytes as a maximum size for a one freeze frame.
     */

     /*
      * #13 If the avilable length in the buffer for the next freeze frame is greater
      *     than the maximum size of one freeze frame:
      */
# if (J1939DCM_MAX_FF_SIZE_CONFORM == STD_ON)
    if (lFreezeFrameBufferLength > (J1939DCM_FF_MAX_DATA_LENGTH + J1939DCM_FF_HEADER_LENGTH))
    {
      /* #14 Limit the buffer size for DEM to max possible data length (maximum size of one freeze frame). */
      lFreezeFrameDataLength = J1939DCM_FF_MAX_DATA_LENGTH;
    }
    /* #16 If the available buffer length is greater than the header size of the next freeze frame: */
    else
# endif
    if (lFreezeFrameBufferLength > J1939DCM_FF_HEADER_LENGTH)
    {
      /* #17 Calculate the allowed data length for DEM, considering that the header is added as well. */
      lFreezeFrameDataLength = (uint8)(lFreezeFrameBufferLength - J1939DCM_FF_HEADER_LENGTH);
    }
    /* #18 Otherwise (if the available buffer length is not greater than the header size of the next freeze frame): */
    else
    {
      /* #19 Indicate a buffer inavailability. */
      lFreezeFrameDataLength = 0;
    }

    /* #20 Try to obtain the next freeze frame that matches the filtering criteria. */
    /* If successful, the occurance counter and the freeze frame will be added by DEM to the DM buffer. */
    lGetFFResult = Dem_J1939DcmGetNextFreezeFrame(                                                                                                   /* VCA_J1939DCM_DEM_GET_NEXT_FF */
                     &lDTCNumber,
                     &lOccurenceCounter,
                     &lFreezeFramePtr[J1939DCM_FF_DATA_OFFSET],
                     &lFreezeFrameDataLength,
                     J1939Dcm_Cfg_GetNodeDemClientId(nodeHdl)                                                                                        /* VCA_J1939DCM_FALSE_POSITIVE */
                     );

    switch (lGetFFResult)
    {
      /* #21 In case of a freeze frame is available matches the filtering criteria: */
      case E_OK:
        /*
         * #22 Add DTC number and freeze frame length to the buffer
         *     (freeze frame data and occurance counter have been added to the buffer by DEM).
         */
        J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, (uint8)(J1939DCM_FF_SPN_OCC_LENGTH + lFreezeFrameDataLength));
        J1939Dcm_DtcHandlerProvideResDataAsU24(pDtcHandlerState, lDTCNumber);
        J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, lOccurenceCounter);

        /* #23 Update the length of the occupied part of the DM buffer. */
        J1939Dcm_DtcHandlerCommitResData(pDtcHandlerState, (PduLengthType)lFreezeFrameDataLength);

        /* #24 Register the number of the filtered freeze frames collected in this main function call. */
        pDtcHandlerState->NumDTCsInCycle++;
        /* #25 Register the number of the filtered freeze frames collected for the next transmsission task. */
        pDtcHandlerState->NumDTCs++;

        /*#26 If the number of the filtered freeze frames collected in this main function call exceeds the predetermined limit: */
        if (pDtcHandlerState->NumDTCsInCycle >= J1939DCM_MAX_FF_PER_CYCLE)
        {
          /*
           * Do not change DM processor state to be able to collected more filtered freeze frames
           * for the DM response in the next main function call.
           */

          /*
           * #27 Indicate that the maximum number of collected freeze frames in this cycle
           *     reached but there is more to collect in the next cycle.
           */
          lGetFFResult = DEM_PENDING;
          /* #28 Reset the number of the filtered freeze frames collected in this main function call. */
          pDtcHandlerState->NumDTCsInCycle = 0;
        }
        break;

      /* #29 In case of DEM is not done with processing the filtered freeze frames: */
      case DEM_PENDING:
        /* Do not change DM processor state and retry on next task cycle. */
        /* #30 Reset the number of the filtered freeze frames collected in this main function call. */
        pDtcHandlerState->NumDTCsInCycle = 0;
        break;

      /* #31 In case of there are no more filtered freeze frames to collect from DEM: */
      case DEM_NO_SUCH_ELEMENT:
        /* finished; continue with transmission */
        /* #32 If there are no filtered freeze frames have been prepared to be sent in the next transmission task: */
        if (pDtcHandlerState->NumDTCs == 0u)
        {
          /* #33 Set up default message [J1939-73]. */
          J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 0u);    /* Zero length */
          J1939Dcm_DtcHandlerProvideResDataAsU24(pDtcHandlerState, 0u);   /* Zero DTC */
          J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 0u);    /* Zero occurance number */
        }

        /* #34 Set processing state to trigger transmission of message. */
        *pDMProcessorState = J1939DCM_MSG_STATE_TX;                                                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */
        break;

      /* #35 In case of DEM is not capable of obtaining the filtered freeze frames for any other reasons: */
      /* An explicit case for buffer too small is not required as this API is used by DM24. */ /* SWS_J1939Dcm_00165 */
      default:
        /* #36 Notify DET: Something's wrong! Maybe buffer is too small? */
        J1939Dcm_DetAssertAlways(J1939DCM_API_MAINFUNCTION, J1939DCM_E_INVALID_STATE)
        /* #37 Set processing state to send NAK. */
        *pDMProcessorState = J1939DCM_MSG_STATE_SENDACK;                                                                                             /* VCA_J1939DCM_FALSE_POSITIVE */
        break;
    }
  } while (E_OK == lGetFFResult);
}
#endif /* (J1939DCM_NEED_DTC_HANDLER_FF == STD_ON) */

#if (J1939DCM_NEED_DTC_HANDLER_OBD == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DtcHandlerGetReadiness()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_DtcHandlerGetReadiness(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState,
  uint8 diagMessage,                                                                                                                                 /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_NodeHdlType nodeHdl                                                                                                                       /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  Std_ReturnType                       lReadinessReturn;
  Dem_J1939DcmDiagnosticReadiness1Type lReadinessData;

  /*
   * Currently only DM5 is supported;
   * other readiness messages, which will then be read from DEM, may be added in the future
   */
  J1939Dcm_IgnoreUnusedArgument(diagMessage)                                                                                                         /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(nodeHdl)                                                                                                             /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /*
   * Currently, only the count of the active and peviously active DTCs is available
   * for the Readiness 1 DM (non-OBD system).
   */

  /* #10 Try to obtain the Readiness 1 data. */
  lReadinessReturn = Dem_J1939DcmReadDiagnosticReadiness1(                                                                                           /* VCA_J1939DCM_POINTER_FORWARD_LOCAL */
                       &lReadinessData,
                       J1939Dcm_Cfg_GetNodeDemClientId(nodeHdl)                                                                                      /* VCA_J1939DCM_FALSE_POSITIVE */
                       );

  /* #11 If the Readiness 1 data was successfully collected from DEM: */
  if (lReadinessReturn == E_OK)
  {
    J1939Dcm_DtcHandlerPtrType pDtcHandlerState = &J1939Dcm_DiagContext.CommonContext.DtcHandlerState;                                               /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */

    J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, lReadinessData.ActiveTroubleCodes);                     /* Active DTCs */
    J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, lReadinessData.PreviouslyActiveDiagnosticTroubleCodes); /* Previously active DTCs */
    J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 5u);                                                    /* OBD compliance; 5 = no OBD */
    J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 0u);                                                    /* Continuously Monitored Systems Support/Status; 0 = not supported */
    J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 0u);                                                    /* Non-continuously Monitored Systems Support; 0 = not supported */
    J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 0u);                                                    /* Non-continuously Monitored Systems Support; 0 = not supported */
    J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 0u);                                                    /* Non-continuously Monitored Systems Status; 0 = not supported  */
    J1939Dcm_DtcHandlerProvideResDataAsU8(pDtcHandlerState, 0u);                                                    /* Non-continuously Monitored Systems Status; 0 = not supported  */

    /* #13 Set processing state to trigger transmission of message. */
    *pDMProcessorState = J1939DCM_MSG_STATE_TX;                                                                                                      /* VCA_J1939DCM_FALSE_POSITIVE */
  }

  /* #14 Otherwise (if it is failed to collect the Readiness 1 data from DEM): */
  else
  {
    /* #15 Set processing state to send NAK (reset DM processor). */
    *pDMProcessorState = J1939DCM_MSG_STATE_SENDACK;                                                                                                 /* VCA_J1939DCM_FALSE_POSITIVE */
  }
}
#endif /* (J1939DCM_NEED_DTC_HANDLER_OBD == STD_ON) */

#if (J1939DCM_NEED_CLEAR_HANDLER == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DMxClearHandler()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(J1939Rm_AckCode, J1939DCM_CODE)
J1939Dcm_DMxClearHandler(
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pDMProcessorState
  )
{
  Std_ReturnType                   lResult;
  J1939Rm_AckCode                  lAckCode;
  J1939Dcm_ClearHandlerReadPtrType pClearHandler = &J1939Dcm_DiagContext.CommonContext.ClearHandlerState;

  /* #10 Request clearing DTC from DEM. */
  lResult = Dem_J1939DcmClearDTC(
              pClearHandler->ClearFilter,
              pClearHandler->DTCOrigin,
              J1939Dcm_Cfg_GetNodeDemClientId(pClearHandler->ClearNode)                                                                              /* VCA_J1939DCM_FALSE_POSITIVE */
              );

  /* #11 Update the processing state and set the acknowledgement code based on the return value of the clear handler.*/

  /*
         ClearResult          | ProcessorState                 | AckCode
        ======================+================================+======================
         E_OK                 | J1939DCM_MSG_STATE_SENDACK     | J1939RM_ACK_POSITIVE
         DEM_PENDING          | J1939DCM_MSG_STATE_CLEAR       | J1939RM_ACK_POSITIVE
         Other                | J1939DCM_MSG_STATE_SENDACK     | J1939RM_ACK_NEGATIVE
  */
  switch (lResult)
  {
    case E_OK:
      *pDMProcessorState = J1939DCM_MSG_STATE_SENDACK;                                                                                               /* VCA_J1939DCM_FALSE_POSITIVE */
      lAckCode = J1939RM_ACK_POSITIVE;
      break;

    case DEM_PENDING:
      *pDMProcessorState = J1939DCM_MSG_STATE_CLEAR;                                                                                                 /* VCA_J1939DCM_FALSE_POSITIVE */
      lAckCode = J1939RM_ACK_POSITIVE;
      break;

    default:
      *pDMProcessorState = J1939DCM_MSG_STATE_SENDACK;                                                                                               /* VCA_J1939DCM_FALSE_POSITIVE */
      lAckCode = J1939RM_ACK_NEGATIVE;
      break;
  }

  /* #12 Return the acknowledgement code. */
  return lAckCode;
}
#endif /* (J1939DCM_NEED_CLEAR_HANDLER == STD_ON) */

/***********************************************************************************************************************
 * J1939Dcm_NetTxHandlerPrepare()
 **********************************************************************************************************************/
/*!
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
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(Std_ReturnType, J1939DCM_CODE)
J1939Dcm_NetTxHandlerPrepare(
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  uint8_least diagMessage,
  J1939Dcm_NodeHdlType nodeHdl,
  uint8_least responseAddress,
  uint8 metaDataLength
  )
{
  J1939Dcm_TxHandlerPtrType  pTxHandler = &J1939Dcm_DiagContext.CommonContext.TxHandlerState;
  J1939Dcm_ChannelHdlOptType lChannelHdl;
  Std_ReturnType             lResult;
  /* #10 Assume unsuccessful transmission preparation. */
  /* In case of something went wrong! */
  lResult = E_NOT_OK;

  /*
   * #11 Enter critical section
   * (Reason: protect data consistency of the handler state during the transmission preparation of an DM).
   */
  J1939Dcm_EnterCritical();

  if (NULL_PTR == pTxHandler->BufferContext)
  {
    /* #13 Update the transmission handler state with the meta data, the payload, the DM, and the node handle. */
    pTxHandler->MetaData[J1939DCM_METADATA_SA_OFFSET]   = J1939Dcm_Cfg_GetNodeAddress(nodeHdl);                                                      /* VCA_J1939DCM_FALSE_POSITIVE */
    pTxHandler->MetaData[J1939DCM_METADATA_DA_OFFSET]   = (uint8)responseAddress;
    /* PGN is filled in by CanIf therefore J1939Dcm can insert random data */
    pTxHandler->MetaData[J1939DCM_METADATA_PDUF_OFFSET] = 0x00u;
    /* Priority is static and can be filled in by J1939Dcm */
    pTxHandler->MetaData[J1939DCM_METADATA_PRIO_OFFSET] = J1939DCM_DEFAULT_PRIORITY;

    /* setup transmission */
    pTxHandler->BufferContext = pBufferContext;
    pTxHandler->DM            = (uint8)diagMessage;
    pTxHandler->NodeHdl       = nodeHdl;

    /* IF or TP? */
    /*
     * #14 If the incoming DM can be sent directly via the CAN interface
     * (message length is 8 bytes and only applicable for DM5, DM15, DM21, or DM26):
     */
    /* not yet supported DMs: (J1939DCM_DM21 == diagMessage) || (J1939DCM_DM26 == diagMessage) */
    if ((J1939DCM_DM5 == diagMessage) || (J1939DCM_DM15 == diagMessage))
    {
      /* for IF connections: meta data is part of SduLength and SduPointer */
      /* #15 Append the meta data to the payload. */
      J1939Dcm_UtiProvideMetaDataAsU8(pBufferContext, pTxHandler, metaDataLength, J1939DCM_METADATA_SA_OFFSET);
      J1939Dcm_UtiProvideMetaDataAsU8(pBufferContext, pTxHandler, metaDataLength, J1939DCM_METADATA_DA_OFFSET);
      J1939Dcm_UtiProvideMetaDataAsU8(pBufferContext, pTxHandler, metaDataLength, J1939DCM_METADATA_PDUF_OFFSET);
      J1939Dcm_UtiProvideMetaDataAsU8(pBufferContext, pTxHandler, metaDataLength, J1939DCM_METADATA_PRIO_OFFSET);

      /* #17 Set the transmission path to send via CAN interface and reload the transmission timer. */
      pTxHandler->TransmitPath = J1939DCM_TX_PATH_IF;
      pTxHandler->TxTimer      = J1939DCM_TXTIMEOUT;
    }
    /* #18 Otherwise (if the incoming DM needs a TP session because the message length is greater than 8 bytes): */
    else
    {
      /* for TP connections: SduLength contains payload only; no change required */
      /* #19 Set the transmission path to send via a TP session (transmission timeout is supervised by J1939TP). */
      pTxHandler->TransmitPath = J1939DCM_TX_PATH_TP;
      pTxHandler->TxTimer      = 0; /* no timeout supervision is used */
    }

    /*
     * Set channels counters initially to message length --> nothing will be transmitted.
     * Transmission preparation is triggered on the node level.
     * All channels referenced by the current node are accounted for in case of a global
     * channel broadcast is requested (DM1).
     */
    /* #20 Iterate over the configured channels for the requested node. */
    for (lChannelHdl = 0u; lChannelHdl < J1939Dcm_GetSizeOfCfg_ChannelTable(); ++lChannelHdl)
    {
      /*
       * #21 Update the buffer indices of all channels as if all channels transmit the same DM
       * (in case of global broadcast of DM1).
       */
      pTxHandler->BufferIndex[lChannelHdl] = pBufferContext->Buffer.SduLength;                                                                       /* VCA_J1939DCM_VERIFIED_CHANNEL_ACCESS */
    }

    /* #22 Indicate successful transmission preparation. */
    lResult = E_OK;
  }
  else
  {
    /* else: transmission is already in progress; reject request */
  }
  /* #23 Leave critical section. */
  J1939Dcm_ExitCritical();

  /* #24 Return transmission results. */
  return lResult;
}

/***********************************************************************************************************************
 * J1939Dcm_NetTxHandlerTransmit()
 **********************************************************************************************************************/
/*!
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
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(Std_ReturnType, J1939DCM_CODE)
  J1939Dcm_NetTxHandlerTransmit(PduIdType TxPduId,
  J1939Dcm_ChannelHdlType channelHdl
  )
{
  Std_ReturnType lResult;
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  if (!J1939Dcm_IsValidChannelHdl(channelHdl))                                                                                                       /* PRQA S 2995 */ /* MD_J1939Dcm_ConstExpr */
  {
    J1939Dcm_DetAssertAlways(
          J1939DCM_API_MAINFUNCTION,
          J1939DCM_E_INVALID_CHANNEL
          )
    lResult = E_NOT_OK;
  }
  /* #10 If channel is valid: */
  else
#endif
  {
    uint8_least    lUnconfChannels;
    PduInfoType    lTpTransmitData;
    J1939Dcm_TxHandlerPtrType pTxHandler = &J1939Dcm_DiagContext.CommonContext.TxHandlerState;

    /*
     * #11 Enter critical section (Reason: protect data consistency of the handler state during
     *     the transmission preparation of an DM).
     */
    J1939Dcm_EnterCritical();

    /*
     * #12 Prepare a transmission for one specific channel (reset the buffer index and increment
     *     the number of channels that are waiting for confirmation).
     */
    pTxHandler->BufferIndex[channelHdl] = 0;                                                                                                         /* VCA_J1939DCM_VERIFIED_CHANNEL_ACCESS */
    pTxHandler->UnconfirmedChannels++;                                                                                                               /* PRQA S 3387 */ /* MD_J1939Dcm_OptimizedInlineCode_3387 */
    lUnconfChannels = pTxHandler->UnconfirmedChannels;

    /* #13 Leave critical section. */
    J1939Dcm_ExitCritical();

    /* #14 If the transmission path is to send via a TP session: */
    if (pTxHandler->TransmitPath == J1939DCM_TX_PATH_TP)
    {
      /*
       * for TP transmission: pass only meta data to PduR_Transmit. Payload is
       * requested for from PduR via a copy Tx function.
       */
      /* #15 Reference only the meta data via the Sdu data pointer of the local transmitting object. */
      lTpTransmitData.SduDataPtr = (SduDataPtrType)pTxHandler->MetaData;                                                                             /* PRQA S 0312 */ /* MD_J1939Dcm_Rule11.8 */
    }
    /* #16 Otherwise (if the transmission path is to send via a CAN interface): */
    else
    {
      /* for IF transmissions: use buffer as it is; meta data have been added during Tx preparation */
      /*
       * #17 Reference the whole message (payload and meta data) via the Sdu data pointer of the
       *     local transmitting object.
       */
      lTpTransmitData.SduDataPtr = pTxHandler->BufferContext->Buffer.SduDataPtr;
    }
    /* #18 Update the Sdu length of the local transmitting object. */
    /*
     * The length of the Sdu does not include the length of the meta data when sending
     * via TP session while it is included when sending via CAN interface.
     */
    lTpTransmitData.SduLength = pTxHandler->BufferContext->Buffer.SduLength;

    /* #19 Start transmission on channel. */
    lResult = PduR_J1939DcmTransmit(                                                                                                                 /* VCA_J1939DCM_POINTER_FORWARD_LOCAL */
                TxPduId,
                &lTpTransmitData
                );

    /* #20 If the transmission is unsuccessful and the transmission is not confirmed: */
    if ((lResult != E_OK) && (pTxHandler->UnconfirmedChannels >= lUnconfChannels))
    {
       /*
        * #21 Enter critical section (Reason: protect data consistency of the handler state during
        *     the transmission preparation of an DM).
        */
      J1939Dcm_EnterCritical();

      /*
       * Nothing transmitted and apparently no confirmation occurred.
       * In case of transmission was declined even before calling copy transmitted data function (DM1 and DM35).
       * Otherwise, channels waiting for confirmation are decremented in TP transmission confirmation function.
       */

      /* #22 Decrement the number of channels waiting for confirmation. */
      pTxHandler->UnconfirmedChannels--;                                                                                                             /* PRQA S 3387 */ /* MD_J1939Dcm_OptimizedInlineCode_3387 */

      /* #23 Leave critical section. */
      J1939Dcm_ExitCritical();
    }
  }
  /* #24 Return the transmission results. */
  return lResult;
}

#if (J1939DCM_DM1_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM1ConfirmTx()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1ConfirmTx(
  J1939Dcm_NodeContextPtrType pNodeContext,
  Std_ReturnType result
  )
{
  /*
   * #11 Enter critical section
   *     (Reason: protect data consistency of the queue of events of DM1 against the request manager interrupts).
   */
  J1939Dcm_EnterCritical();
  /* #12 Update the queue of events of DM1 with a transmission success or a transmission failure. */
  if (result == E_OK)
  {
    /* trigger transmission finalization */
    J1939Dcm_QueueBitOpSet(&pNodeContext->DM1Queue, J1939DCM_QUEUE_TXCONF);                                                                          /* VCA_J1939DCM_FALSE_POSITIVE */
  }
  else
  {
    /* trigger NACK transmission (in case of broadcast) */
    J1939Dcm_QueueBitOpSet(&pNodeContext->DM1Queue, J1939DCM_QUEUE_TXFAIL);                                                                          /* VCA_J1939DCM_FALSE_POSITIVE */
  }
  /* #13 Leave critical section. */
  J1939Dcm_ExitCritical();
}
#endif

#if ((J1939DCM_DM2_SUPPORT == STD_ON) || \
    (J1939DCM_DM4_SUPPORT == STD_ON) || \
    (J1939DCM_DM5_SUPPORT == STD_ON) || \
    (J1939DCM_DM24_SUPPORT == STD_ON) || \
    (J1939DCM_DM25_SUPPORT == STD_ON) || \
    (J1939DCM_DM27_SUPPORT == STD_ON) || \
    (J1939DCM_DM31_SUPPORT == STD_ON) || \
    (J1939DCM_DM53_SUPPORT == STD_ON) || \
    (J1939DCM_DM54_SUPPORT == STD_ON))
/***********************************************************************************************************************
 * J1939Dcm_DMxConfirmTx()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxConfirmTx(
  J1939Dcm_NodeContextPtrType pNodeContext,
  Std_ReturnType result
  )
{
  /*
   * #15 Enter critical section
   * (Reason: protect data consistency of the queue of events of DMx against the request manager interrupts).
   */
  J1939Dcm_EnterCritical();
  /* #16 Update the queue of events of DMx with a transmission success or a transmission failure. */
  if (result == E_OK)
  {
    /* trigger transmission finalization */
    J1939Dcm_QueueBitOpSet(&pNodeContext->DMxQueue, J1939DCM_QUEUE_TXCONF);                                                                          /* VCA_J1939DCM_FALSE_POSITIVE */
  }
  else
  {
    /* trigger NACK transmission (in case of broadcast) */
    J1939Dcm_QueueBitOpSet(&pNodeContext->DMxQueue, J1939DCM_QUEUE_TXFAIL);                                                                          /* VCA_J1939DCM_FALSE_POSITIVE */
  }
  /* #17 Leave critical section.*/
  J1939Dcm_ExitCritical();
}
#endif

#if (J1939DCM_DM35_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM35ConfirmTx()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35ConfirmTx(
  J1939Dcm_NodeContextPtrType pNodeContext
  )
{
  /*
   * #19 Enter critical section
   * (Reason: protect data consistency of the queue of events of DM35 against the request manager interrupts).
   */
  J1939Dcm_EnterCritical();
  /* trigger transmission finalization (DM35 is always broadcast, no NACK need to be sent) */
  /* #20 Update the queue of events of DMx with a transmission success. */
  J1939Dcm_QueueBitOpSet(&pNodeContext->DM35Queue, J1939DCM_QUEUE_TXCONF);                                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
  /* #21 Leave critical section. */
  J1939Dcm_ExitCritical();
}
#endif

#if (J1939DCM_DM15_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_NetTxHandlerConfirmMemRes()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_NetTxHandlerConfirmMemRes(
  Std_ReturnType result,
  uint8 apiId                                                                                                                                        /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  J1939Dcm_IgnoreUnusedArgument(apiId)                                                                                                               /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* #10 Reset memory and transmission handlers and notify the application. */
  J1939Dcm_NetTxHandlerReset();
  J1939Dcm_MemHandlerReset();

  if(NULL_PTR == J1939Dcm_Cfg_MemResponseTxConfFunc)                                                                                                 /* PRQA S 2992, 2995, 2996 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_MEM_CALLOUT_CHECK */
  {
    J1939Dcm_DetAssertAlways(                                                                                                                        /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      apiId,
      J1939DCM_E_PARAM_CONFIG
      )
  }
  else
  {
    J1939Dcm_Cfg_MemResponseTxConfFunc(result);
  }
}
#endif

#if ((J1939DCM_DM16_SUPPORT == STD_ON) || \
    (J1939DCM_DM18_SUPPORT == STD_ON))
/***********************************************************************************************************************
 * J1939Dcm_NetTxHandlerConfirmMemData()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_NetTxHandlerConfirmMemData(
  J1939Dcm_MemDataType DataKind,
  Std_ReturnType result,
  uint8 apiId                                                                                                                                        /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  J1939Dcm_IgnoreUnusedArgument(apiId)                                                                                                               /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* #10 Reset memory and transmission handlers and notify the application. */
  J1939Dcm_NetTxHandlerReset();
  J1939Dcm_MemHandlerReset();

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  if(NULL_PTR == J1939Dcm_Cfg_MemDataTxConfFunc)                                                                                                     /* PRQA S 2992, 2995, 2996 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_MEM_CALLOUT_CHECK */
  {
    J1939Dcm_DetAssertAlways(                                                                                                                        /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      apiId,
      J1939DCM_E_PARAM_CONFIG
      )
  }
  else
# endif
  {
    J1939Dcm_Cfg_MemDataTxConfFunc(DataKind, result);
  }
}
#endif

/***********************************************************************************************************************
 * J1939Dcm_NetTxHandlerConfirm()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_NetTxHandlerConfirm(
  J1939Dcm_NodeHdlType nodeHdl,                                                                                                                      /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  uint8_least diagMessage,
  Std_ReturnType result,                                                                                                                             /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  uint8 apiId                                                                                                                                        /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* Assert invalid node if applicable. */
  if(!J1939Dcm_IsValidNodeHdl(nodeHdl))                                                                                                              /* PRQA S 2995 */ /* MD_J1939Dcm_ConstExpr */
  {
    J1939Dcm_DetAssertAlways(
          apiId,
          J1939DCM_E_INVALID_NODE
          )
  }
  else
#endif
  {
#if (J1939DCM_NEED_DTC_HANDLER == STD_ON)
    J1939Dcm_NodeContextPtrType pNodeContext = &J1939Dcm_DiagContext.NodeContext[nodeHdl];                                                           /* PRQA S 2932 */ /* MD_J1939Dcm_ComputingOfInvalidPointer */ /* VCA_J1939DCM_FALSE_POSITIVE */
#endif

    J1939Dcm_IgnoreUnusedArgument(nodeHdl)                                                                                                           /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    J1939Dcm_IgnoreUnusedArgument(result)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    J1939Dcm_IgnoreUnusedArgument(apiId)                                                                                                             /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

    switch (diagMessage)
    {
      /* #10 Trigger specific confirm handlers according to the incomming DM. */
#if (J1939DCM_DM1_SUPPORT == STD_ON)
      case J1939DCM_DM1:
        J1939Dcm_DM1ConfirmTx(
          pNodeContext,
          result
          );

        break;
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

#if ((J1939DCM_DM2_SUPPORT == STD_ON)  || \
    (J1939DCM_DM4_SUPPORT == STD_ON)  || \
    (J1939DCM_DM5_SUPPORT == STD_ON)  || \
    (J1939DCM_DM24_SUPPORT == STD_ON) || \
    (J1939DCM_DM25_SUPPORT == STD_ON) || \
    (J1939DCM_DM27_SUPPORT == STD_ON) || \
    (J1939DCM_DM31_SUPPORT == STD_ON) || \
    (J1939DCM_DM53_SUPPORT == STD_ON) || \
    (J1939DCM_DM54_SUPPORT == STD_ON))
# if (J1939DCM_DM2_SUPPORT == STD_ON)
      case J1939DCM_DM2:
# endif
# if (J1939DCM_DM4_SUPPORT == STD_ON)
      case J1939DCM_DM4:
# endif
# if (J1939DCM_DM5_SUPPORT == STD_ON)
      case J1939DCM_DM5:
# endif
# if (J1939DCM_DM24_SUPPORT == STD_ON)
      case J1939DCM_DM24:
# endif
# if (J1939DCM_DM25_SUPPORT == STD_ON)
      case J1939DCM_DM25:
# endif
# if (J1939DCM_DM27_SUPPORT == STD_ON)
      case J1939DCM_DM27:
# endif
# if (J1939DCM_DM31_SUPPORT == STD_ON)
      case J1939DCM_DM31:
# endif
# if (J1939DCM_DM53_SUPPORT == STD_ON)
      case J1939DCM_DM53:
# endif
# if (J1939DCM_DM54_SUPPORT == STD_ON)
      case J1939DCM_DM54:
# endif
        J1939Dcm_DMxConfirmTx(
          pNodeContext,
          result
          );
        break;
#endif

#if (J1939DCM_DM35_SUPPORT == STD_ON)
      case J1939DCM_DM35:
        J1939Dcm_DM35ConfirmTx(pNodeContext);
        break;
#endif /* (J1939DCM_NEED_DM35_PROCESSOR == STD_ON) */

#if (J1939DCM_DM15_SUPPORT == STD_ON)
      case J1939DCM_DM15:
        J1939Dcm_NetTxHandlerConfirmMemRes(
          result,
          J1939DCM_API_TPTXCONFIRMATION
          );
        break;
#endif

#if (J1939DCM_DM16_SUPPORT == STD_ON)
      case J1939DCM_DM16:
        J1939Dcm_NetTxHandlerConfirmMemData(
          J1939DCM_MEM_DATA_BINARY,
          result,
          J1939DCM_API_TPTXCONFIRMATION
          );
        break;
#endif

#if (J1939DCM_DM18_SUPPORT == STD_ON)
      case J1939DCM_DM18:
        J1939Dcm_NetTxHandlerConfirmMemData(
          J1939DCM_MEM_DATA_SECURITY,
          result,
          J1939DCM_API_TPTXCONFIRMATION
          );
        break;
#endif
    /* #20 If the incoming message does not match any of the previous cases, check whether the configuration is correct.*/
      default:                                                                                                                                       /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
        /* no TxConfirmation implemented for given DM! */
        J1939Dcm_DetAssertAlways(
          apiId,
          J1939DCM_E_PARAM_CONFIG
          )
        break;
    }
  }
}

/***********************************************************************************************************************
 * J1939Dcm_ComStateReset()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_ComStateReset(
  void
  )
{
  J1939Dcm_NodeHdlOptType lNodeHdl;

  for (lNodeHdl = 0u; lNodeHdl < J1939Dcm_GetSizeOfCfg_NodeTable(); ++lNodeHdl)
  {
    J1939Dcm_DiagContext.NodeContext[lNodeHdl].ComState = 0u;                                                                                        /* VCA_J1939DCM_VERIFIED_NODE_ACCESS */
  }
}

/***********************************************************************************************************************
 * J1939Dcm_NetTxHandlerReset()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_NetTxHandlerReset(
  void
  )
{
  J1939Dcm_TxHandlerPtrType pTxHandler = &J1939Dcm_DiagContext.CommonContext.TxHandlerState;
  /*
   * #10 Enter critical section
   * (Reason: protect data consistency of the handler state against new transmission or confirmation interrupt).
   */
  J1939Dcm_EnterCritical();

  /* #11 Reset transmission handler state. */
  pTxHandler->BufferContext       = NULL_PTR;
  pTxHandler->UnconfirmedChannels = 0;
  pTxHandler->DM                  = J1939DCM_DM_UNDEF;
  pTxHandler->NodeHdl             = J1939DCM_INVALID_NODE_HDL;
  pTxHandler->TxTimer             = 0;

  /* #12 Leave critical section. */
  J1939Dcm_ExitCritical();
}

#if (J1939DCM_NEED_TP_RECEPTION == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_NetRxHandlerReset()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_NetRxHandlerReset(
  void
  )
{
  J1939Dcm_RxHandlerPtrType pRxHandler = &J1939Dcm_DiagContext.CommonContext.RxHandlerState;
  /* #10 Reset reception handler state. */
  pRxHandler->RxPduId                          = J1939DCM_INVALID_PDU_ID;
  pRxHandler->RxAddressInfo.Channel            = J1939DCM_INVALID_CHANNEL_HDL;
  pRxHandler->RxAddressInfo.SourceAddress      = J1939DCM_INVALID_MEM_ADDRESS;
  pRxHandler->RxAddressInfo.DestinationAddress = J1939DCM_INVALID_MEM_ADDRESS;
}
#endif

#if (J1939DCM_NEED_MEM_ACCESS == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_MemHandlerReset()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_MemHandlerReset(
  void
  )
{
  J1939Dcm_MemHandlerPtrType pMemHandler = &J1939Dcm_DiagContext.CommonContext.MemHandlerState;
  /*
   * #10 Enter critical section
   *     (Reason: protect data consistency of the memory handler state against another CDD interruption).
   */
  J1939Dcm_EnterCritical();

  /* #11 Reset Memory handler state. */
  pMemHandler->DiagMessage            = J1939DCM_DM_UNDEF;
  pMemHandler->ChannelHdl             = J1939DCM_INVALID_CHANNEL_HDL;
  pMemHandler->NodeHdl                = J1939DCM_INVALID_NODE_HDL;
  pMemHandler->DestinationAddress     = J1939DCM_INVALID_MEM_ADDRESS;
  pMemHandler->TxPduId                = J1939DCM_INVALID_PDU_ID;
  pMemHandler->MetaDataLength         = 0;
  pMemHandler->MessageEvent           = J1939DCM_MEM_MSG_NO_EVENT;

  /* #12 Leave critical section. */
  J1939Dcm_ExitCritical();

}
#endif /* (J1939DCM_NEED_MEM_ACCESS == STD_ON) */

#if (J1939DCM_NEED_MEM_ACCESS == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_MemHandlerTransmit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_MemHandlerTransmit(
  uint8 diagMessage,
  CONSTP2VAR(Std_ReturnType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pTxResult
  )
{
  J1939Dcm_MemHandlerPtrType pMemHandler = &J1939Dcm_DiagContext.CommonContext.MemHandlerState;

  /* #10 Prepare for a transmission according to the queued data. */
  *pTxResult = J1939Dcm_NetTxHandlerPrepare(
                 &pMemHandler->TxData,
                 diagMessage,
                 pMemHandler->NodeHdl,
                 pMemHandler->DestinationAddress,
                 pMemHandler->MetaDataLength
                 );

  /* #30 If the preparation for the DM transmission is successful: */
  if (*pTxResult == E_OK)
  {
    /* #40 Transmit the DM because the transmission handler is free. */
    *pTxResult = J1939Dcm_NetTxHandlerTransmit(pMemHandler->TxPduId, pMemHandler->ChannelHdl);
    
    /* Indicate transmission finished */
    pMemHandler->MessageEvent = J1939DCM_MEM_MSG_NO_EVENT;
  }
  /* #50 Otherwise (if the preparation for the DM transmission is unsuccessful): */
  else
  {
    /* #60 Retry in next cycle because the transmission handler is busy. */
    *pTxResult = E_OK;
  }
}
#endif

#if (J1939DCM_NEED_MEM_ACCESS == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_MemHandlerHandleTransmissionFailure()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_MemHandlerHandleTransmissionFailure(
  uint8 diagMessage,                                                                                                                                 /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  Std_ReturnType txResult
  )
{
  J1939Dcm_IgnoreUnusedArgument(diagMessage)                                                                                                         /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 If the transmission was unsuccessful: */
  if (txResult != E_OK)
  {
    /* #20 Reset the transmission Handler and the memory Handler and notify the application.  */
    switch (diagMessage)
    {
# if (J1939DCM_DM15_SUPPORT == STD_ON)
      case J1939DCM_DM15:
        J1939Dcm_NetTxHandlerConfirmMemRes(
          E_NOT_OK,
          J1939DCM_API_MAINFUNCTION
          );
        break;
# endif
# if (J1939DCM_DM16_SUPPORT == STD_ON)
      case J1939DCM_DM16:
        J1939Dcm_NetTxHandlerConfirmMemData(
          J1939DCM_MEM_DATA_BINARY,
          E_NOT_OK,
          J1939DCM_API_MAINFUNCTION
          );
        break;
# endif
# if (J1939DCM_DM18_SUPPORT == STD_ON)
      case J1939DCM_DM18:
        J1939Dcm_NetTxHandlerConfirmMemData(
          J1939DCM_MEM_DATA_SECURITY,
          E_NOT_OK,
          J1939DCM_API_MAINFUNCTION
          );
        break;
# endif
      default:                                                                                                                                       /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
        J1939Dcm_NetTxHandlerReset();
        J1939Dcm_MemHandlerReset();
        /* should already be detected in RxIndication APIs, but also done here for robustness */
        J1939Dcm_DetAssertAlways(
          J1939DCM_API_MAINFUNCTION,
          J1939DCM_E_INVALID_PGN
          )

        break;
    }
  }
}
#endif

#if (J1939DCM_NEED_MEM_ACCESS == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_MemHandlerTask()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_MemHandlerTask(
  void
  )
{
  Std_ReturnType                 lTxResult;
  J1939Dcm_MemMsgEventType       lMessageEvent;
  uint8                          lDiagMessage;
  J1939Dcm_MemHandlerReadPtrType pMemHandler = &J1939Dcm_DiagContext.CommonContext.MemHandlerState;

  /*
  * #10 Enter critical section
  * (Reason: protect data consistency of the memory handler state during the transmission preparation of a DM).
  */
  J1939Dcm_EnterCritical();

  /* #12 Store Diagnostic Message and Message Event to local variables. */
  lDiagMessage  = pMemHandler->DiagMessage;
  lMessageEvent = pMemHandler->MessageEvent;

  /* #15 Leave critical section. */
  J1939Dcm_ExitCritical();

  /* #20 If there is a memory access message (DM15, DM16, or DM18) to be transmitted: */
  if (lMessageEvent == J1939DCM_MEM_MSG_TRANSMIT)
  {
    /* #30 Prepare for a transmission according to the queued data. */
    J1939Dcm_MemHandlerTransmit(
      lDiagMessage,
      &lTxResult
      );

    /* #40 Handles memory message transmission failure. */
    J1939Dcm_MemHandlerHandleTransmissionFailure(
      lDiagMessage,
      lTxResult
      );
  }
}
#endif /* (J1939DCM_NEED_MEM_ACCESS == STD_ON) */

/***********************************************************************************************************************
 * J1939Dcm_Reset()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL FUNC(void, J1939DCM_CODE)
J1939Dcm_Reset(
  void
  )
{
  J1939Dcm_NodeHdlType lNodeHdl;
  /* --- global module status ----------------------------------------------------------------- */
  /* #10 Set node handles in the global context. */
  for (lNodeHdl = 0u; lNodeHdl < J1939Dcm_GetSizeOfCfg_NodeTable(); ++lNodeHdl)
  {
    J1939Dcm_DiagContext.NodeContext[lNodeHdl].NodeHdl = lNodeHdl;                                                                                   /* VCA_J1939DCM_VERIFIED_NODE_ACCESS */
  }

  /* #20 Reset communication state. */
  J1939Dcm_ComStateReset();

  /* --- DEM Semaphore ------------------------------------------------------------------------ */
  /* #30 Release DEM resources. */
#if (J1939DCM_NEED_DEM == STD_ON)
  J1939Dcm_DtcHandlerDemSemaphoreSetLocked(FALSE);
#endif

  /* --- Communication Handler ---------------------------------------------------------------- */
    /* #40 Reset the transmission and reception handlers. */
  J1939Dcm_NetTxHandlerReset();
  J1939Dcm_NetRxHandlerReset();

  /* --- DM specific data --------------------------------------------------------------------- */
  /* #50 Reset the Diagnostic messages handlers. */
  J1939Dcm_DM1Init();
  J1939Dcm_DM13Init();
  J1939Dcm_DM35Init();
  J1939Dcm_DMxInit();

  J1939Dcm_MemHandlerReset();
}                                                                                                                                                    /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 * J1939Dcm_NetUpdateQueuedCommStateChange()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_NetUpdateQueuedCommStateChange(
  J1939Dcm_StateType newState,                                                                                                                       /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_NodeContextPtrType pNodeContext                                                                                                           /* PRQA S 3673, 3206 */ /* MD_MSR_Rule8.13, MD_J1939Dcm_Rule2.7 */
  )
{
  J1939Dcm_IgnoreUnusedArgument(newState)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument_CONST(pNodeContext)                                                                                                  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /*
  * #26 Enter critical section
  * (Reason: protect data consistency of the queue of events against a new communication setup request).
  */
  J1939Dcm_EnterCritical();

  /* #27 Queue state request to notify DM message handlers. */
#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
  J1939Dcm_QueueBitOpSet(&pNodeContext->DM1Queue, J1939DCM_QUEUE_STATE);                                                                             /* VCA_J1939DCM_FALSE_POSITIVE */
  pNodeContext->DM1Queue.StateChangeRequest = newState;                                                                                              /* VCA_J1939DCM_FALSE_POSITIVE */
#endif

#if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
  J1939Dcm_QueueBitOpSet(&pNodeContext->DM35Queue, J1939DCM_QUEUE_STATE);                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
  pNodeContext->DM35Queue.StateChangeRequest = newState;                                                                                             /* VCA_J1939DCM_FALSE_POSITIVE */
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
  J1939Dcm_QueueBitOpSet(&pNodeContext->DMxQueue, J1939DCM_QUEUE_STATE);                                                                             /* VCA_J1939DCM_FALSE_POSITIVE */
  pNodeContext->DMxQueue.StateChangeRequest = newState;                                                                                              /* VCA_J1939DCM_FALSE_POSITIVE */
#endif
  /* #28 Leave critical section. */
  J1939Dcm_ExitCritical();
}

/**********************************************************************************************************************
 * J1939Dcm_NetCalculateResponseAddress()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(uint8, J1939DCM_CODE)
J1939Dcm_NetCalculateResponseAddress(
  uint8 sourceAddress,
  uint8 destAddress
  )
{
  uint8 lResponseAddress;
  /* Resolve address to which the response shall be transmitted. */
  /*
   * [J1939-73]
   * If the Request or applicable PGN is sent to a global address, then the response is sent to a global address.
   * If the Request or applicable PGN is sent to a specific address, then the response is sent to a specific address.
   */
  /* #10 If the destination address is global: */
  if (destAddress == J1939DCM_ADDRESS_BROADCAST)
  {
    /* #20 Set the response address to global. */
    lResponseAddress = J1939DCM_ADDRESS_BROADCAST;
  }
  /* #30 Otherwise (if the destination address is specific): */
  else
  {
    /* #40 Set the response address to the specific source address of the requested diagnostic message. */
    lResponseAddress = sourceAddress;
  }
  return lResponseAddress;
}

#if (J1939DCM_DM1_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM1Receive()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM1Receive(
  J1939Dcm_NodeContextPtrType pNodeContext,
  J1939Dcm_ChannelHdlType channelHdl,
  uint32 requestedPgn,
  uint8 responseAddress,
  uint8 priority
  )
{
  J1939Dcm_DM1StateReadPtrType pDM1State = &pNodeContext->DM1State;
  J1939Dcm_DM1QueuePtrType     pDM1Queue = &pNodeContext->DM1Queue;

  /* #10 If currently there is no other DM1 request being processed: */
  if ((!J1939Dcm_QueueBitOpTest(pDM1Queue, J1939DCM_QUEUE_REQ)) &&
      (pDM1State->ProcessingState < J1939DCM_MSG_STATE_PREP_START))
  {
      /*
       * #20 Enter critical section
       * (Reason: protect data consistency of the events queue against another request manager interrupt).
       */
    J1939Dcm_EnterCritical();
    /*
     * #30 Indicate the incoming request in the queue of events and set the corresponding channel
     *     handle and response address.
     */
    J1939Dcm_QueueBitOpSet(pDM1Queue, J1939DCM_QUEUE_REQ);                                                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
    pDM1Queue->ChannelHdl = channelHdl;                                                                                                              /* VCA_J1939DCM_FALSE_POSITIVE */
    pDM1Queue->ResponseDA = responseAddress;                                                                                                         /* VCA_J1939DCM_FALSE_POSITIVE */
    /* #40 Leave critical section. */
    J1939Dcm_ExitCritical();
  }
  /* #50 Otherwise (if currently a DM1 request is being processed): */
  else
  {
    /* DM request has already been queued. */
    /*
     * [J1939-73]
     * If for some reason a device can not perform the requested action,
     *    then it is required to send a negative acknowledgement.
     * Implementers be aware that no positive or negative acknowledgement is sent
     *    when the request was sent to a global address.
     */

    /* #60 If the response address of the requested DM is specific: */
    if (responseAddress != J1939DCM_ADDRESS_BROADCAST)
    {

      (void)J1939Rm_SendAck(                                                                                                                         /* VCA_J1939DCM_POINTER_FORWARD_NULL */
              J1939Dcm_Cfg_GetNodeUserId(pNodeContext->NodeHdl),                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
              J1939Dcm_Cfg_GetChannelId(channelHdl),                                                                                                 /* VCA_J1939DCM_FALSE_POSITIVE */
              requestedPgn,
              NULL_PTR,
              J1939RM_ACK_CANNOT_RESPOND,
              responseAddress,
              priority,
              FALSE
              );
    }
  }
}
#endif

#if (J1939DCM_NEED_DMX_PROCESSOR)
/**********************************************************************************************************************
 * J1939Dcm_DMxReceive()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/

J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DMxReceive(
  J1939Dcm_NodeContextPtrType pNodeContext,
  J1939Dcm_ChannelHdlType channelHdl,
  uint32 requestedPgn,
  uint8 responseAddress,
  uint8 priority
  )
{
  J1939Dcm_MessageHdlType      lMessageHdl;
  J1939Dcm_DMxStateReadPtrType pDMxState = &pNodeContext->DMxState;
  J1939Dcm_DMxQueuePtrType     pDMxQueue = &pNodeContext->DMxQueue;

  /* #10 Calculate the local ID of the requested diagnostic message. */
  lMessageHdl = J1939Dcm_UtiGetMsgHdlByPGN(
                  requestedPgn,
                  pNodeContext->NodeHdl,
                  channelHdl,
                  J1939DCM_API_MAINFUNCTION
                  );

  /* #20 If currently there is no other DMx request being processed: */
  if ((!J1939Dcm_QueueBitOpTest(pDMxQueue, J1939DCM_QUEUE_REQ)) &&
      (pDMxState->ProcessingState < J1939DCM_MSG_STATE_PREP_START))
  {
    /*
     * #30 Enter critical section (Reason: protect data consistency of the events
     *     queue against another request manager interrupt). */
    J1939Dcm_EnterCritical();

    /*
     * #40 Indicate the incoming request in the queue of events and set the corresponding
     *     channel handle, message, and response address.
     */
    J1939Dcm_QueueBitOpSet(pDMxQueue, J1939DCM_QUEUE_REQ);                                                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
    pDMxQueue->ChannelHdl = channelHdl;                                                                                                              /* VCA_J1939DCM_FALSE_POSITIVE */
    pDMxQueue->MessageHdl = lMessageHdl;                                                                                                             /* VCA_J1939DCM_FALSE_POSITIVE */
    pDMxQueue->ResponseDA = responseAddress;                                                                                                         /* VCA_J1939DCM_FALSE_POSITIVE */

    /* #50 Leave critical section. */
    J1939Dcm_ExitCritical();
  }
  /* #60 Otherwise (if currently a DMx request is being processed): */
  else
  {
    /* DM request have already been queued. */
    /*
     * [J1939-73]
     * If for some reason a device can not perform the requested action,
     *    then it is required to send a negative acknowledgement.
     * Implementers be aware that no positive or negative acknowledgement is sent
     *    when the request was sent to a global address.
     */

    /* #70 If the response address of the requested DM is specific: */
    if (responseAddress != J1939DCM_ADDRESS_BROADCAST)
    {
      (void)J1939Rm_SendAck(                                                                                                                         /* VCA_J1939DCM_POINTER_FORWARD_NULL */
              J1939Dcm_Cfg_GetNodeUserId(pNodeContext->NodeHdl),                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
              J1939Dcm_Cfg_GetChannelId(channelHdl),                                                                                                 /* VCA_J1939DCM_FALSE_POSITIVE */
              requestedPgn,
              NULL_PTR,
              J1939RM_ACK_CANNOT_RESPOND,
              responseAddress,
              priority,
              FALSE
              );
    }
  }
}
#endif

#if (J1939DCM_DM35_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_DM35Receive()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM35Receive(
  J1939Dcm_DM35QueuePtrType pDM35Queue,
  J1939Dcm_ChannelHdlType channelHdl
  )
{
   /*
   * #10 Enter critical section
   *     (Reason: protect data consistency of the events queue against another request manager interrupt).
   */
  J1939Dcm_EnterCritical();

  /* #20 Indicate the incoming request in the queue of events and activate the corresponding channel. */
  J1939Dcm_QueueBitOpSet(pDM35Queue, J1939DCM_QUEUE_REQ);                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
  J1939Dcm_DM35SetChannelActive(pDM35Queue->RequestedChannels, channelHdl);                                                                          /* VCA_J1939DCM_FALSE_POSITIVE */

  /* #30 Leave critical section. */
  J1939Dcm_ExitCritical();
}
#endif

/**********************************************************************************************************************
 * J1939Dcm_NetHandleRmErroneousInterrupt()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_NetHandleRmErroneousInterrupt(
  J1939Dcm_NodeHdlType nodeHdl,                                                                                                                      /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_ChannelHdlType channelHdl,                                                                                                                /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  uint32 requestedPgn,
  uint8 responseAddress,
  uint8 priority
  )
{
  J1939Dcm_IgnoreUnusedArgument(nodeHdl)         /* parameter not used in single node configurations. */                                             /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(channelHdl)      /* parameter not used in single channel configurations. */                                          /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Check whether PGN is invalid. */
  J1939Dcm_DetAssertAlways(
    J1939DCM_API_REQUESTINDICATION,
    J1939DCM_E_INVALID_PGN
    )   /* SWS_J1939Dcm_00006 */

  /*
   * [J1939-21] A response is always required from the specified destination(not global)
   *            even if it is a NACK indicating that the particular PGN value is not supported.
   * [J1939-73] Implementers be aware that no positive or negative acknowledgement
   *            is sent when the request was sent to a global address.
   */

   /* #20 If the response address to the requested DM is specific: */
  if (responseAddress != J1939DCM_ADDRESS_BROADCAST)
  {
    (void)J1939Rm_SendAck(                                                                                                                           /* VCA_J1939DCM_POINTER_FORWARD_NULL */
            J1939Dcm_Cfg_GetNodeUserId(nodeHdl),                                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
            J1939Dcm_Cfg_GetChannelId(channelHdl),                                                                                                   /* VCA_J1939DCM_FALSE_POSITIVE */
            requestedPgn,
            NULL_PTR,
            J1939RM_ACK_NEGATIVE,
            responseAddress,
            priority,
            FALSE
            );
  }
}

#if(J1939DCM_NEED_DEM == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_NetHandleRmInterrupt()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_NetHandleRmInterrupt(
  J1939Dcm_NodeContextPtrType pNodeContext,
  J1939Dcm_ChannelHdlType channelHdl,
  uint32 requestedPgn,
  uint8 responseAddress,
  uint8 priority
  )
{
  uint8 lDiagMessage;
  /* #30 Calculate requested diagnostic message. */
  lDiagMessage = J1939Dcm_UtiGetDiagMsgByPGN(
                   requestedPgn,
                   pNodeContext->NodeHdl,
                   channelHdl,
                   J1939DCM_API_REQUESTINDICATION
                   );

  /* #35 Forward the DM request to respective message handler. */
  switch (lDiagMessage)
  {
# if (J1939DCM_DM1_SUPPORT == STD_ON)
    /* #40 In case of DM1, receive DM1. */
    case J1939DCM_DM1:
      J1939Dcm_DM1Receive(
        pNodeContext,
        channelHdl,
        requestedPgn,
        responseAddress,
        priority
        );
      break;
# endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */

      /* #45 In case of DMx, receive DMx. */
# if (J1939DCM_NEED_DMX_PROCESSOR)
#  if (J1939DCM_DM2_SUPPORT == STD_ON)
    case J1939DCM_DM2:
#  endif
#  if (J1939DCM_DM3_SUPPORT == STD_ON)
    case J1939DCM_DM3:
#  endif
#  if (J1939DCM_DM4_SUPPORT == STD_ON)
    case J1939DCM_DM4:
#  endif
#  if (J1939DCM_DM5_SUPPORT == STD_ON)
    case J1939DCM_DM5:
#  endif
#  if (J1939DCM_DM11_SUPPORT == STD_ON)
    case J1939DCM_DM11:
#  endif
#  if (J1939DCM_DM24_SUPPORT == STD_ON)
    case J1939DCM_DM24:
#  endif
#  if (J1939DCM_DM25_SUPPORT == STD_ON)
    case J1939DCM_DM25:
#  endif
#  if (J1939DCM_DM27_SUPPORT == STD_ON)
    case J1939DCM_DM27:
#  endif
#  if (J1939DCM_DM31_SUPPORT == STD_ON)
    case J1939DCM_DM31:
#  endif
#  if (J1939DCM_DM53_SUPPORT == STD_ON)
    case J1939DCM_DM53:
#  endif
#  if (J1939DCM_DM54_SUPPORT == STD_ON)
    case J1939DCM_DM54:
#  endif
#  if (J1939DCM_DM55_SUPPORT == STD_ON)
    case J1939DCM_DM55:
#  endif
      J1939Dcm_DMxReceive(
        pNodeContext,
        channelHdl,
        requestedPgn,
        responseAddress,
        priority
        );
      break;
# endif

    /* #50 In case of DM35, receive DM35. */
# if (J1939DCM_DM35_SUPPORT == STD_ON)
    case J1939DCM_DM35:
      J1939Dcm_DM35Receive(
        &pNodeContext->DM35Queue,
        channelHdl
        );
      break;
# endif /* (J1939DCM_NEED_DM35_PROCESSOR == STD_ON) */

    /* #55 In case of default, handle Request manager erroneous interrupt. */
    default:
      J1939Dcm_NetHandleRmErroneousInterrupt(
        pNodeContext->NodeHdl,
        channelHdl,
        requestedPgn,
        responseAddress,
        priority
        );
      break;
  }
}
#endif

#if (J1939DCM_DM13_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM13Receive()
 **********************************************************************************************************************/
/*!
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
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM13Receive(
  J1939Dcm_NetworkType currentNetwork,
  P2CONST(PduInfoType, AUTOMATIC, J1939DCM_APPL_DATA) PduInfoPtr                                                                                     /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  J1939Dcm_ChannelHdlOptType lChannelHdl;
  uint32_least               lMessageData;
  uint8                      lBroadcastCommand;
  uint8                      lHoldSignal;
  J1939Dcm_DM13QueuePtrType  pDM13Queue = &J1939Dcm_DiagContext.CommonContext.DM13Queue;

  J1939Dcm_IgnoreUnusedArgument(currentNetwork)                                                                                                      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /*
   * #10 Extract the first 4 bytes of the DM from the payload
   *     (the broadcast status of the different bus types [3 bytes] + hold and suspend Signals [1 byte]).
   */
  lMessageData = J1939Dcm_UtiSduDataTo32Bit(PduInfoPtr->SduDataPtr);
  /* #15 Extract the hold signal (the high nibble of the fourth byte of the DM). */
  lHoldSignal = J1939Dcm_DM13DataGetHoldSignal(lMessageData);

  /* check for each channel if broadcast status need to be changed */
  /* #20 Iterate over the available channels. */
  for (lChannelHdl = 0u; lChannelHdl < J1939Dcm_GetSizeOfCfg_ChannelTable(); ++lChannelHdl)
  {
    /* #25 If a channel has a different bus type than the network where DM13 has been received: */
    if (J1939Dcm_Cfg_GetChannelBusType(lChannelHdl) != currentNetwork)
    {
       /*
        * #30 Update the broadcast command of that channel according to the bus type status
        *     of the corresponding network.
        */
      lBroadcastCommand = J1939Dcm_DM13DataGetBroadcastStatus(
                            lMessageData,
                            J1939Dcm_Cfg_GetChannelBusType(lChannelHdl)
                            );                                                                                                                       /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    /* #35 Otherwise (if a channel has same bus type as the network where DM13 has been received): */
    else
    {
      /*
       * #40 Update the broadcast command of that channel according to the bus type
       *     status of the current network.
       */
      lBroadcastCommand = J1939Dcm_DM13DataGetBroadcastStatus(
                            lMessageData,
                            J1939DCM_CURRENT_NETWORK
                            );

      /*
       * #42 If the broadcast command is leave as it is, update the broadcast command of that channel
       *     according to the bus type status of the corresponding network.
       */
      if (lBroadcastCommand == 0x03u)
      {
        lBroadcastCommand = J1939Dcm_DM13DataGetBroadcastStatus(
                              lMessageData,
                              J1939Dcm_Cfg_GetChannelBusType(lChannelHdl)
                              );
      }
    }

    /*
     * #45 Enter critical section
     *     (Reason: protect data consistency of the queue of events against another PduR interruption).
     */
    J1939Dcm_EnterCritical();
    /*
     * #50 Update the queue of events according to the incoming DM. Indicate that DM13
     *     has not been processed yet.
     */
    pDM13Queue->HoldSignal = lHoldSignal;
    pDM13Queue->BroadcastCommand[lChannelHdl] = lBroadcastCommand;                                                                                   /* VCA_J1939DCM_VERIFIED_CHANNEL_ACCESS */
    pDM13Queue->RequestPending = TRUE;
    /* #55 Leave critical section. */
    J1939Dcm_ExitCritical();
  }
  /*
   * Note: NodeId not relevant for DM13; broadcast status is only channel specific
   * and handled for the complete J1939Dcm
   */
}
#endif

#if (J1939DCM_DM14_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM14Receive()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM14Receive(
  NetworkHandleType currentChannelId,
  P2CONST(PduInfoType, AUTOMATIC, J1939DCM_APPL_DATA) PduInfoPtr,                                                                                    /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  uint8 sourceAddress,
  uint8 destinationAddress,
  PduLengthType payloadLength
  )
{
  J1939Dcm_IgnoreUnusedArgument(currentChannelId)                                                                                                    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /*
   * #10 If the DM is requested from a specific address and the length
   *     of the DM is equivalent to a length of a CAN frame (8 bytes):
   */
  if ((destinationAddress != J1939DCM_ADDRESS_BROADCAST) &&
       (payloadLength == J1939DCM_MEM_ACCESS_MSG_LENGTH))
  {
    J1939Dcm_MemReqParamType lMemRequestInfo;
    J1939Dcm_AddressInfoType lMemAddressInfo;

    /*
     * #20 Collect addressing information for the application
     *     (channel handler and destination and source addresses).
     */
    lMemAddressInfo.Channel            = currentChannelId;
    lMemAddressInfo.DestinationAddress = destinationAddress;
    lMemAddressInfo.SourceAddress      = sourceAddress;

    /* #30 Collect request contents for the application. */
    lMemRequestInfo.Command            = J1939Dcm_DM14GetCommand(PduInfoPtr->SduDataPtr);
    lMemRequestInfo.Key                = J1939Dcm_DM14GetKey(PduInfoPtr->SduDataPtr);
    lMemRequestInfo.Length             = J1939Dcm_DM14GetLength(PduInfoPtr->SduDataPtr);
    lMemRequestInfo.Pointer            = J1939Dcm_DM14GetPointer(PduInfoPtr->SduDataPtr);
    lMemRequestInfo.PointerExtension   = J1939Dcm_DM14GetPointerExt(PduInfoPtr->SduDataPtr);
    lMemRequestInfo.PointerType        = J1939Dcm_DM14GetPointerType(PduInfoPtr->SduDataPtr);

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    /* #40 Check whether a call-out function for the memory access request is configured. */
    if(NULL_PTR == J1939Dcm_Cfg_MemRequestIndicationFunc)                                                                                            /* PRQA S 2992, 2995, 2996 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_MEM_CALLOUT_CHECK */
    {
      J1939Dcm_DetAssertAlways(                                                                                                                      /* PRQA S 2880 */ /* MD_MSR_Unreachable */
        J1939DCM_API_RXINDICATION,
        J1939DCM_E_PARAM_CONFIG
        )
    }
    /* #50 If applicable, pass the addressing information and the request contents to the application. */
    else
# endif
    {
      J1939Dcm_Cfg_MemRequestIndicationFunc(                                                                                                         /* VCA_J1939DCM_POINTER_FORWARD_LOCAL */
        &lMemAddressInfo,
        &lMemRequestInfo
        );
    }
  }
  /* else: broadcast memory access makes no sense; ignore request as broadcast NACK is also not allowed */
  /*   or: data length must be 8 */
}
#endif

#if (J1939DCM_DM17_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_DM17Receive()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_DM17Receive(
  NetworkHandleType currentChannelId,
  P2CONST(PduInfoType, AUTOMATIC, J1939DCM_APPL_DATA) PduInfoPtr,                                                                                    /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  uint8 sourceAddress,
  uint8 destinationAddress,
  PduLengthType payloadLength
  )
{
  J1939Dcm_IgnoreUnusedArgument(currentChannelId)                                                                                                    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 If the diagnostic message is requested from a specific address: */
  if (destinationAddress != J1939DCM_ADDRESS_BROADCAST)
  {
    PduInfoType                 lBootLoadData;
    J1939Dcm_AddressInfoType    lMemAddressInfo;

    /* #20 Collect request contents for the application (message content without meta data). */
    lBootLoadData.SduDataPtr = PduInfoPtr->SduDataPtr;
    lBootLoadData.SduLength  = payloadLength;

    /*
     * #30 Collect addressing information for the application
     *     (channel handler and destination and source addresses).
     */
    lMemAddressInfo.Channel            = currentChannelId;
    lMemAddressInfo.DestinationAddress = destinationAddress;
    lMemAddressInfo.SourceAddress      = sourceAddress;

    /* #40 Check whether a call-out function for the boot load data request is configured. */
    if(NULL_PTR == J1939Dcm_Cfg_MemDataRxIndicationFunc)                                                                                             /* PRQA S 2992, 2995, 2996 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_MEM_CALLOUT_CHECK */
    {
      J1939Dcm_DetAssertAlways(                                                                                                                      /* PRQA S 2880 */ /* MD_MSR_Unreachable */
        J1939DCM_API_RXINDICATION,
        J1939DCM_E_PARAM_CONFIG
        )
    }
    /* #50 If applicable, pass the addressing information and the request contents to the application. */
    else
    {
      J1939Dcm_Cfg_MemDataRxIndicationFunc(                                                                                                          /* VCA_J1939DCM_POINTER_FORWARD_LOCAL */
        J1939DCM_MEM_DATA_BOOTLOAD,
        &lMemAddressInfo,
        &lBootLoadData,
        E_OK
        );
    }
  }
  /* else: broadcast memory access makes no sense; ignore request as broadcast NACK is also not allowed */
}
#endif

#if (J1939DCM_NEED_IF_RECEPTION == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_NetIsNodeOnline()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *

 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(boolean, J1939DCM_CODE)
J1939Dcm_NetIsNodeOnline(
  J1939Dcm_ChannelHdlType currentChannel,                                                                                                            /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  uint8 destinationAddress
  )
{
  J1939Dcm_NodeHdlOptType  lNodeHdl;
  boolean                  lNodeOnline;

  J1939Dcm_IgnoreUnusedArgument(currentChannel)                                                                                                      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  lNodeOnline = FALSE;

  /* If the diagnostic message is requested globally: */
  if (destinationAddress == J1939DCM_ADDRESS_BROADCAST)
  {
    /* Check the communication status of all nodes with the requested channel (broadcast request). */
    for (lNodeHdl = 0u; lNodeHdl < J1939Dcm_GetSizeOfCfg_NodeTable(); ++lNodeHdl)
    {
      if(J1939Dcm_ComStateIsOnlineAny(lNodeHdl))                                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
      {
        lNodeOnline = TRUE;
        break;
      }
    }
  }
  /* Otherwise (if the diagnostic message is requested from a specific address): */
  else
  {
    /* If the destination address of the requested DM references a configured node: */
    lNodeHdl = J1939Dcm_NetGetNodeHdlByAddr(destinationAddress);

    /* Obtain the communication status of the node-channel pair. */
    lNodeOnline = (boolean)(J1939Dcm_ComStateIsOnline(                                                                                               /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* VCA_J1939DCM_FALSE_POSITIVE */
                                 lNodeHdl,
                                 currentChannel
                                 ));
  }

  return lNodeOnline;
}
#endif

#if (((J1939DCM_NEED_IF_RECEPTION  == STD_ON) || \
    (J1939DCM_NEED_TP_RECEPTION == STD_ON)) && \
    (J1939DCM_DEV_ERROR_DETECT == STD_ON))                                                                                                           /* COV_J1939DCM_REQUIRED_BY_SAFEBSW */
/***********************************************************************************************************************
 * J1939Dcm_NetIsRxPduIdValid()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(boolean, J1939DCM_CODE)
J1939Dcm_NetIsRxPduIdValid(
  PduIdType id                                                                                                                                       /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  boolean lResult = TRUE;
  /* #10 Check whether the ID of the RxPdu is less than the total number of the configured RxPdus. */
  if ((id >= J1939Dcm_Cfg_GetRxPduTableSize())
  /* #20 If the configuration variant does not indicate precompile: */
# if (J1939DCM_CONFIGURATION_VARIANT != J1939DCM_CONFIGURATION_VARIANT_PRECOMPILE)
  /* #30 Check whether the incoming RxPdu defined in the RxPdu table has a valid index in the message table. */
    || (!J1939Dcm_IsCfg_MessageTableUsedOfCfg_RxPduTable(id))                                                                                        /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  /* #40 Check whether at least one valid RxPdu exists in RxPdu table. */
    || (0u >= J1939Dcm_Cfg_GetNumberOfExistedRxPdus())
# endif
    )
  {
    lResult = FALSE;
  }
 return lResult;
}
#endif

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_NetIsTxPduIdValid()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(boolean, J1939DCM_CODE)
J1939Dcm_NetIsTxPduIdValid(
  PduIdType id                                                                                                                                       /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  boolean lResult = TRUE;
  /* #10 Check whether the ID of the TxPdu is less than the total number of the configured TxPdus. */
  if ((id >= J1939Dcm_Cfg_GetTxPduTableSize())
  /* #20 If the configuration variant does not indicate precompile: */
# if (J1939DCM_CONFIGURATION_VARIANT != J1939DCM_CONFIGURATION_VARIANT_PRECOMPILE)
  /* #30 Check whether the incoming TxPdu defined in the TxPdu table has a valid index in the message table. */
    || (!J1939Dcm_IsCfg_MessageTableUsedOfCfg_TxPduTable(id))                                                                                        /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  /* #40 Check whether at least one valid TxPdu exists in TxPdu table. */
    || (0u >= J1939Dcm_Cfg_GetNumberOfExistedTxPdus())
# endif
    )
  {
    lResult = FALSE;
  }
  return lResult;
}
#endif

/***********************************************************************************************************************
 * J1939Dcm_NetIsValidOnlineNodeChannel()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(boolean, J1939DCM_CODE)
J1939Dcm_NetIsValidOnlineNodeChannel(
  uint8 apiId,                                                                                                                                       /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  J1939Dcm_NodeHdlType nodeHdl,
  J1939Dcm_ChannelHdlType channelHdl
  )
{
  boolean lResult;
  uint8   lErrorId = J1939DCM_E_NO_ERROR;

  J1939Dcm_IgnoreUnusedArgument(apiId)                                                                                                               /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  lResult = FALSE;

  if(!J1939Dcm_IsValidNodeHdl(nodeHdl))                                                                                                              /* PRQA S 2995 */ /* MD_J1939Dcm_ConstExpr */
  {
    lErrorId = J1939DCM_E_INVALID_NODE;
  }
  else if (!J1939Dcm_IsValidChannelHdl(channelHdl))                                                                                                  /* PRQA S 2995 */ /* MD_J1939Dcm_ConstExpr */
  {
    lErrorId = J1939DCM_E_INVALID_CHANNEL;
  }
  else
#endif
  {
    lResult = (boolean)J1939Dcm_ComStateIsOnline(nodeHdl, channelHdl);                                                                               /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  }

#if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)
  {
    J1939Dcm_DetAssertAlways(
      apiId,
      lErrorId
      )
  }
#else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

  return lResult;
}

/**********************************************************************************************************************
 * J1939Dcm_UtiBufferContextInit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
*********************************************************************************************************************/
J1939DCM_LOCAL_INLINE FUNC(void, J1939DCM_CODE)
J1939Dcm_UtiBufferContextInit(
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBufferContext,
  P2VAR(uint8, AUTOMATIC, J1939DCM_INTERNAL_DATA) pBuffer,
  PduLengthType sduLength,
  PduLengthType bufferLength
  )
{
  pBufferContext->Buffer.SduDataPtr = pBuffer;                                                                                                       /* VCA_J1939DCM_FALSE_POSITIVE */
  pBufferContext->Buffer.SduLength  = sduLength;                                                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
  pBufferContext->AvailLen          = bufferLength;                                                                                                  /* VCA_J1939DCM_FALSE_POSITIVE */
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/* --- Service functions ---------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************
 * J1939Dcm_Init()
 **********************************************************************************************************************/
/*!
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
 *
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_Init(
  P2CONST(J1939Dcm_ConfigType, AUTOMATIC, J1939DCM_INIT_DATA) configPtr                                                                              /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8 lErrorId = J1939DCM_E_NO_ERROR;

  /* #10 If the configuration variant does not indicate precompile: */
#if (J1939DCM_USE_INIT_POINTER == STD_ON)
  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* NULL pointer check is not always needed and is done later for ECUM error reporting */

  /* ----- Implementation ---------------------------------------------------------------------- */
  /* config pointer is set immediately, but will only be used if the validity check below is passed */
  /* #11 Set the configuration pointer. */
  J1939Dcm_Data_ConfigPtr() = configPtr;

  /* post-build loadable: report errors to EcuM     */
  /* post-build selectable: only check init pointer */
  /* #12 If the configuration pointer is NULL: */
  if (configPtr == NULL_PTR)
  {
    /* #13 Set DET error with invalid pointer and inform EcuM. */
    lErrorId = J1939DCM_E_PARAM_POINTER;
    J1939DCM_EcuMReportBswError(ECUM_BSWERROR_NULLPTR)
  }
  /* #14 If configuration variant indicates post build loadable: */
# if (J1939DCM_CONFIGURATION_VARIANT == J1939DCM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
  /*#15 If there is inconsistency in the generator version compatibility: */
  else if (configPtr->CompatibilityVersionOfPBConfig != J1939DCM_GENERATOR_COMPATIBILITY_VERSION)
  {
    /* #16 Report the error to EcuM. */
    J1939DCM_EcuMReportBswError(ECUM_BSWERROR_COMPATIBILITYVERSION)
  }
  /* #17 If there is inconsistency in the magic number: */
  else if (configPtr->FinalMagicNumberOfPBConfig != J1939DCM_FINAL_MAGIC_NUMBER)
  {
    /* #18 Report the error to EcuM. */
    J1939DCM_EcuMReportBswError(ECUM_BSWERROR_MAGICNUMBER)
  }
# endif
# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* #19 Check, whether the size of the postbuild channel table exceeds the size of the table spezified during precompile. */
  else if (J1939Dcm_GetSizeOfCfg_ChannelTable() > J1939DCM_MAX_NUM_CHANNELS)                                                                         /* PRQA S 2742 */ /* MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_NBR_OF_CHANNELS_EQUAL */
  {
    lErrorId = J1939DCM_E_INVALID_CHANNEL;                                                                                                           /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
  /* #20 Check, whether the size of the postbuild node table exceeds the size of the table spezified during precompile. */
  else if (J1939Dcm_GetSizeOfCfg_NodeTable() > J1939DCM_MAX_NUM_NODES)                                                                               /* PRQA S 2742 */ /* MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_NBR_OF_NODES_EQUAL */
  {
    lErrorId = J1939DCM_E_INVALID_NODE;                                                                                                              /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# endif
  /* #21 Otherwise (if no errors were found): */
  else
#else
  J1939Dcm_IgnoreUnusedArgument(configPtr)                                                                                                           /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif /* J1939DCM_USE_INIT_POINTER == STD_ON */
  {
    /* #22 If J11939Dcm is not initialized: */
    if (J1939Dcm_InitState == J1939DCM_STATE_UNINIT)
    {
      /* #23 Initialize and reset J1939Dcm. */
      J1939Dcm_InitState = J1939DCM_STATE_INIT;
      J1939Dcm_Reset();
    }
    /* #24 Otherwise (If J11939Dcm is initialized): */
    else
    {
      /* #25 Notify DET: J1939Dcm was previously initialized. */
      lErrorId = J1939DCM_E_REINIT;   /* SWS_J1939Dcm_00005 */
    }
  }
/* ----- Development Error Report ------------------------------------------------------------ */
#if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)                                                                                                               /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_INIT,
      lErrorId
      )
  }
#else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}                                                                                                                                                    /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
 * J1939Dcm_InitMemory()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_InitMemory(
  void
  )
{
  /* #10 Initialize the statically initialized RAM variables. */
  J1939Dcm_InitState = J1939DCM_STATE_UNINIT;
}

/***********************************************************************************************************************
 * J1939Dcm_DeInit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_DeInit(
  void
  )
{
  uint8 lErrorId = J1939DCM_E_NO_ERROR;

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Insure that J1939Dcm is initialized. */
  if (J1939Dcm_InitState == J1939DCM_STATE_UNINIT)  /* SWS_J1939Dcm_00004 */
  {
    lErrorId = J1939DCM_E_UNINIT;
  }
  else
#endif
  {
    /* #11 Set the state of J1939Dcm to uninitialized. */
    J1939Dcm_InitState = J1939DCM_STATE_UNINIT;    /* SWS_J1939Dcm_00003 */
    /* #12 Reset J1939Dcm. */
    J1939Dcm_Reset();
  }
#if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)                                                                                                               /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_DEINIT,
      lErrorId
      )
  }
#else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}

#if (J1939DCM_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_GetVersionInfo()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, J1939DCM_APPL_DATA) versioninfo
  )
{
  uint8 lErrorId = J1939DCM_E_NO_ERROR;

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Insure that the provided pointer to the version information is not NULL. */
  if (versioninfo == NULL_PTR)
  {
    lErrorId = J1939DCM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* #11 Register the version information. */
    versioninfo->vendorID         = J1939DCM_VENDOR_ID;
    versioninfo->moduleID         = J1939DCM_MODULE_ID;

    versioninfo->sw_major_version = (uint8)J1939DCM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = (uint8)J1939DCM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = (uint8)J1939DCM_SW_PATCH_VERSION;
  }

# if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)                                                                                                               /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_GETVERSIONINFO,
      lErrorId
      )
  }
# else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* J1939Dcm_GetVersionInfo */
#endif /* (J1939DCM_VERSION_INFO_API == STD_ON) */

/***********************************************************************************************************************
 * J1939Dcm_SetState()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939DCM_CODE)
J1939Dcm_SetState(
  NetworkHandleType channel,
  uint8 node,
  J1939Dcm_StateType newState
  )
{
  Std_ReturnType          lResult;
  J1939Dcm_NodeHdlType    lNodeHdl;
  J1939Dcm_ChannelHdlType lChannelHdl;
  J1939Dcm_StateType      lnewState;
  uint8                   lErrorId;

  lResult     = E_NOT_OK;
  lNodeHdl    = J1939Dcm_NetGetNodeHdlById(node);
  lChannelHdl = J1939Dcm_NetGetChannelHdlById(channel);
  lErrorId    = J1939DCM_E_NO_ERROR;

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* SWS_J1939Dcm_00004 */
  if (J1939Dcm_InitState == J1939DCM_STATE_UNINIT)
  {
    lErrorId = J1939DCM_E_UNINIT;
  }
  else if(!J1939Dcm_IsValidNodeHdl(lNodeHdl))                                                                                                        /* PRQA S 2995 */ /* MD_J1939Dcm_ConstExpr */
  {
    lErrorId = J1939DCM_E_INVALID_NODE;
  }
  else if(!J1939Dcm_IsValidChannelHdl(lChannelHdl))                                                                                                  /* PRQA S 2995 */ /* MD_J1939Dcm_ConstExpr */
  {
    lErrorId = J1939DCM_E_INVALID_CHANNEL;
  }
  else if(J1939Dcm_NetIsNodeChannelSupported(lNodeHdl, lChannelHdl) == FALSE)                                                                        /* PRQA S 2742, 2992, 2996, 4304 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr, MD_MSR_AutosarBoolean */ /* COV_J1939DCM_NODE_CHANNEL_SUPPORTED */
  {
    lErrorId = J1939DCM_E_PARAM_CONFIG;                                                                                                              /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
  else
#endif
  {
    J1939Dcm_NodeContextPtrType pNodeContext = &J1939Dcm_DiagContext.NodeContext[lNodeHdl];                                                          /* VCA_J1939DCM_VERIFIED_NODE_ACCESS */

    lnewState = newState;

    /* #16 If the new state indicates offline: */
    if (lnewState == J1939DCM_STATE_OFFLINE)
    {
      /* #17 Set the communication status of the node-channel pair to offline. */
      J1939Dcm_ComStateSetOffline(lNodeHdl, lChannelHdl);                                                                                            /* VCA_J1939DCM_VERIFIED_NODE_ACCESS */
      /* #18 If there is(are) still channel(s) referenced by the requested node in online state: */
      if (pNodeContext->ComState != 0u)
      {
        /*
         * #19 Set the new state to online
         * (the node is online if at least it references one channel that is in online state as well).
         */
        lnewState = J1939DCM_STATE_ONLINE;
      }
      /*
       * else all the channels referenced by that particular node are offline and hence the node
       * communication state shall be offline as well
       */
      /* #20 Indicate successful communication setup. */
      lResult = E_OK;
    }
    /* #21 If the new state indicates online: */
    else if (lnewState == J1939DCM_STATE_ONLINE)
    {
      /* #22 Set the communication status of the node-channel pair to online. */
      J1939Dcm_ComStateSetOnline(lNodeHdl, lChannelHdl);                                                                                             /* VCA_J1939DCM_VERIFIED_NODE_ACCESS */
      /* #23 Indicate successful communication setup. */
      lResult = E_OK;
    }
    /* #24 Otherwise (if the new state does not indicate either online or offline): */
    else
    {
      /* #25 Notify DET: state parameter is out of range. */
      lErrorId = J1939DCM_E_INVALID_STATE; /* SWS_J1939Dcm_00130 */
    }

    /* #26 Update queued communication state change. */
    J1939Dcm_NetUpdateQueuedCommStateChange(lnewState, pNodeContext);
  }

#if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)                                                                                                               /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_SETSTATE,
      lErrorId
      )
  }
#else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

  return lResult;
}                                                                                                                                                    /* PRQA S 6080 */ /* MD_MSR_STMIF */


/* --- Scheduled functions -------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************
 * J1939Dcm_MainFunction()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_MainFunction(
  void
  )
{
  uint8 lErrorId = J1939DCM_E_NO_ERROR;

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Insure that J1939Dcm is initialized. */
  if (J1939Dcm_InitState == J1939DCM_STATE_UNINIT)  /* SWS_J1939Dcm_00004 */
  {
    lErrorId = J1939DCM_E_UNINIT;
  }
  else
#endif
  {
    /* #11 Call J1939Dcm tasks. */
    J1939Dcm_NetTxHandlerTask();

    J1939Dcm_MemHandlerTask();

    J1939Dcm_DM1Task();
    J1939Dcm_DM13Task();
    J1939Dcm_DM35Task();
    J1939Dcm_DMxTask();
  }

#if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_MAINFUNCTION,
      lErrorId
      )
  }
#else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}                                                                                                                                                    /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* --- Callback functions --------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************
 * J1939Dcm_RequestIndication()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_RequestIndication(
  uint8 node,
  NetworkHandleType channel,
  uint32 requestedPgn,
  P2CONST(J1939Rm_ExtIdInfoType, AUTOMATIC, J1939DCM_APPL_DATA) extIdInfo,                                                                           /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  uint8 sourceAddress,
  uint8 destAddress,                                                                                                                                 /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  uint8 priority                                                                                                                                     /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  uint8 lErrorId = J1939DCM_E_NO_ERROR;

  J1939Dcm_IgnoreUnusedArgument(extIdInfo)     /* not needed; DMx messages don't use extended identifier bytes. */                                   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(destAddress)   /* not needed; address is already known through node parameter. */                                    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(priority)      /* not needed; default priority is used. */                                                           /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check whether the module is initialized. */
  if (J1939Dcm_InitState == J1939DCM_STATE_UNINIT)
  {
    lErrorId = J1939DCM_E_UNINIT;
  } /* SWS_J1939Dcm_00004 */
  else
#endif
  {
    J1939Dcm_NodeHdlType    lNodeHdl;
    J1939Dcm_ChannelHdlType lChannelHdl;

    lNodeHdl    = J1939Dcm_NetGetNodeHdlById(node);
    lChannelHdl = J1939Dcm_NetGetChannelHdlById(channel);

    if(J1939Dcm_NetIsValidOnlineNodeChannel(
         J1939DCM_API_REQUESTINDICATION,
         lNodeHdl,
         lChannelHdl) == TRUE)
    {
      uint8                       lResponseAddress;
#if(J1939DCM_NEED_DEM == STD_ON)
      J1939Dcm_NodeContextPtrType pNodeContext = &J1939Dcm_DiagContext.NodeContext[lNodeHdl];                                                        /* VCA_J1939DCM_VERIFIED_NODE_ACCESS */
#endif
      /* #40 Calculate response address. */
      lResponseAddress = J1939Dcm_NetCalculateResponseAddress(
                           sourceAddress,
                           destAddress
                           );

      /* #50 Handle request manager interrupt. */
#if(J1939DCM_NEED_DEM == STD_ON)
      J1939Dcm_NetHandleRmInterrupt(
        pNodeContext,
        lChannelHdl,
        requestedPgn,
        lResponseAddress,
        priority
        );
#else
      J1939Dcm_NetHandleRmErroneousInterrupt(
        lNodeHdl,
        lChannelHdl,
        requestedPgn,
        lResponseAddress,
        priority
        );
#endif
    }
  }

#if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_REQUESTINDICATION,
      lErrorId
      )
  }
#else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}                                                                                                                                                    /* PRQA S 6060 */ /* MD_MSR_STPAR */

/***********************************************************************************************************************
 * J1939Dcm_RxIndication()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_RxIndication(
  PduIdType RxPduId,                                                                                                                                 /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  P2CONST(PduInfoType, AUTOMATIC, J1939DCM_APPL_DATA) PduInfoPtr                                                                                     /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
#if (J1939DCM_NEED_IF_RECEPTION == STD_ON)
  uint8 lErrorId = J1939DCM_E_NO_ERROR;

  /* parameter check */
# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check whether the module is initialized. */
  if (J1939Dcm_InitState == J1939DCM_STATE_UNINIT)
  {
    lErrorId = J1939DCM_E_UNINIT;
  } /* SWS_J1939Dcm_00004 */
  /* #11 Check whether Rx Pdu Id is valid. */
  else if (J1939Dcm_NetIsRxPduIdValid(RxPduId) == FALSE)
  {
    lErrorId = J1939DCM_E_INVALID_PDU_SDU_ID;
  }
  /* #12 Check whether the pointer to the buffer containing the I-PDU (the payload and the meta data) is NULL. */
  else if (PduInfoPtr == NULL_PTR)
  {
    lErrorId = J1939DCM_E_PARAM_POINTER;
  }
  else if (J1939Dcm_Cfg_GetRxPduMetaDataLength(RxPduId) > PduInfoPtr->SduLength)                                                                     /* VCA_J1939DCM_FALSE_POSITIVE */
  {
    lErrorId = J1939DCM_E_PARAM_CONFIG;
  }
  /* #13 Otherwise: */
  else
# endif
  {
    J1939Dcm_ChannelHdlType  lCurrentChannel;
    J1939Dcm_MessageHdlType  lMessageHdl;
    PduLengthType            lPayloadLength;
    uint8                    lSourceAddress;
    uint8                    lDestinationAddress;

    /* #14 Analyse meta data (extract length of the payload, source address, and destination address). */
    lPayloadLength      = PduInfoPtr->SduLength - J1939Dcm_Cfg_GetRxPduMetaDataLength(RxPduId);                                                      /* VCA_J1939DCM_FALSE_POSITIVE */
    lSourceAddress      = PduInfoPtr->SduDataPtr[(lPayloadLength + J1939DCM_METADATA_SA_OFFSET)];                                                    /* PRQA S 2985 */ /* MD_J1939Dcm_Rule2.2_2985 */

    if (J1939Dcm_Cfg_GetRxPduMetaDataLength(RxPduId) < 2u)                                                                                           /* PRQA S 2742 */ /* MD_J1939Dcm_ConstExpr */ /* VCA_J1939DCM_FALSE_POSITIVE */
    {
      lDestinationAddress = J1939Dcm_Cfg_GetRxPduNodeAddress(RxPduId);                                                                               /* PRQA S 2880 */ /* MD_MSR_Unreachable */ /* VCA_J1939DCM_FALSE_POSITIVE */
    }
    else
    {
      lDestinationAddress = PduInfoPtr->SduDataPtr[(lPayloadLength + J1939DCM_METADATA_DA_OFFSET)];
    }

    /* #15 Obtain the local channel and message handles for the incoming RxPdu. */
    lCurrentChannel = J1939Dcm_Cfg_GetRxPduChannelHdl(RxPduId);                                                                                      /* VCA_J1939DCM_FALSE_POSITIVE */
    lMessageHdl     = J1939Dcm_Cfg_GetRxPduMessageHdl(RxPduId);                                                                                      /* VCA_J1939DCM_FALSE_POSITIVE */

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    if( (lDestinationAddress != J1939DCM_ADDRESS_BROADCAST)
      &&(!J1939Dcm_IsValidNodeHdl(J1939Dcm_NetGetNodeHdlByAddr(lDestinationAddress))) )                                                              /* PRQA S 3415 */ /* MD_J1939Dcm_Rule13.5 */
    {
      lErrorId = J1939DCM_E_INVALID_NODE;
    }
    else if(!J1939Dcm_IsValidChannelHdl(lCurrentChannel))                                                                                            /* PRQA S 2992, 2995, 2996 */ /* MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_CHANNEL_HDL_VALID */
    {
      lErrorId = J1939DCM_E_INVALID_CHANNEL;                                                                                                         /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    else if(lMessageHdl >= J1939Dcm_Cfg_GetMessageTableSize())                                                                                       /* PRQA S 2992, 2996 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */
    {
      J1939Dcm_DetAssertAlways(                                                                                                                      /* PRQA S 2880 */ /* MD_MSR_Unreachable */
        J1939DCM_API_RXINDICATION,
        J1939DCM_E_PARAM_CONFIG
        )
    }
    else
# endif
    {
      /* #16 Find out whether any node is online. */
      if(J1939Dcm_NetIsNodeOnline(lCurrentChannel, lDestinationAddress) == TRUE)
      {
        switch (J1939Dcm_Cfg_GetMessageDM(lMessageHdl))
        {
# if (J1939DCM_DM13_SUPPORT == STD_ON)
          /* #19 In case of DM13, receive DM13. */
          case J1939DCM_DM13:
            J1939Dcm_DM13Receive(
              J1939Dcm_Cfg_GetChannelBusType(lCurrentChannel),
              PduInfoPtr
              );
            break;
# endif

# if (J1939DCM_DM14_SUPPORT == STD_ON)
          /* #20 In case of DM14, receive DM14. */
          case J1939DCM_DM14:
            J1939Dcm_DM14Receive(
              J1939Dcm_Cfg_GetChannelId(lCurrentChannel),
              PduInfoPtr,
              lSourceAddress,
              lDestinationAddress,
              lPayloadLength
              );
            break;
# endif

# if (J1939DCM_DM17_SUPPORT == STD_ON)
          /* #21 In case of DM17, receive DM17. */
          case J1939DCM_DM17:
            J1939Dcm_DM17Receive(
              J1939Dcm_Cfg_GetChannelId(lCurrentChannel),
              PduInfoPtr,
              lSourceAddress,
              lDestinationAddress,
              lPayloadLength
              );
            break;
# endif
          /* #22 Otherwise: */
          default:
            /* #23 If the diagnostic message is requested from a specific address: */
            if (lDestinationAddress != J1939DCM_ADDRESS_BROADCAST)                                                                                   /* PRQA S 2995 */ /* MD_J1939Dcm_ConstExpr */
            {
              /* #24 Request sending negative acknowledgement from the request manager. */
              (void)J1939Rm_SendAck(                                                                                                                 /* VCA_J1939DCM_POINTER_FORWARD_NULL */
                      J1939Dcm_Cfg_GetNodeUserId(J1939Dcm_NetGetNodeHdlByAddr(lDestinationAddress)),                                                 /* PRQA S 2842 */ /* MD_J1939Dcm_DerefInvalidPointer */ /* VCA_J1939DCM_FALSE_POSITIVE */
                      J1939Dcm_Cfg_GetChannelId(lCurrentChannel),
                      J1939Dcm_Cfg_GetMessagePGN(lMessageHdl),
                      NULL_PTR,
                      J1939RM_ACK_NEGATIVE,
                      lSourceAddress,
                      J1939DCM_PRIORITY_DEFAULT,
                      FALSE
                      );
            }
            break;
        } /* end: switch DiagMessage */
      }
    }
  }

# if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)                                                                                                               /* PRQA S 2992, 2996 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */
  {
    J1939Dcm_DetAssertAlways(                                                                                                                        /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      J1939DCM_API_RXINDICATION,
      lErrorId
      )
  }
# else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
#else
  J1939Dcm_IgnoreUnusedArgument(RxPduId)                                                                                                             /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(PduInfoPtr)                                                                                                          /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}                                                                                                                                                    /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/***********************************************************************************************************************
 * J1939Dcm_StartOfReception()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
FUNC(BufReq_ReturnType, J1939DCM_CODE)
J1939Dcm_StartOfReception(
  PduIdType id,                                                                                                                                      /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  P2VAR(PduInfoType, AUTOMATIC, J1939DCM_APPL_DATA) info,                                                                                            /* PRQA S 3673, 3206 */ /* MD_MSR_Rule8.13, MD_J1939Dcm_Rule2.7 */
  PduLengthType TpSduLength,                                                                                                                         /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  P2VAR(PduLengthType, AUTOMATIC, J1939DCM_APPL_DATA) bufferSizePtr                                                                                  /* PRQA S 3673, 3206 */ /* MD_MSR_Rule8.13, MD_J1939Dcm_Rule2.7 */
  )
{
  BufReq_ReturnType lBufferResult = BUFREQ_E_NOT_OK;
  uint8             lErrorId      = J1939DCM_E_NO_ERROR;                                                                                             /* PRQA S 2981 */ /* MD_J1939Dcm_Rule2.2_2981 */

  /* #11 If any DM requires TP reception is configured: */
#if (J1939DCM_NEED_TP_RECEPTION == STD_ON)
# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* SWS_J1939Dcm_00004 */
  /* #12 Check whether the module is initialized. */
  if (J1939Dcm_InitState == J1939DCM_STATE_UNINIT)
  {
    lErrorId = J1939DCM_E_UNINIT;
  }
  /* #13 Check plausibility of input parameters */
  else if (J1939Dcm_NetIsRxPduIdValid(id) == FALSE)
  {
    lErrorId = J1939DCM_E_INVALID_PDU_SDU_ID;
  }
  else if ((info == NULL_PTR)
        || (info->SduDataPtr == NULL_PTR)
        || (bufferSizePtr == NULL_PTR))
  {
    lErrorId = J1939DCM_E_PARAM_POINTER;
  }
  else if (info->SduLength < J1939Dcm_Cfg_GetRxPduMetaDataLength(id))                                                                                /* VCA_J1939DCM_FALSE_POSITIVE */
  {
    lErrorId = J1939DCM_E_PARAM_CONFIG;
  }
  else
# endif
  {
    J1939Dcm_NodeHdlType lNodeHdl;
    J1939Dcm_MemDataType lDataKind;
    uint8                lDestinationAddress;

    if (J1939Dcm_Cfg_GetRxPduMetaDataLength(id) < 2u)                                                                                                /* PRQA S 2742 */ /* MD_J1939Dcm_ConstExpr */ /* VCA_J1939DCM_FALSE_POSITIVE */
    {
      lDestinationAddress = J1939Dcm_Cfg_GetRxPduNodeAddress(id);                                                                                    /* PRQA S 2880 */ /* MD_MSR_Unreachable */ /* VCA_J1939DCM_FALSE_POSITIVE */
    }
    else
    {
      lDestinationAddress = info->SduDataPtr[(info->SduLength - J1939Dcm_Cfg_GetRxPduMetaDataLength(id)) + J1939DCM_METADATA_DA_OFFSET];             /* VCA_J1939DCM_FALSE_POSITIVE */
    }

    lNodeHdl = J1939Dcm_NetGetNodeHdlByAddr(lDestinationAddress);

    /* if the destination address match the preferred address */
    if (lNodeHdl != J1939DCM_INVALID_NODE_HDL)
    {
      /* #20 Obtain the kind of the incoming message (the definition is equal to related DM). */
      lDataKind = J1939Dcm_Cfg_GetMessageDM(J1939Dcm_Cfg_GetRxPduMessageHdl(id));                                                                    /* VCA_J1939DCM_FALSE_POSITIVE */

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
      /* #21 Check whether the incoming message is binary data transfer or data security. */
      if((lDataKind != J1939DCM_MEM_DATA_BINARY) && (lDataKind != J1939DCM_MEM_DATA_SECURITY))
      {
        lErrorId = J1939DCM_E_PARAM_CONFIG;
      }
      else if(NULL_PTR == J1939Dcm_Cfg_MemDataStartOfReceptionFunc)                                                                                  /* PRQA S 2992, 2996 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_MEM_CALLOUT_CHECK */
      {
        lErrorId = J1939DCM_E_PARAM_CONFIG;                                                                                                          /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      }
      else
# endif
      {
        if(J1939Dcm_NetIsValidOnlineNodeChannel(
            J1939DCM_API_STARTOFRECEPTION,
            lNodeHdl,
            J1939Dcm_Cfg_GetRxPduChannelHdl(id)) == TRUE)                                                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
        {
          J1939Dcm_RxHandlerPtrType pRxHandler = &J1939Dcm_DiagContext.CommonContext.RxHandlerState;

          /*
          * #23 Enter critical section (Reason: protect data consistency of the reception handler
          *     state against another PduR interruption).
          */
          J1939Dcm_EnterCritical();

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
          /* #24 Check whether there is no other TP reception in progress. */
          if (pRxHandler->RxPduId != J1939DCM_INVALID_PDU_ID)
          {
            lErrorId = J1939DCM_E_INVALID_STATE;
          }
          else
# endif
          {
            pRxHandler->RxPduId = id;
            lBufferResult       = BUFREQ_OK;
          }

          /* #25 Leave critical section. */
          J1939Dcm_ExitCritical();

          if (lBufferResult == BUFREQ_OK)                                                                                                            /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */
          {
            /*
            * #27 Update reception handler state
            *    (memory access address info from meta data) to be used later in the Copy received data function.
            */
            pRxHandler->RxAddressInfo.Channel            = J1939Dcm_Cfg_GetChannelId(J1939Dcm_Cfg_GetRxPduChannelHdl(id));                           /* VCA_J1939DCM_FALSE_POSITIVE */
            pRxHandler->RxAddressInfo.DestinationAddress = lDestinationAddress;
            pRxHandler->RxAddressInfo.SourceAddress      = info->SduDataPtr[(info->SduLength - J1939Dcm_Cfg_GetRxPduMetaDataLength(id)) +            /* PRQA S 2985 */ /* MD_J1939Dcm_Rule2.2_2985 */ /* VCA_J1939DCM_FALSE_POSITIVE */
                                                                             J1939DCM_METADATA_SA_OFFSET];

            /* #29 Inform the application with the a start of a message reception (DM16 or DM18). */
            lBufferResult = J1939Dcm_Cfg_MemDataStartOfReceptionFunc(                                                                                /* VCA_J1939DCM_POINTER_FORWARD_COMBINED */
                              lDataKind,
                              &pRxHandler->RxAddressInfo,
                              TpSduLength,
                              bufferSizePtr
                              );
          }
        }
      }
    }
    /*
     * else: The destination address does not match the preferred address or it is the broadcast address. Return BUFREQ_E_NOT_OK.
     *       For the broadcast address also BUFREQ_E_NOT_OK is returned, because of the only supported DMs with TP reception are DM16
     *       and DM18. Both DMs shall not be requested with a broadcast address.
     */
  }
#else
  /* #30 Otherwise (If none of the DMs that require TP reception is configured): */
  J1939Dcm_IgnoreUnusedArgument(id)                                                                                                                  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(info)                                                                                                                /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(TpSduLength)                                                                                                         /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(bufferSizePtr)                                                                                                       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #31 Notify DET: invalid configuration. */
  lErrorId = J1939DCM_E_PARAM_CONFIG;
#endif

#if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)                                                                                                               /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_DET_ALWAYS_REPORTED */
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_STARTOFRECEPTION,
      lErrorId
      )
  }
#else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

  return lBufferResult;
}                                                                                                                                                    /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */

/***********************************************************************************************************************
 * J1939Dcm_CopyRxData()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
FUNC(BufReq_ReturnType, J1939DCM_CODE)
J1939Dcm_CopyRxData(
  PduIdType id,                                                                                                                                      /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  P2VAR(PduInfoType, AUTOMATIC, J1939DCM_APPL_DATA) info,                                                                                            /* PRQA S 3673, 3206 */ /* MD_MSR_Rule8.13, MD_J1939Dcm_Rule2.7 */
  P2VAR(PduLengthType, AUTOMATIC, J1939DCM_APPL_DATA) bufferSizePtr                                                                                  /* PRQA S 3673, 3206 */ /* MD_MSR_Rule8.13, MD_J1939Dcm_Rule2.7 */
  )
{
  /* #10 Assume unsuccessful copying process from the PduR buffer to the application buffer. */
  BufReq_ReturnType lBufferResult = BUFREQ_E_NOT_OK;                                                                                                 /* PRQA S 2981 */ /* MD_J1939Dcm_Rule2.2_2981 */
  uint8             lErrorId      = J1939DCM_E_NO_ERROR;                                                                                             /* PRQA S 2981 */ /* MD_J1939Dcm_Rule2.2_2981 */

  /* #11 If any DM requires TP reception is configured: */
#if (J1939DCM_NEED_TP_RECEPTION == STD_ON)
# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* #12 Check whether the module is initialized. */
  if (J1939Dcm_InitState == J1939DCM_STATE_UNINIT)
  {
    lErrorId = J1939DCM_E_UNINIT;
  }
  /* #13 Check plausibility of input parameters. */
  else if (J1939Dcm_NetIsRxPduIdValid(id) == FALSE)
  {
    lErrorId = J1939DCM_E_INVALID_PDU_SDU_ID;
  }
  else if (info == NULL_PTR)
  {
    lErrorId = J1939DCM_E_PARAM_POINTER;
  }
  else if (bufferSizePtr == NULL_PTR)
  {
    lErrorId = J1939DCM_E_PARAM_POINTER;
  }
  else if(J1939Dcm_Cfg_MemDataCopyRxFunc == NULL_PTR)                                                                                                /* PRQA S 2992, 2996 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_MEM_CALLOUT_CHECK */
  {
    lErrorId = J1939DCM_E_PARAM_CONFIG;                                                                                                              /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
  else
# endif
  {
    J1939Dcm_RxHandlerPtrType pRxHandler = &J1939Dcm_DiagContext.CommonContext.RxHandlerState;
    J1939Dcm_NodeHdlType      lNodeHdl;

    /*
     * #15 Enter critical section
     *     (Reason: protect data consistency of the reception handler state against PduR interruptions).
     */
    J1939Dcm_EnterCritical();

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    /* #16 Check whether the RxPduId is consistent with the one indicated by the reception handler state. */
    if (id != pRxHandler->RxPduId)
    {
      lErrorId = J1939DCM_E_INVALID_STATE;
    }
    else
# endif
    {
      lBufferResult = BUFREQ_OK;
    }

    /* #17 Leave critical section. */
    J1939Dcm_ExitCritical();

    /* #18 If RxPduId is equal to the the one indicated by the reception handler state. */
    if (lBufferResult == BUFREQ_OK)                                                                                                                  /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */
    {
      /* If RxPduId for reception handler State is set correctly, the other parameters can be expected as correct. */
      /* Checks on data kind and node handle have been done already in the start of reception function */

      /* #20 Obtain the local node handle. */
      lNodeHdl = J1939Dcm_NetGetNodeHdlByAddr(pRxHandler->RxAddressInfo.DestinationAddress);

      /* #21 Check whether node channel combination is valid. */
      if(J1939Dcm_NetIsValidOnlineNodeChannel(
           J1939DCM_API_COPYRXDATA,
           lNodeHdl,
           J1939Dcm_Cfg_GetRxPduChannelHdl(id)) == TRUE)                                                                                        /* VCA_J1939DCM_FALSE_POSITIVE */
      {
        /* #29 Trigger the application to copy the data from PduR. */
        /* The application is notified each time this function is executed. Therefore, this function is reentrant. */
        lBufferResult = J1939Dcm_Cfg_MemDataCopyRxFunc(                                                                                              /* VCA_J1939DCM_POINTER_FORWARD_COMBINED */
                          J1939Dcm_Cfg_GetMessageDM(J1939Dcm_Cfg_GetRxPduMessageHdl(id)),                                                            /* VCA_J1939DCM_FALSE_POSITIVE */
                          &pRxHandler->RxAddressInfo,
                          info,
                          bufferSizePtr
                          );
      }
    }
  }
#else
  /* #30 Otherwise (If none of the DMs that require TP reception is configured): */
  J1939Dcm_IgnoreUnusedArgument(id)                                                                                                                  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(info)                                                                                                                /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(bufferSizePtr)                                                                                                       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #31 Notify DET: invalid configuration. */
  lErrorId = J1939DCM_E_PARAM_CONFIG;
#endif

#if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)                                                                                                               /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_DET_ALWAYS_REPORTED */
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_COPYRXDATA,
      lErrorId
      )
  }
#else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

  return lBufferResult;
}                                                                                                                                                    /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
 * J1939Dcm_TpRxIndication()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_TpRxIndication(
  PduIdType id,                                                                                                                                      /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  Std_ReturnType result                                                                                                                              /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  uint8 lErrorId = J1939DCM_E_NO_ERROR;                                                                                                              /* PRQA S 2981 */ /* MD_J1939Dcm_Rule2.2_2981 */

  /* #10 If any DM that needs transport protocol is configured: */
#if (J1939DCM_NEED_TP_RECEPTION == STD_ON)
# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* #11 Check whether the module is initialized. */
  if (J1939Dcm_InitState == J1939DCM_STATE_UNINIT)
  {
    lErrorId = J1939DCM_E_UNINIT;
  } /* SWS_J1939Dcm_00004 */
  /* #12 Check plausibility of input parameters. */
  else if (J1939Dcm_NetIsRxPduIdValid(id) == FALSE)
  {
    lErrorId = J1939DCM_E_INVALID_PDU_SDU_ID;
  }
  else if (NULL_PTR == J1939Dcm_Cfg_MemDataRxIndicationFunc)                                                                                         /* PRQA S 2992, 2995, 2996, 2880 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr, MD_MSR_Unreachable */ /* COV_J1939DCM_MEM_CALLOUT_CHECK */
  {
    lErrorId = J1939DCM_E_PARAM_CONFIG;                                                                                                              /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
  else
# endif
  {
    J1939Dcm_RxHandlerReadPtrType pRxHandler = &J1939Dcm_DiagContext.CommonContext.RxHandlerState;
    J1939Dcm_NodeHdlType          lNodeHdl;
    J1939Dcm_AddressInfoType      lMemAddressInfo;
    Std_ReturnType                lRxPduResult = E_NOT_OK;                                                                                           /* PRQA S 2981 */ /* MD_J1939Dcm_Rule2.2_2981 */

    /*
     * #13 Enter critical section
     *     (Reason: protect data consistency of the queue of events against another PduR interruption).
     */
    J1939Dcm_EnterCritical();

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    /* #16 Check whether the requested Rx Pdu Id is consistent with the corresponding Id indicated by the Rx handler state. */
    if (id != pRxHandler->RxPduId)
    {
      lErrorId = J1939DCM_E_INVALID_STATE;
    }
    else
# endif
    {
      lRxPduResult = E_OK;
    }

    /* #17 Leave critical section. */
    J1939Dcm_ExitCritical();

    /* #18 If RxPduId is equal to the the one indicated by the reception handler state. */
    if (lRxPduResult == E_OK)                                                                                                                        /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */
    {
      /* #20 Obtain the local node handle. */
      lNodeHdl = J1939Dcm_NetGetNodeHdlByAddr(pRxHandler->RxAddressInfo.DestinationAddress);

      /* #22 Check whether node channel combination is valid. */
      if(J1939Dcm_NetIsValidOnlineNodeChannel(
           J1939DCM_API_TPRXINDICATION,
           lNodeHdl,
           J1939Dcm_Cfg_GetRxPduChannelHdl(id)) == TRUE)                                                                                             /* VCA_J1939DCM_FALSE_POSITIVE */
      {
        /* #24 Copy the Rx handler state to a local parameter. */
        lMemAddressInfo.Channel            = pRxHandler->RxAddressInfo.Channel;
        lMemAddressInfo.DestinationAddress = pRxHandler->RxAddressInfo.DestinationAddress;
        lMemAddressInfo.SourceAddress      = pRxHandler->RxAddressInfo.SourceAddress;

        /* successfully or not: TP reception is now finished */
        /* #26 Reset Rx handler. */
        J1939Dcm_NetRxHandlerReset();

        /* #28 Callout to application to indicate that TP reception is finished. */
        J1939Dcm_Cfg_MemDataRxIndicationFunc(                                                                                                          /* VCA_J1939DCM_POINTER_FORWARD_COMBINED */
          J1939Dcm_Cfg_GetMessageDM(J1939Dcm_Cfg_GetRxPduMessageHdl(id)),                                                                              /* VCA_J1939DCM_FALSE_POSITIVE */
          &lMemAddressInfo,
          NULL_PTR,
          result
          );
      }
    }
  }
#else
  /* #30 Otherwise (if there are no DM that needs transport protocol is configured): */
  J1939Dcm_IgnoreUnusedArgument(id)                                                                                                                  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(result)                                                                                                              /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #40 Notify DET: invalid configuration. */
  lErrorId = J1939DCM_E_PARAM_CONFIG;
#endif

#if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)                                                                                                               /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_DET_ALWAYS_REPORTED */
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_TPRXINDICATION,
      lErrorId
      )
  }
#else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}                                                                                                                                                    /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/***********************************************************************************************************************
 * J1939Dcm_CopyTxData()
 **********************************************************************************************************************/
/*!
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
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(BufReq_ReturnType, J1939DCM_CODE)
J1939Dcm_CopyTxData(
  PduIdType id,                                                                                                                                      /* PRQA S 3206, 3673 */ /* MD_J1939Dcm_Rule2.7, MD_MSR_Rule8.13 */
  P2VAR(PduInfoType, AUTOMATIC, J1939DCM_APPL_DATA) info,                                                                                            /* PRQA S 3206, 3673 */ /* MD_J1939Dcm_Rule2.7, MD_MSR_Rule8.13 */
  P2VAR(RetryInfoType, AUTOMATIC, J1939DCM_APPL_DATA) retry,                                                                                         /* PRQA S 3673, 3206 */ /* MD_MSR_Rule8.13, MD_J1939Dcm_Rule2.7 */
  P2VAR(PduLengthType, AUTOMATIC, J1939DCM_APPL_DATA) availableDataPtr                                                                               /* PRQA S 3206, 3673 */ /* MD_J1939Dcm_Rule2.7, MD_MSR_Rule8.13 */
  )
{
  BufReq_ReturnType lResult  = BUFREQ_E_NOT_OK;
  uint8             lErrorId = J1939DCM_E_NO_ERROR;                                                                                                  /* PRQA S 2981 */ /* MD_J1939Dcm_Rule2.2_2981 */

  /* This function is called several times by the PduR to transmit a response of a DM. */
  /* The confirmation only comes when the complete message is transmitted, then the application is notified. */
  /* Therefore, this function cannot be reentrant. */
  /* #11 If any DM requires TP transmission is configured: */
#if (J1939DCM_NEED_TP_TRANSMISSION == STD_ON)
# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* SWS_J1939Dcm_00004 */
  /* #12 Check whether the module is initialized. */
  if (J1939Dcm_InitState == J1939DCM_STATE_UNINIT)
  {
    lErrorId = J1939DCM_E_UNINIT;
  }
  else if (J1939Dcm_NetIsTxPduIdValid(id) == FALSE)
  {
    lErrorId = J1939DCM_E_INVALID_PDU_SDU_ID;
  }
  else if( (info == NULL_PTR)
         ||(availableDataPtr == NULL_PTR) )
  {
    lErrorId = J1939DCM_E_PARAM_POINTER;
  }
  else
# endif
  {
    J1939Dcm_TxHandlerPtrType pTxHandler = &J1939Dcm_DiagContext.CommonContext.TxHandlerState;
    J1939Dcm_ChannelHdlType   lChannelHdl;
    uint8_least               lDiagMessage;
    PduLengthType             lCopyIndex;
    PduLengthType             lBufferIndex;

    lChannelHdl  = J1939Dcm_Cfg_GetTxPduChannelHdl(id);                                                                                              /* VCA_J1939DCM_FALSE_POSITIVE */
    lDiagMessage = J1939Dcm_Cfg_GetMessageDM(J1939Dcm_Cfg_GetTxPduMessageHdl(id));                                                                   /* VCA_J1939DCM_FALSE_POSITIVE */

    /*
     * #18 Enter critical section
     *     (Reason: protect data consistency of the transmission handler state against another PduR interrupt).
     */
    J1939Dcm_EnterCritical();

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    if(!J1939Dcm_IsValidNodeHdl(pTxHandler->NodeHdl))                                                                                                /* PRQA S 2995, 2992 */ /* MD_J1939Dcm_ConstExpr */
    {
      lErrorId = J1939DCM_E_INVALID_NODE;                                                                                                            /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    else if (!J1939Dcm_IsValidChannelHdl(lChannelHdl))                                                                                               /* PRQA S 2992, 2995, 2996 */ /* MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_CHANNEL_HDL_VALID */
    {
      lErrorId = J1939DCM_E_INVALID_CHANNEL;                                                                                                         /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    else
# endif
    {
      if(J1939Dcm_ComStateIsOnline(pTxHandler->NodeHdl, lChannelHdl))                                                                                /* VCA_J1939DCM_FALSE_POSITIVE */
      {
        lBufferIndex = pTxHandler->BufferIndex[lChannelHdl];                                                                                         /* VCA_J1939DCM_FALSE_POSITIVE */
        /* #21 If the requested message is consistent with the DM indicated by the transmission handler state: */
        if( (lDiagMessage == pTxHandler->DM)
          /* Tx Handler prepared and Pdu-DM is consistent */
          /* #22 If no transmission retry is required: */
          &&((retry == NULL_PTR) || (retry->TpDataState != TP_DATARETRY))
          /*
          * #23 If there is still data in the buffer of the transmission handler state to be copied
           *     or the PduR requires to copy no data (request for buffer size):
          */
          &&((lBufferIndex < pTxHandler->BufferContext->Buffer.SduLength) || (info->SduLength == 0u))
          /* message not yet completely transmitted or request for buffer size */
          /* #24 If there is enough buffer remaining in the transmission handler state to fill the buffer provided by the PduR: */
          &&(info->SduLength <= (pTxHandler->BufferContext->Buffer.SduLength - lBufferIndex)) )
        {
          /* enough buffer remaining; copy data */
          /* #25 Copy the data. */
          lCopyIndex = 0u;
          while (lCopyIndex < info->SduLength)
          {
            info->SduDataPtr[lCopyIndex] = pTxHandler->BufferContext->Buffer.SduDataPtr[(lBufferIndex + lCopyIndex)];                                /* VCA_J1939DCM_COPY_TO_PDUINFO */
            lCopyIndex++;
          }

          /*
          * #26 Update the buffer index and the pointer to the available data in the
          *     buffer of the transmission handler state.
          */

          lBufferIndex += info->SduLength;
          pTxHandler->BufferIndex[lChannelHdl] = lBufferIndex;                                                                                       /* VCA_J1939DCM_VERIFIED_CHANNEL_ACCESS */

          *availableDataPtr = (PduLengthType)(pTxHandler->BufferContext->Buffer.SduLength - lBufferIndex);
          /* #27 Return successful copying process. */
          lResult = BUFREQ_OK;
        }
        /*
        * else: TxHandler not prepared or not prepared for requested DM, Or
        *       Error in a message transmission occured. Stop transmission till further notice, Or
        *       message already completed; reject!, Or
        *       lower layer requests more data than overall message length; reject.
        */
      }
    }

    /* #28 Leave critical section. */
    J1939Dcm_ExitCritical();
  }
  /* #29 Otherwise (If none of the DMs that require TP transmission is configured): */
#else
  /* no DM configured which needs transmission via TP */
  J1939Dcm_IgnoreUnusedArgument(id)                                                                                                                  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(info)                                                                                                                /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(retry)                                                                                                               /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(availableDataPtr)                                                                                                    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #30 Notify DET: invalid configuration. */
  lErrorId = J1939DCM_E_PARAM_CONFIG;
#endif

#if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)                                                                                                               /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_ALWAYS_TRUE_IN_CFG_WITHOUT_TP */
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_COPYTXDATA,
      lErrorId
      )
  }
#else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

  return lResult;
}                                                                                                                                                    /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
 * J1939Dcm_TpTxConfirmation()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_TpTxConfirmation(
  PduIdType id,
  Std_ReturnType result
  )
{
  uint8 lErrorId = J1939DCM_E_NO_ERROR;                                                                                                              /* PRQA S 2981 */ /* MD_J1939Dcm_Rule2.2_2981 */

  /* #10 If any DM requires TP transmission is configured: */
#if (J1939DCM_NEED_TP_TRANSMISSION == STD_ON)
  J1939Dcm_NodeHdlType    lNodeHdl = J1939DCM_INVALID_NODE_HDL;                                                                                      /* PRQA S 2981 */ /* MD_J1939Dcm_Rule2.2_2981 */
  uint8_least             lDiagMessage;
  boolean                 lCallApplication = FALSE;

  /* parameter check */
# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* SWS_J1939Dcm_00004 */
  /* #11 Check whether the module is initialized. */
  if (J1939Dcm_InitState == J1939DCM_STATE_UNINIT)
  {
    lErrorId = J1939DCM_E_UNINIT;
  }
  /* #12 Check whether Tx Pdu Id is valid. */
  else if (J1939Dcm_NetIsTxPduIdValid(id) == FALSE)
  {
    lErrorId = J1939DCM_E_INVALID_PDU_SDU_ID;
  }
  else
# endif
  {
    lDiagMessage = J1939Dcm_Cfg_GetMessageDM(J1939Dcm_Cfg_GetTxPduMessageHdl(id));                                                                   /* VCA_J1939DCM_FALSE_POSITIVE */

    /* #13 Check whether the obtained local channel handle is valid.  */
# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    if(!J1939Dcm_IsValidChannelHdl(J1939Dcm_Cfg_GetTxPduChannelHdl(id)))                                                                             /* PRQA S 2992, 2995, 2996, 2742 */ /* MD_J1939Dcm_ConstExpr */ /* VCA_J1939DCM_FALSE_POSITIVE */ /* COV_J1939DCM_CHANNEL_HDL_VALID */
    {
      lErrorId = J1939DCM_E_INVALID_CHANNEL;                                                                                                         /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    else
# endif
    {
      J1939Dcm_TxHandlerPtrType pTxHandler = &J1939Dcm_DiagContext.CommonContext.TxHandlerState;

      /* #14 Enter critical section (Reason: protect data consistency of the transmission handler state). */
      J1939Dcm_EnterCritical();

      /*
       * #15 If the requested message is consistent with the DM indicated by the transmission handler
       *     state and at least one channel is still waiting for transmission confirmation:
       */
      if ((lDiagMessage == pTxHandler->DM) && (pTxHandler->UnconfirmedChannels > 0u))
      {
        /* #16 Mark the channel as confirmed (a transmission is in progress for the received TxPdu).  */
        pTxHandler->UnconfirmedChannels--;                                                                                                           /* PRQA S 3387 */ /* MD_J1939Dcm_OptimizedInlineCode_3387 */

        if (pTxHandler->UnconfirmedChannels == 0u)
        {
          /* TxHandler ensures that only one node at a time can trigger a transmission (Via transmission handler prepare) */
          /* therefore this confirmation must belong to the node which currently uses the TxHandler */
          lNodeHdl = pTxHandler->NodeHdl;

          lCallApplication = TRUE;
        } /* else: there are still channels waiting for a Tx Confirmation (may happen on DM1 broadcast transmission) */
      }

      /* #17 Leave critical section. */
      J1939Dcm_ExitCritical();

      /* #18 If confirmations for all channels belong to the current node are received: */
      if (lCallApplication == TRUE)
      {
        /* #19 Finalize the transmission (on the node level). */
        J1939Dcm_NetTxHandlerConfirm(
          lNodeHdl,
          lDiagMessage,
          result,
          J1939DCM_API_TPTXCONFIRMATION
          );
      }
    }
  }
#else
  /* #22 Otherwise (If none of the DMs that require TP transmission is configured): */
  J1939Dcm_IgnoreUnusedArgument(id)                                                                                                                  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  J1939Dcm_IgnoreUnusedArgument(result)                                                                                                              /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #23 Notify DET: invalid configuration. */
  lErrorId = J1939DCM_E_PARAM_CONFIG;
#endif

#if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)                                                                                                               /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_ALWAYS_TRUE_IN_CFG_WITHOUT_TP */
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_TPTXCONFIRMATION,
      lErrorId
      )
  }
#else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}                                                                                                                                                    /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
 * J1939Dcm_TxConfirmation()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_TxConfirmation(
  PduIdType id                                                                                                                                       /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  uint8 lErrorId = J1939DCM_E_NO_ERROR;                                                                                                              /* PRQA S 2981 */ /* MD_J1939Dcm_Rule2.2_2981 */

  /* #10 If any DM requires IF transmission is configured: */
#if (J1939DCM_NEED_IF_TRANSMISSION == STD_ON)

  /* parameter check */
# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* SWS_J1939Dcm_00004 */
  /* #11 Check whether the module is initialized. */
  if (J1939Dcm_InitState == J1939DCM_STATE_UNINIT)
  {
    lErrorId = J1939DCM_E_UNINIT;
  }
  /* #12 Check whether Tx Pdu Id is valid. */
  else if (J1939Dcm_NetIsTxPduIdValid(id) == FALSE)
  {
    lErrorId = J1939DCM_E_INVALID_PDU_SDU_ID;
  }
  else
# endif
  {
    uint8_least lDiagMessage;

    lDiagMessage = J1939Dcm_Cfg_GetMessageDM(J1939Dcm_Cfg_GetTxPduMessageHdl(id));                                                                   /* VCA_J1939DCM_FALSE_POSITIVE */

    /* #13 Check whether the obtained local channel handle is valid.  */
# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
    if(!J1939Dcm_IsValidChannelHdl(J1939Dcm_Cfg_GetTxPduChannelHdl(id)))                                                                             /* PRQA S 2742, 2992, 2995, 2996 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* VCA_J1939DCM_FALSE_POSITIVE */ /* COV_J1939DCM_CHANNEL_HDL_VALID */
    {
      lErrorId = J1939DCM_E_INVALID_CHANNEL;                                                                                                         /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    else
# endif
    {
      J1939Dcm_TxHandlerReadPtrType pTxHandler = &J1939Dcm_DiagContext.CommonContext.TxHandlerState;
      J1939Dcm_NodeHdlType          lNodeHdl;
      uint8                         lTxHandlerDm;

      /* #14 Enter critical section (Reason: protect data consistency of the transmission handler state). */
      J1939Dcm_EnterCritical();

      /* #15 Update the node handle of the transmission handler state. */
      lNodeHdl     = pTxHandler->NodeHdl;
      lTxHandlerDm = pTxHandler->DM;

      /* #16 Leave critical section. */
      J1939Dcm_ExitCritical();

      /* #20 If the requested message is consistent with the DM indicated by the transmission handler state: */
      if (lDiagMessage == lTxHandlerDm)
      {
        /*
         * note: as all IF messages are always transmitted on only one channel,
         * transmission confirmation counter is not required like in TP transmission confirmation function.
         */
        /* notify message handler (for IF transmission, result is always ok) */

        /* #18 Finalize the transmission (on the node level). */
        J1939Dcm_NetTxHandlerConfirm(
          lNodeHdl,
          lDiagMessage,
          E_OK,
          J1939DCM_API_TXCONFIRMATION
          );
      }
      /*
       * #30 Otherwise
       *     (if the requested message is not consistent with the DM indicated by the transmission handler state):
       *     unexpected confirmation -> ignore
       */
    }
  }
  /* #40 Otherwise (If none of the DMs that require TP transmission is configured): */
#else
  /* no DM configured which needs transmission via IF */
  J1939Dcm_IgnoreUnusedArgument(id)                                                                                                                  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #50 Notify DET: invalid configuration. */
  lErrorId = J1939DCM_E_PARAM_CONFIG;
#endif

#if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)                                                                                                               /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */ /* COV_J1939DCM_DET_ALWAYS_REPORTED */
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_TXCONFIRMATION,
      lErrorId
      )
  }
#else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}                                                                                                                                                    /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
 * J1939Dcm_DemTriggerOnDTCStatus()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_DemTriggerOnDTCStatus(
  uint32 DTC,                                                                                                                                        /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  uint8 ClientId                                                                                                                                     /* PRQA S 3206 */ /* MD_J1939Dcm_Rule2.7 */
  )
{
  uint8 lErrorId = J1939DCM_E_NO_ERROR;

#if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check whether J1939Dcm is initialized. */
  if(J1939Dcm_InitState == J1939DCM_STATE_UNINIT)
  {
    lErrorId = J1939DCM_E_UNINIT;
  }
  else
#endif
  {
    J1939Dcm_IgnoreUnusedArgument(DTC)                                                                                                               /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    J1939Dcm_IgnoreUnusedArgument(ClientId)                                                                                                          /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

    /* #11 If DM1 is supported: */
#if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
    /* #12 If DM13 is supported, then at least one channel has to be active. */
    /*
     * [J1939-73]
     * Network devices should look for the Hold Signal to be absent for more than 6
     * seconds before recording any applicable DTCs.
     */
# if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
    if (J1939Dcm_DiagContext.CommonContext.DM13State.NumActiveBroadcastChannels != 0u)
# endif
    {
      J1939Dcm_NodeHdlOptType lNodeHdl;

      /* #13 Iterate over the configured nodes. */
      for (lNodeHdl = 0u; lNodeHdl < J1939Dcm_GetSizeOfCfg_NodeTable(); ++lNodeHdl)
      {
        /*
         * #14 Enter critical section
         *     (Reason: protect data consistency of the queue of events against request manager interruptions).
         */
        J1939Dcm_EnterCritical();

        /*#15 Queue DTC status change for all nodes. */
        J1939Dcm_QueueBitOpSet(&J1939Dcm_DiagContext.NodeContext[lNodeHdl].DM1Queue, J1939DCM_QUEUE_DTC);                                            /* VCA_J1939DCM_VERIFIED_NODE_ACCESS */

        /* #16 Leave critical section. */
        J1939Dcm_ExitCritical();
      }
    } /* else: broadcast is disabled on all channels; transmission will be rejected anyway by BswM */
#endif /* (J1939DCM_NEED_DM1_PROCESSOR == STD_ON) */
  }

#if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_DEMTRIGGERONDTCSTATUS,
      lErrorId
      )
  }
#else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}

#if (J1939DCM_DM15_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * J1939Dcm_MemResponseTransmit()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939DCM_CODE)
J1939Dcm_MemResponseTransmit(
  P2CONST(J1939Dcm_AddressInfoType, AUTOMATIC, J1939DCM_APPL_DATA) AddressInfo,
  P2CONST(J1939Dcm_MemRespParamType, AUTOMATIC, J1939DCM_APPL_DATA) MemResponseParameter
  )
{
  /* This function is called by the application to transmit a response of a DM. */
  /* The application is notified when J1939Dcm receives a confirmation. */
  /* Therefore, this function cannot be reentrant. */
  Std_ReturnType TxResult = E_NOT_OK;
  uint8          lErrorId = J1939DCM_E_NO_ERROR;

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  if (J1939Dcm_InitState == J1939DCM_STATE_UNINIT)
  {
    lErrorId = J1939DCM_E_UNINIT;
  } /* SWS_J1939Dcm_00004 */
  else
# endif
  {
    J1939Dcm_TxPduContextType lTxPduContext;
    J1939Dcm_NodeHdlType      lNodeHdl;
    J1939Dcm_ChannelHdlType   lChannelHdl;

    lNodeHdl    = J1939Dcm_NetGetNodeHdlByAddr(AddressInfo->SourceAddress);
    lChannelHdl = J1939Dcm_NetGetChannelHdlById(AddressInfo->Channel);

    if(J1939Dcm_NetIsValidOnlineNodeChannel(
         J1939DCM_API_MEMRESPONSETRANSMIT,
         lNodeHdl,
         lChannelHdl) == TRUE)
    {
      /* #14 Obtain the corresponding TxPdu Id for DM15 transmitted from the source node via the requested channel. */
      lTxPduContext = J1939Dcm_UtiGetPeerTxPduContextByDM(                                                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
                        lNodeHdl,
                        lChannelHdl,
                        J1939DCM_DM15
                        );

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
      if (lTxPduContext.PduId == J1939DCM_INVALID_PDU_ID)
      {
        lErrorId = J1939DCM_E_PARAM_CONFIG;
      }
      else
# endif
      {
        J1939Dcm_MemHandlerPtrType pMemHandler = &J1939Dcm_DiagContext.CommonContext.MemHandlerState;
        /*
         * #17 Enter critical section
         *     (Reason: protect data consistency of the memory handler state against another CDD interruption).
         */
        J1939Dcm_EnterCritical();

        /* #18 Check whether there is no memory access message (DM15, DM16, or DM18) to be transmitted. */
# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
        if(pMemHandler->DiagMessage != J1939DCM_DM_UNDEF)
        {
          lErrorId = J1939DCM_E_INVALID_STATE;
        }
        else if (lTxPduContext.MetaDataLength > J1939DCM_DM15_METADATA_LEN)
        {
          lErrorId = J1939DCM_E_BUFFER_TOO_SMALL;
        }
        else
# endif
        {
          /* #20 Store required information to transmit DM15 on task level. */
          pMemHandler->DiagMessage        = J1939DCM_DM15;
          pMemHandler->TxPduId            = lTxPduContext.PduId;
          pMemHandler->MetaDataLength     = lTxPduContext.MetaDataLength;
          pMemHandler->NodeHdl            = lNodeHdl;
          pMemHandler->ChannelHdl         = lChannelHdl;
          pMemHandler->DestinationAddress = AddressInfo->DestinationAddress;
          pMemHandler->MessageEvent       = J1939DCM_MEM_MSG_TRANSMIT;

          /* #21 Build DM15 content without taking into account meta data. */
          pMemHandler->DM15Buffer[0] = (uint8)(MemResponseParameter->Length & 0x00FFu);
          pMemHandler->DM15Buffer[1] = (uint8)( (uint8)((MemResponseParameter->Length & 0x0700u) >> 3) |
                                                   (uint8)((MemResponseParameter->Status & 0x07u)   << 1) );
          pMemHandler->DM15Buffer[2] = J1939Dcm_UtiGetLoLoByte(MemResponseParameter->ErrorIndicator);
          pMemHandler->DM15Buffer[3] = J1939Dcm_UtiGetLoHiByte(MemResponseParameter->ErrorIndicator);
          pMemHandler->DM15Buffer[4] = J1939Dcm_UtiGetHiLoByte(MemResponseParameter->ErrorIndicator);
          pMemHandler->DM15Buffer[5] = MemResponseParameter->EDCPExtension;
          pMemHandler->DM15Buffer[6] = J1939Dcm_Uti16BitGetLoByte(MemResponseParameter->Seed);
          pMemHandler->DM15Buffer[7] = J1939Dcm_Uti16BitGetHiByte(MemResponseParameter->Seed);                                                       /* PRQA S 2985 */ /* MD_J1939Dcm_Rule2.2_2985 */

          J1939Dcm_UtiBufferContextInit(&pMemHandler->TxData,
                                        pMemHandler->DM15Buffer,
                                        J1939DCM_MEM_ACCESS_MSG_LENGTH,
                                        J1939DCM_MEM_ACCESS_MSG_LENGTH + (PduLengthType)lTxPduContext.MetaDataLength);

          /* #22 Indicate successful transmission. */
          TxResult = E_OK;
        }
        /* #23 Leave critical section. */
        J1939Dcm_ExitCritical();
      }
    }
  }

# if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)                                                                                                               /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_MEMRESPONSETRANSMIT,
      lErrorId
      )
  }
# else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

  return TxResult;
}                                                                                                                                                    /* PRQA S 6050, 6080 */ /*  MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (J1939DCM_DM15_SUPPORT == STD_ON) */

#if ((J1939DCM_DM16_SUPPORT == STD_ON) || \
    (J1939DCM_DM18_SUPPORT == STD_ON))
/***********************************************************************************************************************
 * J1939Dcm_MemDataTransmit()
 **********************************************************************************************************************/
/*!
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939DCM_CODE)
J1939Dcm_MemDataTransmit(
  J1939Dcm_MemDataType DataKind,
  P2CONST(J1939Dcm_AddressInfoType, AUTOMATIC, J1939DCM_APPL_DATA) AddressInfo,
  P2CONST(PduInfoType, AUTOMATIC, J1939DCM_APPL_DATA) PduInfo
  )
{
  Std_ReturnType lTxResult = E_NOT_OK;
  uint8          lErrorId  = J1939DCM_E_NO_ERROR;

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
  /* API only allowed for binary and security data */
  if((DataKind != J1939DCM_MEM_DATA_BINARY) && (DataKind != J1939DCM_MEM_DATA_SECURITY))
  {
    lErrorId = J1939DCM_E_INVALID_PGN;
  }
  else
# endif
  {
    J1939Dcm_TxPduContextType lTxPduContext;
    J1939Dcm_NodeHdlType      lNodeHdl;
    J1939Dcm_ChannelHdlType   lChannelHdl;

    lNodeHdl    = J1939Dcm_NetGetNodeHdlByAddr(AddressInfo->SourceAddress);
    lChannelHdl = J1939Dcm_NetGetChannelHdlById(AddressInfo->Channel);

    if(J1939Dcm_NetIsValidOnlineNodeChannel(
         J1939DCM_API_MEMDATATRANSMIT,
         lNodeHdl,
         lChannelHdl) == TRUE)
    {
      /*#14 Obtain TxPdu Id for DM16 or DM18 transmitted from the source node via the requested channel. */
      lTxPduContext = J1939Dcm_UtiGetPeerTxPduContextByDM(                                                                                           /* VCA_J1939DCM_FALSE_POSITIVE */
                        lNodeHdl,
                        lChannelHdl,
                        DataKind
                        );

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
      if (lTxPduContext.PduId == J1939DCM_INVALID_PDU_ID)
      {
        lErrorId = J1939DCM_E_PARAM_CONFIG;
      }
      else
# endif
      {
        J1939Dcm_MemHandlerPtrType pMemHandler = &J1939Dcm_DiagContext.CommonContext.MemHandlerState;
        /*
         * #17 Enter critical section
         *     (Reason: protect data consistency of the memory handler state against another CDD interruption).
         */
        J1939Dcm_EnterCritical();

# if (J1939DCM_DEV_ERROR_DETECT == STD_ON)
        /* #18 Check whether there is no memory access message (DM15, DM16, or DM18) to be transmitted. */
        if(pMemHandler->DiagMessage != J1939DCM_DM_UNDEF)
        {
          lErrorId = J1939DCM_E_INVALID_STATE;
        }
        else
# endif
        {
          /* #20 Store required information to transmit DM16 or DM18 on task level. */
          pMemHandler->DiagMessage        = DataKind;
          pMemHandler->TxPduId            = lTxPduContext.PduId;
          pMemHandler->MetaDataLength     = lTxPduContext.MetaDataLength;
          pMemHandler->NodeHdl            = lNodeHdl;
          pMemHandler->ChannelHdl         = lChannelHdl;
          pMemHandler->DestinationAddress = AddressInfo->DestinationAddress;
          pMemHandler->MessageEvent       = J1939DCM_MEM_MSG_TRANSMIT;

          /* #21 Reference the data to be transmitted. */
          J1939Dcm_UtiBufferContextInit(&pMemHandler->TxData,
                                        PduInfo->SduDataPtr,
                                        PduInfo->SduLength,
                                        PduInfo->SduLength);

          /* #22 Indicate successful transmission. */
          lTxResult = E_OK;
        }
        /* #23 Leave critical section. */
        J1939Dcm_ExitCritical();
      }
    }
  }

# if (J1939DCM_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != J1939DCM_E_NO_ERROR)                                                                                                               /* PRQA S 2991, 2995 */ /* MD_J1939Dcm_ConstExpr, MD_J1939Dcm_ConstExpr */
  {
    J1939Dcm_DetAssertAlways(
      J1939DCM_API_MEMDATATRANSMIT,
      lErrorId
      )
  }
# else
  J1939Dcm_IgnoreUnusedArgument(lErrorId)                                                                                                            /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

  return lTxResult;
}                                                                                                                                                    /* PRQA S 6050, 6080 */ /*  MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (J1939DCM_DM17_SUPPORT == STD_ON) || \
          (J1939DCM_DM18_SUPPORT == STD_ON) */

#define J1939DCM_STOP_SEC_CODE
#include "J1939Dcm_MemMap.h"                                                                                                                         /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************
 module specific MISRA deviations:
************************************
  MD_J1939Dcm_Rule2.2_2985
    Description: This operation is redundant. The value of the result is always that of the left-hand operand.
    Reason:      apparent redundant-like operations are needed for better code readability.
    Risk:        none
    Prevention:  n/a

  MD_J1939Dcm_Rule2.2_2986
    Description: This operation is redundant. The value of the result is always that of the right-hand operand.
    Reason:      apparent redundant-like operations are needed for better code readability or occurs in a set of configurations domain.
    Risk:        none
    Prevention:  n/a

  MD_J1939Dcm_Rule2.2_2981
    Description: This initialization is redundant. The value of this object is never used before being modified.
    Reason:      to provide a variable initialization at the beginning of a function.
    Risk:        none
    Prevention:  n/a

  MD_J1939Dcm_Rule2.2_2982
    Description: This assignment is redundant. The value of this object is never used before being modified.
    Reason:      to provide a variable initialization at the beginning of a function.
    Risk:        none
    Prevention:  n/a

  MD_J1939Dcm_Rule2.7
    Description: Rule2.7: There should be no unused parameters in functions
    Reason:      parameter is unused only in certain configurations
    Risk:        none
    Prevention:  n/a

  MD_J1939Dcm_Rule11.8
    Description: Rule 11.8: A cast shall not remove any const or volatile qualification from the type pointed to by a pointer.
    Reason:      the casted volatile pointer is assigned to a local pointer
    Risk:        none
    Prevention:  n/a

   MD_J1939Dcm_Rule13.5:
     Description: Rule 13.5
                  The right hand operand of a logical && or || operator shall not contain persistent side effects.
     Reason:      The function called on the right hand side has no side effects or the side effects are intentional.
     Risk:        The function may introduce unintentional side effects at a later time.
     Prevention:  none

  MD_J1939Dcm_ConstExpr
    Description: The result of this logical operation is always 'false' or is always 'true'. The value of this 'if' controlling expression is always 'false' or is always 'true'.
    Reason:      A configuration dependent situation could lead to a constant logical expression.
    Risk:        none
    Prevention:  n/a

  MD_J1939Dcm_OptimizedInlineCode_3387:
     Description: Rule 13.3
                  A full expression containing an increment (++) or decrement (--) operator should have no other
                  potential side effects other than that caused by the increment or decrement operator
     Reason:      This kind of operator is used only in case of function-like macros where also a return value is expected.
                  Needed for maximum inlining efficiency and less other MISRA deviations.
     Risk:        The risks are at minimum since the affected locations are simple expressions.
     Prevention:  These code sections are thoroughly tested by dedicated unit tests.

  MD_J1939Dcm_DerefInvalidPointer:
     Description: Rule 18.1
                  Dereference of an invalid pointer value.
     Reason:      This is a false positive and a known PRQA issue.
     Risk:        None.
     Prevention:  None.

  MD_J1939Dcm_ComputingOfInvalidPointer:
    Description: Rule 18.1
                 Apparent: Computing an invalid pointer value.
    Reason:      This is a false positive. 
    Risk:        Read / Write operation outside of the J1939Dcm memory region.
    Prevention:  Verified by checking of the nodeHdl before the access to the array is done.
*/

/* ----------------------------------------------
 ~&&&   COVERAGE
---------------------------------------------- */
/* COV_JUSTIFICATION_BEGIN

\ID COV_J1939DCM_MACRO_OVERRIDE
  \ACCEPT TX
  \ACCEPT XF
  \REASON The value of a macro may be overridden by user config for test purposes. Since this is not officially
          supported, it is not covered by the test suite.

\ID COV_J1939DCM_REQUIRED_BY_SAFEBSW
  \ACCEPT TF tf tf tx
  \REASON This configuration switch is always on as required by SafeBSW context.

\ID COV_J1939DCM_MESSAGE_TABLE_START_END_IDX
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XX
  \REASON The difference between the end index and the start index of the message table differs in some configurations only by one (in configurations
          where only on DM message is configured). Therefore the condition in the while loop cannot be true in such configurations.
  
\ID COV_J1939DCM_SINGLE_CHANNEL_ISOBUS_CHARACTERISTIC
  \ACCEPT TF tf tf tx
  \ACCEPT XF tf tf xf
  \REASON The ISOBUS characteristic can not be different in a configuration with only one channel. Therefore the condition can be either true or false
          in such configurations. Both conditions true and false in a configuration with only one channel is not possible.

\ID COV_J1939DCM_NBR_OF_CHANNELS_EQUAL
  \ACCEPT XF
  \REASON In postbuild selectable configurations the value of J1939Dcm_GetSizeOfCfg_ChannelTable() is equal to J1939DCM_MAX_NUM_CHANNELS. Only in
          case of invalid postbuild selectable configurations the values differs.

\ID COV_J1939DCM_NBR_OF_NODES_EQUAL
  \ACCEPT XF
  \REASON In postbuild selectable configurations the value of J1939Dcm_GetSizeOfCfg_NodeTable() is equal to J1939DCM_MAX_NUM_NODES. Only in
          case of invalid postbuild selectable configurations the values differs.

\ID COV_J1939DCM_NODE_CHANNEL_SUPPORTED
  \ACCEPT XF
  \ACCEPT TX
  \REASON In configurations with only one channel the macro J1939Dcm_IsCfg_ChannelSupportedArray() is always true.

\ID COV_J1939DCM_CHANNEL_HDL_VALID
  \ACCEPT XF
  \ACCEPT XX
  \REASON In configurations with only one channel the macros J1939Dcm_Cfg_GetRxPduChannelHdl() or J1939Dcm_Cfg_GetTxPduChannelHdl() are always 0 and therefore
          the channel handle is always valid.

\ID COV_J1939DCM_ALWAYS_TRUE_IN_CFG_WITHOUT_TP
  \ACCEPT TX
  \REASON In configurations which supports only diagnostic messages without TP transmission the condition is always fulfilled. 

\ID COV_J1939DCM_ONLY_ONE_DM_CONFIGURED
  \ACCEPT XF
  \REASON In configurations with only one diagnostic message the while loop is traversed only once.

\ID COV_J1939DCM_MEM_CALLOUT_CHECK
  \ACCEPT XF
  \ACCEPT XX
  \REASON The justified object is uncovered, since it is not intended to be reached. It just exists in case of memory services incomplete configurations (callouts are not configured).

\ID COV_J1939DCM_SUPPORT_ALWAYS
  \ACCEPT TX
  \REASON The condition must always be true.

\ID COV_J1939DCM_DET_ALWAYS_REPORTED
  \ACCEPT TX
  \ACCEPT XX
  \REASON In all configurations public API functions like J1939Dcm_StartOfReception are available, but the API shall not be called in some 
          configurations (for example J1939Dcm_StartOfReception shall only be called when DM messages are configured which needs TP reception). 
          In these cases a DET is always reported.

COV_JUSTIFICATION_END */
/* ----------------------------------------------
 ~&&&   SafeBSW
---------------------------------------------- */
/* SBSW_JUSTIFICATION_BEGIN

\ID VCA_J1939DCM_POINTER_FORWARD_LOCAL
  \DESCRIPTION    A pointer is passed to a function expecting a valid pointer.
  \COUNTERMEASURE \N The pointer is taken from a local variable, as such it is always valid.

\ID VCA_J1939DCM_POINTER_FORWARD_NULL
  \DESCRIPTION    A pointer is passed to a function expecting a null pointer.
  \COUNTERMEASURE \N The null pointer is a substitute for an unused argument of a pointer type.

\ID VCA_J1939DCM_POINTER_FORWARD_GLOBAL
  \DESCRIPTION    A pointer is passed to a function expecting a valid pointer. The called function does not store its
                  pointer parameters.
  \COUNTERMEASURE \N The pointer is taken from a global variable, as such it is always valid.

\ID VCA_J1939DCM_POINTER_FORWARD_COMBINED
\DESCRIPTION    A combination of pointers is passed to a function expecting valid pointers.
                The pointer is taken from one of the following locations:
                 - global variable;
                 - local (stack) variable;
                 - is an argument of the caller function;
  \COUNTERMEASURE \N In case of a local (stack) variable the pointer is always valid.
                  \N In case of a global variable the pointer is always valid.
                  \N In case of a passed argument, the caller has to ensure that the pointer is valid.

\ID VCA_J1939DCM_WRITE_DTC_HANDLER_STATE
  \DESCRIPTION    In an internal function, data is written through a pointer to a DTC handler state, or the
                  pointer is passed to a function expecting a valid reference to a DTC handler state.
                  The pointer is initialized by J1939Dcm_DtcHandlerStateInit(), which will always initialize it to point
                  to a valid memory entry. A DTC handler state ensures that the SduLength of MessageData member never
                  exceeds the available buffer length specified by AvailLen.
  \COUNTERMEASURE \R [CM_J1939DCM_R_WRITE_DTC_HANDLER_STATE]

\ID VCA_J1939DCM_WRITE_BUFFER_CONTEXT
  \DESCRIPTION    In an internal function, data is written through a pointer to a message buffer.
                  The pointer is initialized by J1939Dcm_UtiBufferContextInit(), which will always initialize it to point
                  to a valid memory entry. A runtime check against the available length ensures that
                  the SduLength never exceeds the SduBuffer.
  \COUNTERMEASURE \R [CM_J1939DCM_R_WRITE_DMX_MESSAGE_BUFFER]

\ID VCA_J1939DCM_VERIFIED_CHANNEL_ACCESS
  \DESCRIPTION    Data is written to an array using a channel handle. Before the data is written, it is either checked
                  whether the channel handle is a valid one or the access to the array is done within a for loop. The 
                  upper limit of the for loop is configured in a rom structure by the macro 
                  J1939Dcm_GetSizeOfCfg_ChannelTable(). The value J1939Dcm_GetSizeOfCfg_ChannelTable() is checked against 
                  J1939DCM_MAX_NUM_CHANNELS and ensured that J1939Dcm_GetSizeOfCfg_ChannelTable() is less or equal to 
                  J1939DCM_MAX_NUM_CHANNELS.
  \COUNTERMEASURE \R [CM_J1939DCM_R_MAX_NUM_CHANNELS]
                  \R [CM_J1939DCM_R_VALID_CHANNEL_HDL]

\ID VCA_J1939DCM_VERIFIED_NODE_ACCESS
  \DESCRIPTION    Data is written to an array using a node handle. Before the data is written, it is either checked
                  whether the node handle is a valid one or the access to the array is done within a for loop.
                  The upper limit of the for loop is configured in a rom structure by the macro 
                  J1939Dcm_GetSizeOfCfg_NodeTable(). The value J1939Dcm_GetSizeOfCfg_NodeTable() is checked 
                  against J1939DCM_MAX_NUM_NODES and ensured that J1939Dcm_GetSizeOfCfg_NodeTable() is less or equal 
                  to J1939DCM_MAX_NUM_NODES.
  \COUNTERMEASURE \R [CM_J1939DCM_R_MAX_NUM_NODES]
                  \R [CM_J1939DCM_R_VALID_NODE_HDL]

\ID VCA_J1939DCM_POINTER_MEMCPY_BUFFER
  \DESCRIPTION    In an internal function, data is copied into a buffer through a pointer using memcpy, or the
                  buffer pointer with the appropriate buffer size are passed to a function expecting a valid pair
                  of buffer pointer and buffer size.
  \COUNTERMEASURE \R [CM_J1939DCM_R_MEMCPY_PASS_BUFFER]
                  \R [CM_J1939DCM_R_MEMCPY_WRITE]

\ID VCA_J1939DCM_DEM_GET_NEXT_FF
  \DESCRIPTION    A combination of pointers is passed to a function expecting valid pointers. The pointer is
                  taken from one of the following locations:
                 - global variable with fixed offset J1939DCM_FF_DATA_OFFSET;
                 - local (stack) variable;
  \COUNTERMEASURE \N The pointer is taken from a local variable, as such it is always valid.
                  \N In case of a global variable the pointer is always valid. The offset J1939DCM_FF_DATA_OFFSET
                     is checked with a compiler error directive against J1939DCM_FF_HEADER_LENGTH to be sure that
                     the available buffer is greater or equal to buffer length passed to the Dem function.

\ID VCA_J1939DCM_COPY_TO_PDUINFO
  \DESCRIPTION    A write operation to a PDU info pointer is performed. The buffer pointer with the appropriate buffer 
                  size are passed to the function. The function always writes as many data as the caller expects.
  \COUNTERMEASURE \N The pointer is passed to the function by an external caller. The caller must guarantee that
                     the pair of buffer and buffer size are valid.

\ID VCA_J1939DCM_FALSE_POSITIVE
  \DESCRIPTION    Vector code Analyzer incorrectly interprets a read access as write access and reports an error.
  \COUNTERMEASURE \N No countermeasure necessary, because of misinterpretation of a read access.

SBSW_JUSTIFICATION_END */

/*
\CM CM_J1939DCM_R_MAX_NUM_NODES
  Verify that J1939DCM_MAX_NUM_NODES has a value greater or equal to J1939Dcm_GetSizeOfCfg_NodeTable().

\CM CM_J1939DCM_R_MAX_NUM_CHANNELS
  Verify that J1939DCM_MAX_NUM_CHANNELS has a value greater or equal to J1939Dcm_GetSizeOfCfg_ChannelTable().

\CM CM_J1939DCM_R_WRITE_DTC_HANDLER_STATE
  Verify that the pDtcHandlerState->MessageData->SduLength is smaller than pDtcHandlerState->BufferLength before
  writing to pDtcHandlerState->MessageData->SduDataPtr.

\CM CM_J1939DCM_R_WRITE_DMX_MESSAGE_BUFFER
  Verify that the pMsgBuffer->SduLength is smaller than J1939DCM_BUFFERSIZE_COMMON before writing to
  pMsgBuffer->SduDataPtr.

\CM CM_J1939DCM_R_VALID_CHANNEL_HDL
  Verify that the channel handle is a valid one using the function J1939Dcm_IsValidChannelHdl.

\CM CM_J1939DCM_R_VALID_NODE_HDL
  Verify that the node handle is a valid one using the function J1939Dcm_IsValidNodeHdl.

\CM CM_J1939DCM_R_MEMCPY_PASS_BUFFER
  Verify that the passed pair of buffer pointer and buffer size matches to referenced memory entry and memory size.

\CM CM_J1939DCM_R_MEMCPY_WRITE
  Verify that the array index is in range between 0 and the passed buffer size before writing to the passed
  buffer pointer.
*/

/**********************************************************************************************************************
 *  END OF FILE: J1939DCM.C
 *********************************************************************************************************************/
