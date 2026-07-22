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
 *         File:  J1939Dcm.h
 *    Component:  MICROSAR Diagnostic Communication Manager for SAE J1939
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  main header file for J1939 DCM
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2014-02-07  visdth  ESCAN00071378 Component Diag_Asr4J1939Dcm created
 *  01.00.01  2014-04-11  visdth  ESCAN00074274 no changes
 *  02.00.00  2014-05-12  visdth  ESCAN00073996 J1939Dcm_InitMemory added
 *                        visdth  ESCAN00071929 StartOfReception changed according to AR4.1.2
 *                        visdth  ESCAN00073477 no changes
 *                        visdth  ESCAN00073465 no changes
 *                        visdth  ESCAN00073464 no changes
 *                        visdth  ESCAN00076282 no changes
 *  02.01.00  2014-09-01  visdth  ESCAN00076487 no changes
 *                        visdth  ESCAN00077928 no changes
 *                        visdth  ESCAN00076604 Support for J1939 Diagnostics (release status)
 *                        visdth  ESCAN00078264 no changes
 *  03.00.00  2015-07-01  visdth  ESCAN00080031 no changes
 *                        visdth  ESCAN00083142 no changes
 *                        visdth  ESCAN00083700 no changes
 *  04.00.00  2016-02-23  visaey  ESCAN00087869 Support DM5/27/53/54/55 in J1939Dcm
 *                        visaey  ESCAN00084694 Adapt to changes of J1939Dcm_RequestIndication and J1939Rm_SendAck
 *  04.01.00  2016-05-17  visaey  ESCAN00089033 PB-S and PB-L for J1939Dcm
 *                        visaey  ESCAN00089284 uninitialized local variable 'lFilterHandler'
 *                        visaey  ESCAN00089006 Node goes offline only when all the referenced channels are offline
 *  04.02.00  2016-06-20  visaey  ESCAN00089269 ISOBUS support in J1939Dcm
 *  07.00.00  2017-09-11  visaey  STORYC-1946   Upgrade Interface in J1939Dcm
 *                        visaey  ESCAN00096873 Possible restriction by J1939Dcm on Dem to issue DEM_NO_SUCH_ELEMENT when no more freeze frames to provide
 *                        visaey  ESCAN00096875 Possibility of insufficient freeze frame buffer
 *  07.00.01  2017-11-10  visaey  ESCAN00097347 Incompatible J1939Dcm and PduR interface
 *  08.00.00  2018-31-01  visaey  ESCAN00098020 Compiler warning: 'NodeHdl' : unreferenced formal parameter
 *                        visaey  ESCAN00098023 Compiler error: Cannot open include file: 'Det.h'
 *  09.00.00  2018-04-17  visaey  STORYC-4781   MISRA-C:2012 Compliance
 *                        visaey  ESCAN00099562 J1939Dcm does not send a diagnostic message (DM) that requires DEM
 *  10.00.00  2018-10-15  visaey  STORYC-6160   J1939Dcm - Process 3.0: Common
 *  10.01.00  2019-02-06  visaey  No relevant changes
 *  11.00.00  2019-03-18  visaey  STORYC-7937   Deny Retry in J1939Dcm
 *            2019-03-27  visaey  STORYC-6106   J1939Dcm - Process 3.0
 *  11.01.00  2019-07-15  visaey  DCM-872       Process 3.0: CAD traceability
 *  11.03.00  2019-07-29  visaey  DCM-73        J1939Dcm Silent - TX/RX and General APIs
 *  12.00.00  2019-09-11  visuvo  -             No relevant changes
 *  12.01.00  2019-09-26  visvkr  DCM-60        J1939Dcm Silent - DMs Processing
 *  12.02.00  2019-10-25  viswse  ESCAN00104602 Compiler error: Inconsistent declaration of J1939Dcm_CopyRxData()
 *                        visuvo  ESCAN00104785 Compiler warning: Unreferenced formal parameter in function J1939Dcm_GetPeerTxPduByDM()
 *                        visuvo  ESCAN00104788 Compiler warning: Unreferenced formal parameter in function J1939Dcm_DMxTriggerAssembly()
 *  12.03.00  2019-11-22  visuvo  DCM-2094      J1939Dcm Silent - Check postbuild configuration consistency
 *  12.04.00  2020-01-20  visepp  -             No relevant changes
 *  13.00.00  2020-03-13  visuvo  DCM-2208      Use different MetaDataLength, depending on DM
 *  13.01.00  2020-06-23  visuvo  ESCAN00106380 Validation rule prevents the correct setting of the meta data length for DM5 and DM17
 *  13.02.00  2020-08-03  visuvo  -             No relevant changes
 *  13.03.00  2020-08-26  visuvo  ESCAN00107201 Exclusive Area J1939DCM_EXCLUSIVE_AREA_0 locked in case of memory access DMs are supported
 *                        visuvo  ESCAN00107204 Exclusive Area J1939DCM_EXCLUSIVE_AREA_0 locked in case of API J1939Dcm_CopyRxData is called
 *                        visuvo  ESCAN00107205 Exclusive Area J1939DCM_EXCLUSIVE_AREA_0 locked in case of API J1939Dcm_CopyTxData is called
 *  13.04.00  2021-02-12  visuvo  DCM-4004      J1939Dcm - Update VCA
 *  14.00.00  2021-05-07  visepp  -             No relevant changes
 *  15.00.00  2022-04-20  visepp  DCM-4810      Usage of <Ma>_MemMap.h in J1939Dcm
 *  15.01.00  2022-05-05  visuvo  DCM-4118      J1939Dcm - Update to QAC 2019.2 (Helix)
 *                        visuvo  ESCAN00111228 DM13: Start/Stop Broadcast on dedicated channel is ignored when DM13 message is received over a channel which is assigned to this network
 *********************************************************************************************************************/


