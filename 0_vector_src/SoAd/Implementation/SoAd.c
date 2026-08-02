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
/*!        \file  SoAd.c
 *        \brief  Socket Adaptor source file
 *
 *      \details  Vector static code implementation for AUTOSAR Socket Adaptor module.
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

/* PRQA S 1881 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA S 4304 EOF */ /* MD_MSR_AutosarBoolean */

#define SOAD_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "SoAd.h"
#include "SoAd_Priv.h"
#include "SoAd_Cbk.h"
#include "SoAd_EventQueue.h"
#include "SoAd_TimeoutList.h"
#include "SoAd_SoCon.h"
#include "SoAd_RouteGrp.h"
#include "SoAd_Util.h"
#include "SoAd_Tx.h"
#include "SoAd_Rx.h"
#include "SoAd_Anomaly.h"
#include "SoAd_GenTcpIpApi.h"
#include "SoAd_State_Int.h"

#include "IpBase.h"
#if ( SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE == SOAD_CONFIGURATION_VARIANT )
# include "EcuM_Error.h"
#endif /* SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE == SOAD_CONFIGURATION_VARIANT */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of SoAd header file */
#if ( (SOAD_SW_MAJOR_VERSION != 19u) \
    || (SOAD_SW_MINOR_VERSION != 4u) \
    || (SOAD_SW_PATCH_VERSION != 0u) )
# error "Vendor specific version numbers of SoAd.c and SoAd.h are inconsistent"
#endif /* (SOAD_SW_MAJOR_VERSION != 19u) \
    || (SOAD_SW_MINOR_VERSION != 4u) \
    || (SOAD_SW_PATCH_VERSION != 0u) */

/* Check configuration variant for building the library */
#if ( (defined(V_EXTENDED_BUILD_LIB_CHECK)) && (SOAD_CONFIGURATION_VARIANT_PRECOMPILE == SOAD_CONFIGURATION_VARIANT) )
# error "SoAd.c: Switch configuration variant to link-time or post-build for library build!"
#endif /* (defined(V_EXTENDED_BUILD_LIB_CHECK)) &&
  (SOAD_CONFIGURATION_VARIANT_PRECOMPILE == SOAD_CONFIGURATION_VARIANT) */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (SOAD_LOCAL) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL static
#endif /* !defined (SOAD_LOCAL) */

#if !defined (SOAD_LOCAL_INLINE) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL_INLINE LOCAL_INLINE
#endif /* !defined (SOAD_LOCAL_INLINE) */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define SOAD_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "SoAd_MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/*! Pointer to the post-build configuration. */
P2CONST(SoAd_ConfigType, SOAD_VAR_CLEARED, SOAD_PBCFG) SoAd_ConfigDataPtr = NULL_PTR;

#define SOAD_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "SoAd_MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
/**********************************************************************************************************************
 *  SoAd_CheckIpAddrAssignmentType()
 *********************************************************************************************************************/
/*! \brief      Checks value range of variables of type SoAd_IpAddrAssignmentType.
 *  \details    -
 *  \pre        -
 *  \param[in]  Type          IP address type.
 *  \return     E_OK          Type is in valid range.
 *  \return     E_NOT_OK      Type is invalid.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_DEV_ERROR_DETECT
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckIpAddrAssignmentType(
  SoAd_IpAddrAssignmentType Type);

# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
/**********************************************************************************************************************
 *  SoAd_CheckApplicationIdValidity()
 *********************************************************************************************************************/
/*! \brief      Checks the validity of the OS application identifier and the SoAd partition index.
 *  \details    -
 *  \pre        -
 *  \param[in]  PartitionIdx  Partition index.
 *                            [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \return     E_OK          Application identifier is valid and matches to the partition index.
 *  \return     E_NOT_OK      Application identifier does not match to partition index.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE
 *  \config     SOAD_DEV_ERROR_DETECT & SOAD_MULTI_PARTITION
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckApplicationIdValidity(
  SoAd_PartitionConfigIdxType PartitionIdx);
# endif /* SOAD_MULTI_PARTITION == STD_ON */

/**********************************************************************************************************************
 *  SoAd_CheckAndGetTxPduId()
 *********************************************************************************************************************/
/*! \brief      Checks the validity of the Tx PDU map identifier and gets the partition specific index.
 *  \details    -
 *  \pre        -
 *  \param[in]  TxPduMapId      Tx PDU map identifier.
 *  \param[out] PduRouteIdxPtr  Pointer to the partition specific PduRouteIdx.
 *  \param[out] PartitionIdxPtr Pointer to the partition index of the PduRoute.
 *  \return     E_OK            Tx PDU map identifier is inside valid range.
 *  \return     E_NOT_OK        Tx PDU map identifier is not inside valid range.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_DEV_ERROR_DETECT
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckAndGetTxPduId(
  PduIdType TxPduMapId,
  P2VAR(SoAd_SizeOfPduRouteType, AUTOMATIC, SOAD_APPL_DATA) PduRouteIdxPtr,
  P2VAR(SoAd_PartitionConfigIdxType, AUTOMATIC, SOAD_APPL_DATA) PartitionIdxPtr);

/**********************************************************************************************************************
 *  SoAd_CheckAndGetRxPduId()
 *********************************************************************************************************************/
/*! \brief      Checks the validity of the Rx PDU map identifier and gets the partition specific index.
 *  \details    -
 *  \pre        -
 *  \param[in]  RxPduMapId             Rx PDU map identifier.
 *  \param[out] SocketRouteDestIdxPtr  Pointer to the partition specific SocketRouteDestIdx.
 *  \param[out] PartitionIdxPtr        Pointer to the partition index of the SocketRouteDest.
 *  \return     E_OK                   Rx PDU map identifier is inside valid range.
 *  \return     E_NOT_OK               Rx PDU map identifier is not inside valid range.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_DEV_ERROR_DETECT
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckAndGetRxPduId(
  PduIdType RxPduMapId,
  P2VAR(SoAd_SizeOfSocketRouteDestType, AUTOMATIC, SOAD_APPL_DATA) SocketRouteDestIdxPtr,
  P2VAR(SoAd_PartitionConfigIdxType, AUTOMATIC, SOAD_APPL_DATA) PartitionIdxPtr);

/**********************************************************************************************************************
 *  SoAd_CheckAndGetSoConId()
 *********************************************************************************************************************/
/*! \brief      Checks the validity of the socket connection map identifier and gets the partition specific index.
 *  \details    -
 *  \pre        -
 *  \param[in]  SoConMapId      SoCon map identifier.
 *  \param[out] SoConIdxPtr     Pointer to the partition specific SoConIdx.
 *  \param[out] PartitionIdxPtr Pointer to the partition index of the SoCon.
 *  \return     E_OK            SoCon map identifier is inside valid range.
 *  \return     E_NOT_OK        SoCon map identifier is not inside valid range.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_DEV_ERROR_DETECT
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckAndGetSoConId(
  SoAd_SoConIdType SoConMapId,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxPtr,
  P2VAR(SoAd_PartitionConfigIdxType, AUTOMATIC, SOAD_APPL_DATA) PartitionIdxPtr);
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */

/**********************************************************************************************************************
 *  SoAd_CheckAndGetRouteGrp()
 *********************************************************************************************************************/
/*! \brief      Checks if the routing group ID is used by SoAd and gets the partition specific index if available.
 *  \details    -
 *  \pre        -
 *  \param[in]  RouteGrpMapId   Routing group map identifier.
 *  \param[out] RouteGrpIdxPtr  Pointer to the partition specific RouteGrpIdx.
 *  \param[out] PartitionIdxPtr Pointer to the partition index of the RouteGrp.
 *  \return     E_OK            RouteGrp map identifier is inside valid range.
 *  \return     E_NOT_OK        RouteGrp map identifier is not inside valid range.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckAndGetRouteGrp(
  SoAd_RoutingGroupIdType RouteGrpMapId,
  P2VAR(SoAd_SizeOfRouteGrpType, AUTOMATIC, SOAD_APPL_DATA) RouteGrpIdxPtr,
  P2VAR(SoAd_PartitionConfigIdxType, AUTOMATIC, SOAD_APPL_DATA) PartitionIdxPtr);

/**********************************************************************************************************************
 *  SoAd_CheckAndGetLocalAddr()
 *********************************************************************************************************************/
/*! \brief      Checks if the IP address ID is used by SoAd and gets the partition specific index if available.
 *  \details    -
 *  \pre        -
 *  \param[in]  IpAddrId        IP address identifier.
 *  \param[out] LocalAddrIdxPtr Pointer to the partition specific LocalAddrIdx.
 *  \param[out] PartitionIdxPtr Pointer to the partition index of the LocalAddr.
 *  \return     E_OK            IP address identifier is inside valid range.
 *  \return     E_NOT_OK        IP address identifier is not inside valid range.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckAndGetLocalAddr(
  SoAd_LocalAddrIdType IpAddrId,
  P2VAR(SoAd_SizeOfLocalAddrType, AUTOMATIC, SOAD_APPL_DATA) LocalAddrIdxPtr,
  P2VAR(SoAd_PartitionConfigIdxType, AUTOMATIC, SOAD_APPL_DATA) PartitionIdxPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
/**********************************************************************************************************************
 *  SoAd_CheckIpAddrAssignmentType()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckIpAddrAssignmentType(
  SoAd_IpAddrAssignmentType Type)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if IP address assignment type is in valid range. */
  if ( (Type == SOAD_IPADDR_ASSIGNMENT_STATIC) ||
    (Type == SOAD_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP) ||
    (Type == SOAD_IPADDR_ASSIGNMENT_DHCP) ||
    (Type == SOAD_IPADDR_ASSIGNMENT_LINKLOCAL) ||  /* PRQA S 2996 */ /* MD_SoAd_MacroRedundantCheck */
    (Type == SOAD_IPADDR_ASSIGNMENT_IPV6_ROUTER) )
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_CheckIpAddrAssignmentType() */

# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
/**********************************************************************************************************************
 *  SoAd_CheckApplicationIdValidity()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckApplicationIdValidity(
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ApplicationType             osApplicationId = (ApplicationType)GetApplicationID();
  Std_ReturnType              retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the OS application identifier contains a valid value. */
  if ( osApplicationId >= INVALID_OSAPPLICATION )
  {
    retVal = E_NOT_OK;
  }
  /* #20 Check if the mapped OS application ID of the partition does not match to the OS application ID otherwise. */
  else if ( SoAd_GetOsApplicationIdOfPartition(0u, PartitionIdx) != osApplicationId )
  {
    retVal = E_NOT_OK;
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_CheckApplicationIdValidity() */
# endif /* SOAD_MULTI_PARTITION == STD_ON */

/**********************************************************************************************************************
 *  SoAd_CheckAndGetTxPduId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckAndGetTxPduId(
  PduIdType TxPduMapId,
  P2VAR(SoAd_SizeOfPduRouteType, AUTOMATIC, SOAD_APPL_DATA) PduRouteIdxPtr,
  P2VAR(SoAd_PartitionConfigIdxType, AUTOMATIC, SOAD_APPL_DATA) PartitionIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the Tx PDU map identifier is inside the valid range. */
  if ( TxPduMapId < SoAd_GetSizeOfTxPduIdMap() )
  {
    /* #20 Get the partition specific PDU route index and the corresponding partition index. */
    *PduRouteIdxPtr = SoAd_GetPartitionSpecificPduRouteIdxOfTxPduIdMap(TxPduMapId);                                    /* SBSW_SOAD_POINTER_WRITE */
    *PartitionIdxPtr = SoAd_GetPartitionSpecificPduRoutePartitionIdxOfTxPduIdMap(TxPduMapId);                          /* SBSW_SOAD_POINTER_WRITE */
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_CheckAndGetTxPduId() */

/**********************************************************************************************************************
 *  SoAd_CheckAndGetRxPduId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckAndGetRxPduId(
  PduIdType RxPduMapId,
  P2VAR(SoAd_SizeOfSocketRouteDestType, AUTOMATIC, SOAD_APPL_DATA) SocketRouteDestIdxPtr,
  P2VAR(SoAd_PartitionConfigIdxType, AUTOMATIC, SOAD_APPL_DATA) PartitionIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the Rx PDU map identifier is inside the valid range. */
  if ( RxPduMapId < SoAd_GetSizeOfRxPduIdIdMap() )
  {
    /* #20 Get the partition specific socket route destination index and the corresponding partition index. */
    *SocketRouteDestIdxPtr = SoAd_GetPartitionSpecificSocketRouteDestIdxOfRxPduIdIdMap(RxPduMapId);                    /* SBSW_SOAD_POINTER_WRITE */
    *PartitionIdxPtr = SoAd_GetPartitionSpecificSocketRouteDestPartitionIdxOfRxPduIdIdMap(RxPduMapId);                 /* SBSW_SOAD_POINTER_WRITE */
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_CheckAndGetRxPduId() */

/**********************************************************************************************************************
 *  SoAd_CheckAndGetSoConId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckAndGetSoConId(
  SoAd_SoConIdType SoConMapId,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxPtr,
  P2VAR(SoAd_PartitionConfigIdxType, AUTOMATIC, SOAD_APPL_DATA) PartitionIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the socket connection map identifier is inside the valid range. */
  if ( SoConMapId < SoAd_GetSizeOfSoConMap() )
  {
    /* #20 Get the partition specific socket connection index and the corresponding partition index. */
    *SoConIdxPtr = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConMapId);                                            /* SBSW_SOAD_POINTER_WRITE */
    *PartitionIdxPtr = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConMapId);                               /* SBSW_SOAD_POINTER_WRITE */
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_CheckAndGetSoConId() */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */

/**********************************************************************************************************************
 *  SoAd_CheckAndGetRouteGrp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckAndGetRouteGrp(
  SoAd_RoutingGroupIdType RouteGrpMapId,
  P2VAR(SoAd_SizeOfRouteGrpType, AUTOMATIC, SOAD_APPL_DATA) RouteGrpIdxPtr,
  P2VAR(SoAd_PartitionConfigIdxType, AUTOMATIC, SOAD_APPL_DATA) PartitionIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the routing group is mapped to any partition. */
  if ( SoAd_IsPartitionSpecificRouteGrpUsedOfRouteGrpIdMap(RouteGrpMapId) )
  {
    /* #20 Get the partition specific routing group index and the corresponding partition index. */
    *RouteGrpIdxPtr = SoAd_GetPartitionSpecificRouteGrpIdxOfRouteGrpIdMap(RouteGrpMapId);                              /* SBSW_SOAD_POINTER_WRITE */
    *PartitionIdxPtr = SoAd_GetPartitionSpecificRouteGrpPartitionIdxOfRouteGrpIdMap(RouteGrpMapId);                    /* SBSW_SOAD_POINTER_WRITE */
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_CheckAndGetRouteGrp() */

/**********************************************************************************************************************
 *  SoAd_CheckAndGetLocalAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckAndGetLocalAddr(
  SoAd_LocalAddrIdType IpAddrId,
  P2VAR(SoAd_SizeOfLocalAddrType, AUTOMATIC, SOAD_APPL_DATA) LocalAddrIdxPtr,
  P2VAR(SoAd_PartitionConfigIdxType, AUTOMATIC, SOAD_APPL_DATA) PartitionIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the local address is mapped to any partition. */
  if ( SoAd_IsPartitionSpecificLocalAddrUsedOfLocalAddrIdMap(IpAddrId) )
  {
    /* #20 Get the partition specific local address index and the corresponding partition index. */
    *LocalAddrIdxPtr = SoAd_GetPartitionSpecificLocalAddrIdxOfLocalAddrIdMap(IpAddrId);                                /* SBSW_SOAD_POINTER_WRITE */
    *PartitionIdxPtr = SoAd_GetPartitionSpecificLocalAddrPartitionIdxOfLocalAddrIdMap(IpAddrId);                       /* SBSW_SOAD_POINTER_WRITE */
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_CheckAndGetLocalAddr() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_IfTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_IfTransmit(
  PduIdType SoAdSrcPduId,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) SoAdSrcPduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType     pduRouteIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType              retVal = E_NOT_OK;
#else
  Std_ReturnType              retVal;
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAd_CheckAndGetTxPduId(SoAdSrcPduId, &pduRouteIdx, &partitionIdx) == E_NOT_OK)                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfTxPduIdMap(SoAdSrcPduId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoAd_GetUpperLayerApiOfPduRoute(pduRouteIdx, partitionIdx) == SOAD_UL_API_TP )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoAdSrcPduInfoPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  /* Check trigger transmit with meta data use case:
   * If trigger transmit and meta data is enabled data pointer with meta data must be provided. */
  else if ( (SoAd_GetIfTriggerTransmitModeOfPduRoute(pduRouteIdx, partitionIdx) != SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE)
    && (SoAd_IsMetaDataTxEnabledOfPduRoute(pduRouteIdx, partitionIdx) == TRUE) &&
    (SoAdSrcPduInfoPtr->SduDataPtr == NULL_PTR) )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  /* Check trigger transmit use case:
   * If no data pointer is provided trigger transmit is required. */
  else if ( (SoAdSrcPduInfoPtr->SduDataPtr == NULL_PTR) && (SoAd_GetIfTriggerTransmitModeOfPduRoute(pduRouteIdx,
        partitionIdx) == SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE) )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
    pduRouteIdx = SoAd_GetPartitionSpecificPduRouteIdxOfTxPduIdMap(SoAdSrcPduId);
    partitionIdx = SoAd_GetPartitionSpecificPduRoutePartitionIdxOfTxPduIdMap(SoAdSrcPduId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

    /* #30 Trigger transmission of PDU. */
    retVal = SoAd_Tx_IfTransmit(pduRouteIdx, partitionIdx, SoAdSrcPduInfoPtr, &errorId);                               /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_IF_TRANSMIT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_IfTransmit() */

/**********************************************************************************************************************
 *  SoAd_IfRoutingGroupTransmit()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_IfRoutingGroupTransmit(
  SoAd_RoutingGroupIdType id)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRouteGrpType     routeGrpIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (id >= SoAd_GetSizeOfRouteGrpIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRouteGrpIdMap(id)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  if ( SoAd_CheckAndGetRouteGrp(id, &routeGrpIdx, &partitionIdx) == E_NOT_OK )                                         /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    /* This is a valid use-case. No DETs are expected when the routing group is not mapped to any partition. */
  }
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  else if ( !SoAd_IsTxTriggerableOfRouteGrp(routeGrpIdx, partitionIdx) )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  /* PRQA S 3415 2 */ /* MD_SoAd_RightHandOperandWithoutSideEffects */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check initialization state to reject request in case of shutdown. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
      /* #40 Set transmission request for all related PduRouteDests. */
      SoAd_RouteGrp_SetIfTransmit(routeGrpIdx, partitionIdx);

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_IF_ROUT_GROUP_TRANSMIT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_IfRoutingGroupTransmit() */

/**********************************************************************************************************************
 *  SoAd_IfSpecificRoutingGroupTransmit()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_IfSpecificRoutingGroupTransmit(
  SoAd_RoutingGroupIdType id,
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRouteGrpType     routeGrpIdx;
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType routeGrpPartitionIdx;
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  SoAd_PartitionConfigIdxType soConPartitionIdx;
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  uint8                       errorId = SOAD_E_NO_ERROR;
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (id >= SoAd_GetSizeOfRouteGrpIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRouteGrpIdMap(id)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  if ( SoAd_CheckAndGetRouteGrp(id, &routeGrpIdx, &routeGrpPartitionIdx) == E_NOT_OK )                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    /* This is a valid use-case. No DETs are expected when the routing group is not mapped to any partition. */
  }
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  else if ( !SoAd_IsTxTriggerableOfRouteGrp(routeGrpIdx, routeGrpPartitionIdx) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &soConPartitionIdx) == E_NOT_OK)                              /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  /* PRQA S 3415 2 */ /* MD_SoAd_RightHandOperandWithoutSideEffects */
  else if ( SoAd_CheckApplicationIdValidity(routeGrpPartitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
  else if ( SoAd_CheckApplicationIdValidity(soConPartitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check initialization state to reject request in case of shutdown. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Set transmission request for the related PduRouteDest. */
      retVal = SoAd_RouteGrp_SetIfSpecificTransmit(routeGrpIdx, soConIdx, routeGrpPartitionIdx);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_IF_SPEC_ROUT_GROUP_TRANSMIT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_IfSpecificRoutingGroupTransmit() */

/**********************************************************************************************************************
 *  SoAd_TpTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TpTransmit(
  PduIdType SoAdSrcPduId,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) SoAdSrcPduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType     pduRouteIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType              retVal = E_NOT_OK;
#else
  Std_ReturnType              retVal;
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAd_CheckAndGetTxPduId(SoAdSrcPduId, &pduRouteIdx, &partitionIdx) == E_NOT_OK)                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfTxPduIdMap(SoAdSrcPduId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoAd_GetUpperLayerApiOfPduRoute(pduRouteIdx, partitionIdx) == SOAD_UL_API_IF )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoAdSrcPduInfoPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
    pduRouteIdx = SoAd_GetPartitionSpecificPduRouteIdxOfTxPduIdMap(SoAdSrcPduId);
    partitionIdx = SoAd_GetPartitionSpecificPduRoutePartitionIdxOfTxPduIdMap(SoAdSrcPduId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

    /* #30 Request transmission of PDU. */
    retVal = SoAd_Tx_TpTransmit(pduRouteIdx, partitionIdx, SoAdSrcPduInfoPtr);                                         /* SBSW_SOAD_POINTER_FORWARD */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TP_TRANSMIT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_TpTransmit() */

/**********************************************************************************************************************
 *  SoAd_TpCancelTransmit()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TpCancelTransmit(
  PduIdType PduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType     pduRouteIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (SoAd_CheckAndGetTxPduId(PduId, &pduRouteIdx, &partitionIdx) == E_NOT_OK)                                  /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfTxPduIdMap(PduId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoAd_GetUpperLayerApiOfPduRoute(pduRouteIdx, partitionIdx) == SOAD_UL_API_IF )
  {
    errorId = SOAD_E_INV_PDUID;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      pduRouteIdx = SoAd_GetPartitionSpecificPduRouteIdxOfTxPduIdMap(PduId);
      partitionIdx = SoAd_GetPartitionSpecificPduRoutePartitionIdxOfTxPduIdMap(PduId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Store cancellation request. */
      retVal = SoAd_Tx_TpCancelTransmit(pduRouteIdx, partitionIdx);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TP_CANCEL_TRANSMIT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_TpCancelTransmit() */

/**********************************************************************************************************************
 *  SoAd_TpCancelReceive()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TpCancelReceive(
  PduIdType PduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketRouteDestType sockRouteDestIdx;
  SoAd_PartitionConfigIdxType    partitionIdx;
  uint8                          errorId = SOAD_E_NO_ERROR;
  Std_ReturnType                 retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (SoAd_CheckAndGetRxPduId(PduId, &sockRouteDestIdx, &partitionIdx) == E_NOT_OK)                             /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRxPduIdIdMap(PduId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoAd_GetUpperLayerApiOfSocketRoute(SoAd_GetSocketRouteIdxOfSocketRouteDest(sockRouteDestIdx, partitionIdx),
      partitionIdx) == SOAD_UL_API_IF )
  {
    errorId = SOAD_E_INV_PDUID;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      sockRouteDestIdx = SoAd_GetPartitionSpecificSocketRouteDestIdxOfRxPduIdIdMap(PduId);
      partitionIdx = SoAd_GetPartitionSpecificSocketRouteDestPartitionIdxOfRxPduIdIdMap(PduId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Store cancellation request. */
      retVal = SoAd_Rx_TpCancelReceive(sockRouteDestIdx, partitionIdx);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TP_CANCEL_RECEIVE, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_TpCancelReceive() */

/**********************************************************************************************************************
 *  SoAd_GetSoConId()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetSoConId(
  PduIdType TxPduId,
  P2VAR(SoAd_SoConIdType, AUTOMATIC, SOAD_APPL_VAR) SoConIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType     pduRouteIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  SoAd_SizeOfPduRouteDestType pduRouteDestIdx;
  SoAd_SizeOfSoConType        soConIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAd_CheckAndGetTxPduId(TxPduId, &pduRouteIdx, &partitionIdx) == E_NOT_OK)                                /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfTxPduIdMap(TxPduId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( (SoAd_GetPduRouteDestEndIdxOfPduRoute(pduRouteIdx, partitionIdx) -
      SoAd_GetPduRouteDestStartIdxOfPduRoute(pduRouteIdx, partitionIdx)) != 1u )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoConIdPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
      /* #40 Return corresponding socket connection identifier. */
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      pduRouteIdx = SoAd_GetPartitionSpecificPduRouteIdxOfTxPduIdMap(TxPduId);
      partitionIdx = SoAd_GetPartitionSpecificPduRoutePartitionIdxOfTxPduIdMap(TxPduId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */
      pduRouteDestIdx = SoAd_GetPduRouteDestStartIdxOfPduRoute(pduRouteIdx, partitionIdx);
      soConIdx = SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIdx, partitionIdx);

      *SoConIdPtr = SoAd_GetSoConIdOfSoCon(soConIdx, partitionIdx);                                                    /* SBSW_SOAD_POINTER_WRITE */

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_SO_CON_ID, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_GetSoConId() */

/**********************************************************************************************************************
 *  SoAd_OpenSoCon()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_OpenSoCon(
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx, partitionIdx), partitionIdx) )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Store open request. */
      retVal = SoAd_SoCon_RequestOpenSoCon(soConIdx, partitionIdx);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_OPEN_SO_CON, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_OpenSoCon() */

/**********************************************************************************************************************
 *  SoAd_CloseSoCon()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_CloseSoCon(
  SoAd_SoConIdType SoConId,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter 'SoConId'. */
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx, partitionIdx), partitionIdx) )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Store close request. */
      retVal = SoAd_SoCon_RequestCloseSoCon(soConIdx, partitionIdx, Abort);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_CLOSE_SO_CON, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_CloseSoCon() */

/**********************************************************************************************************************
 *  SoAd_RequestIpAddrAssignment()
 *********************************************************************************************************************/
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
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_RequestIpAddrAssignment(
  SoAd_SoConIdType SoConId,
  SoAd_IpAddrAssignmentType Type,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalIpAddrPtr,
  uint8 Netmask,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter 'SoConId'. */
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  /* #30 Check plausibility of input parameter 'Type'. */
  else if ( SoAd_CheckIpAddrAssignmentType(Type) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_ARG;
  }
  /* #40 Check plausibility of input parameter 'LocalIpAddrPtr' dependent on 'Type'. */
  else if ( (Type == SOAD_IPADDR_ASSIGNMENT_STATIC) && (LocalIpAddrPtr == NULL_PTR) )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( (Type == SOAD_IPADDR_ASSIGNMENT_STATIC) && (SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(
          SoAd_GetSoConGrpIdxOfSoCon(soConIdx, partitionIdx), partitionIdx), partitionIdx) != LocalIpAddrPtr->domain) )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #50 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
      /* #60 Handle IP address assignment request. */
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      retVal = SoAd_SoCon_RequestIpAddrAssignment(
        soConIdx,
        partitionIdx,
        Type,
        LocalIpAddrPtr,
        Netmask,
        DefaultRouterPtr);                                                                                             /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #70 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_REQ_IP_ADDR_ASSIGN, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_RequestIpAddrAssignment() */

/**********************************************************************************************************************
 *  SoAd_ReleaseIpAddrAssignment()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_ReleaseIpAddrAssignment(
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
      /* #40 Handle IP address assignment release request. */
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      retVal = SoAd_TcpIpApiReleaseIpAddrAssignment(SoAd_GetAddrIdOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(
            SoAd_GetSoConGrpIdxOfSoCon(soConIdx, partitionIdx), partitionIdx), partitionIdx));
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_RLS_IP_ADDR_ASSIGN, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_ReleaseIpAddrAssignment() */

/**********************************************************************************************************************
 *  SoAd_GetLocalAddr()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetLocalAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalAddrPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) NetmaskPtr,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( LocalAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( NetmaskPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( DefaultRouterPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
      /* #40 Get local IP address. */
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      SoAd_SoCon_GetIpAddr(soConIdx, partitionIdx, LocalAddrPtr, NetmaskPtr, DefaultRouterPtr);                        /* SBSW_SOAD_POINTER_FORWARD */

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_LOCAL_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_GetLocalAddr() */

/**********************************************************************************************************************
 *  SoAd_GetPhysAddr()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetPhysAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  SoAd_SizeOfSoConGrpType     soConGrpIdx;
  SoAd_SizeOfLocalAddrType    localAddrIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( PhysAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
      /* #40 Forward request to TcpIp module to get physical address. */
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */
      soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx, partitionIdx);
      localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx, partitionIdx);

      retVal = SoAd_TcpIpApiGetPhysAddr(SoAd_GetAddrIdOfLocalAddr(localAddrIdx, partitionIdx), PhysAddrPtr);           /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_PHYS_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_GetPhysAddr() */

