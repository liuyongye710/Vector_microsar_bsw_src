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
/*!        \file  vMem_30_Fls_Types.h
 *        \brief  vMem_30_Fls types header file
 *
 *      \details  Defines vMem_30_Fls types.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (VMEM_30_FLS_TYPES_H)
# define VMEM_30_FLS_TYPES_H

# include "Std_Types.h"
# include "vMemAccM_vMemApi.h"
# include "MemIf_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef vMemAccM_vMemConstDataPtrType     vMem_30_Fls_ConstDataPtrType;
typedef vMemAccM_vMemDataPtrType          vMem_30_Fls_DataPtrType;
typedef vMemAccM_vMemJobResultType        vMem_30_Fls_JobResultType;
typedef vMemAccM_vMemInstanceIdType       vMem_30_Fls_InstanceIdType;

/* Used as address offset from the configured nv memory base address to access a certain nv memory area */
typedef vMemAccM_vMemAddressType          vMem_30_Fls_AddressType;

/* Specifies the number of bytes to read/write/erase/blank check */
typedef vMemAccM_vMemLengthType           vMem_30_Fls_LengthType;

/* Specifies the config pointer type for the init service. */
typedef vMemAccM_vMemConfigPtrType        vMem_30_Fls_ConfigPtrType;

typedef P2CONST(uint8, AUTOMATIC, VMEM_30_FLS_APPL_VAR) vMem_30_Fls_uint8ConstDataPtrType;
typedef P2VAR(uint8, AUTOMATIC, VMEM_30_FLS_APPL_VAR) vMem_30_Fls_uint8DataPtrType;

typedef uint32 vMem_30_vMemAccM_AddressType;
typedef uint32 vMem_30_vMemAccM_LengthType;

/* Function Pointer typedef for Read, Write, Erase, BlankCheck, GetJobResult services of underlying Flash Driver */
typedef P2FUNC (Std_ReturnType,  VMEM_30_FLS_CODE, vMem_30_Fls_ServiceReadType) (vMem_30_vMemAccM_AddressType SourceAddress,  vMem_30_Fls_uint8DataPtrType TargetAddressPtr, vMem_30_vMemAccM_LengthType Length );
typedef P2FUNC (Std_ReturnType,  VMEM_30_FLS_CODE, vMem_30_Fls_ServiceWriteType) (vMem_30_vMemAccM_AddressType TargetAddress, vMem_30_Fls_uint8ConstDataPtrType SourceAddressPtr, vMem_30_vMemAccM_LengthType Length );
typedef P2FUNC (Std_ReturnType,  VMEM_30_FLS_CODE, vMem_30_Fls_ServiceEraseType) (vMem_30_vMemAccM_AddressType TargetAddress, vMem_30_vMemAccM_LengthType Length );
typedef P2FUNC (Std_ReturnType,  VMEM_30_FLS_CODE, vMem_30_Fls_ServiceBlankCheckType) (vMem_30_vMemAccM_AddressType TargetAddress, vMem_30_vMemAccM_LengthType Length );
typedef P2FUNC (MemIf_JobResultType,  VMEM_30_FLS_CODE, vMem_30_Fls_ServiceGetJobResultType) (void);


/* Structure which contains the Function Pointer to services of underlying Flash Driver */
typedef struct
{
   vMem_30_Fls_InstanceIdType                   InstID;
   vMem_30_Fls_ServiceReadType                  Read;
   vMem_30_Fls_ServiceWriteType                 Write;
   vMem_30_Fls_ServiceEraseType                 Erase;
   vMem_30_Fls_ServiceBlankCheckType            BlankCheck;
   vMem_30_Fls_ServiceGetJobResultType          GetJobResult;

} vMem_30_Fls_ServicesType;


#endif /* VMEM30FLS_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem30Fls_Types.h
 *********************************************************************************************************************/
