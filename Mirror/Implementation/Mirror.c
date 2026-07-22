/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**     \file     Mirror.c
 *      \brief    MIRROR source file
 *
 *      \details  Implementation of Mirror component.
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
#define MIRROR_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror.h"
#include "Mirror_Int.h"

#include "Mirror_SourceChannelCan.h"
#include "Mirror_SourceChannelLin.h"

#include "Mirror_DestChannel.h"

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
# include "Mirror_DestChannelIP.h"
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
# include "Mirror_DestChannelCan.h"
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#include "SchM_Mirror.h"

#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if (MIRROR_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
# include "EcuM_Error.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Check the version of Mirror header file */
#if (  (MIRROR_SW_MAJOR_VERSION != (4u)) \
    || (MIRROR_SW_MINOR_VERSION != (0u)) \
    || (MIRROR_SW_PATCH_VERSION != (3u)) )
# error "Vendor specific version numbers of <Mirror>.c and <Mirror>.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (MIRROR_CFG_MAJOR_VERSION != (2u)) \
    || (MIRROR_CFG_MINOR_VERSION != (0u)))
# error "Version numbers of <Mirror>.c and <Mirror>_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define MIRROR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/*! Global state of the Mirror module. */
MIRROR_LOCAL VAR(Mirror_GeneralContextType, MIRROR_VAR_ZERO_INIT) Mirror_GeneralCtx = { 0 };

#define MIRROR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#define MIRROR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_USE_INIT_POINTER == STD_ON)
/*! Mirror PostBuild configuration. */
P2CONST(Mirror_ConfigType, MIRROR_VAR_NOINIT, MIRROR_PBCFG) Mirror_ConfigDataPtr;
#endif

#define MIRROR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/**********************************************************************************************************************
 *  Mirror_InitMemory()
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
FUNC(void, MIRROR_CODE)Mirror_InitMemory(void)
{
  /* #10 Set the Mirror module to not initialized. */
  Mirror_GeneralCtx.ModuleInitialized = MIRROR_UNINIT;

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
  /* #20 Trigger the initialization of source channel CAN. */
  Mirror_SourceChannelCan_InitMemory();
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
  /* #30 Trigger the initialization of source channel LIN. */
  Mirror_SourceChannelLin_InitMemory();
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
  /* #40 Trigger the initialization of source channel FlexRay. */
  Mirror_SourceChannelFlexRay_InitMemory();
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */
} /* Mirror_InitMemory() */

/**********************************************************************************************************************
 *  Mirror_Init()
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
FUNC(void, MIRROR_CODE) Mirror_Init(P2CONST(Mirror_ConfigType, AUTOMATIC, MIRROR_PBCFG) configPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = MIRROR_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is not initialized yet. */
  if (Mirror_GeneralCtx.ModuleInitialized != MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_REINIT;
#endif
  }
#if (MIRROR_USE_INIT_POINTER == STD_ON)
  /* #20 If "MIRROR_USE_INIT_POINTER" is enabled, check if the configuration data pointer is set. */
  else if(configPtr == NULL_PTR)
  {
# if (MIRROR_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
    EcuM_BswErrorHook(MIRROR_MODULE_ID, ECUM_BSWERROR_NULLPTR);
# endif
    errorId = MIRROR_E_PARAM_POINTER;
  }
  else
# if (MIRROR_FINALMAGICNUMBER == STD_ON)
   /* #30 Check if the final magic number is correct. */
  if(configPtr->FinalMagicNumberOfPBConfig != MIRROR_FINAL_MAGIC_NUMBER)
  {
#  if (MIRROR_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
    EcuM_BswErrorHook(MIRROR_MODULE_ID, ECUM_BSWERROR_MAGICNUMBER);
#  endif
    errorId = MIRROR_E_INIT_FAILED;
  }
  /* #40 If the initial checks are passed or not required: */
  else
