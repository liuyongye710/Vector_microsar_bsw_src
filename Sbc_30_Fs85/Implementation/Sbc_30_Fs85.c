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
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  Sbc_30_Fs85.c
 *        \brief  System Basis Chip Implementation
 *
 *      \details  This file contains the implementation of a hardware specific SBC module.
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

/* Defined only in Sbc.c */
#define SBC_SOURCE
#define SBC_INTERNAL
#define SBC_30_FS85_INTERNAL

/*********************************************************************************************************************
 *  INCLUDES
 ********************************************************************************************************************/


#include "Sbc_30_Fs85.h"
/* PRQA L:Sbc_Include_Tag */

#include "EcuM.h"
#include "SchM_Sbc_30_Fs85.h"

#if (SBC_30_FS85_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/*********************************************************************************************************************
 *  VERSION CHECK
 ********************************************************************************************************************/

/* Check the version of Sbc header file */
#if (  (SBC_30_CORE_SW_MAJOR_VERSION != (2u)) \
    || (SBC_30_CORE_SW_MINOR_VERSION != (3u)) \
    || (SBC_30_CORE_SW_PATCH_VERSION != (2u)) )
 #error "Vendor specific version numbers of Sbc.c and Sbc.h are inconsistent."
#endif

/* Check the version of the configuration header file */
#if ( SBC_30_FS85_CFG_BASE_COMPAT_VERSION != 0x0102u )
 #error "The configuration data contained in Sbc_30_Fs85_Cfg.h is not compatible to this implementation."
#endif


/*********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Controls the scope of local variables. By default, internal variables are static. */
#if !defined(SBC_30_FS85_LOCAL) /* COV_SBC_LOCAL_SCOPE */
# define SBC_LOCAL static
#else
# define SBC_LOCAL SBC_30_FS85_LOCAL
#endif

#if defined(SBC_30_FS85_LOCAL_INLINE) /* COV_SBC_LOCAL_SCOPE */
# define SBC_LOCAL_INLINE SBC_30_FS85_LOCAL_INLINE
#else
# define SBC_LOCAL_INLINE LOCAL_INLINE
#endif

/*********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/* PRQA S 3453 Sbc_LocalFunctionMacros_Tag */ /* MD_MSR_FctLikeMacro */

/* Macros to access the configuration data */
/* Retrieves the number of configured SBC devices */
#define Sbc_Cfg_GetNumberOfDevices()              (SBC_30_FS85_NUMBER_OF_DEVICES)

/* Retrieves the number of CanTrcv for a given SBC device */
#define Sbc_Cfg_GetNumberOfCanTrcv(dId)           (Sbc_30_Fs85_GetNumberOfCanTrcvOfDeviceConfiguration(dId))

/* Retrieves the number of LinTrcv for a given SBC device */
#define Sbc_Cfg_GetNumberOfLinTrcv(dId)           (Sbc_30_Fs85_GetNumberOfLinTrcvOfDeviceConfiguration(dId))

/* Retrieves the number of Wdg for a given SBC device */
#define Sbc_Cfg_GetNumberOfWdg(dId)               (Sbc_30_Fs85_GetNumberOfWdgOfDeviceConfiguration(dId))

/* Retrieves the wake-up source of POR for a given SBC device */
#define Sbc_Cfg_GetWuSrcPor(dId)                  (Sbc_30_Fs85_GetWuSrcPorOfDeviceConfiguration(dId))

/* Retrieves a index to the watchdog config */
#define Sbc_Cfg_GetWdgConfigIdx(dId, pId)         (Sbc_30_Fs85_GetWdgConfigStartIdxOfDeviceConfiguration(dId) + (pId))

/* Retrieves a index to the CanTrcv config */
#define Sbc_Cfg_GetCanTrcvConfigIdx(dId, pId)     (Sbc_30_Fs85_GetCanTrcvConfigStartIdxOfDeviceConfiguration(dId) + (pId))

/* Retrieves a index to the LinTrcv config */
#define Sbc_Cfg_GetLinTrcvConfigIdx(dId, pId)     (Sbc_30_Fs85_GetLinTrcvConfigStartIdxOfDeviceConfiguration(dId) + (pId))

/* Retrieves a index to the CanTrcv PN config */
#define Sbc_Cfg_GetCanTrcvPnConfigIdx(dId, pId)   (Sbc_30_Fs85_GetCanTrcvPnConfigIdxOfCanTrcvConfig( Sbc_Cfg_GetCanTrcvConfigIdx(dId, pId) ))

/* Retrieves the initial watchdog mode */
#define Sbc_Cfg_GetWdgInitialMode(dId, pId)       (Sbc_30_Fs85_GetWdgInitModeOfWdgConfig(Sbc_Cfg_GetWdgConfigIdx(dId, pId)))


/* Macros to access runtime data */
/* Access to the system status of the given device */
#define Sbc_Rt_GetSystemStatus(dId)           (Sbc_SystemStatus[dId])

/* Access to the CanTrcv status of the given device */
#define Sbc_Rt_GetCanTrcvStatus(dId, pId)     (Sbc_CanTrcvStatus[dId][pId])

/* Access to the LinTrcv status of the given device */
#define Sbc_Rt_GetLinTrcvStatus(dId, pId)     (Sbc_LinTrcvStatus[dId][pId])

/* Get the Wdg mode of the given device */
#define Sbc_Rt_GetWdgMode(dId, pId)           (Sbc_WdgMode[dId][pId])

/* Set the Wdg mode of the given device */
#define Sbc_Rt_SetWdgMode(dId, pId, newval)   (Sbc_WdgMode[dId][pId] = (newval))


/* Status handling */
/* Updates the status val by clearing the mask and writing the new value */

#define Sbc_UpdateStatusFlags(val, newval)            (val)->Events |= (newval).Events; \
                                                      (val)->States  = (newval).States; \
                                                      (val)->Mode    = (newval).Mode

/* Resets a bit in flags if the corresponding flag in wflags is set to 1 */
#define Sbc_ClearEventFlags(flags, wflags)            ( (flags)->Events &= (Sbc_CanTrcvEventType)(~(wflags)) )

/* Macros for ID handling */
/* Create an SbcId using the given dId and pId */
#define Sbc_MakeId(dId, pId)            ( (uint16)( ((dId) & 0xFFFu) << 4u ) | ( (pId) & 0xFu ) )

/* Retrieve the Device Id from a given Id */
#define Sbc_GetDeviceIndex(id)          ( (id) >> 4u )

/* Retrieve the Peripheral Id from a given Id */
#define Sbc_GetPeriphalIndex(id)        ( (id)  & 0xFu )

/* Used for DET checks */

/* Checks if the Module is initialized */
#define Sbc_IsModuleInitialized()         ( Sbc_ModuleInitialized == SBC_INIT )

/* Checks if the SBC ID is valid */
#define Sbc_IsIdValid(id)             ( (Sbc_GetDeviceIndex(id) < Sbc_Cfg_GetNumberOfDevices()) && \
                                        (Sbc_GetPeriphalIndex(id) == 0u) )

/* Checks if the CanTrcv ID is valid */
#define Sbc_IsCanTrcvIdValid(id)   ( (Sbc_GetDeviceIndex(id) < Sbc_Cfg_GetNumberOfDevices()) && \
                                     (Sbc_GetPeriphalIndex(id) < Sbc_Cfg_GetNumberOfCanTrcv(Sbc_GetDeviceIndex(id))) && \
                                     (Sbc_GetPeriphalIndex(id) < SBC_30_FS85_MAX_NUMBER_OF_CANTRCV) )

/* Checks if the LinTrcv ID is valid */
#define Sbc_IsLinTrcvIdValid(id)   ( (Sbc_GetDeviceIndex(id) < Sbc_Cfg_GetNumberOfDevices()) && \
                                     (Sbc_GetPeriphalIndex(id) < Sbc_Cfg_GetNumberOfLinTrcv(Sbc_GetDeviceIndex(id))) && \
                                     (Sbc_GetPeriphalIndex(id) < SBC_30_FS85_MAX_NUMBER_OF_LINTRCV) )

/* Checks if the Wdg ID is valid */
#define Sbc_IsWdgIdValid(id)   ( (Sbc_GetDeviceIndex(id) < Sbc_Cfg_GetNumberOfDevices()) && \
                                 (Sbc_GetPeriphalIndex(id) < Sbc_Cfg_GetNumberOfWdg(Sbc_GetDeviceIndex(id))) && \
                                 (Sbc_GetPeriphalIndex(id) < SBC_30_FS85_MAX_NUMBER_OF_WDG) )

/* Checks if the System Mode is in range */
#define Sbc_IsSysModeValid(mode)      ( ((mode) >= SBC_SYS_MODE_NORMAL) && ((mode) <= SBC_SYS_MODE_SLEEP) )

/* Checks if the CanTrcv Mode is in range */
#define Sbc_IsCanTrcvModeValid(mode)  ( ((mode) >= SBC_CANTRCV_MODE_NORMAL) && ((mode) <= SBC_CANTRCV_MODE_STANDBY) )

/* Checks if the LinTrcv Mode is in range */
#define Sbc_IsLinTrcvModeValid(mode)  ( ((mode) >= SBC_LINTRCV_MODE_NORMAL) && ((mode) <= SBC_LINTRCV_MODE_STANDBY) )

/* Checks if the Wdg Mode is in range */
#define Sbc_IsWdgModeValid(mode)      ( ((mode) >= SBC_WDG_MODE_OFF) && ((mode) <= SBC_WDG_MODE_FAST) )

/* Checks if the pointer is valid */
#define Sbc_IsPtrValid(ptr)           ( (ptr) != NULL_PTR )

/* PRQA S 0342 Sbc_GlueOperator_Tag */ /* MD_MSR_Rule20.10_0342 */
/* Enter a critical area */
#define Sbc_EnterCritical(s) SchM_Enter_Sbc_30_Fs85_##s()
/* Leave a critical area */
#define Sbc_LeaveCritical(s) SchM_Exit_Sbc_30_Fs85_##s()
/* PRQA L:Sbc_GlueOperator_Tag */

/* PRQA L:Sbc_LocalFunctionMacros_Tag */


/*********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/*********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define SBC_30_FS85_START_SEC_VAR_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
/* Initialization state of the module */
SBC_LOCAL VAR(uint8, SBC_30_FS85_VAR_INIT) Sbc_ModuleInitialized = SBC_UNINIT;
#endif

#define SBC_30_FS85_STOP_SEC_VAR_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define SBC_30_FS85_START_SEC_VAR_NOINIT_SAFE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* for SafeBSW the variables must be linked to a memory section that is protected from QM software access */

/* Stores the current System Status of the SBC. The values are updated each time they are read. */
SBC_LOCAL VAR(Sbc_SystemStatusType, SBC_30_FS85_VAR_NOINIT) Sbc_SystemStatus[SBC_30_FS85_NUMBER_OF_DEVICES];

#if defined(SBC_30_FS85_ENABLE_WDG)
/* Stores the current Mode of the Wdg. */
SBC_LOCAL VAR(Sbc_WdgModeType, SBC_30_FS85_VAR_NOINIT) Sbc_WdgMode[SBC_30_FS85_NUMBER_OF_DEVICES][SBC_30_FS85_MAX_NUMBER_OF_WDG];

# if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
/* This variable must be written in Sbc_Wdg_Trigger function to protect against Wrong Caller */
SBC_LOCAL VAR(uint32, SBC_30_FS85_VAR_NOINIT) Sbc_WdgTriggerFlag[SBC_30_FS85_NUMBER_OF_DEVICES][SBC_30_FS85_MAX_NUMBER_OF_WDG];  /* PRQA S 3218 */ /* MD_Sbc_3218 */

# endif
#endif

#define SBC_30_FS85_STOP_SEC_VAR_NOINIT_SAFE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define SBC_30_FS85_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */



#if (SBC_30_FS85_USE_INIT_POINTER == STD_ON) /* COV_SBC_LL_POSTBUILD_SELECTABLE */
/* In the following variable the configuration is stored during the initialization of the SBC driver in case of a Post-build  selectable configuration. */
SBC_LOCAL P2CONST(Sbc_30_Fs85_ConfigType, SBC_30_FS85_VAR_NOINIT, SBC_30_FS85_PBCFG) Sbc_30_Fs85_ConfigDataPtr;
#endif

#define SBC_30_FS85_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


/*********************************************************************************************************************
 *  LOW LEVEL FUNCTION
 *********************************************************************************************************************/
#define SBC_30_FS85_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Sbc_Ll_InitDevice()
 *********************************************************************************************************************/
/*! \brief       Initialize the SBC hardware identified by deviceID dId.
 *  \details     Switches the SBC Mode to NORMAL and the peripherals to an initialized mode that does not affect bus
 *               communication. The watchdog could be enabled after this API returns.
 *               The following events shall be held pending even if they occurred prior to the initialization:
 *               - POR
 *               - Peripheral Wakeups (WUP/WUF)
 *  \param[in]   dId  Identifies the device id, dId must be a valid value.
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_InitDevice(Sbc_IdType dId);

/**********************************************************************************************************************
 *  Sbc_Ll_Sys_CanSetMode()
 *********************************************************************************************************************/
/*! \brief       Returns whether the System Mode can be changed.
 *  \details     Checks if the system mode of the SBC that is identified by the given dId can be changed to the given
 *               mode.
 *               The API checks if the mode transition is supported by the hardware and whether the peripherals
 *               are in the expected state.
 *  \param[in]   dId   Identifies the device id, dId must be a valid value.
 *  \param[in]   mode  The mode that shall be reached.
 *  \return      E_OK if it is possible to change the mode. \n
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \note        If this API returns E_OK the module expects that the call to Sbc_Ll_Sys_SetMode() fails only if the
 *               module is not possible to communicate with the hardware.
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_CanSetMode(Sbc_IdType dId, Sbc_SystemModeType mode);

/**********************************************************************************************************************
 *  Sbc_Ll_Sys_SetMode()
 *********************************************************************************************************************/
