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
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthTrcv_30_Rtl9000_LL.h
 *        \brief  Ethernet Transceiver Driver Lower Layer Implementation
 *      \details  Hardware dependent implementation for Rtl9000
 *
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2018-01-25  visfmo  -             Initial creation
 *  02.00.00  2018-05-14  visdrr  FIX-4120      ESCAN00099397: PHY-Test modes are not correctly enabled
 *                                STORY-5007    Adapt implementation to fit DrvTrans__coreEthAsr 2.00.00
 *  03.00.00  2021-09-04  mmares  ETHPLAY-90    Update subpackages of DrvTrans_Rtl9000EthAsr to the latest version of
 *                                              DrvTrans__coreAsr and release the component(s)
 *                                ESCAN00109007 Missing memory section in lower layer file
 *                                ESCAN00109063 Errata sheet initialization sequence is missing in driver 
 *                                              implementation
 *  03.00.01  2022-02-22  visdrr  ESCAN00111098 Incorrect transceiver configuration performed for Erratum 2
 *********************************************************************************************************************/
#if !defined (ETHTRCV_30_RTL9000_LL_H)
# define ETHTRCV_30_RTL9000_LL_H
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTrcv_30_Rtl9000_Int.h"
# include "EthTrcv_30_Rtl9000_LL_Regs.h"
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined(ETHTRCV_30_RTL9000_LL_LOCAL)                                                                              /* COV_ETHTRCV_COMPATIBILITY */
#  define ETHTRCV_30_RTL9000_LL_LOCAL                                 static
# endif

# if !defined(ETHTRCV_30_RTL9000_LL_LOCAL_INLINE)                                                                       /* COV_ETHTRCV_COMPATIBILITY */
#  define ETHTRCV_30_RTL9000_LL_LOCAL_INLINE                          LOCAL_INLINE
# endif

/* supported version */
# define ETHTRCV_30_RTL9000_SW_MAJOR_VERSION                          (3u)
# define ETHTRCV_30_RTL9000_SW_MINOR_VERSION                          (0u)
# define ETHTRCV_30_RTL9000_SW_PATCH_VERSION                          (1u)

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETHTRCV_30_RTL9000_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  START TRANSCEIVER ACCESS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_ReadTrcvRegister()
 *********************************************************************************************************************/
/*! \brief   Triggers a read command on the MDIO interface of a Ethernet controller
 *  \details     Function triggers a read command on the MDIO interface according to clause 22 of the IEEE
 *               specification to access clause 45 registers
 *  \param[in]   TrcvIdx           Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                                 instances
 *  \param[in]   PageAddress       Page Address to be selected for the register to be  written
 *  \param[in]   RegisterAddress   Address of the register that shall be written
 *  \param[in]   RegValPtr         Pointer to the value that shall be read to the register
 *  \return      ETH_E_NOT_OK - Service call failed due to invalid module state or function parameters
 *  \return      ETH_E_NO_ACCESS - Access to the MDIO interface timed out
 *  \return      ETH_OK - Read command was triggered successfully
 *  \context     TASK
 *  \reentrant   TRUE for different MDIO interfaces
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
 *********************************************************************************************************************/
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE Std_ReturnType EthTrcv_30_Rtl9000_LL_ReadTrcvRegister(
    uint8 TrcvIdx,
    uint16 PageAddress,
    uint16 RegisterAddress,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_DATA) RegValPtr);

/*********************************************************************************************************************
  * EthTrcv_30_Rtl9000_LL_WriteTrcvRegister()
  ********************************************************************************************************************/
/*! \brief   Triggers a write command on the MDIO interface of a Ethernet controller
 *  \details     Function triggers a write command on the MDIO interface according to clause 22 of the IEEE
 *               specification to access clause 45 registers
 *  \param[in]   TrcvIdx           Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                                 instances
 *  \param[in]   PageAddress       Page Address to be selected for the register to be written
 *  \param[in]   RegisterAddress   Address of the register that shall be written
 *  \param[in]   RegVal            Value that shall be read to the register
 *  \return      ETH_E_NOT_OK - Service call failed due to invalid module state or function parameters
 *  \return      ETH_E_NO_ACCESS - Access to the MDIO interface timed out
 *  \return      ETH_OK - Write command was triggered successfully
 *  \context     TASK
 *  \reentrant   TRUE for different MDIO interfaces
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
  ********************************************************************************************************************/
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE Std_ReturnType EthTrcv_30_Rtl9000_LL_WriteTrcvRegister(
    uint8 TrcvIdx,
    uint16 PageAddress,
    uint16 RegisterAddress,
    uint16 RegVal);

/*********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits()
 ********************************************************************************************************************/
/*! \brief   Updated a bitmask in a transceiver register (set/clear)
 *  \details     Function triggers a read-modify-write operation on the MDIO interface according to clause 22 of the
 *               IEEE specification in order to update a bitmask
 *  \param[in]   TrcvIdx           Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                                 instances
 *  \param[in]   PageAddress       Page Address to be selected for the register to be modified
 *  \param[in]   RegisterAddress   Address of the register that shall be written
 *  \param[in]   RegisterMask      Bitmask to be applied in the selected register
 *  \param[in]   RegisterValue     Target bitvalue to set in the register at the specified mask position
 *  \return      ETH_E_NOT_OK - Service call failed due to invalid module state or function parameters
 *  \return      ETH_E_NO_ACCESS - Access to the MDIO interface timed out
 *  \return      ETH_OK - Write command was triggered successfully
 *  \context     TASK
 *  \reentrant   TRUE for different MDIO interfaces
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
  ********************************************************************************************************************/
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE Std_ReturnType EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits(
    uint8 TrcvIdx,
    uint16 PageAddress,
    uint16 RegisterAddress,
    uint16 RegisterMask,
    uint16 RegisterValue);
/**********************************************************************************************************************
 *  END TRANSCEIVER ACCESS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  START SET MII INTERFACE
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_ClearMiiModeSettings()
 *********************************************************************************************************************/
/*! \brief         Clears the controller interface settings.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_ClearMiiModeSettings(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToMiiMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Mii Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToMiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToLightMiiMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Light Mii Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToLightMiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRmiiMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Rmii Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRmiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRmiiXtalMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Rmii Xtal Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRmiiXtalMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToGmiiMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Gmii Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToGmiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRgmiiMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Rgmii Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRgmiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRgmiiXtalMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Rgmii Xtal Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRgmiiXtalMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_SetBasicConfigurationRegister()
 *********************************************************************************************************************/
/*! \brief         Sets the basic configuration register value.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetBasicConfigurationRegister(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_IsTransceiverAccessOk()
 *********************************************************************************************************************/
/*! \brief         Checks if the transciever's registers are accessible.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \return        TRUE - Transceiver registers can be read/written
 *  \return        FALSE - Transceiver registers cannot be read/written
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Module is initialized.
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsTransceiverAccessOk(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_ApplyAdditionalConfigSteps()
 *********************************************************************************************************************/
/*! \brief         Applies additional configuration steps if necessary
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_ApplyAdditionalConfigSteps(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_GetLinkState()
 *********************************************************************************************************************/