# endif
#else
  MIRROR_DUMMY_STATEMENT(configPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8 channelType;
    Mirror_SourceComMChannelIterType sourceComMChannelIdx;

    /* #50 Set global Mirror mode to inactive. */
    Mirror_GeneralCtx.GlobalMode = MIRROR_INACTIVE;

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
    Mirror_GeneralCtx.StartTime.nanoseconds = 0u;
    Mirror_GeneralCtx.StartTime.seconds = 0u;
    Mirror_GeneralCtx.StartTime.secondsHi = 0u;
    Mirror_GeneralCtx.StartTime.timeBaseStatus = 0u;
#endif

#if (MIRROR_USE_INIT_POINTER == STD_ON)
    Mirror_ConfigDataPtr = configPtr;
#endif

    /* #60 Trigger the initialization of all configured source channels. */
    for(sourceComMChannelIdx = 0u; sourceComMChannelIdx < Mirror_GetSizeOfSourceComMChannel(); sourceComMChannelIdx++)
    {
# if (MIRROR_INVALIDHNDOFSOURCECOMMCHANNEL == STD_ON)
      if(!Mirror_IsInvalidHndOfSourceComMChannel(sourceComMChannelIdx))
# endif
      {
#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
        if(Mirror_GetChannelTypeOfSourceComMChannel(sourceComMChannelIdx) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFSOURCECOMMCHANNEL)
        {
          Mirror_SourceChannelCan_Init(Mirror_GetSourceChannelCanIdxOfSourceComMChannel(sourceComMChannelIdx), &Mirror_GeneralCtx);
        }
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
        if(Mirror_GetChannelTypeOfSourceComMChannel(sourceComMChannelIdx) == MIRROR_E_MIRROR_CHANNEL_LIN_CHANNELTYPEOFSOURCECOMMCHANNEL)
        {
          Mirror_SourceChannelLin_Init(Mirror_GetSourceChannelLinIdxOfSourceComMChannel(sourceComMChannelIdx), &Mirror_GeneralCtx);
        }
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
        if(Mirror_GetChannelTypeOfSourceComMChannel(sourceComMChannelIdx) == MIRROR_E_MIRROR_CHANNEL_FLEXRAY_CHANNELTYPEOFSOURCECOMMCHANNEL)
        {
          Mirror_SourceChannelFlexRay_Init(Mirror_GetSourceChannelFlexRayIdxOfSourceComMChannel(sourceComMChannelIdx), &Mirror_GeneralCtx);
        }
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */
      }
    }

    /* #70 Set the default destination channel. */
    Mirror_GeneralCtx.CurrentDestChannelIndex = (NetworkHandleType)Mirror_GetMirrorDestinationChannelDefault();

    channelType = (uint8)Mirror_GetChannelTypeOfDestComMChannel(Mirror_GeneralCtx.CurrentDestChannelIndex);

    /* #80 Trigger the initialization of the current destination channel. */
#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
    {
      Mirror_DestChannelCan_Init(&Mirror_GeneralCtx);
    }
#endif

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
    {
      Mirror_DestChannelIp_Init(&Mirror_GeneralCtx);
    }
#endif

    /* #90 Set the Mirror module to initialized state. */
    Mirror_GeneralCtx.ModuleInitialized = (uint8) MIRROR_INIT;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON) && (MIRROR_USE_INIT_POINTER == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_INIT, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_Init() */

/**********************************************************************************************************************
 * Mirror_DeInit()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DeInit(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if the Mirror module is initialized, if error detection is enabled. */
  if(Mirror_GeneralCtx.ModuleInitialized != MIRROR_INIT)
  {
    errorId = MIRROR_E_UNINIT;
  }
#endif

  /* #20 Set the state of Mirror module to not initialized. */
  Mirror_GeneralCtx.ModuleInitialized = MIRROR_UNINIT;

  /* ----- Development Error Report ------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  { 
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_DEINIT, errorId); 
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 
} /* Mirror_DeInit() */

#if (MIRROR_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Mirror_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, MIRROR_CODE)Mirror_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, MIRROR_APPL_VAR) versioninfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (MIRROR_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if version information pointer is set. */
  if(versioninfo == NULL_PTR)
  {
    errorId = MIRROR_E_PARAM_POINTER;
  }
  /* #20 If the initial checks are passed or not required: */
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Copy required information. */
    versioninfo->vendorID = (MIRROR_VENDOR_ID);
    versioninfo->moduleID = (MIRROR_MODULE_ID);
    versioninfo->sw_major_version = (MIRROR_SW_MAJOR_VERSION);
    versioninfo->sw_minor_version = (MIRROR_SW_MINOR_VERSION);
    versioninfo->sw_patch_version = (MIRROR_SW_PATCH_VERSION);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_GET_VERSION_INFO, errorId);
  }
# else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
} /* Mirror_GetVersionInfo() */
#endif /* (MIRROR_VERSION_INFO_API == STD_ON) */

/**********************************************************************************************************************
 * Mirror_GetStaticFilterState()
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
/* PRQA S 3673 1 */ /* MD_MSR_Rule8.13 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_GetStaticFilterState(NetworkHandleType network, uint8 filterId, boolean* isActive)
{
 /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MIRROR_E_NO_ERROR;

#if(((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_OFF)) || ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTER == STD_OFF)))
  MIRROR_DUMMY_STATEMENT(filterId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(isActive); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the network ID is valid. */
  else if(network >= Mirror_GetSizeOfSourceComMChannel())
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# if (MIRROR_INVALIDHNDOFSOURCECOMMCHANNEL == STD_ON)
  else if(Mirror_IsInvalidHndOfSourceComMChannel(network))
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# endif
  /* #30 Check if the passed value for isActive is set. */
  else if(isActive == NULL_PTR)
  {
    errorId = MIRROR_E_PARAM_POINTER;
  }
#endif
  /* #40 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8 channelType = (uint8)Mirror_GetChannelTypeOfSourceComMChannel(network);

    /* #50 Get the current state of the given static filter for the Mirror source channel assigned to the given network. */
#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
#if (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON)
      retVal = Mirror_SourceChannelCan_GetStaticFilterState(Mirror_GetSourceChannelCanIdxOfSourceComMChannel(network), filterId, isActive);
#endif
    }
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_LIN_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
#if (MIRROR_SOURCECHANNELLINSTATICFILTER == STD_ON)
      retVal = Mirror_SourceChannelLin_GetStaticFilterState(Mirror_GetSourceChannelLinIdxOfSourceComMChannel(network), filterId, isActive);
#endif
    }
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_FLEXRAY_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
#if (MIRROR_SOURCECHANNELFLEXRAYSTATICFILTER == STD_ON)
      retVal = Mirror_SourceChannelFlexRay_GetStaticFilterState(Mirror_GetSourceChannelFlexRayIdxOfSourceComMChannel(network), filterId, isActive);
#endif
    }
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_GET_STATIC_FILTER_STATE, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_GetStaticFilterState() */

