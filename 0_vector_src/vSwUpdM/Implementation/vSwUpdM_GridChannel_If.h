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
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vSwUpdM_GridChannel_If.h
 *        \brief  vSwUpdM_GridChannel unit interface header file
 *      \details  Interface provided by the vSwUpdM_GridChannel unit.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vSwUpdM.h.
 *********************************************************************************************************************/

#if !defined (VSWUPDM_GRIDCHANNEL_IF_H)
# define VSWUPDM_GRIDCHANNEL_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* GridChannel types header */
#include "vSwUpdM_GridChannel_Types.h"

/* Interface header of containing MultipleUnit */
#include "vSwUpdM_Grid_If.h"

/* Other MultipleUnits used by GridChannel_If (Prefer smallest set required, i.e. prefer _Types over _If) */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
struct vSwUpdM_GridChannel_VarChannelType_tag
{
  vSwUpdM_GridChannel_StateType State;
  vSwUpdM_GridSrvc_ServiceIdxType Service;
  vSwUpdM_NodeGroupIterType Destination;
  vSwUpdM_GridChannel_ResponseCountType ResponseCount;
  boolean AggregatedResultDirty;
};

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_Prepare
 *********************************************************************************************************************/
/*! \brief       Prepare transmission of a RPC request.
 *  \details     Set up channel for response aggregation.
 *  \param[in]   ChannelIndex  Channel to prepare.
 *  \param[in]   ServiceIndex  Service to transmit
 *  \param[in]   Destination   Group of receivers for the request.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Channel associated with Service must be idle.
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_Prepare(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeGroupIterType Destination);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_GetState
 *********************************************************************************************************************/
/*! \brief       Get State of GridChannel.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \return      State of Channel
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridChannel_StateType, VSWUPDM_CODE) vSwUpdM_GridChannel_GetState(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
  );

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_SetState
 *********************************************************************************************************************/
/*! \brief       Set State of GridChannel.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \param[in]   State            New state, which shall be set.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetState(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_GridChannel_StateType State
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_GetDestination
 *********************************************************************************************************************/
/*! \brief       Get Destination of Channel.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \return      Destination of Channel.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_NodeGroupIterType, VSWUPDM_CODE) vSwUpdM_GridChannel_GetDestination(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_SetDestination
 *********************************************************************************************************************/
/*! \brief       Set Destination of Channel.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \param[in]   Destination      Value, which shall be set.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetDestination( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_NodeGroupIterType Destination
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_GetService
 *********************************************************************************************************************/
/*! \brief       Get current service of Channel.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \return      Current service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridSrvc_ServiceIdxType, VSWUPDM_CODE) vSwUpdM_GridChannel_GetService( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_SetService
 *********************************************************************************************************************/
/*! \brief       Set current service of Channel.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \param[in]   Service          Value, which shall be set.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetService( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_GridSrvc_ServiceIdxType Service
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_GetAggregatedResultPtr
 *********************************************************************************************************************/
/*! \brief       Get pointer to Aggregated Result of Channel.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \return      Aggregated Result of Channel.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC( vSwUpdM_GridSrvc_ResponseClassBasePtrType, VSWUPDM_CODE) vSwUpdM_GridChannel_GetAggregatedResultPtr( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_SetAggregatedResult
 *********************************************************************************************************************/
/*! \brief       Set Aggregated Result of Channel.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \param[in]   Value            Value for Aggregated Result.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetAggregatedResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  Std_ReturnType Value
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_SetAggregatedResultToErrorCondition
 *********************************************************************************************************************/
/*! \brief       Set Aggregated Result of Channel to an error.
 *  \details     Depending on the ReponseClass of the Channel, the error condition can be different.
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \param[in]   Value            For Aggregated Result.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetAggregatedResultToErrorCondition( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  Std_ReturnType Value
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_InitAggregatedResultGood
 *********************************************************************************************************************/
/*! \brief       Init Aggregated Result of Channel.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_InitAggregatedResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_GetAggregatedResultDirty
 *********************************************************************************************************************/
/*! \brief       Get Aggregated Result Dirty flag.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \return      Aggregated Result Dirty flag.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_GridChannel_GetAggregatedResultDirty( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_GetAggregatedResultDirty
 *********************************************************************************************************************/
/*! \brief       Set Aggregated Result Dirty flag.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \param[in]   Value            to set to Dirty flag.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetAggregatedResultDirty( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  boolean Value
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_GetResponseCount
 *********************************************************************************************************************/
/*! \brief       Get ResponseCount of a Channel.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \return      ResponseCount
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(uint8, VSWUPDM_CODE) vSwUpdM_GridChannel_GetResponseCount( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_SetResponseCount
 *********************************************************************************************************************/
/*! \brief       Set ResponseCount of a Channel.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \param[in]   ResponseCount Value to set.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetResponseCount( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  uint8 ResponseCount
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_IncResponseCount
 *********************************************************************************************************************/
/*! \brief       Increase ResponseCount of a Channel.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_IncResponseCount( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_ClearAggregatedResult
 *********************************************************************************************************************/
/*! \brief       Clears all aggregated result information of a Channel.
 *  \details     Clears Aggregated Result, ResponseCount and Dirty-flag.
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_ClearAggregatedResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_StoreResponseResult
 *********************************************************************************************************************/
/*! \brief       Store response in provided response result buffers.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \param[in]   NodeIndex        Node index of requesting node.
 *  \param[in]   ServiceIdx       Service index.
 *  \param[in]   ServiceResult    Result, which needs to be stored.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_StoreResponseResult(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_NodeIterType NodeIndex,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIdx,
  uint8 ServiceResult);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_StoreResponseServiceState
 *********************************************************************************************************************/
/*! \brief       Store response in provided response result buffers.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \param[in]   NodeIndex        Node index of requesting node.
 *  \param[in]   ServiceIdx       Service index.
 *  \param[in]   ServiceState     State, which needs to be stored.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_StoreResponseServiceState(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_NodeIterType NodeIndex,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIdx,
  vSwUpdM_GridChannel_ServiceStateType ServiceState);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_LegacyIsIncrementOnLocalNodeRequired
 *********************************************************************************************************************/
/*! \brief       Helper function for aggregate results of legacy responses.
 *  \details     -
 *  \param[in]   ServiceIdx       Service index.
 *  \return      TRUE if legacy handling for responses is required
 *  \return      FALSE if legacy handling for responses is not required
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_GridChannel_LegacyIsIncrementOnLocalNodeRequired(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIdx);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_GetRequestBuffer
 *********************************************************************************************************************/
/*! \brief       Returns pointer so parameter assembly buffer for request.
 *  \details     -
 *  \param[in]   ChannelIndex     Index of grid channel.
 *  \param[out]  Parameter        Request buffer content.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_GetRequestBuffer( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_GridSrvc_ServiceClassBasePtrPtrType Parameter
);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_GRIDCHANNEL_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_GridChannel_If.h
 *********************************************************************************************************************/
