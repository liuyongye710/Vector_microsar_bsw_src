/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *           File:  Lin.c
 *      Component:  AUTOSAR LIN Driver
 *         Module:  DrvLin_VttCanoeAsr / DrvLin_CanoeemuAsr
 *      Generator:  DrvLin_VttCanoeAsr / DrvLin_CanoeemuAsr
 *
 *  Target system:  Canoe
 *       Compiler:  Ansi

 *    Derivatives:  VTT/EMU
 *
 *    Description:  Implementation of the AUTOSAR LIN Driver
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

#define LIN_SOURCE
/**********************************************************************************************************************
 *  MISRA
 *********************************************************************************************************************/
/* Disable the following MISRA warnings because they would appear too often for individual suppression.
   See justification at the end of file */

                       /* PRQA  S 2880 EOF */ /* MD_MSR_Unreachable */
                       /* PRQA  S 2742 EOF */ /* MD_CSL_ConstantValueAsDefine */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Lin.h"
#include "Lin_Cbk.h"
#include "EcuM_Cbk.h"
#include "LinIf_Cbk.h"

#if ( LIN_DEV_ERROR_DETECT == STD_ON )
# include "Det.h"
#endif

#if ( LIN_E_TIMEOUT_TYPE_DET == STD_OFF )
# include "Dem.h"
#endif

#if ( LIN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON )
# include "Rtm.h"
#endif

#if ( LIN_USE_ECUM_BSW_ERROR_HOOK == STD_ON )
# include "EcuM_Error.h"
#endif
#include "VttCntrl_Base.h"

#if defined ( LIN_CANOE_API_REVERSE_ENGINEERING )
# include "stdio.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if ( LIN_SW_MAJOR_VERSION != 11 )
# error "Source and Header are inconsistent (LIN_SW_MAJOR_VERSION)!"
#endif
#if ( LIN_SW_MINOR_VERSION != 2 )
# error "Source and Header are inconsistent (LIN_SW_MINOR_VERSION)!"
#endif
#if ( LIN_SW_PATCH_VERSION != 1 )
# error "Source and Header are inconsistent (LIN_SW_PATCH_VERSION)!"
#endif

