/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!       \file   FvM.c
 *        \brief  FvM source file
 *
 *      \details  This is the implementation of the Freshness Value Manager.
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

#define FVM_SOURCE
/**********************************************************************************************************************
 *  LOCAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* *INDENT-OFF* */

/* *INDENT-ON* */


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "FvM.h"
#include "SchM_FvM.h"
#include "Rte_SecOC.h"

#include "SecOC.h"
#include "SecOC_Cbk.h"
#include "vstdlib.h"

#if (FVM_SYNCMESSAGERECEPTIONTIMEOUTCOUNTER == STD_ON)
# include "Dem.h"
#endif

#if ((FVM_LATESTTRIPCOUNTERWITHOUTRESETCOUNTER == STD_ON) || (FVM_TRIPCOUNTERNVMBLOCKDESCRIPTOR == STD_ON))
# include "NvM.h"
#endif

#if (FVM_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if(FVM_USE_INIT_POINTER == STD_ON)
# include "EcuM_Error.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of FvM header file */
#if (  (FVM_SW_MAJOR_VERSION != 10u) \
    || (FVM_SW_MINOR_VERSION != 0u) \
    || (FVM_SW_PATCH_VERSION != 1u) )
# error "Vendor specific version numbers of <FvM>.c and <FvM>.h are inconsistent"
#endif


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#define FVM_SIZEOF_UINT32   sizeof(uint32)
#define FVM_SIZEOF_UINT64   sizeof(uint64)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

#if !defined (FVM_LOCAL_INLINE)
# define FVM_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#if(FVM_USE_INIT_POINTER == STD_ON)
# define FVM_START_SEC_VAR_INIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */
P2CONST(FvM_ConfigType, FVM_VAR_ZERO_INIT, FVM_PBCFG) FvM_ConfigDataPtr = NULL_PTR;
# define FVM_STOP_SEC_VAR_INIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FVM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) && (FVM_STARTUPCYCLECOUNTER == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_SetVerifyOverrideStatus
**********************************************************************************************************************/
/*! \brief       Sets all rx freshness values to the passed override status.
 *  \details     -
 *  \pre         -
 *  \param[in]   overrideStatus
 *               0 ==> Override VerifyStatus to "Fail" until further notice.
 *               1 ==> Override VerifyStatus to "Fail" until NumberOfMessagesToOverride of the
 *                     corresponding SecOC processing is reached.
 *               2 ==> Cancel override of VerifyStatus.
 *               40 ==> Override VerifyStatus to "Pass" until further notice.
 *                      Only available if SecOCEnableForcedPassOverride is set to TRUE.
 *               41 ==> Override VerifyStatus to "Pass" until NumberOfMessagesToOverride of the
 *                      corresponding SecOC processing is reached.
 *                      Only available if SecOCEnableForcedPassOverride is set to TRUE.
 *               0x41 ==> Until NumberOfMessagesToOverride is reached, authenticator verification is not performed.
 *                        Only available if SecOCEnableForcedPassOverride is set to TRUE.
 *               0x43 ==> Authenticator verification is not performed until further notice.
 *                        Only available if SecOCEnableForcedPassOverride is set to TRUE.
 *               0x40 ==> Override VerifyStatus to "Pass" until further notice.
 *                        Only available if SecOCEnableForcedPassOverride is set to TRUE.
 *               0x42 ==> Override VerifyStatus to "Pass" until NumberOfMessagesToOverride of the
 *                        corresponding SecOC processing is reached.
 *                        Only available if SecOCEnableForcedPassOverride is set to TRUE.
 *  \context     TASK|ISR2
 *********************************************************************************************************************/
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetVerifyOverrideStatus(uint8 overrideStatus);
#endif

#if((FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON) || (FVM_RX_RESET_SYNC_MSG_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_CheckTripAndResetSyncMessageValues
**********************************************************************************************************************/
/*!
 *  \brief      Checks the plausibility of the received sync message values.
    \details    -
    \pre        -
    \param[in]  latestFreshnessValueIdx  freshness value layout info id.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_CheckTripAndResetSyncMessageValues(FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx);
#endif

#if (FVM_RX_TRIP_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_CheckTripSyncMessageValues
**********************************************************************************************************************/
/*!
 *  \brief      Checks the plausibility of the received sync message values.
    \details    -
    \pre        -
    \param[in]  latestFreshnessValueIdx  freshness value layout info id.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_CheckTripSyncMessageValues(FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx);
#endif

#if(FVM_RX_JASPAR_WITHOUT_RESET_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_CheckTripAndMessageCounter
**********************************************************************************************************************/
/*!
 *  \brief      Checks the plausibility of the received trip and message counter values.
    \details    -
    \pre        -
    \param[in]  latestFreshnessValueIdx  freshness value layout info id.
    \param[in]  previousFreshnessValueIdx  freshness value layout info id.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_CheckTripAndMessageCounter(FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx, FvM_FreshnessValueLayoutInfoIterType previousFreshnessValueIdx);
#endif

#if (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_TxProcessing_Jaspar
**********************************************************************************************************************/
/*!
 * \brief      Processes the Jaspar use case
 * \details    -
 * \pre        -
 * \param[in]      SecOCFreshnessValueID      Holds the identifier of the freshness value.
 * \param[out]     SecOCFreshnessValue        Holds the current freshness value.
 * \param[out]     SecOCTruncatedFreshnessValue Holds the truncated freshness to be included into the Secured I-PDU.
 * \param[in,out] SecOCTruncatedFreshnessValueLength  Provides the truncated freshness length configured for this freshness.
 * \return         Std_ReturnType
 *                 E_OK:     request successful
 *                 E_NOT_OK: request failed, a freshness value cannot be provided due to
 *                           general issues for freshness or this FreshnessValueId.
 *                 E_BUSY:   The freshness information can temporarily not be provided
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_TxProcessing_Jaspar(FvM_TxFreshnessValueInfoIdxOfTxProcessingInfoType SecOCFreshnessValueID, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, P2CONST(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValueLength);
#endif

#if (FVM_TX_JASPAR_WITHOUT_RESET_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_TxProcessing_JasparWithoutResetCounter
**********************************************************************************************************************/
/*!
 * \brief      Processes the Jaspar use case
 * \details    -
 * \pre        -
 * \param[in]      SecOCFreshnessValueID      Holds the identifier of the freshness value.
 * \param[out]     SecOCFreshnessValue        Holds the current freshness value.
 * \param[out]     SecOCTruncatedFreshnessValue Holds the truncated freshness to be included into the Secured I-PDU.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_TxProcessing_JasparWithoutResetCounter(FvM_TxFreshnessValueInfoIdxOfTxProcessingInfoType SecOCFreshnessValueID, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue);
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || (FVM_TXFRESHNESSVALUEINFO == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_SetTripCounter
**********************************************************************************************************************/
/*!
 *  \brief      Sets the Trip Counter Value.
    \details    -
    \pre        -
    \param[in]  freshnessValueLayoutId  freshness value layout info id.
    \param[in]  TripCounterValue        trip counter value
    \param[in]  tripCounterBitSize      trip counter bit size
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetTripCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint32 TripCounterValue, uint8 tripCounterBitSize);
#endif

#if((FVM_TXFRESHNESSVALUEINFO == STD_ON) || (FVM_RXFRESHNESSVALUEINFO == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetTripCounter
**********************************************************************************************************************/
/*!
 * \brief      Returns the Trip Counter Value.
    \details   -
    \pre       -
    \param[in] freshnessValueLayoutId  freshness value layout info id.
    \param[in] tripCounterBitSize      trip counter bit size
    \return    trip counter value.
 */
FVM_LOCAL_INLINE FUNC(uint32, FVM_CODE) FvM_FVJaspar_GetTripCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint8 tripCounterBitSize);
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_SetResetCounter
**********************************************************************************************************************/
/*!
 * \brief      Sets the Reset Counter Value.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \param[in]  ResetCounterValue       reset counter value
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetResetCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint64 ResetCounterValue);
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON) || (FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetResetCounter
**********************************************************************************************************************/
/*!
 * \brief      Returns the Reset Counter Value.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \return     reset counter value.
 */
FVM_LOCAL_INLINE FUNC(uint64, FVM_CODE) FvM_FVJaspar_GetResetCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId);
#endif

#if ((FVM_TXFRESHNESSVALUEINFO == STD_ON) || (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_SetMessageCounter
**********************************************************************************************************************/
/*!
 * \brief      Sets the Message Counter Value.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \param[in]  MessageCounterValue     message counter value
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetMessageCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint32 MessageCounterValue);
#endif

#if((FVM_TXFRESHNESSVALUEINFO == STD_ON) || (FVM_RXFRESHNESSVALUEINFO == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetMessageCounter
**********************************************************************************************************************/
/*!
 * \brief      Returns the Message Counter Value.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \return     message counter value.
 */
FVM_LOCAL_INLINE FUNC(uint32, FVM_CODE) FvM_FVJaspar_GetMessageCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId);
#endif

#if (FVM_TXFRESHNESSVALUEINFO == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_IncMessageCounter
**********************************************************************************************************************/
/*!
 * \brief      Increments the Message Counter Value.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \param[in]  freshnessValueInfoIDx   freshness value id.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_IncMessageCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, FvM_SizeOfTxFreshnessValueInfoType freshnessValueInfoIDx);
#endif

#if (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_MessageCounterCarryProcessing
**********************************************************************************************************************/
/*!
 * \brief      Does Carry processing for the truncated Message Counter Value.
   \details    -
   \pre        -
   \param[in]  freshnessValueInfoId  freshness value id
   \return     E_OK       carry processing was successful.
               E_NOT_OK   carry processing failed.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_MessageCounterCarryProcessing(FvM_RxFreshnessValueInfoIterType freshnessValueInfoId);
#endif

#if (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_SetResetFlag
**********************************************************************************************************************/
/*!
 * \brief      Sets the reset flag.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \param[in]  ResetCounterValue       reset counter value
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetResetFlag(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint64 ResetCounterValue);
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetResetFlagValueMask
**********************************************************************************************************************/
/*!
 * \brief      Get the reset flag value mask.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \return     reset flag value mask.
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetResetFlagValueMask(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId);
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetResetFlagOfResetCounter
**********************************************************************************************************************/
/*!
 * \brief      Get the reset flag of the the passed reset counter.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \param[in]  ResetCounterValue       reset counter value
   \return     reset flag value.
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetResetFlagOfResetCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint64 ResetCounterValue);
#endif

#if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_GetResetFlag
**********************************************************************************************************************/
/*!
 * \brief      Returns the Reset Flag Value.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \return     reset flag value.
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetResetFlag(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId);
#endif

#if (FVM_TRIPFLAGBITSIZEOFFRESHNESSVALUELAYOUTINFO == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_GetTripFlagOfTripCounter
**********************************************************************************************************************/
/*!
 * \brief      Returns the trip flag of the passed trip counter
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \param[in]  TripCounterValue        trip counter value.
   \return     trip flag value.
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetTripFlagOfTripCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint32 TripCounterValue);
#endif

#if (FVM_TRIPFLAGBITSIZEOFFRESHNESSVALUELAYOUTINFO == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_GetTripFlagValueMask
**********************************************************************************************************************/
/*!
 * \brief      Returns the mask of the trip flag.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \return     trip flag mask.
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetTripFlagValueMask(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId);
#endif

#if (FVM_TRIPFLAGBITSIZEOFFRESHNESSVALUELAYOUTINFO == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_SetTripFlag
**********************************************************************************************************************/
/*!
 * \brief      Sets the trip flag to the buffer.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \param[in]  TripCounterValue        Trip Counter Value.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetTripFlag(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint32 TripCounterValue);
#endif

#if ((FVM_TRIPFLAGBITSIZEOFFRESHNESSVALUELAYOUTINFO == STD_ON) && (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetTripFlag
**********************************************************************************************************************/
/*!
 * \brief      Read trip flag from the buffer.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \return     trip flag.
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetTripFlag(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId);
#endif

/**********************************************************************************************************************
  FvM_FVJaspar_GetLengthInBytes
**********************************************************************************************************************/
/*!
 * \brief      Returns the length in full bytes.
   \details    -
   \pre        -
   \param[in]  lengthInBits  the length in bits.
   \return     the length in full bytes.
 */
FVM_LOCAL_INLINE FUNC(uint32, FVM_CODE) FvM_FVJaspar_GetLengthInBytes(uint32 lengthInBits);

/**********************************************************************************************************************
  FvM_FVJaspar_GetOffsetInBits
**********************************************************************************************************************/
/*!
 * \brief      Returns an offset in bits.
   \details    -
   \pre        -
   \param[in]  lengthInBits  the length in bits.
   \return     the number of bits that are missing to make lengthInBits divisible by eight. The return value is always in the range of [0..7].
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetOffsetInBits(uint32 lengthInBits);

#if ((FVM_TXFRESHNESSVALUEINFO == STD_ON) || (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_SetInteger32
**********************************************************************************************************************/
/*!
 * \brief      Convert given integer value to big-endian byte array.
   \details    -
   \pre        -
   \param[in]  count   Number of relevant bytes.
   \param[in]  input   Input value.
   \param[out] buffer  Pointer to output buffer.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetInteger32(uint8_least count, uint32 input, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) buffer);
#endif

#if ((FVM_TXFRESHNESSVALUEINFO == STD_ON) || (FVM_RXFRESHNESSVALUEINFO == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetInteger32
**********************************************************************************************************************/
/*!
 * \brief      Convert given big-endian byte array to integer value.
   \details    -
   \pre        -
   \param[in]  count   Number of relevant bytes.
   \param[in]  buffer  Pointer to input buffer.
   \return     Integer value
 */
FVM_LOCAL_INLINE FUNC(uint32, FVM_CODE) FvM_FVJaspar_GetInteger32(uint8_least count, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) buffer);
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || \
     (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON) || \
     (FVM_RESETCOUNTERCYCLETIMECOUNTER == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_SetInteger64
**********************************************************************************************************************/
/*!
 * \brief      Convert given integer value to big-endian byte array.
   \details    -
   \pre        -
   \param[in]  count   Number of relevant bytes.
   \param[in]  input   Input value.
   \param[out] buffer  Pointer to output buffer.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetInteger64(uint8_least count, uint64 input, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) buffer);
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || \
     (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON) || \
     (FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetInteger64
**********************************************************************************************************************/
/*!
 * \brief      Convert given big-endian byte array to integer value.
   \details    -
   \pre        -
   \param[in]  count   Number of relevant bytes.
   \param[in]  buffer  Pointer to input buffer.
   \return     Integer value
 */
FVM_LOCAL_INLINE FUNC(uint64, FVM_CODE) FvM_FVJaspar_GetInteger64(uint8_least count, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) buffer);
#endif

/**********************************************************************************************************************
  FvM_FVJaspar_BitCopy
**********************************************************************************************************************/
/*!
 * \brief      Copies a number of bits from a source to a destination.
   \details    -
   \pre        -
   \param[out] dst              Byte-pointer to the destination.
   \param[in]  dstLength        Total length (in bytes) of the destination byte array.
   \param[in]  dstBitOffsetBig  This bit offset (big, because it can even be greater than 7) is added to the destination-byte-pointer. Bits are copied to exactly this bit position.
   \param[in]  src              Byte-pointer to the source.
   \param[in]  srcBitOffsetBig  This bit offset (big, because it can even be greater than 7) is added to the source-byte-pointer. Bits are copied from exactly this bit position.
   \param[in]  numberOfBits     The number of bits that should be copied.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_BitCopy(P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) dst, uint32 dstLength, uint8 dstBitOffsetBig, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) src, uint8 srcBitOffsetBig, uint32 numberOfBits);

#if ((FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON) || (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_CopyTruncFreshnessValueToBuffer
**********************************************************************************************************************/
/*!
 * \brief      Copies truncated freshness value to the freshness verify value buffer.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \param[in]  truncatedFreshnessValue truncated freshness value.
   \param[in]  truncatedFreshnessBitLength truncated freshness value length in bit.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_CopyTruncFreshnessValueToBuffer(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) truncatedFreshnessValue, uint32 truncatedFreshnessBitLength);
#endif

#if (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_CopyFreshnessVerifyValueToTruncFreshnessValue
**********************************************************************************************************************/
/*!
 * \brief      Copies freshness verify value to truncated freshness value buffer.
   \details    -
   \pre        -
   \param[in]  freshnessValueLayoutId  freshness value layout info id.
   \param[out] truncatedFreshnessValue truncated freshness value.
   \param[in]  truncatedFreshnessBitLength truncated freshness value length in bit.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_CopyFreshnessVerifyValueToTruncFreshnessValue(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) truncatedFreshnessValue, uint32 truncatedFreshnessBitLength);
#endif

#if (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_DoRxFreshnessVerifyValueLatestPreviousCompare
**********************************************************************************************************************/
/*!
 * \brief      Compares the Latest received with the Previous Trip/Rest Counter and updates the freshness verify value.
   \details    -
   \pre        -
   \param[in]  freshnessValueInfoId    freshness value info id.
   \param[in]  latestResetCounterWithOffset  offset that is taken into account if latest and previous Trip/Rest Counter are compared.
   \return     E_OK, if freshness verify value was updated and E_NOT_OK if not freshness verify value was not updated.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_DoRxFreshnessVerifyValueLatestPreviousCompare(FvM_RxFreshnessValueInfoIterType freshnessValueInfoId, uint64 latestResetCounterWithOffset);
#endif

#if (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_GetPositiveOffestOfResetCounter
**********************************************************************************************************************/
/*!
 * \brief      Adds the offset to the reset counter with overflow protection.
   \details    -
   \pre        -
   \param[in]  offset                  offset value.
   \return     result value of calculation.
 */
FVM_LOCAL_INLINE FUNC(uint64, FVM_CODE) FvM_FVJaspar_GetPositiveOffestOfResetCounter(uint8 offset);
#endif

#if (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_GetNegativeOffestOfResetCounter
**********************************************************************************************************************/
/*!
s* \brief      Subtracts the offset of the reset counter with overflow protection.
   \details    -
   \pre        -
   \param[in]  offset                  offset value.
   \return     result value of calculation.
 */
FVM_LOCAL_INLINE FUNC(uint64, FVM_CODE) FvM_FVJaspar_GetNegativeOffestOfResetCounter(uint8 offset);
#endif

