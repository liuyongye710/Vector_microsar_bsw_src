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
 *         File:  J1939Dcm_Types.h
 *    Component:  MICROSAR Diagnostic Communication Manager for SAE J1939
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  global type definitions and macros for J1939 DCM
 *
 *********************************************************************************************************************/

#if !defined (J1939DCM_TYPES_H)
# define J1939DCM_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "ComStack_Types.h"

/*! Version Information */

/*! Implementation version */
# define J1939DCM_TYPES_MAJOR_VERSION                                15u
# define J1939DCM_TYPES_MINOR_VERSION                                1u
# define J1939DCM_TYPES_PATCH_VERSION                                0u

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! SAE definitions: parameter group numbers of the diagnostic messages */
# define J1939DCM_DM1_PGN                                            (uint32)0x0000FECAuL
# define J1939DCM_DM2_PGN                                            (uint32)0x0000FECBuL
# define J1939DCM_DM3_PGN                                            (uint32)0x0000FECCuL
# define J1939DCM_DM4_PGN                                            (uint32)0x0000FECDuL
# define J1939DCM_DM5_PGN                                            (uint32)0x0000FECEuL /*!< OBD only */
# define J1939DCM_DM6_PGN                                            (uint32)0x0000FECFuL /*!< OBD only */
# define J1939DCM_DM7_PGN                                            (uint32)0x0000E300uL /*!< Currently not supported */
# define J1939DCM_DM8_PGN                                            (uint32)0x0000FED0uL /*!< Currently not supported */
# define J1939DCM_DM9_PGN                                            (uint32)0xFFFFFFFFuL /*!< Not specified */
# define J1939DCM_DM10_PGN                                           (uint32)0x0000FED2uL /*!< Currently not supported */
# define J1939DCM_DM11_PGN                                           (uint32)0x0000FED3uL
# define J1939DCM_DM12_PGN                                           (uint32)0x0000FED4uL /*!< OBD only */
# define J1939DCM_DM13_PGN                                           (uint32)0x0000DF00uL
# define J1939DCM_DM14_PGN                                           (uint32)0x0000D900uL /*!< Needed for OEM */
# define J1939DCM_DM15_PGN                                           (uint32)0x0000D800uL /*!< Needed for OEM */
# define J1939DCM_DM16_PGN                                           (uint32)0x0000D700uL /*!< Needed for OEM */
# define J1939DCM_DM17_PGN                                           (uint32)0x0000D600uL /*!< Needed for OEM */
# define J1939DCM_DM18_PGN                                           (uint32)0x0000D400uL /*!< Needed for OEM */
# define J1939DCM_DM19_PGN                                           (uint32)0x0000D300uL /*!< OBD only */
# define J1939DCM_DM20_PGN                                           (uint32)0x0000C200uL /*!< OBD only */
# define J1939DCM_DM21_PGN                                           (uint32)0x0000C100uL /*!< OBD only */
# define J1939DCM_DM22_PGN                                           (uint32)0x0000C300uL /*!< Currently not supported */
# define J1939DCM_DM23_PGN                                           (uint32)0x0000FDB5uL /*!< OBD only */
# define J1939DCM_DM24_PGN                                           (uint32)0x0000FDB6uL
# define J1939DCM_DM25_PGN                                           (uint32)0x0000FDB7uL
# define J1939DCM_DM26_PGN                                           (uint32)0x0000FDB8uL /*!< OBD only */
# define J1939DCM_DM27_PGN                                           (uint32)0x0000FD82uL
# define J1939DCM_DM28_PGN                                           (uint32)0x0000FD80uL /*!< OBD only */
# define J1939DCM_DM29_PGN                                           (uint32)0x00009E00uL /*!< OBD only */
# define J1939DCM_DM30_PGN                                           (uint32)0x0000A400uL /*!< Currently not supported */
# define J1939DCM_DM31_PGN                                           (uint32)0x0000A300uL
# define J1939DCM_DM32_PGN                                           (uint32)0x0000A200uL /*!< Currently not supported */
# define J1939DCM_DM33_PGN                                           (uint32)0x0000A100uL /*!< Currently not supported */
# define J1939DCM_DM34_PGN                                           (uint32)0x0000A000uL /*!< Currently not supported */
# define J1939DCM_DM35_PGN                                           (uint32)0x00009F00uL
# define J1939DCM_DM53_PGN                                           (uint32)0x0000FCD1uL
# define J1939DCM_DM54_PGN                                           (uint32)0x0000FCD2uL
# define J1939DCM_DM55_PGN                                           (uint32)0x0000FCD3uL


