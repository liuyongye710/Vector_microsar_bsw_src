/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!     \file     Mirror_SourceChannelCan.h
 *      \brief    Mirror CAN source channel header file
 *
 *      \details  Header of implementation of CAN source channel.
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
#if !defined (MIRROR_SOURCECHANNELCAN_H)
# define MIRROR_SOURCECHANNELCAN_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_Int.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
# define MIRROR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON))
/**********************************************************************************************************************
 * Mirror_SourceChannelCan_GetStaticFilterState()
 *********************************************************************************************************************/
/*! \brief       Returns the state of a pre-configured CAN filter.
 *  \details     -
 *  \param[in]   sourceChannelIdx  Source bus to which the filter is attached
 *  \param[in]   filterId Id of the filter.
 *  \param[out]  isActive Pointer to where to store the current filter state
 *  \return      E_OK: Filter state copied to isActive.
 *  \return      E_NOT_OK: Function was called with invalid parameters.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON and 
 *               MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelCan_GetStaticFilterState(Mirror_SizeOfSourceChannelCanType sourceChannelIdx, uint8 filterId, boolean* isActive);
#endif /* ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON))
/**********************************************************************************************************************
 * Mirror_SourceChannelCan_SetStaticFilterState()
 *********************************************************************************************************************/
/*! \brief       Sets the state of a pre-configured CAN filter.
 *  \details     -
 *  \param[in]   sourceChannelIdx Source bus to which the filter is attached
 *  \param[in]   filterId Id of the filter.
 *  \param[in]   isActive TRUE: Activate filter, FALSE: Deactivate filter
 *  \return      E_OK: Filter state updated from isActive
 *  \return      E_NOT_OK: Function was called with invalid parameters.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON and
 *               MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelCan_SetStaticFilterState(Mirror_SizeOfSourceChannelCanType sourceChannelIdx, uint8 filterId, boolean isActive);
#endif /* ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANSTATICFILTER == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON))
/**********************************************************************************************************************
 * Mirror_SourceChannelCan_RemoveFilter()
 *********************************************************************************************************************/
/*! \brief       Removes a CAN filter that was added at runtime.
 *  \details     -
 *  \param[in]   sourceChannelIdx  Source bus to which the filter is attached
 *  \param[in]   filterId Id of the filter.
 *  \return      E_OK: Filter was removed.
 *  \return      E_NOT_OK: Function was called with invalid parameters.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE for different networks.
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON and
 *               MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelCan_RemoveFilter(Mirror_SizeOfSourceChannelCanType sourceChannelIdx, uint8 filterId);
#endif /* ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCECHANNELCANDYNAMICFILTER == STD_ON)) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 * Mirror_SourceChannelCan_Offline()
 *********************************************************************************************************************/
/*! \brief       Completely disables any mirroring activities on a CAN source channel.
 *  \details     -
 *  \param[in]   sourceChannelIdx  Internal index of the CAN source channel.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_SourceChannelCan_Offline(Mirror_SizeOfSourceChannelCanType sourceChannelIdx);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelCan_StartSourceNetwork()
 *********************************************************************************************************************/
/*! \brief       Activates a CAN source bus.
 *  \details     -
 *  \param[in]   sourceChannelIdx    Internal source channel index corresponding to the source bus that shall be started.
 *  \return      E_OK: Source bus was activated.
 *  \return      E_NOT_OK: Function was called with invalid parameters
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE for different networks.
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelCan_StartSourceNetwork(Mirror_SizeOfSourceChannelCanType sourceChannelIdx);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelCan_StopSourceNetwork()
 *********************************************************************************************************************/
/*! \brief       Deactivates a CAN source bus.
 *  \details     -
 *  \param[in]   sourceChannelIdx    Internal source channel index corresponding to the source bus that shall be stopped.
 *  \return      E_OK: Source bus was deactivated.
 *  \return      E_NOT_OK: Function was called with invalid parameters.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE for different networks.
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelCan_StopSourceNetwork(Mirror_SizeOfSourceChannelCanType sourceChannelIdx);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelCan_Init()
 *********************************************************************************************************************/
/*! \brief       Internal initialization function for source channel CAN.
 *  \details     Handles the initialization of a CAN source bus.
 *  \param[in]   sourceChannelIdx  Internal index of the CAN source channel.
 *  \param[in]   mirrorCtx Mirror context.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE)Mirror_SourceChannelCan_Init(Mirror_SourceChannelCanIterType sourceChannelIdx, 
                                                    Mirror_GeneralContextType* mirrorCtx);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelCan_MainFunction()
 *********************************************************************************************************************/
/*! \brief       Internal main function for source channel CAN.
 *  \details     Handles the state of a CAN source bus.
 *  \param[in]   sourceChannelIdx  Internal index of the CAN source channel.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE)Mirror_SourceChannelCan_MainFunction(Mirror_SourceChannelCanIterType sourceChannelIdx);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelCan_InitMemory()
*********************************************************************************************************************/
/*! \brief       Function for *_INIT_*-variable initialization
 *  \details     Service to initialize source channel CAN global variables at power up. This function initializes the
 *               variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \pre         Module is uninitialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
*********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_SourceChannelCan_InitMemory(void);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

# define MIRROR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/

#endif /* MIRROR_SOURCECHANNELCAN_H */

/**********************************************************************************************************************
 *  END OF FILE: Mirror_SourceChannelCan.h
 *********************************************************************************************************************/