/*! \brief         Gets the current link state from the transceiver
 *  \details       -
 *  \param[in]     TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \param[out]    LinkStatePtr  Pointer to the memory address where the read link state value is stored. Values:
 *                               ETHTRCV_LINK_STATE_ACTIVE, ETHTRCV_LINK_STATE_DOWN
 *  \param[in]     RetVal        State of success of the previous operations before the call of this function:
 *                               E_OK     - The previous operations were successful
 *                               E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK        - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK    - Function has been called with invalid parameters or at least one of the hardware operations
 *                               (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_GetLinkState(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_LinkStateType, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) LinkStatePtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_SetTransceiverModeActive()
 *********************************************************************************************************************/
/*! \brief         Sets the transceiver's mode to active
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetTransceiverModeActive(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_SetTransceiverModeDown()
 *********************************************************************************************************************/
/*! \brief         Sets the transceiver's mode to down
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetTransceiverModeDown(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_GetTransceiverMode()
 *********************************************************************************************************************/
/*! \brief         Gets the transceiver's mode
 *  \details       -
 *  \param[in]     TrcvIdx      Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                              minus one.
 *  \param[out]    TrcvModePtr  Pointer to the memory address where the read transceiver mode value is stored. Values:
 *                              ETHTRCV_MODE_DOWN, ETHTRCV_MODE_ACTIVE
 *  \param[in]     RetVal       State of success of the previous operations before the call of this function:
 *                              E_OK     - The previous operations were successful
 *                              E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK       - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK   - Function has been called with invalid parameters or at least one of the hardware operations
 *                              (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_GetTransceiverMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) TrcvModePtr,
    Std_ReturnType RetVal);

# if ( ETHTRCV_30_RTL9000_ENABLE_GET_DUPLEX_MODE == STD_ON )
/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_GetDuplexMode()
 *********************************************************************************************************************/
/*! \brief         Reads the duplex mode from the transciver.
 *  \details       -
 *  \param[in]     TrcvIdx        Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                                minus one.
 *  \param[out]    DuplexModePtr  Pointer to the memory address where the read duplex mode value is stored. Values:
 *                                ETHTRCV_DUPLEX_MODE_FULL, ETHTRCV_DUPLEX_MODE_HALF
 *  \param[in]     RetVal         State of success of the previous operations before the call of this function:
 *                                E_OK     - The previous operations were successful
 *                                E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK         - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK     - Function has been called with invalid parameters or at least one of the hardware operations
 *                                (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_GetDuplexMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_DuplexModeType, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) DuplexModePtr,
    Std_ReturnType RetVal);
# endif /* ETHTRCV_30_RTL9000_ENABLE_GET_DUPLEX_MODE */

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_IsSetTestModeAvailable()
 *********************************************************************************************************************/
/*! \brief       Checks if the transceiver supports to set the test mode
 *  \details     -
 *  \param[in]   TrcvIdx Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                       minus one.
 *  \return      TRUE  - Transceiver supports to set the test mode
 *  \return      FALSE - Transceiver does not support to set the test mode
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsSetTestModeAvailable(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_IsSignalQualityAvailable()
 *********************************************************************************************************************/
/*! \brief       Checks if the transceiver supports the retrieval of the signal quality
 *  \details     -
 *  \param[in]   TrcvIdx  Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                        minus one.
 *  \return      TRUE   - Transceiver supports the retrieval of the signal quality
 *  \return      FALSE  - Transceiver does not support the retrieval
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsSignalQualityAvailable(
    uint8 TrcvIdx);

# if ( ETHTRCV_30_RTL9000_DEV_ERROR_DETECT == STD_ON )
/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_IsTestmodeSupportedByHw()
 *********************************************************************************************************************/
/*! \brief       Checks if a given test mode is supported by the hardware
 *  \details     -
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \param[in]   TestMode   Test mode to check. Values:
 *                          ETHTRCV_PHYTESTMODE_NONE - Normal operation
 *                          ETHTRCV_PHYTESTMODE_1 - Test transmitter drop
 *                          ETHTRCV_PHYTESTMODE_2 - Test master timing jitter
 *                          ETHTRCV_PHYTESTMODE_3 - Test slave timing jitter
 *                          ETHTRCV_PHYTESTMODE_4 - Test transmitter distortion
 *                          ETHTRCV_PHYTESTMODE_5 - Test power spectral density
 *  \return      TRUE     - Transceiver supports the given test mode
 *  \return      FALSE    - Transceiver does not support the given test mode
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsTestmodeSupportedByHw(
    uint8 TrcvIdx,
    EthTrcv_PhyTestModeType TestMode);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_IsLoopbackmodeSupportedByHw()
 *********************************************************************************************************************/
/*! \brief       Checks if a given loopback mode is supported by the hardware
 *  \details     -
 *  \param[in]   TrcvIdx        Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                              minus one.
 *  \param[in]   LoopbackMode   Loopback mode to check. Values:
 *                              ETHTRCV_PHYLOOPBACK_NONE - Normal operation
 *                              ETHTRCV_PHYLOOPBACK_INTERNAL - Internal Loopback
 *                              ETHTRCV_PHYLOOPBACK_EXTERNAL - External Loopback
 *                              ETHTRCV_PHYLOOPBACK_REMOTE - Remote loopback
 *  \return      TRUE         - Transceiver supports the given loopback mode
 *  \return      FALSE        - Transceiver does not support the given loopback mode
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsLoopbackmodeSupportedByHw(
    uint8 TrcvIdx,
    EthTrcv_PhyLoopbackModeType LoopbackMode);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_IsTxmodeSupportedByHw()
 *********************************************************************************************************************/
/*! \brief       Checks if a given transmission mode is supported by the hardware
 *  \details     -
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \param[in]   TxMode     Transmission mode to check. Values:
 *                          ETHTRCV_PHYTXMODE_NORMAL        Normal Operation
                            ETHTRCV_PHYTXMODE_TX_OFF        Transmitter disabled
                            ETHTRCV_PHYTXMODE_SCRAMBLER_OFF Scrambler disabled
 *  \return      TRUE     - Transceiver supports the given transmission mode
 *  \return      FALSE    - Transceiver does not support the given transmission mode
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE)  EthTrcv_30_Rtl9000_LL_IsTxmodeSupportedByHw(
    uint8 TrcvIdx,
    EthTrcv_PhyTxModeType TxMode);
# endif /* ETHTRCV_30_RTL9000_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_IsCableDiagAvailable()
 *********************************************************************************************************************/
/*! \brief       Checks if the transceiver supports cable diagnostics
 *  \details     -
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \return      TRUE     - Transceiver supports cable diagnostics
 *  \return      FALSE    - Transceiver does not support cable diagnostics
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsCableDiagAvailable(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_IsCableDiagFinished()
 *********************************************************************************************************************/
/*! \brief         Checks if the transceiver's cable diagnostics has finished
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]    ResultPtr  Pointer to the memory address where value of the decision, if the Cable diagnostic has
 *                            finished is stored:
 *                            TRUE: Cable diagnostic has finished
 *                            FALSE: Cable diagnostic has not yet finished
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsCableDiagFinished(
    uint8 TrcvIdx,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_IsCableDiagPrepared()
 *********************************************************************************************************************/
