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
 *        \file   Dlt.c
 *        \brief  Dlt source file
 *
 *      \details  Source file of the AUTOSAR Diagnostic Log and Trace, according to:
 *                AUTOSAR Diagnostic Log and Trace, AUTOSAR Release 4.0
 *
 *********************************************************************************************************************/

 /*********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 * 
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define DLT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Dlt.h"
#include "Rte_Dlt.h"


#if (DLT_DEV_ERROR_REPORT == STD_ON)
# include "Det.h" /* Include Development Error Tracer */
#endif

#if defined (DLT_USE_COMLAYER_XCP) && (DLT_USE_COMLAYER_XCP == STD_ON) /* COV_DLT_FILTER_ASR_XCP */
# include "Xcp.h"

# if (DLT_USE_VERBOSE_MODE == STD_ON)
#  include "vstdlib.h"            /* for VStdMemCpy */
# endif
#endif

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */
/*lint -e522 */ /* Suppress ID522 because all functions without side-effect have to have no side-effect */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
/* Dlt500 */
#if((DLT_SW_MAJOR_VERSION != (0x05u)) || (DLT_SW_MINOR_VERSION != (0x00u)) || (DLT_SW_PATCH_VERSION != (0x00u)))
# error "Vendor specific version numbers of Dlt.c and Dlt.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#define DLT_SHIFT_5BIT (5u)
#define DLT_SHIFT_8BIT (8u)
#define DLT_SHIFT_16BIT (16u)
#define DLT_SHIFT_24BIT (24u)

#define DLT_DET_MESSAGE_ID (0x00000002u)
#define DLT_DET_INVALID_XCP_DET_ID (0x01000000u)

#define DLT_TYPE_LONG_LENGTH (4u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 1533 EOF */ /* MD_Dlt_1533 */


/* PRQA S 3453 FUNCTIONLIKEMACRO_C */ /*  MD_MSR_FctLikeMacro */

#define DLT_BEGIN_CRITICAL_SECTION_APIS() SchM_Enter_Dlt_DLT_EXCLUSIVE_AREA_APIS()
#define DLT_END_CRITICAL_SECTION_APIS()   SchM_Exit_Dlt_DLT_EXCLUSIVE_AREA_APIS()
#define DLT_BEGIN_CRITICAL_SECTION_TX()   SchM_Enter_Dlt_DLT_EXCLUSIVE_AREA_TX()
#define DLT_END_CRITICAL_SECTION_TX()     SchM_Exit_Dlt_DLT_EXCLUSIVE_AREA_TX()
#define DLT_BEGIN_CRITICAL_SECTION_RX()   SchM_Enter_Dlt_DLT_EXCLUSIVE_AREA_RX()
#define DLT_END_CRITICAL_SECTION_RX()     SchM_Exit_Dlt_DLT_EXCLUSIVE_AREA_RX()

#if (DLT_USE_DEFAULT_API == STD_ON)
# define DltCheckLogChannelName()         (LogChannelName != NULL_PTR)
#else
# define DltCheckLogChannelName()         (TRUE == TRUE)
#endif

/* PRQA L:FUNCTIONLIKEMACRO_C */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/* ====================================================================================================================
 * COMLAYER AUTOSAR
 * ====================================================================================================================
 */

/* ====================================================================================================================
 * COMLAYER XCP
 * ====================================================================================================================
 */

# define DLT_START_SEC_VAR_CLEARED_UNSPECIFIED
# include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

DLT_LOCAL VAR(Dlt_GlobalStateType, DLT_VAR_CLEARED) Dlt_GlobalState = DLT_GLOBAL_STATE_UNINIT;
DLT_LOCAL VAR(Dlt_GlobalStateType, DLT_VAR_CLEARED) Dlt_GlobalStateNew = DLT_GLOBAL_STATE_UNINIT;

DLT_LOCAL VAR(boolean, DLT_VAR_CLEARED)             Dlt_EnterDetTransmitContext = FALSE;

# define DLT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define DLT_START_SEC_VAR_NO_INIT_32
# include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Variable is loaded with the last DET error code */
VAR(uint32, DLT_VAR_NO_INIT)                          Dlt_DetErrorCode;

# define DLT_STOP_SEC_VAR_NO_INIT_32
# include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define DLT_START_SEC_VAR_NO_INIT_UNSPECIFIED
# include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Variable is loaded with DEM event id and status code. */
VAR(Dlt_DemEventStatusType, DLT_VAR_NO_INIT)          Dlt_DemEventStatus; /*lint -e830 */ /* Suppress ID830 */ /*lint -e552 */ /* Suppress ID552 */

/* Variable is loaded with message ID of non-verbose message . */
VAR(Dlt_MessageIDType, DLT_VAR_NO_INIT)               Dlt_NonVerboseMessageId;

# if (DLT_USE_VERBOSE_MODE == STD_ON)
/* Buffer is loaded with payload of verbose message. */
VAR(uint8, DLT_VAR_NO_INIT)                           Dlt_VerboseMessageData[DLT_MAX_MESSAGE_LENGTH];
# endif /* (DLT_USE_VERBOSE_MODE == STD_ON) */

# define DLT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
# include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
#define DLT_START_SEC_CONST_8
#include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


