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
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TcpIpXcp.c
 *    Component:  TcpIpXcp Implementation
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Implementation of XCP over TcpIp based on Vector AUTOSAR Stack
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

#define TCPIPXCP_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIpXcp.h"
#include "SoAd.h"
#include "Xcp.h"

#if ( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
  #include "Det.h"              /* Include Diagnostic Event Manager */
#endif

#include "SchM_Xcp.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if (  (TCPIPXCP_SW_MAJOR_VERSION != (0x07u)) \
    || (TCPIPXCP_SW_MINOR_VERSION != (0x00u)) \
    || (TCPIPXCP_SW_PATCH_VERSION != (0x00u)) )
  #error "Vendor specific version numbers of TcpIpXcp.c and TcpIpXcp.h are inconsistent"
#endif

/* AUTOSAR version information check has to match definition in header file */
#if (  (TCPIPXCP_AR_MAJOR_VERSION != (0x04u)) \
    || (TCPIPXCP_AR_MINOR_VERSION != (0x00u)) \
    || (TCPIPXCP_AR_PATCH_VERSION != (0x03u)) )
  #error "AUTOSAR Specification Version numbers of TcpIpXcp.c and TcpIpXcp.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/
#define TCPIPXCP_MAX(a, b)   (((a) > (b)) ? (a) : (b)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#if !defined ( TCPIPXCP_COPY )
  #if defined ( XCP_ENABLE_ALIGNED_DTO )
    #define TCPIPXCP_COPY(dest, src, length) TcpIpXcp_FastCopy( (DAQBYTEPTR)(dest), (ROMDAQBYTEPTR)(src), (length) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
  #else
  #define TCPIPXCP_COPY(dest, src, length) Xcp_MemCpy( (DAQBYTEPTR)(dest), (ROMDAQBYTEPTR)(src), (length) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
  #endif
#endif

/* Configuration access (depending on configuration variant)*/
#if ( TCPIPXCP_CONFIG_VARIANT == 3 )
# define TcpIpXcp_GetSoAdTxPduId(idx) TcpIpXcp_Configuration->TcpIpXcp_XcpPduPtr[idx].SoAdTxPduId /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define TcpIpXcp_GetTxConfPduId(idx) TcpIpXcp_Configuration->TcpIpXcp_XcpPduPtr[idx].TxConfPduId /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define TcpIpXcp_GetRxPduId(idx)     TcpIpXcp_Configuration->TcpIpXcp_XcpPduPtr[idx].RxPduId /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define TcpIpXcp_GetSoConId(idx)     TcpIpXcp_Configuration->TcpIpXcp_XcpPduPtr[idx].SoConId /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#else /* ( TCPIPXCP_CONFIG_VARIANT == 1 ) */
# define TcpIpXcp_GetSoAdTxPduId(idx) TcpIpXcp_PduIdField[idx].SoAdTxPduId /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define TcpIpXcp_GetTxConfPduId(idx) TcpIpXcp_PduIdField[idx].TxConfPduId /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define TcpIpXcp_GetRxPduId(idx)     TcpIpXcp_PduIdField[idx].RxPduId /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define TcpIpXcp_GetSoConId(idx)     TcpIpXcp_PduIdField[idx].SoConId /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#endif
  /* TCPIPXCP_CONFIG_VARIANT */

/* States of TcpIpXcp_SendWithoutQueueState */
#define TCPIPXCP_MSG_IDLE           0u
#define TCPIPXCP_MSG_PENDING        1u

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/
typedef union { /* PRQA S 0750 */ /* MD_MSR_Union */
  uint8  fc[TCPIPXCP_PDU_SIZE];  /* PRQA S 3493, 3494 */ /* MD_TCPIPXCP_3493_4 */
  uint32 dw[(TCPIPXCP_PDU_SIZE)/4u];  /* PRQA S 3493, 3494 */ /* MD_TCPIPXCP_3493_4 */
} TcpIpXcpAlignedFrameCacheType;


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/
#define TCPIPXCP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA S 3218 3 */ /* MD_TCPIPXCP_3218_FileScopeStatic */
TCPIPXCP_LOCAL VAR(TcpIpXcpAlignedFrameCacheType, TCPIPXCP_VAR_NOINIT) TcpIpXcp_TxFrameCache[TCPIPXCP_NUMBER_OF_CHANNELS]; /* PRQA S 1514, 3408 */ /* MD_TCPIPXCP_1514, MD_TCPIPXCP_3408 */

#if ( TCPIPXCP_CONFIG_VARIANT == 3u )
P2CONST(TcpIpXcp_ConfigType, TCPIPXCP_VAR_NOINIT, TCPIPXCP_PBCFG) TcpIpXcp_Configuration; /* PRQA S 3408 */ /* MD_TCPIPXCP_3408 */
#endif

VAR(PduInfoType, TCPIPXCP_VAR_NOINIT) TcpIpXcp_QueuedPduInfo[TCPIPXCP_NUMBER_OF_CHANNELS]; /* PRQA S 3408, 1514 */ /* MD_TCPIPXCP_3408 */
volatile VAR(TcpIpXcp_TimeoutTimerType, TCPIPXCP_VAR_NOINIT) TcpIpXcp_ConfTimeoutTimer[TCPIPXCP_NUMBER_OF_CHANNELS]; /* PRQA S 3408 */ /* MD_TCPIPXCP_3408 */

#if ( XCP_NUMBER_OF_CHANNELS <= 1u )
VAR(PduIdType, TCPIPXCP_VAR_NOINIT) TcpIpXcp_RxPduId; /* PRQA S 3408 */ /* MD_TCPIPXCP_3408 */
#endif

#if ( TCPIPXCP_ENABLE_PDUMODE == STD_ON )
VAR(TcpIpXcp_PduSetModeType, TCPIPXCP_VAR_NOINIT) TcpIpXcp_PduState[TCPIPXCP_NUMBER_OF_CHANNELS]; /* PRQA S 3408 */ /* MD_TCPIPXCP_3408 */
#endif

#define TCPIPXCP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define TCPIPXCP_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(uint16, TCPIPXCP_VAR_NOINIT) TcpIpXcp_SequenceCounter[TCPIPXCP_NUMBER_OF_CHANNELS]; /* PRQA S 3408 */ /* MD_TCPIPXCP_3408 */
volatile VAR(uint16, TCPIPXCP_VAR_NOINIT) TcpIpXcp_ConcatPos[TCPIPXCP_NUMBER_OF_CHANNELS]; /* PRQA S 3408 */ /* MD_TCPIPXCP_3408 */