#if !defined (J1939DCM_H)
# define J1939DCM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
/*! Module configuration */
# include "J1939Dcm_Cfg.h"
# include "J1939Dcm_Lcfg.h"
# include "J1939Dcm_PBcfg.h"

# include "J1939Dcm_Types.h"

/*! Callback prototypes */
# include "J1939Dcm_Cbk.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Version Information */

/*! Vendor and module identification - decimal encoding */
# define J1939DCM_VENDOR_ID                                          (30u)
# define J1939DCM_MODULE_ID                                          (58u)
# define J1939DCM_INSTANCE_ID                                        (0u)

/*! AUTOSAR Software Specification Version Information - decimal encoding */
# define J1939DCM_AR_RELEASE_MAJOR_VERSION                           (4u)
# define J1939DCM_AR_RELEASE_MINOR_VERSION                           (1u)
# define J1939DCM_AR_RELEASE_PATCH_VERSION                           (2u)

/*! Component Version Information - decimal encoding */
# define J1939DCM_SW_MAJOR_VERSION                                   (15u)
# define J1939DCM_SW_MINOR_VERSION                                   (1u)
# define J1939DCM_SW_PATCH_VERSION                                   (0u)


/*! Error Reporting Parameters */
/*! DET error-IDs (SWS_J1939Dcm_00090) */
# define J1939DCM_E_INVALID_PDU_SDU_ID                               (0x01u)
# define J1939DCM_E_INVALID_STATE                                    (0x06u)
# define J1939DCM_E_PARAM_ID                                         (0x07u) /*!< RfC 58535 */
# define J1939DCM_E_INVALID_NODE                                     (0x08u) /*!< RfC 58535 */
# define J1939DCM_E_INVALID_PRIO                                     (0x0Au) /*!< RfC 58535 */
# define J1939DCM_E_INVALID_CHANNEL                                  (0x0Bu) /*!< RfC 58535 */
# define J1939DCM_E_INVALID_PGN                                      (0x0Du) /*!< RfC 58535 */
# define J1939DCM_E_BUFFER_TOO_SMALL                                 (0x0Eu)
# define J1939DCM_E_PARAM_POINTER                                    (0x11u)
# define J1939DCM_E_INIT_FAILED                                      (0x14u)
# define J1939DCM_E_UNINIT                                           (0x20u)
# define J1939DCM_E_REINIT                                           (0x21u)