/*! SAE definitions: default priorities */
# define J1939DCM_DM1_PRIORITY                                       6u
# define J1939DCM_DM2_PRIORITY                                       6u
# define J1939DCM_DM3_PRIORITY                                       6u
# define J1939DCM_DM4_PRIORITY                                       6u
# define J1939DCM_DM5_PRIORITY                                       6u
# define J1939DCM_DM6_PRIORITY                                       6u
# define J1939DCM_DM7_PRIORITY                                       6u
# define J1939DCM_DM8_PRIORITY                                       6u
# define J1939DCM_DM9_PRIORITY                                       6u
# define J1939DCM_DM10_PRIORITY                                      6u
# define J1939DCM_DM11_PRIORITY                                      6u
# define J1939DCM_DM12_PRIORITY                                      6u
# define J1939DCM_DM13_PRIORITY                                      6u
# define J1939DCM_DM14_PRIORITY                                      6u
# define J1939DCM_DM15_PRIORITY                                      6u
# define J1939DCM_DM16_PRIORITY                                      6u
# define J1939DCM_DM17_PRIORITY                                      6u
# define J1939DCM_DM18_PRIORITY                                      6u
# define J1939DCM_DM19_PRIORITY                                      7u
# define J1939DCM_DM20_PRIORITY                                      6u
# define J1939DCM_DM21_PRIORITY                                      6u
# define J1939DCM_DM22_PRIORITY                                      6u
# define J1939DCM_DM23_PRIORITY                                      6u
# define J1939DCM_DM24_PRIORITY                                      6u
# define J1939DCM_DM25_PRIORITY                                      6u
# define J1939DCM_DM26_PRIORITY                                      6u
# define J1939DCM_DM27_PRIORITY                                      6u
# define J1939DCM_DM28_PRIORITY                                      6u
# define J1939DCM_DM29_PRIORITY                                      6u
# define J1939DCM_DM30_PRIORITY                                      6u
# define J1939DCM_DM31_PRIORITY                                      6u
# define J1939DCM_DM32_PRIORITY                                      6u
# define J1939DCM_DM33_PRIORITY                                      6u
# define J1939DCM_DM34_PRIORITY                                      6u
# define J1939DCM_DM35_PRIORITY                                      6u
# define J1939DCM_PRIORITY_DEFAULT                                   6u


/*! DM message identifier */
# define J1939DCM_DM_UNDEF                                           0u
# define J1939DCM_DM1                                                1u
# define J1939DCM_DM2                                                2u
# define J1939DCM_DM3                                                3u
# define J1939DCM_DM4                                                4u
# define J1939DCM_DM5                                                5u
# define J1939DCM_DM6                                                6u
# define J1939DCM_DM7                                                7u
# define J1939DCM_DM8                                                8u
# define J1939DCM_DM9                                                9u
# define J1939DCM_DM10                                               10u
# define J1939DCM_DM11                                               11u
# define J1939DCM_DM12                                               12u
# define J1939DCM_DM13                                               13u
# define J1939DCM_DM14                                               14u
# define J1939DCM_DM15                                               15u
# define J1939DCM_DM16                                               16u
# define J1939DCM_DM17                                               17u
# define J1939DCM_DM18                                               18u
# define J1939DCM_DM19                                               19u
# define J1939DCM_DM20                                               20u
# define J1939DCM_DM21                                               21u
# define J1939DCM_DM22                                               22u
# define J1939DCM_DM23                                               23u
# define J1939DCM_DM24                                               24u
# define J1939DCM_DM25                                               25u
# define J1939DCM_DM26                                               26u
# define J1939DCM_DM27                                               27u
# define J1939DCM_DM28                                               28u
# define J1939DCM_DM29                                               29u
# define J1939DCM_DM30                                               30u
# define J1939DCM_DM31                                               31u
# define J1939DCM_DM32                                               32u
# define J1939DCM_DM33                                               33u
# define J1939DCM_DM34                                               34u
# define J1939DCM_DM35                                               35u
# define J1939DCM_DM36                                               36u
# define J1939DCM_DM37                                               37u
# define J1939DCM_DM38                                               38u
# define J1939DCM_DM39                                               39u
# define J1939DCM_DM40                                               40u
# define J1939DCM_DM41                                               41u
# define J1939DCM_DM42                                               42u
# define J1939DCM_DM43                                               43u
# define J1939DCM_DM44                                               44u
# define J1939DCM_DM45                                               45u
# define J1939DCM_DM46                                               46u
# define J1939DCM_DM47                                               47u
# define J1939DCM_DM48                                               48u
# define J1939DCM_DM49                                               49u
# define J1939DCM_DM50                                               50u
# define J1939DCM_DM51                                               51u
# define J1939DCM_DM52                                               52u
# define J1939DCM_DM53                                               53u
# define J1939DCM_DM54                                               54u
# define J1939DCM_DM55                                               55u
# define J1939DCM_DM_MAX                                             56u


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Data types */