#define TCPIPXCP_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define TCPIPXCP_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

volatile VAR(uint8, TCPIPXCP_VAR_NOINIT) TcpIpXcp_SendWithoutQueueState[TCPIPXCP_NUMBER_OF_CHANNELS]; /* PRQA S 3408 */ /* MD_TCPIPXCP_3408 */

#define TCPIPXCP_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define TCPIPXCP_START_SEC_VAR_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
TCPIPXCP_LOCAL volatile VAR(uint8, TCPIPXCP_VAR_INIT) TcpIpXcp_InitializationState = TCPIPXCP_UNINIT; /* PRQA S 3408 */ /* MD_TCPIPXCP_3408 */
#endif
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
VAR(uint8, TCPIPXCP_VAR_INIT) TcpIpXcp_ControlDeniedCount = 0u; /* PRQA S 3408 */ /* MD_TCPIPXCP_3408 */
#endif

#define TCPIPXCP_STOP_SEC_VAR_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
# define TCPIPXCP_START_SEC_VAR_INIT_UNSPECIFIED_SAFE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* TL Enable/Disable state */
VAR(uint8, TCPIPXCP_VAR_INIT) TcpIpXcp_ControlState = kXcponTcpIp_Control_Enable;

# define TCPIPXCP_STOP_SEC_VAR_INIT_UNSPECIFIED_SAFE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
#define TCPIPXCP_START_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Requirement Specification Template version */
CONST(uint8, TCPIPXCP_CONST) TcpIpXcp_MainVersion    = (uint8)TCPIPXCP_SW_MAJOR_VERSION;
CONST(uint8, TCPIPXCP_CONST) TcpIpXcp_SubVersion     = (uint8)TCPIPXCP_SW_MINOR_VERSION;
CONST(uint8, TCPIPXCP_CONST) TcpIpXcp_ReleaseVersion = (uint8)TCPIPXCP_SW_PATCH_VERSION;

#define TCPIPXCP_STOP_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define TCPIPXCP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if defined ( XCP_ENABLE_ALIGNED_DTO )
/**********************************************************************************************************************
 *  TcpIpXcp_FastCopy()
 *********************************************************************************************************************/
/*! 
 *  \brief       32Bit copy function for aligned data.
 *  \details     -
 *  \param[out]  dest    Pointer to the destination.
 *  \param[in]   src     Pointer to the source.
 *  \param[in]   len     The length of the data to be copied.
 *  \pre         -
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      Available only if XCP_ENABLE_ALIGNED_DTO is defined.
 *  \ingroup     General
 **********************************************************************************************************************/
TCPIPXCP_LOCAL FUNC(void, TCPIPXCP_CODE) TcpIpXcp_FastCopy( P2VAR(uint8, AUTOMATIC, TCPIPXCP_VAR_NOINIT) dest, P2CONST(uint8, AUTOMATIC, TCPIPXCP_VAR_NOINIT) src, uint16 len );
#endif


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

#if defined ( XCP_ENABLE_ALIGNED_DTO )
/**********************************************************************************************************************
 *  TcpIpXcp_FastCopy()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIPXCP_LOCAL FUNC(void, TCPIPXCP_CODE) TcpIpXcp_FastCopy( P2VAR(uint8, AUTOMATIC, TCPIPXCP_VAR_NOINIT) dest, P2CONST(uint8, AUTOMATIC, TCPIPXCP_VAR_NOINIT) src, uint16 len )
{
  while( len >= 4u )
  {
    *(P2VAR(uint32, AUTOMATIC, TCPIPXCP_VAR_NOINIT))dest = *(P2CONST(uint32, AUTOMATIC, TCPIPXCP_VAR_NOINIT))src; /* PRQA S 0310, 3305 */ /* MD_TCPIPXCP_0310 */ /* MD_TCPIPXCP_3305 */
    dest = &dest[4]; /* PRQA S 1338 */ /* MD_TCPIPXCP_1338 */
    src = &src[4]; /* PRQA S 1338 */ /* MD_TCPIPXCP_1338 */
    len -= 4u; /* PRQA S 1338 */ /* MD_TCPIPXCP_1338 */
  }
  while( len > 0u )
  {
    *(P2VAR(uint8, AUTOMATIC, TCPIPXCP_VAR_NOINIT))dest = *(P2CONST(uint8, AUTOMATIC, TCPIPXCP_VAR_NOINIT))src;
    dest = &dest[1]; /* PRQA S 1338 */ /* MD_TCPIPXCP_1338 */
    src = &src[1]; /* PRQA S 1338 */ /* MD_TCPIPXCP_1338 */
    len -= 1u; /* PRQA S 1338 */ /* MD_TCPIPXCP_1338 */
  }
}
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Xcp_SoAdRxIndication
 **********************************************************************************************************************/
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
  /* PRQA S 6080 3 */ /* MD_MSR_STMIF */
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6010 1 */ /* MD_MSR_STPTH */
FUNC(void, TCPIPXCP_CODE) Xcp_SoAdRxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, TCPIPXCP_APPL_DATA) PduInfoPtr) /* PRQA S 2889 */ /* MD_TCPIPXCP_2889 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 xcpFrameLen;
#if ( XCP_NUMBER_OF_CHANNELS > 1u )
  PduIdType TcpIpXcp_RxPduId;
#endif
  uint8 errorId = TCPIPXCP_E_NO_ERROR;

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  /* #10 Check whether XCP functionality shall be enabled. */
  if ( TcpIpXcp_ControlState == kXcponTcpIp_Control_Enable )