# define J1939DCM_E_OVERRUN                                          (0x31u) /*!< Non-AUTOSAR extension */
# define J1939DCM_E_PARAM_CONFIG                                     (0x32u) /*!< Non-AUTOSAR extension */
# define J1939DCM_E_NO_ERROR                                         (0xFFu) /*!< Not Autosar error. Used for local variables initialization */

/*! DET API-IDs */
# define J1939DCM_API_INIT                                           (0x01u) /*!< SWS_J1939Dcm_00098 */
# define J1939DCM_API_DEINIT                                         (0x02u) /*!< SWS_J1939Dcm_00099 */
# define J1939DCM_API_GETVERSIONINFO                                 (0x03u) /*!< SWS_J1939Dcm_00100 */
# define J1939DCM_API_MAINFUNCTION                                   (0x04u) /*!< SWS_J1939Dcm_00107 */
# define J1939DCM_API_DEMTRIGGERONDTCSTATUS                          (0x0Au) /*!< SWS_J1939Dcm_00122 */
# define J1939DCM_API_SETSTATE                                       (0x0Bu) /*!< SWS_J1939Dcm_00124 */
# define J1939DCM_API_TXCONFIRMATION                                 (0x40u) /*!< SWS_J1939Dcm_00145 */
# define J1939DCM_API_RXINDICATION                                   (0x42u) /*!< SWS_J1939Dcm_00128 */
# define J1939DCM_API_COPYTXDATA                                     (0x43u) /*!< SWS_J1939Dcm_00105 */
# define J1939DCM_API_COPYRXDATA                                     (0x44u) /*!< SWS_J1939Dcm_00103 */
# define J1939DCM_API_TPRXINDICATION                                 (0x45u) /*!< SWS_J1939Dcm_00104 */
# define J1939DCM_API_STARTOFRECEPTION                               (0x46u) /*!< SWS_J1939Dcm_00102 */
# define J1939DCM_API_REQUESTINDICATION                              (0x47u) /*!< SWS_J1939Dcm_00101 */
# define J1939DCM_API_TPTXCONFIRMATION                               (0x48u) /*!< SWS_J1939Dcm_00106 */
# define J1939DCM_API_MEMRESPONSETRANSMIT                            (0x50u) /*!< Vector specific */
# define J1939DCM_API_MEMDATATRANSMIT                                (0x51u) /*!< Vector specific */
# define J1939DCM_API_INITMEMORY                                     (0x80u) /*!< Vector specific */



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define J1939DCM_START_SEC_CODE
# include "J1939Dcm_MemMap.h"                                                                                                                        /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* --- Service Functions --------------------------------------------------------------------------------------------*/
/**********************************************************************************************************************
 * J1939Dcm_Init()
 **********************************************************************************************************************/
/*! \brief        Initializes J1939Dcm.
 *  \details      Insures that the configuration pointer is valid.
 *  \param[in]    ConfigPtr  Pointer to configuration structure for initializing the module
 *  \context      ISR1|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        DSGN-J1939Dcm20848
 *  \pre          Interrupts must be disabled
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_Init(
  P2CONST(J1939Dcm_ConfigType, AUTOMATIC, J1939DCM_INIT_DATA) configPtr
  ); /* SWS_J1939Dcm_00098 */

/**********************************************************************************************************************
 * J1939Dcm_InitMemory()
 **********************************************************************************************************************/
