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
/**     \file     Mirror_SourceChannelCan.c
 *      \brief    Mirror CAN source channel source file
 *
 *      \details  Implementation of Mirror CAN source channel.
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
#define MIRROR_SOURCECHANNELCAN_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_SourceChannelCan.h"
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

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
# include "CanIf.h"
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define MIRROR_SOURCECHANNEL_CAN_FILTER_ACTIVE               (1u)

#define MIRROR_SOURCECHANNEL_CAN_NETWORKSTATE_AVAILABLE      (0x80u)
#define MIRROR_SOURCECHANNEL_CAN_NETWORKSTATE_NOT_AVAILABLE  (0x00u)
#define MIRROR_SOURCECHANNEL_CAN_FRAMEID_AVAILABLE           (0x40u)
#define MIRROR_SOURCECHANNEL_CAN_FRAMEID_NOT_AVAILABLE       (0x00u)
#define MIRROR_SOURCECHANNEL_CAN_PAYLOAD_AVAILABLE           (0x20u)
#define MIRROR_SOURCECHANNEL_CAN_PAYLOAD_NOT_AVAILABLE       (0x00u)
#define MIRROR_SOURCECHANNEL_CAN_RESEVED                     (0x00u)

#define MIRROR_SOURCECHANNEL_CAN_BUS_ONLINE                  (0x40u)
#define MIRROR_SOURCECHANNEL_CAN_ERROR_PASSIVE               (0x20u)
#define MIRROR_SOURCECHANNEL_CAN_BUSS_OFF                    (0x10u)

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define MIRROR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/*! Global state of the Mirror module. */
MIRROR_LOCAL VAR(Mirror_GeneralContextType*, MIRROR_VAR_ZERO_INIT) Mirror_SourceChannelCan_GeneralCtx = NULL_PTR;   /* PRQA S 3218 */ /* MD_Mirror_3218_FileScopeStatic */

#define MIRROR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelCan_GetState()
*********************************************************************************************************************/
/*! \brief      Returns the current state of a CAN source channel
*  \details     -
*  \param[in]   sourceChannelIdx  Internal index of the CAN source channel.
*  \param[in]   destNetworkType   Type of the destination network
*  \param[out]  metaData          Meta data of the network
*  \param[out]  networkId         Id of the network
*  \param[out]  networkState      State of the network
*  \return      E_OK:             State is valid.
*  \return      E_NOT_OK:         State is invalid.
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   FALSE
*  \synchronous TRUE
*  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
*********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE)Mirror_SourceChannelCan_GetState(Mirror_SourceChannelCanIterType sourceChannelIdx,
                                                                                      Mirror_NetworkType destNetworkType,
                                                                                      uint8* metaData, uint8* networkId,
                                                                                      uint8* networkState);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON))
/**********************************************************************************************************************
 *  Mirror_SourceChannelCan_AddDynamicFilter()
 *********************************************************************************************************************/
/*! \brief       Creates a CAN dynamic filter.
 *  \details     -
 *  \param[in]   network           ComM channel that corresponds to the CAN bus to which the filter shall be attached.
 *  \param[out]  filterId          Id of the newly created filter.
 *  \param[in]   valueLowerOrId    Lower CAN ID of the range or Id.
 *  \param[in]   valueUpperOrMask  Upper CAN ID of the range or Mask.
 *  \param[in]   isIdMaskFilter    Flag that indicates if a Range or Id/Mask filter shall be created.
 *  \return      E_OK: New filter created.
 *  \return      E_NOT_OK: Creation of filter failed because of invalid parameters or because no filter on the given
 *                         network was free.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE for different networks.
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON and 
 *               MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelCan_AddDynamicFilter(NetworkHandleType network, uint8* filterId,
                                                             uint32 valueLowerOrId, uint32 valueUpperOrMask, boolean isIdMaskFilter);
#endif /* ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON))
/**********************************************************************************************************************
 *  Mirror_SourceChannelCan_ProcessStaticFilter()
 *********************************************************************************************************************/
/*! \brief       Function searches for matching static filter.
 *  \details     Only active filters will be evaluated.
 *  \param[in]   sourceChannelIdx  Index of the source channel
 *  \param[in]   canId       ID of the CAN frame
 *  \return      TRUE if filter matched, FALSE if not
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON and
 *               MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_SourceChannelCan_ProcessStaticFilter(Mirror_SizeOfSourceChannelCanType sourceChannelIdx, Can_IdType canId);
#endif /* ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON))
/**********************************************************************************************************************
 *  Mirror_SourceChannelCan_ProcessDynamicFilter()
 *********************************************************************************************************************/
/*! \brief       Function searches for matching dynamic filter.
 *  \details     Only active filters will be evaluated.
 *  \param[in]   sourceChannelIdx  Index of the source channel
 *  \param[in]   canId       ID of the CAN frame
 *  \return      TRUE if filter matched, FALSE if not
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON and
 *               MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_SourceChannelCan_ProcessDynamicFilter(Mirror_SizeOfSourceChannelCanType sourceChannelIdx, Can_IdType canId);
#endif /* ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON)) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelCan_ProcessFilter()
 *********************************************************************************************************************/
/*! \brief       Function searches for matching filter.
 *  \details     Only active filters will be evaluated.
 *  \param[in]   sourceChannelIdx  Index of the source channel
 *  \param[in]   canId       ID of the CAN frame
 *  \return      TRUE if filter matched, FALSE if not
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_SourceChannelCan_ProcessFilter(Mirror_SizeOfSourceChannelCanType sourceChannelIdx, Can_IdType canId);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelCan_ProcessFrame()
 *********************************************************************************************************************/
