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
/*!        \file  vSwUpdM_Range.c
 *        \brief  vSwUpdM range implementation source file
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

#define VSWUPDM_RANGE_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "vSwUpdM_Priv.h"
#include "vSwUpdM_Range.h"

#include "vSwUpdM_Lcfg.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/*! Align address to front of range defined by bitmask (must be 2^n - 1, e.g. 0x00FF).
  E.g. 0x123 with a mask of 0xFF will return 0x100. */
#define VSWUPDM_ALIGN_ADDRESS_FRONT(address, mask)    (((address) | (mask)) ^ (mask))
/*! Align address to end of range defined by bitmask (must be 2^n - 1, e.g. 0x00FF).
  E.g. 0x123 with a mask of 0xFF will return 0x1FF. */
#define VSWUPDM_ALIGN_ADDRESS_END(address, mask)      ((address) | (mask))

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_Range_IsRangeValid
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
/* PRQA S 3219 3 */ /* MD_MSR_Unreachable */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Range_IsRangeValid(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length)
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean                 retVal = FALSE;
  vMemAccM_MemoryInfoType memoryInfo;
  vSwUpdM_LengthType      length;

  /* ----- Implementation ------------------------------------------------- */
  length = Length;
  /* #10 If length is equal to zero, indicating that only address is relevant
   *   Set to one, to handle special case. */
  if (length == 0u)
  {
    length = 1u;
  }

  /* #20 If memory information for given range can successfully be evaluated for opened partition
   *   Memory range is mapped in partition and thus valid. */
  if (vMemAccM_GetMemoryInfo(vSwUpdM_GetVarPartitions(PartitionId).AddrAreaIdOfPartitions, StartAddress, length, &memoryInfo) == E_OK)
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_Range_IsRangeValid */

/**********************************************************************************************************************
 * vSwUpdM_Range_AlignAddress
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
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Range_AlignAddress(
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_CONST) Address,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_AddressAlignmentType Alignment,
  vSwUpdM_AlignGranularityType Granularity)
{
  Std_ReturnType result = VSWUPDM_E_MEM_UNMAPPED;

  if (Granularity == VSWUPDM_ALIGN_GRANULARITY_NONE)
  {
    result = E_OK;
  }
  else
  {
    vMemAccM_MemoryInfoType memoryInfo;
    vSwUpdM_LengthType      alignSize;
    vSwUpdM_AddressType     alignMask;
    vSwUpdM_AddressType     virtualAddress;
    vSwUpdM_AddressType     physicalAddress;
    vSwUpdM_AddressType     alignedPhysAddress;
    vSwUpdM_LengthType      offset;

    virtualAddress = *Address;

    /* #10 Evaluate memory information for given address (with a length of one) for opened partition. */
    if (vMemAccM_GetMemoryInfo(vSwUpdM_GetVarPartitions(PartitionId).AddrAreaIdOfPartitions, virtualAddress, 1u, &memoryInfo) == E_OK)
    {
      /* #20 Use page or sector size for alignment, based on requested granularity. */
      if (Granularity == VSWUPDM_ALIGN_GRANULARITY_PAGE)
      {
        alignSize = memoryInfo.PageSize;
      }
      else
      {
        alignSize = memoryInfo.SectorSize;
      }

      /* #30 Physical address must be used for alignment.
       *   Calculate it for the given virtual address. */
      offset = virtualAddress - memoryInfo.VirtualStartAddress;
      physicalAddress = memoryInfo.PhysicalStartAddress + offset;

      /* #40 Calculate alignment bitmask from alignment size.
       *   Alignment size must be a power of two. */
      alignMask = (alignSize - 1u);

      /* #50 Align physical address to end of range, by setting all bits defined by mask. */
      alignedPhysAddress = physicalAddress | alignMask;

      /* #60 If address shall be aligned to front of range */
      if (Alignment == VSWUPDM_ADDRESS_ALIGNMENT_FRONT)
      {
        /* #70 Align physical address to front of range, by clearing all bits defined by mask. */
        alignedPhysAddress ^= alignMask;
        /* #80 Calculate offset between original and aligned physical address and apply it to virtual address. */
        offset = physicalAddress - alignedPhysAddress;
        virtualAddress -= offset;
      }
      /* #100 Otherwise */
      else
      {
        /* #110 Calculate offset between original and aligned physical address and apply it to virtual address. */
        offset = alignedPhysAddress - physicalAddress;
        virtualAddress += offset;
      }

      /* #200 Return aligned virtual address. */
      *Address = virtualAddress;

      result = E_OK;
    }
  }

  return result;
} /* vSwUpdM_Range_AlignAddress */