/*! \brief        Initializes VAR_INIT data.
 *  \details      Initializes the statically initialized RAM variables.
 *  \context      ISR1|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        DSGN-J1939Dcm20848
 *  \pre          Interrupts must be disabled
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_InitMemory(
  void
  );

/**********************************************************************************************************************
 * J1939Dcm_DeInit()
 **********************************************************************************************************************/
/*! \brief        Resets J1939Dcm to an uninitialized state.
 *  \details      Sets the state of J1939Dcm to uninitialized and resets J1939Dcm.
 *  \context      ISR1|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        DSGN-J1939Dcm20848
 *  \pre          -
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_DeInit(
  void
  ); /* SWS_J1939Dcm_00099 */

# if (J1939DCM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_GetVersionInfo()
 **********************************************************************************************************************/
/*! \brief        Gets version information.
 *  \details      Gets version information.
 *  \param[in]    versioninfo  Version of the used implementation
 *  \context      ISR1|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        DSGN-J1939Dcm20325
 *  \pre          -
 **********************************************************************************************************************/
FUNC(void, J1939DCM_CODE)
J1939Dcm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, J1939DCM_APPL_DATA) versioninfo
  ); /* SWS_J1939Dcm_00100 */
# endif
/**********************************************************************************************************************
 * J1939Dcm_SetState()
 **********************************************************************************************************************/
/*! \brief        Sets the communication state of J1939Dcm.
 *  \details      Updates state request to notify DM message handlers.
 *  \param[in]    channel   Channel for which the state shall be changed
 *  \param[in]    node      Node for which the state shall be changed
 *  \param[in]    newState  New state the J1939Dcm shall enter
 *  \return       E_OK      New communication state was set
 *  \return       E_NOT_OK  Communication state was not set due to error
 *  \context      ISR1|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        DSGN-J1939Dcm20848
 *  \pre          -
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939DCM_CODE)
J1939Dcm_SetState(
  NetworkHandleType channel,
  uint8 node,
  J1939Dcm_StateType newState); /* SWS_J1939Dcm_00124 */


/* --- Scheduled functions -------------------------------------------------------------------------------------------*/
/**********************************************************************************************************************
 * J1939Dcm_MainFunction()
 **********************************************************************************************************************/
/*! \fn           void J1939Dcm_MainFunction(void)
 *  \brief        Calls J1939Dcm tasks.
 *  \details      Calls J1939Dcm tasks.
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        DSGN-J1939Dcm20340
 *  \pre          -
 **********************************************************************************************************************/


/* --- Memory Access Functions --------------------------------------------------------------------------------------*/
# if (J1939DCM_DM15_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * J1939Dcm_MemResponseTransmit()
 **********************************************************************************************************************/
/*! \brief        Triggers transmission of a memory access response message (DM15).
 *  \details      Constructs the memory handler state for DM15.
 *  \param[in]    AddressInfo           Pointer to channel, source and destination addresses
 *  \param[in]    MemResponseParameter  Pointer to parameters of the DM15 message
 *  \return       E_OK                  If the transmission initiation succeeded
 *  \return       E_NOT_OK              If the transmission initiation failed
 *  \context      ISR1|ISR2
 *  \reentrant    FALSE
 *  \synchronous  FALSE
 *  \trace        DSGN-J1939Dcm22144
 *  \pre          -
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939DCM_CODE)
J1939Dcm_MemResponseTransmit(
  P2CONST(J1939Dcm_AddressInfoType, AUTOMATIC, J1939DCM_APPL_DATA) AddressInfo,
  P2CONST(J1939Dcm_MemRespParamType, AUTOMATIC, J1939DCM_APPL_DATA) MemResponseParameter
  );
# endif

# if ((J1939DCM_DM16_SUPPORT == STD_ON) || \
     (J1939DCM_DM18_SUPPORT == STD_ON))
/**********************************************************************************************************************
 * J1939Dcm_MemDataTransmit()
 **********************************************************************************************************************/