#if ( LIN_TPS_MAJOR_VERSION != LIN_SW_MAJOR_VERSION )
# error "Source and Types Header are inconsistent (LIN_TPS_MAJOR_VERSION)!"
#endif
#if ( LIN_TPS_MINOR_VERSION != LIN_SW_MINOR_VERSION )
# error "Source and Types Header are inconsistent (LIN_TPS_MINOR_VERSION)!"
#endif
#if ( LIN_TPS_PATCH_VERSION != LIN_SW_PATCH_VERSION )
# error "Source and Types Header are inconsistent (LIN_TPS_PATCH_VERSION)!"
#endif
/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 **********************************************************************************************************************/
#if   ( LIN_CONFIGURATION_VARIANT != LIN_CONFIGURATION_VARIANT_PRECOMPILE ) && \
      ( LIN_CONFIGURATION_VARIANT != LIN_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
# error "LIN_CONFIGURATION_VARIANT not in valid range, check settings in generation tool!"
#endif

#if ( LIN_HL_GENERATORMSR_IMPLEMENTATION != LIN_HL_GENERATORMSR_COMPATIBILITY_VERSION )
# error "Version of the Hl generator is not consistent with the implementation!"
#endif

#if ( LIN_LL_GENERATORMSR_IMPLEMENTATION != LIN_LL_GENERATORMSR_COMPATIBILITY_VERSION )
# error "Version of the LL generator is not consistent with the implementation!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/
#if ( LIN_DEV_ERROR_REPORT == STD_ON )
# define Lin_Det_ReportError( Lin_ApiId, Lin_ErrorCode) (Det_ReportError(LIN_MODULE_ID, 0, (Lin_ApiId), (Lin_ErrorCode)))   /* PRQA S 3453 */   /* MD_MSR_FctLikeMacro */
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/
/* Define if not already defined */
#if !defined (STATIC)   /* COV_LIN_COMPATIBILITY */
# define STATIC static
#endif

#if !defined (LIN_LOCAL_INLINE) /* COV_LIN_COMPATIBILITY */
# define LIN_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/
#if (LIN_USE_INIT_POINTER == STD_ON)
# define LIN_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */
STATIC P2CONST(Lin_ConfigType, LIN_VAR_NOINIT, LIN_PBCFG) Lin_ConfigDataPtr;
# define LIN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */
#endif

#if ( LIN_DEV_ERROR_DETECT == STD_ON )
# define LIN_DEV_UNINITVALUE                              0u
# define LIN_DEV_INITVALUE                                165u

# define LIN_START_SEC_VAR_ZERO_INIT_8BIT
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

/* Variable Lin_Dev_InitDetect must be initialized after reset for working debug check */
STATIC VAR(uint8, LIN_VAR_ZERO_INIT) Lin_Dev_InitDetect = LIN_DEV_UNINITVALUE;
# define LIN_STOP_SEC_VAR_ZERO_INIT_8BIT
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */
#endif

#if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
# define LIN_START_SEC_CONST_8BIT
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

STATIC CONST(uint8, LIN_CONST) Lin_AllPid[64] = { 0x80, 0xC1, 0x42, 0x03, 0xC4, 0x85, 0x06, 0x47, 0x08, 0x49, 0xCA, 0x8B, 0x4C, 0x0D, 0x8E, 0xCF, 0x50, 0x11, 0x92, 0xD3, 0x14, 0x55, 0xD6, 0x97, 0xD8, 0x99, 0x1A, 0x5B, 0x9C, 0xDD, 0x5E, 0x1F, 0x20, 0x61, 0xE2, 0xA3, 0x64, 0x25, 0xA6, 0xE7, 0xA8, 0xE9, 0x6A, 0x2B, 0xEC, 0xAD, 0x2E, 0x6F, 0xF0, 0xB1, 0x32, 0x73, 0xB4, 0xF5, 0x76, 0x37, 0x78, 0x39, 0xBA, 0xFB, 0x3C, 0x7D, 0xFE, 0xBF };

# define LIN_STOP_SEC_CONST_8BIT
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */
#endif


/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define LIN_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#if( LIN_LEAST_ONE_CHANNEL_WAKEUP_SUPPORT_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  Lin_CheckIrqWakeupEvent
 **********************************************************************************************************************/
/*! \brief      Checks an wake up event.
 *  \details    If the channel has a EcuM Wakeup Source ID the wake up event are set and EcuM_CheckWakeup() are called.
 *  \param[in]  ChannelConfigIdx Channel index of configuration.
 *  \pre        -
 *  \context    ANY
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_CheckIrqWakeupEvent(Lin_ChannelConfigIdxOfChannelHwType ChannelConfigIdx);
#endif

/***********************************************************************************************************************
 *  Lin_SetSleep
 **********************************************************************************************************************/
/*! \brief      Set sleep.
 *  \details    Set the hardware and software state to sleep.
 *  \param[in]  ChannelConfigIdx  Channel index of configuration.
 *  \param[in]  ApiId             Lin Service ID, needed only for some hardware.
 *  \pre        -
 *  \context    ANY
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetSleep(Lin_ChannelConfigIdxOfChannelHwType ChannelConfigIdx, uint8 ApiId);

/***********************************************************************************************************************
 *  Lin_SetHardwareWake
 **********************************************************************************************************************/
/*! \brief      Set hardware to operational.
 *  \details    Set the hardware to operational without sending a wake-up-frame. Software state does not change.
 *  \param[in]  ChannelConfigIdx  Channel index of configuration.
 *  \param[in]  ApiId             Lin Service ID, needed only for some hardware.
 *  \pre        -
 *  \context    ANY
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetHardwareWake(Lin_ChannelConfigIdxOfChannelHwType ChannelConfigIdx, uint8 ApiId);

/* --- Platform specific local function prototypes() ---------------------------------------------------------------- */
/***********************************************************************************************************************
 *  Lin_GetInternalStateOfChannelData
 **********************************************************************************************************************/
/*! \brief      Atomic read access to internal state.
 *  \details    Replacing the ComStackLib Macro.
 *  \param[in]  ChannelConfigIdx  Channel index of configuration.
 *  \return     Internal state of channel.
 *  \pre        -
 *  \context    ANY
 **********************************************************************************************************************/
FUNC(uint8, LIN_CODE) Lin_GetInternalStateOfChannelData(Lin_ChannelConfigIdxOfChannelHwType index);

/***********************************************************************************************************************
 *  Lin_SetInternalStateOfChannelData
 **********************************************************************************************************************/
/*! \brief      Atomic write access to internal state.
 *  \details    Replacing the ComStackLib Macro.
 *  \param[in]  ChannelConfigIdx  Channel index of configuration.
 *  \param[in]  internalState  Internal state of channel to set
 *  \pre        -
 *  \context    ANY
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) Lin_SetInternalStateOfChannelData(Lin_ChannelConfigIdxOfChannelHwType index, uint8 internalState);

#define LIN_STOP_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  FUNCTIONS
 **********************************************************************************************************************/

#define LIN_START_SEC_CODE_ISR
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */


/***********************************************************************************************************************
 *  Lin_Interrupt
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, LIN_CODE_ISR) Lin_Interrupt(uint8 ChannelHw)
{
  Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx;
  uint8 ErrorId = LIN_E_NO_ERROR;
#if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
  Std_ReturnType ret;
#endif

#if ( LIN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON )
  Rtm_Start(RtmConf_RtmMeasurementPoint_Lin_Interrupt);
#endif
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if(Lin_GetSizeOfChannelHw() <= ChannelHw)
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# if( LIN_INVALIDHNDOFCHANNELHW == STD_ON )
  else if(Lin_IsInvalidHndOfChannelHw(ChannelHw))
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# endif
  else
#else
  LIN_DUMMY_STATEMENT(ChannelHw);       /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
  {
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelHw(ChannelHw);

/* --- Platform specific implementation of Lin_Interrupt() ---------------------------------------------------------- */
#if( LIN_LEAST_ONE_CHANNEL_WAKEUP_SUPPORT_ENABLED == STD_ON )
    if(Lin_GetInternalStateOfChannelData(ChannelConfigIdx) == LIN_ONSLEEP_INTERNALSTATEOFCHANNELDATA)
    {
      Lin_CheckIrqWakeupEvent(ChannelConfigIdx);
    }
#endif


#if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
    if((Lin_GetNodeTypeOfChannelConfig(ChannelConfigIdx) == LIN_SLAVE_NODETYPEOFCHANNELCONFIG) && (Lin_GetInternalStateOfChannelData(ChannelConfigIdx) != LIN_ONSLEEP_INTERNALSTATEOFCHANNELDATA))
    {
      switch (Lin_GetSlaveStateOfChannelData(ChannelConfigIdx))
      {
        case LIN_SLAVE_STATE_FRAME_COMPLETE:
          Lin_SetSlaveStateOfChannelData(ChannelConfigIdx, LIN_SLAVE_STATE_UNKNOWN);
          if(Lin_GetSlavePduOfChannelData(ChannelConfigIdx).Pid == 0x7Du)
          {
            /* SRF was expected and processed, confirm to upper layer and re-enable message polling to process next frame */
            if(Lin_GetFrame3DPollStateOfChannelData(ChannelConfigIdx) == LIN_FRAME_3D_POLL_STATE_WAITING_FOR_BUS)
            {
              LinIf_TxConfirmation(Lin_GetChannelIDOfChannelConfig(ChannelConfigIdx));  /* remove from LinIf */
              Lin_SetFrame3DPollStateOfChannelData(ChannelConfigIdx, LIN_FRAME_3D_POLL_STATE_POLLING);
            }
          }
          else
          {
            /* any other than SRF */
            if(Lin_GetFrame3DPollStateOfChannelData(ChannelConfigIdx) == LIN_FRAME_3D_POLL_STATE_WAITING_FOR_BUS)
            {
              /* if we are waiting for a SRF header (and the SRF header is already indicated to upper layer in this case), do not report intermediate frames to upper layer to avoid aborting Tp connection - except MRF */
              if(Lin_GetSlavePduOfChannelData(ChannelConfigIdx).Pid == 0x3Cu)
              { /* if 3c received after a valid 3d was already queued, set polling state again to reconfigure new SRF Tx data */
                ret = LinIf_HeaderIndication(Lin_GetChannelIDOfChannelConfig(ChannelConfigIdx), &Lin_GetSlavePduOfChannelData(ChannelConfigIdx));
                LinIf_RxIndication(Lin_GetChannelIDOfChannelConfig(ChannelConfigIdx), Lin_GetSlavePduOfChannelData(ChannelConfigIdx).SduPtr);
                Lin_SetFrame3DPollStateOfChannelData(ChannelConfigIdx, LIN_FRAME_3D_POLL_STATE_POLLING);
              }
            }
            else
            {
              /* process handled frame and notify them to upper layer */
              ret = LinIf_HeaderIndication(Lin_GetChannelIDOfChannelConfig(ChannelConfigIdx), &Lin_GetSlavePduOfChannelData(ChannelConfigIdx));

              if(Lin_GetSlavePduOfChannelData(ChannelConfigIdx).Drc == LIN_FRAMERESPONSE_TX)
              {
                LinIf_TxConfirmation(Lin_GetChannelIDOfChannelConfig(ChannelConfigIdx));
              }
              else if(Lin_GetSlavePduOfChannelData(ChannelConfigIdx).Drc == LIN_FRAMERESPONSE_RX)
              {
                LinIf_RxIndication(Lin_GetChannelIDOfChannelConfig(ChannelConfigIdx), Lin_GetSlavePduOfChannelData(ChannelConfigIdx).SduPtr);
              }
            }
          }
          break;
        case LIN_SLAVE_STATE_HEADER_ERROR:
          Lin_SetSlaveStateOfChannelData(ChannelConfigIdx, LIN_SLAVE_STATE_UNKNOWN);
          LinIf_LinErrorIndication(Lin_GetChannelIDOfChannelConfig(ChannelConfigIdx), LIN_ERR_HEADER);
          break;
        case LIN_SLAVE_STATE_ANY_ERROR:
          Lin_SetSlaveStateOfChannelData(ChannelConfigIdx, LIN_SLAVE_STATE_UNKNOWN);

          if(Lin_GetSlavePduOfChannelData(ChannelConfigIdx).Pid == 0x7Du)
          {
            /* do not indicate header again, already done for SRF */
            LinIf_LinErrorIndication(Lin_GetChannelIDOfChannelConfig(ChannelConfigIdx), LIN_ERR_RESP_CHKSUM);
            Lin_SetFrame3DPollStateOfChannelData(ChannelConfigIdx, LIN_FRAME_3D_POLL_STATE_POLLING);
          }
          else
          {
            Lin_GetSlavePduOfChannelData(ChannelConfigIdx).SduPtr = Lin_GetShadowDataBufferOfChannelData(ChannelConfigIdx);
            ret = LinIf_HeaderIndication(Lin_GetChannelIDOfChannelConfig(ChannelConfigIdx), &Lin_GetSlavePduOfChannelData(ChannelConfigIdx));
            if(Lin_GetSlavePduOfChannelData(ChannelConfigIdx).Drc != LIN_FRAMERESPONSE_IGNORE)
            {
              LinIf_LinErrorIndication(Lin_GetChannelIDOfChannelConfig(ChannelConfigIdx), LIN_ERR_RESP_CHKSUM);
            }
          }
          break;
        case LIN_SLAVE_STATE_NO_RESPONSE_ERROR:
          Lin_SetSlaveStateOfChannelData(ChannelConfigIdx, LIN_SLAVE_STATE_UNKNOWN);
          if(Lin_GetSlavePduOfChannelData(ChannelConfigIdx).Pid != 0x7Du)       /* Do not report the error for 3d */
          {
            Lin_GetSlavePduOfChannelData(ChannelConfigIdx).SduPtr = Lin_GetShadowDataBufferOfChannelData(ChannelConfigIdx);
            ret = LinIf_HeaderIndication(Lin_GetChannelIDOfChannelConfig(ChannelConfigIdx), &Lin_GetSlavePduOfChannelData(ChannelConfigIdx));
            if(Lin_GetSlavePduOfChannelData(ChannelConfigIdx).Drc != LIN_FRAMERESPONSE_IGNORE)
            {
              LinIf_LinErrorIndication(Lin_GetChannelIDOfChannelConfig(ChannelConfigIdx), LIN_ERR_NO_RESP);
            }
          }
          break;
        default:
          break;
      }
    }
#endif

    LIN_DUMMY_STATEMENT(ChannelConfigIdx);      /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
/* ------------------------------------------------------------------------------------------------------------------ */
  }

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if(ErrorId != LIN_E_NO_ERROR)
  {
    (void) Lin_Det_ReportError(LIN_SID_INTERRUPT_ID, ErrorId);
  }