/**********************************************************************************************************************
 * Mirror_SetStaticFilterState()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SetStaticFilterState(NetworkHandleType network, uint8 filterId, boolean isActive)
{
 /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MIRROR_E_NO_ERROR;

#if(((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_OFF)) || ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTER == STD_OFF)))
  MIRROR_DUMMY_STATEMENT(filterId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(isActive); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the network ID is valid. */
  else if(network >= Mirror_GetSizeOfSourceComMChannel())
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# if (MIRROR_INVALIDHNDOFSOURCECOMMCHANNEL == STD_ON)
  else if(Mirror_IsInvalidHndOfSourceComMChannel(network))
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# endif
#endif
  /* #30 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8 channelType = (uint8)Mirror_GetChannelTypeOfSourceComMChannel(network);

    /* #40 Trigger the state change of the given static filter for the Mirror source channel assigned to the given network. */
#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
#if (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON)
      retVal = Mirror_SourceChannelCan_SetStaticFilterState(Mirror_GetSourceChannelCanIdxOfSourceComMChannel(network), filterId, isActive);
#endif
    }
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_LIN_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
#if (MIRROR_SOURCECHANNELLINSTATICFILTER == STD_ON)
      retVal = Mirror_SourceChannelLin_SetStaticFilterState(Mirror_GetSourceChannelLinIdxOfSourceComMChannel(network), filterId, isActive);
#endif
    }
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_FLEXRAY_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
#if (MIRROR_SOURCECHANNELFLEXRAYSTATICFILTER == STD_ON)
      retVal = Mirror_SourceChannelFlexRay_SetStaticFilterState(Mirror_GetSourceChannelFlexRayIdxOfSourceComMChannel(network), filterId, isActive);
#endif
    }
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_SET_STATIC_FILTER_STATE, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
} /* Mirror_SetStaticFilterState() */

/**********************************************************************************************************************
 * Mirror_RemoveFilter()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_RemoveFilter(NetworkHandleType network, uint8 filterId)
{
 /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MIRROR_E_NO_ERROR;

  MIRROR_DUMMY_STATEMENT(filterId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the network ID is valid. */
  else if(network >= Mirror_GetSizeOfSourceComMChannel())
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# if (MIRROR_INVALIDHNDOFSOURCECOMMCHANNEL == STD_ON)
  else if(Mirror_IsInvalidHndOfSourceComMChannel(network))
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# endif
#endif
  /* #30 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8 channelType = (uint8)Mirror_GetChannelTypeOfSourceComMChannel(network);

    /* #40 Trigger the deletion of the given dynamic filter for the Mirror source channel assigned to the given network. */
#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
#if (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON)
      retVal = Mirror_SourceChannelCan_RemoveFilter(Mirror_GetSourceChannelCanIdxOfSourceComMChannel(network), filterId);
#endif
    }
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_LIN_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
#if (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON)
      retVal = Mirror_SourceChannelLin_RemoveFilter(Mirror_GetSourceChannelLinIdxOfSourceComMChannel(network), filterId);
#endif
    }
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_FLEXRAY_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
#if (MIRROR_SOURCECHANNELFLEXRAYDYNAMICFILTER == STD_ON)
      retVal = Mirror_SourceChannelFlexRay_RemoveFilter(Mirror_GetSourceChannelFlexRayIdxOfSourceComMChannel(network), filterId);
#endif
    }
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_REMOVE_FILTER, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
} /* Mirror_RemoveFilter() */

/**********************************************************************************************************************
 * Mirror_IsMirrorActive()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, MIRROR_CODE) Mirror_IsMirrorActive(void)
{
 /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = FALSE;
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
  /* #20 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #30 Return the current global Mirror state. */
    retVal = (boolean)Mirror_GeneralCtx.GlobalMode;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_IS_MIRROR_ACTIVE, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
} /* Mirror_IsMirrorActive() */