#if (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_DoRxFreshnessVerifyValueCalculation
**********************************************************************************************************************/
/*!
 * \brief      Does the Rx freshness verify value calculation.
   \details    -
   \pre        -
   \param[in]  freshnessValueInfoId    freshness value info id.
   \param[in]  offset                  offset value.
   \param[in]  negate                  TRUE  -> the negative offset is used.
                                       FALSE -> the positive offset is used.
   \return     E_OK, if successful and E_NOT_OK if not successful.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_DoRxFreshnessVerifyValueCalculation(FvM_RxFreshnessValueInfoIterType freshnessValueInfoId, uint8 offset, boolean negate);
#endif

#if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_DoRxTripFlagEvaluation
**********************************************************************************************************************/
/*!
 * \brief      Evaluates the received Trip Flag
   \details    -
   \pre        -
   \param[in]  freshnessValueInfoId    freshness value info id.
   \param[in]  SecOCAuthVerifyAttempts Authentication Verify Attempts parameter.
   \return     E_OK, if successful and E_NOT_OK if not successful.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_DoRxTripFlagEvaluation(FvM_RxFreshnessValueInfoIterType freshnessValueInfoId, uint16 SecOCAuthVerifyAttempts);
#endif

#if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_DoAttemptsEvaluation
**********************************************************************************************************************/
/*!
 * \brief      Evaluates the attempts counter and calculates the freshness value.
   \details    -
   \pre        -
   \param[in]  freshnessValueInfoId    freshness value info id.
   \param[in]  SecOCAuthVerifyAttempts Authentication Verify Attempts parameter.
   \param[in]  offset                  offset for the freshness value calculation.
   \param[in]  firstAttempt            TRUE if the first attempt is negated.
   \param[in]  secondAttempt           TRUE if the second attempt is negated.
   \return     E_OK, if successful and E_NOT_OK if not successful.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_DoAttemptsEvaluation(FvM_RxFreshnessValueInfoIterType freshnessValueInfoId, uint16 SecOCAuthVerifyAttempts, uint8 offset, boolean firstAttempt, boolean secondAttempt);
#endif

#if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_DoRxResetFlagEvaluation
**********************************************************************************************************************/
/*!
 * \brief      Evaluates the received Rest Flag
   \details    -
   \pre        -
   \param[in]  freshnessValueInfoId    freshness value info id.
   \param[in]  SecOCAuthVerifyAttempts Authentication Verify Attempts parameter.
   \return     E_OK, if successful and E_NOT_OK if not successful.
   \trace      SPEC-2983913
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_DoRxResetFlagEvaluation(FvM_RxFreshnessValueInfoIterType freshnessValueInfoId, uint16 SecOCAuthVerifyAttempts);
#endif

#if (FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_ProcessRxTripResetSyncMessage
**********************************************************************************************************************/
/*!
 * \brief      Processes the received freshness value containing trip and reset counter in one message.
   \details    -
   \pre        -
   \param[in]  SecOCFreshnessValueID              Freshness value id.
   \param[in]  SecOCTruncatedFreshnessValue       Truncated freshness value containing trip and reset cnt.
   \param[in]  SecOCTruncatedFreshnessValueLength Truncated freshness value length.
   \param[in]  SecOCFreshnessValue                Complete freshness value.
   \return     E_OK, if successful and E_NOT_OK if not successful.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_ProcessRxTripResetSyncMessage(uint16 SecOCFreshnessValueID, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue);
#endif

# if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_ProcessRxJasparMessage
**********************************************************************************************************************/
/*!
 * \brief      Processes the received jaspar message.
   \details    -
   \pre        -
   \param[in]  SecOCFreshnessValueID              Freshness value id.
   \param[in]  SecOCTruncatedFreshnessValue       Truncated freshness value containing trip and reset cnt.
   \param[in]  SecOCTruncatedFreshnessValueLength Truncated freshness value length.
   \param[in]  SecOCAuthVerifyAttempts            Amount of verification attempts.
   \param[in]  SecOCFreshnessValue                Complete freshness value.
   \return     E_OK, if successful and E_NOT_OK if not successful.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_ProcessRxJasparMessage(uint16 SecOCFreshnessValueID, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength,
     uint16 SecOCAuthVerifyAttempts, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue);
#endif

#if(FVM_RX_JASPAR_WITHOUT_RESET_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_ProcessRxJasparWithoutResetCntMessage
**********************************************************************************************************************/
/*!
 * \brief      Processes the received jaspar message without reset counter.
   \details    -
   \pre        -
   \param[in]  SecOCFreshnessValueID              Freshness value id.
   \param[in]  SecOCTruncatedFreshnessValue       Truncated freshness value.
   \param[in]  SecOCFreshnessValue                Complete freshness value.
   \return     E_OK, if successful and E_NOT_OK if not successful.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_ProcessRxJasparWithoutResetCntMessage(uint16 SecOCFreshnessValueID, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue);
#endif

#if (FVM_RX_RESET_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_ProcessRxResetCounterSyncMessage
**********************************************************************************************************************/
/*!
 * \brief      Processes the received rx sync message
   \details    -
   \pre        -
   \param[in]  SecOCFreshnessValueID              Freshness value id.
   \param[in]  SecOCTruncatedFreshnessValue       Truncated freshness value containing trip and reset cnt.
   \param[in]  SecOCTruncatedFreshnessValueLength Truncated freshness value length.
   \param[in]  SecOCFreshnessValue                Complete freshness value.
   \return     E_OK, if successful and E_NOT_OK if not successful.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_ProcessRxResetCounterSyncMessage(uint16 SecOCFreshnessValueID, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue);
#endif

#if (FVM_RX_TRIP_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_ProcessRxTripCounterMessage
**********************************************************************************************************************/
/*!
 * \brief      Processes the received rx sync message
   \details    -
   \pre        -
   \param[in]  SecOCFreshnessValueID              Freshness value id.
   \param[in]  SecOCTruncatedFreshnessValue       Truncated freshness value containing trip cnt.
   \param[in]  SecOCTruncatedFreshnessValueLength Truncated freshness value length.
   \param[out] SecOCFreshnessValue                Complete freshness value.
   \return     E_OK, if successful and E_NOT_OK if not successful.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_ProcessRxTripCounterMessage(uint16 SecOCFreshnessValueID, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue);
#endif

#if (FVM_RXFRESHNESSVALUEINFO == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_ProcessRxMessage
**********************************************************************************************************************/
/*!
 * \brief      Processes the received rx message.
   \details    -
   \pre        -
   \param[in]  SecOCFreshnessValueID              Freshness value id.
   \param[in]  SecOCTruncatedFreshnessValue       Truncated freshness value.
   \param[in]  SecOCTruncatedFreshnessValueLength Truncated freshness value length.
   \param[in]  SecOCAuthVerifyAttempts            Amount of verification attempts.
   \param[out] SecOCFreshnessValue                Complete freshness value.
   \return     E_OK, if successful and E_NOT_OK if not successful.
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_ProcessRxMessage(uint16 SecOCFreshnessValueID, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength, uint16 SecOCAuthVerifyAttempts, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue);
#endif

#if(FVM_RX_RESET_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_SerializeTripAndResetCounter
**********************************************************************************************************************/
/*!
 * \brief      Serialize trip counter and reset counter into the buffer.
   \details    -
   \pre        -
   \param[in]  latestFreshnessValueIdx            Freshness value id.
   \param[in]  SecOCTruncatedFreshnessValue       Truncated freshness value (reset counter).
   \param[in]  SecOCTruncatedFreshnessValueLength Truncated freshness value length (reset counter length).
   \return     E_OK, if successful and E_NOT_OK if not successful.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SerializeTripAndResetCounter(FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength);
#endif

#if(FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVConstruction_ResetTripSyncMessageVerificationStatusCallout
**********************************************************************************************************************/
/*!
 * \brief      Process the verification status callout for the sync messages.
   \details    -
   \pre        -
   \param[in]  verificationStatus    verification status.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVConstruction_ResetTripSyncMessageVerificationStatusCallout(SecOC_VerificationStatusType verificationStatus);
#endif

#if(FVM_RX_TRIP_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVConstruction_TripSyncMessageVerificationStatusCallout
**********************************************************************************************************************/
/*!
 * \brief      Process the verification status callout for the trip sync messages.
   \details    -
   \pre        -
   \param[in]  verificationStatus    verification status.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVConstruction_TripSyncMessageVerificationStatusCallout(SecOC_VerificationStatusType verificationStatus);
#endif

#if(FVM_RX_RESET_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVConstruction_ResetSyncMessageVerificationStatusCallout
**********************************************************************************************************************/
/*!
 * \brief      Process the verification status callout for the reset sync messages.
   \details    -
   \pre        -
   \param[in]  verificationStatus    verification status.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVConstruction_ResetSyncMessageVerificationStatusCallout(SecOC_VerificationStatusType verificationStatus);
#endif

#if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVConstruction_JasparVerificationStatusCallout
**********************************************************************************************************************/
/*!
 * \brief      Process the verification status callout for the Jaspar messages.
   \details    -
   \pre        -
   \param[in]  verificationStatus    verification status.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVConstruction_JasparVerificationStatusCallout(SecOC_VerificationStatusType verificationStatus);
#endif

#if(FVM_RX_JASPAR_WITHOUT_RESET_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVConstruction_JasparWithoutRestCounterVerificationStatusCallout
**********************************************************************************************************************/
/*!
 * \brief      Process the verification status callout for the Jaspar Without Reset Counter messages.
   \details    -
   \pre        -
   \param[in]  verificationStatus    verification status.
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVConstruction_JasparWithoutRestCounterVerificationStatusCallout(SecOC_VerificationStatusType verificationStatus);
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_ProcessRxTripResetSyncMessage
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_ProcessRxTripResetSyncMessage(uint16 SecOCFreshnessValueID, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue)
{
  Std_ReturnType ret = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(SecOCFreshnessValueID);
  FvM_FVJaspar_CopyTruncFreshnessValueToBuffer(latestFreshnessValueIdx, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength);        /* SBSW_FVM_CONST_POINTER */

  ret = FvM_FVJaspar_CheckTripAndResetSyncMessageValues(latestFreshnessValueIdx);

  if(ret == E_OK)
  {
    VStdMemCpyRamToRam(SecOCFreshnessValue,       /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_SECOC_MEM_CPY_RAM2RAM */
    FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)), FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(latestFreshnessValueIdx));
  }
  FVM_DUMMY_STATEMENT(SecOCFreshnessValueID);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return ret;
}
#endif

#if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_ProcessRxJasparMessage
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_ProcessRxJasparMessage(uint16 SecOCFreshnessValueID, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength,
     uint16 SecOCAuthVerifyAttempts, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue)
{
  Std_ReturnType ret = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  FvM_FreshnessValueLayoutInfoIterType previousFreshnessValueIdx;
  FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx;

# if((FVM_USE_DEFAULT_FRESHNESS_VALUE_IF_OUT_OF_SYNC_AFTER_START_UP_TIME == STD_OFF) && (FVM_SYNCSTATE == STD_ON))
  if(FvM_GetSyncState() == FVM_IN_SYNC_SYNCSTATE)
# endif
  {
    previousFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoPreviousIdxOfRxFreshnessValueInfo(SecOCFreshnessValueID);
    latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(SecOCFreshnessValueID);

    VStdMemCpyRamToRam(FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)),    /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_FVM_CSL03 */
        FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(previousFreshnessValueIdx)), FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(latestFreshnessValueIdx));
    FvM_FVJaspar_CopyTruncFreshnessValueToBuffer(latestFreshnessValueIdx, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength);      /* SBSW_FVM_CONST_POINTER */

    ret = FvM_FVJaspar_DoRxTripFlagEvaluation((FvM_RxFreshnessValueInfoIterType) SecOCFreshnessValueID, SecOCAuthVerifyAttempts);

    if(ret == E_OK)       /* COV_FVM_2BIT_RESET_FLAG */
    {
      VStdMemCpyRamToRam(SecOCFreshnessValue,     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_SECOC_MEM_CPY_RAM2RAM */
        FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)), FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(latestFreshnessValueIdx));
    }
  }
# if((FVM_USE_DEFAULT_FRESHNESS_VALUE_IF_OUT_OF_SYNC_AFTER_START_UP_TIME == STD_OFF) && (FVM_SYNCSTATE == STD_ON))
#  if (FVM_STARTUPCYCLECOUNTER == STD_ON)
  else if(FvM_GetSyncState() == FVM_INITIAL_OUT_OF_SYNC_SYNCSTATE)
  {
    ret = E_OK;
  }
# endif
  else
  {
    ret = E_NOT_OK;
  }
# endif
  return ret;
}
#endif

# if(FVM_RX_JASPAR_WITHOUT_RESET_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FvJaspar_ProcessRxJasparWithoutResetCntMessage
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_ProcessRxJasparWithoutResetCntMessage(uint16 SecOCFreshnessValueID, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue)
{
  FvM_FreshnessValueLayoutInfoIterType previousFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoPreviousIdxOfRxFreshnessValueInfo(SecOCFreshnessValueID);
  FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(SecOCFreshnessValueID);
  Std_ReturnType ret;

  VStdMemCpyRamToRam(FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)),      /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_FVM_CSL03 */
   SecOCTruncatedFreshnessValue, FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(latestFreshnessValueIdx));

# if(FVM_DEVMODEENABLED == STD_ON)
  if(FvM_IsDevModeEnabled())
  {
    ret = E_OK;
  }
  else
# endif
  {
    ret = FvM_FVJaspar_CheckTripAndMessageCounter(latestFreshnessValueIdx, previousFreshnessValueIdx);
  }

  if(ret == E_OK)
  {
    VStdMemCpyRamToRam(SecOCFreshnessValue,       /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_SECOC_MEM_CPY_RAM2RAM */
      FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)), FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(latestFreshnessValueIdx));
  }

  FVM_DUMMY_STATEMENT(SecOCFreshnessValueID);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return ret;
}
#endif

#if (FVM_RX_RESET_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_ProcessRxResetCounterSyncMessage
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_ProcessRxResetCounterSyncMessage(uint16 SecOCFreshnessValueID, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue)
{
  Std_ReturnType ret = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx;

# if((FVM_USE_DEFAULT_FRESHNESS_VALUE_IF_OUT_OF_SYNC_AFTER_START_UP_TIME == STD_OFF) && (FVM_SYNCSTATE == STD_ON))
  if((FvM_GetSyncState() == FVM_TRIP_COUNTER_SYNC_SYNCSTATE) || (FvM_GetSyncState() == FVM_IN_SYNC_SYNCSTATE))
# endif
  {
    latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(SecOCFreshnessValueID);

    /* Serialize trip counter into freshness value array */
    FvM_FVJaspar_SerializeTripAndResetCounter(latestFreshnessValueIdx, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength); /* SBSW_FVM_FUNC_CALL */

    ret = FvM_FVJaspar_CheckTripAndResetSyncMessageValues(latestFreshnessValueIdx);

    if(ret == E_OK)
    {
      VStdMemCpyRamToRam(SecOCFreshnessValue,       /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_SECOC_MEM_CPY_RAM2RAM */
      FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)), FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(latestFreshnessValueIdx));
    }
  }
  return ret;
}
#endif

#if (FVM_RX_TRIP_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_ProcessRxTripCounterMessage
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_ProcessRxTripCounterMessage(uint16 SecOCFreshnessValueID, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue)
{
  Std_ReturnType ret;
  FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(SecOCFreshnessValueID);
  FvM_FreshnessValueArrayTripCounterStartIdxOfFreshnessValueLayoutInfoType dstStartIdx = FvM_GetFreshnessValueArrayTripCounterStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx);
  FvM_FreshnessValueArrayTripCounterLengthOfFreshnessValueLayoutInfoType dstLength = FvM_GetFreshnessValueArrayTripCounterLengthOfFreshnessValueLayoutInfo(latestFreshnessValueIdx);

  uint8 srcBitOffset = FvM_FVJaspar_GetOffsetInBits(SecOCTruncatedFreshnessValueLength);

  FvM_FVJaspar_BitCopy(FvM_GetAddrFreshnessValueArray(dstStartIdx), dstLength, 0u, SecOCTruncatedFreshnessValue, srcBitOffset, SecOCTruncatedFreshnessValueLength); /* SBSW_FVM_FUNC_CALL */

  ret = FvM_FVJaspar_CheckTripSyncMessageValues(latestFreshnessValueIdx);

  if(ret == E_OK)
  {
    VStdMemCpyRamToRam(SecOCFreshnessValue,       /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_SECOC_MEM_CPY_RAM2RAM */
    FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)), FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(latestFreshnessValueIdx));
  }
  return ret;
}
#endif

#if (FVM_RXFRESHNESSVALUEINFO == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_ProcessRxMessage
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_ProcessRxMessage(uint16 SecOCFreshnessValueID, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength, uint16 SecOCAuthVerifyAttempts, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue)
{
  Std_ReturnType ret;

  switch (FvM_GetProcessingTypeOfRxFreshnessValueInfo(SecOCFreshnessValueID))
  {
# if (FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON)
    case FVM_JASPAR_FRESHNESS_TRIP_RESET_SYNC_MESSAGE_PROCESSINGTYPEOFRXFRESHNESSVALUEINFO:
    {
      ret = FvM_FVJaspar_ProcessRxTripResetSyncMessage(SecOCFreshnessValueID, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength, SecOCFreshnessValue); /* SBSW_FVM_FUNC_CALL */
    }
    break;
# endif
# if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
    case FVM_JASPAR_FRESHNESS_PROCESSINGTYPEOFRXFRESHNESSVALUEINFO:
    {
      ret = FvM_FVJaspar_ProcessRxJasparMessage(SecOCFreshnessValueID, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength, SecOCAuthVerifyAttempts, SecOCFreshnessValue); /* SBSW_FVM_FUNC_CALL */
    }
    break;
# endif
# if(FVM_RX_JASPAR_WITHOUT_RESET_FRESHNESS_USED == STD_ON)
    case FVM_JASPAR_FRESHNESS_WITHOUT_RESET_COUNTER_PROCESSINGTYPEOFRXFRESHNESSVALUEINFO:
    {
      ret = FvM_FVJaspar_ProcessRxJasparWithoutResetCntMessage(SecOCFreshnessValueID, SecOCTruncatedFreshnessValue, SecOCFreshnessValue); /* SBSW_FVM_FUNC_CALL */
    }
    break;
# endif
# if(FVM_RX_RESET_SYNC_MSG_USED == STD_ON)
    case FVM_JASPAR_FRESHNESS_RESET_SYNC_MESSAGE_PROCESSINGTYPEOFRXFRESHNESSVALUEINFO:
    {
      ret = FvM_FVJaspar_ProcessRxResetCounterSyncMessage(SecOCFreshnessValueID, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength, SecOCFreshnessValue); /* SBSW_FVM_FUNC_CALL */
    }
    break;
# endif
# if(FVM_RX_TRIP_SYNC_MSG_USED == STD_ON)
    case FVM_JASPAR_FRESHNESS_TRIP_SYNC_MESSAGE_PROCESSINGTYPEOFRXFRESHNESSVALUEINFO:
    {
      ret = FvM_FVJaspar_ProcessRxTripCounterMessage(SecOCFreshnessValueID, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength, SecOCFreshnessValue); /* SBSW_FVM_FUNC_CALL */
    }
    break;
# endif
    default: /* COV_FVM_MISRA */
      ret = E_NOT_OK;
    break;
  }
  FVM_DUMMY_STATEMENT(SecOCAuthVerifyAttempts);                   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  FVM_DUMMY_STATEMENT(SecOCTruncatedFreshnessValueLength);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return ret;
}
#endif