CONST(uint8, DLT_CONST) Dlt_ModuleTable[256] = 
{
/*  0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F           */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x0Au, 0x0Bu, 0x0Cu, 0x0Du, 0x00u, 0x00u,  /* 0x */ /* 0x0A = ECUM, 0x0B = FIM, 0x0C = COMM, 0x0D = WDGM */
  0x00u, 0x00u, 0x00u, 0x00u, 0x14u, 0x15u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Au, 0x00u, 0x00u, 0x1Du, 0x00u, 0x1Fu,  /* 1x */ /* 0x14 = NVM, 0x15 = FEE, 0x1A = XCP, 0x1D = NM, 0x1F = CANNM */
  0x20u, 0x00u, 0x00u, 0x23u, 0x24u, 0x25u, 0x00u, 0x00u, 0x28u, 0x00u, 0x2Au, 0x2Bu, 0x00u, 0x00u, 0x00u, 0x00u,  /* 2x */ /* 0x20 = FRNM, 0x23 = CANTP, 0x24 = FRTP, 0x25 = J1939TP, 0x28 = EA, 0x2A = BSWM, 0x2B = WDGIF */
  0x00u, 0x00u, 0x32u, 0x33u, 0x34u, 0x35u, 0x36u, 0x00u, 0x38u, 0x00u, 0x00u, 0x00u, 0x3Cu, 0x3Du, 0x3Eu, 0x00u,  /* 3x */ /* 0x32 = COM, 0x33 = PDUR, 0x34 = IPDUM, 0x35 = DCM, 0x36 = DEM, 0x38 depends on InstanceId (SOAD = 0x00, TCPIP = 0x01, IPV4 = 0x02, IPV6 = 0x04), 0x3C = CANIF, 0x3D = FRIF, 0x3E = LINIF */
  0x00u, 0x41u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x49u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* 4x */ /* 0x41 = ETHIF, 0x49 = ETHTRCV */
  0x50u, 0x51u, 0x52u, 0x53u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x5Cu, 0x00u, 0x00u, 0x00u,  /* 5x */ /* 0x50 = CAN, 0x51 = FR, 0x52 = LIN, 0x53 = SPI, 0x5C = FLS */
  0x00u, 0x00u, 0x00u, 0x00u, 0x64u, 0x65u, 0x66u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* 6x */ /* 0x64 = GPT, 0x65 = MCU, 0x66 = WDG */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x78u, 0x79u, 0x7Au, 0x7Bu, 0x00u, 0x00u, 0x00u, 0x00u,  /* 7x */ /* 0x78 = DIO, 0x79 = PWM, 0x7A = ICU, 0x7B = ADC */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x8Cu, 0x8Du, 0x8Eu, 0x8Fu,  /* 8x */ /* 0x8C = CANSM, 0x8D = LINSM, 0x8E = FRSM , 0x8F = ETHSM */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* 9x */ 
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xAEu, 0x00u,  /* Ax */ /* 0x(1)AE = ETH */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* Bx */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* Cx */
  0x00u, 0x00u, 0x00u, 0xD3u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* Dx */ /* 0xD3 = FRXCP */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* Ex */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xFFu   /* Fx */ /* 0xFF : depends on InstanceId - 0x00: CANXCP, 0x65: RCS, 0x66: HTTP, 0x67: TLS, 0x68: Crypto, 0x69: DNS, 0x6A: JSON, 0x6B..0x6D: EXI, 0x6E: IPBase, 0x6F: SCC */
};

#define DLT_STOP_SEC_CONST_8
#include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define DLT_START_SEC_CODE
#include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ####################################################################################################################
 *   HH      HH  EEEEEEEEEE  LL          PPPPPPPP    EEEEEEEEEE  RRRRRRRR
 *   HH      HH  EE          LL          PP      PP  EE          RR      RR
 *   HH      HH  EE          LL          PP      PP  EE          RR      RR
 *   HHHHHHHHHH  EEEEEEEE    LL          PPPPPPPP    EEEEEEEE    RRRRRRRR
 *   HH      HH  EE          LL          PP          EE          RR    RR
 *   HH      HH  EE          LL          PP          EE          RR      RR
 *   HH      HH  EEEEEEEEEE  LLLLLLLLLL  PP          EEEEEEEEEE  RR      RR
 * ####################################################################################################################
 */
#if ((DLT_USE_COMLAYER_XCP == STD_ON) || (DLT_RX_DATA_PATH_SUPPORT == STD_ON)) /* COV_DLT_FILTER_ASR_XCP */
/**********************************************************************************************************************
  Dlt_Hlp_CopyArrayToLongLittleEndian_AndMoveIndex()
**********************************************************************************************************************/
/*! \brief       Copies data from array to variable.
 *  \details     Copies 4 byte from source array to variable with least significant byte first.
 *  \param[in]   SourceData            Data source.
 *  \param[out]  DestData              Pointer to data destination.
 *  \param[out]  StartIndex            Pointer to start index of source array where the data is copied from.
 *  \pre         The source array must have at least the size of 4.
 *  \pre         Only reentrant if destination and source pointer content are not affected by second call while 
 *               interrupted.
 *  \context     TASK|ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      This function is only available if (DLT_USE_COMLAYER_XCP == STD_ON) || DLT_RX_DATA_PATH_SUPPORT == STD_ON).
**********************************************************************************************************************/
DLT_LOCAL_INLINE FUNC(void, DLT_CODE) Dlt_Hlp_CopyArrayToLongLittleEndian_AndMoveIndex(
  P2CONST(uint8, AUTOMATIC, DLT_APPL_VAR) SourceData,
  P2VAR(uint32, AUTOMATIC, DLT_APPL_VAR) DestData,
  P2VAR(uint16, AUTOMATIC, DLT_APPL_VAR) StartIndex);
#endif


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/* ####################################################################################################################
 *   HH      HH  EEEEEEEEEE  LL          PPPPPPPP    EEEEEEEEEE  RRRRRRRR
 *   HH      HH  EE          LL          PP      PP  EE          RR      RR
 *   HH      HH  EE          LL          PP      PP  EE          RR      RR
 *   HHHHHHHHHH  EEEEEEEE    LL          PPPPPPPP    EEEEEEEE    RRRRRRRR
 *   HH      HH  EE          LL          PP          EE          RR    RR
 *   HH      HH  EE          LL          PP          EE          RR      RR
 *   HH      HH  EEEEEEEEEE  LLLLLLLLLL  PP          EEEEEEEEEE  RR      RR
 * ####################################################################################################################
 */
#if ((DLT_USE_COMLAYER_XCP == STD_ON) || (DLT_RX_DATA_PATH_SUPPORT == STD_ON)) /* COV_DLT_FILTER_ASR_XCP */
/**********************************************************************************************************************
 * Dlt_Hlp_CopyArrayToLongLittleEndian_AndMoveIndex
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
DLT_LOCAL_INLINE FUNC(void, DLT_CODE) Dlt_Hlp_CopyArrayToLongLittleEndian_AndMoveIndex(
  P2CONST(uint8, AUTOMATIC, DLT_APPL_VAR) SourceData,
  P2VAR(uint32, AUTOMATIC, DLT_APPL_VAR) DestData,
  P2VAR(uint16, AUTOMATIC, DLT_APPL_VAR) StartIndex)
{
  /* ----- Implementation ------------------------------------------------- */
  /* #10 Copy source data from little endian array to destination 32bit variable. */
  (*DestData)  = (uint32)((uint32)(SourceData[StartIndex[0] + 3u]) << DLT_SHIFT_24BIT);
  (*DestData) |= (uint32)((uint32)(SourceData[StartIndex[0] + 2u]) << DLT_SHIFT_16BIT);
  (*DestData) |= (uint32)((uint32)(SourceData[StartIndex[0] + 1u]) << DLT_SHIFT_8BIT);
  (*DestData) |= (uint32)((uint32)(SourceData[StartIndex[0]]));

  /* #20 Set array index to new position. */
  *StartIndex = StartIndex[0] + DLT_TYPE_LONG_LENGTH;
} /* Dlt_Hlp_CopyArrayToLongLittleEndian_AndMoveIndex */
#endif


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/


