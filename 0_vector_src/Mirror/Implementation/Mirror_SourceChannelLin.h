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
/*!     \file     Mirror_SourceChannelLin.h
 *      \brief    Mirror LIN source channel header file
 *
 *      \details  Header of implementation of LIN source channel.
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
#if !defined (MIRROR_SOURCECHANNELLIN_H)
# define MIRROR_SOURCECHANNELLIN_H

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

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTERSTATE == STD_ON))
/**********************************************************************************************************************
 * Mirror_SourceChannelLin_GetStaticFilterState()
 *********************************************************************************************************************/
/*! \brief       Returns the state of a pre-configured LIN filter.
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
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON and 
 *               MIRROR_SOURCECHANNELLINSTATICFILTERSTATE == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelLin_GetStaticFilterState(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 filterId, boolean* isActive);
#endif /* ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTERSTATE == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTERSTATE == STD_ON))
/**********************************************************************************************************************
 * Mirror_SourceChannelLin_SetStaticFilterState()
 *********************************************************************************************************************/
/*! \brief       Sets the state of a pre-configured LIN filter.
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
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON and
 *               MIRROR_SOURCECHANNELLINSTATICFILTERSTATE == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelLin_SetStaticFilterState(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 filterId, boolean isActive);
#endif /* ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINSTATICFILTERSTATE == STD_ON)) */

#if ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON))
/**********************************************************************************************************************
 * Mirror_SourceChannelLin_RemoveFilter()
 *********************************************************************************************************************/
/*! \brief       Removes a LIN filter that was added at runtime.
 *  \details     -
 *  \param[in]   sourceChannelIdx  Source bus to which the filter is attached
 *  \param[in]   filterId Id of the filter.
 *  \return      E_OK: Filter was removed.
 *  \return      E_NOT_OK: Function was called with invalid parameters.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE for different networks.
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON and
 *               MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelLin_RemoveFilter(Mirror_SizeOfSourceChannelLinType sourceChannelIdx, uint8 filterId);
#endif /* ((MIRROR_SOURCE_CHANNEL_LIN == STD_ON) && (MIRROR_SOURCECHANNELLINDYNAMICFILTER == STD_ON)) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 * Mirror_SourceChannelLin_Offline()
 *********************************************************************************************************************/
/*! \brief       Completely disables any mirroring activities on a LIN source channel.
 *  \details     -
 *  \param[in]   sourceChannelIdx  Internal index of the LIN source channel.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_SourceChannelLin_Offline(Mirror_SizeOfSourceChannelLinType sourceChannelIdx);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_StartSourceNetwork()
 *********************************************************************************************************************/
/*! \brief       Activates a LIN source bus.
 *  \details     -
 *  \param[in]   network    ComM channel.
 *  \return      E_OK: Source bus was activated.
 *  \return      E_NOT_OK: Function was called with invalid parameters
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE for different networks.
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelLin_StartSourceNetwork(NetworkHandleType network);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_StopSourceNetwork()
 *********************************************************************************************************************/
/*! \brief       Deactivates a LIN source bus.
 *  \details     -
 *  \param[in]   network    ComM channel.
 *  \return      E_OK: Source bus was deactivated.
 *  \return      E_NOT_OK: Function was called with invalid parameters.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE for different networks.
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SourceChannelLin_StopSourceNetwork(NetworkHandleType network);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_Init()
 *********************************************************************************************************************/
/*! \brief       Internal initialization function for source channel LIN.
 *  \details     Handles the initialization of a LIN source bus.
 *  \param[in]   sourceChannelIdx  Internal index of the LIN source channel.
 *  \param[in]   mirrorCtx Mirror context.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_APPL_CODE)Mirror_SourceChannelLin_Init(Mirror_SourceChannelLinIterType sourceChannelIdx, 
                                                         Mirror_GeneralContextType* mirrorCtx);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_SourceChannelLin_MainFunction()
 *********************************************************************************************************************/
/*! \brief       Internal main function for source channel LIN.
 *  \details     Handles the state of a LIN source bus.
 *  \param[in]   sourceChannelIdx  Internal index of the LIN source channel.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_APPL_CODE)Mirror_SourceChannelLin_MainFunction(Mirror_SourceChannelLinIterType sourceChannelIdx);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
*  Mirror_SourceChannelLin_InitMemory()
*********************************************************************************************************************/
/*! \brief      Function for *_INIT_*-variable initialization
 *  \details     Service to initialize source channel LIN global variables at power up. This function initializes the
 *               variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \pre         Module is uninitialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
*********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_SourceChannelLin_InitMemory(void);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

# define MIRROR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/

#endif /* MIRROR_SOURCECHANNELLIN_H */

/**********************************************************************************************************************
 *  END OF FILE: Mirror_SourceChannelLin.h
 *********************************************************************************************************************/