#else
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

#if ( LIN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON )
  Rtm_Stop(RtmConf_RtmMeasurementPoint_Lin_Interrupt);
#endif
}

#define LIN_STOP_SEC_CODE_ISR
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#define LIN_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  Lin_SendFrame
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
 */
FUNC(Std_ReturnType, LIN_CODE) Lin_SendFrame(uint8 Channel, P2VAR(Lin_PduType, AUTOMATIC, LIN_APPL_VAR) PduInfoPtr)
{
  Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx;
  Std_ReturnType RetTmp = E_NOT_OK;
  uint8 ErrorId = LIN_E_NO_ERROR;

#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if(Lin_Dev_InitDetect != LIN_DEV_INITVALUE)
  {
    ErrorId = LIN_E_UNINIT;
  }
  else if(PduInfoPtr == NULL_PTR)
  {
    ErrorId = LIN_E_PARAM_POINTER;
  }
  else if(Lin_GetSizeOfChannelId() <= Channel)
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  else if(Lin_IsInvalidHndOfChannelId(Channel))
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# endif
  else
#endif
  {
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId(Channel);

    if((PduInfoPtr->Dl == 0u) || (PduInfoPtr->Dl > 8u))
    {
      ErrorId = LIN_E_PARAM_VALUE;
    }
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
    else if((Lin_GetInternalStateOfChannelData(ChannelConfigIdx) & 0x0Fu) == LIN_ONSLEEP_INTERNALSTATEOFCHANNELDATA)
    {
      ErrorId = LIN_E_STATE_TRANSITION;
    }
#endif
    else
    {
      RetTmp = E_OK;
/* --- Platform specific implementation of Lin_SendFrame() ---------------------------------------------------------- */
      switch (PduInfoPtr->Drc)
      {
        case (Lin_FrameResponseType) LIN_FRAMERESPONSE_TX:
          Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONTX_BUSY_INTERNALSTATEOFCHANNELDATA);
          CANoeAPI_SendLinMessage(Channel,      /* PRQA S 2784 */ /* MD_LIN_2784 */
                                  (PduInfoPtr->Pid) & 0x3FLu, (uint32) CANOEAPI_LINRECONFIGUREDATA | (uint32) CANOEAPI_LINAPPLYHEADER, CANOEAPI_LINRESPONSEALWAYS, PduInfoPtr->Dl, PduInfoPtr->SduPtr);
          break;

        case (Lin_FrameResponseType) LIN_FRAMERESPONSE_RX:
          Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONRX_BUSY_INTERNALSTATEOFCHANNELDATA);
          CANoeAPI_SendLinMessage(Channel, (PduInfoPtr->Pid) & 0x3FLu, CANOEAPI_LINAPPLYHEADER, CANOEAPI_LINRESPONSEALWAYS, 0, NULL_PTR);
          break;

        default:       /* slave-to-slave frame */
          Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONS2S_BUSY_INTERNALSTATEOFCHANNELDATA);
          CANoeAPI_SendLinMessage(Channel, (PduInfoPtr->Pid) & 0x3FLu, CANOEAPI_LINAPPLYHEADER, CANOEAPI_LINRESPONSEALWAYS, 0, NULL_PTR);
          break;
      }
/* ------------------------------------------------------------------------------------------------------------------ */
    }
  }
#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if(ErrorId != LIN_E_NO_ERROR)
  {
    (void) Lin_Det_ReportError(LIN_SID_SENDFRAME_ID, ErrorId);
  }
#else
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

  LIN_DUMMY_STATEMENT(Channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return (RetTmp);
}

/***********************************************************************************************************************
 *  Lin_GetStatus
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
 */
FUNC(Lin_StatusType, LIN_CODE) Lin_GetStatus(uint8 Channel, P2VAR(Lin_u8PtrType, AUTOMATIC, LIN_APPL_VAR) Lin_SduPtr)
{
  Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx;
  Lin_StatusType RetTmp = LIN_NOT_OK;
  uint8 ErrorId = LIN_E_NO_ERROR;
  uint8 i;
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if(Lin_Dev_InitDetect != LIN_DEV_INITVALUE)
  {
    ErrorId = LIN_E_UNINIT;
  }
  else if(Lin_SduPtr == NULL_PTR)
  {
    ErrorId = LIN_E_PARAM_POINTER;
  }
  else if(Lin_GetSizeOfChannelId() <= Channel)
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  else if(Lin_IsInvalidHndOfChannelId(Channel))
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# endif
  else
#endif
  {
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId(Channel);
/* --- Platform specific implementation of Lin_GetStatus() ---------------------------------------------------------- */
    switch (Lin_GetInternalStateOfChannelData(ChannelConfigIdx))
    {
      case LIN_ONSLEEP_PENDING_INTERNALSTATEOFCHANNELDATA:
        Lin_SetSleep(ChannelConfigIdx, LIN_SID_GETSTATUS_ID);
        break;

      case LIN_ONWAKEUP_PENDING_INTERNALSTATEOFCHANNELDATA:
        Lin_SetHardwareWake(ChannelConfigIdx, LIN_SID_GETSTATUS_ID);
        Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONWAKE_INTERNALSTATEOFCHANNELDATA);
        break;

      case LIN_ONRX_OK_INTERNALSTATEOFCHANNELDATA:
        /* store RX Data */
        CANoeAPI_AtomicBegin();
        for(i = 0u; i < 8u; i++)
        {
          Lin_GetShadowDataBufferOfChannelData(ChannelConfigIdx)[i] = Lin_GetDataBufferOfChannelData(ChannelConfigIdx)[i];
        }
        CANoeAPI_AtomicEnd();
        *Lin_SduPtr = Lin_GetShadowDataBufferOfChannelData(ChannelConfigIdx);
        break;

      default:
        /* current state valid or nothing to do */
        break;
    }

    RetTmp = Lin_GetInternalStateOfChannelData(ChannelConfigIdx) & 0x0Fu;       /* mask non ASR sub-states */ /* PRQA S 4442 */ /* MD_LIN_4442 */
/* ------------------------------------------------------------------------------------------------------------------ */
  }

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if(ErrorId != LIN_E_NO_ERROR)
  {
    (void) Lin_Det_ReportError(LIN_SID_GETSTATUS_ID, ErrorId);
  }
#else
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

  LIN_DUMMY_STATEMENT(Channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return (RetTmp);
}

