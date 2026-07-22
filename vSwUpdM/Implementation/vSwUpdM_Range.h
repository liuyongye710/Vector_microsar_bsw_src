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
/*!        \file  vSwUpdM_Range.h
 *        \brief  vSwUpdM range implementation header file
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#ifndef VSWUPDM_RANGE_H
#define VSWUPDM_RANGE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vSwUpdM_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vSwUpdM_Range_IsRangeValid()
 *********************************************************************************************************************/
/*! \brief       Checks if the specified range is valid.
 *  \details     -
 *  \param[in]   StartAddress  The start address of the range to be verified.
 *  \param[in]   Length        The length of the range to be verified.
 *  \return      FALSE         Handle is invalid.
 *  \return      TRUE          Handle is valid.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     range
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Range_IsRangeValid(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 *  vSwUpdM_Range_AlignAddress()
 *********************************************************************************************************************/
/*! \brief       Align address to memory device constraints.
 *  \details     -
 *  \param[in,out] Address     Input: The address to be aligned. Output: The aligned address.
 *  \param[in]   Alignment     VSWUPDM_ADDRESS_ALIGNMENT_FRONT: Align address to front of range defined by device constraint.
 *                             VSWUPDM_ADDRESS_ALIGNMENT_BACK: Align address to end of range defined by device constraint.
 *  \param[in]   Granularity   VSWUPDM_ALIGN_GRANULARITY_PAGE: Align address to page size of device.
 *                             VSWUPDM_ALIGN_GRANULARITY_SECTOR: Align address to sector size of device.
 *  \return      E_OK          Address successfully aligned.
 *  \return      else          Alignment of address failed, e.g. because no device mapped to it.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     range
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Range_AlignAddress(
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_CONST) Address,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_AddressAlignmentType Alignment,
  vSwUpdM_AlignGranularityType Granularity);

/**********************************************************************************************************************
 *  vSwUpdM_Range_TrimLength()
 *********************************************************************************************************************/
/*! \brief       Align address to memory device constraints.
 *  \details     -
 *  \param[in,out] Address     Input: The address to be aligned. Output: The aligned address.
 *  \param[in]   Alignment     VSWUPDM_ADDRESS_ALIGNMENT_FRONT: Align address to front of range defined by device constraint.
 *                             VSWUPDM_ADDRESS_ALIGNMENT_BACK: Align address to end of range defined by device constraint.
 *  \param[in]   Granularity   VSWUPDM_ALIGN_GRANULARITY_PAGE: Align address to page size of device.
 *                             VSWUPDM_ALIGN_GRANULARITY_SECTOR: Align address to sector size of device.
 *  \return      E_OK          Address successfully aligned.
 *  \return      else          Alignment of address failed, e.g. because no device mapped to it.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     range
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Range_TrimLength(
  P2VAR(vSwUpdM_LengthType, AUTOMATIC, VSWUPDM_APPL_CONST) Length,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_AddressType Address,
  vSwUpdM_AlignGranularityType Granularity,
  vSwUpdM_TrimTypeType TrimType);

/**********************************************************************************************************************
 *  vSwUpdM_Range_IsAddressInRange()
 *********************************************************************************************************************/
/*! \brief       Checks if a address lies within the given range.
 *  \details     -
 *  \param[in]   Address            The address which should be checked against the reference range.
 *  \param[in]   RangeStartAddress  The start address of the reference range.
 *  \param[in]   RangeLength        The length of the reference range.
 *  \return      FALSE              Address doesn't lie within the range.
 *  \return      TRUE               Address lies within the range.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Range_IsAddressInRange(
  vSwUpdM_AddressType Address,
  vSwUpdM_AddressType RangeStartAddress,
  vSwUpdM_LengthType RangeLength);

/**********************************************************************************************************************
 *  vSwUpdM_Range_CheckAgainstRange()
 *********************************************************************************************************************/
/*! \brief       Checks if a range lies within another range.
 *  \details     -
 *  \param[in]   StartAddress       The start address of the range which should be checked against the reference range.
 *  \param[in]   Length             The length of the range  which should be checked against the reference range.
 *  \param[in]   RangeStartAddress  The start address of the reference range.
 *  \param[in]   RangeLength        The length of the reference range.
 *  \return      VSWUPDM_RANGE_CHECK_MISMATCH       The ranges don't overlap at all.
 *  \return      VSWUPDM_RANGE_CHECK_CONTAINED      The range completely lies within the reference range.
 *  \return      VSWUPDM_RANGE_CHECK_OVERLAP_START  The range partially overlaps the start of the reference range.
 *  \return      VSWUPDM_RANGE_CHECK_OVERLAP_END    The range partially overlaps the end of the reference range.
 *  \return      TRUE               Address lies within range.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
FUNC(vSwUpdM_RangeCheckType, VSWUPDM_CODE) vSwUpdM_Range_CheckAgainstRange(
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length,
  vSwUpdM_AddressType RangeStartAddress,
  vSwUpdM_LengthType RangeLength);

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_RANGE_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Range.h
 *********************************************************************************************************************/