/*! Indicates the handle of the requested node */
typedef uint8                          J1939Dcm_NodeHdlType;
typedef uint8_least                    J1939Dcm_NodeHdlOptType;
/*! Indicates the handle of the requested channel */
typedef uint8                          J1939Dcm_ChannelHdlType;
typedef uint8_least                    J1939Dcm_ChannelHdlOptType;
/*! Indicates the handle of the requested message */
typedef uint8                          J1939Dcm_MessageHdlType;
typedef uint8_least                    J1939Dcm_MessageHdlOptType;
/*! Each bit represents one channel (Bit0 = ChannelHdl 0...) */
typedef uint16                         J1939Dcm_ChannelSupportType;

/*! Enumerations */

/*! Indicates the communication state ON/OFF */
typedef uint8 J1939Dcm_StateType;
# define J1939DCM_STATE_ONLINE                                       (J1939Dcm_StateType)0u /* SWS_J1939Dcm_00123 */
# define J1939DCM_STATE_OFFLINE                                      (J1939Dcm_StateType)1u /* SWS_J1939Dcm_00123 */

/*! Indicates, whether a memory message has to be transmitted */
typedef uint8 J1939Dcm_MemMsgEventType;
# define J1939DCM_MEM_MSG_NO_EVENT                                   (J1939Dcm_MemMsgEventType)0u
# define J1939DCM_MEM_MSG_TRANSMIT                                   (J1939Dcm_MemMsgEventType)1u

/*! Indicates the bus type (Network) via which a request is received or response is sent */
typedef uint8 J1939DcmBusType;
/*! Note: order of enumeration derived from SAE definition for DM13 */
# define J1939DCM_CURRENT_NETWORK                                    (J1939DcmBusType)0u
# define J1939DCM_J1587                                              (J1939DcmBusType)1u
# define J1939DCM_J1922                                              (J1939DcmBusType)2u
# define J1939DCM_J1939_NETWORK_1                                    (J1939DcmBusType)3u
# define J1939DCM_J1939_NETWORK_2                                    (J1939DcmBusType)4u
# define J1939DCM_ISO9141                                            (J1939DcmBusType)5u
# define J1939DCM_J1850                                              (J1939DcmBusType)6u
# define J1939DCM_OTHER                                              (J1939DcmBusType)7u
# define J1939DCM_J1939_NETWORK_3                                    (J1939DcmBusType)8u
# define J1939DCM_PROPRIETARY_NETWORK_1                              (J1939DcmBusType)9u
# define J1939DCM_PROPRIETARY_NETWORK_2                              (J1939DcmBusType)10u
# define J1939DCM_J1939_NETWORK_4                                    (J1939DcmBusType)11u

/*! Indicates whether the requested message is of an interface or an TP type */
typedef uint8 J1939Dcm_TxPathType;
# define J1939DCM_TX_PATH_TP                                         (J1939Dcm_TxPathType)0u
# define J1939DCM_TX_PATH_IF                                         (J1939Dcm_TxPathType)1u

/*! Indicates the memory statuses for DM15 */
typedef uint8  J1939Dcm_MemStatusType;
# define J1939DCM_MEM_STATUS_PROCEED                                 0u
# define J1939DCM_MEM_STATUS_BUSY                                    1u
# define J1939DCM_MEM_STATUS_OPCOMPLETE                              4u
# define J1939DCM_MEM_STATUS_OPFAILED                                5u

/*! Indicates the memory commands for DM14 */
typedef uint8  J1939Dcm_MemCommandType;
# define J1939DCM_MEM_CMD_ERASE                                      0u
# define J1939DCM_MEM_CMD_READ                                       1u
# define J1939DCM_MEM_CMD_WRITE                                      2u
# define J1939DCM_MEM_CMD_STATUS                                     3u
# define J1939DCM_MEM_CMD_OPCOMPLETE                                 4u
# define J1939DCM_MEM_CMD_OPFAILED                                   5u
# define J1939DCM_MEM_CMD_BOOTLOAD                                   6u
# define J1939DCM_MEM_CMD_EDCPGEN                                    7u