/**********************************************************************************************************************
 *  SoAd_GetRemoteAddr()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetRemoteAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( IpAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Return remote address if it contains at least wildcards. */
      retVal = SoAd_SoCon_CheckAndGetRemoteAddr(soConIdx, partitionIdx, IpAddrPtr);                                    /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_REMOTE_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_GetRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_GetRemoteAddrState()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetRemoteAddrState(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr,
  P2VAR(SoAd_RemAddrStateType, AUTOMATIC, SOAD_APPL_VAR) RemAddrState)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( IpAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( RemAddrState == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Return remote address state. */
      SoAd_SoCon_GetRemoteAddrState(soConIdx, partitionIdx, IpAddrPtr, RemAddrState);                                  /* SBSW_SOAD_POINTER_FORWARD */

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_REMOTE_ADDR_STATE, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_GetRemoteAddrState() */

/**********************************************************************************************************************
 *  SoAd_GetRcvRemoteAddr()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetRcvRemoteAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( !SoAd_IsRcvRemAddrUsedOfSoCon(soConIdx, partitionIdx) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( IpAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Try to return received remote address. */
      retVal = SoAd_SoCon_CheckAndGetRcvRemoteAddr(soConIdx, partitionIdx, IpAddrPtr);                                 /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_RCV_REMOTE_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_GetRcvRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_EnableRouting()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_EnableRouting(
  SoAd_RoutingGroupIdType id)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRouteGrpType     routeGrpIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  uint8                       errorId = SOAD_E_NO_ERROR;
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (id >= SoAd_GetSizeOfRouteGrpIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRouteGrpIdMap(id)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  if ( SoAd_CheckAndGetRouteGrp(id, &routeGrpIdx, &partitionIdx) == E_NOT_OK )                                         /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    /* This is a valid use-case. No DETs are expected when the routing group is not mapped to any partition. */
  }
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  else if ( SoAd_IsMultiInstanceOnGrpOfRouteGrp(routeGrpIdx, partitionIdx) )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  /* PRQA S 3415 2 */ /* MD_SoAd_RightHandOperandWithoutSideEffects */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
      /* #40 Enable routing group on all related socket connections. */
      SoAd_RouteGrp_SetRoutingGroupState(routeGrpIdx, partitionIdx, TRUE);

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_ENABLE_ROUTING, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_EnableRouting() */

/**********************************************************************************************************************
 *  SoAd_EnableSpecificRouting()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_EnableSpecificRouting(
  SoAd_RoutingGroupIdType id,
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_SizeOfRouteGrpType     routeGrpIdx;
  SoAd_PartitionConfigIdxType routeGrpPartitionIdx;
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  SoAd_PartitionConfigIdxType soConPartitionIdx;
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  uint8                       errorId = SOAD_E_NO_ERROR;
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (id >= SoAd_GetSizeOfRouteGrpIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRouteGrpIdMap(id)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  if ( SoAd_CheckAndGetRouteGrp(id, &routeGrpIdx, &routeGrpPartitionIdx) == E_NOT_OK )                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    errorId = SOAD_E_INV_ARG;
  }
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &soConPartitionIdx) == E_NOT_OK)                              /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  /* PRQA S 3415 2 */ /* MD_SoAd_RightHandOperandWithoutSideEffects */
  else if ( SoAd_CheckApplicationIdValidity(routeGrpPartitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
  else if ( SoAd_CheckApplicationIdValidity(soConPartitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Enable routing group on all related PduRouteDests and SocketRoutes on the specified socket connection. */
      retVal = SoAd_RouteGrp_SetSpecificRoutingGroupState(routeGrpIdx, soConIdx, routeGrpPartitionIdx, TRUE);

#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
      /* #50 Check if routing group could not be disabled since specified socket connection is not related. */
      if ( retVal == E_NOT_OK )
      {
        errorId = SOAD_E_INV_ARG;
      }
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #60 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_ENABLE_SPECIFIC_ROUTING, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_EnableSpecificRouting() */

/**********************************************************************************************************************
 *  SoAd_DisableRouting()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_DisableRouting(
  SoAd_RoutingGroupIdType id)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRouteGrpType     routeGrpIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  uint8                       errorId = SOAD_E_NO_ERROR;
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (id >= SoAd_GetSizeOfRouteGrpIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRouteGrpIdMap(id)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  if ( SoAd_CheckAndGetRouteGrp(id, &routeGrpIdx, &partitionIdx) == E_NOT_OK )                                         /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    /* This is a valid use-case. No DETs are expected when the routing group is not mapped to any partition. */
  }
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  /* PRQA S 3415 2 */ /* MD_SoAd_RightHandOperandWithoutSideEffects */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
      /* #40 Disable routing group on all dependent socket connections. */
      SoAd_RouteGrp_SetRoutingGroupState(routeGrpIdx, partitionIdx, FALSE);

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_DISABLE_ROUTING, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_DisableRouting() */

/**********************************************************************************************************************
 *  SoAd_DisableSpecificRouting()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_DisableSpecificRouting(
  SoAd_RoutingGroupIdType id,
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_SizeOfRouteGrpType     routeGrpIdx;
  SoAd_PartitionConfigIdxType routeGrpPartitionIdx;
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  SoAd_PartitionConfigIdxType soConPartitionIdx;
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  uint8                       errorId = SOAD_E_NO_ERROR;
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (id >= SoAd_GetSizeOfRouteGrpIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRouteGrpIdMap(id)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  if ( SoAd_CheckAndGetRouteGrp(id, &routeGrpIdx, &routeGrpPartitionIdx) == E_NOT_OK )                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    errorId = SOAD_E_INV_ARG;
  }
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &soConPartitionIdx) == E_NOT_OK)                              /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  /* PRQA S 3415 2 */ /* MD_SoAd_RightHandOperandWithoutSideEffects */
  else if ( SoAd_CheckApplicationIdValidity(routeGrpPartitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
  else if ( SoAd_CheckApplicationIdValidity(soConPartitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Disable routing group on all related PduRouteDests and SocketRoutes on the specified socket connection. */
      retVal = SoAd_RouteGrp_SetSpecificRoutingGroupState(routeGrpIdx, soConIdx, routeGrpPartitionIdx, FALSE);

#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
      /* #50 Check if routing group could not be disabled since specified socket connection is not related. */
      if ( retVal == E_NOT_OK )
      {
        errorId = SOAD_E_INV_ARG;
      }
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #60 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_DISABLE_SPECIFIC_ROUTING, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_DisableSpecificRouting() */

/**********************************************************************************************************************
 *  SoAd_SetRemoteAddr()
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
/* PRQA S 6080 2 */ /* MD_MSR_STMIF */
/* PRQA S 3673 3 */ /* MD_MSR_Rule8.13 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SetRemoteAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  uint8                       errorId = SOAD_E_NO_ERROR;
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( RemoteAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx, partitionIdx), partitionIdx) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx,
    partitionIdx), partitionIdx), partitionIdx) != RemoteAddrPtr->domain )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Try to set remote address. */
      retVal = SoAd_SoCon_SetRemoteAddr(soConIdx, partitionIdx, RemoteAddrPtr);                                        /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_SET_REMOTE_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_SetRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_SetUniqueRemoteAddr()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SetUniqueRemoteAddr(
  SoAd_SoConIdType SoConId,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2VAR(SoAd_SoConIdType, AUTOMATIC, SOAD_APPL_VAR) AssignedSoConIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( RemoteAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx,
    partitionIdx), partitionIdx), partitionIdx) != RemoteAddrPtr->domain )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( AssignedSoConIdPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Try to set remote address and return the assigned socket connection. */
      retVal = SoAd_SoCon_SetUniqueRemoteAddr(soConIdx, partitionIdx, RemoteAddrPtr, AssignedSoConIdPtr);              /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_SET_UNI_REMOTE_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_SetUniqueRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_ReleaseRemoteAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(void, SOAD_CODE) SoAd_ReleaseRemoteAddr(
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx, partitionIdx), partitionIdx) )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Check if the currently set remote address is unequal to the configured one. */
      if ( SoAd_SoCon_CheckRemoteAddrRelease(soConIdx, partitionIdx) == E_OK )
      {
        /* #50 Try to release the remote address of the socket connection. */
        SoAd_SoCon_ReleaseRemoteAddr(soConIdx, partitionIdx, FALSE, TRUE);
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #60 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_RELEASE_REMOTE_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_ReleaseRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_ForceReleaseRemoteAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(void, SOAD_CODE) SoAd_ForceReleaseRemoteAddr(
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx, partitionIdx), partitionIdx) )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */

      /* #40 Check if the currently set remote address is unequal to the configured one. */
      if ( SoAd_SoCon_CheckRemoteAddrRelease(soConIdx, partitionIdx) == E_OK )
      {
        /* #50 Try to release the remote address of the socket connection. */
        SoAd_SoCon_ReleaseRemoteAddr(soConIdx, partitionIdx, TRUE, TRUE);
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #60 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_FORCE_RELEASE_REMOTE_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_ForceReleaseRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_ReadDhcpHostNameOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 2 */ /* MD_MSR_STMIF */
/* PRQA S 3673 4 */ /* MD_SoAd_ConstCausedByUnused */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_ReadDhcpHostNameOption(
  SoAd_SoConIdType SoConId,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) data)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
#if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
  SoAd_SizeOfSoConGrpType     soConGrpIdx;
  SoAd_SizeOfLocalAddrType    localAddrIdx;
#endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( length == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( data == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if component is initialized. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */
#if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
      soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx, partitionIdx);
      localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx, partitionIdx);

# if ( SOAD_DHCPV6_CLIENT_ENABLED == STD_ON )
      /* #40 Forward request to TcpIp module for DHCPv6. */
      if ( SoAd_GetDomainOfLocalAddr(localAddrIdx, partitionIdx) == SOAD_AF_INET6 )
      {
        uint16 tmpLength = *length;

        if ( SoAd_TcpIpApiDhcpV6ReadOption(SoAd_GetAddrIdOfLocalAddr(localAddrIdx, partitionIdx),                      /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
          SOAD_DHCP_OPT_V6_HOSTNAME, &tmpLength, data) == E_OK )
        {
          *length = (uint8)tmpLength;                                                                                  /* SBSW_SOAD_POINTER_WRITE */
          retVal = E_OK;
        }
      }
# endif /* SOAD_DHCPV6_CLIENT_ENABLED == STD_ON */
# if ( SOAD_DHCPV4_CLIENT_ENABLED == STD_ON )
      /* #50 Forward request to TcpIp module for DHCPv4. */
      if ( SoAd_GetDomainOfLocalAddr(localAddrIdx, partitionIdx) == SOAD_AF_INET )
      {
        retVal = SoAd_TcpIpApiDhcpReadOption(SoAd_GetAddrIdOfLocalAddr(localAddrIdx, partitionIdx),                    /* SBSW_SOAD_POINTER_FORWARD */
          SOAD_DHCP_OPT_V4_HOSTNAME, length, data);
      }
# endif /* SOAD_DHCPV4_CLIENT_ENABLED == STD_ON */
#else
      SOAD_DUMMY_STATEMENT(SoConId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT(length); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT(data); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT(soConIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #60 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_READ_DHCP_HOST_NAME_OPT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_ReadDhcpHostNameOption() */

/**********************************************************************************************************************
 *  SoAd_WriteDhcpHostNameOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_WriteDhcpHostNameOption(
  SoAd_SoConIdType SoConId,
  uint8 length,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) data)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
#if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
  SoAd_SizeOfSoConGrpType     soConGrpIdx;
  SoAd_SizeOfLocalAddrType    localAddrIdx;
#endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAd_CheckAndGetSoConId(SoConId, &soConIdx, &partitionIdx) == E_NOT_OK)                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( data == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if component is initialized. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( SOAD_DEV_ERROR_DETECT == STD_OFF )
      soConIdx = SoAd_GetPartitionSpecificSoConIdxOfSoConMap(SoConId);
      partitionIdx = SoAd_GetPartitionSpecificSoConPartitionIdxOfSoConMap(SoConId);
#endif /* SOAD_DEV_ERROR_DETECT == STD_OFF */
#if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
      soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx, partitionIdx);
      localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx, partitionIdx);

# if ( SOAD_DHCPV6_CLIENT_ENABLED == STD_ON )
      /* #40 Forward request to TcpIp module for DHCPv6. */
      if ( SoAd_GetDomainOfLocalAddr(localAddrIdx, partitionIdx) == SOAD_AF_INET6 )
      {
        retVal = SoAd_TcpIpApiDhcpV6WriteOption(SoAd_GetAddrIdOfLocalAddr(localAddrIdx, partitionIdx),                 /* SBSW_SOAD_POINTER_FORWARD */
          SOAD_DHCP_OPT_V6_HOSTNAME, length, data);
      }
# endif /* SOAD_DHCPV6_CLIENT_ENABLED == STD_ON */
# if ( SOAD_DHCPV4_CLIENT_ENABLED == STD_ON )
      /* #50 Forward request to TcpIp module for DHCPv4. */
      if ( SoAd_GetDomainOfLocalAddr(localAddrIdx, partitionIdx) == SOAD_AF_INET )
      {
        retVal = SoAd_TcpIpApiDhcpWriteOption(SoAd_GetAddrIdOfLocalAddr(localAddrIdx, partitionIdx),                   /* SBSW_SOAD_POINTER_FORWARD */
          SOAD_DHCP_OPT_V4_HOSTNAME, length, data);
      }
# endif /* SOAD_DHCPV4_CLIENT_ENABLED == STD_ON */
#else
      SOAD_DUMMY_STATEMENT(SoConId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT(length); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT_CONST(data); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT(soConIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON)) */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #60 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_WRITE_DHCP_HOST_NAME_OPT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_WriteDhcpHostNameOption() */

/**********************************************************************************************************************
 *  SoAd_ReadDhcpOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6030, 6080 2 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
/* PRQA S 3673 5 */ /* MD_SoAd_ConstCausedByUnused */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_ReadDhcpOption(
  SoAd_LocalAddrIdType IpAddrId,
  uint16 Option,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) DataLengthPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfLocalAddrType    localAddrIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (IpAddrId >= SoAd_GetSizeOfLocalAddrIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfLocalAddrIdMap(IpAddrId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  if ( SoAd_CheckAndGetLocalAddr(IpAddrId, &localAddrIdx, &partitionIdx) == E_NOT_OK )                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    /* This is a valid use-case. No DETs are expected when the local address is not mapped to any partition since not
     * all TcpIp local addresses are used by SoAd. */
  }
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  else if ( (SoAd_GetDomainOfLocalAddr(localAddrIdx, partitionIdx) == SOAD_AF_INET) && (Option > SOAD_MAX_UINT_8) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( DataLengthPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( (SoAd_GetDomainOfLocalAddr(localAddrIdx, partitionIdx) == SOAD_AF_INET) &&
    (*DataLengthPtr > SOAD_MAX_UINT_8) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( DataPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  /* PRQA S 3415 2 */ /* MD_SoAd_RightHandOperandWithoutSideEffects */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if component is initialized. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
# if ( SOAD_DHCPV6_CLIENT_ENABLED == STD_ON )
      /* #40 Forward request to TcpIp module for DHCPv6. */
      if ( SoAd_GetDomainOfLocalAddr(localAddrIdx, partitionIdx) == SOAD_AF_INET6 )
      {
        retVal = SoAd_TcpIpApiDhcpV6ReadOption(IpAddrId, Option, DataLengthPtr, DataPtr);                              /* SBSW_SOAD_POINTER_FORWARD */
      }
# endif /* SOAD_DHCPV6_CLIENT_ENABLED == STD_ON */
# if ( SOAD_DHCPV4_CLIENT_ENABLED == STD_ON )
      /* #50 Forward request to TcpIp module for DHCPv4. */
      if ( SoAd_GetDomainOfLocalAddr(localAddrIdx, partitionIdx) == SOAD_AF_INET )
      {
        uint8 tmpDataLength = (uint8)*DataLengthPtr;

        retVal = SoAd_TcpIpApiDhcpReadOption(IpAddrId, (uint8)Option, &tmpDataLength, DataPtr);                        /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */

        *DataLengthPtr = tmpDataLength;                                                                                /* SBSW_SOAD_POINTER_WRITE */
      }
# endif /* SOAD_DHCPV4_CLIENT_ENABLED == STD_ON */
#else
      SOAD_DUMMY_STATEMENT(IpAddrId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT(Option); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT(DataLengthPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT(DataPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #60 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_READ_DHCP_OPT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_ReadDhcpOption() */

/**********************************************************************************************************************
 *  SoAd_WriteDhcpOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 6030, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_WriteDhcpOption(
  SoAd_LocalAddrIdType IpAddrId,
  uint16 Option,
  uint16 DataLength,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfLocalAddrType    localAddrIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (IpAddrId >= SoAd_GetSizeOfLocalAddrIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfLocalAddrIdMap(IpAddrId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  if ( SoAd_CheckAndGetLocalAddr(IpAddrId, &localAddrIdx, &partitionIdx) == E_NOT_OK )                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    /* This is a valid use-case. No DETs are expected when the local address is not mapped to any partition since not
     * all TcpIp local addresses are used by SoAd. */
  }
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  else if ( (SoAd_GetDomainOfLocalAddr(localAddrIdx, partitionIdx) == SOAD_AF_INET) && (Option > SOAD_MAX_UINT_8) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( (SoAd_GetDomainOfLocalAddr(localAddrIdx, partitionIdx) == SOAD_AF_INET) && (DataLength > SOAD_MAX_UINT_8) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( DataPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  /* PRQA S 3415 2 */ /* MD_SoAd_RightHandOperandWithoutSideEffects */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if component is initialized. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
#if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
# if ( SOAD_DHCPV6_CLIENT_ENABLED == STD_ON )
      /* #40 Forward request to TcpIp module for DHCPv6. */
      if ( SoAd_GetDomainOfLocalAddr(localAddrIdx, partitionIdx) == SOAD_AF_INET6 )
      {
        retVal = SoAd_TcpIpApiDhcpV6WriteOption(IpAddrId, Option, DataLength, DataPtr);                                /* SBSW_SOAD_CONST_POINTER_FORWARD */
      }
# endif /* SOAD_DHCPV6_CLIENT_ENABLED == STD_ON */
# if ( SOAD_DHCPV4_CLIENT_ENABLED == STD_ON )
      /* #50 Forward request to TcpIp module for DHCPv4. */
      if ( SoAd_GetDomainOfLocalAddr(localAddrIdx, partitionIdx) == SOAD_AF_INET )
      {
        retVal = SoAd_TcpIpApiDhcpWriteOption(IpAddrId, (uint8)Option, (uint8)DataLength, DataPtr);                    /* SBSW_SOAD_CONST_POINTER_FORWARD */
      }
# endif /* SOAD_DHCPV4_CLIENT_ENABLED == STD_ON */
#else
      SOAD_DUMMY_STATEMENT(IpAddrId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT(Option); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT(DataLength); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      SOAD_DUMMY_STATEMENT(DataPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #60 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_WRITE_DHCP_OPT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_WriteDhcpOption() */

#if ( SOAD_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  SoAd_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, SOAD_APPL_VAR) versioninfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of input parameter. */
  if ( versioninfo == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON  */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Return version info. */
    versioninfo->vendorID = (SOAD_VENDOR_ID);                                                                          /* SBSW_SOAD_POINTER_WRITE */
    versioninfo->moduleID = (SOAD_MODULE_ID);                                                                          /* SBSW_SOAD_POINTER_WRITE */
    versioninfo->sw_major_version = (SOAD_SW_MAJOR_VERSION);                                                           /* SBSW_SOAD_POINTER_WRITE */
    versioninfo->sw_minor_version = (SOAD_SW_MINOR_VERSION);                                                           /* SBSW_SOAD_POINTER_WRITE */
    versioninfo->sw_patch_version = (SOAD_SW_PATCH_VERSION);                                                           /* SBSW_SOAD_POINTER_WRITE */
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_VERSION_INFO, errorId);
  }
# else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON  */
} /* SoAd_GetVersionInfo() */
#endif /* SOAD_VERSION_INFO_API == STD_ON */

#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
/**********************************************************************************************************************
 *  SoAd_GetAndResetMeasurementData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetAndResetMeasurementData(
  SoAd_MeasurementIdxType MeasurementIdx,
  boolean MeasurementResetNeeded,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) MeasurementDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
# if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retVal = E_NOT_OK;
# else
  Std_ReturnType retVal;
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  uint8          errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  /* Do not check 'MeasurementDataPtr' since it can be NULL_PTR. */
  /* No DET error check is expected for the parameter MeasurementIdx. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* PRQA S 2992,2996,2880 4 */ /* MD_SoAd_BooleanValueRangeCheck */
  else if( (MeasurementResetNeeded != TRUE) &&
    (MeasurementResetNeeded != FALSE) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Try to get and reset measurement data. */
    retVal = SoAd_Anomaly_GetAndResetMeasurementData(MeasurementIdx, MeasurementResetNeeded, MeasurementDataPtr);      /* SBSW_SOAD_POINTER_AND_NULL_POINTER_FORWARD */
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_RESET_MEASURE_DATA, errorId);
  }
# else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_GetAndResetMeasurementData() */
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

/**********************************************************************************************************************
 *  SoAd_MainFunctionInstanceRx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_MainFunctionInstanceRx(
  SoAd_SizeOfInstanceMapType InstMapIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check instance map index. */
  else if ( InstMapIdx >= SoAd_GetSizeOfInstanceMap() )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* #30 Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(SoAd_GetPartitionSpecificInstancePartitionIdxOfInstanceMap(InstMapIdx)) ==
    E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 Check if component is initialized. */
    if ( SoAd_State_GetState() == SOAD_STATE_INIT )
    {
      /* #50 Handle TP reception. */
      SoAd_Rx_HandleReception(InstMapIdx, &errorId);                                                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #60 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_MAIN_FUNCTION_RX, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_MainFunctionInstanceRx() */

/**********************************************************************************************************************
 *  SoAd_MainFunctionInstanceState()
 *********************************************************************************************************************/
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
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(void, SOAD_CODE) SoAd_MainFunctionInstanceState(
  SoAd_SizeOfInstanceMapType InstMapIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfInstanceType     instanceIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check instance map index. */
  else if ( InstMapIdx >= SoAd_GetSizeOfInstanceMap() )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* #30 Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(SoAd_GetPartitionSpecificInstancePartitionIdxOfInstanceMap(InstMapIdx)) ==
    E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    instanceIdx = SoAd_GetPartitionSpecificInstanceIdxOfInstanceMap(InstMapIdx);
    partitionIdx = SoAd_GetPartitionSpecificInstancePartitionIdxOfInstanceMap(InstMapIdx);

    /* #40 Process state machine. */
    SoAd_State_ProcessStateMachine(InstMapIdx);

    /* #50 Check if component is not in state shutdown. */
    if ( SoAd_State_GetState() != SOAD_STATE_SHUTDOWN )
    {
      /* #60 Check if UDP alive supervision timeout is configured. */
      if ( SoAd_IsTimeoutListUdpAliveConfigUsedOfTimeoutListIdent(SoAd_GetTimeoutListIdentIdxOfInstance(instanceIdx,
            partitionIdx), partitionIdx) )
      {
        /* #70 Handle UDP alive supervision timeout. */
        SoAd_SoCon_HandleUdpAliveTimeout(InstMapIdx);
      }

      /* #80 Handle socket connection states. */
      SoAd_SoCon_HandleSoConStates(InstMapIdx);
    }

    /* #90 Handle global timer counter. */
    /* Has to be handled at the end of this main function since timeouts for transmission (nPdu) are set in this
       context which would be overwritten in each call to this main function and no transmission would be performed in
       context of the transmission main function. */
    SoAd_IncCounterOfInstanceDyn(instanceIdx, partitionIdx);                                                           /* SBSW_SOAD_PARAMETER_IDX */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #100 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_MAIN_FUNCTION_STATE, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_MainFunctionInstanceState() */

/**********************************************************************************************************************
 *  SoAd_MainFunctionInstanceTx()
 *********************************************************************************************************************/
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
 */
FUNC(void, SOAD_CODE) SoAd_MainFunctionInstanceTx(
  SoAd_SizeOfInstanceMapType InstMapIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check instance map index. */
  else if ( InstMapIdx >= SoAd_GetSizeOfInstanceMap() )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* #30 Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(SoAd_GetPartitionSpecificInstancePartitionIdxOfInstanceMap(InstMapIdx)) ==
    E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 Check if component is not in state shutdown. */
    if ( SoAd_State_GetState() != SOAD_STATE_SHUTDOWN )
    {
      /* #50 Handle PDU transmission. */
      SoAd_Tx_HandleTransmission(InstMapIdx);

      /* #60 Handle routing group transmission. */
      SoAd_RouteGrp_HandleIfTransmit(InstMapIdx, &errorId);                                                            /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

      /* #70 Handle transmission confirmation. */
      SoAd_Tx_HandleConfirmation(InstMapIdx);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #80 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_MAIN_FUNCTION_TX, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_MainFunctionInstanceTx() */

#if ( SOAD_SINGLE_MAIN_FUNCTION == STD_ON )
/**********************************************************************************************************************
 *  SoAd_MainFunctionInstance()
 *********************************************************************************************************************/
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
 */
FUNC(void, SOAD_CODE) SoAd_MainFunctionInstance(
  SoAd_SizeOfInstanceMapType InstMapIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check instance map index. */
  else if ( InstMapIdx >= SoAd_GetSizeOfInstanceMap() )
  {
    errorId = SOAD_E_INV_ARG;
  }
#  if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* #30 Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(SoAd_GetPartitionSpecificInstancePartitionIdxOfInstanceMap(InstMapIdx)) ==
    E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
#  endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 Call main function for reception (socket states are checked additionally). */
    SoAd_MainFunctionInstanceRx(InstMapIdx);

    /* #50 Call main function for states. */
    SoAd_MainFunctionInstanceState(InstMapIdx);

    /* #60 Call main function for transmission (if enabled). */
    SoAd_MainFunctionInstanceTx(InstMapIdx);
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #70 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_MAIN_FUNCTION, errorId);
  }
# else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_MainFunctionInstance() */
#endif /* SOAD_SINGLE_MAIN_FUNCTION == STD_ON */

/**********************************************************************************************************************
 *  SoAd_RxIndication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 2 */ /* MD_MSR_STMIF */
/* PRQA S 3673 3 */ /* MD_MSR_Rule8.13 */
FUNC(void, SOAD_CODE) SoAd_RxIndication(
  SoAd_SocketIdType SocketId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType       sockIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx, &partitionIdx) == E_NOT_OK )                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( RemoteAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(
          SoAd_GetSoConStartIdxOfSocket(sockIdx, partitionIdx), partitionIdx), partitionIdx), partitionIdx) !=
    RemoteAddrPtr->domain )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( BufPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( Length == 0u )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#else
  if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx, &partitionIdx) == E_OK )                                    /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Forward received data segment to handle reception. */
    SoAd_Rx_RxIndication(sockIdx, partitionIdx, RemoteAddrPtr, BufPtr, Length, &errorId);                              /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_RX_INDICATION, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_RxIndication() */

/**********************************************************************************************************************
 *  SoAd_CopyTxData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 2 */ /* MD_MSR_STMIF */
FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_CopyTxData(
  SoAd_SocketIdType SocketId,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
#if ( SOAD_TX_DYN_LEN == STD_ON )
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr
#else
  uint16 BufLength
#endif /* SOAD_TX_DYN_LEN == STD_ON */
  )
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_TX_DYN_LEN == STD_OFF )
  uint16                      localBufLength = BufLength;
#endif /* SOAD_TX_DYN_LEN == STD_OFF */
  SoAd_SizeOfSocketType       sockIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  BufReq_ReturnType           retVal = BUFREQ_E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx, &partitionIdx) == E_NOT_OK )                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( BufPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_TX_DYN_LEN == STD_ON )
  else if ( BufLengthPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( *BufLengthPtr == 0u )
  {
    errorId = SOAD_E_INV_ARG;
  }
# else
  else if ( localBufLength == 0u )
  {
    errorId = SOAD_E_INV_ARG;
  }
# endif /* SOAD_TX_DYN_LEN == STD_ON */
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#else
  if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx, &partitionIdx) == E_OK )                                    /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Handle copy request for transmission data. */
#if ( SOAD_TX_DYN_LEN == STD_ON )
    retVal = SoAd_Tx_CopyTxData(sockIdx, partitionIdx, BufPtr, BufLengthPtr);                                          /* SBSW_SOAD_POINTER_FORWARD */
#else
    retVal = SoAd_Tx_CopyTxData(sockIdx, partitionIdx, BufPtr, &localBufLength);                                       /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_TX_DYN_LEN == STD_ON */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_COPY_TX_DATA, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_CopyTxData() */

/**********************************************************************************************************************
 *  SoAd_TxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(void, SOAD_CODE) SoAd_TxConfirmation(
  SoAd_SocketIdType SocketId,
  uint16 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType       sockIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( Length == 0u )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx, &partitionIdx) == E_NOT_OK )                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( !SoAd_IsTxMgtUsedOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIdx, partitionIdx), partitionIdx) )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#else
  if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx, &partitionIdx) == E_OK )                                    /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #30 Handle TxConfirmation. */
    SoAd_Tx_TxConfirmation(sockIdx, partitionIdx, Length);
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TX_CONFIRMATION, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_TxConfirmation() */

/**********************************************************************************************************************
 *  SoAd_LocalIpAddrAssignmentChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(void, SOAD_CODE) SoAd_LocalIpAddrAssignmentChg(
  SoAd_LocalAddrIdType IpAddrId,
  SoAd_IpAddrStateType State)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfLocalAddrType    localAddrIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (IpAddrId >= SoAd_GetSizeOfLocalAddrIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfLocalAddrIdMap(IpAddrId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  if ( SoAd_CheckAndGetLocalAddr(IpAddrId, &localAddrIdx, &partitionIdx) == E_NOT_OK )                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    /* This is a valid use-case. No DETs are expected when the local address is not mapped to any partition since not
     * all TcpIp local addresses are used by SoAd. */
  }
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  else if ( (State != SOAD_IPADDR_STATE_ASSIGNED) &&
    (State != SOAD_IPADDR_STATE_ONHOLD) &&
    (State != SOAD_IPADDR_STATE_UNASSIGNED) )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  /* PRQA S 3415 2 */ /* MD_SoAd_RightHandOperandWithoutSideEffects */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Handle local address state change. */
    SoAd_SoCon_LocalIpAddrAssignmentChg(localAddrIdx, partitionIdx, State);
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_LOCAL_IP_ADDR_ASSIGNMENT_CHG, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_LocalIpAddrAssignmentChg() */

/**********************************************************************************************************************
 *  SoAd_TcpAccepted()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 3 */ /* MD_MSR_STMIF */
/* PRQA S 3673 5 */ /* MD_MSR_Rule8.13 */
/* PRQA S 3206 4 */ /* MD_SoAd_UnusedParameter */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpAccepted(
  SoAd_SocketIdType SocketId,
  SoAd_SocketIdType SocketIdConnected,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType       sockIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  Std_ReturnType              retVal = E_NOT_OK;
#if ( SOAD_TCP == STD_ON )
  uint8                       errorId = SOAD_E_NO_ERROR;
#else
  uint8                       errorId = SOAD_E_INV_SOCKETID;
#endif /* SOAD_TCP == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx, &partitionIdx) == E_NOT_OK )                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
# if ( SOAD_TCP == STD_ON )
  else if ( !SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(
          sockIdx, partitionIdx), partitionIdx), partitionIdx) )
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(
          SoAd_GetSoConStartIdxOfSocket(sockIdx, partitionIdx), partitionIdx), partitionIdx), partitionIdx) )
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( SocketIdConnected == SOAD_INV_SOCKET_ID )
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( RemoteAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(
          SoAd_GetSoConStartIdxOfSocket(sockIdx, partitionIdx), partitionIdx), partitionIdx), partitionIdx) !=
    RemoteAddrPtr->domain )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# endif /* SOAD_TCP == STD_ON */
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#else
  if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx, &partitionIdx) == E_OK )                                    /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
    /* #30 Handle acceptance of TCP connection establishment (if enabled). */
    retVal = SoAd_SoCon_TcpAccepted(sockIdx, partitionIdx, SocketIdConnected, RemoteAddrPtr);                          /* SBSW_SOAD_POINTER_FORWARD */