/*! \brief       Changes the system mode of the SBC identified by dId to the given mode.
 *  \details     The API changes the system mode of the SBC with the given dId to the requested mode.
 *               When NORMAL mode is requested, a possibly pending POR is cleared from hardware.
 *  \param[in]   dId   Identifies the device id, dId must be a valid value.
 *  \param[in]   mode  The mode that shall be reached.
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         This API is only called if Sbc_Ll_Sys_CanSetMode returned E_OK.
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_SetMode(Sbc_IdType dId, Sbc_SystemModeType mode);

/**********************************************************************************************************************
 *  Sbc_Ll_Sys_ClearEvents()
 *********************************************************************************************************************/
/*! \brief       Clears the specified events from the SBC hardware.
 *  \details     This API clears the events that have a "1" at the corresponding position of the given clearFlags from
 *               the SBC device that is identified by dId.
 *               If necessary the API stores the state and events after the clearing in the objects that is referred
 *               by parameter status.
 *  \param[in]   dId         Identifies the device id, dId must be a valid value.
 *  \param[out]  status      Reference to the object to store the status.
 *  \param[in]   clearFlags  The flags that shall be cleared.
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_ClearEvents(Sbc_IdType dId, P2VAR(Sbc_SystemStatusType, AUTOMATIC, SBC_30_FS85_APPL_DATA) status, Sbc_SystemEventType clearFlags);

/**********************************************************************************************************************
 *  Sbc_Ll_Sys_ReadStatus()
 *********************************************************************************************************************/
/*! \brief       Reads the current system status from the SBC hardware.
 *  \details     This API reads the current hardware status from the SBC that is identified by parameter dId and stores
 *               the flags in the object that is referred by parameter status.
 *  \param[in]   dId         Identifies the device id, dId must be a valid value.
 *  \param[out]  status      Reference to the object to store the status.
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_ReadStatus(Sbc_IdType dId, P2VAR(Sbc_SystemStatusType, AUTOMATIC, SBC_30_FS85_APPL_DATA) status);

/**********************************************************************************************************************
 *  Sbc_Ll_Sys_AccessRegister()
 *********************************************************************************************************************/
/*! \brief       Accesses specific SBC register.
 *  \details     This API accesses specific SBC registers identified by the register address that is coded in the spiCommand.
 *               The value that is read back on MISO pin is copied to spiAnswer variable.
 *  \param[in]   dId         Identifies the device id, dId must be a valid value.
 *  \param[in]   spiCommand  The complete SPI value that can be directly written to MOSI register.
 *  \param[out]  spiAnswer   The complete SPI value that is received on MISO register. SpiAnswer must be a valid pointer.
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_AccessRegister(Sbc_IdType dId, Sbc_SpiDataWidth spiCommand, P2VAR(Sbc_SpiDataWidth, AUTOMATIC, SBC_30_FS85_APPL_DATA) spiAnswer);



#if defined(SBC_30_FS85_ENABLE_WDG)
/**********************************************************************************************************************
 *  Sbc_Ll_Wdg_Trigger()
 *********************************************************************************************************************/
/*! \brief       Triggers the watchdog.
 *  \details     This API triggers the hardware watchdog by sending a proper command via SPI to the underlying hardware.
 *  \param[in]   dId         Identifies the device id, dId must be a valid value.
 *  \param[in]   pId         Identifies the peripheral id, pId must be a valid value.
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      SBC_30_FS85_ENABLE_WDG
 *  \pre         -
 *  \note        This API should use a separate high-priority sequence in order to ensure that the sequence is processed
 *               in time.
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Wdg_Trigger(Sbc_IdType dId, Sbc_IdType pId);

/**********************************************************************************************************************
 *  Sbc_Ll_Wdg_CanSetMode()
 *********************************************************************************************************************/
/*! \brief       Checks if the mode of the watchdog can be changed.
 * \details      This functions checks if it is possible to change the current watchdog mode to the given new mode.
 *               Reasons for not allowed mode changes may be:
 *                 - Unsupported mode
 *                 - Invalid mode transition
 *                 - Incorrect timing
 *  \param[in]   dId         Identifies the device id, dId must be a valid value.
 *  \param[in]   pId         Identifies the peripheral id, pId must be a valid value.
 *  \param[in]   mode        The mode that shall be reached.
 *  \return      E_OK if it is possible to change the mode.
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      SBC_30_FS85_ENABLE_WDG
 *  \pre         -
 *  \note        If this API returns E_OK it is expected that Sbc_Ll_Wdg_SetMode() may only fail due to incorrect
 *               communication towards the hardware.
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Wdg_CanSetMode(Sbc_IdType dId, Sbc_IdType pId, Sbc_WdgModeType mode);

/**********************************************************************************************************************
 *  Sbc_Ll_Wdg_SetMode()
 *********************************************************************************************************************/
/*! \brief       Changes the mode of the watchdog.
 *  \details     This API changes the mode of the watchdog that is identified by parameter dId and pId to the given mode.
 *  \param[in]   dId         Identifies the device id, dId must be a valid value.
 *  \param[in]   pId         Identifies the peripheral id, pId must be a valid value.
 *  \param[in]   mode        The mode that shall be reached.
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      SBC_30_FS85_ENABLE_WDG
 *  \pre         -
 *  \note        This API is only called if Sbc_Ll_Wdg_CanSetMode() returned E_OK.
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Wdg_SetMode(Sbc_IdType dId, Sbc_IdType pId, Sbc_WdgModeType mode);
#endif /* SBC_30_FS85_ENABLE_WD */

#define SBC_30_FS85_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if !defined(SBC_SOURCE)
# error "This file must be included in Sbc.c"
#endif

/* Check the version of Sbc header file */
#if (  (SBC_30_FS85_SW_MAJOR_VERSION != (0x01u)) \
    || (SBC_30_FS85_SW_MINOR_VERSION != (0x01u)) \
    || (SBC_30_FS85_SW_PATCH_VERSION != (0x00u)) )
 #error "Vendor specific version numbers of Sbc.c and Sbc.h are inconsistent"
#endif

/* Configuration compatibility checks */
#if defined(SBC_30_FS85_ENABLE_WDG)
# if defined(SBC_30_FS85_WDTYPECHALLENGER) && defined(SBC_30_FS85_WDTYPESIMPLE)
 #error "Invalid configuration, only one WDTYPE must be defined."
# endif
# if !defined(SBC_30_FS85_WDTYPECHALLENGER) && !defined(SBC_30_FS85_WDTYPESIMPLE)
 #error "Invalid configuration, a WDTYPE must be defined if WD is enabled."
# endif
#endif

/* register address mask */
#define SBC_LL_REG_ADDR_MASK                         0xFE000000u /*!< SPI frame adress mask                                       */
#define SBC_LL_REG_MASK_DATA                         0x00FFFF00u /*!< SPI frame data mask                                         */
#define SBC_LL_REG_MASK_CRC                          0x000000FFu /*!< SPI frame CRC mask                                          */

/* write command */
#define SBC_LL_WRITE_COMMAND                         0x01000000u /*!< SPI frame R/W flag                                          */

/* register address mask incl. write command */
#define SBC_LL_REG_ADDR_WRITE_MASK                   0xFF000000u /*!< SPI frame adress mask incl. R/W flag                        */

/*! DATA-BUFFER bit masks */ 
#define SBC_LL_REG_MASK_BIT_23                       0x00800000u /*!< SPI bitmask for single data bit of index 23                 */
#define SBC_LL_REG_MASK_BIT_22                       0x00400000u /*!< SPI bitmask for single data bit of index 22                 */
#define SBC_LL_REG_MASK_BIT_21                       0x00200000u /*!< SPI bitmask for single data bit of index 21                 */
#define SBC_LL_REG_MASK_BIT_20                       0x00100000u /*!< SPI bitmask for single data bit of index 20                 */
#define SBC_LL_REG_MASK_BIT_19                       0x00080000u /*!< SPI bitmask for single data bit of index 19                 */
#define SBC_LL_REG_MASK_BIT_18                       0x00040000u /*!< SPI bitmask for single data bit of index 18                 */
#define SBC_LL_REG_MASK_BIT_17                       0x00020000u /*!< SPI bitmask for single data bit of index 17                 */
#define SBC_LL_REG_MASK_BIT_16                       0x00010000u /*!< SPI bitmask for single data bit of index 16                 */
#define SBC_LL_REG_MASK_BIT_15                       0x00008000u /*!< SPI bitmask for single data bit of index 15                 */
#define SBC_LL_REG_MASK_BIT_14                       0x00004000u /*!< SPI bitmask for single data bit of index 14                 */
#define SBC_LL_REG_MASK_BIT_13                       0x00002000u /*!< SPI bitmask for single data bit of index 13                 */
#define SBC_LL_REG_MASK_BIT_12                       0x00001000u /*!< SPI bitmask for single data bit of index 12                 */
#define SBC_LL_REG_MASK_BIT_11                       0x00000800u /*!< SPI bitmask for single data bit of index 11                 */
#define SBC_LL_REG_MASK_BIT_10                       0x00000400u /*!< SPI bitmask for single data bit of index 10                 */
#define SBC_LL_REG_MASK_BIT_9                        0x00000200u /*!< SPI bitmask for single data bit of index 9                  */
#define SBC_LL_REG_MASK_BIT_8                        0x00000100u /*!< SPI bitmask for single data bit of index 8                  */

/*! 
 * Internal comment removed. *
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
 */ 

/*! main register addresses incl. M/FS bit */
#define SBC_LL_REG_ADDR_M_FLAG                       0x00000000u /*!< Initialization of M_FLAG                                    */
#define SBC_LL_REG_ADDR_M_MODE                       0x02000000u /*!< Initialization of M_MODE                                    */
#define SBC_LL_REG_ADDR_M_FLAG1                      0x10000000u /*!< Initialization of M_FLAG1                                   */
#define SBC_LL_REG_ADDR_M_FLAG2                      0x12000000u /*!< Initialization of M_FLAG2                                   */

/*! fail-safe register addresses incl. M/FS bit */
#define SBC_LL_REG_ADDR_FS_I_OVUV_SAFE_REACTION1     0x82000000u /*!< Initialization of FS_I_OVUV_SAFE_REACTION1                  */
#define SBC_LL_REG_ADDR_FS_I_NOT_OVUV_SAFE_REACTION1 0x84000000u /*!< Initialization of FS_I_NOT_OVUV_SAFE_REACTION1              */
#define SBC_LL_REG_ADDR_FS_I_OVUV_SAFE_REACTION2     0x86000000u /*!< Initialization of FS_I_OVUV_SAFE_REACTION2                  */
#define SBC_LL_REG_ADDR_FS_I_NOT_OVUV_SAFE_REACTION2 0x88000000u /*!< Initialization of FS_I_NOT_OVUV_SAFE_REACTION2              */
#define SBC_LL_REG_ADDR_FS_I_WD_CFG                  0x8A000000u /*!< Initialization of FS_I_WD_CFG                               */
#define SBC_LL_REG_ADDR_FS_I_NOT_WD_CFG              0x8C000000u /*!< Initialization of FS_I_NOT_WD_CFG                           */
#define SBC_LL_REG_ADDR_FS_I_SAFE_INPUTS             0x8E000000u /*!< Initialization of FS_I_SAFE_INPUTS                          */
#define SBC_LL_REG_ADDR_FS_I_NOT_SAFE_INPUTS         0x90000000u /*!< Initialization of FS_I_NOT_SAFE_INPUTS                      */
#define SBC_LL_REG_ADDR_FS_I_FSSM                    0x92000000u /*!< Initialization of FS_I_FSSM                                 */
#define SBC_LL_REG_ADDR_FS_I_NOT_FSSM                0x94000000u /*!< Initialization of FS_I_NOT_FSSM                             */
#define SBC_LL_REG_ADDR_FS_I_SVS                     0x96000000u /*!< Initialization of FS_I_SVS                                  */
#define SBC_LL_REG_ADDR_FS_I_NOT_SVS                 0x98000000u /*!< Initialization of FS_I_NOT_SVS                              */
#define SBC_LL_REG_ADDR_FS_WD_WINDOW                 0x9A000000u /*!< Initialization of FS_WD_WINDOW                              */
#define SBC_LL_REG_ADDR_FS_NOT_WD_WINDOW             0x9C000000u /*!< Initialization of FS_NOT_WD_WINDOW                          */
#define SBC_LL_REG_ADDR_FS_WD_SEED                   0x9E000000u /*!< Initialization of FS_WD_SEED                                */
#define SBC_LL_REG_ADDR_FS_WD_ANSWER                 0xA0000000u /*!< Initialization of FS_WD_ANSWER                              */
#define SBC_LL_REG_ADDR_FS_DIAG_SAFETY               0xA8000000u /*!< Initialization of FS_DIAG_SAFETY                            */
#define SBC_LL_REG_ADDR_FS_STATES                    0xAC000000u /*!< Initialization of FS_STATES                                 */

/*! Readback masks for initialization of _NOT_ registers */
#define SBC_LL_REG_FS_I_RB_MASK_OVUV_SAFE_REACTION1  0x00F7EF00u /*!< Readback mask for OVUV_SAFE_REACTION1 register              */
#define SBC_LL_REG_FS_I_RB_MASK_OVUV_SAFE_REACTION2  0x00FFFF00u /*!< Readback mask for OVUV_SAFE_REACTION2 register              */
#define SBC_LL_REG_FS_I_RB_MASK_WD_CFG               0x00DB7F00u /*!< Readback mask for WD_CFG register                           */
#define SBC_LL_REG_FS_I_RB_MASK_SAFE_INPUTS          0x00DDDE00u /*!< Readback mask for SAFE_INPUTS register                      */
#define SBC_LL_REG_FS_I_RB_MASK_FSSM                 0x00DABF00u /*!< Readback mask for FSSM register                             */
#define SBC_LL_REG_FS_I_RB_MASK_SVS                  0x00F80000u /*!< Readback mask for SVS register                              */
#define SBC_LL_REG_FS_RB_MASK_WD_WINDOW              0x00F70F00u /*!< Readback mask for WD_WINDOW register                        */

/*! MODE register bit masks */ 
#define SBC_LL_REG_M_MODE_GOTOSTBY                   SBC_LL_REG_MASK_BIT_8  /*!< Go to Standby: write only                        */

