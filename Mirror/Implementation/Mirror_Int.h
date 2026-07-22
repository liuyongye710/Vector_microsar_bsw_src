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
/*! \file  Mirror_Int.h
 *  \brief Mirror module
 *
 *  \details Internal header of the Mirror module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  MISRA / PClint JUSTIFICATIONS
 *********************************************************************************************************************/
/* *INDENT-OFF* */
/* PRQA S 3453 EOF */ /* MD_MSR_19.7 */
/* *INDENT-ON* */

#if !defined (MIRROR_INT_H)
# define MIRROR_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_Queue.h"
#include "Mirror_Types.h"

#include "Mirror_Cfg.h"
#include "Mirror_Lcfg.h"
#include "Mirror_PBcfg.h"

#if(MIRROR_STBMID == STD_ON)
# include "Rte_StbM_Type.h"
#endif

/**********************************************************************************************************************
 *  INTERNAL CONSTANT MACROS
 *********************************************************************************************************************/
#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_CAN_FRAMEID_LENGTH     (4u)
#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_LIN_FRAMEID_LENGTH     (1u)
#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_FLEXRAY_FRAMEID_LENGTH (3u)

#if !defined (MIRROR_LOCAL)
# define MIRROR_LOCAL static
#endif

#if !defined (MIRROR_LOCAL_INLINE)
# define MIRROR_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/*! Definition of the queue management elements for a IP destination channel. */
typedef struct
{
  uint16 QueueElementWriteIdx;
  uint16 QueueElementLength;
  boolean UseNewElementAfterTransmit;
  StbM_TimeStampType WriteTimeStamp;
  Mirror_Queue Queue;
} Mirror_QueueIP;
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/*! Context of a destination channel. */
typedef struct sMirror_DestChannelIpContextType
{
  Mirror_QueueIP QueueIP;
  boolean FrameLost;
  boolean TransmissionDeadlineEnabled;
  uint8 SeqNumber;
  uint16 TransmissionDeadline;
} Mirror_DestChannelIpContextType;
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

/*! General Mirror context. */
typedef struct sMirror_GeneralContextType
{
  Mirror_ModeType GlobalMode;
  NetworkHandleType CurrentDestChannelIndex;
  boolean DestChannel_TxPduLocked;
  uint16 TxConfTimeout;
  uint8 ModuleInitialized;
#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
  StbM_TimeStampType StartTime;
#endif
} Mirror_GeneralContextType;

#endif /* MIRROR_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Mirror_Int.h
 *********************************************************************************************************************/
