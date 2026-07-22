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
 *        \file  Dlt_Types.h
 *        \brief  Dlt Types header file
 *
 *      \details  Types header file of the AUTOSAR Diagnostic Log and Trace, according to:
 *                AUTOSAR Diagnostic Log and Trace, AUTOSAR Release 4.0
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (DLT_TYPES_H_)
# define DLT_TYPES_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dlt_Cfg.h"
# include "ComStack_Types.h"
# include "Rte_Dlt_Type.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# define DLT_OK                                         0x0u
# define DLT_NOT_SUPPORTED                              0x1u
# define DLT_ERROR                                      0x2u

# define DLT_NOT_OK                                     0x1u

/* Dlt_GlobalStateType */
# define DLT_GLOBAL_STATE_UNINIT                        0x0u
/* DLT_GLOBAL_STATE_OFFLINE and DLT_GLOBAL_STATE_ONLINE are defined in Rte_Dlt_Type.h */

/* Keyword macros */
# if !defined (STATIC)                 /* COV_DLT_MSR_COMPATIBILITY */
#  define STATIC static
# endif

# if !defined (LOCAL_INLINE)           /* COV_DLT_MSR_COMPATIBILITY */
#  define LOCAL_INLINE INLINE STATIC
# endif

# if !defined (DLT_LOCAL)              /* COV_DLT_MSR_COMPATIBILITY */
#  define DLT_LOCAL STATIC
# endif

# if !defined (DLT_LOCAL_INLINE)       /* COV_DLT_MSR_COMPATIBILITY */
#  define DLT_LOCAL_INLINE LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

/*! \typedef Variables of this type are used to represent the error codes Dlt can return */
typedef Std_ReturnType Dlt_ReturnType;                       /*!< Return type: defining the possible return values of Dlt APIs. */ /* [Dlt238]; ESCAN00082472 */
# define DLT_E_OK                                       0x0u /*!< Return type value: no error occurred. */
# define DLT_E_MSG_TOO_LARGE                            0x2u /*!< Return type value: API service Dlt_SendLogMessage or Dlt_SendTraceMessage called with too long message. */
# define DLT_E_CONTEXT_ALREADY_REG                      0x3u /*!< Return type value: API service Dlt_RegisterContext called repeatedly with same context. */
# define DLT_E_UNKNOWN_SESSION_ID                       0x4u /*!< Return type value: API service Dlt_RegisterContext, Dlt_SendLogMessage or Dlt_SendTraceMessage called with invalid session ID. */
# define DLT_E_NO_BUFFER                                0x5u /*!< Return type value: Not enough buffer available, therefore the message is rejected. */
# define DLT_E_CONTEXT_NOT_YET_REG                      0x6u /*!< Return type value: The requested context is not registered. */
# define DLT_E_NOT_SUPPORTED                            0x7u /*!< Return type value: The requested service is not supported. */
# define DLT_E_ERROR                                    0x9u /*!< Return type value: Generic error. */

# define DLT_E_MESSAGE_REJECTED                         0xA0u /*!< Return type value: The message was rejected. */

/* ESCAN00082472 */

/* Dlt458 */
typedef struct
{
  uint8  HeaderType;                                       /*!< Standard header type member: contains flags defining size and content of standard header. */ /* Dlt094: HTYP */
  uint8  MessageCounter;                                   /*!< Standard header type member: contains message counter. */ /* Dlt319: MCNT */
  uint16 Length;                                           /*!< Standard header type member: contains length of complete Dlt message. */ /* Dlt320: Length (LEN) shall hold the total length of non-static data of the Dlt message in byte. */
} Dlt_StandardHeaderType;                                  /*!< Standard header type: structure type for standard header of Dlt messages. */

/* Dlt228 */
typedef uint32 Dlt_MessageIDType;                          /*!< Message ID type: defining the type of message ID. */

# if (DLT_USE_COMLAYER_XCP == STD_ON) /* COV_DLT_FILTER_ASR_XCP */
typedef uint32 Dlt_DemEventStatusType;                     /*!< Dem event status type: defining the type of an Dem event status. */

# else /* (DLT_USE_COMLAYER_XCP == STD_ON) */
typedef uint8 Dlt_MessageTypeType;                         /*!< Message type type: defining the type of Dlt message. */
#  define DLT_TYPE_LOG                                  0u /*!< Message type type value: a log message. */
#  define DLT_TYPE_APP_TRACE                            1u /*!< Message type type value: a application trace message. */
#  define DLT_TYPE_NW_TRACE                             2u /*!< Message type type value: a network trace message. */
#  define DLT_TYPE_CONTROL                              3u /*!< Message type type value: a control message. */

/* States of the diagnostic log and trace state machine */
typedef uint8 Dlt_StateType;                              /*!< State type: defining the type of sub state machine. */
#  define DLT_STATE_UNINIT                              0u /*!< State type value: the DLT is uninitialized. */
#  define DLT_STATE_WAIT_FOR_TX_DATA                    1u /*!< State type value: Wait for data to be transmitted. */
#  define DLT_STATE_SENDING                             2u /*!< State type value: wait for successful transmission. */

/* Number of states */
#  define DLT_STATE_NUMBER_OF_STATES                    (0x03u)

/* Valid option settings for GetLogInfo */
#  define DLT_LOG_OPTIONS_RESERVED_3                    (0x03u)
#  define DLT_LOG_OPTIONS_RESERVED_4                    (0x04u)
#  define DLT_LOG_OPTIONS_UNSUSED_5                     (0x05u)
#  define DLT_LOG_OPTIONS_ALL_INFO_WITHOUT_DESCRIPTIONS (0x06u)
#  define DLT_LOG_OPTIONS_ALL_INFO_WITH_DESCRIPTIONS    (0x07u)

/* Valid status settings for GetLogInfo */
#  define DLT_LOG_STATUS_RESERVED_3                     (0x03u)
#  define DLT_LOG_STATUS_RESERVED_4                     (0x04u)
#  define DLT_LOG_STATUS_UNSUSED_5                      (0x05u)
#  define DLT_LOG_STATUS_ALL_INFO_WITHOUT_DESCRIPTIONS  (0x06u)
#  define DLT_LOG_STATUS_ALL_INFO_WITH_DESCRIPTIONS     (0x07u)
#  define DLT_LOG_STATUS_NO_MATCHING_CONTEXT_IDS        (0x08u)
#  define DLT_LOG_STATUS_RESPONSE_DATA_OVERFLOW         (0x09u)

typedef uint32 Dlt_LocalApplicationIDType;
typedef uint32 Dlt_LocalContextIDType;

typedef uint8 Dlt_MessageControlInfoType;

# endif /* (DLT_USE_COMLAYER_XCP == STD_ON) */
#endif /* DLT_TYPES_H_ */

