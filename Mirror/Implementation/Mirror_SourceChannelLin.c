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
/**     \file     Mirror_SourceChannelLin.c
 *      \brief    Mirror LIN source channel source file
 *
 *      \details  Implementation of Mirror LIN source channel.
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
#define MIRROR_SOURCECHANNELLIN_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_SourceChannelLin.h"
#include "Mirror.h"

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

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
# include "LinIf.h"
# include "Lin_GeneralTypes.h"
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define MIRROR_SOURCECHANNEL_LIN_PID_MASK    (0x3Fu)

#define MIRROR_SOURCECHANNEL_LIN_NETWORKSTATE_AVAILABLE      (0x80u)
#define MIRROR_SOURCECHANNEL_LIN_NETWORKSTATE_NOT_AVAILABLE  (0x00u)
#define MIRROR_SOURCECHANNEL_LIN_FRAMEID_AVAILABLE           (0x40u)
#define MIRROR_SOURCECHANNEL_LIN_FRAMEID_NOT_AVAILABLE       (0x00u)
#define MIRROR_SOURCECHANNEL_LIN_PAYLOAD_AVAILABLE           (0x20u)

#define MIRROR_SOURCECHANNEL_LIN_BUS_ONLINE                  (0x40u)
#define MIRROR_SOURCECHANNEL_LIN_FRAME_RX_NO_RESPONSE        (0x01u)
#define MIRROR_SOURCECHANNEL_LIN_FRAME_RX_ERROR              (0x02u)
#define MIRROR_SOURCECHANNEL_LIN_BUS_TX_ERROR                (0x04u)
#define MIRROR_SOURCECHANNEL_LIN_BUS_HEADER_TX_ERROR         (0x08u)

#define MIRROR_SOURCECHANNEL_LIN_CAN_STANDARD_ID_MAX         (0x7FFu)
#define MIRROR_SOURCECHANNEL_LIN_CANID_EXTENDED_IF_FLAG      (0x80000000u)

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define MIRROR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/*! Global state of the Mirror module. */
MIRROR_LOCAL VAR(Mirror_GeneralContextType*, MIRROR_VAR_ZERO_INIT) Mirror_SourceChannelLin_GeneralCtx = NULL_PTR;   /* PRQA S 3218 */ /* MD_Mirror_3218_FileScopeStatic */

#define MIRROR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelLin_GetState()
*********************************************************************************************************************/
/*! \brief       Returns the current state of a LIN source channel
*  \details     -
*  \param[in]   sourceChannelIdx     Internal index of the LIN source channel.
*  \param[in]   destNetworkType      Type of the destination network which requests the LIN channel state
*  \param[in]   mirrorLinFrameState  State of a LIN frame
*  \param[out]  metaData             Meta data
*  \param[out]  networkId            Network Id of the LIN source channel
*  \param[out]  networkState         State of the LIN source channel
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   FALSE
*  \synchronous TRUE
*  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
*********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE)Mirror_SourceChannelLin_GetState(Mirror_SourceChannelLinIterType sourceChannelIdx,
                                                                                           Mirror_NetworkType destNetworkType, 
                                                                                           Mirror_SourceChannelLinFrameStateType mirrorLinFrameState,
                                                                                           uint8* metaData, uint8* networkId,
                                                                                           uint8* networkState);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON))
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_AddDynamicFilter()
 *********************************************************************************************************************/
/*! \brief       Creates a LIN dynamic filter.
 *  \details     -
 *  \param[in]   network           ComM channel that corresponds to the LIN bus to which the filter shall be attached.
 *  \param[out]  filterId          Id of the newly created filter.
 *  \param[in]   valueLowerOrId    Lower LIN ID of the range or Id.
 *  \param[in]   valueUpperOrMask  Upper LIN ID of the range or Mask.
 *  \param[in]   isIdMaskFilter    Flag that indicates if a Range or Id/Mask filter shall be created.
 *  \return      E_OK: New filter created.
 *  \return      E_NOT_OK: Creation of filter failed because of invalid parameters or because no filter on the given
 *                         network was free.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE for different networks.
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON and 
 *               MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelLin_AddDynamicFilter(NetworkHandleType network, uint8* filterId,
                                                             uint32 valueLowerOrId, uint32 valueUpperOrMask,
                                                             boolean isIdMaskFilter);
#endif /* ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTER == STD_ON))
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_ProcessStaticFilter()
 *********************************************************************************************************************/
/*! \brief       Function searches for matching static filter.
 *  \details     Only active filters will be evaluated.
 *  \param[in]   sourceChannelIdx  Index of the source channel
 *  \param[in]   id                ID of the frame
 *  \return      TRUE if filter matched, FALSE if not
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON and
 *               MIRROR_SOURCECHANNELLINSTATICFILTER == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_SourceChannelLin_ProcessStaticFilter(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 id);
#endif /* ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTER == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON))
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_ProcessDynamicFilter()
 *********************************************************************************************************************/
/*! \brief       Function searches for matching dynamic filter.
 *  \details     Only active filters will be evaluated.
 *  \param[in]   sourceChannelIdx  Index of the source channel
 *  \param[in]   id                ID of the frame
 *  \return      TRUE if filter matched, FALSE if not
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON and
 *               MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_SourceChannelLin_ProcessDynamicFilter(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 id);
#endif /* ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON)) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_ProcessFilter()
 *********************************************************************************************************************/
/*! \brief       Function searches for matching filter.
 *  \details     Only active filters will be evaluated.
 *  \param[in]   sourceChannelIdx  Index of the source channel
 *  \param[in]   id                ID of the frame
 *  \return      TRUE if filter matched, FALSE if not
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_SourceChannelLin_ProcessFilter(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 id);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON))
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_GetCanId()
 *********************************************************************************************************************/
/*! \brief       Calculates the CAN Id for a LIN Id.
 *  \details     Function is only called for LIN frames that passed the filter.
 *  \param[in]   sourceChannelIdx  Internal index of the source channel.
 *  \param[in]   id                Id of the frame
 *  \return      The CAN Id based on the given LIN Id.
 *  \pre         Module is initialized.
 *  \context     ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON and
 *               MIRROR_DESTINATION_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(uint32, MIRROR_CODE) Mirror_SourceChannelLin_GetCanId(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 id);
#endif /* ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) 
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_GetFrameState()
 *********************************************************************************************************************/