/***********************************************************************************************************************
 *  Lin_CheckWakeup
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LIN_CODE) Lin_CheckWakeup(uint8 Channel)
{
#if( LIN_LEAST_ONE_CHANNEL_WAKEUP_SUPPORT_ENABLED == STD_ON )

  Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx;
  Std_ReturnType RetTmp = E_NOT_OK;
  uint8 ErrorId = LIN_E_NO_ERROR;
# if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if(Lin_Dev_InitDetect != LIN_DEV_INITVALUE)
  {
    ErrorId = LIN_E_UNINIT;
  }
  else if(Lin_GetSizeOfChannelId() <= Channel)
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
#  if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  else if(Lin_IsInvalidHndOfChannelId(Channel))
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  {
    RetTmp = E_OK;
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId(Channel);

    if(Lin_GetInternalStateOfChannelData(ChannelConfigIdx) == LIN_ONWAKEUP_EXTERNAL_INTERNALSTATEOFCHANNELDATA)
    {
      Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONSLEEP_INTERNALSTATEOFCHANNELDATA);
      EcuM_SetWakeupEvent(Lin_GetEcuMWakeupSourceOfChannelConfig(ChannelConfigIdx));
      LinIf_WakeupConfirmation(Lin_GetEcuMWakeupSourceOfChannelConfig(ChannelConfigIdx));
    }
  }

# if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if(ErrorId != LIN_E_NO_ERROR)
  {
    (void) Lin_Det_ReportError(LIN_SID_CHECKWAKEUP_ID, ErrorId);
  }
# else
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif

  LIN_DUMMY_STATEMENT(Channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return (RetTmp);
#else
  LIN_DUMMY_STATEMENT(Channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return E_OK;
#endif
}

/***********************************************************************************************************************
 *  Lin_Wakeup
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LIN_CODE) Lin_Wakeup(uint8 Channel)
{
  Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx;
  Std_ReturnType RetTmp = E_NOT_OK;
  uint8 ErrorId = LIN_E_NO_ERROR;

#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if(Lin_Dev_InitDetect != LIN_DEV_INITVALUE)
  {
    ErrorId = LIN_E_UNINIT;
  }
  else if(Lin_GetSizeOfChannelId() <= Channel)
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  else if(Lin_IsInvalidHndOfChannelId(Channel))
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# endif
  else
#endif
  {
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId(Channel);

#if ( LIN_DEV_ERROR_DETECT == STD_ON )
    if((Lin_GetInternalStateOfChannelData(ChannelConfigIdx) & 0x0Fu) != LIN_ONSLEEP_INTERNALSTATEOFCHANNELDATA)
    {
      ErrorId = LIN_E_STATE_TRANSITION;
    }
    else
#endif
    {
      RetTmp = E_OK;

      Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONWAKEUP_PENDING_INTERNALSTATEOFCHANNELDATA);     /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
/* --- Platform specific implementation of Lin_Wakeup() ------------------------------------------------------------- */
      CANoeAPI_SendLinWakeupFrame(Channel, 125, 0x01);
/* ------------------------------------------------------------------------------------------------------------------ */
    }
  }

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if(ErrorId != LIN_E_NO_ERROR)
  {
    (void) Lin_Det_ReportError(LIN_SID_WAKEUP_ID, ErrorId);
  }
#else
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

  LIN_DUMMY_STATEMENT(Channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return (RetTmp);
}

/***********************************************************************************************************************
 *  Lin_GoToSleep
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LIN_CODE) Lin_GoToSleep(uint8 Channel)
{
  Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx;
  Std_ReturnType RetTmp = E_NOT_OK;
  uint8 ErrorId = LIN_E_NO_ERROR;
  Lin_PduType PduTmp;
  uint8 DataTmp[8];

#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if(Lin_Dev_InitDetect != LIN_DEV_INITVALUE)
  {
    ErrorId = LIN_E_UNINIT;
  }
  else if(Lin_GetSizeOfChannelId() <= Channel)
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  else if(Lin_IsInvalidHndOfChannelId(Channel))
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# endif
  else
#endif
  {
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId(Channel);

    PduTmp.Cs = LIN_CLASSIC_CS;
    PduTmp.Dl = 8;
    PduTmp.Drc = LIN_FRAMERESPONSE_TX;
    PduTmp.Pid = 0x3Cu;
    PduTmp.SduPtr = DataTmp;
    PduTmp.SduPtr[0] = 0x00u;   /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[1] = 0xFFu;   /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[2] = 0xFFu;   /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[3] = 0xFFu;   /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[4] = 0xFFu;   /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[5] = 0xFFu;   /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[6] = 0xFFu;   /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[7] = 0xFFu;   /* SBSW_LIN_BUFFER_WRITE */

    RetTmp = Lin_SendFrame(Channel, &PduTmp);   /* SBSW_LIN_PTR_CALL */

    Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONSLEEP_PENDING_INTERNALSTATEOFCHANNELDATA);        /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
  }

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if(ErrorId != LIN_E_NO_ERROR)
  {
    (void) Lin_Det_ReportError(LIN_SID_GOTOSLEEP_ID, ErrorId);
  }
#else
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

  LIN_DUMMY_STATEMENT(Channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return (RetTmp);
}

/***********************************************************************************************************************
 *  Lin_GoToSleepInternal
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LIN_CODE) Lin_GoToSleepInternal(uint8 Channel)
{
  Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx;
  Std_ReturnType RetTmp = E_NOT_OK;
  uint8 ErrorId = LIN_E_NO_ERROR;

#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if(Lin_Dev_InitDetect != LIN_DEV_INITVALUE)
  {
    ErrorId = LIN_E_UNINIT;
  }
  else if(Lin_GetSizeOfChannelId() <= Channel)
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  else if(Lin_IsInvalidHndOfChannelId(Channel))
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# endif
  else
#else
  LIN_DUMMY_STATEMENT(Channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
  {
    RetTmp = E_OK;
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId(Channel);
    Lin_SetSleep(ChannelConfigIdx, LIN_SID_GOTOSLEEPINTERNAL_ID);
  }

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if(ErrorId != LIN_E_NO_ERROR)
  {
    (void) Lin_Det_ReportError(LIN_SID_GOTOSLEEPINTERNAL_ID, ErrorId);
  }
#else
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

  return (RetTmp);
}

/***********************************************************************************************************************
 *  Lin_WakeupInternal
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LIN_CODE) Lin_WakeupInternal(uint8 Channel)
{
  Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx;
  Std_ReturnType RetTmp = E_NOT_OK;
  uint8 ErrorId = LIN_E_NO_ERROR;
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if(Lin_Dev_InitDetect != LIN_DEV_INITVALUE)
  {
    ErrorId = LIN_E_UNINIT;
  }
  else if(Lin_GetSizeOfChannelId() <= Channel)
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  else if(Lin_IsInvalidHndOfChannelId(Channel))
  {
    ErrorId = LIN_E_INVALID_CHANNEL;
  }
# endif
  else
#endif
  {
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId(Channel);
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
    if((Lin_GetInternalStateOfChannelData(ChannelConfigIdx) & 0x0Fu) != LIN_ONSLEEP_INTERNALSTATEOFCHANNELDATA)
    {
      ErrorId = LIN_E_STATE_TRANSITION;
    }
    else
#endif
    {
      RetTmp = E_OK;
      Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONWAKE_INTERNALSTATEOFCHANNELDATA);       /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      Lin_SetHardwareWake(ChannelConfigIdx, LIN_SID_WAKEUPINTERNAL_ID);
    }
  }
#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if(ErrorId != LIN_E_NO_ERROR)
  {
    (void) Lin_Det_ReportError(LIN_SID_WAKEUPINTERNAL_ID, ErrorId);
  }
#else
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

  LIN_DUMMY_STATEMENT(Channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return (RetTmp);
}

#if ( LIN_VERSION_INFO_API == STD_ON )
/***********************************************************************************************************************
 *  Lin_GetVersionInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, LIN_CODE) Lin_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, LIN_APPL_VAR) versioninfo)
{
  uint8 ErrorId = LIN_E_NO_ERROR;

# if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if(versioninfo == (P2VAR(Std_VersionInfoType, AUTOMATIC, LIN_APPL_VAR)) NULL_PTR)
  {
    ErrorId = LIN_E_PARAM_POINTER;
  }
  else
# endif
  {
    versioninfo->vendorID = LIN_VENDOR_ID;      /* SBSW_LIN_PTR */
    versioninfo->moduleID = LIN_MODULE_ID;      /* SBSW_LIN_PTR */
    versioninfo->sw_major_version = LIN_SW_MAJOR_VERSION;       /* SBSW_LIN_PTR */
    versioninfo->sw_minor_version = LIN_SW_MINOR_VERSION;       /* SBSW_LIN_PTR */
    versioninfo->sw_patch_version = LIN_SW_PATCH_VERSION;       /* SBSW_LIN_PTR */
  }