/**********************************************************************************************************************
 * Dlt_InitMemory
 *********************************************************************************************************************/
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
 */
FUNC(void, DLT_CODE) Dlt_InitMemory(void)
{
  /* #10 If com layer is AUTOSAR, pre-initialize global variables. */

  /* #60 Set the global state to DLT_GLOBAL_STATE_UNINIT, now the logging of DEM and DET messages is active. */
  Dlt_GlobalState = DLT_GLOBAL_STATE_UNINIT;
  Dlt_GlobalStateNew = DLT_GLOBAL_STATE_UNINIT;

#if (DLT_USE_COMLAYER_XCP == STD_ON) /* COV_DLT_FILTER_ASR_XCP */
  Dlt_EnterDetTransmitContext = FALSE;
#endif
} /* Dlt_InitMemory */

/**********************************************************************************************************************
 * Dlt_Init
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DLT_CODE) Dlt_Init(P2CONST(Dlt_ConfigType, AUTOMATIC, DLT_PBCFG) ConfigPtr)
{

  /* ----- Implementation ------------------------------------------------- */
  DLT_DUMMY_STATEMENT(ConfigPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */

  /* #10 Initialize all global variables which have to be available with DLT module initialization. */

#if (DLT_USE_COMLAYER_XCP == STD_ON) /* COV_DLT_FILTER_ASR_XCP */
  Dlt_DetErrorCode = 0u;
  Dlt_DemEventStatus = 0u;
  Dlt_NonVerboseMessageId = 0u;
#endif /* (DLT_USE_COMLAYER_XCP == STD_ON) */

  /* #40 Set the global state to DLT_GLOBAL_STATE_OFFLINE, now the logging as well as sending is disabled. */
  Dlt_GlobalState = DLT_GLOBAL_STATE_OFFLINE;
  Dlt_GlobalStateNew = DLT_GLOBAL_STATE_OFFLINE;
  /*lint -e{438} */ /* PC_Dlt_438 */
} /* Dlt_Init */

#if (DLT_VERSION_INFO_API == STD_ON)

/**********************************************************************************************************************
 * Dlt_GetVersionInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, DLT_CODE) Dlt_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, DLT_APPL_VAR) VersionInfo)
{ /* [Dlt271] */
  /* ----- Local Variables ------------------------------------------------ */
  uint8 errorId = DLT_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
# if (DLT_DEV_ERROR_DETECT == STD_ON)
  if (VersionInfo == NULL_PTR)
  {
    errorId = DLT_E_PARAM_POINTER;
  }
  else
# endif
  /* ----- Implementation ------------------------------------------------- */
  {
    VersionInfo->vendorID         = DLT_VENDOR_ID;
    VersionInfo->moduleID         = DLT_MODULE_ID;
    VersionInfo->sw_major_version = DLT_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = DLT_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = DLT_SW_PATCH_VERSION;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (DLT_DEV_ERROR_REPORT == STD_ON)
  if (errorId != DLT_E_NO_ERROR)
  {
    (void)Det_ReportError(DLT_MODULE_ID, 0, DLT_API_ID_GETVERSIONINFO, errorId);
  }
# else
  DLT_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */ /* PC_Dlt_438 */
# endif

  /*lint -e{550} */ /* PC_Dlt_550 */
} /* Dlt_GetVersionInfo */
#endif /* (DLT_VERSION_INFO_API == STD_ON) */

/**********************************************************************************************************************
 * Dlt_DetForwardErrorTrace
 *********************************************************************************************************************/
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
 */
FUNC(void, DLT_CODE) Dlt_DetForwardErrorTrace(
  uint16 ModuleId,
  uint8 InstanceId,
  uint8 ApiId,
  uint8 ErrorId)
{ 

  /* ----- Implementation ------------------------------------------------- */
  /* #10 Forwarding of DET messages is only allowed before initialization and after DLT activation. */
  if ((Dlt_GlobalState == DLT_GLOBAL_STATE_ONLINE) ||
      (Dlt_GlobalState == DLT_GLOBAL_STATE_UNINIT))
  {
    /* Dlt430, Dlt432 */
    /* #20 Prevent recursion in case DLT throws a DET error itself. */
    if (ModuleId != DLT_MODULE_ID)
    {
      /* #30 Enter Dlt_DLT_EXCLUSIVE_AREA_APIS. */
      DLT_BEGIN_CRITICAL_SECTION_APIS(); 

      /* #40 If use comlayer xcp enabled, build log message for DET error reporting. */
#if (DLT_USE_COMLAYER_XCP == STD_ON) /* COV_DLT_FILTER_ASR_XCP */
      if ((uint8)ModuleId == Dlt_ModuleTable[(uint8)ModuleId])
      {  
        Dlt_DetErrorCode = (uint8)InstanceId; /* ESCAN00070451: necessary for components with same module ids */
        Dlt_DetErrorCode <<= DLT_SHIFT_8BIT;
        Dlt_DetErrorCode |= (uint8)ModuleId; /* ESCAN00074824 */
        Dlt_DetErrorCode <<= DLT_SHIFT_8BIT;
        Dlt_DetErrorCode |= (uint8)ApiId;
        Dlt_DetErrorCode <<= DLT_SHIFT_8BIT;
        Dlt_DetErrorCode |= (uint8)ErrorId;
      }
      else
      {
        /* [Dlt439]: detected invalid module ID are not reported to DET to prevent a loop. Instead an invalid module ID is reported to the XCP master via Dlt_DetErrorCode  */
        Dlt_DetErrorCode = (uint32)(DLT_DET_INVALID_XCP_DET_ID | ModuleId);
      }

      /* #50 Protect the transmission context against recursion. */
      if (Dlt_EnterDetTransmitContext == FALSE) /* PRQA S 2996 */ /* MD_Dlt_AlwaysFalse */
      {
        Dlt_EnterDetTransmitContext = TRUE;
        /* 60 Send DLT-DET-message via XCP. */
        (void)Xcp_Event((uint16)DLT_DET_EVENT);
        Dlt_EnterDetTransmitContext = FALSE;
      }
#endif /* (DLT_USE_COMLAYER_XCP == STD_ON) */

      /* #100 Leave Dlt_DLT_EXCLUSIVE_AREA_APIS. */
      DLT_END_CRITICAL_SECTION_APIS(); 
    }
  }
} /* Dlt_DetForwardErrorTrace */