/*! FLAG1 register bit masks */ 
#define SBC_LL_REG_M_FLAG1_CLEAR                     0x00FF7F00u            /*!< FLAG1 register mask for all W2C bits             */
#define SBC_LL_REG_M_FLAG1_VBOSUVH                   SBC_LL_REG_MASK_BIT_23 /*!< FLAG1 register mask for bit: VBOSUVH             */
#define SBC_LL_REG_M_FLAG1_VBOOSTUVH                 SBC_LL_REG_MASK_BIT_22 /*!< FLAG1 register mask for bit: VBOOSTUVH           */
#define SBC_LL_REG_M_FLAG1_VPREOC                    SBC_LL_REG_MASK_BIT_21 /*!< FLAG1 register mask for bit: VPREOC              */
#define SBC_LL_REG_M_FLAG1_BUCK1OC                   SBC_LL_REG_MASK_BIT_20 /*!< FLAG1 register mask for bit: BUCK1OC             */
#define SBC_LL_REG_M_FLAG1_BUCK2OC                   SBC_LL_REG_MASK_BIT_19 /*!< FLAG1 register mask for bit: BUCK2OC             */
#define SBC_LL_REG_M_FLAG1_BUCK3OC                   SBC_LL_REG_MASK_BIT_18 /*!< FLAG1 register mask for bit: BUCK3OC             */
#define SBC_LL_REG_M_FLAG1_LDO1OC                    SBC_LL_REG_MASK_BIT_17 /*!< FLAG1 register mask for bit: LDO1OC              */
#define SBC_LL_REG_M_FLAG1_LDO2OC                    SBC_LL_REG_MASK_BIT_16 /*!< FLAG1 register mask for bit: LDO2OC              */
#define SBC_LL_REG_M_FLAG1_CLK_FIN_DIV_OK            SBC_LL_REG_MASK_BIT_15 /*!< FLAG1 register mask for bit: CLK_FIN_DIV_OK      */
#define SBC_LL_REG_M_FLAG1_VBOOSTOV                  SBC_LL_REG_MASK_BIT_14 /*!< FLAG1 register mask for bit: VBOOSTOV            */
#define SBC_LL_REG_M_FLAG1_VBOOSTOT                  SBC_LL_REG_MASK_BIT_13 /*!< FLAG1 register mask for bit: VBOOSTOT            */
#define SBC_LL_REG_M_FLAG1_BUCK1OT                   SBC_LL_REG_MASK_BIT_12 /*!< FLAG1 register mask for bit: BUCK1OT             */
#define SBC_LL_REG_M_FLAG1_BUCK2OT                   SBC_LL_REG_MASK_BIT_11 /*!< FLAG1 register mask for bit: BUCK2OT             */
#define SBC_LL_REG_M_FLAG1_BUCK3OT                   SBC_LL_REG_MASK_BIT_10 /*!< FLAG1 register mask for bit: BUCK3OT             */
#define SBC_LL_REG_M_FLAG1_LDO1OT                    SBC_LL_REG_MASK_BIT_9  /*!< FLAG1 register mask for bit: LDO1OT              */
#define SBC_LL_REG_M_FLAG1_LDO2OT                    SBC_LL_REG_MASK_BIT_8  /*!< FLAG1 register mask for bit: LDO2OT              */

/*! FLAG2 register bit masks */ 
#define SBC_LL_REG_M_FLAG2_CLEAR                     0x00C0F300u            /*!< FLAG2 register mask for all W2C bits             */
#define SBC_LL_REG_M_FLAG2_VPRE_FB_OV                SBC_LL_REG_MASK_BIT_23 /*!< FLAG2 register mask for bit: VPRE_FB_OV          */
#define SBC_LL_REG_M_FLAG2_VSUPUV7                   SBC_LL_REG_MASK_BIT_22 /*!< FLAG2 register mask for bit: VSUPUV7             */
#define SBC_LL_REG_M_FLAG2_BOOST_ST                  SBC_LL_REG_MASK_BIT_21 /*!< FLAG2 register mask for bit: BOOST_ST            */
#define SBC_LL_REG_M_FLAG2_BUCK1_ST                  SBC_LL_REG_MASK_BIT_20 /*!< FLAG2 register mask for bit: BUCK1_ST            */
#define SBC_LL_REG_M_FLAG2_BUCK2_ST                  SBC_LL_REG_MASK_BIT_19 /*!< FLAG2 register mask for bit: BUCK2_ST            */
#define SBC_LL_REG_M_FLAG2_BUCK3_ST                  SBC_LL_REG_MASK_BIT_18 /*!< FLAG2 register mask for bit: BUCK3_ST            */
#define SBC_LL_REG_M_FLAG2_LDO1_ST                   SBC_LL_REG_MASK_BIT_17 /*!< FLAG2 register mask for bit: LDO1_ST             */
#define SBC_LL_REG_M_FLAG2_LDO2_ST                   SBC_LL_REG_MASK_BIT_16 /*!< FLAG2 register mask for bit: LDO2_ST             */
#define SBC_LL_REG_M_FLAG2_VPREUVL                   SBC_LL_REG_MASK_BIT_15 /*!< FLAG2 register mask for bit: VPREUVL             */
#define SBC_LL_REG_M_FLAG2_VPREUVH                   SBC_LL_REG_MASK_BIT_14 /*!< FLAG2 register mask for bit: VPREUVH             */
#define SBC_LL_REG_M_FLAG2_VSUPUVL                   SBC_LL_REG_MASK_BIT_13 /*!< FLAG2 register mask for bit: VSUPUVL             */
#define SBC_LL_REG_M_FLAG2_VSUPUVH                   SBC_LL_REG_MASK_BIT_12 /*!< FLAG2 register mask for bit: VSUPUVH             */
#define SBC_LL_REG_M_FLAG2_WK2RT                     SBC_LL_REG_MASK_BIT_11 /*!< FLAG2 register mask for bit: WK2RT               */
#define SBC_LL_REG_M_FLAG2_WK1RT                     SBC_LL_REG_MASK_BIT_10 /*!< FLAG2 register mask for bit: WK1RT               */
#define SBC_LL_REG_M_FLAG2_WK2FLG                    SBC_LL_REG_MASK_BIT_9  /*!< FLAG2 register mask for bit: WK2FLG              */
#define SBC_LL_REG_M_FLAG2_WK1FLG                    SBC_LL_REG_MASK_BIT_8  /*!< FLAG2 register mask for bit: WK1FLG              */

/*! DIAG_SAFETY register bit masks */ 
#define SBC_LL_REG_FS_DIAG_SAFETY_BAD_WD_DATA        SBC_LL_REG_MASK_BIT_17 /*!< DIAG_SAFETY register mask for bit: BAD_WD_DATA   */
#define SBC_LL_REG_FS_DIAG_SAFETY_BAD_WD_TIMING      SBC_LL_REG_MASK_BIT_16 /*!< DIAG_SAFETY register mask for bit: BAD_WD_TIMING */
#define SBC_LL_REG_FS_DIAG_SAFETY_ABIST1_OK          SBC_LL_REG_MASK_BIT_15 /*!< DIAG_SAFETY register mask for bit: ABIST1_OK     */
#define SBC_LL_REG_FS_DIAG_SAFETY_ABIST2_OK          SBC_LL_REG_MASK_BIT_14 /*!< DIAG_SAFETY register mask for bit: ABIST2_OK     */
#define SBC_LL_REG_FS_DIAG_SAFETY_SPI_FS_CLK         SBC_LL_REG_MASK_BIT_13 /*!< DIAG_SAFETY register mask for bit: SPI_FS_CLK    */
#define SBC_LL_REG_FS_DIAG_SAFETY_SPI_FS_REQ         SBC_LL_REG_MASK_BIT_12 /*!< DIAG_SAFETY register mask for bit: SPI_FS_REQ    */
#define SBC_LL_REG_FS_DIAG_SAFETY_SPI_FS_CRC         SBC_LL_REG_MASK_BIT_11 /*!< DIAG_SAFETY register mask for bit: SPI_FS_CRC    */

/*! FS STATES register bit masks */ 
#define SBC_LL_REG_FS_STATES_FSM_STATE               0x00000F00u            /*!< FSM_STATE[3:0]: mask                             */
#define SBC_LL_REG_FS_STATES_FSM_STATE_INIT_FS       0x00000600u            /*!< FSM_STATE[3:0]: INIT_FS                          */

/* FS WD WINDOW PERIOD register bit masks */
#define SBC_LL_REG_FS_WD_WINDOW_PERIOD               0x00F00000u            /*!< WD_WINDOW register mask for bits: WDW_PERIOD     */
#define SBC_LL_REG_FS_WD_WINDOW_PERIOD_DISABLE       0x00000000u            /*!< WD_WINDOW set WDW_PERIOD to DISABLE              */

/* FS WD SEED register bit masks */
#define SBC_LL_REG_FS_WD_SEED_WD_SEED_DEFAULT        0x005AB200u            /*!< Watchdog Default Seed                            */

/* SIF: status information field - updated by each SPI access. */
#define SBC_LL_SIF_VLDO_G                            0x01u                  /*!< Status Information Field Mask: VLDO_G            */
#define SBC_LL_SIF_VBUCK3_G                          0x02u                  /*!< Status Information Field Mask: VBUCK3_G          */
#define SBC_LL_SIF_VBUCK2_G                          0x04u                  /*!< Status Information Field Mask: VBUCK2_G          */
#define SBC_LL_SIF_VBUCK1_G                          0x08u                  /*!< Status Information Field Mask: VBUCK1_G          */
#define SBC_LL_SIF_VBOOST_G                          0x10u                  /*!< Status Information Field Mask: VBOOST_G          */
#define SBC_LL_SIF_VPRE_G                            0x20u                  /*!< Status Information Field Mask: VPRE_G            */
#define SBC_LL_SIF_WU_G                              0x40u                  /*!< Status Information Field Mask: WU_G              */
#define SBC_LL_SIF_COM_ERR                           0x80u                  /*!< Status Information Field Mask: COM_ERR           */

/* compatibility defines for SPI API mapping */
#if !defined(Sbc_SpiSetupEB) /* COV_SBC_SPI_COMPATIBILITY */
# define Sbc_SpiSetupEB Spi_SetupEB
#endif

#if !defined(Sbc_SpiSyncTransmit) /* COV_SBC_SPI_COMPATIBILITY */
# define Sbc_SpiSyncTransmit Spi_SyncTransmit
#endif

#if !defined(SBC_LL_SPI_TRANSFER_LENGTH) /* COV_SBC_SPI_COMPATIBILITY */
# define SBC_LL_SPI_TRANSFER_LENGTH 2u
#endif

#if !defined(Sbc_SpiDataType) /* COV_SBC_SPI_COMPATIBILITY */
# define Sbc_SpiDataType Spi_DataType
#endif

#define Sbc_ll_GetBit(bits,index)              (((uint8)((bits)>>(index)))&0x01u)

#define Sbc_Ll_MkWrCmd(addr, value)      (uint32)( ( ( (addr) & SBC_LL_REG_ADDR_MASK ) | SBC_LL_WRITE_COMMAND ) | ( (uint32)(value) & 0x00FFFF00u ) )
#define Sbc_Ll_MkRdCmd(addr)             (uint32)(     (addr) & SBC_LL_REG_ADDR_MASK )

#define Sbc_Ll_ReadRegister(dId, adr, dst)                  Sbc_Ll_RwRegister(dId, Sbc_Ll_MkRdCmd(adr), dst)
#define Sbc_Ll_ReadWriteRegister(dId, adr, value, dst)      Sbc_Ll_RwRegister(dId, Sbc_Ll_MkWrCmd(adr, value), dst)
#define Sbc_Ll_WriteRegister(dId, adr, value)               Sbc_Ll_ReadWriteRegister(dId, adr, value, NULL_PTR)

#define Sbc_Ll_Sif(dId) Sbc_Ll_RegVal(dId, SIF)
#define Sbc_Ll_RegVal(dId, regName)                   (Sbc_Ll_RegState[dId].regName)

#define Sbc_Ll_Cfg_GetSpiSequence(dId) \
    ((Spi_SequenceType)(Sbc_30_Fs85_GetSbcSpiSeq_SbcSpiSequenceOfSpiSequence(dId)))
#define Sbc_Ll_Cfg_GetSpiChannel(dId)  \
    ((Spi_ChannelType)(Sbc_30_Fs85_GetSbcSpiChl_SbcSpiChannelOfSpiChannel(dId)))

#define Sbc_Ll_Cfg_GetWdgValueSlow(dId, pId) \
    (((uint32)(Sbc_30_Fs85_GetSlowRegValOfWdgConfig(Sbc_Cfg_GetWdgConfigIdx(dId, pId)))) << 8u)
#define Sbc_Ll_Cfg_GetWdgValueFast(dId, pId) \
    (((uint32)(Sbc_30_Fs85_GetFastRegValOfWdgConfig(Sbc_Cfg_GetWdgConfigIdx(dId, pId)))) << 8u)


#define Sbc_LL_Cfg_GetInitOvuvSafeReaction1(dId)     (((uint32)(Sbc_30_Fs85_GetOvuvSafeReaction1OfInitConfig(dId))) << 8u)
#define Sbc_LL_Cfg_GetInitOvuvSafeReaction2(dId)     (((uint32)(Sbc_30_Fs85_GetOvuvSafeReaction2OfInitConfig(dId))) << 8u)
#define Sbc_LL_Cfg_GetInitWdCfg(dId)                 (((uint32)(Sbc_30_Fs85_GetWdCfgOfInitConfig(dId))) << 8u)
#define Sbc_LL_Cfg_GetInitSafeInputs(dId)            (((uint32)(Sbc_30_Fs85_GetSafeInputsOfInitConfig(dId))) << 8u)
#define Sbc_LL_Cfg_GetInitFssm(dId)                  (((uint32)(Sbc_30_Fs85_GetFssmOfInitConfig(dId))) << 8u)
#define Sbc_LL_Cfg_GetInitSvs(dId)                   (((uint32)(Sbc_30_Fs85_GetSvsOfInitConfig(dId))) << 8u)

