/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 Vector Informatik GmbH.                                                     All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  J1939Tp_Int.h
 *       Module:  J1939 Transport Layer
 *
 *  Description:  Internal header of the SAE J1939 Transport Layer module.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  MISRA / PClint JUSTIFICATIONS
 *********************************************************************************************************************/

#if !defined (J1939TP_INT_H)
# define J1939TP_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "J1939Tp.h"


# if ((J1939TP_DEV_ERROR_REPORT == STD_ON) || (J1939TP_RUNTIME_ERROR_REPORT == STD_ON))
/*! \trace SPEC-2167285 */
#  include "Det.h"
# endif


/**********************************************************************************************************************
 *  INTERNAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Types of control bytes. */
typedef uint8 J1939Tp_ControlByteType;
# define J1939TP_CB_RTS        (0x10u)
# define J1939TP_CB_CTS        (0x11u)
# define J1939TP_CB_EOMACK     (0x13u)
# define J1939TP_CB_ABORT      (0xFFu)
# define J1939TP_CB_BAM        (0x20u)

# if (J1939TP_ETP_ENABLED == STD_ON)
/*! Types of extended control bytes. */
typedef uint8 J1939Tp_EtpControlByteType;
#  define J1939TP_ECB_RTS      (0x14u)
#  define J1939TP_ECB_CTS      (0x15u)
#  define J1939TP_ECB_DPO      (0x16u)
#  define J1939TP_ECB_EOMACK   (0x17u)
#  define J1939TP_ECB_ABORT    (0xFFu)
# endif


/**********************************************************************************************************************
 *  INTERNAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Compiler abstraction */
# ifndef J1939TP_LOCAL  /* COV_J1939TP_LOCAL_TESTSUITE_INSTRUMENTATION */
#  define J1939TP_LOCAL                         static
# endif
# ifndef J1939TP_LOCAL_INLINE /* COV_J1939TP_LOCAL_TESTSUITE_INSTRUMENTATION */
#  define J1939TP_LOCAL_INLINE                  LOCAL_INLINE
# endif

/* Development Error Detection */
# define J1939TP_INSTANCE_ID_DET                (0u)

/* Special addresses */
# define J1939TP_NULL_ADDRESS                   (0xFEu)
# define J1939TP_BROADCAST_ADDRESS              (0xFFu)
# define J1939TP_NO_ADDRESS_CONFIGURED          (0xFEu)

/* Default priority for TP frames */
# define J1939TP_DEFAULT_PRIORITY               (7u << 2)
# define J1939TP_PRIORITY_MASK                  (0x1Cu)

/* MetaData sizes and positions */
# define J1939TP_MDL_SIZE                       (4u)
# define J1939TP_MDL_SA_POS                     (0u)
# define J1939TP_MDL_DA_POS                     (1u)
# define J1939TP_MDL_GE_POS                     J1939TP_MDL_DA_POS
# define J1939TP_MDL_PDUF_POS                   (2u)
# define J1939TP_MDL_DP_POS                     (3u)
# define J1939TP_MDL_PRI_POS                    J1939TP_MDL_DP_POS