#endif
  {
    /* ----- Development Error Checks ------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
    /* #20 Perform parameter plausibility checks and report error in failure case. */
    if( TcpIpXcp_InitializationState == TCPIPXCP_UNINIT )
    {
      errorId = TCPIPXCP_E_NOT_INITIALIZED;
    }
    else if(PduInfoPtr == NULL_PTR)
    {
      errorId = TCPIPXCP_E_PARAM_POINTER;
    }
    else if(PduInfoPtr->SduDataPtr == NULL_PTR)
    {
      errorId = TCPIPXCP_E_PARAM_POINTER;
    }
# if ( XCP_NUMBER_OF_CHANNELS > 1u )
    else if((XCP_TRANSPORT_LAYER_TCPIP + RxPduId) >= XCP_NUMBER_OF_CHANNELS) /* PRQA S 2986 */ /* MD_TCPIPXCP_2985_6 */
    {
      errorId = TCPIPXCP_E_INV_SOCK_IDX;
    }
# endif
    else
#endif
    {
      /* ----- Implementation ------------------------------------- */
      /* #30 The Xcp Rx PDU Id is stored to memorize the reception channel. Depending on configuration options this
              is either done unconditionally or optionally when no other connection is interrupted. */
#if ( XCP_NUMBER_OF_CHANNELS > 1u )
      TcpIpXcp_RxPduId = RxPduId;
#else
# if ( TCPIPXCP_NUMBER_OF_CHANNELS > 1u )
      if ( TcpIpXcp_RxPduId != RxPduId )
      {
#  if ( TCPIPXCP_MULTI_CONN_PROT == STD_ON )
        /* #40 When a existing connection should be interrupted then return and do not process the frame and transmit a response. */
        if ( 0u != (Xcp_GetSessionStatus((Xcp_ChannelType)(XCP_TRANSPORT_LAYER_TCPIP + TcpIpXcp_RxPduId)) & (SessionStatusType)SS_CONNECTED) ) /* PRQA S 2986 */ /* MD_TCPIPXCP_2985_6 */
        {
          return;
        }
        else
#  endif
        {
          TcpIpXcp_RxPduId = RxPduId;
        }
      }
# else
      /* Verify RX Pdu Id */
      if(RxPduId == TcpIpXcp_GetRxPduId(0))
      {
        /* Store the Rx PDU Id for the reception. */
        TcpIpXcp_RxPduId = RxPduId;
# endif
#endif

        /* #50 We check the incoming frame for valid length in the TcpIp XCP header. */
        xcpFrameLen = (PduInfoPtr->SduDataPtr[0]) | ((uint16)PduInfoPtr->SduDataPtr[1] << 8);
        if( (xcpFrameLen <= (PduInfoPtr->SduLength - (uint16)TCPIPXCP_HEADER_SIZE))
          /* ESCAN00100672 */
         && (xcpFrameLen <= (TCPIPXCP_MAX(kTcpIpXcpMaxCTO, kTcpIpXcpMaxDTO))))  /* PRQA S 3493, 3494 */ /* MD_TCPIPXCP_3493_4 */
        {
          /* #60 In case of connect we set this as active TL. */
          if(0xffu == PduInfoPtr->SduDataPtr[TCPIPXCP_HEADER_SIZE])
          {
            Xcp_SetActiveTl((Xcp_ChannelType)(XCP_TRANSPORT_LAYER_TCPIP + TcpIpXcp_RxPduId), kTcpIpXcpMaxCTO, kTcpIpXcpMaxDTO, (uint8)(XCP_TRANSPORT_LAYER_TCPIP + TcpIpXcp_RxPduId)); /* PRQA S 2986 */ /* MD_TCPIPXCP_2985_6 */
          }

          /* #70 And last but not least, we forward the received frame to the protocol layer. */
          if((XCP_TRANSPORT_LAYER_TCPIP + TcpIpXcp_RxPduId) == Xcp_GetActiveTl((uint8)(XCP_TRANSPORT_LAYER_TCPIP + TcpIpXcp_RxPduId))) /* PRQA S 2986 */ /* MD_TCPIPXCP_2985_6 */
          {
            /* Copying of the received frame to an 32-Bit aligned buffer is not necessary as ETH pdu are already aligned. */
            /* PRQA S 0310 3 */ /* MD_TCPIPXCP_0310 */
            /* PRQA S 2986 2 */ /* MD_TCPIPXCP_2985_6 */
            /* PRQA S 3305 1 */ /* MD_TCPIPXCP_3305 */
            Xcp_Command((uint8)(XCP_TRANSPORT_LAYER_TCPIP + TcpIpXcp_RxPduId), (uint32*)&(PduInfoPtr->SduDataPtr[TCPIPXCP_HEADER_SIZE]));
          }
        }
#if ( XCP_NUMBER_OF_CHANNELS > 1u )
#else
# if ( TCPIPXCP_NUMBER_OF_CHANNELS > 1u )
# else
      }
# endif
#endif
    }
    /* ----- Development Error Report --------------------------------------- */
# if( TCPIPXCP_DEV_ERROR_REPORT == STD_ON )
    if( errorId != TCPIPXCP_E_NO_ERROR )
    {
      (void)Det_ReportError( TCPIPXCP_MODULE_ID, 0u, TCPIPXCP_RXINDICATION_SERVICE_ID, errorId );
    }
# else
    XCP_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif
  }
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  else
  {
    TcpIpXcp_ControlDeniedCount++;
  }
#endif
}

/***********************************************************************************************************************
 *  Xcp_SoAdTxConfirmation
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIPXCP_CODE) Xcp_SoAdTxConfirmation(PduIdType TxPduId)
{
  /* ----- Local Variables ---------------------------------------------- */
#if (TCPIPXCP_BURST_MODE == STD_OFF)
  uint8_least i;
#endif
  uint8 errorId = TCPIPXCP_E_NO_ERROR;

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  /* #10 Check whether XCP functionality shall be enabled. */
  if ( TcpIpXcp_ControlState == kXcponTcpIp_Control_Enable )
