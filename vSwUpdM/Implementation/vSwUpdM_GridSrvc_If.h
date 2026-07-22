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
/*!        \file  vSwUpdM_GridSrvc_If.h
 *        \brief  vSwUpdM_GridSrvc unit interface header file
 *      \details  Interface provided by the vSwUpdM_GridSrvc unit.
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

#if !defined (VSWUPDM_GRIDSRVC_IF_H)
# define VSWUPDM_GRIDSRVC_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* GridSrvc types header */
#include "vSwUpdM_GridSrvc_Types.h"

/* Interface header of containing MultipleUnit */
#include "vSwUpdM_Grid_If.h"

/* Other MultipleUnits used by GridSrvc_If (Prefer smallest set required, i.e. prefer _Types over _If) */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
struct vSwUpdM_GridSrvc_ResponseClassConstType_tag
{
  vSwUpdM_GridChannel_ChannelIdxType        ChannelIndex;
  vSwUpdM_GridSrvc_ResponseClassBasePtrType NodeBuffer;
  vSwUpdM_GridSrvc_ResponseClassBasePtrType AggregationBuffer;
};

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * Global Inline Functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_InitResponseClassMain
 *********************************************************************************************************************/
/*! \brief       "Constructor" function for ResponseClass.
 *  \details     Provide initialization for ResponseClass.
 *  \param[in]   Result        Initial result value.
 *  \param[out]  ResponseClass Initialized ResponseClass structure.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_InitResponseClassMain(
  Std_ReturnType Result,
  vSwUpdM_GridSrvc_ResponseClassMainPtrType ResponseClass
);

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_InitResponseClassLock
 *********************************************************************************************************************/
/*! \brief       "Constructor" function for ResponseClass.
 *  \details     Provide initialization for ResponseClass.
 *  \param[in]   Result        Initial result value.
 *  \param[out]  ResponseClass Initialized ResponseClass structure.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_InitResponseClassMaintenance(
  Std_ReturnType Result,
 vSwUpdM_GridSrvc_ResponseClassMaintenancePtrType ResponseClass
);

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_InitResponseClassSuspend
 *********************************************************************************************************************/
/*! \brief       "Constructor" function for ResponseClass.
 *  \details     Provide initialization for ResponseClass.
 *  \param[in]   Result        Initial result value.
 *  \param[out]  ResponseClass Initialized ResponseClass structure.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_InitResponseClassSuspend(
  Std_ReturnType Result,
  vSwUpdM_GridSrvc_ResponseClassSuspendPtrType ResponseClass
);

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_InitResponseClassBookkeeper
 *********************************************************************************************************************/
/*! \brief       "Constructor" function for ResponseClass.
 *  \details     Provide initialization for ResponseClass.
 *  \param[in]   Result        Initial result value.
 *  \param[out]  ResponseClass Initialized ResponseClass structure.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_InitResponseClassBookkeeper(
  Std_ReturnType Result,
  vSwUpdM_GridSrvc_ResponseClassSuspendPtrType ResponseClass
);

/**********************************************************************************************************************
 *  vSwUpdM_GridSrvc_GetResponseClassIndexOfService
 *********************************************************************************************************************/
/*! \brief       Returns the ResponseClassIndex for a given Service.
 *  \details     -
 *  \param[in]   ServiceIndex   Service index of given service.
 *  \return      ResponseClassIndex of given service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridSrvc_ResponseClassIdxType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetResponseClassIndexOfService(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex
);

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_GetChannelOfService
 *********************************************************************************************************************/
/*! \brief       Get Channel for GridService.
 *  \details     -
 *  \param[in]   ServiceIndex   Service index for which the channel shall be determined.
 *  \return      GridChannel of given service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridChannel_ChannelIdxType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetChannelOfService(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridSrvc_GetResponseClassNodeBuffer
 *********************************************************************************************************************/
/*! \brief       Returns the ResponseClass Buffer for a given Service.
 *  \details     -
 *  \param[in]   ServiceIndex   Service index of given service.
 *  \return      Pointer to ResponseClassNode buffer of given service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridSrvc_ResponseClassBasePtrType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetResponseClassNodeBuffer( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridSrvc_GetResponseClassAggregationBuffer
 *********************************************************************************************************************/
/*! \brief       Returns the ResponseClass Aggregated Result for a given Service.
 *  \details     -
 *  \param[in]   ServiceIndex   Service index of given service.
 *  \return      Pointer to aggregation buffer buffer of given service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
  *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridSrvc_ResponseClassBasePtrType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetResponseClassAggregationBuffer( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex
);

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_GetServiceClassOfService
 *********************************************************************************************************************/
/*! \brief       Get ServiceClass for GridService of given service.
 *  \details     -
 *  \param[in]   ServiceIndex   Service index of given service.
 *  \return      ServiceClass of Service
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(SwUpdM_GridSrvc_ServiceClassType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetServiceClassOfService(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex
);

/**********************************************************************************************************************
 * Global Functions
 *********************************************************************************************************************/

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_GRIDSRVC_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_GridSrvc_If.h
 *********************************************************************************************************************/