# if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if(ErrorId != LIN_E_NO_ERROR)
  {
    (void) Lin_Det_ReportError(LIN_SID_GETVERSIONINFO_ID, ErrorId);
  }
# else
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
}
#endif /* LIN_VERSION_INFO_API == STD_ON */

/***********************************************************************************************************************
 *  Lin_InitMemory
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, LIN_CODE) Lin_InitMemory(void)
{
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  Lin_Dev_InitDetect = LIN_DEV_UNINITVALUE;
#endif
}

/***********************************************************************************************************************
 *  Lin_Init
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
 */
FUNC(void, LIN_CODE) Lin_Init(P2CONST(Lin_ConfigType, AUTOMATIC, LIN_PBCFG) Config)
{
  Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx;
  uint8 ErrorId = LIN_E_NO_ERROR;

#if ( LIN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON )
  Rtm_Start(RtmConf_RtmMeasurementPoint_Lin_Init);
#endif
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if(Lin_Dev_InitDetect == LIN_DEV_INITVALUE)
  {
    ErrorId = LIN_E_STATE_TRANSITION;
  }
  else
#endif
  {

#if (LIN_USE_INIT_POINTER == STD_ON)
    if(Config == NULL_PTR)
    {
# if ( LIN_DEV_ERROR_DETECT == STD_ON )
      ErrorId = LIN_E_INVALID_POINTER;
# endif

# if( LIN_USE_ECUM_BSW_ERROR_HOOK == STD_ON )
      EcuM_BswErrorHook(LIN_MODULE_ID, ECUM_BSWERROR_NULLPTR);
# endif
    }
    else
#endif
    {

#if (LIN_USE_INIT_POINTER == STD_ON)
      Lin_ConfigDataPtr = Config;
#else
      LIN_DUMMY_STATEMENT(Config);      /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

#if( LIN_USE_ECUM_BSW_ERROR_HOOK == STD_ON )
      if(Lin_GetHLGeneratorCompatibilityVersion() != (uint16) LIN_HL_GENERATORMSR_COMPATIBILITY_VERSION)
      {
        EcuM_BswErrorHook(LIN_MODULE_ID, ECUM_BSWERROR_COMPATIBILITYVERSION);
      }
      else if(Lin_GetLLGeneratorCompatibilityVersion() != (uint16) LIN_LL_GENERATORMSR_COMPATIBILITY_VERSION)
      {
        EcuM_BswErrorHook(LIN_MODULE_ID, ECUM_BSWERROR_COMPATIBILITYVERSION);
      }
      else if(Lin_GetFinalMagicNumber() != LIN_FINAL_MAGIC_NUMBER)
      {
        EcuM_BswErrorHook(LIN_MODULE_ID, ECUM_BSWERROR_MAGICNUMBER);
      }
      else
#endif
      {
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
        Lin_Dev_InitDetect = LIN_DEV_INITVALUE;
#endif

/* --- Platform specific implementation of Lin_Init() --------------------------------------------------------------- */
        CANoeAPI_SetLinHandler(Lin_CANoeOnMessageHandler, Lin_CANoeOnWakeupHandler, Lin_CANoeOnSleepHandler, Lin_CANoeOnErrorHandler);
/* ------------------------------------------------------------------------------------------------------------------ */
        for(ChannelConfigIdx = 0x00u; ChannelConfigIdx < Lin_GetSizeOfChannelConfig(); ChannelConfigIdx++)
        {
          Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONWAKE_INTERNALSTATEOFCHANNELDATA);   /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
/* --- Platform specific implementation of Lin_Init() - Channel loop - ---------------------------------------------- */
#if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
          Lin_SetSlaveStateOfChannelData(ChannelConfigIdx, LIN_SLAVE_STATE_UNKNOWN);
          Lin_SetFrame3DPollStateOfChannelData(ChannelConfigIdx, LIN_FRAME_3D_POLL_STATE_POLLING);
          Lin_SetPollingLinHeaderStateOfChannelData(ChannelConfigIdx, LIN_POLLING_LINHEADER_ONCE_AFTER_INIT);
#endif
/* ------------------------------------------------------------------------------------------------------------------ */
        }
      }
    }
  }

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if(ErrorId != LIN_E_NO_ERROR)
  {
    (void) Lin_Det_ReportError(LIN_SID_INIT_ID, ErrorId);
  }
#else
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

#if ( LIN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON )
  Rtm_Stop(RtmConf_RtmMeasurementPoint_Lin_Init);
#endif
}

/***********************************************************************************************************************
 *  Lin_SetSleep
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetSleep(Lin_ChannelConfigIdxOfChannelHwType ChannelConfigIdx, uint8 ApiId /* needed only for some hardware */ )
{
/* --- Platform specific implementation of Lin_SetSleep() ----------------------------------------------------------- */
  uint8 channel;

  /* find channel */
  for(channel = 0; channel < Lin_GetSizeOfChannelId(); channel++)
  {
    if(Lin_GetChannelConfigIdxOfChannelId(channel) == ChannelConfigIdx)
    {
      CANoeAPI_SendLinSleepModeFrame(channel, 0x01, 0x00, 0xFF);
    }
  }
  LIN_DUMMY_STATEMENT(ApiId);   /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
/* ------------------------------------------------------------------------------------------------------------------ */

  Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONSLEEP_INTERNALSTATEOFCHANNELDATA);  /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
#if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
  Lin_SetPollingLinHeaderStateOfChannelData(ChannelConfigIdx, LIN_POLLING_LINHEADER_DISABLED);
#endif
}

/***********************************************************************************************************************
 *  Lin_SetHardwareWake
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetHardwareWake(Lin_ChannelConfigIdxOfChannelHwType ChannelConfigIdx, uint8 ApiId /* needed only for some hardware */ )
{
/* --- Platform specific implementation of Lin_SetHardwareWake() ---------------------------------------------------- */
  uint8 channel;

  /* find channel */
  for(channel = 0; channel < Lin_GetSizeOfChannelId(); channel++)
  {
    if(Lin_GetChannelConfigIdxOfChannelId(channel) == ChannelConfigIdx)
    {
      if(Lin_GetInternalStateOfChannelData(channel) != LIN_ONWAKEUP_PENDING_INTERNALSTATEOFCHANNELDATA)
      {
        CANoeAPI_SendLinWakeupFrame(channel, 125, 0x01);
      }
    }
  }
  LIN_DUMMY_STATEMENT(ApiId);   /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
/* ------------------------------------------------------------------------------------------------------------------ */
}

/* --- Platform specific implementation of internal functions ------------------------------------------------------- */