#endif
  {
    /* ----- Development Error Checks ------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
    /* #20 Perform parameter plausibility checks and report error in failure case. */
    if( TcpIpXcp_InitializationState == TCPIPXCP_UNINIT )
    {
      errorId = TCPIPXCP_E_NOT_INITIALIZED;
    }
    else
#endif
    {
      /* ----- Implementation ------------------------------------- */
      /* #30 If burst mode is disabled: search respective channel handle an trigger the Xcp send callback. */
#if (TCPIPXCP_BURST_MODE == STD_OFF)
      for(i=0u; i<TCPIPXCP_NUMBER_OF_CHANNELS; i++)
      {
        if( TcpIpXcp_GetTxConfPduId(i) == TxPduId )
        {
          TcpIpXcp_ConfTimeoutTimer[i] = (TcpIpXcp_TimeoutTimerType)0u;
          (void)Xcp_SendCallBack((uint8)(XCP_TRANSPORT_LAYER_TCPIP + i)); /* PRQA S 2986 */ /* MD_TCPIPXCP_2985_6 */
          break;
        }
      }
#else
      /* #40 Otherwise: do nothing. */
      XCP_DUMMY_STATEMENT (TxPduId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
    }
    /* ----- Development Error Report --------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_REPORT == STD_ON )
    if( errorId != TCPIPXCP_E_NO_ERROR )
    {
      (void)Det_ReportError( TCPIPXCP_MODULE_ID, 0u, TCPIPXCP_TXCONFIRMATION_SERVICE_ID, errorId );
    }
#else
    XCP_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
  }
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  else
  {
    TcpIpXcp_ControlDeniedCount++;
  }
#endif
}

#if ( TCPIPXCP_MODE_CHG_API == STD_ON ) /* COV_TCPIPXCP_UNSUPPORTED_FEATURE */
/***********************************************************************************************************************
 *  Xcp_SoConModeChg
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIPXCP_CODE) Xcp_SoConModeChg(SoAd_SoConIdType SoConId, SoAd_SoConModeType Mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = TCPIPXCP_E_NO_ERROR;

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  /* #10 Check whether XCP functionality shall be enabled. */
  if ( TcpIpXcp_ControlState == kXcponTcpIp_Control_Enable )
#endif
  {
    /* ----- Development Error Checks ------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
    /* #20 Perform parameter plausibility checks and report error in failure case. */
    if( TcpIpXcp_InitializationState == TCPIPXCP_UNINIT )
    {
      errorId = TCPIPXCP_E_NOT_INITIALIZED;
    }
    else
#endif
    {
      /* ----- Implementation ------------------------------------- */
#if( TCPIPXCP_PROTOCOL_FORMAT == TCPIPXCP_PROTOCOL_TCP ) /* COV_TCPIPXCP_UNSUPPORTED_FEATURE */
      if( SOAD_SOCON_OFFLINE == Mode )
      {
        uint8_least i;

        /* #30 If protocol is TCP: search respective channel handle and disconnect if a channel handle has been found. */
        for(i=0; i<TCPIPXCP_NUMBER_OF_CHANNELS; i++)
        {
          if( TcpIpXcp_GetSoConId(i) == SoConId )
          {
            break;
          }
        }
        
        if( i < TCPIPXCP_NUMBER_OF_CHANNELS )
        {
          TcpIpXcp_ConfTimeoutTimer[i] = (TcpIpXcp_TimeoutTimerType)0u;
          Xcp_Disconnect((uint8)(XCP_TRANSPORT_LAYER_TCPIP + i));
        }
      }
#else
      /* #40 Otherwise: do nothing. */
      XCP_DUMMY_STATEMENT (SoConId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
      XCP_DUMMY_STATEMENT (Mode); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
    }
    /* ----- Development Error Report --------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_REPORT == STD_ON )
    if( errorId != TCPIPXCP_E_NO_ERROR )
    {
      (void)Det_ReportError( TCPIPXCP_MODULE_ID, 0u, TCPIPXCP_SOCONMODECHG_SERVICE_ID, errorId );
    }
#else
    XCP_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
  }
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  else
  {
    TcpIpXcp_ControlDeniedCount++;
  }
#endif
}
#endif

/***********************************************************************************************************************
 *  TcpIpXcp_Send
 **********************************************************************************************************************/
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
 */
  /* PRQA S 6080 2 */ /* MD_MSR_STMIF */
  /* PRQA S 6010 1 */ /* MD_MSR_STPTH */
FUNC(void, TCPIPXCP_CODE) TcpIpXcp_Send( uint8 Xcp_Channel, uint16 len, P2CONST(uint8, AUTOMATIC, TCPIPXCP_APPL_DATA) msg )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 currentPos;
  uint8 actualChannel;
  uint8 errorId = TCPIPXCP_E_NO_ERROR;
#if ( TCPIPXCP_CONCATENATION_MODE == STD_OFF )
  PduInfoType PduInfo;
#endif

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  /* #10 Check whether XCP functionality shall be enabled. */
  if ( TcpIpXcp_ControlState == kXcponTcpIp_Control_Enable )
#endif
  {
    /* #15 Determine the correct channel index based on XCP multiple client configuration option. */
#if ( XCP_NUMBER_OF_CHANNELS <= 1u )
    XCP_DUMMY_STATEMENT (Xcp_Channel); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
    actualChannel = (uint8)TcpIpXcp_RxPduId;
#else
    actualChannel = Xcp_Channel - XCP_TRANSPORT_LAYER_TCPIP; /* PRQA S 2985 */ /* MD_TCPIPXCP_2985_6 */
#endif
    /* ----- Development Error Checks ------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
    /* #20 Perform parameter plausibility checks and report error in failure case. */
    if( TcpIpXcp_InitializationState == TCPIPXCP_UNINIT )
    {
      errorId = TCPIPXCP_E_NOT_INITIALIZED;
    }
    else if (msg == NULL_PTR)
    {
      errorId = TCPIPXCP_E_PARAM_POINTER;
    }
    else if (actualChannel >= TCPIPXCP_NUMBER_OF_CHANNELS)
    {
      errorId = TCPIPXCP_E_INV_SOCK_IDX;
    }
    else
#endif
    {
      /* ----- Implementation ------------------------------------- */
      /* #30 Prepare TcpIpXcp Header and insert the XCP frame. */
      currentPos = TcpIpXcp_ConcatPos[actualChannel];
      if ((currentPos + len + TCPIPXCP_HEADER_SIZE) <= TCPIPXCP_PDU_SIZE)
      {
        TcpIpXcp_TxFrameCache[actualChannel].fc[currentPos] = (uint8)(len & 0xffu); /* PRQA S 2985 */ /* MD_TCPIPXCP_2985_6 */
        TcpIpXcp_TxFrameCache[actualChannel].fc[currentPos + 1u] = (uint8)(len >> 8);
        TcpIpXcp_TxFrameCache[actualChannel].fc[currentPos + 2u] = (uint8)(TcpIpXcp_SequenceCounter[actualChannel] & 0xffu);
        TcpIpXcp_TxFrameCache[actualChannel].fc[currentPos + 3u] = (uint8)(TcpIpXcp_SequenceCounter[actualChannel] >> 8);
        TcpIpXcp_SequenceCounter[actualChannel]++;

        TCPIPXCP_COPY(&(TcpIpXcp_TxFrameCache[actualChannel].fc[currentPos + TCPIPXCP_HEADER_SIZE]), msg, len);
        TcpIpXcp_ConcatPos[actualChannel] = currentPos + len + TCPIPXCP_HEADER_SIZE;
      }

#if ( TCPIPXCP_CONCATENATION_MODE == STD_OFF )
      /* #35 In case concatenation mode is off we directly transmit the frame here by preparing the pdu information. */
      {
        PduInfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, TCPIPXCP_APPL_VAR)) &TcpIpXcp_TxFrameCache[actualChannel].fc[0];
        PduInfo.SduLength = (PduLengthType)TcpIpXcp_ConcatPos[actualChannel];

# if ( TCPIPXCP_ENABLE_PDUMODE == STD_ON )
        /* #40 If PDU Mode is set to OFFLINE we memorize the PDU information in the else path and sent it at a later point
               in time during the MainFunction when the PDU Mode is set to ONLINE again. */
        if (TCPIPXCP_SET_ONLINE == TcpIpXcp_PduState[actualChannel])
        {
# endif
          /* #50 And if required, we transmit it now. */
          TcpIpXcp_ConfTimeoutTimer[actualChannel] = (TcpIpXcp_TimeoutTimerType)TCPIPXCP_CONF_TIMEOUT;
          TcpIpXcp_ConcatPos[actualChannel] = 0u;
          if (SoAd_IfTransmit(TcpIpXcp_GetSoAdTxPduId(actualChannel), &PduInfo) == (Std_ReturnType)E_OK)
          {
            /* The message was sent successfully: do nothing. */
          }
          else
          {
            /* #60 If XCP Packet cannot be transmitted we store this information for later use in the MainFunction. */
            TcpIpXcp_ConfTimeoutTimer[actualChannel] = (TcpIpXcp_TimeoutTimerType)0u;
            TcpIpXcp_SendWithoutQueueState[actualChannel] = (uint8)TCPIPXCP_MSG_PENDING;
            TcpIpXcp_QueuedPduInfo[actualChannel] = PduInfo;
          }
# if ( TCPIPXCP_ENABLE_PDUMODE == STD_ON )
        }
        else
        {
          TcpIpXcp_SendWithoutQueueState[actualChannel] = (uint8)TCPIPXCP_MSG_PENDING;
          TcpIpXcp_QueuedPduInfo[actualChannel] = PduInfo;
        }
# endif
      }
#endif
    }
    /* ----- Development Error Report --------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_REPORT == STD_ON )
    if( errorId != TCPIPXCP_E_NO_ERROR )
    {
      (void)Det_ReportError( TCPIPXCP_MODULE_ID, 0u, TCPIPXCP_SEND_SERVICE_ID, errorId );
    }
#else
    XCP_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
  }
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  else
  {
    TcpIpXcp_ControlDeniedCount++;
  }
#endif
} 

/***********************************************************************************************************************
 *  TcpIpXcp_SendFlush
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIPXCP_CODE) TcpIpXcp_SendFlush( uint8 Xcp_Channel, uint8 XcpFlushTypeSel )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = TCPIPXCP_E_NO_ERROR;

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  /* #10 Check whether XCP functionality shall be enabled. */
  if ( TcpIpXcp_ControlState == kXcponTcpIp_Control_Enable )
#endif
  {
    /* ----- Development Error Checks ------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
    /* #20 Perform parameter plausibility checks and report error in failure case. */
    if( TcpIpXcp_InitializationState == TCPIPXCP_UNINIT )
    {
      errorId = TCPIPXCP_E_NOT_INITIALIZED;
    }
    else
#endif
    {
      /* ----- Implementation ------------------------------------- */
      /* #30 Do nothing since this API is only provided for compatibility. */

      XCP_DUMMY_STATEMENT (Xcp_Channel); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */  
      XCP_DUMMY_STATEMENT (XcpFlushTypeSel); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
    }
    /* ----- Development Error Report --------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_REPORT == STD_ON )
    if( errorId != TCPIPXCP_E_NO_ERROR )
    {
      (void)Det_ReportError( TCPIPXCP_MODULE_ID, 0u, TCPIPXCP_SENDFLUSH_SERVICE_ID, errorId );
    }
#else
    XCP_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
  }
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  else
  {
    TcpIpXcp_ControlDeniedCount++;
  }
#endif
}

/***********************************************************************************************************************
 *  TcpIpXcp_TLService
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(uint8, TCPIPXCP_CODE) TcpIpXcp_TLService( uint8 Xcp_Channel, P2CONST(uint8, AUTOMATIC, TCPIPXCP_APPL_DATA) pCmd )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = TCPIPXCP_E_NO_ERROR;

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  /* #10 Check whether XCP functionality shall be enabled. */
  if ( TcpIpXcp_ControlState == kXcponTcpIp_Control_Enable )
#endif
  {
    /* ----- Development Error Checks ------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
    /* #20 Perform parameter plausibility checks and report error in failure case. */
    if( TcpIpXcp_InitializationState == TCPIPXCP_UNINIT )
    {
      errorId = TCPIPXCP_E_NOT_INITIALIZED;
    }
    else
#endif
    {
      /* ----- Implementation ------------------------------------- */
      /* #30 Do nothing since this API is only provided for compatibility. */

      XCP_DUMMY_STATEMENT (Xcp_Channel); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */  
      XCP_DUMMY_STATEMENT (pCmd); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
    }
    /* ----- Development Error Report --------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_REPORT == STD_ON )
    if( errorId != TCPIPXCP_E_NO_ERROR )
    {
      (void)Det_ReportError( TCPIPXCP_MODULE_ID, 0u, TCPIPXCP_TLSERVICE_SERVICE_ID, errorId );
    }
#else
    XCP_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
  }
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  else
  {
    TcpIpXcp_ControlDeniedCount++;
  }
#endif

  return(XCP_CMD_UNKNOWN);
}

/***********************************************************************************************************************
 *  TcpIpXcp_MainFunction
 **********************************************************************************************************************/
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
 *
 *
 *
 */
  /* PRQA S 6010 3 */ /* MD_MSR_STPTH */
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(void, TCPIPXCP_CODE) TcpIpXcp_MainFunction( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least i;
#if ( TCPIPXCP_CONCATENATION_MODE == STD_ON )
  PduInfoType PduInfo;
  boolean messagePending;
  Std_ReturnType lResult;
# if (TCPIPXCP_BURST_MODE == STD_ON)
  uint16 burstCounter;
# endif
#endif

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  /* #10 Check whether XCP functionality shall be enabled. */
  if ( TcpIpXcp_ControlState == kXcponTcpIp_Control_Enable )
#endif
  {
    /* ----- Implementation ------------------------------------- */
    for( i = 0u; i < TCPIPXCP_NUMBER_OF_CHANNELS; i++ )
    {
#if ( TCPIPXCP_ENABLE_PDUMODE == STD_ON )
      /* #20 If PDU Mode is set to OFFLINE we memorize the PDU information in the else path and sent it at a later point
             in time during the MainFunction when the PDU Mode is set to ONLINE again. */
      if ( TCPIPXCP_SET_ONLINE == TcpIpXcp_PduState[i] )
#endif
      {
# if (TCPIPXCP_BURST_MODE == STD_ON)
        burstCounter = 0;
# endif
        /* #30 If a message is pending, we try to send it now. */
        if (TcpIpXcp_SendWithoutQueueState[i] == (uint8)TCPIPXCP_MSG_PENDING)
        {
          /* Clear the 'message pending' bit. */
          TcpIpXcp_SendWithoutQueueState[i] = (uint8)TCPIPXCP_MSG_IDLE;
          /* Try to transmit the XCP Packet */
# if (TCPIPXCP_BURST_MODE == STD_ON)
          TcpIpXcp_ConfTimeoutTimer[i] = 0;
# else
          TcpIpXcp_ConfTimeoutTimer[i] = (TcpIpXcp_TimeoutTimerType)TCPIPXCP_CONF_TIMEOUT;
# endif
          TcpIpXcp_ConcatPos[i] = 0u;
          if (SoAd_IfTransmit(TcpIpXcp_GetSoAdTxPduId(i), &TcpIpXcp_QueuedPduInfo[i]) == (Std_ReturnType)E_OK)
          {
            /* The message was sent successfully. */
# if (TCPIPXCP_BURST_MODE == STD_ON)
           burstCounter = 1;
# endif
          }
          else
          {
            /* The message is still pending. */
            TcpIpXcp_SendWithoutQueueState[i] = (uint8)TCPIPXCP_MSG_PENDING;
            TcpIpXcp_ConfTimeoutTimer[i] = (TcpIpXcp_TimeoutTimerType)0u;
          }
        }
      
#if ( TCPIPXCP_CONCATENATION_MODE == STD_ON )
        /* #35 If concatenation mode is enabled we try to prepare multiple XCP frames in one Ethernet frame for better bandwidth use. */
        if ((TcpIpXcp_SendWithoutQueueState[i] == (uint8)TCPIPXCP_MSG_IDLE)
         && (TcpIpXcp_ConfTimeoutTimer[i] == 0u))
        {
# if (TCPIPXCP_BURST_MODE == STD_ON)
          do
          {
            lResult = E_NOT_OK;
# endif
            /* #40 Concatenation logic, we insert the next frame, as long as there is enough space in the Eth PDU
                   and there are frames available. */
            messagePending = Xcp_TlQueryMessagePending((uint8)(XCP_TRANSPORT_LAYER_TCPIP + i)); /* PRQA S 2986 */ /* MD_TCPIPXCP_2985_6 */
            /* PRQA S 3494 3 */ /* MD_TCPIPXCP_3494 */
            while ((messagePending == TRUE)
               && (TcpIpXcp_ConcatPos[i] <= TCPIPXCP_PDU_SIZE) 
               && ((TCPIPXCP_PDU_SIZE - TcpIpXcp_ConcatPos[i]) >= (TCPIPXCP_MAX(kTcpIpXcpMaxCTO, kTcpIpXcpMaxDTO) + TCPIPXCP_HEADER_SIZE)))
            {
              (void)Xcp_SendCallBack((uint8)(XCP_TRANSPORT_LAYER_TCPIP + i)); /* PRQA S 2986 */ /* MD_TCPIPXCP_2985_6 */
              messagePending = Xcp_TlQueryMessagePending((uint8)(XCP_TRANSPORT_LAYER_TCPIP + i)); /* PRQA S 2986 */ /* MD_TCPIPXCP_2985_6 */
            }

            if (TcpIpXcp_ConcatPos[i] > 0u)
            {
              /* #50 If the Eth PDU is full or there are no additional XCP frames available, we prepare the PDU information for transmission. */
              PduInfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, TCPIPXCP_APPL_VAR)) &TcpIpXcp_TxFrameCache[i].fc[0];
              PduInfo.SduLength = (PduLengthType)TcpIpXcp_ConcatPos[i];
# if (TCPIPXCP_BURST_MODE == STD_ON)
              TcpIpXcp_ConfTimeoutTimer[i] = 0;
# else
              TcpIpXcp_ConfTimeoutTimer[i] = (TcpIpXcp_TimeoutTimerType)TCPIPXCP_CONF_TIMEOUT;
# endif
              TcpIpXcp_ConcatPos[i] = 0u;
              lResult = SoAd_IfTransmit(TcpIpXcp_GetSoAdTxPduId(i), &PduInfo);
              if (lResult == (Std_ReturnType)E_OK)
              {
                /* #60 The message was sent successfully, increment burstcounter and if last packet confirm it. */
# if (TCPIPXCP_BURST_MODE == STD_ON)
                burstCounter++;
                if (messagePending == FALSE)
                {
                  (void)Xcp_SendCallBack((uint8)(XCP_TRANSPORT_LAYER_TCPIP + i)); /* PRQA S 2986 */ /* MD_TCPIPXCP_2985_6 */
                }
# endif
              }
              else
              {
                /* #70 In case of an error and the XCP Packet cannot be transmitted: set the message pending again for retransmission. */
                TcpIpXcp_ConfTimeoutTimer[i] = (TcpIpXcp_TimeoutTimerType)0u;
                TcpIpXcp_SendWithoutQueueState[i] = (uint8)TCPIPXCP_MSG_PENDING;
                TcpIpXcp_QueuedPduInfo[i] = PduInfo;
              }
            }
# if (TCPIPXCP_BURST_MODE == STD_ON)
            /* #80 In burst mode we repeat the above while there are packets available, SoAd_IfTransmit accepts requests and the burstcounter did not expire. */
          } while ((lResult == E_OK) && (burstCounter < TCPIPXCP_BURST_MODE_SIZE));
# endif
        }
#endif
      }

      /* #90 As last step we handle the TxConfirmation timeout timer to reset the confirmation if it failed. */
      TcpIpXcp_EnterCritical();
      if( TcpIpXcp_ConfTimeoutTimer[i] > 0u)
      {
        TcpIpXcp_ConfTimeoutTimer[i] = TcpIpXcp_ConfTimeoutTimer[i] - 1u;
        TcpIpXcp_LeaveCritical();
        if( 0u == TcpIpXcp_ConfTimeoutTimer[i] )
        {
          /* Timeout happened, release PDU */
          (void)Xcp_SendCallBack((uint8)(XCP_TRANSPORT_LAYER_TCPIP + i)); /* PRQA S 2986 */ /* MD_TCPIPXCP_2985_6 */
        }
      }
      else
      {
        TcpIpXcp_LeaveCritical();
      }

      /* Trigger pending DTOs */
      Xcp_TlMainFunction((uint8)(XCP_TRANSPORT_LAYER_TCPIP + i)); /* PRQA S 2986 */ /* MD_TCPIPXCP_2985_6 */
    }
  }
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  else
  {
    TcpIpXcp_ControlDeniedCount++;
  }
#endif
}

/***********************************************************************************************************************
 *  TcpIpXcp_InitMemory
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIPXCP_CODE) TcpIpXcp_InitMemory( void )
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the following variables with the corresponding values. */
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  TcpIpXcp_ControlState = (uint8)kXcponTcpIp_Control_Enable;
  TcpIpXcp_ControlDeniedCount = 0u;
#endif

#if ( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
  TcpIpXcp_InitializationState = TCPIPXCP_UNINIT;
#endif
}

/***********************************************************************************************************************
 *  TcpIpXcp_Init
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIPXCP_CODE) TcpIpXcp_Init( P2CONST(TcpIpXcp_ConfigType, AUTOMATIC, TCPIPXCP_PBCFG) ConfigPtr )
{
  uint8_least i;

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  /* #10 Check whether XCP functionality shall be enabled. */
  if ( TcpIpXcp_ControlState == kXcponTcpIp_Control_Enable )
#endif
  {

#if ( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
    TcpIpXcp_InitializationState = TCPIPXCP_UNINIT;
#endif

#if ( TCPIPXCP_CONFIG_VARIANT == 3u )
    TcpIpXcp_Configuration = ConfigPtr;
#else
    XCP_DUMMY_STATEMENT (ConfigPtr); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif

    /* #20 Initialize all XCP variables to zero. */
#if ( XCP_NUMBER_OF_CHANNELS <= 1u )
    TcpIpXcp_RxPduId = TcpIpXcp_GetRxPduId(0);
#endif
    for( i = 0u; i < TCPIPXCP_NUMBER_OF_CHANNELS; i++ )
    {
#if ( TCPIPXCP_ENABLE_PDUMODE == STD_ON )
      TcpIpXcp_PduState[i] = TCPIPXCP_SET_OFFLINE;
#endif
      TcpIpXcp_ConfTimeoutTimer[i] = 0u;
      TcpIpXcp_SequenceCounter[i] = 0u;
      TcpIpXcp_SendWithoutQueueState[i] = (uint8)TCPIPXCP_MSG_IDLE;
      TcpIpXcp_ConcatPos[i] = 0u;
    }

#if ( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
    TcpIpXcp_InitializationState = TCPIPXCP_INIT;
#endif
  }
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  else
  {
    TcpIpXcp_ControlDeniedCount++;
  }
#endif
}

#if ( TCPIPXCP_VERSION_INFO_API == STD_ON )
/***********************************************************************************************************************
 *  TcpIpXcp_GetVersionInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIPXCP_CODE) TcpIpXcp_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, TCPIPXCP_APPL_DATA) versioninfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = TCPIPXCP_E_NO_ERROR;

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  /* #10 Check whether XCP functionality shall be enabled. */
  if ( TcpIpXcp_ControlState == kXcponTcpIp_Control_Enable )
#endif
  {
    /* ----- Development Error Checks ------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
    /* #20 Perform parameter plausibility checks and report error in failure case. */
    if(versioninfo == NULL_PTR)
    {
      errorId = TCPIPXCP_E_PARAM_POINTER;
    }
    else
#endif
    {
      /* ----- Implementation ------------------------------------- */
      /* #30 Copy version information. */
      versioninfo->vendorID         = TCPIPXCP_VENDOR_ID;
      versioninfo->moduleID         = TCPIPXCP_MODULE_ID;
      versioninfo->sw_major_version = (uint8)TCPIPXCP_SW_MAJOR_VERSION;
      versioninfo->sw_minor_version = (uint8)TCPIPXCP_SW_MINOR_VERSION;
      versioninfo->sw_patch_version = (uint8)TCPIPXCP_SW_PATCH_VERSION;
    }
    /* ----- Development Error Report --------------------------------------- */
# if( TCPIPXCP_DEV_ERROR_REPORT == STD_ON )
    if( errorId != TCPIPXCP_E_NO_ERROR )
    {
      (void)Det_ReportError( TCPIPXCP_MODULE_ID, 0u, TCPIPXCP_GETVERSIONINFO_SERVICE_ID, errorId );
    }
# else
    XCP_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif
  }
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  else
  {
    TcpIpXcp_ControlDeniedCount++;
  }
#endif
}
#endif