#else
    SOAD_DUMMY_STATEMENT(SocketIdConnected); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    SOAD_DUMMY_STATEMENT(RemoteAddrPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_TCP == STD_ON  */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
# if ( SOAD_TCP == STD_ON )
  if ( errorId != SOAD_E_NO_ERROR )
# endif /* SOAD_TCP == STD_ON */
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TCP_ACCEPTED, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_TcpAccepted() */

/**********************************************************************************************************************
 *  SoAd_TcpConnected()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_TcpConnected(
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType       sockIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
#if ( SOAD_TCP == STD_ON )
  uint8                       errorId = SOAD_E_NO_ERROR;
#else
  uint8                       errorId = SOAD_E_INV_SOCKETID;
#endif /* SOAD_TCP == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx, &partitionIdx) == E_NOT_OK )                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
# if ( SOAD_TCP == STD_ON )
  else if ( !SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(
          sockIdx, partitionIdx), partitionIdx), partitionIdx) )
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( !SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(
          SoAd_GetSoConStartIdxOfSocket(sockIdx, partitionIdx), partitionIdx), partitionIdx), partitionIdx) )
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
# endif /* SOAD_TCP == STD_ON */
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#else
  if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx, &partitionIdx) == E_OK )                                    /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
    /* #30 Handle TCP connect (if enabled). */
    SoAd_SoCon_TcpConnected(sockIdx, partitionIdx);