/**********************************************************************************************************************
 * Dlt_DemTriggerOnEventStatus
 *********************************************************************************************************************/
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
 */
FUNC(void, DLT_CODE) Dlt_DemTriggerOnEventStatus(
  Dem_EventIdType EventId,
  Dem_EventStatusExtendedType EventStatusOld,
  Dem_EventStatusExtendedType EventStatusNew)
{ /* [Dlt474] */
  /* ----- Local Variables ------------------------------------------------ */
  uint8 errorId = DLT_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (DLT_DEV_ERROR_DETECT == STD_ON)
  /* #10 If required, check that event ID is in valid range. */
  /* DEM Event ID = 0 indicates no event or failure. Highest valid event ID is DLT_NUM_DEM_EVENTS. */
  if ((EventId == 0u) || (EventId > DLT_NUM_DEM_EVENTS))
  {
    errorId = DLT_E_PARAM;
  }
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  /* #20 If the initial check is passed or not required: */
  {
    /* #30 DEM events are only allowed to be send before initialization and after DLT activation. */
    if ((Dlt_GlobalState == DLT_GLOBAL_STATE_ONLINE) ||
        (Dlt_GlobalState == DLT_GLOBAL_STATE_UNINIT))
    {
#if (DLT_DEM_EVENT_FILTERING_ENABLED == STD_ON)
      boolean sendDemMsg;
#endif
      /* [Dlt475]: the DEM already ensures that EventStatusOld and EventStatusNew are not equal, because Dlt_DemTriggerOnEventStatus is only called if they differ. Hence the log message can always be generated. */
      /* #40 Enter Dlt_DLT_EXCLUSIVE_AREA_APIS. */
      DLT_BEGIN_CRITICAL_SECTION_APIS(); 

      /* #50 If DEM event filtering is enabled, call callback function to add individual message filter. */
#if (DLT_DEM_EVENT_FILTERING_ENABLED == STD_ON)
      /* UREQ00041311: The implementation shall be able to filter for the following properties: DEM Event ID and DEM Event Status Bits */
      sendDemMsg = Appl_DltDemEventFilterCbk(EventId, EventStatusOld, EventStatusNew);

      if (sendDemMsg == TRUE) /* PRQA S 2995 */ /* MD_Dlt_AlwaysTrue */
#else
      DLT_DUMMY_STATEMENT(EventStatusOld); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */ /* PC_Dlt_438 */
#endif
      {
        /* #60 If comlayer XCP is active, send DEM event via XCP. */
#if (DLT_USE_COMLAYER_XCP == STD_ON) /* COV_DLT_FILTER_ASR_XCP */
        Dlt_DemEventStatus = (uint16)EventId;
        Dlt_DemEventStatus <<= DLT_SHIFT_16BIT;
        Dlt_DemEventStatus |= (uint8)EventStatusNew;

        /* UREQ00040542: Report DEM Event change */
        (void)Xcp_Event((uint16)DLT_DEM_EVENT);
#endif /* (DLT_USE_COMLAYER_XCP == STD_ON) */
      }

      /* #100 Leave Dlt_DLT_EXCLUSIVE_AREA_APIS. */
      DLT_END_CRITICAL_SECTION_APIS(); 
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (DLT_DEV_ERROR_REPORT == STD_ON)
  if (errorId != DLT_E_NO_ERROR)
  {
    (void)Det_ReportError(DLT_MODULE_ID, 0u, DLT_API_ID_DEMTRIGGERONEVENTSTATUS, errorId);
  }
#else
  DLT_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */ /* PC_Dlt_438 */
#endif

  /*lint -e{438} */ /* PC_Dlt_438 */
  /*lint -e{550} */ /* PC_Dlt_550 */  
} /* Dlt_DemTriggerOnEventStatus */

/**********************************************************************************************************************
 * Dlt_SendLogMessage
 *********************************************************************************************************************/
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
 * \spec        requires LogData != NULL_PTR;
 *              requires LogInfo != NULL_PTR;
 *              requires $lengthOf(LogData) >= LogDataLength;
 *              requires LogDataLength <= DLT_MAX_MESSAGE_LENGTH;
 * \endspec
 */
/* PRQA S 6030 2 */ /* MD_MSR_STCYC */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(Std_ReturnType, DLT_CODE) Dlt_SendLogMessage(
  Dlt_SessionIDType parg0, 
  P2CONST(Dlt_MessageLogInfoType, AUTOMATIC, DLT_APPL_VAR) LogInfo, 
  P2CONST(uint8, AUTOMATIC, DLT_APPL_VAR) LogData, 
  uint16 LogDataLength)
{ /* Dlt241 */
  /* ----- Local Variables ------------------------------------------------ */
  Dlt_ReturnType retVal = DLT_E_ERROR;
  uint8 errorId = DLT_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (DLT_DEV_ERROR_DETECT == STD_ON)
  if (Dlt_GlobalState == DLT_GLOBAL_STATE_UNINIT)
  {
    errorId = DLT_E_UNINITIALIZED;
  }
  else if (LogData == NULL_PTR)
  {
    errorId = DLT_E_PARAM_POINTER;
  }
  else if (LogDataLength >= DLT_MAX_MESSAGE_LENGTH)
  {
    errorId = DLT_E_PARAM;
  }
#endif

  /* #10 If the comlayer ASR is active: */
  /* #50 Otherwise: */
# if (DLT_DEV_ERROR_DETECT == STD_ON)
  else
# endif
  /* ----- Implementation ------------------------------------------------- */
  {
    DLT_DUMMY_STATEMENT(parg0); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

    /* #60 If global state is DLT_GLOBAL_STATE_ONLINE: */
    if (Dlt_GlobalState == DLT_GLOBAL_STATE_ONLINE)
    {
      /* SWS_Dlt_00014 */
      /* #70 If message is in verbose mode AND
       *       If implement verbose mode is enabled, build and send the log message with string payload.
       *       Otherwise, invalid request. */
      if ((LogInfo->options & DLT_VERBOSE_MSG) == DLT_VERBOSE_MSG)
      {
# if (DLT_USE_VERBOSE_MODE == STD_ON)
        /* verbose message handling */
        uint8 retVal_Xcp;
        /* #80 Enter Dlt_DLT_EXCLUSIVE_AREA_APIS. */
        DLT_BEGIN_CRITICAL_SECTION_APIS(); 

        VStdLib_MemCpy(&Dlt_VerboseMessageData[0], &LogData[sizeof(Dlt_StandardHeaderType)+sizeof(Dlt_MessageIDType)], LogDataLength); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

        /* SREQ00024774: If the string written to the data buffer is shorter than the defined data field it shall be terminated with 0. */
        Dlt_VerboseMessageData[LogDataLength] = (uint8)'\0';

        /* UREQ00040541: generate verbose log message */
        retVal_Xcp = Xcp_Event((uint16)DLT_VERBOSE_MSG_EVENT);

        if (retVal_Xcp != (XCP_EVENT_NOP))
        {
        retVal = (Dlt_ReturnType)(DLT_E_OK);
        }
        else
        {
        retVal = (Dlt_ReturnType)(DLT_E_ERROR);
        }

        /* #90 Leave Dlt_DLT_EXCLUSIVE_AREA_APIS. */
        DLT_END_CRITICAL_SECTION_APIS(); 
# else /* (DLT_USE_VERBOSE_MODE == STD_ON) */
        DLT_DUMMY_STATEMENT(LogDataLength); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */ /* PC_Dlt_438 */
        /* SWS_Dlt_00090 */
        retVal = (Dlt_ReturnType)DLT_E_ERROR;
# endif /* (DLT_USE_VERBOSE_MODE == STD_ON) */
      }
      /* #100 Otherwise, build the log message with message ID and send it via XCP. */
      else
      {
        /* non-verbose message handling */
        uint32 msgId = 0u;
        uint16 index = 4u;
        Dlt_Hlp_CopyArrayToLongLittleEndian_AndMoveIndex(&LogData[0], &msgId, &index); /* ESCAN00081868 */
        /* Dlt031: Message IDs used for Dem (0x00000001) and Det (0x00000002) are reserved and not usable for SW-Cs. */
        /* #110 If message ID in invalid range, reject send request.
         *     Otherwise, send log message via XCP. */
        if ((msgId <= DLT_DET_MESSAGE_ID) || (msgId >= DLT_NUM_NON_VERBOSE_MESSAGES))
        {
          errorId = DLT_E_PARAM;
          retVal = (Dlt_ReturnType)DLT_E_ERROR;
        }
        else
        {
          uint8 retVal_Xcp;

          /* #120 Enter Dlt_DLT_EXCLUSIVE_AREA_APIS. */
          DLT_BEGIN_CRITICAL_SECTION_APIS(); 
          
          Dlt_NonVerboseMessageId = (Dlt_MessageIDType)(msgId);

          retVal_Xcp = Xcp_Event((uint16)DLT_NON_VERBOSE_MSG_EVENT);

          if (retVal_Xcp != (XCP_EVENT_NOP))
          {
            retVal = (Dlt_ReturnType)(DLT_E_OK);
          }
          else
          {
            retVal = (Dlt_ReturnType)(DLT_E_ERROR);
          }

          /* #130 Leave Dlt_DLT_EXCLUSIVE_AREA_APIS. */
          DLT_END_CRITICAL_SECTION_APIS(); 
        }
      }
    }
  }

#if (DLT_DEV_ERROR_REPORT == STD_ON)
  /* ----- Development Error Report --------------------------------------- */
  if (errorId != DLT_E_NO_ERROR)
  {
    (void)Det_ReportError(DLT_MODULE_ID, 0u, DLT_API_ID_SENDLOGMESSAGE, errorId);
  }
#else
  DLT_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */ /* PC_Dlt_438 */
#endif

  /*lint -e{438} */ /* PC_Dlt_438 */
  return (Std_ReturnType)retVal; /*lint -e{550} */ /* PC_Dlt_550 */
} /* Dlt_SendLogMessage */


/**********************************************************************************************************************
 * Dlt_SetState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DLT_CODE) Dlt_SetState(Dlt_GlobalStateType NewState)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = DLT_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (DLT_DEV_ERROR_DETECT == STD_ON)
  if (Dlt_GlobalState == DLT_GLOBAL_STATE_UNINIT)
  {
    errorId = DLT_E_UNINITIALIZED;
  }
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #10 Enter Dlt_DLT_EXCLUSIVE_AREA_APIS. */
    DLT_BEGIN_CRITICAL_SECTION_APIS(); 

    /* #20 If Dlt_GlobalState differs from new state, change the Dlt_GlobalStateNew.
     *     Otherwise, the request is invalid.
     */
    switch(Dlt_GlobalState)
    {
      case (DLT_GLOBAL_STATE_OFFLINE):
        if (NewState == DLT_GLOBAL_STATE_ONLINE)
        {
          Dlt_GlobalStateNew = DLT_GLOBAL_STATE_ONLINE;
          retVal = E_OK;
        }
        break;

      case (DLT_GLOBAL_STATE_ONLINE):
        if (NewState == DLT_GLOBAL_STATE_OFFLINE)
        {
          Dlt_GlobalStateNew = DLT_GLOBAL_STATE_OFFLINE;
          retVal = E_OK;
        }
        break;

      default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */ /* COV_DLT_DEFAULT_BRANCH */
        break;
    }

    /* #30 Leave Dlt_DLT_EXCLUSIVE_AREA_APIS. */
    DLT_END_CRITICAL_SECTION_APIS(); 
  }

  /* ----- Development Error Report --------------------------------------- */
#if (DLT_DEV_ERROR_REPORT == STD_ON)
  if (errorId != DLT_E_NO_ERROR)
  {
    (void)Det_ReportError(DLT_MODULE_ID, 0u, DLT_API_ID_SETSTATE, errorId);
  }
#else
  DLT_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */ /* PC_Dlt_438 */
#endif

  return retVal; /*lint -e{550} */ /* PC_Dlt_550 */
} /* Dlt_SetState */

