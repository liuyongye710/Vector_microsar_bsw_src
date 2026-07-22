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
 *         File:  J1939Tp_Types.h
 *       Module:  J1939 Transport Layer
 *
 *  Description:  Global types header of the SAE J1939 Transport Layer module.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (J1939TP_TYPES_H)
# define J1939TP_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*! \trace SPEC-2167284 */
# include "ComStack_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/




/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Types of connection abort reasons (CAR). */
typedef uint8 J1939Tp_ConnectionAbortReasonType;
#define J1939TP_CAR_NO_ABORT        (0x00u) /*!< No Abort Reason, do not send abort */

/* J1939, ISOBUS (TP, ETP) */
#define J1939TP_CAR_CONNECTION      (0x01u) /*!< Abort Reason: Already in one or more connection-managed sessions and cannot support another */
#define J1939TP_CAR_RESOURCES       (0x02u) /*!< Abort Reason: System resources were needed for another task so this connection managed session was terminated */
#define J1939TP_CAR_TIMEOUT         (0x03u) /*!< Abort Reason: A timeout occurred and this is the connection abort to close the session */
#define J1939TP_CAR_UNTIMELY_CTS    (0x04u) /*!< Abort Reason: CTS messages received when data transfer is in progress */
#define J1939TP_CAR_RETRANSMIT      (0x05u) /*!< Abort Reason: Maximum retransmit request limit reached */

/* ISOBUS (TP, ETP) */
#define J1939TP_CAR_UNTIMELY_DT     (0x06u) /*!< Abort Reason: Unexpected data transfer packet */
#define J1939TP_CAR_BAD_SEQ         (0x07u) /*!< Abort Reason: Bad sequence number (and software is not able to recover) */
#define J1939TP_CAR_DUP_SEQ         (0x08u) /*!< Abort Reason: Duplicate sequence number (and software is not able to recover) */

/* ISOBUS (ETP) */
#define J1939TP_CAR_UNTIMELY_DPO    (0x09u) /*!< Abort Reason: Unexpected EDPO packet */
#define  J1939TP_CAR_DPO_PGN        (0x0Au) /*!< Abort Reason: Unexpected EDPO PGN (PGN in EDPO is bad) */
#define  J1939TP_CAR_DPO_PACKETS    (0x0Bu) /*!< Abort Reason: EDPO number of packets is greater than CTS */
#define  J1939TP_CAR_DPO_OFFSET     (0x0Cu) /*!< Abort Reason: Bad EDPO offset */
#define  J1939TP_CAR_ECTS_PGN       (0x0Eu) /*!< Abort Reason: Unexpected ECTS PGN (PGN in ECTS is bad) */
#define  J1939TP_CAR_ECTS_PACKETS   (0x0Fu) /*!< Abort Reason: ECTS requested packets exceeds message size */

/* J1939, ISOBUS (TP, ETP) */
#define  J1939TP_CAR_OTHER          (0xFFu) /*!< Abort Reason: Unknown */

/*! Types of N-SDUs. */
typedef uint8 J1939Tp_NSduType;
#define J1939TP_NSDU_DIRECT   (0x0u)
#define J1939TP_NSDU_BAM      (0x1u)
#define J1939TP_NSDU_CMDT_TX  (0x2u)
#define J1939TP_NSDU_CMDT_RX  (0x3u)
#define J1939TP_NSDU_ETP_TX   (0x4u)
#define J1939TP_NSDU_ETP_RX   (0x5u)
#define J1939TP_NSDU_FPP      (0x6u)

/*! States of the transport protocols. */
typedef uint16 J1939Tp_StateType;
#define J1939TP_STATE_IDLE                (0x0000u)
#define J1939TP_STATE_FINISH              (0x0001u)

#define J1939TP_STATEMASK_BUSY            (0x0040u)
#define J1939TP_STATEMASK_CONF            (0x0080u)

#define J1939TP_STATEMASK_DIRECT          (0x0100u)
#define J1939TP_STATE_DIRECT              (0x0101u)
#define J1939TP_STATE_DIRECT_BUSY         (0x0141u)
#define J1939TP_STATE_DIRECT_CONF         (0x0181u)

#define J1939TP_STATEMASK_BAM             (0x0200u)
#define J1939TP_STATE_BAM_BAM             (0x0201u)
#define J1939TP_STATE_BAM_DATA            (0x0205u)
#define J1939TP_STATE_BAM_BAM_BUSY        (0x0241u)
#define J1939TP_STATE_BAM_DATA_BUSY       (0x0245u)
#define J1939TP_STATE_BAM_BAM_CONF        (0x0281u)
#define J1939TP_STATE_BAM_DATA_CONF       (0x0285u)