/**********************************************************************************************************************
 * Mirror_Offline()
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
FUNC(void, MIRROR_CODE) Mirror_Offline(void)
{
 /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
  /* #20 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 If the Mirror module is currently active: */
    if(Mirror_GeneralCtx.GlobalMode == MIRROR_ACTIVE)
    {
      uint8 channelType;
      Mirror_SourceComMChannelIterType sourceComMChannelIdx;

      /* #40 Set the global state to inactive */
      Mirror_GeneralCtx.GlobalMode = MIRROR_INACTIVE;

      /* #50 Trigger the deactivation of all active source channels. */
      for(sourceComMChannelIdx = 0u; sourceComMChannelIdx < Mirror_GetSizeOfSourceComMChannel(); sourceComMChannelIdx++)
      {
# if (MIRROR_INVALIDHNDOFSOURCECOMMCHANNEL == STD_ON)
        if(!Mirror_IsInvalidHndOfSourceComMChannel(sourceComMChannelIdx))
# endif
        {
#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
          if(Mirror_GetChannelTypeOfSourceComMChannel(sourceComMChannelIdx) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFSOURCECOMMCHANNEL)
          {
            Mirror_SourceChannelCan_Offline(Mirror_GetSourceChannelCanIdxOfSourceComMChannel(sourceComMChannelIdx));
          }
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
          if(Mirror_GetChannelTypeOfSourceComMChannel(sourceComMChannelIdx) == MIRROR_E_MIRROR_CHANNEL_LIN_CHANNELTYPEOFSOURCECOMMCHANNEL)
          {
            Mirror_SourceChannelLin_Offline(Mirror_GetSourceChannelLinIdxOfSourceComMChannel(sourceComMChannelIdx));
          }
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
          if(Mirror_GetChannelTypeOfSourceComMChannel(sourceComMChannelIdx) == MIRROR_E_MIRROR_CHANNEL_FLEXRAY_CHANNELTYPEOFSOURCECOMMCHANNEL)
          {
            Mirror_SourceChannelFlexRay_Offline(Mirror_GetSourceChannelFlexRayIdxOfSourceComMChannel(sourceComMChannelIdx));
          }
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */
        }
      }

      /* #60 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
      SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

      /* #70 Trigger the reset to default of the current destination channel. */
#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
      if(Mirror_GetChannelTypeOfDestComMChannel(Mirror_GeneralCtx.CurrentDestChannelIndex) == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
      {
        Mirror_DestChannelIp_Init(&Mirror_GeneralCtx);
      }
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
      if(Mirror_GetChannelTypeOfDestComMChannel(Mirror_GeneralCtx.CurrentDestChannelIndex) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
      {
        Mirror_DestChannelCan_Init(&Mirror_GeneralCtx);
      }
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

      /* #80 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

      /* #90 Set the current destination channel to the default value and initialize the default destination channel. */
      Mirror_GeneralCtx.CurrentDestChannelIndex = (NetworkHandleType)Mirror_GetMirrorDestinationChannelDefault();

      channelType = (uint8)Mirror_GetChannelTypeOfDestComMChannel(Mirror_GeneralCtx.CurrentDestChannelIndex);

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
      if(channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
      {
         Mirror_DestChannelCan_Init(&Mirror_GeneralCtx);
      }
#endif

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
      if(channelType == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
      {
          Mirror_DestChannelIp_Init(&Mirror_GeneralCtx);
      }
#endif
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_OFFLINE, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 
  /* PRQA S 6010 3 */ /* MD_MSR_STPTH */
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_Offline() */

/**********************************************************************************************************************
 * Mirror_GetDestNetwork()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(NetworkHandleType, MIRROR_CODE) Mirror_GetDestNetwork(void)
{
 /* ----- Local Variables ---------------------------------------------- */
  NetworkHandleType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the Mirror module is not initialized yet, return the default destination channel. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
    retVal = (NetworkHandleType)Mirror_GetMirrorDestinationChannelDefault();
  }
  /* #20 Otherwise, return the current destination channel. */
  else
  {
    retVal = Mirror_GeneralCtx.CurrentDestChannelIndex;
  }

  return retVal;
} /* Mirror_GetDestNetwork() */

/**********************************************************************************************************************
 * Mirror_SwitchDestNetwork()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SwitchDestNetwork(NetworkHandleType network)
{
 /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the network ID is valid. */
  else if(network >= Mirror_GetSizeOfDestComMChannel())
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# if (MIRROR_INVALIDHNDOFDESTCOMMCHANNEL == STD_ON)
  else if(Mirror_IsInvalidHndOfDestComMChannel(network))
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# endif
#endif
  /* #30 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 If the given network is not already active: */
    if(Mirror_GeneralCtx.CurrentDestChannelIndex != network)
    {
      /* #50 Trigger the reset of all source and destination channel */
      if(Mirror_GeneralCtx.GlobalMode == MIRROR_ACTIVE)
      {
        Mirror_Offline();
      }

      Mirror_GeneralCtx.CurrentDestChannelIndex = network;

      /* #60 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
      SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

      /* #70 Set the given network as current destination channel and initialize it. */
#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
      if(Mirror_GetChannelTypeOfDestComMChannel(Mirror_GeneralCtx.CurrentDestChannelIndex) == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
      {
        Mirror_DestChannelIp_Init(&Mirror_GeneralCtx);
      }
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
      if(Mirror_GetChannelTypeOfDestComMChannel(Mirror_GeneralCtx.CurrentDestChannelIndex) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
      {
        Mirror_DestChannelCan_Init(&Mirror_GeneralCtx);
      }
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

      /* #80 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_SWITCH_DEST_NETWORK, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_SwitchDestNetwork() */

/**********************************************************************************************************************
 * Mirror_IsSourceNetworkStarted()
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
FUNC(boolean, MIRROR_CODE) Mirror_IsSourceNetworkStarted(NetworkHandleType network)
{
 /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = FALSE;
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the network ID is valid. */
  else if(network >= Mirror_GetSizeOfSourceComMChannel())
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# if (MIRROR_INVALIDHNDOFSOURCECOMMCHANNEL == STD_ON)
  else if(Mirror_IsInvalidHndOfSourceComMChannel(network))
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# endif
#endif
  /* #30 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8 channelType = (uint8)Mirror_GetChannelTypeOfSourceComMChannel(network);

    /* #40 Enter MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
    SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();

    /* #50 Return the state of the source channel assigned to the given network. */
#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
      if((Mirror_GetSourceChannelCanState(Mirror_GetSourceChannelCanStateIdxOfSourceChannelCan((uint8)Mirror_GetSourceChannelCanIdxOfSourceComMChannel(network)))).IsEnabled == TRUE)
      {
        retVal = TRUE;
      }
    }
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_LIN_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
      if((Mirror_GetSourceChannelLinState(Mirror_GetSourceChannelLinStateIdxOfSourceChannelLin((uint8)Mirror_GetSourceChannelLinIdxOfSourceComMChannel(network)))).IsEnabled == TRUE)
      {
        retVal = TRUE;
      }
    }
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_FLEXRAY_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
      if((Mirror_GetSourceChannelFlexRayState(Mirror_GetSourceChannelFlexRayStateIdxOfSourceChannelFlexRay((uint8)Mirror_GetSourceChannelFlexRayIdxOfSourceComMChannel(network)))).IsEnabled == TRUE)
      {
        retVal = TRUE;
      }
    }
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */

    /* #60 Leave MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_IS_SOURCE_NETWORK_STARTED, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_IsSourceNetworkStarted() */

/**********************************************************************************************************************
 *  Mirror_StartSourceNetwork()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_StartSourceNetwork(NetworkHandleType network)
{
 /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the network ID is valid. */
  else if(network >= Mirror_GetSizeOfSourceComMChannel())
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# if (MIRROR_INVALIDHNDOFSOURCECOMMCHANNEL == STD_ON)
  else if(Mirror_IsInvalidHndOfSourceComMChannel(network))
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# endif
#endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8 channelType = (uint8)Mirror_GetChannelTypeOfSourceComMChannel(network);

    /* #30 Enter MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
    SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();

    /* #40 Activate the Mirror module if the global Mirror state is inactive. */
    if(Mirror_GeneralCtx.GlobalMode == MIRROR_INACTIVE)
    {
      Mirror_GeneralCtx.GlobalMode = MIRROR_ACTIVE;

#if(MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
      retVal = Mirror_DestChannel_GetTime(&Mirror_GeneralCtx.StartTime);
#endif
    }

    /* #50 Leave MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();

    /* #60 Trigger the activation of the source channel assigned to the given network. */
#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
      retVal = Mirror_SourceChannelCan_StartSourceNetwork((uint8) Mirror_GetSourceChannelCanIdxOfSourceComMChannel(network));
    }
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_LIN_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
      retVal = Mirror_SourceChannelLin_StartSourceNetwork(network);
    }
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_FLEXRAY_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
      retVal = Mirror_SourceChannelFlexRay_StartSourceNetwork((uint8) Mirror_GetSourceChannelFlexRayIdxOfSourceComMChannel(network));
    }
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_START_SOURCE_NETWORK, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
} /* Mirror_StartSourceNetwork() */

