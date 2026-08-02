/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 Vector Informatik GmbH.                                                     All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*! \file  J1939Rm_Types.h
 *  \brief SAE J1939 Request Manager (J1939Rm)
 *
 *  \details Global types header of the SAE J1939 Request Manager.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
#if !defined (J1939RM_TYPES_H)
# define J1939RM_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "ComStack_Types.h"
# include "Rte_J1939Rm_Type.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! Value for unused extended identifier bytes, as used in the J1939Rm_ExtIdInfoType. */
# define J1939RM_EXTID_UNUSED                  (0xFFu)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  User_RequestIndication
 *********************************************************************************************************************/
/*! \brief       Indicates reception of a Request PG.
 *  \details     -
 *  \param[in]   node            Node by which the request was received.
 *  \param[in]   channel         Channel on which the request was received.
 *  \param[in]   requestedPgn    PGN of the requested PG.
 *  \param[in]   extIdInfo       Extended identifier bytes.
 *  \param[in]   sourceAddress   Address of the node that sent the Request PG.
 *  \param[in]   destAddress     Address of this node or 0xFF for broadcast.
 *  \param[in]   priority        Priority of the Request PG.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
typedef P2FUNC(void, J1939RM_APPL_CODE,
               J1939Rm_RequestIndicationFctPtrType) (uint8 node, NetworkHandleType channel, uint32 requestedPgn,
                                                     P2CONST(J1939Rm_ExtIdInfoType, AUTOMATIC, J1939RM_APPL_DATA)
                                                     extIdInfo, uint8 sourceAddress, uint8 destAddress, uint8 priority);

/**********************************************************************************************************************
 *  User_AckIndication
 *********************************************************************************************************************/
/*! \brief       Indicates reception of an Acknowledgement PG.
 *  \details     -
 *  \param[in]   node            Node by which the acknowledgement was received.
 *  \param[in]   channel         Channel on which the acknowledgement was received.
 *  \param[in]   ackPgn          Acknowledged PGN.
 *  \param[in]   extIdInfo       Extended identifier bytes.
 *  \param[in]   ackCode         Type of acknowledgement, see definition of J1939Rm_AckCode for available codes.
 *  \param[in]   ackAddress      Address of this node.
 *  \param[in]   sourceAddress   Address of the node that sent the Acknowledgement PG.
 *  \param[in]   priority        Priority of the Acknowledgement PG.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
typedef P2FUNC(void, J1939RM_APPL_CODE,
               J1939Rm_AckIndicationFctPtrType) (uint8 node, NetworkHandleType channel, uint32 ackPgn,
                                                 P2CONST(J1939Rm_ExtIdInfoType, AUTOMATIC, J1939RM_APPL_DATA)
                                                 extIdInfo, J1939Rm_AckCode ackCode, uint8 ackAddress,
                                                 uint8 sourceAddress, uint8 priority);

/**********************************************************************************************************************
 *  User_RequestTimeoutIndication
 *********************************************************************************************************************/
/*! \brief       Indicates timeout of a request triggered with the same parameters.
 *  \details     -
 *  \param[in]   node            Node by which the request was sent.
 *  \param[in]   channel         Channel on which the request was sent.
 *  \param[in]   requestedPgn    PGN of the requested PG.
 *  \param[in]   extIdInfo       Extended identifier bytes.
 *  \param[in]   destAddress     Address of this node or 0xFF for broadcast.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
typedef P2FUNC(void, J1939RM_APPL_CODE,
               J1939Rm_RequestTimeoutIndicationFctPtrType) (uint8 node, NetworkHandleType channel, uint32 requestedPgn,
                                                            P2CONST(J1939Rm_ExtIdInfoType, AUTOMATIC,
                                                                    J1939RM_APPL_DATA) extIdInfo, uint8 destAddress);

/**********************************************************************************************************************
 *  Rte_RequestIndication
 *********************************************************************************************************************/