/**********************************************************************************************************************
 * vSwUpdM_Range_TrimLength
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Range_TrimLength(
  P2VAR(vSwUpdM_LengthType, AUTOMATIC, VSWUPDM_APPL_CONST) Length,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_AddressType Address,
  vSwUpdM_AlignGranularityType Granularity,
  vSwUpdM_TrimTypeType TrimType)
{
  Std_ReturnType          retVal          = VSWUPDM_E_MEM_UNMAPPED;
  vSwUpdM_TrimTypeType    trimType        = TrimType;
  vMemAccM_MemoryInfoType memoryInfo;
  vSwUpdM_LengthType      minAlignSize;
  vSwUpdM_LengthType      maxAlignSize;
  vSwUpdM_LengthType      alignSize       = 0u;
  vSwUpdM_AddressType     minAlignMask;
  vSwUpdM_AddressType     maxAlignMask;
  vSwUpdM_AddressType     alignMask       = 0u;
  vSwUpdM_AddressType     physicalAddress;
  vSwUpdM_LengthType      offset;
  vSwUpdM_AddressType     virtualAddress  = Address;
  vSwUpdM_LengthType      length          = *Length;

  /* #10 Evaluate memory information for given range for opened partition. */
  if (vMemAccM_GetMemoryInfo(vSwUpdM_GetVarPartitions(PartitionId).AddrAreaIdOfPartitions, virtualAddress, length, &memoryInfo) == E_OK)
  {
    retVal = E_OK;

    /* #20 Use page or sector size for alignment, based on requested granularity.
     *   Same for potential burst modes. */
    if (Granularity == VSWUPDM_ALIGN_GRANULARITY_PAGE)
    {
      minAlignSize = memoryInfo.PageSize;
      maxAlignSize = memoryInfo.PageBurstSize;
    }
    else
    {
      minAlignSize = memoryInfo.SectorSize;
      maxAlignSize = memoryInfo.SectorBurstSize;
    }

    /* #30 Calculate alignment bitmask from minimum (non-burst) and maximum (burst) alignment size.
     *   Alignment size must be a power of two. */
    minAlignMask = (minAlignSize - 1u);
    maxAlignMask = (maxAlignSize - 1u);

    /* #40 Physical address must be used for alignment.
     *   Calculate it for the given virtual address. */
    offset          = virtualAddress - memoryInfo.VirtualStartAddress;
    physicalAddress = memoryInfo.PhysicalStartAddress + offset;

    /* #50 If physical address is already aligned to maximum alignment
     *   and length is greater than maximum alignment */
    if ( ((physicalAddress & maxAlignMask) == 0u)
      && (length >= maxAlignSize) )
    {
      /* #51 Apply maximum alignment. */
      alignSize = maxAlignSize;
      alignMask = maxAlignMask;

      /* #52 If burst alignment is requested by given trim type, use maximum alignment instead to achieve desired result. */
      if (trimType == VSWUPDM_TRIM_TYPE_BURST)
      {
        trimType = VSWUPDM_TRIM_TYPE_MAX;
      }
    }
    /* #60 Otherwise, if physical address is already aligned to minimum alignment */
    else if ((physicalAddress & minAlignMask) == 0u)
    {
      /* #61 Apply minimum alignment. */
      alignSize = minAlignSize;
      alignMask = minAlignMask;
    }
    /* #70 Otherwise */
    else
    {
      /* #71 Given range start address is unaligned, report error. */
      retVal = VSWUPDM_E_MEM_UNALIGNED_ADDRESS;
    }

    /* #100 If alignment can be applied */
    if (retVal == E_OK)
    {
      /* #110 Trim range according to requested type */
      switch (trimType)
      {
        case VSWUPDM_TRIM_TYPE_SINGLE:
        /* #120 If range shall be trimmed to single alignment size */
        {
          /* #121 If length is smaller than align size, report zero.
           * Otherwise, report single alignment size */
          if (length < alignSize)
          {
            length = 0u;
          }
          else
          {
            length = alignSize;
          }

          break;
        }
        case VSWUPDM_TRIM_TYPE_MAX:
        /* #130 If range shall be trimmed to maximum aligned size */
        {
          vSwUpdM_LengthType localRemainder = length;
          vSwUpdM_LengthType maxLength = (memoryInfo.MaxOffset - offset) + 1u;

          length = 0u;

          while (localRemainder > maxLength)
          {
            length    += maxLength;
            localRemainder -= maxLength;

            (void)vMemAccM_GetMemoryInfo(vSwUpdM_GetVarPartitions(PartitionId).AddrAreaIdOfPartitions, (virtualAddress + length), localRemainder, &memoryInfo);

            maxLength = memoryInfo.MaxOffset + 1u;

            if (Granularity == VSWUPDM_ALIGN_GRANULARITY_PAGE)
            {
              alignMask = memoryInfo.PageBurstSize - 1u;
            }
            else
            {
              alignMask = memoryInfo.SectorBurstSize - 1u;
            }
          }

          /* #131 Align length, by clearing all bits defined by mask. */
          length += VSWUPDM_ALIGN_ADDRESS_FRONT(localRemainder, alignMask);

          break;
        }
        case VSWUPDM_TRIM_TYPE_BURST:
        /* #140 If range shall be trimmed to next address boundary required for burst operation */
        {
          /* #141 Calculate distance to next burst boundary. */
          vSwUpdM_LengthType burstDistance = (VSWUPDM_ALIGN_ADDRESS_END(physicalAddress, maxAlignMask) - physicalAddress) + 1u;

          /* #142 If necessary, limit length to burst distance. */
          if (length > burstDistance)
          {
            length = burstDistance;
          }

          /* #143 Align length, by clearing all bits defined by mask. */
          length = VSWUPDM_ALIGN_ADDRESS_FRONT(length, alignMask);

          break;
        }
        default:
        /* #150 Otherwise: Invalid trim type, report error. */
        {
          retVal = VSWUPDM_E_WRONG_PARAMETER;
          break;
        }
      }

      /* #200 Report back trimmed length. */
      *Length = length;
    }
  }

  return retVal;
  /* PRQA S 6030, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
} /* vSwUpdM_Range_TrimLength */