/*! \brief         Checks if the transceiver's cable diagnostics has been prepared
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]    ResultPtr  Pointer to the memory address where value of the decision, if the Cable diagnostic has
 *                            been prepared is stored:
 *                            TRUE: Cable diagnostic is prepared
 *                            FALSE: Cable diagnostic is not yet prepared
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsCableDiagPrepared(
    uint8 TrcvIdx,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_CheckSwReset()
 *********************************************************************************************************************/
/*! \brief         Checks if the software reset has finished
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]    ResultPtr  Pointer to the memory address where value of the decision, if the SW-Reset has finished
 *                            is stored:
 *                            TRUE: SW-Reset has finished
 *                            FALSE: SW-Reset has not yet finished
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_CheckSwReset(
    uint8 TrcvIdx,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_GetPhySignalQualityValueInPercent()
 *********************************************************************************************************************/
/*! \brief         Retrieves the signal quality from the transceiver hardware and stores the value in percent.
 *  \details       This function reads the signal quality from the transceiver hardware and performs the necessary
 *                 calculations to retrieve the value in percent. 0 percent corresponds to the worst and 100 percent 
 *                 corresponds to the best signal quality value that can be read from the transceiver.
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]    ResultPtr  Pointer to the memory address where the read signal quality value in percent is stored.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre         -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_GetPhySignalQualityValueInPercent(
    uint8 TrcvIdx,
    P2VAR(uint8, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_DATA) ResultPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_PerformSwReset()
 *********************************************************************************************************************/
/*! \brief         Performs a software reset.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_PerformSwReset(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_InitGlobalVariables()
 *********************************************************************************************************************/
/*! \brief         Initializes global variables.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_InitGlobalVariables(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_EnableLinkStartupDelay()
 *********************************************************************************************************************/
/*! \brief         Enables a delay before link startup.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_EnableLinkStartupDelay(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_RunVendorSpecificInitScripts()
 *********************************************************************************************************************/
/*! \brief         Runs given vendor specific initializations scripts.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_RunVendorSpecificInitScripts(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_EnableConfigAccess()
 *********************************************************************************************************************/
/*! \brief         Enables the configuration access of the transceiver.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_EnableConfigAccess(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_DisableConfigAccess()
 *********************************************************************************************************************/
/*! \brief         Disables the configuration access of the transceiver.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_DisableConfigAccess(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

# if ( ETHTRCV_30_RTL9000_ENABLE_START_AUTO_NEG == STD_ON )
/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_EnableStartAutoNegotiation()
 *********************************************************************************************************************/
/*! \brief         Enables the auto negotiation.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_EnableStartAutoNegotiation(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);
# endif /* ETHTRCV_30_RTL9000_ENABLE_START_AUTO_NEG */

# if ( ETHTRCV_30_RTL9000_ENABLE_GET_BAUD_RATE == STD_ON )
/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_CheckBaudRate()
 *********************************************************************************************************************/
/*! \brief         Retrieves the baud rate out of the read register value.
 *  \details       -
 *  \param[in]     TrcvIdx      Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                              minus one.
 *  \param[out]    BaudRatePtr  Pointer to the memory address where the retrieved baud rate is stored. Values:
 *                              ETHTRCV_BAUD_RATE_10MBIT   - Linkspeed  10 Mbit/s
 *                              ETHTRCV_BAUD_RATE_100MBIT  - Linkspeed: 100 Mbit/s
 *                              ETHTRCV_BAUD_RATE_1000MBIT - Linkspeed: 1Gb/s
 *  \param[in]     RetVal       State of success of the previous operations before the call of this function:
 *                              E_OK     - The previous operations were successful
 *                              E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK       - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK   - Function has been called with invalid parameters or at least one of the hardware operations
 *                              (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_GetBaudRate(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_BaudRateType, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) BaudRatePtr,
    Std_ReturnType RetVal);
# endif /* ETHTRCV_30_RTL9000_ENABLE_GET_BAUD_RATE */

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_PrepareSignalQualityMeasurement()
 *********************************************************************************************************************/
/*! \brief         Prepares the signal quality measurement.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_PrepareSignalQualityMeasurement(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_SetTestMode()
 *********************************************************************************************************************/
/*! \brief         Sets the phy into the given test mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     TestMode   Test mode to set. Values:
 *                            ETHTRCV_PHYTESTMODE_NONE - Normal operation
 *                            ETHTRCV_PHYTESTMODE_1 - Test transmitter drop
 *                            ETHTRCV_PHYTESTMODE_2 - Test master timing jitter
 *                            ETHTRCV_PHYTESTMODE_3 - Test slave timing jitter
 *                            ETHTRCV_PHYTESTMODE_4 - Test transmitter distortion
 *                            ETHTRCV_PHYTESTMODE_5 - Test power spectral density
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetPhyTestMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTestModeType TestMode,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_SetPhyLoopbackMode()
 *********************************************************************************************************************/
/*! \brief       Sets the phy into the given loopback mode.
 *  \details     -
 *  \param[in]   TrcvIdx        Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                              minus one.
 *  \param[in]   LoopbackMode   Loopback mode to set. Values:
 *                              ETHTRCV_PHYLOOPBACK_NONE - Normal operation
 *                              ETHTRCV_PHYLOOPBACK_INTERNAL - Internal Loopback
 *                              ETHTRCV_PHYLOOPBACK_EXTERNAL - External Loopback
 *                              ETHTRCV_PHYLOOPBACK_REMOTE - Remote loopback
 *  \param[in]   RetVal         State of success of the previous operations before the call of this function:
 *                              E_OK     - The previous operations were successful
 *                              E_NOT_OK - At least one of the previous operations has failed
 *  \return      E_OK         - The operations in this function and the previous operations were successful
 *  \return      E_NOT_OK     - Function has been called with invalid parameters or at least one of the hardware operations
 *                              (read/write) in this function or the previous functions has failed
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetPhyLoopbackMode(
    uint8 TrcvIdx,
    EthTrcv_PhyLoopbackModeType LoopbackMode,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_SetPhyTxMode()
 *********************************************************************************************************************/
/*! \brief         Sets the phy into the given transmission mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     TxMode     Transmission mode to set. Values:
 *                            ETHTRCV_PHYTXMODE_NORMAL        Normal Operation
 *                            ETHTRCV_PHYTXMODE_TX_OFF        Transmitter disabled
 *                            ETHTRCV_PHYTXMODE_SCRAMBLER_OFF Scrambler disabled
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetPhyTxMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTxModeType TxMode,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_FinalizeSignalQualityMeasurement()
 *********************************************************************************************************************/
/*! \brief         Performs configuration which is necessary after a signal quality measurement to resume normal operation
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_FinalizeSignalQualityMeasurement(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_PrepareCableDiag()
 *********************************************************************************************************************/
/*! \brief         Prepares the transceiver for the retrieval of the cable diagnostics result, for example turning down
 *                 the link
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_PrepareCableDiag(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_EnableDiagnosticSequence()
 *********************************************************************************************************************/
/*! \brief         Enables the transceiver's cable diagnostic measurement sequence
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_EnableDiagnosticSequence(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_CheckCableDiagResult()
 *********************************************************************************************************************/
