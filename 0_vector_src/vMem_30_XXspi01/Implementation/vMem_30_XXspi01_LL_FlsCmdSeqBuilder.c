/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vMem_30_XXspi01_LL_FlsCmdSeqBuilder.c
 *        \brief  Flash command sequence builder source file
 *
 *      \details  See vMem_30_XXspi01_LL_FlsCmdSeqBuilder.h
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_LL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vMem_30_XXspi01_LL_FlsCmdSeqBuilder.h"
#include "vMem_30_XXspi01_Cfg.h"

#if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! One byte bitmask. */
#define VMEM_30_XXSPI01_BYTE_MASK (uint8)(0xFF)

/*! 8 bit shift value. */
#define VMEM_30_XXSPI01_EIGHT_BIT_SHIFT   (uint8)(8u)

/*! Size of the address buffer for each instance */
#define VMEM_30_XXSPI01_ADDRESS_BUFFER_SIZE (0x04u)

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (VMEM_XXSPI01_LOCAL) /* COV_VMEM_30_XXSPI01_COMPATIBILITY */
# define VMEM_30_XXSPI01_LOCAL static
#endif

#if !defined (VMEM_XXSPI01_LOCAL_INLINE) /* COV_VMEM_30_XXSPI01_COMPATIBILITY */
# define VMEM_30_XXSPI01_LOCAL_INLINE LOCAL_INLINE
#endif


typedef uint8 vMem_30_XXspi01_ExtMappingIndexType; /*! Type to index the extended mapping entry within the ExtMappingTbl. */

/*!
 * This struct specifies all necessary parameters for a standard register read access and for a register read access
 * in case of an extended flash command sequence required by some multi-die devices.
 */
typedef struct
{
  vMem_30_XXspi01_InstanceIdType InstanceId;
  vMem_30_XXspi01_DeviceIdType DeviceId;
  vMem_30_XXspi01_InstanceIdType SectorIndex;
  vMem_30_XXspi01_SpiDataPtrType Buffer;
  vMem_30_XXspi01_SpiLengthType Length;
  vMem_30_XXspi01_ConstFlsCmdPtrType Cfg_GetFlsCmdPtr;
  vMem_30_XXspi01_ExtMappingIndexType Cfg_GetFlsCmdExtMapping;
} vMem_30_XXspi01_SeqBuilderJobType;

