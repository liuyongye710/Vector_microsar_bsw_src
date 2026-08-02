/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Fls_30_vMemAccM_Privates.h
 *        \brief  Fls_30_vMemAccM privates header file
 *
 *      \details  Defines Fls_30_vMemAccM privates:
 *                Fls_30_vMemAccM_TargetAddressAreaId and vMemAccM header file inclusion should not be make public to the module above (Fee),
 *                which will include Fls_30_vMemAccM.h.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (FLS_30_VMEMACCM_PRIVATES_H)
# define FLS_30_VMEMACCM_PRIVATES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"
#include "vMemAccM.h"

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#define FLS_30_VMEMACCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
extern CONST(vMemAccM_AddressAreaIdType, FLS_30_VMEMACCM_CONST) Fls_30_vMemAccM_TargetAddressAreaId;
#define FLS_30_VMEMACCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* FLS_30_VMEMACCM_PRIVATES_H */

/**********************************************************************************************************************
 *  END OF FILE: Fls_30_vMemAccM_Privates.h
 *********************************************************************************************************************/