/*! \brief         Retrieves the result of the cable diagnostics measurement.
 *  \details       -
 *  \param[in]     TrcvIdx             Zero based index of the transceiver. Range: 0 to number of configured
 *                                     transceiver instances minus one.
 *  \param[out]    CableDiagResultPtr  Pointer to the memory address where the result of the cable diagnosis is stored:
 *                                     ETHTRCV_CABLEDIAG_OK: Cable diagnostics result was OK
 *                                     ETHTRCV_CABLEDIAG_ERROR: Cable diagnostics failed
 *                                     ETHTRCV_CABLEDIAG_SHORT: Cable diagnostics detected a short on the MDI
 *                                     ETHTRCV_CABLEDIAG_OPEN: Cable diagnostics detected an open on the MDI
 *  \param[in]     RetVal              State of success of the previous operations before the call of this function:
 *                                     E_OK     - The previous operations were successful
 *                                     E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK              - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK          - Function has been called with invalid parameters or at least one of the hardware
 *                                     operations (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_CheckCableDiagResult(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_CableDiagResultType, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) CableDiagResultPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_AdditionalStepsAfterCableDiag()
 *********************************************************************************************************************/
/*! \brief         Performs configuration which is necessary after a cable diagnostics measurement to resume normal
 *                 operation
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_AdditionalStepsAfterCableDiag(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_ReadIdentifier1Register()
 *********************************************************************************************************************/
/*! \brief         Reads the first identifier register of the transceiver
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]    RegValPtr  Pointer to the memory where the content of the first identifier register of the
 *                            transceiver is stored
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_ReadIdentifier1Register(
    uint8 TrcvIdx,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) RegValPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_ReadIdentifier2Register()
 *********************************************************************************************************************/
/*! \brief         Reads the second identifier register of the transceiver
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]    RegValPtr  Pointer to the memory where the content of the second identifier register of the
 *                            transceiver is stored
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_ReadIdentifier2Register(
    uint8 TrcvIdx,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) RegValPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_LL_MainFunctionLinkHandling()
 *********************************************************************************************************************/
/*! \brief         Main function lower layer implementation which is used for link handling and link startup.
 *  \details       This function is used to perform timing relevant initialization and link startup and/or link
 *                 handling tasks.
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Module is initialized.
 *  \pre           EthTrcv_30_Rtl9000_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \pre           EthTrcv_30_Rtl9000_SetTransceiverMode() has been called for the transceiver with index TrcvIdx with
 *                 mode ACTIVE
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_MainFunctionLinkHandling(
    uint8 TrcvIdx);

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_Erratum2
 *********************************************************************************************************************/
/*! \brief         Workaround for Erratum 2 of Erratasheet v1.5_164675.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_Erratum2(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES DERIVATIVE SPECIFIC
 *********************************************************************************************************************/
# if !defined(ETHTRCV_30_RTL9000_UNIT_TEST) /* COV_ETHTRCV_TEST_SUITE_UNIT_TESTS */
/**********************************************************************************************************************
 *  START TRANSCEIVER ACCESS
 *********************************************************************************************************************/
