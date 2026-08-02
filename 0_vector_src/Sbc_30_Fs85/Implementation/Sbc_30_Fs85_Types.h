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
/**        \file  Sbc_30_Fs85_Types.h
 *        \brief  System Basis Chip Implementation
 *
 *      \details  This file contains type and macro definitions of this SBC driver instance.
 *
 *********************************************************************************************************************/

#ifndef SBC_TYPES_H_
#define SBC_TYPES_H_

#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! \brief Specifies the compatibility version of this file */
#define SBC_TYPES_H_COMPAT_VERSION              0x0100u


/* ----- API service IDs ----- */
/*! \brief Service ID: Sbc_Init() */
#define SBC_SID_INIT                            (0x00u)
/*! \brief Service ID: Sbc_GetVersionInfo() */
#define SBC_SID_GETVERSIONINFO                  (0x10u)
/*! \brief Service ID: Sbc_SetMode() */
#define SBC_SID_SETMODE                         (0x20u)
/*! \brief Service ID: Sbc_GetStatus() */
#define SBC_SID_GETSTATUS                       (0x21u)
/*! \brief Service ID: Sbc_ClearEvents() */
#define SBC_SID_CLEAREVENTS                     (0x22u)
/*! \brief Service ID: Sbc_AccessRegister */
#define SBC_SID_ACCESS_REGISTER                 (0x24u)
/*! \brief Service ID: Sbc_CanTrcv_SetMode */
#define SBC_SID_CANTRCV_SETMODE                 (0x30u)
/*! \brief Service ID: Sbc_CanTrcv_ReadStatus */
#define SBC_SID_CANTRCV_READSTATUS              (0x31u)
/*! \brief Service ID: Sbc_CanTrcv_ClearEvents */
#define SBC_SID_CANTRCV_CLEAREVENTS             (0x32u)
/*! \brief Service ID: Sbc_CanTrcv_WritePnConfig */
#define SBC_SID_CANTRCV_WRITEPNCONFIG           (0x33u)
/*! \brief Service ID: Sbc_CanTrcv_EnableSelectiveWakeup */
#define SBC_SID_CANTRCV_ENABLESELECTIVEWAKEUP   (0x34u)
/*! \brief Service ID: Sbc_LinTrcv_SetMode */
#define SBC_SID_LINTRCV_SETMODE                 (0x40u)
/*! \brief Service ID: Sbc_LinTrcv_ReadStatus */
#define SBC_SID_LINTRCV_READSTATUS              (0x41u)
/*! \brief Service ID: Sbc_LinTrcv_ClearEvents */
#define SBC_SID_LINTRCV_CLEAREVENTS             (0x42u)
/*! \brief Service ID: Sbc_Wdg_SetMode */
#define SBC_SID_WDG_SETMODE                     (0x50u)
/*! \brief Service ID: Sbc_Wdg_Trigger */
#define SBC_SID_WDG_TRIGGER                     (0x51u)

/* ----- Error codes ----- */
/*! \deterror Error code: Used to check if no error occurred. */
# define SBC_E_NO_ERROR                         (0x00u)
/*! \deterror Error code: API service used with an invalid versionInfo pointer. */
#define SBC_E_PARAM_VERSIONINFO                 (0x09u)
/*! \deterror Error Code: API service used with an invalid SBC identifier. */
#define SBC_E_PARAM_ID                          (0x0Au)
/*! \deterror Error Code: API service used with an invalid mode */
#define SBC_E_PARAM_MODE                        (0x0Bu)
/*! \deterror Error Code: API service used with an invalid status */
#define SBC_E_PARAM_STATUS                      (0x0Cu)
/*! \deterror Error Code: API service used with an invalid SPI answer pointer */
#define SBC_E_PARAM_SPIANSWER                   (0x0Du)

/*! \deterror Error code: API service used without module initialization */
#define SBC_E_UNINIT                            (0x10u)
/*! \deterror Error code: The service Sbc_Init() is called while the module is already initialized  */
#define SBC_E_ALREADY_INITIALIZED               (0x11u)
/*! \deterror Error code: API service called with NULL_PTR as parameter  */
#define SBC_E_NULL_POINTER                      (0x12u)
/*! \deterror Error code: The API is called while the SBC is in an invalid state. */
#define SBC_E_INVALID_STATE                     (0x13u)
/*! \deterror Error code: The initialization was not successful */
#define SBC_E_INITIALIZATION_FAILED             (0x14u)
/*! \deterror Error code:  No or invalid communication towards the hardware. */
#define SBC_E_COMMUNICATION                     (0x20u)
/*! \deterror Error code: Failed to set the peripheral mode */
#define SBC_E_MODE_FAILED                       (0x21u)