#if ( TCPIPXCP_ENABLE_PDUMODE == STD_ON )
/***********************************************************************************************************************
 *  TcpIpXcp_SetPduMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIPXCP_CODE) TcpIpXcp_SetPduMode( NetworkHandleType XcpNwH, TcpIpXcp_PduSetModeType PduMode )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = TCPIPXCP_E_NO_ERROR;

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  /* #10 Check whether XCP functionality shall be enabled. */
  if ( TcpIpXcp_ControlState == kXcponTcpIp_Control_Enable )
#endif
  {
    /* ----- Development Error Checks ------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
    /* #20 Perform parameter plausibility checks and report error in failure case. */
    if(TcpIpXcp_InitializationState == TCPIPXCP_UNINIT)
    {
      errorId = TCPIPXCP_E_NOT_INITIALIZED;
    }
    else
#endif
    {
      /* ----- Implementation ------------------------------------- */
      /* #30 Set the requested PDU mode. */
      TcpIpXcp_PduState[XcpNwH] = PduMode;
    }
    /* ----- Development Error Report --------------------------------------- */
# if( TCPIPXCP_DEV_ERROR_REPORT == STD_ON )
    if( errorId != TCPIPXCP_E_NO_ERROR )
    {
      (void)Det_ReportError( TCPIPXCP_MODULE_ID, 0u, TCPIPXCP_SETPDUMODE_SERVICE_ID, errorId );
    }
# else
    XCP_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif
  }
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  else
  {
    TcpIpXcp_ControlDeniedCount++;
  }
