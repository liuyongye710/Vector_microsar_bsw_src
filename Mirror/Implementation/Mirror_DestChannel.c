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
/**     \file     Mirror_DestChannel.c
 *      \brief    Mirror destination channel source file
 *
 *      \details  Implementation of Mirror destination channel.
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
#define MIRROR_DESTCHANNEL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_DestChannel.h"

#include "PduR_Mirror.h"

#include "SchM_Mirror.h"

#if(MIRROR_STBMID == STD_ON)
# include "StbM.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define MIRROR_NANOSECONDS_TO_MICROSECONDS                 (10000u)
#define MIRROR_PROTOCOL_DATA_HEADER_TIMESTAMP_OVERFLOW     (65535u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)))
/**********************************************************************************************************************
 *  Mirror_DestChannel_GetTime()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannel_GetTime(StbM_TimeStampType* timeStamp)
{
  Std_ReturnType retVal;

# if(MIRROR_STBMID == STD_ON)
  StbM_UserDataType userData;

  /* #10 Request the current time by calling StbM_GetCurrentTime(). */
  retVal = StbM_GetCurrentTime(Mirror_GetStbMId(), timeStamp, &userData);
#else
  retVal = E_NOT_OK;
# endif

  return retVal;
} /* Mirror_DestChannel_GetTime() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)))
/**********************************************************************************************************************
 *  Mirror_DestChannel_GetDataTimeStamp()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannel_GetDataTimeStamp(StbM_TimeStampType baseTimeStamp, uint16* dataTime)
{
  Std_ReturnType retVal = E_NOT_OK;
  StbM_TimeStampType newTimeStamp;

  /* #10 If the request for the current time is successful: */
  if(Mirror_DestChannel_GetTime(&newTimeStamp) == E_OK)
  {
    /* #20 Calculate the difference between the current time and the time of the first data element in the current queue element */
    uint16 timeDiff = (uint16)((newTimeStamp.nanoseconds - baseTimeStamp.nanoseconds) / MIRROR_NANOSECONDS_TO_MICROSECONDS);

    /* #30 If the time stamp does not overflow, return the time difference */
    if(timeDiff < MIRROR_PROTOCOL_DATA_HEADER_TIMESTAMP_OVERFLOW)
    {
      (*dataTime) = timeDiff;

      retVal = E_OK;
    }
    /* #40 Otherwise, return 0. */
    else
    {
      (*dataTime) = 0u;
    }
  }

  return retVal;
} /* Mirror_DestChannel_GetDataTimeStamp() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)))
/**********************************************************************************************************************
 *  Mirror_DestChannel_Swap16()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DestChannel_Swap16(uint16 value, P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) destBuffer)
{
  /* #10 Copy two bytes from the source pointer to the destination pointer and perform endianness conversion
   *     to big endian. */
  destBuffer[0] = (uint8) (value >> 8u);
  destBuffer[1] = (uint8) value;
} /* Mirror_DestChannel_Swap16() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)))
/**********************************************************************************************************************
 *  Mirror_DestChannel_Swap32()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DestChannel_Swap32(uint32 value, P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) destBuffer)
{
  /* #10 Copy four bytes from the source pointer to the destination pointer and perform endianness conversion
   *     to big endian. */
  destBuffer[0] = (uint8) (value >> 24u);
  destBuffer[1] = (uint8) (value >> 16u);
  destBuffer[2] = (uint8) (value >> 8u);
  destBuffer[3] = (uint8) value;
} /* Mirror_DestChannel_Swap32() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))) */

/**********************************************************************************************************************
 * Mirror_DestChannel_Transmit()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannel_Transmit(Mirror_GeneralContextType* mirrorCtx, const PduInfoType* mirrorPdu, PduIdType id)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Enter MIRROR_EXCLUSIVE_AREA_TXPDU. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();

  /* #20 If the transmission PDU of the current destination channel is free for use: */
  if(mirrorCtx->DestChannel_TxPduLocked == FALSE)
  {
    /* #30 Lock the transmission PDU. */
    mirrorCtx->DestChannel_TxPduLocked = TRUE;
    mirrorCtx->TxConfTimeout = Mirror_GetTxConfirmationTimeout();

    /* #40 Leave MIRROR_EXCLUSIVE_AREA_TXPDU. */
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();

    /* #50 Trigger the PduR to transmit the given mirrorPdu, if the transmission failed, release the lock of the transmission PDU. */
    if(PduR_MirrorTransmit(id, mirrorPdu) == E_OK)
    {
      retVal = E_OK;
    }
    else
    {
      mirrorCtx->DestChannel_TxPduLocked = FALSE;
    }
  }
  /* #60 Otherwise, leave MIRROR_EXCLUSIVE_AREA_TXPDU. */
  else
  {
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();
  }

  return retVal;
} /* Mirror_DestChannel_Transmit() */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  END OF FILE: Mirror_DestChannel.c
 *********************************************************************************************************************/