/* Standardized sizes and positions */
# define J1939TP_FRAME_LENGTH                   (8u)
/* TP.CM */
# define J1939TP_TPCM_CB                        (0u) /* all */
# define J1939TP_TPCM_TMS_LO                    (1u) /* BAM, RTS, EOMAck */
# define J1939TP_TPCM_TMS_HI                    (2u) /* BAM, RTS, EOMAck */
# define J1939TP_TPCM_TNOP                      (3u) /* BAM, RTS, EOMAck */
# define J1939TP_TPCM_MNOP                      (4u) /* RTS */
# define J1939TP_TPCM_NOP                       (1u) /* CTS */
# define J1939TP_TPCM_NPN                       (2u) /* CTS */
# define J1939TP_TPCM_CAR                       (1u) /* Abort */
# define J1939TP_TPCM_RES3                      (2u) /* Abort */
# define J1939TP_TPCM_RES4                      (3u) /* CTS, Abort */
# define J1939TP_TPCM_RES5                      (4u) /* BAM, CTS, EOMAck, Abort */
# define J1939TP_TPCM_PGN_LO                    (5u) /* all */
# define J1939TP_TPCM_PGN_MD                    (6u) /* all */
# define J1939TP_TPCM_PGN_HI                    (7u) /* all */
/* TP.DT */
# define J1939TP_TPDT_SEQ                       (0u)
# define J1939TP_TPDT_DATA                      (1u)
# define J1939TP_TPDT_DATA_SIZE                 (7u)
# if (J1939TP_ETP_ENABLED == STD_ON)
/* ETP.CM */
#  define J1939TP_ETPCM_CB                      J1939TP_TPCM_CB /* all */
#  define J1939TP_ETPCM_NBT_LO                  (1u) /* RTS, EOMAck */
#  define J1939TP_ETPCM_NBT_LOMD                (2u) /* RTS, EOMAck */
#  define J1939TP_ETPCM_NBT_HIMD                (3u) /* RTS, EOMAck */
#  define J1939TP_ETPCM_NBT_HI                  (4u) /* RTS, EOMAck */
#  define J1939TP_ETPCM_NOP                     J1939TP_TPCM_NOP /* CTS */
#  define J1939TP_ETPCM_NPN_LO                  (2u) /* CTS */
#  define J1939TP_ETPCM_NPN_MD                  (3u) /* CTS */
#  define J1939TP_ETPCM_NPN_HI                  (4u) /* CTS */
#  define J1939TP_ETPCM_NPO                     (1u) /* DPO */
#  define J1939TP_ETPCM_DPO_LO                  (2u) /* DPO */
#  define J1939TP_ETPCM_DPO_MD                  (3u) /* DPO */
#  define J1939TP_ETPCM_DPO_HI                  (4u) /* DPO */
#  define J1939TP_ETPCM_CAR                     J1939TP_TPCM_CAR /* Abort */
#  define J1939TP_ETPCM_RES3                    J1939TP_TPCM_RES3 /* Abort */
#  define J1939TP_ETPCM_RES4                    J1939TP_TPCM_RES4 /* Abort */
#  define J1939TP_ETPCM_RES5                    J1939TP_TPCM_RES5 /* Abort */
#  define J1939TP_ETPCM_PGN_LO                  J1939TP_TPCM_PGN_LO /* all */
#  define J1939TP_ETPCM_PGN_MD                  J1939TP_TPCM_PGN_MD /* all */
#  define J1939TP_ETPCM_PGN_HI                  J1939TP_TPCM_PGN_HI /* all */
/* ETP.DT */
#  define J1939TP_ETPDT_SEQ                     J1939TP_TPDT_SEQ
#  define J1939TP_ETPDT_DATA                    J1939TP_TPDT_DATA
#  define J1939TP_ETPDT_DATA_SIZE               J1939TP_TPDT_DATA_SIZE
# endif
# if (J1939TP_FPP_ENABLED == STD_ON)
/* FF */
#  define J1939TP_FF_SC                         (0u) /* sequence counter */
#  define J1939TP_FF_TNDB                       (1u) /* total number of data bytes */
#  define J1939TP_FF_DATA                       (2u)
#  define J1939TP_FF_DATA_SIZE                  (6u)
/* AF */
#  define J1939TP_AF_SCFC                       (0u) /* frame counter / sequence counter */
#  define J1939TP_AF_DATA                       (1u)
#  define J1939TP_AF_DATA_SIZE                  (7u)
# endif

/* Standardized values */
# define J1939TP_MAX_LENGTH                     (1785u)
# if (J1939TP_ETP_ENABLED == STD_ON)
#  define J1939TP_ETP_MAX_LENGTH                (117440505L)
# endif
# if (J1939TP_FPP_ENABLED == STD_ON)
#  define J1939TP_FPP_MAX_LENGTH                (223u)
#  define J1939TP_FPP_SC_OFFSET                 (5u)
#  define J1939TP_FPP_SC_MASK                   (0xE0u)
#  define J1939TP_FPP_FC_MASK                   (0x1Fu)
# endif
# define J1939TP_CTS_WAIT                       (0u)