#if(FVM_RX_RESET_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_SerializeTripAndResetCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SerializeTripAndResetCounter(FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength)
{
  FvM_FreshnessValueArrayResetCounterStartIdxOfFreshnessValueLayoutInfoType dstStartIdx = FvM_GetFreshnessValueArrayResetCounterStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx);
  FvM_FreshnessValueArrayResetCounterLengthOfFreshnessValueLayoutInfoType dstLength = FvM_GetFreshnessValueArrayResetCounterLengthOfFreshnessValueLayoutInfo(latestFreshnessValueIdx);
  FvM_ResetCounterBitOffsetType dstBitOffset = FvM_GetResetCounterBitOffset();
  uint8 srcBitOffset = FvM_FVJaspar_GetOffsetInBits(SecOCTruncatedFreshnessValueLength);

  /* Serialize trip counter into freshness value array */
  FvM_FVJaspar_SetTripCounter(latestFreshnessValueIdx, FvM_GetLatestTripCounter(), FvM_GetTripCounterBitSize());

  /* Serialize reset counter into freshness value array */
  FvM_FVJaspar_BitCopy(FvM_GetAddrFreshnessValueArray(dstStartIdx), dstLength, dstBitOffset, SecOCTruncatedFreshnessValue, srcBitOffset, SecOCTruncatedFreshnessValueLength); /* SBSW_FVM_FUNC_CALL */
}
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || (FVM_TXFRESHNESSVALUEINFO == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_SetTripCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetTripCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint32 TripCounterValue, uint8 tripCounterBitSize)
{
  uint8 tripCounterValueArray[FVM_SIZEOF_UINT32];
  FvM_FreshnessValueArrayTripCounterStartIdxOfFreshnessValueLayoutInfoType tripCounterStartIdx = FvM_GetFreshnessValueArrayTripCounterStartIdxOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  FvM_FreshnessValueArrayTripCounterLengthOfFreshnessValueLayoutInfoType tripCounterLength = FvM_GetFreshnessValueArrayTripCounterLengthOfFreshnessValueLayoutInfo(freshnessValueLayoutId);

  FvM_FVJaspar_SetInteger32(FVM_SIZEOF_UINT32, TripCounterValue, tripCounterValueArray); /* SBSW_FVM_FUNC_CALL_ARRAY_WRITE */

  FvM_FVJaspar_BitCopy(FvM_GetAddrFreshnessValueArray(tripCounterStartIdx), tripCounterLength, 0u, tripCounterValueArray, (FVM_SIZEOF_UINT32 * 8u) - tripCounterBitSize, tripCounterBitSize); /* SBSW_FVM_FUNC_CALL */
}
#endif

#if((FVM_TXFRESHNESSVALUEINFO == STD_ON) || (FVM_RXFRESHNESSVALUEINFO == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetTripCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint32, FVM_CODE) FvM_FVJaspar_GetTripCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint8 tripCounterBitSize)
{
  uint8 tripCounterValueArray[FVM_SIZEOF_UINT32] = { 0u };
  FvM_FreshnessValueArrayTripCounterStartIdxOfFreshnessValueLayoutInfoType tripCounterStartIdx = FvM_GetFreshnessValueArrayTripCounterStartIdxOfFreshnessValueLayoutInfo(freshnessValueLayoutId);

  FvM_FVJaspar_BitCopy(tripCounterValueArray, FVM_SIZEOF_UINT32, (FVM_SIZEOF_UINT32 * 8u) - tripCounterBitSize, FvM_GetAddrFreshnessValueArray(tripCounterStartIdx), 0u, tripCounterBitSize); /* SBSW_FVM_FUNC_CALL */

  return FvM_FVJaspar_GetInteger32(FVM_SIZEOF_UINT32, tripCounterValueArray); /* SBSW_FVM_FUNC_CALL_ARRAY_WRITE */
}
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_SetResetCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetResetCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint64 ResetCounterValue)
{
  uint8 resetCounterValueArray[FVM_SIZEOF_UINT64];
  FvM_ResetCounterBitSizeType resetCounterBitSize = FvM_GetResetCounterBitSize();
  FvM_FreshnessValueArrayResetCounterStartIdxOfFreshnessValueLayoutInfoType resetCounterStartIdx = FvM_GetFreshnessValueArrayResetCounterStartIdxOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  FvM_FreshnessValueArrayResetCounterLengthOfFreshnessValueLayoutInfoType resetCounterLength = FvM_GetFreshnessValueArrayResetCounterLengthOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  FvM_ResetCounterBitOffsetType resetCounterBitOffset = FvM_GetResetCounterBitOffset();

  FvM_FVJaspar_SetInteger64(FVM_SIZEOF_UINT64, ResetCounterValue, resetCounterValueArray); /* SBSW_FVM_FUNC_CALL_ARRAY_WRITE */

  if (FvM_IsFreshnessValueArrayResetCounterUsedOfFreshnessValueLayoutInfo(freshnessValueLayoutId)) /* PRQA S 2741 */ /* MD_FvM_2741 */ /* COV_FVM_DEFENSIVE_PROGRAMMING */
  {
    FvM_FVJaspar_BitCopy(FvM_GetAddrFreshnessValueArray(resetCounterStartIdx), resetCounterLength, resetCounterBitOffset, resetCounterValueArray, (FVM_SIZEOF_UINT64 * 8u) - resetCounterBitSize, resetCounterBitSize); /* SBSW_FVM_FUNC_CALL */
  }
}
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON) || (FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetResetCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint64, FVM_CODE) FvM_FVJaspar_GetResetCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId)
{
  uint8 resetCounterValueArray[FVM_SIZEOF_UINT64] = { 0u };
  FvM_ResetCounterBitSizeType resetCounterBitSize = FvM_GetResetCounterBitSize();
  FvM_FreshnessValueArrayResetCounterStartIdxOfFreshnessValueLayoutInfoType resetCounterStartIdx = FvM_GetFreshnessValueArrayResetCounterStartIdxOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  FvM_ResetCounterBitOffsetType resetCounterBitOffset = FvM_GetResetCounterBitOffset();

  if (FvM_IsFreshnessValueArrayResetCounterUsedOfFreshnessValueLayoutInfo(freshnessValueLayoutId)) /* PRQA S 2741 */ /* MD_FvM_2741 */ /* COV_FVM_DEFENSIVE_PROGRAMMING */
  {
    FvM_FVJaspar_BitCopy(resetCounterValueArray, FVM_SIZEOF_UINT64, (FVM_SIZEOF_UINT64 * 8u) - resetCounterBitSize, FvM_GetAddrFreshnessValueArray(resetCounterStartIdx), resetCounterBitOffset, resetCounterBitSize); /* SBSW_FVM_FUNC_CALL_ARRAY_WRITE */
  }

  return FvM_FVJaspar_GetInteger64(FVM_SIZEOF_UINT64, resetCounterValueArray); /* SBSW_FVM_FUNC_CALL_ARRAY_WRITE */
}
#endif

#if ((FVM_TXFRESHNESSVALUEINFO == STD_ON) || (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_SetMessageCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetMessageCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint32 MessageCounterValue)
{
  uint32 MessageCounterValueIntern = MessageCounterValue;
  uint8 messageCounterValueArray[FVM_SIZEOF_UINT32];
  FvM_MessageCounterBitSizeOfFreshnessValueLayoutInfoType messageCounterBitSize = FvM_GetMessageCounterBitSizeOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  FvM_FreshnessValueArrayMessageCounterStartIdxOfFreshnessValueLayoutInfoType messageCounterStartIdx = FvM_GetFreshnessValueArrayMessageCounterStartIdxOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  FvM_FreshnessValueArrayMessageCounterLengthOfFreshnessValueLayoutInfoType messageCounterLength = FvM_GetFreshnessValueArrayMessageCounterLengthOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  FvM_MessageCounterBitOffsetOfFreshnessValueLayoutInfoType messageCounterBitOffset = FvM_GetMessageCounterBitOffsetOfFreshnessValueLayoutInfo(freshnessValueLayoutId);

# if (FVM_LATESTTRIPCOUNTER == STD_ON)
  if (FvM_FVJaspar_GetResetCounter(freshnessValueLayoutId) == FvM_GetResetCounterMax()) /* COV_FVM_REST_COUNTER_MAX_IN_MASTER_CONF */
  {
    MessageCounterValueIntern = FvM_GetMessageCounterMaxValueOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  }
# endif

  FvM_FVJaspar_SetInteger32(FVM_SIZEOF_UINT32, MessageCounterValueIntern, messageCounterValueArray); /* SBSW_FVM_FUNC_CALL_ARRAY_WRITE */

  if (FvM_IsFreshnessValueArrayMessageCounterUsedOfFreshnessValueLayoutInfo(freshnessValueLayoutId)) /* PRQA S 2741 */ /* MD_FvM_2741 */ /* COV_FVM_DEFENSIVE_PROGRAMMING */
  {
    FvM_FVJaspar_BitCopy(FvM_GetAddrFreshnessValueArray(messageCounterStartIdx), messageCounterLength, messageCounterBitOffset, messageCounterValueArray, (FVM_SIZEOF_UINT32 * 8u) - messageCounterBitSize, messageCounterBitSize); /* SBSW_FVM_FUNC_CALL */
  }
}
#endif

#if((FVM_TXFRESHNESSVALUEINFO == STD_ON) || (FVM_RXFRESHNESSVALUEINFO == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetMessageCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint32, FVM_CODE) FvM_FVJaspar_GetMessageCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId)
{
  uint8 messageCounterValueArray[FVM_SIZEOF_UINT32] = { 0u };
  FvM_MessageCounterBitSizeOfFreshnessValueLayoutInfoType messageCounterBitSize = FvM_GetMessageCounterBitSizeOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  FvM_FreshnessValueArrayMessageCounterStartIdxOfFreshnessValueLayoutInfoType messageCounterStartIdx = FvM_GetFreshnessValueArrayMessageCounterStartIdxOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  FvM_MessageCounterBitOffsetOfFreshnessValueLayoutInfoType messageCounterBitOffset = FvM_GetMessageCounterBitOffsetOfFreshnessValueLayoutInfo(freshnessValueLayoutId);

  if (FvM_IsFreshnessValueArrayMessageCounterUsedOfFreshnessValueLayoutInfo(freshnessValueLayoutId)) /* PRQA S 2741 */ /* MD_FvM_2741 */ /* COV_FVM_DEFENSIVE_PROGRAMMING */
  {
    FvM_FVJaspar_BitCopy(messageCounterValueArray, FVM_SIZEOF_UINT32, (FVM_SIZEOF_UINT32 * 8u) - messageCounterBitSize, FvM_GetAddrFreshnessValueArray(messageCounterStartIdx), messageCounterBitOffset, messageCounterBitSize); /* SBSW_FVM_FUNC_CALL_ARRAY_WRITE */
  }

  return FvM_FVJaspar_GetInteger32(FVM_SIZEOF_UINT32, messageCounterValueArray); /* SBSW_FVM_FUNC_CALL_ARRAY_WRITE */
}
#endif

#if (FVM_TXFRESHNESSVALUEINFO == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_IncMessageCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_IncMessageCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, FvM_SizeOfTxFreshnessValueInfoType freshnessValueInfoIDx)
{
  uint32 MessageCounterValue = FvM_FVJaspar_GetMessageCounter(freshnessValueLayoutId);
  if(MessageCounterValue != FvM_GetMessageCounterMaxValueOfFreshnessValueLayoutInfo(freshnessValueLayoutId))
  {
    MessageCounterValue++;
    FvM_FVJaspar_SetMessageCounter(freshnessValueLayoutId, MessageCounterValue);
# if ((FVM_TXMESSAGECOUNTERMAXNOTIFICATION == STD_ON) || (FVM_TXMESSAGECOUNTERWITHOUTRESETCOUNTERMAXNOTIFICATION == STD_ON))
    if(MessageCounterValue == FvM_GetMessageCounterMaxValueOfFreshnessValueLayoutInfo(freshnessValueLayoutId))
    {
      switch (FvM_GetProcessingTypeOfTxFreshnessValueInfo(freshnessValueInfoIDx))
      {
#  if (FVM_TXMESSAGECOUNTERMAXNOTIFICATION == STD_ON)
        case FVM_JASPAR_FRESHNESS_PROCESSINGTYPEOFTXFRESHNESSVALUEINFO:
          FvM_GetTxMessageCounterMaxNotification(0) (FvM_GetTxProcessingInfoIdxOfTxFreshnessValueInfo(freshnessValueInfoIDx)); /* SBSW_FVM_CSL_FCT_PTR */
          break;
#  endif
#  if (FVM_TXMESSAGECOUNTERWITHOUTRESETCOUNTERMAXNOTIFICATION == STD_ON)
        case FVM_JASPAR_FRESHNESS_WITHOUT_RESET_COUNTER_PROCESSINGTYPEOFTXFRESHNESSVALUEINFO:
          FvM_GetTxMessageCounterWithoutResetCounterMaxNotification(0) (FvM_GetTxProcessingInfoIdxOfTxFreshnessValueInfo(freshnessValueInfoIDx));      /* SBSW_FVM_CSL_FCT_PTR */
          break;
#  endif
        default:       /* COV_FVM_MISRA */
          /* do nothing */
          break;
      }
    }
# endif
  }
  FVM_DUMMY_STATEMENT(freshnessValueInfoIDx);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_MessageCounterCarryProcessing
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_MessageCounterCarryProcessing(FvM_RxFreshnessValueInfoIterType freshnessValueInfoId)
{
  Std_ReturnType ret = E_OK;
  FvM_FreshnessValueLayoutInfoIterType previousFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoPreviousIdxOfRxFreshnessValueInfo(freshnessValueInfoId);
  FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(freshnessValueInfoId);
  uint32 previousMessageCounter = FvM_FVJaspar_GetMessageCounter(previousFreshnessValueIdx);
  uint32 latestMessageCounter = FvM_FVJaspar_GetMessageCounter(latestFreshnessValueIdx);
  if((latestMessageCounter <= previousMessageCounter) && (latestMessageCounter != FvM_GetMessageCounterMaxValueOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)))
  {
    latestMessageCounter = latestMessageCounter + FvM_GetMessageCounterHighBitsIncValueOfRxFreshnessValueInfo(freshnessValueInfoId);
    if(latestMessageCounter > FvM_GetMessageCounterMaxValueOfFreshnessValueLayoutInfo(latestFreshnessValueIdx))
    {
      ret = E_NOT_OK;
    }
    else
    {
      FvM_FVJaspar_SetMessageCounter(latestFreshnessValueIdx, latestMessageCounter);
    }
  }
  return ret;
}
#endif

#if (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_SetResetFlag
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetResetFlag(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint64 ResetCounterValue)
{
  FvM_FreshnessValueArrayIterType destIdx = FvM_GetFreshnessValueArrayResetFlagIdxOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  uint8 copyByte = FvM_FVJaspar_GetResetFlagOfResetCounter(freshnessValueLayoutId, ResetCounterValue);

  copyByte = copyByte << FvM_GetResetFlagEndPaddingBitSizeOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  copyByte = (uint8) (copyByte | (FvM_GetFreshnessValueArray(destIdx) & FvM_GetResetFlagUnUsedBitMaskOfFreshnessValueLayoutInfo(freshnessValueLayoutId)));
  FvM_SetFreshnessValueArray(destIdx, copyByte);        /* SBSW_FVM_CSL03 */
}
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetResetFlagValueMask
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetResetFlagValueMask(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId)
{
  FvM_ResetFlagBitSizeOfFreshnessValueLayoutInfoType bitCount = FvM_GetResetFlagBitSizeOfFreshnessValueLayoutInfo(freshnessValueLayoutId);

  uint8 unUsedBits = 8u - bitCount;
  uint8 resetFlagValueMask = 255u >> unUsedBits;

  FVM_DUMMY_STATEMENT(freshnessValueLayoutId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint !e438 */
  return resetFlagValueMask;
}
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetResetFlagOfResetCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetResetFlagOfResetCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint64 ResetCounterValue)
{
  uint8 resetFlagValueMask = FvM_FVJaspar_GetResetFlagValueMask(freshnessValueLayoutId);
  uint8 resetFlag = (uint8) (ResetCounterValue & resetFlagValueMask);
  return resetFlag;
}
#endif

#if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_GetResetFlag
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetResetFlag(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId)
{
  FvM_FreshnessValueArrayIterType srcIdx = FvM_GetFreshnessValueArrayResetFlagIdxOfFreshnessValueLayoutInfo(freshnessValueLayoutId);

  uint8 resetFlag = FvM_GetFreshnessValueArray(srcIdx) & FvM_GetResetFlagCopyBitMaskOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  resetFlag = resetFlag >> FvM_GetResetFlagEndPaddingBitSizeOfFreshnessValueLayoutInfo(freshnessValueLayoutId);

  return resetFlag;
}
#endif

#if (FVM_TRIPFLAGBITSIZEOFFRESHNESSVALUELAYOUTINFO == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_GetTripFlagOfTripCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetTripFlagOfTripCounter(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint32 TripCounterValue)
{
  uint8 tripFlagValueMask = FvM_FVJaspar_GetTripFlagValueMask(freshnessValueLayoutId);
  uint8 tripFlag = (uint8) (TripCounterValue & tripFlagValueMask);
  return tripFlag;
}
#endif