/* PRQA L:Sbc_Ll_LocalFunctionMacros_Tag */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/
/* Stores a shadow copy of some SBC internal registers */
typedef struct
{
  uint8 SIF;          /* Status information field. Updated by each SPI access. */
} Sbc_Ll_RegStateType;

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

#define SBC_30_FS85_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Protected by SBC_EXCLUSIVE_AREA_3 */
SBC_LOCAL VAR(Sbc_SpiDataType, SBC_30_FS85_VAR_NOINIT) Sbc_Ll_SpiOutBuffer[2u*SBC_30_FS85_NUMBER_OF_DEVICES];
SBC_LOCAL VAR(Sbc_SpiDataType, SBC_30_FS85_VAR_NOINIT) Sbc_Ll_SpiInBuffer[2u*SBC_30_FS85_NUMBER_OF_DEVICES];

#define SBC_30_FS85_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define SBC_30_FS85_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Protected by SBC_LL_ACCESS_STATE */
SBC_LOCAL VAR(Sbc_Ll_RegStateType, SBC_30_FS85_VAR_NOINIT) Sbc_Ll_RegState[SBC_30_FS85_NUMBER_OF_DEVICES];

#define SBC_30_FS85_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define SBC_30_FS85_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Sbc_Ll_RwRegister()
 *********************************************************************************************************************/
/*! \brief       Initiates SPI transfer to SBC module.
 *  \details     This function computes the parity bit for write commands and trigger synchronous SPI transfer.
 *  \param[in]   dId  Identifies the device id, dId must be a valid value.
 *  \param[in]   out  SPI output value for MOSI pin.
 *  \param[out]  in   SPI input value from MISO pin.
 *  \return      E_OK on success. 
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
SBC_LOCAL FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_RwRegister(
    Sbc_IdType dId, uint32 out, P2VAR(uint32, AUTOMATIC, SBC_30_FS85_APPL_DATA) in);

/**********************************************************************************************************************
 *  Sbc_Ll_ComputeCRC()
 *********************************************************************************************************************/
/*! \brief       Computes the CRC bits.
 *  \details     This function is called for read/write commands to compute and set the CRC bits.
 *  \param[in]   cmd         SPI command without usage of the crc bits.
 *  \return      spiCommand  SPI command with usage of the crc bits.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(uint32, SBC_30_FS85_CODE) Sbc_Ll_ComputeCRC(uint32 cmd);

#if defined(SBC_30_FS85_ENABLE_WDG)
# if defined(SBC_30_FS85_WDTYPECHALLENGER)
/**********************************************************************************************************************
 *  Sbc_Ll_ComputeWdgAnswer()
 *********************************************************************************************************************/
/*! \brief       Computes the watchdog answer.
 *  \details     Computes the value that must be sent to SBC as watchdog trigger.
 *  \param[in]   lFsrVal  Value on which the computation is based.
 *  \return      wdgAnswer
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      SBC_30_FS85_ENABLE_WDG, SBC_30_FS85_WDTYPECHALLENGER
 *  \pre         -
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(uint32, SBC_30_FS85_CODE) Sbc_Ll_ComputeWdgAnswer(uint32 lFsrVal);
# endif

/**********************************************************************************************************************
 *  Sbc_Ll_Wdg_GetWdgRegValue()
 *********************************************************************************************************************/
/*! \brief       Gets the register value for watchdog mode.
 *  \details     This function gets the register value to configure the watchdog windows register
 *               for a specific watchdog mode.
 *  \param[in]   dId      Identifies the device id, dId must be a valid value.
 *  \param[in]   pId      Identifies the peripheral id, pId must be a valid value.
 *  \param[in]   mode     The requested watchdog mode.
 *  \return      Watchdog mode register value.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      SBC_30_FS85_ENABLE_WDG
 *  \pre         -
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(uint32, SBC_30_FS85_CODE) Sbc_Ll_Wdg_GetWdgRegValue(
    Sbc_IdType dId, Sbc_IdType pId, Sbc_WdgModeType mode);
#endif

/**********************************************************************************************************************
 *  Sbc_Ll_Sys_EvaluateFlag1Reg()
 *********************************************************************************************************************/
/*! \brief       Evaluates FLAG1 register events.
 *  \details     This function reads and stores the events of the corresponding register.
 *  \param[in]   dId      Identifies the device id, dId must be a valid value.
 *  \param[in]   clear    Determines if flags should be read and cleared or only read.
 *  \param[out]  status   Reference to the object to store the status.
 *  \return      E_OK on success. 
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_EvaluateFlag1Reg(
    Sbc_IdType dId, P2VAR(Sbc_SystemStatusType, AUTOMATIC, SBC_30_FS85_APPL_DATA) status, uint16 clear);
    
/**********************************************************************************************************************
 *  Sbc_Ll_Sys_EvaluateFlag2Reg()
 *********************************************************************************************************************/
/*! \brief       Evaluates FLAG2 register events.
 *  \details     This function reads and stores the events of the corresponding register.
 *  \param[in]   dId      Identifies the device id, dId must be a valid value.
 *  \param[in]   clear    Determines if flags should be read and cleared or only read.
 *  \param[out]  status   Reference to the object to store the status.
 *  \return      E_OK on success. 
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_EvaluateFlag2Reg(
    Sbc_IdType dId, P2VAR(Sbc_SystemStatusType, AUTOMATIC, SBC_30_FS85_APPL_DATA) status, uint16 clear);

/**********************************************************************************************************************
 *  Sbc_Ll_Sys_EvaluateDiagSafetyReg()
 *********************************************************************************************************************/
/*! \brief       Evaluates DIAG_SAFETY register events.
 *  \details     This function reads and stores the events of the corresponding register.
 *  \param[in]   dId      Identifies the device id, dId must be a valid value.
 *  \param[in]   clear    Determines if flags should be read and cleared or only read.
 *  \param[out]  status   Reference to the object to store the status.
 *  \return      E_OK on success. 
 *               E_NOT_OK otherwise.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_EvaluateDiagSafetyReg(
    Sbc_IdType dId, P2VAR(Sbc_SystemStatusType, AUTOMATIC, SBC_30_FS85_APPL_DATA) status, uint16 clear);

/* ********************************************************************************************************************
 *  LOCAL LOW LEVEL FUNCTIONS
 * ********************************************************************************************************************/

/* ********************************************************************************************************************
 * Sbc_Ll_InitDevice
 * ********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_InitDevice(Sbc_IdType dId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result;
  uint32 tmp = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the external buffers (EB) for SPI communication */
  result = /* SBSW_SBC_CALL_SPI_SETUPEB */
      Sbc_SpiSetupEB(Sbc_Ll_Cfg_GetSpiChannel(dId), (Sbc_SpiDataType*)&Sbc_Ll_SpiOutBuffer[dId], (Sbc_SpiDataType*)&Sbc_Ll_SpiInBuffer[dId], SBC_LL_SPI_TRANSFER_LENGTH);

  /* only initialize SBC module if SPI external buffer are setup successfully */
  if (result == E_OK) /* COV_SBC_LL_HW_SPI_ERR */
  {
    /* #20 Read state register to detect current FS state */
    result = Sbc_Ll_ReadRegister(dId, SBC_LL_REG_ADDR_FS_STATES, &tmp); /* SBSW_SBC_LOCALPTR_PARAM */
    if ( result == E_OK ) /* COV_SBC_LL_HW_SPI_ERR */
    {
      /* #30 Check if SBC is in INIT mode */
      if ((tmp & SBC_LL_REG_FS_STATES_FSM_STATE) == SBC_LL_REG_FS_STATES_FSM_STATE_INIT_FS) /* COV_SBC_LL_INIT_FS_NOT_IN_ALL_CONFIG */
      {
        /* #40 Initialize FAILSAFE INIT registers, can only be written in INIT_FS mode */
        result  = Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_I_OVUV_SAFE_REACTION1, Sbc_LL_Cfg_GetInitOvuvSafeReaction1(dId)); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
        result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_I_NOT_OVUV_SAFE_REACTION1, ~Sbc_LL_Cfg_GetInitOvuvSafeReaction1(dId)&SBC_LL_REG_FS_I_RB_MASK_OVUV_SAFE_REACTION1); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
        result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_I_OVUV_SAFE_REACTION2, Sbc_LL_Cfg_GetInitOvuvSafeReaction2(dId)); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
        result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_I_NOT_OVUV_SAFE_REACTION2, ~Sbc_LL_Cfg_GetInitOvuvSafeReaction2(dId)&SBC_LL_REG_FS_I_RB_MASK_OVUV_SAFE_REACTION2); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
        result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_I_WD_CFG, Sbc_LL_Cfg_GetInitWdCfg(dId)); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
        result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_I_NOT_WD_CFG, ~Sbc_LL_Cfg_GetInitWdCfg(dId)&SBC_LL_REG_FS_I_RB_MASK_WD_CFG); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
        result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_I_SAFE_INPUTS, Sbc_LL_Cfg_GetInitSafeInputs(dId)); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
        result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_I_NOT_SAFE_INPUTS, ~Sbc_LL_Cfg_GetInitSafeInputs(dId)&SBC_LL_REG_FS_I_RB_MASK_SAFE_INPUTS); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
        result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_I_FSSM, Sbc_LL_Cfg_GetInitFssm(dId)); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
        result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_I_NOT_FSSM, ~Sbc_LL_Cfg_GetInitFssm(dId)&SBC_LL_REG_FS_I_RB_MASK_FSSM); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
        result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_I_SVS, Sbc_LL_Cfg_GetInitSvs(dId)); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
        result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_I_NOT_SVS, ~Sbc_LL_Cfg_GetInitSvs(dId)&SBC_LL_REG_FS_I_RB_MASK_SVS); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
#if defined(SBC_30_FS85_ENABLE_WDG)
        result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_WD_SEED, SBC_LL_REG_FS_WD_SEED_WD_SEED_DEFAULT); /* SBSW_SBC_NULLPTR_PARAM */
        if (result == E_OK) /* COV_SBC_LL_HW_SPI_ERR */
        {
          /* #50 Disable watchdog: set watchdog window to zero and trigger watchdog in initial 256ms fully open window */
          result  = Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_WD_WINDOW, SBC_LL_REG_FS_WD_WINDOW_PERIOD_DISABLE); /* SBSW_SBC_NULLPTR_PARAM */
          result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_NOT_WD_WINDOW, ~SBC_LL_REG_FS_WD_WINDOW_PERIOD_DISABLE&SBC_LL_REG_FS_RB_MASK_WD_WINDOW); /* SBSW_SBC_NULLPTR_PARAM */
# if defined(SBC_30_FS85_WDTYPESIMPLE)
          result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_WD_ANSWER, SBC_LL_REG_FS_WD_SEED_WD_SEED_DEFAULT); /* SBSW_SBC_NULLPTR_PARAM */
# else
          result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_WD_ANSWER, Sbc_Ll_ComputeWdgAnswer(SBC_LL_REG_FS_WD_SEED_WD_SEED_DEFAULT)); /* SBSW_SBC_NULLPTR_PARAM */
# endif
        }
#endif
      }
    }
  }
  return result;
}

/* ********************************************************************************************************************
 * Sbc_Ll_Sys_CanSetMode
 * ********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_CanSetMode(
    Sbc_IdType dId, Sbc_SystemModeType mode)
{
  Std_ReturnType result = E_NOT_OK;
  Sbc_SystemModeType currentMode = (Sbc_SystemModeType)Sbc_Sys_St_GetMode(Sbc_Rt_GetSystemStatus(dId));

  /* #10 Check if the requested mode switch is valid */
  if (mode == SBC_SYS_MODE_STANDBY)
  {
    result = E_OK;
  }
  else if (mode == SBC_SYS_MODE_SLEEP)
  {
    if (currentMode == SBC_SYS_MODE_STANDBY)
    {
      result = E_OK;
    }
  }
  else /* NORMAL Mode: only NORMAL, STANDBY and SLEEP Mode are valid: Invalid ones are blocked by core DET check */
  {
      result = E_OK;
  }

  return result;
}

/*********************************************************************************************************************
 * Sbc_Ll_Sys_SetMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_SetMode(
    Sbc_IdType dId, Sbc_SystemModeType mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Switch to requested mode */
  if (mode == SBC_SYS_MODE_SLEEP)
  {
    /* Switch to (hardware) STANDBY mode: only transition from (software) STANDBY to SLEEP is allowed */
    result = Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_M_MODE, SBC_LL_REG_M_MODE_GOTOSTBY); /* SBSW_SBC_NULLPTR_PARAM */
  }
  else /* NORMAL or STANDBY (software) Mode are the same and always present out-of hardware STANDBY (software SLEEP) mode */
  {
    result = E_OK;
  }

  return result;
}


/* ********************************************************************************************************************
 * Sbc_Ll_Sys_ClearEvents
 * ********************************************************************************************************************/
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
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_ClearEvents(
    Sbc_IdType dId, P2VAR(Sbc_SystemStatusType, AUTOMATIC, SBC_30_FS85_APPL_DATA) status, Sbc_SystemEventType clearFlags)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset the events to zero */
  status->Events = 0u; /* SBSW_SBC_VALID_STATUSPTR */

  /* #20 Check if there are under-/over-voltage, overcurrent or temp-fail events to clear */ 
  if ( (clearFlags & (SBC_SYS_EV_UVERR | SBC_SYS_EV_OVERR | SBC_SYS_EV_OCERR | SBC_SYS_EV_TEMPFAIL)) != 0u )
  {
    /* #30 Get FLAG1 register events */
    result = Sbc_Ll_Sys_EvaluateFlag1Reg(dId, status, clearFlags); /* SBSW_SBC_VALID_STATUSPTR */
  }

  /* #40 Check if there are only under-/over-voltage events to clear */ 
  if ( (clearFlags & (SBC_SYS_EV_UVERR | SBC_SYS_EV_OVERR)) != 0u )
  {
    /* #50 Get FLAG2 register events */
    result |= Sbc_Ll_Sys_EvaluateFlag2Reg(dId, status, clearFlags); /* SBSW_SBC_VALID_STATUSPTR */
  }

  /* #60 Check if there are SPI-/WD-fail events to clear */ 
  if ( (clearFlags & (SBC_SYS_EV_SPIFAIL | SBC_SYS_EV_WDFAIL)) != 0u )
  {
    /* #70 Get DIAG_SAFETY register events */
    result |= Sbc_Ll_Sys_EvaluateDiagSafetyReg(dId, status, clearFlags); /* SBSW_SBC_VALID_STATUSPTR */
  }

  return result;
}