typedef P2VAR(vMem_30_XXspi01_SeqBuilderJobType, AUTOMATIC, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_SeqBuilderJobPtrType;

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_XXSPI01_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_FlsCmdSequenceType, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_FlashSequenceBuffer[vMem_30_XXspi01_GetSizeOfvMemInstance()];

#define VMEM_30_XXSPI01_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VMEM_30_XXSPI01_START_SEC_VAR_NOINIT_BUFFER
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* According to [SWS_Spi_00355] and [SWS_Spi_00437] each of these data buffers must be 32 bit aligned. Therefore, the size is initialized with VMEM_30_XXSPI01_32BIT_ALIGNMENT (4u). */
VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_SpiDataType, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_SingleFlsCmdBuffer[vMem_30_XXspi01_GetSizeOfvMemInstance()][VMEM_30_XXSPI01_32BIT_ALIGNMENT];

VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_SpiDataType, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_FlsCmdBuffer[vMem_30_XXspi01_GetSizeOfvMemInstance()][VMEM_30_XXSPI01_32BIT_ALIGNMENT];

VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_SpiDataType, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_AddressBuffer[vMem_30_XXspi01_GetSizeOfvMemInstance()][VMEM_30_XXSPI01_32BIT_ALIGNMENT]; /* PRQA S 3218 */ /* MD_vMem_XXspi01_3218 */

#define VMEM_30_XXSPI01_STOP_SEC_VAR_NOINIT_BUFFER
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressBuffer()
 *********************************************************************************************************************/
/*! \brief       Fills the address buffer for the given instance.
 *  \details     The function fills the address buffer of the given instance with the value of the given instance.
 *               The length of the address buffer depends on the configured address mode. The address buffer is filled
 *               with respect to the configured SpiChannel data width and the configured byte endianess.
 *  \param[in]   instanceId          ID and index of the related vMem_30_XXspi01 instance.
 *  \param[in]   deviceId            ID and index of the related device information.
 *  \param[in]   address             The address that shall be written into the address buffer.
 *  \param[in]   channelIdx          Index of the related SpiChannel.
 *  \param[out]  addressBuffer       Pointer to the filled address buffer.
 *  \return      addressBufferLength
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(vMem_30_XXspi01_SpiLengthType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressBuffer(
    vMem_30_XXspi01_InstanceIdType instanceId,  vMem_30_XXspi01_DeviceIdType deviceId, vMem_30_XXspi01_AddressType address,
    vMem_30_XXspi01_SpiDataPtrPtrType addressBuffer, vMem_30_XXspi01_vMemSpiChlConfigStartIdxOfvMemSpiConfigType channelIdx);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetDataWidthAlignedLength()
 *********************************************************************************************************************/
/*! \brief        This function returns the passed length parameter aligned to the Spi Channel DataWidth.
 *  \details      This function aligns the passed length to the SpiChannel specific DataWidth. The DataWidth
 *                defines the size with which the SPI accesses the given data buffer. The DataWidth can be
 *                a multiple of 8 (bits).
 *  \param[in]    channelIdx        Index position of the channel within the corresponding channel list.
 *  \param[in]    length            Requested length. This length is always 1 Byte aligned.
 *  \return       Returns the length aligned to the configured SpiChannel DataWidth.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(vMem_30_XXspi01_SpiLengthType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetDataWidthAlignedLength(
    vMem_30_XXspi01_SpiChannelType channelIdx, vMem_30_XXspi01_SpiLengthType length);

/*
 * The define VMEM_30_XXSPI01_VMEMFLSEXTTBL (generated by the ComStackLib) specifies if
 * the vMem_30_XXspi01_vMemFlsExtTbl[] does exist or not.
 * If the table does not exist, there are invalid accesses on that array.
 */
#if (VMEM_30_XXSPI01_VMEMFLSEXTTBL == STD_ON)
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetRegisterSeqExt()
 *********************************************************************************************************************/
/*! \brief        Sets up and triggers the execution for the requested register sequence with command extension.
 *  \details      In case the processed instance is a multi-die device with die-specific registers, this function
 *                sets up the corresponding Spi sequences including the configured command extension, in order to
 *                read from the target device.
 *  \param[in]    seqBuilderJobPtr       Pointer to structure which contains all required information to
 *                                       build the requested sequence.
 *  \return       Pointer to the setup sequence.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqExt(
    vMem_30_XXspi01_SeqBuilderJobPtrType seqBuilderJobPtr);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqExt()
 *********************************************************************************************************************/
/*! \brief        Sets up and triggers the execution for the requested register sequence without command extension.
 *  \details      In case the processed instance is a multi-die device with die-specific registers, this function
 *                sets up the corresponding Spi sequences including the configured command extension, in order to
 *                write to the target device.
 *  \param[in]    seqBuilderJobPtr       Pointer to structure which contains all required information
 *                                       to build the requested sequence.
 *  \return       Pointer to the setup sequence.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqExt(
    vMem_30_XXspi01_SeqBuilderJobPtrType seqBuilderJobPtr);
#endif /* VMEM_30_XXSPI01_VMEMFLSEXTTBL */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetRegisterSeqStd()
 *********************************************************************************************************************/
/*! \brief        Sets up and triggers the execution for the requested read register sequence without command extension.
 *  \details      -
 *  \param[in]    seqBuilderJobPtr       Pointer to structure which contains all required information
 *                                       to build the requested sequence.
 *  \return       Pointer to the setup sequence.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqStd(
    vMem_30_XXspi01_SeqBuilderJobPtrType seqBuilderJobPtr);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqStd()
 *********************************************************************************************************************/
/*! \brief        Sets up and triggers the execution for the requested write register sequence without command extension.
 *  \details      -
 *  \param[in]    deviceId               ID and index of the related device information.
 *  \param[in]    seqBuilderJobPtr       Pointer to structure which contains all required information
 *                                       to build the requested sequence.
 *  \return       Pointer to the setup sequence.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqStd(
    vMem_30_XXspi01_DeviceIdType deviceId, vMem_30_XXspi01_SeqBuilderJobPtrType seqBuilderJobPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetDataWidthAlignedLength()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(vMem_30_XXspi01_SpiLengthType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetDataWidthAlignedLength(
    vMem_30_XXspi01_SpiChannelType channelIdx, vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_SpiLengthType alignedLength;

  /* The returned value of the getter is the DataWidth in bits. To get the DataWidth in Bytes the value is divided by 8. */
  vMem_30_XXspi01_SpiLengthType dataWidth = (vMem_30_XXspi01_SpiLengthType)(vMem_30_XXspi01_LL_CfgInstance_GetSpiChlDataWidth(channelIdx) / 8u);

  if((length % dataWidth) == 0u)
  {
    alignedLength = (length / dataWidth);
  }
  else
  {
    alignedLength = (length / dataWidth) + 1u;
  }

  return alignedLength;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetDataWidthAlignedLength */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressBuffer()
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
VMEM_30_XXSPI01_LOCAL FUNC(vMem_30_XXspi01_SpiLengthType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressBuffer(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_AddressType address, vMem_30_XXspi01_SpiDataPtrPtrType addressBuffer,
    vMem_30_XXspi01_vMemSpiChlConfigStartIdxOfvMemSpiConfigType channelIdx)
{
  vMem_30_XXspi01_SpiLengthType addressBufferLength;
  vMem_30_XXspi01_SpiChlDataWidthOfvMemSpiChlConfigType dataWidthBits = vMem_30_XXspi01_LL_CfgInstance_GetSpiChlDataWidth(channelIdx);

  *addressBuffer = vMem_30_XXspi01_AddressBuffer[instanceId]; /* SBSW_vMem_30_XXspi01_AddressBufferAssignment */

  /*
   * The size which is used by the SPI to access this buffer (dataWidth) can vary from 8 bits, 16 bits to 32 bits. In case of a
   * little endian system the byte order within the data buffer must be taken into account.
   */
  if (vMem_30_XXspi01_LL_CfgDevice_IsExtendedAddressingEnabled(deviceId))
  {
#if (VMEM_30_XXSPI01_BYTE_ORDER == LOW_BYTE_FIRST) /* COV_VMEM_30_XXSPI01_BYTE_ORDER */
    {
      /* The LSB is transmitted first. */
      if(dataWidthBits <= 8u)
      {
        vMem_30_XXspi01_AddressBuffer[instanceId][0] = (vMem_30_XXspi01_SpiDataType) (address >> 24u); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][1] = (vMem_30_XXspi01_SpiDataType) ((address >> 16u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][2] = (vMem_30_XXspi01_SpiDataType) ((address >> 8u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][3] = (vMem_30_XXspi01_SpiDataType) (address & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
      }
      else if(dataWidthBits <= 16u)
      {
        vMem_30_XXspi01_AddressBuffer[instanceId][0] = (vMem_30_XXspi01_SpiDataType) ((address >> 16u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][1] = (vMem_30_XXspi01_SpiDataType) (address >> 24u); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][2] = (vMem_30_XXspi01_SpiDataType) (address & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][3] = (vMem_30_XXspi01_SpiDataType) ((address >> 8u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
      }
      else
      {
        vMem_30_XXspi01_AddressBuffer[instanceId][0] = (vMem_30_XXspi01_SpiDataType) (address & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][1] = (vMem_30_XXspi01_SpiDataType) ((address >> 8u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][2] = (vMem_30_XXspi01_SpiDataType) ((address >> 16u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][3] = (vMem_30_XXspi01_SpiDataType) (address >> 24u); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
      }
    }
#else
    {
        /* The MSB is transmitted first. */
        vMem_30_XXspi01_AddressBuffer[instanceId][0] = (vMem_30_XXspi01_SpiDataType) (address >> 24u); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][1] = (vMem_30_XXspi01_SpiDataType) ((address >> 16u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][2] = (vMem_30_XXspi01_SpiDataType) ((address >> 8u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][3] = (vMem_30_XXspi01_SpiDataType) (address & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
    }
#endif /* VMEM_30_XXSPI01_BYTE_ORDER */

    addressBufferLength = VMEM_30_XXSPI01_ADDRESS_BUFFER_SIZE; /* SBSW_vMem_30_XXspi01_AddressBufferLengthWriteAccess */
  }
  else
  {
#if (VMEM_30_XXSPI01_BYTE_ORDER == LOW_BYTE_FIRST) /* COV_VMEM_30_XXSPI01_BYTE_ORDER */
    {
      /* The LSB is transmitted first. */
      if(dataWidthBits <= 8u)
      {
        vMem_30_XXspi01_AddressBuffer[instanceId][0] = (vMem_30_XXspi01_SpiDataType) ((address >> 16u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][1] = (vMem_30_XXspi01_SpiDataType) ((address >> 8u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][2] = (vMem_30_XXspi01_SpiDataType) (address & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
      }
      else if(dataWidthBits <= 16u)
      {
        vMem_30_XXspi01_AddressBuffer[instanceId][0] = (vMem_30_XXspi01_SpiDataType) ((address >> 8u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][1] = (vMem_30_XXspi01_SpiDataType) ((address >> 16u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][2] = (vMem_30_XXspi01_SpiDataType) (address & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
      }
      else
      {
        vMem_30_XXspi01_AddressBuffer[instanceId][0] = (vMem_30_XXspi01_SpiDataType) (address & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][1] = (vMem_30_XXspi01_SpiDataType) ((address >> 8u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
        vMem_30_XXspi01_AddressBuffer[instanceId][2] = (vMem_30_XXspi01_SpiDataType) ((address >> 16u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
      }
    }
#else
    {
      /* The MSB is transmitted first. */
      vMem_30_XXspi01_AddressBuffer[instanceId][0] = (vMem_30_XXspi01_SpiDataType) ((address >> 16u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
      vMem_30_XXspi01_AddressBuffer[instanceId][1] = (vMem_30_XXspi01_SpiDataType) ((address >> 8u) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
      vMem_30_XXspi01_AddressBuffer[instanceId][2] = (vMem_30_XXspi01_SpiDataType) (address & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
    }
#endif /* VMEM_30_XXSPI01_BYTE_ORDER */

    addressBufferLength = (vMem_30_XXspi01_SpiLengthType) VMEM_30_XXSPI01_ADDRESS_BUFFER_SIZE
        - (vMem_30_XXspi01_SpiLengthType) 1; /* SBSW_vMem_30_XXspi01_AddressBufferLengthWriteAccess */
  }

  return addressBufferLength;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressBuffer */

/*
 * The define VMEM_30_XXSPI01_VMEMFLSEXTTBL (generated by the ComStackLib) specifies if
 * the vMem_30_XXspi01_vMemFlsExtTbl[] does exist or not.
 * If the table does not exist, there are invalid accesses on that array.
 */
#if (VMEM_30_XXSPI01_VMEMFLSEXTTBL == STD_ON)
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqExt()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqExt(
    vMem_30_XXspi01_SeqBuilderJobPtrType seqBuilderJobPtr)
{
  vMem_30_XXspi01_AddressType flsCmdExtension;
  vMem_30_XXspi01_SpiLengthType flsCmdExtensionLength;
  vMem_30_XXspi01_SpiDataPtrType extensionBufferPtr = NULL_PTR;
  vMem_30_XXspi01_FlsCmdSequencePtrType instSequencePtr = &(vMem_30_XXspi01_FlashSequenceBuffer[seqBuilderJobPtr->InstanceId]);
  vMem_30_XXspi01_vMemSpiChlConfigStartIdxOfvMemSpiConfigType channelIdx;

  /*!
   * The Spi sequence of an extended read register access is identical to the Spi sequence of a read access to the non-volatile memory (Command - Address - Data).
   * Therefore, the same Spi sequence can be used.
   */
  channelIdx = vMem_30_XXspi01_LL_CfgInstance_GetSpiReadChlStartIdx(seqBuilderJobPtr->InstanceId);
  instSequencePtr->SpiSequence = vMem_30_XXspi01_LL_CfgInstance_GetSpiReadSeq(seqBuilderJobPtr->InstanceId); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSequencePtr->FlsCmdItemCount = 3u; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* ------ FlsCmdItem 0 ------------------------------------------------------------------------------------------- */
  instSequencePtr->FlsCmdItems[0].SpiChannel = (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[0].SendDataBufferPtr = seqBuilderJobPtr->Cfg_GetFlsCmdPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 1 ------------------------------------------------------------------------------------------- */
  flsCmdExtension = (vMem_30_XXspi01_AddressType) vMem_30_XXspi01_LL_CfgInstance_GetFlsDeviceExtData(
      seqBuilderJobPtr->Cfg_GetFlsCmdExtMapping);
  flsCmdExtension += (vMem_30_XXspi01_AddressType) vMem_30_XXspi01_LL_CfgSector_GetDieSpecificRegisterAddressOffset(
      seqBuilderJobPtr->SectorIndex);

  /* Prepare the data buffer with the register address. The register address length is equal to the length of the memory address of the external device. */
  flsCmdExtensionLength = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressBuffer(seqBuilderJobPtr->InstanceId, /* SBSW_vMem_30_XXspi01_GetAddressBuffer */
      seqBuilderJobPtr->DeviceId, flsCmdExtension, &extensionBufferPtr,
      channelIdx);

  instSequencePtr->FlsCmdItems[1].SpiChannel = (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[1].SendDataBufferPtr = (vMem_30_XXspi01_ConstSpiDataPtrType) extensionBufferPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[1].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[1].DataBufferLength = (vMem_30_XXspi01_SpiLengthType) flsCmdExtensionLength; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 2 ------------------------------------------------------------------------------------------- */
  instSequencePtr->FlsCmdItems[2].SpiChannel = (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[2].SendDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[2].ReceiveDataBufferPtr = seqBuilderJobPtr->Buffer; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[2].DataBufferLength = seqBuilderJobPtr->Length; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSequencePtr;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqExt */


/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqExt()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqExt(
    vMem_30_XXspi01_SeqBuilderJobPtrType seqBuilderJobPtr)
{
  vMem_30_XXspi01_AddressType flsCmdExtension;
  vMem_30_XXspi01_SpiLengthType flsCmdExtensionLength;
  vMem_30_XXspi01_SpiDataPtrType extensionBufferPtr = NULL_PTR;
  vMem_30_XXspi01_FlsCmdSequencePtrType instSequencePtr = &(vMem_30_XXspi01_FlashSequenceBuffer[seqBuilderJobPtr->InstanceId]);
  vMem_30_XXspi01_vMemSpiChlConfigStartIdxOfvMemSpiConfigType channelIdx;

  /*!
   * The Spi sequence of an extended write register access is identical to the Spi sequence of a write access to the non-volatile memory ("Write Enable" - Command - Address - Data).
   * Therefore, the same Spi sequence can be used.
   */
  channelIdx = vMem_30_XXspi01_LL_CfgInstance_GetSpiWriteChlStartIdx(seqBuilderJobPtr->InstanceId);
  instSequencePtr->SpiSequence = vMem_30_XXspi01_LL_CfgInstance_GetSpiWriteSeq(seqBuilderJobPtr->InstanceId); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSequencePtr->FlsCmdItemCount = 4u; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* ------ FlsCmdItem 0 ------------------------------------------------------------------------------------------- */
  instSequencePtr->FlsCmdItems[0].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[0].SendDataBufferPtr = &(vMem_30_XXspi01_LL_CfgDevice_GetWriteEnableCommand(seqBuilderJobPtr->DeviceId)); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 1 ------------------------------------------------------------------------------------------- */
  instSequencePtr->FlsCmdItems[1].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[1].SendDataBufferPtr = seqBuilderJobPtr->Cfg_GetFlsCmdPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[1].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[1].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 2 ------------------------------------------------------------------------------------------- */
  flsCmdExtension = (vMem_30_XXspi01_AddressType) vMem_30_XXspi01_LL_CfgInstance_GetFlsDeviceExtData(
      seqBuilderJobPtr->Cfg_GetFlsCmdExtMapping);
  flsCmdExtension += (vMem_30_XXspi01_AddressType) vMem_30_XXspi01_LL_CfgSector_GetDieSpecificRegisterAddressOffset(
      seqBuilderJobPtr->SectorIndex);

  /* Prepare the data buffer with the register address. The register address length is equal to the length of the memory address of the external device. */
  flsCmdExtensionLength = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressBuffer(seqBuilderJobPtr->InstanceId, /* SBSW_vMem_30_XXspi01_GetAddressBuffer */
      seqBuilderJobPtr->DeviceId, flsCmdExtension, &extensionBufferPtr, channelIdx);

  instSequencePtr->FlsCmdItems[2].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[2].SendDataBufferPtr = (vMem_30_XXspi01_ConstSpiDataPtrType) extensionBufferPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[2].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[2].DataBufferLength = flsCmdExtensionLength; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 3 ------------------------------------------------------------------------------------------- */
  instSequencePtr->FlsCmdItems[3].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[3].SendDataBufferPtr = (vMem_30_XXspi01_ConstSpiDataPtrType) (seqBuilderJobPtr->Buffer); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[3].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[3].DataBufferLength = seqBuilderJobPtr->Length; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSequencePtr;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqExt */
#endif /* VMEM_30_XXSPI01_VMEMFLSEXTTBL */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqStd()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqStd(
    vMem_30_XXspi01_SeqBuilderJobPtrType seqBuilderJobPtr)
{
  vMem_30_XXspi01_FlsCmdSequencePtrType instSequencePtr = &(vMem_30_XXspi01_FlashSequenceBuffer[seqBuilderJobPtr->InstanceId]);
  vMem_30_XXspi01_vMemSpiChlConfigStartIdxOfvMemSpiConfigType channelIdx;

  channelIdx = vMem_30_XXspi01_LL_CfgInstance_GetSpiReadRegisterChlStartIdx(seqBuilderJobPtr->InstanceId);
  instSequencePtr->SpiSequence = vMem_30_XXspi01_LL_CfgInstance_GetSpiReadRegisterSeq(seqBuilderJobPtr->InstanceId); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSequencePtr->FlsCmdItemCount = 2u; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* ------ FlsCmdItem 0 ------------------------------------------------------------------------------------------- */
  instSequencePtr->FlsCmdItems[0].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[0].SendDataBufferPtr = seqBuilderJobPtr->Cfg_GetFlsCmdPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 1 ------------------------------------------------------------------------------------------- */
  instSequencePtr->FlsCmdItems[1].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[1].SendDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[1].ReceiveDataBufferPtr = seqBuilderJobPtr->Buffer; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[1].DataBufferLength = seqBuilderJobPtr->Length; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSequencePtr;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqStd */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqStd()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqStd(
    vMem_30_XXspi01_DeviceIdType deviceId, vMem_30_XXspi01_SeqBuilderJobPtrType seqBuilderJobPtr)
{
  vMem_30_XXspi01_FlsCmdSequencePtrType instSequencePtr = &(vMem_30_XXspi01_FlashSequenceBuffer[seqBuilderJobPtr->InstanceId]);
  vMem_30_XXspi01_vMemSpiChlConfigStartIdxOfvMemSpiConfigType channelIdx;

  channelIdx = vMem_30_XXspi01_LL_CfgInstance_GetSpiWriteRegisterChlStartIdx(seqBuilderJobPtr->InstanceId);
  instSequencePtr->SpiSequence = vMem_30_XXspi01_LL_CfgInstance_GetSpiWriteRegisterSeq(seqBuilderJobPtr->InstanceId); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSequencePtr->FlsCmdItemCount = 3u; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* ------ FlsCmdItem 0 ------------------------------------------------------------------------------------------- */
  instSequencePtr->FlsCmdItems[0].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  vMem_30_XXspi01_SingleFlsCmdBuffer[seqBuilderJobPtr->InstanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetWriteEnableCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  instSequencePtr->FlsCmdItems[0].SendDataBufferPtr = vMem_30_XXspi01_SingleFlsCmdBuffer[seqBuilderJobPtr->InstanceId]; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 1 ------------------------------------------------------------------------------------------- */
  instSequencePtr->FlsCmdItems[1].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[1].SendDataBufferPtr = seqBuilderJobPtr->Cfg_GetFlsCmdPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[1].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[1].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 2 ------------------------------------------------------------------------------------------- */
  instSequencePtr->FlsCmdItems[2].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[2].SendDataBufferPtr = (vMem_30_XXspi01_ConstSpiDataPtrType) (seqBuilderJobPtr->Buffer); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[2].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSequencePtr->FlsCmdItems[2].DataBufferLength = seqBuilderJobPtr->Length; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSequencePtr;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqStd */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/*********************************************************************************************************************
 *  MEMORY ACCESS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_AddressType sourceAddress, vMem_30_XXspi01_SpiDataPtrType targetAddressPtr,
    vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_SpiDataPtrType addressBufferPtr = NULL_PTR;
  vMem_30_XXspi01_SpiLengthType addressBufferLength;
  vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(vMem_30_XXspi01_FlashSequenceBuffer[instanceId]);
  vMem_30_XXspi01_vMemSpiChlConfigStartIdxOfvMemSpiConfigType channelIdx;

  channelIdx = vMem_30_XXspi01_LL_CfgInstance_GetSpiReadChlStartIdx(instanceId);
  instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_CfgInstance_GetSpiReadSeq(instanceId); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSeqBuffer->FlsCmdItemCount = 3u; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* ------ FlsCmdItem 0 ------------------------------------------------------------------------------------------- */
  instSeqBuffer->FlsCmdItems[0].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetReadCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId]; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 1 ------------------------------------------------------------------------------------------- */
  addressBufferLength = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressBuffer(instanceId, deviceId, sourceAddress, /* SBSW_vMem_30_XXspi01_GetAddressBuffer */
      &addressBufferPtr, channelIdx);

  instSeqBuffer->FlsCmdItems[1].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].SendDataBufferPtr = addressBufferPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  /* The SpiChannel to transmit the address is the only channel that can be configured with a data width > 8 bit. Therefore, the length must be aligned to the configured data width. */
  instSeqBuffer->FlsCmdItems[1].DataBufferLength = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetDataWidthAlignedLength( /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
      channelIdx, addressBufferLength);
  channelIdx++;

  /* ------ FlsCmdItem 2 ------------------------------------------------------------------------------------------- */
  instSeqBuffer->FlsCmdItems[2].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].SendDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].ReceiveDataBufferPtr = targetAddressPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].DataBufferLength = length; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSeqBuffer;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_AddressType targetAddress, vMem_30_XXspi01_ConstSpiDataPtrType sourceAddressPtr,
    vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_SpiDataPtrType addressBufferPtr = NULL_PTR;
  vMem_30_XXspi01_SpiLengthType addressBufferLength;
  vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(vMem_30_XXspi01_FlashSequenceBuffer[instanceId]);
  vMem_30_XXspi01_vMemSpiChlConfigStartIdxOfvMemSpiConfigType channelIdx;

  channelIdx = vMem_30_XXspi01_LL_CfgInstance_GetSpiWriteChlStartIdx(instanceId);
  instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_CfgInstance_GetSpiWriteSeq(instanceId); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSeqBuffer->FlsCmdItemCount = 4u; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* ------ FlsCmdItem 0 ------------------------------------------------------------------------------------------- */
  instSeqBuffer->FlsCmdItems[0].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  vMem_30_XXspi01_SingleFlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetWriteEnableCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = vMem_30_XXspi01_SingleFlsCmdBuffer[instanceId]; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 1 ------------------------------------------------------------------------------------------- */
  instSeqBuffer->FlsCmdItems[1].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetWriteCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  instSeqBuffer->FlsCmdItems[1].SendDataBufferPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId]; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 2 ------------------------------------------------------------------------------------------- */
  addressBufferLength = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressBuffer(instanceId, deviceId, targetAddress, &addressBufferPtr, channelIdx); /* SBSW_vMem_30_XXspi01_GetAddressBuffer */

  instSeqBuffer->FlsCmdItems[2].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].SendDataBufferPtr = addressBufferPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  /* The SpiChannel to transmit the address is the only channel that can be configured with a data width > 8 bit. Therefore, the length must be aligned to the configured data width. */
  instSeqBuffer->FlsCmdItems[2].DataBufferLength = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetDataWidthAlignedLength( /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
      channelIdx, addressBufferLength);
  channelIdx++;

  /* ------ FlsCmdItem 3 ------------------------------------------------------------------------------------------- */
  instSeqBuffer->FlsCmdItems[3].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[3].SendDataBufferPtr = sourceAddressPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[3].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[3].DataBufferLength = length; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSeqBuffer;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEraseSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEraseSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_AddressType targetAddress)
{
  vMem_30_XXspi01_SpiDataPtrType addressBufferPtr = NULL_PTR;
  vMem_30_XXspi01_SpiLengthType addressBufferLength;
  vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(vMem_30_XXspi01_FlashSequenceBuffer[instanceId]);
  vMem_30_XXspi01_vMemSpiChlConfigStartIdxOfvMemSpiConfigType channelIdx;

  channelIdx = vMem_30_XXspi01_LL_CfgInstance_GetSpiEraseChlStartIdx(instanceId);
  instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_CfgInstance_GetSpiEraseSeq(instanceId); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSeqBuffer->FlsCmdItemCount = 3u; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* ------ FlsCmdItem 0 ------------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_SingleFlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetWriteEnableCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */

  instSeqBuffer->FlsCmdItems[0].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = vMem_30_XXspi01_SingleFlsCmdBuffer[instanceId]; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 1 ------------------------------------------------------------------------------------------- */
  instSeqBuffer->FlsCmdItems[1].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetEraseCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  instSeqBuffer->FlsCmdItems[1].SendDataBufferPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId]; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 2 ------------------------------------------------------------------------------------------- */
  addressBufferLength = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressBuffer(instanceId, deviceId, targetAddress, &addressBufferPtr, channelIdx); /* SBSW_vMem_30_XXspi01_GetAddressBuffer */

  instSeqBuffer->FlsCmdItems[2].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].SendDataBufferPtr = addressBufferPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  /* The SpiChannel to transmit the address is the only channel that can be configured with a data width > 8 bit. Therefore, the length must be aligned to the configured data width. */
  instSeqBuffer->FlsCmdItems[2].DataBufferLength = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetDataWidthAlignedLength( /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
      channelIdx, addressBufferLength);

  return instSeqBuffer;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEraseSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetSmallSectorEraseSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetSmallSectorEraseSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_AddressType targetAddress)
{
  vMem_30_XXspi01_SpiDataPtrType addressBufferPtr = NULL_PTR;
  vMem_30_XXspi01_SpiLengthType addressBufferLength;
  vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(vMem_30_XXspi01_FlashSequenceBuffer[instanceId]);
  vMem_30_XXspi01_vMemSpiChlConfigStartIdxOfvMemSpiConfigType channelIdx;

  channelIdx = vMem_30_XXspi01_LL_CfgInstance_GetSpiEraseSmallSizedSectorChlStartIdx(instanceId);
  instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_CfgInstance_GetSpiEraseSmallSizedSectorSeq(instanceId); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSeqBuffer->FlsCmdItemCount = 3u; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* ------ FlsCmdItem 0 ------------------------------------------------------------------------------------------- */
  instSeqBuffer->FlsCmdItems[0].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  vMem_30_XXspi01_SingleFlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetWriteEnableCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = vMem_30_XXspi01_SingleFlsCmdBuffer[instanceId]; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 1 ------------------------------------------------------------------------------------------- */
  instSeqBuffer->FlsCmdItems[1].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetEraseSmallSizedSectorCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  instSeqBuffer->FlsCmdItems[1].SendDataBufferPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId]; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  channelIdx++;

  /* ------ FlsCmdItem 2 ------------------------------------------------------------------------------------------- */
  addressBufferLength = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressBuffer(instanceId, deviceId, targetAddress, &addressBufferPtr, channelIdx); /* SBSW_vMem_30_XXspi01_GetAddressBuffer */

  instSeqBuffer->FlsCmdItems[2].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].SendDataBufferPtr = addressBufferPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  /* The SpiChannel to transmit the address is the only channel that can be configured with a data width > 8 bit. Therefore, the length must be aligned to the configured data width. */
  instSeqBuffer->FlsCmdItems[2].DataBufferLength = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetDataWidthAlignedLength( /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
      channelIdx, addressBufferLength);

  return instSeqBuffer;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetSmallSectorEraseSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetClearResultRegisterSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetClearResultRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId)
{
  vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(vMem_30_XXspi01_FlashSequenceBuffer[instanceId]);
  vMem_30_XXspi01_vMemSpiChlConfigStartIdxOfvMemSpiConfigType channelIdx;

  channelIdx = vMem_30_XXspi01_LL_CfgInstance_GetSpiSingleCommandChlStartIdx(instanceId);
  instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_CfgInstance_GetSingleCommandSeq(instanceId); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSeqBuffer->FlsCmdItemCount = 1u; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* ------ FlsCmdItem 0 ------------------------------------------------------------------------------------------- */
  instSeqBuffer->FlsCmdItems[0].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  vMem_30_XXspi01_SingleFlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetClearResultRegisterCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = vMem_30_XXspi01_SingleFlsCmdBuffer[instanceId]; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSeqBuffer;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetClearResultRegisterSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEnable4ByteAddressModeSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEnable4ByteAddressModeSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId)
{
  vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(vMem_30_XXspi01_FlashSequenceBuffer[instanceId]);
  vMem_30_XXspi01_vMemSpiChlConfigStartIdxOfvMemSpiConfigType channelIdx;

  channelIdx = vMem_30_XXspi01_LL_CfgInstance_GetSpiSingleCommandChlStartIdx(instanceId);
  instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_CfgInstance_GetSingleCommandSeq(instanceId); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSeqBuffer->FlsCmdItemCount = 1u; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* ------ FlsCmdItem 0 ------------------------------------------------------------------------------------------- */
  instSeqBuffer->FlsCmdItems[0].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  vMem_30_XXspi01_SingleFlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetEnable4ByteAddressModeCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = vMem_30_XXspi01_SingleFlsCmdBuffer[instanceId]; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSeqBuffer;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEnable4ByteAddressModeSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteDisableSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteDisableSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId)
{
  vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(vMem_30_XXspi01_FlashSequenceBuffer[instanceId]);
  vMem_30_XXspi01_vMemSpiChlConfigStartIdxOfvMemSpiConfigType channelIdx;

  channelIdx = vMem_30_XXspi01_LL_CfgInstance_GetSpiSingleCommandChlStartIdx(instanceId);
  instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_CfgInstance_GetSingleCommandSeq(instanceId); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSeqBuffer->FlsCmdItemCount = 1u; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* ------ FlsCmdItem 0 ------------------------------------------------------------------------------------------- */
  instSeqBuffer->FlsCmdItems[0].SpiChannel =
      (vMem_30_XXspi01_SpiChannelType) vMem_30_XXspi01_LL_CfgInstance_GetSpiChl(channelIdx); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  vMem_30_XXspi01_SingleFlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetWriteDisableCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = vMem_30_XXspi01_SingleFlsCmdBuffer[instanceId]; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSeqBuffer;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteDisableSequence */

/*********************************************************************************************************************
 *  REGISTER ACCESS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetStatusRegisterSequence()
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
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetStatusRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_InstanceIdType sectorIndex, vMem_30_XXspi01_SpiDataPtrType buffer,
    vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_FlsCmdSequencePtrType sequencePtr;
  vMem_30_XXspi01_SeqBuilderJobType seqBuilderJob;

  seqBuilderJob.InstanceId = instanceId;
  seqBuilderJob.DeviceId = deviceId;
  seqBuilderJob.Buffer = buffer;
  seqBuilderJob.Length = length;
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetReadStatusRegisterCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  seqBuilderJob.Cfg_GetFlsCmdPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId];

  /*
   * The define VMEM_30_XXSPI01_VMEMFLSEXTTBL (generated by the ComStackLib) specifies if
   * the vMem_30_XXspi01_vMemFlsExtTbl[] does exist or not.
   * If the table does not exist, there are invalid accesses on that array.
   */
#if (VMEM_30_XXSPI01_VMEMFLSEXTTBL == STD_ON)
  if ((vMem_30_XXspi01_ExtMappingIndexType) vMem_30_XXspi01_LL_CfgDevice_GetReadStatusRegisterCommandExtMapping(
      deviceId) != (vMem_30_XXspi01_ExtMappingIndexType) VMEM_30_XXSPI01_CMD_EXT_TBL_INVALID_INDEX)
  {
    /*!
     * The instanceId and the sectorIndex is only necessary, if the flash command extension is used to read
     * the register.
     */
    seqBuilderJob.SectorIndex = sectorIndex;
    seqBuilderJob.Cfg_GetFlsCmdExtMapping =
        (vMem_30_XXspi01_ExtMappingIndexType) vMem_30_XXspi01_LL_CfgDevice_GetReadStatusRegisterCommandExtMapping(
            deviceId);

    sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqExt(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
  }
  else
#else
  VMEM_30_XXSPI01_DUMMY_STATEMENT(sectorIndex); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* VMEM_30_XXSPI01_VMEMFLSEXTTBL */
  {
    sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqStd(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
  }

  return sequencePtr;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetStatusRegisterSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetExtendedProgressCheckRegisterSequence()
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
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetExtendedProgressCheckRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_InstanceIdType sectorIndex, vMem_30_XXspi01_SpiDataPtrType buffer,
    vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_FlsCmdSequencePtrType sequencePtr;
  vMem_30_XXspi01_SeqBuilderJobType seqBuilderJob;

  seqBuilderJob.InstanceId = instanceId;
  seqBuilderJob.DeviceId = deviceId;
  seqBuilderJob.Buffer = buffer;
  seqBuilderJob.Length = length;
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetReadExtendedProgressCheckRegisterCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  seqBuilderJob.Cfg_GetFlsCmdPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId];

  /*
   * The define VMEM_30_XXSPI01_VMEMFLSEXTTBL (generated by the ComStackLib) specifies if
   * the vMem_30_XXspi01_vMemFlsExtTbl[] does exist or not.
   * If the table does not exist, there are invalid accesses on that array.
   */
#if (VMEM_30_XXSPI01_VMEMFLSEXTTBL == STD_ON)
  if ((vMem_30_XXspi01_ExtMappingIndexType) vMem_30_XXspi01_LL_CfgDevice_GetReadExtendedProgressCheckRegisterCommandExtMapping(
      deviceId) != (vMem_30_XXspi01_ExtMappingIndexType) VMEM_30_XXSPI01_CMD_EXT_TBL_INVALID_INDEX)
  {
    /*!
     * The instanceId and the sectorIndex is only necessary, if the flash command extension is used to read
     * the register.
     */
    seqBuilderJob.SectorIndex = sectorIndex;
    seqBuilderJob.Cfg_GetFlsCmdExtMapping =
        (vMem_30_XXspi01_ExtMappingIndexType) vMem_30_XXspi01_LL_CfgDevice_GetReadExtendedProgressCheckRegisterCommandExtMapping(
            deviceId);

    sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqExt(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
  }
  else
#else
  VMEM_30_XXSPI01_DUMMY_STATEMENT(sectorIndex); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* VMEM_30_XXSPI01_VMEMFLSEXTTBL */
  {
    sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqStd(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
  }

  return sequencePtr;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetExtendedProgressCheckRegisterSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetResultRegisterSequence()
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
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetResultRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_InstanceIdType sectorIndex, vMem_30_XXspi01_SpiDataPtrType buffer,
    vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_FlsCmdSequencePtrType sequencePtr;
  vMem_30_XXspi01_SeqBuilderJobType seqBuilderJob;

  seqBuilderJob.InstanceId = instanceId;
  seqBuilderJob.DeviceId = deviceId;
  seqBuilderJob.Buffer = buffer;
  seqBuilderJob.Length = length;
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetReadResultRegisterCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  seqBuilderJob.Cfg_GetFlsCmdPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId];

  /*
   * The define VMEM_30_XXSPI01_VMEMFLSEXTTBL (generated by the ComStackLib) specifies if
   * the vMem_30_XXspi01_vMemFlsExtTbl[] does exist or not.
   * If the table does not exist, there are invalid accesses on that array.
   */
#if (VMEM_30_XXSPI01_VMEMFLSEXTTBL == STD_ON)
  if ((vMem_30_XXspi01_ExtMappingIndexType) vMem_30_XXspi01_LL_CfgDevice_GetReadResultRegisterCommandExtMapping(
      deviceId) != (vMem_30_XXspi01_ExtMappingIndexType) VMEM_30_XXSPI01_CMD_EXT_TBL_INVALID_INDEX)
  {
    /*!
     * The instanceId and the sectorIndex is only necessary, if the flash command extension is used to read
     * the register.
     */
    seqBuilderJob.SectorIndex = sectorIndex;
    seqBuilderJob.Cfg_GetFlsCmdExtMapping =
        (vMem_30_XXspi01_ExtMappingIndexType) vMem_30_XXspi01_LL_CfgDevice_GetReadResultRegisterCommandExtMapping(
            deviceId);

    sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqExt(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
  }
  else
#else
  VMEM_30_XXSPI01_DUMMY_STATEMENT(sectorIndex); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* VMEM_30_XXSPI01_VMEMFLSEXTTBL */
  {
    sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqStd(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
  }

  return sequencePtr;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetResultRegisterSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressModeRegisterSequence()
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
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressModeRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_InstanceIdType sectorIndex, vMem_30_XXspi01_SpiDataPtrType buffer,
    vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_FlsCmdSequencePtrType sequencePtr;
  vMem_30_XXspi01_SeqBuilderJobType seqBuilderJob;

  seqBuilderJob.InstanceId = instanceId;
  seqBuilderJob.DeviceId = deviceId;
  seqBuilderJob.Buffer = buffer;
  seqBuilderJob.Length = length;
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetReadAddressModeCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  seqBuilderJob.Cfg_GetFlsCmdPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId];

  /*
   * The define VMEM_30_XXSPI01_VMEMFLSEXTTBL (generated by the ComStackLib) specifies if
   * the vMem_30_XXspi01_vMemFlsExtTbl[] does exist or not.
   * If the table does not exist, there are invalid accesses on that array.
   */
#if (VMEM_30_XXSPI01_VMEMFLSEXTTBL == STD_ON)
  if ((vMem_30_XXspi01_ExtMappingIndexType) vMem_30_XXspi01_LL_CfgDevice_GetReadAddressModeCommandExtMapping(
      deviceId) != (vMem_30_XXspi01_ExtMappingIndexType) VMEM_30_XXSPI01_CMD_EXT_TBL_INVALID_INDEX)
  {
    /*!
     * The instanceId and the sectorIndex is only necessary, if the flash command extension is used to read
     * the register.
     */
    seqBuilderJob.SectorIndex = sectorIndex;
    seqBuilderJob.Cfg_GetFlsCmdExtMapping =
        (vMem_30_XXspi01_ExtMappingIndexType) vMem_30_XXspi01_LL_CfgDevice_GetReadAddressModeCommandExtMapping(
            deviceId);

    sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqExt(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
  }
  else
#else
  VMEM_30_XXSPI01_DUMMY_STATEMENT(sectorIndex); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* VMEM_30_XXSPI01_VMEMFLSEXTTBL */
  {
    sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqStd(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
  }

  return sequencePtr;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressModeRegisterSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadHybridSectorLayoutSequence()
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
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadHybridSectorLayoutSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_InstanceIdType sectorIndex, vMem_30_XXspi01_SpiDataPtrType buffer,
    vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_FlsCmdSequencePtrType sequencePtr;
  vMem_30_XXspi01_SeqBuilderJobType seqBuilderJob;

  seqBuilderJob.InstanceId = instanceId;
  seqBuilderJob.DeviceId = deviceId;
  seqBuilderJob.Buffer = buffer;
  seqBuilderJob.Length = length;
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetReadConfigSectorLayoutCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  seqBuilderJob.Cfg_GetFlsCmdPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId];

  /*
   * The define VMEM_30_XXSPI01_VMEMFLSEXTTBL (generated by the ComStackLib) specifies if
   * the vMem_30_XXspi01_vMemFlsExtTbl[] does exist or not.
   * If the table does not exist, there are invalid accesses on that array.
   */
#if (VMEM_30_XXSPI01_VMEMFLSEXTTBL == STD_ON)
  if ((vMem_30_XXspi01_ExtMappingIndexType) vMem_30_XXspi01_LL_CfgDevice_GetReadConfigSectorLayoutCommandExtMapping(
      deviceId) != (vMem_30_XXspi01_ExtMappingIndexType) VMEM_30_XXSPI01_CMD_EXT_TBL_INVALID_INDEX)
  {
    /*!
     * The instanceId and the sectorIndex is only necessary, if the flash command extension is used to read
     * the register.
     */
    seqBuilderJob.SectorIndex = sectorIndex;
    seqBuilderJob.Cfg_GetFlsCmdExtMapping =
        (vMem_30_XXspi01_ExtMappingIndexType) vMem_30_XXspi01_LL_CfgDevice_GetReadConfigSectorLayoutCommandExtMapping(
            deviceId);

    sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqExt(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
  }
  else
#else
  VMEM_30_XXSPI01_DUMMY_STATEMENT(sectorIndex); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* VMEM_30_XXSPI01_VMEMFLSEXTTBL */
  {
    sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqStd(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
  }

  return sequencePtr;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadHybridSectorLayoutSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteHybridSectorLayoutSequence()
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
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteHybridSectorLayoutSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_InstanceIdType sectorIndex, vMem_30_XXspi01_SpiDataPtrType buffer,
    vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_FlsCmdSequencePtrType sequencePtr;
  vMem_30_XXspi01_SeqBuilderJobType seqBuilderJob;

  seqBuilderJob.InstanceId = instanceId;
  seqBuilderJob.DeviceId = deviceId;
  seqBuilderJob.Buffer = buffer;
  seqBuilderJob.Length = length;
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetWriteConfigSectorLayoutCommand(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  seqBuilderJob.Cfg_GetFlsCmdPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId];
  /*
   * The define VMEM_30_XXSPI01_VMEMFLSEXTTBL (generated by the ComStackLib) specifies if
   * the vMem_30_XXspi01_vMemFlsExtTbl[] does exist or not.
   * If the table does not exist, there are invalid accesses on that array.
   */
#if (VMEM_30_XXSPI01_VMEMFLSEXTTBL == STD_ON)
  if ((vMem_30_XXspi01_ExtMappingIndexType) vMem_30_XXspi01_LL_CfgDevice_GetWriteConfigSectorLayoutCommandExtMapping(
      deviceId) != (vMem_30_XXspi01_ExtMappingIndexType) VMEM_30_XXSPI01_CMD_EXT_TBL_INVALID_INDEX)
  {
    seqBuilderJob.SectorIndex = sectorIndex;
    seqBuilderJob.Cfg_GetFlsCmdExtMapping =
        (vMem_30_XXspi01_ExtMappingIndexType) vMem_30_XXspi01_LL_CfgDevice_GetWriteConfigSectorLayoutCommandExtMapping(
            deviceId);

    sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqExt(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
  }
  else
#else
  VMEM_30_XXSPI01_DUMMY_STATEMENT(sectorIndex); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* VMEM_30_XXSPI01_VMEMFLSEXTTBL */
  {
    sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqStd(deviceId, &seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
  }

  return sequencePtr;
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteHybridSectorLayoutSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadQuadSpiModeRegisterSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadQuadSpiModeRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_SpiDataPtrType buffer, vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_SeqBuilderJobType seqBuilderJob;

  seqBuilderJob.InstanceId = instanceId;
  seqBuilderJob.Buffer = buffer;
  seqBuilderJob.Length = length;
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetReadQuadSpiModeRegCmd(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  seqBuilderJob.Cfg_GetFlsCmdPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId];

  /*
   * No support of the S70FS01GS derivative regarding this feature. Therefore, no extended access required.
   */
  return vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqStd(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadQuadSpiModeRegisterSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteQuadSpiModeRegisterSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteQuadSpiModeRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_SpiDataPtrType buffer, vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_SeqBuilderJobType seqBuilderJob;

  seqBuilderJob.InstanceId = instanceId;
  seqBuilderJob.Buffer = buffer;
  seqBuilderJob.Length = length;
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetWriteQuadSpiModeRegCmd(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  seqBuilderJob.Cfg_GetFlsCmdPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId];

  /*
   * No support of the S70FS01GS derivative regarding this feature. Therefore, no extended access required.
   */
  return vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqStd(deviceId, &seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteQuadSpiModeRegisterSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadDummyCycleRegisterSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadDummyCycleRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_SpiDataPtrType buffer, vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_SeqBuilderJobType seqBuilderJob;

  seqBuilderJob.InstanceId = instanceId;
  seqBuilderJob.Buffer = buffer;
  seqBuilderJob.Length = length;
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetReadDummyCycleRegCmd(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  seqBuilderJob.Cfg_GetFlsCmdPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId];

  /*
   * No support of the S70FS01GS derivative regarding this feature. Therefore, no extended access required.
   */
  return vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqStd(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadDummyCycleRegisterSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteDummyCycleRegisterSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteDummyCycleRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_SpiDataPtrType buffer, vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_SeqBuilderJobType seqBuilderJob;

  seqBuilderJob.InstanceId = instanceId;
  seqBuilderJob.Buffer = buffer;
  seqBuilderJob.Length = length;
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetWriteDummyCycleRegCmd(deviceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  seqBuilderJob.Cfg_GetFlsCmdPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId];

  /*
   * No support of the S70FS01GS derivative regarding this feature. Therefore, no extended access required.
   */
  return vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqStd(deviceId, &seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteDummyCycleRegisterSequence */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetJedecIdSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetJedecIdSequence(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_SpiDataPtrType jedecIdBuffer)
{
  vMem_30_XXspi01_SeqBuilderJobType seqBuilderJob;

  seqBuilderJob.InstanceId = instanceId;
  seqBuilderJob.Buffer = jedecIdBuffer;
  seqBuilderJob.Length = VMEM_30_XXSPI01_JEDECID_BUFFER_LENGTH;

  /*
   * During this operation the corresponding device ID is not known, yet. The command to read the device's JEDEC ID is the same
   * for every device. Therefore, it is possible to use a valid instance ID instead of the device ID to retrieve the "Read JEDEC ID"-command.
   */
  vMem_30_XXspi01_FlsCmdBuffer[instanceId][0] = vMem_30_XXspi01_LL_CfgDevice_GetReadJedecIdCommand(instanceId); /* SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess */
  seqBuilderJob.Cfg_GetFlsCmdPtr = vMem_30_XXspi01_FlsCmdBuffer[instanceId];

  return vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadRegisterSeqStd(&seqBuilderJob); /* SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq */
} /* vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetJedecIdSequence */

#define VMEM_30_XXSPI01_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:
 MD_vMem_XXspi01_3218: rule 8.9
 Reason:     The buffer is only accessed in one function.
 Risk:       An object should be defined at block scope if its identifier only appears in a single function. But there's
 no risk.
 Prevention: No prevention necessary and possible. A pointer to the buffer is later passed to the underlying SPI driver.
 If this buffer would be defined at block scope, the pointer would point to an invalid address.

 MD_vMem_XXspi01_2985: rule 2.2
 Reason:     The getter macro for the SPI channel reference requires a channel index.
 The first channel index for a sequence inevitable is zero, what causes the rule deviation.
 Risk:       No risk.
 Prevention: No prevention.

 */

/* SBSW_JUSTIFICATION_BEGIN

 \ID SBSW_vMem_30_XXspi01_AddressBufferAssignment
 \DESCRIPTION A pointer to the address buffer for a specific instance is assigned to the dereferenced given address buffer
 pointer pointer.
 \COUNTERMEASURE \N No countermeasure is necessary because the caller of the function is responsible for providing a correct
 pointer pointer where the pointer to the address buffer could be stored.

 \ID SBSW_vMem_30_XXspi01_AddressBufferWriteAccess
 \DESCRIPTION A write access on the address buffer through the buffer pointer is performed.
 \COUNTERMEASURE \N No countermeasure is necessary because the buffer pointer is valid as long as the caller of the function
 provides a valid instance index. For each configured flash device an address buffer is preallocated.

 \ID SBSW_vMem_30_XXspi01_AddressBufferLengthWriteAccess
 \DESCRIPTION A write access on the address buffer length pointer parameter is performed.
 \COUNTERMEASURE \N No countermeasure is necessary because the caller of the function is responsible for providing a valid
 pointer to store the address buffer length.

 \ID SBSW_vMem_30_XXspi01_SequenceBufferPointer
 \DESCRIPTION A write access on the sequence buffer for a specific instance is performed.
 \COUNTERMEASURE \N No countermeasure is necessary because the pointer on the instances sequence buffer is retrieved
 by using the given instance index. No out of bounds access occurs as long as a valid instance index is provided
 by the caller. The validity of the instance index is ensured by the DET checks in the components public interface.
 For every configured device a sequence buffer is preallocated using the generated vMem_30_XXspi01_GetSizeOfvMemInstance()
 macro, that delivers the amount of configured devices.

 \ID SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess
 \DESCRIPTION A write access on the flash command item array is performed.
 \COUNTERMEASURE \N No countermeasure is necessary because the array is statically preallocated and only accessed with a static
 index. It has to be checked that the set value for the flash command item count reflects the amount of initialized
 flash command items. The total amount of preallocated flash command items is defined by the
 vMem_30_XXspi01_LL_MaximumChannels. It is obvious that the longest sequence of flash command items required
 for a sequence is lower or equal to this value. The validity of the instSeqBuffer pointer is justified by the
 SBSW_vMem_30_XXspi01_SequenceBufferPointer justification.

 \ID SBSW_vMem_30_XXspi01_GetAddressBuffer
 \DESCRIPTION Function call to retrieve the pointer to the filled address buffer and the length of the buffer for the given instance.
 \COUNTERMEASURE \N No countermeasure is necessary because the passed pointers for the address buffer pointer and the address buffer
 length are defined locally in the function and are therefore valid.

 \ID SBSW_vMem_30_XXspi01_WriteArraySpiSeqExtensionBuffer
 \DESCRIPTION A write access on the array vMem_SpiSeqExtensionBuffer[][] is performed. It must be ensured that
 the access is valid.
 \COUNTERMEASURE \N No countermeasure necessary. The array is accessed via two independent parameters. The instanceId
 is retrieved from the SeqBuilderJob structure which is previously set up with a correct instanceId.
 The source of the instanceId is always the vMem_LLProcessing() where it is ensured that only
 a valid instanceId is passed to the functions below.
 The second value is bufferIterator which is part of a for loop iteration where the max value is limited
 by flsCmdExtensionLength which specifies the length of the flash command extension and which is received
 from the generated configuration.

 \ID SBSW_vMem_30_XXspi01_FunctionCallGetRegisterSeq
 \DESCRIPTION A function is called with a pointer to the local seqBuilderJob structure.
 \COUNTERMEASURE \N No countermeasure necessary, because the local seqBuilderJob structure is valid during the call of
 vMem_FlsCmdSeqBuilder_GetRegisterSeq(Ext/Std). The values of this structure are directly copied
 to another structure. After the call of vMem_FlsCmdSeqBuilder_GetRegisterSeq(Ext/Std) returns
 the seqBuilderJob structure is no longer needed.

 \ID SBSW_vMem_30_XXspi01_LocalFlsCmdBufferAccess
 \DESCRIPTION A local 2d array is accessed and written. It must be ensured that the access is valid.
 \COUNTERMEASURE \N No countermeasure necessary. The size of the 1. dimension of this array is equal to the number
                 of vMemInstances and it's accessed using the Instance ID. The size of the 2. dimension of this array
                 is 4 and it's accessed always at index 0. Therefore, each access is valid.

 SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION

 Variant coverage:

 \ID COV_VMEM_30_XXSPI01_COMPATIBILITY
 \ACCEPT TX
 \REASON COV_MSR_COMPATIBILITY

 \ID COV_VMEM_30_XXSPI01_BYTE_ORDER
 \ACCEPT TX
 \REASON This pre-processed switch depends on the used platform. The runtime test are executed on only one platform.
         Therefore, only one setting of this switch can be covered.

 END_COVERAGE_JUSTIFICATION
 */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL_FlsCmdSeqBuilder.c
 *********************************************************************************************************************/