/*! \brief       Function returns the Mirror frame state for the given LIN status.
 *  \details     Function is only called for LIN frames that passed the filter.
 *  \param[in]   status   LIN frame status.
 *  \return      The Mirror LIN frame status.
 *  \pre         Module is initialized.
 *  \context     ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(Mirror_SourceChannelLinFrameStateType, MIRROR_CODE) Mirror_SourceChannelLin_GetFrameState(Lin_StatusType status);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_ProcessFrame()
 *********************************************************************************************************************/
/*! \brief       Handles the destination bus specific actions to process the incoming frame.
 *  \details     Function is only called for LIN frames that passed the filter.
 *  \param[in]   sourceChannelIdx  Internal index of the source channel.
 *  \param[in]   id                Id of the frame
 *  \param[in]   pdu               payload and length
 *  \param[in]   status            status of the frame
 *  \pre         Module is initialized.
 *  \context     ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_SourceChannelLin_ProcessFrame(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 id, const PduInfoType* pdu, Lin_StatusType status);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelLin_ProcessStatus()
*********************************************************************************************************************/
/*! \brief      Handles a new state of the bus.
*  \details     -
*  \param[in]   sourceChannelIdx  Internal index of the Lin source channel.
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   FALSE
*  \synchronous TRUE
*  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
*********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_SourceChannelLin_ProcessStatus(Mirror_SourceChannelLinIterType sourceChannelIdx);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelLin_GetBusState()
*********************************************************************************************************************/
/*! \brief      Gets the state of a LIN bus.
*  \details     -
*  \param[in]   sourceChannelIdx  Internal index of the LIN source channel.
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   FALSE
*  \synchronous TRUE
*  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
*********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_SourceChannelLin_GetBusState(Mirror_SourceChannelLinIterType sourceChannelIdx);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelLin_GetState()
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
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE)Mirror_SourceChannelLin_GetState(Mirror_SourceChannelLinIterType sourceChannelIdx,
                                                                                           Mirror_NetworkType destNetworkType, 
                                                                                           Mirror_SourceChannelLinFrameStateType mirrorLinFrameState,
                                                                                           uint8* metaData, uint8* networkId,
                                                                                           uint8* networkState)
{
  Std_ReturnType retVal = E_NOT_OK;
  Mirror_SourceChannelLinStateType* sourceChannelState = &Mirror_GetSourceChannelLinState(Mirror_GetSourceChannelLinStateIdxOfSourceChannelLin(sourceChannelIdx));

  /* #10 If the given source channel is enabled: */
  if (sourceChannelState->IsEnabled == TRUE)
  {
    /* #20 Return network type and Mirror network Id. */
    (*metaData) = (uint8)MIRROR_NT_LIN;

    (*networkState) = 0u;

    (*networkId) = (uint8)Mirror_GetNetworkIdOfSourceChannelLin(sourceChannelIdx);

    /* #30 If the state of the LIN bus assigned to the source channel has changed: */
    if (sourceChannelState->HasStateChanged == TRUE)
    {
      /* #40 Return the network state and mark it as available. */
      (*metaData) |= MIRROR_SOURCECHANNEL_LIN_NETWORKSTATE_AVAILABLE;

      if (sourceChannelState->State == MIRROR_SOURCECHANNELLIN_STATE_ONLINE)
      {
        (*networkState) |= MIRROR_SOURCECHANNEL_LIN_BUS_ONLINE;
      }

      sourceChannelState->HasStateChanged = FALSE;

      retVal = E_OK;
    }

    /* #50 If the status is requested in the context of a reported LIN frame: */
    if (mirrorLinFrameState == MIRROR_SOURCECHANNELLIN_FRAMESTATE_OK)
    {
      /* #60 If the source channel state information shall be used for a destination network (IP, FlexRay, CDD) that uses the AUTOSAR Protocol,
       *     return the frame Id and payload available flags. */
      if ((destNetworkType == MIRROR_NT_FLEXRAY) || (destNetworkType == MIRROR_NT_ETHERNET) || (destNetworkType == MIRROR_NT_PROPRIETARY))
      {
        (*metaData) |= MIRROR_SOURCECHANNEL_LIN_FRAMEID_AVAILABLE | MIRROR_SOURCECHANNEL_LIN_PAYLOAD_AVAILABLE;
      }

      retVal = E_OK;
    }
    /* #70 Otherwise, the state is requested cyclic and no frame state is available: */
    else if (mirrorLinFrameState != MIRROR_SOURCECHANNELLIN_FRAMESTATE_UNUSED)
    {
      /* #80 Add the transmission and reception errors to the returned state. */
      (*metaData) |= MIRROR_SOURCECHANNEL_LIN_NETWORKSTATE_AVAILABLE;
      (*metaData) |= MIRROR_SOURCECHANNEL_LIN_FRAMEID_AVAILABLE;

      (*networkState) |= MIRROR_SOURCECHANNEL_LIN_BUS_ONLINE;

      if (mirrorLinFrameState == MIRROR_SOURCECHANNELLIN_FRAMESTATE_HEADER_TRANSMISSION_ERROR)
      {
        (*networkState) |= MIRROR_SOURCECHANNEL_LIN_BUS_HEADER_TX_ERROR;
      }

      if (mirrorLinFrameState == MIRROR_SOURCECHANNELLIN_FRAMESTATE_TRANSMISSION_ERROR)
      {
        (*networkState) |= MIRROR_SOURCECHANNEL_LIN_BUS_TX_ERROR;
      }

      if (mirrorLinFrameState == MIRROR_SOURCECHANNELLIN_FRAMESTATE_RECEPTION_ERROR)
      {
        (*networkState) |= MIRROR_SOURCECHANNEL_LIN_FRAME_RX_ERROR;
      }

      if (mirrorLinFrameState == MIRROR_SOURCECHANNELLIN_FRAMESTATE_NO_RESPONSE_ERROR)
      {
        (*networkState) |= MIRROR_SOURCECHANNEL_LIN_FRAME_RX_NO_RESPONSE;
      }

      retVal = E_OK;
    }
    else
    {
      /* MISRA */
    }
  }

  return retVal;
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* Mirror_SourceChannelLin_GetState() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON))
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_AddDynamicFilter()
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
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelLin_AddDynamicFilter(NetworkHandleType network, uint8* filterId,
                                                             uint32 valueLowerOrId, uint32 valueUpperOrMask,
                                                             boolean isIdMaskFilter)
{
  Std_ReturnType retVal = E_NOT_OK;
  Mirror_SizeOfSourceChannelLinType sourceChannelIdx = Mirror_GetSourceChannelLinIdxOfSourceComMChannel(network);

  /* #10 If the given source channel supports dynamic filter: */
  if(Mirror_IsSourceChannelLinDynamicFilterIndUsedOfSourceChannelLin(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    Mirror_SourceChannelLinDynamicFilterIndIterType sourceChannelFilterIdx;
    uint8 newFilterId = 0u;

    /* #20 Search for a free dynamic filter: */
    for(sourceChannelFilterIdx = Mirror_GetSourceChannelLinDynamicFilterIndStartIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelFilterIdx < Mirror_GetSourceChannelLinDynamicFilterIndEndIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelFilterIdx++)
    {
      Mirror_SourceChannelLinDynamicFilterType* dynamicLinFilter = &Mirror_GetSourceChannelLinDynamicFilter(Mirror_GetSourceChannelLinDynamicFilterInd(sourceChannelFilterIdx));

      if(dynamicLinFilter->IsActive == FALSE)
      {
        /* #30 Store the given filter parameter and activate the new filter. */
        dynamicLinFilter->IsActive = TRUE;
        dynamicLinFilter->FilterId = newFilterId;
        dynamicLinFilter->IsIdMaskFilter = isIdMaskFilter;
        dynamicLinFilter->FilterValueLowOrId = valueLowerOrId;
        dynamicLinFilter->FilterValueHighOrMask = valueUpperOrMask;

        /* #40 Return the Id of the new filter. */
        (*filterId) = newFilterId;

        retVal = E_OK;

        break;
      }

      newFilterId++;
    }
  }

  return retVal;
} /* Mirror_SourceChannelLin_AddDynamicFilter() */
#endif /* ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTER == STD_ON))
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_ProcessStaticFilter()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_SourceChannelLin_ProcessStaticFilter(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 id)
{
  Mirror_SourceChannelLinStaticFilterStateIndIterType sourceChannelFilterIdx;
  boolean filterMatched = FALSE;

  /* #10 If the given source channel supports static filter: */
  if(Mirror_IsSourceChannelLinStaticFilterIndUsedOfSourceChannelLin(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    /* #20 Go through all active static filter (Id and Range) and check if one of the filter matches the given Id. If a filter matches, return TRUE. */
    for(sourceChannelFilterIdx = Mirror_GetSourceChannelLinStaticFilterStateIndStartIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelFilterIdx < Mirror_GetSourceChannelLinStaticFilterStateIndEndIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelFilterIdx++)
    {
      if(Mirror_IsSourceChannelLinStaticFilterState(Mirror_GetSourceChannelLinStaticFilterStateInd(sourceChannelFilterIdx)))
      {
#if (MIRROR_EXISTS_E_MIRROR_SOURCENETWORK_FILTER_TYPE_ID_FILTERTYPEOFSOURCECHANNELLINSTATICFILTER == STD_ON)
        if(Mirror_GetFilterTypeOfSourceChannelLinStaticFilter(Mirror_GetSourceChannelLinStaticFilterInd(sourceChannelFilterIdx)) == MIRROR_E_MIRROR_SOURCENETWORK_FILTER_TYPE_ID_FILTERTYPEOFSOURCECHANNELLINSTATICFILTER)
        {
          if((id & (uint8)Mirror_GetFilterValueHighOrMaskOfSourceChannelLinStaticFilter(Mirror_GetSourceChannelLinStaticFilterInd(sourceChannelFilterIdx))) == ((uint8)Mirror_GetFilterValueLowOrIdOfSourceChannelLinStaticFilter(Mirror_GetSourceChannelLinStaticFilterInd(sourceChannelFilterIdx))))
          {
            filterMatched = TRUE;
          }
        }
        else
#endif
        {
          if((id >= Mirror_GetFilterValueLowOrIdOfSourceChannelLinStaticFilter(Mirror_GetSourceChannelLinStaticFilterInd(sourceChannelFilterIdx))) && (id <= Mirror_GetFilterValueHighOrMaskOfSourceChannelLinStaticFilter(Mirror_GetSourceChannelLinStaticFilterInd(sourceChannelFilterIdx))))
          {
            filterMatched = TRUE;
          }
        }

        if(filterMatched == TRUE)
        {
          break;
        }
      }
    }
  }

  return filterMatched;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_SourceChannelLin_ProcessStaticFilter() */
#endif /* ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTER == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON))
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_ProcessDynamicFilter()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_SourceChannelLin_ProcessDynamicFilter(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 id)
{
  Mirror_SourceChannelLinDynamicFilterIndIterType sourceChannelFilterIdx;
  boolean filterMatched = FALSE;

  /* #10 If the given source channel supports dynamic filter: */
  if(Mirror_IsSourceChannelLinDynamicFilterIndUsedOfSourceChannelLin(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    /* #20 Go through all dynamic filter (Id and Range) and check if one of the filter matches the given Id. If a filter matches, return TRUE. */
    for(sourceChannelFilterIdx = Mirror_GetSourceChannelLinDynamicFilterIndStartIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelFilterIdx < Mirror_GetSourceChannelLinDynamicFilterIndEndIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelFilterIdx++)
    {
      Mirror_SourceChannelLinDynamicFilterType* dynamicLinFilter = &Mirror_GetSourceChannelLinDynamicFilter(Mirror_GetSourceChannelLinDynamicFilterInd(sourceChannelFilterIdx)); 

      if(dynamicLinFilter->IsActive == TRUE)
      {
        if(dynamicLinFilter->IsIdMaskFilter == TRUE)
        {
          if((id & dynamicLinFilter->FilterValueHighOrMask) == dynamicLinFilter->FilterValueLowOrId)
          {
            filterMatched = TRUE;
          }
        }
        else
        {
          if((id >= dynamicLinFilter->FilterValueLowOrId) && (id <= dynamicLinFilter->FilterValueHighOrMask))
          {
            filterMatched = TRUE;
          }
        }

        if(filterMatched == TRUE)
        {
          break;
        }
      }
    }
  }

  return filterMatched;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_SourceChannelLin_ProcessDynamicFilter() */
#endif /* ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON)) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_ProcessFilter()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_SourceChannelLin_ProcessFilter(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 id)
{
  boolean filterMatched;

#if ((MIRROR_SOURCECHANNELLINSTATICFILTER == STD_OFF) && (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_OFF))
  filterMatched = FALSE;
#endif

#if (MIRROR_SOURCECHANNELLINSTATICFILTER == STD_ON)
  /* #10 Trigger the check if the given Id matches a static filter. */
  filterMatched = Mirror_SourceChannelLin_ProcessStaticFilter(sourceChannelIdx, id);
#endif

#if ((MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTER == STD_ON))
  /* #20 If no static filter is configured or no static filter matches the given Id: */
  if(filterMatched == FALSE)
#endif
#if (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON)
  {
    /* #30 Trigger the check if the given Id matches a dynamic filter. */
    filterMatched = Mirror_SourceChannelLin_ProcessDynamicFilter(sourceChannelIdx, id);
  }
#endif

  return filterMatched;
}/* Mirror_SourceChannelLin_ProcessFilter() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON))
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_GetCanId()
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
MIRROR_LOCAL_INLINE FUNC(uint32, MIRROR_CODE) Mirror_SourceChannelLin_GetCanId(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 id)
{
  uint32 canId;

#if (MIRROR_SOURCECHANNELLINIDTOCANIDMAPPING == STD_ON)
  canId = 0u;
#endif

#if (MIRROR_SOURCECHANNELLINIDTOCANIDMAPPING == STD_ON)
#if (MIRROR_SOURCECHANNELLINIDTOCANIDMAPPINGINDUSEDOFSOURCECHANNELLIN == STD_ON)
  /* #10 If the given source channel supports LIN to CAN Id mapping; */
  if(Mirror_IsSourceChannelLinIdToCanIdMappingIndUsedOfSourceChannelLin(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
#endif
  {
    Mirror_SourceChannelLinIdToCanIdMappingIterType linIdToCanIdMappingIdx;

    /* #20 Search for a LIN to CAN Id mapping that matches the given Id and return the associated CAN Id. */
    for(linIdToCanIdMappingIdx = Mirror_GetSourceChannelLinIdToCanIdMappingIndStartIdxOfSourceChannelLin(sourceChannelIdx); linIdToCanIdMappingIdx < Mirror_GetSourceChannelLinIdToCanIdMappingIndEndIdxOfSourceChannelLin(sourceChannelIdx); linIdToCanIdMappingIdx++)
    {
      if ((uint8)Mirror_GetLinIdOfSourceChannelLinIdToCanIdMapping(Mirror_GetSourceChannelLinIdToCanIdMappingInd(linIdToCanIdMappingIdx)) == id)
      {
        canId = Mirror_GetCanIdOfSourceChannelLinIdToCanIdMapping(Mirror_GetSourceChannelLinIdToCanIdMappingInd(linIdToCanIdMappingIdx));

        break;
      }
    }
  }
#endif

  /* #30 If no LIN to CAN Id mapping is configured or no mapping matched the given Id, return the Id added the configured LIN to CAN base Id. */
#if (MIRROR_SOURCECHANNELLINIDTOCANIDMAPPING == STD_ON)
  if(canId == 0u)
#endif
  {
    canId = (uint32)id + (uint32)Mirror_GetLinToCanRangeBaseIdOfSourceChannelLin(sourceChannelIdx);
  }

  /* #40 If the calculated CAN id is of type extended CAN Id, add the extended Id flag. */
  if (canId > MIRROR_SOURCECHANNEL_LIN_CAN_STANDARD_ID_MAX)
  {
    canId = canId | MIRROR_SOURCECHANNEL_LIN_CANID_EXTENDED_IF_FLAG;
  }

  return canId;
} /* Mirror_SourceChannelLin_GetCanId() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) 
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_GetFrameState()
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
MIRROR_LOCAL_INLINE FUNC(Mirror_SourceChannelLinFrameStateType, MIRROR_CODE) Mirror_SourceChannelLin_GetFrameState(Lin_StatusType status)
{
  Mirror_SourceChannelLinFrameStateType mirrorLinFrameState = MIRROR_SOURCECHANNELLIN_FRAMESTATE_OK;

  /* #10 Transform the given LIN status to the Mirror LIN status: */
  switch(status)
  {
  /* #20 If the given status is 'LIN_TX_HEADER_ERROR', return 'MIRROR_SOURCECHANNELLIN_FRAMESTATE_HEADER_TRANSMISSION_ERROR'. */
  case LIN_TX_HEADER_ERROR:
    mirrorLinFrameState = MIRROR_SOURCECHANNELLIN_FRAMESTATE_HEADER_TRANSMISSION_ERROR;
    break;
  
  /* #30 If the given status is 'LIN_TX_ERROR', return 'MIRROR_SOURCECHANNELLIN_FRAMESTATE_TRANSMISSION_ERROR'. */
  case LIN_TX_ERROR:
    mirrorLinFrameState = MIRROR_SOURCECHANNELLIN_FRAMESTATE_TRANSMISSION_ERROR;
    break;
  
  /* #40 If the given status is 'LIN_RX_ERROR', return 'MIRROR_SOURCECHANNELLIN_FRAMESTATE_RECEPTION_ERROR'. */
  case LIN_RX_ERROR:
    mirrorLinFrameState = MIRROR_SOURCECHANNELLIN_FRAMESTATE_RECEPTION_ERROR;
    break;

  /* #50 If the given status is 'LIN_RX_NO_RESPONSE', return 'MIRROR_SOURCECHANNELLIN_FRAMESTATE_NO_RESPONSE_ERROR'. */
  case LIN_RX_NO_RESPONSE:
    mirrorLinFrameState = MIRROR_SOURCECHANNELLIN_FRAMESTATE_NO_RESPONSE_ERROR;
    break;
  
  default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
    break;
  }

  return mirrorLinFrameState;
} /* Mirror_SourceChannelLin_GetFrameState() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_ProcessFrame()
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
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_SourceChannelLin_ProcessFrame(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 id, const PduInfoType* pdu, Lin_StatusType status)
{
  Std_ReturnType retVal = E_NOT_OK;
  NetworkHandleType destChannelIndex;

  /* #10 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

  /* #20 Get the current destination channel. */
  destChannelIndex = Mirror_SourceChannelLin_GeneralCtx->CurrentDestChannelIndex;

  /* #30 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
  SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

  /* #40 If the given LIN frame status is supported: */
  if((status == LIN_TX_OK) || (status == LIN_RX_OK) ||
     (status == LIN_TX_HEADER_ERROR) || (status == LIN_TX_ERROR) ||
     (status == LIN_RX_ERROR) || (status == LIN_RX_NO_RESPONSE))
  {
    /* #50 Trigger the transformation of the given LIN frame status to the Mirror LIN frame status. */
    Mirror_SourceChannelLinFrameStateType mirrorLinFrameState = Mirror_SourceChannelLin_GetFrameState(status);

    /* #60 If the current destination channel is of the type 'MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL': */
#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
    if(Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
    {
      uint8 metaData = 0u;
      uint8 networkId = 0u;
      uint8 networkState = 0u;

      /* #70 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
      SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

      /* #80 Get the current state of the source channel. */
      (void)Mirror_SourceChannelLin_GetState(sourceChannelIdx, MIRROR_NT_ETHERNET, mirrorLinFrameState, &metaData, &networkId, &networkState);

      /* #90 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

      /* #100 Trigger the processing of the LIN frame for the current IP destination channel. */
      retVal = Mirror_DestChannelIp_ProcessLinFrame(id, (uint8)pdu->SduLength, (const uint8*)pdu->SduDataPtr, metaData, networkId, networkState);
    }
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

    /* #110 If the current destination channel is of the type 'MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL': */
#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
    if(Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
    {
      uint8 metaData = 0u;
      uint8 networkId = 0u;
      uint8 networkState = 0u;

      /* #120 Get the CAN Id for the transmission on the CAN destination channel. */
      uint32 canId = Mirror_SourceChannelLin_GetCanId(sourceChannelIdx, id);

      /* #130 If the frame state is ok (payload available): */
      if(mirrorLinFrameState == MIRROR_SOURCECHANNELLIN_FRAMESTATE_OK)
      {
        /* #140 Trigger the processing of the LIN frame for the current CAN destination channel. */
        retVal = Mirror_DestChannelCan_ProcessLinFrame(id, canId, (uint8)pdu->SduLength, (const uint8*)pdu->SduDataPtr, metaData, networkId, networkState);
      }
      /* Otherwise, only a status frame can be reported to the CAN destination channel: */
      else
      {
        /* #150 Get the current state of the source channel, including the frame state: */
        if(Mirror_SourceChannelLin_GetState(sourceChannelIdx, MIRROR_NT_CAN, mirrorLinFrameState, &metaData, &networkId, &networkState) == E_OK)
        {
          /* #160 Trigger the processing of the state for the current CAN destination channel. */
          retVal = Mirror_DestChannelCan_ProcessLinFrame(id, canId, 0u, NULL_PTR, metaData, networkId, networkState);
        }
        /* #170 Otherwise, there is no LIN frame or status to process, set retVal to E_OK to avoid DET reporting. */
        else
        {
          retVal = E_OK;
        }
      }
    }
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */
  }

# if (MIRROR_RUNTIME_ERROR_REPORT == STD_ON)
  if(retVal != E_OK)
  {
    (void)Det_ReportRuntimeError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_REPORT_LIN_FRAME, MIRROR_E_QUEUE_OVERRUN);
  }
#else
  MIRROR_DUMMY_STATEMENT(retVal); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
}/* Mirror_SourceChannelLin_ProcessFrame() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelLin_ProcessStatus()
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
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_SourceChannelLin_ProcessStatus(Mirror_SourceChannelLinIterType sourceChannelIdx)
{
  NetworkHandleType destChannelIndex;
  uint8 metaData = 0u;
  uint8 networkId = 0u;
  uint8 networkState = 0u;

  /* #10 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

  /* #20 Get the current destination channel: */
  destChannelIndex = Mirror_SourceChannelLin_GeneralCtx->CurrentDestChannelIndex;

  /* #30 Get the current state of the LIN source channel. */
  (void)Mirror_SourceChannelLin_GetState(sourceChannelIdx, MIRROR_NT_INVALID, MIRROR_SOURCECHANNELLIN_FRAMESTATE_UNUSED, &metaData, &networkId, &networkState);

  /* #40 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
  SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

  /* #50 If the current destination channel is of the type 'MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL': */
#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
  if (Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
  {
    /* #60 Trigger the processing of the source channel state for the current IP destination channel. */
    Mirror_DestChannelIp_ProcessLinStatus(metaData, networkId, networkState);
  }
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

  /* #70 If the current destination channel is of the type 'MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL': */
#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
  if (Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
  {
    /* #80 Trigger the processing of the source channel state for the current CAN destination channel. */
    Mirror_DestChannelCan_ProcessLinStatus(metaData, networkId, networkState);
  }
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */
} /* Mirror_SourceChannelLin_ProcessStatus() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelLin_GetBusState()
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
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_SourceChannelLin_GetBusState(Mirror_SourceChannelLinIterType sourceChannelIdx)
{
  Mirror_SourceChannelLinStateType* sourceChannelState = &Mirror_GetSourceChannelLinState(Mirror_GetSourceChannelLinStateIdxOfSourceChannelLin(sourceChannelIdx));

#if (MIRROR_SOURCE_CHANNEL_LIN_TRCV_ENABLED == STD_ON)
  /* #10 If a LIN transceiver is configured for the given source channel: */
  if (Mirror_IsTrcvUsedOfSourceChannelLin(sourceChannelIdx))
  {
    LinTrcv_TrcvModeType linIfTrcvModeType;

    /* #20 Get the transceiver state. */
    if (LinIf_GetTrcvMode(Mirror_GetComMChannelIdOfSourceChannelLin(sourceChannelIdx), &linIfTrcvModeType) == E_OK)
    {
      Mirror_SourceChannelLinBusStateType oldState = sourceChannelState->State;

      /* #30 If the transceiver state is normal, set the source channel state to online. */
      if (linIfTrcvModeType == LINTRCV_TRCV_MODE_NORMAL)
      {
        sourceChannelState->State = MIRROR_SOURCECHANNELLIN_STATE_ONLINE;
      }
      /* #40 Otherwise, set the source channel state to offline. */
      else
      {
        sourceChannelState->State = MIRROR_SOURCECHANNELLIN_STATE_OFFLINE;
      }

      /* #50 If the source channel state has changed, mark it as changed. */
      if (oldState != sourceChannelState->State)
      {
        sourceChannelState->HasStateChanged = TRUE;
      }
    }
  }
  /* #60 Otherwise, set source channel state to online. */
  else
#endif /* (MIRROR_SOURCE_CHANNEL_LIN_TRCV_ENABLED == STD_ON) */
  {
    if(sourceChannelState->State != MIRROR_SOURCECHANNELLIN_STATE_ONLINE)
    {
      sourceChannelState->State = MIRROR_SOURCECHANNELLIN_STATE_ONLINE;

      sourceChannelState->HasStateChanged = TRUE;
    }
  }
} /* Mirror_SourceChannelLin_GetBusState() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  GLOBAL FUNCTION
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTERSTATE == STD_ON))
/**********************************************************************************************************************
 * Mirror_SourceChannelLin_GetStaticFilterState()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelLin_GetStaticFilterState(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 filterId, boolean* isActive)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 If the given source channel supports static filter, return the current state of the filter assigned with the given filter Id. */
  if(Mirror_IsSourceChannelLinStaticFilterStateIndUsedOfSourceChannelLin(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    if(filterId < (Mirror_GetSourceChannelLinStaticFilterStateIndEndIdxOfSourceChannelLin(sourceChannelIdx) - Mirror_GetSourceChannelLinStaticFilterStateIndStartIdxOfSourceChannelLin(sourceChannelIdx)))
    {
      (*isActive) = (boolean)Mirror_IsSourceChannelLinStaticFilterState(Mirror_GetSourceChannelLinStaticFilterStateInd((Mirror_GetSourceChannelLinStaticFilterStateIndStartIdxOfSourceChannelLin(sourceChannelIdx) + filterId))); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

      retVal = E_OK;
    }
  }

  return retVal;
} /* Mirror_SourceChannelLin_GetStaticFilterState() */
#endif /* ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTERSTATE == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTERSTATE == STD_ON))
/**********************************************************************************************************************
 * Mirror_SourceChannelLin_SetStaticFilterState()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelLin_SetStaticFilterState(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 filterId, boolean isActive)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 If the given source channel supports static filter, set the given filter state for the filter assigned with the given filter Id. */
  if(Mirror_IsSourceChannelLinStaticFilterStateIndUsedOfSourceChannelLin(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    if(filterId < (Mirror_GetSourceChannelLinStaticFilterStateIndEndIdxOfSourceChannelLin(sourceChannelIdx) - Mirror_GetSourceChannelLinStaticFilterStateIndStartIdxOfSourceChannelLin(sourceChannelIdx)))
    {
      Mirror_SetSourceChannelLinStaticFilterState(Mirror_GetSourceChannelLinStaticFilterStateInd((Mirror_GetSourceChannelLinStaticFilterStateIndStartIdxOfSourceChannelLin(sourceChannelIdx) + filterId)), isActive);

      retVal = E_OK;
    }
  }

  return retVal;
} /* Mirror_SourceChannelLin_SetStaticFilterState() */
#endif /* ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTERSTATE == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON))
/**********************************************************************************************************************
 * Mirror_SourceChannelLin_RemoveFilter()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelLin_RemoveFilter(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 filterId)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 If the given source channel supports dynamic filter */
  if(Mirror_IsSourceChannelLinDynamicFilterIndUsedOfSourceChannelLin(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    Mirror_SourceChannelLinDynamicFilterIndIterType sourceChannelFilterIdx;

    /* #20 Remove the filter assigned with the given filter Id. */
    for(sourceChannelFilterIdx = Mirror_GetSourceChannelLinDynamicFilterIndStartIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelFilterIdx < Mirror_GetSourceChannelLinDynamicFilterIndEndIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelFilterIdx++)
    {
      Mirror_SourceChannelLinDynamicFilterType* dynamicLinFilter = &Mirror_GetSourceChannelLinDynamicFilter(Mirror_GetSourceChannelLinDynamicFilterInd(sourceChannelFilterIdx));

      if(dynamicLinFilter->FilterId == filterId)
      {
        dynamicLinFilter->IsActive = FALSE;

        retVal = E_OK;
      }
    }
  }

  return retVal;
} /* Mirror_SourceChannelLin_RemoveFilter() */
#endif /* ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON)) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 * Mirror_SourceChannelLin_Offline()
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
FUNC(void, MIRROR_CODE) Mirror_SourceChannelLin_Offline(Mirror_SizeOfSourceChannelLinType sourceChannelIdx)
{
  Mirror_SourceChannelLinStateType* sourceChannelState = &Mirror_GetSourceChannelLinState(Mirror_GetSourceChannelLinStateIdxOfSourceChannelLin(sourceChannelIdx));

  /* #10 If the given source channel is enabled: */
  if(sourceChannelState->IsEnabled == TRUE)
  {
#if (MIRROR_SOURCECHANNELLINSTATICFILTERSTATE == STD_ON) 
    Mirror_SourceChannelLinStaticFilterStateIndIterType sourceChannelStaticFilterIdx;
#endif

#if (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON) 
    Mirror_SourceChannelLinDynamicFilterIndIterType sourceChannelDynamicFilterIdx;
#endif

    /* #20 Disable the given source channel */
    sourceChannelState->IsEnabled = FALSE;

    /* #30 Trigger the deactivation of Bus Mirroring for the LIN channel assigned to the given source channel in LinIf. */
    (void)LinIf_EnableBusMirroring(Mirror_GetComMChannelIdOfSourceChannelLin(sourceChannelIdx), FALSE);

#if (MIRROR_SOURCECHANNELLINSTATICFILTER == STD_ON)
    /* #40 If the given source channel supports static filter: */
    if(Mirror_IsSourceChannelLinStaticFilterIndUsedOfSourceChannelLin(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    {
      /* #50 Deactivate all static filter (Id and Range). */
      for (sourceChannelStaticFilterIdx = Mirror_GetSourceChannelLinStaticFilterStateIndStartIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelStaticFilterIdx < Mirror_GetSourceChannelLinStaticFilterStateIndEndIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelStaticFilterIdx++)
      {
        Mirror_SetSourceChannelLinStaticFilterState(Mirror_GetSourceChannelLinStaticFilterStateInd(sourceChannelStaticFilterIdx), FALSE);
      }
    }
#endif

#if (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON)
    /* #60 If the given source channel supports dynamic filter */
    if(Mirror_IsSourceChannelLinDynamicFilterIndUsedOfSourceChannelLin(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    {
      /* #70 Remove all dynamic filter (Id and Range). */
      for (sourceChannelDynamicFilterIdx = Mirror_GetSourceChannelLinDynamicFilterIndStartIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelDynamicFilterIdx < Mirror_GetSourceChannelLinDynamicFilterIndEndIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelDynamicFilterIdx++)
      {
        Mirror_SourceChannelLinDynamicFilterType* dynamicLinFilter = &Mirror_GetSourceChannelLinDynamicFilter(Mirror_GetSourceChannelLinDynamicFilterInd(sourceChannelDynamicFilterIdx));

        dynamicLinFilter->IsActive = FALSE;
      }
    }
#endif
  }
} /* Mirror_SourceChannelLin_Offline() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_StartSourceNetwork()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelLin_StartSourceNetwork(NetworkHandleType network)
{
  Std_ReturnType retVal = E_NOT_OK;
  Mirror_SourceChannelLinStateType* sourceChannelState;

  /* #10 Enter MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();

  /* #20 Get the state of the given source channel */
  sourceChannelState = &Mirror_GetSourceChannelLinState(Mirror_GetSourceChannelLinStateIdxOfSourceChannelLin(Mirror_GetSourceChannelLinIdxOfSourceComMChannel(network)));

  /* #30 If the given source channel is already started: */
  if(sourceChannelState->IsEnabled == TRUE)
  {
    /* #40 Leave MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();
  }
  /* #50 Otherwise: */
  else
  {
    /* #60 Enabled the given source channel. */
    sourceChannelState->IsEnabled = TRUE;

    /* #70 Leave MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();

    /* #80 Trigger the activation of Bus Mirroring for the LIN channel assigned to the given source channel in LinIf */
    retVal = LinIf_EnableBusMirroring(network, TRUE);
  }

  return retVal;
} /* Mirror_SourceChannelLin_StartSourceNetwork() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_StopSourceNetwork()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelLin_StopSourceNetwork(NetworkHandleType network)
{
  Std_ReturnType retVal = E_NOT_OK;
  Mirror_SourceChannelLinStateType* sourceChannelState;

  /* #10 Enter MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();

  /* #20 Get the state of the given source channel */
  sourceChannelState = &Mirror_GetSourceChannelLinState(Mirror_GetSourceChannelLinStateIdxOfSourceChannelLin(Mirror_GetSourceChannelLinIdxOfSourceComMChannel(network)));
  
  /* #30 If the given source channel is not started: */
  if(sourceChannelState->IsEnabled == FALSE)
  {
    /* #40 Leave MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();
  }
  /* #50 Otherwise: */
  else
  {
    /* #60 Enabled the given source channel. */
    sourceChannelState->IsEnabled = FALSE;

    /* #70 Leave MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();

    /* #80 Trigger the deactivation of Bus Mirroring for the LIN channel assigned to the given source channel in LinIf. */
    retVal= LinIf_EnableBusMirroring(network, FALSE);
  }

  return retVal;
} /* Mirror_SourceChannelLin_StopSourceNetwork() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_Init()
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
FUNC(void, MIRROR_APPL_CODE)Mirror_SourceChannelLin_Init(Mirror_SourceChannelLinIterType sourceChannelIdx,
                                                         Mirror_GeneralContextType* mirrorCtx)
{
#if (MIRROR_SOURCECHANNELLINSTATICFILTERSTATE == STD_ON) 
  Mirror_SourceChannelLinStaticFilterStateIndIterType sourceChannelStaticFilterStateIdx;
#endif

#if (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON) 
  Mirror_SourceChannelLinDynamicFilterIndIterType sourceChannelDynamicFilterIdx;
#endif

  /* #10 Initialize the general configuration for the given source channel. */
  Mirror_SourceChannelLinStateType* sourceChannelState = &Mirror_GetSourceChannelLinState(Mirror_GetSourceChannelLinStateIdxOfSourceChannelLin(sourceChannelIdx));

  Mirror_SourceChannelLin_GeneralCtx = mirrorCtx;

  sourceChannelState->IsEnabled = FALSE;
  sourceChannelState->HasStateChanged = FALSE;
  sourceChannelState->State = MIRROR_SOURCECHANNELLIN_STATE_OFFLINE;

#if (MIRROR_SOURCECHANNELLINSTATICFILTER == STD_ON)
  /* #20 If the given source channel supports static filter: */
  if(Mirror_IsSourceChannelLinStaticFilterStateIndUsedOfSourceChannelLin(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    /* #30 Initialize the state of all static filter to deactivated. */
    for (sourceChannelStaticFilterStateIdx = Mirror_GetSourceChannelLinStaticFilterStateIndStartIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelStaticFilterStateIdx < Mirror_GetSourceChannelLinStaticFilterStateIndEndIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelStaticFilterStateIdx++)
    {
      Mirror_SetSourceChannelLinStaticFilterState(Mirror_GetSourceChannelLinStaticFilterStateInd(sourceChannelStaticFilterStateIdx), FALSE);
    }
  }
#endif

#if (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON)
  /* #40 If the given source channel supports dynamic filter: */
  if(Mirror_IsSourceChannelLinDynamicFilterIndUsedOfSourceChannelLin(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    /* #50 Deactivate all dynamic filter. */
    for (sourceChannelDynamicFilterIdx = Mirror_GetSourceChannelLinDynamicFilterIndStartIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelDynamicFilterIdx < Mirror_GetSourceChannelLinDynamicFilterIndEndIdxOfSourceChannelLin(sourceChannelIdx); sourceChannelDynamicFilterIdx++)
    {
      Mirror_SourceChannelLinDynamicFilterType* dynamicLinFilter = &Mirror_GetSourceChannelLinDynamicFilter(Mirror_GetSourceChannelLinDynamicFilterInd(sourceChannelDynamicFilterIdx));

      dynamicLinFilter->IsActive = FALSE;
    }
  }
#endif
} /* Mirror_SourceChannelLin_Init() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_MainFunction()
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
FUNC(void, MIRROR_APPL_CODE)Mirror_SourceChannelLin_MainFunction(Mirror_SourceChannelLinIterType sourceChannelIdx)
{
#if (MIRROR_TRCVUSEDOFSOURCECHANNELLIN == STD_ON)
  Mirror_SourceChannelLinStateType* sourceChannelState = &Mirror_GetSourceChannelLinState(Mirror_GetSourceChannelLinStateIdxOfSourceChannelLin(sourceChannelIdx));

  /* #10 If the given source channel is started: */
  if(sourceChannelState->IsEnabled == TRUE)
  {
     /* #20 If the state of the LIN channel that is assigned to the given source channel has changed: */
    if (sourceChannelState->HasStateChanged == TRUE)
    {
      /* #30 Trigger the reporting of the channel state to the current destination channel. */
      Mirror_SourceChannelLin_ProcessStatus(sourceChannelIdx);
    }

    /* #40 Trigger the request for the state of the LIN channel that is assigned to the given source channel. */
    Mirror_SourceChannelLin_GetBusState(sourceChannelIdx);
  }
#else
  MIRROR_DUMMY_STATEMENT(sourceChannelIdx);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif /* (MIRROR_ISTRCVUSEDOFSOURCECHANNELLIN == STD_ON) */
} /* Mirror_SourceChannelLin_MainFunction() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelLin_InitMemory()
*********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(void, MIRROR_CODE) Mirror_SourceChannelLin_InitMemory(void)
{
  /* #10 Initialize the global Mirror module context. */
  Mirror_SourceChannelLin_GeneralCtx = NULL_PTR;
} /* Mirror_SourceChannelLin_InitMemory() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_AddLinRangeFilter()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_AddLinRangeFilter(NetworkHandleType network, uint8* filterId,
                                                           uint32 lowerId, uint32 upperId)
{
 /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if((Mirror_SourceChannelLin_GeneralCtx == NULL_PTR) ||
     (Mirror_SourceChannelLin_GeneralCtx->ModuleInitialized == (uint8)MIRROR_UNINIT))
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
  /* #30 Check if the given filter Id buffer is valid. */
  else if(filterId == NULL_PTR)
  {
    errorId = MIRROR_E_PARAM_POINTER;
  }
#endif
  /* #40 If the initial checks are passed or not required: */
  else
  {
#if (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON)
    /* ----- Implementation ----------------------------------------------- */

    /* #50 Trigger the addition of the new dynamic range filter. */
    retVal = Mirror_SourceChannelLin_AddDynamicFilter(network, filterId, lowerId, upperId, FALSE);
#else
    MIRROR_DUMMY_STATEMENT(network);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
    MIRROR_DUMMY_STATEMENT(filterId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
    MIRROR_DUMMY_STATEMENT(lowerId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
    MIRROR_DUMMY_STATEMENT(upperId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_ADD_LIN_RANGE_FILTER, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
} /* Mirror_AddLinRangeFilter() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_AddLinMaskFilter()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_AddLinMaskFilter(NetworkHandleType network, uint8* filterId,
                                                          uint32 id, uint32 mask)
{
 /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if((Mirror_SourceChannelLin_GeneralCtx == NULL_PTR) || 
     (Mirror_SourceChannelLin_GeneralCtx->ModuleInitialized == (uint8)MIRROR_UNINIT))
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
  /* #30 Check if the given filter Id buffer is valid. */
  else if(filterId == NULL_PTR)
  {
    errorId = MIRROR_E_PARAM_POINTER;
  }
#endif
  /* #40 If the initial checks are passed or not required: */
  else
  {
#if (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON)
    /* ----- Implementation ----------------------------------------------- */
    /* #50 Trigger the addition of the new dynamic mask filter. */
    retVal = Mirror_SourceChannelLin_AddDynamicFilter(network, filterId, id, mask, TRUE);
#else
    MIRROR_DUMMY_STATEMENT(network);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
    MIRROR_DUMMY_STATEMENT(filterId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
    MIRROR_DUMMY_STATEMENT(id);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
    MIRROR_DUMMY_STATEMENT(mask);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_ADD_LIN_MASK_FILTER, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
} /* Mirror_AddLinMaskFilter() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_ReportLinFrame()
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
 */
FUNC(void, MIRROR_CODE) Mirror_ReportLinFrame(NetworkHandleType network, Lin_FramePidType pid, const PduInfoType* pdu, Lin_StatusType status)
{
 /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if((Mirror_SourceChannelLin_GeneralCtx == NULL_PTR) ||
     (Mirror_SourceChannelLin_GeneralCtx->ModuleInitialized == (uint8)MIRROR_UNINIT))
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the controllerId is valid. */
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
    /* #40 Enter MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
    SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();

    /* #50 If the Mirror module and the given source channel are active: */
    if((Mirror_SourceChannelLin_GeneralCtx->GlobalMode == MIRROR_ACTIVE) && (Mirror_GetSourceChannelLinState(Mirror_GetSourceChannelLinIdxOfSourceComMChannel(network)).IsEnabled == TRUE))
    {
      /*#60 Extract the protected ID from the given Id. */
      uint8 localId = pid & MIRROR_SOURCECHANNEL_LIN_PID_MASK;

      /* #70 Trigger the matching of the given CAN Id against all active filter. */
      boolean filterMatched = Mirror_SourceChannelLin_ProcessFilter(Mirror_GetSourceChannelLinIdxOfSourceComMChannel(network), localId);

      /* #80 Leave MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();

      /* #90 If the given LIN Id matches at least one filter, process the given frame. */
      if(filterMatched == TRUE)
      {
        Mirror_SourceChannelLin_ProcessFrame(Mirror_GetSourceChannelLinIdxOfSourceComMChannel(network), localId, pdu, status);
      }
    }
    /* #100 Otherwise, leave MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
    else
    {
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != MIRROR_E_NO_ERROR)
  {
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_REPORT_LIN_FRAME, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_ReportLinFrame() */
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  END OF FILE: Mirror_SourceChannelLin.c
 *********************************************************************************************************************/