/* ----- Modes ----- */
#define SBC_UNINIT                              (0x00u)
#define SBC_INIT                                (0x01u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/*!\brief       Convert a bit number to a mask */
#define SBC_B2M(bit)             (1u<<(bit))
/*!\brief       Convert a bit number to a negated mask */
#define SBC_B2NM(bit)            (~Sbc_Uti_Bit2Mask(bit))


/* **** Flag access **** */

/*!\brief       Returns whether an event is set */
#define Sbc_IsEvPending(flags, mask)        ( ( ((flags).Events) & (mask)) != 0 )
/*!\brief       Returns the state flag */
#define Sbc_GetStateBit(flags, mask)        ( ((flags).States) & (mask) )

#if defined(SBC_SOURCE)
/*!\brief        Clears an event bit */
# define Sbc_Ev_Clr(flags, mask)          ( (*(flags)).Events &= (uint8)(~(mask)) )
/*!\brief        Set an event bit */
# define Sbc_Ev_Set(flags, mask)          ( (*(flags)).Events |= (uint8)(mask) )
/*!\brief        Clears a state bit */
# define Sbc_St_Clr(flags, mask)          ( (*(flags)).States &= (uint8)(~(mask)) )
/*!\brief        Set a state bit */
# define Sbc_St_Set(flags, mask)          ( (*(flags)).States |= (uint8)(mask) )
#endif

/* *** System Status *** */

/*! \brief Power-on reset occurred.
 *         Clear condition: SBC is set to STANDBY mode.
 */
#define SBC_SYS_EV_POR      0x01u
/*! \brief An over-temperature error occurred. */
#define SBC_SYS_EV_TEMPFAIL 0x02u
/*! \brief An under-voltage error occurred. */
#define SBC_SYS_EV_UVERR    0x04u
/*! \brief An over-voltage error occurred. */
#define SBC_SYS_EV_OVERR    0x08u
/*! \brief A SPI failure occurred. */
#define SBC_SYS_EV_SPIFAIL  0x10u
/*! \brief A watchdog failure occurred. */
#define SBC_SYS_EV_WDFAIL   0x20u
/*! \brief An over-current error occurred. */
#define SBC_SYS_EV_OCERR    0x40u
/*! \brief Displays if there is any wake-up pending in this SBC.
 *         Clear condition: All wake-up events are cleared.
 */

/*! \brief Returns whether the POR event is pending in flags */
#define Sbc_Sys_Ev_IsPor(flags)       Sbc_IsEvPending(flags, SBC_SYS_EV_POR)
/*! \brief Returns whether the TEMPFAIL event is pending in flags */
#define Sbc_Sys_Ev_IsTempFail(flags)  Sbc_IsEvPending(flags, SBC_SYS_EV_TEMPFAIL)
/*! \brief Returns whether the UVERR event is pending in flags */
#define Sbc_Sys_Ev_IsUverr(flags)     Sbc_IsEvPending(flags, SBC_SYS_EV_UVERR)
/*! \brief Returns whether the OVERR event is pending in flags */
#define Sbc_Sys_Ev_IsOverr(flags)     Sbc_IsEvPending(flags, SBC_SYS_EV_OVERR)
/*! \brief Returns whether the SPIFAIL event is pending in flags */
#define Sbc_Sys_Ev_IsSpifail(flags)   Sbc_IsEvPending(flags, SBC_SYS_EV_SPIFAIL)
/*! \brief Returns whether the WDFAIL event is pending in flags */
#define Sbc_Sys_Ev_IsWdfail(flags)    Sbc_IsEvPending(flags, SBC_SYS_EV_WDFAIL)
/*! \brief Returns whether the OCERR event is pending in flags */
#define Sbc_Sys_Ev_IsOcerr(flags)     Sbc_IsEvPending(flags, SBC_SYS_EV_OCERR)

/*! \brief Displays that a wake-up event is currently pending */
#define SBC_SYS_ST_WAKEUP   0x01u

/*! \brief Returns the current mode that are stored in flags */
#define Sbc_Sys_St_GetMode(flags)     ((flags).Mode)
/*! \brief Returns the whether a wake-up is pending */
#define Sbc_Sys_St_GetWakeup(flags)   Sbc_GetStateBit(flags, SBC_SYS_ST_WAKEUP)

#if defined(SBC_INTERNAL)
/*! \brief Store the current system mode. */
# define Sbc_Sys_St_SetMode(flags, mode)      ((flags)->Mode = (mode))
/*! \brief Store the current wake-up state. */
# define Sbc_Sys_Set_SetWakeup(flags, wakeup) (Sbc_SetStateBit(flags, wakeup))
#endif

