/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vMem_30_XXspi01_LL_Types.h
 *        \brief  vMem_30_XXspi01_LL types header file
 *
 *      \details  Defines vMem_30_XXspi01_LL types and symbols used in the low level implementation of the vMem driver.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (VMEM_30_XXSPI01_LL_TYPES_H)
# define VMEM_30_XXSPI01_LL_TYPES_H

# include "Std_Types.h"
# include "vMemAccM_vMemApi.h"
# include "vMem_30_XXspi01_Types.h"
# include "vMem_30_XXspi01_Cfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Predefines the maximum amount of flash command items for a flash command sequence. */
#define vMem_30_XXspi01_LL_MaximumChannels 4u

/* ----- Error codes ----- */
# define VMEM_30_XXSPI01_RUNTIME_E_INITIALIZATION_FAILED       (0x20u)    /*!< used to check if no error occurred - use a value unequal to any error code. */

/*! This macro is defined to initialize the size of certain static data buffers which must be 32 bit aligned. */
# define VMEM_30_XXSPI01_32BIT_ALIGNMENT        (4u)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef P2VAR(vMem_30_XXspi01_SpiDataType, AUTOMATIC, VMEM_30_XXSPI01_APPL_VAR) vMem_30_XXspi01_SpiDataPtrType;
typedef P2CONST(vMem_30_XXspi01_SpiDataType, AUTOMATIC, VMEM_30_XXSPI01_APPL_CONST) vMem_30_XXspi01_ConstSpiDataPtrType;
typedef P2VAR(vMem_30_XXspi01_SpiDataPtrType, AUTOMATIC, VMEM_30_XXSPI01_APPL_VAR) vMem_30_XXspi01_SpiDataPtrPtrType;
typedef P2VAR(vMem_30_XXspi01_SpiLengthType, AUTOMATIC, VMEM_30_XXSPI01_APPL_VAR) vMem_30_XXspi01_SpiLengthPtrType;

/*! Predefined length of a JedecId */
#define VMEM_30_XXSPI01_JEDECID_BUFFER_LENGTH (0x04u)

/*! Type for the Device ID. */
typedef uint8 vMem_30_XXspi01_DeviceIdType;

/*! Type for pointer to a flash command. */
typedef P2CONST(uint8, AUTOMATIC, VMEM_30_XXSPI01_CONST) vMem_30_XXspi01_ConstFlsCmdPtrType;

/*! Defines the possible transmission direction for a flash command item */
typedef enum
{
  VMEM_30_XXSPI01_CMD_SEND,
  VMEM_30_XXSPI01_CMD_RECEIVE
} vMem_30_XXspi01_FlsCmdTransDirectionType;

/*! Represents a single flash command item */
typedef struct
{
  vMem_30_XXspi01_SpiChannelType SpiChannel;
  vMem_30_XXspi01_ConstSpiDataPtrType SendDataBufferPtr;
  vMem_30_XXspi01_SpiDataPtrType ReceiveDataBufferPtr;
  vMem_30_XXspi01_SpiLengthType DataBufferLength;
} vMem_30_XXspi01_FlsCmdItemType;

/*! Represents a sequence of flash commands */
typedef struct
{
  vMem_30_XXspi01_SpiSequenceType SpiSequence;
  uint8 FlsCmdItemCount;
  vMem_30_XXspi01_FlsCmdItemType FlsCmdItems[vMem_30_XXspi01_LL_MaximumChannels];
} vMem_30_XXspi01_FlsCmdSequenceType;

typedef P2VAR(vMem_30_XXspi01_FlsCmdSequenceType, AUTOMATIC, VMEM_30_XXSPI01_APPL_VAR) vMem_30_XXspi01_FlsCmdSequencePtrType;
typedef P2CONST(vMem_30_XXspi01_FlsCmdSequenceType, AUTOMATIC, VMEM_30_XXSPI01_APPL_CONST) vMem_30_XXspi01_ConstFlsCmdSequencePtrType;


#endif /* VMEM_30_XXSPI01_LL_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_Types.h
 *********************************************************************************************************************/
