/* Kernbauer Version: 1.16 Konfiguration: DrvSbc_Fs85Asr Erzeugungsgangnummer: 33 */

/*!********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Sbc_30_Fs85.h
 *        \brief  System Basis Chip Implementation
 *
 *      \details  This file contains public definitions of this SBC driver instance.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2018-10-16  visjan  STORYC-7107   Initial implementation
 *  01.00.01  2019-01-07  visjan  STORYC-7371   Support Safe-BSW
 *  01.00.02  2019-03-05  visjan  ESCAN00102049 Unintended reset after initialization
 *  01.01.00  2020-11-19  fbatz   CTM-2393      Migrate to MISRA C:2012
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CORE REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id      Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  00.00.00  2014-05-07  vistvi                 Initial implementation
 *  01.00.00  2015-03-31  visrse                 Initial implementation part 2
 *  01.01.00  2015-03-31  visrse  ESCAN00085409  Implementation extension and general improvements
 *  02.00.00  2015-09-29  visrse  ESCAN00085156  FEAT-1527: SafeBSW Step 3
 *  02.01.00  2015-09-29  visrse  ESCAN00087990  Sbc driver optimization for R15
 *  02.01.01  2016-06-22  visrse  ESCAN00090608  Sbc raises a DET error "SBC_E_INVALID_STATE" if PN is enabled
 *  02.01.02  2016-06-22  visrse  ESCAN00091500  Use Sbc_SpiDataWidth as type for SPI command value
 *  02.01.03  2019-05-06  virmid  ESCAN00101347  SBC peripherals cannot operate after initialization
 *  02.02.00  2019-12-16  visjan  CAN-707        Support PostbuildSelectable
 *  02.03.00  2020-05-22  virmid  CTM-493        MISRA-C:2012 compliance
 *  02.03.01  2020-06-24  visjan  CAN-1604       Add MISRA-C:2012 justifications for hw specific scenarios
 *  02.03.02  2020-11-03  visjan  CAN-1957       Improvements in justification comments
 *********************************************************************************************************************/

#if !defined(SBC_30_FS85_H)
#define SBC_30_FS85_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Sbc_30_Fs85_Cfg.h"
#include "Spi.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/



#if (SBC_30_FS85_MAX_NUMBER_OF_WDG != 0u)
# define SBC_30_FS85_ENABLE_WDG
#else
# define SBC_30_FS85_DISABLE_WDG
#endif

/* ----- Component version information (decimal version of ALM implementation package) ----- */
#define SBC_30_CORE_SW_MAJOR_VERSION                   (2u)
#define SBC_30_CORE_SW_MINOR_VERSION                   (3u)
#define SBC_30_CORE_SW_PATCH_VERSION                   (2u)

/* Vendor and module identification */
#define SBC_30_FS85_VENDOR_ID                            (30u)
/* According to AUTOSAR_TR_BSWModuleList.pdf (v1.6.0) the Module ID for Complex Drivers is 255 */
#define SBC_30_FS85_MODULE_ID                            (0xFFu)

/* AUTOSAR Software specification version information */
#define SBC_30_FS85_AR_RELEASE_MAJOR_VERSION             (0x04u)
#define SBC_30_FS85_AR_RELEASE_MINOR_VERSION             (0x00u)
#define SBC_30_FS85_AR_RELEASE_REVISION_VERSION          (0x03u)

/* Version of the API. This version is incremented when the API becomes incompatible. */
#define SBC_30_FS85_API_VERSION                          (0x0100u)

#if !defined(SBC_30_FS85_INSTANCE_ID_DET) /* COV_SBC_SINGLE_INSTANCE_API */
# define SBC_30_FS85_INSTANCE_ID_DET                     (0x00u)
#endif

/*
 * Compatibility defines for the single instance API
 */