/* *** CanTrcv Status *** */
/*! \brief  This flag Indicate a wake-up that was caused by CAN bus activity.
 *  \note   This wake-up can be pending at the same time as SYSERR. Higher layer (i.e. CanTrcv)
 *          has to decide what to report as WU Reason in this case.
 *
 *          Clear condition:
 *          \li Transition to NORMAL
 *          \li Only if SWK is currently disabled: Transition NORMAL->STANDBY
 *          \li When in NORMAL mode: On Request
 */
#define SBC_CAN_EV_WAKEUP         0x01u
/*! \brief  Indicates whether a SYSERR was detected.
            Clear condition: PN initialization or on request.*/
#define SBC_CAN_EV_SYSERR         0x02u
/*! \brief  Indicates whether a bus timeout event was detected.
            Clear condition: On request only. */
#define SBC_CAN_EV_TIMEOUT        0x04u
/*! \brief  Indicates whether a bus error was detected.
            Clear condition: On request only. */
#define SBC_CAN_EV_BUSERR         0x08u
/*! \brief  Represents a local error such as short-circuits or over-temperature.
            Clear condition: On request only. */
#define SBC_CAN_EV_LOCALERR       0x10u

/*! \brief  Silent flag detected. */
#define SBC_CAN_ST_SILENT         0x01u

/*! \brief  Represents the state of the partial networking support. */
# define SBC_CAN_ST_PNEN          0x02u

/*! \brief  Represents whether the partial networking configuration is valid.
 *  \note   This must not represent the actual state of the hardware in each case. If the hardware
 *          clears the configuration valid for example after a wake-up and the configuration can be considered
 *          as still valid the flag may be forced by the driver implementation.
 */
# define SBC_CAN_ST_PNCOK         0x04u

#if defined(SBC_INTERNAL)
/*! \brief Store the current system mode. */
#  define Sbc_Can_St_SetMode(val, mode)    (val).Mode = (mode)
#endif /* SBC_SOURCE */

/** \brief Returns whether a \ref SBC_CAN_EV_WUF "WUF" event is pending in flags */
#define Sbc_Can_Ev_IsWakeup(flags)          Sbc_IsEvPending(flags, SBC_CAN_EV_WAKEUP)
/** \brief Returns whether a \ref SBC_CAN_EV_SYSERR "SYSERR" event is pending */
#define Sbc_Can_Ev_IsSyserr(flags)          Sbc_IsEvPending(flags, SBC_CAN_EV_SYSERR)
/** \brief Returns whether a \ref SBC_CAN_EV_TIMEOUT "TIMEOUT" event is pending */
#define Sbc_Can_Ev_IsTimeout(flags)         Sbc_IsEvPending(flags, SBC_CAN_EV_TIMEOUT)
/** \brief Returns whether a \ref SBC_CAN_EV_BUSERR "BUSERR" event is pending */
#define Sbc_Can_Ev_IsBuserr(flags)          Sbc_IsEvPending(flags, SBC_CAN_EV_BUSERR)
/** \brief Returns whether a \ref SBC_CAN_EV_LOCALERR "LOCALERR" event is pending */
#define Sbc_Can_Ev_IsLocalErr(flags)        Sbc_IsEvPending(flags, SBC_CAN_EV_LOCALERR)

/*! \brief Returns the current \ref Sbc_CanTrcvModeTypeTag "mode" that is stored in flags */
#define Sbc_Can_St_GetMode(flags)     ((flags).Mode)
/*! \brief Returns whether the bus is \ref SBC_CAN_ST_SILENT "silent" */
#define Sbc_Can_St_GetSilent(flags)   Sbc_GetStateBit(flags, SBC_CAN_ST_SILENT)
/*! \brief Returns whether \ref SBC_CAN_ST_PNEN "selective wake-up" is enabled */
#define Sbc_Can_St_GetPnen(flags)     Sbc_GetStateBit(flags, SBC_CAN_ST_PNEN)
/*! \brief Returns whether the selective wake-up configuration \ref SBC_CAN_ST_PNCOK "is valid" */
#define Sbc_Can_St_GetPncok(flags)    Sbc_GetStateBit(flags, SBC_CAN_ST_PNCOK)


/*! This flag indicates whether a wake-up occurred.
 * Clear condition: Mode transition to NORMAL or NORMAL->STANDBY or NORMAL->SLEEP or on request.
 */
#define SBC_LIN_EV_WAKEUP         0x01u
/*! \brief This flag indicates whether a bus error was detected (bus clamping, short-circuits on bus side, ...)
 *         Clear condition: On request only.
 */
#define SBC_LIN_EV_BUSERR         0x02u
/*! \brief Indicates whether a local error (over-temperature, under-voltage, short-circuits on TTL side,...) was
 *         detected.
 *         Clear condition: On request.
 */
#define SBC_LIN_EV_LOCALERR       0x04u