/* Pattern for unused areas */
# define J1939TP_SNA_VALUE                      (0xFFu)
# define J1939TP_TPCM_NPN_UNUSED                J1939TP_SNA_VALUE
# if (J1939TP_ETP_ENABLED == STD_ON)
#  define J1939TP_ETPCM_NPN_UNUSED              (0xFFFFFFUL)
# endif

/* Special values */
# define J1939TP_BS_MIN                         (0u)
# define J1939TP_BS_MAX                         (255u)
# define J1939TP_SEQUENCE_INVALID               (0u)
# define J1939TP_TX_SEQUENCE_INITIAL            (1u)
# define J1939TP_RX_SEQUENCE_INITIAL            (0u)
# define J1939TP_PACKET_OFFSET_INITIAL          (0u)
# define J1939TP_MAX_RETRY_ATTEMPTS             (3u)
# if (J1939TP_FPP_ENABLED == STD_ON)
#  define J1939TP_FPP_FC_FF                     (0u)
#  define J1939TP_FPP_SC_INITIAL                (0u)
#  define J1939TP_FPP_SC_MAX                    (7u)
#  define J1939TP_FPP_SC_INVALID                (0xFFu)
# endif

/* N-PDU size and MDL positions */
# define J1939TP_NPDU_LENGTH                    (J1939TP_FRAME_LENGTH + J1939TP_MDL_SIZE)
# define J1939TP_NPDU_MDL_POS                   J1939TP_FRAME_LENGTH
# define J1939TP_NPDU_SA_POS                    (J1939TP_FRAME_LENGTH + J1939TP_MDL_SA_POS)
# define J1939TP_NPDU_DA_POS                    (J1939TP_FRAME_LENGTH + J1939TP_MDL_DA_POS)
# define J1939TP_NPDU_GE_POS                    J1939TP_NPDU_DA_POS
# define J1939TP_NPDU_PDUF_POS                  (J1939TP_FRAME_LENGTH + J1939TP_MDL_PDUF_POS)
# define J1939TP_NPDU_DP_POS                    (J1939TP_FRAME_LENGTH + J1939TP_MDL_DP_POS)
# define J1939TP_NPDU_PRI_POS                   J1939TP_NPDU_DP_POS


/**********************************************************************************************************************
 *  INTERNAL FUNCTION MACROS
 *********************************************************************************************************************/

/* Divide and round up */
# define J1939Tp_RoundUp(value, div)            (((value) + ((div) - 1u)) / (div))

/* Generic access macros */
# define J1939Tp_AssembleTwoBytes(lo, hi)       (((uint16)(hi) << 8) | (lo))
# define J1939Tp_AssembleThreeBytes(lo, md, hi) (((uint32)(hi) << 16) | ((uint16)(md) << 8) | (lo))
# if (J1939TP_ETP_ENABLED == STD_ON)
#  define J1939Tp_AssembleFourBytes(lo, lomd, himd, hi) (((uint32)(hi) << 24) | ((uint32)(himd) << 16) | ((uint16)(lomd) << 8) | (lo))
# endif
# define J1939Tp_ExtractByteOne(val)            ((uint8)(val))
# define J1939Tp_ExtractByteTwo(val)            ((uint8)((uint16_least)(val) >> 8))
# define J1939Tp_ExtractByteThree(val)          ((uint8)((uint32)(val) >> 16))
# define J1939Tp_ExtractByteFour(val)           ((uint8)((uint32)(val) >> 24))

/* PGN access and check macros */
# define J1939Tp_PGN_GetDP(pgn)                 (J1939Tp_ExtractByteThree(pgn) & 0x03u)
# define J1939Tp_PGN_GetPDUF(pgn)               J1939Tp_ExtractByteTwo(pgn)
# define J1939Tp_PGN_GetPDUS(pgn)               J1939Tp_ExtractByteOne(pgn)
# define J1939Tp_PGN_IsPDU2(pgn)                (J1939Tp_PGN_GetPDUF(pgn) >= 0xF0u)
# define J1939Tp_PGN_ValidDP(pgn)               (J1939Tp_PGN_GetDP(pgn) != 0x03u)
# define J1939Tp_PGN_ValidPDUS(pgn)             (J1939Tp_PGN_IsPDU2(pgn) || (J1939Tp_PGN_GetPDUS(pgn) == 0x00u))
# define J1939Tp_PGN_Valid(pgn)                 (J1939Tp_PGN_ValidDP(pgn) && J1939Tp_PGN_ValidPDUS(pgn))

