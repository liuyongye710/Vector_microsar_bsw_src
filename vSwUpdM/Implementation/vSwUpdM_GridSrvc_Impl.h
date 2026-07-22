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
/*!        \file  vSwUpdM_GridSrvc_Impl.h
 *        \brief  vSwUpdM_GridSrvc implementation header file
 *      \details  vSwUpdM_GridSrvc subcomponent public inline implementations.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vSwUpdM.h.
 *********************************************************************************************************************/

#if !defined (VSWUPDM_GRIDSRVC_IMPL_H)
# define VSWUPDM_GRIDSRVC_IMPL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* GridSrvc interface header */
#include "vSwUpdM_GridSrvc_If.h"

/* Implementation header of containing MultipleUnit */
#include "vSwUpdM_Grid_Impl.h"

/* Other MultipleUnits used by GridSrvc_Impl (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(vSwUpdM_GridSrvc_ResponseClassMainType, VSWUPDM_APPL_DATA)              vSwUpdM_GridSrvc_ResponseMain_Aggregated;
extern VAR(vSwUpdM_GridSrvc_ResponseClassSuspendType, VSWUPDM_APPL_DATA)           vSwUpdM_GridSrvc_ResponseSuspend_Aggregated;
extern VAR(vSwUpdM_GridSrvc_ResponseClassMaintenanceType, VSWUPDM_APPL_DATA)       vSwUpdM_GridSrvc_ResponseMaintenance_Aggregated;
extern VAR(vSwUpdM_GridSrvc_ResponseClassBookkeeperType, VSWUPDM_APPL_DATA)        vSwUpdM_GridSrvc_ResponseBookkeeper_Aggregated;

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA S 3684 1 */ /* MD_vSwUpdM_Rule8.11_3684_ConfigStructure */
extern CONST(vSwUpdM_GridSrvc_ServiceType, VSWUPDM_CONST) vSwUpdM_GridSrvc_Service[];

extern CONST(vSwUpdM_GridSrvc_ResponseClassConstType, VSWUPDM_CONST) vSwUpdM_GridSrvc_ResponseClassConst[VSWUPDM_GRIDSRVC_RESPONSECLASS_COUNT];

#define VSWUPDM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_InitResponseClassMain
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_InitResponseClassMain(
  Std_ReturnType Result,
  vSwUpdM_GridSrvc_ResponseClassMainPtrType ResponseClass
)
{
  ResponseClass->Base.ResponseClassIndex = VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN;
  ResponseClass->Result = Result;
} /* vSwUpdM_GridSrvc_ResponseClassMain */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_InitResponseClassMaintenance
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_InitResponseClassMaintenance(
  Std_ReturnType Result,
  vSwUpdM_GridSrvc_ResponseClassMaintenancePtrType ResponseClass
)
{
  ResponseClass->Base.ResponseClassIndex = VSWUPDM_GRIDSRVC_RESPONSECLASS_MAINTENANCE;
  ResponseClass->Result = Result;
} /* vSwUpdM_GridSrvc_InitResponseClassMaintenance */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_InitResponseClassSuspend
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_InitResponseClassSuspend(
  Std_ReturnType Result,
  vSwUpdM_GridSrvc_ResponseClassSuspendPtrType ResponseClass
)
{
  ResponseClass->Base.ResponseClassIndex = VSWUPDM_GRIDSRVC_RESPONSECLASS_SUSPEND;
  ResponseClass->Result = Result;
} /* vSwUpdM_GridSrvc_ResponseClassSuspend */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_InitResponseClassBookkeeper
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_InitResponseClassBookkeeper(
  Std_ReturnType Result,
  vSwUpdM_GridSrvc_ResponseClassSuspendPtrType ResponseClass
)
{
  ResponseClass->Base.ResponseClassIndex = VSWUPDM_GRIDSRVC_RESPONSECLASS_BK;
  ResponseClass->Result = Result;
} /* vSwUpdM_GridSrvc_InitResponseClassBookkeeper */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_GetResponseClassIndexOfService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridSrvc_ResponseClassIdxType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetResponseClassIndexOfService(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex
)
{
  return vSwUpdM_GridSrvc_Service[ServiceIndex].ResponseClassIndex;
} /* vSwUpdM_GridSrvc_GetResponseClassIndexOfService */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_GetChannelOfService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridChannel_ChannelIdxType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetChannelOfService(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex
)
{
  return vSwUpdM_GridSrvc_ResponseClassConst[vSwUpdM_GridSrvc_GetResponseClassIndexOfService(ServiceIndex)].ChannelIndex;
} /* vSwUpdM_GridSrvc_GetChannelOfService */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_GetResponseClassNodeBuffer
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridSrvc_ResponseClassBasePtrType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetResponseClassNodeBuffer( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex
)
{
  return vSwUpdM_GridSrvc_ResponseClassConst[vSwUpdM_GridSrvc_GetResponseClassIndexOfService(ServiceIndex)].NodeBuffer;
} /* vSwUpdM_GridSrvc_GetResponseClassNodeBuffer */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_GetResponseClassAggregationBuffer
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridSrvc_ResponseClassBasePtrType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetResponseClassAggregationBuffer( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex
)
{
  return vSwUpdM_GridSrvc_ResponseClassConst[vSwUpdM_GridSrvc_GetResponseClassIndexOfService(ServiceIndex)].AggregationBuffer;
} /* vSwUpdM_GridSrvc_GetResponseClassAggregationBuffer */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_GetServiceClassOfService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(SwUpdM_GridSrvc_ServiceClassType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetServiceClassOfService(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex
)
{
  return vSwUpdM_GridSrvc_Service[ServiceIndex].ServiceClass;
} /* vSwUpdM_GridSrvc_GetServiceClassOfService */

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_GRIDSRVC_IMPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_GridSrvc_Impl.h
 *********************************************************************************************************************/