#if (SBC_30_FS85_SINGLE_INSTANCE_API == STD_ON) /* COV_SBC_SINGLE_INSTANCE_API */
# define Sbc_InitMemory                    Sbc_30_Fs85_InitMemory
# define Sbc_Init                          Sbc_30_Fs85_Init
# define Sbc_GetVersionInfo                Sbc_30_Fs85_GetVersionInfo
# define Sbc_SetMode                       Sbc_30_Fs85_SetMode
# define Sbc_GetStatus                     Sbc_30_Fs85_GetStatus
# define Sbc_ClearEvents                   Sbc_30_Fs85_ClearEvents
# define Sbc_AccessRegister                Sbc_30_Fs85_AccessRegister
# define Sbc_CanTrcv_ReadStatus            Sbc_30_Fs85_CanTrcv_ReadStatus
# define Sbc_CanTrcv_ClearEvents           Sbc_30_Fs85_CanTrcv_ClearEvents
# define Sbc_CanTrcv_SetMode               Sbc_30_Fs85_CanTrcv_SetMode
# define Sbc_CanTrcv_WritePnConfig         Sbc_30_Fs85_CanTrcv_WritePnConfig
# define Sbc_CanTrcv_EnableSelectiveWakeup Sbc_30_Fs85_CanTrcv_EnableSelectiveWakeup
# define Sbc_LinTrcv_SetMode               Sbc_30_Fs85_LinTrcv_SetMode
# define Sbc_LinTrcv_ReadStatus            Sbc_30_Fs85_LinTrcv_ReadStatus
# define Sbc_LinTrcv_ClearEvents           Sbc_30_Fs85_LinTrcv_ClearEvents
# define Sbc_Wdg_SetMode                   Sbc_30_Fs85_Wdg_SetMode
# define Sbc_Wdg_Trigger                   Sbc_30_Fs85_Wdg_Trigger
#endif

#if !defined(Sbc_SpiDataWidth) /* COV_SBC_SPI_COMPATIBILITY */
# define Sbc_SpiDataWidth uint16
#endif


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

#define SBC_30_FS85_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Sbc_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Function for *_INIT_*-variable initialization
 *  \details     Service to initialize module global variables at power up. This function can be used to initialize the
 *               variables in *_INIT_* sections in case they are not initialized by the startup code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module must not be initialized.
 *  \trace       CREQ-103749
 *********************************************************************************************************************/
FUNC(void, SBC_30_FS85_CODE) Sbc_30_Fs85_InitMemory(void);

/**********************************************************************************************************************
 *  Sbc_Init()
 *********************************************************************************************************************/
/*! \brief       Initialization function
 *  \details     The API initializes each configured device. For each device
 *               all corresponding status variables are set to an initialized state. The API then initializes the
 *               underlying hardware device and sets all embedded peripherals to a safe state, e.g. a state that does
 *               not influence any attached device or bus.
 *               If the underlying hardware device has detected a Power-on-Reset (POR) event, the API reports the event
 *               to the EcuM by calling EcuM_SetWakeupEvent with the corresponding configured wake-up source.
 *               If any error occurs during the initialization the module remains in an uninitialized state.
 *  \param[in]   ConfigPtr   Configuration structure for initializing the module.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Interrupts have to be disabled.
 *               The module has to be uninitialized.
 *               The function Sbc_InitMemory must be called before the function Sbc_Init can be called.
 *               This function must be called before any other service functionality of the Sbc driver.
 *               The SPI driver must be initialized.
 *  \trace       CREQ-103749
 *  \note        This API must not be interrupted by any other API of the SBC module.
 *********************************************************************************************************************/
FUNC(void, SBC_30_FS85_CODE) Sbc_30_Fs85_Init(P2CONST(Sbc_30_Fs85_ConfigType, AUTOMATIC, SBC_30_FS85_PBCFG) ConfigPtr);

#if (SBC_30_FS85_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Sbc_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     This API returns version information, vendor ID and AUTOSAR module ID of the component.
 *               The versions are decimal-coded.
 *  \param[out]  versioninfo             Pointer to where to store the version information
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Output parameter must not be NULL.
 *  \trace       CREQ-103784
 *********************************************************************************************************************/
FUNC(void, SBC_30_FS85_CODE) Sbc_30_Fs85_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, SBC_30_FS85_APPL_DATA) versioninfo);
#endif