/**********************************************************************************************************************
 * Dlt_GetState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 * \spec        requires CurrentStatePtr != NULL_PTR;
 * \endspec
 */
FUNC(Std_ReturnType, DLT_CODE) Dlt_GetState(
  P2VAR(Dlt_GlobalStateType, AUTOMATIC, DLT_APPL_VAR) CurrentStatePtr)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = DLT_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (DLT_DEV_ERROR_DETECT == STD_ON)
  if (Dlt_GlobalState == DLT_GLOBAL_STATE_UNINIT)
  {
    errorId = DLT_E_UNINITIALIZED;
  }
  else
#endif  /* (DLT_DEV_ERROR_DETECT == STD_ON) */
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #10 The request of Dlt_GlobalState is only valid in state DLT_GLOBAL_STATE_OFFLINE and 
     *     DLT_GLOBAL_STATE_ONLINE.
     */
    switch(Dlt_GlobalState)
    {
      case (DLT_GLOBAL_STATE_OFFLINE):
        *CurrentStatePtr = (Dlt_GlobalStateType) DLT_GLOBAL_STATE_OFFLINE;
        retVal = E_OK;
        break;

      case (DLT_GLOBAL_STATE_ONLINE):
        *CurrentStatePtr = (Dlt_GlobalStateType) DLT_GLOBAL_STATE_ONLINE;
        retVal = E_OK;
        break;

      default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */ /* COV_DLT_DEFAULT_BRANCH */
        break;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (DLT_DEV_ERROR_REPORT == STD_ON)
  if (errorId != DLT_E_NO_ERROR)
  {
    (void)Det_ReportError(DLT_MODULE_ID, 0u, DLT_API_ID_GETSTATE, errorId);
  }
#else
  DLT_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */ /* PC_Dlt_438 */
#endif

  return retVal; /*lint -e{550} */ /* PC_Dlt_550 */
} /* Dlt_GetState */

