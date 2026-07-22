/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 Vector Informatik GmbH.                                                     All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!  \file   Mirror_Types.h
 *  \brief  Mirror Types header file
 *
 *  \details  Global types header of the Mirror component.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (MIRROR_TYPES_H)
# define MIRROR_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "ComStack_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! Bus Mirroring inactive state. */
# define MIRROR_INACTIVE                    (Mirror_ModeType) 0x00u

/*! Bus Mirroring active state. */
# define MIRROR_ACTIVE                      (Mirror_ModeType) 0x01u

/*! Version of the Bus Mirroring stream protocol. */
# define MIRROR_STATUS_PROTOCOL_VERSION     (0x01u)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Types of networks supported by Bus Mirroring. */
typedef enum eMirror_NetworkType
{
  MIRROR_NT_CAN = 0x01,
  MIRROR_NT_LIN = 0x02,
  MIRROR_NT_FLEXRAY = 0x03,
  MIRROR_NT_ETHERNET = 0x04,
  MIRROR_NT_PROPRIETARY = 0x05,
  MIRROR_NT_INVALID = 0x00
} Mirror_NetworkType;

/*! Types of FlexRay channels. */
typedef enum eMirror_FlexRayChannelType
{
  MIRROR_FR_CHANNEL_A = 0x01,
  MIRROR_FR_CHANNEL_B = 0x02,
  MIRROR_FR_CHANNEL_AB = 0x03
} Mirror_FlexRayChannelType;

/*! Enable/Disable the mirroring functionality. */
typedef uint8 Mirror_ModeType;

/*! State of a CAN source network. */
typedef enum eMirror_SourceChannelCanStateType
{
  MIRROR_SOURCECHANNELCAN_STATE_ONLINE = 0,
  MIRROR_SOURCECHANNELCAN_STATE_OFFLINE,
  MIRROR_SOURCECHANNELCAN_STATE_ERRORPASSIVE,
  MIRROR_SOURCECHANNELCAN_STATE_ERRORBUSOFF
} Mirror_SourceChannelCanBusStateType;

/*! State of a LIN source network. */
typedef enum eMirror_SourceChannelLinStateType
{
  MIRROR_SOURCECHANNELLIN_STATE_ONLINE = 0,
  MIRROR_SOURCECHANNELLIN_STATE_OFFLINE
} Mirror_SourceChannelLinBusStateType;

/*! State of a LIN frame. */
typedef enum eMirror_SourceChannelLinFrameStateType
{
  MIRROR_SOURCECHANNELLIN_FRAMESTATE_HEADER_TRANSMISSION_ERROR = 0,
  MIRROR_SOURCECHANNELLIN_FRAMESTATE_TRANSMISSION_ERROR,
  MIRROR_SOURCECHANNELLIN_FRAMESTATE_RECEPTION_ERROR,
  MIRROR_SOURCECHANNELLIN_FRAMESTATE_NO_RESPONSE_ERROR,
  MIRROR_SOURCECHANNELLIN_FRAMESTATE_OK,
  MIRROR_SOURCECHANNELLIN_FRAMESTATE_UNUSED
} Mirror_SourceChannelLinFrameStateType;

/*! State of a dynamic filter of a source network CAN. */
typedef struct sMirror_SourceChannelCanDynamicFilterType
{
  uint32 FilterValueLowOrId;
  uint32 FilterValueHighOrMask;
  uint8 FilterId;
  boolean IsActive;
  boolean IsIdMaskFilter;
} Mirror_SourceChannelCanDynamicFilterType;

/*! State of a source network CAN. */
typedef struct sMirror_SourceChannelCanStateType
{
  boolean IsEnabled;
  boolean HasStateChanged;
  uint8 TxErrorCounter;
  Mirror_SourceChannelCanBusStateType State;
} Mirror_SourceChannelCanStateType;

/*! State of a dynamic filter of a source network FlexRay. */
typedef struct sMirror_SourceChannelFlexRayDynamicFilterType
{
  uint16 lowerSlotId;
  uint16 upperSlotId;
  boolean IsActive;
  uint8 FilterId;
  uint8 lowerBaseCycle;
  uint8 upperBaseCycle;
  uint8 cycleRepetition;
  Mirror_FlexRayChannelType frChannel;
} Mirror_SourceChannelFlexRayDynamicFilterType;

/*! State of a source network FlexRay. */
typedef struct sMirror_SourceChannelFlexRayStateType
{
  boolean IsEnabled;
  boolean HasStateChanged;
  boolean IsOnline;
  boolean IsSynchronous;
  boolean IsNormalActive;
  boolean HasChannelAStateChanged;
  boolean IsSyntaxError_ChannelA;
  boolean IsContentError_ChannelA;
  boolean HasChannelBStateChanged;
  boolean IsBoundaryViolation_ChannelA;
  boolean IsSyntaxError_ChannelB;
  boolean IsContentError_ChannelB;
  boolean IsBoundaryViolation_ChannelB;
} Mirror_SourceChannelFlexRayStateType;

/*! State of a dynamic filter of a source network LIN. */
typedef struct sMirror_SourceChannelLinDynamicFilterType
{
  uint32 FilterValueLowOrId;
  uint32 FilterValueHighOrMask;
  uint8 FilterId;
  boolean IsActive;
  boolean IsIdMaskFilter;
} Mirror_SourceChannelLinDynamicFilterType;

/*! State of a source network LIN. */
typedef struct sMirror_SourceChannelLinStateType
{
  boolean IsEnabled;
  boolean HasStateChanged;
  Mirror_SourceChannelLinBusStateType State;
} Mirror_SourceChannelLinStateType;

/*! Queue element of the Mirror queue. */
typedef struct sMirror_QueueElementType
{
  uint16 Length;
  uint8* Data;
} Mirror_QueueElementType;

#endif