/**********************************************************************************************************************
 * vSwUpdM_Range_IsAddressInRange
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Range_IsAddressInRange(
  vSwUpdM_AddressType Address,
  vSwUpdM_AddressType RangeStartAddress,
  vSwUpdM_LengthType RangeLength)
{
  boolean retVal = FALSE;
  vSwUpdM_AddressType offset;

  /* #10 If given address is greater or equal to given start address of range */
  if (Address >= RangeStartAddress)
  {
    offset = Address - RangeStartAddress;

    /* #20 If offset from given start address of range to given address is smaller than given length of range
     *   Address lies within range. */
    if (offset < RangeLength)
    {
      retVal = TRUE;
    }
  }

  return retVal;
} /* vSwUpdM_Range_IsAddressInRange */

/**********************************************************************************************************************
 * vSwUpdM_Range_CheckAgainstRange
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
 *
 */
FUNC(vSwUpdM_RangeCheckType, VSWUPDM_CODE) vSwUpdM_Range_CheckAgainstRange(
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length,
  vSwUpdM_AddressType RangeStartAddress,
  vSwUpdM_LengthType RangeLength)
{
  vSwUpdM_RangeCheckType retVal = VSWUPDM_RANGE_CHECK_MISMATCH;
  vSwUpdM_LengthType length;
  boolean startResult;
  boolean endResult;

  length = Length;
  /* #10 If length is greater zero, decrement length to calculate last address in range.
   *   Special case of zero length indicates that only address is relevant. */
  if (length > 0u)
  {
    length--;
  }

  startResult = vSwUpdM_Range_IsAddressInRange(StartAddress, RangeStartAddress, RangeLength);
  endResult   = vSwUpdM_Range_IsAddressInRange(StartAddress + length, RangeStartAddress, RangeLength);

  /* #20 If given start address lies within given reference range */
  if (startResult == TRUE)
  {
    /* #21 If last address (calculated from given start address and length) lies within given reference range
     *   Report that given range completely lies within given reference range. */
    if (endResult == TRUE)
    {
      retVal = VSWUPDM_RANGE_CHECK_CONTAINED;
    }
    /* #22 Otherwise
     *   Report that given range overlaps with end of given reference range. */
    else
    {
      retVal = VSWUPDM_RANGE_CHECK_OVERLAP_END;
    }
  }
  /* #30 Otherwise */
  else
  {
    /* #31 If last address lies within given reference range
     *   Report that given range overlaps with start of given reference range.
     * Otherwise: Report given range doesn't overlap with given reference range at all. */
    if (endResult == TRUE)
    {
      retVal = VSWUPDM_RANGE_CHECK_OVERLAP_START;
    }
  }

  return retVal;
} /* vSwUpdM_Range_CheckAgainstRange */

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Range.c
 *********************************************************************************************************************/