/**********************************************************************************************************************
 * Dlt_MainFunction
 *********************************************************************************************************************/
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
 */
/* PRQA S 6030 2 */ /* MD_MSR_STCYC */
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(void, DLT_CODE) Dlt_MainFunction(void)
{

  /* #70 Update global state. */
  if (Dlt_GlobalState != Dlt_GlobalStateNew)
  {
    Dlt_GlobalState = Dlt_GlobalStateNew;
  }


  /*lint -e{550} */ /* PC_Dlt_550 */
} /* Dlt_MainFunction */

#define DLT_STOP_SEC_CODE
#include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* module specific MISRA deviations:

  MD_Dlt_NvMWriteBlock: Misra rule 1.1
     Reason:          The function 'NvM_WriteBlock' from the NVRAM Manager has a void pointer as a function parameter.
     Risk:            No risk, because the underlying pointer type is known.
     Prevention:      No prevention necessary.

  MD_Dlt_3218:        MISRA rule 8.7: File scope static, '%s', only accessed in one function.
     Reason:          Constants defined global but are used only once. The function uses reference, thus constants 
                      have to live after leaving the function.
     Risk:            No error.
     Prevention:      Not required.

  MD_Dlt_1514:        MISRA rule 8.7: Objects shall be defined at block scope if they are only accessed from within a 
                                      single function.
     Reason:          Constants defined global but are used only once. The function uses reference, thus constants 
                      have to live after leaving the function.
     Risk:            No error.
     Prevention:      Not required.

   MD_Dlt_1533:       MISRA rule 8.9: An object should be defined at block scope if its identifier only appears in a
                                      single function.
     Reason:          Constants defined global but are used only once. The function uses reference, thus constants 
                      have to live after leaving the function.
     Risk:            No error.
     Prevention:      Not required.

  MD_Dlt_0686:        MISRA rule 9.2: Braces shall be used to indicate and match the structure in the non-zero 
                                      initialization of arrays and structures. 
     Reason:          The structure Dlt_Context cannot be initialized completely global due to variable length depending 
                      on config parameter Dlt_GetMaxNumberOfApplications().
     Risk:            No error.
     Prevention:      Not required.

  MD_Dlt_3673:        MISRA rule 16.7: A pointer parameter in a function prototype should be declared as pointer to const
                                       if the pointer is not used to modify the addressed object.
     Reason:          The use of these parameters is configuration dependent. In some configurations the pointer is used
                      to modify the addressed object.
     Risk:            No error.
     Prevention:      Not required.

  MD_Dlt_AlwaysTrue:  MISRA rule 2.2: There shall be no dead code
     Reason:          The condition is, depending on the configuration, always true.
     Risk:            No error.
     Prevention:      Not required.

  MD_Dlt_AlwaysFalse: MISRA rule 2.2: There shall be no dead code
     Reason:          The condition is, depending on the configuration, always false.
     Risk:            No error.
     Prevention:      Not required.
*/

/* module specific PClint deviations:
  
  PC_Dlt_438:         PClint rule 438: Last value assigned to variable 'Symbol' not used.
     Reason:          The variables which are not used in functions are covered by dummy statements, but these statements 
                      can be defined to nothing.
     Risk:            Undetected unused variables.
     Prevention:      Not required.

  PC_Dlt_550:         PClint rule 550: Symbol 'Symbol' (Location) not accessed.
     Reason:          The errorId is always created and initialized, but if development error reporting is disabled, 
                      the variable is never used.
     Risk:            Undetected unused variables.
     Prevention:      Not required.
 */

/* COV_JUSTIFICATION_BEGIN

--- Preprocessor Coverage Justifications ------------------------------------------------------------------------------

\ID COV_DLT_FILTER_ASR_XCP
  \ACCEPT XF tx xf
  \ACCEPT TX tx tx 
  \ACCEPT TF tx tf 
  \ACCEPT TF xf tf
  \REASON The feature Dlt_Autosar is filtered if according license is not available (see also [CM_DLT_PRECOMPILEOPTIONS]).

\ID COV_DLT_MSR_COMPATIBILITY
  \ACCEPT TX 
  \ACCEPT XF 
  \REASON [COV_MSR_COMPATIBILITY]

--- Condition Coverage Justifications ---------------------------------------------------------------------------------
\ID COV_DLT_DEFAULT_BRANCH
  \ACCEPT X
  \REASON Rule 15.3 requires a default case at the end of each switch statement. 

\ID COV_DLT_RESPONSE_MSG_LENGTH
  \ACCEPT TX
  \ACCEPT TX tx tx
  \REASON The response message will always have a valid length if DET checks are active (which is mandatory for SafeBSW). Only exception is when too many DltLogChannels are configured. 
          In this case some services cannot be handled by the DLT as defined by ASR. 

\ID COV_DLT_TXMSG_MSGTYPE_VALID
  \ACCEPT TX tf tx
  \ACCEPT TX tx xx
  \REASON The messageType will always be valid if DET checks are active (which is mandatory for SafeBSW).

\ID COV_DLT_NO_RX_DATA_PATH_SUPPORT
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TF tf tx
  \ACCEPT TF xf xf tf
  \ACCEPT TF xf tf tf
  \ACCEPT TF tf xf tf
  \REASON In some configurations, the condition will always match here, because validity is already ensured by previous checks. This happens especially in confiugrations where DLT_RX_DATA_PATH_SUPPORT is disabled.

\ID COV_DLT_LOG_CNTX_FCT
  \ACCEPT TX
  \ACCEPT XF
  \REASON When log context specific SetTraceStatus or SetLogLevel functions are configured, parts of Dlt_Hlp_SetOptionInOneContext() will never/always be executed.

\ID COV_DLT_LOG_LVL_CHG_NOTIFICATION
  \ACCEPT TX
  \ACCEPT XF
  \REASON When log channel specific change notification is enabled/disabled, parts of Dlt_Init_RegisterDefaultDltContexts() and Dlt_RegisterContext() will never/always be executed.

\ID COV_DLT_LOG_CHNL_OPTION
  \ACCEPT TX
  \ACCEPT XF
  \REASON When only a single log channel is configured, parts of Dlt_TxMsg_IsMessageValidOnLogChannel(), Dlt_Hlp_SetLogChannelAssignment(), Dlt_Hlp_GetLogChannelIndexByLogChannelName(), Dlt_TxMsg_Transmit(), Dlt_Init_InitializeLogChannelInfo() and Dlt_TpTxConfirmation() will never/always be executed depending on the config settings.

\ID COV_DLT_SWC_CNTX_OPTION
  \ACCEPT TX
  \ACCEPT XF
  \REASON When only a SWC context is configured, parts of Dlt_Init_RegisterDefaultDltContexts() will never/always be executed depending on the config settings.

COV_JUSTIFICATION_END */