#define J1939TP_STATEMASK_CMDT            (0x0400u)
#define J1939TP_STATE_CMDT_RTS            (0x0401u)
#define J1939TP_STATE_CMDT_CTSWAIT        (0x0402u)
#define J1939TP_STATE_CMDT_CTS            (0x0403u)
#define J1939TP_STATE_CMDT_DATA_FIRST     (0x0404u)
#define J1939TP_STATE_CMDT_DATA           (0x0405u)
#define J1939TP_STATE_CMDT_EOMACK         (0x0406u)
#define J1939TP_STATE_CMDT_ABORT          (0x0407u)
#define J1939TP_STATE_CMDT_RETRY          (0x0408u)
#define J1939TP_STATE_CMDT_RTS_BUSY       (0x0441u)
#define J1939TP_STATE_CMDT_CTSWAIT_BUSY   (0x0442u)
#define J1939TP_STATE_CMDT_CTS_BUSY       (0x0443u)
#define J1939TP_STATE_CMDT_DATA_BUSY      (0x0445u)
#define J1939TP_STATE_CMDT_EOMACK_BUSY    (0x0446u)
#define J1939TP_STATE_CMDT_ABORT_BUSY     (0x0447u)
#define J1939TP_STATE_CMDT_RTS_CONF       (0x0481u)
#define J1939TP_STATE_CMDT_CTSWAIT_CONF   (0x0482u)
#define J1939TP_STATE_CMDT_CTS_CONF       (0x0483u)
#define J1939TP_STATE_CMDT_DATA_CONF      (0x0485u)
#define J1939TP_STATE_CMDT_EOMACK_CONF    (0x0486u)
#define J1939TP_STATE_CMDT_ABORT_CONF     (0x0487u)

#define J1939TP_STATEMASK_ETP             (0x0800u)
#define J1939TP_STATE_ETP_RTS             (0x0801u)
#define J1939TP_STATE_ETP_CTSWAIT         (0x0802u)
#define J1939TP_STATE_ETP_CTS             (0x0803u)
#define J1939TP_STATE_ETP_DPO             (0x0804u)
#define J1939TP_STATE_ETP_DATA            (0x0805u)
#define J1939TP_STATE_ETP_EOMACK          (0x0806u)
#define J1939TP_STATE_ETP_ABORT           (0x0807u)
#define J1939TP_STATE_ETP_RETRY           (0x0808u)
#define J1939TP_STATE_ETP_RTS_BUSY        (0x0841u)
#define J1939TP_STATE_ETP_CTSWAIT_BUSY    (0x0842u)
#define J1939TP_STATE_ETP_CTS_BUSY        (0x0843u)
#define J1939TP_STATE_ETP_DPO_BUSY        (0x0844u)
#define J1939TP_STATE_ETP_DATA_BUSY       (0x0845u)
#define J1939TP_STATE_ETP_EOMACK_BUSY     (0x0846u)
#define J1939TP_STATE_ETP_ABORT_BUSY      (0x0847u)
#define J1939TP_STATE_ETP_RTS_CONF        (0x0881u)
#define J1939TP_STATE_ETP_CTSWAIT_CONF    (0x0882u)
#define J1939TP_STATE_ETP_CTS_CONF        (0x0883u)
#define J1939TP_STATE_ETP_DPO_CONF        (0x0884u)
#define J1939TP_STATE_ETP_DATA_CONF       (0x0885u)
#define J1939TP_STATE_ETP_EOMACK_CONF     (0x0886u)
#define J1939TP_STATE_ETP_ABORT_CONF      (0x0887u)

#define J1939TP_STATEMASK_FPP             (0x1000u)
#define J1939TP_STATE_FPP_FF              (0x1001u)
#define J1939TP_STATE_FPP_AF              (0x1002u)
#define J1939TP_STATE_FPP_FF_BUSY         (0x1041u)
#define J1939TP_STATE_FPP_AF_BUSY         (0x1042u)
#define J1939TP_STATE_FPP_FF_CONF         (0x1081u)
#define J1939TP_STATE_FPP_AF_CONF         (0x1082u)

#define J1939TP_STATEMASK_PROTOCOL        (0x1F00u)

/*! State of a Tx N-SDU. */
typedef struct
{
  uint32 Size;
  uint32 Packets; /*!< Number of (E)TP.DT frames for BAM/CMDT/ETP, number of additional frames for FPP */
  uint32 PacketOffset;
  PduLengthType DataSize;
  RetryInfoType Retry;
  uint16 TimeOut;
  volatile J1939Tp_StateType State;
  J1939Tp_ConnectionAbortReasonType AbortReason;
  uint8 Aborted;
  uint8 Sequence; /*!< Sequence number for BAM/CMDT/ETP, frame counter for FPP */
  uint8 NextBlock; /*!< Packet number that starts the next block for BAM/CMDT/ETP */
  uint8 MaxBlock;
  uint8 Sender;
  uint8 Receiver;
  uint8 Priority;
} J1939Tp_TxNSduStateType;

/*! State of an Rx N-SDU. */
typedef struct
{
  uint32 Size;
  uint32 Packets; /*!< Number of (E)TP.DT frames for BAM/CMDT/ETP, number of additional frames for FPP */
  uint32 PacketOffset;
  PduLengthType BufSize;
  uint16 TimeOut;
  volatile J1939Tp_StateType State;
  J1939Tp_ConnectionAbortReasonType AbortReason;
  uint8 Aborted;
  uint8 InSession;
  uint8 Sequence; /*!< Sequence number for BAM/CMDT/ETP, frame counter for FPP */
  uint8 NextBlock; /*!< Packet number that starts the next block for BAM/CMDT/ETP */
  uint8 MaxBlock;
  uint8 Sender;
  uint8 Receiver;
  uint8 Priority;
  uint8 RetryAttempts;
} J1939Tp_RxNSduStateType;

/*! State of a Tx N-PDU. */
typedef struct
{
  uint16 ConfTimeout;
  J1939Tp_NSduType CurrentNSduType;
  PduIdType CurrentNSduId;
  volatile boolean Locked;
} J1939Tp_TxNPduStateType;

#endif /* !defined (J1939TP_TYPES_H) */

/**********************************************************************************************************************
 *  END OF FILE: J1939Tp_Types.h
 *********************************************************************************************************************/