/* ********************************************************************************************************************
 * Sbc_Ll_Sys_ReadStatus
 * ********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_ReadStatus(
    Sbc_IdType dId, P2VAR(Sbc_SystemStatusType, AUTOMATIC, SBC_30_FS85_APPL_DATA) status)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset the events and status to zero */
  status->Events = 0u; /* SBSW_SBC_VALID_STATUSPTR */
  status->States = 0u; /* SBSW_SBC_VALID_STATUSPTR */

  /* #20 Get FLAG1 register events */
  result = Sbc_Ll_Sys_EvaluateFlag1Reg(dId, status, 0u); /* SBSW_SBC_VALID_STATUSPTR */
  /* #30 Get FLAG2 register events */
  result |= Sbc_Ll_Sys_EvaluateFlag2Reg(dId, status, 0u); /* SBSW_SBC_VALID_STATUSPTR */
  /* #40 Get DIAG_SAFETY register events */
  result |= Sbc_Ll_Sys_EvaluateDiagSafetyReg(dId, status, 0u); /* SBSW_SBC_VALID_STATUSPTR */

  /* #50 Check if the device indicates that a system wakeup occurred */
  if ( ( Sbc_Ll_Sif(dId) & SBC_LL_SIF_WU_G ) != 0u ) /* COV_SBC_LL_EVENTS */
  {
    Sbc_St_Set(status, SBC_SYS_ST_WAKEUP); /* SBSW_SBC_VALID_STATUSPTR */
  }
  
  return result;
}

/* ********************************************************************************************************************
 * Sbc_Ll_Sys_AccessRegister
 * ********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_AccessRegister(
  Sbc_IdType dId, Sbc_SpiDataWidth spiCommand, P2VAR(Sbc_SpiDataWidth, AUTOMATIC, SBC_30_FS85_APPL_DATA) spiAnswer)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
  /* #10 Ensure that the spiCommand does not influence the Watchdog behaviour */
  if ( ((spiCommand & SBC_LL_REG_ADDR_WRITE_MASK) != (SBC_LL_WRITE_COMMAND | SBC_LL_REG_ADDR_FS_WD_ANSWER)    ) &&
       ((spiCommand & SBC_LL_REG_ADDR_WRITE_MASK) != (SBC_LL_WRITE_COMMAND | SBC_LL_REG_ADDR_FS_WD_SEED)      ) &&
       ((spiCommand & SBC_LL_REG_ADDR_WRITE_MASK) != (SBC_LL_WRITE_COMMAND | SBC_LL_REG_ADDR_FS_WD_WINDOW)    ) &&
       ((spiCommand & SBC_LL_REG_ADDR_WRITE_MASK) != (SBC_LL_WRITE_COMMAND | SBC_LL_REG_ADDR_FS_NOT_WD_WINDOW))
      )
#endif
  {
    /* #20 Call Sbc_Ll_RwRegister to initiate SPI transfer */
    result = Sbc_Ll_RwRegister(dId, spiCommand, spiAnswer); /* SBSW_SBC_VALID_SPIANSWERPTR */
  }
  
  return result;
}

/*********************************************************************************************************************
 * Sbc_Ll_Sys_EvaluateFlag1Reg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_EvaluateFlag1Reg(
    Sbc_IdType dId, P2VAR(Sbc_SystemStatusType, AUTOMATIC, SBC_30_FS85_APPL_DATA) status, uint16 clear)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result;
  uint32 tmp;
  uint32 clearMask = 0u;
  
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check which flags should be cleared */
  if (clear != 0u)
  {
    if((clear & SBC_SYS_EV_UVERR) == SBC_SYS_EV_UVERR)
    {
      clearMask = (SBC_LL_REG_M_FLAG1_VBOSUVH | SBC_LL_REG_M_FLAG1_VBOOSTUVH);
    }
    if((clear & SBC_SYS_EV_OVERR) == SBC_SYS_EV_OVERR)
    {
      clearMask |= SBC_LL_REG_M_FLAG1_VBOOSTOV;
    }
    if((clear & SBC_SYS_EV_OCERR) == SBC_SYS_EV_OCERR)
    {
      clearMask |= (SBC_LL_REG_M_FLAG1_VPREOC | SBC_LL_REG_M_FLAG1_BUCK1OC | SBC_LL_REG_M_FLAG1_BUCK2OC | SBC_LL_REG_M_FLAG1_BUCK3OC | SBC_LL_REG_M_FLAG1_LDO1OC | SBC_LL_REG_M_FLAG1_LDO2OC);
    }
    if((clear & SBC_SYS_EV_TEMPFAIL) == SBC_SYS_EV_TEMPFAIL)
    {
      clearMask |= (SBC_LL_REG_M_FLAG1_VBOOSTOT | SBC_LL_REG_M_FLAG1_BUCK1OT | SBC_LL_REG_M_FLAG1_BUCK2OT | SBC_LL_REG_M_FLAG1_BUCK3OT | SBC_LL_REG_M_FLAG1_LDO1OT | SBC_LL_REG_M_FLAG1_LDO2OT);
    }
    /* #20 Clear FLAG1 register and store events */
    result = Sbc_Ll_ReadWriteRegister(dId, SBC_LL_REG_ADDR_M_FLAG1, clearMask, &tmp); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
  }
  else
  {
    /* #30 Evaluate FLAG1 register and store events */
    result = Sbc_Ll_ReadRegister(dId, SBC_LL_REG_ADDR_M_FLAG1, &tmp); /* SBSW_SBC_LOCALPTR_PARAM */
  }

  if (result == E_OK) /* COV_SBC_LL_HW_SPI_ERR */
  {
    if ( ((tmp) & (SBC_LL_REG_M_FLAG1_VBOSUVH|SBC_LL_REG_M_FLAG1_VBOOSTUVH)) != 0u ) /* COV_SBC_LL_EVENTS */
    {
      Sbc_Ev_Set(status, SBC_SYS_EV_UVERR); /* SBSW_SBC_VALID_STATUSPTR */
    }
    if ( ((tmp) & SBC_LL_REG_M_FLAG1_VBOOSTOV) != 0u ) /* COV_SBC_LL_EVENTS */
    {
      Sbc_Ev_Set(status, SBC_SYS_EV_OVERR); /* SBSW_SBC_VALID_STATUSPTR */
    }
    if ( ((tmp) & (SBC_LL_REG_M_FLAG1_VBOOSTOT|SBC_LL_REG_M_FLAG1_BUCK1OT|SBC_LL_REG_M_FLAG1_BUCK3OT|SBC_LL_REG_M_FLAG1_LDO1OT|SBC_LL_REG_M_FLAG1_LDO2OT)) != 0u ) /* COV_SBC_LL_EVENTS */
    {
      Sbc_Ev_Set(status, SBC_SYS_EV_TEMPFAIL); /* SBSW_SBC_VALID_STATUSPTR */
    }
    if ( ((tmp) & (SBC_LL_REG_M_FLAG1_VPREOC|SBC_LL_REG_M_FLAG1_BUCK1OC|SBC_LL_REG_M_FLAG1_BUCK2OC|SBC_LL_REG_M_FLAG1_BUCK3OC|SBC_LL_REG_M_FLAG1_LDO1OC|SBC_LL_REG_M_FLAG1_LDO2OC)) != 0u ) /* COV_SBC_LL_EVENTS */
    {
      Sbc_Ev_Set(status, SBC_SYS_EV_OCERR); /* SBSW_SBC_VALID_STATUSPTR */
    }
  }
  
  return result;
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */

/*********************************************************************************************************************
 * Sbc_Ll_Sys_EvaluateFlag2Reg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_EvaluateFlag2Reg(
    Sbc_IdType dId, P2VAR(Sbc_SystemStatusType, AUTOMATIC, SBC_30_FS85_APPL_DATA) status, uint16 clear)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result;
  uint32 tmp;
  uint32 clearMask = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check which flags should be cleared */
  if (clear != 0u)
  {
    if((clear & SBC_SYS_EV_UVERR) == SBC_SYS_EV_UVERR)
    {
      clearMask = (SBC_LL_REG_M_FLAG2_VSUPUV7 | SBC_LL_REG_M_FLAG2_VPREUVL | SBC_LL_REG_M_FLAG2_VPREUVH | SBC_LL_REG_M_FLAG2_VSUPUVL | SBC_LL_REG_M_FLAG2_VSUPUVH);
    }
    if((clear & SBC_SYS_EV_OVERR) == SBC_SYS_EV_OVERR)
    {
      clearMask |= SBC_LL_REG_M_FLAG2_VPRE_FB_OV;
    }
    /* #20 Clear FLAG2 register and store events */
    result = Sbc_Ll_ReadWriteRegister(dId, SBC_LL_REG_ADDR_M_FLAG2, clearMask, &tmp); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
  }
  else
  {
    /* #30 Evaluate FLAG2 register and store events */
    result = Sbc_Ll_ReadRegister(dId, SBC_LL_REG_ADDR_M_FLAG2, &tmp); /* SBSW_SBC_LOCALPTR_PARAM */
  }

  if (result == E_OK) /* COV_SBC_LL_HW_SPI_ERR */
  {
    if ( ((tmp) & (SBC_LL_REG_M_FLAG2_VSUPUV7|SBC_LL_REG_M_FLAG2_VPREUVL|SBC_LL_REG_M_FLAG2_VPREUVH|SBC_LL_REG_M_FLAG2_VSUPUVL|SBC_LL_REG_M_FLAG2_VSUPUVH)) != 0u )
    {
      Sbc_Ev_Set(status, SBC_SYS_EV_UVERR); /* SBSW_SBC_VALID_STATUSPTR */
    }
    if ( ((tmp) & SBC_LL_REG_M_FLAG2_VPRE_FB_OV) != 0u ) /* COV_SBC_LL_EVENTS */
    {
      Sbc_Ev_Set(status, SBC_SYS_EV_OVERR); /* SBSW_SBC_VALID_STATUSPTR */
    }
  }
  
  return result;
}

/*********************************************************************************************************************
 * Sbc_Ll_Sys_EvaluateDiagSafetyReg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Sys_EvaluateDiagSafetyReg(
    Sbc_IdType dId, P2VAR(Sbc_SystemStatusType, AUTOMATIC, SBC_30_FS85_APPL_DATA) status, uint16 clear)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result;
  uint32 tmp;
  uint32 clearMask = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check which flags should be cleared */
  if (clear != 0u)
  {
    if((clear & SBC_SYS_EV_SPIFAIL) == SBC_SYS_EV_SPIFAIL)
    {
      clearMask = (SBC_LL_REG_FS_DIAG_SAFETY_SPI_FS_CLK | SBC_LL_REG_FS_DIAG_SAFETY_SPI_FS_REQ | SBC_LL_REG_FS_DIAG_SAFETY_SPI_FS_CRC);
    }
    if((clear & SBC_SYS_EV_WDFAIL) == SBC_SYS_EV_WDFAIL)
    {
      clearMask |= (SBC_LL_REG_FS_DIAG_SAFETY_BAD_WD_DATA | SBC_LL_REG_FS_DIAG_SAFETY_BAD_WD_TIMING);
    }
    /* #20 Clear DIAG_SAFETY register and store events */
    result = Sbc_Ll_ReadWriteRegister(dId, SBC_LL_REG_ADDR_FS_DIAG_SAFETY, clearMask, &tmp); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
  }
  else
  {
    /* #30 Evaluate DIAG_SAFETY register and store events */
    result = Sbc_Ll_ReadRegister(dId, SBC_LL_REG_ADDR_FS_DIAG_SAFETY, &tmp); /* SBSW_SBC_LOCALPTR_PARAM */
  }
  if (result == E_OK) /* COV_SBC_LL_HW_SPI_ERR */
  {
    if ( ((tmp) & (SBC_LL_REG_FS_DIAG_SAFETY_SPI_FS_CLK|SBC_LL_REG_FS_DIAG_SAFETY_SPI_FS_REQ|SBC_LL_REG_FS_DIAG_SAFETY_SPI_FS_CRC)) != 0u ) /* COV_SBC_LL_HW_SPI_ERR */
    {
      Sbc_Ev_Set(status, SBC_SYS_EV_SPIFAIL); /* SBSW_SBC_VALID_STATUSPTR */
    }
    if ( ((tmp) & (SBC_LL_REG_FS_DIAG_SAFETY_BAD_WD_DATA|SBC_LL_REG_FS_DIAG_SAFETY_BAD_WD_TIMING)) != 0u )
    {
      Sbc_Ev_Set(status, SBC_SYS_EV_WDFAIL); /* SBSW_SBC_VALID_STATUSPTR */
    }
  }
  
  return result;
}

#if defined(SBC_30_FS85_ENABLE_WDG)
/* ********************************************************************************************************************
 * Sbc_Ll_Wdg_Trigger
 * ********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Wdg_Trigger(
    Sbc_IdType dId, Sbc_IdType pId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result;
#if defined(SBC_30_FS85_WDTYPECHALLENGER)
  uint32 lFsrValue = 0u;
#endif

  SBC_30_FS85_DUMMY_STATEMENT(pId); /* PRQA S 1338,2983 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
#if defined (SBC_30_FS85_WDTYPECHALLENGER)
  /* #10 LFSR value must be read to compute the WD_answer */
  result = Sbc_Ll_ReadRegister(dId, SBC_LL_REG_ADDR_FS_WD_SEED, &lFsrValue); /* SBSW_SBC_LOCALPTR_PARAM */

  if (result == E_OK) /* COV_SBC_LL_HW_SPI_ERR */
  {
    /* #20 Trigger watchdog */
    result = Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_WD_ANSWER, Sbc_Ll_ComputeWdgAnswer(lFsrValue)); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
  }