#if (FVM_TRIPFLAGBITSIZEOFFRESHNESSVALUELAYOUTINFO == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_GetTripFlagValueMask
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetTripFlagValueMask(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId)
{
  FvM_TripFlagBitSizeOfFreshnessValueLayoutInfoType bitCount = FvM_GetTripFlagBitSizeOfFreshnessValueLayoutInfo(freshnessValueLayoutId);

  uint8 unUsedBits = 8u - bitCount;
  uint8 tripFlagValueMask = 255u >> unUsedBits;

  FVM_DUMMY_STATEMENT(freshnessValueLayoutId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint !e438 */
  return tripFlagValueMask;
}
#endif

#if (FVM_TRIPFLAGBITSIZEOFFRESHNESSVALUELAYOUTINFO == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_SetTripFlag
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetTripFlag(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, uint32 TripCounterValue)
{
  if(FvM_IsFreshnessValueArrayTripFlagUsedOfFreshnessValueLayoutInfo(freshnessValueLayoutId))   /* PRQA S 2991 */ /* MD_FvM_2991 */
  {
    FvM_FreshnessValueArrayIterType destIdx = FvM_GetFreshnessValueArrayTripFlagIdxOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
    uint8 copyByte = FvM_FVJaspar_GetTripFlagOfTripCounter(freshnessValueLayoutId, TripCounterValue);

    copyByte = copyByte << FvM_GetEndPaddingBitSizeOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
    copyByte = (uint8) (copyByte | (FvM_GetFreshnessValueArray(destIdx) & FvM_GetTripFlagUnUsedBitMaskOfFreshnessValueLayoutInfo(freshnessValueLayoutId)));
    FvM_SetFreshnessValueArray(destIdx, copyByte);      /* SBSW_FVM_CSL03 */
  }
}
#endif

#if ((FVM_TRIPFLAGBITSIZEOFFRESHNESSVALUELAYOUTINFO == STD_ON) && (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetTripFlag
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetTripFlag(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId)
{
  FvM_FreshnessValueArrayIterType srcIdx = FvM_GetFreshnessValueArrayTripFlagIdxOfFreshnessValueLayoutInfo(freshnessValueLayoutId);

  uint8 tripFlag = FvM_GetFreshnessValueArray(srcIdx) & FvM_GetTripFlagCopyBitMaskOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  tripFlag = tripFlag >> FvM_GetEndPaddingBitSizeOfFreshnessValueLayoutInfo(freshnessValueLayoutId);

  return tripFlag;
}
#endif

/**********************************************************************************************************************
  FvM_FVJaspar_GetLengthInBytes
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint32, FVM_CODE) FvM_FVJaspar_GetLengthInBytes(uint32 lengthInBits)
{
  uint32 fullBytes = lengthInBits >> 3u;
  if((lengthInBits & 7u) != 0u) /* COV_FVM_BYTE_LENGTH */
  {
    fullBytes++;
  }
  return fullBytes;
}

/**********************************************************************************************************************
  FvM_FVJaspar_GetOffsetInBits
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint8, FVM_CODE) FvM_FVJaspar_GetOffsetInBits(uint32 lengthInBits)
{
  uint8 offset = (uint8) (lengthInBits & 7u);
  if (offset != 0u) /* COV_FVM_TRIP_RESET_CNT_BITSIZE */
  {
    offset = 8u - offset;
  }
  return offset;
}

#if ((FVM_TXFRESHNESSVALUEINFO == STD_ON) || (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || (FVM_RESETCOUNTERCYCLETIMECOUNTER == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_SetInteger32
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetInteger32(uint8_least count, uint32 input, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) buffer)
{
  uint8_least countVar = count;
  uint32 inputVar = input;

  /* Loop relevant bytes */
  while (countVar > 0u)
  {
    countVar--;
    /* Store most significant byte first */
    buffer[countVar] = (uint8)(inputVar & 0xFFu); /* SBSW_FVM_SET_INTEGER */
    /* Shift in next byte */
    inputVar >>= 8u;
  }
}
#endif

#if ((FVM_TXFRESHNESSVALUEINFO == STD_ON) || (FVM_RXFRESHNESSVALUEINFO == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetInteger32
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint32, FVM_CODE) FvM_FVJaspar_GetInteger32(uint8_least count, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) buffer)
{
  uint32 output = 0u;
  uint8_least idx = 0u;
  uint8_least countVar = count;

  /* Loop relevant bytes */
  while (countVar > 0u)
  {
    /* Most significant byte first */
    output <<= 8u;
    /* Add current byte */
    output |= (uint32)buffer[idx];

    idx++;
    countVar--;
  }

  return output;
}
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || \
     (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON) || \
     (FVM_RESETCOUNTERCYCLETIMECOUNTER == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_SetInteger64
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetInteger64(uint8_least count, uint64 input, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) buffer)
{
  uint8_least countVar = count;
  uint64 inputVar = input;

  /* Loop relevant bytes */
  while (countVar > 0u)
  {
    countVar--;
    /* Store most significant byte first */
    buffer[countVar] = (uint8)(inputVar & 0xFFu); /* SBSW_FVM_SET_INTEGER */
    /* Shift in next byte */
    inputVar >>= 8u;
  }
}
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) || \
     (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON) || \
     (FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_GetInteger64
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint64, FVM_CODE) FvM_FVJaspar_GetInteger64(uint8_least count, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) buffer)
{
  uint64 output = 0u;
  uint8_least idx = 0u;
  uint8_least countVar = count;

  /* Loop relevant bytes */
  while (countVar > 0u)
  {
    /* Most significant byte first */
    output <<= 8u;
    /* Add current byte */
    output |= (uint64)buffer[idx];

    idx++;
    countVar--;
  }

  return output;
}
#endif

/**********************************************************************************************************************
  FvM_FVJaspar_BitCopy
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
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_BitCopy(P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) dst,
                                                       uint32 dstLength,
                                                       uint8 dstBitOffsetBig,
                                                       P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) src,
                                                       uint8 srcBitOffsetBig,
                                                       uint32 numberOfBits)
{
  /* DECLARATION */

  uint32 numberOfBitsInternal;

  uint32 dstIdx;
  uint32 dstStartIdx;
  uint32 dstEndIdx;
  uint8 dstBitOffset;

  uint32 srcIdx;
  uint32 srcStartIdx;
  uint32 srcEndIdx;
  uint8 srcBitOffset;

  uint8 srcRShift;
  uint8 srcLShift;

  uint8 dstBitMaskStart;
  uint8 dstBitMaskEnd;
  uint8 dstBitMask;

  uint8 srcByte;

  /* INITIALIZATION */

  /* Ensure freedom of interference */
  if ((dstBitOffsetBig + numberOfBits) > (dstLength * 8u)) /* COV_FVM_BITCOPY_DEFENSIVE_PROGRAMMING */
  {
    numberOfBitsInternal = ((dstLength * 8u) - dstBitOffsetBig);
  }
  else
  {
    numberOfBitsInternal = numberOfBits;
  }

  /* Prepare iterations */
  dstEndIdx = FvM_FVJaspar_GetLengthInBytes(dstBitOffsetBig + numberOfBitsInternal);
  dstStartIdx = (uint32) dstBitOffsetBig / 8u;
  dstBitOffset = dstBitOffsetBig % 8u;

  srcEndIdx = FvM_FVJaspar_GetLengthInBytes(srcBitOffsetBig + numberOfBitsInternal);
  srcStartIdx = (uint32) srcBitOffsetBig / 8u;
  srcBitOffset = srcBitOffsetBig % 8u;

  /* Prepare shifts */
  srcRShift = 0u;
  srcLShift = 0u;
  if (dstBitOffset > srcBitOffset) /* COV_FVM_TRIP_RESET_CNT_BITSIZE */
  {
    srcRShift = dstBitOffset - srcBitOffset;
  }
  else
  {
    srcLShift = srcBitOffset - dstBitOffset;
  }

  /* Prepare masks */
  dstBitMaskStart   = 0xFFu;
  dstBitMaskStart >>= dstBitOffset;
  dstBitMaskEnd     = 0xFFu;
  dstBitMaskEnd   <<= FvM_FVJaspar_GetOffsetInBits(dstBitOffset + numberOfBitsInternal);

  /* ALGORITHM */

  srcIdx = srcStartIdx;

  for (dstIdx = dstStartIdx; dstIdx < dstEndIdx; dstIdx++)
  {
    srcByte = 0u;
    if (srcIdx < srcEndIdx) /* The total number of src bytes can be one byte less than the total number of dst bytes */ /* COV_FVM_TRIP_RESET_CNT_BITSIZE */
    {
      srcByte = (uint8)(src[srcIdx]);
    }

    if (srcLShift > 0u) /* Left shift case */ /* COV_FVM_TRIP_RESET_CNT_BITSIZE */
    {
      srcByte <<= srcLShift;
      if ((srcIdx + 1u) < srcEndIdx)  /* The total number of src bytes can be one byte more than the total number of dst bytes */
      {
        srcByte |= (src[srcIdx + 1u] >> (8u - srcLShift));
      }
    }
    else if (srcRShift > 0u) /* Right shift case */ /* COV_FVM_TRIP_RESET_CNT_BITSIZE */
    {
      srcByte >>= srcRShift;
      if (srcIdx > srcStartIdx)
      {
        srcByte |= (src[srcIdx - 1u] << (8u - srcRShift));
      }
    }
    else /* No shift case */
    {
      /* Do nothing */
    }


    dstBitMask = 0xFFu;

    /* Note: First and last loop cycle can be the same */

    if (dstIdx == dstStartIdx)  /* First loop cycle */
    {
      dstBitMask &= dstBitMaskStart; /* PRQA S 2986 */ /* MD_FvM_2986_BitCopy */
    }

    if (dstIdx == (dstEndIdx - 1u))  /* Last loop cycle */
    {
      dstBitMask &= dstBitMaskEnd;
    }

    if (dstBitMask == 0xFFu) /* COV_FVM_TRIP_RESET_CNT_BITSIZE */
    {
      dst[dstIdx] = srcByte; /* SBSW_FVM_BITCOPY_ARRAY_WRITE */
    }
    else
    {
      uint8 tmpByte;
      tmpByte = dst[dstIdx]; /* Read */
      tmpByte &= (~dstBitMask); /* Modify */
      srcByte &= dstBitMask;
      tmpByte |= srcByte; /* Modify */
      dst[dstIdx] = tmpByte; /* Write */ /* SBSW_FVM_BITCOPY_ARRAY_WRITE */
    }

    srcIdx++;
  }
} /* PRQA S 6010, 6030, 6060 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STPAR */

#if ((FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON) || (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_CopyTruncFreshnessValueToBuffer
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_CopyTruncFreshnessValueToBuffer(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) truncatedFreshnessValue, uint32 truncatedFreshnessBitLength)
{
  FvM_FreshnessValueArrayTruncatedFreshnessValueStartIdxOfFreshnessValueLayoutInfoType dstStartIdx = FvM_GetFreshnessValueArrayTruncatedFreshnessValueStartIdxOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  FvM_TruncatedFreshnessValueBitOffsetOfFreshnessValueLayoutInfoType dstBitOffset = FvM_GetTruncatedFreshnessValueBitOffsetOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  FvM_FreshnessValueArrayTruncatedFreshnessValueLengthOfFreshnessValueLayoutInfoType dstLength = FvM_GetFreshnessValueArrayTruncatedFreshnessValueLengthOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  uint8 srcBitOffset = FvM_FVJaspar_GetOffsetInBits(truncatedFreshnessBitLength);

  FvM_FVJaspar_BitCopy(FvM_GetAddrFreshnessValueArray(dstStartIdx), dstLength, dstBitOffset, truncatedFreshnessValue, srcBitOffset, truncatedFreshnessBitLength); /* SBSW_FVM_FUNC_CALL */
}
#endif

#if (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_CopyFreshnessVerifyValueToTruncFreshnessValue
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_CopyFreshnessVerifyValueToTruncFreshnessValue(FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) truncatedFreshnessValue, uint32 truncatedFreshnessBitLength)
{
  FvM_FreshnessValueArrayTruncatedFreshnessValueStartIdxOfFreshnessValueLayoutInfoType srcStartIdx = FvM_GetFreshnessValueArrayTruncatedFreshnessValueStartIdxOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  FvM_TruncatedFreshnessValueBitOffsetOfFreshnessValueLayoutInfoType srcBitOffset = FvM_GetTruncatedFreshnessValueBitOffsetOfFreshnessValueLayoutInfo(freshnessValueLayoutId);
  uint32 dstLength = FvM_FVJaspar_GetLengthInBytes(truncatedFreshnessBitLength);
  uint8 dstBitOffset = FvM_FVJaspar_GetOffsetInBits(truncatedFreshnessBitLength);

  FvM_FVJaspar_BitCopy(truncatedFreshnessValue, dstLength, dstBitOffset, FvM_GetAddrFreshnessValueArray(srcStartIdx), srcBitOffset, truncatedFreshnessBitLength); /* SBSW_FVM_FUNC_CALL */
}
#endif


#if (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_DoRxFreshnessVerifyValueLatestPreviousCompare
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_DoRxFreshnessVerifyValueLatestPreviousCompare(FvM_RxFreshnessValueInfoIterType freshnessValueInfoId, uint64 latestResetCounterWithOffset)
{
  Std_ReturnType ret = E_OK;    /* PRQA S 2981 */ /* MD_MSR_RetVal */
  FvM_FreshnessValueLayoutInfoIterType previousFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoPreviousIdxOfRxFreshnessValueInfo(freshnessValueInfoId);
  FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(freshnessValueInfoId);
  uint64 previousReceivedResetCounter = FvM_FVJaspar_GetResetCounter(previousFreshnessValueIdx);
  uint32 previousReceivedTripCounter = FvM_FVJaspar_GetTripCounter(previousFreshnessValueIdx, FvM_GetTripCounterBitSize());

  if((previousReceivedTripCounter == FvM_GetLatestTripCounter()) && (previousReceivedResetCounter == latestResetCounterWithOffset))
  {
    ret = FvM_FVJaspar_MessageCounterCarryProcessing((FvM_RxFreshnessValueInfoIterType) freshnessValueInfoId);
  }
  else if((latestResetCounterWithOffset > previousReceivedResetCounter) || (FvM_GetLatestTripCounter() > previousReceivedTripCounter))
  {
    FvM_FVJaspar_SetTripCounter(latestFreshnessValueIdx, FvM_GetLatestTripCounter(), FvM_GetTripCounterBitSize());
    FvM_FVJaspar_SetResetCounter(latestFreshnessValueIdx, latestResetCounterWithOffset);
    if(latestResetCounterWithOffset == FvM_GetResetCounterMax())
    {
      FvM_FVJaspar_SetMessageCounter(latestFreshnessValueIdx, FvM_GetMessageCounterMaxValueOfFreshnessValueLayoutInfo(latestFreshnessValueIdx));
    }
    else
    {
      FvM_FVJaspar_SetMessageCounter(latestFreshnessValueIdx, FvM_FVJaspar_GetMessageCounter(latestFreshnessValueIdx) & FvM_GetMessageCounterLowerBitsMaskOfRxFreshnessValueInfo(freshnessValueInfoId));
    }
  }
  else
  {
    ret = E_NOT_OK;
  }
  return ret;
}
#endif

#if (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_GetPositiveOffestOfResetCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint64, FVM_CODE) FvM_FVJaspar_GetPositiveOffestOfResetCounter(uint8 offset)
{
  uint64 retValue;
  if((FvM_GetResetCounterMax() - FvM_GetLatestResetCounter()) >= offset)        /* COV_FVM_ALWAYS_TRUE_DEF_PROGRAMMING */
  {
    retValue = (uint64) (FvM_GetLatestResetCounter() + offset);
  }
  else
  {
    retValue = FvM_GetResetCounterMax();
  }
  return retValue;
}
#endif

#if (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_GetNegativeOffestOfResetCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(uint64, FVM_CODE) FvM_FVJaspar_GetNegativeOffestOfResetCounter(uint8 offset)
{
  uint64 retValue;
  if(FvM_GetLatestResetCounter() >= offset)
  {
    retValue = (uint64) (FvM_GetLatestResetCounter() - offset);
  }
  else
  {
    retValue = 0u;
  }
  return retValue;
}
#endif

#if (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_DoRxFreshnessVerifyValueCalculation
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_DoRxFreshnessVerifyValueCalculation(FvM_RxFreshnessValueInfoIterType freshnessValueInfoId, uint8 offset, boolean negate)
{
  Std_ReturnType ret = E_OK;    /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint64 latestResetCounterWithOffsetFirstTry;
  uint64 latestResetCounterWithOffsetSecoundTry;

  if(negate == TRUE)
  {
    latestResetCounterWithOffsetFirstTry = FvM_FVJaspar_GetNegativeOffestOfResetCounter(offset);
    latestResetCounterWithOffsetSecoundTry = FvM_FVJaspar_GetPositiveOffestOfResetCounter(offset);
  }
  else
  {
    latestResetCounterWithOffsetFirstTry = FvM_FVJaspar_GetPositiveOffestOfResetCounter(offset);
    latestResetCounterWithOffsetSecoundTry = FvM_FVJaspar_GetNegativeOffestOfResetCounter(offset);
  }

  ret = FvM_FVJaspar_DoRxFreshnessVerifyValueLatestPreviousCompare(freshnessValueInfoId, latestResetCounterWithOffsetFirstTry);

  if(ret != E_OK)
  {
    ret = FvM_FVJaspar_DoRxFreshnessVerifyValueLatestPreviousCompare(freshnessValueInfoId, latestResetCounterWithOffsetSecoundTry);
  }

  return ret;
}
#endif