/*! Indicates the memory service/DM */
typedef uint8  J1939Dcm_MemDataType;
# define J1939DCM_MEM_DATA_BINARY                                    J1939DCM_DM16
# define J1939DCM_MEM_DATA_BOOTLOAD                                  J1939DCM_DM17
# define J1939DCM_MEM_DATA_SECURITY                                  J1939DCM_DM18
# define J1939DCM_MEM_DATA_INVALID                                   J1939DCM_DM_UNDEF

/*! Indicates the type of the memory pointer in DM14 */
typedef uint8  J1939Dcm_MemPointerTypeType;
# define J1939DCM_MEM_PTRTYPE_DIRECT                                 0u
# define J1939DCM_MEM_PTRTYPE_SPATIAL                                1u

/*! Indicates an error during a memory operation */
typedef uint32 J1939Dcm_MemErrorType;
# define J1939DCM_MEM_ERROR_NONE                                     0x00000000uL /*!< No Error */
# define J1939DCM_MEM_ERROR_UNDEF                                    0x00000001uL /*!< Error NOT identified */
# define J1939DCM_MEM_ERROR_BUSY_OTHER                               0x00000002uL /*!< Currently processing for someone else */
# define J1939DCM_MEM_ERROR_BUSY_ERASE                               0x00000010uL /*!< Currently processing Erase Request */
# define J1939DCM_MEM_ERROR_BUSY_READ                                0x00000011uL /*!< Currently processing Read Request */
# define J1939DCM_MEM_ERROR_BUSY_WRITE                               0x00000012uL /*!< Currently processing Write Request */
# define J1939DCM_MEM_ERROR_BUSY_STATUS                              0x00000013uL /*!< Currently processing Status Request */
# define J1939DCM_MEM_ERROR_BUSY_BOOT                                0x00000016uL /*!< Currently processing Boot Load Request */
# define J1939DCM_MEM_ERROR_BUSY_EDCP                                0x00000017uL /*!< Currently processing EDCP Generation Request */
# define J1939DCM_MEM_ERROR_BUSY_UNDEF                               0x0000001FuL /*!< Currently processing unspecified request from this address */
# define J1939DCM_MEM_ERROR_EDC_PARAM                                0x00000020uL /*!< EDC parameter not correct for data stream */
# define J1939DCM_MEM_ERROR_WRITE_RAM                                0x00000021uL /*!< RAM did not verify on Write */
# define J1939DCM_MEM_ERROR_WRITE_FLASH                              0x00000022uL /*!< FLASH did not verify on Write */
# define J1939DCM_MEM_ERROR_WRITE_PROM                               0x00000023uL /*!< PROM did not verify on Write */
# define J1939DCM_MEM_ERROR_INTERNAL                                 0x00000024uL /*!< Internal failure preventing request (i.e. within the ECU)  */
# define J1939DCM_MEM_ERROR_ADDR_GENERAL                             0x00000100uL /*!< Addressing or DATA General Error */
# define J1939DCM_MEM_ERROR_ADDR_BOUND                               0x00000101uL /*!< Addressing Error - Address not on a valid boundary (Block, Word, Object, etc.) */
# define J1939DCM_MEM_ERROR_ADDR_LENGTH                              0x00000102uL /*!< Addressing Error - Length not valid for memory structure and operation */
# define J1939DCM_MEM_ERROR_ADDR_EXCEED                              0x00000103uL /*!< Addressing Error - required memory exceeded available memory */
# define J1939DCM_MEM_ERROR_ADDR_DATA                                0x00000104uL /*!< Addressing Error - requested operation requires prior erase of DATA memory */
# define J1939DCM_MEM_ERROR_ADDR_PROG                                0x00000105uL /*!< Addressing Error - requested operation requires prior erase of PROGRAM memory */
# define J1939DCM_MEM_ERROR_ADDR_PROG2                               0x00000106uL /*!< Addressing Error - requested operation requires prior execution transfer and erase of PROGRAM memory */
# define J1939DCM_MEM_ERROR_ADDR_BOOT_EXE                            0x00000107uL /*!< Addressing Error - requested address for Boot Loader execution transfer is NOT within executable memory */
# define J1939DCM_MEM_ERROR_ADDR_BOOT_BND                            0x00000108uL /*!< Addressing Error - requested address for Boot Loader execution transfer is NOT on valid boundary */
# define J1939DCM_MEM_ERROR_DATA_RANGE                               0x00000109uL /*!< DATA Error - data does NOT conform to expected or allowed value ranges */
# define J1939DCM_MEM_ERROR_DATA_VALUE                               0x0000010AuL /*!< DATA Error - NAME does NOT conform to expected value */
# define J1939DCM_MEM_ERROR_SEC_GENRAL                               0x00001000uL /*!< Security Error General */
# define J1939DCM_MEM_ERROR_SEC_PASSWD                               0x00001001uL /*!< Security Error - Invalid Password */
# define J1939DCM_MEM_ERROR_SEC_USER                                 0x00001002uL /*!< Security Error - Invalid User Level */
# define J1939DCM_MEM_ERROR_SEC_KEY                                  0x00001003uL /*!< Security Error - Invalid Key {Seed} */
# define J1939DCM_MEM_ERROR_SEC_NODIAG                               0x00001004uL /*!< Security Error - NOT in Diagnostic mode */
# define J1939DCM_MEM_ERROR_SEC_NODEV                                0x00001005uL /*!< Security Error - NOT in Engineering or Development mode */
# define J1939DCM_MEM_ERROR_SEC_ENGINE                               0x00001006uL /*!< Security Error - Engine running */
# define J1939DCM_MEM_ERROR_SEC_NOPARK                               0x00001007uL /*!< Security Error - Vehicle NOT in 'Park' or otherwise NOT stationary */
# define J1939DCM_MEM_ERROR_ABORT_EXTERN                             0x00010000uL /*!< Abort from external to normal software process */
# define J1939DCM_MEM_ERROR_RETRIES                                  0x00010001uL /*!< Too Many Retries - module exceeding a set number of retries */
# define J1939DCM_MEM_ERROR_TIMEOUT_RESP                             0x00010002uL /*!< No response in the time allowed */
# define J1939DCM_MEM_ERROR_TIMEOUT_START                            0x00010003uL /*!< Transport of data NOT initiated within the time allowed */
# define J1939DCM_MEM_ERROR_TIMEOUT_CMPLT                            0x00010004uL /*!< Transport of data NOT completed within the time allowed */
# define J1939DCM_MEM_ERROR_UNAVAILABLE                              0x00FFFFFFuL /*!< No Error Indicator Available */