/*! \brief        Triggers transmission of either binary (DM16) or security data (DM18)
 *  \details      Constructs the memory handler state for DM16 or DM18.
 *  \param[in]    DataKind     kind of data (binary or security)
 *  \param[in]    AddressInfo  Pointer to channel, source- and destination addresses
 *  \param[in]    PduInfo      Pointer to data to be transmitted
 *  \return       E_OK         If the transmission initiation succeeded
 *  \return       E_NOT_OK     If the transmission initiation failed
 *  \context      ISR1|ISR2
 *  \reentrant    FALSE
 *  \synchronous  FALSE
 *  \trace        DSGN-J1939Dcm22144
 *  \pre          -
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939DCM_CODE)
J1939Dcm_MemDataTransmit(
  J1939Dcm_MemDataType DataKind,
  P2CONST(J1939Dcm_AddressInfoType, AUTOMATIC, J1939DCM_APPL_DATA) AddressInfo,
  P2CONST(PduInfoType, AUTOMATIC, J1939DCM_APPL_DATA) PduInfo
  );
# endif


# define J1939DCM_STOP_SEC_CODE
# include "J1939Dcm_MemMap.h"                                                                                                                        /* PRQA S 5087 */ /* MD_MSR_MemMap */


/***********************************************************************************************************************
 *  EXCLUSIVE AREA DEFINITION
 **********************************************************************************************************************/
/*!
 * \exclusivearea J1939DCM_EXCLUSIVE_AREA_0
 *                Ensures consistency of the J1939Dcm global state variables.
 *
 * \protects      DM1Queue,
 *                DM13Queue,
 *                DM35Queue,
 *                DMxQueue,
 *                TxHandlerState,
 *                RxHandlerState,
 *                MemHandlerState,
 *                J1939Dcm_QueueBitOPClrAll,
 *                J1939Dcm_TxHandlerPrepare,
 *                J1939Dcm_DM35SetChannelActive,
 *                J1939Dcm_Cfg_MemDataStartOfReceptionFunc,
 *                J1939Dcm_RxHandlerReset,
 *                J1939Dcm_TxHandlerConfirm,
 *                J1939Dcm_QueueBitOpSet
 *
 * \usedin        J1939Dcm_DM1Task,
 *                J1939Dcm_DM13Task,
 *                J1939Dcm_DM35Task,
 *                J1939Dcm_DMxTask,
 *                J1939Dcm_NetTxHandlerTask,
 *                J1939Dcm_NetTxHandlerPrepare,
 *                J1939Dcm_NetTxHandlerTransmit,
 *                J1939Dcm_NetTxHandlerConfirm,
 *                J1939Dcm_NetTxHandlerReset,
 *                J1939Dcm_MemHandlerReset,
 *                J1939Dcm_MemHandlerTask
 *
 * \exclude       J1939Dcm_DM1Init,
 *                J1939Dcm_MemDataTransmit,
 *                J1939Dcm_DeInit,
 *                J1939Dcm_GetVersionInfo,
 *                J1939Dcm_Init,
 *                J1939Dcm_InitMemory,
 *                J1939Dcm_MainFunction,
 *                J1939Dcm_SetState,
 *                J1939Dcm_RequestIndication,
 *                J1939Dcm_RxIndication,
 *                J1939Dcm_StartOfReception,
 *                J1939Dcm_CopyRxData,
 *                J1939Dcm_TpRxIndication,
 *                J1939Dcm_CopyTxData,
 *                J1939Dcm_TpTxConfirmation,
 *                J1939Dcm_TxConfirmation,
 *                J1939Dcm_DemTriggerOnDTCStatus,
 *                J1939Dcm_MemResponseTransmit
 *
 * \length        MEDIUM Typically the exclusive area is short, but there are cases, where function calls are performed.
 * \endexclusivearea
 */
#endif /* J1939DCM_H */

/**********************************************************************************************************************
 *  END OF FILE: Msn.h
 *********************************************************************************************************************/