#endif
}
#endif


#if defined ( XCP_ENABLE_DAQ_RESUME )
/***********************************************************************************************************************
 *  TcpIpXcp_DaqResumeGet
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIPXCP_CODE) TcpIpXcp_DaqResumeGet( CONSTP2VAR(SoAd_SockAddrInet6Type, AUTOMATIC, TCPIPXCP_APPL_DATA) resumeData )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least i;
  uint8 errorId = TCPIPXCP_E_NO_ERROR;

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  /* #10 Check whether XCP functionality shall be enabled. */
  if ( TcpIpXcp_ControlState == kXcponTcpIp_Control_Enable )
#endif
  {
    /* ----- Development Error Checks ------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
    /* #20 Perform parameter plausibility checks and report error in failure case. */
    if(TcpIpXcp_InitializationState == TCPIPXCP_UNINIT)
    {
      errorId = TCPIPXCP_E_NOT_INITIALIZED;
    }
    else if (resumeData == NULL_PTR)
    {
      errorId = TCPIPXCP_E_PARAM_POINTER;
    }
    else
#endif
    {
      /* ----- Implementation ------------------------------------- */
      /* #30 Read the SoAd connections remote address for all configured channels. */
      for(i=0; i<TCPIPXCP_NUMBER_OF_CHANNELS; i++)
      {
        (void)SoAd_GetRemoteAddr(TcpIpXcp_GetSoConId(i), (CONSTP2VAR(SoAd_SockAddrType, AUTOMATIC, TCPIPXCP_APPL_DATA))&(resumeData[i]));
      }
    }
    /* ----- Development Error Report --------------------------------------- */
# if( TCPIPXCP_DEV_ERROR_REPORT == STD_ON )
    if( errorId != TCPIPXCP_E_NO_ERROR )
    {
      (void)Det_ReportError( TCPIPXCP_MODULE_ID, 0u, TCPIPXCP_DAQRESUMEGET_SERVICE_ID, errorId );
    }
# else
    XCP_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif
  }
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  else
  {
    TcpIpXcp_ControlDeniedCount++;
  }