/*! Function pointers and structs for memory access */
/*! Parameters of DM14: Memory Access Request */
struct J1939DCM_MEMREQPARAM_TAG
{
  uint32                      Pointer;          /*!< 3 bytes of 4 bytes direct memmory address or 3 bytes to identify an object in a particular SPACE */
  uint16                      Length;           /*!< 11 bits parameter to identify memory range desired for a requested operation */
  uint16                      Key;              /*!< 2 bytes Security key */
  uint8                       PointerExtension; /*!< 1 byte to complete a direct memory address or 1 byte to identify a particular SPACE */
  J1939Dcm_MemPointerTypeType PointerType;      /*!< Direct memory addressing (0u) or directed spatial addressing (1u). */
  J1939Dcm_MemCommandType     Command;          /*!< 3 bits command parameter, Erase, Read, Write.... */
};
typedef struct J1939DCM_MEMREQPARAM_TAG J1939Dcm_MemReqParamType;

/*! Parameters of DM15: Memory Access Response */
struct J1939DCM_MEMRESPPARAM_TAG
{
  J1939Dcm_MemErrorType  ErrorIndicator; /*!< 3 bytes parameter to indicate an error or to transfer CRC/EDC */
  uint16                 Length;         /*!< 11 bits parameter to identify memory range approved for a requested operation */
  uint16                 Seed;           /*!< 2 bytes parameter security seed */
  J1939Dcm_MemStatusType Status;         /*!< 3 bits status parameter, Proceed, Busy, Reserved, .... */
  uint8                  EDCPExtension;
};
typedef struct J1939DCM_MEMRESPPARAM_TAG J1939Dcm_MemRespParamType;


/*! Addressing info for received TP messages */
struct J1939DCM_ADDRESSINFO_TAG
{
  NetworkHandleType Channel;            /*!< Communication channel */
  uint8             SourceAddress;      /*!< Source address */
  uint8             DestinationAddress; /*!< Destination address */
};
typedef struct J1939DCM_ADDRESSINFO_TAG J1939Dcm_AddressInfoType;

#endif /* J1939DCM_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: J1939Dcm_Types.h
 *********************************************************************************************************************/