#if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_DoRxTripFlagEvaluation
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_DoRxTripFlagEvaluation(FvM_RxFreshnessValueInfoIterType freshnessValueInfoId, uint16 SecOCAuthVerifyAttempts)
{
  Std_ReturnType ret = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
# if(FVM_TRIPFLAGBITSIZEOFFRESHNESSVALUELAYOUTINFO == STD_ON)
  boolean doResetFlagEvaluation = TRUE;
  FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(freshnessValueInfoId);
  if(FvM_IsFreshnessValueArrayTripFlagUsedOfFreshnessValueLayoutInfo(latestFreshnessValueIdx))  /* PRQA S 2991 */ /* MD_FvM_2991 */
  {
    uint8 receivedTripFlag = FvM_FVJaspar_GetTripFlag(latestFreshnessValueIdx);
    uint8 latestTripFlag = FvM_FVJaspar_GetTripFlagOfTripCounter(latestFreshnessValueIdx, FvM_GetLatestTripCounter());
    if(receivedTripFlag != latestTripFlag)
    {
      FvM_FreshnessValueLayoutInfoIterType previousFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoPreviousIdxOfRxFreshnessValueInfo(freshnessValueInfoId);
      uint32 previousReceivedTripCounter = FvM_FVJaspar_GetTripCounter(previousFreshnessValueIdx, FvM_GetTripCounterBitSize());
      if(previousReceivedTripCounter == FvM_GetLatestTripCounter())   /* COV_FVM_ALWAYS_TRUE_TRIP_FLAG */
      {
        FvM_FVJaspar_SetTripCounter(latestFreshnessValueIdx, FvM_GetLatestTripCounter() + 1u, FvM_GetTripCounterBitSize());
        FvM_FVJaspar_SetResetCounter(latestFreshnessValueIdx, 1u);
        FvM_FVJaspar_SetMessageCounter(latestFreshnessValueIdx, FvM_FVJaspar_GetMessageCounter(latestFreshnessValueIdx) & FvM_GetMessageCounterLowerBitsMaskOfRxFreshnessValueInfo(freshnessValueInfoId));
        ret = E_OK;
      }
      else
      {
        ret = FvM_FVJaspar_MessageCounterCarryProcessing((FvM_RxFreshnessValueInfoIterType) freshnessValueInfoId);
      }
      doResetFlagEvaluation = FALSE;
    }
  }

  if(doResetFlagEvaluation == TRUE)
# endif
  {
    ret = FvM_FVJaspar_DoRxResetFlagEvaluation(freshnessValueInfoId, SecOCAuthVerifyAttempts);
  }
  return ret;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_DoAttemptsEvaluation
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_DoAttemptsEvaluation(FvM_RxFreshnessValueInfoIterType freshnessValueInfoId, uint16 SecOCAuthVerifyAttempts, uint8 offset, boolean firstAttempt, boolean secondAttempt)
{
  Std_ReturnType ret = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  if(SecOCAuthVerifyAttempts == 0u)
  {
    ret = FvM_FVJaspar_DoRxFreshnessVerifyValueCalculation((FvM_RxFreshnessValueInfoIterType) freshnessValueInfoId, offset, firstAttempt);
  }
  else if(SecOCAuthVerifyAttempts == 1u)        /* COV_FVM_ALWAYS_TRUE_MISRA */
  {
    ret = FvM_FVJaspar_DoRxFreshnessVerifyValueCalculation((FvM_RxFreshnessValueInfoIterType) freshnessValueInfoId, offset, secondAttempt);
  }
  else
  {
    /* do nothing */
  }
  return ret;
}
#endif

#if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_DoRxResetFlagEvaluation
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_DoRxResetFlagEvaluation(FvM_RxFreshnessValueInfoIterType freshnessValueInfoId, uint16 SecOCAuthVerifyAttempts)
{
  Std_ReturnType ret = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(freshnessValueInfoId);
  uint8 receivedResetFlag = FvM_FVJaspar_GetResetFlag(latestFreshnessValueIdx);
  uint8 latestResetFlag = FvM_FVJaspar_GetResetFlagOfResetCounter(latestFreshnessValueIdx, (uint64) FvM_GetLatestResetCounter());
  uint8 resetFlagValueMask = FvM_FVJaspar_GetResetFlagValueMask(latestFreshnessValueIdx);

  if(latestResetFlag == receivedResetFlag)
  {
    ret = FvM_FVJaspar_DoRxFreshnessVerifyValueCalculation((FvM_RxFreshnessValueInfoIterType) freshnessValueInfoId, 0u, FALSE);
  }
  else if((((uint8) (latestResetFlag - 1u)) & resetFlagValueMask) == receivedResetFlag)
  {
    ret = FvM_FVJaspar_DoAttemptsEvaluation(freshnessValueInfoId, SecOCAuthVerifyAttempts, 1u, TRUE, FALSE);
  }
  else if(((latestResetFlag + 1u) & resetFlagValueMask) == receivedResetFlag)
  {
    ret = FvM_FVJaspar_DoAttemptsEvaluation(freshnessValueInfoId, SecOCAuthVerifyAttempts, 1u, FALSE, TRUE);
  }
  else if((((uint8) (latestResetFlag - 2u)) & resetFlagValueMask) == receivedResetFlag) /* COV_FVM_ALWAYS_TRUE_MISRA */
  {
    ret = FvM_FVJaspar_DoAttemptsEvaluation(freshnessValueInfoId, SecOCAuthVerifyAttempts, 2u, TRUE, FALSE);
  }
  else
  {
    /* do nothing */
  }
  return ret;
}
#endif

#if ((FVM_RX_JASPAR_FRESHNESS_USED == STD_ON) && (FVM_STARTUPCYCLECOUNTER == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_SetVerifyOverrideStatus
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_SetVerifyOverrideStatus(uint8 overrideStatus)
{
  FvM_RxFreshnessValueInfoIterType rxFreshnessValueId = 0u;
  for(; rxFreshnessValueId < FvM_GetSizeOfRxFreshnessValueInfo(); rxFreshnessValueId++)
  {
# if(FVM_INVALIDHNDOFRXFRESHNESSVALUEINFO == STD_ON)
    if(!FvM_IsInvalidHndOfRxFreshnessValueInfo(rxFreshnessValueId))
# endif
    {
      if(FvM_GetProcessingTypeOfRxFreshnessValueInfo(rxFreshnessValueId) == FVM_JASPAR_FRESHNESS_PROCESSINGTYPEOFRXFRESHNESSVALUEINFO)
      {
        (void) SecOC_VerifyStatusOverride((uint16) rxFreshnessValueId, overrideStatus, 255u);
      }
    }
  }
}
#endif


#if((FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON) || (FVM_RX_RESET_SYNC_MSG_USED == STD_ON))
/**********************************************************************************************************************
  FvM_FVJaspar_CheckTripAndResetSyncMessageValues
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_CheckTripAndResetSyncMessageValues(FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx)
{
  Std_ReturnType ret = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint32 receivedTripCounter = FvM_FVJaspar_GetTripCounter(latestFreshnessValueIdx, FvM_GetTripCounterBitSize());
  uint64 receivedResetCounter = FvM_FVJaspar_GetResetCounter(latestFreshnessValueIdx);

  if(receivedTripCounter > FvM_GetLatestTripCounter()) /* COV_FVM_TRIP_CNT_SEPARATE_MSG */
  {
    ret = E_OK;
  }
  else if ((receivedTripCounter == FvM_GetLatestTripCounter()) && (receivedResetCounter == FvM_GetLatestResetCounter())) /* COV_FVM_TRIP_CNT_SEPARATE_MSG */
  {
    ret = FVM_RETURN_VALUE_FOR_SAME_TRIP_RESET_COUNTER_SYNC_MESSAGE;
  }
  else if((receivedTripCounter == FvM_GetLatestTripCounter()) && (receivedResetCounter > FvM_GetLatestResetCounter())) /* COV_FVM_TRIP_CNT_SEPARATE_MSG */
  {
    ret = E_OK;
  }
  else if((FvM_GetLatestTripCounter() + FvM_GetClearAcceptanceWindow()) >= FvM_GetTripCounterMax())     /* PRQA S 2985 */ /* MD_FvM_2985_ClearAcceptanceWindow */ /* COV_FVM_TRIP_CNT_SEPARATE_MSG */
  {
    if((receivedTripCounter >= 1u) && (receivedTripCounter <= (((uint32) FvM_GetClearAcceptanceWindow()) + 1u))) /* COV_FVM_TRIP_CNT_SEPARATE_MSG */
    {
      ret = E_OK;
    }
  }
  else
  {
    /* do nothing */
  }
  return ret;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (FVM_RX_TRIP_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_CheckTripSyncMessageValues
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_CheckTripSyncMessageValues(FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx)
{
  Std_ReturnType ret = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint32 receivedTripCounter = FvM_FVJaspar_GetTripCounter(latestFreshnessValueIdx, FvM_GetTripCounterBitSize());

  if(receivedTripCounter > FvM_GetLatestTripCounter())
  {
    ret = E_OK;
  }
  else if(receivedTripCounter == FvM_GetLatestTripCounter())
  {
    ret = FVM_RETURN_VALUE_FOR_SAME_TRIP_SYNC_MESSAGE;
  }
  else if((FvM_GetLatestTripCounter() + FvM_GetClearAcceptanceWindow()) >= FvM_GetTripCounterMax())     /* PRQA S 2985 */ /* MD_FvM_2985_ClearAcceptanceWindow */
  {
    if((receivedTripCounter >= 1u) && (receivedTripCounter <= (((uint32) FvM_GetClearAcceptanceWindow()) + 1u)))
    {
      ret = E_OK;
    }
  }
  else
  {
    /* do nothing */
  }
  return ret;
}
#endif

#if(FVM_RX_JASPAR_WITHOUT_RESET_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_CheckTripAndMessageCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_CheckTripAndMessageCounter(FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx, FvM_FreshnessValueLayoutInfoIterType previousFreshnessValueIdx)
{
  Std_ReturnType ret = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint64 previousTripCounter = (uint64) FvM_FVJaspar_GetTripCounter(previousFreshnessValueIdx, FvM_GetTripCounterWithoutResetCounterBitSize());
  uint64 latestTripCounter = (uint64) FvM_FVJaspar_GetTripCounter(latestFreshnessValueIdx, FvM_GetTripCounterWithoutResetCounterBitSize());

  if(previousTripCounter <= latestTripCounter)
  {
    if(previousTripCounter == latestTripCounter)
    {
      uint32 previousMessageCounter = FvM_FVJaspar_GetMessageCounter(previousFreshnessValueIdx);
      uint32 latestMessageCounter = FvM_FVJaspar_GetMessageCounter(latestFreshnessValueIdx);
      if((previousMessageCounter < latestMessageCounter) || (FvM_GetMessageCounterMaxValueOfFreshnessValueLayoutInfo(previousFreshnessValueIdx) == latestMessageCounter))
      {
        ret = E_OK;
      }
    }
    else
    {
      ret = E_OK;
    }
  }
  else if((previousTripCounter + FvM_GetClearAcceptanceWindowWithoutResetCounter()) >= FvM_GetTripCounterWithoutResetCounterMax())
  {
    if((latestTripCounter >= 1u) && (latestTripCounter <= (((uint64) FvM_GetClearAcceptanceWindowWithoutResetCounter()) + 1u)))
    {
      ret = E_OK;
    }
  }
  else  /* COV_FVM_MISRA */
  {
    /* do nothing */
  }
  return ret;
}
#endif

#if (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_TxProcessing_Jaspar
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(Std_ReturnType, FVM_CODE) FvM_FVJaspar_TxProcessing_Jaspar(FvM_TxFreshnessValueInfoIdxOfTxProcessingInfoType SecOCFreshnessValueID, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, P2CONST(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValueLength)
{
  Std_ReturnType ret = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
# if(FVM_TX_USE_DEFAULT_FRESHNESS_VALUE_DURING_START_UP == STD_OFF)
  if(FvM_GetSyncState() == FVM_IN_SYNC_SYNCSTATE)
# elif(FVM_RECEPTIONTIMEOUTFORTRANSMISSIONCOUNTER == STD_ON)
  if(FvM_GetReceptionTimeoutForTransmissionCounter() == 0u)
# endif
  {
    FvM_FreshnessValueLayoutInfoIterType previousFreshnessValueIdx = (FvM_FreshnessValueLayoutInfoIterType) FvM_GetFreshnessValueLayoutInfoPreviousIdxOfTxFreshnessValueInfo(SecOCFreshnessValueID);
    FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = (FvM_FreshnessValueLayoutInfoIterType) FvM_GetFreshnessValueLayoutInfoLatestIdxOfTxFreshnessValueInfo(SecOCFreshnessValueID);
    uint32 previousTripCounter = FvM_FVJaspar_GetTripCounter(previousFreshnessValueIdx, FvM_GetTripCounterBitSize());
    uint64 previousResetCounter = FvM_FVJaspar_GetResetCounter(previousFreshnessValueIdx);

    if((FvM_GetLatestTripCounter() == previousTripCounter) && (FvM_GetLatestResetCounter() == previousResetCounter))
    {
      FvM_FVJaspar_IncMessageCounter(latestFreshnessValueIdx, SecOCFreshnessValueID);
    }
    else
    {
      FvM_FVJaspar_SetTripCounter(latestFreshnessValueIdx, FvM_GetLatestTripCounter(), FvM_GetTripCounterBitSize());
      FvM_FVJaspar_SetResetCounter(latestFreshnessValueIdx, FvM_GetLatestResetCounter());
      FvM_FVJaspar_SetMessageCounter(latestFreshnessValueIdx, 1u);
      FvM_FVJaspar_SetResetFlag(latestFreshnessValueIdx, (uint32) FvM_GetLatestResetCounter());
# if (FVM_TRIPFLAGBITSIZEOFFRESHNESSVALUELAYOUTINFO == STD_ON)
      FvM_FVJaspar_SetTripFlag(latestFreshnessValueIdx, FvM_GetLatestTripCounter());
# endif
    }
    VStdMemCpyRamToRam(SecOCFreshnessValue,     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_SECOC_MEM_CPY_RAM2RAM */
                       FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)), FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(latestFreshnessValueIdx));

    FvM_FVJaspar_CopyFreshnessVerifyValueToTruncFreshnessValue(latestFreshnessValueIdx, SecOCTruncatedFreshnessValue, *SecOCTruncatedFreshnessValueLength);     /* SBSW_FVM_CHECKED_POINTER_1 */

    ret = E_OK;
  }
# if(FVM_TX_USE_DEFAULT_FRESHNESS_VALUE_DURING_START_UP == STD_OFF)
  else
  {
    ret = E_BUSY;
  }
# endif
  return ret;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (FVM_TX_JASPAR_WITHOUT_RESET_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVJaspar_TxProcessing_JasparWithoutResetCounter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVJaspar_TxProcessing_JasparWithoutResetCounter(FvM_TxFreshnessValueInfoIdxOfTxProcessingInfoType SecOCFreshnessValueID, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue)
{
  FvM_FreshnessValueLayoutInfoIterType previousFreshnessValueIdx = (FvM_FreshnessValueLayoutInfoIterType) FvM_GetFreshnessValueLayoutInfoPreviousIdxOfTxFreshnessValueInfo(SecOCFreshnessValueID);
  FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = (FvM_FreshnessValueLayoutInfoIterType) FvM_GetFreshnessValueLayoutInfoLatestIdxOfTxFreshnessValueInfo(SecOCFreshnessValueID);
  uint32 previousTripCounter = FvM_FVJaspar_GetTripCounter(previousFreshnessValueIdx, FvM_GetTripCounterWithoutResetCounterBitSize());

  if(FvM_GetLatestTripCounterWithoutResetCounter() == previousTripCounter)
  {
    FvM_FVJaspar_IncMessageCounter(latestFreshnessValueIdx, SecOCFreshnessValueID);
  }
  else
  {
    FvM_FVJaspar_SetTripCounter(latestFreshnessValueIdx, FvM_GetLatestTripCounterWithoutResetCounter(), FvM_GetTripCounterWithoutResetCounterBitSize());
    FvM_FVJaspar_SetMessageCounter(latestFreshnessValueIdx, 1u);
  }

  VStdMemCpyRamToRam(SecOCFreshnessValue,       /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_SECOC_MEM_CPY_RAM2RAM */
                     FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)), FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(latestFreshnessValueIdx));
  VStdMemCpyRamToRam(SecOCTruncatedFreshnessValue,      /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_SECOC_MEM_CPY_RAM2RAM */
                     FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)), FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(latestFreshnessValueIdx));
}
#endif


#if(FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVConstruction_ResetTripSyncMessageVerificationStatusCallout
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVConstruction_ResetTripSyncMessageVerificationStatusCallout(SecOC_VerificationStatusType verificationStatus)
{
  if((verificationStatus.verificationStatus == SECOC_VERIFICATIONSUCCESS)
#  if(FVM_DEVMODEENABLED == STD_ON)
      || (FvM_IsDevModeEnabled() && (verificationStatus.verificationStatus != SECOC_FRESHNESSFAILURE))
#  endif
  )
  {
    FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(verificationStatus.freshnessValueID);
    uint32 newTripCounter = FvM_FVJaspar_GetTripCounter(latestFreshnessValueIdx, FvM_GetTripCounterBitSize());
    uint64 newResetCounter = FvM_FVJaspar_GetResetCounter(latestFreshnessValueIdx);
    uint32 oldTripCounterValue = FvM_GetLatestTripCounter();

    if(newTripCounter < oldTripCounterValue)
    {
      VStdMemClr(FvM_GetAddrFreshnessValueArray(0), FvM_GetSizeOfFreshnessValueArray());  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_FVM_MEM_CPY_CLR */
    }

    FvM_SetLatestTripCounter(newTripCounter);     /* SBSW_FVM_CSL_VAR_ACCESS */
    FvM_SetLatestResetCounter(newResetCounter);   /* SBSW_FVM_CSL_VAR_ACCESS */

#  if(FVM_TRIPCOUNTERNVMBLOCKDESCRIPTOR == STD_ON)
    if(newTripCounter != oldTripCounterValue)
    {
      /* Write updated trip counter to NvM */
      (void) NvM_WriteBlock(FvM_GetTripCounterNvMBlockDescriptor(0), &FvM_GetLatestTripCounter());        /* PRQA S 0315 */ /* MD_FvM_0315_NvMWriteBlock */ /* SBSW_FVM_FUNC_CALL */
    }
#  endif

#  if (FVM_TRIPCOUNTERMAXNOTIFICATION == STD_ON)
    if(newTripCounter == FvM_GetTripCounterMax())
    {
      FvM_GetTripCounterMaxNotification(0) ();    /* SBSW_FVM_CSL_FCT_PTR */
    }
#  endif
#  if (FVM_RESETCOUNTERMAXNOTIFICATION == STD_ON)
    if(newResetCounter == FvM_GetResetCounterMax())
    {
      FvM_GetResetCounterMaxNotification(0) ();   /* SBSW_FVM_CSL_FCT_PTR */
    }
#  endif
#  if(FVM_SYNCSTATE == STD_ON)
    if(FvM_GetSyncState() != FVM_IN_SYNC_SYNCSTATE)
    {
      FvM_SetSyncState(FVM_IN_SYNC_SYNCSTATE);    /* SBSW_FVM_CSL_VAR_ACCESS */
    }
#  endif
#  if (FVM_SYNCMESSAGERECEPTIONTIMEOUTCOUNTER == STD_ON)
    FvM_SetSyncMessageReceptionTimeoutCounter(FvM_GetSyncMessageReceptionTimeoutCnt() + 1u);      /* SBSW_FVM_CSL_VAR_ACCESS */
    (void) Dem_SetEventStatus(FvM_GetDemEventIdReference(0), DEM_EVENT_STATUS_PASSED);
#  endif

#  if (FVM_RECEPTIONTIMEOUTFORTRANSMISSIONCOUNTER == STD_ON)
    FvM_SetReceptionTimeoutForTransmissionCounter(0u);    /* SBSW_FVM_CSL_VAR_ACCESS */
#  endif
  }
}
#endif