/**********************************************************************************************************************
 *  Sbc_SetMode()
 *********************************************************************************************************************/
/*! \brief       Changes the mode of the SBC module
 *  \details     This API changes the system mode of the SBC identified by SBC id to the given mode.
 *  \param[in]   id    Identifies the SBC instance that shall change its mode.
 *  \param[in]   mode  Specifies the mode that the SBC instance shall be switched to.
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         The module must be initialized.
 *  \trace       CREQ-103748, DSGN-SbcDiag2048, DSGN-SbcDiag1953
 *  \note        When the mode of the hardware could not be changed successfully the internal (software) mode remains
 *               unchanged and the mode of the hardware is undefined.
 *               In order to query the actual operation mode of the underlying hardware the API Sbc_GetStatus() must be used.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_30_Fs85_SetMode(Sbc_IdType id, Sbc_SystemModeType mode);

/**********************************************************************************************************************
 *  Sbc_GetStatus()
 *********************************************************************************************************************/
/*! \brief       Reads the current system status of the SBC
 *  \details     This API queries the current state from the underlying hardware and writes it to the object that is
 *               referred by parameter status.
 *               Note: If E_NOT_OK is returned the value of status is undefined.
 *  \param[in]   id      Identifies the SBC instance that shall be queried.
 *  \param[out]  status  Pointer to the object where the API should store the current status, pointer must be valid.
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         The module must be initialized.
 *               Output parameter must not be NULL.
 *  \trace       CREQ-105542
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_30_Fs85_GetStatus(Sbc_IdType id, P2VAR(Sbc_SystemStatusType, AUTOMATIC, SBC_30_FS85_APPL_DATA) status);

/**********************************************************************************************************************
 *  Sbc_ClearEvents()
 *********************************************************************************************************************/
/*! \brief       Clears pending events from the SBC
 *  \details     This API clears the given events from SBC hardware. Events are cleared by writing "1" to them.
 *  \param[in]   id     Identifies the SBC instance whose events should be cleared.
 *  \param[in]   events The events that should be cleared.
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         The module must be initialized.
 *  \trace       CREQ-105555
 *  \note        Only flags that are set in the given parameter "events" are cleared.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_30_Fs85_ClearEvents(Sbc_IdType id, Sbc_SystemEventType events);

/**********************************************************************************************************************
 *  Sbc_AccessRegister()
 *********************************************************************************************************************/
/*! \brief       Access of SBC registers
 *  \details     The API allows the application to get access to specific SBC registers.
 *               Please refer to manual of semiconductor manufacturer to get knowledge about the structure of commands.
 *  \param[in]   id          Identifies the SBC instance whose register shall be accessed.
 *  \param[in]   spiCommand  The complete SPI value that can be directly written to MOSI register.
 *  \param[out]  spiAnswer   The complete SPI value that is received on MISO register. SpiAnswer must be a valid pointer.
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         The module must be initialized.
 *  \trace       CREQ-105527
 *  \note        Please note that it is optional to include security or parity bits in the SPI command.
 *               They are recomputed and inserted by the Sbc driver itself.
 *               Be careful in usage of this API because manual access to SBC register can influence the behaviour
 *               of the SBC driver in a not wanted manner.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_30_Fs85_AccessRegister(Sbc_IdType id, Sbc_SpiDataWidth spiCommand, P2VAR(Sbc_SpiDataWidth, AUTOMATIC, SBC_30_FS85_APPL_DATA) spiAnswer);



#if defined(SBC_30_FS85_ENABLE_WDG)
/**********************************************************************************************************************
 *  Sbc_Wdg_SetMode()
 *********************************************************************************************************************/