/**********************************************************************************************************************
 *  Mirror_StopSourceNetwork()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_StopSourceNetwork(NetworkHandleType network)
{
 /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the network ID is valid. */
  else if(network >= Mirror_GetSizeOfSourceComMChannel())
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# if (MIRROR_INVALIDHNDOFSOURCECOMMCHANNEL == STD_ON)
  else if(Mirror_IsInvalidHndOfSourceComMChannel(network))
  {
    errorId = MIRROR_E_INVALID_NETWORK_ID;
  }
# endif
#endif
  /* #30 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8 channelType = (uint8)Mirror_GetChannelTypeOfSourceComMChannel(network);

    /* #40 Trigger the deactivation of the source channel assigned to the given network. */
#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
      retVal = Mirror_SourceChannelCan_StopSourceNetwork((uint8) Mirror_GetSourceChannelCanIdxOfSourceComMChannel(network));
    }
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_LIN_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
      retVal = Mirror_SourceChannelLin_StopSourceNetwork(network);
    }
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
    if(channelType == MIRROR_E_MIRROR_CHANNEL_FLEXRAY_CHANNELTYPEOFSOURCECOMMCHANNEL)
    {
      retVal = Mirror_SourceChannelFlexRay_StopSourceNetwork((uint8) Mirror_GetSourceChannelFlexRayIdxOfSourceComMChannel(network));
    }
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_STOP_SOURCE_NETWORK, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
} /* Mirror_StopSourceNetwork() */