#if(FVM_RX_RESET_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVConstruction_ResetSyncMessageVerificationStatusCallout
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVConstruction_ResetSyncMessageVerificationStatusCallout(SecOC_VerificationStatusType verificationStatus)
{
  if((verificationStatus.verificationStatus == SECOC_VERIFICATIONSUCCESS)
# if(FVM_DEVMODEENABLED == STD_ON)
      || (FvM_IsDevModeEnabled() && (verificationStatus.verificationStatus != SECOC_FRESHNESSFAILURE))
# endif
    )
  {
    FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(verificationStatus.freshnessValueID);
    uint64 newResetCounter = FvM_FVJaspar_GetResetCounter(latestFreshnessValueIdx);

    FvM_SetLatestResetCounter(newResetCounter);   /* SBSW_FVM_CSL_VAR_ACCESS */

# if (FVM_RESETCOUNTERMAXNOTIFICATION == STD_ON)
    if(newResetCounter == FvM_GetResetCounterMax())
    {
      FvM_GetResetCounterMaxNotification(0) ();   /* SBSW_FVM_CSL_FCT_PTR */
    }
# endif
# if(FVM_SYNCSTATE == STD_ON)
    if(FvM_GetSyncState() != FVM_IN_SYNC_SYNCSTATE)
    {
      FvM_SetSyncState(FVM_IN_SYNC_SYNCSTATE);    /* SBSW_FVM_CSL_VAR_ACCESS */
    }
# endif

# if (FVM_RECEPTIONTIMEOUTFORTRANSMISSIONCOUNTER == STD_ON)
    FvM_SetReceptionTimeoutForTransmissionCounter(0u);    /* SBSW_FVM_CSL_VAR_ACCESS */
# endif
# if (FVM_SYNCMESSAGERECEPTIONTIMEOUTCOUNTER == STD_ON)
    FvM_SetSyncMessageReceptionTimeoutCounter(FvM_GetSyncMessageReceptionTimeoutCnt() + 1u);      /* SBSW_FVM_CSL_VAR_ACCESS */
    (void) Dem_SetEventStatus(FvM_GetDemEventIdReference(0), DEM_EVENT_STATUS_PASSED);
# endif
  }
}
#endif

#if(FVM_RX_TRIP_SYNC_MSG_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVConstruction_TripSyncMessageVerificationStatusCallout
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVConstruction_TripSyncMessageVerificationStatusCallout(SecOC_VerificationStatusType verificationStatus)
{
  if((verificationStatus.verificationStatus == SECOC_VERIFICATIONSUCCESS)
#  if(FVM_DEVMODEENABLED == STD_ON)
      || (FvM_IsDevModeEnabled() && (verificationStatus.verificationStatus != SECOC_FRESHNESSFAILURE))
#  endif
  )
  {
    FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(verificationStatus.freshnessValueID);
    uint32 newTripCounter = FvM_FVJaspar_GetTripCounter(latestFreshnessValueIdx, FvM_GetTripCounterBitSize());
    uint32 oldTripCounterValue = FvM_GetLatestTripCounter();

    if(newTripCounter < oldTripCounterValue)
    {
      VStdMemClr(FvM_GetAddrFreshnessValueArray(0), FvM_GetSizeOfFreshnessValueArray());  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_FVM_MEM_CPY_CLR */
    }

    FvM_SetLatestTripCounter(newTripCounter);     /* SBSW_FVM_CSL_VAR_ACCESS */

#  if(FVM_TRIPCOUNTERNVMBLOCKDESCRIPTOR == STD_ON)
    if(newTripCounter != oldTripCounterValue)
    {
      /* Write updated trip counter to NvM */
      (void) NvM_WriteBlock(FvM_GetTripCounterNvMBlockDescriptor(0), &FvM_GetLatestTripCounter());        /* PRQA S 0315 */ /* MD_FvM_0315_NvMWriteBlock */ /* SBSW_FVM_FUNC_CALL */
    }
#  endif

#  if (FVM_TRIPCOUNTERMAXNOTIFICATION == STD_ON)
    if(newTripCounter == FvM_GetTripCounterMax())
    {
      FvM_GetTripCounterMaxNotification(0) ();    /* SBSW_FVM_CSL_FCT_PTR */
    }
#  endif

#  if(FVM_SYNCSTATE == STD_ON)
    if((FvM_GetSyncState() == FVM_INITIAL_OUT_OF_SYNC_SYNCSTATE) || (FvM_GetSyncState() == FVM_INVALID_OUT_OF_SYNC_SYNCSTATE))
    {
      FvM_SetSyncState(FVM_TRIP_COUNTER_SYNC_SYNCSTATE);    /* SBSW_FVM_CSL_VAR_ACCESS */
    }
#  endif
#  if (FVM_RECEPTIONTIMEOUTFORTRANSMISSIONCOUNTER == STD_ON)
     FvM_SetReceptionTimeoutForTransmissionCounter(0u);    /* SBSW_FVM_CSL_VAR_ACCESS */
#  endif
#  if (FVM_SYNCMESSAGERECEPTIONTIMEOUTCOUNTER == STD_ON)
    FvM_SetSyncMessageReceptionTimeoutCounter(FvM_GetSyncMessageReceptionTimeoutCnt() + 1u);      /* SBSW_FVM_CSL_VAR_ACCESS */
    (void) Dem_SetEventStatus(FvM_GetDemEventIdReference(0), DEM_EVENT_STATUS_PASSED);
#  endif
  }
}
#endif


#if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVConstruction_JasparVerificationStatusCallout
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVConstruction_JasparVerificationStatusCallout(SecOC_VerificationStatusType verificationStatus)
{
#  if((FVM_USE_DEFAULT_FRESHNESS_VALUE_IF_OUT_OF_SYNC_AFTER_START_UP_TIME == STD_OFF) && (FVM_SYNCSTATE == STD_ON))
  if(FvM_GetSyncState() == FVM_IN_SYNC_SYNCSTATE)
#  endif
  {
    if(verificationStatus.verificationStatus == SECOC_VERIFICATIONSUCCESS)
    {
      FvM_FreshnessValueLayoutInfoIterType previousFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoPreviousIdxOfRxFreshnessValueInfo(verificationStatus.freshnessValueID);
      FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(verificationStatus.freshnessValueID);
      VStdMemCpyRamToRam(FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(previousFreshnessValueIdx)),        /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_FVM_CSL03 */
                         FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)), FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(previousFreshnessValueIdx));
#  if(FVM_RXMESSAGECOUNTERMAXNOTIFICATION == STD_ON)
      if(FvM_FVJaspar_GetMessageCounter(previousFreshnessValueIdx) == FvM_GetMessageCounterMaxValueOfFreshnessValueLayoutInfo(previousFreshnessValueIdx))
      {
        FvM_GetRxMessageCounterMaxNotification(0) (verificationStatus.freshnessValueID);  /* SBSW_FVM_CSL_FCT_PTR */
      }
#  endif
    }
  }
}
#endif

#if(FVM_RX_JASPAR_WITHOUT_RESET_FRESHNESS_USED == STD_ON)
/**********************************************************************************************************************
  FvM_FVConstruction_JasparWithoutRestCounterVerificationStatusCallout
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FVM_LOCAL_INLINE FUNC(void, FVM_CODE) FvM_FVConstruction_JasparWithoutRestCounterVerificationStatusCallout(SecOC_VerificationStatusType verificationStatus)
{
  if(verificationStatus.verificationStatus == SECOC_VERIFICATIONSUCCESS)
  {
    FvM_FreshnessValueLayoutInfoIterType previousFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoPreviousIdxOfRxFreshnessValueInfo(verificationStatus.freshnessValueID);
#  if(FVM_DEVMODEENABLED == STD_ON)
    if(!FvM_IsDevModeEnabled())
#  endif
    {
      FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(verificationStatus.freshnessValueID);
      VStdMemCpyRamToRam(FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(previousFreshnessValueIdx)),  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_FVM_CSL03 */
                         FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)), FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(previousFreshnessValueIdx));
    }
#  if(FVM_RXMESSAGECOUNTERWITHOUTRESETCOUNTERMAXNOTIFICATION == STD_ON)
    if(FvM_FVJaspar_GetMessageCounter(previousFreshnessValueIdx) == FvM_GetMessageCounterMaxValueOfFreshnessValueLayoutInfo(previousFreshnessValueIdx))
    {
      FvM_GetRxMessageCounterWithoutResetCounterMaxNotification(0) (verificationStatus.freshnessValueID); /* SBSW_FVM_CSL_FCT_PTR */
    }
#  endif
#  if(FVM_RXTRIPCOUNTERWITHOUTRESETCOUNTERMAXNOTIFICATION == STD_ON)
    if(FvM_FVJaspar_GetTripCounter(previousFreshnessValueIdx, FvM_GetTripCounterWithoutResetCounterBitSize()) == FvM_GetTripCounterWithoutResetCounterMax())
    {
      FvM_GetRxTripCounterWithoutResetCounterMaxNotification(0) (verificationStatus.freshnessValueID); /* SBSW_FVM_CSL_FCT_PTR */
    }
#  endif
  }
}
#endif



/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  FvM_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, FVM_CODE) FvM_InitMemory(void)
{
  /* ----- Implementation ----------------------------------------------- */
  FvM_SetInitialized(FALSE);    /* SBSW_FVM_CSL_VAR_ACCESS */
#if(FVM_USE_INIT_POINTER == STD_ON)
  FvM_ConfigDataPtr = NULL_PTR;
#endif
#if (FVM_LATESTTRIPCOUNTERWITHOUTRESETCOUNTER == STD_ON)
  FvM_SetTripCounterReadErrorDetectedFlag(FALSE); /* SBSW_FVM_CSL_VAR_ACCESS */
#endif
}

/**********************************************************************************************************************
  FvM_DeInit
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
*/
FUNC(void, FVM_CODE) FvM_DeInit(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = FVM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  if(!FvM_IsInitialized())
  {
    errorId = FVM_E_INVALID_REQUEST;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    FvM_SetInitialized(FALSE);  /* SBSW_FVM_CSL_VAR_ACCESS */
#if(FVM_USE_INIT_POINTER == STD_ON)
    FvM_ConfigDataPtr = NULL_PTR;
#endif
  }

#if(FVM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != FVM_E_NO_ERROR)
  {
    (void) Det_ReportError(FVM_MODULE_ID, FVM_INSTANCE_ID_DET, FVM_SID_DEINIT, errorId);
  }
#endif

  FVM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

/**********************************************************************************************************************
 *  FvM_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, FVM_CODE) FvM_Init(P2CONST(FvM_ConfigType, AUTOMATIC, FVM_PBCFG) ConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = FVM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
#if(FVM_USE_INIT_POINTER == STD_ON)
  FvM_ConfigDataPtr = ConfigPtr;
#endif

  /* ----- Development Error Checks ------------------------------------- */
  /* Check initialization state of the component */
  if(FvM_IsInitialized())
  {
    errorId = FVM_E_ALREADY_INITIALIZED;
  }
  /* Check parameter 'ConfigPtr' */
#if(FVM_USE_INIT_POINTER == STD_ON)
  /* Check validity of Config pointer */
  else if(FvM_ConfigDataPtr == NULL_PTR)
  {
# if(FVM_USE_ECUM_BSW_ERROR_HOOK == STD_ON)   /* COV_FVM_VAR_DEPENDENT_SWITCH */
    EcuM_BswErrorHook(FVM_MODULE_ID, ECUM_BSWERROR_NULLPTR);
# endif
    errorId = FVM_E_PARAM_CONFIG;
  }
# if (FVM_FINALMAGICNUMBER == STD_ON) /* COV_FVM_VAR_DEPENDENT_SWITCH */
  else if(FvM_GetFinalMagicNumber() != FVM_FINAL_MAGIC_NUMBER)
  {
#  if(FVM_USE_ECUM_BSW_ERROR_HOOK == STD_ON)  /* COV_FVM_VAR_DEPENDENT_SWITCH */
    EcuM_BswErrorHook(FVM_MODULE_ID, ECUM_BSWERROR_MAGICNUMBER);
#  endif
    errorId = FVM_E_PARAM_CONFIG;
    FvM_ConfigDataPtr = NULL_PTR;
  }
# endif
#else
  else if(ConfigPtr != NULL_PTR)
  {
    errorId = FVM_E_PARAM_CONFIG;
  }
#endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#if (FVM_FRESHNESSVALUEARRAY == STD_ON)
    VStdMemClr(FvM_GetAddrFreshnessValueArray(0), FvM_GetSizeOfFreshnessValueArray());  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_FVM_MEM_CPY_CLR */
#endif
#if (FVM_STARTUPCYCLECOUNTER == STD_ON)
    FvM_SetStartUpCycleCounter(FvM_GetStartUpCycleCnt());       /* SBSW_FVM_CSL_VAR_ACCESS */
# if (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
    FvM_FVJaspar_SetVerifyOverrideStatus(SECOC_OVERRIDE_VERIFICATION_STATUS_PASS_UNTIL_NOTICE);
# endif
#endif

#if (FVM_SYNCMESSAGERECEPTIONTIMEOUTCOUNTER == STD_ON)
    FvM_SetSyncMessageReceptionTimeoutCounter(FvM_GetSyncMessageReceptionTimeoutCnt() + 1u);    /* SBSW_FVM_CSL_VAR_ACCESS */
#endif

#if (FVM_RECEPTIONTIMEOUTFORTRANSMISSIONCOUNTER == STD_ON)
    FvM_SetReceptionTimeoutForTransmissionCounter(FvM_GetReceptionTimeoutForTransmissionCnt()); /* SBSW_FVM_CSL_VAR_ACCESS */
#endif

#if (FVM_SYNCSTATE == STD_ON)
# if(FVM_STARTUPCYCLECOUNTER == STD_ON)
    FvM_SetSyncState(FVM_INITIAL_OUT_OF_SYNC_SYNCSTATE);        /* SBSW_FVM_CSL_VAR_ACCESS */
# else
    FvM_SetSyncState(FVM_INVALID_OUT_OF_SYNC_SYNCSTATE);        /* SBSW_FVM_CSL_VAR_ACCESS */
# endif
#endif

#if (FVM_LATESTTRIPCOUNTER == STD_ON)
# if (FVM_TRIPCOUNTERNVMBLOCKDESCRIPTOR == STD_OFF)
    FvM_SetLatestTripCounter(0);        /* SBSW_FVM_CSL_VAR_ACCESS */
# endif

# if(FVM_RESETCOUNTERCYCLETIMECOUNTER == STD_ON)
    FvM_SetLatestResetCounter(1);       /* SBSW_FVM_CSL_VAR_ACCESS */
    FvM_IncLatestTripCounter();       /* SBSW_FVM_CSL_VAR_ACCESS */

    (void) NvM_WriteBlock(FvM_GetTripCounterNvMBlockDescriptor(0), &FvM_GetLatestTripCounter());        /* PRQA S 0315 */ /* MD_FvM_0315_NvMWriteBlock */ /* SBSW_FVM_FUNC_CALL */

    FvM_SetResetCounterCycleTimeCounter(FvM_GetResetCounterCycleTime()); /* SBSW_FVM_CSL_VAR_ACCESS */
# else
    FvM_SetLatestResetCounter(0);       /* SBSW_FVM_CSL_VAR_ACCESS */
# endif

# if (FVM_TRIPFLAGBITSIZEOFFRESHNESSVALUELAYOUTINFO == STD_ON)
    {
      FvM_FreshnessValueLayoutInfoIterType freshnessValueLayoutId = 0u;
      for(; freshnessValueLayoutId < FvM_GetSizeOfFreshnessValueLayoutInfo(); freshnessValueLayoutId++)
      {
        FvM_FVJaspar_SetTripFlag(freshnessValueLayoutId, FvM_GetLatestTripCounter());
      }
    }
# endif
#endif

#if(FVM_LATESTTRIPCOUNTERWITHOUTRESETCOUNTER == STD_ON)
  /* If NvM read error was detected the Latest Trip Counter Value is set to the maximum value and is not written back to NvM */
  if(FvM_IsTripCounterReadErrorDetectedFlag())
  {
    FvM_SetLatestTripCounterWithoutResetCounter((FvM_LatestTripCounterWithoutResetCounterType)  FvM_GetTripCounterWithoutResetCounterMax()); /* SBSW_FVM_CSL_VAR_ACCESS */
#  if (FVM_TX_JASPAR_WITHOUT_RESET_FRESHNESS_USED == STD_ON)
    {
      FvM_TxFreshnessValueInfoIterType txFreshnessValueInfo = 0;
      for(; txFreshnessValueInfo < FvM_GetSizeOfTxFreshnessValueInfo(); txFreshnessValueInfo++)
      {
        if(FvM_GetProcessingTypeOfTxFreshnessValueInfo(txFreshnessValueInfo) == FVM_JASPAR_FRESHNESS_WITHOUT_RESET_COUNTER_PROCESSINGTYPEOFTXFRESHNESSVALUEINFO)  /* PRQA S 2741 */ /* MD_FvM_2741 */ /* COV_FVM_WITHOUT_RESETCOUNTER_TX */
        {
          FvM_FreshnessValueLayoutInfoIterType previousFreshnessValueIdx = (FvM_FreshnessValueLayoutInfoIterType) FvM_GetFreshnessValueLayoutInfoPreviousIdxOfTxFreshnessValueInfo(txFreshnessValueInfo);
          FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = (FvM_FreshnessValueLayoutInfoIterType) FvM_GetFreshnessValueLayoutInfoLatestIdxOfTxFreshnessValueInfo(txFreshnessValueInfo);
          FvM_FVJaspar_SetTripCounter(latestFreshnessValueIdx, FvM_GetLatestTripCounterWithoutResetCounter(), FvM_GetTripCounterWithoutResetCounterBitSize());
          FvM_FVJaspar_SetMessageCounter(latestFreshnessValueIdx,  FvM_GetMessageCounterMaxValueOfFreshnessValueLayoutInfo(latestFreshnessValueIdx));
          FvM_FVJaspar_SetTripCounter(previousFreshnessValueIdx, FvM_GetLatestTripCounterWithoutResetCounter(), FvM_GetTripCounterWithoutResetCounterBitSize());
          FvM_FVJaspar_SetMessageCounter(previousFreshnessValueIdx,  FvM_GetMessageCounterMaxValueOfFreshnessValueLayoutInfo(previousFreshnessValueIdx));
        }
      }
    }
#  endif
  }
  else
  {
    /* Latest Trip Counter Value is read form NvM and is incremented during start up */
    if(FvM_GetTripCounterWithoutResetCounterMax() == FvM_GetLatestTripCounterWithoutResetCounter())
    {
      FvM_SetLatestTripCounterWithoutResetCounter(0);   /* SBSW_FVM_CSL_VAR_ACCESS */
    }
    FvM_IncLatestTripCounterWithoutResetCounter();      /* SBSW_FVM_CSL_VAR_ACCESS */
    /* Write updated trip counter to NvM */
    (void) NvM_WriteBlock(FvM_GetTripCounterWithoutResetCounterNvMBlockDescriptor(0), &FvM_GetLatestTripCounterWithoutResetCounter());  /* PRQA S 0315 */ /* MD_FvM_0315_NvMWriteBlock */ /* SBSW_FVM_FUNC_CALL */
  }

# if(FVM_TRIPCOUNTERWITHOUTRESETCOUNTERMAXNOTIFICATION == STD_ON)
    if(FvM_GetTripCounterWithoutResetCounterMax() == FvM_GetLatestTripCounterWithoutResetCounter())
    {
      FvM_GetTripCounterWithoutResetCounterMaxNotification(0) ();       /* SBSW_FVM_CSL_FCT_PTR */
    }
# endif
#endif

#if(FVM_DEVMODEENABLED == STD_ON)
    FvM_SetDevModeEnabled(FALSE);       /* SBSW_FVM_CSL_VAR_ACCESS */
#endif

    FvM_SetInitialized(TRUE);   /* SBSW_FVM_CSL_VAR_ACCESS */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (FVM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != FVM_E_NO_ERROR)
  {
    (void) Det_ReportError(FVM_MODULE_ID, FVM_INSTANCE_ID_DET, FVM_SID_INIT, errorId);
  }
#else
  FVM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint !e438 */
#endif
  FVM_DUMMY_STATEMENT(ConfigPtr);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint !e438 */
} /* PRQA S 6080, 6030, 6050 */ /* MD_MSR_STMIF, MD_MSR_STCYC, MD_MSR_STCAL */