#endif
}


/***********************************************************************************************************************
 *  TcpIpXcp_DaqResumeStore
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIPXCP_CODE) TcpIpXcp_DaqResumeStore( CONSTP2CONST(SoAd_SockAddrInet6Type, AUTOMATIC, TCPIPXCP_APPL_DATA) resumeData )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least i;
  uint8 errorId = TCPIPXCP_E_NO_ERROR;

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  /* #10 Check whether XCP functionality shall be enabled. */
  if ( TcpIpXcp_ControlState == kXcponTcpIp_Control_Enable )
#endif
  {
    /* ----- Development Error Checks ------------------------------------- */
#if( TCPIPXCP_DEV_ERROR_DETECT == STD_ON )
    /* #20 Perform parameter plausibility checks and report error in failure case. */
    if(TcpIpXcp_InitializationState == TCPIPXCP_UNINIT)
    {
      errorId = TCPIPXCP_E_NOT_INITIALIZED;
    }
    else if (resumeData == NULL_PTR)
    {
      errorId = TCPIPXCP_E_PARAM_POINTER;
    }
    else
#endif
    {
      /* ----- Implementation ------------------------------------- */
      /* #30 Set the SoAd connections remote address for all configured channels. */
      for(i=0; i<TCPIPXCP_NUMBER_OF_CHANNELS; i++)
      {
        (void)SoAd_SetRemoteAddr(TcpIpXcp_GetSoConId(i), (CONSTP2CONST(SoAd_SockAddrType, AUTOMATIC, TCPIPXCP_APPL_DATA))&(resumeData[i]));
      }
    }
    /* ----- Development Error Report --------------------------------------- */
# if( TCPIPXCP_DEV_ERROR_REPORT == STD_ON )
    if( errorId != TCPIPXCP_E_NO_ERROR )
    {
      (void)Det_ReportError( TCPIPXCP_MODULE_ID, 0u, TCPIPXCP_DAQRESUMESTORE_SERVICE_ID, errorId );
    }
# else
    XCP_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif
  }