/* SBSW_JUSTIFICATION_BEGIN
 
 \ID             VCA_DLT_VALID_CONFIGURED_APP_ID
 \DESCRIPTION    The ApplicationIndex is determined by calling Dlt_Hlp_GetApplicationIDIndex(). 
                 This function loops for Dlt_Context.appIdCount which is reset in Dlt_Init_InitializeDltContext() 
                 and Dlt_Init_RegisterDefaultDltContexts() and is only incremented Dlt_RegisterContext().
 \COUNTERMEASURE \R Dlt_RegisterContext() has to check Dlt_Context.appIdCount < Dlt_GetMaxNumberOfApplications() before incrementing appIdCount.
                 \M [CM_DLT_VALID_CONFIGURED_APP_ID]
 
 \ID             VCA_DLT_VALID_CONFIGURED_CONTEXT_ID
 \DESCRIPTION    The ContextIndex is determined by calling Dlt_Hlp_GetContextIDIndex(). 
                 This function loops for Dlt_Context.appIds[].contextIdCount which is reset in Dlt_Init_InitializeDltContext() 
                 and Dlt_Init_RegisterDefaultDltContexts() and is only incremented Dlt_RegisterContext().
 \COUNTERMEASURE \R Dlt_RegisterContext() has to check Dlt_Context.appIds[].contextIdCount < Dlt_GetMaxNumberOfContextsPerApplication() before incrementing contextIdCount.
                 \M [CM_DLT_VALID_CONFIGURED_CONTEXT_ID]
 
 \ID             VCA_DLT_VALID_CONFIGURED_LOGCHANNEL_ID
 \DESCRIPTION    The LogChannelIndex is determined by calling Dlt_Hlp_GetLogChannelIndexByLogChannelName(). 
                 This function loops for Dlt_GetSizeOfLogChannelDescriptor().
 \COUNTERMEASURE \M [CM_DLT_VALID_CONFIGURED_LOGCHANNEL_ID]

 \ID             VCA_DLT_VALID_LOG_LVL_CHG_NOTIFICATION_FCT
 \DESCRIPTION    The setLogLevelFct is determined via Dlt_Context.appIds[AppIdIndex].contextInfoList[ConIdIndex].cbkInfo.Dlt_SetLogLevel_ in Dlt_Hlp_SetOptionInOneContext() or Dlt_RegisterContext().
                 This variable is intitialized based on Dlt_SetLogLevelOpClass[]. 
 \COUNTERMEASURE \N  Since DLT_NUMBER_OF_SWCS is used for dimensioning the Dlt_SetLogLevelOpClass[] array no further countermeasure is necessary.

 \ID             VCA_DLT_VALID_TRACE_STATUS_FCT
 \DESCRIPTION    The setTraceStatusFct is determined via Dlt_Context.appIds[AppIdIndex].contextInfoList[ConIdIndex].cbkInfo.Dlt_SetTraceStatus_ in Dlt_Hlp_SetOptionInOneContext() 
                 or Dlt_RegisterContext().
                 This variable is intitialized based on Dlt_SetTraceStatusOpClass[]. 
 \COUNTERMEASURE \N  Since DLT_NUMBER_OF_SWCS is used for dimensioning the Dlt_SetTraceStatusOpClass[] array no further countermeasure is necessary.

 \ID             VCA_DLT_VALID_INJECT_CALL_FCT
 \DESCRIPTION    The injectCallFct is determined via Dlt_Context.appIds[AppIdIndex].contextInfoList[ConIdIndex].cbkInfo.Dlt_InjectCall_ in Dlt_Hlp_SetOptionInOneContext() 
                 or Dlt_RegisterContext().
                 This variable is intitialized based on Dlt_InjectionCallOpClass[]. 
 \COUNTERMEASURE \N  Since DLT_NUMBER_OF_SWCS is used for dimensioning the Dlt_InjectionCallOpClass[] array no further countermeasure is necessary.

 \ID             VCA_VALID_MEMCOPY_DSTPTR
 \DESCRIPTION    The destination pointer and byte count to be copied by VStdLib_MemCopy() is defined by the upperlayer. 
 \COUNTERMEASURE \S The upper layer module of Dlt_SendLogMessage(), Dlt_SendTraceMessage(), Dlt_GetLogChannelNames(), Dlt_DetForwardErrorTrace(), Dlt_DemTriggerOnEventStatus() 
                    and Dlt_CopyTxData() has to ensure that the buffer array size given by the pointer parameters are matching the given number of elements.

 \ID             VCA_DLT_VALID_SEND_BUFFER_IDX
 \DESCRIPTION    The Dlt_SendBuffer[LogChannelIndex].Write is set in Dlt_TxBuf_WriteToBuf() with Range [0..Dlt_GetLogChannelBufferSizeOfLogChannelDescriptor(LogChannelIndex)].
 \COUNTERMEASURE \R Dlt_TxBuf_WriteToBuf() ensures the range using the following runtime check for overflow detection: 
                    (bufferIndex >= (uint32)Dlt_GetLogChannelBufferSizeOfLogChannelDescriptor(LogChannelIndex))
                 \M [CM_DLT_VALID_SEND_BUFFER_IDX]

 \ID             VCA_DLT_VALID_CTRL_BUFFER_IDX
 \DESCRIPTION    The Dlt_ControlSendBuffer[LogChannelIndex].Write is set in Dlt_TxBuf_WriteToCtrlBuf() with Range [0..DLT_CONTROL_BUFFER_SIZE].                
 \COUNTERMEASURE \R Dlt_TxBuf_WriteToCtrlBuf() ensures the range using the following runtime check for overflow detection: (bufferIndex >= (uint32)DLT_CONTROL_BUFFER_SIZE)
                 \N Since DLT_CONTROL_BUFFER_SIZE is used for dimensioning the Dlt_ControlSendBuffer[LogChannelIndex].Buffer[] array no further countermeasure is necessary.

 \ID             VCA_DLT_VALID_RECEIVE_BUFFER_IDX
 \DESCRIPTION    The Dlt_ReceiveBuffer.Write is set in Dlt_CopyRxData() with Range [0..DLT_CONTROL_BUFFER_SIZE].                 
 \COUNTERMEASURE \R Dlt_CopyRxData() ensures the range using the following runtime check for overflow detection: (bufferIndex >= (uint32)DLT_CONTROL_BUFFER_SIZE)
                 \N Since DLT_CONTROL_BUFFER_SIZE is used for dimensioning the Dlt_ReceiveBuffer.Buffer[] array no further countermeasure is necessary.

 \ID             VCA_DLT_VALID_MESSAGE_BUFFER_SIZE
 \DESCRIPTION    The writing the content of the txt message to Dlt_SendData[LogChannelIndex][] the Dlt_TxBuf_CalculateMessageLength() function is used to determine the number of bytes to be copied. 
                 Range: [0 .. DLT_MESSAGE_BUFFER_SIZE].                 
 \COUNTERMEASURE \R Dlt_TxBuf_CalculateMessageLength() ensures the range using the following runtime checks: 
                    Dlt_TxBuf_CalculateMessageLength never returns a value larger then DLT_MESSAGE_BUFFER_SIZE, because Dlt_TxBuf_GetLengthOfNextMsg return 0 in case the read index is out of range 
                    (ReadIndex >= BufferSize) to indicate end of message. This requires DLT_CONTROL_BUFFER_SIZE to be LessEqual DLT_MESSAGE_BUFFER_SIZE which is ensured by CM_DLT_VALID_CTRL_BUFFER_SIZE.
                 \M [CM_DLT_VALID_CTRL_BUFFER_SIZE]

 \ID             VCA_DLT_VALID_READ_IDX
 \DESCRIPTION    The bufferIndex given to Dlt_TxBuf_SetReadIndex() is because Dlt_TxBuf_WriteBufToTxMsg() uses bufferIndex only a valid range. 
 \COUNTERMEASURE \R Dlt_TxBuf_WriteBufToTxMsg() ensures the range of bufferIndex using the following runtime check: 
                    (bufferIndex >= (IsControlBuffer)?(bufferIndex < DLT_CONTROL_BUFFER_SIZE):(bufferIndex < DLT_MESSAGE_BUFFER_SIZE)

 \ID             VCA_DLT_VALID_LAST_STATE
 \DESCRIPTION    The lastState is determined by kDltStateMatrix[lastState][transitionEvent] in Dlt_Sm_StateTransition(). 
 \COUNTERMEASURE \N Since all elements of kDltStateMatrix[][] are either DLT_STATE_UNINIT (0), DLT_STATE_WAIT_FOR_TX_DATA (1) or DLT_STATE_SENDING (2) no further countermeasure is necessary.

 \ID             VCA_DLT_VALID_DATA_PTR
 \DESCRIPTION    The SourceBuffer[] is used as pduInfo.SduDataPtr when calling PduR_DltTransmit(). This SourceBuffer is given when Dlt_TxBuf_WriteBufToTxMsg() is called in Dlt_Sm_SendingDecision().
 \COUNTERMEASURE \N Since either Dlt_ControlSendBuffer[LogChannelIndex].Buffer or Dlt_SendBuffer[LogChannelIndex].Buffer is used as source buffer in Dlt_Sm_SendingDecision() 
                    no further countermeasure is necessary.

 SBSW_JUSTIFICATION_END */
 
 /* ------------------------------------------------------------------------------------------------------------------ */