#if defined(SBC_INTERNAL)
/*! \brief Store the current system mode. */
# define Sbc_Lin_St_SetMode(val, mode)    (val).Mode = (mode)
#endif

/** \brief Returns whether a \ref SBC_LINN_EV_WUF "WUF" event is pending in flags */
#define Sbc_Lin_Ev_IsWakeup(flags)          Sbc_IsEvPending(flags, SBC_LIN_EV_WAKEUP)
/** \brief Returns whether a \ref SBC_LIN_EV_BUSERR "BUSERR" event is pending */
#define Sbc_Lin_Ev_IsBuserr(flags)          Sbc_IsEvPending(flags, SBC_LIN_EV_BUSERR)
/** \brief Returns whether a \ref SBC_LIN_EV_LOCALERR "LOCALERR" event is pending */
#define Sbc_Lin_Ev_IsLocalErr(flags)        Sbc_IsEvPending(flags, SBC_LIN_EV_LOCALERR)

#define Sbc_Lin_St_GetMode(flags)     ((flags).Mode)
/* PRQA L:Sbc_GlobalFunctionMacros_Tag */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Identifies a SBC instance. Encodes the SBC instance and a peripheral id */
typedef uint16 Sbc_IdType;

/* Identifies a specific peripheral */
typedef uint16 Sbc_PeripheralIdType;

/* System modes of the SBC */
typedef enum Sbc_SystemModeTypeTag
{
  SBC_SYS_MODE_INVALID = 0, /* For internal usage only */
  /* NORMAL mode of the system. */
  SBC_SYS_MODE_NORMAL,
  /* STANDBY mode of the system. */
  SBC_SYS_MODE_STANDBY,
  /* SLEEP mode of the system. */
  SBC_SYS_MODE_SLEEP
} Sbc_SystemModeType;

/* CanTrcv modes of the SBC */
typedef enum Sbc_CanTrcvModeTypeTag
{
  SBC_CANTRCV_MODE_OFF = 0, /* For internal usage only */
  /* The CAN transceiver is enabled and reflects the bus state */
  SBC_CANTRCV_MODE_NORMAL,
  /* The CAN transceiver is disabled. Wake-up detection is enabled. */
  SBC_CANTRCV_MODE_STANDBY
} Sbc_CanTrcvModeType;

/* LinTrcv modes of the SBC */
typedef enum Sbc_LinTrcvModeTypeTag
{
  SBC_LINTRCV_MODE_OFF = 0, /* For internal usage only */
  /* The LIN transceiver is enabled and reflects the bus state */
  SBC_LINTRCV_MODE_NORMAL,
  /* The CAN transceiver is disabled. Wake-up detection is enabled. */
  SBC_LINTRCV_MODE_STANDBY
} Sbc_LinTrcvModeType;

/* Wdg modes of the SBC */
typedef enum Sbc_WdgModeTypeTag
{
  SBC_WDG_MODE_INVALID = 0, /* For internal usage only */
  /* The watchdog is disabled. No triggering occurs. */
  SBC_WDG_MODE_OFF,
  /* The watchdog is configured in a slow mode with large trigger intervals (typically > 200ms) */
  SBC_WDG_MODE_SLOW,
  /* The watchdog is configured in the fast mode with small trigger intervals */
  SBC_WDG_MODE_FAST
} Sbc_WdgModeType;

/* Represents the events of a SBC instance. */
typedef uint16 Sbc_SystemEventType;

/* Stores the system status */
typedef struct Sbc_SystemStatusTypeTag
{
  /* Stores the events */
  Sbc_SystemEventType Events;
  /* Stores the states */
  uint8  States;
  /* Stores the current mode */
  Sbc_SystemModeType Mode;
} Sbc_SystemStatusType;

/* Represents the events of a CanTrcv driver instance. */
typedef uint16 Sbc_CanTrcvEventType;

/* This type represents the current state of a CAN transceiver instance.  */
typedef struct Sbc_CanTrcvStatusTypeTag
{
  /* Stores the events */
  Sbc_CanTrcvEventType Events;
  /* Stores the states */
  uint8  States;
  /* The configuration information of the CanTrcv. */
  Sbc_CanTrcvModeType Mode;
} Sbc_CanTrcvStatusType;

/* Represents the events of a LinTrcv driver instance. */
typedef uint16 Sbc_LinTrcvEventType;

/* This type represents the current state of a LIN transceiver instance.  */
typedef struct Sbc_LinTrcvStatusTypeTag
{
  /* Stores the events */
  Sbc_LinTrcvEventType Events;
  /* Stores the states */
  uint8 States;
  /* The current operation mode of the LinTrcv. */
  Sbc_LinTrcvModeType Mode;
} Sbc_LinTrcvStatusType;


#endif /* SBC_TYPES_H_ */