#else
  /* #20 Trigger watchdog */
  result = Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_WD_ANSWER, SBC_LL_REG_FS_WD_SEED_WD_SEED_DEFAULT); /* SBSW_SBC_NULLPTR_PARAM */
#endif

  return result;
}

/* ********************************************************************************************************************
 * Sbc_Ll_Wdg_CanSetMode
 * ********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Wdg_CanSetMode(
    Sbc_IdType dId, Sbc_IdType pId, Sbc_WdgModeType mode)
{
  Std_ReturnType result;
  
  SBC_30_FS85_DUMMY_STATEMENT(dId); /* PRQA S 1338,2983 */ /* MD_MSR_DummyStmt */
  SBC_30_FS85_DUMMY_STATEMENT(pId); /* PRQA S 1338,2983 */ /* MD_MSR_DummyStmt */

  /* #10 Check if the requested mode switch is valid */
  if ((SBC_WDG_MODE_FAST == mode) || (SBC_WDG_MODE_SLOW == mode))
  {
    result = E_OK;
  }
  else
  {
    result = E_NOT_OK;
  }
  
  return result;
}

/* ********************************************************************************************************************
 * Sbc_Ll_Wdg_SetMode
 * ********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SBC_LOCAL_INLINE FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_Wdg_SetMode(
    Sbc_IdType dId, Sbc_IdType pId, Sbc_WdgModeType mode)
{
  Std_ReturnType result;
  uint32 wdgRegValue;
  uint32 tmp;

  /* #10 Get the register value for mode change */
  wdgRegValue = Sbc_Ll_Wdg_GetWdgRegValue(dId, pId, mode);

  /* #20 Change the requested watchdog mode */
  result  = Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_WD_WINDOW, wdgRegValue); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
  result |= Sbc_Ll_WriteRegister(dId, SBC_LL_REG_ADDR_FS_NOT_WD_WINDOW, ~wdgRegValue&SBC_LL_REG_FS_RB_MASK_WD_WINDOW); /* SBSW_SBC_NULLPTR_PARAM */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
  if (result == E_OK) /* COV_SBC_LL_HW_SPI_ERR */
  {
    /* #30 Read back the changed mode and check if mode was changed successfully */
    /* Any WRITE command to the WD_window in the Normal mode must be followed
     *  by a READ command to verify the correct change of the WD window duration */
    result = Sbc_Ll_ReadRegister(dId, SBC_LL_REG_ADDR_FS_WD_WINDOW, &tmp); /* SBSW_SBC_LOCALPTR_PARAM */
    if (result == E_OK) /* COV_SBC_LL_HW_SPI_ERR */
    {
      /* return E_NOT_OK if WD window was not changed successfully */
      if ( (wdgRegValue & SBC_LL_REG_FS_WD_WINDOW_PERIOD) != (tmp & SBC_LL_REG_FS_WD_WINDOW_PERIOD) ) /* COV_SBC_LL_HW_SPI_ERR */
      {
        result = E_NOT_OK;
      }
    }
  }
  return result;
}

# if defined(SBC_30_FS85_WDTYPECHALLENGER)
/*********************************************************************************************************************
 * Sbc_Ll_ComputeWdgAnswer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SBC_LOCAL_INLINE FUNC(uint32, SBC_30_FS85_CODE) Sbc_Ll_ComputeWdgAnswer(uint32 lFsrVal)
{
  uint32 tmpVal;

  /* #10 Compute watchdog answer */
  tmpVal = (uint32) (  SBC_LL_REG_MASK_DATA & (((uint32)~(uint32)(((((uint32)lFsrVal) << 2u /*mul4*/) + 6u) - 4u)) >> 2u /*div4*/)  );

  return (uint32)(tmpVal);
}
# endif

/*********************************************************************************************************************
 * Sbc_Ll_Wdg_GetWdgRegValue
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SBC_LOCAL_INLINE FUNC(uint32, SBC_30_FS85_CODE) Sbc_Ll_Wdg_GetWdgRegValue(Sbc_IdType dId, Sbc_IdType pId, Sbc_WdgModeType mode)
{
  uint32 value;
  
  /* #10 Get the register value for mode change */
  if (mode == SBC_WDG_MODE_SLOW)
  {
    value = ((uint32)Sbc_Ll_Cfg_GetWdgValueSlow(dId, pId));
  }
  else /* FAST Mode: only SLOW and FAST Mode are valid. Invalid ones are blocked by core DET check */
  {
    value = ((uint32)Sbc_Ll_Cfg_GetWdgValueFast(dId, pId));
  }

  return value;
}
#endif /* SBC_30_FS85_ENABLE_WDG */



/*********************************************************************************************************************
 * Sbc_Ll_ComputeCRC
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SBC_LOCAL_INLINE FUNC(uint32, SBC_30_FS85_CODE) Sbc_Ll_ComputeCRC(uint32 cmd)
{
  uint32 cmdcrc;
  uint8 crc = 0u;
  uint8 crcArr[8];
  uint8 i;

  /* #10 Compute CRC of SPI command */
  crcArr[7] = Sbc_ll_GetBit(cmd,31u)^Sbc_ll_GetBit(cmd,24u)^Sbc_ll_GetBit(cmd,23u)^Sbc_ll_GetBit(cmd,22u)^Sbc_ll_GetBit(cmd,20u)^Sbc_ll_GetBit(cmd,17u)^Sbc_ll_GetBit(cmd,13u)^Sbc_ll_GetBit(cmd,12u)^Sbc_ll_GetBit(cmd,11u); /* SBSW_SBC_ARRAY_ACCESS_CONSTANT */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
  crcArr[6] = Sbc_ll_GetBit(cmd,31u)^Sbc_ll_GetBit(cmd,30u)^Sbc_ll_GetBit(cmd,23u)^Sbc_ll_GetBit(cmd,22u)^Sbc_ll_GetBit(cmd,21u)^Sbc_ll_GetBit(cmd,19u)^Sbc_ll_GetBit(cmd,16u)^Sbc_ll_GetBit(cmd,12u)^Sbc_ll_GetBit(cmd,11u)^Sbc_ll_GetBit(cmd,10u); /* SBSW_SBC_ARRAY_ACCESS_CONSTANT */ /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
  crcArr[5] = Sbc_ll_GetBit(cmd,30u)^Sbc_ll_GetBit(cmd,29u)^Sbc_ll_GetBit(cmd,22u)^Sbc_ll_GetBit(cmd,21u)^Sbc_ll_GetBit(cmd,20u)^Sbc_ll_GetBit(cmd,18u)^Sbc_ll_GetBit(cmd,15u)^Sbc_ll_GetBit(cmd,11u)^Sbc_ll_GetBit(cmd,10u)^Sbc_ll_GetBit(cmd,9u); /* SBSW_SBC_ARRAY_ACCESS_CONSTANT */
  crcArr[4] = Sbc_ll_GetBit(cmd,29u)^Sbc_ll_GetBit(cmd,28u)^Sbc_ll_GetBit(cmd,21u)^Sbc_ll_GetBit(cmd,20u)^Sbc_ll_GetBit(cmd,19u)^Sbc_ll_GetBit(cmd,17u)^Sbc_ll_GetBit(cmd,14u)^Sbc_ll_GetBit(cmd,10u)^Sbc_ll_GetBit(cmd,9u)^Sbc_ll_GetBit(cmd,8u); /* SBSW_SBC_ARRAY_ACCESS_CONSTANT */
  crcArr[3] = Sbc_ll_GetBit(cmd,28u)^Sbc_ll_GetBit(cmd,27u)^Sbc_ll_GetBit(cmd,24u)^Sbc_ll_GetBit(cmd,23u)^Sbc_ll_GetBit(cmd,22u)^Sbc_ll_GetBit(cmd,19u)^Sbc_ll_GetBit(cmd,18u)^Sbc_ll_GetBit(cmd,17u)^Sbc_ll_GetBit(cmd,16u)^Sbc_ll_GetBit(cmd,12u)^Sbc_ll_GetBit(cmd,11u)^Sbc_ll_GetBit(cmd,9u)^Sbc_ll_GetBit(cmd,8u)^1u; /* SBSW_SBC_ARRAY_ACCESS_CONSTANT */
  crcArr[2] = Sbc_ll_GetBit(cmd,27u)^Sbc_ll_GetBit(cmd,26u)^Sbc_ll_GetBit(cmd,24u)^Sbc_ll_GetBit(cmd,21u)^Sbc_ll_GetBit(cmd,20u)^Sbc_ll_GetBit(cmd,18u)^Sbc_ll_GetBit(cmd,16u)^Sbc_ll_GetBit(cmd,15u)^Sbc_ll_GetBit(cmd,13u)^Sbc_ll_GetBit(cmd,12u)^Sbc_ll_GetBit(cmd,10u)^Sbc_ll_GetBit(cmd,8u)^1u; /* SBSW_SBC_ARRAY_ACCESS_CONSTANT */
  crcArr[1] = Sbc_ll_GetBit(cmd,26u)^Sbc_ll_GetBit(cmd,25u)^Sbc_ll_GetBit(cmd,24u)^Sbc_ll_GetBit(cmd,22u)^Sbc_ll_GetBit(cmd,19u)^Sbc_ll_GetBit(cmd,15u)^Sbc_ll_GetBit(cmd,14u)^Sbc_ll_GetBit(cmd,13u)^Sbc_ll_GetBit(cmd,9u)^1u; /* SBSW_SBC_ARRAY_ACCESS_CONSTANT */
  crcArr[0] = Sbc_ll_GetBit(cmd,25u)^Sbc_ll_GetBit(cmd,24u)^Sbc_ll_GetBit(cmd,23u)^Sbc_ll_GetBit(cmd,21u)^Sbc_ll_GetBit(cmd,18u)^Sbc_ll_GetBit(cmd,14u)^Sbc_ll_GetBit(cmd,13u)^Sbc_ll_GetBit(cmd,12u)^Sbc_ll_GetBit(cmd,8u); /* SBSW_SBC_ARRAY_ACCESS_CONSTANT */

  /* #20 Convert bits of CRC array to uint8 value */
  for (i = 0u; i < 8u; i++) {
    crc |= (uint8) ( (uint8) ( crcArr[i] ) << i );
  }

  /* #30 Add crc to SPI cmd */
  cmdcrc = (cmd | crc);

  return cmdcrc;
}

/*********************************************************************************************************************
 * Sbc_Ll_RwRegister
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
SBC_LOCAL FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_Ll_RwRegister(
    Sbc_IdType dId, uint32 out, P2VAR(uint32, AUTOMATIC, SBC_30_FS85_APPL_DATA) in)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result;
  uint32 outCrc;
#if defined(SBC_30_FS85_RXCRCCHECK)
  uint32 crcCheck;
#endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compute CRC byte */
  outCrc = Sbc_Ll_ComputeCRC(out);


  Sbc_EnterCritical(SBC_EXCLUSIVE_AREA_3);
  /* >>> CRITICAL SECTION START >>> */

  /* #20 Copy SPI command to external output buffer */
  Sbc_Ll_SpiOutBuffer[dId]   = (uint16)(outCrc >> 16u); /* SBSW_SBC_VALID_DID */
  Sbc_Ll_SpiOutBuffer[dId+1u] = (uint16)(outCrc); /* SBSW_SBC_VALID_DID */

  /* #30 Trigger synchronous SPI transfer */
  result = Sbc_SpiSyncTransmit(Sbc_Ll_Cfg_GetSpiSequence(dId));

  /* #40 Copy value external input buffer to SPI answer, independently of SPI return value  */
  if (in != NULL_PTR)
  {
#if defined(SBC_30_FS85_RXCRCCHECK)
    crcCheck = (uint32)((((uint32)Sbc_Ll_SpiInBuffer[dId]<<16u)|(uint32)Sbc_Ll_SpiInBuffer[dId+1u]));
    if(crcCheck == Sbc_Ll_ComputeCRC(crcCheck&(~SBC_LL_REG_MASK_CRC))) /* COV_SBC_LL_HW_SPI_ERR */
    {
#endif
    *in = (uint32)(SBC_LL_REG_MASK_DATA&(((uint32)Sbc_Ll_SpiInBuffer[dId]<<16u)|(uint32)Sbc_Ll_SpiInBuffer[dId+1u])); /* SBSW_SBC_VALID_INPTR */
#if defined(SBC_30_FS85_RXCRCCHECK)
    }
    else
    {
      result |= E_NOT_OK;
    }
#endif
  }
  /* #50 Copy status information field to software buffer */
  Sbc_Ll_RegState[dId].SIF = (uint8)(Sbc_Ll_SpiInBuffer[dId] >> 8u); /* SBSW_SBC_VALID_DID */

  /* <<< CRITICAL SECTION END <<< */
  Sbc_LeaveCritical(SBC_EXCLUSIVE_AREA_3);

  return result;
}

#define SBC_30_FS85_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */



#define SBC_30_FS85_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Sbc_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, SBC_30_FS85_CODE) Sbc_30_Fs85_InitMemory(void)
{

  /* ----- Implementation ----------------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
  Sbc_ModuleInitialized = SBC_UNINIT;
#endif

} /* Sbc_InitMemory() */


/*********************************************************************************************************************
 * Sbc_Init()
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
FUNC(void, SBC_30_FS85_CODE) Sbc_30_Fs85_Init( P2CONST(Sbc_30_Fs85_ConfigType, AUTOMATIC, SBC_30_FS85_PBCFG) ConfigPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SBC_E_NO_ERROR;
  Std_ReturnType deviceResult;
  Sbc_IdType dId;

#if defined(SBC_30_FS85_ENABLE_WDG)
  Sbc_IdType pId;
#endif

  /* ----- Development Error Checks ------------------------------------- */
#if (SBC_30_FS85_USE_INIT_POINTER == STD_ON) /* COV_SBC_LL_POSTBUILD_SELECTABLE */
  /* #10 Store the configuration pointer. (Required before any check) */
  Sbc_30_Fs85_ConfigDataPtr = ConfigPtr;
#endif

#if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if SBC driver is in an uninitialized state */
  if ( Sbc_IsModuleInitialized() )
  {
    /* Module is already initialized. */
    errorId = SBC_E_ALREADY_INITIALIZED;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #30 Loop over all SBC instances */
    for (dId = 0; dId < Sbc_Cfg_GetNumberOfDevices(); dId++)
    {
      /* #40 Reset the software states of all SBC instances and all of their peripherals */

      /* Reset the system data. No need for a critical area here as module is not initialized. */
      Sbc_Rt_GetSystemStatus(dId).Events = 0; /* SBSW_SBC_DEVICE_INIT_LOOP */
      Sbc_Rt_GetSystemStatus(dId).States = 0; /* SBSW_SBC_DEVICE_INIT_LOOP */
      Sbc_Rt_GetSystemStatus(dId).Mode = SBC_SYS_MODE_NORMAL; /* SBSW_SBC_DEVICE_INIT_LOOP */



#if defined(SBC_30_FS85_ENABLE_WDG)
      /* Initialize mode of Wdg(s): Wdg modes are hw dependent and must be set in Sbc_Ll_InitDevice() or by watchdog driver */
      for (pId = 0; pId < Sbc_Cfg_GetNumberOfWdg(dId); pId++)
      {
# if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
        if (pId < SBC_30_FS85_MAX_NUMBER_OF_WDG) /* COV_SBC_INVALID_PID */
# endif
        {
          Sbc_Rt_SetWdgMode(dId, pId, SBC_WDG_MODE_INVALID); /* SBSW_SBC_PERIPHERAL_INIT_LOOP */
        }
# if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
        else
        {
          errorId = SBC_E_PARAM_ID;
        }
# endif
      }
#endif

      /* #50 Initialize hardware specific parts of SBC instance */
      deviceResult = Sbc_Ll_InitDevice(dId);

      /* #60 If hardware specific parts of SBC instance is not initialized successfully */
      if ( deviceResult == E_NOT_OK )
      {
        /* #70 Set the error flag and cancel initialization loop */
        errorId = SBC_E_INITIALIZATION_FAILED;

        /* leave the loop over Sbc devices */
        break;
      }
#if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
      else
      {
        /* Initialization was successful. */
        Sbc_ModuleInitialized = SBC_INIT;
      }
#endif
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != SBC_E_NO_ERROR )
  {
    (void) Det_ReportError(SBC_30_FS85_MODULE_ID, SBC_30_FS85_INSTANCE_ID_DET, SBC_SID_INIT, errorId);
  }
#else
  SBC_30_FS85_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif

#if (SBC_30_FS85_USE_INIT_POINTER == STD_OFF) /* COV_SBC_LL_POSTBUILD_SELECTABLE */
  SBC_30_FS85_DUMMY_STATEMENT(ConfigPtr); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif

} /* Sbc_Init() */ /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */




#if ( SBC_30_FS85_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  Sbc_GetVersionInfo()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SBC_30_FS85_CODE) Sbc_30_Fs85_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, SBC_30_FS85_APPL_DATA) versioninfo)
{
  uint8 errorId = SBC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter versioninfo */
  if ( !Sbc_IsPtrValid(versioninfo) )
  {
    errorId = SBC_E_PARAM_VERSIONINFO;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Fill versions from defines into versioninfo structure  */
    versioninfo->vendorID         = ( SBC_30_FS85_VENDOR_ID );         /* SBSW_SBC_VERSIONINFO */
    versioninfo->moduleID         = ( SBC_30_FS85_MODULE_ID );         /* SBSW_SBC_VERSIONINFO */
    versioninfo->sw_major_version = ( SBC_30_FS85_SW_MAJOR_VERSION );  /* SBSW_SBC_VERSIONINFO */
    versioninfo->sw_minor_version = ( SBC_30_FS85_SW_MINOR_VERSION );  /* SBSW_SBC_VERSIONINFO */
    versioninfo->sw_patch_version = ( SBC_30_FS85_SW_PATCH_VERSION );  /* SBSW_SBC_VERSIONINFO */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (SBC_30_FS85_DEV_ERROR_REPORT == STD_ON)
  if (errorId != SBC_E_NO_ERROR)
  {
    (void) Det_ReportError(SBC_30_FS85_MODULE_ID, SBC_30_FS85_INSTANCE_ID_DET, SBC_SID_GETVERSIONINFO, errorId);
  }
# else
  SBC_30_FS85_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
# endif

} /* Sbc_GetVersionInfo() */
#endif

/*********************************************************************************************************************
 * Sbc_SetMode
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
 */
FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_30_Fs85_SetMode(Sbc_IdType id, Sbc_SystemModeType mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SBC_E_NO_ERROR;
  Std_ReturnType result = E_NOT_OK;
  Sbc_IdType dId;

  /* ----- Development Error Checks ------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if SBC driver is initialized and parameters 'id' and 'mode' are valid */
  if ( !Sbc_IsModuleInitialized() )
  {
    errorId = SBC_E_UNINIT;
  }
  else if (!Sbc_IsIdValid(id) ) /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
  {
    errorId = SBC_E_PARAM_ID;
  }
  else if ( !Sbc_IsSysModeValid(mode) )
  {
    errorId = SBC_E_PARAM_MODE;
  }
  else
#endif
  {
  /* ----- Implementation ----------------------------------------------- */
    /* Get the device id */
    dId = Sbc_GetDeviceIndex(id);

    /* #20 If mode change is possible */
    if ( Sbc_Ll_Sys_CanSetMode(dId, mode) == E_OK )
    {
      /* #30 Change the operation mode */
      result = Sbc_Ll_Sys_SetMode(dId, mode);

      /* #40 If mode was changed successfully */
      if ( result == E_OK )
      {
        Sbc_EnterCritical(SBC_EXCLUSIVE_AREA_0);
        /* >>> CRITICAL AREA START >>> */

        /* #50 Store the operation mode */
        Sbc_Sys_St_SetMode(&Sbc_Rt_GetSystemStatus(dId), mode); /* SBSW_SBC_VALID_DID_DET */

        /* #60 Clear POR event if mode is changed to NORMAL mode */
        if (SBC_SYS_MODE_NORMAL == mode)
        {
          Sbc_Ev_Clr(&Sbc_Rt_GetSystemStatus(dId), SBC_SYS_EV_POR); /* SBSW_SBC_VALID_DID_DET */
        }

        /* <<< CRITICAL AREA END <<< */
        Sbc_LeaveCritical(SBC_EXCLUSIVE_AREA_0);
      }
      else
      {
        /* Communication failed */
        errorId = SBC_E_COMMUNICATION;
      }

    }
    else
    {
      /* Mode change not possible */
      errorId = SBC_E_INVALID_STATE;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_REPORT == STD_ON)
  if (errorId != SBC_E_NO_ERROR)
  {
    (void) Det_ReportError(SBC_30_FS85_MODULE_ID, SBC_30_FS85_INSTANCE_ID_DET, SBC_SID_SETMODE, errorId);
  }
#else
  SBC_30_FS85_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif

  return result;
} /* Sbc_SetMode() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/*********************************************************************************************************************
 * Sbc_GetStatus
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
FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_30_Fs85_GetStatus(Sbc_IdType id, P2VAR(Sbc_SystemStatusType, AUTOMATIC, SBC_30_FS85_APPL_DATA) status)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SBC_E_NO_ERROR;
  Std_ReturnType result = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Sbc_IdType dId;
  Sbc_SystemStatusType tempStatus;

  /* ----- Development Error Checks ------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if SBC driver is initialized and parameters 'id' and 'status' are valid */
  if ( !Sbc_IsModuleInitialized() )
  {
    errorId = SBC_E_UNINIT;
  }
  else if ( !Sbc_IsIdValid(id) ) /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
  {
    errorId = SBC_E_PARAM_ID;
  }
  else if ( !Sbc_IsPtrValid(status) )
  {
    errorId = SBC_E_PARAM_STATUS;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* Get the device id */
    dId = Sbc_GetDeviceIndex(id);

    tempStatus.Events = 0;
    tempStatus.States = 0;
    /* Preserve the current mode. LL may overwrite it */
    tempStatus.Mode = Sbc_Rt_GetSystemStatus(dId).Mode;

    /* #20 Query the status from hardware */
    result = Sbc_Ll_Sys_ReadStatus(dId, &tempStatus); /* SBSW_SBC_LOCALPTR_PARAM */

    /* #30 If status was read from hardware successfully */
    if ( result == E_OK )
    {
      Sbc_EnterCritical(SBC_EXCLUSIVE_AREA_0);
      /* >>> CRITICAL AREA START >>> */

      /* #40 Update the global status */
      /* PRQA S 2985 1 */ /* MD_Sbc_2985_LowLevelSpecific */
      Sbc_UpdateStatusFlags(&Sbc_Rt_GetSystemStatus(dId), tempStatus); /* SBSW_SBC_VALID_DID_DET */ /* SBSW_SBC_VALID_DID_DET */ /* SBSW_SBC_VALID_DID_DET */

      /* #50 Copy it to the return value */
      *status = Sbc_Rt_GetSystemStatus(dId); /* SBSW_SBC_VALID_STATUSPTR */

      /* <<< CRITICAL AREA END <<< */
      Sbc_LeaveCritical(SBC_EXCLUSIVE_AREA_0);
    }
    else
    {
      /* Communication was not possible */
      errorId = SBC_E_COMMUNICATION;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_REPORT == STD_ON)
  if (errorId != SBC_E_NO_ERROR)
  {
    (void) Det_ReportError(SBC_30_FS85_MODULE_ID, SBC_30_FS85_INSTANCE_ID_DET, SBC_SID_GETSTATUS, errorId);
  }
#else
  SBC_30_FS85_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif

  return result;
} /* Sbc_GetStatus() */


/*********************************************************************************************************************
 * Sbc_ClearEvents
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
Std_ReturnType Sbc_30_Fs85_ClearEvents(Sbc_IdType id, Sbc_SystemEventType events)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SBC_E_NO_ERROR;
  Std_ReturnType result = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Sbc_IdType dId;
  Sbc_SystemStatusType tempStatus;

  /* ----- Development Error Checks ------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if SBC driver is initialized and parameter 'id' is valid */
  if ( !Sbc_IsModuleInitialized() )
  {
    errorId = SBC_E_UNINIT;
  }
  else if ( !Sbc_IsIdValid(id) ) /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
  {
    errorId = SBC_E_PARAM_ID;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* Get the device id */
    dId = Sbc_GetDeviceIndex(id);

    tempStatus.Events = 0;
    /* Preserve the current mode and state */
    tempStatus.States = Sbc_Rt_GetSystemStatus(dId).States;
    tempStatus.Mode = Sbc_Rt_GetSystemStatus(dId).Mode;

    /* #20 Clear the flags from hardware */
    result = Sbc_Ll_Sys_ClearEvents(dId, &tempStatus, events); /* SBSW_SBC_LOCALPTR_PARAM */

    /* #30 If events are cleared from hardware successfully */
    if ( result == E_OK )
    {
      Sbc_EnterCritical(SBC_EXCLUSIVE_AREA_0);
      /* >>> CRITICAL AREA START >>> */

      /* #40 Update the global status with the newly read flags */
       /* PRQA S 2985 1 */ /* MD_Sbc_2985_LowLevelSpecific */
      Sbc_UpdateStatusFlags(&Sbc_Rt_GetSystemStatus(dId), tempStatus); /* SBSW_SBC_VALID_DID_DET */ /* SBSW_SBC_VALID_DID_DET */ /* SBSW_SBC_VALID_DID_DET */

      /* #50 Clear the status flags */
      Sbc_ClearEventFlags(&Sbc_Rt_GetSystemStatus(dId), events); /* SBSW_SBC_VALID_DID_DET */

      /* <<< CRITICAL AREA END <<< */
      Sbc_LeaveCritical(SBC_EXCLUSIVE_AREA_0);
    }
    else
    {
      /* Communication not possible */
      errorId = SBC_E_COMMUNICATION;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_REPORT == STD_ON)
  if (errorId != SBC_E_NO_ERROR)
  {
    (void) Det_ReportError(SBC_30_FS85_MODULE_ID, SBC_30_FS85_INSTANCE_ID_DET, SBC_SID_CLEAREVENTS, errorId);
  }
#else
  SBC_30_FS85_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif

  return result;
} /* Sbc_ClearEvents() */

/*********************************************************************************************************************
 * Sbc_AccessRegister()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_30_Fs85_AccessRegister(Sbc_IdType id, Sbc_SpiDataWidth spiCommand, P2VAR(Sbc_SpiDataWidth, AUTOMATIC, SBC_30_FS85_APPL_DATA) spiAnswer)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SBC_E_NO_ERROR;
  Std_ReturnType result = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Sbc_IdType dId;

  /* ----- Development Error Checks ------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if SBC driver is initialized and parameters 'id' and 'spiAnswer' are valid */
  if ( !Sbc_IsModuleInitialized() )
  {
    errorId = SBC_E_UNINIT;
  }
  else if ( !Sbc_IsIdValid(id) ) /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */
  {
    errorId = SBC_E_PARAM_ID;
  }
  else if ( !Sbc_IsPtrValid(spiAnswer) )
  {
    errorId = SBC_E_PARAM_SPIANSWER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* Get the device id */
    dId = Sbc_GetDeviceIndex(id);

    /* #20 Initiates SPI transfer to SBC module */
    result = Sbc_Ll_Sys_AccessRegister(dId, spiCommand, spiAnswer); /* SBSW_SBC_PTR_PARAM */
    if (result == E_NOT_OK)
    {
      errorId = SBC_E_COMMUNICATION;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_REPORT == STD_ON)
  if (errorId != SBC_E_NO_ERROR)
  {
    (void) Det_ReportError(SBC_30_FS85_MODULE_ID, SBC_30_FS85_INSTANCE_ID_DET, SBC_SID_ACCESS_REGISTER, errorId);
  }
#else
  SBC_30_FS85_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif

  return result;
} /* Sbc_AccessRegister() */




#if defined(SBC_30_FS85_ENABLE_WDG)
/*********************************************************************************************************************
 * Sbc_Wdg_SetMode
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
FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_30_Fs85_Wdg_SetMode(Sbc_PeripheralIdType id, Sbc_WdgModeType mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SBC_E_NO_ERROR;
  Sbc_IdType dId, pId;
  Std_ReturnType result = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if SBC driver is initialized and parameters 'id' and 'mode' are valid */
  if ( !Sbc_IsModuleInitialized() )
  {
    errorId = SBC_E_UNINIT;
  }
  else if ( !Sbc_IsWdgIdValid(id) ) /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */ /* COV_SBC_INVALID_PID */
  {
    errorId = SBC_E_PARAM_ID;
  }
  else if ( !Sbc_IsWdgModeValid(mode) )
  {
    errorId = SBC_E_PARAM_MODE;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* Get the device and peripheral id */
    dId = Sbc_GetDeviceIndex(id);
    pId = Sbc_GetPeriphalIndex(id); /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */

    /* #20 If the requested mode is supported */
    
    /* PRQA S 2991,2995 1 */ /* MD_Sbc_2991_2995_LowLevelSpecific */
    if ( Sbc_Ll_Wdg_CanSetMode(dId, pId, mode) == E_OK ) /* COV_SBC_WDG_CANSETMODE */
    {

      /* #30 If requested mode == current mode */
      if (Sbc_Rt_GetWdgMode(dId, pId) == mode)
      {
        /* #40 Do not change the mode in hardware, just return E_OK */
        result = E_OK;
      }
      /* #50 If requested mode != current mode */
      else
      {
        /* #60 Change the operation mode */
        result = Sbc_Ll_Wdg_SetMode(dId, pId, mode);

        /* #70 Store the operation mode if mode was changed successfully */

        /* PRQA S 2991,2995 1 */ /* MD_Sbc_2991_2995_LowLevelSpecific */
        if (result == E_OK) /* COV_SBC_LL_HW_SPI_ERR */
        {
          Sbc_Rt_SetWdgMode(dId, pId, mode); /* SBSW_SBC_VALID_DID_PID_DET */
        }
        else
        {
          /* mode change failed: set error id */
          errorId = SBC_E_COMMUNICATION;
        }
      }
    }
    else
    {
      /* The mode change is not allowed */
      errorId = SBC_E_MODE_FAILED;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_REPORT == STD_ON)
  if (errorId != SBC_E_NO_ERROR)
  {
    (void) Det_ReportError(SBC_30_FS85_MODULE_ID, SBC_30_FS85_INSTANCE_ID_DET, SBC_SID_WDG_SETMODE, errorId);
  }
#else
  SBC_30_FS85_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif

  return result;
} /* Sbc_Wdg_SetMode() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/*********************************************************************************************************************
 * Sbc_Wdg_Trigger
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SBC_30_FS85_CODE) Sbc_30_Fs85_Wdg_Trigger(Sbc_PeripheralIdType id)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SBC_E_NO_ERROR;
  Std_ReturnType result = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Sbc_IdType dId, pId;

  /* ----- Development Error Checks ------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if SBC driver is initialized and parameter 'id' is valid */
  if ( !Sbc_IsModuleInitialized() )
  {
    errorId = SBC_E_UNINIT;
  }
  else if ( !Sbc_IsWdgIdValid(id) ) /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */ /* COV_SBC_INVALID_PID */
  {
    errorId = SBC_E_PARAM_ID;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* Get the device and peripheral id */
    dId = Sbc_GetDeviceIndex(id);
    pId = Sbc_GetPeriphalIndex(id); /* PRQA S 2985 */ /* MD_Sbc_2985_2986_RedundantOperation */

#if (SBC_30_FS85_DEV_ERROR_DETECT == STD_ON)
    /* #20 Sbc_WdgTriggerFlag must be written to protect against Wrong Caller */
    Sbc_WdgTriggerFlag[dId][pId] = 1u; /* SBSW_SBC_VALID_DID_PID_DET */

    /* self-assignment to prevent compiler warning */
    /* PRQA S 1338,2983,3112 1 */ /* MD_MSR_DummyStmt */
    SBC_30_FS85_DUMMY_STATEMENT(Sbc_WdgTriggerFlag[dId][pId]); /* SBSW_SBC_VALID_DID_PID_DET */
#endif

    /* #30 Trigger the watchdog */
    result = Sbc_Ll_Wdg_Trigger(dId, pId);

    /* PRQA S 2992,2996 1 */ /* MD_Sbc_2992_2996_LowLevelSpecific */
    if (result == E_NOT_OK) /* COV_SBC_LL_WDG_TRIGGER_RETVAL */
    {
      errorId = SBC_E_COMMUNICATION;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (SBC_30_FS85_DEV_ERROR_REPORT == STD_ON)
  if (errorId != SBC_E_NO_ERROR)
  {
    (void) Det_ReportError(SBC_30_FS85_MODULE_ID, SBC_30_FS85_INSTANCE_ID_DET, SBC_SID_WDG_TRIGGER, errorId);
  }
#else
  SBC_30_FS85_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif

  return result;
} /* Sbc_Wdg_Trigger() */
#endif /* SBC_30_FS85_ENABLE_WDG */

#define SBC_30_FS85_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:

MD_Sbc_2985_2986_RedundantOperation: MISRA Rule 2.2
  Reason: This operation is redundant.
  - The application of a bit mask to a configured value of a certain range leads to a redundant operation.
  - A combined boolean expression where the result of an operation with higher precedence using a configured
    value as operand causes other operations of this expression to become redundant. Such a combined expression
    may result from macro expansion.
  - A macro argument with value '0' is used as an operand after macro expansion. (E.g. during calculation of
    SPI access commands / configuration getter function.)
  - Usage of an extended assignment operator (e.g. |=) leads to redundant operation in one specific preprocessor
    variant.
  Risk: No risk. The relevance of the operation may depend on the configuration (e.g. number of configured
        devices/peripherals).
  Prevention: -

MD_Sbc_2985_LowLevelSpecific: MISRA Rule 2.2
  Reason: This operation is redundant.
  - Redundance is given in case low-level implementation does not modify any data of the value of the passed status
    object.
  Risk: No risk. The relevance of the operation depends on LowLevel-specific implementation.
  Prevention: 

MD_Sbc_2991_2995_LowLevelSpecific
   Reason: The value of this 'if' controlling expression is always 'true'. 
   The result of this logical operation is always 'true'.
   - The derivative-specific implementation of the LowLevel returns a constant value. (For example the Sbc 
     derivative does not require control structures in called LowLevel function).
   Risk: No risk.
   Prevention: -
   
MD_Sbc_2992_2996_LowLevelSpecific
   Reason: The value of this 'if' controlling expression is always 'false'. 
   The result of this logical operation is always 'false'.
   - The derivative-specific implementation of the LowLevel returns a constant value. (For example the Sbc 
     watchdog is triggered by Dio access and never returns E_NOT_OK).
   Risk: No risk.
   Prevention: -

MD_Sbc_3218: MISRA Rule 8.9
  Reason: File scope static, 'Sbc_WdgTriggerFlag', only accessed in one function.
  Risk: No risk. Must be in file scope static so could be linked to a safe section for SafeBSW requirements.
  Prevention: Code inspection.


*/

/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_SBC_DEVICE_INIT_LOOP
 \DESCRIPTION Linear memory access using a for loop.
 \COUNTERMEASURE \R The for loop ensures that 'dId' never exceeds the size of the array because the loop
                from 0 to dimension of the array.

\ID SBSW_SBC_PERIPHERAL_INIT_LOOP
 \DESCRIPTION Linear memory access using a for loop.
 \COUNTERMEASURE \R The for loop ensures that 'dId' never exceeds the size of the first dimension of the array
                because the loop iterates from 0 to dimension of the array.
                'If-conditions' ensure that the 'pId' never exceeds the size of the second dimension of the array.

\ID SBSW_SBC_VALID_DID
 \DESCRIPTION Array access or function call using parameter 'dId'.
 \COUNTERMEASURE \N The caller ensures that the parameter 'dId' is valid.

\ID SBSW_SBC_VALID_DID_DET
 \DESCRIPTION Array access or function call using parameter 'dId'.
 \COUNTERMEASURE \R DET check (Sbc_IsIdValid) ensures that the parameter 'dId' is valid.

\ID SBSW_SBC_VALID_DID_PID
 \DESCRIPTION Array access or function call using parameter 'dId' and 'pId'.
 \COUNTERMEASURE \N The caller ensures that the parameter 'dId' and 'pId' is valid.

\ID SBSW_SBC_VALID_DID_PID_DET
 \DESCRIPTION Array access or function call using parameter 'dId' or 'pId'.
 \COUNTERMEASURE \R DET check (Sbc_IsCanTrcvIdValid, Sbc_IsLinTrcvIdValid or Sbc_IsWdgIdValid) ensures
                  that the parameter 'dId' and 'pId' is valid.

\ID SBSW_SBC_VALID_STATUSPTR
 \DESCRIPTION Array access or function call using pointer 'status'.
 \COUNTERMEASURE \N The caller ensures that the pointer 'status' that is used as parameter is valid.

\ID SBSW_SBC_VALID_SPIANSWERPTR
 \DESCRIPTION Array access or function call using pointer 'spiAnswer'.
 \COUNTERMEASURE \N The caller ensures that the pointer 'spiAnswer' that is used as parameter is valid.

\ID SBSW_SBC_VALID_INPTR
 \DESCRIPTION Array access or function call using parameter 'in'.
 \COUNTERMEASURE \N The caller ensures that the pointer 'in' that is used as parameter is valid.

\ID SBSW_SBC_VERSIONINFO
  \DESCRIPTION The function writes to the object referenced by parameter 'versioninfo'.
  \COUNTERMEASURE \N The caller ensures that the pointer passed to the parameter 'versioninfo' is valid and references
                    an object of type Std_VersionInfoType.

\ID SBSW_SBC_LOCALPTR_PARAM
  \DESCRIPTION Static functions are called with a local pointer as a parameter.
  \COUNTERMEASURE \N The static function is only called with valid pointers to local parameters.

\ID SBSW_SBC_PTR_PARAM
  \DESCRIPTION API functions are called with a pointer as a parameter.
  \COUNTERMEASURE \N The caller mist ensure that the pointer is valid.

\ID SBSW_SBC_NULLPTR_PARAM
  \DESCRIPTION Static function Sbc_Ll_RwRegister is called with a null pointer as a parameter.
  \COUNTERMEASURE \R A 'if-condition' ensures that in case of a null pointer the parameter 'in' is not used.

\ID SBSW_SBC_CALL_SPI_SETUPEB
  \DESCRIPTION SPI API function Spi_SetupEB is called with parameter 'Channel', 'SrcDataBufferPtr',
        'DesDataBufferPtr' and 'Length'.
  \COUNTERMEASURE \N SrcDataBufferPtr is a pointer to const and its content cannot be modified by the callee.
        For DesDataBufferPtr a pointer to one element of the Sbc_Ll_SpiOutBuffer is passed.
        The element identified by dId
        The caller of Sbc_Ll_InitDevice ensures that dId is smaller than the size of Sbc_Ll_SpiOutBuffer (SBC_NUMBER_OF_DEVICES).
        The length is always 1.

\ID SBSW_SBC_ARRAY_ACCESS_CONSTANT
   \DESCRIPTION Array access using a constant parameter.
   \COUNTERMEASURE \N The constant is secured by code inspection.

SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION

\ID COV_SBC_SINGLE_INSTANCE_API
  \ACCEPT TX
  \REASON For that release only single instance API is supported.

\ID COV_SBC_SPI_COMPATIBILITY
  \ACCEPT TX
  \REASON This is a compatibility define to manipulate SPI usage by user configuration file, if needed by SPI driver.
    The code is verified by code inspection.

\ID COV_SBC_LOCAL_SCOPE
  \ACCEPT TX
  \ACCEPT XF
  \REASON This defines an easier control of the compiler behaviour for functions in local scope.
    The code is verified by code inspection.

\ID COV_SBC_INVALID_PID
  \ACCEPT TX
  \ACCEPT TF tf tf tx
  \REASON The condition checks for invalid configured PID cannot be simulated. The code is verified by code inspection.

\ID COV_SBC_WDG_CANSETMODE
  \ACCEPT TX
  \REASON Some watchdog support all Wdg Modes (OFF, SLOW and FAST). So all Mode switches are supported. Invalid Mode values are blocked with DET check.
    The code is verified by code inspection.

\ID COV_SBC_UNUSED_MEM_SEC
  \ACCEPT TX
  \REASON Memory section is only used in generated data and not part of the static implementation, therefore not detected by coverage tooling. Fully covered.

COV_SBC_SPI_COMPATIBILITY is intentionally overwritten here because of hardware specific use case in this driver.
\ID COV_SBC_SPI_COMPATIBILITY
  \ACCEPT TX
  \ACCEPT XF
  \REASON This is a compatibility define to manipulate SPI usage by user configuration file, if needed by SPI driver.
    The code is verified by code inspection.

\ID COV_SBC_LL_EVENTS
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XX
  \REASON The condition checks for hardware failures that cannot be simulated. The code is verified by code inspection.

\ID COV_SBC_LL_HW_SPI_ERR
  \ACCEPT TX
  \ACCEPT XF
  \REASON Incorrect behaviour of HW or SPI error. This only occurs on SPI or HW failure. The code is verified by code inspection.

\ID COV_SBC_LL_INIT_FS_NOT_IN_ALL_CONFIG
  \ACCEPT TX
  \REASON A successful watchdog trigger WD_OK is required to leave INIT_FS, since SBC_30_FS85_ENABLE_WDG is not true for all configs, this condition is always true for these configurations.

\ID COV_SBC_LL_WDG_TRIGGER_RETVAL
  \ACCEPT XF
  \REASON The condition checks for communication error that cannot be simulated. The code is verified by code inspection.

\ID COV_SBC_LL_POSTBUILD_SELECTABLE
  \ACCEPT TX
  \ACCEPT XF
  \REASON The postbuild selectable function is only used for devices with CAN modules. 
          Since this Device has no CAN module, the part of the code is not used.

END_COVERAGE_JUSTIFICATION */

/* ********************************************************************************************************************
 *  END OF FILE: Sbc.c
 * *******************************************************************************************************************/