#if (FVM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  FvM_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, FVM_CODE) FvM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, FVM_APPL_VAR) versioninfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = FVM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (FVM_DEV_ERROR_DETECT == STD_ON)   /* COV_FVM_VAR_DEV_ERROR_DETECT */
  if(versioninfo == NULL_PTR)
  {
    errorId = FVM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    versioninfo->vendorID = (FVM_VENDOR_ID);    /* SBSW_FVM_CHECKED_POINTER */
    versioninfo->moduleID = (FVM_MODULE_ID);    /* SBSW_FVM_CHECKED_POINTER */
    versioninfo->sw_major_version = (FVM_SW_MAJOR_VERSION);     /* SBSW_FVM_CHECKED_POINTER */
    versioninfo->sw_minor_version = (FVM_SW_MINOR_VERSION);     /* SBSW_FVM_CHECKED_POINTER */
    versioninfo->sw_patch_version = (FVM_SW_PATCH_VERSION);     /* SBSW_FVM_CHECKED_POINTER */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (FVM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != FVM_E_NO_ERROR)
  {
    (void) Det_ReportError(FVM_MODULE_ID, FVM_INSTANCE_ID_DET, FVM_SID_GET_VERSION_INFO, errorId);
  }
# else
  FVM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint !e438 */
# endif
}
#endif

#if(FVM_RXFRESHNESSVALUEINFO == STD_ON)
/**********************************************************************************************************************
 *  FvM_VerificationStatusCallout()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, FVM_CODE) FvM_VerificationStatusCallout(SecOC_VerificationStatusType verificationStatus)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = FVM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  if(!FvM_IsInitialized())
  {
    errorId = FVM_E_UNINIT;
  }
# if(FVM_DEV_ERROR_DETECT == STD_ON)    /* COV_FVM_VAR_DEV_ERROR_DETECT */
  else if(verificationStatus.freshnessValueID >= FvM_GetSizeOfRxFreshnessValueInfo())
  {
    errorId = FVM_E_PARAM;
  }
#  if(FVM_INVALIDHNDOFRXFRESHNESSVALUEINFO == STD_ON)
  else if(FvM_IsInvalidHndOfRxFreshnessValueInfo(verificationStatus.freshnessValueID))
  {
    errorId = FVM_E_PARAM;
  }
#  endif
# endif
  else
  {
    SchM_Enter_FvM_FVM_EXCLUSIVE_AREA_RX_FRESHNESS();
    /* ----- Implementation ----------------------------------------------- */
    switch (FvM_GetProcessingTypeOfRxFreshnessValueInfo(verificationStatus.freshnessValueID))
    {
# if(FVM_RX_TRIP_RESET_SYNC_MSG_USED == STD_ON)
      case FVM_JASPAR_FRESHNESS_TRIP_RESET_SYNC_MESSAGE_PROCESSINGTYPEOFRXFRESHNESSVALUEINFO:
      {
        FvM_FVConstruction_ResetTripSyncMessageVerificationStatusCallout(verificationStatus);
      }
        break;
# endif
# if(FVM_RX_TRIP_SYNC_MSG_USED == STD_ON)
      case FVM_JASPAR_FRESHNESS_TRIP_SYNC_MESSAGE_PROCESSINGTYPEOFRXFRESHNESSVALUEINFO:
      {
        FvM_FVConstruction_TripSyncMessageVerificationStatusCallout(verificationStatus);
      }
        break;
# endif
# if(FVM_RX_RESET_SYNC_MSG_USED == STD_ON)
      case FVM_JASPAR_FRESHNESS_RESET_SYNC_MESSAGE_PROCESSINGTYPEOFRXFRESHNESSVALUEINFO:
      {
        FvM_FVConstruction_ResetSyncMessageVerificationStatusCallout(verificationStatus);
      }
        break;
# endif
# if(FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
      case FVM_JASPAR_FRESHNESS_PROCESSINGTYPEOFRXFRESHNESSVALUEINFO:
      {
        FvM_FVConstruction_JasparVerificationStatusCallout(verificationStatus);
      }
        break;
# endif
# if(FVM_RX_JASPAR_WITHOUT_RESET_FRESHNESS_USED == STD_ON)
      case FVM_JASPAR_FRESHNESS_WITHOUT_RESET_COUNTER_PROCESSINGTYPEOFRXFRESHNESSVALUEINFO:
      {
        FvM_FVConstruction_JasparWithoutRestCounterVerificationStatusCallout(verificationStatus);
      }
        break;
# endif
      default: /* COV_FVM_MISRA */
        /* do nothing */
        break;
    }
    SchM_Exit_FvM_FVM_EXCLUSIVE_AREA_RX_FRESHNESS();
  }
  /* ----- Development Error Report --------------------------------------- */
# if (FVM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != FVM_E_NO_ERROR)
  {
    (void) Det_ReportError(FVM_MODULE_ID, FVM_INSTANCE_ID_DET, FVM_SID_VERIFICATION_STATUS_CALLOUT, errorId);
  }
# else
  FVM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint !e438 */
# endif
}  /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif



#if(FVM_TXPROCESSINGINFO == STD_ON)
/**********************************************************************************************************************
 *  SecOC_GetTxFreshnessTruncData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, FVM_CODE) SecOC_GetTxFreshnessTruncData(uint16 SecOCFreshnessValueID, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue, P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValueLength)  /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = FVM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Std_ReturnType ret = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  if(!FvM_IsInitialized())
  {
    errorId = FVM_E_UNINIT;
  }
# if(FVM_DEV_ERROR_DETECT == STD_ON)    /* COV_FVM_VAR_DEV_ERROR_DETECT */
  else if(SecOCFreshnessValueID >= FvM_GetSizeOfTxProcessingInfo())
  {
    errorId = FVM_E_PARAM;
  }
#  if (FVM_INVALIDHNDOFTXPROCESSINGINFO == STD_ON)
  else if(FvM_IsInvalidHndOfTxProcessingInfo(SecOCFreshnessValueID))
  {
    errorId = FVM_E_PARAM;
  }
#  endif
  else if(SecOCFreshnessValue == NULL_PTR)
  {
    errorId = FVM_E_PARAM_POINTER;
  }
  else if(SecOCFreshnessValueLength == NULL_PTR)
  {
    errorId = FVM_E_PARAM_POINTER;
  }
  else if(SecOCTruncatedFreshnessValue == NULL_PTR)
  {
    errorId = FVM_E_PARAM_POINTER;
  }
  else if(SecOCTruncatedFreshnessValueLength == NULL_PTR)
  {
    errorId = FVM_E_PARAM_POINTER;
  }
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if(FVM_TXFRESHNESSVALUEINFOUSEDOFTXPROCESSINGINFO == STD_ON)
    if(FvM_IsTxFreshnessValueInfoUsedOfTxProcessingInfo(SecOCFreshnessValueID)) /* PRQA S 2741 */ /* MD_FvM_2741 */ /* COV_FVM_NO_MASTER_CONF */
    {
      FvM_TxFreshnessValueInfoIdxOfTxProcessingInfoType txFreshnessValueInfoIdx = FvM_GetTxFreshnessValueInfoIdxOfTxProcessingInfo(SecOCFreshnessValueID);
      ret = E_OK; /* PRQA S 2982 */ /* MD_FvM_2982 */
#  if(FVM_DEV_ERROR_DETECT == STD_ON)    /* COV_FVM_VAR_DEV_ERROR_DETECT */
      if(*SecOCFreshnessValueLength != ((uint32) (FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(FvM_GetFreshnessValueLayoutInfoLatestIdxOfTxFreshnessValueInfo(txFreshnessValueInfoIdx))) << 3u))
      {
        errorId = FVM_E_PARAM;
        ret = E_NOT_OK;
      }
      else if(FvM_FVJaspar_GetLengthInBytes(*SecOCTruncatedFreshnessValueLength) > FvM_GetFreshnessValueArrayTruncatedFreshnessValueLengthOfFreshnessValueLayoutInfo(FvM_GetFreshnessValueLayoutInfoLatestIdxOfTxFreshnessValueInfo(txFreshnessValueInfoIdx)))
      {
        errorId = FVM_E_PARAM;
        ret = E_NOT_OK;
      }
      else
#  endif
      {
       SchM_Enter_FvM_FVM_EXCLUSIVE_AREA_TX_FRESHNESS();
        switch (FvM_GetProcessingTypeOfTxFreshnessValueInfo(txFreshnessValueInfoIdx))
        {
#  if (FVM_TX_JASPAR_FRESHNESS_USED == STD_ON)
          case FVM_JASPAR_FRESHNESS_PROCESSINGTYPEOFTXFRESHNESSVALUEINFO:
          {
            ret = FvM_FVJaspar_TxProcessing_Jaspar(txFreshnessValueInfoIdx, SecOCFreshnessValue, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength); /* SBSW_FVM_CHECKED_POINTER_1 */
          }
          break;
#  endif
#  if (FVM_TX_JASPAR_WITHOUT_RESET_FRESHNESS_USED == STD_ON)
          case FVM_JASPAR_FRESHNESS_WITHOUT_RESET_COUNTER_PROCESSINGTYPEOFTXFRESHNESSVALUEINFO:
          {
            FvM_FVJaspar_TxProcessing_JasparWithoutResetCounter(txFreshnessValueInfoIdx, SecOCFreshnessValue, SecOCTruncatedFreshnessValue);        /* SBSW_FVM_CHECKED_POINTER_1 */
          }
          break;
#  endif
          default: /* COV_FVM_MISRA */
            /* do nothing */
            break;
        }
        SchM_Exit_FvM_FVM_EXCLUSIVE_AREA_TX_FRESHNESS();
      }
    }
    else
# endif
    {
# if (FVM_RESETCOUNTERCYCLETIMECOUNTER == STD_ON)
      FvM_ResetCounterBitSizeType tripResetSyncBitCount = FvM_GetTripCounterBitSize() + FvM_GetResetCounterBitSize();
      if((*SecOCFreshnessValueLength >= *SecOCTruncatedFreshnessValueLength) && (*SecOCTruncatedFreshnessValueLength >= tripResetSyncBitCount))
      {
        uint8 tripCounterByteArray[FVM_SIZEOF_UINT32];
        uint8 resetCounterByteArray[FVM_SIZEOF_UINT64];
        uint32 freshnessValueByteLength = FvM_FVJaspar_GetLengthInBytes(*SecOCFreshnessValueLength);
        uint8 tripCounterOffset = FvM_FVJaspar_GetOffsetInBits(tripResetSyncBitCount);

        SchM_Enter_FvM_FVM_EXCLUSIVE_AREA_TX_FRESHNESS();

        FvM_FVJaspar_SetInteger32(FVM_SIZEOF_UINT32, FvM_GetLatestTripCounter(), tripCounterByteArray); /* SBSW_FVM_FUNC_CALL_ARRAY_WRITE */
        FvM_FVJaspar_BitCopy(SecOCFreshnessValue, freshnessValueByteLength, tripCounterOffset, tripCounterByteArray, (FVM_SIZEOF_UINT32 * 8u) - FvM_GetTripCounterBitSize(), FvM_GetTripCounterBitSize()); /* SBSW_FVM_FUNC_CALL */

        FvM_FVJaspar_SetInteger64(FVM_SIZEOF_UINT64, FvM_GetLatestResetCounter(), resetCounterByteArray); /* SBSW_FVM_FUNC_CALL_ARRAY_WRITE */
        FvM_FVJaspar_BitCopy(SecOCFreshnessValue, freshnessValueByteLength, tripCounterOffset + FvM_GetTripCounterBitSize(), resetCounterByteArray, (FVM_SIZEOF_UINT64 * 8u) - FvM_GetResetCounterBitSize(), FvM_GetResetCounterBitSize()); /* SBSW_FVM_FUNC_CALL */

        VStdMemCpyRamToRam(SecOCTruncatedFreshnessValue,      /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_SECOC_MEM_CPY_RAM2RAM */
                           SecOCFreshnessValue, freshnessValueByteLength);
        SchM_Exit_FvM_FVM_EXCLUSIVE_AREA_TX_FRESHNESS();
        ret = E_OK;
      }
      else
      {
        errorId = FVM_E_PARAM;
        ret = E_NOT_OK;
      }
# endif
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if(FVM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != FVM_E_NO_ERROR)
  {
    (void) Det_ReportError(FVM_MODULE_ID, FVM_INSTANCE_ID_DET, FVM_SID_GET_TX_FRESHNESS, errorId);
  }
# endif

  FVM_DUMMY_STATEMENT(SecOCFreshnessValueID);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  FVM_DUMMY_STATEMENT(SecOCTruncatedFreshnessValueLength);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  FVM_DUMMY_STATEMENT(SecOCFreshnessValueLength);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  FVM_DUMMY_STATEMENT(SecOCTruncatedFreshnessValue);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  FVM_DUMMY_STATEMENT(SecOCFreshnessValue);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  FVM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return ret;
}  /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if(FVM_TXPROCESSINGINFO == STD_ON)
/**********************************************************************************************************************
 *  SecOC_SPduTxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FVM_CODE) SecOC_SPduTxConfirmation(uint16 SecOCFreshnessValueID)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = FVM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  if(!FvM_IsInitialized())
  {
    errorId = FVM_E_UNINIT;
  }
# if(FVM_DEV_ERROR_DETECT == STD_ON)    /* COV_FVM_VAR_DEV_ERROR_DETECT */
  else if(SecOCFreshnessValueID >= FvM_GetSizeOfTxProcessingInfo())
  {
    errorId = FVM_E_PARAM;
  }
#  if (FVM_INVALIDHNDOFTXPROCESSINGINFO == STD_ON)
  else if(FvM_IsInvalidHndOfTxProcessingInfo(SecOCFreshnessValueID))
  {
    errorId = FVM_E_PARAM;
  }
#  endif
# endif
  else
  {
# if(FVM_TXFRESHNESSVALUEINFOUSEDOFTXPROCESSINGINFO == STD_ON)
    if(FvM_IsTxFreshnessValueInfoUsedOfTxProcessingInfo(SecOCFreshnessValueID)) /* PRQA S 2741 */ /* MD_FvM_2741 */ /* COV_FVM_NO_MASTER_CONF */
    {
      FvM_TxFreshnessValueInfoIdxOfTxProcessingInfoType txFreshnessValueInfoIdx = FvM_GetTxFreshnessValueInfoIdxOfTxProcessingInfo(SecOCFreshnessValueID);
      SchM_Enter_FvM_FVM_EXCLUSIVE_AREA_TX_FRESHNESS();
      {
        FvM_FreshnessValueLayoutInfoIterType previousFreshnessValueIdx = (FvM_FreshnessValueLayoutInfoIterType) FvM_GetFreshnessValueLayoutInfoPreviousIdxOfTxFreshnessValueInfo(txFreshnessValueInfoIdx);
        FvM_FreshnessValueLayoutInfoIterType latestFreshnessValueIdx = (FvM_FreshnessValueLayoutInfoIterType) FvM_GetFreshnessValueLayoutInfoLatestIdxOfTxFreshnessValueInfo(txFreshnessValueInfoIdx);
        VStdMemCpyRamToRam(FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(previousFreshnessValueIdx)), FvM_GetAddrFreshnessValueArray(FvM_GetFreshnessValueArrayCompleteFreshnessStartIdxOfFreshnessValueLayoutInfo(latestFreshnessValueIdx)), FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(previousFreshnessValueIdx));     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_FVM_CSL03 */
      }
      SchM_Exit_FvM_FVM_EXCLUSIVE_AREA_TX_FRESHNESS();
    }