/***********************************************************************************************************************
 *  Lin_GetInternalStateOfChannelData
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(uint8, LIN_CODE) Lin_GetInternalStateOfChannelData(Lin_ChannelConfigIdxOfChannelHwType index)
{
  uint8 ret;
  CANoeAPI_AtomicBegin();
  ret = Lin_GetAtomicInternalStateOfChannelData(index);
  CANoeAPI_AtomicEnd();
  return ret;
}

/***********************************************************************************************************************
 *  Lin_SetInternalStateOfChannelData
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, LIN_CODE) Lin_SetInternalStateOfChannelData(Lin_ChannelConfigIdxOfChannelHwType index, uint8 internalState)
{
  CANoeAPI_AtomicBegin();
  Lin_SetAtomicInternalStateOfChannelData(index, internalState);
  CANoeAPI_AtomicEnd();
}

#if( LIN_LEAST_ONE_CHANNEL_WAKEUP_SUPPORT_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  Lin_CheckIrqWakeupEvent
 **********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_CheckIrqWakeupEvent(Lin_ChannelConfigIdxOfChannelHwType ChannelConfigIdx)
{
  /* #10 If channel has a EcuM Wakeup Source ID */
# if( LIN_LEAST_ONE_CHANNEL_WAKEUP_SUPPORT_DISABLED == STD_ON ) /* COV_LIN_DERIVATIVE */
  if(Lin_GetEcuMWakeupSourceOfChannelConfig(ChannelConfigIdx) != 0)
# endif
  {
    /* #20 Set channel state to external wakeup pending (according DSGN-Lin22334) */
    Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONWAKEUP_EXTERNAL_INTERNALSTATEOFCHANNELDATA);      /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
    /* #30 Call EcuM_CheckWakeup() to inform EcuM about wakeup event */
    EcuM_CheckWakeup(Lin_GetEcuMWakeupSourceOfChannelConfig(ChannelConfigIdx));
  }
}
#endif