/*! \brief       Handles the destination bus specific actions to process the incoming frame.
 *  \details     Function is only called for CAN frames that passed the filter.
 *  \param[in]   controllerId   ID of the CAN controller that received or transmitted the frame.
 *  \param[in]   canId        CAN ID of the CAn frame.
 *  \param[in]   length       Length of the CAn frame.
 *  \param[in]   payload      Content of the CAN frame.
 *  \pre         Module is initialized.
 *  \context     ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_SourceChannelCan_ProcessFrame(uint8 controllerId,
                                                                                           Can_IdType canId,
                                                                                           uint8 length,
                                                                                           const uint8* payload);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelCan_ProcessStatus()
*********************************************************************************************************************/
/*! \brief      Handles a new state of the bus.
*  \details     -
*  \param[in]   sourceChannelIdx  Internal index of the CAN source channel.
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   FALSE
*  \synchronous TRUE
*  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
*********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_SourceChannelCan_ProcessStatus(Mirror_SourceChannelCanIterType sourceChannelIdx);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelCan_GetBusState()
*********************************************************************************************************************/
/*! \brief      Gets the state of a CAN bus.
*  \details     -
*  \param[in]   sourceChannelIdx  Internal index of the CAN source channel.
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   FALSE
*  \synchronous TRUE
*  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
*********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_SourceChannelCan_GetBusState(Mirror_SourceChannelCanIterType sourceChannelIdx);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
* Mirror_SourceChannelCan_GetState()
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
 */
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE)Mirror_SourceChannelCan_GetState(Mirror_SourceChannelCanIterType sourceChannelIdx,
  Mirror_NetworkType destNetworkType,
  uint8* metaData, uint8* networkId,
  uint8* networkState)
{
  Std_ReturnType retVal = E_NOT_OK;
  Mirror_SourceChannelCanStateType* sourceChannelState = &Mirror_GetSourceChannelCanState(Mirror_GetSourceChannelCanStateIdxOfSourceChannelCan(sourceChannelIdx));

  /* #10 If the given source channel is enabled: */
  if (sourceChannelState->IsEnabled == TRUE)
  {
    /* #20 Return network type and Mirror network Id. */
    (*metaData) = (uint8)MIRROR_NT_CAN;

    (*networkState) = 0u;

    (*networkId) = (uint8)Mirror_GetNetworkIdOfSourceChannelCan(sourceChannelIdx);

    /* #30 If the state of the CAN bus assigned to the source channel has changed: */
    if (sourceChannelState->HasStateChanged == TRUE)
    {
      /* #40 Return the network state and mark it as available. */
      (*metaData) |= MIRROR_SOURCECHANNEL_CAN_NETWORKSTATE_AVAILABLE;

      if (sourceChannelState->State == MIRROR_SOURCECHANNELCAN_STATE_ONLINE)
      {
        (*networkState) = MIRROR_SOURCECHANNEL_CAN_BUS_ONLINE;
      }

      if (sourceChannelState->State == MIRROR_SOURCECHANNELCAN_STATE_ERRORPASSIVE)
      {
        (*networkState) = MIRROR_SOURCECHANNEL_CAN_ERROR_PASSIVE;
      }

      if (sourceChannelState->State == MIRROR_SOURCECHANNELCAN_STATE_ERRORBUSOFF)
      {
        (*networkState) = MIRROR_SOURCECHANNEL_CAN_BUSS_OFF;
      }

      (*networkState) = (*networkState) | (0x0Fu & (sourceChannelState->TxErrorCounter / 8u));

      sourceChannelState->HasStateChanged = FALSE;

      retVal = E_OK;
    }

    /* #50 If the source channel state information shall be used for a destination network (IP, FlexRay, CDD) that uses the AUTOSAR Protocol,
     *     return the frame Id and payload available flags */
    if ((destNetworkType == MIRROR_NT_FLEXRAY) || (destNetworkType == MIRROR_NT_ETHERNET) || (destNetworkType == MIRROR_NT_PROPRIETARY))
    {
      (*metaData) |= MIRROR_SOURCECHANNEL_CAN_FRAMEID_AVAILABLE | MIRROR_SOURCECHANNEL_CAN_PAYLOAD_AVAILABLE;

      retVal = E_OK;
    }
  }

  return retVal;
} /* Mirror_SourceChannelCan_GetState() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON))
/**********************************************************************************************************************
 *  Mirror_SourceChannelCan_AddDynamicFilter()
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
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelCan_AddDynamicFilter(NetworkHandleType network, uint8* filterId,
                                                             uint32 valueLowerOrId, uint32 valueUpperOrMask, boolean isIdMaskFilter)
{
  Std_ReturnType retVal = E_NOT_OK;
  Mirror_SizeOfSourceChannelCanType sourceChannelIdx = Mirror_GetSourceChannelCanIdxOfSourceComMChannel(network);

  /* #10 If the given source channel supports dynamic filter: */
  if(Mirror_IsSourceChannelCanDynamicFilterIndUsedOfSourceChannelCan(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    Mirror_SourceChannelCanDynamicFilterIndIterType sourceChannelFilterIdx;
    uint8 newFilterId = 0u;

    /* #20 Search for a free dynamic filter: */
    for(sourceChannelFilterIdx = Mirror_GetSourceChannelCanDynamicFilterIndStartIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelFilterIdx < Mirror_GetSourceChannelCanDynamicFilterIndEndIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelFilterIdx++)
    {
      Mirror_SourceChannelCanDynamicFilterType* dynamicCanFilter = &Mirror_GetSourceChannelCanDynamicFilter(Mirror_GetSourceChannelCanDynamicFilterInd(sourceChannelFilterIdx));

      if(dynamicCanFilter->IsActive == FALSE)
      {
        /* #30 Store the given filter parameter and activate the new filter. */
        uint32 valueLower = valueLowerOrId;
        uint32 valueUpper = valueUpperOrMask;

#if(MIRROR_CAN_MIXED_ID_ENABLED == FALSE)
        if ((valueLower & MIRROR_CAN_EXTENDED_ID_FD_FLAG_MASK) == MIRROR_CAN_EXTENDED_ID_FD_FLAG_MASK)
        {
          valueLower = (valueLower & MIRROR_CAN_STANDARD_ID_MAX_VALUE) + MIRROR_CAN_STANDARD_ID_FD_FLAG_VALUE;
        }

        if ((valueUpper & MIRROR_CAN_EXTENDED_ID_FD_FLAG_MASK) == MIRROR_CAN_EXTENDED_ID_FD_FLAG_MASK) 
        {
          valueUpper = (valueUpper & MIRROR_CAN_STANDARD_ID_MAX_VALUE) + MIRROR_CAN_STANDARD_ID_FD_FLAG_VALUE;
        }
#endif

        dynamicCanFilter->IsActive = TRUE;
        dynamicCanFilter->FilterId = newFilterId;
        dynamicCanFilter->IsIdMaskFilter = isIdMaskFilter;
        dynamicCanFilter->FilterValueLowOrId = valueLower;
        dynamicCanFilter->FilterValueHighOrMask = valueUpper;

        /* #40 Return the Id of the new filter. */
        (*filterId) = newFilterId;

        retVal = E_OK;

        break;
      }

      newFilterId++;
    }

    /* #50 If no free filter is available, return E_NOT_OK. */
  }

  return retVal;
} /* Mirror_SourceChannelCan_AddDynamicFilter() */
#endif /* ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON))
/**********************************************************************************************************************
 * Mirror_SourceChannelCan_ProcessStaticFilter()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_SourceChannelCan_ProcessStaticFilter(Mirror_SizeOfSourceChannelCanType sourceChannelIdx, Can_IdType canId)
{
  Mirror_SourceChannelCanStaticFilterStateIndIterType sourceChannelFilterIdx;
  boolean filterMatched = FALSE;

  /* #10 If the given source channel supports static filter: */
  if(Mirror_IsSourceChannelCanStaticFilterIndUsedOfSourceChannelCan(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    /* #20 Go through all active static filter (Id and Range) and check if one of the filter matches the given CAN Id. If a filter matches, return TRUE. */
    for(sourceChannelFilterIdx = Mirror_GetSourceChannelCanStaticFilterStateIndStartIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelFilterIdx < Mirror_GetSourceChannelCanStaticFilterStateIndEndIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelFilterIdx++)
    {
      if(Mirror_IsSourceChannelCanStaticFilterState(Mirror_GetSourceChannelCanStaticFilterStateInd(sourceChannelFilterIdx)))
      {
#if (MIRROR_EXISTS_E_MIRROR_SOURCENETWORK_FILTER_TYPE_ID_FILTERTYPEOFSOURCECHANNELCANSTATICFILTER == STD_ON)
        if(Mirror_GetFilterTypeOfSourceChannelCanStaticFilter(Mirror_GetSourceChannelCanStaticFilterInd(sourceChannelFilterIdx)) == MIRROR_E_MIRROR_SOURCENETWORK_FILTER_TYPE_ID_FILTERTYPEOFSOURCECHANNELCANSTATICFILTER)
        {
          if((canId & (uint32)Mirror_GetFilterValueHighOrMaskOfSourceChannelCanStaticFilter(Mirror_GetSourceChannelCanStaticFilterInd(sourceChannelFilterIdx))) == ((uint32)Mirror_GetFilterValueLowOrIdOfSourceChannelCanStaticFilter(Mirror_GetSourceChannelCanStaticFilterInd(sourceChannelFilterIdx))))
          {
            filterMatched = TRUE;
          }
        }
        else
#endif
        {
          if((canId >= Mirror_GetFilterValueLowOrIdOfSourceChannelCanStaticFilter(Mirror_GetSourceChannelCanStaticFilterInd(sourceChannelFilterIdx))) && (canId <= Mirror_GetFilterValueHighOrMaskOfSourceChannelCanStaticFilter(Mirror_GetSourceChannelCanStaticFilterInd(sourceChannelFilterIdx))))
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
} /* Mirror_SourceChannelCan_ProcessStaticFilter() */
#endif /* ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON))
/**********************************************************************************************************************
 * Mirror_SourceChannelCan_ProcessDynamicFilter()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_SourceChannelCan_ProcessDynamicFilter(Mirror_SizeOfSourceChannelCanType sourceChannelIdx, Can_IdType canId)
{
  Mirror_SourceChannelCanDynamicFilterIndIterType sourceChannelFilterIdx;
  boolean filterMatched = FALSE;

  /* #10 If the given source channel supports dynamic filter: */
  if(Mirror_IsSourceChannelCanDynamicFilterIndUsedOfSourceChannelCan(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    /* #20 Go through all dynamic filter (Id and Range) and check if one of the filter matches the given CAN Id. If a filter matches, return TRUE. */
    for(sourceChannelFilterIdx = Mirror_GetSourceChannelCanDynamicFilterIndStartIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelFilterIdx < Mirror_GetSourceChannelCanDynamicFilterIndEndIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelFilterIdx++)
    {
      Mirror_SourceChannelCanDynamicFilterType* dynamicCanFilter = &Mirror_GetSourceChannelCanDynamicFilter(Mirror_GetSourceChannelCanDynamicFilterInd(sourceChannelFilterIdx));

      if(dynamicCanFilter->IsActive == TRUE)
      {
        if(dynamicCanFilter->IsIdMaskFilter == TRUE)
        {
          if((canId & dynamicCanFilter->FilterValueHighOrMask) == dynamicCanFilter->FilterValueLowOrId)
          {
            filterMatched = TRUE;
          }
        }
        else
        {
          if((canId >= dynamicCanFilter->FilterValueLowOrId) && (canId <= dynamicCanFilter->FilterValueHighOrMask))
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
} /* Mirror_SourceChannelCan_ProcessDynamicFilter() */
#endif /* ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON)) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 * Mirror_SourceChannelCan_ProcessFilter()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_SourceChannelCan_ProcessFilter(Mirror_SizeOfSourceChannelCanType sourceChannelIdx, Can_IdType canId)
{
  boolean filterMatched;

#if ((MIRROR_SOURCECHANNELCANSTATICFILTER == STD_OFF) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_OFF))
  filterMatched = FALSE;
#endif

#if (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON)
  /* #10 Trigger the check if the given CAN Id matches a static filter. */
  filterMatched = Mirror_SourceChannelCan_ProcessStaticFilter(sourceChannelIdx, canId);
#endif

#if ((MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON))
  /* #20 If no static filter is configured or no static filter matches the given CAN Id: */
  if(filterMatched == FALSE)
#endif
#if (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON)
  {
    /* #30 Trigger the check if the given CAN id matches a dynamic filter. */
    filterMatched = Mirror_SourceChannelCan_ProcessDynamicFilter(sourceChannelIdx, canId);
  }
#endif

  return filterMatched;
} /* Mirror_SourceChannelCan_ProcessFilter() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 * Mirror_SourceChannelCan_ProcessFrame()
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
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_SourceChannelCan_ProcessFrame(uint8 controllerId,
                                                                                 Can_IdType canId,
                                                                                 uint8 length,
                                                                                 const uint8* payload)
{
  Std_ReturnType retVal = E_NOT_OK;
  NetworkHandleType destChannelIndex;

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_OFF)
  MIRROR_DUMMY_STATEMENT(controllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif

  /* #10 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

  /* #20 Get the current destination channel. */
  destChannelIndex = Mirror_SourceChannelCan_GeneralCtx->CurrentDestChannelIndex;

  /* #30 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
  SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

  /* #40 If the current destination channel is of the type 'MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL': */
#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
  if(Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
  {
    uint8 metaData = 0u;
    uint8 networkId = 0u;
    uint8 networkState = 0u;

    /* #50 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
    SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

    /* #60 Get the current state of the source channel. */
    (void)Mirror_SourceChannelCan_GetState(Mirror_GetSourceChannelCanIdxOfSourceChannelCanCanController(controllerId), MIRROR_NT_ETHERNET, &metaData, &networkId, &networkState);

    /* #70 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();
    
    /* #80 Trigger the processing of the CAN frame for the current IP destination channel. */
    retVal = Mirror_DestChannelIp_ProcessCanFrame((uint32)canId, length, payload, metaData, networkId, networkState);
  }
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

  /* #90 If the current destination channel is of the type 'MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL': */
#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
  if(Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
  {
    /* #100 Trigger the processing of the CAN frame for the current CAN destination channel. */
    retVal = Mirror_DestChannelCan_ProcessCanFrame(canId, length, payload);
  }
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

# if (MIRROR_RUNTIME_ERROR_REPORT == STD_ON)
  if(retVal != E_OK)
  {
    (void)Det_ReportRuntimeError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_REPORT_CAN_FRAME, MIRROR_E_QUEUE_OVERRUN);
  }
#else
  MIRROR_DUMMY_STATEMENT(retVal); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
} /* Mirror_SourceChannelCan_ProcessFrame() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelCan_ProcessStatus()
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
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_SourceChannelCan_ProcessStatus(Mirror_SourceChannelCanIterType sourceChannelIdx)
{
  NetworkHandleType destChannelIndex;
  uint8 metaData = 0u;
  uint8 networkId = 0u;
  uint8 networkState = 0u;

  /* #10 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

  /* #20 Get the current destination channel: */
  destChannelIndex = Mirror_SourceChannelCan_GeneralCtx->CurrentDestChannelIndex;

  /* #30 Get the current state of the CAN source channel. */
  (void)Mirror_SourceChannelCan_GetState(sourceChannelIdx, MIRROR_NT_INVALID, &metaData, &networkId, &networkState);

  /* #40 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
  SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

  /* #50 If the current destination channel is of the type 'MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL': */
#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
  if (Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_IP_CHANNELTYPEOFDESTCOMMCHANNEL)
  {
    /* #60 Trigger the processing of the source channel state for the current IP destination channel. */
    Mirror_DestChannelIp_ProcessCanStatus(metaData, networkId, networkState);
  }
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

  /* #70 If the current destination channel is of the type 'MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL': */
#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
  if (Mirror_GetChannelTypeOfDestComMChannel(destChannelIndex) == MIRROR_E_MIRROR_CHANNEL_CAN_CHANNELTYPEOFDESTCOMMCHANNEL)
  {
    /* #80 Trigger the processing of the source channel state for the current CAN destination channel. */
    Mirror_DestChannelCan_ProcessCanStatus(metaData, networkId, networkState);
  }
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

} /* Mirror_SourceChannelCan_ProcessStatus() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelCan_GetBusState()
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
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_SourceChannelCan_GetBusState(Mirror_SourceChannelCanIterType sourceChannelIdx)
{
  Mirror_SourceChannelCanStateType* sourceChannelState = &Mirror_GetSourceChannelCanState(Mirror_GetSourceChannelCanStateIdxOfSourceChannelCan(sourceChannelIdx));
  CanIf_ControllerModeType controllerMode;
  Std_ReturnType retVal;
  boolean isTrcvNormal = TRUE;

#if (MIRROR_CANTRCVIDOFSOURCECHANNELCANCANCONTROLLER == STD_ON)
  /* #10 If a CAN transceiver is configured for the given source channel, get the transceiver state. */
  if (Mirror_GetCanTrcvIdOfSourceChannelCanCanController(Mirror_GetCanControllerIdOfSourceChannelCan(sourceChannelIdx)) != MIRROR_NO_CANTRCVIDOFSOURCECHANNELCANCANCONTROLLER)
  {
    CanTrcv_TrcvModeType trcvMode;

    retVal = CanIf_GetTrcvMode(&trcvMode, Mirror_GetCanTrcvIdOfSourceChannelCanCanController(Mirror_GetCanControllerIdOfSourceChannelCan(sourceChannelIdx)));

    if ((retVal == E_OK) && (trcvMode != CANTRCV_TRCVMODE_NORMAL))
    {
      isTrcvNormal = FALSE;
    }
  }
#endif

  /* #20 Get the CanIf controller mode for the CanIf channel assigned to the given source channel. */
  retVal = CanIf_GetControllerMode(Mirror_GetCanControllerIdOfSourceChannelCan(sourceChannelIdx), &controllerMode);

  /* #30 If transceiver and CanIf controller mode are in normal operation state: */
  if ((retVal == E_OK) && (isTrcvNormal == TRUE) && (controllerMode == CANIF_CS_STARTED))
  {
    uint8 txErrorCounter;
    Can_ErrorStateType errorState;

    /* #40 Get the CanIf error tx counter and controller error state, save the information
     *      and mark the source channel state as changed. */
    retVal = CanIf_GetControllerTxErrorCounter(Mirror_GetCanControllerIdOfSourceChannelCan(sourceChannelIdx), &txErrorCounter);

    if ((retVal == E_OK) && (txErrorCounter != sourceChannelState->TxErrorCounter))
    {
      sourceChannelState->TxErrorCounter = txErrorCounter;

      sourceChannelState->HasStateChanged = TRUE;
    }

    retVal = CanIf_GetControllerErrorState(Mirror_GetCanControllerIdOfSourceChannelCan(sourceChannelIdx), &errorState);

    if (retVal == E_OK)
    {
      if (errorState == CAN_ERRORSTATE_PASSIVE)
      {
        if (sourceChannelState->State != MIRROR_SOURCECHANNELCAN_STATE_ERRORPASSIVE)
        {
          sourceChannelState->HasStateChanged = TRUE;
        }

        sourceChannelState->State = MIRROR_SOURCECHANNELCAN_STATE_ERRORPASSIVE;
      }
      else if (errorState == CAN_ERRORSTATE_BUSOFF)
      {
        if (sourceChannelState->State != MIRROR_SOURCECHANNELCAN_STATE_ERRORBUSOFF)
        {
          sourceChannelState->HasStateChanged = TRUE;
        }

        sourceChannelState->State = MIRROR_SOURCECHANNELCAN_STATE_ERRORBUSOFF;
      }
      else
      {
        if (sourceChannelState->State != MIRROR_SOURCECHANNELCAN_STATE_ONLINE)
        {
          sourceChannelState->HasStateChanged = TRUE;
        }

        sourceChannelState->State = MIRROR_SOURCECHANNELCAN_STATE_ONLINE;
      }
    }
  }
  /* #50 Otherwise, if CAN controller or transceiver are in error state,
   *     change the source channel state to offline and
   *     store the information and mark the source channel state as changed. */
  else
  {
    if (sourceChannelState->State != MIRROR_SOURCECHANNELCAN_STATE_OFFLINE)
    {
      sourceChannelState->HasStateChanged = TRUE;
    }

    sourceChannelState->State = MIRROR_SOURCECHANNELCAN_STATE_OFFLINE;
  }

  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_SourceChannelCan_GetBusState() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  GLOBAL FUNCTION
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTERSTATE == STD_ON))
/**********************************************************************************************************************
* Mirror_SourceChannelCan_GetStaticFilterState()
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelCan_GetStaticFilterState(Mirror_SizeOfSourceChannelCanType sourceChannelIdx, uint8 filterId, boolean* isActive)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 If the given source channel supports static filter, return the current state of the filter assigned with the given filter Id. */
  if(Mirror_IsSourceChannelCanStaticFilterStateIndUsedOfSourceChannelCan(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    if(filterId < (Mirror_GetSourceChannelCanStaticFilterStateIndEndIdxOfSourceChannelCan(sourceChannelIdx) - Mirror_GetSourceChannelCanStaticFilterStateIndStartIdxOfSourceChannelCan(sourceChannelIdx)))
    {
      (*isActive) = (boolean)Mirror_IsSourceChannelCanStaticFilterState(Mirror_GetSourceChannelCanStaticFilterStateInd((Mirror_GetSourceChannelCanStaticFilterStateIndStartIdxOfSourceChannelCan(sourceChannelIdx) + filterId))); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

      retVal = E_OK;
    }
  }

  return retVal;
} /* Mirror_SourceChannelCan_GetStaticFilterState() */
#endif /* ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTERSTATE == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTERSTATE == STD_ON))
/**********************************************************************************************************************
* Mirror_SourceChannelCan_SetStaticFilterState()
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelCan_SetStaticFilterState(Mirror_SizeOfSourceChannelCanType sourceChannelIdx, uint8 filterId, boolean isActive)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 If the given source channel supports static filter, set the given filter state for the filter assigned with the given filter Id. */
  if(Mirror_IsSourceChannelCanStaticFilterStateIndUsedOfSourceChannelCan(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    if(filterId < (Mirror_GetSourceChannelCanStaticFilterStateIndEndIdxOfSourceChannelCan(sourceChannelIdx) - Mirror_GetSourceChannelCanStaticFilterStateIndStartIdxOfSourceChannelCan(sourceChannelIdx)))
    {
      Mirror_SetSourceChannelCanStaticFilterState(Mirror_GetSourceChannelCanStaticFilterStateInd((Mirror_GetSourceChannelCanStaticFilterStateIndStartIdxOfSourceChannelCan(sourceChannelIdx) + filterId)), isActive);

      retVal = E_OK;
    }
  }

  return retVal;
} /* Mirror_SourceChannelCan_SetStaticFilterState() */
#endif /* ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTERSTATE == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON))
/**********************************************************************************************************************
* Mirror_SourceChannelCan_RemoveFilter()
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelCan_RemoveFilter(Mirror_SizeOfSourceChannelCanType sourceChannelIdx, uint8 filterId)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 If the given source channel supports dynamic filter */
  if(Mirror_IsSourceChannelCanDynamicFilterIndUsedOfSourceChannelCan(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    Mirror_SourceChannelCanDynamicFilterIndIterType sourceChannelFilterIdx;
    
    /* #20 Remove the filter assigned with the given filter Id. */
    for(sourceChannelFilterIdx = Mirror_GetSourceChannelCanDynamicFilterIndStartIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelFilterIdx < Mirror_GetSourceChannelCanDynamicFilterIndEndIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelFilterIdx++)
    {
      Mirror_SourceChannelCanDynamicFilterType* dynamicCanFilter = &Mirror_GetSourceChannelCanDynamicFilter(Mirror_GetSourceChannelCanDynamicFilterInd(sourceChannelFilterIdx));

      if(dynamicCanFilter->FilterId == filterId)
      {
        dynamicCanFilter->IsActive = FALSE;

        retVal = E_OK;
      }
    }
  }

  return retVal;
} /* Mirror_SourceChannelCan_RemoveFilter() */
#endif /* ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON)) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
* Mirror_SourceChannelCan_Offline()
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
FUNC(void, MIRROR_CODE) Mirror_SourceChannelCan_Offline(Mirror_SizeOfSourceChannelCanType sourceChannelIdx)
{
  Mirror_SourceChannelCanStateType* sourceChannelState = &Mirror_GetSourceChannelCanState(Mirror_GetSourceChannelCanStateIdxOfSourceChannelCan(sourceChannelIdx));

  /* #10 If the given source channel is enabled: */
  if(sourceChannelState->IsEnabled == TRUE)
  {
#if (MIRROR_SOURCECHANNELCANSTATICFILTERSTATE == STD_ON) 
    Mirror_SourceChannelCanStaticFilterStateIndIterType sourceChannelStaticFilterIdx;
#endif

#if (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON) 
    Mirror_SourceChannelCanDynamicFilterIndIterType sourceChannelDynamicFilterIdx;
#endif

    /* #20 Disable the given source channel */
    sourceChannelState->IsEnabled = FALSE;

    /* #30 Trigger the deactivation of Bus Mirroring for the CAN controller assigned to the given source channel in CanIf. */
    (void)CanIf_EnableBusMirroring(Mirror_GetCanControllerIdOfSourceChannelCan(sourceChannelIdx), FALSE);

#if (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON)
    /* #40 If the given source channel supports static filter: */
    if(Mirror_IsSourceChannelCanStaticFilterIndUsedOfSourceChannelCan(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    {
      /* #50 Deactivate all static filter (Id and Range). */
      for (sourceChannelStaticFilterIdx = Mirror_GetSourceChannelCanStaticFilterStateIndStartIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelStaticFilterIdx < Mirror_GetSourceChannelCanStaticFilterStateIndEndIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelStaticFilterIdx++)
      {
        Mirror_SetSourceChannelCanStaticFilterState(Mirror_GetSourceChannelCanStaticFilterStateInd(sourceChannelStaticFilterIdx), FALSE);
      }
    }
#endif

#if (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON)
    /* #60 If the given source channel supports dynamic filter */
    if(Mirror_IsSourceChannelCanDynamicFilterIndUsedOfSourceChannelCan(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    {
      /* #70 Remove all dynamic filter (Id and Range). */
      for (sourceChannelDynamicFilterIdx = Mirror_GetSourceChannelCanDynamicFilterIndStartIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelDynamicFilterIdx < Mirror_GetSourceChannelCanDynamicFilterIndEndIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelDynamicFilterIdx++)
      {
        Mirror_SourceChannelCanDynamicFilterType* dynamicCanFilter = &Mirror_GetSourceChannelCanDynamicFilter(Mirror_GetSourceChannelCanDynamicFilterInd(sourceChannelDynamicFilterIdx));

        dynamicCanFilter->IsActive = FALSE;
      }
    }
#endif
  }
} /* Mirror_SourceChannelCan_Offline() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
* Mirror_SourceChannelCan_StartSourceNetwork()
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
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelCan_StartSourceNetwork(Mirror_SizeOfSourceChannelCanType sourceChannelIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  Mirror_SourceChannelCanStateType* sourceChannelState;

  /* #10 Enter MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();

  /* #20 Get the state of the given source channel */
  sourceChannelState = &Mirror_GetSourceChannelCanState(Mirror_GetSourceChannelCanStateIdxOfSourceChannelCan(sourceChannelIdx));

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

    /* #80 Trigger the activation of Bus Mirroring for the CAN controller assigned to the given source channel in CanIf. */
    retVal = CanIf_EnableBusMirroring(Mirror_GetCanControllerIdOfSourceChannelCan(sourceChannelIdx), TRUE);
  }

  return retVal;
} /* Mirror_SourceChannelCan_StartSourceNetwork() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
* Mirror_SourceChannelCan_StopSourceNetwork()
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
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelCan_StopSourceNetwork(Mirror_SizeOfSourceChannelCanType sourceChannelIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  Mirror_SourceChannelCanStateType* sourceChannelState;

  /* #10 Enter MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();

  /* #20 Get the state of the given source channel */
  sourceChannelState = &Mirror_GetSourceChannelCanState(Mirror_GetSourceChannelCanStateIdxOfSourceChannelCan(sourceChannelIdx));
  
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

    /* #80 Trigger the deactivation of Bus Mirroring for the CAN controller assigned to the given source channel in CanIf. */
    retVal= CanIf_EnableBusMirroring(Mirror_GetCanControllerIdOfSourceChannelCan(sourceChannelIdx), FALSE);
  }

  return retVal;
} /* Mirror_SourceChannelCan_StopSourceNetwork() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
* Mirror_SourceChannelCan_Init()
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
 */
FUNC(void, MIRROR_CODE)Mirror_SourceChannelCan_Init(Mirror_SourceChannelCanIterType sourceChannelIdx,
                                                    Mirror_GeneralContextType* mirrorCtx)
{
#if (MIRROR_SOURCECHANNELCANSTATICFILTERSTATE == STD_ON) 
  Mirror_SourceChannelCanStaticFilterStateIndIterType sourceChannelStaticFilterIdx;
#endif

#if (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON) 
  Mirror_SourceChannelCanDynamicFilterIndIterType sourceChannelDynamicFilterIdx;
#endif

  /* #10 Initialize the general configuration for the given source channel. */
  Mirror_SourceChannelCanStateType* sourceChannelState = &Mirror_GetSourceChannelCanState(Mirror_GetSourceChannelCanStateIdxOfSourceChannelCan(sourceChannelIdx));

  Mirror_SourceChannelCan_GeneralCtx = mirrorCtx;

  sourceChannelState->IsEnabled = FALSE;
  sourceChannelState->HasStateChanged = FALSE;
  sourceChannelState->TxErrorCounter = 0u;
  sourceChannelState->State = MIRROR_SOURCECHANNELCAN_STATE_OFFLINE;

#if (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON)
  /* #20 If the given source channel supports static filter: */
  if(Mirror_IsSourceChannelCanStaticFilterStateIndUsedOfSourceChannelCan(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    /* #30 Initialize the state of all static filter to deactivated. */
    for (sourceChannelStaticFilterIdx = Mirror_GetSourceChannelCanStaticFilterStateIndStartIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelStaticFilterIdx < Mirror_GetSourceChannelCanStaticFilterStateIndEndIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelStaticFilterIdx++)
    {
      Mirror_SetSourceChannelCanStaticFilterState(Mirror_GetSourceChannelCanStaticFilterStateInd(sourceChannelStaticFilterIdx), FALSE);
    }
  }
#endif

#if (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON)
  /* #40 If the given source channel supports dynamic filter: */
  if(Mirror_IsSourceChannelCanDynamicFilterIndUsedOfSourceChannelCan(sourceChannelIdx)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    /* #50 Deactivate all dynamic filter. */
    for (sourceChannelDynamicFilterIdx = Mirror_GetSourceChannelCanDynamicFilterIndStartIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelDynamicFilterIdx < Mirror_GetSourceChannelCanDynamicFilterIndEndIdxOfSourceChannelCan(sourceChannelIdx); sourceChannelDynamicFilterIdx++)
    {
      Mirror_SourceChannelCanDynamicFilterType* dynamicCanFilter = &Mirror_GetSourceChannelCanDynamicFilter(Mirror_GetSourceChannelCanDynamicFilterInd(sourceChannelDynamicFilterIdx));

      dynamicCanFilter->IsActive = FALSE;
    }
  }
#endif
} /* Mirror_SourceChannelCan_Init() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
* Mirror_SourceChannelCan_MainFunction()
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, MIRROR_CODE)Mirror_SourceChannelCan_MainFunction(Mirror_SourceChannelCanIterType sourceChannelIdx)
{
  Mirror_SourceChannelCanStateType* sourceChannelState = &Mirror_GetSourceChannelCanState(Mirror_GetSourceChannelCanStateIdxOfSourceChannelCan(sourceChannelIdx));

  /* #10 If the given source channel is started: */
  if (sourceChannelState->IsEnabled == TRUE)
  {    
    /* #20 If the state of the CAN channel that is assigned to the given source channel has changed: */
    if (sourceChannelState->HasStateChanged == TRUE)
    {
      /* #30 Trigger the reporting of the channel state to the current destination channel. */
      Mirror_SourceChannelCan_ProcessStatus(sourceChannelIdx);
    }

    /* #40 Trigger the request for the state of the CAN channel that is assigned to the given source channel. */
    Mirror_SourceChannelCan_GetBusState(sourceChannelIdx);
  }
} /* Mirror_SourceChannelCan_MainFunction() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelCan_InitMemory()
*********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(void, MIRROR_CODE) Mirror_SourceChannelCan_InitMemory(void)
{
  /* #10 Initialize the global Mirror module context. */
  Mirror_SourceChannelCan_GeneralCtx = NULL_PTR;
} /* Mirror_SourceChannelCan_InitMemory() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_AddCanRangeFilter()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_AddCanRangeFilter(NetworkHandleType network, uint8* filterId,
                                                           uint32 lowerId, uint32 upperId)
{
 /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if((Mirror_SourceChannelCan_GeneralCtx == NULL_PTR) ||
     (Mirror_SourceChannelCan_GeneralCtx->ModuleInitialized == (uint8)MIRROR_UNINIT))
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
#if (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON)
    /* ----- Implementation ----------------------------------------------- */

    /* #50 Trigger the addition of the new dynamic range filter. */
    retVal = Mirror_SourceChannelCan_AddDynamicFilter(network, filterId, lowerId, upperId, FALSE);
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
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_ADD_CAN_RANGE_FILTER, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
} /* Mirror_AddCanRangeFilter() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_AddCanMaskFilter()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_AddCanMaskFilter(NetworkHandleType network, uint8* filterId,
                                                          uint32 id, uint32 mask)
{
 /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if((Mirror_SourceChannelCan_GeneralCtx == NULL_PTR) ||
     (Mirror_SourceChannelCan_GeneralCtx->ModuleInitialized == (uint8)MIRROR_UNINIT))
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
#if (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON)
    /* ----- Implementation ----------------------------------------------- */

    /* #50 Trigger the addition of the new dynamic mask filter. */
    retVal = Mirror_SourceChannelCan_AddDynamicFilter(network, filterId, id, mask, TRUE);
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
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_ADD_CAN_MASK_FILTER, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif 

  return retVal;
} /* Mirror_AddCanMaskFilter() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 * Mirror_ReportCanFrame()
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
 *
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_ReportCanFrame(uint8 controllerId, Can_IdType canId, uint8 length, const uint8* payload)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = MIRROR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if the Mirror module is initialized. */
  if((Mirror_SourceChannelCan_GeneralCtx == NULL_PTR) ||
     (Mirror_SourceChannelCan_GeneralCtx->ModuleInitialized == (uint8)MIRROR_UNINIT))
  {
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
    errorId = MIRROR_E_UNINIT;
#endif
  }
#if (MIRROR_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the controllerId is valid. */
  else if(controllerId >= Mirror_GetSizeOfSourceChannelCanCanController())
  {
    errorId = MIRROR_E_PARAM_CTRL;
  }
#if (MIRROR_INVALIDHNDOFSOURCECHANNELCANCANCONTROLLER == STD_ON)
  else if(Mirror_IsInvalidHndOfSourceChannelCanCanController(controllerId))
  {
    errorId = MIRROR_E_PARAM_CTRL;
  }
#endif
  /* #30 Check if the buffer of the given payload is valid. */
  else if(payload == NULL_PTR)
  {
    errorId = MIRROR_E_PARAM_POINTER;
  }
#endif
  /* #40 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #50 Enter MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
    SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();

    /* #60 If the Mirror module and the given source channel are active: */
    if((Mirror_SourceChannelCan_GeneralCtx->GlobalMode == MIRROR_ACTIVE) && (Mirror_GetSourceChannelCanState(Mirror_GetSourceChannelCanIdxOfSourceChannelCanCanController(controllerId)).IsEnabled == TRUE))
    {
      /* #70 Compare the given CAN Id against all active filter. */
      boolean filterMatched = Mirror_SourceChannelCan_ProcessFilter(Mirror_GetSourceChannelCanIdxOfSourceChannelCanCanController(controllerId), canId);

      /* #80 Leave MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL. */
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL();

      /* #90 If the given CAN Id matches at least one filter, process the given frame. */
      if(filterMatched == TRUE)
      {
        Mirror_SourceChannelCan_ProcessFrame(controllerId, canId, length, payload);
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
    (void)Det_ReportError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_REPORT_CAN_FRAME, errorId);
  }
#else
  MIRROR_DUMMY_STATEMENT(errorId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_ReportCanFrame() */
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  END OF FILE: Mirror_SourceChannelCan.c
 *********************************************************************************************************************/