/**********************************************************************************************************************
 * Mirror_GetNetworkType()
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
FUNC(Mirror_NetworkType, MIRROR_CODE)  Mirror_GetNetworkType(NetworkHandleType network)
{
 /* ----- Local Variables ---------------------------------------------- */
  Mirror_NetworkType retVal = MIRROR_NT_INVALID;
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
  /* #20 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8 channelType;

    /* #30 Check if the given network can be assigned to a source channel: */
    if(network < Mirror_GetSizeOfSourceComMChannel())
    {
#if (MIRROR_INVALIDHNDOFSOURCECOMMCHANNEL == STD_ON)
      if(!Mirror_IsInvalidHndOfSourceComMChannel(network))
#endif
      {
        channelType = (uint8)Mirror_GetChannelTypeOfSourceComMChannel(network);

        /* #40 Return the type of the source channel assigned to the given network. */
#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
        if(channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFSOURCECOMMCHANNEL)
        {
          retVal = MIRROR_NT_CAN;
        }
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
        if(channelType == MIRROR_E_MIRROR_CHANNEL_LIN_CHANNELTYPEOFSOURCECOMMCHANNEL)
        {
          retVal = MIRROR_NT_LIN;
        }
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
        if(channelType == MIRROR_E_MIRROR_CHANNEL_FLEXRAY_CHANNELTYPEOFSOURCECOMMCHANNEL)
        {
          retVal = MIRROR_NT_FLEXRAY;
        }
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */
      }
    }

    /* #50 If the given network is not assigned to a source channel: */
    if(retVal == MIRROR_NT_INVALID)
    {
      /* #60 Check if the given network can be assigned to a destination channel: */
      if(network < Mirror_GetSizeOfDestComMChannel())
      {
#if (MIRROR_INVALIDHNDOFDESTCOMMCHANNEL == STD_ON)
        if(!Mirror_IsInvalidHndOfDestComMChannel(network))
#endif
        {
          channelType = (uint8) Mirror_GetChannelTypeOfDestComMChannel(network);

          /* #70 Return the type of the destination channel assigned to the given network. */
#if(MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
          if(channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
          {
            retVal = MIRROR_NT_CAN;
          }
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if(MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
          if(channelType == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
          {
            retVal = MIRROR_NT_ETHERNET;
          }
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */
        }
      }
    }

    /* #80 Check if the given network could be assigned to any source or destination network and report an error if not. */
    if(retVal == MIRROR_NT_INVALID)
    {
      errorId = MIRROR_E_INVALID_NETWORK_ID;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_GET_NETWORK_TYPE, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
  /* PRQA S 6010 3 */ /* MD_MSR_STPTH */
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_GetNetworkType() */

/**********************************************************************************************************************
 * Mirror_GetNetworkId()
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
FUNC(uint8, MIRROR_CODE)  Mirror_GetNetworkId(NetworkHandleType network)
{
 /* ----- Local Variables ---------------------------------------------- */
  uint8 retVal = 0xFFu;
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
  /* #20 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if the given network can be assigned to a source channel: */
    if(network < Mirror_GetSizeOfSourceComMChannel())
    {
#if (MIRROR_INVALIDHNDOFSOURCECOMMCHANNEL == STD_ON)
      if(!Mirror_IsInvalidHndOfSourceComMChannel(network))
#endif
      {
        uint8 channelType = (uint8)Mirror_GetChannelTypeOfSourceComMChannel(network);

        /* #40 Return the Id of the source channel assigned to the given network. */
#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
        if(channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFSOURCECOMMCHANNEL)
        {
          retVal = (uint8) Mirror_GetNetworkIdOfSourceChannelCan(Mirror_GetSourceChannelCanIdxOfSourceComMChannel(network));
        }
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
        if(channelType == MIRROR_E_MIRROR_CHANNEL_LIN_CHANNELTYPEOFSOURCECOMMCHANNEL)
        {
          retVal = (uint8) Mirror_GetNetworkIdOfSourceChannelLin(Mirror_GetSourceChannelLinIdxOfSourceComMChannel(network));
        }
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
        if(channelType == MIRROR_E_MIRROR_CHANNEL_FLEXRAY_CHANNELTYPEOFSOURCECOMMCHANNEL)
        {
          retVal = (uint8) Mirror_GetNetworkIdOfSourceChannelFlexRay(Mirror_GetSourceChannelFlexRayIdxOfSourceComMChannel(network));
        }
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */
      }
    }

    /* #50 If the given network is not assigned to a source channel: */
    if(retVal == 0xFFu)
    {
      /* #60 Check if the given network can be assigned to a destination channel: */
      if(network < Mirror_GetSizeOfDestComMChannel())
      {
#if (MIRROR_INVALIDHNDOFDESTCOMMCHANNEL == STD_ON)
        if(!Mirror_IsInvalidHndOfDestComMChannel(network))
#endif
        {
          uint8 channelType = (uint8) Mirror_GetChannelTypeOfDestComMChannel(network);

          /* #70 Return the Id of the destination channel assigned to the given network. */
#if(MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
          if(channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
          {
            retVal = (uint8) Mirror_GetNetworkIdOfDestinationChannelCan(Mirror_GetDestinationChannelCanIdxOfDestComMChannel(network));
          }
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if(MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
          if(channelType == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
          {
            retVal = (uint8) Mirror_GetNetworkIdOfDestinationChannelIp(Mirror_GetDestinationChannelIpIdxOfDestComMChannel(network));
          }
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */
        }
      }
    }

    /* #80 Check if the given network could be assigned to any source or destination network and report an error if not. */
    if(retVal == 0xFFu)
    {
      errorId = MIRROR_E_INVALID_NETWORK_ID;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_GET_NETWORK_ID, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
  /* PRQA S 6010 3 */ /* MD_MSR_STPTH */
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_GetNetworkId() */

/**********************************************************************************************************************
 * Mirror_GetNetworkHandle()
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
FUNC(NetworkHandleType, MIRROR_CODE)  Mirror_GetNetworkHandle(Mirror_NetworkType networkType, uint8 networkId)
{
 /* ----- Local Variables ---------------------------------------------- */
  NetworkHandleType retVal = 0xFFu;
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
  /* #20 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    Mirror_SourceComMChannelIterType sourceComMChannelIdx;

    /* #30 If there is a source channel that matches the given Mirror networkId and networkType, return the global network Id. */
    for(sourceComMChannelIdx = 0u; sourceComMChannelIdx < Mirror_GetSizeOfSourceComMChannel(); sourceComMChannelIdx++)
    {
# if (MIRROR_INVALIDHNDOFSOURCECOMMCHANNEL == STD_ON)
      if(!Mirror_IsInvalidHndOfSourceComMChannel(sourceComMChannelIdx))
# endif
      {
#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
        if((Mirror_GetChannelTypeOfSourceComMChannel(sourceComMChannelIdx) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFSOURCECOMMCHANNEL) && (networkType == MIRROR_NT_CAN))
        {
          if((Mirror_GetNetworkIdOfSourceChannelCan(Mirror_GetSourceChannelCanIdxOfSourceComMChannel(sourceComMChannelIdx)) == networkId))
          {
            retVal = (NetworkHandleType)sourceComMChannelIdx;
          }
        }
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
        if((Mirror_GetChannelTypeOfSourceComMChannel(sourceComMChannelIdx) == MIRROR_E_MIRROR_CHANNEL_LIN_CHANNELTYPEOFSOURCECOMMCHANNEL) && (networkType == MIRROR_NT_LIN))
        {
          if((Mirror_GetNetworkIdOfSourceChannelLin(Mirror_GetSourceChannelLinIdxOfSourceComMChannel(sourceComMChannelIdx)) == networkId))
          {
            retVal = (NetworkHandleType)sourceComMChannelIdx;
          }
        }
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
        if((Mirror_GetChannelTypeOfSourceComMChannel(sourceComMChannelIdx) == MIRROR_E_MIRROR_CHANNEL_FLEXRAY_CHANNELTYPEOFSOURCECOMMCHANNEL) && (networkType == MIRROR_NT_FLEXRAY))
        {
          if((Mirror_GetNetworkIdOfSourceChannelFlexRay(Mirror_GetSourceChannelFlexRayIdxOfSourceComMChannel(sourceComMChannelIdx)) == networkId))
          {
            retVal = (NetworkHandleType)sourceComMChannelIdx;
          }
        }
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */
      }
    }

    /* #40 If the given combination of Mirror networkId and networkType does not match any source channel: */
    if(retVal == 0xFFu)
    {
      Mirror_DestComMChannelIterType destComMChannelIdx;

      /* #50 If there is a destination channel that matches the given Mirror networkId and networkType, return the global network Id. */
      for(destComMChannelIdx = 0u; destComMChannelIdx < Mirror_GetSizeOfDestComMChannel(); destComMChannelIdx++)
      {
#if (MIRROR_INVALIDHNDOFDESTCOMMCHANNEL == STD_ON)
        if(!Mirror_IsInvalidHndOfDestComMChannel(destComMChannelIdx))
#endif
        {
          uint8 channelType = (uint8)Mirror_GetChannelTypeOfDestComMChannel(destComMChannelIdx);

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
          if((channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL) && (networkType == MIRROR_NT_CAN))
          {
            if(Mirror_GetNetworkIdOfDestinationChannelCan(Mirror_GetDestinationChannelCanIdxOfDestComMChannel(destComMChannelIdx)) == networkId)
            {
              retVal = (NetworkHandleType)destComMChannelIdx;
            }
          }
#endif

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
          if((channelType == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL) && (networkType == MIRROR_NT_ETHERNET))
          {
            if(Mirror_GetNetworkIdOfDestinationChannelIp(Mirror_GetDestinationChannelIpIdxOfDestComMChannel(destComMChannelIdx)) == networkId)
            {
              retVal = (NetworkHandleType)destComMChannelIdx;
            }
          }
#endif
        }
      }
    }

    /* #60 Check if the given combination of Mirror networkId and networkType could be assigned to any source or destination network and report an error if not. */
    if(retVal == 0xFFu)
    {
      errorId = MIRROR_E_INVALID_NETWORK_ID;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_GET_NETWORK_NETWORK_HANDLE, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
  /* PRQA S 6010 3 */ /* MD_MSR_STPTH */
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */  
} /* Mirror_GetNetworkHandle() */

/**********************************************************************************************************************
* Mirror_MainFunction()
**********************************************************************************************************************/
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
FUNC(void, MIRROR_APPL_CODE)Mirror_MainFunction(void)
{
  /* #10 Check if the Mirror module is initialized. */
  if (Mirror_GeneralCtx.ModuleInitialized == MIRROR_INIT)
  {
    /* #20 If the global Mirror mode is active: */
    if(Mirror_GeneralCtx.GlobalMode == MIRROR_ACTIVE)
    {
      Mirror_SourceComMChannelIterType sourceComMChannelIdx;
      NetworkHandleType currentDestChannelIndex;

      /* #30 Trigger the handling of all cyclic actions of all active source channels. */
      for(sourceComMChannelIdx = 0u; sourceComMChannelIdx < Mirror_GetSizeOfSourceComMChannel(); sourceComMChannelIdx++)
      {
#if (MIRROR_INVALIDHNDOFSOURCECOMMCHANNEL == STD_ON)
        if(!Mirror_IsInvalidHndOfSourceComMChannel(sourceComMChannelIdx))
#endif
        {
          uint8 channelType = (uint8)Mirror_GetChannelTypeOfSourceComMChannel(sourceComMChannelIdx);

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
          if(channelType == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFSOURCECOMMCHANNEL)
          {
            Mirror_SourceChannelCan_MainFunction(Mirror_GetSourceChannelCanIdxOfSourceComMChannel(sourceComMChannelIdx));
          }
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
          if(channelType == MIRROR_E_MIRROR_CHANNEL_LIN_CHANNELTYPEOFSOURCECOMMCHANNEL)
          {
            Mirror_SourceChannelLin_MainFunction(Mirror_GetSourceChannelLinIdxOfSourceComMChannel(sourceComMChannelIdx));
          }
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
          if(channelType == MIRROR_E_MIRROR_CHANNEL_FLEXRAY_CHANNELTYPEOFSOURCECOMMCHANNEL)
          {
            Mirror_SourceChannelFlexRay_MainFunction(Mirror_GetSourceChannelFlexRayIdxOfSourceComMChannel(sourceComMChannelIdx));
          }
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */
        }
      }

      /* #40 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
      SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

      /* #50 Get the current destination channel. */
      currentDestChannelIndex = Mirror_GeneralCtx.CurrentDestChannelIndex;

      /* #60 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

      /* #70 Trigger the handling of all cyclic actions of the current destination channel. */
#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
      if(Mirror_GetChannelTypeOfDestComMChannel(currentDestChannelIndex) == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
      {
        Mirror_DestChannelIp_MainFunction();
      }
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
      if(Mirror_GetChannelTypeOfDestComMChannel(currentDestChannelIndex) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
      {
        Mirror_DestChannelCan_MainFunction();
      }
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */
    }
  }
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_MainFunction() */

/**********************************************************************************************************************
 * Mirror_TxConfirmation()
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
FUNC(void, MIRROR_CODE) Mirror_TxConfirmation(PduIdType TxPduId)
{
 /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
  /* #20 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    NetworkHandleType destChannelIndex;
    PduIdType localPduId = 0u;

    /* #30 Enter MIRROR_EXCLUSIVE_AREA_TXPDU. */
    SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();

    /* #40 Get the current destination channel. */
    destChannelIndex = Mirror_GeneralCtx.CurrentDestChannelIndex;

    /* #50 Check if the given TxPduId matches the TxPduId of the current destination channel: */
#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
    if(Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
    {
      localPduId = Mirror_GetMirrorConfTxPduIdOfDestinationChannelIp(Mirror_GetDestinationChannelIpIdxOfDestComMChannel(destChannelIndex));
    }
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
    if(Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
    {
      localPduId = Mirror_GetMirrorConfTxPduIdOfDestinationChannelCan(Mirror_GetDestinationChannelCanIdxOfDestComMChannel(destChannelIndex));
    }
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

    if(TxPduId == localPduId)
    {
      /* #60 Release the TxPdu lock. */
      Mirror_GeneralCtx.DestChannel_TxPduLocked = FALSE;

      /* #70 Leave MIRROR_EXCLUSIVE_AREA_TXPDU. */
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();

      /* #80 Trigger the handling of the TxConfirmation for the current destination channel. */
#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
      if(Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
      {
        Mirror_DestChannelCan_TxConfirmation();
      }
#endif

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
      if(Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
      {
          Mirror_DestChannelIp_TxConfirmation();
      }
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */
    }
    /* #90 Otherwise, leave MIRROR_EXCLUSIVE_AREA_TXPDU and report an error. */
    else
    {
      errorId = MIRROR_E_INVALID_PDU_SDU_ID;
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_TXCONFIRMATION, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 
} /* Mirror_TxConfirmation() */

/**********************************************************************************************************************
 * Mirror_RxIndication()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_RxIndication(PduIdType rxPduId,
                                            P2CONST(PduInfoType, AUTOMATIC, MIRROR_APPL_DATA) pduInfoPtr)
{
  /* #10 Dummy API only necessary for PduR */
  MIRROR_DUMMY_STATEMENT(rxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(pduInfoPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_RXINDICATION, MIRROR_E_DUMMY_API);
#endif
} /* Mirror_RxIndication() */

/**********************************************************************************************************************
 *  Mirror_TriggerTransmit
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr)
{
 /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_GeneralCtx.ModuleInitialized == (uint8) MIRROR_UNINIT)
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the given PduInfoPtr is valid. */
  else if(PduInfoPtr == NULL_PTR)
  {
    errorId = MIRROR_E_PARAM_POINTER;
  }
# endif
  /* #30 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    NetworkHandleType destChannelIndex;
    PduIdType localPduId = 0u;

    /* #40 Enter MIRROR_EXCLUSIVE_AREA_TXPDU. */
    SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();

    /* #50 Get the current destination channel. */
    destChannelIndex = Mirror_GeneralCtx.CurrentDestChannelIndex;

    /* #60 Check if the given TxPduId matches the TxPduId of the current destination channel: */
#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
    if(Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
    {
      localPduId = Mirror_GetMirrorConfTxPduIdOfDestinationChannelIp(Mirror_GetDestinationChannelIpIdxOfDestComMChannel(destChannelIndex));
    }
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
    if(Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
    {
      localPduId = Mirror_GetMirrorConfTxPduIdOfDestinationChannelCan(Mirror_GetDestinationChannelCanIdxOfDestComMChannel(destChannelIndex));
    }
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

    if(TxPduId == localPduId)
    {
      /* #70 Leave MIRROR_EXCLUSIVE_AREA_TXPDU. */
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();

      /* #80 Trigger the handling of the TriggerTransmit for the current destination channel. */
#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
      if(Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
      {
        retVal = Mirror_DestChannelCan_TriggerTransmit(PduInfoPtr);
      }
#endif

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
      if(Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
      {
        retVal = Mirror_DestChannelIp_TriggerTransmit(PduInfoPtr);
      }
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */
    }
    /* #90 Otherwise, leave MIRROR_EXCLUSIVE_AREA_TXPDU and report an error. */
    else
    {
      errorId = MIRROR_E_INVALID_PDU_SDU_ID;
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_TRIGGER_TRANSMIT, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_TriggerTransmit() */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/*================================================= MIRROR_STOP_SEC_CODE ============================================*/

/* Module specific MISRA deviations:

 MD_Mirror_3218_FileScopeStatic
      Reason:     There might be setups where an global variable is used in just one function but in other setups
                  in multiple functions.
      Risk:       None
      Prevention: N/A
*/

/**********************************************************************************************************************
 *  END OF FILE: Mirror.c
 *********************************************************************************************************************/
