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
/*        \file   vFotaH_Types.h
 *        \brief  vFotaH_Types header file
 *
 *        \details
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

#ifndef VFOTAH_TYPES_H
#define VFOTAH_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Compiler.h"
#include "ComStack_Types.h"
#include "vSwUpdM_Types.h"
#include "vFotaH_Lcfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#ifndef INLINE
# define INLINE inline
#endif

#ifndef STATIC
# define STATIC static
#endif

#ifndef VFOTAH_LOCAL
# define VFOTAH_LOCAL STATIC
#endif

#ifndef LOCAL_INLINE
# define LOCAL_INLINE STATIC INLINE
#endif

#ifndef VFOTAH_LOCAL_INLINE
# define VFOTAH_LOCAL_INLINE LOCAL_INLINE
#endif

#ifndef ALWAYS_LOCAL_INLINE
# define ALWAYS_LOCAL_INLINE STATIC INLINE
#endif

#ifndef VFOTAH_ALWAYS_INLINE
# define VFOTAH_ALWAYS_INLINE ALWAYS_LOCAL_INLINE
#endif

# ifndef VFOTAH_E_PENDING
#  ifdef E_PENDING
#   define VFOTAH_E_PENDING                                      E_PENDING
#  else
#   define VFOTAH_E_PENDING                                      2u
#  endif
# endif


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* General types: */
typedef uint8 vFotaH_StateType;
typedef uint8 vFotaH_FotaStateType;
typedef Std_ReturnType vFotaH_ReturnType;
typedef uint8 vFotaH_DownloadStateType;
typedef uint8 vFotaH_ErrorCodeType; /*!< Error code: Type for error codes */

typedef uint32 vFotaH_AddrType;
typedef uint32 vFotaH_LengthType;

typedef struct
{
  uint16                LogBlockId;
  uint8                 ModuleHd;
  volatile uint8        StartRequest;
  uint8                 RoutineOp;
  boolean               ModuleInfoValid;
  boolean               UpdateStartValid;
} vFotaH_StartRequestType;
                           
typedef struct
{
  volatile uint8        EraseRequest;
} vFotaH_EraseRequestType; /*!< Erase request:
                            *     Type for holding the state information of the erase routine. */

typedef struct
{
  volatile uint8  SwitchBankRequest;
  uint8   SwitchOption;
  boolean ResetPending;
} vFotaH_SwitchBankRequestType; /*!< Switch bank request:
                                 *     Type for holding the state information of the switch routine. */

typedef struct
{
  uint16 SizeofVerifyData;
  volatile uint8  VerifyModuleRequest;
  uint8  VerifyData[VFOTAH_SIZE_OF_SIGNATURE];
  uint8  VerifyOption;
} vFotaH_VerifyModuleType; /*!< Verify Module request:
                            *     Type for holding the state information of the verify routine. */

typedef struct
{
  volatile uint8 PrepareActivationRequest;
} vFotaH_PrepareActivationType; /*!< Prepare Activation request:
                                 *     Type for holding the state information of the prepare activation routine. */

typedef struct
{
  volatile uint8  UpdateCommitRequest;
} vFotaH_UpdateCommitType; /*!< Update Commit request:
                            *     Type for holding the state information of the update commit routine. */

/* Data structs: */
typedef struct
{
  P2VAR(uint8, AUTOMATIC, VFOTAH_APPL_VAR) DcmSourceBufferPtr;
  uint32                Address;
  uint32                DataSize;
  uint32                RemainingBlockSize;
  uint32                BlockSize;
  uint32                MaxBlockSize;
  uint32                BytesProcessed;
  uint16                LogBlockId;
  uint8                 SeqCnt;
} vFotaH_DownloadDataType; /*!< Download data: Type for holding the complete download data of one segment. */


typedef struct
{
  uint32 MemAddress;
  uint32 MemSize;
  vSwUpdM_ProcessingOperationType ProcessingInfo;
  uint8  MemAddressLength;
  uint8  MemSizeLength;
  boolean IsMemDataValid;
} vFotaH_DownloadMessageInfoType; /*!< Download message info:
                                  *     Type for holding the download information required for currently processed
                                  *     block. */


/* State types: */
typedef uint8 vFotaH_InitializationStateType; /*!< Initialization state:
                                               *     Type for initialization and shutdown state handling. */

typedef struct
{
  uint8   SwitchBankRequest;
  uint8   ModuleStatus;
  uint8   Fingerprint_Active[VFOTAH_FINGERPRINT_SIZE];
  uint8   Fingerprint_Inactive[VFOTAH_FINGERPRINT_SIZE];
} vFotaH_NvMInfoBlockType; /*!< NvMInfoBlock:
                            *     Type for holding the the fingerprint and switch Bank state. The fingerprint is
                            *     application specific. */


typedef struct
{
  uint8   Fingerprint[VFOTAH_FINGERPRINT_SIZE];
  boolean FingerprintValid;
} vFotaH_FingerprintType; /*!< Fingerprint RAM repesentation:
                            *     Temporary fingerprint RAM representation used during erase operation. */

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif /* VFOTAH_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: vFotaH_Types.h
 *********************************************************************************************************************/