#endif /* SOAD_TCP == STD_ON  */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
# if ( SOAD_TCP == STD_ON )
  if ( errorId != SOAD_E_NO_ERROR )
# endif /* SOAD_TCP == STD_ON */
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TCP_CONNECTED, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_TcpConnected() */

/**********************************************************************************************************************
 *  SoAd_TcpIpEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(void, SOAD_CODE) SoAd_TcpIpEvent(
  SoAd_SocketIdType SocketId,
  SoAd_EventType Event)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketMapType    sockIdx;
  SoAd_PartitionConfigIdxType partitionIdx;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx, &partitionIdx) == E_NOT_OK )                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    /* SoAd may be called with a SocketId which is already removed from socket mapping. Do not report a DET error. */
  }
# if ( SOAD_TCP == STD_ON )
  else if ( (SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(
            sockIdx, partitionIdx), partitionIdx), partitionIdx)) &&
    (Event != SOAD_TCP_RESET) &&
    (Event != SOAD_TCP_CLOSED) &&
    (Event != SOAD_TCP_FIN_RECEIVED) &&
    (Event != SOAD_TLS_HANDSHAKE_SUCCEEDED) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( (SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(
            sockIdx, partitionIdx), partitionIdx), partitionIdx)) &&
    (SoAd_GetSocketIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(
            sockIdx, partitionIdx), partitionIdx), partitionIdx) == sockIdx) &&
    (Event == SOAD_TCP_FIN_RECEIVED) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_IsSocketUdpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(
            sockIdx, partitionIdx), partitionIdx), partitionIdx) && (Event != SOAD_UDP_CLOSED) )
  {
    errorId = SOAD_E_INV_ARG;
  }
# else
  else if ( Event != SOAD_UDP_CLOSED )
  {
    errorId = SOAD_E_INV_ARG;
  }
# endif /* SOAD_TCP == STD_ON */
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  else if ( SoAd_CheckApplicationIdValidity(partitionIdx) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#else
  if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx, &partitionIdx) == E_OK )                                    /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Handle event on socket. */
    SoAd_SoCon_Event(sockIdx, partitionIdx, Event);
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TCPIP_EVENT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_TcpIpEvent() */

/**********************************************************************************************************************
 *  SoAd_DhcpEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(void, SOAD_CODE) SoAd_DhcpEvent(
  SoAd_LocalAddrIdType IpAddrId,
  SoAd_DhcpEventType Event)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
  SoAd_DhcpEventCbkIterType   cbkIter;
#endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State_GetState() < SOAD_STATE_INIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (IpAddrId >= SoAd_GetSizeOfLocalAddrIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfLocalAddrIdMap(IpAddrId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( Event == SOAD_DHCP_EVENT_INVALID )
  {
    errorId = SOAD_E_INV_ARG;
  }
# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  /* Check validity of application identifier and the mapped instance index. */
  /* PRQA S 3415 2 */ /* MD_SoAd_RightHandOperandWithoutSideEffects */
  else if ( SoAd_IsPartitionSpecificLocalAddrUsedOfLocalAddrIdMap(IpAddrId) && (SoAd_CheckApplicationIdValidity(
        SoAd_GetPartitionSpecificLocalAddrPartitionIdxOfLocalAddrIdMap(IpAddrId)) == E_NOT_OK) )
  {
    errorId = SOAD_E_INV_APPLICATION_ID;
  }
# endif /* SOAD_MULTI_PARTITION == STD_ON */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
    /* #30 Forward DHCP event to user (if DHCP is enabled). */
    for ( cbkIter = 0u; cbkIter < SoAd_GetSizeOfDhcpEventCbk(); cbkIter++ )
    {
      if ( SoAd_GetDhcpEventCbk(cbkIter) != NULL_PTR )
      {
        SoAd_GetDhcpEventCbk(cbkIter)(IpAddrId, Event);                                                                /* SBSW_SOAD_FUNCTION_PTR */
      }
    }