#if( LIN_SLAVE_POLL_WORKAROUND == STD_ON )
/***********************************************************************************************************************
 *  VTTLin_Slave1msPoll
 **********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, LIN_CODE) VTTLin_Slave1msPoll(void)
{
  Std_ReturnType ret;
  Lin_PduType LinPdu;
  uint8 data[8];
  uint32 counterPId; /* List could possibly be long */
  uint8 counterChannelId;

  LinPdu.SduPtr = data;

  for(counterChannelId = 0; counterChannelId < Lin_GetSizeOfChannelId(); counterChannelId++)    /* All channel till max Id */
  {
# if (LIN_INVALIDHNDOFCHANNELID == STD_ON)
    /* do nothing if this is an invalid channel */
    if(Lin_IsInvalidHndOfChannelId(counterChannelId))
    {
      continue;
    }
# endif/* (LIN_INVALIDHNDOFCHANNELID == STD_ON) */
    if(Lin_GetPollingLinHeaderStateOfChannelData(counterChannelId) == LIN_POLLING_LINHEADER_DISABLED)
    {
      continue;
    }

    if(Lin_GetPollingLinHeaderStateOfChannelData(counterChannelId) == LIN_POLLING_LINHEADER_ONCE_AFTER_INIT)
    {
      Lin_SetPollingLinHeaderStateOfChannelData(counterChannelId, LIN_POLLING_LINHEADER_DISABLED);
    }

    if(Lin_GetFrame3DPollStateOfChannelData(counterChannelId) == LIN_FRAME_3D_POLL_STATE_POLLING)       /* only poll when no data is waiting */
    {
      /* update 3D frame with data */
      LinPdu.Pid = 0x7Du;
      ret = LinIf_HeaderIndication(counterChannelId, &LinPdu);
      if(LinPdu.Drc == LIN_FRAMERESPONSE_TX)
      {
        Lin_SetFrame3DPollStateOfChannelData(counterChannelId, LIN_FRAME_3D_POLL_STATE_WAITING_FOR_BUS);
        /* confirmation is done in interrupt after frame is processed */
        /* for valid id send the response */
        CANoeAPI_SendLinMessage(counterChannelId, LinPdu.Pid & 0x3FLu, CANOEAPI_LINRECONFIGUREDATA, CANOEAPI_LINRESPONSEALWAYS, LinPdu.Dl, LinPdu.SduPtr);
      }
    }
    /* if a SRF is expected and pending, do no request other frames */
    if(Lin_GetFrame3DPollStateOfChannelData(counterChannelId) != LIN_FRAME_3D_POLL_STATE_WAITING_FOR_BUS)
    {
      for(counterPId = Lin_GetPID_SetStartIdxOfChannelConfig(counterChannelId); counterPId < Lin_GetPID_SetEndIdxOfChannelConfig(counterChannelId); counterPId++)
      {
        /* update all unconditional frame tx responses with data */
        LinPdu.Pid = Lin_GetPID_Set(counterPId);
        ret = LinIf_HeaderIndication(counterChannelId, &LinPdu);
        /* Workaround to not provoke a LinIf problem */
        LinIf_LinErrorIndication(counterChannelId, LIN_ERR_HEADER);
        if(LinPdu.Drc == LIN_FRAMERESPONSE_TX)
        {
          /* for valid id send the response */
          CANoeAPI_SendLinMessage(counterChannelId, LinPdu.Pid & 0x3FLu, CANOEAPI_LINRECONFIGUREDATA, CANOEAPI_LINRESPONSEALWAYS, LinPdu.Dl, LinPdu.SduPtr);
        }
      }
    }
  }
}
#endif /* LIN_SLAVE_POLL_WORKAROUND == STD_ON */

 /***********************************************************************************************************************
 *  VttLin_OnStateChange
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 */
FUNC(void, LIN_CODE) VttLin_OnStateChange(uint8 action, uint8 oldState, uint8 newState)
{
  uint8 counter;

  (void) oldState;
  (void) newState;
  switch (action)
  {
    case CANOEAPI_ECUACTION_NOACTION:
      break;
    case CANOEAPI_ECUACTION_LOAD:
      break;
    case CANOEAPI_ECUACTION_UNLOAD:
      break;
    case CANOEAPI_ECUACTION_INITMEASUREMENT:
      /* set lin slave mode, API only allowed in CANOEAPI_ECUACTION_INITMEASUREMENT */
      for(counter = 0; counter < Lin_GetSizeOfPBSChannelData(); counter++)
      {
#if (LIN_INVALIDHNDOFPBSCHANNELDATA == STD_ON)
        if(!Lin_IsInvalidHndOfPBSChannelData(counter))  /* Only the valide channel -> not invalide */
#endif /* (LIN_INVALIDHNDOFPBSCHANNELDATA == STD_ON) */
        {
          /* Workaround with generation Enum switched against real driver so that Slave is 0 and Master is 1. */
          CANoeAPI_SetLinNodeType(counter, (boolean) Lin_GetPBSNodeTypeOfPBSChannelData(counter), 0, 2, 0);
        }
      }
      break;
    case CANOEAPI_ECUACTION_STARTMEASUREMENT:
    case CANOEAPI_ECUACTION_STOPMEASUREMENT:
    case CANOEAPI_ECUACTION_SWITCHON:
    case CANOEAPI_ECUACTION_SWITCHOFF:
    case CANOEAPI_ECUACTION_GOTOSLEEP:
    case CANOEAPI_ECUACTION_WAKEUP:
    case CANOEAPI_ECUACTION_RESET:
    default:
      break;
  }
}

 /***********************************************************************************************************************
 *  Lin_CANoeEventHandler
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 */
FUNC(void, LIN_CODE) Lin_CANoeEventHandler(uint8 channel, uint8 event, uint8 data[])    /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  Lin_ChannelConfigIdxOfChannelHwType ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId(channel);
  (void) data;
  /* handling of current state */
  switch (Lin_GetInternalStateOfChannelData(ChannelConfigIdx))
  {
    case LIN_ONSLEEP_INTERNALSTATEOFCHANNELDATA:
#if( LIN_LEAST_ONE_CHANNEL_WAKEUP_SUPPORT_ENABLED == STD_ON )
      if((event == 4) && (Lin_GetEcuMWakeupSourceOfChannelConfig(ChannelConfigIdx) != 0))
      {
        VttCntrl_Base_SetCheckedInterrupt(IRQ_LinIsr_0 + channel);
      }
#endif
      break;

    case LIN_ONSLEEP_PENDING_INTERNALSTATEOFCHANNELDATA:
      Lin_SetSleep(ChannelConfigIdx, LIN_SID_INTERRUPT_ID);
      break;

    case LIN_ONWAKEUP_PENDING_INTERNALSTATEOFCHANNELDATA:
      Lin_SetHardwareWake(ChannelConfigIdx, LIN_SID_INTERRUPT_ID);
      Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONWAKE_INTERNALSTATEOFCHANNELDATA);
      break;

    case LIN_ONTX_BUSY_INTERNALSTATEOFCHANNELDATA:
      if(event == 0u)
      { /* TX message successful transmitted */
        Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONTX_OK_INTERNALSTATEOFCHANNELDATA);
      }
      else if(event == 2u)
      { /* No successful TX message but header was successful transmitted */
        Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONTX_ERROR_INTERNALSTATEOFCHANNELDATA);
      }
      else
      { /* No successful TX message and no header was successful transmitted */
        Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONTX_HEADER_ERROR_INTERNALSTATEOFCHANNELDATA);
      }
      break;

    case LIN_ONRX_BUSY_INTERNALSTATEOFCHANNELDATA:
      if(event == 0u)
      { /* Response successfully received */
        Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONRX_OK_INTERNALSTATEOFCHANNELDATA);
      }
      else if(event == 1u)
      { /* no header was successful transmitted */
        Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONTX_HEADER_ERROR_INTERNALSTATEOFCHANNELDATA);
      }
      else if(event == 3u)
      { /* no response byte received */
        Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONRX_NO_RESPONSE_INTERNALSTATEOFCHANNELDATA);
      }
      else
      { /* response partly received */
        Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONRX_ERROR_INTERNALSTATEOFCHANNELDATA);
      }
      break;

    case LIN_ONS2S_BUSY_INTERNALSTATEOFCHANNELDATA:
      if(event == 0u)
      { /* header was successful transmitted */
        Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONTX_OK_INTERNALSTATEOFCHANNELDATA);
      }
      else
      { /* any error on slave to slave is an header error */
        Lin_SetInternalStateOfChannelData(ChannelConfigIdx, LIN_ONTX_HEADER_ERROR_INTERNALSTATEOFCHANNELDATA);
      }
      break;

    default:
      /* interrupt not needed in other states than above --> ignore */
      break;
  }
  LIN_DUMMY_STATEMENT(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

 /***********************************************************************************************************************
 *  Lin_CANoeOnMessageHandler
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 */
FUNC(void, LIN_CODE) Lin_CANoeOnMessageHandler(uint8 channel, uint8 dir, uint32 id, uint8 dlc, uint8 data[])    /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  uint8 i;
  uint8 d[8];
  Lin_ChannelConfigIdxOfChannelHwType ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId(channel);

#if defined ( LIN_CANOE_API_REVERSE_ENGINEERING_MSG_HANDLER )
  char str[1000];
  sprintf(str, "%f: VLinMsgHandler( %u, %u, %u, %u )", (float32) CANoeAPI_UserTimer_CurrentTime() / 1000000000, channel, dir, id, dlc);
  CANoeAPI_WriteString(str);
#else
  LIN_DUMMY_STATEMENT(id);      /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  LIN_DUMMY_STATEMENT(dir);     /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

  CANoeAPI_AtomicBegin();
#if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
  if(Lin_GetNodeTypeOfChannelConfig(ChannelConfigIdx) == LIN_SLAVE_NODETYPEOFCHANNELCONFIG)
  {
    Lin_GetSlavePduOfChannelData(ChannelConfigIdx).Drc = dir;
    Lin_GetSlavePduOfChannelData(ChannelConfigIdx).Dl = dlc;
    Lin_GetSlavePduOfChannelData(ChannelConfigIdx).Pid = Lin_AllPid[id];
    Lin_GetSlavePduOfChannelData(ChannelConfigIdx).SduPtr = Lin_GetShadowDataBufferOfChannelData(ChannelConfigIdx);
    for(i = 0; i < dlc; i++)
    {
      Lin_GetShadowDataBufferOfChannelData(ChannelConfigIdx)[i] = data[i];
    }
    Lin_SetSlaveStateOfChannelData(ChannelConfigIdx, LIN_SLAVE_STATE_FRAME_COMPLETE);
    Lin_SetPollingLinHeaderStateOfChannelData(ChannelConfigIdx, LIN_POLLING_LINHEADER_ENABLED);
    /* call interrupt */
    VttCntrl_Base_SetCheckedInterrupt(IRQ_LinIsr_0 + channel);
  }
  else
#endif
  {
    /* copy data to 8 byte buffer does not matter if it shorter */
    for(i = 0; i < dlc; i++)
    {
      d[i] = data[i];
      Lin_GetDataBufferOfChannelData(ChannelConfigIdx)[i] = data[i];
    }
    Lin_CANoeEventHandler(channel, 0, d);
  }
  CANoeAPI_AtomicEnd();

}

 /***********************************************************************************************************************
 *  Lin_CANoeOnErrorHandler
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 */
FUNC(void, LIN_CODE) Lin_CANoeOnErrorHandler(uint8 channel, uint32 errorCode, uint32 subcode, uint32 id)
{
#if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
  Lin_ChannelConfigIdxOfChannelHwType ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId(channel);
#endif
#if defined ( LIN_CANOE_API_REVERSE_ENGINEERING )
  char str[1000];
  sprintf(str, "%f: VLinErrorHandler( %u, 0x%x, 0x%x, %u/0x%x )", (float32) CANoeAPI_UserTimer_CurrentTime() / 1000000000, channel, errorCode, subcode, id, id);
  CANoeAPI_WriteString(str);
#endif
#if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
  if(Lin_GetNodeTypeOfChannelConfig(ChannelConfigIdx) == LIN_SLAVE_NODETYPEOFCHANNELCONFIG)
  {     /* enable header polling when error occured */
    Lin_SetPollingLinHeaderStateOfChannelData(ChannelConfigIdx, LIN_POLLING_LINHEADER_ENABLED);
  }
#endif
/* *INDENT-OFF* */
  if ( ((errorCode == 0x03u) && (subcode == 0x20u) && ( id <= 64u )) ||
       ((errorCode == 0x03u) && (subcode == 0x4du) && ( id <= 64u )) ||
       ((errorCode == 0x03u) && (subcode == 0x10u) && ( id <= 64u )) ||
       ((errorCode == 0x04u) && (subcode == 0x00u) && ( id == 0xFFFFFFFFu )) || /* CANOEAPI_LINSYNCHERROR  */
       ((errorCode == 0x03u) && (subcode == 0x13u) && ( id <= 64u )) ||
       ((errorCode == 0x03u) && (subcode == 0x23u) && ( id <= 64u )) )
  {
#if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
    if (Lin_GetNodeTypeOfChannelConfig(ChannelConfigIdx) == LIN_SLAVE_NODETYPEOFCHANNELCONFIG)
    {
      Lin_SetSlaveStateOfChannelData(ChannelConfigIdx, LIN_SLAVE_STATE_HEADER_ERROR);
      /* call interrupt */
      VttCntrl_Base_SetCheckedInterrupt(IRQ_LinIsr_0 + channel);
    }
    else
#endif
    {
      Lin_CANoeEventHandler(channel, 1, NULL_PTR);        /* Header error */
    }
  }
  else if( ((errorCode == 0x03u) && (subcode >= 0x05u) && (subcode <= 0x0cu) && ( id <= 64u )) || /* bit error */
           ((errorCode == 0x03u) && (subcode >= 0x25u) && (subcode <= 0x2bu) && ( id <= 64u )) ||
           ((errorCode == 0x03u) && (subcode >= 0x24u) && (subcode <= 0x2Cu) && ( id <= 64u )) ||
           ((errorCode == 0x02u) && (subcode == 0x00u)                      && ( id <= 64u )) ||  /* checksum error */
           ((errorCode == 0x02u) && (subcode == 0x01u)                      && ( id <= 64u )) )   /* checksum error on go-to-sleep-command */
  {
#if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
    if (Lin_GetNodeTypeOfChannelConfig(ChannelConfigIdx) == LIN_SLAVE_NODETYPEOFCHANNELCONFIG)
    {
      Lin_SetSlaveStateOfChannelData(ChannelConfigIdx, LIN_SLAVE_STATE_ANY_ERROR);
      Lin_GetSlavePduOfChannelData(ChannelConfigIdx).Pid = Lin_AllPid[id];
      /* call interrupt */
      VttCntrl_Base_SetCheckedInterrupt(IRQ_LinIsr_0 + channel);
    }
    else
#endif
    {
      Lin_CANoeEventHandler(channel, 2, NULL_PTR);        /* error */
    }
  }
  else if((errorCode == 0x01u) && (subcode == 0x00u))
  {
#if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
    if (Lin_GetNodeTypeOfChannelConfig(ChannelConfigIdx) == LIN_SLAVE_NODETYPEOFCHANNELCONFIG)
    {
      Lin_SetSlaveStateOfChannelData(ChannelConfigIdx, LIN_SLAVE_STATE_NO_RESPONSE_ERROR);
      Lin_GetSlavePduOfChannelData(ChannelConfigIdx).Pid = Lin_AllPid[id];
      /* call interrupt */
      VttCntrl_Base_SetCheckedInterrupt(IRQ_LinIsr_0 + channel);
    }
    else
#endif
    {
      Lin_CANoeEventHandler(channel, 3, NULL_PTR);        /* no response */
    }
  }
  else
  {
    /* error pattern not needed */
  }
/* *INDENT-ON* */
}

 /***********************************************************************************************************************
 *  Lin_CANoeOnWakeupHandler
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 */
FUNC(void, LIN_CODE) Lin_CANoeOnWakeupHandler(uint8 channel, uint8 external)
{
#if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
  Lin_ChannelConfigIdxOfChannelHwType ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId(channel);
#endif

#if defined ( LIN_CANOE_API_REVERSE_ENGINEERING )
  char str[1000];
  sprintf(str, "%f: VLinWakeupHandler( %d, %d )", (float32) CANoeAPI_UserTimer_CurrentTime() / 1000000000, channel, external);
  CANoeAPI_WriteString(str);
#else
  LIN_DUMMY_STATEMENT(external);        /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

#if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
  if(Lin_GetNodeTypeOfChannelConfig(ChannelConfigIdx) == LIN_SLAVE_NODETYPEOFCHANNELCONFIG)
  {     /* enable header polling on wakeup */
    Lin_SetPollingLinHeaderStateOfChannelData(ChannelConfigIdx, LIN_POLLING_LINHEADER_ENABLED);
  }
#endif

  Lin_CANoeEventHandler(channel, 4, NULL_PTR);
}

 /***********************************************************************************************************************
 *  Lin_CANoeOnSleepHandler
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 */
FUNC(void, LIN_CODE) Lin_CANoeOnSleepHandler(uint8 channel, uint8 external, uint8 isAwake, uint8 wasAwake, uint8 reason)
{
#if defined ( LIN_CANOE_API_REVERSE_ENGINEERING )
  char str[1000];
  sprintf(str, "%f: VLinSleepHandler( %d, %d, %d, %d, %d )", (float32) CANoeAPI_UserTimer_CurrentTime() / 1000000000, channel, external, isAwake, wasAwake, reason);
  CANoeAPI_WriteString(str);
#else
  LIN_DUMMY_STATEMENT(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  LIN_DUMMY_STATEMENT(external);        /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  LIN_DUMMY_STATEMENT(isAwake); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  LIN_DUMMY_STATEMENT(wasAwake);        /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  LIN_DUMMY_STATEMENT(reason);  /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

/* not needed, because the go-to-sleep-command is indicated by the VLinMsgHandler or VLinErrorHandle */
}

/* ------------------------------------------------------------------------------------------------------------------ */

#define LIN_STOP_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

/* module specific MISRA deviations:

  MD_LIN_2784:
   Reason: The CANoeAPI_SendLinMessage() API has an array with the length 8 as a parameter.
           The passed pointer could point to an array with a length smaller than 8.
           The The CANoeAPI_SendLinMessage() API is only called by the Lin_GoToSleep() API,
           where the passe pointer points to an array of length 8.
   Risk: The CANoeAPI_SendLinMessage() could write to or read from an area outside of the passed array.
   Prevention: Investigation of the passed pointer value of the CANoeAPI_SendLinMessage() API.
               The CANoeAPI_SendLinMessage() API is only called by the Lin_GoToSleep() API,
               where the passe pointer points to an array of length 8.

  MD_LIN_4442:
   Reason: An expression of 'essentially unsigned' type is being converted to enum type, on assignment.
           The Lin_GetStatus() API has to return a value of the enum Type Lin_StatusType
           The return value of operation has to be converted to the Lin_StatusType.
           The value of the Lin_GetInternalStateOfChannelData() API is of the unsigend type.
           The Lin_GetInternalStateOfChannelData() returns a value of the type Lin_AtomicInternalStateOfChannelDataType
           which is a type consistiting of the StatusType as a lower nibble and an internal Type as the higer nibble.
   Risk: a wrong value is returned
   Prevention: review if the Lin_StatusType and the Lin_AtomicInternalStateOfChannelDataType returend by the Lin_GetInternalStateOfChannelData() API are matching.

*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_LIN_PTR_HW
  \DESCRIPTION The function accesses a hardware register using a pointer access.
  \COUNTERMEASURE \T The code inspection and tests on hardware ensure that the memory location
                     referenced contains the registers with the same structure as specified.
                  \S Verify that the values generated match the address of register of the used hardware.

  \ID SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID
  \DESCRIPTION Access to InternalState via indirection over ChannelId.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib.

  \ID SBSW_LIN_BUFFER_WRITE
  \DESCRIPTION Write to the array of constant size.
  \COUNTERMEASURE \R The index based access to the array uses constant index values. The buffer is statically allocated
                     with fixed size (e.g. 8 bytes). The size is sufficient for the largest used index value (e.g. 7).

  \ID SBSW_LIN_PTR
  \DESCRIPTION The function writes to the object referenced by parameter.
  \COUNTERMEASURE \N The caller ensures that the pointers passed to the parameter is valid.

  \ID SBSW_LIN_PTR_CALL
  \DESCRIPTION The function call uses a pointer parameter.
  \COUNTERMEASURE \N A local variable is used and Lin_SendFrame copy the data to internal buffer.

SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION

  \ID COV_LIN_COMPILER
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XX
  \REASON The source code covers different compilers. There is however only a subset of the compilers released for
          safeBSW, therefore the code of the unsupported compilers is not covered.

  \ID COV_LIN_DERIVATIVE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XX
  \REASON The source code covers different derivatives. There is however only a subset of the derivatives released for
          safeBSW, therefore the code of the unsupported derivatives features or existing/not existing erratas is not
          covered.

  \ID COV_LIN_TOOL_ISSUE
  \ACCEPT TX tx xf
  \REASON Tool issue. Condition depends on include path.

  \ID COV_LIN_INTEGRATION
  \ACCEPT XF
  \REASON The include of the transceiver types header is not tested in the LIN driver test suite because it is a stub
          test without transceiver driver.

  \ID COV_LIN_COMPATIBILITY
  \ACCEPT TX
  \REASON [COV_MSR_COMPATIBILITY]

END_COVERAGE_JUSTIFICATION */

/**********************************************************************************************************************
 *  END OF FILE: Lin.c
 *********************************************************************************************************************/