/*! \brief       Indicates reception of a Request PG to the RTE.
 *  \details     -
 *  \param[in]   node            Node by which the request was received.
 *  \param[in]   channel         Channel on which the request was received.
 *  \param[in]   requestedPgn    PGN of the requested PG.
 *  \param[in]   extIdInfo       Extended identifier bytes.
 *  \param[in]   sourceAddress   Address of the node that sent the Request PG.
 *  \param[in]   destAddress     Address of this node or 0xFF for broadcast.
 *  \param[in]   priority        Priority of the Request PG.
 *  \return      Return code from runnable. Ignored by J1939Rm.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
typedef P2FUNC(Std_ReturnType, J1939RM_APPL_CODE,
               J1939Rm_RteRequestIndicationFctPtrType) (uint8 node, NetworkHandleType channel, uint32 requestedPgn,
                                                        P2CONST(J1939Rm_ExtIdInfoType, AUTOMATIC, J1939RM_APPL_DATA)
                                                        extIdInfo, uint8 sourceAddress, uint8 destAddress,
                                                        uint8 priority);

/**********************************************************************************************************************
 *  Rte_AckIndication
 *********************************************************************************************************************/
/*! \brief       Indicates reception of an Acknowledgement PG to the RTE.
 *  \details     -
 *  \param[in]   node            Node by which the acknowledgement was received.
 *  \param[in]   channel         Channel on which the acknowledgement was received.
 *  \param[in]   ackPgn          Acknowledged PGN.
 *  \param[in]   extIdInfo       Extended identifier bytes.
 *  \param[in]   ackCode         Type of acknowledgement, see definition of J1939Rm_AckCode for available codes.
 *  \param[in]   ackAddress      Address of this node.
 *  \param[in]   sourceAddress   Address of the node that sent the Acknowledgement PG.
 *  \param[in]   priority        Priority of the Acknowledgement PG.
 *  \return      Return code from runnable. Ignored by J1939Rm.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
typedef P2FUNC(Std_ReturnType, J1939RM_APPL_CODE,
               J1939Rm_RteAckIndicationFctPtrType) (uint8 node, NetworkHandleType channel, uint32 ackPgn,
                                                    P2CONST(J1939Rm_ExtIdInfoType, AUTOMATIC, J1939RM_APPL_DATA)
                                                    extIdInfo, J1939Rm_AckCode ackCode, uint8 ackAddress,
                                                    uint8 sourceAddress, uint8 priority);

/**********************************************************************************************************************
 *  Rte_RequestTimeoutIndication
 *********************************************************************************************************************/
/*! \brief       Indicates timeout of a request triggered with the same parameters to the RTE.
 *  \details     -
 *  \param[in]   node            Node by which the request was sent.
 *  \param[in]   channel         Channel on which the request was sent.
 *  \param[in]   requestedPgn    PGN of the requested PG.
 *  \param[in]   extIdInfo       Extended identifier bytes.
 *  \param[in]   destAddress     Address of this node or 0xFF for broadcast.
 *  \return      Return code from runnable. Ignored by J1939Rm.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
typedef P2FUNC(Std_ReturnType, J1939RM_APPL_CODE,
               J1939Rm_RteRequestTimeoutIndicationFctPtrType) (uint8 node, NetworkHandleType channel,
                                                               uint32 requestedPgn, P2CONST(J1939Rm_ExtIdInfoType,
                                                                                            AUTOMATIC,
                                                                                            J1939RM_APPL_DATA)
                                                               extIdInfo, uint8 destAddress);

/*! States of J1939Rm nodes. */
typedef enum
{
  J1939RM_STATE_OFFLINE = 0,
  J1939RM_STATE_ONLINE = 1
} J1939Rm_StateType;

/*! Internal states of J1939Rm nodes per channel. */
typedef J1939Rm_StateType J1939Rm_NodeChannelStateType;

/*! State of Tx PDUs. */
typedef struct
{
  uint16 ConfTimeout;               /*!< Configurate timeout of the Tx PDU. */
  boolean Locked;                   /*!< Indicates whether the Tx PDU is locked or not. */
} J1939Rm_TxPduStateType;