/* Silent BSW Countermeasures                                                                                         */
/* ------------------------------------------------------------------------------------------------------------------ */
/*
--- MSSV Plugin ---
\CM CM_DLT_PRECOMPILEOPTIONS To ensure that all mandatory / excluded features are as expected, the following must be verified by MSSV:
                               - DLT_USE_COMLAYER_XCP is STD_OFF
                               
\CM CM_DLT_VALID_CONFIGURED_APP_ID To ensure that the array access to Dlt_Context.appIds[] is valid the following must be verified by MSSV:
                               - AssertArraySize(Dlt_LocalLogInfoType.appIds[], Equal, Dlt_GetMaxNumberOfApplications())
                               
\CM CM_DLT_VALID_CONFIGURED_CONTEXT_ID To ensure that the array access to Dlt_Context.appIds[].contextInfoList[] is valid the following must be verified by MSSV:
                               - AssertArraySize(Dlt_LocalApplicationIdInfoType.contextInfoList[], Equal, Dlt_GetMaxNumberOfContextsPerApplication())
                               
\CM CM_DLT_VALID_CONFIGURED_LOGCHANNEL_ID To ensure that the array access to Dlt_NvLogInfoType.logChannelIndexes[] is valid 
                              the following must be verified by MSSV:
                               - AssertArraySize(Dlt_NvLogInfoType.logChannelIndexes[], GreaterEqual, Dlt_GetNumberOfAllValidLogChannels())
                               - Assert(Dlt_GetSizeOfLogChannelDescriptor(), Equal, Dlt_GetNumberOfAllValidLogChannels())    
                               - Assert(DLT_DEFAULT_LOG_CHANNEL_INDEX, LessThan, Dlt_GetNumberOfAllValidLogChannels())                                   

\CM CM_DLT_VALID_SEND_BUFFER_IDX To ensure that the array access to Dlt_SendBuffer[LogChannelIndex].Buffer[bufferIndex] is valid 
                              the following must be verified by MSSV:
                               - Assert(Dlt_GetLogChannelBufferSizeOfLogChannelDescriptor(LogChannelIndex), LessEqual, DLT_MESSAGE_BUFFER_SIZE)

\CM CM_DLT_VALID_CTRL_BUFFER_SIZE To ensure that the array access to Dlt_SendData[LogChannelIndex][] is valid the following must be verified by MSSV:
                               - Assert(DLT_CONTROL_BUFFER_SIZE, LessEqual, DLT_MESSAGE_BUFFER_SIZE)
*/


/**********************************************************************************************************************
 *  END OF FILE: Dlt.c
 *********************************************************************************************************************/
 