/* (E)TP.CM access and check macros */
# define J1939Tp_Get_TMS(tms_lo, tms_hi)        J1939Tp_AssembleTwoBytes(tms_lo, tms_hi)
# define J1939Tp_Make_TMS_LO(tms)               J1939Tp_ExtractByteOne(tms)
# define J1939Tp_Make_TMS_HI(tms)               J1939Tp_ExtractByteTwo(tms)
# define J1939Tp_Get_Packets(size)              J1939Tp_RoundUp(size, J1939TP_TPDT_DATA_SIZE)
# if (J1939TP_ETP_ENABLED == STD_ON)
#  define J1939Tp_Get_NBT(nbt_lo, nbt_lomd, nbt_himd, nbt_hi) J1939Tp_AssembleFourBytes(nbt_lo, nbt_lomd, nbt_himd, nbt_hi)
#  define J1939Tp_Make_NBT_LO(nbt)              J1939Tp_ExtractByteOne(nbt)
#  define J1939Tp_Make_NBT_LOMD(nbt)            J1939Tp_ExtractByteTwo(nbt)
#  define J1939Tp_Make_NBT_HIMD(nbt)            J1939Tp_ExtractByteThree(nbt)
#  define J1939Tp_Make_NBT_HI(nbt)              J1939Tp_ExtractByteFour(nbt)
#  define J1939Tp_Get_EtpPackets(size)          J1939Tp_RoundUp(size, J1939TP_ETPDT_DATA_SIZE)
#  define J1939Tp_Get_NPN(npn_lo, npn_md, npn_hi) J1939Tp_AssembleThreeBytes(npn_lo, npn_md, npn_hi)
#  define J1939Tp_Make_NPN_LO(npn)              J1939Tp_ExtractByteOne(npn)
#  define J1939Tp_Make_NPN_MD(npn)              J1939Tp_ExtractByteTwo(npn)
#  define J1939Tp_Make_NPN_HI(npn)              J1939Tp_ExtractByteThree(npn)
#  define J1939Tp_Get_DPO(dpo_lo, dpo_md, dpo_hi) J1939Tp_AssembleThreeBytes(dpo_lo, dpo_md, dpo_hi)
#  define J1939Tp_Make_DPO_LO(dpo)              J1939Tp_ExtractByteOne(dpo)
#  define J1939Tp_Make_DPO_MD(dpo)              J1939Tp_ExtractByteTwo(dpo)
#  define J1939Tp_Make_DPO_HI(dpo)              J1939Tp_ExtractByteThree(dpo)
# endif
# define J1939Tp_Get_PGN(pgn_lo, pgn_md, pgn_hi) J1939Tp_AssembleThreeBytes(pgn_lo, pgn_md, pgn_hi)
# define J1939Tp_Make_PGN_LO(pgn)               J1939Tp_PGN_GetPDUS(pgn)
# define J1939Tp_Make_PGN_MD(pgn)               J1939Tp_PGN_GetPDUF(pgn)
# define J1939Tp_Make_PGN_HI(pgn)               J1939Tp_PGN_GetDP(pgn)
# define J1939Tp_CAR_Valid(car)                 ((((car) >= J1939TP_CAR_CONNECTION) && ((car) <= J1939TP_CAR_RETRANSMIT)) || ((car) == J1939TP_CAR_OTHER))
# define J1939Tp_CAR_ISO_Valid(car)             ((((car) >= J1939TP_CAR_CONNECTION) && ((car) <= J1939TP_CAR_DUP_SEQ)) || ((car) == J1939TP_CAR_OTHER))
# define J1939Tp_CAR_ETP_Valid(car)             ((((car) >= J1939TP_CAR_CONNECTION) && ((car) <= J1939TP_CAR_ECTS_PACKETS)) || ((car) == J1939TP_CAR_OTHER))
# define J1939Tp_DA_Valid(da)                   ((da) != J1939TP_NULL_ADDRESS)
# define J1939Tp_SA_Valid(sa)                   (((sa) != J1939TP_NULL_ADDRESS) && ((sa) != J1939TP_BROADCAST_ADDRESS))