#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
  else
  {
    TcpIpXcp_ControlDeniedCount++;
  }
#endif
}
#endif /* defined ( XCP_ENABLE_DAQ_RESUME ) */


#define TCPIPXCP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* module specific MISRA deviations:
  MD_TCPIPXCP_0310: Rule 11.3
      Reason:     pointer cast has no side effects if underlying layer aligns the buffer accordingly.
      Risk:       If this option is enabled and the buffer is not aligned a trap will occur.
      Prevention: Optional feature

  MD_TCPIPXCP_1338: Rule 17.8
      Reason:     Parameter is modified to keep function simple and readable.
      Risk:       None.
      Prevention: Not required.

  MD_TCPIPXCP_1514: Rule 8.7
      Reason:     Under certain configuration variants the variable is only used in one function.
      Risk:       None.
      Prevention: Not required.

  MD_TCPIPXCP_2889: Rule 15.5
      Reason:     API pattern not applied in this component yet.
      Risk:       Code understandability and maintainability reduced.
      Prevention: Covered by code review.

  MD_TCPIPXCP_2985_6: Rule 2.2
      Reason:     generated code might have 0 as value which leads to this warning.
      Risk:       No Risk.
      Prevention: Not required.

  MD_TCPIPXCP_3218_FileScopeStatic: Rule 8.9
      Reason:     To provide AUTOSAR memory mapping a global variable is required.
      Risk:       No Risk.
      Prevention: Not required.

  MD_TCPIPXCP_3305: Rule 11.3
      Reason:     A uint8 pointer is cast to a uint32 pointer.
      Risk:       Misaligned access might happen.
      Prevention: It is guaranteed in code that access is always 16bit aligned. See XCP_START_SEC_VAR_NOCACHE_NOINIT_32BIT.
                  Covered by review.

  MD_TCPIPXCP_3408: Rule 8.4
      Reason:     The variable is not defined as static to be accessible for measurement. No prototype is required for this.
      Risk:       There is no risk as this variable is not accessed externally.
      Prevention: Not required.

  MD_TCPIPXCP_3493_4: Rule 14.3
      Reason:     A pre-compile macros is used to determine parameters based on configuration.
      Risk:       There is no risk as this is a valid operation and performed by pre-processor.
      Prevention: Not required.

  MD_TCPIPXCP_3494: Rule 14.3
      Reason:     A variable is modified in another function.
      Risk:       There is no risk as the variable is set to volatile.
      Prevention: Not required.

*/

/* COV_JUSTIFICATION_BEGIN

\ID COV_TCPIPXCP_MSR_COMPATIBILITY
\ACCEPT TX
\ACCEPT XF
\REASON [COV_MSR_COMPATIBILITY]

\ID COV_TCPIPXCP_UNSUPPORTED_FEATURE
\ACCEPT TX
\ACCEPT XF
\REASON [COV_MSR_UNSUPPORTED] The following features are not supported by TcpIpXcp: TCPIPXCP_MODE_CHG_API (only STD_ON), TCPIPXCP_PROTOCOL_FORMAT (only UDP)

COV_JUSTIFICATION_END */


/**********************************************************************************************************************
 *  END OF FILE: TcpIpXcp.C
 *********************************************************************************************************************/