/*! \brief       Changes the mode of the watchdog to the given mode.
 *  \details     The API changes the operation mode of the watchdog to either OFF, SLOW or FAST.
 *               The settings of each mode depend on hardware and configuration.
 *               If the hardware successfully changed the mode the new mode is stored in the internal status variable.
 *  \param[in]   id       Identifies the SBC instance and peripheral that shall change its mode.
 *  \param[in]   mode     The desired mode.
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      SBC_30_FS85_ENABLE_WDG
 *  \pre         The module must be initialized.
 *  \trace       CREQ-105529, DSGN-SbcDiag2044
 *  \note        When the mode of the hardware could not be changed successfully the internal (software) mode remains
 *               unchanged and the mode of the hardware is undefined.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_30_Fs85_Wdg_SetMode(Sbc_PeripheralIdType id, Sbc_WdgModeType mode);

/**********************************************************************************************************************
 *  Sbc_Wdg_Trigger()
 *********************************************************************************************************************/
/*! \brief       Triggers the watchdog peripheral
 *  \details     The API triggers the hardware watchdog.
 *               The API has to be called according to the timing requirements of the selected watchdog mode.
 *  \param[in]   id       Identifies the SBC instance and peripheral that shall be triggered.
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      SBC_30_FS85_ENABLE_WDG
 *  \pre         The module must be initialized.
 *  \trace       CREQ-105530
 *  \note        Must not be interrupted by any other WDG call.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_30_Fs85_Wdg_Trigger(Sbc_PeripheralIdType id);
#endif /* SBC_ENABLE_WDG */

#define SBC_30_FS85_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ----- Component version information (decimal version of ALM implementation package) ----- */
#define SBC_30_FS85_SW_MAJOR_VERSION                    (1u)
#define SBC_30_FS85_SW_MINOR_VERSION                    (1u)
#define SBC_30_FS85_SW_PATCH_VERSION                    (0u)

/*!
 * \exclusivearea SBC_EXCLUSIVE_AREA_0
 * Ensures consistency while modifying the System status.
 * \protects Sbc_SystemStatus
 * \usedin Sbc_SetMode, Sbc_GetStatus, Sbc_ClearEvents
 * \exclude Sbc_SetMode, Sbc_GetStatus, Sbc_ClearEvents (Modification of Sbc_SystemStatus).
 * \length SHORT Update of Sbc_SystemStatus.
 * \endexclusivearea
 *
 * \exclusivearea SBC_EXCLUSIVE_AREA_1
 * Ensures consistency while modifying the CanTrcv status.
 * \protects Sbc_CanTrcvStatus
 * \usedin Sbc_CanTrcv_ReadStatus, Sbc_CanTrcv_ClearEvents, Sbc_CanTrcv_SetMode, Sbc_CanTrcv_WritePnConfig, Sbc_CanTrcv_EnableSelectiveWakeup
 * \exclude Sbc_CanTrcv_ReadStatus, Sbc_CanTrcv_ClearEvents, Sbc_CanTrcv_SetMode, Sbc_CanTrcv_WritePnConfig, Sbc_CanTrcv_EnableSelectiveWakeup (Modification of Sbc_CanTrcvStatus).
 * \length SHORT Update of Sbc_CanTrcvStatus.
 * \endexclusivearea
 *
 * \exclusivearea SBC_EXCLUSIVE_AREA_2
 * Ensures consistency while modifying the LinTrcv status.
 * \protects Sbc_LinTrcvStatus
 * \usedin Sbc_LinTrcv_ReadStatus, Sbc_LinTrcv_ClearEvents, Sbc_LinTrcv_SetMode
 * \exclude Sbc_LinTrcv_ReadStatus, Sbc_LinTrcv_ClearEvents, Sbc_LinTrcv_SetMode (Modification of Sbc_LinTrcvStatus).
 * \length SHORT Update of Sbc_LinTrcvStatus.
 * \endexclusivearea
 */

/*!
 * \exclusivearea SBC_EXCLUSIVE_AREA_3
 * Ensures consistent hardware access.
 * \protects SPI data transfer
 * \usedin Sbc_Ll_RwRegister
 * \exclude Other calls to SPI module.
 * \length LONG Call to SPI module.
 * \endexclusivearea
 */ 

#endif  /* SBC_H */

/**********************************************************************************************************************
 *  END OF FILE: Sbc.h
 *********************************************************************************************************************/