/*! State of J1939Rm queues. */
typedef struct
{
  uint16 AckQueueWrite;             /*!< Acknowledgment Queue Write of J1939Rm queue. */
  uint16 ReqQueueWrite;             /*!< Request Queue Write of J1939Rm queue. */
  uint16 Req2QueueWrite;            /*!< Request2 Queue Write of J1939Rm queue. */
  uint16 AckQueueRead;              /*!< Acknowledgment Queue Read of J1939Rm queue. */
  uint16 ReqQueueRead;              /*!< Request Queue Read of J1939Rm queue. */
  uint16 Req2QueueRead;             /*!< Request2 Queue Read of J1939Rm queue. */
  uint8 AckQueueFree;               /*!< Acknowledgment Queue Free of J1939Rm queue. */
  uint8 ReqQueueFree;               /*!< Request Queue Free of J1939Rm queue. */
  uint8 Req2QueueFree;              /*!< Request2 Queue Free of J1939Rm queue. */
} J1939Rm_ChannelStateType;

/*! Element of J1939Rm ACKM queue. */
typedef struct
{
  uint32 AckPgn;                    /*!< Contains the acknowlagement pgn of J1939Rm ACKM queue. */
  uint16 NodeChannelStateIndex;     /*!< State Index of the node channel of J1939Rm ACKM queue. */
  uint8 AckCb;                      /*!< Contains the Acknowledgment control byte of J1939Rm ACKM queue. */
  uint8 ExtId1;                     /*!< Contains the Extended identifier byte 1 of J1939Rm ACKM queue. */
  uint8 ExtId2;                     /*!< Contains the Extended identifier byte 2 of J1939Rm ACKM queue. */
  uint8 ExtId3;                     /*!< Contains the Extended identifier byte 3 of J1939Rm ACKM queue. */
  uint8 AckAddress;                 /*!< Contains the address of the node of J1939Rm ACKM queue. */
  uint8 SourceAddress;              /*!< Contains the source address of J1939Rm ACKM queue. */
  uint8 Priority;                   /*!< Contains the priority of of J1939Rm ACKM queue. */
  boolean Broadcast;                /*!< Indicates whether the Ack PG is a response to a broadcast request. */
} J1939Rm_AckQueueElementType;

/*! Element of J1939Rm RQST queue. */
typedef struct
{
  uint32 RequestedPgn;              /*!< Contains the requested pgn of J1939Rm RQST queue. */
  uint16 NodeChannelStateIndex;     /*!< State Index of the node channel of J1939Rm RQST queue. */
  uint8 SourceAddress;              /*!< Contains the source address of J1939Rm RQST queue. */
  uint8 DestAddress;                /*!< Contains the destination address of J1939Rm RQST queue. */
  uint8 Priority;                   /*!< Contains the priority of of J1939Rm RQST queue. */
} J1939Rm_ReqQueueElementType;

/*! Element of J1939Rm RQST2 queue. */
typedef struct
{
  uint32 RequestedPgn;              /*!< Contains the requested pgn of J1939Rm RQST2 queue. */
  uint16 NodeChannelStateIndex;     /*!< State Index of the node channel of J1939Rm RQST2 queue. */
  uint8 SpecInstr;                  /*!< Special instructions byte of J1939Rm RQST2 queue. */
  uint8 ExtId1;                     /*!< Contains the Extended identifier byte 1 of J1939Rm RQST2 queue. */
  uint8 ExtId2;                     /*!< Contains the Extended identifier byte 2 of J1939Rm RQST2 queue. */
  uint8 ExtId3;                     /*!< Contains the Extended identifier byte 3 of J1939Rm RQST2 queue. */
  uint8 SourceAddress;              /*!< Contains the source address of J1939Rm RQST2 queue. */
  uint8 DestAddress;                /*!< Contains the destination address of J1939Rm RQST2 queue. */
  uint8 Priority;                   /*!< Contains the priority of of J1939Rm RQST2 queue. */
} J1939Rm_Req2QueueElementType;

#endif /* J1939RM_TYPES_H */
/**********************************************************************************************************************
 *  END OF FILE: J1939Rm_Types.h
 *********************************************************************************************************************/