#else
    SOAD_DUMMY_STATEMENT(IpAddrId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    SOAD_DUMMY_STATEMENT(Event); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_DHCP_EVENT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_DhcpEvent() */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/* Justification for module-specific MISRA deviations:
 MD_SoAd_UnusedParameter: rule 2.7
      Reason:     Function parameter is only used in some configurations or is required by specification but not used.
      Risk:       None.
      Prevention: No prevention necessary.
 MD_SoAd_ConstCausedByUnused: rule 8.13
      Reason:     Function parameter is only used in some configurations.
      Risk:       None.
      Prevention: No prevention necessary.
 MD_SoAd_PointerCastOnStruct: rule 11.3
      Reason:     A generic struct is used to support one generic parameter in a function but with different derived
                  types which are identified by an element in the generic struct.
      Risk:       Issues concerning safety, portability, and readability.
      Prevention: Program flow has been verified by component tests and code inspection.
 MD_SoAd_PointerCastOnParam: rule 11.3
      Reason:     A generic type is used to support one generic parameter in a function but with different derived
                  types which are identified by an additional function parameter.
      Risk:       Issues concerning safety, portability, and readability.
      Prevention: Program flow has been verified by component tests and code inspection.
 MD_SoAd_GenericWiderTypeCast: rule 10.3, rule 10.8
      Reason:     A configuration dependent data type is cast to the widest expected data type to be
                  generic/configuration independent.
      Risk:       Type mismatch may indicate usage of a wrong data type or variable.
      Prevention: Code inspection.
 MD_SoAd_MacroRedundantCheck: rule 13.7
      Reason:     Value of macro is provided by other module. It may have a different value.
      Risk:       Duplicated macro with same value may lead to misunderstanding while code inspection.
      Prevention: Code inspection.
 MD_SoAd_UsageNotDetected: rule 2.2
      Reason:     Tool does not detect usage of value.
      Risk:       None.
      Prevention: No prevention necessary.
 MD_SoAd_BooleanValueRangeCheck: rule 2.1, rule 2.2, rule 13.7, rule 14.1, rule 14.3
      Reason:     The value range size of boolean may be greater than 2. Therefore, the value range is checked for
                  invalid values. In configurations with a value range of 2 causes this check "always true/false"
                  conditions and unreachable code.
      Risk:       None.
      Prevention: No prevention necessary.
 MD_SoAd_CopyingToPointerWithGreaterLifetime:
      Reason:     The local pointer is storing the address of a global variable. Since it is global, the source to
                  which it is copied cannot have any greater lifetime.
      Risk:       None.
      Prevention: Code inspection.
 MD_SoAd_RedundantCallWithoutSideEffects: rule 2.2
      Reason:     Global data is set inside the called function by using the ComStackLib. Therefore, the function call
                  is required.
      Risk:       None.
      Prevention: None.
 MD_SoAd_P2CONSTNotApplicable:
      Reason:     The usage of a local variable is required for the access to ComStackLib. Declaring the local variable
                  as P2CONST is not applicable because it is assigned to a P2VAR, which is a less heavily qualified
                  type than P2CONST.
      Risk:       None.
      Prevention: None.
 MD_SoAd_RightHandOperandWithoutSideEffects: rule 13.5
      Reason:     Optimization of evaluation of if condition. The function call (right hand operand) shall only be done
                  if the left hand operand evaluates to true. Not evaluating the right hand operand does not lead to
                  any side effects.
      Risk:       None.
      Prevention: None.
 */

/* Safe BSW assumptions:

  Indirections:
    SoCon -> RxMgt 1:0..1 (available if a SoAdSocketRoute is configured)
    SoCon -> RxBufferConfig 1:0..1 (available if a
      IF SoAdSocketRoute over TCP SoAdSocketConnection is configured
      OR
      TP SoAdSocketRoute over UDP SoAdSocketConnection is configured
      OR
      TP SoAdSocketRoute over TCP SoAdSocketConnection with PDU header option is configured)
    SoCon -> RxBufStructMgt 1:0..1 (available if a SoAdSocketRoute over TCP SoAdSocketConnection is configured)
    SoCon -> TxMgt 1:0..1 (available if a SoAdPduRoute is configured)
    SoCon -> TpTxBufferConfig 1:0..1 (available if a TP SoAdPduRoute over UDP SoAdSocketConnection is configured)
    SoCon -> TcpTxQueue 1:0..1 (available if TCP is configured on SoAdSocketConnection)
    SoCon -> NPduUdpTx 1:0..1 (available if at least one IF SoAdPduRoute with SoAdTxUdpTriggerMode TRIGGER_NEVER
      and no TP SoAdPduRoute over UDP SoAdSocketConnection is configured)
    SoCon -> Socket 1:1
    SoCon -> SoConGrp 1:1
    SoConGrp -> Socket 1:0..1 (available if UDP/TCP SoAdSocketConnection and no SoAdSocketTcpInitiate are configured)
    Socket -> SoCon 1:1..n
    TcpTxQueue-> TcpTxQueueData 1:1..n
    NPduUdpTx -> NPduUdpTxBuffer 0..n (available if at least one SoAdPduRoute without SoAdTxIfTriggerTransmit is
      configured; n = NPduUdpTxBufferMinOfSocketUdp)
    NPduUdpTx -> NPduUdpTxQueue 0..n (available if at least one SoAdPduRoute with SoAdTxIfTriggerTransmit is
      configured; n = NPduUdpTxQueueSizeOfSocketUdp)
    NPduUdpTxQueue -> NPduUdpTxBuffer 0..n (available if at least one SoAdPduRoute without SoAdTxIfTriggerTransmit is
      configured additionally; n = NPduUdpTxBufferMinOfSocketUdp)
    TpTxBufferConfig -> TpTxBuffer 1:0..n (available if a TP SoAdPduRoute over UDP SoAdSocketConnection is configured;
      n = SOAD_PDU_HDR_SIZE (if enabled) + maximum configured TP-PDU size on corresponding SoAdSocketConnection)
    RxBufferConfig -> IfRxBuffer 1:0..n (available if a IF SoAdSocketRoute over TCP SoAdSocketConnection is configured;
      n = SOAD_PDU_HDR_SIZE (if enabled) + maximum configured IF-PDU size on corresponding SoAdSocketConnectionGroup)
    RxBufferConfig -> TpRxBuffer 1:0..n (available if a TP SoAdSocketRoute over
      UDP SoAdSocketConnection is configured; n = maximum configured TP-PDU size on SoAdSocketConnection
      OR
      TCP SoAdSocketConnection with SoAdTxPduHeaderId is configured; n = SOAD_PDU_HDR_SIZE)
    SocketRoute -> UpperLayer 1:1
    SocketRoute -> SoCon 1:1
    UpperLayer -> IfRxIndicationCbk 1:0..1 (available if a IF SoAdSocketRoute is configured)
    UpperLayer -> IfTriggerTransmitCbk 1:0..1 (available if a IF SoAdPduRoute and SoAdIfTriggerTransmit are configured)
    UpperLayer -> IfTxConfirmationCbk 1:0..1 (available if a IF SoAdPduRoute and SoAdIfTxConfirmation are configured)
    UpperLayer -> TpCopyRxDataCbk 1:0..1 (available if a TP SoAdSocketRoute and no SoAdTpCopyRxDataWithConstPointer are
      configured - xor to TpCopyRxDataConstCbk)
    UpperLayer -> TpCopyRxDataConstCbk 1:0..1 (available if a TP SoAdSocketRoute and SoAdTpCopyRxDataWithConstPointer
      are configured - xor to TpCopyRxDataCbk)
    UpperLayer -> TpCopyTxDataCbk 1:0..1 (available if a TP SoAdPduRoute and no SoAdTpCopyTxDataWithConstPointer are
      configured - xor to TpCopyTxDataConstCbk)
    UpperLayer -> TpCopyTxDataConstCbk 1:0..1 (available if a TP SoAdPduRoute and SoAdTpCopyTxDataWithConstPointer are
      configured - xor to TpCopyTxDataCbk)
    UpperLayer -> TpRxIndicationCbk 1:0..1 (available if a TP SoAdSocketRoute is configured)
    UpperLayer -> TpStartOfReceptionCbk 1:0..1 (available if a TP SoAdSocketRoute and no
      SoAdTpStartOfReceptionWithConstPointer are configured - xor to TpStartOfReceptionConstCbk)
    UpperLayer -> TpStartOfReceptionConstCbk 1:0..1 (available if a TP SoAdSocketRoute and
      SoAdTpStartOfReceptionWithConstPointer are configured - xor to TpStartOfReceptionCbk)
    UpperLayer -> TpTxConfirmationCbk 1:0..1 (available if a TP SoAdPduRoute is configured)
    Instance -> EventQueueIdent 1:1
    Instance -> TimeoutListIdent 1:1
    Instance -> BestMatchSoConIdxList 1:1..n (n is the maximum number of SoCon per SoConGrp of the instance)
    TimeoutListIdent -> TimeoutListUdpAliveConfig 1:0..1 (available if at least one SoAdSocketRoute over UDP
      SoAdSocketConnection with SoAdSocketUdpAliveSupervisionTimeout is configured on the instance)
    TimeoutListIdent -> TimeoutListNPduUdpTxConfig 1:0..1 (available if at least one IF SoAdPduRoute with
      SoAdTxUdpTriggerMode TRIGGER_NEVER and no TP SoAdPduRoute over UDP SoAdSocketConnection is configured on the
      instance)
    EventQueueIdent -> EventQueueTpRxSoConConfig 1:0..1 (available if a TP SoAdSocketRoute is configured on the
      instance)
    EventQueueIdent -> EventQueueStateSoConConfig 1:1
    EventQueueIdent -> EventQueueTpTxSoConConfig 1:0..1 (available if a TP SoAdPduRoute is configured on the instance)
    EventQueueIdent -> EventQueueIfUdpPduRouteConfig 1:0..1 (available if a IF SoAdPduRoute over UDP
      SoAdSocketConnection is configured on the instance)
    EventQueueIdent -> EventQueueIfTxRouteGrpConfig 1:0..1 (available if a SoAdRoutingGroupTxTriggerable is enabled on
      the instance)

  Size Constraints:
    TpTxBufferConfigDyn <-> TpTxBufferConfig
    TcpTxQueueMgt <-> TcpTxQueue
    NPduUdpTx <-> NPduUdpTxDyn
    SocketDyn <-> Socket
    EventQueueTpRxSoCon <-> SoCon (with TP socket routes)
    EventQueueStateSoCon <-> SoCon
    EventQueueTpTxSoCon <-> SoCon (with TP PDU routes)
    EventQueueIfUdpPduRoute <-> PduRoute (IF on UDP socket connection)
    EventQueueIfTxRouteGrp <-> RouteGrp (with Tx triggerable)
    TimeoutListUdpAliveMap <-> SoCon
    TimeoutListNPduUdpTxMap <-> NPduUdpTx

  These assumptions are modeled in ComStackLib (verification: to be reviewed in generator).
*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_SOAD_CSL01_CSL05
    \DESCRIPTION      Access to partition dependent array with index using ComStackLib.
    \COUNTERMEASURE   \N Qualified use-case CSL01 of ComStackLib. The PartitionIdx has been derived in advance by a
                         qualified use-case of CSL05.

  \ID SBSW_SOAD_CSL02_CSL05
    \DESCRIPTION      Access to partition dependent array with index of array with same size using ComStackLib.
    \COUNTERMEASURE   \N Qualified use-case CSL02 of ComStackLib. The PartitionIdx has been derived in advance by a
                         qualified use-case of CSL05.

  \ID SBSW_SOAD_CSL03_CSL05
    \DESCRIPTION      Access to array via partition dependent indirection using ComStackLib.
    \COUNTERMEASURE   \N Qualified use-case CSL03 of ComStackLib. The PartitionIdx has been derived in advance by a
                         qualified use-case of CSL05.

  \ID SBSW_SOAD_CSL02_CSL03_CSL05
    \DESCRIPTION      Access to partition dependent array with index of array with same size via indirection using
                      ComStackLib.
    \COUNTERMEASURE   \N Qualified use-case CSL03 followed by CSL02 of ComStackLib. The PartitionIdx has been derived
                         in advance by a qualified use-case of CSL05.

  \ID SBSW_SOAD_OPTIONAL_CSL03_CSL05
    \DESCRIPTION      Access to array via optional (partition dependent) indirection using ComStackLib.
    \COUNTERMEASURE   \N Qualified use-case CSL03 of ComStackLib. According to the Safe BSW assumptions modeled in
                         ComStackLib it is ensured that optional indirection is available here. The index used to
                         access the indirection may depend on a function parameter. The validity of the function
                         parameter is defined at the function declaration and has to be ensured by the caller. The
                         PartitionIdx has been derived in advance by a qualified use-case of CSL05.

  \ID SBSW_SOAD_OPTIONAL_CHECKED_CSL03
    \DESCRIPTION      Access to array via optional indirection using ComStackLib.
    \COUNTERMEASURE   \R The availability of the optional indirection (qualified use-case CSL03 of ComStackLib) is
                         checked. The index used to access the indirection may depend on a function parameter. The
                         validity of the function parameter is defined at the function declaration and has to be
                         ensured by the caller.

  \ID SBSW_SOAD_OPTIONAL_CHECKED_CSL03_CSL05
    \DESCRIPTION      Access to array via optional (partition dependent) indirection using ComStackLib.
    \COUNTERMEASURE   \R The availability of the optional indirection (qualified use-case CSL03 of ComStackLib) is
                         checked. The index used to access the indirection may depend on a function parameter. The
                         validity of the function parameter is defined at the function declaration and has to be
                         ensured by the caller. The PartitionIdx has been derived in advance by a qualified use-case of
                         CSL05.

  \ID SBSW_SOAD_OPTIONAL_CHECKED_PREPROC_CSL03_CSL05
    \DESCRIPTION      Access to array via optional (partition dependent) indirection using ComStackLib.
    \COUNTERMEASURE   \N The availability of the optional indirection (qualified use-case CSL03 of ComStackLib) is
                         checked in a specific preprocessor variant. The index used to access the indirection may
                         depend on a function parameter. The validity of the function parameter is defined at the
                         function declaration and has to be ensured by the caller. In other preprocessor variants the
                         runtime check is not available. In this case according to the Safe BSW assumptions modeled in
                         ComStackLib it is ensured that optional indirection is available here. The PartitionIdx has
                         been derived in advance by a qualified use-case of CSL05.

  \ID SBSW_SOAD_CALCULATED_CSL03_CSL05_RxBufStructSeg
    \DESCRIPTION      Access to array "SoAd_RxBufStructSeg" based on index stored in "SoAd_RxBufStructMgt".
    \COUNTERMEASURE   \N There is an indirection modeled with ComStackLib (Qualified use-case CSL03) in "SoAd_SoCon" to
                         get corresponding start and end index of "SoAd_RxBufStructSeg". "SoAd_RxBufStructMgt" is used
                         to store an index and a fill level calculated in range of start and end index provided by
                         "SoAd_SoCon". After initialization the values are always in valid range. Calculations based on
                         the stored values always consider the start and end index given in "SoAd_SoCon". The
                         PartitionIdx has been derived in advance by a qualified use-case of CSL05.

  \ID SBSW_SOAD_CALCULATED_CSL03_CSL05_TcpTxQueueData
    \DESCRIPTION      Access to array "SoAd_TcpTxQueueData" based on index stored in "SoAd_TcpTxQueueMgt".
    \COUNTERMEASURE   \N There is an indirection modeled with ComStackLib (Qualified use-case CSL03) in
                         "SoAd_TcpTxQueue" to get corresponding start and end index of "SoAd_TcpTxQueueData".
                         "SoAd_TcpTxQueueMgt" is used to store an index and fill level calculated in range of start
                         and end index provided by "SoAd_TcpTxQueue". After initialization the values are always in
                         valid range. Calculations based on the stored values always consider the start and end index
                         given in "SoAd_TcpTxQueue". The PartitionIdx has been derived in advance by a qualified
                         use-case of CSL05.

  \ID SBSW_SOAD_CALCULATED_CSL03_CSL05_NPduUdpTxQueue
    \DESCRIPTION      Access to array "SoAd_NPduUdpTxQueue" based on index stored in "SoAd_NPduUdpTxDyn".
    \COUNTERMEASURE   \N There is an indirection modeled with ComStackLib (Qualified use-case CSL03) in
                         "SoAd_NPduUdpTx" to get corresponding start and end index of "SoAd_NPduUdpTxQueue".
                         "SoAd_NPduUdpTxDyn" is used to store an fill level calculated in range of start and end index
                         provided by "SoAd_NPduUdpTx". After initialization the value is always in valid range.
                         Calculations based on the stored value always consider the start and end index given in
                         "SoAd_NPduUdpTx". The PartitionIdx has been derived in advance by a qualified use-case of
                         CSL05.

  \ID SBSW_SOAD_CALCULATED_CSL03_CSL05_IpFragBufConfigDyn
    \DESCRIPTION      Access to array "SoAd_IpFragBufConfigDyn" based on index stored in "SoAd_IpFragMgt".
    \COUNTERMEASURE   \N The index stored in "SoAd_IpFragMgt" is always checked against the size of
                         "SoAd_IpFragBufConfig". To access "SoAd_IpFragBufConfigDyn" with an index checked against size
                         of "SoAd_IpFragBufConfig" is qualified use-case CSL02. The index stored in "SoAd_IpFragMgt" is
                         always valid or set to an invalid value after initialization. Before index is used to access
                         "SoAd_IpFragBufConfigDyn" the value is checked against the invalid value. The PartitionIdx has
                         been derived in advance by a qualified use-case of CSL05.

  \ID SBSW_SOAD_CALCULATED_CHECKED_CSL03_CSL05
    \DESCRIPTION      Write access to an array element with an index which is calculated.
    \COUNTERMEASURE   \R The valid range of the calculated index is checked with an indirection modelled in the
                         ComStackLib (CSL03). The index check may depend on a function parameter. The validity of the
                         function parameter is defined at the function declaration and has to be ensured by the caller.
                         The PartitionIdx has been derived in advance by a qualified use-case of CSL05.

  \ID SBSW_SOAD_CALCULATED_TimeoutListUdpAlive
    \DESCRIPTION      Access to array "SoAd_TimeoutListUdpAlive" based on index stored in "SoAd_TimeoutListMgmt" or
                      "SoAd_TimeoutListUdpAliveMap".
    \COUNTERMEASURE   \N The index/fill level stored in "SoAd_TimeoutListMgmt" is incremented/decremented with the
                         elements added to or removed from array list "SoAd_TimeoutListUdpAlive". Therefore, the index
                         is always valid after initialization. The index stored in "SoAd_TimeoutListUdpAliveMap" is set
                         dependent on the index/fill level provided by "SoAd_TimeoutListMgmt" or set to an invalid
                         value if unused. When using the value runtime checks are implemented to verify that invalid
                         value is not used as index to access the array.

  \ID SBSW_SOAD_CALCULATED_TimeoutListUdpAliveMap
    \DESCRIPTION      Access to array "SoAd_TimeoutListUdpAliveMap" based on index stored in
                      "SoAd_TimeoutListUdpAlive".
    \COUNTERMEASURE   \N The index stored in "SoAd_TimeoutListUdpAlive" is only used to access
                         "SoAd_TimeoutListUdpAliveMap" when index is valid. This is verified by runtime checks for
                         "SoAd_TimeoutListUdpAlive" with the assumption that all elements of a specific entry in
                         "SoAd_TimeoutListUdpAlive" are set consistently.

  \ID SBSW_SOAD_CALCULATED_TimeoutListNPduUdpTx
    \DESCRIPTION      Access to array "SoAd_TimeoutListNPduUdpTx" based on index stored in "SoAd_TimeoutListMgmt" or
                      "SoAd_TimeoutListNPduUdpTxMap".
    \COUNTERMEASURE   \N The index/fill level stored in "SoAd_TimeoutListMgmt" is incremented/decremented with the
                         elements added to or removed from array list "SoAd_TimeoutListNPduUdpTx". Therefore, the index
                         is always valid after initialization. The index stored in "SoAd_TimeoutListNPduUdpTxMap" is
                         set dependent on the index/fill level provided by "SoAd_TimeoutListMgmt" or set to an invalid
                         value if unused. When using the value runtime checks are implemented to verify that invalid
                         value is not used as index to access the array.

  \ID SBSW_SOAD_CALCULATED_TimeoutListNPduUdpTxMap
    \DESCRIPTION      Access to array "SoAd_TimeoutListNPduUdpTxMap" based on index stored in
                      "SoAd_TimeoutListNPduUdpTx".
    \COUNTERMEASURE   \N The index stored in "SoAd_TimeoutListNPduUdpTx" is only used to access
                         "SoAd_TimeoutListNPduUdpTxMap" when index is valid. This is verified by runtime checks for
                         "SoAd_TimeoutListNPduUdpTx" with the assumption that all elements of a specific entry in
                         "SoAd_TimeoutListNPduUdpTx" are set consistently.

  \ID SBSW_SOAD_NULL_POINTER_FORWARD
    \DESCRIPTION      The function forwards a "null" pointer. The pointer can be used to write to the corresponding
                      invalid memory location.
    \COUNTERMEASURE   \N A different function parameter indicates that pointer must not be used or the function is
                         defined to be called "null" pointer.

  \ID SBSW_SOAD_CAST_POINTER_FORWARD
    \DESCRIPTION      A pointer to a local variable is passed as function parameter with cast to different data type.
                      Pointer can be used to write to the corresponding memory location.
    \COUNTERMEASURE   \N Local variables are located in valid memory locations. A different function parameter
                         indicates how pointer must be used. Callee cast back to the original data type. The expected
                         data type is defined by the callee.

  \ID SBSW_SOAD_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter which could be used to write to the
                      corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type or an additional
                         function parameter is used to describe pointer validity. This is ensured by the caller.

  \ID SBSW_SOAD_POINTER_FORWARD_EXPECTED_SIZE_TX
    \DESCRIPTION      The function forwards pointer to array passed as function parameter which could be used to write
                      to the corresponding memory location. The callee expects a specific range which is not ensured
                      in this context.
    \COUNTERMEASURE   \N In this context a struct "SoAd_TxMgt" is used to store the length to be transmitted. The
                         transmission buffer is provided together with a function parameter which indicates the size of
                         the provided buffer. The validity is ensured by the provider. The size of the provided buffer
                         is checked in this context before (SoAd_Tx_CopyTxDataCheckParameter()) against the values
                         stored in "SoAd_TxMgt" to ensure that forwarded pointer fits to the expected range.

  \ID SBSW_SOAD_POINTER_WITH_OFFSET_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter with offset. Pointer can be used to
                      write to the corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering an additional function 
                         parameter. The offset is checked at runtime in a sub-routine or in the called function itself
                         (iterative call) to be smaller than the size indicated by the function parameter.

  \ID SBSW_SOAD_POINTER_WITH_OFFSET_FORWARD_NPduUdpTxBuffer
    \DESCRIPTION      The function forwards pointer to array "SoAd_NPduUdpTxBuffer" with offset. Pointer can be used to
                      write to the corresponding memory location.
    \COUNTERMEASURE   \N There is an indirection modeled with ComStackLib (Qualified use-case CSL03) in
                         "SoAd_NPduUdpTx" to get corresponding start and end index of "SoAd_NPduUdpTxBuffer".
                         "SoAd_NPduUdpTxDyn" is used to store the nPdu length calculated in range of start and end
                         index. Actually "NPduUdpTxBufferMinOfSocketUdp" is used instead of start and end index 
                         provided by "SoAd_NPduUdpTx". According to the Safe BSW assupmtions these values are
                         equivalent. After initialization the length stored in "SoAd_NPduUdpTxDyn" is always in valid
                         range. Calculations based on the stored value always consider the
                         "NPduUdpTxBufferMinOfSocketUdp".

  \ID SBSW_SOAD_CONST_POINTER_AND_POINTER_WITH_OFFSET_FORWARD_NPduUdpTxBuffer
    \DESCRIPTION      The function forwards pointer to array "SoAd_NPduUdpTxBuffer" with offset. Pointer can be used to
                      write to the corresponding memory location. Additionaly function forwards a pointer to constant.
    \COUNTERMEASURE   \N There is an indirection modeled with ComStackLib (Qualified use-case CSL03) in
                         "SoAd_NPduUdpTx" to get corresponding start and end index of "SoAd_NPduUdpTxBuffer".
                         "SoAd_NPduUdpTxDyn" is used to store the nPdu length calculated in range of start and end
                         index. Actually "NPduUdpTxBufferMinOfSocketUdp" is used instead of start and end index 
                         provided by "SoAd_NPduUdpTx". According to the Safe BSW assupmtions these values are
                         equivalent. After initialization the length stored in "SoAd_NPduUdpTxDyn" is always in valid
                         range. Calculations based on the stored value always consider the
                         "NPduUdpTxBufferMinOfSocketUdp".
                         A pointer to constant must not be used to write to the corresponding memory location.

  \ID SBSW_SOAD_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to constant.
    \COUNTERMEASURE   \N A pointer to constant must not be used to write to the corresponding memory location.

  \ID SBSW_SOAD_POINTER_AND_NULL_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter and a "null" pointer which could be
                      used to write to the corresponding memory locations.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range. This is ensured by the caller. To
                         forward a "null" pointer is supported by the function.

  \ID SBSW_SOAD_POINTER_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter which could be
                      used to write to the corresponding memory location and a pointer to constant.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type or an additional
                         function parameter is used to describe pointer validity. This is ensured by the caller.
                         A pointer to constant must not be used to write to the corresponding memory location.

  \ID SBSW_SOAD_POINTER_WITH_OFFSET_AND_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter with offset and directly without
                      offset. Both pointer can be used to write to the corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type of pointer or an
                         additional function parameter. The offset is checked at runtime to be smaller than the size
                         indicated by the function parameter.

  \ID SBSW_SOAD_POINTER_WITH_OFFSET_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter with offset which can be used to write
                      to the corresponding memory location and a pointer to constant.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering an additional function
                         parameter. The offset is checked at runtime to be smaller than the size indicated by the
                         function parameter. A pointer to constant must not be used to write to the corresponding
                         memory location.

  \ID SBSW_SOAD_VARIABLE_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to a local/global variable which could be used to write to memory
                      location of the variable.
    \COUNTERMEASURE   \N Local/global variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter.

  \ID SBSW_SOAD_VARIABLE_POINTER_FORWARD_CSL01
    \DESCRIPTION      The function forwards pointer to a local/global array generated by ComStackLib which could be
                      used to write to memory location.
    \COUNTERMEASURE   \N Local/global variables are located in valid memory locations. Therefore, address of array can
                         be passed as function parameter. The array size is forwarded as addtional function parameter
                         to indicate the valid memory range of the array. The value is checked according to qualified
                         use-case CSL01.

  \ID SBSW_SOAD_VARIABLE_POINTER_FORWARD_CSL02
    \DESCRIPTION      The function forwards pointer to a local/global array with index of array with same size which is
                      passed as function parameter. The pointer could be used to write to memory location.
    \COUNTERMEASURE   \N Local/global variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter. The validity of the index passed as function parameter is
                         defined at the function declaration and has to be ensured by the caller. The access with an
                         index of array with same size is qualified use-case CSL02 of ComStackLib.

  \ID SBSW_SOAD_VARIABLE_POINTER_FORWARD_CSL01_CSL05
    \DESCRIPTION      The function forwards pointer to a partition dependent array generated by ComStackLib which could
                      be used to write to memory location.
    \COUNTERMEASURE   \N Local/global variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter. The value is checked according to qualified use-case
                         CSL01.

  \ID SBSW_SOAD_VARIABLE_POINTER_FORWARD_CSL02_CSL03_CSL05
    \DESCRIPTION      The function forwards pointer to a local/global array with index of array with same size. The
                      index to array with same size is retrieved by indirection using ComStackLib. The index to
                      indirection is passed as function parameter. The pointer could be used to write to memory
                      location.
    \COUNTERMEASURE   \N Local/global variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter. The validity of the index passed as function parameter is
                         defined at the function declaration and has to be ensured by the caller. The access with an
                         index of array with same size is qualified use-case CSL02 of ComStackLib. The usage of
                         indirections is qualified use-case CSL03 of ComStackLib. The PartitionIdx has been derived in
                         advance by a qualified use-case of CSL05.

  \ID SBSW_SOAD_VARIABLE_POINTER_FORWARD_CSL02_CSL03_CSL05_AND_NULL_POINTER
    \DESCRIPTION      The function forwards pointer to a local/global array with index of array with same size and it
                      forwards a "null" pointer. The index to array with same size is retrieved by indirection using
                      ComStackLib. The index to indirection is passed as function parameter. The pointer could be used
                      to write to memory location. The "null" pointer can be used to write to the corresponding
                      invalid memory location.
    \COUNTERMEASURE   \N Local/global variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter. The validity of the index passed as function parameter is
                         defined at the function declaration and has to be ensured by the caller. The access with an
                         index of array with same size is qualified use-case CSL02 of ComStackLib. The usage of
                         indirections is qualified use-case CSL03 of ComStackLib. To forward a "null" pointer is
                         supported by the function. The PartitionIdx has been derived in advance by a qualified
                         use-case of CSL05.

  \ID SBSW_SOAD_POINTER_FORWARD_IfRxBuffer
    \DESCRIPTION      The function forwards pointer to array "SoAd_IfRxBuffer" with index stored in a global variable
                      "IfRxBufferIdxOfRxBufferConfigDyn". The pointer could be used to write to memory location.
    \COUNTERMEASURE   \N The global variable is set in SoAd_RxIf_TcpPduHdrReceiveHeader() which is called previously. A
                         runtime check ensures that the value is in valid range. Additionally
                         SoAd_RxIf_TcpPduHdrReceiveHeader() checks that this function is not able to exceed the valid
                         range beyond the index. Only if SoAd_RxIf_TcpPduHdrReceiveHeader() succeeds this function is
                         called.

  \ID SBSW_SOAD_VARIABLE_POINTER_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to a local/global variable which could be used to write to memory
                      location of the variable and a pointer to constant.
    \COUNTERMEASURE   \N Local/global variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter. A pointer to constant must not be used to write to the
                         corresponding memory location.

  \ID SBSW_SOAD_VARIABLE_POINTER_CSL02_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to a local/global array with index of array with same size which is
                      passed as function parameter and pointer to constant. None-constant pointers could be used to
                      write to memory location.
    \COUNTERMEASURE   \N Local/global variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter. The validity of the index passed as function parameter is
                         defined at the function declaration and has to be ensured by the caller. The access with an
                         index of array with same size is qualified use-case CSL02 of ComStackLib. A pointer to
                         constant must not be used to write to the corresponding memory location.

  \ID SBSW_SOAD_VARIABLE_POINTER_CSL03_CSL05_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to a local/global array with index of an optional indirection which
                      is accessed with an index passed as function parameter and pointer to constant. None-constant
                      pointers could be used to write to memory location.
    \COUNTERMEASURE   \N Local/global variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter. The validity of the index passed as function parameter is
                         defined at the function declaration and has to be ensured by the caller. The availability of
                         the optional indirection (qualified use-case CSL03 of ComStackLib) is checked at runtime. A
                         pointer to constant must not be used to write to the corresponding memory location. The
                         PartitionIdx has been derived in advance by a qualified use-case of CSL05.

  \ID SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter, pointer to a local/global variable
                      and pointer to constant. None-constant pointers could be used to write to memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type of pointer or an
                         additional function parameter is used to describe pointer validity. This is ensured by the
                         caller. Local/global variables are located in valid memory locations. Therefore, address of
                         variable can be passed as function parameter. A pointer to constant must not be used to write
                         to the corresponding memory location.

  \ID SBSW_SOAD_OPTIONAL_POINTER_FORWARD_CSL03_CSL05
    \DESCRIPTION      The function forwards pointer to an optional array generated by ComStackLib which could be used
                      to write to memory location.
    \COUNTERMEASURE   \N The pointer to the array generated by ComStackLib is based on qualified use-case CSL03 of
                         ComStackLib. According to the Safe BSW assumptions modeled in ComStackLib it is ensured that
                         optional indirection is available here. The index used to access the indirection may depend
                         on a function parameter. The validity of the function parameter is defined at the function
                         declaration and has to be ensured by the caller. The PartitionIdx has been derived in advance
                         by a qualified use-case of CSL05.

  \ID SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter and to a local/global variable. Both
                      pointer can be used to write to the corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type of pointer or an
                         additional function parameter is used to describe pointer validity. This is ensured by the
                         caller. Local/global variables are located in valid memory locations. Therefore, address of
                         variable can be passed as function parameter.

  \ID SBSW_SOAD_POINTER_EXPECTED_SIZE_AND_VARIABLE_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter which requires a specific length and
                      to a local/global variable. Both pointer can be used to write to the corresponding memory
                      location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering additional function
                         parameter. This is ensured by the caller. The required range is checked previously against the
                         additional function parameter by a sub-routine in this function. Local/global variables are
                         located in valid memory locations. Therefore, address of variable can be passed as function
                         parameter.

  \ID SBSW_SOAD_POINTER_POINTER_AND_VARIABLE_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter as pointer and to a local/global
                      variable. Both pointer can be used to write to the corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering an additional function
                         parameter which is used to describe pointer validity. This is ensured by the caller.
                         Local/global variables are located in valid memory locations. Therefore, address of
                         variable can be passed as function parameter.

  \ID SBSW_SOAD_POINTER_AND_POINTER_FORWARD_CSL01
    \DESCRIPTION      The function forwards pointer passed as function parameter and to an array generated by
                      ComStackLib. Both pointer can be used to write to the corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type of pointer or an
                         additional function parameter is used to describe pointer validity. This is ensured by the
                         caller. The pointer to the array generated by ComStackLib is based on qualified use-case
                         CSL01 of ComStackLib.

  \ID SBSW_SOAD_POINTER_AND_CONST_POINTER_FORWARD_CSL02
    \DESCRIPTION      The function forwards pointer passed as function parameter and to an element generated by
                      ComStackLib. Both pointer can be used to write to the corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type of pointer or an
                         additional function parameter is used to describe pointer validity. This is ensured by the
                         caller. The pointer to the element generated by ComStackLib is based on qualified use-case
                         CSL02 of ComStackLib.

  \ID SBSW_SOAD_CONST_POINTER_AND_OPTIONAL_POINTER_FORWARD_CSL03_CSL05
    \DESCRIPTION      The function forwards pointer to constant and to an optional element generated by ComStackLib.
                      The pointer to optional element generated by ComStackLib can be used to write to the
                      corresponding memory location.
    \COUNTERMEASURE   \N A pointer to constant must not be used to write to the corresponding memory location. The
                         pointer to the element generated by ComStackLib is based on qualified use-case CSL03 of
                         ComStackLib. According to the Safe BSW assumptions modeled in ComStackLib it is ensured that
                         optional indirection is available here. The index used to access the indirection may depend
                         on a function parameter. The validity of the function parameter is defined at the function
                         declaration and has to be ensured by the caller. In case element generated by ComStackLib is
                         an array an addtional parameter describes the valid range. The value of the additional
                         parameter is verified by a runtime check or the Safe BSW assumptions modeled in ComStackLib.
                         The PartitionIdx has been derived in advance by a qualified use-case of CSL05.

  \ID SBSW_SOAD_SOCK_ADDR_CAST_POINTER_STRUCT_ELEMENT_FORWARD
    \DESCRIPTION      The function forwards pointer to struct element after casting a pointer passed as function
                      parameter to a different type. This may lead to access violations when pointer is not valid.
    \COUNTERMEASURE   \N Module casts a specific struct type to a generic struct type which is used as function
                         parameter. Depending on a common struct element (used in all specific struct types and
                         generic struct) module can cast back to the corresponding specific struct type. By checking
                         the common struct element it is ensured that only valid memory location is accessed. Refer to
                         definition of generic type "SoAd_SockAddrType" and specfic types "SoAd_SockAddrInetType" and
                         "SoAd_SockAddrInet6Type". The validity of the function parameter is defined at the function
                         declaration and has to be ensured by the caller. "SoAd_SockAddrInetType" and
                         "SoAd_SockAddrInet6Type" have additional common struct elements.

  \ID SBSW_SOAD_SOCK_ADDR_CAST_POINTER_STRUCT_ELEMENT_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to struct element after casting a pointer passed as function
                      parameter to a different type. This may lead to access violations when pointer is not valid.
                      Additionally the function forwards pointer to constant.
    \COUNTERMEASURE   \N Module casts a specific struct type to a generic struct type which is used as function
                         parameter. Depending on a common struct element (used in all specific struct types and
                         generic struct) module can cast back to the corresponding specific struct type. By checking
                         the common struct element it is ensured that only valid memory location is accessed. Refer to
                         definition of generic type "SoAd_SockAddrType" and specfic types "SoAd_SockAddrInetType" and
                         "SoAd_SockAddrInet6Type". The validity of the function parameter is defined at the function
                         declaration and has to be ensured by the caller. "SoAd_SockAddrInetType" and
                         "SoAd_SockAddrInet6Type" have additional common struct elements.
                         A pointer to constant must not be used to write to the corresponding memory location.

  \ID SBSW_SOAD_SOCK_ADDR_VARIABLE_POINTER_AND_VARIABLE_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to a local/global variable with cast to a different struct type
                      which could be used to write to memory location of the variable.
                      Additionally the function forwards pointer to a local/global variable which could be used to
                      write to memory location of the variable.
    \COUNTERMEASURE   \N Module casts a specific struct type to a generic struct type which is used as function
                         parameter. Depending on a common struct element (used in all specific struct types and
                         generic struct) module can cast back to the corresponding specific struct type. By checking
                         the common struct element it is ensured that only valid memory location is accessed. Refer to
                         definition of generic type "SoAd_SockAddrType" and specfic types "SoAd_SockAddrInetType" and
                         "SoAd_SockAddrInet6Type".
                         Local/global variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter.

  \ID SBSW_SOAD_SOCK_ADDR_CAST_POINTER_WRITE
    \DESCRIPTION      The function casts a pointer to a different struct type and uses struct elements of the different
                      struct type to write to the memory location the pointer points to.
    \COUNTERMEASURE   \R Module casts a specific struct type to a generic struct type which is used as function
                         parameter. Depending on a common struct element (used in all specific struct types and
                         generic struct) module can cast back to the corresponding specific struct type. By checking
                         the common struct element it is ensured that only valid memory location is accessed. This is
                         done by a runtime check. Refer to definition of generic type "SoAd_SockAddrType" and specfic
                         types "SoAd_SockAddrInetType" and "SoAd_SockAddrInet6Type".

  \ID SBSW_SOAD_POINTER_WRITE
    \DESCRIPTION      Write access to pointer passed as function parameter.
    \COUNTERMEASURE   \N Pointer passed as function parameter points to valid memory location. This includes struct
                         members in case pointer points to a struct type. This is ensured by caller.

  \ID SBSW_SOAD_POINTER_WRITE_EXTERNAL_CHECK
    \DESCRIPTION      Write access to a local pointer which is set previously by a subroutine.
    \COUNTERMEASURE   \N The subroutine ensures that the pointer points to a valid memory location according to a
                         minimum requested length. It is ensured that the index, which is used for write access to the
                         local pointer, does not exceed the requested length.

  \ID SBSW_SOAD_PARAMETER_IDX
    \DESCRIPTION      Write access to array element with index given as function parameter which is not checked for
                      validity. The index may be an index of array with same size using ComStackLib.
    \COUNTERMEASURE   \N The valid range of the function parameter is defined at the function declaration and
                         has to be ensured by the caller. In case index is index of different array qualified use-case
                         CSL02 of ComStackLib applies.

  \ID SBSW_SOAD_INDEX_BY_FUNCTION
    \DESCRIPTION      The function writes to array element with index retrieved by subfunction.
    \COUNTERMEASURE   \N Subfunction always returns a valid index for accessed array or indicates if returned value
                         must not be used (e.g. via specific function return value).

  \ID SBSW_SOAD_EXPECTED_SIZE_WRITE
    \DESCRIPTION      The function writes to an array with a specific index. The array size is not checked.
    \COUNTERMEASURE   \N The array has an expected length so indexes within this length can be used to write to
                         corresponding memory location. The expected length is specified by data type (e.g. array of
                         specific size), by Safe BSW assumptions modeled in ComStackLib or by size restrictions in case
                         of function parameter.

  \ID SBSW_SOAD_FUNCTION_PTR
    \DESCRIPTION      Calling a function pointer stored in an array with an index using ComStackLib.
    \COUNTERMEASURE   \S The user of MICROSAR Safe shall perform the integration (ISO 26262:6-10) and verification
                         (ISO 26262:6-11) processes as required by ISO 26262.
                         SMI-4
                      \R In case an optional function pointer is used, availability is enusured by a runtime "null"
                         pointer check. Index validity is already ensured by qualified use-case CSL03 of ComStackLib.
                         In case of optional indirection it is ensured that optional indirection is available according
                         to Safe BSW assumptions modeled in ComStackLib.

SBSW_JUSTIFICATION_END */

/* COV_JUSTIFICATION_BEGIN

  \ID COV_SOAD_COMPATIBILITY
    \ACCEPT TX
    \ACCEPT XF
    \REASON [COV_MSR_COMPATIBILITY]

  \ID COV_SOAD_QM_FEATURE_MULTI_PARTITION
    \ACCEPT TX
    \ACCEPT XF
    \REASON This code is part of a QM-Feature and has to be deactivated for SafeBSW.

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: SoAd.c
 *********************************************************************************************************************/