/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_ReadTrcvRegister
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
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_ReadTrcvRegister(
    uint8 TrcvIdx,
    uint16 PageAddress,
    uint16 RegisterAddress,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_DATA) RegValPtr)
{

  Std_ReturnType retVal;

  /* #10 The function was called to perform a special register access method  */
  if(PageAddress == ETHTRCV_30_RTL9000_PAGE_NONE)
  {
    /* #110 Set address in PHY SRAM Address Register */
    retVal = EthTrcv_30_Rtl9000_WriteTrcvReg(
        TrcvIdx,
        ETHTRCV_30_RTL9000_REG_OFFS_PHYSRAD,
        RegisterAddress);

    /* #120 Read Data trough PHY SRAM Data Register */
    retVal |= EthTrcv_30_Rtl9000_ReadTrcvReg(
        TrcvIdx,
        ETHTRCV_30_RTL9000_REG_OFFS_PHYSRD,
        RegValPtr);
  }
  /* #20 The function was called to perform a normal register access */
  else
  {

    /* #210 Set the page in the page select register */
    retVal = EthTrcv_30_Rtl9000_WriteTrcvReg(
        TrcvIdx,
        ETHTRCV_30_RTL9000_REG_OFFS_PAGSR,
        PageAddress);

    /* #220 Read data from the register */
    retVal |= EthTrcv_30_Rtl9000_ReadTrcvReg(
        TrcvIdx,
        (uint8) RegisterAddress,
        RegValPtr);

    /* #230 Restore default page in the page select register */
    retVal |= EthTrcv_30_Rtl9000_WriteTrcvReg(
        TrcvIdx,
        ETHTRCV_30_RTL9000_REG_OFFS_PAGSR,
        ETHTRCV_30_RTL9000_PAGE_DEFAULT);
  }

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_WriteTrcvRegister
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
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_WriteTrcvRegister(
    uint8 TrcvIdx,
    uint16 PageAddress,
    uint16 RegisterAddress,
    uint16 RegVal)
{
  Std_ReturnType retVal;

  /* #10 The function was called to perform a special register access method */
  if(PageAddress == ETHTRCV_30_RTL9000_PAGE_NONE)
  {
    /* #110 Set address in PHY SRAM Address Register */
    retVal = EthTrcv_30_Rtl9000_WriteTrcvReg(
        TrcvIdx,
        ETHTRCV_30_RTL9000_REG_OFFS_PHYSRAD,
        RegisterAddress);

    /* #120 Write data in PHY SRAM data register */
    retVal |= EthTrcv_30_Rtl9000_WriteTrcvReg(
        TrcvIdx,
        ETHTRCV_30_RTL9000_REG_OFFS_PHYSRD,
        RegVal);
  }
  /* #20 The function was called to perform a normal register access */
  else
  {
    /* #210 Set the page in the page select register */
    retVal = EthTrcv_30_Rtl9000_WriteTrcvReg(
        TrcvIdx,
        ETHTRCV_30_RTL9000_REG_OFFS_PAGSR,
        PageAddress);

    /* #220 Write data into the register */
    retVal |= EthTrcv_30_Rtl9000_WriteTrcvReg(
        TrcvIdx,
        (uint8) RegisterAddress,
        RegVal);

    /* #230 Restore default page in the page select register */
    retVal |= EthTrcv_30_Rtl9000_WriteTrcvReg(
        TrcvIdx,
        ETHTRCV_30_RTL9000_REG_OFFS_PAGSR,
        ETHTRCV_30_RTL9000_PAGE_DEFAULT);
  }

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits(
    uint8 TrcvIdx,
    uint16 PageAddress,
    uint16 RegisterAddress,
    uint16 RegisterMask,
    uint16 RegisterValue)
{
  Std_ReturnType retVal;
  uint16 currentValue;
  uint16 tempValue;

  /* #10 Read the current value from the register in which the bits should be updated */
  retVal = EthTrcv_30_Rtl9000_LL_ReadTrcvRegister(TrcvIdx, PageAddress, RegisterAddress, &currentValue);

  /* #20 Clear the bits in the previously read register value that are set in the given register mask and set the bits
   *     that  are set in both the mask and the register value to be set */
  tempValue = currentValue & ((uint16) ~RegisterMask);
  tempValue |= RegisterValue & RegisterMask;

  /* #30 Write the resulting value back into the register */
  retVal |= EthTrcv_30_Rtl9000_LL_WriteTrcvRegister(TrcvIdx, PageAddress, RegisterAddress, tempValue);

  return retVal;
}
/**********************************************************************************************************************
 *  END TRANSCEIVER ACCESS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  START SET MII INTERFACE
 *********************************************************************************************************************/
/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_ClearMiiModeSettings
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_ClearMiiModeSettings(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing to do */
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRmiiMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToMiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing to do */
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToLightMiiMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToLightMiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing to do */
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRmiiMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRmiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing to do */
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRmiiXtalMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRmiiXtalMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing to do */
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToGmiiMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToGmiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing to do */
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRgmiiMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRgmiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing to do */
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRgmiiXtalMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetMiiInterfaceToRgmiiXtalMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing to do */
  return retVal;
}
/**********************************************************************************************************************
 *  END SET MII INTERFACE
 *********************************************************************************************************************/
/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_SetBasicConfigurationRegister
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetBasicConfigurationRegister(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  uint16 regVal = EthTrcv_30_Rtl9000_GetBasicCtrlRegValOfEthTrcv(TrcvIdx);

  /* #10 Set the basic configuration in the PHYCR register */
  retVal |= EthTrcv_30_Rtl9000_LL_WriteTrcvRegister(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_0,
      ETHTRCV_30_RTL9000_REG_OFFS_PHYCR,
      regVal);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_PerformSwReset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_PerformSwReset(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 If the Erratum #2 v. 1.5 is enabled */
  if (EthTrcv_30_Rtl9000_IsErratum2ActiveOfEthTrcvRtl9000(TrcvIdx) == TRUE)
  {
    /* #110 Perform lines 1 to 94 of the Erratum #2 sequence */
    retVal |= EthTrcv_30_Rtl9000_LL_Erratum2(TrcvIdx);
  }

  /* #20 Set the SW-Reset bit in the basic control register (equal to line 95 of Erratum #2) */
  retVal |= EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_0,
      ETHTRCV_30_RTL9000_REG_OFFS_BMCR,
      ETHTRCV_30_RTL9000_REG_BMCR_RESET,
      ETHTRCV_30_RTL9000_REG_BMCR_RESET);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_InitGlobalVariables
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_InitGlobalVariables(
    uint8 TrcvIdx)
{
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  /* #10 Nothing to do */
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_EnableLinkStartupDelay
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_EnableLinkStartupDelay(
    uint8 TrcvIdx)
{
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  /* #10 Nothing to do */
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_IsTransceiverAccessOk
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsTransceiverAccessOk(
    uint8 TrcvIdx)
{
  Std_ReturnType retVal;
  uint16 regVal;
  boolean result = FALSE;

  /* #10 Read OUI-MSB from PHYIDR1 */
  retVal = EthTrcv_30_Rtl9000_LL_ReadTrcvRegister(
      TrcvIdx, ETHTRCV_30_RTL9000_PAGE_0,
      ETHTRCV_30_RTL9000_REG_OFFS_PHYIDR1,
      &regVal);

  /* #20 The read value corresponds to the 15 MSB of the OUI */
  if ( (regVal == ETHTRCV_30_RTL9000_REG_PHYIDR1_OUI_MSB ) && (retVal == E_OK) )
  {
    /* #210 The transceiver can be accessed correctly over the management interface */
    result = TRUE;
  }

  return result;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_ApplyAdditionalConfigSteps
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_ApplyAdditionalConfigSteps(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing to do */
  
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_IsSetTestModeAvailable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsSetTestModeAvailable(
    uint8 TrcvIdx)
{
  boolean result = TRUE;
  
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  
  /* #10 Return that setting the test modes is available */
  return result;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_IsSignalQualityAvailable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsSignalQualityAvailable(
    uint8 TrcvIdx)
{
  boolean result = TRUE;
  
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  
  /* #10 Return that signal quality measurement is available */
  return result;
}

#  if ( ETHTRCV_30_RTL9000_DEV_ERROR_DETECT == STD_ON )
/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_IsTestmodeSupportedByHw
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsTestmodeSupportedByHw(
    uint8 TrcvIdx,
    EthTrcv_PhyTestModeType TestMode)
{
  boolean result;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 The test mode to be set is among the supported test modes */
  if ((TestMode == ETHTRCV_PHYTESTMODE_NONE) ||
      (TestMode == ETHTRCV_PHYTESTMODE_1) ||
      (TestMode == ETHTRCV_PHYTESTMODE_2) ||
      (TestMode == ETHTRCV_PHYTESTMODE_4) ||
      (TestMode == ETHTRCV_PHYTESTMODE_5))
  {
    /* #110 Return that the test mode to be set is supported */
    result = TRUE;
  }
  /* #20 The test mode to be set is not supported */
  else
  {
    /* #210 Return that the test mode to be set is not supported */
    result = FALSE;
  }

  return result;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_IsLoopbackmodeSupportedByHw
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsLoopbackmodeSupportedByHw(
    uint8 TrcvIdx,
    EthTrcv_PhyLoopbackModeType LoopbackMode)
{
  boolean result;
  
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  
  /* #10 The loopback mode to be set is among the supported loopback modes */
  if((LoopbackMode == ETHTRCV_PHYLOOPBACK_NONE) ||
     (LoopbackMode == ETHTRCV_PHYLOOPBACK_INTERNAL) ||
     (LoopbackMode == ETHTRCV_PHYLOOPBACK_EXTERNAL) ||
     (LoopbackMode == ETHTRCV_PHYLOOPBACK_REMOTE))
  {
    /* #110 Return that the loopback mode to be set is supported */
    result = TRUE;
  }
  /* #20 The loopback mode to be set is not supported */
  else
  {
    /* #210 Return that the loopback mode to be set is not supported */
    result = FALSE;
  }


  return result;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_IsTxmodeSupportedByHw
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE)  EthTrcv_30_Rtl9000_LL_IsTxmodeSupportedByHw(
    uint8 TrcvIdx,
    EthTrcv_PhyTxModeType TxMode)
{
  boolean result;
  
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 The tx mode to be set is among the supported tx modes */
  if(TxMode == ETHTRCV_PHYTXMODE_NORMAL)
  {
    /* #110 Return that the tx mode to be set is supported */
    result = TRUE;
  }
  /* #20 The tx mode to be set is not supported */
  else
  {
    /* #210 Return that the tx mode to be set is not supported */
    result = FALSE;
  }
  
  return result;
}
#  endif /* ETHTRCV_30_RTL9000_DEV_ERROR_DETECT */

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_IsCableDiagAvailable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsCableDiagAvailable(
    uint8 TrcvIdx)
{
  boolean result = TRUE;

  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Return that cable diagnostics is available */
  return result;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_IsCableDiagFinished
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
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsCableDiagFinished(
    uint8 TrcvIdx,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal)
{
  boolean result;
  uint16 regVal;
  Std_ReturnType retVal = RetVal;

  /* #10 Read the RTCT control register */
  retVal |= EthTrcv_30_Rtl9000_LL_ReadTrcvRegister(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_A42,
      ETHTRCV_30_RTL9000_REG_OFFS_RTCTCR,
      &regVal);

  /* #20 The RTCT control register returns that RTCT has finished */
  if ((regVal & ETHTRCV_30_RTL9000_REG_RTCTCR_CABLEDIAG_DONE) == ETHTRCV_30_RTL9000_REG_RTCTCR_CABLEDIAG_DONE)
  {
    /* #210 Return that the cable diagnostics has finished */
    result = TRUE;
  }
  /* #30 The RTCT control register returns that RTCT has finished */
  else
  {
    /* #310 Return that the cable diagnostics has not yet finished */
    result = FALSE;
  }


  *ResultPtr = result;
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_IsCableDiagPrepared
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_IsCableDiagPrepared(
    uint8 TrcvIdx,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 No preparation steps necessary */
  *ResultPtr = TRUE;
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_CheckSwReset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_CheckSwReset(
    uint8 TrcvIdx,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal)
{
  boolean result = FALSE;
  Std_ReturnType retVal = RetVal;
  uint16 regVal;

  retVal |= EthTrcv_30_Rtl9000_LL_ReadTrcvRegister(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_0,
      ETHTRCV_30_RTL9000_REG_OFFS_BMCR,
      &regVal);

  /* #10 If the SW-Reset bit in the BMCR is cleared */
  if((regVal & ETHTRCV_30_RTL9000_REG_BMCR_RESET) == 0)
  {
    /* #110 Return that the SW reset is finished */
    result = TRUE;
  }
  
  *ResultPtr = result;
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_GetTransceiverMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_GetTransceiverMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) TrcvModePtr,
    Std_ReturnType RetVal)
{
  uint16 regVal;
  Std_ReturnType retVal = RetVal;
  EthTrcv_ModeType trcvMode = ETHTRCV_MODE_DOWN;

  retVal |= EthTrcv_30_Rtl9000_LL_ReadTrcvRegister(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_0,
      ETHTRCV_30_RTL9000_REG_OFFS_BMCR,
      &regVal);

  /* #10 The Power-down bit is cleared in the BMCR */
  if((regVal & ETHTRCV_30_RTL9000_REG_BMCR_POWER_DOWN) == 0)
  {
    /* #110 Return that the transceiver is in mode ACTIVE */
    trcvMode = ETHTRCV_MODE_ACTIVE;
  }

  *TrcvModePtr = trcvMode;
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_GetLinkState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_GetLinkState(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_LinkStateType, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) LinkStatePtr,
    Std_ReturnType RetVal)
{
  uint16 regVal;
  Std_ReturnType retVal = RetVal;
  EthTrcv_LinkStateType linkState = ETHTRCV_LINK_STATE_DOWN;

  /* #10 Read the BMSR twice (Link State bit is latched low) */
  retVal |= EthTrcv_30_Rtl9000_LL_ReadTrcvRegister(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_0,
      ETHTRCV_30_RTL9000_REG_OFFS_BMSR,
      &regVal);

  retVal |= EthTrcv_30_Rtl9000_LL_ReadTrcvRegister(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_0,
      ETHTRCV_30_RTL9000_REG_OFFS_BMSR,
      &regVal);

  /* #20 The link state bit is set in the BMSR */
  if ((regVal & ETHTRCV_30_RTL9000_REG_BMSR_LINK_STATE) == ETHTRCV_30_RTL9000_REG_BMSR_LINK_STATE)
  {
    /* #210 Return that the link state is ACTIVE */
    linkState = ETHTRCV_LINK_STATE_ACTIVE;
  }

  *LinkStatePtr = linkState;
  return retVal;
}

#  if ( ETHTRCV_30_RTL9000_ENABLE_GET_DUPLEX_MODE == STD_ON )
/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_GetDuplexMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_GetDuplexMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_DuplexModeType, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) DuplexModePtr,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = E_OK;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(RetVal); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Only full duplex is supported */
  *DuplexModePtr = ETHTRCV_DUPLEX_MODE_FULL;

  return retVal;
}
#  endif /* ETHTRCV_30_RTL9000_ENABLE_GET_DUPLEX_MODE */

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_GetPhySignalQualityValueInPercent
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
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_GetPhySignalQualityValueInPercent(
    uint8 TrcvIdx,
    P2VAR(uint8, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_DATA) ResultPtr,
    Std_ReturnType RetVal)
{
  uint16 snrRaw;
  uint8 percent;
  Std_ReturnType                                        retVal                = RetVal;
  uint32                                                signalQualityValueSum = 0;
  EthTrcv_30_Rtl9000_SizeOfSignalQualityBordersType     maxSqiClass           = EthTrcv_30_Rtl9000_GetSizeOfSignalQualityBorders() - 1;
  EthTrcv_30_Rtl9000_SignalQualityBordersIterType       sqiClass;
  EthTrcv_30_Rtl9000_SignalQualityBordersIterType       sqiClassIndex;
  EthTrcv_30_Rtl9000_PhySignalQualityMeanOfEthTrcvType  signalQualityIndex;
  EthTrcv_30_Rtl9000_PhySignalQualityMeanOfEthTrcvType  meanLength;

  /* #10 Initialize the sqiClass with the worst case value in case the read-operation fails */
  sqiClass = 0;

  /* #20 Retrieve the mean length to be used to calculate the average signal quality value */
  meanLength = EthTrcv_30_Rtl9000_GetPhySignalQualityMeanOfEthTrcv(TrcvIdx);

  /* #30 Summarize the data points for the signal quality until the mean length is reached */
  for(signalQualityIndex = 0; signalQualityIndex < meanLength; signalQualityIndex++)
  {
    /* #310 Read the SNR-Register */
    retVal |= EthTrcv_30_Rtl9000_LL_ReadTrcvRegister(
        TrcvIdx,
        ETHTRCV_30_RTL9000_PAGE_NONE,
        ETHTRCV_30_RTL9000_REG_OFFS_SNRR,
        &snrRaw);
    
    /* #320 Sum the signal quality value */ 
    signalQualityValueSum += snrRaw;
  }

  /* #40 Calculate the average of the obtained data points for the signal quality in percent */
  snrRaw = (uint8)(signalQualityValueSum / meanLength);

  /* #50 Map raw value to sqi classification based on RTL9000AA_AN-VB_Datasheet_DRAFT_V1.4_131471 Chapter 7.13.1 */
  for(sqiClassIndex = 0; sqiClassIndex < EthTrcv_30_Rtl9000_GetSizeOfSignalQualityBorders(); sqiClassIndex++)
  {
    if(snrRaw >= EthTrcv_30_Rtl9000_GetSignalQualityBorders(sqiClassIndex))
    {
      sqiClass = sqiClassIndex;
      break;
    }
  }

  /* #60 Calculate rounded percentage */
  percent = (uint8)(((sqiClass * 100 ) + (maxSqiClass / 2)) / maxSqiClass);

  *ResultPtr = percent;
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_RunVendorSpecificInitScripts
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_RunVendorSpecificInitScripts(
    uint8 TrcvIdx)
{
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  /* #10 Nothing to do */
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_EnableConfigAccess
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_EnableConfigAccess(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing to do */
  
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_DisableConfigAccess
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_DisableConfigAccess(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing to do */
  
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_SetTransceiverModeActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetTransceiverModeActive(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 Clear the power-down bit in the BMCR */
  retVal |= EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_0,
      ETHTRCV_30_RTL9000_REG_OFFS_BMCR,
      ETHTRCV_30_RTL9000_REG_BMCR_POWER_DOWN,
      0);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_SetTransceiverModeDown
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetTransceiverModeDown(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 Set the power-down bit in the BMCR */
  retVal |= EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_0,
      ETHTRCV_30_RTL9000_REG_OFFS_BMCR,
      ETHTRCV_30_RTL9000_REG_BMCR_POWER_DOWN,
      ETHTRCV_30_RTL9000_REG_BMCR_POWER_DOWN);

  return retVal;
}

#  if ( ETHTRCV_30_RTL9000_ENABLE_START_AUTO_NEG == STD_ON )
/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_EnableStartAutoNegotiation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_EnableStartAutoNegotiation(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = E_NOT_OK;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(RetVal); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  /* #10 Request not possible */
  return retVal;
}
#  endif /* ETHTRCV_30_RTL9000_ENABLE_START_AUTO_NEG */

#  if ( ETHTRCV_30_RTL9000_ENABLE_GET_BAUD_RATE == STD_ON )
/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_GetBaudRate
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_GetBaudRate(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_BaudRateType, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) BaudRatePtr,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = E_OK;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(RetVal); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Return that the baud rate is 100Mbps */
  *BaudRatePtr = ETHTRCV_BAUD_RATE_100MBIT;
  return retVal;
}
#  endif /* ETHTRCV_30_RTL9000_ENABLE_GET_BAUD_RATE */

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_PrepareSignalQualityMeasurement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_PrepareSignalQualityMeasurement(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 No preparation necessary */
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_SetPhyTestMode
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
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetPhyTestMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTestModeType TestMode,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  uint16 regVal;

  /* #10 The current test mode shall be disabled */
  if(TestMode == ETHTRCV_PHYTESTMODE_NONE)
  {
    /* #110 Resume normal operation */
    retVal |= EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits(
        TrcvIdx,
        ETHTRCV_30_RTL9000_PAGE_0,
        ETHTRCV_30_RTL9000_REG_OFFS_PHYCR,
        ETHTRCV_30_RTL9000_REG_PHYCR_TESTMODE_MASK,
        0);
  }
  /* #20 Test mode 1, 2, 4 or 5 shall be enabled */
  else if((TestMode == ETHTRCV_PHYTESTMODE_1) ||
          (TestMode == ETHTRCV_PHYTESTMODE_2) ||
          (TestMode == ETHTRCV_PHYTESTMODE_4) ||
          (TestMode == ETHTRCV_PHYTESTMODE_5))
  {
    /* #210 Set the test mode in the PHYCR */
    regVal = (uint16)((uint16)TestMode << ETHTRCV_30_RTL9000_REG_OFFS_PHYCR_PHYTESTMODE_LSHIFT);

    retVal |= EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits(
        TrcvIdx,
        ETHTRCV_30_RTL9000_PAGE_0,
        ETHTRCV_30_RTL9000_REG_OFFS_PHYCR,
        ETHTRCV_30_RTL9000_REG_PHYCR_TESTMODE_MASK,
        regVal);
  }
  /* #30 Test mode 3 shall be enabled or another unsupported mode is chosen */
  else
  {
    /* #310 Return E_NOT_OK */
    retVal = E_NOT_OK;
  }
  return retVal;
} /*lint !e438 */

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_SetPhyLoopbackMode
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
 *
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetPhyLoopbackMode(
    uint8 TrcvIdx,
    EthTrcv_PhyLoopbackModeType LoopbackMode,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  uint16 page = 0, reg = 0, mask = 0, val = 0;

  /* #10 Disable all loopback modes */
  retVal |= EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_0,
      ETHTRCV_30_RTL9000_REG_OFFS_BMCR,
      ETHTRCV_30_RTL9000_REG_BMCR_LOOPBACK,
      0);

  retVal |= EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_A43,
      ETHTRCV_30_RTL9000_REG_OFFS_PHYSCR,
      ETHTRCV_30_RTL9000_REG_PHYSCR_MDI_LOOPBACK,
      0);

  retVal |= EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_NONE,
      ETHTRCV_30_RTL9000_REG_OFF_REMOTE_LB,
      ETHTRCV_30_RTL9000_REG_REMOTE_LB_DISABLE_MASK,
      0);

  switch (LoopbackMode) {
  /* #20 Normal mode shall be resumed */
  case ETHTRCV_PHYLOOPBACK_NONE:
    /*  #210 Nothing more to do */
    retVal |= E_OK;
    break;
  /* #30 Internal loopback mode shall be enabled */
  case ETHTRCV_PHYLOOPBACK_INTERNAL:
    /* #310 Set the register and page values to internal loopback */
    page = ETHTRCV_30_RTL9000_PAGE_0;
    reg = ETHTRCV_30_RTL9000_REG_OFFS_BMCR;
    mask = ETHTRCV_30_RTL9000_REG_BMCR_LOOPBACK;
    val = ETHTRCV_30_RTL9000_REG_BMCR_LOOPBACK;
    retVal |= E_OK;
    break;
    /* #40 External loopback mode shall be enabled */
  case ETHTRCV_PHYLOOPBACK_EXTERNAL:
    /* #410 Set the register and page values to external loopback */
    page = ETHTRCV_30_RTL9000_PAGE_A43;
    reg = ETHTRCV_30_RTL9000_REG_OFFS_PHYSCR;
    mask = ETHTRCV_30_RTL9000_REG_PHYSCR_MDI_LOOPBACK;
    val = ETHTRCV_30_RTL9000_REG_PHYSCR_MDI_LOOPBACK;
    retVal |= E_OK;
    break;
  /* #50 Remote loopback mode shall be enabled */
  case ETHTRCV_PHYLOOPBACK_REMOTE:
    /* #510 Set the register and page values to remote loopback */
    page = ETHTRCV_30_RTL9000_PAGE_NONE;
    reg = ETHTRCV_30_RTL9000_REG_OFF_REMOTE_LB;
    mask = ETHTRCV_30_RTL9000_REG_REMOTE_LB_ENABLE;
    val = ETHTRCV_30_RTL9000_REG_REMOTE_LB_ENABLE;
    retVal |= E_OK;
    break;
  /* #60 An unsupported loopback mode shall be enabled */
  default:
    /* #610 Return E_NOT_OK */
    retVal |= E_NOT_OK;
  }

  /* #70 Internal, external or remote loopback shall be enabled */
  if (((LoopbackMode == ETHTRCV_PHYLOOPBACK_INTERNAL) ||
       (LoopbackMode == ETHTRCV_PHYLOOPBACK_EXTERNAL) ||
       (LoopbackMode == ETHTRCV_PHYLOOPBACK_REMOTE))  &&
       (retVal == E_OK))
  {
    /* #710 Set the previously prepared values on the transceiver hardware */
    retVal |= EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits(TrcvIdx, page, reg, mask, val);
  }

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_FinalizeSignalQualityMeasurement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_FinalizeSignalQualityMeasurement(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing more to do */
  
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_PrepareCableDiag
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_PrepareCableDiag(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  /* #10 No preparation necessary */
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_PrepareCableDiag
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_EnableDiagnosticSequence(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Set the cable diagnostic enable bit in the RTCT control register */
  retVal |= EthTrcv_30_Rtl9000_LL_TrcvRegisterUpdateBits(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_A42,
      ETHTRCV_30_RTL9000_REG_OFFS_RTCTCR,
      ETHTRCV_30_RTL9000_REG_RTCTCR_CABLEDIAG_ENABLE,
      ETHTRCV_30_RTL9000_REG_RTCTCR_CABLEDIAG_ENABLE);
  
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_CheckCableDiagResult
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
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_CheckCableDiagResult(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_CableDiagResultType, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) CableDiagResultPtr,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  uint16 cableStatus;
  EthTrcv_CableDiagResultType cableDiagResult = ETHTRCV_CABLEDIAG_ERROR;

  /* #10 Read the cable length status register */
  retVal |= EthTrcv_30_Rtl9000_WriteTrcvReg(
      TrcvIdx,
      ETHTRCV_30_RTL9000_REG_OFFS_PAGSR,
      ETHTRCV_30_RTL9000_PAGE_A43);

  retVal |= EthTrcv_30_Rtl9000_LL_ReadTrcvRegister(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_NONE,
      ETHTRCV_30_RTL9000_REG_OFFS_CH_STATUS_CABLE_LENGTH,
      &cableStatus);

    cableStatus = (uint16)(cableStatus >> ETHTRCV_30_RTL9000_CABLE_STAT_RSHIFT);

    switch (cableStatus)
    {
      /* #20 The cable length status register indicates that the cable diagnostic result is OK */
      case ETHTRCV_30_RTL9000_CABLE_STAT_NORMAL:
        /* #210 Return that the cable diagnostic result is OK */
        cableDiagResult = ETHTRCV_CABLEDIAG_OK;
        break;
      /* #30 The cable length status register indicates that the cable diagnostic result is a short was detected */
      case ETHTRCV_30_RTL9000_CABLE_STAT_SHORT:
        /* #310 Return that the cable diagnostic result is SHORT */
        cableDiagResult = ETHTRCV_CABLEDIAG_SHORT;
        break;
      /* #40 The cable length status register indicates that the cable diagnostic result is a open was detected */
      case ETHTRCV_30_RTL9000_CABLE_STAT_OPEN:
        /* #410 Return that the cable diagnostic result is OPEN */
        cableDiagResult = ETHTRCV_CABLEDIAG_OPEN;
        break;
      /* #50 The cable length status register indicates that the cable diagnostic failed */
      default:
        /* #510 Return that the cable diagnostic result ERROR */
        break;
    }

  *CableDiagResultPtr = cableDiagResult;
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_AdditionalStepsAfterCableDiag
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_AdditionalStepsAfterCableDiag(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing more to do */
  
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_SetPhyTxMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_SetPhyTxMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTxModeType TxMode,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* No support of other Tx-Modes than NORMAL */
  if (TxMode != ETHTRCV_PHYTXMODE_NORMAL)
  {
    retVal = E_NOT_OK;
  }

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_MainFunctionLinkHandling
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_MainFunctionLinkHandling(
    uint8 TrcvIdx)
{
  ETHTRCV_30_RTL9000_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Nothing to do */
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_ReadIdentifier1Register
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_ReadIdentifier1Register(
    uint8 TrcvIdx,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) RegValPtr,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 Read the first identifier register */
  retVal |= EthTrcv_30_Rtl9000_LL_ReadTrcvRegister(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_0,
      ETHTRCV_30_RTL9000_REG_OFFS_PHYIDR1,
      RegValPtr);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_ReadIdentifier2Register
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_ReadIdentifier2Register(
    uint8 TrcvIdx,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_RTL9000_APPL_VAR) RegValPtr,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 Read the second identifier register */
  retVal |= EthTrcv_30_Rtl9000_LL_ReadTrcvRegister(
      TrcvIdx,
      ETHTRCV_30_RTL9000_PAGE_0,
      ETHTRCV_30_RTL9000_REG_OFFS_PHYIDR2,
      RegValPtr);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Rtl9000_LL_Erratum2
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
ETHTRCV_30_RTL9000_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_LL_Erratum2(
    uint8 TrcvIdx)
{
  Std_ReturnType retVal = E_OK;
  EthTrcv_30_Rtl9000_Erratum2DataIterType idx;


  for(idx = 0; idx < EthTrcv_30_Rtl9000_GetSizeOfErratum2Data(); idx++)
  {
    /* #10 Retrieve the address, value and operation type to be performed */
    EthTrcv_30_Rtl9000_OpTypeOfErratum2DataType opType =
        EthTrcv_30_Rtl9000_GetOpTypeOfErratum2Data(idx);
    EthTrcv_30_Rtl9000_RegAddrOfErratum2DataType regAddr =
        EthTrcv_30_Rtl9000_GetRegAddrOfErratum2Data(idx);
    EthTrcv_30_Rtl9000_RegValOfErratum2DataType regVal =
        EthTrcv_30_Rtl9000_GetRegValOfErratum2Data(idx);

    if(opType == ETHTRCV_30_RTL9000_ERRATUM2_READ_OP_OPTYPEOFERRATUM2DATA)
    {
      /* #20 If the register must be read / polled */
      EthTrcv_30_Rtl9000_SoftResetWaitCyclesOfEthTrcvType loopCount;

      for(loopCount = 0; loopCount < EthTrcv_30_Rtl9000_GetSoftResetWaitCyclesOfEthTrcv(TrcvIdx); loopCount++) /*lint !e522 */
      {
        /* #210 Read the register until the generated value is presented or a timeout occurs */
        uint16 readRegVal;
        retVal |= EthTrcv_30_Rtl9000_Internal_ReadTrcvReg(TrcvIdx, (uint8)regAddr, &readRegVal);

        if(readRegVal == regVal)
        {
          break;
        }
      }

      if(loopCount == EthTrcv_30_Rtl9000_GetSoftResetWaitCyclesOfEthTrcv(TrcvIdx))
      {
        retVal = E_NOT_OK;
      }
    }
    /* #30 If the register must be written */
    else if(opType == ETHTRCV_30_RTL9000_ERRATUM2_WRITE_OP_OPTYPEOFERRATUM2DATA)
    {
      /* #310 Write the generated register value to the generated register address */
      retVal |= EthTrcv_30_Rtl9000_Internal_WriteTrcvReg(TrcvIdx, (uint8)regAddr, (uint16)regVal);
    }
    else
    {
      /* #40 Other optypes are currently not supported */
    }
  }

  return retVal;
}

# endif /* ETHTRCV_30_RTL9000_UNIT_TEST */

# define ETHTRCV_30_RTL9000_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

#endif /* ETHTRCV_30_RTL9000_LL_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Rtl9000_LL.h
 *********************************************************************************************************************/
