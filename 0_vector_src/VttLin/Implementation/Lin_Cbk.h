
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *           File:  Lin_Cbk.h
 *      Component:  AUTOSAR LIN Driver
 *         Module:  DrvLin_VttCanoeAsr / DrvLin_CanoeemuAsr
 *      Generator:  DrvLin_VttCanoeAsr / DrvLin_CanoeemuAsr
 *
 *  Target system:  Canoe
 *       Compiler:  Ansi

 *    Derivatives:  VTT/EMU
 *
 *    Description:  CANoeApi Callbacks of the AUTOSAR LIN Driver
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (LIN_CBK_H)
# define LIN_CBK_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TYPE AND DEFINE DEFINITIONS FOR INTERNAL USE IN LIN DRIVER
 *********************************************************************************************************************/
# define LIN_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * Lin_CANoeEventHandler
 **********************************************************************************************************************/
/*! \brief      Event Handler used instead of interrupt.
 *  \details    -
 *  \param[in]  Channel Channel Id used from LinIf
 *  \param[in]  event OK (0), Error in header(1), Error(2), no response(3), wakeup(4)
 *  \param[in]  data Data of frame
 *  \pre        -
 *  \context    ANY
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) Lin_CANoeEventHandler(uint8 channel, uint8 event, uint8 data[]);

/**********************************************************************************************************************
 * Lin_CANoeOnMessageHandler
 **********************************************************************************************************************/
/*! \brief      Callback from CANoe. Assumption this is called if a Frame occurs on LIN Bus.
 *  \details    Try to remap the pattern to easy to use events.
 *  \param[in]  channel
 *  \param[in]  dir
 *  \param[in]  id
 *  \param[in]  dlc
 *  \param[in]  data
 *  \pre        -
 *  \context    ANY
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) Lin_CANoeOnMessageHandler(uint8 channel, uint8 dir, uint32 id, uint8 dlc, uint8 data[]);

/**********************************************************************************************************************
 * Lin_CANoeOnWakeupHandler
 **********************************************************************************************************************/
/*! \brief      Callback from CANoe. Assumption this is called if a Wake Up Frame occurs on LIN Bus.
 *  \details    Try to remap the pattern to easy to use events.
 *  \param[in]  channel
 *  \param[in]  external
 *  \pre        -
 *  \context    ANY
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) Lin_CANoeOnWakeupHandler(uint8 channel, uint8 external);

/**********************************************************************************************************************
 * Lin_CANoeOnSleepHandler
 **********************************************************************************************************************/
/*! \brief      This is a Callback handler and is called when Sleep Request Frame was sent on the bus.
 *  \details    Not used.
 *  \param[in]  channel
 *  \param[in]  external
 *  \param[in]  isAwake
 *  \param[in]  wasAwake
 *  \param[in]  reason
 *  \pre        -
 *  \context    ANY
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) Lin_CANoeOnSleepHandler(uint8 channel, uint8 external, uint8 isAwake, uint8 wasAwake, uint8 reason);

/**********************************************************************************************************************
 * Lin_CANoeOnErrorHandler
 **********************************************************************************************************************/
/*! \brief      Callback from CANoe. Assumption this is called if an error occurs on LIN Bus.
 *  \details    Try to remap the error pattern to easy to use events.
 *  \param[in]  channel
 *  \param[in]  errorCode
 *  \param[in]  subcode
 *  \param[in]  id
 *  \pre        -
 *  \context    ANY
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) Lin_CANoeOnErrorHandler(uint8 channel, uint32 errorCode, uint32 subcode, uint32 id);

# define LIN_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* LIN_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: Lin_Cbk.h
 *********************************************************************************************************************/