# endif
  }
  /* ----- Development Error Report --------------------------------------- */
# if(FVM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != FVM_E_NO_ERROR)
  {
    (void) Det_ReportError(FVM_MODULE_ID, FVM_INSTANCE_ID_DET, FVM_SID_TX_FRESHNESS_CONFIRMATION, errorId);
  }
# endif
  FVM_DUMMY_STATEMENT(SecOCFreshnessValueID);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  FVM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if(FVM_RXFRESHNESSVALUEINFO == STD_ON)
/**********************************************************************************************************************
 *  SecOC_GetRxFreshness()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, FVM_CODE) SecOC_GetRxFreshness(uint16 SecOCFreshnessValueID, P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength, uint16 SecOCAuthVerifyAttempts, P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue, P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength)  /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = FVM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Std_ReturnType ret = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  if(!FvM_IsInitialized())
  {
    errorId = FVM_E_UNINIT;
  }
# if(FVM_DEV_ERROR_DETECT == STD_ON)    /* COV_FVM_VAR_DEV_ERROR_DETECT */
  else if(SecOCFreshnessValueID >= FvM_GetSizeOfRxFreshnessValueInfo())
  {
    errorId = FVM_E_PARAM;
  }
#  if(FVM_INVALIDHNDOFRXFRESHNESSVALUEINFO == STD_ON)
  else if(FvM_IsInvalidHndOfRxFreshnessValueInfo(SecOCFreshnessValueID))
  {
    errorId = FVM_E_PARAM;
  }
#  endif
  else if(SecOCTruncatedFreshnessValue == NULL_PTR)
  {
    errorId = FVM_E_PARAM_POINTER;
  }
  else if(SecOCFreshnessValue == NULL_PTR)
  {
    errorId = FVM_E_PARAM_POINTER;
  }
  else if(SecOCFreshnessValueLength == NULL_PTR)
  {
    errorId = FVM_E_PARAM_POINTER;
  }
  else if(*SecOCFreshnessValueLength != ((uint32) (FvM_GetFreshnessValueArrayCompleteFreshnessLengthOfFreshnessValueLayoutInfo(FvM_GetFreshnessValueLayoutInfoLatestIdxOfRxFreshnessValueInfo(SecOCFreshnessValueID))) << 3u))
  {
    errorId = FVM_E_PARAM;
  }
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_FvM_FVM_EXCLUSIVE_AREA_RX_FRESHNESS();
    ret = FvM_FVJaspar_ProcessRxMessage(SecOCFreshnessValueID, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength, SecOCAuthVerifyAttempts, SecOCFreshnessValue); /* SBSW_FVM_FUNC_CALL */
    SchM_Exit_FvM_FVM_EXCLUSIVE_AREA_RX_FRESHNESS();
  }

  /* ----- Development Error Report --------------------------------------- */
# if(FVM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != FVM_E_NO_ERROR)
  {
    (void) Det_ReportError(FVM_MODULE_ID, FVM_INSTANCE_ID_DET, FVM_SID_GET_RX_FRESHNESS, errorId);
  }
# endif


  FVM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  FVM_DUMMY_STATEMENT(SecOCFreshnessValueLength);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  FVM_DUMMY_STATEMENT(SecOCAuthVerifyAttempts); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  FVM_DUMMY_STATEMENT(SecOCTruncatedFreshnessValueLength);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return ret;
}  /* PRQA S 6030, 6050, 6060, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPAR, MD_MSR_STMIF */
#endif

#if (FVM_MAINFUNCTION_API == STD_ON)
/**********************************************************************************************************************
  FvM_MainFunction
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, FVM_CODE) FvM_MainFunction(void)
{
  if(FvM_IsInitialized())
  {
# if (FVM_STARTUPCYCLECOUNTER == STD_ON)
    if(FvM_GetStartUpCycleCounter() != 0u)
    {
      FvM_DecStartUpCycleCounter();     /* SBSW_FVM_CSL_VAR_ACCESS */
      if(FvM_GetStartUpCycleCounter() == 0u)
      {
#  if (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
        FvM_FVJaspar_SetVerifyOverrideStatus(SECOC_OVERRIDE_VERIFICATION_STATUS_CANCEL);
#  endif
#  if (FVM_SYNCSTATE == STD_ON)
        if(FvM_GetSyncState() == FVM_INITIAL_OUT_OF_SYNC_SYNCSTATE)
        {
          FvM_SetSyncState(FVM_INVALID_OUT_OF_SYNC_SYNCSTATE);  /* SBSW_FVM_CSL_VAR_ACCESS */
        }
#  endif
      }
    }
# endif

# if (FVM_SYNCMESSAGERECEPTIONTIMEOUTCOUNTER == STD_ON)
    SchM_Enter_FvM_FVM_EXCLUSIVE_AREA_SYNC_STATE();

    FvM_DecSyncMessageReceptionTimeoutCounter();        /* SBSW_FVM_CSL_VAR_ACCESS */
    if(FvM_GetSyncMessageReceptionTimeoutCounter() == 0u)
    {
      FvM_SetSyncMessageReceptionTimeoutCounter(FvM_GetSyncMessageReceptionTimeoutCnt());       /* SBSW_FVM_CSL_VAR_ACCESS */
      SchM_Exit_FvM_FVM_EXCLUSIVE_AREA_SYNC_STATE();
      (void) Dem_SetEventStatus(FvM_GetDemEventIdReference(0), DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      SchM_Exit_FvM_FVM_EXCLUSIVE_AREA_SYNC_STATE();
    }
# endif

# if (FVM_RECEPTIONTIMEOUTFORTRANSMISSIONCOUNTER == STD_ON)
    SchM_Enter_FvM_FVM_EXCLUSIVE_AREA_SYNC_STATE();
    if(FvM_GetReceptionTimeoutForTransmissionCounter() != 0u)
    {
      FvM_DecReceptionTimeoutForTransmissionCounter();  /* SBSW_FVM_CSL_VAR_ACCESS */
    }
    SchM_Exit_FvM_FVM_EXCLUSIVE_AREA_SYNC_STATE();
# endif

# if (FVM_RESETCOUNTERCYCLETIMECOUNTER == STD_ON)
    FvM_DecResetCounterCycleTimeCounter(); /* SBSW_FVM_CSL_VAR_ACCESS */
    if(FvM_GetResetCounterCycleTimeCounter() == 0u)
    {
      FvM_SetResetCounterCycleTimeCounter(FvM_GetResetCounterCycleTime()); /* SBSW_FVM_CSL_VAR_ACCESS */
      /* increment Reset Counter and update Signals */
      SchM_Enter_FvM_FVM_EXCLUSIVE_AREA_BOTH_FRESHNESS();
      FvM_IncLatestResetCounter(); /* SBSW_FVM_CSL_VAR_ACCESS */
      SchM_Exit_FvM_FVM_EXCLUSIVE_AREA_BOTH_FRESHNESS();
    }
# endif
  }
}
#endif

#if (FVM_STARTUPCYCLECOUNTER == STD_ON)
/**********************************************************************************************************************
  FvM_RestartStartUpAcceptanceTime
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(void, FVM_CODE) FvM_RestartStartUpAcceptanceTime(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = FVM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* ----- Development Error Checks ------------------------------------- */
  if(!FvM_IsInitialized())
  {
    errorId = FVM_E_UNINIT;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    FvM_SetStartUpCycleCounter(FvM_GetStartUpCycleCnt());       /* SBSW_FVM_CSL_VAR_ACCESS */
# if (FVM_RX_JASPAR_FRESHNESS_USED == STD_ON)
    FvM_FVJaspar_SetVerifyOverrideStatus(SECOC_OVERRIDE_VERIFICATION_STATUS_PASS_UNTIL_NOTICE);
# endif
# if (FVM_SYNCSTATE == STD_ON)
    FvM_SetSyncState(FVM_INITIAL_OUT_OF_SYNC_SYNCSTATE);        /* SBSW_FVM_CSL_VAR_ACCESS */
# endif
  }
  /* ----- Development Error Report --------------------------------------- */
# if(FVM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != FVM_E_NO_ERROR)
  {
    (void) Det_ReportError(FVM_MODULE_ID, FVM_INSTANCE_ID_DET, FVM_SID_FVM_RESTART_START_UP_ACCEPTANCE_TIME, errorId);
  }
# endif
  FVM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if(FVM_DEVMODEENABLED == STD_ON)
/***********************************************************************************************************************
 *  FvM_SetDevelopmentMode()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
FUNC(void, FVM_CODE) FvM_SetDevelopmentMode(boolean enableDevMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = FVM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  if(!FvM_IsInitialized())
  {
    errorId = FVM_E_UNINIT;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    FvM_SetDevModeEnabled(enableDevMode);       /* SBSW_FVM_CSL_VAR_ACCESS */
  }
  /* ----- Development Error Report --------------------------------------- */
# if(FVM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != FVM_E_NO_ERROR)
  {
    (void) Det_ReportError(FVM_MODULE_ID, FVM_INSTANCE_ID_DET, FVM_SID_SET_DEVELOPMENT_MODE, errorId);
  }
# endif

  FVM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (FVM_LATESTTRIPCOUNTER == STD_ON)
/***********************************************************************************************************************
 *  FvM_ResetTripAndResetCounter()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
FUNC(void, FVM_CODE) FvM_ResetTripAndResetCounter(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = FVM_E_NO_ERROR;       /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  if(!FvM_IsInitialized())
  {
    errorId = FVM_E_UNINIT;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    FvM_SetLatestTripCounter(0);        /* SBSW_FVM_CSL_VAR_ACCESS */
    FvM_SetLatestResetCounter(0);       /* SBSW_FVM_CSL_VAR_ACCESS */

# if (FVM_FRESHNESSVALUEARRAY == STD_ON)
    VStdMemClr(FvM_GetAddrFreshnessValueArray(0), FvM_GetSizeOfFreshnessValueArray());  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_FVM_MEM_CPY_CLR */
# endif
# if(FVM_TRIPCOUNTERNVMBLOCKDESCRIPTOR == STD_ON)
    (void) NvM_WriteBlock(FvM_GetTripCounterNvMBlockDescriptor(0), &FvM_GetLatestTripCounter());        /* PRQA S 0315 */ /* MD_FvM_0315_NvMWriteBlock */ /* SBSW_FVM_FUNC_CALL */
# endif
  }
  /* ----- Development Error Report --------------------------------------- */
# if(FVM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != FVM_E_NO_ERROR)
  {
    (void) Det_ReportError(FVM_MODULE_ID, FVM_INSTANCE_ID_DET, FVM_SID_RESET_TRIP_AND_RESET_COUNTER, errorId);
  }
# endif

  FVM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif


#if (FVM_LATESTTRIPCOUNTERWITHOUTRESETCOUNTER == STD_ON)
/***********************************************************************************************************************
 *  FvM_TripCounterReadErrorDetected()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
FUNC(void, FVM_CODE) FvM_TripCounterReadErrorDetected(void)
{
  FvM_SetTripCounterReadErrorDetectedFlag(TRUE); /* SBSW_FVM_CSL_VAR_ACCESS */
}
#endif

#define FVM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:

  MD_FvM_0315_NvMWriteBlock: Misra Dir 1.1
     Reason:      The function 'NvM_WriteBlock' from the NVRAM Manager has a void pointer as a function parameter.
     Risk:        No risk, because the underlying pointer type is known.
     Prevention:  No prevention necessary.

  MD_FvM_2985_ClearAcceptanceWindow: Misra Rule 2.2
     Reason:      If the ClearAcceptanceWindow is 0 the operation has no effect.
     Risk:        No risk.
     Prevention:  No prevention necessary.

  MD_FvM_2991: Misra Rule 14.3
     Reason:      The value of the if-controlling expression depends on the configuration.
     Risk:        No risk.
     Prevention:  No prevention necessary.

  MD_FvM_2741: Misra Rule 14.3
     Reason:      The value of the if-controlling expression depends on the configuration.
     Risk:        No risk.
     Prevention:  No prevention necessary.

  MD_FvM_2982: Misra Rule 2.2
     Reason:      Dependent on the configuration the value of the object is never being used before modified.
     Risk:        No risk.
     Prevention:  No prevention necessary.

  MD_FvM_2986_BitCopy: Misra Rule 2.2
     Reason:      The assignment is not unnecessary, it depends on external parameters which can change. This QAC message is a false-positive.
     Risk:        No risk.
     Prevention:  No prevention necessary.
*/
/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_FVM_CSL03
    \DESCRIPTION Access to Table1 via indirection over Table2.
    \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

  \ID SBSW_FVM_CONST_POINTER
    \DESCRIPTION Pointer is handed over to a function
    \COUNTERMEASURE \N The pointer references a constant memory location (P2CONST). Therefore it can not be written.

  \ID SBSW_FVM_CHECKED_POINTER
    \DESCRIPTION Pointer write access
    \COUNTERMEASURE \R It is checked at runtime that the pointer is no NULL_PTR. The caller has to ensure that the pointer references a valid memory location.

  \ID SBSW_FVM_CHECKED_POINTER_1
    \DESCRIPTION Pointer is handed over to a function
    \COUNTERMEASURE \R It is checked at runtime that the pointer is no NULL_PTR. The caller has to ensure that the pointer references a valid memory location.
                       The length of the buffer is checked for sufficient length.

  \ID SBSW_FVM_MEM_CPY_CLR
    \DESCRIPTION A Pointer is handed to a function to clear the corresponding memory.
    \COUNTERMEASURE \N The address is read via a ComStackLib macro and is valid. The corresponding size is also read via the corresponding ComStackLib macro and ensures that only the correct length is cleared.

  \ID SBSW_FVM_CSL_FCT_PTR
    \DESCRIPTION A Function Pointer is called.
    \COUNTERMEASURE \N The function pointer is read using a ComStackLib macro and is therefore valid. Only one function pointer is written to the corresponding table, therefore it can always be read using index 0.

  \ID SBSW_SECOC_MEM_CPY_RAM2RAM
    \DESCRIPTION Call to copy RAM data to RAM
    \COUNTERMEASURE \R The passed pointers are either read by ComStackLib macros or are passed through and checked at the beginning of the function. The caller has to ensure that it references a valid memory location.
                    \R The size of the copy operation is checked against the freshness value length provided by the caller.

  \ID SBSW_FVM_CSL_VAR_ACCESS
    \DESCRIPTION A ComStackLib generated variable is accessed.
    \COUNTERMEASURE \N The variable is written using a generated macro of the CSL. It immediately dereferences the variables address without pointer arithmetic.

  \ID SBSW_FVM_FUNC_CALL
    \DESCRIPTION A Function is called.
    \COUNTERMEASURE \N The passed parameter are read via a ComStackLib macro and are valid.

  \ID SBSW_FVM_FUNC_CALL_ARRAY_WRITE
    \DESCRIPTION A Function is called.
    \COUNTERMEASURE \N The caller must ensure that the used counter index and buffer are matching and do not exceed the available buffer size.

  \ID SBSW_FVM_BITCOPY_ARRAY_WRITE
    \DESCRIPTION The array dst is written with index dstIdx.
    \COUNTERMEASURE \N The access is in a loop, the end criterion parameter is checked with
                       a runtime check against the function parameter dstLength. The caller
                       must ensure this parameter value matches the size of the available
                       buffer in dst.

  \ID SBSW_FVM_SET_INTEGER
    \DESCRIPTION The buffer array is written with index counterVar.
    \COUNTERMEASURE \N The caller must ensure that the index used for the buffer array does not exceed the buffer size.

   SBSW_JUSTIFICATION_END */
/* START_COVERAGE_JUSTIFICATION

  \ID COV_FVM_VAR_DEV_ERROR_DETECT
    \ACCEPT TX
    \REASON Det error detection must always be enabled for SafeBsw.

  \ID COV_FVM_VAR_DEPENDENT_SWITCH
    \ACCEPT TX
    \REASON The nested switch depends on a previous switch.

  \ID COV_FVM_MISRA
    \ACCEPT X
    \ACCEPT XF
    \REASON [MSR_COV_MISRA]

   \ID COV_FVM_ALWAYS_TRUE_MISRA
    \ACCEPT TX
    \REASON [MSR_COV_MISRA]

   \ID COV_FVM_2BIT_RESET_FLAG
    \ACCEPT TX
    \REASON In configurations with 2 bit reset flag the evaluation will always be successful.

   \ID COV_FVM_BYTE_LENGTH
    \ACCEPT XF
    \ACCEPT TX
    \REASON Due to the configuration the result always evaluates one way.

   \ID COV_FVM_WITHOUT_RESETCOUNTER_TX
    \ACCEPT TX
    \REASON The statement is always true if only Without ResetCounter processings exist.

   \ID COV_FVM_ALWAYS_TRUE_TRIP_FLAG
    \ACCEPT TX
    \REASON Due to the Specification the else is required.

   \ID COV_FVM_ALWAYS_TRUE_DEF_PROGRAMMING
    \ACCEPT TX
    \REASON Due to defensive programming.

   \ID COV_FVM_NO_MASTER_CONF
    \ACCEPT TX
    \REASON The FvM has not the role master.

  \ID COV_FVM_REST_COUNTER_MAX_IN_MASTER_CONF
    \ACCEPT XF
    \REASON The FvM has the role master and the reset counter cannot be reached in acceptable time.

  \ID COV_FVM_DEFENSIVE_PROGRAMMING
    \ACCEPT TX
    \REASON Defensive programming. Condition will always evaluate to TRUE.

  \ID COV_FVM_TRIP_CNT_SEPARATE_MSG
    \ACCEPT XF
    \ACCEPT TF tx tf
    \ACCEPT XF
    \ACCEPT XX xx xx
    \REASON In configuations with only separate messages, latest trip counter will always be received trip counter.

  \ID COV_FVM_BITCOPY_DEFENSIVE_PROGRAMMING
    \ACCEPT XF
    \REASON Destination bit offset + number of bits shall never be greater than the length of the destination the value is copied to.

  \ID COV_FVM_TRIP_RESET_CNT_BITSIZE
    \ACCEPT XF
    \ACCEPT TX
    \REASON The condition depends on the configured bitsize of trip and reset counter and might not be fully covered.

END_COVERAGE_JUSTIFICATION
*/


/**********************************************************************************************************************
 *  END OF FILE: FvM.c
 *********************************************************************************************************************/