/* FPP FF/AF access and check macros */
# if (J1939TP_FPP_ENABLED == STD_ON)
#  define J1939Tp_Get_Fpp_Packets(size)         ((size) / J1939TP_AF_DATA_SIZE)
#  define J1939Tp_Get_SC(scfc)                  (((scfc) & J1939TP_FPP_SC_MASK) >> J1939TP_FPP_SC_OFFSET)
#  define J1939Tp_Get_FC(scfc)                  ((scfc) & J1939TP_FPP_FC_MASK)
#  define J1939Tp_Make_SC(sc)                   (((sc) << J1939TP_FPP_SC_OFFSET) & J1939TP_FPP_SC_MASK)
#  define J1939Tp_Make_SCFC(sc, fc)             (J1939Tp_Make_SC(sc) | (fc))
# endif

/* MDL access macros */
# define J1939Tp_MDL_Get_PRI(pri)               ((pri) & J1939TP_PRIORITY_MASK)

/* Development Error Detection */
# if (J1939TP_DEV_ERROR_REPORT == STD_ON)
#  define J1939Tp_ReportDevError(SID, ERROR)    ((void)Det_ReportError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID_DET, (SID), (ERROR)))
# else
#  define J1939Tp_ReportDevError(SID, ERROR)
# endif

/* Runtime Error Detection */
# if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
#  define J1939Tp_ReportRuntimeError(SID, ERROR)    ((void)Det_ReportRuntimeError(J1939TP_MODULE_ID, J1939TP_INSTANCE_ID_DET, (SID), (ERROR)))
# else
#  define J1939Tp_ReportRuntimeError(SID, ERROR)
# endif




/**********************************************************************************************************************
 *  INTERNAL DATA PROTOTYPES
 *********************************************************************************************************************/

/*=================================== J1939TP_START_SEC_VAR_ZERO_INIT_UNSPECIFIED ===================================*/
# define J1939TP_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */

# if(J1939TP_USE_INIT_POINTER == STD_ON)
/*! Post-build configuration data of the J1399Tp */
extern P2CONST(J1939Tp_ConfigType, J1939TP_VAR_ZERO_INIT, J1939TP_PBCFG) J1939Tp_ConfigDataPtr;
# endif

# define J1939TP_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*=================================== J1939TP_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED ====================================*/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/*============================================== J1939TP_START_SEC_CODE =============================================*/
# define J1939TP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */

# if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON))
/**********************************************************************************************************************
 * J1939Tp_InternalGetPriority()
 *********************************************************************************************************************/
/*! \brief        Returns the priority
 *  \details      This function returns the priority of the given sduIdx.
 *  \param[in]    txSduIdx      ID of the J1939Tp N-SDU.
 *  \param[in]    info        Pointer to J1939Tp N-SDU structure.
 *  \return       priority    range: 0..7
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/

FUNC(uint8, J1939TP_CODE) J1939Tp_InternalGetPriority(PduIdType txSduIdx,
                                                      P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info);
# endif

# define J1939TP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*============================================== J1939TP_STOP_SEC_CODE ==============================================*/

/* COV_JUSTIFICATION_BEGIN

\ID COV_J1939TP_LOCAL_TESTSUITE_INSTRUMENTATION
  \ACCEPT tx
  \REASON Not all branches covered because the following preprocessor defines are necessary for test execution: J1939TP_LOCAL, J1939TP_LOCAL_INLINE

COV_JUSTIFICATION_END */

#endif /* !defined (J1939TP_INT_H) */

/**********************************************************************************************************************
 *  END OF FILE: J1939Tp_Int.h
 *********************************************************************************************************************/
